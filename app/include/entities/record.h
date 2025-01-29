#ifndef RECORD_H
#define RECORD_H

#include <QString>

#include <optional>

#include "entities/usrdata.h"

class Record final : public UsrData
{
public:
    struct Tbl
    {
        Tbl() = delete;
        static const QString TblName;
        static const QString Id;
        static const QString Username;
        static const QString ModeId;
        static const QString TimePassed; // scnds!
    };

public:
    Record();

    explicit Record(const int id);
    Record(const int id, const QString& un, const int modeId, const int tp);
    Record(const QString& un, const int modeId, const int tp);

    ~Record() override = default;

public:
    std::optional<int> getModeId() const;
    void setModeId(const int modeId);

    int getTimePassed() const;
    void setTimePassed(const int timePassed);

private:
    std::optional<int> m_modeId;
    int m_timePassed;
};

#endif // RECORD_H
