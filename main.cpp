#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QVector>

#include "../../CalendarWidget/calendarofevents.h"
#include "../../EventsWidget/events.h"
#include "../../EventsWidget/designationdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //CalendarOfEvents d;
    //DesignationDialog d;
    Events d;
    d.show();



    return a.exec();
}
