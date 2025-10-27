#include "File.h"
#include <iostream>
#include <fstream> 

using std::cout;
using std::endl;
using std::ofstream; 

void File::printInfo() const {
    cout << "-rw-    " << name;
}

// Helper function to write a string safely to a binary file
// We first write the size of the string, then the string's data.
inline void writeString(ofstream& file, const string& str) {
    size_t len = str.length();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(str.c_str(), len);
}


// Implementation of the save contract for a File
void File::save(ofstream& file) const {
    // 1. Write a marker character 'F' to identify this as a File
    char type = 'F';
    file.write(&type, sizeof(type));

    // 2. Write the name and content using our helper
    writeString(file, this->name);
    writeString(file, this->content);
}