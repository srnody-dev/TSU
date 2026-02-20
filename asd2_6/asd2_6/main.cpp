//
//  main.cpp
//  asd2_6
//
//  Created by srnody on 19.02.2026.
//

#include <iostream>
#include <string>

using namespace std;

class IHashFunc {
public:
    virtual int hash(int key, int i, int N) const = 0;
    virtual ~IHashFunc() {}
};


// хеш функция 3
// hi(K) = ((K mod N) + i × (1+ K mod (N – 2))) mod N

class HashFunc3 : public IHashFunc {
public:
    int hash(int key, int i, int N) const override {
        int h0 = key % N;
        int h1 = key % (N - 2);
        return (h0 + i * (1 + h1)) % N;
    }
};

struct Node {
    int key;
    string value;
    Node* next;

    Node(int k, const string& v)
        : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    Node** table;
    int size;
    IHashFunc* hashFunc;
    
    void clear() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }
    
public:
    HashTable(IHashFunc* func= nullptr,int N = 10) : size(N), hashFunc(func) {
        
        table = new Node*[size];
        for (int i = 0; i < size; i++)
            table[i] = nullptr;
    }
    
    
    ~HashTable() {
        clear();
    }
    
    HashTable(const HashTable& other)
    : size(other.size), hashFunc(other.hashFunc) {
        
        table = new Node*[size];
        
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
            
            Node* current = other.table[i];
            Node** tail = &table[i];
            
            while (current) {
                *tail = new Node(current->key, current->value);
                tail = &((*tail)->next);
                current = current->next;
            }
        }
    }
    
    void insert(int key, const string& value) {
        int bucket = hashFunc->hash(key, 1, size);

        Node* current = table[bucket];

        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = table[bucket];
        table[bucket] = newNode;
    }
    
    bool contains(int key) const {
        int bucket = hashFunc->hash(key, 1, size);

        Node* current = table[bucket];

        while (current) {
            if (current->key == key)
                return true;
            current = current->next;
        }

        return false;
    }
    
    void remove(int key) {
        int bucket = hashFunc->hash(key, 1, size);

        Node* current = table[bucket];
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev)
                    prev->next = current->next;
                else
                    table[bucket] = current->next;

                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
    
    HashTable& operator=(const HashTable& other) {
        if (this == &other) return *this;
        clear();
        
        size = other.size;
        hashFunc = other.hashFunc;
        
        table = new Node*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
            
            Node* current = other.table[i];
            Node** tail = &table[i];
            
            while (current) {
                *tail = new Node(current->key, current->value);
                tail = &((*tail)->next);
                current = current->next;
            }
        }
        return *this;
    }
    
    string& operator[](int key) {
        int bucket = hashFunc->hash(key, 1, size);

        Node* current = table[bucket];

        while (current) {
            if (current->key == key)
                return current->value;
            current = current->next;
        }

        insert(key, "");
        return table[bucket]->value;
    }
    
    void print() const {
        cout << " Bucket |  Key/Value" << endl;
        for (int i = 0; i < size; i++) {
            cout << "\t"<< i << "\t| ";
            Node* current = table[i];
            while (current) {
                cout << "[" << current->key
                     << ", " << current->value << "] ";
                current = current->next;
            }

            cout << endl;
        }
    }
    
};

int main() {
    
    HashFunc3 hf3;

    HashTable table(&hf3);

    table.insert(197, "Bentley");
    table.insert(178, "Jaguar");
    table.insert(77, "BMW");
    table.insert(777, "Mercedes");
    table.insert(78, "Nissan");
    table.insert(99, "Audi");
    table.insert(70, "Toyota");
    table.insert(78, "Tesla");

    table.print();

    cout << "\nContains 77? "
         << (table.contains(77) ? "Yes" : "No") << endl;
    
    table.remove(70);
    cout << "\nAfter remove:\n";
    table.print();
    
    table[777]="Mercedes-Benz";
    cout << "\nAfter operator[]:\n";
    table.print();
}

