//
//  main.cpp
//  asd2_2
//
//  Created by srnody on 24.02.2026.
//

#include <iostream>
/*
#include <QApplication>
#include <QWidget>
#include <QPainter>
*/
#include "BinaryTree.hpp"

/*
class BinaryTreeWidget : public QWidget {
private:
    BinaryTree tree;
    const int NODE_RADIUS = 25;
    const int NODE_DIAMETER = 50;

    void drawNode(QPainter& painter, TreeNode* node, int x, int y, int offset) {
        if (!node) return;

        painter.setBrush(QColor(255, 200, 100));
        painter.setPen(Qt::black);
        painter.drawEllipse(QPoint(x, y),NODE_RADIUS, NODE_RADIUS);

        painter.drawText(QRect(x - NODE_RADIUS, y - NODE_RADIUS, NODE_DIAMETER, NODE_DIAMETER),Qt::AlignCenter,QString::number(node->getKey()));

        if (node->getLeft()) {
            int childX = x - offset;
            int childY = y + 100;
            painter.drawLine(x, y + NODE_RADIUS, childX, childY - NODE_RADIUS);
            drawNode(painter, node->getLeft(), childX, childY, offset/2);
        }

        if (node->getRight()) {
            int childX = x + offset;
            int childY = y + 100;
            painter.drawLine(x, y + NODE_RADIUS, childX, childY - NODE_RADIUS);
            drawNode(painter, node->getRight(), childX, childY, offset/2);
        }
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        if (!tree.isEmpty()) {
            drawNode(painter, tree.getRoot(), width()/2, 50, width()/4);
        }
    }

public:
    BinaryTreeWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setWindowTitle("Бинарное дерево");
        resize(800, 600);

        tree.insert(799);
        tree.insert(77);
        tree.insert(777);
        tree.insert(97);
        tree.insert(197);
        tree.insert(15);
        tree.insert(999);

    }
};

*/

int main(int argc, char *argv[]) {

    /*
    QApplication app(argc, argv);
    
    BinaryTreeWidget window;
    window.show();

    return app.exec();
     */
    
    BinaryTree tree;

    tree.insert(799);
    tree.insert(77);
    tree.insert(777);
    tree.insert(97);
    tree.insert(197);
    
    std::cout << "Дерево:\n";
        tree.print();
    
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;
    
    int key = 97;
    if (tree.find(key))
        std::cout << "Найден узел " << key << std::endl;
    else
        std::cout << "Узел " << key << " не найден" << std::endl;
    
    std::vector<int> keys = tree.getAllKeys();
    std::cout << "\nВсе ключи по возрастанию: ";
    for (int key : keys) {
        std::cout << key << " ";
    }
    std::cout << std::endl;
    
    int key2 = 777;
    tree.remove(key2);
    std::cout << "\nПосле удаления узла "<< key2 << ":\n";
    tree.print();
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;
    std::cout << "\nВысота дерева: " << tree.getHeight() << std::endl;
    
    std::cout << "Минимальный ключ: " << tree.getMinKey() << std::endl;
    std::cout << "Максимальный ключ: " << tree.getMaxKey() << std::endl;
    
    BinaryTree tree2=tree;
    std::cout << "\nКопия дерева:\n";
    tree2.print();
    
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;
}

