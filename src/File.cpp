#include "File.h"      // Include the header file for the File class
#include <iostream>   // Now we can safely include iostream here

// Use the specific 'using' declarations you need in the .cpp file
using std::cout;
using std::endl;

//
// --- Implementation for File::printInfo ---
//
// We use 'File::' to tell the compiler we are defining the
// printInfo function that belongs to the File class.
//
void File::printInfo() const {
    // TODO: Implement the printInfo logic.
    // You can now safely use 'cout' and access 'name' directly.
    // Remember, 'name' was inherited from FileSystemNode.
    cout << "-rw-    " << name;
}