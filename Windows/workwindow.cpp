#include "containers/matrix.cpp"
#include "Windows/workwindow.h"
#include "ui_workwindow.h"
#include "exceptions/dataerror.h"
#include "other/codding.h"
#include "QString"
#include "QDebug"
#include "QShortcut"
#include <ctime>

WorkWindow::WorkWindow(const QString& fio, const QString& group, QWidget *parent) :
    QWidget(parent), fio(fio), group(group),
    ui(new Ui::WorkWindow), row(2), column(2)
{
    ui->setupUi(this);
    this->setWindowTitle("таблица");
    //QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    //static_cast<QObject*>(this)->connect(shortcut, SIGNAL(activated()), this, SLOT(move_back()));

    this->move_back();

    this->saved_sost.clear();
}

WorkWindow::~WorkWindow()
{
    delete ui;
}

QTableWidget* WorkWindow::get_table() const
{
    return this->ui->table;
}

void WorkWindow::closeEvent(QCloseEvent *event)
{
    this->closeOther(true);
    this->close();
}

void WorkWindow::backup_table()
{
   Matrix<QString> to_save(this->ui->table->rowCount(), this->ui->table->columnCount());

   for(int i = 0; i < to_save.get_row_count(); i++)
       for(int j = 0; j < to_save.get_column_count(); j++)
       {
            if (ui->table->item(i, j))
            {
                to_save.set(ui->table->item(i, j)->text(), i, j);
            }
            else {
                to_save.set("", i, j);
            }
       }
   this->saved_sost.push_front(to_save);
}

void WorkWindow::move_back()
{

     // убираем текущую позицию
    auto it = this->saved_sost.begin();
    if(it==this->saved_sost.end())
        return;
    auto mtr = *it; //получаем таблицу, которую нужно развернуть
    this->saved_sost.pop_front();

    auto table = this->ui->table;

    table->setRowCount(mtr.get_row_count());
    table->setColumnCount(mtr.get_column_count());
    this->row=mtr.get_row_count();
    this->column=mtr.get_column_count();

    for (int i = 0; i < table->rowCount(); i++) //копируем данные из
        for(int j = 0; j < table->columnCount(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(mtr.get(i,j));
            table->setItem(i, j, item);
        }

}

void WorkWindow::on_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    auto table = this->ui->table;

    if(!this->saved_sost.size())
    {
        this->backup_table();
        return;
    }
    Matrix<QString> temp = *this->saved_sost.begin();

    if (table->rowCount() != temp.get_row_count() || table->columnCount() != temp.get_column_count())
    {
        this->backup_table();
        return;
    }
    for (int i = 0; i < table->rowCount(); i++) //проверяем, ізменілі лі мы что-то в табліце
        for(int j = 0; j < table->columnCount(); j++)
        {
            // если хоть одна клетка отличается, сохраняем таблицу
            if(!table->item(i,j))
            {
                if(temp.get(i,j) != "")
                {
                    backup_table();
                    return;
                }
            }
            else {
                if(table->item(i,j)->text() != temp.get(i, j))
                {
                    backup_table();
                    return;
                }

            }
        }
}
