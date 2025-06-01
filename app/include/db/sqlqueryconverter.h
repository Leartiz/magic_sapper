#ifndef SQLQUERYCONVERTER_H
#define SQLQUERYCONVERTER_H

#include <QSqlQuery>
#include <QVector>

#include "entities/descriptormode.h"
#include "entities/record.h"
#include "entities/settings.h"
#include "entities/stats.h"

class SqlQueryConverter final
{
public:
    static QVector<DescriptorMode> queryToDModes(QSqlQuery& query);
    static QVector<Record> queryToRecords(QSqlQuery& query);
    static QVector<Settings> queryToSettgss(QSqlQuery& query);
    static QVector<Stats> queryToStats(QSqlQuery& query);
};

#endif // SQLQUERYCONVERTER_H
