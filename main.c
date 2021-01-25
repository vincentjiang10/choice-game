#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "functions.h"

char currentaddress[256]; // To keep track of what node we're currently at.
int autosave = 0; // If 0, then autosave is off. If 1, then autosave is on.
time_t starttime = 0; // Start time (epoch time)

// Function to save the game.
void saveGame() {
  int fd = open("savefile.txt", O_CREAT | O_WRONLY, 0644);
  printf("Saved Game!\n");
  write(fd, currentaddress, sizeof(currentaddress));
  close(fd);
}

// Function to autosave. Basically saveGame() but without the text prompts. (It happens in the background).
void autoSave() {
  int fd = open("savefile.txt", O_WRONLY);
  write(fd, currentaddress, sizeof(currentaddress));
  close(fd);
}

// Function to ask the player if they have installed ImageMagick.
void promptImageMagick() {
  printf("\nNOTE: WSL users may have to run this program through ssh (i.e. via PuTTY and enabling X11 forwarding) and install an X server (i.e. Xming)\n");
  printf("Linux/MacOS users usually have an inbuilt X server: able to run this program right away\n");
  printf("\nNOTE: make sure to install ImageMagick before running this program\n");
  printf("To install: $ sudo apt-get install imagemagick\n");
  printf("Have you installed ImageMagick? (y/n)\n");
  char response[10];
  sigs();
  fgets(response, sizeof(response), stdin);

  char * promptResponse = trim(response);

  // If the player types anything other than 'y' or 'n'
  if (strcmp(promptResponse, "y\n")&&strcmp(promptResponse, "n\n")) {
    while (strcmp(promptResponse, "y\n")&&strcmp(promptResponse, "n\n")) {
      if (!strcmp(promptResponse, "help\n")) {
        help();
        printf("\nHave you installed ImageMagick? (y/n)\n");
      }
      else {
        printf("Invalid input. Type 'y' or 'n'.\n");
        sigs();
        fgets(response, sizeof(response), stdin);
        promptResponse = trim(response);
      }
    }
  }

  // If the player types 'n'
  else if (promptResponse[0] == 'n') {
    printf("\nPlease install ImageMagick to run this program\n");
    printf("You can remove ImageMagick after using: $ sudo apt-get remove imagemagick\n");
    exit(0);
  }
}

// Function to prompt the player if they want to enable autosave. Enables autosave if desired.
void promptAutosave() {
  char response[256];
  sigs();
  fgets(response, sizeof(response), stdin);
  char * promptResponse = trim(response); 

  // If the player types anything other than 'y' or 'n'
  if (strcmp(promptResponse, "y\n")&&strcmp(promptResponse, "n\n")) {
    while (strcmp(promptResponse, "y\n")&&strcmp(promptResponse, "n\n")) {
      if (!strcmp(promptResponse, "help\n")) {
        help();
        printf("\nWould you like to enable autosave? (y/n)\n");
      }
      else {printf("Invalid input. Type 'y' or 'n'.\n");}
      sigs();
      fgets(response, sizeof(response), stdin);
      promptResponse = trim(response);
    }
  }

  // If the player types 'y', enable autosave.
  if (promptResponse[0]=='y') {
    autosave = 1;
    printf("Autosave enabled.\n\n");
  }

  // If the player types 'n', disable autosave.
  if (promptResponse[0]=='n') {
    printf("Autosave disabled.\n\n");
  }
}

// Function to prompt the player if they want to load a savefile.
void promptLoadfile(char *buffer, char *buffer2) {
  char response[256];
  sigs();
  fgets(response, sizeof(response), stdin);
  char * promptResponse = trim(response);

  // If the player types anything other than 'y' or 'n'
  if (strcmp(promptResponse, "y\n")&&strcmp(promptResponse, "n\n")) {
    while (strcmp(promptResponse, "y\n")&&strcmp(promptResponse, "n\n")) {
      if (!strcmp(promptResponse, "help\n")) {
        help();
        printf("\nWould you like to load in a saved file? (y/n)\n");
      }
      else {printf("Invalid input. Type 'y' or 'n'.\n");}
      sigs();
      fgets(response, sizeof(response), stdin);
      promptResponse = trim(response);
    }
  }

  char address[10];

  // If the player types 'y', attempt to load the savefile.
  if (promptResponse[0]=='y') {
    printf("\nLooking for save file...\n");
    int fd = open("savefile.txt", O_RDONLY);
    read(fd, address, sizeof(address));
    close(fd);

    // If savefile.txt doesn't start with E, then a save file exists.
    if (address[0]!='E') {
      struct stat sb;
      stat("./savefile.txt", &sb);
      printf("Found save file, last saved on: %s", ctime(&(sb.st_mtime)));
      printf("Loading from last saved checkpoint...\n");
    }

    // If savefile.txt starts with E, then no save file exists.
    else {
      printf("You have no save file. Loading from beginning of the game...\n");
    }
  }

  printf("\nStarting game...\n");
  
  // If the player types 'n', then the program automatically comes here.
  address[0] = '0'; // If savefile.txt only had an 'E', then this replaces that 'E' with a '0'.
                    // If savefile.txt had a save file, then this wouldn't change anything.
  struct Node node = makeNode(address, buffer, buffer2); // Load in the game.
}

