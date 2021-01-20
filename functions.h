#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct Node {
    char address[256];
};

// function to save the game at any given point
void saveGame();

// function to autosave the game
void autoSave();

// function to prompt asking the player if they have installed ImageMagick
void promptImageMagick();

// function to prompt & enable/disable autosave
void promptAutosave();

// function to prompt & load in savefile
void promptLoadfile(char *buffer, char *buffer2);

// function to prompt prompt restart
void promptRestart(char *buffer, char *buffer2);

// function that trims user input
char * trim(char * input);

// function which makes the choice (takes in stdin int)
int makeChoice(int numChoice);

// helper function for checkConvergence();
int helper(char * str);

// checks for convergence and merges addresses accordingly
char * checkConvergence();

// makes node and connects to next node recursively
struct Node makeNode(char str[], char * buffer, char * buffer2);

// returns whether there is a picture file at address
// also used to determine whether the address is a terminating one
char reader0(char * address, char * buffer);

// prints the text from story.txt at address
void reader(char * address, char * buffer);

// second reader; returns the number of choices at address
int reader2(char * address, char * buffer);

// function that summarizes program features and utilities
void help();

// helper function for display()
char ** parse_args(char * line);

// displays image at address
void display(char * address);

// sighandler
static void sighandler(int signo);

// helper function that calls sighandler
void sigs();

#endif
