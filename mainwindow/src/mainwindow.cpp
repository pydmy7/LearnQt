#include "mainwindow/mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringListModel>
#include <qabstractitemmodel.h>
#include <qcheckbox.h>
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init() {
    stringlist_ << "北京" << "上海" << "广州" << "深圳";

    stringlistmodel_ = new QStringListModel{this};
    stringlistmodel_->setStringList(stringlist_);
    
    ui->listView->setModel(stringlistmodel_);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    connect(ui->btnIniList, &QPushButton::clicked, this, [this]() {
        stringlistmodel_->setStringList(stringlist_);
    });
    connect(ui->btnListClear, &QPushButton::clicked, this, [this]() {
        stringlistmodel_->removeRows(0, stringlistmodel_->rowCount());
    });
    connect(ui->chkEditable, &QCheckBox::clicked, this, [this](bool checked) {
        if (checked) {
            ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
        } else {
            ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    });
    connect(ui->btnListAppend, &QPushButton::clicked, this, [this]() {
        stringlistmodel_->insertRow(stringlistmodel_->rowCount());
        QModelIndex modelindex = stringlistmodel_->index(stringlistmodel_->rowCount() - 1);
        stringlistmodel_->setData(modelindex, "Neo Item");
        ui->listView->setCurrentIndex(modelindex);
    });
    connect(ui->btnListInsert, &QPushButton::clicked, this, [this]() {
        QModelIndex modelindex = ui->listView->currentIndex();
        stringlistmodel_->insertRow(modelindex.row());
        stringlistmodel_->setData(modelindex, "Neo Item");
        ui->listView->setCurrentIndex(modelindex);
    });
    connect(ui->btnListMoveUp, &QPushButton::clicked, this, [this]() {
        int currentrow = ui->listView->currentIndex().row();
        stringlistmodel_->moveRow(QModelIndex{}, currentrow,
            QModelIndex{}, currentrow - 1);
    });
    connect(ui->btnListMoveDown, &QPushButton::clicked, this, [this]() {
        int currentrow = ui->listView->currentIndex().row();
        stringlistmodel_->moveRow(QModelIndex{}, currentrow,
            QModelIndex{}, currentrow + 2);
    });
}
