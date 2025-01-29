#include <random>
#include <chrono>
#include <algorithm>

#include <QDebug>
#include <QStack>
#include <QByteArray>

#include "model/gamefieldmodel.h"

namespace
{
    struct PointGenerator
    {
        const GameFieldModel::Point operator()(const GameFieldModel::Size& sz)
        {
            static const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            static std::default_random_engine eng(seed);

            // size is not const!
            std::uniform_int_distribution<int> distRw(0, sz.first - 1); // row
            std::uniform_int_distribution<int> distCl(0, sz.second - 1); // col
            return { distRw(eng), distCl(eng) };
        }
    };
}

const GameFieldModel::Point GameFieldModel::indexToPoint(int index) const
{
    const GameFieldModel::Point p = {
        index / m_dMode.getSideSzs().second,
        index % m_dMode.getSideSzs().second
    };
    return p;
}

std::optional<int> GameFieldModel::pointToIndex(const GameFieldModel::Point& p) const
{
    if (p.first < 0 || p.first >= m_dMode.getSideSzs().first) // rows
        return std::nullopt;
    if (p.second < 0 || p.second >= m_dMode.getSideSzs().second) // cols
        return std::nullopt;
    return p.first * m_dMode.getSideSzs().second + p.second;
}

bool GameFieldModel::isValidIndex(const int index) const
{
    if (index < 0 && index >= rowCount())
        return false;
    return true;
}

// static!
const int GameFieldModel::m_maxNumAvblPromt = 3;

GameFieldModel::GameFieldModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_nowTool(WrTool::Tool::Shovel)
    , m_amBombs(0)
    , m_spendTime(0)

    , m_isUsedNoAvblPrompt(false)
    , m_numAvblPromt(m_maxNumAvblPromt)

    , m_isNeedUpdPartFields(false)
    , m_isEndGame(false)

    , m_dbFacade(DBFacade::instance())
{
    connect(&m_timer, &QTimer::timeout, this, &GameFieldModel::onTimeout); // one time!
    connect(this, &GameFieldModel::gameWined, this, &GameFieldModel::saveGameWinedStats);
    connect(this, &GameFieldModel::gameLosed, this, &GameFieldModel::saveGameLosedStats);

    m_settgs = m_dbFacade.selSettgs();
    m_dMode = m_dbFacade.selDModeById(m_settgs.getModeId().value());
    m_stats = m_dbFacade.selStatsByModeId(m_dMode.getId().value());

    prepareNewGame();
}

bool GameFieldModel::eqMode(int mode) const
{
    return static_cast<int>(m_dMode.getMode()) == mode;
}

void GameFieldModel::updatePartFields()
{
    m_settgs = m_dbFacade.selSettgs();
    m_dMode = m_dbFacade.selDModeById(m_settgs.getModeId().value());
    m_stats = m_dbFacade.selStatsByModeId(m_dMode.getId().value());

    m_isNeedUpdPartFields = false;

    const auto sideSzs = m_dMode.getSideSzs();
    {
        emit sideSizesWillChanged();

        emit colAmChanged(sideSzs.second);
        emit rowAmChanged(sideSzs.first);

        emit sideSizesChanged();
    }
}

// safe!
void GameFieldModel::updatePartSettgs()
{
    const Settgs settgs = m_dbFacade.selSettgs();
    m_settgs.setUsername(settgs.getUsername());
    m_settgs.setIsUseQuestionMark(settgs.getIsUseQuestionMark());
    m_settgs.setIsUseSizeSlider(settgs.getIsUseSizeSlider());

    // use signals!
    emit isUseQMChanged(getIsUseQuestionMark());
    emit isUseSSChanged(getIsUseSizeSlider());
}

