#ifndef SMPLMODESMODEL_H
#define SMPLMODESMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include <QVector>
#include <QByteArray>

#include "db/dbfacade.h"
#include "entities/descriptormode.h"

class SmplModesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int curModeId READ getCurModeId NOTIFY curModeIdChanged)
    Q_PROPERTY(int curIndx READ getCurIndx WRITE setCurIndx NOTIFY curIndxChanged)

public:
    explicit SmplModesModel(QObject* parent = nullptr);
    void prepareDModes();
    ~SmplModesModel() override = default;

public:
    Q_INVOKABLE int getModeIdByIndx(const int indx) const;

    int getCurIndx() const;
    void setCurIndx(const int indx);

    int getCurModeId() const;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role) const override;

signals:
    void curModeIdChanged(int curModeId);
    void curIndxChanged(int curIndx);

private:
    enum Roles
    {
        ModeId = Qt::UserRole + 1,
        ModeEnum,
        ModeName,
    };

private:
    int m_curIndx;
    QVector<DescriptorMode> m_dModes;

private:
    const DBFacade& m_dbFacade;
};

#endif // SMPLMODESMODEL_H
