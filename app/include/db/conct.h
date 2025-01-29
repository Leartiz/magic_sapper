#ifndef CONCT_H
#define CONCT_H

#include <QString>

class Conct
{
    Conct() = delete;

    Conct(const Conct&) = delete;
    Conct& operator=(const Conct&) = delete;
public:
    static const QString driverName;
    static const QString dbName;

    static void init();

private:
    static void createTbls();

private:
    static void createDMode();
    static void createSettgs();
    static void createRecord();
    static void createStats();

    // default!
    static void inflateDMode();
    static void inflateSettgs();
    static void inflateStats();
};

#endif // CONCT_H
