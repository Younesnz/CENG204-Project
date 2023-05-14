#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <windows.h>
#include <io.h>

#define PATH_MAX 4096


char* getCWD(void);
void printCWD(void);
void list_dir(const char*);
void ListDirectoryContents(const char*);
void listFiles();
void change_directory(char*);
void cat(char*);
void remove_file(const char*);
void process_user_input(char*);

void welcomeMsg(void);
void printLine(int);

char* currentDir;

int main(void) {

    currentDir = getCWD();

	welcomeMsg();
    
    // read user input from command line and process it
    char input[1024];
    while (1) {
        printCWD();
        printf("Enter Your Command (ls, cd, cat)\n > ");
        fgets(input, sizeof(input), stdin);

        // remove newline character from user input
        input[strcspn(input, "\n")] = 0;

        process_user_input(input);
    }

    getchar();
	return 0;
}
void process_user_input(char* input) {
    // check if the input starts with "cd"
    if (strncmp(input, "cd", 2) == 0) {
        // extract the directory path from the input string
        char* dir_path = input + 3;  // skip the "cd " prefix

        // call the change_directory function with the directory path
        change_directory(dir_path);
    }
    // check if the input starts with "ls"
    else if (strncmp(input, "ls", 2) == 0) {
        listFiles();
    }
    // check if the input starts with "cat"
    else if (strncmp(input, "cat", 3) == 0) {
        // extract the filename from the input string
        char* filename = input + 4;  // skip the "cat " prefix

        // call the cat function with the filename
        cat(filename);
    }
    // check if the input starts with "rm"
    else if (strncmp(input, "rm", 2) == 0) {
        // extract the file or directory path from the input string
        char* path = input + 3; // skip the "rm " prefix

        // call the rm function with the path
        remove_file(path);
    }
    else {
        // handle other commands here
        printf("Unsupported command\n");
    }
}


void printCWD() {

    if (currentDir != NULL) {
        printf("\n Current directory:");
        printLine(strlen(currentDir) + 5);
        printf(" %s", currentDir);
        printLine(strlen(currentDir) + 5);
    }
    else {
        printf("Failed to get current directory\n");
    }
}
char* getCWD() {
    char* buffer = NULL;
    size_t size = PATH_MAX;
    size_t len;

    for (;;) {
        buffer = realloc(buffer, size);
        if (buffer == NULL) {
            perror("Error allocating memory for current directory");
            return NULL;
        }
        if (getcwd(buffer, size) != NULL) {
            len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '/') {
                buffer[len - 1] = '\0';
            }
            return buffer;
        }
        if (errno != ERANGE) {
            perror("Error getting current directory");
            free(buffer);
            return NULL;
        }
        size *= 2;
    }
}

//void listFiles() {
//    char* cwd = getCWD();
//    char command[MAX_PATH + 6];
//
//    sprintf_s(command, MAX_PATH + 6, "dir /b \"%s\"", cwd);
//    system(command);
//}
void listFiles() {
    char command[MAX_PATH + 6];  // MAX_PATH + length of "dir /b " and null terminator
    char buffer[4096];
    FILE* fp;

    // Build the command string
    sprintf_s(command, MAX_PATH + 6, "dir /b /a \"%s\"", currentDir);

    // Open a pipe to the command prompt and execute the command
    fp = _popen(command, "r");
    if (fp == NULL) {
        printf("Error executing command\n");
        return;
    }

    // Print the files and directories separately
    char* p;
    while (fgets(buffer, sizeof(buffer), fp)) {
        // Remove trailing newline character
        if ((p = strchr(buffer, '\n')) != NULL) {
            *p = '\0';
        }

        // Check if the current item is a file or directory
        DWORD fileAttr = GetFileAttributesA(buffer);
        if (fileAttr != INVALID_FILE_ATTRIBUTES) {
            if (fileAttr & FILE_ATTRIBUTE_DIRECTORY) {
                printf(" >  %-7s %s\n", "Dir:", buffer);
            }
            else {
                printf(" * %-8s %s\n", "File:", buffer);
            }
        }
    }

    // Close the pipe
    _pclose(fp);
}

void change_directory(char* dir_path) {
    char newDir[MAX_PATH] = "";

    // if the user input is "..", move up one directory
    if (strcmp(dir_path, "..") == 0) {
        char* last_slash = strrchr(currentDir, '\\');
        if (last_slash != NULL) {
            *last_slash = '\0';
        }
        return;
    }

    // get the full path of the target directory
    if (_fullpath(newDir, dir_path, MAX_PATH) == NULL) {
        fprintf(stderr, "Error: could not get full path for directory '%s'\n", dir_path);
        return;
    }

    // check if the target directory exists and is a directory
    if (_chdir(newDir) != 0) {
        fprintf(stderr, "Error: could not change directory to '%s'\n", newDir);
        return;
    }

    // update the global variable with the new current directory
    if (_getcwd(currentDir, MAX_PATH) == NULL) {
        fprintf(stderr, "Error: could not get current directory\n");
        exit(1);
    }
}

