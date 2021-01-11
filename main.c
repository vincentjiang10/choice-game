#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>

struct Node {
  char *address;
  char *msg;
  Node choice1;
  Node choice2;
  Node choice3;
};

Node makeChoice(char *address) {

}

Node makeNode(char *address, char *msg) {
  struct Node node;
  node.address = address;
  node.msg = msg;
  node.choice1 = makeChoice(address);
}

int main() {
  struct Node root = makeNode("0", "test");
  


  while(1) {
  }
  return 0;
}
