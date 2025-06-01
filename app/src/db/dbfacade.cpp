#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>
#include <QVariant>
#include <QStringList>
#include <QVariantList>

#include "db/dbfacade.h"
#include "db/crudquerycreator.h"
#include "db/sqlqueryconverter.h"

DBFacade& DBFacade::instance()
{
    static DBFacade dbFacade;
    return dbFacade;
}

DBFacade::DBFacade(bool isPc)
    : m_isPermanentConnection(isPc)
{
    Conct::init();
}

DBFacade::~DBFacade()
{
    QSqlDatabase::database(QSqlDatabase::defaultConnection, false).close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void DBFacade::insRecord(const Record& rec) const
{
    if (!rec.getModeId().has_value())
    {
        qCritical() << "DBFacade, insRecord, recors has no mode id.";
        return;
    }

    // skip name!
    const QStringList cols = {
        Record::Tbl::Username,
        Record::Tbl::ModeId,
        Record::Tbl::TimePassed
    };
    const QList<QVariantList> someVals = {
        { rec.getUsername(), rec.getModeId().value(), rec.getTimePassed() }
    };
    const QString sQuery = CrudQueryCreator::insert_vals(Record::Tbl::TblName, cols, someVals);

    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, insRecord, exec failed: " << query.lastError();
        return;
    }
}

QVector<DescriptorMode> DBFacade::selAllDModesAtInit(bool closeConct)
{
    const auto sQuery = CrudQueryCreator::select_all(DescriptorMode::Tbl::TblName);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, selAllDModesAtInit, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    if (closeConct)
        QSqlDatabase::database().close();
    return SqlQueryConverter::queryToDModes(query);
}

