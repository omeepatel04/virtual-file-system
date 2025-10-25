#include "Directory.h"
#include <iostream>



Directory::~Directory() {
    // This is the C++11 compatible way to loop through a map
    for (auto const& pair : children) {
        FileSystemNode* nodePtr = pair.second; // Get the pointer from the map's pair
        delete nodePtr; // Delete the pointer
    }
}

void Directory::printInfo() const{
    std::cout << "drw- " << name;
}

FileSystemNode* Directory::findChild(const std::string& name){
    auto it = children.find(name);
    if (it != children.end()){
        return it->second;
    }

    return nullptr;
}