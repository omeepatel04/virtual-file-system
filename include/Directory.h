#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FileSystemNode.h"
#include <string>
#include <map>
#include <fstream>

class File;

class Directory : public FileSystemNode {
private:
    std::map<std::string, FileSystemNode*> children;

public:
    Directory(const std::string& name, FileSystemNode* parent) 
        : FileSystemNode(name, parent) {}

    virtual ~Directory();

    string getType() const override { return "Directory"; }
    void printInfo() const override;


    void save(std::ofstream& file) const override;

    FileSystemNode* findChild(const std::string& name);
    void addChild(FileSystemNode* child);
    void removeChild(const std::string& name);
    std::map<std::string, FileSystemNode*>& getChildren();
};

#endif // DIRECTORY_H