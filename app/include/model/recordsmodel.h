#ifndef RECORDSMODEL_H
#define RECORDSMODEL_H

#include <memory>
#include <optional>

#include <QObject>
#include <QAbstractListModel>

#include <QVector>
#include <QByteArray>

#include "db/dbfacade.h"
#include "entities/record.h"

class RecordsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int modeId READ getModeId WRITE setModeId NOTIFY modeIdChanged)

public:
    explicit RecordsModel(QObject* parent = nullptr);
    ~RecordsModel() override = default;

public:
    int getModeId() const;
    void setModeId(const int modeId);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

signals:
    void modeIdChanged(int modeId);

private:
    enum Roles
    {
        Username = Qt::UserRole + 1,
        TimePassed
    };

private:
    std::optional<int> m_modeId;
    QVector<Record> m_records;

private:
    const DBFacade& m_dbFacade;
};

#endif // RECORDSMODEL_H
