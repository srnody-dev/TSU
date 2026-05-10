//
//  main.cpp
//  asd2_3
//
//  Created by srnody on 23.02.2026.
//

#include "BinarySearchTree.hpp"
#include <iostream>
/*
 #include <QApplication>
 #include <QWidget>
 #include <QPainter>
 */

/*
class BinaryTreeWidget : public QWidget {
private:

    BinaryTree *tree = new BinarySearchTree();
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

        if (!tree->isEmpty()) {
            drawNode(painter, tree->getRoot(), width()/2, 50, width()/4);
        }
    }

public:
    BinaryTreeWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setWindowTitle("Бинарное дерево поиска");
        resize(800, 600);

        

        tree->insert(6);
        tree->insert(1);
        tree->insert(3);
        tree->insert(11);
        tree->insert(5);
        tree->insert(4);
        tree->insert(8);
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

    BinaryTree *tree = new BinarySearchTree();

    tree->insert(6);
    tree->insert(1);
    tree->insert(3);
    tree->insert(11);
    tree->insert(5);
    tree->insert(4);
    tree->insert(8);

    std::cout << "Дерево:\n";
    tree->print();

    std::vector<int> keys = tree->getAllKeys();

    std::cout << "\nВсе ключи: ";
    for (int key : keys) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    std::cout << "Минимальный ключ: " << tree->getMinKey() << std::endl;
    std::cout << "Максимальный ключ: " << tree->getMaxKey() << std::endl;

    BinarySearchTree *bst = dynamic_cast<BinarySearchTree *>(tree);
    std::cout << "\nОбход через итератор (LNR): ";
    for (int key : *bst) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    int key = 97;
    if (tree->find(key))
        std::cout << "Найден узел " << key << std::endl;
    else
        std::cout << "Узел " << key << " не найден" << std::endl;

    int key2 = 5;
    tree->remove(key2);
    std::cout << "\nПосле удаления узла " << key2 << ":\n";
    tree->print();
    std::cout << "\nКоличество узлов: " << tree->getNodesCount() << std::endl;

    delete tree;
}