int main();

void promptRestart(char * buffer, char * buffer2) {

  printf("Would you like to restart the game? (y/n)\n");
  char response[10];
  sigs();
  fgets(response, sizeof(response), stdin);
  char * promptResponse = trim(response);

  // If the player types anything other than 'y' or 'n'
  if (strcmp(promptResponse, "y\n")&&strcmp(promptResponse, "n\n")) {
    while (strcmp(promptResponse, "y\n")&&strcmp(promptResponse, "n\n")) {
      if (!strcmp(promptResponse, "help\n")) {
        help();
        printf("\nWould you like to restart the game? (y/n)\n");
      }
      else {
        printf("Invalid input. Type 'y' or 'n'.\n");
        sigs();
        fgets(response, sizeof(response), stdin);
        promptResponse = trim(response);
      }
    }
  }

  else if (promptResponse[0] == 'y') {
    printf("\n-----------------------\n");
    main();
  }

  // If the player types 'n'
  else exit(0);

}

// print and summarize features
void help() {
  printf("------------------------------------------\n");
  printf("type \"quit\" or \"exit\" to quit the game\n");
  printf("type \"back\" to move back to last scene\n");
  printf("type \"save\" or \"Ctrl \\\" to save the game at current scene\n");
  printf("type \"Ctrl C\" or \"Ctrl Z\" to quit the game\n");
  printf("type \"replay\" to replay current scene\n");
  printf("type \"restart\" to restart the game\n");
  printf("type \"rm-auto\" to remove autosave\n");
  printf("type \"prompts\" to disable or enable prompts at the beginning of program\n");
  printf("--------------------------------------------\n");
}

char * trim(char * input) {
  char *output = malloc(sizeof(char)*256);
  int i;
  int j = 0;
  for (i = 0; input[i]; i++) {
    if (input[i]!=' ') {
      output[j] = input[i];
      j++;
    }
  }
  return output;
}

// function which makes the choice (takes in stdin int)
int makeChoice(int numChoice) {
    printf("Input choice #: ");
    char input [256];
    sigs();
    fgets(input, sizeof(input), stdin);

    // trims input and gets rid of leading and trailing whitespace
    char * choice = trim(input);

    // If the player types 'restart'
    if (!strcmp(choice, "restart\n")) {
      printf("Are you sure you want to start from the beginning? (y/n)\n");
      sigs();
      fgets(choice, sizeof(choice), stdin);
      if (choice[0] == 'y') return 0;
      else {return makeChoice(numChoice);}
    }

    // If the play types "rm autosave"
    else if (!strcmp(choice, "rm-auto\n")) {
      printf("Autosave removed!\n");
      autosave = 0;
      return makeChoice(numChoice);
    }

    // If the player types 'help'
    else if (!strcmp(choice, "help\n")) {
      help();
      return makeChoice(numChoice);
    }

    // If the player types 'quit'
    else if (!strcmp(choice, "quit\n") || !strcmp(choice, "exit\n")) {
      printf("\nHope you had fun!\n");
      display("00");
      exit(0);
    }

    // If the player types 'save'
    else if (!strcmp(choice, "save\n")) {
      saveGame();
      return makeChoice(numChoice);
    }

    // If the player types 'back'
    else if (!strcmp(choice, "back\n")){
      if (!strcmp(currentaddress, "0")) {
        printf("Can't go back. You're at the beginning!\n");
        return makeChoice(numChoice);
      }
      else return atoi("10");
    }

    else if (!strcmp(choice, "replay\n")) return atoi("9");

    // If the player types 'prompts'
    else if (!strcmp(choice, "prompts\n")) {
      sigs();
      int fd = open("prompts.txt", O_CREAT | O_WRONLY, 0644);
      printf("\nWhich prompts do you want?\n");
      printf("Type in 3 digits. 0 means the prompt is off. 1 means it's on.\nThe first digit corresponds to the ImageMagick prompt, etc.\n");
      fgets(choice, sizeof(choice), stdin);
      int i;
      for (i = 0; i < 3; i++) {
        while (choice[i] != '1' && choice[i] != '0') {
          printf("Invalid input. Only use 1s and 0s.\n");
          sigs();
          fgets(choice, sizeof(choice), stdin);
        }
      }
      write(fd, choice, sizeof(choice));
      close(fd);
      return makeChoice(numChoice);
    }

    else {
      while (atoi(choice) < 1 || atoi(choice) > numChoice) {
          printf("Input invalid. Please try again.\n");
          return makeChoice(numChoice);
      }
    }

    return atoi(choice);
}

