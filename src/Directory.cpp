#include "Directory.h"
#include <iostream>



Directory::~Directory(){
    for(auto const& [name, nodePtr] : children){
        delete nodePtr;
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