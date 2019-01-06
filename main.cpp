#include "Windows/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    a.setApplicationDisplayName("кодирование автомата");
    w.show();



    return a.exec();
}