// returns whether there is a picture file at address
// also determines whether address is a terminating case
char reader0(char * address, char * buffer) {
  char add[256];
  strcpy(add, address);
  strcat(add, " ");
  char *x = strstr(buffer, add);
  x+=strlen(add);
  return x[0];
}

// prints the text from story.txt at address
void reader(char * address, char * buffer){
    char add [256];
    strcpy(add, address);
    strcat(add, " ");
    char *x = strstr(buffer, add);
    x+=strlen(add);
    int i; for (i = 0; x[i] != '|'; x++); x++;
    int k; for (k = 0; x[k] != '|'; k++) printf("%c", x[k]);
    printf("\n");
}

// second reader; returns the number of choices at address
int reader2(char * address, char * buffer) {
    char add [256];
    strcpy(add, address);
    strcat(add, " ");
    char *x = strstr(buffer, add);
    x+=strlen(add);
    int i; for (i = 0; x[i] != ':'; x++); x++;
    return atoi(x);
}

static void sighandler(int signo){
    if (signo == SIGQUIT) {
      printf("\n");
      saveGame();  // Ctrl + "\"
      printf("Input choice #: \n");
    }
    if (signo == SIGINT || signo == SIGTERM || signo == SIGTSTP) {
      printf("\nHope you had fun!\n");
      display("00");
      exit(0);
    }
}

void sigs() {
  signal(SIGQUIT, sighandler);
  signal(SIGINT, sighandler);
  signal(SIGTERM, sighandler);
  signal(SIGTSTP, sighandler);
}

char ** parse_args(char * line) {
  char **args = malloc(sizeof(char*)*100);
  char *p = line;

  int i;
  for (i=0; p!=NULL; i++) {
    args[i] = strsep(&p, " ");
  }
  args[i] = NULL;
  return args;
}

// function for displaying images
void display(char * address) {
  char buffer[1000];
  int fd = open("pictureAddress.txt", O_RDONLY);
  read(fd, buffer, sizeof(buffer));
  close(fd);
  char add[256];
  strcpy(add, address);
  strcat(add, " ");
  char *x = strstr(buffer, add);
  x+=strlen(add);
  int j;
  for (j = 0; x[j] != ':'; x++); x++;
  char picAddress[50];
  j = 0;
  int i; for (i = 0; x[i] != '|'; x++) {
    picAddress[j] = x[i];
    j++;
  }
  char line[256] = "display -resize 500x500 pics/";
  strcat(line, picAddress); strcat(line, ".jpg");
  char **args = parse_args(line);
  execvp(args[0], args);
}

// helper function for checkConvergence() - looks for the rightmost address of a converging Node
int helper(char * str) {
  char *str2 = strchr(str, '|');
  int i = (int)(str2- str);
  for (i; str[i]!=','; i--);
  return i+1;
}

// function to check for convergence and return a new address if applicable
char * checkConvergence(char * buffer) {
  char *str = strstr(buffer, currentaddress);
  int i = strlen(currentaddress)+1;

  if (str[i]=='W'||str[i]=='L'||str[i]=='Q') i++;

  // If there's no comma, then there's no convergence needed.
  if (str[i]!=',') {
    return "noconvergence";
  }

  // Else, converge addresses.
  char *newaddress = malloc(sizeof(char)*256);
  i = helper(str);
  int j = 0;
  for (i; str[i]!=' '; i++) {
    newaddress[j] = str[i];
    j++;
  }
  return newaddress;
}

