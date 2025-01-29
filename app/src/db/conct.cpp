#include <algorithm>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>

#include "db/conct.h"
#include "db/dbfacade.h"
#include "db/crudquerycreator.h"

#include "entities/descriptormode.h"
#include "entities/mode.h"
#include "entities/settgs.h"
#include "entities/record.h"
#include "entities/stats.h"

const QString Conct::driverName = "QSQLITE";
const QString Conct::dbName = "sppr_db.sqlite";

void Conct::init()
{
    if (QSqlDatabase::contains())
        return; // ok!

    QSqlDatabase db = QSqlDatabase::addDatabase(driverName);
    db.setDatabaseName(dbName);

    if (!db.open())
    {
        qCritical() << "Conct, init, database not open: " << db.lastError();
        return;
    }

    createTbls(); // if first time!

    db.close();
    qInfo() << "Conct init end (maybe repeated).";
}

void Conct::createTbls()
{
    QSqlDatabase db = QSqlDatabase::database(); // open!

    const auto tbls = db.tables();
    // order!
    if (!tbls.contains(DescriptorMode::Tbl::TblName))
    {
        createDMode();
        inflateDMode();
    }
    if (!tbls.contains(Settgs::Tbl::TblName))
    {
        createSettgs();
        inflateSettgs();
    }
    if (!tbls.contains(Record::Tbl::TblName))
        createRecord();
    if (!tbls.contains(Stats::Tbl::TblName))
    {
        createStats();
        inflateStats();
    }

    db.close();
}

void Conct::createDMode()
{
    const QString sQuery = {
        "CREATE TABLE " + DescriptorMode::Tbl::TblName + " (" +
        DescriptorMode::Tbl::Id + " INTEGER, " +
        DescriptorMode::Tbl::ModeEnm + " INTEGER NOT NULL, " +
        DescriptorMode::Tbl::ModeNme + " TEXT NOT NULL, " +
        DescriptorMode::Tbl::NumRows + " INTEGER NOT NULL, " +
        DescriptorMode::Tbl::NumCols + " INTEGER NOT NULL, " +
        DescriptorMode::Tbl::AmBombs + " INTEGER NOT NULL, " +
        "PRIMARY KEY(" + DescriptorMode::Tbl::Id + ")" +
        ");"
    };
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "Conct, createDMode, exec failed: " << query.lastError();
        return;
    }
    qInfo() << "Tbl DMode was created.";
}

void Conct::createSettgs()
{
    const QString sQuery = {
        "CREATE TABLE " + Settgs::Tbl::TblName + " (" +
        Settgs::Tbl::Id + " INTEGER, " +
        Settgs::Tbl::Username + " TEXT NOT NULL, " +
        Settgs::Tbl::ModeId + " INTEGER NOT NULL, " +
        Settgs::Tbl::MaxAmRecords + " INTEGER NOT NULL, " +
        Settgs::Tbl::IsUseQuestionMark + " INTEGER NOT NULL, " +
        Settgs::Tbl::IsUseSizeSlider + " INTEGER NOT NULL, " +
        "FOREIGN KEY(" + Settgs::Tbl::ModeId + ") "
        "REFERENCES " + DescriptorMode::Tbl::TblName + "(" + DescriptorMode::Tbl::Id + "), "
        "PRIMARY KEY(" + Settgs::Tbl::Id + ")" +
        ");"
    };
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "Conct, createSettgs, exec failed: " << query.lastError();
        return;
    }
    qInfo() << "Tbl Settgs was created.";
}

void Conct::createRecord()
{
    const QString sQuery = {
        "CREATE TABLE " + Record::Tbl::TblName + " (" +
        Record::Tbl::Id + " INTEGER, " +
        Record::Tbl::Username + " TEXT NOT NULL, " +
        Record::Tbl::ModeId + " INTEGER NOT NULL, " +
        Record::Tbl::TimePassed + " INTEGER NOT NULL, " +
        "FOREIGN KEY(" + Record::Tbl::ModeId + ") "
        "REFERENCES " + DescriptorMode::Tbl::TblName + "(" + DescriptorMode::Tbl::Id + "), "
        "PRIMARY KEY(" + Record::Tbl::Id + ")" +
        ");"
    };
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "Conct, createSettgs, exec failed: " << query.lastError();
        return;
    }
    qInfo() << "Tbl Record was created.";
}

