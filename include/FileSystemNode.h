#ifndef FILESYSTEMNODE_H
#define FILESYSTEMNODE_H

#include <string> // For using std::string


// An abstract base class representing any entity in the file system (a file or a directory).
class FileSystemNode {
protected:
    std::string name;
    FileSystemNode* parent; // Pointer to the parent directory

public:
    // Constructor
    FileSystemNode(const std::string& name, FileSystemNode* parent)
        : name(name), parent(parent) {}

    // Virtual destructor is crucial for base classes with virtual functions.
    virtual ~FileSystemNode() {}

    // --- Getters ---
    std::string getName() const { return name; }
    FileSystemNode* getParent() const { return parent; }

    // --- Pure Virtual Functions (The "Contract") ---

    // Must be implemented by derived classes (File, Directory).
    // Returns the type of the node, e.g., "File" or "Directory".
    virtual std::string getType() const = 0;

    // Prints detailed information about the node.
    virtual void printInfo() const = 0;
};

#endif // FILESYSTEMNODE_H