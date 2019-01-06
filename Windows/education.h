#ifndef EDUCATION_H
#define EDUCATION_H

#include <QMainWindow>
#include "list"

namespace Ui {
class Education;
}

class Education : public QMainWindow
{
    Q_OBJECT

    QString fio, group;


public:
    explicit Education(const QString& fio, const QString& group, QWidget *parent = nullptr);
    ~Education();

private slots:
    void on_next_clicked();

private:
    Ui::Education *ui;
};

#endif // EDUCATION_H
