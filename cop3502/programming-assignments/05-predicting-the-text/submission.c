/* COP 3502C Programming Assignment 5
This program is written by: Thomas Hanson */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leak_detector_c.h"

typedef struct trie {
  int isWord, freq, maxFreq;
  struct trie *children[26];
} trie;

trie* createTrie();
void insert(trie *tree, char word[], int count, int position, int string_length);
int predict(FILE *outfile, trie *dictionary, char *prefix, int position);
void freeDictionary(trie *tree);

int main(void) {

  // Leak detector
  atexit(report_mem_leak);

  // File management
  FILE *infile  = fopen("in.txt", "r"),
       *outfile = fopen("out.txt", "w");

  if (!infile) {
    printf("Input file does not exist!\n");
    exit(1);
  }

  // Variables for the commands
  char string[100000];
  int numCommands = 0, commandType = 0;

  // Create a brand new dictionary (trie)
  trie *dictionary = createTrie();

  fscanf(infile, "%d", &numCommands);

  for (int i = 0; i < numCommands; i++) {
    
    fscanf(infile, "%d %s", &commandType, string);
    int string_length = strlen(string);

    switch (commandType) {

      case 1: {

        int count = 0;
        fscanf(infile, "%d", &count);

        // Insert the frequency of the string
        insert(dictionary, string, count, 0, string_length);

        break;
      }

      case 2: {

        // Whether or not a prediction can be made
        int value = predict(outfile, dictionary, string, 0);

        // Print appropriately
        fprintf(outfile, value ? "\n" : "unknown word\n");

        break;
      }

      default: {
        fprintf(outfile, "Command not recognized!\n");
      }
    }
  }

  /*
   * Clean up
   */
  fclose(infile);
  fclose(outfile);
  freeDictionary(dictionary);

  return 0;
}

/*
 * Function responsible for allocating the
 * memory for a new trie, and returning it.
 */
trie* createTrie() {

  trie *newTree = malloc(sizeof(trie));

  // Assign all values to 0, to prevent garbage values
  newTree->isWord = newTree->freq = newTree->maxFreq = 0;

  // Set all children to NULL, to prevent bad memory access
  for (int i = 0; i < 26; i++)
    newTree->children[i] = NULL;

  return newTree;
}

/*
 * Function responsible for inserting a new
 * word into a trie. This is a recursive function
 * that gets called based on the position in the
 * string.
 */
void insert(trie *tree, char word[], int count, int position, int string_length) {

  // Store the sum to calculate the highest frequency
  int sumFreq = tree->freq + count;

  // Assign the frequency to the sum
  tree->freq = sumFreq;

  // If the position is at the end of the word
  if (position == string_length) {
    tree->isWord = 1;
    return;
  }

  int index = word[position] - 'a';

  // If no child exists, create it
  if (!tree->children[index])
    tree->children[index] = createTrie();

  // Insert the next character to the child and increase position
  insert(tree->children[index], word, count, position + 1, string_length);

  // Check if max frequency should change
  if (tree->children[index]->freq > tree->maxFreq)
    tree->maxFreq = tree->children[index]->freq;
}

/*
 * Function responsible for predicting the next
 * letter from a trie, prefix, and the position
 * in a string. If a valid prediction can be made
 * it will return 1, otherwise 0. It is also in
 * charge of printing out the value to output file.
 */
int predict(FILE *outfile, trie *dictionary, char *prefix, int position) {

  int string_length = strlen(prefix);

  // If the position is at the end of the word
  if (position == string_length) {

    // Flag determines if prediction can be made
    int flag = 0;

    for (int i = 0; i < 26; i++) {

      // If we are at the highest frequency, flag the prediction to true
      if (dictionary->children[i] && dictionary->maxFreq == dictionary->children[i]->freq) {
        flag = 1;
        fprintf(outfile, "%c", (char) (i + 'a'));
      }
    }

    // If nothing else reached, the default flag is 0
    return flag;
  }

  int index = prefix[position] - 'a';

  /*
   * If there is a child node, recursively call the
   * prediction function again while increasing the
   * current position. Otherwise, return 0.
   */
  return dictionary->children[index] ? 
    predict(outfile, dictionary->children[index], prefix, position + 1) : 0;
}

/*
 * Function responsible for freeing all memory
 * associated to a trie and making them NULL.
 */
void freeDictionary(trie *tree) {

  for (int i = 0; i < 26; i++)
    if (tree->children[i])
      freeDictionary(tree->children[i]);

  free(tree);
  tree = NULL;
}