void GameFieldModel::startNewGame()
{
    if (m_isNeedUpdPartFields == true)
        updatePartFields();

    prepareNewGame();

    m_isEndGame = false;
    emit isEndGameChanged(m_isEndGame);

    m_timer.stop();
    m_spendTime = 0;
    // and bombs!

    m_numAvblPromt = m_maxNumAvblPromt;
    emit numAvblPromtChanged(m_numAvblPromt);
    m_isUsedNoAvblPrompt = false;

    emit amBombsChanged(m_amBombs);
    emit spendTimeChanged(m_spendTime);

    emit newGameStarted();
    emit layoutChanged();
}

void GameFieldModel::prepareNewGame()
{
    m_amBombs = m_dMode.getAmBombs();
    m_allField.clear(); // destruct!
    const Size& sz = m_dMode.getSideSzs(); // alias!
    m_allField.reserve(sz.first * sz.second);
    std::fill_n(std::back_inserter(m_allField), sz.first * sz.second, WrCellType::Unknown);
    m_bombs.clear(); // to empty!
}

void GameFieldModel::endGame()
{
    m_timer.stop();
    m_isEndGame = true;
    emit isEndGameChanged(m_isEndGame);
}

bool GameFieldModel::getIsEndGame() const
{
    return m_isEndGame;
}

int GameFieldModel::getAmBombs() const
{
    return m_amBombs;
}

int GameFieldModel::getSpendTime() const
{
    return m_spendTime;
}

const QSet<GameFieldModel::Point> GameFieldModel::generateBombsExcept(const QVector<Point>& pnts) const
{
    const int amBombs = m_dMode.getAmBombs(); // const!
    const Size& sideSzs = m_dMode.getSideSzs();
    QSet<GameFieldModel::Point> bombs;
    bombs.reserve(amBombs);
    PointGenerator pg;
    while (bombs.size() < amBombs)
    {
        const Point pBomb = pg(sideSzs);
        if (pnts.contains(pBomb))
            continue;

        bombs.insert(pBomb);
    }
    return bombs;
}

int GameFieldModel::calcObjsNumAround(
        const int index, const std::function<int(const QVector<int>&)>& fnc) const
{
    const Point p = indexToPoint(index);
    const Size& sideSzs = m_dMode.getSideSzs();
    const int cols = static_cast<int>(sideSzs.second);

    // corners!
    if (p.first == 0 && p.second == 0) // lt
        return fnc({index + 1, index + cols, index + cols + 1});
    if (p.first == sideSzs.first - 1 && p.second == 0) // lb
        return fnc({index + 1, index - cols, index - cols + 1});
    if (p.first == 0 && p.second == sideSzs.second - 1) // rt
        return fnc({index - 1, index + cols, index + cols - 1});
    if (p.first == sideSzs.second - 1 && p.second == sideSzs.second - 1) // rt
        return fnc({index - 1, index - cols, index - cols - 1});

    // sides!
    if (p.first == 0) // t
        return fnc({index - 1, index + 1, index + cols, index + cols + 1, index + cols - 1});
    if (p.first == sideSzs.first - 1) // b
        return fnc({index - 1, index + 1, index - cols, index - cols + 1, index - cols - 1});
    if (p.second == 0) // l
        return fnc({index + 1, index + cols, index - cols, index + cols + 1, index - cols + 1});
    if (p.second == sideSzs.second - 1) // r
        return fnc({index - 1, index + cols, index - cols, index + cols - 1, index - cols - 1});

    // other
    return fnc({index - 1, index + 1,
                    index + cols, index - cols,
                    index + cols + 1, index + cols - 1,
                    index - cols + 1, index - cols - 1});
}

int GameFieldModel::calcBombsNumAround(const int index) const
{
    return calcObjsNumAround(index, [this](const QVector<int>& indxs) -> int {
        int num = 0;
        for (const auto& indx : indxs)
            if (m_bombs.contains(indexToPoint(indx)))
                ++num;
        return num;
    });
}

int GameFieldModel::calcFlagsNumAround(const int index) const
{
    return calcObjsNumAround(index, [this](const QVector<int>& indxs) -> int {
        int num = 0;
        for (const auto& indx : indxs)
            if (m_allField[indx] == WrCellType::Flag)
                ++num;
        return num;
    });
}

