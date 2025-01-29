#ifndef TOOL_H
#define TOOL_H

#include <QObject>

class WrTool
{
    Q_GADGET

public:
    enum class Tool
    {
        Shovel = 0,

        Flag,
        Question,
        Magic_stick
    };
    Q_ENUM(Tool)
};

#endif // TOOL_H
