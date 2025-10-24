#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Directory.h"
#include <string>

class FileSystem {
    private:

    Directory* root;
    Directory* currentDirectory;

    public:

    FileSystem() {
        root = new Directory("/", nullptr);
        currentDirectory = root;
    }

    ~FileSystem(){
        delete root;
    }

    Directory* getRoot() const {return root;}
    Directory* getCurrentDirectory() const {return currentDirectory;}
    void setCurrentDirectory(Directory* directory);

}

#endif