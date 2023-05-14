# Project Report: Simple Command Line Shell Application

## Introduction

The objective of this project was to build a simple command-line shell application supporting basic commands like `cd`, `ls`, `cat`, `rm`, `mkdir`, `touch`, and `clear`. The application allows users to navigate through the file system, list files, view file contents, delete files and directories, and create new directories, and files.

The project is important as it provides a simplified interface for users to interact with the file system without using a graphical user interface. Moreover, command-line interfaces are still widely used in many software development and system administration tasks, and having an understanding of building such interfaces is valuable for programmers and developers.

The scope of this project is limited to the basic file manipulation commands mentioned above. The application is designed to run on the Windows operating system.

## Design

The system design and architecture of the application follow a simple modular approach, where each command is implemented in a separate function, and the main function calls these functions based on user input. The `process_user_input()` function receives user input and calls the corresponding command functions.

The design choices made are based on simplicity and readability of the code. The code is written in C and follows the procedural programming paradigm. We use the built-in Windows commands, like `dir`, to execute certain functionalities.

### Explanation of Design Choices or Trade-offs Made:

1.  **Modular Design:** We chose to follow a modular design to increase the readability and maintainability of the code. Each command is implemented as a separate function, making it easier to add new commands in the future.
2.  **Use of Standard Libraries:** We used standard C libraries like <stdio.h>, <stdlib.h>, and <string.h> to simplify the implementation of the commands.
3.  **Use of Windows-specific Libraries:** Since the application is designed to run on a Windows operating system, we used Windows-specific libraries like <windows.h> and <io.h> to execute system-specific commands like listing files and removing files.
4.  **Dynamic Memory Allocation:** We used dynamic memory allocation to store the current working directory, allowing the program to handle paths of varying lengths.

## Implementation

The program allows the user to run basic commands such as "cd", "ls", "cat", "rm", "mkdir", "touch", and "clear". It is written in C and uses standard libraries like `stdio.h`, `string.h`, and `limits.h`. The program is designed to run on Windows operating systems.

The main function calls the `getCWD()` function to get the current working directory and store it in the `"currentDir"` variable. It then calls the `welcomeMsg()` function to print a welcome message to the user.

The program enters an infinite loop that reads user input from the command line using `fgets()` and processes it using the `process_user_input()` function. The function checks the user input to determine which command to execute. If the input matches a supported command, the appropriate function is called. Otherwise, the program prints an error message.

The program uses the following functions:

1.  `getCWD()`: This function gets the current working directory and returns a string with the path. It uses the getcwd() function to get the path and reallocates memory as needed to ensure that the path fits in the buffer.
2.  `printCWD()`: This function prints the current working directory to the console.
3.  `listFiles()`: This function lists all files and directories in the current working directory. It uses the "dir" command to get a list of files and directories and prints them to the console.
4.  `change_directory()`: This function changes the current working directory to the directory specified in the input. It uses the chdir() function to change the directory.
5.  `cat()`: This function prints the contents of a file specified in the input to the console. It uses the fopen() and fgets() functions to read the file.
6.  `remove_file()`: This function deletes the file or directory specified in the input. It uses the remove() function to delete the file or rmdir() function to delete the directory.
7.  `mymkdir()`: This function creates a new directory with the name specified in the input. It uses the mkdir() function to create the directory.
8.  `create_file()`: This function creates a new file with the name specified in the input. It uses the fopen() function to create the file.
9.  `process_user_input()`: This function processes user input and calls the appropriate function based on the command specified in the input.
10. `welcomeMsg()`: This function prints the project title and students information.

### Challenges:

The primary challenge encountered during this project was the implementation in the C programming language. While it would have been easier to use a higher-level language like Python or Node.js, C presented significant difficulties. Although the developer had experience with Node.js, using C was particularly challenging and difficult.

One of the major challenges encountered was the inability to use libraries such as `<unistd.h>` and `<dirent.h>` because they are not supported by Windows and Visual Studio 2022. Consequently, the System function had to be used in some parts of the implementation.

Another challenge was memory management. The program kept throwing errors related to memory problems, and the team could not resolve them. Ultimately, a completely new code had to be implemented. These problems would not have arisen in high-level languages due to their automatic memory management capabilities.

## Results and Discussion:

### Summary of the results achieved

The code provides the user with an interactive command-line interface. The user can execute basic commands such as changing the current working directory, listing the contents of the current directory, displaying the contents of a file, removing a file or directory, creating a new directory, and creating a new file. The user can also clear the console screen.

### Discussion of limitations or areas for improvement

The current implementation of the command-line shell application has a few limitations. The application does not support all the features that are available in a typical command-line interface, such as command history, command line editing, and wildcard expansion. The application also lacks error handling mechanisms, which may result in undefined behavior if the user enters invalid input. Additionally, the application has limited support for cross-platform functionality, as it uses Windows API functions that are not available on other operating systems.

To improve the application, we can add support for command-line editing and command history. This can be achieved by using third-party libraries such as GNU Readline. The application can also implement error handling mechanisms to handle invalid input from the user and prevent undefined behavior. Moreover, to improve cross-platform functionality, we can use cross-platform libraries like libuv or implement platform-specific code paths to support different operating systems.

### Relating results to project objectives and significance

The developed command-line shell application fulfills its intended objective of providing the user with an interactive command-line interface that can execute basic commands. The application's significance lies in its ability to provide a simple, lightweight, and easy-to-use alternative to traditional graphical user interfaces. Command-line interfaces are widely used in programming, system administration, and automation tasks, and this application can help users become more productive and efficient in their work. By providing users with a simple and intuitive interface, this application can reduce the learning curve and make command-line tools more accessible to a wider audience.

## Conclusion

### Summary of the Project and its Outcomes

The project aimed to build a simple command-line shell application that supports basic commands like cd, ls, cat, rm, mkdir, and touch. The program allows the user to interact with the file system and perform operations such as changing directories, listing files, creating files and directories, removing files and directories, and displaying file contents. The project successfully achieves these goals and provides a basic command-line interface to interact with the file system.

### Highlighting the main contributions and achievements

The program can change the current directory to the specified path, list all files in the current directory, display the contents of a file, create directories and files, and remove files and directories. The program uses the standard libraries provided by C and Windows API functions such as GetFileAttributes, CreateDirectory, and DeleteFile to perform these operations. The program is well-structured and easy to understand, making it easy to modify and extend.

### Discussion of potential future work

Several features can be added to the program to improve its functionality and usability. For example, the program could support wildcards in the ls and rm commands, allowing the user to select multiple files and directories at once. Additionally, the program could include more advanced commands, such as file copying, moving, and searching. Furthermore, the program could support environment variables to make it more flexible and customizable. Overall, the project provides a good starting point for building a more comprehensive command-line shell application.
