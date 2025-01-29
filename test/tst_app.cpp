#include <QtTest>

// add necessary includes here

class App : public QObject
{
    Q_OBJECT

public:
    App();
    ~App();

private slots:
    void test_case1();

};

App::App()
{

}

App::~App()
{

}

void App::test_case1()
{

}

QTEST_APPLESS_MAIN(App)

#include "tst_app.moc"
