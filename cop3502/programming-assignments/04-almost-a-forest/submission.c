/* COP 3502C Assignment 4
This program is written by: Thomas Hanson */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "leak_detector_c.h"

/*
 * Represents individual item nodes. These nodes
 * get inserted into each of the tree name nodes.
 */
typedef struct itemNode {
  char name[100];
  int count;
  struct itemNode *left, *right;
} itemNode;

/*
 * Represents the major tree names.
 */
typedef struct treeNameNode {
  char treeName[100];
  struct treeNameNode *left, *right;
  itemNode *theTree;
} treeNameNode;

// The output file (to be globally accessed)
FILE *outfile;

/*
 * Creation functions
 *
 * These functions are in charge of building or
 * creating each item or tree node properly. 
 */
treeNameNode* createTreeNameNode(char *name);
itemNode* createItemNode(char *name, int count);
treeNameNode* buildNameTree(treeNameNode *root, FILE *infile, int numTreeNames);

/*
 * Insertion functions
 *
 * These functions are in charge of inserting a tree
 * into the list of trees, or child node into node.
 */
treeNameNode* insertTree(treeNameNode *root, treeNameNode *tree);
itemNode* insertNode(itemNode *root, itemNode *tree);

/*
 * Search functions
 *
 * These functions are in charge of searching for a
 * specific tree or item node and then returning them.
 */
treeNameNode* searchNameNode(treeNameNode *root, char treeName[50]);
itemNode* findNode(itemNode *root, char nodeName[50]);

/*
 * Deletion functions
 *
 * These functions are in charge of properly deleting
 * a tree or node and freeing the memory.
 */
void deleteTree(treeNameNode *root, char name[50]);
itemNode* findMinValueNode(itemNode *root);
itemNode* deleteNode(treeNameNode *tree, itemNode *root, char name[50]);

/*
 * Traversal functions
 *
 * These functions simplify the process of traversing
 * through the binary tree and outputting our values.
 */
void traverse_in_traverse(treeNameNode *root);

/*
 * Command functions
 *
 * These functions are in charge of simplifying the
 * command process by adding helper functions.
 */
int itemsBefore(itemNode *root, itemNode *node);
int height(treeNameNode *tree);
int rootHeight(itemNode *root);
int isBalanced(treeNameNode* root);
int max(int a, int b);

int count(itemNode *root);

/*
 * Cleaning functions
 *
 * These functions are in charge of properly freeing any
 * leftover memory leaks in our code from trees and nodes.
 */
void cleanTreeNameNodes(treeNameNode *root);
void cleanItemNodes(itemNode *root);

/*
 * Order functions
 * 
 * These functions are in charge of making sure the values
 * are printing in order, according to the sample output.
 */
void inorder(itemNode *p);
void inorderTree(treeNameNode *p);
void printFancyOutput(treeNameNode *root);

