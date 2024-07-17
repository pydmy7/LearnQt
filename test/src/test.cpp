#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QDebug>

class CustomStandardItemModel : public QStandardItemModel {
public:
    using QStandardItemModel::QStandardItemModel;
};

class CustomTreeView : public QTreeView {
public:
    using QTreeView::QTreeView;

protected:
    void startDrag(Qt::DropActions supportedActions) override {
        this->sourceindex_ = QTreeView::currentIndex();
        QTreeView::startDrag(supportedActions);
    }

    void dragMoveEvent(QDragMoveEvent *event) override {
        QModelIndex targetindex = indexAt(event->pos());
        if (this->sourceindex_.isValid() && targetindex.isValid() && this->canDragDrop(this->sourceindex_, targetindex)) {
            QTreeView::dragMoveEvent(event);
        } else {
            event->ignore();
        }
    }

    void dropEvent(QDropEvent *event) override {
        QModelIndex targetindex = indexAt(event->pos());
        if (this->sourceindex_.isValid() && targetindex.isValid() && this->canDragDrop(this->sourceindex_, targetindex)) {
            QTreeView::dropEvent(event);
        } else {
            event->ignore();
        }
    }

    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override {
        QTreeView::selectionChanged(selected, deselected);

        QModelIndexList indexes = QTreeView::selectionModel()->selectedIndexes();
        if (indexes.isEmpty()) {
            return;
        }

        for (QModelIndex aimindex = indexes.first(); const QModelIndex &index : indexes) {
            if (!this->canMultiSelect(aimindex, index)) {
                QTreeView::selectionModel()->select(index, QItemSelectionModel::Deselect);
            }
        }
    }

private:
    QModelIndex sourceindex_;

    QModelIndex getRootModelIndex(const QModelIndex& a) {
        QModelIndex root {a};
        while (root.parent().isValid()) {
            root = root.parent();
        }
        return root;
    }

    bool canDragDrop(const QModelIndex& a, const QModelIndex& b) {
        return getRootModelIndex(a) == getRootModelIndex(b);
    }
    bool canMultiSelect(const QModelIndex& leader, const QModelIndex& other) {
        return getRootModelIndex(leader) == getRootModelIndex(other);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CustomStandardItemModel model;
    QStandardItem* rootitem {model.invisibleRootItem()};
    for (int i = 0; i < 5; ++i) {
        QStandardItem *item1 {new QStandardItem{QString{"tree-%0"}.arg(i)}};
        rootitem->appendRow(item1);
        for (int j = 0; j < 3; ++j) {
            QStandardItem *item2 {new QStandardItem{QString{"node-%0"}.arg(j)}};
            item1->appendRow(item2);
            for (int k = 0; k < 3; ++k) {
                QStandardItem *item3 {new QStandardItem{QString{"leaf-%0"}.arg(k)}};
                item2->appendRow(item3);
            }
        }
    }

    CustomTreeView treeView;
    treeView.setDragEnabled(true);
    treeView.setAcceptDrops(true);
    treeView.setDropIndicatorShown(true);
    treeView.setDragDropMode(QAbstractItemView::InternalMove);
    treeView.setSelectionMode(QAbstractItemView::ExtendedSelection);
    treeView.setSelectionBehavior(QAbstractItemView::SelectItems);
    treeView.setModel(&model);
    treeView.show();

    return app.exec();
}
