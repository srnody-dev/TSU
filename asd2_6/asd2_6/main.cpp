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

/*

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

*/

int main(int argc, char *argv[])
{
    
    /*QApplication app(argc, argv);

    HashTableWindow window;
    window.show();

    return app.exec();
*/
     HashFunc3 hashFunc;
    HashTable table(&hashFunc, 5);
    cout << "create table size 5 " << endl;
    table.print();
    cout << endl;
  
    table.insert(10, "Bently");
    table.insert(20, "BMW");
    table.insert(30, "Mecredes");
    table.print();
    cout << endl;
  
    table.insert(15, "Ferrari");
    table.insert(25, "Renault");
    table.print();
    cout << endl;
    
    table.insert(10, "Maserati");
    cout << "Update  10: Bently -> Maserati" << endl;
    table.print();
    cout << endl;
    
    cout << "contains(10): " << (table.contains(10) ? "ДА" : "НЕТ") << endl;
    cout << "contains(20): " << (table.contains(20) ? "ДА" : "НЕТ") << endl;
    cout << "contains(99): " << (table.contains(99) ? "ДА" : "НЕТ") << endl;
    cout << endl;
  
    table.remove(20);
    cout << "Delete 20" << endl;
    table.print();
    cout << endl;
    
    table.remove(15);
    cout << "Delete 15" << endl;
    table.print();
    cout << endl;
    
    cout << "Текущий размер: 5" << endl;
    table.resize(10);
    cout << "Изменен размер на 10" << endl;
    table.print();
    cout << endl;
  
    HashFunc2 hashFunc2;
    HashTable table3(&hashFunc2, 3);
    table3.insert(1, "One");
    table3.insert(2, "Two");
    cout << "Таблица 3 до swap:" << endl;
    table3.print();
    
    table.swap(table3);
    cout << "После swap(table, table3):" << endl;
    cout << "Таблица (бывшая table3):" << endl;
    table.print();
    cout << "Таблица 3 (бывшая table):" << endl;
    table3.print();
    cout << endl;
    
    cout << "swap HashFunc3 на HashFunc2" << endl;
    table.changeHashFunc(&hashFunc2);
    table.print();
    cout << endl;
}

//#include "main.moc"
