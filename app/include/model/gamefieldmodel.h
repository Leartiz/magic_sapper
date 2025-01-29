#ifndef GAMEFIELDMODEL_H
#define GAMEFIELDMODEL_H

#include <optional>
#include <functional>

#include <QSet>
#include <QPair>
#include <QTimer>
#include <QVector>

#include <QObject>
#include <QAbstractListModel>

#include "celltype.h"
#include "tool.h"

#include "db/dbfacade.h"
#include "entities/descriptormode.h"
#include "entities/settgs.h"

class GameFieldModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool isEndGame READ getIsEndGame NOTIFY isEndGameChanged)
    Q_PROPERTY(bool isNeedUpd READ getIsNeedUpd WRITE setIsNeedUpd NOTIFY isNeedUpdChanged)

    Q_PROPERTY(int rowAm READ getRowAm NOTIFY rowAmChanged)
    Q_PROPERTY(int colAm READ getColAm NOTIFY colAmChanged)

    Q_PROPERTY(int nowTool READ getNowTool WRITE setNowTool NOTIFY nowToolChanged)

    Q_PROPERTY(int amBombs READ getAmBombs NOTIFY amBombsChanged)
    Q_PROPERTY(int spendTime READ getSpendTime NOTIFY spendTimeChanged)

    // settgs!
    Q_PROPERTY(bool isUseQuestionMark READ getIsUseQuestionMark NOTIFY isUseQMChanged)
    Q_PROPERTY(bool isUseSizeSlider READ getIsUseSizeSlider NOTIFY isUseSSChanged)

    Q_PROPERTY(int numAvblPromt READ getNumAvblPromt NOTIFY numAvblPromtChanged)

public:
    // start with rows!
    using Point = QPair<int, int>; // i, j
    using Size = QPair<int, int>;

    const Point indexToPoint(int index) const;
    std::optional<int> pointToIndex(const Point& p) const;

    bool isValidIndex(const int index) const;

public:
    explicit GameFieldModel(QObject* parent = nullptr);
    ~GameFieldModel() override = default;

public:
    Q_INVOKABLE bool eqMode(int mode) const;
    Q_INVOKABLE void updatePartFields();
    Q_INVOKABLE void updatePartSettgs();
    Q_INVOKABLE void startNewGame();

    void prepareNewGame();
    void endGame();
    bool getIsEndGame() const;

    int getAmBombs() const;
    int getSpendTime() const;

    // first generation!
    const QSet<Point> generateBombsExcept(const QVector<Point>& pnts) const;
    int calcObjsNumAround(const int index,const std::function<int(const QVector<int>&)>& fnc) const;
    int calcBombsNumAround(const int index) const;
    int calcFlagsNumAround(const int index) const;

    // specific!
    using Vint = QVector<int>;
    QPair<Vint, Vint> getFlagAndQstnIndxsAroundUsingCalc(const int index) const;
    bool bombsContainsIndxs(const Vint& indxs);

public:
    bool getIsUseQuestionMark() const;
    bool getIsUseSizeSlider() const;

    int getNumAvblPromt() const;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex &modIndex, int role) const override;

public:
    Q_INVOKABLE void setCellData(int index);
    Q_INVOKABLE void usePrompt();
    Q_INVOKABLE void setFlagByIndxForUsePrompt();

private:
    // cases!
    void setCellDataForFlag(const int index);
    void setCellDataForQuestion(const int index);
    void setCellDataForShovel(const int index);

    // click!
    void setCellDataForMs(const int index);
    QPair<int, int> openCellsByPoints(const QVector<Point>& points);
    void replaceQstnWithFlag(const Vint& qIxs);

    const QVector<GameFieldModel::Point> generatePointsAround(const GameFieldModel::Point& p) const;
    const QVector<GameFieldModel::Point> generatePointsAroundIncl(const GameFieldModel::Point& p) const;

    // sometimes ignore ret val!
    std::optional<int> openCell(const GameFieldModel::Point& p);
    // return amount all! (old)
    int openCellsAroundRec(const GameFieldModel::Point& p);
    // return amount all and empty!
    QPair<int, int> openCellsAroundLoop(const GameFieldModel::Point& p);

    void setBombsByField();
    void checkWinInGame();

    void saveNewRecordIfBetter();
    void saveGenrStats(); // to db!

public:
    int getRowAm() const;
    int getColAm() const;

    bool getIsNeedUpd() const;
    void setIsNeedUpd(bool isNeedUpd);

    int getNowTool() const;
    Q_INVOKABLE void setNowTool(int tool);

signals:
    void sideSizesWillChanged();
    void sideSizesChanged();

    void rowAmChanged(int rowAm);
    void colAmChanged(int colAm);

    void nowToolChanged(int tool);

    void newGameStarted();
    void isEndGameChanged(bool isEnd);
    void isNeedUpdChanged(bool isNeedUpd);

    void amBombsChanged(int amBombs);
    void spendTimeChanged(int spendTime);

signals:
    // for settgs!
    void isUseQMChanged(bool is);
    void isUseSSChanged(bool is);

signals:
    void openedPartField();

    void numAvblPromtChanged(int nap);
    void numAvblPromtEmptied();

    void gameLosed(); // start anims!
    void gameWined();

private slots:
    void onTimeout();

    void saveGameWinedStats();
    void saveGameLosedStats();

private:
    enum Roles
    {
        cell_data = Qt::UserRole + 1
    };

private:
    WrTool::Tool m_nowTool;

    QTimer m_timer;
    int m_amBombs;
    int m_spendTime;

private:
    std::optional<int> m_indxForUsePrompt;
    bool m_isUsedNoAvblPrompt;

    static const int m_maxNumAvblPromt;
    int m_numAvblPromt;

private:
    bool m_isNeedUpdPartFields;
    bool m_isEndGame;

private:
    Settgs m_settgs;
    DescriptorMode m_dMode;
    Stats m_stats;

private:
    QVector<WrCellType::CellType> m_allField;
    QSet<Point> m_bombs;

private:
    const DBFacade& m_dbFacade;
};

#endif // GAMEFIELDMODEL_H
