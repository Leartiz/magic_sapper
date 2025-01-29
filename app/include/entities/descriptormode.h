#ifndef DESCRIPTORMODE_H
#define DESCRIPTORMODE_H

#include <optional>

#include <QPair>
#include <QString>

#include "mode.h"

// and for db!
class DescriptorMode final
{
public:
    struct Tbl
    {
        Tbl() = delete;
        static const QString TblName;
        static const QString Id;
        static const QString ModeEnm;
        static const QString ModeNme; // as id?
        static const QString NumRows;
        static const QString NumCols;
        static const QString AmBombs;
    };

public:
    using Size = QPair<int, int>;

public:
    DescriptorMode() = default;
    DescriptorMode(const DescriptorMode&) = default;
    DescriptorMode& operator=(const DescriptorMode&) = default;

    explicit DescriptorMode(const int id);
    DescriptorMode(const int id, WrMode::Mode m);
    explicit DescriptorMode(WrMode::Mode m);

    ~DescriptorMode() = default;

public:
    std::optional<int> getId() const;

    WrMode::Mode getMode() const;
    void setMode(WrMode::Mode mode);

    const QString& getName() const;
    void setName(const QString &name);

    const Size& getSideSzs() const;
    bool setSideSzs(const Size &sideSzs);

    int getAmBombs() const;
    void setAmBombs(int amBombs);
    int& increaseBombs();
    int& decreaseBombs();

private:
    std::optional<int> m_id;
    WrMode::Mode m_mode;
    QString m_name;
    Size m_sideSzs;
    int m_amBombs;
};

#endif // DESCRIPTORMODE_H
