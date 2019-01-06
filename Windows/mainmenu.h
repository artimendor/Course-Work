#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>

namespace Ui {
class mainMenu;
}

class mainMenu : public QMainWindow
{
    Q_OBJECT
    QString fio;
    QString group;
public:
    explicit mainMenu(const QString& fio, const QString& group, QWidget *parent = nullptr);

    ~mainMenu();

private slots:
    void on_education_clicked();

    void on_mywork_clicked();

    void on_control_clicked();

private:
    Ui::mainMenu *ui;
};

#endif // MAINMENU_H