int main(void) {

  // Leak detector
  atexit(report_mem_leak);
  
  /*
   * File management
   */
  FILE *infile = fopen("in.txt", "r");
  outfile = fopen("out.txt", "a");
  
  // Double checking
  if (!infile) {
    printf("Input file does not exist! Exiting...\n");
    exit(1);
  }
  
  // Assign starting variables
  treeNameNode *root = NULL;
  int numTreeNames = 0, numInsertItems = 0, numQueries = 0;

  fscanf(infile, "%d %d %d", &numTreeNames, &numInsertItems, &numQueries);
  char namesList[numTreeNames][8];
  
  // The root tree node (fish)
  root = buildNameTree(root, infile, numTreeNames);
  
  // The children trees
  itemNode *childItemTree = malloc(sizeof(itemNode));
  
  // Inserting all of the nodes
  for (int i = 0; i < numInsertItems; i++) {

    char childTreeName[100], parentTreeName[100];
    int childTreeCount = 0;

    fscanf(infile, "%s %s %d", parentTreeName, childTreeName, &childTreeCount);
    
    // Assign the new node to the parent tree
    treeNameNode *parentTree = searchNameNode(root, parentTreeName);
    itemNode *newNode = createItemNode(childTreeName, childTreeCount);
    
    // Assign the tree variable to the root of the item nodes
    parentTree->theTree = insertNode(parentTree->theTree, newNode);
  }
  
  // Call our traversal function
  traverse_in_traverse(root);
  
  // Handle all of our queries/commands
  for (int j = 0; j < numQueries; j++) {

    // Parent and children nodes for all commands
    treeNameNode *parentNode;
    itemNode *childNode;
    
    // Our values that we read and assign to
    char commandName[15], parentName[100], childName[100];

    fscanf(infile, "%s %s", commandName, parentName);
    
    // Search for the parent node (every command requires it)
    parentNode = searchNameNode(root, parentName);

    if (strcmp(commandName, "search") == 0) {

      fscanf(infile, "%s", childName);

      if (parentNode) {
        
        // Find child node to search
        childNode = findNode(parentNode->theTree, childName);

        if (!childNode) {
          printf("%s not found in %s\n", childName, parentName);

        } else {
          printf("%d %s found in %s\n", childNode->count, childNode->name, parentName);
        }

      } else {
        printf("%s does not exist\n", parentName);
      }

    } else if (strcmp(commandName, "item_before") == 0) {

      fscanf(infile, "%s", childName);
      childNode = findNode(parentNode->theTree, childName);

      if (childNode) {
        printf("item before %s: %d\n", childName, itemsBefore(parentNode->theTree, childNode));
      }
      
    } else if (strcmp(commandName, "height_balance") == 0) {
      
      // Get the heights of the sub-trees
      int leftHeight = rootHeight(parentNode->theTree->left) - 1;
      int rightHeight = rootHeight(parentNode->theTree->right) - 1;
      
      // Check if the tree is balanced
      int balance = isBalanced(parentNode);

      printf("%s: left height %d, right height %d, difference %d, %s\n", parentName, leftHeight, rightHeight, balance, (balance != 0) ? "not balanced" : "balanced");
      
    } else if (strcmp(commandName, "count") == 0) {

      //printf("%s count %d\n", parentNode->treeName, count(parentNode->theTree));
      
    } else if (strcmp(commandName, "reduce") == 0) {

      int reductionAmount;
      fscanf(infile, "%s %d", childName, &reductionAmount);
      
      childNode = findNode(parentNode->theTree, childName);

      if (childNode) {
        childNode->count -= reductionAmount;
        printf("%s reduced\n", childName);
      }

    } else if (strcmp(commandName, "delete") == 0) {

      fscanf(infile, "%s", childName);

      itemNode *deleted = deleteNode(parentNode, parentNode->theTree, childName);
      printf("%s deleted from %s\n", childName, parentName);

    } else if (strcmp(commandName, "delete_name") == 0) {

      printf("Preparing to delete %s tree\n", parentName);

      deleteTree(root, parentName);

    } else {
      printf("Unknown command provided! Exiting...");
      exit(1);
    }
  }

  /*
   * Program done, clean up time
   */

   free(childItemTree);
   //cleanTreeNameNodes(root);

  return 0;
}

/*
 * Creates a new tree name node by allocating all of
 * the memory and assigning its values accordingly.
 */
treeNameNode* createTreeNameNode(char *name) {

  treeNameNode *newTree = malloc(sizeof(treeNameNode));
  
  strcpy(newTree->treeName, name);

  newTree->theTree = NULL;
  newTree->left = newTree->right = NULL;

  return newTree;
}

/*
 * Creates a new item node by allocating all of
 * the memory and assigning its values accordingly.
 */
itemNode* createItemNode(char *name, int count) {

  itemNode *newNode = malloc(sizeof(itemNode));
  
  strcpy(newNode->name, name);
  newNode->count = count;

  newNode->left = newNode->right = NULL;

  return newNode;
}

/*
 * Builds a name tree based off a given root, the input file,
 * and the number of trees to create. It sorts them alphabetically
 * within the insert tree name node function.
 */
