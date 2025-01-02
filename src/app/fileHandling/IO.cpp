#include <iostream>
#include "IO.hpp"

using namespace std;

IO::~IO() = default;

IO::IO(const string& file_path){
    file_stream.open(file_path, ios::in | ios::out | ios::binary);
    if(!file_stream.is_open()){
        cout << "Unable to open the file: " << file_path << endl; 
    }
}

fstream IO::getFileStream(){
    return move(file_stream);
}