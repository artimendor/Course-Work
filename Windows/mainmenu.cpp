#include "Windows/mainmenu.h"
#include "Windows/work_result.h"
#include "Windows/education.h"
#include "ui_mainmenu.h"
#include "doubletable.h"
#include "QFileDialog"

mainMenu::mainMenu(const QString& fio, const QString& group, QWidget *parent) :
    QMainWindow(parent), fio(fio), group(group),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
    this->setWindowTitle("главное меню");
    ui->zvarot->setText(fio + ", выберите нужный пункт меню");
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::on_education_clicked()
{
    this->close();
    Education * w = new Education(fio, group);
    w->show();
    delete this;
}

void mainMenu::on_mywork_clicked()
{
    this->close();
    Work_Result *w = new Work_Result(fio, group);
    w->show();
    delete this;
}

void mainMenu::on_control_clicked()
{

    QString filepath = QFileDialog::getOpenFileName(this, "", "", "*.automat");

    if(filepath.length())
    {
        this->close();
        DoubleTable * w = new DoubleTable(fio, group, filepath);
        w->show();
        delete this;
    }
}
