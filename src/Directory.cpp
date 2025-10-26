#include "Directory.h"
#include <iostream>
#include <fstream> // --- NEW ---

using std::cout;
using std::endl;
using std::ofstream; // --- NEW ---
using std::string; // --- NEW ---

// --- NEW ---
// We need the writeString helper here too.
// (In a bigger project, this would go in a shared "utils.h")
inline void writeString(ofstream& file, const string& str) {
    size_t len = str.length();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(str.c_str(), len);
}

Directory::~Directory() {
    for (auto const& pair : children) {
        FileSystemNode* nodePtr = pair.second;
        delete nodePtr;
    }
}

void Directory::printInfo() const {
    cout << "drw-    " << name;
}

FileSystemNode* Directory::findChild(const string& name) {
    auto it = children.find(name);
    if (it != children.end()) {
        return it->second;
    }
    return nullptr;
}

// --- NEW ---
// Implementation of the save contract for a Directory
void Directory::save(ofstream& file) const {
    // 1. Write a marker character 'D' for Directory
    char type = 'D';
    file.write(&type, sizeof(type));

    // 2. Write the directory's name
    writeString(file, this->name);

    // 3. Write the number of children this directory has
    size_t numChildren = children.size();
    file.write(reinterpret_cast<const char*>(&numChildren), sizeof(numChildren));

    // 4. Loop and recursively call save() on each child
    for (auto const& pair : children) {
        pair.second->save(file);
    }
}

void Directory::addChild(FileSystemNode* child) {
    children[child->getName()] = child;
}

void Directory::removeChild(const std::string& name) {
    children.erase(name);
}

std::map<std::string, FileSystemNode*>& Directory::getChildren() {
    return children;
}