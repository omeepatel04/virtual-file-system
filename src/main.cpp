#include <iostream>    
#include <string>       
#include <sstream>     
#include "FileSystem.h"  
#include "Directory.h"   
#include "File.h"        


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::stringstream;

int main() {
    
    FileSystem fs;
    cout << "Welcome to the Virtual File System!" << endl;
    cout << "Type 'help' for a list of commands." << endl;


    while (true) {
      
        cout << fs.getPath(fs.getCurrentDirectory());
        string line;
        if (!getline(cin, line)) {
            break; 
        }

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "exit") {
            cout << "Goodbye!" << endl;
            break;
        
        } else if (command == "mkdir") {
            string dirName;
            ss >> dirName;

            if (dirName.empty()) {
                cout << "Usage: mkdir <directory_name>" << endl;
                continue;
            }

            if (fs.getCurrentDirectory()->findChild(dirName) != nullptr) {
                cout << "Error: Name '" << dirName << "' already exists." << endl;
                continue;
            }

            Directory* newDir = new Directory(dirName, fs.getCurrentDirectory());
            fs.getCurrentDirectory()->addChild(newDir);

        } else if (command == "help") {
             cout << "Available commands:" << endl;
             cout << "  mkdir <name>  - Create a new directory" << endl;
             // We will add more commands here
             cout << "  exit          - Exit the simulator" << endl;

        } else if (command.empty()) {
            // User just pressed Enter, do nothing
            continue;

        } else {
            // Command wasn't recognized
            cout << "Command not found: " << command << endl;
        }
    }

    // --- Step 7: Cleanup ---
    // When main() ends, 'fs' goes out of scope. Its destructor (~FileSystem) is called automatically.
    // The destructor 'delete root;', which triggers the cascading delete for the entire file system.
    return 0;
}