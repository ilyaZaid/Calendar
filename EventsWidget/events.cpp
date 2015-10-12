#include "events.h"
#include "designationdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QDate>
#include <QStandardItem>
#include <QComboBox>
#include <QItemDelegate>
#include "comboboxdelegate.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QXmlStreamReader>
#include <QUuid>

Events::Events(QWidget *parent) : QWidget(parent)
{
    QLabel* hat = new QLabel;
    hat->setText(tr("Список запланированных мероприятий:"));

    mTreeEvent = new QTreeView;
    mTreeDesignation = new QTreeView;

    mTreeEvent->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mTreeEvent, SIGNAL(customContextMenuRequested(QPoint)),
    this, SLOT(showContextMenuEvents(QPoint)));

    mTreeDesignation->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mTreeDesignation, SIGNAL(customContextMenuRequested(QPoint)),
    this, SLOT(showContextMenuDesignation(QPoint)));

    ComboBoxDelegate* delegate = new ComboBoxDelegate();

    //-------Получаем из файла---------
    QList<QString> list;
    list<<"123";
    list<<"545";
    list<<"43";
    list<<"543";
    //--------------------

    delegate->setEventType(list);

    mTreeEvent->setItemDelegateForColumn(1,delegate);

    mTreeEvent->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(mTreeEvent,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onTreeVeiwIndexClicket(QModelIndex)));
    connect(mTreeEvent,SIGNAL(clicked(QModelIndex)),this,SLOT(onTreeVeiwIndexClicket(QModelIndex)));


    mModelEvents = new QStandardItemModel;
    mModelDesignation = new QStandardItemModel;

//---------- На полученную дату создаем модель-------------


    QDate date;
    date = QDate::currentDate();
    //int id = 10;

    QStandardItem *color = new QStandardItem("Синий");
    QStandardItem *nameType = new QStandardItem("Выходной");
    QString id = QString("%0").arg(QString::fromLatin1(QUuid::createUuid().toRfc4122().toHex().right(6)));

    nameType->setData(id,EventIdRole);

    QStandardItem *eventName = new QStandardItem("День независимости");
    eventName->setData(date,DateRole);
    eventName->setData(id,EventIdRole);

    mModelEvents->appendRow({eventName});
    mLawOnEdit << false;


    mModelDesignation->appendRow({color, nameType});

// ---------------------------------------------------

    mModelEvents->setHorizontalHeaderLabels({tr("Название мероприятия"), tr("Вид мероприятия")});
    mModelDesignation->setHorizontalHeaderLabels({tr("Цвет"), tr("Название")});

    mTreeEvent->setModel(mModelEvents);
    mTreeDesignation->setModel(mModelDesignation);


    QLabel* caption = new QLabel;
    caption->setText(tr("Условные обозначения"));

    QPushButton* allEvents = new QPushButton;
    allEvents->setText(tr("Общий список мероприятий"));

    QPushButton* upButton = new QPushButton;
    upButton->setText(tr("Вверх"));

    QPushButton* dounButton = new QPushButton;
    dounButton->setText(tr("Вниз"));

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout->addWidget(upButton);
    hLayout->addWidget(dounButton);

    vLayout->addWidget(hat);
    vLayout->addWidget(mTreeEvent);
    vLayout->addWidget(allEvents);
    vLayout->addWidget(caption);
    vLayout->addWidget(mTreeDesignation);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout);

    mLawOnEdit=false;
    QDate d = QDate::currentDate();
    //writeInfo();
    informCurrentDate(&d);

    //DesignationDialog dt;
    //dt.show();
}

QStandardItemModel* Events::informCurrentDate(QDate *date)
{
//----возвращаем модель на текущий месяц
    QFile* file = new QFile("AllEvents.xml");

    QStandardItem *typeEvent = new QStandardItem;
   // typeEvent->setData(date,DateRole);
    //typeEvent->setData(id,EventIdRole);

    QStandardItem *eventName = new QStandardItem;
    //eventName->setData(date,DateRole);
    //eventName->setData(id,EventIdRole);

    if(file->open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xmlReader(file);
        QString date2;
        while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement
            && xmlReader.name() == "events"))
        {

            if (xmlReader.name() == "event1")
            {
                QXmlStreamAttributes streamAttributes = xmlReader.attributes();
                date2 = streamAttributes.value("day").toString();
            }
        xmlReader.readNext();
        }
    }
}



