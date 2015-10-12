#ifndef LABELBUTTON
#define LABELBUTTON
#include <QLabel>
#include <QMouseEvent>

class LabelButton :public QLabel
{
    Q_OBJECT
public:
    explicit LabelButton(QWidget *parent = 0) : QLabel(parent){};

signals:
    void clicked();

private:
    void mouseReleaseEvent(QMouseEvent *mouseEvent)
    {
    if (mouseEvent->button() == Qt::LeftButton)
        emit clicked();
    }
};

#endif // LABELBUTTON

