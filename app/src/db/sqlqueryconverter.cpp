#include <QVariant>
#include <QSqlRecord>

#include "db/sqlqueryconverter.h"

QVector<DescriptorMode> SqlQueryConverter::queryToDModes(QSqlQuery& query)
{
    const QSqlRecord rec = query.record();
    const int idIx = rec.indexOf(DescriptorMode::Tbl::Id);
    const int modeEnmIx = rec.indexOf(DescriptorMode::Tbl::ModeEnm);
    const int modeNmeIx = rec.indexOf(DescriptorMode::Tbl::ModeNme);
    const int numRowsIx = rec.indexOf(DescriptorMode::Tbl::NumRows);
    const int numColsIx = rec.indexOf(DescriptorMode::Tbl::NumCols);
    const int amBombsIx = rec.indexOf(DescriptorMode::Tbl::AmBombs);

    QVector<DescriptorMode> dModes;
    while (query.next())
    {           
        DescriptorMode dm(query.value(idIx).toInt());
        dm.setMode(static_cast<WrMode::Mode>(query.value(modeEnmIx).toInt()));
        dm.setName(query.value(modeNmeIx).toString());
        dm.setSideSzs({ query.value(numRowsIx).toInt(), query.value(numColsIx).toInt() });
        dm.setAmBombs(query.value(amBombsIx).toInt());
        dModes.append(std::move(dm));
    }
    return dModes;
}

QVector<Record> SqlQueryConverter::queryToRecords(QSqlQuery& query)
{
    const QSqlRecord rec = query.record();
    const int idIx = rec.indexOf(Record::Tbl::Id);
    const int unIx = rec.indexOf(Record::Tbl::Username);
    const int modeIdIx = rec.indexOf(Record::Tbl::ModeId);
    const int tmPssdIx = rec.indexOf(Record::Tbl::TimePassed);

    QVector<Record> rcrds;
    while (query.next())
    {
        Record r(query.value(idIx).toInt());
        r.setUsername(query.value(unIx).toString());
        r.setModeId(query.value(modeIdIx).toInt());
        r.setTimePassed(query.value(tmPssdIx).toInt());
        rcrds.append(std::move(r));
    }
    return rcrds;
}

QVector<Settgs> SqlQueryConverter::queryToSettgss(QSqlQuery& query)
{
    const QSqlRecord rec = query.record();
    const int idIx = rec.indexOf(Settgs::Tbl::Id);
    const int unIx = rec.indexOf(Settgs::Tbl::Username);
    const int modeIdIx = rec.indexOf(Settgs::Tbl::ModeId);
    const int maxAmRecordsIx = rec.indexOf(Settgs::Tbl::MaxAmRecords);

    const int isUseQuestionMarkIx = rec.indexOf(Settgs::Tbl::IsUseQuestionMark);
    const int isUseSizeSliderIx = rec.indexOf(Settgs::Tbl::IsUseSizeSlider);

    QVector<Settgs> stgss;
    while (query.next())
    {
        Settgs s(query.value(idIx).toInt());
        s.setUsername(query.value(unIx).toString());
        s.setModeId(query.value(modeIdIx).toInt());
        s.setMaxAmRecords(query.value(maxAmRecordsIx).toInt());

        s.setIsUseQuestionMark(query.value(isUseQuestionMarkIx).toInt() != 0);
        s.setIsUseSizeSlider(query.value(isUseSizeSliderIx).toInt() != 0);
        stgss.append(std::move(s));
    }
    return stgss;
}

QVector<Stats> SqlQueryConverter::queryToStats(QSqlQuery& query)
{
    const QSqlRecord rec = query.record();
    const int idIx = rec.indexOf(Stats::Tbl::Id);
    const int modeIdIx = rec.indexOf(Stats::Tbl::ModeId);

    const int amGamsIx = rec.indexOf(Stats::Tbl::AmGams);
    const int amWinsIx = rec.indexOf(Stats::Tbl::AmWins);

    const int amWinsInRowIx = rec.indexOf(Stats::Tbl::AmWinsInRow);
    const int amLossInRowIx = rec.indexOf(Stats::Tbl::AmLossInRow);

    const int tmpAmWinsInRowIx = rec.indexOf(Stats::Tbl::TmpAmWinsInRow);
    const int tmpAmLossInRowIx = rec.indexOf(Stats::Tbl::TmpAmLossInRow);

    QVector<Stats> stss;
    while (query.next())
    {
        Stats s(query.value(idIx).toInt(), query.value(modeIdIx).toInt());

        s.setAmGams(query.value(amGamsIx).toInt());
        s.setAmWins(query.value(amWinsIx).toInt());

        s.setAmWinsInRow(query.value(amWinsInRowIx).toInt());
        s.setAmLossInRow(query.value(amLossInRowIx).toInt());

        s.setTmpAmWinsInRow(query.value(tmpAmWinsInRowIx).toInt());
        s.setTmpAmLossInRow(query.value(tmpAmLossInRowIx).toInt());
        stss.append(std::move(s));
    }
    return stss;;
}
