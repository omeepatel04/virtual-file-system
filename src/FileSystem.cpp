#include "FileSystem.h"
#include "Directory.h"
#include <string>
#include <vector>

FileSystem::FileSystem(){
    root = new Directory("/", nullptr);
    currentDirectory = root; 
}

FileSystem::~FileSystem(){
    delete root;
}

Directory* FileSystem::getRoot() const {return root;}
Directory* FileSystem::getCurrentDirectory() const {return currentDirectory;}
void FileSystem::setCurrentDirectory(Directory* directory){
    currentDirectory = directory;
}

std::string FileSystem::getPath(Directory* current) const {
    if (current == root) {
        return "/>"; 
    }

    std::string path;
    
    while (current != root) { 
        path = "/" + current->getName() + path;
        current = (Directory*)current->getParent();
    }

    if (path.empty()) {
        return "/ ";
    }

    return path + "> ";
}







