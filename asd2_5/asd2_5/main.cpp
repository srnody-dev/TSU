
#include "booleanVector.hpp"
#include <iostream>
#include "Huffman.hpp"

int main() {
    Huffman huff;
    
    huff.build("test");

    double huffEncode = huff.encode("input.txt", "encoded.txt");
    std::cout << "encode(): " << huffEncode << std::endl;

    bool huddDecode = huff.decode("encoded.txt", "decoded.txt");
    std::cout << "decode(): " << huddDecode << std::endl;
    
    return 0;
}
