#ifndef FILE_H
#define FILE_H

#include "FileSystemNode.h" // We need to include the parent class definition
#include <string>

// Use a specific 'using' declaration instead of the whole namespace in headers.
using std::string;

// The File class inherits publicly from FileSystemNode.
class File : public FileSystemNode {
private:
    // TODO: Add a member variable to store the content of the file.
    // A 'string' is a good choice for this.
    string content;

public:
    // --- Constructor ---
    // TODO: Implement the constructor.
    // It should accept a name and a pointer to its parent directory.
    // It must call the constructor of the base class (FileSystemNode) to initialize the name and parent.
    File(const string& name, FileSystemNode* parent);


    // --- Destructor ---
    // A virtual destructor is good practice, though it might be empty for this class.
    virtual ~File() {}


    // --- Implementing the "Contract" from FileSystemNode ---
    // The 'override' keyword is a good practice. It tells the compiler you intend
    // to replace the parent's virtual function. The compiler will give an error
    // if you make a typo, which is very helpful.

    // TODO: Implement the getType() function.
    // This function should return the string "File".
    string getType() const override;

    // TODO: Implement the printInfo() function.
    // This function should print details about the file, for example:
    // "-rw-    filename.txt"
    // You can use cout for this.
    void printInfo() const override;


    // --- File-Specific Methods ---

    // TODO: Implement a "getter" for the file's content.
    string getContent() const;

    // TODO: Implement a "setter" to change the file's content.
    void setContent(const string& newContent);
};

#endif // FILE_H