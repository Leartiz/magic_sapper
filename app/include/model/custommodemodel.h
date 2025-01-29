#ifndef CUSTOMMODEMODEL_H
#define CUSTOMMODEMODEL_H

#include <QObject>

#include "db/dbfacade.h"
#include "entities/descriptormode.h"

// DMode!
class CustomModeModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int numRows READ getNumRows WRITE setNumRows NOTIFY numRowsChanged)
    Q_PROPERTY(int numCols READ getNumCols WRITE setNumCols NOTIFY numColsChanged)
    Q_PROPERTY(int amBombs READ getAmBombs WRITE setAmBombs NOTIFY amBombsChanged)

public:
    explicit CustomModeModel(QObject* parent = nullptr);
    ~CustomModeModel() override = default;

public:
    int getNumRows() const;
    void setNumRows(int numRows);

    int getNumCols() const;
    void setNumCols(int numCols);

    int getAmBombs() const;
    void setAmBombs(int amBombs);

signals:
    void numRowsChanged(int numRows);
    void numColsChanged(int numCols);
    void amBombsChanged(int amBombs);
    void customDModeChanged();

private:
    DescriptorMode m_dMode;
    const DBFacade& m_dbFacade;
};

#endif // CUSTOMMODEMODEL_H