QPair<QVector<int>, QVector<int>> GameFieldModel::getFlagAndQstnIndxsAroundUsingCalc(const int index) const
{
    Vint flgsIndxs;
    Vint qstnIndxs;
    calcObjsNumAround(index, [this, &flgsIndxs, &qstnIndxs](const QVector<int>& indxs) -> int {
        for (const auto& indx : indxs)
        {
            if (m_allField[indx] == WrCellType::Flag)
                flgsIndxs.push_back(indx);
            else if (m_allField[indx] == WrCellType::Question)
                qstnIndxs.push_back(indx);
        }
        return flgsIndxs.size() + qstnIndxs.size(); // not used!
    });
    return { flgsIndxs, qstnIndxs };
}

bool GameFieldModel::bombsContainsIndxs(const Vint& indxs)
{
    foreach(const int ix, indxs) // or ref?
        if (!m_bombs.contains(indexToPoint(ix)))
            return false;
    return true;
}

bool GameFieldModel::getIsUseQuestionMark() const
{
    return m_settgs.getIsUseQuestionMark();
}

bool GameFieldModel::getIsUseSizeSlider() const
{
    return m_settgs.getIsUseSizeSlider();
}

int GameFieldModel::getNumAvblPromt() const
{
    return m_numAvblPromt;
}

QHash<int, QByteArray> GameFieldModel::roleNames() const
{
    return {
        { static_cast<int>(Roles::cell_data), QByteArray("CellData") }
    };
}

int GameFieldModel::rowCount(const QModelIndex&) const
{
    return m_allField.size();
}

QVariant GameFieldModel::data(const QModelIndex &modIndex, int role) const
{
    if (modIndex.column() != 0)
        return {};
    if (modIndex.row() < 0 && modIndex.row() >= rowCount())
        return {};

    switch (static_cast<Roles>(role))
    {
    case Roles::cell_data:
        return static_cast<int>(m_allField[modIndex.row()]);
    }
    return {};
}

void GameFieldModel::setCellData(int index)
{
    if (!isValidIndex(index))
        return;

    switch (m_nowTool)
    {
    case WrTool::Tool::Flag:
        setCellDataForFlag(index);
        break;
    case WrTool::Tool::Question:
        setCellDataForQuestion(index);
        break;
    case WrTool::Tool::Shovel:
        setCellDataForShovel(index);
        break;
    case WrTool::Tool::Magic_stick:
        setCellDataForMs(index);
        break;
    }

    emit dataChanged(createIndex(0, 0), createIndex(rowCount(), 0));
    checkWinInGame();
}

void GameFieldModel::usePrompt()
{
    foreach(const Point& p, m_bombs)
    {
        const auto indx = pointToIndex(p);
        if (!indx.has_value())
            continue;

        const auto& ct = m_allField[indx.value()];
        if (ct == WrCellType::Unknown || ct == WrCellType::Question)
        {
            m_indxForUsePrompt = indx.value();
            if (m_numAvblPromt == 0)
            {
                emit numAvblPromtEmptied();
                break;
            }
            setFlagByIndxForUsePrompt();
            break;
        }
    }
}

void GameFieldModel::setFlagByIndxForUsePrompt()
{
    if (!m_indxForUsePrompt.has_value())
        return;

    if (m_numAvblPromt == 0)
        m_isUsedNoAvblPrompt = true;

    if (!m_isUsedNoAvblPrompt)
    {
        --m_numAvblPromt;
        emit numAvblPromtChanged(getNumAvblPromt());
    }

    const auto indxFup = m_indxForUsePrompt.value();
    m_indxForUsePrompt.reset();

    m_allField[indxFup] = WrCellType::Flag;
    const auto modelIndx = createIndex(indxFup, 0);
    --m_amBombs;

    emit amBombsChanged(getAmBombs());
    emit dataChanged(modelIndx, modelIndx);
    checkWinInGame(); // as last step!
}

