# Virtual File System Simulator in C++

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

> A command-line application that simulates a hierarchical file system in memory. This project is a deep dive into core Object-Oriented Programming principles, memory management with pointers, and the implementation of tree-based data structures in C++.

---

## 🚀 Core Concepts Demonstrated

This project was built to showcase a strong understanding of fundamental computer science and programming concepts, including:

* **Object-Oriented Programming (OOP):**
    * **Inheritance:** A base `FileSystemNode` class provides a common interface for `File` and `Directory` objects.
    * **Polymorphism & Virtual Functions:** The `Directory` class manages a collection of `FileSystemNode` pointers, treating files and sub-directories uniformly, especially when executing commands like `ls`.
    * **Encapsulation:** Data and methods are neatly bundled within classes, exposing only necessary functionalities.
* **Memory Management:** The entire file system tree is dynamically allocated on the heap, requiring careful use of **pointers** and manual memory management (`new`/`delete`) to prevent memory leaks.
* **Data Structures:** Implementation of a **tree data structure** from scratch to represent the file system hierarchy. `std::map` is used for efficient directory content lookups.
* **Algorithmic Thinking:** Logic for path parsing, recursive operations (like `rm` on a directory), and tree traversal (`pwd`, `cd`).

---

## ✨ Features

The simulator supports the following standard file system commands:

* `mkdir <dirname>`: Creates a new directory.
* `touch <filename>`: Creates a new, empty file.
* `ls`: Lists the contents of the current directory.
* `cd <path>`: Changes the current directory. Supports `..` for the parent directory.
* `pwd`: Prints the full path of the working directory.
* `rm <name>`: Removes a file or an empty directory. (Future goal: recursive delete).
* `exit`: Exits the simulator.

---

## 🏛️ System Architecture

The core of the simulator is a polymorphic tree structure. An abstract base class, `FileSystemNode`, defines the common interface for all entities within the file system. The `File` and `Directory` classes inherit from this base class and provide specialized implementations.

A `Directory` object contains a map of child nodes, where the key is the file/directory name (a `std::string`) and the value is a `FileSystemNode*` pointer. This design allows a directory to hold both `File` objects and other `Directory` objects seamlessly.



---

## 🛠️ Getting Started

### Prerequisites

* A C++ compiler that supports C++11 or later (e.g., GCC, Clang, MSVC).
* `make` (optional, for easy compilation).

### Building and Running

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/](https://github.com/)<your-username>/virtual-file-system.git
    cd virtual-file-system
    ```

2.  **Compile the source code:**
    ```bash
    g++ -std=c++11 -o vfs src/*.cpp
    ```

3.  **Run the application:**
    ```bash
    ./vfs
    ```

---

## 💻 Example Usage

Here is a sample session interacting with the Virtual File System:

```bash
Welcome to the Virtual File System! /> mkdir documents /> ls drw- documents /> cd documents /documents> touch report.txt /documents> touch notes.txt /documents> ls -rw- report.txt -rw- notes.txt /documents> cd .. /> pwd / /> exit Goodbye!
```

---

## 👥 Contributors

* [Your Name] - ([Your GitHub Profile Link])
* [Your Partner's Name] - ([Their GitHub Profile Link])