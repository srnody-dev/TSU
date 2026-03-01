
#include <iostream>
#include "Huffman.hpp"

int main() {
    Huffman huff;
    
    std::string input;
    std::cout << "Enter text:\n";
    std::getline(std::cin, input);
    
    huff.build(input);
    
    std::string encoded,decoded;

    double huffEncode = huff.encode(input, encoded);
    std::cout << "encode(): " << huffEncode << std::endl;

    bool huddDecode = huff.decode(encoded, decoded);
    std::cout << "decode(): " << huddDecode << std::endl;
    
    return 0;
}
