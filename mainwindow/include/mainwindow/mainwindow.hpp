#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

class QStandardItemModel;
class QItemSelectionModel;

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStandardItemModel* model_;
    QItemSelectionModel* select_;

    void init();
    void initModelData(const QVector<QString>& list);
};
#endif  // MAINWINDOW_H
