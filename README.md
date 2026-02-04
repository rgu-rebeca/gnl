# 42 Cursus' get_next_line (GNL)
*Reading a line from a fd is way too tedious*


## 📌 Status
**Finished**

**Grade:** 125 / 100 ✅


## 💡 About the project

The **get_next_line** project from **42 School** focuses on implementing a function that reads from a file descriptor line by line.

This project introduces an essential concept in C programming: **static variables**, allowing the function to keep track of unread data between function calls.

The `get_next_line` function returns a single line each time it is called. When used inside a loop, it allows reading an entire file line by line until reaching the end of the file. The function behavior adapts to different buffer sizes defined at compile time.


## 🧠 What this project teaches

This project helps develop and demonstrate the following skills:

- Understanding and using **static variables**
- Reading from **file descriptors**
- Managing **dynamic memory** safely
- Handling edge cases (EOF, errors, variable buffer sizes)
- Writing efficient and norm-compliant C code
- Designing functions that preserve state between calls


## 🛠️ Usage

This function is **not a standalone program**.  
Its source files must be included and compiled within another project.

### 1️⃣ Including it in your code

Include the header file in your source code:

```c
#include "get_next_line.h"
```

When compiling, add the source files and define the buffer size:

get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=<size>


Example:

gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c

📋 Function prototype
char *get_next_line(int fd);

Return values

A line read from the file descriptor, including the \n character if present

NULL if there is nothing left to read or if an error occurs

### 📏 Constraints & rules

**Only the following functions are allowed:**

- read

- malloc

- free

Global variables are forbidden

lseek() is forbidden

**The function must work with:**

- Regular files

- Standard input

- Any BUFFER_SIZE value

- Memory leaks are not tolerated

The function must read as little as possible on each call

### ⭐ Bonus part

**The bonus version extends the functionality by:**

Using only one static variable

Handling multiple file descriptors simultaneously

This allows reading from different file descriptors alternately without losing the reading state of each one.

**Bonus files:**

get_next_line_bonus.c

get_next_line_bonus.h

get_next_line_utils_bonus.c

### 🧪 Testing

To test the function manually:

Uncomment the main function inside get_next_line.c

Modify or create test files (e.g. test.txt)

Compile and run:

gcc -Wall -Werror -Wextra -D BUFFER_SIZE=<size> get_next_line.c get_next_line_utils.c && ./a.out


You can also use third-party testers:

https://github.com/Tripouille/gnlTester

