#include <QApplication>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QFileSystemModel model;
    model.setRootPath(QDir::currentPath());

    QTreeView tree;
    tree.setModel(&model);
    tree.setRootIndex(model.index(QDir::currentPath()));
    tree.show();

    QListView list;
    list.setModel(&model);
    list.setRootIndex(model.index(QDir::currentPath()));
    list.show();

    return app.exec();
}

