#ifndef FILE_H
#define FILE_H

#include "FileSystemNode.h"
#include <string>
#include <fstream> // <-- Make sure this is included

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

    // --- NEW ---
    // Add this declaration to fulfill the contract from FileSystemNode
    void save(std::ofstream& file) const override;
    // --- END NEW ---

    string getContent() const { return content; }
    void setContent(const string& newContent) { content = newContent; }
};

#endif // FILE_H