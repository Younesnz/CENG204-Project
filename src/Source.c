#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <windows.h>

#define PATH_MAX 4096

char* getCWD(void);
void printCWD(void);
void list_dir(const char*);
void ListDirectoryContents(const char*);
void listFiles();

void welcomeMsg(void);
void printLine(int);

char* currentDir;

int main(void) {

    currentDir = getCWD();

	welcomeMsg();
    printCWD();
    listFiles();
    getchar();
	return 0;
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
    char* cwd = getCWD();
    char command[MAX_PATH + 6];  // MAX_PATH + length of "dir /b " and null terminator
    char buffer[4096];
    FILE* fp;

    // Build the command string
    sprintf_s(command, MAX_PATH + 6, "dir /b /a \"%s\"", cwd);

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
	printf("\nPress Any Key to Start the CLI >> ");
	getchar();
	system("cls");
	return;
}

void printLine(int count) {
	printf("\n");
	for (int i = 0;i < count;i++) printf("-");
	printf("\n");
}
