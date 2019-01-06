#ifndef WORKWINDOW_H
#define WORKWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <list>
#include "containers/matrix.h"

namespace Ui {
class WorkWindow;
}

class WorkWindow : public QWidget
{
    Q_OBJECT

    std::list<Matrix<QString>> saved_sost;
public:
    explicit WorkWindow(const QString& fio, const QString& group, QWidget *parent = nullptr);
    ~WorkWindow() override;

    int row, column;

protected:

   void backup_table();

   QTableWidget* get_table() const;

   void closeEvent(QCloseEvent *event) override;
   virtual void closeOther(bool is_it_workw) = 0;

   QString fio;
   QString group;

   void move_back();
private slots:

   void on_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::WorkWindow *ui;
};

#endif // WORKWINDOW_H
