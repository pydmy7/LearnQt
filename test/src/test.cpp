#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDragMoveEvent>
#include <QDropEvent>

class CustomStandardItemModel : public QStandardItemModel {
public:
    using QStandardItemModel::QStandardItemModel;
};

class CustomTreeView : public QTreeView {
public:
    using QTreeView::QTreeView;

protected:
    void startDrag(Qt::DropActions supportedActions) override {
        this->source_index = currentIndex();
        QTreeView::startDrag(supportedActions);
    }

    void dragMoveEvent(QDragMoveEvent *event) override {
        QModelIndex target_index = indexAt(event->pos());
        // here : this->source_index.parent() == target_index.parent()
        if (this->source_index.isValid() && target_index.isValid() && this->source_index.parent() == target_index.parent()) {
            QTreeView::dragMoveEvent(event);
        } else {
            event->ignore();
        }
    }

    void dropEvent(QDropEvent *event) override {
        QModelIndex target_index = indexAt(event->pos());
        // here : this->source_index.parent() == target_index.parent()
        if (this->source_index.isValid() && target_index.isValid() && this->source_index.parent() == target_index.parent()) {
            QTreeView::dropEvent(event);
        } else {
            event->ignore();
        }
    }

    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override {
        QTreeView::selectionChanged(selected, deselected);

        QModelIndexList indexes = this->selectionModel()->selectedIndexes();
        if (indexes.isEmpty()) {
            return;
        }

        QModelIndex parent_index = indexes.first().parent();
        for (const QModelIndex &index : indexes) {
            if (index.parent() != parent_index) {
                this->selectionModel()->select(index, QItemSelectionModel::Deselect);
            }
        }
    }

private:
    QModelIndex source_index;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CustomStandardItemModel model;
    QStandardItem* rootitem = model.invisibleRootItem();
    for (int i = 0; i < 5; ++i) {
        QStandardItem *item = new QStandardItem(QString("tree-%0").arg(i));
        rootitem->appendRow(item);
        for (int j = 0; j < 3; ++j) {
            QStandardItem *childItem = new QStandardItem(QString("leaf-%0").arg(j));
            item->appendRow(childItem);
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
