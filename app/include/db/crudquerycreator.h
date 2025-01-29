#ifndef CRUDQUERYCREATOR_H
#define CRUDQUERYCREATOR_H

#include <QList>
#include <QString>
#include <QStringList>
#include <QVariantList>

class CrudQueryCreator
{
public:
    static QString insert_vals(const QString& tblName, const QStringList& cols,
                               const QList<QVariantList>& someVals);

    static QString select_all(const QString& tblName);
    static QString select_all(const QString& tblName, const QStringList& cols);
    static QString select(const QString& tblName, const QString& condWhere);

    static QString update(const QString &tblName, const QStringList &cols,
                          const QVariantList &vals, const QString &condWhere);

    static QString deleteSome(const QString &tblName, const QString& condWhere);
    static QString deleteAll(const QString &tblName);

public:
    static QString qs(const QString& vl);
};

#endif // CRUDQUERYCREATOR_H
