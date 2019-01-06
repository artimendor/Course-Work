#include "work_result.h"
#include "exceptions/dataerror.h"
#include "containers/matrix.cpp"
#include "other/codding.h"
#include <QDebug>
#include <QFileDialog>
#include "mainmenu.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "result_presenter.h"

Matrix<QString> Work_Result::table_to_matrix()
{
    int rows = this->get_table()->rowCount();
    int columns = this->get_table()->columnCount();
    auto table = this->get_table();

    Matrix<QString> mtr(rows, columns);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        {
            auto item = table->item(i, j);
            if (item)
                 mtr.set(item->text(), i, j);
            else {
                mtr.set(QString(""), i, j);
            }
        }
    return mtr;
}

bool Work_Result::save_to_txt_file(QString filepath, Matrix<QString> table)
{
    std::ofstream file(filepath.toStdString(), std::ios_base::trunc);

    int max_len = 0;
    for(auto i : table)
        if (i.length() > max_len)
            max_len = i.length();



    for(int i = 0; i < table.get_row_count(); i++)
    {
        for(int j = 0; j < table.get_column_count(); j++)
        {
            if(i!=j)
                file << std::setw(max_len) << std::left << table.get(i, j).toStdString()+" ";
            else
                file << std::setw(max_len) << std::left << QString("- ").toStdString();
        }
        file << std::endl;
    }

    file.close();
}

Work_Result::Work_Result(const QString& fio, const QString& group, QWidget* parent) :
    Instruments(parent), WorkWindow (fio, group, parent)
{

    this->get_table()->setColumnCount(2);
    this->get_table()->setRowCount(2);
    auto item = new QTableWidgetItem(QString("состояние\\код"));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    this->get_table()->setItem(0, 0, item);
}
void Work_Result::show()
{
    Instruments::show();
    WorkWindow::show();
}

void Work_Result::template_to_file()
{
    try {

        Matrix<QString> mtr = table_to_matrix();

        Codding::validate_matrix(mtr);

        QString filepath = QFileDialog::getSaveFileName(
                    static_cast<WorkWindow*>(this), "", "", "*.automat");

        if (filepath.length() == 0)
            return;

        QFile file(filepath);
        file.open(QIODevice::Truncate | QIODevice::WriteOnly);

        char size[2];

        size[0] = mtr.get_row_count();
        size[1] = mtr.get_column_count();

        file.write(QByteArray(size, 2));

        for(QString i : mtr)
        {
            char temp[1];
            temp[0] = strlen(i.toStdString().c_str());
            file.write(temp, 1);
            qDebug() << int(temp[0]);
            qDebug() << i.toStdString().c_str();
            file.write(i.toStdString().c_str(), temp[0]);


        }
        file.close();

    } catch (DataError e) {
        e.setParent(static_cast<WorkWindow*>(this));
        e.show_message();
    }

}
void Work_Result::result_to_file()
{
    try {

        Matrix<QString> mtr = table_to_matrix();

        Codding::validate_matrix(mtr);

        Matrix<QString> res = Codding::just_result(mtr);


        QString filepath = QFileDialog::getSaveFileName(
                    static_cast<WorkWindow*>(this), "", "", "*.txt");

        if(filepath.length())
            save_to_txt_file(filepath, res);

    } catch (DataError e) {
        e.setParent(static_cast<WorkWindow*>(this));
        e.show_message();
    }
}

void Work_Result::add_row()
{
    this->backup_table();
    this->get_table()->insertRow(row);
    this->row++;

}
void Work_Result::add_column()
{
    this->backup_table();
    this->get_table()->insertColumn(column);
    this->column++;
}
void Work_Result::delete_column()
{
    this->backup_table();
    if (column == 2)
        return;
    this->get_table()->removeColumn(column-1);
    column--;
}
void Work_Result::delete_row()
{
    this->backup_table();
    if(row == 2)
        return;
    this->get_table()->removeRow(row-1);
    row--;
}

void Work_Result::get_result()
{
    try {

        Matrix<QString> mtr = table_to_matrix();
        Codding::validate_matrix(mtr);
        Matrix<QString> res = Codding::just_result(mtr);

        Result_Presenter dialogue(static_cast<WorkWindow*>(this), res);

        bool save = dialogue.exec();

        if (save)
        {
            QString filepath = QFileDialog::getSaveFileName(static_cast<WorkWindow*>(this), "", "", "*.txt");
            if(filepath.length())
                save_to_txt_file(filepath, res);
        }


    } catch (DataError e) {
        e.setParent(static_cast<WorkWindow*>(this));
        e.show_message();
    }
}

void Work_Result::closeOther(bool is_it_workw)
{
    if(is_it_workw)
        Instruments::close();
    else {
        WorkWindow::close();
    }
}

void Work_Result::go_to_menu()
{
    Instruments::close();
    mainMenu * w = new mainMenu(fio, group);
    w->show();

    delete this;
}

void Work_Result::open_template()
{
    QString filepath = QFileDialog::getOpenFileName(
                static_cast<WorkWindow*>(this), "", "", "*.automat");

    if(filepath.length() == 0)
        return;

    QFile file(filepath);
    file.open(QIODevice::ReadOnly);

    char size[2];
    file.read(size, 2);
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


    auto table = this->get_table();
    table->clear();
    table->setRowCount(mtr.get_row_count());
    table->setColumnCount(mtr.get_column_count());

    for(int i = 0; i < mtr.get_row_count(); i++)
        for (int j = 0; j < mtr.get_column_count(); j++)
            table->setItem(i, j, new QTableWidgetItem(mtr.get(i, j)));

   table->item(0, 0)->setFlags(table->item(0, 0)->flags() ^ Qt::ItemIsEditable);

   this->row = table->rowCount();
   this->column = table->columnCount();
}

void Work_Result::back()
{
    this->move_back();
}
