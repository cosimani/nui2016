#include <QApplication>
#include "window.hpp"
#include "visor.h"

int main( int argc, char **argv )  {

    QApplication app( argc, argv );

    Window window;
    window.show();

    Visor visor;
    visor.show();

    return app.exec();
}
