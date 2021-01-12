#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct Node {
    char address[256];
    struct Node *next;
};

int makeChoice();

struct Node makeNode(char str[]);

// reader function 
// end game function
// picture implementation function

#endif