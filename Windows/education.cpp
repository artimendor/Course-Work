#include "education.h"
#include "ui_education.h"
#include "mainmenu.h"
Education::Education(const QString& fio, const QString& group, QWidget *parent) :
    QMainWindow(parent), fio(fio), group(group),
    ui(new Ui::Education)
{
    ui->setupUi(this);
    this->setWindowTitle("обучение");
}

Education::~Education()
{
    delete ui;
}

void Education::on_next_clicked()
{
    this->close();
    mainMenu *w = new mainMenu(fio, group);
    w->show();
    delete this;
}
