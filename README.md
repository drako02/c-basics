# File System Explorer

A lightweight C-based file system exploration tool that demonstrates low-level system programming through direct system calls and POSIX APIs. Built to understand the fundamentals of file I/O, directory traversal, and process management in Linux.

## Features

- **Dual File Access** - Compare standard library functions vs. raw system calls
- **Directory Navigation** - Browse and explore filesystem with detailed metadata
- **Process Management** - View process information and execute shell commands
- **Interactive CLI** - Clean menu-driven interface for exploration
- **Signal Handling** - Graceful shutdown with SIGINT handling

## 🚀 Quick Start

```bash
# Build
make

# Run
./fsexplorer

# Clean
make clean
```

## Tech Stack

- **Language:** C (C99)
- **Build System:** Make
- **System APIs:** POSIX system calls, Linux file APIs
- **Features:** Signal handling, process management, file I/O

## What I Learned

- Direct vs. buffered I/O operations
- File descriptor management and system call efficiency
- POSIX directory APIs and metadata extraction
- Process spawning and signal handling in C

## Project Structure

```
├── main.c          # Entry point & interactive menu
├── fileops.*       # High-level file operations
├── syscalls.*      # Low-level system call wrappers
├── directories.*   # Directory traversal & metadata
├── processes.*     # Process info & command execution
└── makefile        # Build configuration
```

## License

MIT License - feel free to use this project for learning!

---

**Author:** [drako02](https://github.com/drako02)