void GameFieldModel::setCellDataForFlag(const int index)
{
    if (m_allField[index] == WrCellType::Unknown || m_allField[index] == WrCellType::Question)
    {
        m_allField[index] = WrCellType::Flag;
        --m_amBombs;
    }

    else if (m_allField[index] == WrCellType::Flag)
    {
        m_allField[index] = WrCellType::Unknown;
        ++m_amBombs;
    }
    emit amBombsChanged(getAmBombs());
}

void GameFieldModel::setCellDataForQuestion(const int index)
{
    if (m_allField[index] == WrCellType::Unknown)
        m_allField[index] = WrCellType::Question;
    else if (m_allField[index] == WrCellType::Flag)
    {
        m_allField[index] = WrCellType::Question;
        ++m_amBombs;
        emit amBombsChanged(getAmBombs());
    }
    else if (m_allField[index] == WrCellType::Question)
        m_allField[index] = WrCellType::Unknown;
}

void GameFieldModel::setCellDataForShovel(const int index)
{
    if (!m_timer.isActive()) // tics!
        m_timer.start(1000);

    if (m_allField[index] == WrCellType::Flag)
    {
        m_allField[index] = WrCellType::Unknown;
        ++m_amBombs;
        emit amBombsChanged(getAmBombs());
        return;
    }
    if (m_allField[index] == WrCellType::Question)
    {
        m_allField[index] = WrCellType::Unknown;
        return;
    }

    if (m_allField[index] != WrCellType::Unknown)
        return;

    if (m_bombs.empty())
    {
        const Point p = indexToPoint(index);
        m_bombs = generateBombsExcept(generatePointsAroundIncl(p)); // at first!
        openCellsAroundLoop(indexToPoint(index));
        return;
    }

    if (!m_bombs.contains(indexToPoint(index)))
    {
        // use amount all!
        if (openCellsAroundLoop(indexToPoint(index)).first > 1)
            emit openedPartField();
        return;
    }

    setBombsByField();
}

void GameFieldModel::setBombsByField()
{
    std::for_each(m_bombs.begin(), m_bombs.end(), [this](const QSet<Point>::value_type& val) -> void {
        const auto optIndx = pointToIndex(val);
        if (!optIndx.has_value()) // no possible!
            return;

        if (m_allField[optIndx.value()] == WrCellType::Flag)
        {
            m_allField[optIndx.value()] = WrCellType::Bomb_flag;
            return;
        }
        if (m_allField[optIndx.value()] == WrCellType::Question)
        {
            m_allField[optIndx.value()] = WrCellType::Bomb_question;
            return;
        }
        m_allField[optIndx.value()] = WrCellType::Bomb;
    });
    endGame();
    emit gameLosed();
}

void GameFieldModel::checkWinInGame()
{
    if (getAmBombs() != 0)
        return;

    for (auto itCType = m_allField.begin(); itCType != m_allField.end(); ++itCType)
    {
        const auto cType = *itCType;
        if (cType == WrCellType::Unknown)
            return;
        if (cType == WrCellType::Question)
            return;

        const auto indx = static_cast<int>(std::distance(m_allField.begin(), itCType)); // O(1)?
        if (cType == WrCellType::Flag)
        {
            const Point p = indexToPoint(indx);
            if (!m_bombs.contains(p))
                return;
        }
    }
    endGame();

    // save record if!
    if (m_dMode.getMode() != WrMode::Custom && !m_isUsedNoAvblPrompt)
        saveNewRecordIfBetter();

    emit gameWined();
}

