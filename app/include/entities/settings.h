#ifndef SETTINGS_H
#define SETTINGS_H

#include <optional>

#include <QString>

#include "entities/usrdata.h"

class Settings final : public UsrData
{
public:
    struct Tbl
    {
        Tbl() = delete;
        static const QString TblName;
        static const QString Id;
        static const QString Username;
        static const QString ModeId;
        static const QString MaxAmRecords;

        static const QString IsUseQuestionMark;
        static const QString IsUseSizeSlider;
    };

public:
    Settings() = default;
    explicit Settings(const int id);
    Settings(const QString& username, const int modeId);
    Settings(const int id, const QString& username, const int modeId);

    ~Settings() override = default;

public:
    std::optional<int> getModeId() const;
    void setModeId(const int modeId);

    int getMaxAmRecords() const;
    void setMaxAmRecords(int maxAmRecords);

    bool getIsUseQuestionMark() const;
    int getIsUseQuestionMarkAsNum() const;
    void setIsUseQuestionMark(bool isUseQuestionMark);

    bool getIsUseSizeSlider() const;
    int getIsUseSizeSliderAsNum() const;
    void setIsUseSizeSlider(bool isUseSizeSlider);

private:
    std::optional<int> m_modeId; // cur!
    int m_maxAmRecords = 0; // const!

    // flags!
    bool m_isUseQuestionMark = false;
    bool m_isUseSizeSlider = false;
};

#endif // SETTINGS_H
