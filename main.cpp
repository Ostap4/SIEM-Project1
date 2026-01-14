


#include "hellogui.h"
#include <QtWidgets/QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QThread>




int main(int argc, char* argv[])
{
    QApplication app(argc, argv);   

    hellogui window;
    window.show();

    return app.exec();
    
}


