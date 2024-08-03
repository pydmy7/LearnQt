#include "mainwindow/mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QDebug>
#include <QFileDialog>
#include <qbrush.h>
#include <qnamespace.h>
#include <qregion.h>
#include <qregularexpression.h>
#include <qstandarditemmodel.h>

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
        qDebug() << "text ==" << model_->itemFromIndex(current)->text();
    });
    connect(ui->actOpen, &QAction::triggered, this, [this]() {
        QString filename = QFileDialog::getOpenFileName(this,
            "open a file",QApplication::applicationDirPath(), "data file(*.txt);;all file(*.*)");
        if (filename.isEmpty()) {
            return;
        }
        QFile file{filename};
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return;
        }
        ui->plainTextEdit->clear();
        QVector<QString> content;
        QTextStream textstream(&file);
        while (!textstream.atEnd()) {
            QString str = textstream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            content.push_back(str);
        }
        // file.close();  // RAII

        ui->actAppend->setEnabled(true);
        ui->actInsert->setEnabled(true);
        ui->actSave->setEnabled(true);
        ui->actDelete->setEnabled(true);

        initModelData(content);
    });
    connect(ui->actModelData, &QAction::triggered, this, [this]() {
        ui->plainTextEdit->clear();
        QString str;
        for (int j = 0; j < model_->columnCount(); ++j) {
            QStandardItem* item{model_->horizontalHeaderItem(j)};
            str += item->text() + "\t";
        }
        ui->plainTextEdit->appendPlainText(str);

        for (int i = 0; i < model_->rowCount(); ++i) {
            QString str;
            for (int j = 0; j < model_->columnCount() - 1; ++j) {
                str += model_->item(i, j)->text() + "\t";
            }
            ui->plainTextEdit->appendPlainText(str);
        }
    });
}

void MainWindow::initModelData(const QVector<QString>& list) {
    model_->setRowCount(list.size() - 1);

    model_->setHorizontalHeaderLabels(
        list.at(0).split(QRegularExpression(R"(\s+)"),Qt::SkipEmptyParts));

    for (int i = 1; i < list.size(); ++i) {
        QList<QString> strs = list.at(i).split(
            QRegularExpression(R"(\s+)"), Qt::SkipEmptyParts);
        for (int j = 0; j < strs.size() - 1; ++j) {
            QStandardItem* item {new QStandardItem{strs.at(j)}};
            model_->setItem(i - 1, j, item);
        }
        QStandardItem* item {new QStandardItem{strs.back()}};
        item->setCheckable(true);
        item->setBackground(QBrush{Qt::yellow});
        model_->setItem(i - 1, strs.size() - 1, item);
    }
}
