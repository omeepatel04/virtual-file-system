# 🛰️ Virtual File System (VFS) in C++

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/Standard-C%2B%2B17-blue.svg)](https://isocpp.org/std/the-standard)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**A high-performance, persistent virtual file system simulator built from scratch in modern C++.** This project demonstrates a command-line shell interface that manages a complete file and directory tree *in-memory* and includes the ability to **serialize** the entire system state to and from a binary file.

This is a deep dive into core OOP principles, advanced memory management, and C++ file I/O.

---

## 🏛️ System Architecture

The core of the VFS is a **polymorphic tree**. An abstract base class, `FileSystemNode`, defines a common interface (a "contract") for all entities. The `File` and `Directory` classes inherit from this base and provide concrete implementations of its virtual functions.

A `Directory` object manages its contents via an `std::map`, mapping string names to `FileSystemNode*` pointers. This design is the key to its two most powerful features:

1.  **Polymorphism:** The `Directory` can hold both `File*` and `Directory*` pointers in the same collection, allowing commands like `ls` to treat them uniformly.
2.  **Recursive Memory Management:** A recursive, virtual destructor is implemented. Calling `delete` on the `root` directory triggers a "cascading delete," which safely de-allocates the entire tree from the heap, ensuring **zero memory leaks**.



---

## ✨ Features

This VFS simulates a robust Unix-like shell environment, supporting:

* **Full CRUD & Navigation:** `mkdir`, `touch`, `ls`, `cd`, `pwd`, `rm`
* **Content Manipulation:** `write` to files and `cat` to read them.
* **Advanced Deletion:** `rm -r` for recursive, non-empty directory removal.
* **Data Persistence:** `save` and `load` commands to serialize the entire file system state to a binary file, preserving it between sessions.
* **Safe by Design:** All operations are memory-safe. The system handles name collisions, attempts to `cd` into files, and deletion of non-empty directories.

---

## 🚀 How It Works: The "Impressive" Parts

This project stands out by its focus on two complex C++ topics:

### 1. Persistent Binary Serialization (`save`/`load`)
The `save` command triggers a recursive traversal of the file system tree. Each node "serializes" itself to a binary file by writing:
1.  A **Type Marker** (`'D'` for Directory, `'F'` for File).
2.  Its **Name** (length-prefixed).
3.  **For Files:** Its **Content** (length-prefixed).
4.  **For Directories:** The **Number of Children**, followed by the recursive `save()` call for each child.

The `load` command reads this binary file, recursively reconstructing the entire object tree on the heap.

### 2. Automatic Memory Management (RAII)
This project is 100% memory-safe without using smart pointers.
* The `FileSystem` object in `main()` "owns" the `root` pointer.
* When `main()` ends, `fs` goes out of scope, and its destructor is called.
* The destructor calls `delete root;`.
* The `Directory`'s virtual destructor is called, which loops through its `children` map and calls `delete` on every child pointer.
* This triggers a "cascading" delete that unwinds the entire tree, freeing all allocated memory.

---

## 🛠️ Building and Running

### Prerequisites

* A C++ compiler supporting the C++17 standard (e.g., `g++` or `Clang`).
* `make` (optional, for the provided Makefile).

### Option 1: Using the Makefile (Recommended)

A `Makefile` is included for easy compilation.

```bash
# Compile the project
make

# Run the executable
./vfs

# Clean up build artifacts
make clean

```
### Option 2: Manual Compilation (g++)

If you don't have make, you can compile all source files directly:


```bash

g++ -std=c++17 -Wall -I include -o vfs src/main.cpp src/File.cpp src/Directory.cpp src/FileSystem.cpp
-std=c++17: Enables the C++17 standard.
```

-Wall: Enables all common compiler warnings (good practice).
-I include: Tells the compiler to look in the include/ folder for header files.

---

### 💻 Example Session
``bash
$ ./vfs
Welcome to the Virtual File System!
Type 'load vfs.dat' to load previous session.
/> mkdir projects
/> cd projects
/projects> touch todo.txt
/projects> write todo.txt "1. Finish VFS Project. 2. Update resume."
/projects> cat todo.txt
1. Finish VFS Project. 2. Update resume.
/projects> cd ..
/> save my_fs.dat
File system saved to my_fs.dat
/> ls
drw-    projects
/> rm -r projects
/> ls
/> exit
Goodbye!

$ ./vfs
Welcome...
/> load my_fs.dat
File system loaded from my_fs.dat
/> ls
drw-    projects
/> cd projects
/projects> cat todo.txt
1. Finish VFS Project. 2. Update resume.
/projects>

```

--- 

## 👥 Connect

Om Patel - [LinkedIn](https://www.linkedin.com/in/ompatel4306/)