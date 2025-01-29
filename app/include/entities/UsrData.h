#ifndef USRDATA_H
#define USRDATA_H

#include <optional>

#include <QString>

// abstract!
class UsrData
{
public:
    virtual ~UsrData() = default;

protected:
    UsrData() = default;

    explicit UsrData(const int id);
    explicit UsrData(const QString& username);
    UsrData(const int id, const QString& username);

public:
    std::optional<int> getId() const;

    const QString& getUsername() const;
    void setUsername(const QString &username);

private:
    std::optional<int> m_id;
    QString m_username;
};

#endif // USRDATA_H
