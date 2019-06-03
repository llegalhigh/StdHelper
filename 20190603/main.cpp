#include "Login.h"
#include "mainwindow.h"

#include <QApplication>

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    Login l;
    l.show();

    return app.exec();
}