void GameFieldModel::saveNewRecordIfBetter()
{
    QVector<Record> recs = m_dbFacade.selRecordsByModeId(m_dMode.getId().value());
    const Record newRec(m_settgs.getUsername(), m_settgs.getModeId().value(), m_spendTime);
    if (recs.size() < m_settgs.getMaxAmRecords())
    {
        m_dbFacade.insRecord(newRec);
        return;
    }

    std::sort(recs.begin(), recs.end(), [](const Record& lhs, const Record& rhs) {
        return lhs.getTimePassed() < rhs.getTimePassed();
    });

    // worse than!
    if (newRec.getTimePassed() > recs.back().getTimePassed())
        return;

    m_dbFacade.delRecordById(recs.back().getId().value()); // bad!
    m_dbFacade.insRecord(newRec);
}

void GameFieldModel::saveGameWinedStats()
{
    if (m_dMode.getMode() == WrMode::Custom || m_isUsedNoAvblPrompt)
        return;

    m_stats.incAmWins();
    m_stats.setTmpAmLossInRow(0); // rst!
    m_stats.incTmpAmWinsInRow();
    saveGenrStats();
}

void GameFieldModel::saveGameLosedStats()
{
    if (m_dMode.getMode() == WrMode::Custom || m_isUsedNoAvblPrompt)
        return;

    m_stats.setTmpAmWinsInRow(0);
    m_stats.incTmpAmLossInRow();
    saveGenrStats();
}

void GameFieldModel::saveGenrStats()
{
    m_stats.incAmGams();
    m_dbFacade.updStats(m_stats);
}

void GameFieldModel::onTimeout()
{
    ++m_spendTime;
    emit spendTimeChanged(m_spendTime);
}

const QVector<GameFieldModel::Point> GameFieldModel::generatePointsAround(
        const GameFieldModel::Point& p) const
{
    // no check!
    return {
        // sides!
        {p.first + 1, p.second},
        {p.first - 1, p.second},
        {p.first, p.second + 1},
        {p.first, p.second - 1},

        // corners!
        {p.first + 1, p.second + 1},
        {p.first - 1, p.second + 1},
        {p.first + 1, p.second - 1},
        {p.first - 1, p.second - 1}
    };
}

const QVector<GameFieldModel::Point> GameFieldModel::generatePointsAroundIncl(
        const GameFieldModel::Point& p) const
{
    auto pnts = generatePointsAround(p);
    pnts.append(p);
    return pnts;
}

std::optional<int> GameFieldModel::openCell(const GameFieldModel::Point& p)
{
    if (m_isEndGame)
        return 0;

    const auto optIndx = pointToIndex(p);
    if (!optIndx.has_value())
        return 0;

    const WrCellType::CellType ct = m_allField[optIndx.value()];
    if (ct != WrCellType::Unknown && ct != WrCellType::Question)
        return 0;

    // only if use magic stick!
    if (m_bombs.contains(p))
    {
        setBombsByField();
        return 0;
    }

    // border!
    const int bombsNum = calcBombsNumAround(optIndx.value());
    if (bombsNum > 0)
    {
        m_allField[optIndx.value()] = static_cast<WrCellType::CellType>(bombsNum);
        return 1;
    }
    m_allField[optIndx.value()] = WrCellType::Empty;
    return std::nullopt;
}

int GameFieldModel::openCellsAroundRec(const GameFieldModel::Point& p)
{
    const auto optAmOpenedCells = openCell(p);
    if (optAmOpenedCells.has_value())
        return optAmOpenedCells.value();

    int nextAmOpenedCells = 1; // add empty!
    const auto pointsAround = generatePointsAround(p);
    std::for_each(pointsAround.begin(), pointsAround.end(), [this, &nextAmOpenedCells](const GameFieldModel::Point& val) {
        nextAmOpenedCells += openCellsAroundRec(val);
    });
    return nextAmOpenedCells;
}

