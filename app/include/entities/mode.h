#ifndef MODE_H
#define MODE_H

#include <QObject>

class WrMode
{
    Q_GADGET

public:
    enum Mode
    {
        Easy = 0,
        Middle,
        Intricate,
        Unreal,

        Custom
    };
    Q_ENUM(Mode)
};

#endif // MODE_H
