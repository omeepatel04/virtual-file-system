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
    cout << "Type 'load vfs.dat' to load previous session." << endl;

    // --- Main Program Loop ---
    while (true) {
      
        cout << fs.getPath(fs.getCurrentDirectory());
        
        string line;
        if (!getline(cin, line)) { break; }

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
            if(chMap.empty()) { continue; }
            for(auto const& pair: chMap){
                pair.second->printInfo();
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
            } 
            if(pathName==".."){
                FileSystemNode* parent = fs.getCurrentDirectory()->getParent();
                if (parent != nullptr) {
                    fs.setCurrentDirectory((Directory*)parent);
                }
                continue;
            } 
            
            FileSystemNode* node = fs.getCurrentDirectory()->findChild(pathName);
            if(node == nullptr){
                cout << "Error: No such directory: '" << pathName << "'" << endl;
                continue;
            } 
            if(node->getType() == "Directory"){
                fs.setCurrentDirectory((Directory*)node);
            } else {
                cout << "Error: Not a directory: '" << pathName << "'" << endl;
            }

        // --- MODIFIED RM COMMAND ---
        } else if(command=="rm"){
            string arg1, arg2;
            ss >> arg1 >> arg2;

            string name;
            bool recursive = false;

            if (arg1 == "-r") {
                recursive = true;
                name = arg2;
            } else {
                name = arg1;
            }

            if(name.empty()){
                cout << "Usage: rm [-r] <file/directory_name>" << endl;
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
                if (!dirToRemove->getChildren().empty() && !recursive) {
                    // Fail if directory is not empty AND -r was not used
                    cout << "Error: Cannot remove '" << name << "': Directory not empty" << endl;
                } else {
                    // Safe to delete (either empty, or -r was used)
                    currentDir->removeChild(name);
                    delete dirToRemove;
                }
            }

        } else if(command=="pwd"){
            cout << fs.getPwd() << endl;

        } else if(command=="write"){
            string fileName;
            ss >> fileName;
            if(fileName.empty()){
                cout << "Usage: write <filename> \"content\"" << endl;
                continue;
            }
            
            FileSystemNode* node = fs.getCurrentDirectory()->findChild(fileName);
            if(node == nullptr){
                cout << "Error: No such file: '" << fileName << "'" << endl;
                continue;
            }
            if(node->getType() != "File"){
                cout << "Error: Not a file: '" << fileName << "'" << endl;
                continue;
            }

            string contentLine;
            getline(ss, contentLine); 
            size_t firstQuote = contentLine.find('\"');
            size_t lastQuote = contentLine.rfind('\"');
            if (firstQuote == string::npos || lastQuote == string::npos || firstQuote == lastQuote){
                cout << "Error: Content must be in double quotes (e.g. \"hello\")" << endl;
                continue;
            }

            string actualContent = contentLine.substr(firstQuote + 1, lastQuote - firstQuote - 1);
            File* file = (File*)node;
            file->setContent(actualContent);

        } else if (command == "cat") {
            string fileName;
            ss >> fileName;
            if (fileName.empty()) {
                cout << "Usage: cat <filename>" << endl;
                continue;
            }
            FileSystemNode* node = fs.getCurrentDirectory()->findChild(fileName);
            if (node == nullptr) {
                cout << "Error: No such file: '" << fileName << "'" << endl;
                continue;
            }
            if (node->getType() != "File") {
                cout << "Error: Cannot 'cat' a directory: '" << fileName << "'" << endl;
                continue;
            }
            File* file = (File*)node;
            cout << file->getContent() << endl;

            
        } else if (command == "save") {
            string filename;
            ss >> filename;
            if (filename.empty()) {
                filename = "vfs.dat"; // Default save file
            }
            fs.saveSystem(filename);
        
        } else if (command == "load") {
            string filename;
            ss >> filename;
            if (filename.empty()) {
                filename = "vfs.dat"; // Default load file
            }
            fs.loadSystem(filename);

        } else if (command == "help") {
             cout << "Available commands:" << endl;
             cout << "  mkdir <name>       - Create a new directory" << endl;
             cout << "  touch <name>       - Create a new file" << endl;
             cout << "  cd <path>          - Change Directory (use '..' for parent)" << endl;
             cout << "  rm [-r] <name>     - Remove file or directory (use -r for non-empty)" << endl;
             cout << "  pwd                - Print Working Directory" << endl;
             cout << "  write <file> \"...\" - Write content to a file" << endl;
             cout << "  cat <file>         - Read content from a file" << endl;
             cout << "  save [filename]    - Save file system state (default: vfs.dat)" << endl;
             cout << "  load [filename]    - Load file system state (default: vfs.dat)" << endl;
             cout << "  exit               - Exit the simulator" << endl;

        } else if (command.empty()) {
            continue;
        } else {
            cout << "Command not found: " << command << endl;
        }
    }

    return 0;
}