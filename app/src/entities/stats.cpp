#include "entities/stats.h"

const QString Stats::Tbl::TblName = "Stats";
const QString Stats::Tbl::Id = "Id";
const QString Stats::Tbl::ModeId = "ModeId";

const QString Stats::Tbl::AmGams = "AmGams";
const QString Stats::Tbl::AmWins = "AmWins";

const QString Stats::Tbl::AmWinsInRow = "AmWinsInRow";
const QString Stats::Tbl::AmLossInRow = "AmLossInRow";

const QString Stats::Tbl::TmpAmWinsInRow = "TmpAmWinsInRow";
const QString Stats::Tbl::TmpAmLossInRow = "TmpAmLossInRow";

Stats::Stats()
    : m_amGams(0), m_amWins(0)
    , m_amWinsInRow(0), m_amLossInRow(0)
    , m_tmpAmWinsInRow(0), m_tmpAmLossInRow(0)
{
}

Stats::Stats(const int id)
    : m_id(id)
    , m_amGams(0), m_amWins(0)
    , m_amWinsInRow(0), m_amLossInRow(0)
    , m_tmpAmWinsInRow(0), m_tmpAmLossInRow(0)
{
}

Stats::Stats(const int id, const int modeId)
    : m_id(id), m_modeId(modeId)
    , m_amGams(0), m_amWins(0)
    , m_amWinsInRow(0), m_amLossInRow(0)
    , m_tmpAmWinsInRow(0), m_tmpAmLossInRow(0)
{
}

std::optional<int> Stats::getId() const
{
    return m_id;
}

std::optional<int> Stats::getModeId() const
{
    return m_modeId;
}

void Stats::setModeId(const int modeId)
{
    m_modeId = modeId;
}

int Stats::getAmGams() const
{
    return m_amGams;
}

void Stats::setAmGams(int amGams)
{
    m_amGams = amGams;
}

void Stats::incAmGams()
{
    ++m_amGams;
}

int Stats::getAmWins() const
{
    return m_amWins;
}

void Stats::setAmWins(int amWins)
{
    m_amWins = amWins;
}

void Stats::incAmWins()
{
    ++m_amWins;
}

int Stats::getAmWinsInRow() const
{
    return m_amWinsInRow;
}

void Stats::setAmWinsInRow(int amWinsInRow)
{
    m_amWinsInRow = amWinsInRow;
}

int Stats::getAmLossInRow() const
{
    return m_amLossInRow;
}

void Stats::setAmLossInRow(int amLossInRow)
{
    m_amLossInRow = amLossInRow;
}

int Stats::getTmpAmWinsInRow() const
{
    return m_tmpAmWinsInRow;
}

void Stats::setTmpAmWinsInRow(int tmpAmWinsInRow)
{
    m_tmpAmWinsInRow = tmpAmWinsInRow;
}

int Stats::getTmpAmLossInRow() const
{
    return m_tmpAmLossInRow;
}

void Stats::setTmpAmLossInRow(int tmpAmLossInRow)
{
    m_tmpAmLossInRow = tmpAmLossInRow;
}

void Stats::incTmpAmWinsInRow()
{
    ++m_tmpAmWinsInRow;
    if (m_tmpAmWinsInRow > m_amWinsInRow)
        m_amWinsInRow = m_tmpAmWinsInRow;
}

void Stats::incTmpAmLossInRow()
{
    ++m_tmpAmLossInRow;
    if (m_tmpAmLossInRow > m_amLossInRow)
        m_amLossInRow = m_tmpAmLossInRow;
}

void Stats::resetStats()
{
    m_amGams = 0;
    m_amWins = 0;

    m_amWinsInRow = 0;
    m_amLossInRow = 0;

    m_tmpAmWinsInRow = 0;
    m_tmpAmLossInRow = 0;
}
