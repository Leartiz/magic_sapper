#ifndef STATSMODEL_H
#define STATSMODEL_H

#include <memory>

#include <QObject>

#include "db/dbfacade.h"
#include "entities/stats.h"

// readonly!
class StatsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int modeId READ getModeId WRITE setModeId NOTIFY modeIdChanged)

    Q_PROPERTY(int amGams READ getAmGams NOTIFY amGamsChanged)
    Q_PROPERTY(int amWins READ getAmWins NOTIFY amWinsChanged)

    Q_PROPERTY(int amWinsInRow READ getAmWinsInRow NOTIFY amWinsInRowChanged)
    Q_PROPERTY(int amLossInRow READ getAmLossInRow NOTIFY amLossInRowChanged)

    Q_PROPERTY(double percentWin READ getPercentWin NOTIFY percentWinChanged)

public:
    explicit StatsModel(QObject* parent = nullptr);
    ~StatsModel() override = default;

public:
    int getModeId() const;
    void setModeId(const int modeId);

    int getAmGams() const;
    int getAmWins() const;

    int getAmWinsInRow() const;
    int getAmLossInRow() const;

    double getPercentWin() const;

signals:
    void modeIdChanged(int modeId);

    void amGamsChanged(int amGams);
    void amWinsChanged(int amWins);

    void amWinsInRowChanged(int amWinsInRow);
    void amLossInRowChanged(int amLossInRow);

    void percentWinChanged(int perWin);

private:
    std::optional<int> m_modeId;
    std::unique_ptr<Stats> m_stats;

private:
    const DBFacade& m_dbFacade;
};

#endif // STATSMODEL_H
