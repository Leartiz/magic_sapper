#ifndef STATS_H
#define STATS_H

#include <optional>

#include <QString>

// common!
class Stats final
{
public:
    struct Tbl
    {
        Tbl() = delete;
        static const QString TblName;
        static const QString Id;
        static const QString ModeId;

        static const QString AmGams;
        static const QString AmWins;

        static const QString AmWinsInRow;
        static const QString AmLossInRow;

        static const QString TmpAmWinsInRow;
        static const QString TmpAmLossInRow;
    };

public:
    Stats();
    explicit Stats(const int id);
    Stats(const int id, const int modeId);

    ~Stats() = default;

public:
    std::optional<int> getId() const;

    std::optional<int> getModeId() const;
    void setModeId(const int modeId);

public:
    int getAmGams() const;
    void setAmGams(int amGams);
    void incAmGams();

    int getAmWins() const;
    void setAmWins(int amWins);
    void incAmWins();

    int getAmWinsInRow() const;
    void setAmWinsInRow(int amWinsInRow);

    int getAmLossInRow() const;
    void setAmLossInRow(int amLossInRow);

public:
    int getTmpAmWinsInRow() const;
    void setTmpAmWinsInRow(int tmpAmWinsInRow);
    void incTmpAmWinsInRow();

    int getTmpAmLossInRow() const;
    void setTmpAmLossInRow(int tmpAmLossInRow);
    void incTmpAmLossInRow();

public:
    void resetStats();

private:
    std::optional<int> m_id;
    std::optional<int> m_modeId;

private:
    int m_amGams;
    int m_amWins;

    int m_amWinsInRow;
    int m_amLossInRow;

private:
    int m_tmpAmWinsInRow;
    int m_tmpAmLossInRow;
};

#endif // STATS_H