void Events::writeInfo()
{
    QFile file("AllEvents.xml");
    QStandardItem *itemOne;
    QStandardItem *itemTwo;
    QDomDocument doc;
    QDomElement sittings = doc.createElement("sittings");
    QDomElement events = doc.createElement("events");
    doc.appendChild(sittings);
    sittings.appendChild(events);
    QDomElement event;

    for (int i=0; i<mModelEvents->rowCount();  i++)
    {
        itemOne = mModelEvents->item(i,0);
        itemTwo = mModelEvents->item(i,1);

        event = doc.createElement(QString("event%0").arg(i));
        QDate date = itemOne->data(DateRole).toDate();
        event.setAttribute("year",date.year());
        event.setAttribute("month",date.month());
        event.setAttribute("day",date.day());
        event.setAttribute("name",itemOne->text());
        event.setAttribute("type",itemTwo->text());
        event.setAttribute("id",itemOne->data(EventIdRole).toString());
        events.appendChild(event);
    }

    QDomElement designations = doc.createElement("designations");
    sittings.appendChild(designations);
    QDomElement designation;

    for (int i=0; i<mModelDesignation->rowCount();  i++)
    {
        itemOne = mModelDesignation->item(i,0);
        itemTwo = mModelDesignation->item(i,1);

        designation = doc.createElement(QString("designation%0").arg(i));
        designation.setAttribute("color",itemOne->text());
        designation.setAttribute("name",itemTwo->text());
        designation.setAttribute("id",itemOne->data(EventIdRole).toString());
        designations.appendChild(designation);
    }

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        doc.save(out, 2);
        file.close();
    }

}



void Events::onAddActionTriggered(bool)
{
    QStandardItem *locationIdItem = new QStandardItem("Нет данных");
    QStandardItem *locationDescriptionItem = new QStandardItem("Нет данных");

    mModelEvents->appendRow({locationIdItem, locationDescriptionItem});

    QStandardItem *item = new QStandardItem;

     writeInfo();

//--------------------
    QList<QStandardItem*> t;
    t= mModelEvents->findItems("43",Qt::MatchExactly,1);

    QFile file("test.txt");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        item = mModelEvents->item(0,0);
        out<<item->text();
        item = mModelEvents->item(0,1);
        out<<item->text();
        file.close();
    }
// -------------------

    mLawOnEdit=true;

    mIndexEditEvent = mModelEvents->rowCount()-1;

   // QMessageBox g;
  //  int i = mModelEvents->rowCount();
  //  g.setText(QString("%1").arg(i));
 //   g.exec();

}

void Events::onEditActionTriggered(bool)
{
        mTreeEvent->edit(mIndexEditEvent2);
        mIndexEditEvent = mIndexEditEvent2.row();
        mLawOnEdit = true;
}

void Events::onAddActionTriggeredD(bool)
{
    DesignationDialog desDialog;
    if (desDialog.exec() == QDialog::Accepted)
    {

        //
    }
}

void Events::onTreeVeiwIndexClicket(const QModelIndex &index)
{
    mIndexEditEvent2 = index;
    if (index.row() == mIndexEditEvent && mLawOnEdit)
         mTreeEvent->edit(index);
    else
    {
         mTreeEvent->setEditTriggers(QAbstractItemView::NoEditTriggers);
         mLawOnEdit = false;
    }
}

void Events::showContextMenuEvents(const QPoint &pos)
{
    // получаем глобальные координаты
    QPoint globalPos;
    // если запрос от QAbstractScrollArea
    if (sender()->inherits("QAbstractScrollArea"))
        globalPos = ((QAbstractScrollArea*)sender())->viewport()->mapToGlobal(pos);
    // если от других виджетов
    else
        globalPos = ((QWidget*)sender())->mapToGlobal(pos);

    QMenu menu;
    QAction *actionAdd = new QAction(tr("Добавить"), this);
    QAction *actionEdit = new QAction(tr("Переименовать"), this);
    QAction *actionRemove = new QAction(tr("Удалить"), this);

    menu.addAction(actionAdd);
    menu.addAction(actionEdit);
    menu.addAction(actionRemove);

    connect(actionAdd, SIGNAL(triggered(bool)), this,SLOT(onAddActionTriggered(bool)));
    connect(actionEdit, SIGNAL(triggered(bool)), this,SLOT(onEditActionTriggered(bool)));


    // отображаем меню и обрабатываем пользовательский выбор
    QAction* selectedItem = menu.exec(globalPos);

}

void Events::showContextMenuDesignation(const QPoint &pos)
{
    QPoint globalPos;
    if (sender()->inherits("QAbstractScrollArea"))
        globalPos = ((QAbstractScrollArea*)sender())->viewport()->mapToGlobal(pos);
    else
        globalPos = ((QWidget*)sender())->mapToGlobal(pos);

    QMenu menu;
    QAction *actionAdd = new QAction(tr("Добавить"), this);
    QAction *actionEdit = new QAction(tr("Изменить"), this);
    QAction *actionRemove = new QAction(tr("Удалить"), this);

    menu.addAction(actionAdd);
    menu.addAction(actionEdit);
    menu.addAction(actionRemove);

    connect(actionAdd, SIGNAL(triggered(bool)), this,SLOT(onAddActionTriggeredD(bool)));
    //connect(actionEdit, SIGNAL(triggered(bool)), this,SLOT(onEditActionTriggeredD(bool)));

    QAction* selectedItem = menu.exec(globalPos);
}

