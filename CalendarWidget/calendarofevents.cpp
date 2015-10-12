#include "calendarofevents.h"

#include <QTreeView>
#include <QList>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#define DayInMonth 42



CalendarOfEvents::CalendarOfEvents(QWidget *parent) : QWidget(parent)
{
         mCurrentDate = QDate::currentDate();
         mMonthName <<tr("Январь")
                    <<tr("Февраль")
                    <<tr("Март")
                    <<tr("Апрель")
                    <<tr("Май")
                    <<tr("Июнь")
                    <<tr("Июль")
                    <<tr("Август")
                    <<tr("Сентябрь")
                    <<tr("Октябрь")
                    <<tr("Ноябрь")
                    <<tr("Декабрь");

         mCurrentMonthName = new QLabel;
         QGridLayout *gridLayout = new QGridLayout;

         QPushButton *backMonth = new QPushButton;
         backMonth->setText(tr("<<"));
         connect(backMonth,SIGNAL(clicked(bool)),SLOT(showBackMonth()));

         QPushButton *nextMonth = new QPushButton;
         nextMonth->setText(tr(">>"));
         connect(nextMonth,SIGNAL(clicked(bool)),SLOT(showNextMonth()));

         QHBoxLayout *shapka = new QHBoxLayout;
         QVBoxLayout *vertical = new QVBoxLayout;

         shapka->addWidget(backMonth);
         shapka->addWidget(mCurrentMonthName);
         shapka->addWidget(nextMonth);
         vertical->addLayout(shapka);


         for (int i = 0; i<Week; i++)
              for (int j = 0; j<Day; j++)
              {
                 mMonth[i][j] = new LabelButton;
                 if (i >=1)
                   connect(mMonth[i][j],SIGNAL(clicked()),SLOT(onClickDate()));
                 gridLayout->addWidget(mMonth[i][j],i,j);
              }
         mMonth[0][0]->setToolTip("jggfgf");
         vertical->addLayout(gridLayout);
         QList<QString> list;
         list << tr("П");
         list << tr("В");
         list << tr("С");
         list << tr("Ч");
         list << tr("П");
         list << tr("С");
         list << tr("В");
         for (int i = 0; i<Day; i++)
            mMonth[0][i]->setText(list[i]);

         showMonth(&mCurrentDate);
         this->setLayout(vertical);
}

void CalendarOfEvents::showMonth(QDate* data) const
{
    QDate dat(data->year(),data->month(),1);
    mCurrentMonthName->setText(QString(mMonthName[dat.month()-1]+tr("  %0 г.")).arg(dat.year()));
    int t = dat.dayOfWeek()-1;
    int m = 0;
    QList<QString> Month;
    for (int i = 0; i<DayInMonth; i++)
    {
        if (i<t || i>=t+dat.daysInMonth())
            Month<<"";
        else
            if (i-t>=dat.daysInMonth())
            {
                m++;
                Month<< QString("%0").arg(m);
            }
            else
                Month<< QString("%0").arg(i+1-t);
    }
    t=0;
    for (int i = 1; i<Week; i++)
         for (int j = 0; j<Day; j++)
         {
             mMonth[i][j]->setText(Month[t]);
             t++;
         }
}

CalendarOfEvents::~CalendarOfEvents()
{

}

void CalendarOfEvents::showBackMonth()
{
  if (mCurrentDate.month() == 1)
      mCurrentDate.setDate(mCurrentDate.year()-1,12,1);
  else
      mCurrentDate.setDate(mCurrentDate.year(),mCurrentDate.month()-1,1);
  showMonth(&mCurrentDate);
}

void CalendarOfEvents::showNextMonth()
{
  if (mCurrentDate.month() == 12)
      mCurrentDate.setDate(mCurrentDate.year()+1,1,1);
  else
      mCurrentDate.setDate(mCurrentDate.year(),mCurrentDate.month()+1,1);
  showMonth(&mCurrentDate);
}


void CalendarOfEvents::onClickDate()
{
    LabelButton *labelActive = qobject_cast<LabelButton*>(sender());
    if (labelActive && !labelActive->text().isEmpty())
    {
        QDate *date = new QDate;
        date->setDate(mCurrentDate.year(),mCurrentDate.month()+1,labelActive->text().toInt());
        dateEvent(date);
    }

}


