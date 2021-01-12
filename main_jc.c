#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct Node {
  char *address;
  char *msg;
  struct Node *choice1;
  struct Node *choice2;
  struct Node *choice3;
};


int main() {
    struct Node root;
    root.address = "0";
    char buffer[5000];
    int fd = open("story.txt", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    close(fd);


    char *x = strstr(buffer, "0");
    x++;

    int i;
    for(i = 0; x[i] != '|'; i++){
        printf("%c", x[i]);
    }
    x++;
    int k;
    for (k = 0; k < 3; k ++){
      for(; x[i] != '|'; i++){
        printf("%c", x[i]);
      }
      x++;
    }

    /*
    while (*x != '('){
        printf("%s",x);
        x++;
        sleep(5);
    }*/

  //  printf("%s", buffer);

  //while(1) {
 // }
  return 0;
}