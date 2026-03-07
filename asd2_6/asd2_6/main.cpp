//
//  main.cpp
//  asd2_6
//
//  Created by srnody on 19.02.2026.
//

#include <QApplication>
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

#include "hashtable.h"

class HashTableWindow : public QWidget {
    Q_OBJECT

private:
    QTableWidget* tableWidget;
    HashFunc3 hashFunc;
    HashTable table;

public:
    explicit HashTableWindow(QWidget* parent = nullptr)
        : QWidget(parent),
        table(&hashFunc, 10)
    {
        setWindowTitle("Hash Table");
        resize(700, 500);

        QVBoxLayout* layout = new QVBoxLayout(this);

        tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(2);
        tableWidget->setHorizontalHeaderLabels({"Bucket", "Key/Value"});
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

        layout->addWidget(tableWidget);

        table.insert(197, "Bentley");
        table.insert(178, "Jaguar");
        table.insert(77, "BMW");
        table.insert(777, "Mercedes");
        table.insert(78, "Nissan");
        table.insert(99, "Audi");
        table.insert(70, "Toyota");
        table.insert(78, "Tesla");

        updateDisplay();
    }

private:
    void updateDisplay()
    {
        int size = table.getSize();
        tableWidget->setRowCount(size);

        for (int i = 0; i < size; i++) {
            QTableWidgetItem* bucketItem = new QTableWidgetItem(QString::number(i));
            bucketItem->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(i, 0, bucketItem);

            QString values = QString::fromStdString(table.getBucketItems(i));

            QTableWidgetItem* valueItem =
                new QTableWidgetItem(values);
            tableWidget->setItem(i, 1, valueItem);
        }

        tableWidget->resizeColumnsToContents();
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    HashTableWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"
