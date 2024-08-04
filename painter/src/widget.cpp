#include "painter/widget.hpp"
#include "ui_widget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <qpoint.h>
#include <qvariant.h>

Widget::Widget(QWidget* parent)
    : QWidget{parent}
    , ui{new Ui::Widget}
{
    ui->setupUi(this);
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent* event) {
    Widget::myDraw();
    event->accept();
}

void Widget::myDraw() {
    const int width = QWidget::width();
    const int height = QWidget::height();

    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);

    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);

    QPainter painter{this};
    painter.setPen(pen);
    painter.setBrush(brush);

    auto side = std::min(width, height);
    QRect rect{(width - side) / 2, (height - side) / 2, side, side};
    painter.drawRect(rect);
    painter.setViewport(rect);
    painter.setWindow(-100, -100, 200, 200);

    for (int i = 0; i < 36; ++i) {
        painter.drawEllipse(50, 0, 50, 50);
        painter.rotate(10);
    }
}
