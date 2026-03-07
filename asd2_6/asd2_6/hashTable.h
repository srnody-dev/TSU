//
//  hashTable.h
//  asd2_6
//
//  Created by srnody on 03.03.2026.
//

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

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
    
    void rehash(int newSize) {

        Node** oldTable = table;
        int oldSize = size;

        size = newSize;

        table = new Node*[size];
        for (int i = 0; i < size; i++)
            table[i] = nullptr;

        for (int i = 0; i < oldSize; i++) {
            Node* current = oldTable[i];
            while (current) {
                insert(current->key, current->value);
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] oldTable;
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
    
    void resize(int newSize){
        rehash(newSize);
    }
    
    void changeHashFunc(IHashFunc* newHashFunc){
        hashFunc=newHashFunc;
        rehash(size);
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
    
    std::string getBucketItems(int bucketIndex) const {
        if (bucketIndex < 0 || bucketIndex >= size)
            throw std::out_of_range("Invalid bucket index");

        Node* current = table[bucketIndex];
        if (!current)
            return "empty";

        std::string result;

        while (current) {
            result += "[";
            result += std::to_string(current->key);
            result += ", ";
            result += current->value;
            result += "] ";

            current = current->next;
        }

        return result;
    }
    
};
