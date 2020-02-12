#ifndef NODEATTRIBUTETABLEMODEL_H
#define NODEATTRIBUTETABLEMODEL_H

#include "shared/graph/elementid.h"
#include "shared/ui/idocument.h"
#include "shared/plugins/userelementdata.h"

#include <QAbstractTableModel>
#include <QStringList>
#include <QHash>
#include <QObject>

#include <vector>
#include <mutex>
#include <deque>

class Graph;
class IGraph;

class NodeAttributeTableModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList columnNames MEMBER _columnNames NOTIFY columnNamesChanged)

private:
    IDocument* _document = nullptr;
    const IGraph* _graph = nullptr;
    const UserNodeData* _userNodeData = nullptr;

    QHash<int, QByteArray> _roleNames;
    std::recursive_mutex _updateMutex;
    std::vector<QString> _columnsRequiringUpdates;

    using Column = std::vector<QVariant>;
    using Table = std::vector<Column>;

    Column _nodeSelectedColumn;
    Column _nodeIdColumn;

    Table _pendingData; // Update actually occurs here, before being copied to _data on the UI thread
    Table _data;

    QStringList _columnNames;

    int _columnCount = 0;

protected:
    virtual QStringList columnNames() const;
    virtual QVariant dataValue(size_t row, const QString& columnName) const;

    int indexForColumnName(const QString& attributeName);

private:
    void onColumnAdded(size_t columnIndex);
    void onColumnRemoved(size_t columnIndex);
    void updateAttribute(const QString& attributeName);
    void updateColumn(int role, Column& column, const QString& columnName = {});
    void update();

private slots:
    void onUpdateColumnComplete(const QString& columnName);
    void onUpdateComplete();
    void onGraphChanged(const Graph*, bool);

public:
    enum Roles
    {
        NodeIdRole = Qt::UserRole + 1,
        NodeSelectedRole,
        FirstAttributeRole
    };

    void initialise(IDocument* document, UserNodeData* userNodeData);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override { return _roleNames; }

    void onSelectionChanged();

    Q_INVOKABLE virtual bool columnIsCalculated(const QString& columnName) const;
    Q_INVOKABLE virtual bool columnIsHiddenByDefault(const QString& columnName) const;
    Q_INVOKABLE void moveFocusToNodeForRowIndex(size_t row);
    Q_INVOKABLE virtual bool columnIsFloatingPoint(const QString& columnName) const;
    Q_INVOKABLE virtual bool columnIsNumerical(const QString& columnName) const;
    Q_INVOKABLE virtual bool rowVisible(size_t row) const;
    Q_INVOKABLE virtual QString columnNameFor(size_t column) const;

    void updateColumnNames();

public slots:
    void onAttributesChanged(const QStringList& added, const QStringList& removed);
    void onAttributeValuesChanged(const QStringList& attributeNames);

signals:
    void columnNamesChanged();
    void columnAdded(size_t index, const QString& name);
    void columnRemoved(size_t index, const QString& name);
    void selectionChanged();
};

#endif // NODEATTRIBUTETABLEMODEL_H
