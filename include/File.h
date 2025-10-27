#ifndef FILE_H
#define FILE_H

#include "FileSystemNode.h"
#include <string>
#include <fstream> 

using std::string;

class File : public FileSystemNode {
private:
    string content;

public:
    File(const string& name, FileSystemNode* parent)
        : FileSystemNode(name, parent) {}

    virtual ~File() {}

    string getType() const override { return "File"; }
    void printInfo() const override;


    void save(std::ofstream& file) const override;


    string getContent() const { return content; }
    void setContent(const string& newContent) { content = newContent; }
};

#endif 