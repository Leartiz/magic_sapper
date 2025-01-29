#include <QVector>
#include <QDebug>

#include "model/custommodemodel.h"

CustomModeModel::CustomModeModel(QObject* parent)
    : QObject(parent)
    , m_dbFacade(DBFacade::instance())
{
    const auto dModes = m_dbFacade.selDModesByMode(WrMode::Custom);
    if (dModes.size() != 1)
    {
        qCritical() << "CustomModeModel, cntr, selDModesByMode failed.";
        return;
    }
    m_dMode = dModes.first();

    // signal to signal!
    connect(this, &CustomModeModel::numRowsChanged, &CustomModeModel::customDModeChanged);
    connect(this, &CustomModeModel::numColsChanged, &CustomModeModel::customDModeChanged);
    connect(this, &CustomModeModel::amBombsChanged, &CustomModeModel::customDModeChanged);
}

int CustomModeModel::getNumRows() const
{
    return m_dMode.getSideSzs().first;
}

void CustomModeModel::setNumRows(int numRows)
{
    auto sideSzs = m_dMode.getSideSzs();
    sideSzs.first = numRows;
    m_dMode.setSideSzs(sideSzs);
    m_dbFacade.updDMode(m_dMode); // lazy!
    emit numRowsChanged(getNumRows());
}

int CustomModeModel::getNumCols() const
{
    return m_dMode.getSideSzs().second;
}

void CustomModeModel::setNumCols(int numCols)
{
    auto sideSzs = m_dMode.getSideSzs();
    sideSzs.second = numCols;
    m_dMode.setSideSzs(sideSzs);
    m_dbFacade.updDMode(m_dMode);
    emit numRowsChanged(getNumCols());
}

int CustomModeModel::getAmBombs() const
{
    return m_dMode.getAmBombs();
}

void CustomModeModel::setAmBombs(int amBombs)
{
    m_dMode.setAmBombs(amBombs);
    m_dbFacade.updDMode(m_dMode);
    emit numRowsChanged(getAmBombs());
}
