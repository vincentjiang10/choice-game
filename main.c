#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include "functions.h"
#include <fcntl.h>
#include <unistd.h>

/** reads and returns the text from story.txt at address
char * reader(char *address);
**/

// code which makes the choice (takes in stdin int)
int makeChoice() {
    printf("Input choice #: ");
    char choice [10];
    fgets(choice, sizeof(choice), stdin);
    while (atoi(choice) < 1 || atoi(choice) > 3) {
        printf("Input invalid. Please try again: ");
        fgets(choice, sizeof(choice), stdin);
    }
    return atoi(choice);
}

// prints the text from story.txt at address
void reader(char * address, char * buffer){
    char *x = strstr(buffer, address);
    x+=strlen(address);

    int i;
    for(i = 0; x[i] != '|'; i++){
        printf("%c", x[i]);
    }
    printf("\n");
}

struct Node makeNode(char str [256], char * buffer) {
    struct Node node;
    strcpy(node.address, str);
    printf("address: %s\n", node.address);
    reader(node.address, buffer);
    int len = strlen(str);
    if (len == 10) exit(0); // for now it's exit, but we can add a special function (endgame()) that ends the game
    char add[256], choice[10];
    strcpy(add, str);
    sprintf(choice, "%d", makeChoice());
    strcat(add, choice);
    makeNode(add, buffer);
}

int main() {
    // loads in story.txt into a buffer
    char buffer[5000];
    int fd = open("story.txt", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    // at the start, check with user whether he wants to load a save file
    // start at root (new game) if not
    struct Node root = makeNode("0", buffer);
    // start at the checkpoint if yes
    // struct Node save = makeNode(address) // address is imported from save file function
  
    return 0;
}