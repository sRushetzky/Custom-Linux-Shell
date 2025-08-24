# 🐚 Custom Linux Shell
## 📌 Description

This project is an implementation of a basic custom shell written in C, running on Linux (Ubuntu).
The shell continuously displays a prompt, accepts user commands, and executes them using system calls (fork, execv, wait).
It searches for executables inside the directories listed in the $PATH environment variable, supports built-in commands (cd, leave), and provides error handling for invalid inputs.

This project was developed as part of an Operating Systems assignment to practice process creation, system calls, and environment variable handling.

##⚙️ Technologies Used

C (GCC on Ubuntu Linux)

POSIX system calls:

fork() – create a new process

execv() – execute commands

wait() – wait for child processes

getenv() – access environment variables

strtok() – parse PATH and user input

chdir() – change directories

## ✨ Features

Displays a custom shell prompt (shell>)

Executes standard Linux commands (e.g., ls, pwd, echo, etc.)

Command lookup in the current directory and all directories defined in $PATH

Built-in commands:

cd <dir> → change working directory

leave → exit the shell

Error handling:

Prints an error if a command is not found

Prints an error if cd fails

📂 File Structure

 myshell2.c    
 Main shell implementation
 

## 🚀 How to Run
Requirements:

Linux environment (tested on Ubuntu)

GCC compiler installed

Build:
gcc myshell2.c -o myshell2

Run:
./myshell2

## Example Usage:
shell> ls -l
shell> pwd
shell> cd /home/user
shell> echo "Hello World"
shell> leave

## 👨‍💻 Author

Shahar Rushetzky

🔗 LinkedIn Profile: https://www.linkedin.com/in/shahar-rushetzky/

📞 Phone: +972-52-7729726
