#include "model/settgsmodel.h"

SettgsModel::SettgsModel(QObject* parent)
    : QObject(parent)
    , m_dbFacade(DBFacade::instance())
{
    m_settgs = m_dbFacade.selSettgs();
}

QString SettgsModel::getUsername() const
{
    return m_settgs.getUsername();
}

bool SettgsModel::getIsUseQuestionMark() const
{
    return m_settgs.getIsUseQuestionMark();
}

bool SettgsModel::getIsUseSizeSlider() const
{
    return m_settgs.getIsUseSizeSlider();
}

void SettgsModel::setSettgs(const QString& usrname, bool isUseQM, bool isUseSS)
{
    // no check!
    if (!usrname.isEmpty())
    {
        m_settgs.setUsername(usrname);
        emit usernameChanged(getUsername());
    }

    m_settgs.setIsUseQuestionMark(isUseQM);
    m_settgs.setIsUseSizeSlider(isUseSS);

    emit isUseQMChanged(getIsUseQuestionMark());
    emit isUseSSChanged(getIsUseSizeSlider());

    m_dbFacade.updSettgs(m_settgs);
    emit settgsSaved();
}

void SettgsModel::resetStatsAndRecs()
{
    m_dbFacade.delAllRecords();
    auto statss = m_dbFacade.selAllStatss();
    std::for_each(statss.begin(), statss.end(), [&dbFcd = this->m_dbFacade](Stats& vl) {
        vl.resetStats();
        dbFcd.updStats(vl);
    });
    emit statsAndRecsReseted();
}
