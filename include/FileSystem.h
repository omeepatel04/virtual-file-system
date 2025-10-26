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
    std::string getPath(Directory* current) const;
    std::string getPwd() const;

    // --- NEW ---
    void saveSystem(const std::string& filename) const;
    void loadSystem(const std::string& filename);
};

#endif // FILESYSTEM_H