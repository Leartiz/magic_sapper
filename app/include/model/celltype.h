#ifndef CELLTYPE_H
#define CELLTYPE_H

#include <QObject>

class WrCellType
{
    Q_GADGET

public:
    enum CellType
    {
        Unknown = 0,

        Num_1 = 1,
        Num_2 = 2,
        Num_3 = 3,
        Num_4 = 4,
        Num_5 = 5,
        Num_6 = 6,
        Num_7 = 7,
        Num_8 = 8,

        Empty,
        Flag,
        Question,
        Bomb,

        Bomb_flag,
        Bomb_question
    };
    Q_ENUM(CellType)
};

#endif // CELLTYPE_H
