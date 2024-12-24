# Minishell

A minimal shell implementation inspired by bash, created as part of the 42 School curriculum. This project aims to help understand how shells work by implementing basic shell functionalities.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Technical Details](#technical-details)
- [Project Structure](#project-structure)
- [Contributors](#contributors)

## Overview
Minishell is a simple shell that implements basic shell functionality, including command execution, environment variable management, and signal handling. The project is written in C and follows 42 School's coding standards.

## Features
- Command execution with absolute and relative paths
- Built-in command implementation
- Environment variable management
- Signal handling (ctrl-C, ctrl-D, ctrl-\\)
- Command line parsing with quotes and special characters
- Redirections (<, >, >>)
- Pipes implementation
- Environment variable expansion
- Exit status management ($?)
- Error handling

## Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/minishell.git

# Navigate to project directory
cd minishell

# Compile the project
make

# Clean compiled files
make clean

# Recompile
make re
```

## Usage
```bash
# Run minishell
./minishell
```

## Built-in Commands
The following built-in commands are implemented:
- `echo` with option `-n`
- `cd` with relative or absolute path
- `pwd` without options
- `export` without options
- `unset` without options
- `env` without options or arguments
- `exit` without options

## Technical Details
- Prompt display using readline library
- Command history management
- Memory leak handling
- Fork process management
- File descriptor management
- Error handling and appropriate error messages

## Project Structure
```
minishell/
├── src/
│   ├── main.c
│   ├── parsing/
│   ├── execution/
│   ├── builtins/
│   └── utils/
├── include/
│   └── minishell.h
├── libft/
└── Makefile
```

## Norm Compliance
This project follows the 42 School norm requirements:
- All functions are less than 25 lines
- No more than 5 functions per file
- One single variable declaration per line
- Variable declarations at the start of functions
- No `for` loops (while loops only)
- No function returns within other functions

## Error Management
The shell properly handles and displays error messages for:
- Command not found
- Permission denied
- No such file or directory
- Invalid syntax
- Memory allocation failures

## Resources Used
- GNU Bash Reference Manual
- Unix/Linux system calls documentation
- 42 School curriculum resources

## License
This project is part of the 42 School curriculum and follows its academic guidelines.
