#ifndef DBFACADE_H
#define DBFACADE_H

#include <QVector>
#include <QString>

#include "db/conct.h"

#include "entities/mode.h"
#include "entities/descriptormode.h"
#include "entities/settgs.h"
#include "entities/record.h"
#include "entities/stats.h"

class DBFacade final
{
    friend class Conct;

public:
    static DBFacade& instance();
    ~DBFacade();

public:
    void insRecord(const Record& rec) const;

    DescriptorMode selDModeById(const int id) const;
    // return only one!
    QVector<DescriptorMode> selDModesByMode(WrMode::Mode mode) const;
    QVector<DescriptorMode> selAllDModes() const;

    Settgs selSettgs() const;

    Record selRecordById(const int id) const;
    QVector<Record> selRecordsByModeId(const int modeId) const;

    Stats selStatsById(const int id) const;
    Stats selStatsByModeId(const int modeId) const;
    QVector<Stats> selAllStatss() const;

    void updSettgs(const Settgs& s) const;
    void updDMode(const DescriptorMode& dm) const;
    void updStats(const Stats& s) const;

    void delRecordById(const int id) const;
    void delAllRecords() const;

private:
    static QVector<DescriptorMode> selAllDModesAtInit(bool closeConct = true);
    static QVector<DescriptorMode> selDModesByModeAtInit(WrMode::Mode mode, bool closeConct = true);

private:
    const bool m_isPermanentConnection;

private:
    explicit DBFacade(bool isPc = true);

    Q_DISABLE_COPY(DBFacade)
};

#endif // DBFACADE_H
