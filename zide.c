#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Needed for strcmp, strcat, and other string functions

// Function to read the content of a file
char* readFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file for reading.\n");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    char* content = (char*)malloc((fileSize + 1) * sizeof(char));
    fread(content, sizeof(char), fileSize, file);
    content[fileSize] = '\0';
    fclose(file);
    return content;
}

// Function to write content to a file
int writeFile(const char* filePath, const char* content) {
    FILE* file = fopen(filePath, "w");
    if (!file) {
        fprintf(stderr, "Error: Could not open file for writing.\n");
        return 0;
    }
    fputs(content, file);
    fclose(file);
    return 1;
}

// Main function to run the text editor
void textEditor() {
    printf("Welcome to Zide! Start writing here:\n");
    printf("Enter new file name: ");
    char filePath[256];
    scanf("%255s", filePath);
    
    char* content = readFile(filePath);
    if (!content) {
        content = "";
    }
    printf("Current file content:\n%s\n", content);

    printf("\nStart editing. Type ':w' to save, ':q' to exit without saving, or ':wq' to save and exit.\n");

    // Buffer for edited content
    char buffer[1024 * 1024] = ""; // 1MB buffer

    // Start editing loop
    while (1) {
        printf("> ");
        char input[256];
        scanf(" %[^\n]", input);
        
        if (strcmp(input, ":w") == 0) {
            writeFile(filePath, buffer);
            printf("File saved.\n");
        } else if (strcmp(input, ":q") == 0) {
            printf("Exiting without saving.\n");
            break;
        } else if (strcmp(input, ":wq") == 0) {
            writeFile(filePath, buffer);
            printf("File saved and exiting.\n");
            break;
        } else {
            strcat(buffer, input);
            strcat(buffer, "\n");
        }
    }
}

int main() {
    textEditor();
    return 0;
}
