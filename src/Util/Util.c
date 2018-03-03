#include <stdio.h>
#include <stdlib.h>

const char* readFileToString(const char* filePath) {
    FILE* filePointer;
    filePointer = fopen(filePath, "r");

    if(filePointer == NULL) {
        perror("Error");
    }

    //move the file pointer to the end of the file and determine it's length
    fseek(filePointer, 0, SEEK_END);
    long fileLength = ftell(filePointer);

    fseek(filePointer, 0, SEEK_SET);
    char* fileContents = malloc(sizeof(fileContents[0]) * (fileLength + 1));

    //zero memory
    for (int i=0; i < fileLength + 1; i++){
        fileContents[i] = 0;
    }
    //read the file
    fread(fileContents, 1, fileLength, filePointer);

    //add end of string
    fileContents[fileLength + 1] = '\0';
    fclose(filePointer);

    return fileContents;
}
