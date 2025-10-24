#include "FileSystem.h"
#include "Directory.h"

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
