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

        } else if(command=="ls"){
            auto& chMap = fs.getCurrentDirectory()->getChildren();
            if(chMap.empty()) continue;

            for(auto const& pair: chMap){
                string name = pair.first;
                FileSystemNode* nodePtr = pair.second;
                nodePtr->printInfo();
                cout << endl;
            }

        } else if (command == "touch") {
            string fileName;
            ss >> fileName;
            if (fileName.empty()) {
                cout << "Usage: touch <file_name>" << endl;
                continue;
            }

            if (fs.getCurrentDirectory()->findChild(fileName) != nullptr) {
                cout << "Error: Name '" << fileName << "' already exists." << endl;
                continue;
            }
 
            File* newFile = new File(fileName, fs.getCurrentDirectory());
            fs.getCurrentDirectory()->addChild(newFile);
            
        } else if(command=="cd") {
            string pathName;
            ss >> pathName;

            if(pathName.empty()){
                fs.setCurrentDirectory(fs.getRoot());
                continue;
            } else if(pathName==".."){
                FileSystemNode* parent = fs.getCurrentDirectory()->getParent();
                if (parent != nullptr) {
                    fs.setCurrentDirectory((Directory*)parent);
                }
            } else {
                FileSystemNode* node = fs.getCurrentDirectory()->findChild(pathName);
                if(node == nullptr){
                    cout << "Error: No such directory: '" << pathName << "'" << endl;
                    continue;
                } else if(node->getType() == "Directory"){
                    fs.setCurrentDirectory((Directory*)node);
                    continue;
                } else {
                    cout << "Error: Not a directory: '" << pathName << "'" << endl;
                    continue;
                }
            }

        } else if(command=="rm"){
            string name;
            ss >> name;

            if(name.empty()){
                cout << "Usage: <rm file/directory_name>" << endl;
                continue;
            }

            Directory* currentDir = fs.getCurrentDirectory();
            FileSystemNode* nodeToRemove = currentDir->findChild(name);
            if(nodeToRemove==nullptr){
                cout << "Error: No such file or directory: '" << name << "'" << endl;
                continue;
            }

            if (nodeToRemove->getType() == "File"){
                currentDir->removeChild(name);
                delete nodeToRemove;
            } else {
                Directory* dirToRemove = (Directory*)nodeToRemove;
                if (dirToRemove->getChildren().empty()){
                    currentDir->removeChild(name);
                    delete dirToRemove;
                } else {
                    cout << "Error: Cannot remove '" << name << "' not empty" << endl;
                    continue;
                }
            }

        } else if(command=="pwd"){
            cout << fs.getPwd() << endl;
        } else if (command == "help") {
             cout << "Available commands:" << endl;
             cout << "  mkdir <name>  - Create a new directory" << endl;
             cout << "  touch <name>  - Create a new file" << endl;
             cout << "  cd <path>     - Change Directory" << endl;
             cout << "  rm <name>     - Remove File/Directory" << endl;
             cout << "  pwd           - Print Working Directory" << endl;
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