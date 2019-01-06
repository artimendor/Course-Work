#include "windows/mainwindow.h"
#include "ui_mainwindow.h"
#include "exceptions/inputexception.h"
#include <QMessageBox>
#include <regex>
#include "mainmenu.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("вход");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_button_clicked()
{
    try {
        if(ui->fio->text().length() == 0)
            throw InputException("Поле ФИО пустое! ", this);
        if(ui->group->text().length() == 0)
            throw InputException("Поле группа пустое!", this);


        if(ui->group->text().length() != 6)
            throw InputException("Не верно введена группа", this);
        for(QChar i : ui->group->text())
        {
            if(i < '0' || i > '9')
                throw InputException("Не верно ведена группа", this);
        }

        mainMenu *menu = new mainMenu(
                    ui->fio->text(),
                    ui->group->text()
                    );
        menu->show();

        this->close();
    } catch (ProjectBaseException &e) {
        e.show_message();
    }
}
