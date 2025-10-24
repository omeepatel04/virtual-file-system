#ifndef DIRECTORY
#define DIRECTORY

#include "FileSystemNode.h"
#include <string>
#include <map>

class File;

class Directory : public FileSystemNode {
    private:
    std::map<std::string, FileSystemNode*> children;

    public:
    Directory(const std::string &name, FileSystemNode* parent) : FileSystemNode(name, parent) {}

    virtual ~Directory();

    std::string getType() const override {return "Directory";}
    
    void printInfo() const override;

    FileSystemNode* findChild(const std::string& name);

    void addChild(FileSystemNode* child){
        children[child->getName()] = child;
    }

    void removeChild(const std::string& name){
        children.erase(name);
    }

    std::map<std::string, FileSystemNode*>& getChildren(){return children;}

#endif