#include "entities/record.h"

const QString Record::Tbl::TblName = "Record";
const QString Record::Tbl::Id = "Id";
const QString Record::Tbl::Username = "Username";
const QString Record::Tbl::ModeId = "ModeId";
const QString Record::Tbl::TimePassed = "TimePassed";

Record::Record()
    : m_timePassed(0)
{
}

Record::Record(const int id)
    : UsrData(id), m_timePassed(0)
{
}

Record::Record(const int id, const QString& un, const int modeId, const int tp)
    : UsrData(id, un), m_modeId(modeId), m_timePassed(tp)
{
}

Record::Record(const QString& un, const int modeId, const int tp)
    : UsrData(un), m_modeId(modeId), m_timePassed(tp)
{
}

std::optional<int> Record::getModeId() const
{
    return m_modeId;
}

void Record::setModeId(const int modeId)
{
    m_modeId = modeId;
}

int Record::getTimePassed() const
{
    return m_timePassed;
}

void Record::setTimePassed(const int timePassed)
{
    m_timePassed = timePassed;
}
