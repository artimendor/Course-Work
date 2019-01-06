#include "doubletable.h"
#include "ui_doubletable.h"
#include "containers/matrix.h"
#include "QFile"
#include "other/codding.h"
#include "qdebug.h"
#include "Windows/mainmenu.h"

#include <QMessageBox>

DoubleTable::DoubleTable(QString fio, QString group, QString filepath, QWidget *parent) :
    QMainWindow(parent), fio(fio), groupe(group),
    ui(new Ui::DoubleTable)
{

    this->number_of_test = 0;
    ui->setupUi(this);
    this->setWindowTitle("Проверка знаний");

    QFile file(filepath);
    file.open(QIODevice::ReadOnly);

    char size[2];
    file.read(size, 2); // счітываем шаблон
    Matrix<QString> mtr(size[0], size[1]);

    for(QString& i : mtr)
    {
        char temp[1];
        file.read(temp, 1);
        char *c_str = new char[temp[0]];
        file.read(c_str, temp[0]);
        QByteArray arr(c_str, temp[0]);

        i = arr;


        delete[] c_str;
    }
    file.close();

    this->result = new Matrix<QString>(Codding::just_result(mtr));
    qDebug() << result->get_row_count();

    auto table = this->ui->data;
    table->clear();
    table->setRowCount(mtr.get_row_count());
    table->setColumnCount(mtr.get_column_count());

    for(int i = 0; i < mtr.get_row_count(); i++) //записываем шаблон в таблицу
        for (int j = 0; j < mtr.get_column_count(); j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem(mtr.get(i, j));
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);

            table->setItem(i, j, item);
        }

    table = this->ui->workField;
    table->setRowCount(mtr.get_row_count());
    table->setColumnCount(mtr.get_row_count());
    for(int i = 1; i < mtr.get_row_count(); i++) //делаем шапку для ввода ответов
    {

        QTableWidgetItem * item1 = new QTableWidgetItem(mtr.get(i, 0));
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);

        QTableWidgetItem * item2 = new QTableWidgetItem(mtr.get(i, 0));
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);

        table->setItem(i, 0, item1);
        table->setItem(0, i, item2);
    }


    for(int  i = 0; i < table->rowCount(); i++)
    {
        auto item = new QTableWidgetItem("-");
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        table->setItem(i, i, item);
    }

    this->saved_tables.clear();
}

DoubleTable::~DoubleTable()
{
    delete ui;
    delete result;
}

void DoubleTable::on_check_clicked()
{
    auto table = this->ui->workField;
    //Matrix<QString> mtr(result.get_row_count(), result.get_column_count());

    for(int i = 1; i < table->rowCount(); i++)
        for(int j = 1; j < table->columnCount(); j++)
        {
            if(i != j)
            {
                auto item = table->item(i, j);
                if(item)
                    if(item->text() != result->get(i,j))
                    {
                        // студент ошибься
                        this->number_of_test++;
                        QMessageBox::warning(this, "Ошибка", "Вы допустили ошибку, перепроверьте поля");
                        return;
                    }
                    else;
                else {
                    //ошибка студента
                    this->number_of_test++;
                    QMessageBox::warning(this, "Ошибка", "Вы допустили ошибку, перепроверьте поля");
                    return;
                }
            }
        }
    QMessageBox::information(this, "Поздравляю",
                             "Не закрывайте это окно, пока не покажите преподавателю!\n" +
                             fio + "\n" + groupe + "\n" +
                             "Неудачных проверок: " + QString::number(this->number_of_test));
    this->close();
    mainMenu * w = new mainMenu(fio, groupe);
    w->show();
    delete this;
}

//void DoubleTable::on_workField_cellChanged(int row, int column)
//{
   // qDebug() << "changed" << row << column << this->ui->workField->item(row,column)->text();
    //this->backup_table();
//}

void DoubleTable::move_back()
{
    if(this->saved_tables.size() == 0)
        return;

    auto mtr = *saved_tables.begin();
    saved_tables.pop_front();

    for(int i = 0; i < mtr.get_row_count(); i++)
        for(int j = 0; j < mtr.get_column_count(); j++)
            if(i != j)
            {
                this->ui->workField->setItem(i + 1, j + 1, new QTableWidgetItem(mtr.get(i, j)));
            }

}
void DoubleTable::backup_table()
{
    auto table = this->ui->workField;
    Matrix<QString> mtr(table->rowCount() - 1, table->columnCount() - 1);

    for(int i = 0; i < mtr.get_row_count(); i++) //сохраняем все в матрицу
        for(int j = 0; j < mtr.get_column_count(); j++)
        {
            auto item = table->item(i + 1, j + 1);
            if(item)
                mtr.set(item->text(), i, j);
            else
                mtr.set("", i, j);
        }

    if(this->saved_tables.size() > 20)
        this->saved_tables.pop_back();
    this->saved_tables.push_front(mtr);

}

void DoubleTable::on_back_clicked()
{

    this->move_back();
}

void DoubleTable::on_workField_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(this->saved_tables.size() == 0)
    {
        this->backup_table();
        return;
    }

    auto mtr = *saved_tables.begin();

    for(int i = 0; i < mtr.get_row_count(); i++)
        for(int j = 0; j < mtr.get_column_count(); j++)
            if(i != j)
            {
                auto item = this->ui->workField->item(i + 1, j + 1);

                if(item)
                    if(this->ui->workField->item(i + 1, j + 1)->text() != mtr.get(i, j))
                    {
                        this->backup_table();
                        return;
                    }
                    else;
                else
                    if(mtr.get(i, j) != "")
                    {
                        this->backup_table();
                        return;
                    }

            }

}
