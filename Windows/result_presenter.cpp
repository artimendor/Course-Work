#include "result_presenter.h"
#include "ui_result_presenter.h"

Result_Presenter::Result_Presenter(QWidget *parent, Matrix<QString>& mtr) :
    QDialog(parent), mtr(mtr),
    ui(new Ui::Result_Presenter)
{
    ui->setupUi(this);

    this->setWindowTitle("результат");
    QTableWidgetItem* item;

    ui->tableWidget->setRowCount(mtr.get_row_count());
    ui->tableWidget->setColumnCount(mtr.get_column_count());

    for(int i = 0; i < mtr.get_row_count(); i++)
        for(int j = 0; j < mtr.get_column_count(); j++)
        {
            if(i == j)
                item = new QTableWidgetItem("-");
            else
                item = new QTableWidgetItem(mtr.get(i, j));
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i, j, item);
        }
}

Result_Presenter::~Result_Presenter()
{
    delete ui;
}
