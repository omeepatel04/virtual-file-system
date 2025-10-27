#include "FileSystem.h"
#include "Directory.h"
#include "File.h"    
#include <string>
#include <vector>
#include <fstream>    
#include <iostream>   

using std::string;
using std::vector;
using std::ofstream; 
using std::ifstream; 
using std::ios;      

// Helper functions for binary I/O
inline void writeString(ofstream& file, const string& str) {
    size_t len = str.length();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(str.c_str(), len);
}

string readString(ifstream& file) {
    size_t len;
    file.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (file.fail()) return ""; // Handle read error
    std::vector<char> buffer(len);
    file.read(buffer.data(), len);
    return string(buffer.begin(), buffer.end());
}

// --- Recursive Helper for Loading ---
// This function reads from the file and recursively builds the tree
FileSystemNode* loadNode(ifstream& file, Directory* parent) {
    char type;
    file.read(&type, sizeof(type));
    if (file.fail()) return nullptr; // End of file or error

    if (type == 'D') {
        string name = readString(file);
        Directory* dir = new Directory(name, parent);
        
        size_t numChildren;
        file.read(reinterpret_cast<char*>(&numChildren), sizeof(numChildren));
        
        for (size_t i = 0; i < numChildren; ++i) {
            // Recursively load all children
            FileSystemNode* child = loadNode(file, dir);
            if (child) {
                dir->addChild(child);
            }
        }
        return dir;
    } else if (type == 'F') {
        string name = readString(file);
        string content = readString(file);
        File* fileNode = new File(name, parent);
        fileNode->setContent(content);
        return fileNode;
    }
    return nullptr;
}
// --- End of new helper functions ---


FileSystem::FileSystem() {
    root = new Directory("/", nullptr);
    currentDirectory = root;
}

FileSystem::~FileSystem() {
    delete root;
}

Directory* FileSystem::getRoot() const { return root; }
Directory* FileSystem::getCurrentDirectory() const { return currentDirectory; }
void FileSystem::setCurrentDirectory(Directory* directory) {
    currentDirectory = directory;
}

std::string FileSystem::getPath(Directory* current) const {
    if (current == root) {
        return "/> ";
    }
    string path;
    while (current != root) {
        path = "/" + current->getName() + path;
        current = (Directory*)current->getParent();
    }
    return path + "> ";
}

std::string FileSystem::getPwd() const {
    if (currentDirectory == root) {
        return "/";
    }
    string path;
    Directory* current = currentDirectory;
    while (current != root) {
        path = "/" + current->getName() + path;
        current = (Directory*)current->getParent();
    }
    return path;
}

// --- NEW ---
void FileSystem::saveSystem(const string& filename) const {
    // Open the file in binary mode
    ofstream file(filename, ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }
    // Start the recursive save process from the root
    root->save(file);
    file.close();
    std::cout << "File system saved to " << filename << std::endl;
}

void FileSystem::loadSystem(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return;
    }
    
    // Clear the existing file system
    delete root;
    
    // The first node in the file MUST be the root
    FileSystemNode* loadedRoot = loadNode(file, nullptr);
    if (loadedRoot && loadedRoot->getType() == "Directory") {
        root = (Directory*)loadedRoot;
        currentDirectory = root;
        std::cout << "File system loaded from " << filename << std::endl;
    } else {
        std::cerr << "Error: Invalid file format or empty file." << std::endl;
        // Re-initialize a default empty system
        root = new Directory("/", nullptr);
        currentDirectory = root;
    }
    file.close();
}