treeNameNode* buildNameTree(treeNameNode *root, FILE *infile, int numTreeNames) {

  for (int i = 0; i < numTreeNames; i++) {

    char treeName[50];
    fscanf(infile, "%s", treeName);

    if (!root)
      root = createTreeNameNode(treeName);

    treeNameNode *newTree = createTreeNameNode(treeName);
    insertTree(root, newTree);
  }

  return root;
}

/*
 * Inserts a tree name node into another one. It will sort the left
 * and right nodes automatically by name and then recursively keep
 * going until it reaches the bottom of the tree.
 */
treeNameNode* insertTree(treeNameNode *root, treeNameNode *tree) {

  if (strcmp(tree->treeName, root->treeName) < 0) {

    if (!root->left)
      root->left = tree;
    else
      root = insertTree(root->left, tree);
       
  } else if (strcmp(tree->treeName, root->treeName) > 0) {
      
    if (!root->right)
      root->right = tree;
    else
      root = insertTree(root->right, tree);
  }

  return root;
}

/*
 * Inserts a item node into another one. It will sort the left
 * and right nodes automatically by name and then recursively keep
 * going until it reaches the bottom of the tree.
 */
itemNode* insertNode(itemNode *root, itemNode *tree) {

  if (!root) return tree;

  if (strcmp(tree->name, root->name) < 0) {
    root->left = insertNode(root->left, tree);
       
  } else if (strcmp(tree->name, root->name) > 0) {
    root->right = insertNode(root->right, tree);
  }

  return root;
}

/*
 * Searches the tree name nodes for a given name. If it cannnot
 * find it, or if the root is null, it will still return the root.
 */
treeNameNode* searchNameNode(treeNameNode *root, char treeName[50]) {

  if (!root || strcmp(root->treeName, treeName) == 0)
    return root;
  else if (strcmp(treeName, root->treeName) > 0)
    return searchNameNode(root->right, treeName);
  else
    return searchNameNode(root->left, treeName);
}

/*
 * Searhes a given item node root for a specific item node. If it
 * cannot find it, or if the root is null, it will still return
 * the root.
 */
itemNode* findNode(itemNode *root, char nodeName[50]) {

  if (!root || strcmp(root->name, nodeName) == 0)
    return root;
  else if (strcmp(root->name, nodeName) < 0)
    return findNode(root->right, nodeName);
  else
    return findNode(root->left, nodeName);
}

/*
 * Traverses through the search tree and prints out the output
 * according to the sample output.
 */
void traverse_in_traverse(treeNameNode *root) {

  if (!root || !root->theTree) {
    printf("One or more values are invalid\n");
    return;
  }

  inorderTree(root);
  printf("\n");
  printFancyOutput(root);
}

/*
 * Traverses through the search tree and compares the root to
 * the target item node to see how many steps are before it. If
 * there is no root, it will return 0.
 */
int itemsBefore(itemNode *root, itemNode *node) {

  if (!root)
    return 0;
  
  int distance = 0;
  int comparison = strcmp(root->name, node->name);

  if (comparison < 0)
    distance += itemsBefore(root->right, node);

  if (comparison < 0)
    distance++;

  distance += itemsBefore(root->left, node);

  return distance;
}

/*
 * This function will return the difference of the heights between
 * the left sub-tree and the right one. If there is no root, it will
 * return -1, as the tree is not balanced. This function returns the
 * absolute value.
 */
int isBalanced(treeNameNode* root) {

  int leftHeight = 0, rightHeight = 0;
  
  if (!root)
    return -1;
  
  leftHeight = rootHeight(root->theTree->left);
  rightHeight = rootHeight(root->theTree->right);
  
  if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) 
    return abs(rightHeight - leftHeight);
  
  return abs(rightHeight - leftHeight);
}

/*
 * Recursive function to tell the height of a given binary tree of
 * tree name nodes. It compares the left or right side (the max value).
 */
int height(treeNameNode *tree) {

  if (!tree) 
    return 0;

  return 1 + max(height(tree->left), height(tree->right)); 
}

/*
 * Recursive function to tell the height of a given binary tree of
 * item nodes. It compares the left or right side (the max value).
 */
