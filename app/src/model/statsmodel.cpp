#include <QDebug>

#include "model/statsmodel.h"

StatsModel::StatsModel(QObject* parent)
    : QObject(parent)
    , m_dbFacade(DBFacade::instance())
{
}

int StatsModel::getModeId() const
{
    return m_modeId.value_or(0);
}

void StatsModel::setModeId(const int modeId)
{
    m_modeId = modeId;
    emit modeIdChanged(getModeId());

    m_stats = std::make_unique<Stats>(m_dbFacade.selStatsByModeId(m_modeId.value()));
    emit amGamsChanged(getAmGams());
    emit amWinsChanged(getAmWins());

    emit amWinsInRowChanged(getAmWinsInRow());
    emit amLossInRowChanged(getAmLossInRow());

    emit percentWinChanged(getPercentWin());
}

int StatsModel::getAmGams() const
{
    if (!m_stats) return 0;
    return m_stats->getAmGams();
}

int StatsModel::getAmWins() const
{
    if (!m_stats) return 0;
    return m_stats->getAmWins();
}

int StatsModel::getAmWinsInRow() const
{
    if (!m_stats) return 0;
    return m_stats->getAmWinsInRow();
}

int StatsModel::getAmLossInRow() const
{
    if (!m_stats) return 0;
    return m_stats->getAmLossInRow();
}

double StatsModel::getPercentWin() const
{
    if (!m_stats) return 0;
    if (getAmGams() == 0) return 0;
    return getAmWins() / static_cast<double>(getAmGams()) * 100;
}
