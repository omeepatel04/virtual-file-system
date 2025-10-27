#ifndef FILESYSTEMNODE_H
#define FILESYSTEMNODE_H

#include <string>
#include <fstream>

using std::string;

class FileSystemNode {
protected:
    string name;
    FileSystemNode* parent;

public:
    FileSystemNode(const string& name, FileSystemNode* parent)
        : name(name), parent(parent) {}

    virtual ~FileSystemNode() {}

    string getName() const { return name; }
    FileSystemNode* getParent() const { return parent; }

    virtual string getType() const = 0;
    virtual void printInfo() const = 0;


    // A "contract" function to make all nodes saveable
    // We pass an output file stream (ofstream) by reference
    virtual void save(std::ofstream& file) const = 0;
};

#endif