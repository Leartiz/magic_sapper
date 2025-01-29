#include "entities/settgs.h"

const QString Settgs::Tbl::TblName = "Settgs";
const QString Settgs::Tbl::Id = "Id";
const QString Settgs::Tbl::Username = "Username";
const QString Settgs::Tbl::ModeId = "ModeId";
const QString Settgs::Tbl::MaxAmRecords = "MaxAmRecords";
const QString Settgs::Tbl::IsUseQuestionMark = "IsUseQuestionMark";
const QString Settgs::Tbl::IsUseSizeSlider = "IsUseSizeSlider";

Settgs::Settgs(const int id)
    : UsrData(id)
{
}

Settgs::Settgs(const QString& username, const int modeId)
    : UsrData(username), m_modeId(modeId)
{
}

Settgs::Settgs(const int id, const QString& username, const int modeId)
    : UsrData(id, username), m_modeId(modeId)
{
}

std::optional<int> Settgs::getModeId() const
{
    return m_modeId;
}

void Settgs::setModeId(const int modeId)
{
    m_modeId = modeId;
}

int Settgs::getMaxAmRecords() const
{
    return m_maxAmRecords;
}

void Settgs::setMaxAmRecords(int maxAmRecords)
{
    m_maxAmRecords = maxAmRecords;
}

bool Settgs::getIsUseQuestionMark() const
{
    return m_isUseQuestionMark;
}

int Settgs::getIsUseQuestionMarkAsNum() const
{
    return m_isUseQuestionMark ? 1 : 0;
}

void Settgs::setIsUseQuestionMark(bool isUseQuestionMark)
{
    m_isUseQuestionMark = isUseQuestionMark;
}

bool Settgs::getIsUseSizeSlider() const
{
    return m_isUseSizeSlider;
}

int Settgs::getIsUseSizeSliderAsNum() const
{
    return m_isUseSizeSlider ? 1 : 0;
}

void Settgs::setIsUseSizeSlider(bool isUseSizeSlider)
{
    m_isUseSizeSlider = isUseSizeSlider;
}
