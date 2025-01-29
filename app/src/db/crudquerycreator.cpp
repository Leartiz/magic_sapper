#include <QDebug>

#include "db/crudquerycreator.h"

QString CrudQueryCreator::qs(const QString& vl)
{
    return "'" + vl + "'";
}

QString CrudQueryCreator::insert_vals(const QString& tblName, const QStringList& cols,
                                      const QList<QVariantList>& someVals)
{
    // errs!
    if (tblName.isEmpty())
    {
        qWarning() << "CrudQueryCreator, insert, tblName empty.";
        return {};
    }
    if (cols.isEmpty())
    {
        qWarning() << "CrudQueryCreator, insert, cols empty.";
        return {};
    }
    if (someVals.isEmpty())
    {
        qWarning() << "CrudQueryCreator, insert, someVals empty.";
        return {};
    }

    // INSERT INTO table (column1, column2, ...)
    // VALUES (value1, value2 , ...), (value1, value2 , ...), (value1, value2 , ...), ...;
    QString sQuery = {
        "INSERT INTO " + tblName + " ("
    };

    for (const auto& col : cols)
        sQuery.append(col).append(", ");
    sQuery.remove(sQuery.size() - 2, 1);
    sQuery.append(") VALUES ");

    for (int i = 0; i < someVals.size(); ++i)
    {
        sQuery.append("( ");
        if (someVals[i].size() != cols.size())
        {
            qDebug() << "CrudQueryCreator, insert, cols size is not equal someVals at " << i << " size.";
            return {};
        }
        const QVariantList& vals = someVals[i];
        for (int i = 0; i < vals.size(); ++i)
            sQuery.append("'" + vals[i].toString() + "'").append(", ");
        sQuery.remove(sQuery.size() - 2, 1);
        sQuery.append("), ");
    }
    sQuery.remove(sQuery.size() - 2, 2);
    sQuery.append(";");
    return sQuery;
}

QString CrudQueryCreator::select_all(const QString& tblName)
{
    if (tblName.isEmpty())
    {
        qWarning() << "CrudQueryCreator, select_all, tblName empty.";
        return {};
    }

    // SELECT * FROM table_name;
    QString sQuery = { "SELECT * " };
    sQuery.append("FROM ").append(tblName);
    sQuery.append(";");
    return sQuery;
}

QString CrudQueryCreator::select(const QString& tblName, const QString& condWhere)
{
    if (tblName.isEmpty())
    {
        qWarning() << "CrudQueryCreator, select, tblName empty.";
        return {};
    }
    if (condWhere.isEmpty())
    {
        qWarning() << "CrudQueryCreator, select, condWhere empty.";
        return {};
    }

    // SELECT * FROM table_name WHERE condWhere;
    const QString sQuery = {
        "SELECT * FROM " + tblName + " " +
        "WHERE " + condWhere + ";"
    };
    return sQuery;
}

QString CrudQueryCreator::update(const QString &tblName, const QStringList &cols,
                                 const QVariantList &vals, const QString &condWhere)
{
    if (tblName.isEmpty())
    {
        qWarning() << "CrudQueryCreator, select, tblName empty.";
        return {};
    }
    if (cols.isEmpty())
    {
        qWarning() << "CrudQueryCreator, update, cols empty.";
        return {};
    }
    if (vals.isEmpty())
    {
        qWarning() << "CrudQueryCreator, update, vals empty.";
        return {};
    }
    if (cols.size() != vals.size())
    {
        qWarning() << "CrudQueryCreator, update, cols size is not equal vals size.";
        return {};
    }
    if (condWhere.isEmpty())
    {
        qWarning() << "CrudQueryCreator, update, condWhere empty.";
        return {};
    }

    // UPDATE table SET col1 = nwval1, col2 = nwval2, ... WHERE colN == valN;
    QString sQuery = { "UPDATE " + tblName + " SET " };
    for (int i = 0; i < cols.size(); ++i)
    {
        sQuery.append(cols[i]).append("=");
        sQuery.append(qs(vals[i].toString()));
        sQuery.append(", ");
    }
    sQuery.remove(sQuery.size() - 2, 1);
    sQuery.append("WHERE ").append(condWhere);
    sQuery.append(";");
    return sQuery;
}

QString CrudQueryCreator::deleteSome(const QString &tblName, const QString& condWhere)
{
    if (tblName.isEmpty())
    {
        qWarning() << "CrudQueryCreator, deleteSome, tblName empty.";
        return {};
    }
    if (condWhere.isEmpty())
    {
        qWarning() << "CrudQueryCreator, deleteSome, condWhere empty.";
        return {};
    }

    // DELETE FROM table WHERE condWhere;
    const QString sQuery = {
        "DELETE FROM " + tblName + " " +
        "WHERE " + condWhere + ";"
    };
    return sQuery;
}

QString CrudQueryCreator::deleteAll(const QString &tblName)
{
    if (tblName.isEmpty())
    {
        qWarning() << "CrudQueryCreator, deleteAll, tblName empty.";
        return {};
    }

    // DELETE FROM table;
    const QString sQuery = {
        "DELETE FROM " + tblName + ";"
    };
    return sQuery;
}
