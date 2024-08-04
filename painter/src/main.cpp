#include <QApplication>

#include "painter/widget.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Widget widget;
    widget.show();

    return a.exec();
}
