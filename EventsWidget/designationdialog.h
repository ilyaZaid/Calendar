#ifndef DESIGNATIONDIALOG_H
#define DESIGNATIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

class DesignationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DesignationDialog(QWidget *parent = 0);
    QColor colorValue() const;
    QString nameType() const;

signals:

public slots:

    void showColorDialog(bool);
    void endEditing(const QString & text);

private:
QLabel *mColorView;
QLineEdit mEdit;
QColor mColor;
QString mNameType;
};

#endif // DESIGNATIONDIALOG_H
