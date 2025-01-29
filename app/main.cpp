#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "model/gamefieldmodel.h"
#include "model/modesmodel.h"
#include "model/smplmodesmodel.h"
#include "model/custommodemodel.h"
#include "model/recordsmodel.h"
#include "model/statsmodel.h"
#include "model/settgsmodel.h"
#include "model/celltype.h"
#include "model/tool.h"
#include "entities/mode.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    // reg types!
    qmlRegisterType<GameFieldModel>("GameFieldModel", 1, 0, "GameFieldModel");
    qmlRegisterType<ModesModel>("ModesModel", 1, 0, "ModesModel");
    qmlRegisterType<SmplModesModel>("SmplModesModel", 1, 0, "SmplModesModel");
    qmlRegisterType<CustomModeModel>("CustomModeModel", 1, 0, "CustomModeModel");
    qmlRegisterType<RecordsModel>("RecordsModel", 1, 0, "RecordsModel");
    qmlRegisterType<StatsModel>("StatsModel", 1, 0, "StatsModel");
    qmlRegisterType<SettgsModel>("SettgsModel", 1, 0, "SettgsModel");

    qmlRegisterUncreatableType<WrCellType>("WrCellType", 1, 0, "WrCellType", "WrCellType is enum.");
    qRegisterMetaType<WrCellType::CellType>("WrCellType.CellType");

    qmlRegisterUncreatableType<WrTool>("WrTool", 1, 0, "WrTool", "WrTool is enum.");
    qRegisterMetaType<WrTool::Tool>("WrTool.Tool");

    qmlRegisterUncreatableType<WrMode>("WrMode", 1, 0, "WrMode", "WrMode is enum.");
    qRegisterMetaType<WrMode::Mode>("WrMode.Mode");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](const QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