QPair<int, int> GameFieldModel::openCellsAroundLoop(const GameFieldModel::Point& p)
{
    // used in other funcs!
    int nextAmOpenedCells = 0;
    int amEmptyOpenedCells = 0;

    QStack<GameFieldModel::Point> stack;
    stack.push(p);
    while (!stack.isEmpty() && !m_isEndGame) // extra!
    {
        const auto topPoint = stack.top();
        const auto optAmOpenedCells = openCell(topPoint);
        if (optAmOpenedCells.has_value())
        {
            nextAmOpenedCells += optAmOpenedCells.value();
            stack.pop();
            continue;
        }
        ++nextAmOpenedCells;
        ++amEmptyOpenedCells;
        stack.pop();
        stack.append(generatePointsAround(topPoint));
    }
    return { nextAmOpenedCells, amEmptyOpenedCells };
}

void GameFieldModel::setCellDataForMs(const int index)
{
    // borders!
    const int bombsNum1 = static_cast<int>(WrCellType::Num_1);
    const int bombsNum8 = static_cast<int>(WrCellType::Num_8);

    // only nums!
    const int possibleBombsNum = static_cast<int>(m_allField[index]);
    if (possibleBombsNum < bombsNum1 || possibleBombsNum > bombsNum8)
        return;

    const auto flgsAndQstnIndxs = getFlagAndQstnIndxsAroundUsingCalc(index);
    const Vint& fIxs = flgsAndQstnIndxs.first;
    const Vint& qIxs = flgsAndQstnIndxs.second;

    const auto flgsNum = fIxs.size();
    const auto qstnNum = qIxs.size();
    if (flgsNum + qstnNum < possibleBombsNum)
        return;
    if (flgsNum > possibleBombsNum)
        return;

    // not current point!
    const GameFieldModel::Point p = indexToPoint(index);
    const auto pointsAround = generatePointsAround(p);

    // main case!
    int amEmptyOpenedCells = 0;
    if (flgsNum == possibleBombsNum)
        amEmptyOpenedCells = openCellsByPoints(pointsAround).second;
    else if (flgsNum == 0 && qstnNum == possibleBombsNum)
    {
        if (!bombsContainsIndxs(qIxs))
            return;
        replaceQstnWithFlag(qIxs);
        amEmptyOpenedCells = openCellsByPoints(pointsAround).second;
    }
    else if (flgsNum > 0 && flgsNum + qstnNum == possibleBombsNum)
    {
        if (!bombsContainsIndxs(fIxs) || !bombsContainsIndxs(qIxs))
            return;
        replaceQstnWithFlag(qIxs);
        amEmptyOpenedCells = openCellsByPoints(pointsAround).second;
    }

    // anim!
    if (amEmptyOpenedCells > 0)
        emit openedPartField();
}

QPair<int, int> GameFieldModel::openCellsByPoints(const QVector<Point>& points)
{
    QPair<int, int> someAms = { 0, 0 };
    std::for_each(points.begin(), points.end(), [this, &someAms](const GameFieldModel::Point& val) {
        const auto partSomeAms = openCellsAroundLoop(val);
        someAms.first += partSomeAms.first;
        someAms.second += partSomeAms.second;
    });
    return someAms;
}

void GameFieldModel::replaceQstnWithFlag(const Vint& qIxs)
{
    std::for_each(qIxs.begin(), qIxs.end(), [this](const int ix) {
        m_allField[ix] = WrCellType::Flag;
        --m_amBombs;
    });
    emit amBombsChanged(getAmBombs());
}

int GameFieldModel::getRowAm() const
{
    return m_dMode.getSideSzs().first;
}

int GameFieldModel::getColAm() const
{
    return m_dMode.getSideSzs().second;
}

bool GameFieldModel::getIsNeedUpd() const
{
    return m_isNeedUpdPartFields;
}

void GameFieldModel::setIsNeedUpd(bool isNeedUpd)
{
    m_isNeedUpdPartFields = isNeedUpd;
    emit isNeedUpdChanged(getIsNeedUpd());
}

int GameFieldModel::getNowTool() const
{
    return static_cast<int>(m_nowTool);
}

void GameFieldModel::setNowTool(int tool)
{
    m_nowTool = static_cast<WrTool::Tool>(tool);
    emit nowToolChanged(getNowTool());
}
