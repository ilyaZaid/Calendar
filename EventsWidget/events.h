#ifndef EVENTS_H
#define EVENTS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTreeView>
#include <QModelIndex>

class Events : public QWidget
{
    Q_OBJECT

    enum {
        EventIdRole = Qt::UserRole + 1,
        DateRole
    };

public:
    explicit Events(QWidget *parent = 0);

signals:

public slots:
    void showContextMenuEvents(const QPoint &pos);
    void showContextMenuDesignation(const QPoint &pos);
    void onAddActionTriggered(bool);
    void onAddActionTriggeredD(bool);
    void onTreeVeiwIndexClicket(const QModelIndex &index);
    void onEditActionTriggered(bool);

    void writeInfo();

private:
    QStandardItemModel* informCurrentDate(QDate* date);

    int mIndexEditEvent;
    bool mLawOnEdit;
    QStandardItemModel *mModelEvents;
    QStandardItemModel *mModelDesignation;
    QTreeView *mTreeEvent;
    QTreeView *mTreeDesignation;
    QModelIndex mIndexEditEvent2;

};

#endif // EVENTS_H
