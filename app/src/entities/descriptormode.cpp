#include "entities/descriptormode.h"

const QString DescriptorMode::Tbl::TblName = "DMode";
const QString DescriptorMode::Tbl::Id = "Id";
const QString DescriptorMode::Tbl::ModeEnm = "ModeEnm";
const QString DescriptorMode::Tbl::ModeNme = "ModeNme";
const QString DescriptorMode::Tbl::NumRows = "NumRows";
const QString DescriptorMode::Tbl::NumCols = "NumCols";
const QString DescriptorMode::Tbl::AmBombs = "AmBombs";

DescriptorMode::DescriptorMode(const int id)
    : m_id(id)
{
}

DescriptorMode::DescriptorMode(const int id, WrMode::Mode m)
    : m_id(id), m_mode(m)
{
}

DescriptorMode::DescriptorMode(WrMode::Mode m)
    : m_mode(m)
{
}

std::optional<int> DescriptorMode::getId() const
{
    return m_id;
}

WrMode::Mode DescriptorMode::getMode() const
{
    return m_mode;
}

void DescriptorMode::setMode(WrMode::Mode mode)
{
    m_mode = mode;
}

const QString& DescriptorMode::getName() const
{
    return m_name;
}

void DescriptorMode::setName(const QString &name)
{
    m_name = name;
}

const DescriptorMode::Size& DescriptorMode::getSideSzs() const
{
    return m_sideSzs;
}

bool DescriptorMode::setSideSzs(const Size &sideSzs)
{
    if (sideSzs < Size(0, 0))
        return false;

    m_sideSzs = sideSzs;
    return true;
}

int DescriptorMode::getAmBombs() const
{
    return m_amBombs;
}

void DescriptorMode::setAmBombs(int amBombs)
{
    m_amBombs = amBombs;
}

int& DescriptorMode::increaseBombs()
{
    ++m_amBombs;
    return m_amBombs;
}

int& DescriptorMode::decreaseBombs()
{
    --m_amBombs;
    return m_amBombs;
}
