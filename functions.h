#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct Node {
    char address[256];
    struct Node *next;
};

int makeChoice();

struct Node makeNode(char str[], char * buffer);

// reader function 
void reader(char * address, char * buffer);
// end game function
// picture implementation function

#endif