void cat(char* filename) {
    FILE* file = NULL;
    errno_t err;

    err = fopen_s(&file, filename, "r");
    if (err != 0 || file == NULL) {
        printf("Error: could not open file \"%s\"\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void remove_file(const char* filename) {
    char cmd[1024];
    sprintf_s(cmd, sizeof(cmd), "del /q \"%s\"", filename);
    int status = system(cmd);
    if (status == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    }
    else {
        printf("Error deleting file '%s'.\n", filename);
    }
}

//void change_directory(char* dir_path) {
//    char newDir[MAX_PATH];
//
//    // if the user input is "..", move up one directory
//    if (strcmp(dir_path, "..") == 0) {
//        char* last_slash = strrchr(currentDir, '\\');
//        if (last_slash != NULL) {
//            *last_slash = '\0';
//        }
//        return;
//    }
//
//    // concatenate the target directory with the current directory to get the full path
//    snprintf(newDir, sizeof(newDir), "%s\\%s", currentDir, dir_path);
//
//    // check if the target directory exists
//    WIN32_FIND_DATA findData;
//    HANDLE handle = FindFirstFile(newDir, &findData);
//    if (handle == INVALID_HANDLE_VALUE) {
//        fprintf(stderr, "Error: directory '%s' does not exist\n", newDir);
//        return;
//    }
//    FindClose(handle);
//
//    // change the current directory to the target directory
//    if (SetCurrentDirectory(newDir) == 0) {
//        fprintf(stderr, "Error: could not change directory to '%s'\n", newDir);
//        return;
//    }
//
//    // update the global variable with the new current directory
//    if (GetCurrentDirectory(sizeof(currentDir), currentDir) == 0) {
//        fprintf(stderr, "Error: could not get current directory\n");
//        exit(1);
//    }
//}

//void listFiles()
//{
//    char* cwd = getCWD();
//
//    // Remove trailing backslash if it exists
//    size_t len = strlen(cwd);
//    if (len > 0 && cwd[len - 1] == '\\') {
//        cwd[len - 1] = '\0';
//    }
//
//    WIN32_FIND_DATA findData;
//    HANDLE hFind = INVALID_HANDLE_VALUE;
//
//    char searchPath[MAX_PATH];
//    _snprintf_s(searchPath, MAX_PATH, MAX_PATH, "%s\\*", getCWD());
//
//    printf("Search path: %s\n", searchPath);
//
//    hFind = FindFirstFile(searchPath, &findData);
//    if (hFind == INVALID_HANDLE_VALUE) {
//        DWORD dwError = GetLastError();
//        printf("Error %d opening directory %s\n", dwError, cwd);
//        return;
//    }
//
//
//    do {
//        if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
//            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
//                printf("<DIR>\t%s\n", findData.cFileName);
//            }
//            else {
//                printf("\t%s\n", findData.cFileName);
//            }
//        }
//    } while (FindNextFile(hFind, &findData) != 0);
//
//    DWORD dwError = GetLastError();
//    if (dwError != ERROR_NO_MORE_FILES) {
//        printf("Error listing files in directory %s\n", cwd);
//    }
//
//    FindClose(hFind);
//}

//void list_dir(const char* path) {
//    WIN32_FIND_DATA find_data;
//    HANDLE hFind;
//
//    char search_path[MAX_PATH+2];
//    snprintf(search_path, MAX_PATH+2, "%s\\*", path);
//
//    hFind = FindFirstFile(search_path, &find_data);
//    if (hFind == INVALID_HANDLE_VALUE) {
//        DWORD error_code = GetLastError();
//        printf("Failed to open directory: %s\n", path);
//        printf("Error code: %lu\n", error_code);
//        return;
//    }
//
//    do {
//        printf("%s\n", find_data.cFileName);
//    } while (FindNextFile(hFind, &find_data) != 0);
//
//    DWORD error_code = GetLastError();
//    if (error_code != ERROR_NO_MORE_FILES) {
//        printf("Failed to iterate through directory: %s\n", path);
//        printf("Error code: %lu\n", error_code);
//    }
//
//    FindClose(hFind);
//}


void welcomeMsg(void) {
	char* names[] = { "Younes Nourzehi", "Faraz Azarmi", "Nazanin Haghdoust Talebinejad", "Rania M.S. Alshemarti" };
	char* sNums[] = { "210201910", "200201928", "200201929","210201911" };

	printf("\n CENG204 Term Project");
	printLine(35);
	printf(" Command line shell application");
	printLine(35);
	printf("\n %-32s %s", "Group Member", "Student Number");
	printLine(50);
	for (int i = 0; i < 4; i++) {
		printf(" %-32s %s\n", names[i], sNums[i]);
	}
	printf("\nPress ENTER to Start the CLI >> ");
	getchar();
	system("cls");
	return;
}

void printLine(int count) {
	printf("\n");
	for (int i = 0;i < count;i++) printf("-");
	printf("\n");
}
