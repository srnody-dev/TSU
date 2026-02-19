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

int main() {
    
}