void Conct::createStats()
{
    const QString sQuery = {
        "CREATE TABLE " + Stats::Tbl::TblName + " (" +
        Stats::Tbl::Id + " INTEGER, " +
        Stats::Tbl::ModeId + " INTEGER NOT NULL, " +

        Stats::Tbl::AmGams + " INTEGER NOT NULL, " +
        Stats::Tbl::AmWins + " INTEGER NOT NULL, " +

        Stats::Tbl::AmWinsInRow + " INTEGER NOT NULL, " +
        Stats::Tbl::AmLossInRow + " INTEGER NOT NULL, " +

        Stats::Tbl::TmpAmWinsInRow + " INTEGER NOT NULL, " +
        Stats::Tbl::TmpAmLossInRow + " INTEGER NOT NULL, " +

        "FOREIGN KEY(" + Stats::Tbl::ModeId + ") "
        "REFERENCES " + DescriptorMode::Tbl::TblName + "(" + DescriptorMode::Tbl::Id + "), "
        "PRIMARY KEY(" + Stats::Tbl::Id + ")" +
        ");"
    };
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "Conct, createStats, exec failed: " << query.lastError();
        return;
    }
    qInfo() << "Tbl Stats was created.";
}

void Conct::inflateDMode()
{
    const QStringList cols = {
        DescriptorMode::Tbl::ModeEnm,
        DescriptorMode::Tbl::ModeNme,
        DescriptorMode::Tbl::NumRows,
        DescriptorMode::Tbl::NumCols,
        DescriptorMode::Tbl::AmBombs
    };
    const QList<QVariantList> someVals = {
        { static_cast<int>(WrMode::Easy), "легкий", 9, 9, 10 },
        { static_cast<int>(WrMode::Middle), "средний", 16, 16, 40 },
        { static_cast<int>(WrMode::Intricate), "сложный", 16, 30, 99 },
        { static_cast<int>(WrMode::Unreal), "нереальный", 24, 30, 180 },
        { static_cast<int>(WrMode::Custom), "пользовательский", 9, 9, 10 }
    };
    const QString sQuery = CrudQueryCreator::insert_vals(DescriptorMode::Tbl::TblName, cols, someVals);

    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "Conct, inflateDMode, exec failed: " << query.lastError();
        return;
    }
    qInfo() << "Tbl DMode was inflated.";
}

void Conct::inflateSettgs()
{
    const QStringList cols = {
        Settgs::Tbl::Username,
        Settgs::Tbl::ModeId,
        Settgs::Tbl::MaxAmRecords,

        Settgs::Tbl::IsUseQuestionMark,
        Settgs::Tbl::IsUseSizeSlider
    };
    const int maxAmRecords = 10;
    const auto dModes = DBFacade::selDModesByModeAtInit(WrMode::Middle, false); // one!
    const QList<QVariantList> someVals = {
        { "anonymous", dModes.front().getId().value(), maxAmRecords, 1, 1 } // is!
    };

    const QString sQuery = CrudQueryCreator::insert_vals(Settgs::Tbl::TblName, cols, someVals);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "Conct, inflateSettgs, exec failed: " << query.lastError();
        return;
    }
    qInfo() << "Tbl Settgs was inflated.";
}

void Conct::inflateStats()
{
    const auto dModes = DBFacade::selAllDModesAtInit(false);
    if (dModes.size() != 5)
    {
        qCritical() << "Conct, inflateStats, dModes size not equal 5.";
        return;
    }

    const QStringList cols = {
        Stats::Tbl::ModeId,

        Stats::Tbl::AmGams,
        Stats::Tbl::AmWins,

        Stats::Tbl::AmWinsInRow,
        Stats::Tbl::AmLossInRow,

        Stats::Tbl::TmpAmWinsInRow,
        Stats::Tbl::TmpAmLossInRow,
    };
    // reset!
    const QList<QVariantList> someVals = {
        { dModes[0].getId().value(), 0, 0, 0, 0, 0, 0 },
        { dModes[1].getId().value(), 0, 0, 0, 0, 0, 0 },
        { dModes[2].getId().value(), 0, 0, 0, 0, 0, 0 },
        { dModes[3].getId().value(), 0, 0, 0, 0, 0, 0 },
        { dModes[4].getId().value(), 0, 0, 0, 0, 0, 0 }, // no used!
    };

    const QString sQuery = CrudQueryCreator::insert_vals(Stats::Tbl::TblName, cols, someVals);
    QSqlQuery query(QSqlDatabase::database());
    if (!query.exec(sQuery))
    {
        qCritical() << "Conct, inflateStats, exec failed: " << query.lastError();
        return;
    }
    qInfo() << "Tbl Stats was inflated.";
}
