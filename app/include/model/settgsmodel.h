#ifndef SETTGSMODEL_H
#define SETTGSMODEL_H

#include <QObject>

#include "db/dbfacade.h"
#include "entities/settings.h"

class SettgsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString username READ getUsername NOTIFY usernameChanged)

private:
    Q_PROPERTY(bool isUseQuestionMark READ getIsUseQuestionMark NOTIFY isUseQMChanged)
    Q_PROPERTY(bool isUseSizeSlider READ getIsUseSizeSlider NOTIFY isUseSSChanged)

public:
    explicit SettgsModel(QObject* parent = nullptr);
    ~SettgsModel() override = default;

public:
    QString getUsername() const;
    bool getIsUseQuestionMark() const;
    bool getIsUseSizeSlider() const;

public:
    // save to db!
    Q_INVOKABLE void setSettgs(const QString& usrname, bool isUseQM, bool isUseSS);
    Q_INVOKABLE void resetStatsAndRecs();

signals:
    void usernameChanged(QString usrname);
    void isUseQMChanged(bool is);
    void isUseSSChanged(bool is);

    void settgsSaved();
    void statsAndRecsReseted();

private:
    Settings m_settgs;

private:
    const DBFacade& m_dbFacade;
};

#endif // SETTGSMODEL_H