int rootHeight(itemNode *root) {

  if (!root) 
    return 0;

  return 1 + max(rootHeight(root->left), rootHeight(root->right)); 
}

/*
 * Returns the highest integer value between the 2.
 */
int max(int a, int b) { 
  return (a >= b) ? a : b; 
}

/*
 * Finds the minimum value of a given item node. It keeps searching
 * left until there is no more left node (which will return the smallest).
 */
itemNode* findMinValueNode(itemNode* node) {

  itemNode* current = node;
 
  while (current && current->left)
    current = current->left;
 
  return current;
}

/*
 * Deletes a given tree from the tree name root. It the root is null, it
 * will stop the function and not do anything. Otherwise, it will free the
 * memory, and also delete all of the trees nodes appropriately.
 */
void deleteTree(treeNameNode *root, char name[50]) {

  if (!root)
    return;

  treeNameNode *tree = searchNameNode(root, name);

  printf("%s deleted\n", root->treeName);
  
  //deleteNode(root, tree->theTree, tree->theTree->name);

  free(root);
}

/*
 * Deletes a given item node from a given root. It the root is null, it
 * will return NULL as the deleted node. Otherwise, it will recursively
 * call itself and check how many children nodes there are, or if it is
 * a leaf node.
 */
itemNode* deleteNode(treeNameNode *tree, itemNode *root, char name[50]) {

  if (!tree || !root)
    return NULL;

  if (strcmp(name, root->name) > 0)
    root->right = deleteNode(tree, root->right, name);
  else if (strcmp(name, root->name) < 0)
    root->left = deleteNode(tree, root->left, name);

  else {

    // If there are no children nodes
    if (!root->left && !root->right) {
      free(root);
      return NULL;
    }

    // If there is a single child node
    else if (!root->left || !root->right) {

      itemNode *temp = (!root->left) ? root->right : root->left;

      free(root);
      return temp;

    } else {

      // If there are both children
      itemNode *temp = findMinValueNode(root->left);

      temp->left = root->left;
      temp->right = root->right;
      tree->theTree = temp;

      free(root);
      return temp;
    }
  }

  return root;
}

/*
 * Traverses through the search tree and returns the sum of all
 * of the counts combined. If the root is null, it will return 0.
 */
int count(itemNode *root) {

  int totalSum = 0;

  if (root) {
    
    if (root->count > 0)
      totalSum += root->count;

    totalSum += count(root->left);
    totalSum += count(root->right);

  } else {
    return 0;
  }

  return totalSum;
}

/*
 * Cleans all of the tree name nodes recursively to free all memory.
 */
void cleanTreeNameNodes(treeNameNode *root) {

  if (!root)
    return;

  if (root->theTree) {
    printf("Passing on\n");
    cleanItemNodes(root->theTree);
  }

  cleanTreeNameNodes(root->right);
  cleanTreeNameNodes(root->left);

  free(root);
}

/*
 * Cleans all of the item nodes recursively to free all memory.
 */
void cleanItemNodes(itemNode *root) {

  if (!root)
    return;

  if (root->left) {
    printf("About to clear %s\n", root->left->name);
    cleanItemNodes(root->left);
  }
  
  if (root->right) {
    printf("About to clear %s\n", root->right->name);
    cleanItemNodes(root->right);
  }

  free(root);
}

/*
 * Prints item nodes out in order from a given root.
 */
void inorder(itemNode *p) {

  if (p) {
    inorder(p->left);
    printf("%s ", p->name);
    inorder(p->right);
  }
}

/*
 * Prints tree name nodes out in order from a given root.
 */
void inorderTree(treeNameNode *p) {

  if (p) {
    inorderTree(p->left);
    printf("%s ", p->treeName);
    inorderTree(p->right);
  }
}

/*
 * A special function in order to print the output according
 * to the sample output with the tree name nodes and item nodes.
 */
void printFancyOutput(treeNameNode *root) {

  if (root) {

    printFancyOutput(root->left);

    printf("===%s===\n", root->treeName);
    inorder(root->theTree);
    printf("\n");

    printFancyOutput(root->right);
  }  
}
