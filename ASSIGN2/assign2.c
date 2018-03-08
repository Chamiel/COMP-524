#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//node struct for binary tree data structure
struct node {
  char* name;
  char* str; //storing full input string for freeing later
  struct node* father;
  struct node* mother;
};

//function to construct a node
struct node* newNode(char* name, char* str) {
  //allocate memory
  struct node* node = (struct node*)malloc(sizeof(struct node));
  
  node->name = name;
  node->father = NULL;
  node->mother = NULL;
  node->str = str;
  return node;
}

void add();
void delete();
void deleteTree(struct node* child);
struct node* find(char* name, struct node* child);
void print();

struct node *root;
int quit;

int main() {
  //get input
  char* name = malloc(20*sizeof(char));
  printf("Please enter your name :");
  fgets(name, 20, stdin);
  name[strcspn(name, "\n")] = '\0'; //have to edit \n out of input from fgets so strcmp works later

  //initialize a root
  root = newNode(name, name);
  
  quit = 0;
  char* input = malloc(20*sizeof(char));
  //loop until termination
  while(!quit) {
    printf("Please specify whether to add or delete an entry, or print the tree\n");
    fgets(input, 20, stdin);
    input[strcspn(input, "\n")] = '\0';

    //terminate if quit
    if (strcmp(input, "quit") == 0) {
      quit = 1;
      break;
    }

    // call functions depending on input
    if (strcmp(input, "add") == 0) {
      add();
    }
    else if (strcmp(input, "delete") == 0) {
      delete();
    }
    else if (strcmp(input, "print") == 0) {
      printf("\n");
      print(root, 0);
      printf("\n");
    }
    else
      printf("invalid command\n");
  }
  printf("Program Terminating\n");
  //free everything leftover before termination of program
  deleteTree(root);
  free(input);
  input = NULL;
}

//recurse to find node with name
struct node* find(char* name, struct node* child) {
  if (!child) {
    return NULL;
  }
  if (strcmp(name, child->name) == 0) {
    return child;
  }
  struct node* mother = find(name, child->mother);
  if (mother) {
    if (strcmp(name, mother->name) == 0)
      return mother;
  }
  struct node* father = find(name, child->father);
  if (father) {
    if (strcmp(name, father->name) == 0)
      return father;
  }
  return NULL;
}

//recurse to find descendent of node with name
struct node* findKid(char* name, struct node* child, struct node* node) {
  if (!node)
    return NULL;
  struct node* mother = NULL;
  struct node* father = NULL;
  if (strcmp(name, node->name) == 0)
    return child;
  else if (child && strcmp(name, child->name) == 0)
    return NULL;
  else {
    mother = findKid(name, node, node->mother);
    father = findKid(name, node, node->father);
  }
  if (mother)
    return mother;
  return father;
}

//get input and add parent to tree
void add() {
  char* input = malloc(100*sizeof(char));
  printf("Please specify a relation to add\n");
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = '\0';

  //check if quit
  if (strcmp(input, "quit") == 0){
    quit =1;
    free(input);
    return;
  }

  //parse input
  char* a = strchr(input,'(');
  char* b = strchr(input,',');
  if (!a||!b) {
    printf("invalid relationship\n");
    free(input);
    return;
  }
  char* relation = strtok(input, "(");
  char* parent = strtok(NULL, ",");
  char* child = strtok(NULL, ")");

  //call find to check if child is valid, if not print error
  struct node* ch = find(child, root);
  if (!ch) {
    printf("name not found\n");
    free(input);
    add();
  }

  // if input is incorrect print error message
  else if (strcmp(relation, "father") != 0 && strcmp(relation, "mother") !=0) {
    printf("invalid relationship\n");
    free(input);
    add();
  }

  //check whether relationship exists, if not then add to tree
  else {
    struct node *par = newNode(parent, input);
    if (strcmp(relation, "father") == 0) {
      if (ch->father != NULL) {
        printf("relationship already exists\n");
        free(input);
        add();
      }
      else {
        ch->father = par;
      }
    }
    else if (strcmp(relation, "mother") == 0) {
      if (ch->mother != NULL) {
        printf("relationship already exists\n");
        free(input);
        add();
      }
      else
        ch->mother = par;
    }
  }
}


//get input for delete, then deallocate/free nodes
void delete() {
  printf("Please specify the name to delete\n");
  char* input = malloc(13*sizeof(char));
  fgets(input, 13, stdin);
  input[strcspn(input, "\n")] = '\0';
  if (strcmp(input, "quit") == 0) {
    quit = 1;
    free(input);
    return;
  }

  //find node and parent node
  struct node* delete = find(input, root);
  struct node* del = findKid(input, NULL, root);
  if (!delete) {
    printf("name not found\n");
    return;
  }

  //deallocate descendant pointers
  if (del->mother && strcmp(input, del->mother->name) == 0) {
    del->mother = NULL;
  }
  if (del->father && strcmp(input, del->father->name) == 0) {
    del->father = NULL;
  }

  //if leaf free otherwise delete tree
  if (!delete->mother && !delete->father) {
    free(delete->str);
    delete->name = NULL;
    delete->str = NULL;
    free(delete);
    del = NULL;
  }
  else
    deleteTree(delete);
  free(input);
}

//recursively free tree of nodes if not leaf
void deleteTree(struct node* child) {
  if (child) {
    if (child->mother)
      deleteTree(child->mother);
    if (child->father)
      deleteTree(child->father);
    free(child->str);
    child->name = NULL;
    child->str = NULL;
    child->mother = NULL;
    child->father = NULL;
    free(child);
    child = NULL;
  }
}

//recursively print tree, with counter for tabs
void print(struct node* child, int i) {
  if (!child)
    return;
  int a = i;
  for (a;a>0;a--) {
    printf("\t");
  }
  printf("%s\n", child->name);
  print(child->father, i+1);
  print(child->mother, i+1);
}
