#include "mainwindow.h"
#include <QLocale>
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setFixedSize(QSize(576, 524));
    // Load the application style
    QFile styleFile( ":/stylesheets/main.qss" );
    styleFile.open( QFile::ReadOnly );
    // Apply the stylesheet
    a.setStyleSheet(QString(styleFile.readAll()));

    w.show();
    return a.exec();
}
