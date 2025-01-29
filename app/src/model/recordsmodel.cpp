#include <algorithm>

#include "model/recordsmodel.h"

RecordsModel::RecordsModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_dbFacade(DBFacade::instance())
{
}

int RecordsModel::rowCount(const QModelIndex &) const
{
    return m_records.size();
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{
    if (index.column() != 0)
        return {};
    if (index.row() < 0 && index.row() >= rowCount())
        return {};

    switch (static_cast<Roles>(role))
    {
    case Roles::Username:
        return m_records[index.row()].getUsername();
    case Roles::TimePassed:
        return m_records[index.row()].getTimePassed();
    }
    return {};
}

QHash<int, QByteArray> RecordsModel::roleNames() const
{
    return {
        { static_cast<int>(Roles::Username), QByteArray("Username") },
        { static_cast<int>(Roles::TimePassed), QByteArray("TimePassed") }
    };
}

int RecordsModel::getModeId() const
{
    return m_modeId.value_or(0);
}

void RecordsModel::setModeId(const int modeId)
{
    m_modeId = modeId;
    m_records = m_dbFacade.selRecordsByModeId(m_modeId.value());
    std::sort(m_records.begin(), m_records.end(), [](const Record& lhs, const Record& rhs) {
        return lhs.getTimePassed() < rhs.getTimePassed();
    });

    emit modeIdChanged(m_modeId.value());
    emit layoutChanged();
}
