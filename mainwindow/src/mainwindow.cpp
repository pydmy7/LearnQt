#include "mainwindow/mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::init() {
    this->setCentralWidget(ui->splitter);

    model_ = new QStandardItemModel{2, 6, this};
    select_ = new QItemSelectionModel{model_, this};
    
    ui->tableView->setModel(model_);
    ui->tableView->setSelectionModel(select_);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    connect(select_, &QItemSelectionModel::currentChanged, this, [this](const QModelIndex &current, [[maybe_unused]] const QModelIndex &previous) {
        qDebug() << "current.row() ==" << current.row();
        qDebug() << "current.column() ==" << current.column();
        qDebug() << "test ==" << model_->itemFromIndex(current)->text();
    });
}
