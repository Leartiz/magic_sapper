#include <algorithm>

#include <QDebug>

#include "model/modesmodel.h"

ModesModel::ModesModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_dbFacade(DBFacade::instance())
{
    m_settgs = m_dbFacade.selSettgs();
    prepareDModes();
}

void ModesModel::prepareDModes()
{
    auto dModes = m_dbFacade.selAllDModes();
    {
        // in back!
        auto itCustomDMode = std::find_if(dModes.begin(), dModes.end(), [](const DescriptorMode& vl) {
            return vl.getMode() == WrMode::Custom;
        });
        const DescriptorMode customDMode = *itCustomDMode;
        dModes.erase(itCustomDMode);
        std::sort(dModes.begin(), dModes.end(), [](const DescriptorMode& lhs, const DescriptorMode& rhs) {
            return lhs.getAmBombs() < rhs.getAmBombs();
        });
        dModes.push_back(customDMode);
    }
    std::transform(dModes.begin(), dModes.end(), std::back_inserter(m_dModes), [](const DescriptorMode& vl) {
        return std::make_shared<DescriptorMode>(vl);
    });
    m_curDModeAndIndx = findCurDMode();
}

ModesModel::DModeAndIndx ModesModel::findCurDMode() const
{
    // always find!
    auto it = std::find_if(m_dModes.begin(), m_dModes.end(), [this](std::shared_ptr<DescriptorMode> pDm) {
        return pDm->getId().value() == m_settgs.getModeId().value();
    });
    if (it != m_dModes.end())
        return { *it, static_cast<int>(std::distance(m_dModes.begin(), it)) };
    qCritical() << "ModesModel, findCurDMode, find_if failed.";
    return {};
}

int ModesModel::getCurMode() const
{
    return m_curDModeAndIndx.first ? static_cast<int>(m_curDModeAndIndx.first->getMode()) : 0;
}

int ModesModel::getCurIndx() const
{
    return m_curDModeAndIndx.second.has_value() ? m_curDModeAndIndx.second.value() : 0;
}

void ModesModel::setCurModeId(const int modeId)
{
    m_settgs.setModeId(modeId);
    m_dbFacade.updSettgs(m_settgs); // fix!

    m_curDModeAndIndx = findCurDMode();
    emit curModeChanged(getCurMode());
    emit curIndxChanged(getCurIndx());
}

void ModesModel::updCustomDMode()
{
    {
        const auto customDModeId = m_dModes.back()->getId().value();
        const DescriptorMode customDMode = m_dbFacade.selDModeById(customDModeId);
        m_dModes.back() = std::make_shared<DescriptorMode>(customDMode);
    }
    const auto modelIndx = createIndex(rowCount() - 1, 0);
    emit dataChanged(modelIndx, modelIndx);
}

int ModesModel::rowCount(const QModelIndex&) const
{
    return m_dModes.size();
}

QVariant ModesModel::data(const QModelIndex &index, int role) const
{
    if (index.column() != 0)
        return {};
    if (index.row() < 0 && index.row() >= rowCount())
        return {};

    switch (static_cast<Roles>(role))
    {
    case Roles::ModeId:
        return m_dModes[index.row()]->getId().value();
    case Roles::ModeEnum:
        return static_cast<int>(m_dModes[index.row()]->getMode());
    case Roles::ModeName:
        return m_dModes[index.row()]->getName();

    case Roles::NumRows:
        return m_dModes[index.row()]->getSideSzs().first;
    case Roles::NumCols:
        return m_dModes[index.row()]->getSideSzs().second;
    case Roles::AmBombs:
        return m_dModes[index.row()]->getAmBombs();
    }
    return {};
}

QHash<int, QByteArray> ModesModel::roleNames() const
{
    return {
        { static_cast<int>(Roles::ModeId), QByteArray("ModeId") },
        { static_cast<int>(Roles::ModeName), QByteArray("ModeName") },
        { static_cast<int>(Roles::ModeEnum), QByteArray("ModeEnum") },

        { static_cast<int>(Roles::NumRows), QByteArray("NumRows") },
        { static_cast<int>(Roles::NumCols), QByteArray("NumCols") },
        { static_cast<int>(Roles::AmBombs), QByteArray("AmBombs") },
    };
}
