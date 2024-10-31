# File Directory System

A C-based implementation of a hierarchical file directory system with basic file operations and recovery features.

## Table of Contents
1. [About The Project](#about-the-project)
2. [Built With](#built-with)
3. [Getting Started](#getting-started)
4. [Installation](#installation)
5. [Dependencies](#dependencies)
6. [Problem Statement](#problem-statement)
7. [Key Features](#key-features)
8. [Contributing](#contributing)
9. [License](#license)
10. [Authors](#authors)
11. [Acknowledgements](#acknowledgements)

---
## About The Project
This project implements a file directory system in C that simulates basic file system operations. It provides a hierarchical structure similar to a real file system, with features like file and directory management, deletion recovery, and protection for system directories. The implementation uses a tree data structure where each node can represent either a file or a directory.

---
## Built With
- **C Programming Language**: Core implementation
- **Standard C Libraries**: 
  - `stdio.h`: Standard input/output operations
  - `stdlib.h`: Memory allocation and program control
  - `string.h`: String manipulation functions

---
## Getting Started
To get started with this file directory system, you'll need a C compiler installed on your system. The project provides a simple menu-driven interface to interact with the file system operations.

---
## Installation
1. Clone the repository to your local machine.
   ```bash
   git clone [your-repository-link]
   ```
2. Navigate to the project directory.
   ```bash
   cd file-directory-system
   ```
3. Compile the program using a C compiler.
   ```bash
   gcc file_directory_system.c -o file_system
   ```
4. Run the executable.
   ```bash
   ./file_system
   ```

---
## Dependencies
- C Compiler (GCC recommended)
- Standard C Libraries
  - stdio.h
  - stdlib.h
  - string.h

---
## Problem Statement
The goal of this project is to implement a file system that:
- Maintains a hierarchical structure of files and directories
- Provides basic file operations (create, delete, search)
- Implements a recovery system for deleted items
- Protects system directories from accidental deletion
- Manages memory efficiently using dynamic allocation

---
## Key Features
1. **Hierarchical Structure**: 
   - Tree-based implementation of directories and files
   - Support for nested directories
   - Sibling-child relationship management

2. **File Operations**:
   - Create new files and directories
   - Delete existing files and directories
   - Search for files and directories
   - Display directory structure

3. **Recovery System**:
   - Maintains a list of recently deleted items
   - Allows recovery of the last deleted item
   - Prevents permanent data loss

4. **Protected Directories**:
   - System directories (Downloads, Documents, etc.) are protected
   - Cannot be deleted accidentally
   - Ensures system stability

5. **Memory Management**:
   - Dynamic memory allocation for nodes
   - Proper cleanup of allocated memory
   - Prevention of memory leaks

---
## Contributing
Contributions are welcome! Here's how you can contribute:
1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---
## License
Distributed under the MIT License. See `LICENSE` for more information.

---
## Author
- Shubam Sarawagi
- Sai Ganeshan M
- Subhyansh Singh

---
## Acknowledgements
- Data Structures and Algorithms concepts
- C Programming language documentation
- File System design principles
- Open source community for inspiration and best practices

---