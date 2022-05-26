#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QFont base_font("Segoe UI Variable", 11);
    QApplication::setFont(base_font);

    MainWindow w;
    w.show();
    return a.exec();
}
