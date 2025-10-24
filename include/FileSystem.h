#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Directory.h"
#include <string>

class FileSystem {
    private:

    Directory* root;
    Directory* currentDirectory;

    public:

    FileSystem();
    ~FileSystem();

    Directory* getRoot() const;
    Directory* getCurrentDirectory() const;
    void setCurrentDirectory(Directory* directory);

};

#endif