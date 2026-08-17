
# 🏦 Banking System
> A simulation of a banking system in the CLI, written entirely in C.

## 📑 Table of Contents
- [**About the project**](#-about-the-project)
- [**Main menu**](#-main-menu)
- [**File structure & hierarchy**](#-file-structure--hierarchy)
- [**Build & Compilation (Makefile)**](#-build--compilation-makefile)
- [**License**](#-license)

## 📌 About the project
**Banking System** is a personal project through which I want to improve my programming skills and try out some new things. The project is written entirely in **C (C99)** and simulates a minimal banking system in the CLI. <br>
The project is still in its early stages, and it will be further developed with the help of other programming languages for more advanced features (building its own database, more advanced encryption functions, etc.).

### Cloning and running the project
```bash
git clone https://github.com/justxma/bankingSys
cd bankingSys
make # after which the program is run from executableFiles/coreFile
make run # runs the program directly
```

## 📋 Main menu
Under development...

## 🗂 File structure & hierarchy
```
bankingSys/
├── dataBase/
│   ├── config.meta     # configuration file for the database
│   └── dataBase.txt    # test database
├── include/            # header files
│   ├── clientConfig.h
│   ├── colors.h        
│   ├── configDB.h
│   ├── cryptString.h
│   └── hashTable.h
├── src/                # C source code files
│   ├── clientConfig.c
│   ├── configDB.c
│   ├── cryptString.c
│   └── hashTable.c
├── coreFile.c          # main C file
├── Makefile    
└── README.md
```

### Files
| File | Responsibility |
|---|---|
| `coreFile.c` | Main file - CLI menu |
| `cryptString.c/.h` | Encryption and decryption functions |
| `clientConfig.c/.h` | Functions related to client functionality (adding/removing a client, finding a client in the database, etc.) |
| `hashTable.c/.h` | Hash table and related functions |
| `configDB.c/.h` | Functions for configuring the config.meta file |
| `colors.h` | Header file for defining text colors/fonts |

## ⚙️ Build & Compilation (Makefile)

### Prerequisites
- **GCC** (`gcc`) with C99 support or newer
- **GNU Make** (`make`)
- **Valgrind** *(optional)* — for memory profiling on Linux/macOS

### Build commands

**1. Compile binary**
Compiles all source files and links them into `executable_files/coreFile`:
```bash
make
```

**2. Run the application**
Compiles (if necessary) and runs the application:
```bash
make run
```

**3. Clean build artifacts**
Removes executables, object files, and temporary outputs:
```bash
make clean
```

**4. Check for memory leaks**
Compiles (if necessary), runs, and checks the program for memory leaks:
```bash
make valgrind
```
Command executed behind the scenes:
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./executableFiles/coreFile
```

## 📜 License
Distributed under the **MIT license**. Created for educational and demonstrative purposes, for system programming in C, security, and low-level software architecture.