// Endgame function. Prints whether the player won or not & calculates their playtime.
void endgame(int winorloss) {
  if (winorloss) { // If the player won
    printf("\nCongratulations, you won!\n");
  }
  else { // If the player lost
    printf("\nAww, you lost!\n");
  }
  time_t playtime = time(NULL) - starttime;
  int hr = (playtime/3600);
  int	min = (playtime -(3600*hr))/60;
  int sec = (playtime -(3600*hr)-(min*60));

  printf("Your playtime was ");
  if (hr==1) printf("1 hour, ");
  else if (hr>1) printf("%d hours, ", hr);
  if (min==1) printf("1 minute, ");
  else if (min>1) printf("%d minutes, ", min);
  else if (hr>0) printf("0 minutes, ");
  if (sec==1) printf("1 second!\n\n");
  else if (sec>1) printf("%d seconds!\n\n", sec);
  else printf("0 seconds!\n\n");
}

// makes node and links to next node recursively
struct Node makeNode(char str [256], char * buffer, char * buffer2) {
    if (!starttime) starttime = time(NULL); // Set start time.
  
    struct Node node;
    strcpy(node.address, str);
    strcpy(node.prev, currentaddress);

    strcpy(currentaddress, node.address); // Sets the "currentaddress" (global String) to this node's address.

    // Checks for convergence:
    char *potentialnewaddress = checkConvergence(buffer);
    if (strcmp(potentialnewaddress, "noconvergence")) { // If there is convergence...
      strcpy(currentaddress, potentialnewaddress);
      strcpy(node.address, potentialnewaddress);
    }

    if (autosave) autoSave();
    
    reader(node.address, buffer);

    
    if ('y' == reader0(node.address, buffer2)) {
      int f, status;
      f = fork();
      // child process displaying images
      if (!f) {
        display(node.address);
      }
      // parent process waiting for child process
      else {
        int f2, status2;
        f2 = fork();
        // another child process
        if (!f2) {
          sleep(10);
          kill(f, SIGKILL);
          kill(getpid(), SIGKILL);
        }
        waitpid(f, &status, 0);
      }
    }
    // terminating case
    char letter = reader0(node.address, buffer);
    if (letter == 'L' || letter == 'W') {
      if (letter == 'W') endgame(1); // endgame with a win
      if (letter == 'L') endgame(0); // endgame with a loss
      promptRestart(buffer, buffer2);
    }

    // non-terminating case
    char add[256];
    strcpy(add, node.address);

    char choice[10];

    // reads from buffer2 the number of choices with address
    int numChoice = reader2(node.address, buffer2);
    // quick time event. If nothing is chosen, a hidden choice 4 is selected. Thus quick time scenarios must have 4 choices
    if (letter == 'Q'){
      time_t b = time(NULL);
      sprintf(choice, "%d", makeChoice(numChoice));
      time_t e = time(NULL);
      if ((e - b) > 5.0){
        sprintf(choice, "%d", 4);
      }
    }
    else {
      sprintf(choice, "%d", makeChoice(numChoice));
    }


    if (!strcmp(choice, "10")) strcpy(add,node.prev);
    else if (!strcmp(choice, "9"));
    else {strcat(add, choice);}
    if (!strcmp(choice, "0")) main();
    else {makeNode(add, buffer, buffer2);}
}

int main() {
    // loads in story.txt into a buffer
    char buffer[50000];
    int fd = open("story.txt", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    close(fd);
    // loads numChoice.txt into another buffer
    char buffer2[10000];
    int fd2 = open("numChoice.txt", O_RDONLY);
    read(fd2, buffer2, sizeof(buffer2));
    close(fd2);
     // loads prompt options (on/off)
    char buffer3[4];
    int fd3 = open("prompts.txt", O_RDONLY);
    read(fd3, buffer3, sizeof(buffer3));
    close(fd3);

    // Check if the player has installed:
    if (buffer3[0] == '1') promptImageMagick();

    printf("\nNOTE: throughout the program, pictures will be displayed for immersion\n"); 
    printf("Please exit the picture manually to continue, else the picture will exit automatically in a few seconds\n");

    printf("NOTE: type in \"help\" anytime expand program features and utilities\n");
    while (1) {
      // Autosave Prompt:
      if (buffer3[1] == '1') {
        printf("\nWould you like to enable autosave? (y/n)\n");
        promptAutosave();
      }

      // Loadfile Prompt: 
      if (buffer3[2] == '1') {
        printf("Would you like to load in a saved file? (y/n)\n");
        promptLoadfile(buffer, buffer2);
      }
      char address[256];
      address[0] = '0'; 
      struct Node node = makeNode(address, buffer, buffer2);
    }

    return 0;
  }
