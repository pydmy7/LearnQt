#pragma once

#include <QObject>
#include <QWidget>

QT_BEGIN_NAMESPACE

namespace Ui {
class Widget;
}

QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::Widget* ui;

    void myDraw();
};
