#include "entities/settings.h"

const QString Settings::Tbl::TblName = "Settgs";
const QString Settings::Tbl::Id = "Id";
const QString Settings::Tbl::Username = "Username";
const QString Settings::Tbl::ModeId = "ModeId";
const QString Settings::Tbl::MaxAmRecords = "MaxAmRecords";
const QString Settings::Tbl::IsUseQuestionMark = "IsUseQuestionMark";
const QString Settings::Tbl::IsUseSizeSlider = "IsUseSizeSlider";

Settings::Settings(const int id)
    : UsrData(id)
{
}

Settings::Settings(const QString& username, const int modeId)
    : UsrData(username), m_modeId(modeId)
{
}

Settings::Settings(const int id, const QString& username, const int modeId)
    : UsrData(id, username), m_modeId(modeId)
{
}

std::optional<int> Settings::getModeId() const
{
    return m_modeId;
}

void Settings::setModeId(const int modeId)
{
    m_modeId = modeId;
}

int Settings::getMaxAmRecords() const
{
    return m_maxAmRecords;
}

void Settings::setMaxAmRecords(int maxAmRecords)
{
    m_maxAmRecords = maxAmRecords;
}

bool Settings::getIsUseQuestionMark() const
{
    return m_isUseQuestionMark;
}

int Settings::getIsUseQuestionMarkAsNum() const
{
    return m_isUseQuestionMark ? 1 : 0;
}

void Settings::setIsUseQuestionMark(bool isUseQuestionMark)
{
    m_isUseQuestionMark = isUseQuestionMark;
}

bool Settings::getIsUseSizeSlider() const
{
    return m_isUseSizeSlider;
}

int Settings::getIsUseSizeSliderAsNum() const
{
    return m_isUseSizeSlider ? 1 : 0;
}

void Settings::setIsUseSizeSlider(bool isUseSizeSlider)
{
    m_isUseSizeSlider = isUseSizeSlider;
}
