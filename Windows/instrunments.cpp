#include "instrunments.h"
#include "ui_instrunments.h"

Instruments::Instruments(QWidget *parent) :
    QMainWindow(parent, Qt::Tool),
    ui(new Ui::instrunments)
{
    ui->setupUi(this);
    this->setFixedSize(238, 426);
    this->move(0, 0);
    this->setWindowTitle("инструменты");

}

Instruments::~Instruments()
{
    delete ui;
}

void Instruments::on_pushButton_clicked()
{
    this->add_row();
}

void Instruments::on_pushButton_2_clicked()
{
    this->add_column();
}

void Instruments::on_pushButton_3_clicked()
{
    this->delete_row();
}

void Instruments::on_pushButton_4_clicked()
{
    this->delete_column();
}

void Instruments::on_pushButton_5_clicked()
{
    this->template_to_file();
}

void Instruments::on_pushButton_6_clicked()
{
    this->get_result();
}

void Instruments::on_pushButton_7_clicked()
{
    this->result_to_file();
}

void Instruments::on_pushButton_9_clicked()
{
    this->go_to_menu();
}

void Instruments::on_pushButton_8_clicked()
{
    this->open_template();
}

void Instruments::closeEvent(QCloseEvent *event)
{
    this->closeOther(false);
    this->close();
    //event->accept();
}

void Instruments::on_pushButton_10_clicked()
{
   this->back();
}
