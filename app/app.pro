QT       += quick sql core5compat qml gui

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/db/conct.cpp \
        src/db/crudquerycreator.cpp \
        src/db/dbfacade.cpp \
        src/db/sqlqueryconverter.cpp \
        src/entities/descriptormode.cpp \
        src/entities/record.cpp \
        src/entities/settgs.cpp \
        src/entities/stats.cpp \
        src/entities/usrdata.cpp \
        src/model/custommodemodel.cpp \
        src/model/gamefieldmodel.cpp \
        src/model/modesmodel.cpp \
        src/model/recordsmodel.cpp \
        src/model/settgsmodel.cpp \
        src/model/smplmodesmodel.cpp \
        src/model/statsmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += include

HEADERS += \
    include/db/conct.h \
    include/db/crudquerycreator.h \
    include/db/dbfacade.h \
    include/db/sqlqueryconverter.h \
    include/entities/descriptormode.h \
    include/entities/mode.h \
    include/entities/record.h \
    include/entities/settgs.h \
    include/entities/stats.h \
    include/entities/usrdata.h \
    include/model/celltype.h \
    include/model/custommodemodel.h \
    include/model/gamefieldmodel.h \
    include/model/modesmodel.h \
    include/model/recordsmodel.h \
    include/model/settgsmodel.h \
    include/model/smplmodesmodel.h \
    include/model/statsmodel.h \
    include/model/tool.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

message (ANDROID_TARGET_ARCH: $$ANDROID_TARGET_ARCH)
message (QMAKE_TARGET.arch: $$QMAKE_TARGET.arch)
message (QMAKE_HOST.arch: $$QMAKE_HOST.arch)


equals(ANDROID_TARGET_ARCH, x86_64) {
    message( "It's x86_64" )
}
equals(ANDROID_TARGET_ARCH, arm64-v8a) {
    message( "It's arm64-v8a" )
}
equals(ANDROID_TARGET_ARCH, armeabi-v7a) {
    message( "It's armeabi-v7a" )
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.properties
