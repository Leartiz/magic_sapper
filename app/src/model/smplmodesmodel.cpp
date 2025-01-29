#include "model/smplmodesmodel.h"

SmplModesModel::SmplModesModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_curIndx(0)

    , m_dbFacade(DBFacade::instance())
{
    prepareDModes();
}

void SmplModesModel::prepareDModes()
{
    m_dModes = m_dbFacade.selAllDModes();
    auto itCustomDMode = std::find_if(m_dModes.begin(), m_dModes.end(), [](const DescriptorMode& vl) {
        return vl.getMode() == WrMode::Custom;
    });
    m_dModes.erase(itCustomDMode);

    std::sort(m_dModes.begin(), m_dModes.end(), [](const DescriptorMode& lhs, const DescriptorMode& rhs) {
        return lhs.getAmBombs() < rhs.getAmBombs();
    });
}

int SmplModesModel::getModeIdByIndx(const int indx) const
{
    const int modeId = m_dModes[indx].getId().value();
    return modeId;
}

int SmplModesModel::getCurIndx() const
{
    return m_curIndx;
}

void SmplModesModel::setCurIndx(const int indx)
{
    m_curIndx = indx;

    emit curIndxChanged(m_curIndx);
    emit curModeIdChanged(getCurModeId());
}

int SmplModesModel::getCurModeId() const
{
    return m_dModes[getCurIndx()].getId().value();
}

int SmplModesModel::rowCount(const QModelIndex&) const
{
    return m_dModes.size();
}

QHash<int, QByteArray> SmplModesModel::roleNames() const
{
    return {
        { static_cast<int>(Roles::ModeId), QByteArray("ModeId") },
        { static_cast<int>(Roles::ModeEnum), QByteArray("ModeEnum") },
        { static_cast<int>(Roles::ModeName), QByteArray("ModeName") }
    };
}

QVariant SmplModesModel::data(const QModelIndex &index, int role) const
{
    if (index.column() != 0)
        return {};
    if (index.row() < 0 && index.row() >= rowCount())
        return {};

    switch (static_cast<Roles>(role))
    {
    case Roles::ModeId:
        return m_dModes[index.row()].getId().value();
    case Roles::ModeEnum:
        return static_cast<int>(m_dModes[index.row()].getMode());

    case Roles::ModeName:
        return m_dModes[index.row()].getName();
    }
    return {};
}
