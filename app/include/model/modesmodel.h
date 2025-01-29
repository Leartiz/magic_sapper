#ifndef MODESMODEL_H
#define MODESMODEL_H

#include <memory>
#include <optional>

#include <QObject>
#include <QAbstractListModel>

#include <QPair>
#include <QVector>
#include <QByteArray>

#include "db/dbfacade.h"
#include "entities/descriptormode.h"
#include "entities/settgs.h"

class ModesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int curMode READ getCurMode NOTIFY curModeChanged)
    Q_PROPERTY(int curIndx READ getCurIndx NOTIFY curIndxChanged)

public:
    explicit ModesModel(QObject* parent = nullptr);
    ~ModesModel() override = default;

public:
    int getCurMode() const;
    int getCurIndx() const;
    Q_INVOKABLE void setCurModeId(const int modeId);
    Q_INVOKABLE void updCustomDMode();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role) const override;

signals:
    void curModeChanged(int curMode);
    void curIndxChanged(int curIndx);

private:
    enum Roles
    {
        ModeId = Qt::UserRole + 1,
        ModeEnum,
        ModeName,

        // description!
        NumRows,
        NumCols,
        AmBombs
    };

private:
    using DModeAndIndx = QPair<std::shared_ptr<DescriptorMode>, std::optional<int>>;

    DModeAndIndx findCurDMode() const;
    void prepareDModes();

private:
    Settgs m_settgs; // cur mode!
    DModeAndIndx m_curDModeAndIndx;
    QVector<std::shared_ptr<DescriptorMode>> m_dModes;

private:
    const DBFacade& m_dbFacade;
};

#endif // MODESMODEL_H
