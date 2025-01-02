#include "Crypto.hpp"
#include <iostream>

int main(int argc, char* argv[]){
    if(argc != 2){
        std::cerr << "Usage : ./crypto <task-data>" << std::endl;
        return 1;
    }
    executeCryption(argv[1]);
    return 0;
}
