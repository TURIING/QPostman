#include <QApplication>
#include <QPushButton>

#include "qpostman.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QPostman postman;
    postman.show();

    return QApplication::exec();
}
