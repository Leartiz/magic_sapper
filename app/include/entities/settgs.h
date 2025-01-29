#ifndef SETTGS_H
#define SETTGS_H

#include <optional>

#include <QString>

#include "entities/usrdata.h"
#include "entities/mode.h"

class Settgs final : public UsrData
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
    Settgs() = default;

    explicit Settgs(const int id);
    Settgs(const QString& username, const int modeId);
    Settgs(const int id, const QString& username, const int modeId);

    ~Settgs() override = default;

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
    int m_maxAmRecords; // const!

    // flags!
    bool m_isUseQuestionMark;
    bool m_isUseSizeSlider;
};

#endif // SETTGS_H
