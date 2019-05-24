#include "loginform.h"
#include "mainwindow.h"

#include <QApplication>


int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );
    loginForm    w;
    // MainWindow w;
    w.show();

    return app.exec();
}
