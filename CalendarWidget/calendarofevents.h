#ifndef CALENDAROFEVENTS_H
#define CALENDAROFEVENTS_H

#include <QWidget>
#include <QDate>
#include <QLabel>
#include "labelbutton.h"

#define Day 7
#define Week 7

class CalendarOfEvents : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarOfEvents(QWidget *parent = 0);
    ~CalendarOfEvents();
signals:
    void dateEvent(QDate* date);

public slots:
    void showNextMonth();
    void showBackMonth();
    void onClickDate();


private:
    void showMonth(QDate* data) const;

    QDate mCurrentDate; // текущая дата
    LabelButton* mMonth[Week][Day];
    QLabel* mCurrentMonthName;
    QList<QString> mMonthName;

};

#endif // CALENDAROFEVENTS_H
