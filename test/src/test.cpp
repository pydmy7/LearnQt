#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(250, 150);
    window.setWindowTitle("Qt5 Test");

    QLabel hello("Hello, World!", &window);
    hello.move(80, 60);

    window.show();

    return app.exec();
}