QVector<DescriptorMode> DBFacade::selDModesByModeAtInit(WrMode::Mode mode, bool closeConct)
{
    const QString condWhere = {
        DescriptorMode::Tbl::ModeEnm + "==" +
        QString::number(static_cast<int>(mode))
    };
    const auto sQuery = CrudQueryCreator::select(DescriptorMode::Tbl::TblName, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, selDModesByModeAtInit, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    if (closeConct)
        QSqlDatabase::database().close();
    return SqlQueryConverter::queryToDModes(query);
}

DescriptorMode DBFacade::selDModeById(const int id) const
{
    const QString condWhere = {
        DescriptorMode::Tbl::Id + "==" + QString::number(id)
    };
    const auto sQuery = CrudQueryCreator::select(DescriptorMode::Tbl::TblName, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, selDModesById, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
    const auto dModes = SqlQueryConverter::queryToDModes(query);
    return dModes.front();
}

QVector<DescriptorMode> DBFacade::selDModesByMode(WrMode::Mode mode) const
{
    const auto dModes = selDModesByModeAtInit(mode, false);
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
    return dModes;
}

QVector<DescriptorMode> DBFacade::selAllDModes() const
{
    const auto dModes = selAllDModesAtInit(false);
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
    return dModes;
}

Settings DBFacade::selSettgs() const
{
    const auto sQuery = CrudQueryCreator::select_all(Settings::Tbl::TblName);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, selSettgs, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
    const auto settgss = SqlQueryConverter::queryToSettgss(query);
    return settgss.front();
}

Record DBFacade::selRecordById(const int id) const
{
    const QString condWhere = {
        Record::Tbl::Id + "==" + QString::number(id)
    };
    const auto sQuery = CrudQueryCreator::select(Record::Tbl::Id, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, selRecordById, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
    const auto records = SqlQueryConverter::queryToRecords(query);
    return records.front();
}

QVector<Record> DBFacade::selRecordsByModeId(const int modeId) const
{
    const QString condWhere = {
        Record::Tbl::ModeId + "==" + QString::number(modeId)
    };
    const auto sQuery = CrudQueryCreator::select(Record::Tbl::TblName, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, selRecordsByModeId, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
    return SqlQueryConverter::queryToRecords(query);
}

// rpt code!
Stats DBFacade::selStatsById(const int id) const
{
    const QString condWhere = {
        Stats::Tbl::Id + "==" + QString::number(id)
    };
    const auto sQuery = CrudQueryCreator::select(Stats::Tbl::TblName, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, selStatsById, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
    const auto stss = SqlQueryConverter::queryToStats(query);
    return stss.front();
}

Stats DBFacade::selStatsByModeId(const int modeId) const
{
    const QString condWhere = {
        Stats::Tbl::ModeId + "==" + QString::number(modeId)
    };
    const auto sQuery = CrudQueryCreator::select(Stats::Tbl::TblName, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, selStatsByModeId, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
    const auto stss = SqlQueryConverter::queryToStats(query);
    return stss.front();
}

QVector<Stats> DBFacade::selAllStatss() const
{
    const auto sQuery = CrudQueryCreator::select_all(Stats::Tbl::TblName);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, selAllStats, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
    return SqlQueryConverter::queryToStats(query);;
}

void DBFacade::updSettgs(const Settings& s) const
{
    if (!s.getId().has_value())
    {
        qCritical() << "DBFacade, updSettgs, settgs has no id.";
        return;
    }
    if (!s.getModeId().has_value())
    {
        qCritical() << "DBFacade, updSettgs, settgs has no mode id.";
        return;
    }

    const QStringList cols = {
        Settings::Tbl::Username,
        Settings::Tbl::ModeId,
        Settings::Tbl::IsUseQuestionMark,
        Settings::Tbl::IsUseSizeSlider
    };
    const QVariantList vals = {
        s.getUsername(),
        s.getModeId().value(),
        s.getIsUseQuestionMarkAsNum(),
        s.getIsUseSizeSliderAsNum()
    };
    const QString condWhere = {
        Settings::Tbl::Id + "==" +
        QString::number(static_cast<int>(s.getId().value()))
    };
    const auto sQuery = CrudQueryCreator::update(Settings::Tbl::TblName, cols, vals, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, updSettgs, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return;
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
}

void DBFacade::updDMode(const DescriptorMode& dm) const
{
    if (!dm.getId().has_value())
    {
        qCritical() << "DBFacade, updDMode, descriptor mode has no id.";
        return;
    }

    // skip name!
    const QStringList cols = {
        DescriptorMode::Tbl::ModeEnm,
        DescriptorMode::Tbl::NumRows,
        DescriptorMode::Tbl::NumCols,
        DescriptorMode::Tbl::AmBombs
    };
    const QVariantList vals = {
        static_cast<int>(dm.getMode()),
        dm.getSideSzs().first,
        dm.getSideSzs().second,
        dm.getAmBombs()
    };
    const QString condWhere = {
        DescriptorMode::Tbl::Id + "==" + QString::number(dm.getId().value())
    };
    const auto sQuery = CrudQueryCreator::update(DescriptorMode::Tbl::TblName, cols, vals, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, updDMode, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return;
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
}

void DBFacade::updStats(const Stats& s) const
{
    if (!s.getId().has_value())
    {
        qCritical() << "DBFacade, updStats, stats has no id.";
        return;
    }
    if (!s.getModeId().has_value())
    {
        qCritical() << "DBFacade, updStats, stats has no mode id.";
        return;
    }

    const QStringList cols = {
        Stats::Tbl::ModeId,
        Stats::Tbl::AmGams,
        Stats::Tbl::AmWins,

        Stats::Tbl::AmWinsInRow,
        Stats::Tbl::AmLossInRow,

        Stats::Tbl::TmpAmWinsInRow,
        Stats::Tbl::TmpAmLossInRow
    };
    const QVariantList vals = {
        s.getModeId().value(),
        s.getAmGams(),
        s.getAmWins(),

        s.getAmWinsInRow(),
        s.getAmLossInRow(),

        s.getTmpAmWinsInRow(),
        s.getTmpAmLossInRow()
    };
    const QString condWhere = {
        Stats::Tbl::Id + "==" + QString::number(s.getId().value())
    };
    const auto sQuery = CrudQueryCreator::update(Stats::Tbl::TblName, cols, vals, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, updStats, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return;
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
}

void DBFacade::delRecordById(const int id) const
{
    const QString condWhere = {
        Record::Tbl::Id + "==" + QString::number(id)
    };
    const auto sQuery = CrudQueryCreator::deleteSome(Record::Tbl::TblName, condWhere);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, delRecordById, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return;
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
}

void DBFacade::delAllRecords() const
{
    const auto sQuery = CrudQueryCreator::deleteAll(Record::Tbl::TblName);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "DBFacade, delAllRecords, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return;
    }
    if (!m_isPermanentConnection)
        QSqlDatabase::database().close();
}
