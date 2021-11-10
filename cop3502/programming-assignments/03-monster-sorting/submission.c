/* COP 3502C Assignment 3
This program is written by: Thomas Hanson */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// The number of input files to sort through
#define NUM_FILES 6

/*
 * Monster structure to keep track of
 * all information from the file input.
 */
typedef struct monster {
  int id;
  char name[64];
  char element[64];
  int population;
  double weight;
} monster;

/*
 * Sorting wrapper to keep track of how many
 * times a sorting algorithm compares or copies
 * any specific monster structures.
 *
 * This wrapper gets passed by reference to
 * change the values accordingly.
 */
typedef struct {
  long long int compares;
  long long int copies;
} sort_results;

/*
 * All text input files to sort from.
 */
char infiles[NUM_FILES][8] = {
  "10K.txt",
  "20K.txt",
  "30K.txt",
  "40K.txt",
  "50K.txt",
  "60K.txt",
};

/*
 * All output files that need to be
 * generated and have data printed.
 */
 char outfiles[3][15] = {
  "criteria_1.csv",
  "criteria_2.csv",
  "criteria_3.csv",
};

/*
 * Monster Functions
 */
monster** readMonsters(FILE* infile, int numMonsters);

/*
 * Utility Functions
 *
 * Used to facilitate the process or complete
 * multiple things more efficiently.
 */
void swap(monster *a, monster *b);
void copy(monster **dest, monster **src, int n);
char* getCriteria(int criteria);
float timeBetween(clock_t clocks);
void resetResults(sort_results *results);
void freeMonsters(monster **monsters, int n);

/*
 * Sorting Functions
 *
 * Purely in charge of sorting the double monster
 * pointers. Every sorting function also takes in a
 * sort_results wrapper to keep track of results for
 * each algorithm.
 */
void selectionSort(monster **mons, int n, int criteria, sort_results *results);
void bubbleSort(monster **mons, int n, int criteria, sort_results *results);
void insertionSort(monster **mons, int n, int criteria, sort_results *results);
int partition(monster **mons, int low, int high, int criteria, sort_results *results);
void quickSort(monster **mons, int low, int high, int criteria, sort_results *results);
void merge(monster **mons, int left, int middle, int right, int criteria, sort_results *results);
void mergeSort(monster **mons, int left, int right, int criteria, sort_results *results);
void mergeInsertionSort(monster **mons, int low, int high, int criteria, sort_results *results);

/*
 * Comparison Functions
 *
 * These functions are purely in charge of monster
 * comparisons. They return whether a list is already
 * sorted or can also return the comparison value
 * between multiple monsters and a criteria.
 */
int compareTo(monster *m1, monster *m2, int criteria);
int isSorted(monster **mons, int n, int criteria);

/*
 * Printing Functions
 *
 * Small utility functions that are in charge of
 * printing console output for debugging purpose
 * or to match assignment output.
 */
void printMonsters(monster **mons, int n);
void printResults(sort_results *results);
void printClocks(clock_t clocks);

int main(void) {
  
  // Leak detector
  //atexit(report_mem_leak);
  
  monster **monsters, **copyMonsters;
  
  char *criteriaName;
  FILE *curInFile, *curOutFile;
  
  // Criteria loop
  for (int i = 1; i <= 3; i++) {
    
    curOutFile = fopen(outfiles[i - 1], "a");
    criteriaName = getCriteria(i);
    
    fprintf(curOutFile, "DataSize, ");
    fprintf(curOutFile, "SelectionSortCompare, SelectionSortCopy, SelectionSortTIme, ");
    fprintf(curOutFile, "BubbleSortCompare, BubbleSortCopy, BubbleSortTime, ");
    fprintf(curOutFile, "InsertionSortCompare, InsertionSortCopy, InsertionSortTime, ");
    fprintf(curOutFile, "Merge_InsertionSortCompare, Merge_InsertionSortCopy, Merge_InsertionSortTime, ");
    fprintf(curOutFile, "MergeSortCompare, MergeSortCopy, MergeSortTime, ");
    fprintf(curOutFile, "QuickSortCompare, QuickSortCopy, QuickSortTime\n");
    
    // Input loop
    for (int j = 1; j <= NUM_FILES; j++) {
      
      printf("\n========\nProcessing Criteria %d and file %s\n========\n", i, infiles[j - 1]);
      curInFile = fopen(infiles[j - 1], "r");
      
      if (!curInFile) {
        printf("Input file does not exist! Exiting...\n");
        exit(1);
      }

      // The number of monsters in current file
      int n = j * 10000;
      
      fprintf(curOutFile, "%d, ", n);
      
      sort_results *results = calloc(1, sizeof(*results));
      resetResults(results);

      monsters = readMonsters(curInFile, n);
      copyMonsters = calloc(n, sizeof(monster*));
      
      for (int i = 0; i < n; ++i) {
        copyMonsters[i] = malloc(sizeof(monster));
      }
      
      /*
       * Current Sorting Algorithm: Selection Sort
       */
      copy(copyMonsters, monsters, n);
      printf("Array status: not sorted by %s before calling selection sort\n", criteriaName);
      clock_t startTime, endTime;
      startTime = clock();
      selectionSort(copyMonsters, n, i, results);
      endTime = clock();
      
      if (isSorted(copyMonsters, n, i)) {
        printf("Array status: sorted by %s after returning from selection sort\n", criteriaName);
        printClocks(endTime - startTime);
        printResults(results);
        fprintf(curOutFile, "%llu, %llu, %f, ", results->compares, results->copies, timeBetween(endTime - startTime));
      }
      
      resetResults(results);
      
      /*
       * Current Sorting Algorithm: Bubble Sort
       */
      copy(copyMonsters, monsters, n);
      printf("Array status: not sorted by %s before calling bubble sort\n", criteriaName);
      startTime = clock();
      bubbleSort(copyMonsters, n, i, results);
      endTime = clock();
      
      if (isSorted(copyMonsters, n, i)) {
        printf("Array status: sorted by %s after returning from bubble sort\n", criteriaName);
        printClocks(endTime - startTime);
        printResults(results);
        fprintf(curOutFile, "%llu, %llu, %f, ", results->compares, results->copies, timeBetween(endTime - startTime));
      }
      
      resetResults(results);
      
      /*
       * Current Sorting Algorithm: Insertion Sort
       */
      copy(copyMonsters, monsters, n);
      printf("Array status: not sorted by %s before calling insertion sort\n", criteriaName);
      startTime = clock();
      insertionSort(copyMonsters, n, i, results);
      endTime = clock();
      
      if (isSorted(copyMonsters, n, i)) {
        printf("Array status: sorted by %s after returning from insertion sort\n", criteriaName);
        printClocks(endTime - startTime);
        printResults(results);
        fprintf(curOutFile, "%llu, %llu, %f, ", results->compares, results->copies, timeBetween(endTime - startTime));
      }
      
      resetResults(results);
      
      /*
       * Current Sorting Algorithm: Merge Sort
       */
      copy(copyMonsters, monsters, n);
      printf("Array status: not sorted by %s before calling merge sort\n", criteriaName);
      startTime = clock();
      mergeSort(copyMonsters, 0, n - 1, i, results);
      endTime = clock();
      
      if (isSorted(copyMonsters, n, i)) {
        printf("Array status: sorted by %s after returning from merge sort\n", criteriaName);
        printClocks(endTime - startTime);
        printResults(results);
        fprintf(curOutFile, "%llu, %llu, %f, ", results->compares, results->copies, timeBetween(endTime - startTime));
      }

      resetResults(results);
      
      /*
       * Current Sorting Algorithm: Merge Insertion Sort
       */
      copy(copyMonsters, monsters, n);
      printf("Array status: not sorted by %s before calling merge insertion sort\n", criteriaName);
      startTime = clock();
      mergeInsertionSort(copyMonsters, 0, n - 1, i, results);
      endTime = clock();
      
      if (isSorted(copyMonsters, n, i)) {
        printf("Array status: sorted by %s after returning from merge insertion sort\n", criteriaName);
        printClocks(endTime - startTime);
        printResults(results);
        fprintf(curOutFile, "%llu, %llu, %f, ", results->compares, results->copies, timeBetween(endTime - startTime));
      }

      resetResults(results);
      
      /*
       * Current Sorting Algorithm: Quick Sort
       */
      copy(copyMonsters, monsters, n);
      printf("Array status: not sorted by %s before calling quick sort\n", criteriaName);
      startTime = clock();
      quickSort(copyMonsters, 0, n - 1, i, results);
      endTime = clock();
      
      if (isSorted(copyMonsters, n, i)) {
        printf("Array status: sorted by %s after returning from quick sort\n", criteriaName);
        printClocks(endTime - startTime);
        printResults(results);
        fprintf(curOutFile, "%llu, %llu, %f\n", results->compares, results->copies, timeBetween(endTime - startTime));
      }
      
      /*
       * Frees all of our temporary pointers for future
       * use after each input iteration. Also closes the
       * current input file.
       */
      free(results);
      freeMonsters(copyMonsters, n);
      freeMonsters(monsters, n);
      
      fclose(curInFile);
    }
    
    // Closes the current output file after each criteria
    fclose(curOutFile);
  }

  return 0;
}

/*
 * Reads file input for a specific amount of monster and
 * returns a dynamically allocated double pointer that
 * contains information for a monster structure.
 */
monster** readMonsters(FILE* infile, int numMonsters) {

  char name[64], element[64];
  int population;
  double weight;

  monster** monsters = calloc(numMonsters, sizeof(monster*));
    
  /*
   * For each monster, scan the file for the 4
   * values. Create a monster pointer and assign
   * the values to itself.
  */
  for (int i = 0; i < numMonsters; i++) {
    monster *p = malloc(sizeof(monster));
    fscanf(infile, "%s %s %d %lf", p->name, p->element, &p->population, &p->weight);
    monsters[i] = p;
  }

  return monsters;
}

/*
 * Utility function to simplify swapping process.
 */
void swap(monster *a, monster *b) {
  monster temp = *a;
  *a = *b;
  *b = temp;
}

/*
 * Utility function to copy 2 double monster pointers.
 */
void copy(monster **dest, monster **src, int n) {
  for (int i = 0; i < n; i++) {
    memcpy(dest[i], src[i], sizeof(monster));
  }
}

/*
 * Utility function to get the criteria name. This
 * simplifies the process before printing out or
 * hardcoding any of those values. If a criteria
 * is not found, it will simply print "unknown".
 */
char* getCriteria(int criteria) {

  switch (criteria) {

    case 1:
      return "name";

    case 2:
      return "weight";

    case 3:
      return "name and weight";
    
    default:
      return "unknown";
  }
}

/*
 * Utility function to get the time in seconds
 * between clocks. This is used to print out a
 * console value and also file output.
 */
float timeBetween(clock_t clocks) {
  return ((double) clocks) / CLOCKS_PER_SEC;
}

/*
 * Utility function to simply reset the existing
 * comparisons and copies after calling each of
 * the sorting algorithms.
 */
void resetResults(sort_results *results) {
  results->compares = 0;
  results->copies = 0;
}

/*
 * Utility function to free any memory associated
 * with a double monster pointer. This gets called
 * after each input iteration from our main loop.
 */
void freeMonsters(monster **monsters, int n) {
  
  for (int i = 0; i < n; i++) {
    free(monsters[i]);
  }
    
  free(monsters);
}

/*
 * O(N^2) sorting algorithm. Takes in a double monster
 * pointer to sort, along with the number of monsters,
 * criteria to sort by, and a sort_results wrapper to
 * keep track of the number of comparisons and copies.
 */
void selectionSort(monster **mons, int n, int criteria, sort_results *results) {

  int minIndex;
  
  /*
   * Iterate through and move the boundary of our
   * unsorted subarray, one by one.
   */
  for (int i = 0; i < n - 1; i++) {
    
    // Find the minimum element in the unsorted array
    minIndex = i;
    
    for (int j = i + 1; j < n; j++) {
      
      results->compares++;
      
      if (compareTo(mons[j], mons[minIndex], criteria) < 0)
        minIndex = j;
    }
    
    // Swap the found minimum element with the first element
    swap(mons[minIndex], mons[i]);
    results->copies += 3;
  }
}

/*
 * O(N^2) sorting algorithm. Takes in a double monster
 * pointer to sort, along with the number of monsters,
 * criteria to sort by, and a sort_results wrapper to
 * keep track of the number of comparisons and copies.
 */
void bubbleSort(monster **mons, int n, int criteria, sort_results *results) {
  
  // Check if i elements are already in place
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      
      results->compares++;
      
      if (compareTo(mons[j], mons[j + 1], criteria) > 0) {
        
        swap(mons[j], mons[j + 1]);
        results->copies += 3;
      }
    }
  }
}

/*
 * O(N^2) sorting algorithm. Takes in a double monster
 * pointer to sort, along with the number of monsters,
 * criteria to sort by, and a sort_results wrapper to
 * keep track of the number of comparisons and copies.
 */
void insertionSort(monster **mons, int n, int criteria, sort_results *results) {
  
  int i, j;
  monster *item;

  for (i = 1; i < n; i++) {

    item = mons[i];
    results->compares++;

    /*
     * Move elements of mons[0 ... i - 1], that are
     * greater than key, to one position ahead of
     * their current position
     */
     for (j = i - 1; j >= 0; j--) {
       
      results->compares++;

      if (compareTo(mons[j], item, criteria) > 0) {
         
        mons[j + 1] = mons[j];
        results->copies++;

      } else {
        break;
      }
     }
    
    mons[j + 1] = item;
    results->copies++;
  }
}

/*
 * This function takes last element as pivot, places
 * the pivot element at its correct position in sorted
 * array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right
 * of pivot.
 */
int partition(monster **mons, int low, int high, int criteria, sort_results *results) {
  
  // Our pivot (element to be placed at right position)
  monster *pivot = mons[high];
  
  // The index of smaller element
  int i = low - 1;
  
  for (int j = low; j <= high - 1; j++) {

      results->compares++;
      
      // If current element is smaller than the pivot
      if (compareTo(mons[j], pivot, criteria) < 0) {
        
          i++; // Increment index of smaller element
          
          swap(mons[i], mons[j]);
          results->copies += 3;
        }
    }
  
    swap(mons[i + 1], mons[high]);
    results->copies += 3;
  
    return (i + 1);
}

/*
 * O(N^2) sorting algorithm. Takes in a double monster
 * pointer to sort, a low and high value to partition,
 * criteria to sort by, and a sort_results wrapper to
 * keep track of the number of comparisons and copies.
 */
void quickSort(monster **mons, int low, int high, int criteria, sort_results *results) {

  if (low < high) {
    
    // The index that we are partitioning
    int split = partition(mons, low, high, criteria, results);
    
    // Separately sort elements before and after partition
    quickSort(mons, low, split - 1, criteria, results);
    quickSort(mons, split + 1, high, criteria, results);
  }
}

/*
 * Merges two subarrays of double monster pointers.
 *
 * The first subarray is the left half
 * of the array between [left ... middle]
 *
 * The second subarray is the right half
 * of the given array between [middle + 1 ... right]
 */
void merge(monster **mons, int left, int middle, int right, int criteria, sort_results *results) {

  int i, j, k;
  
  // The number of values for each half
  int nLeft = middle - left + 1;
  int nRight = right - middle;
  
  // Temporary arrays for each half
  monster **leftMons = malloc(nLeft * sizeof(monster*));
  monster **rightMons = malloc(nRight * sizeof(monster*));
  
  // Copy data to our left monster pointer
  for (i = 0; i < nLeft; i++) {
    leftMons[i] = mons[left + i];
    results->copies++;
  }

  // Copy data to our right monster pointer
  for (j = 0; j < nRight; j++) {
    rightMons[j] = mons[middle + j + 1];
    results->copies++;
  }
  
  /*
   * Merge the temporary arrays back into our given
   * array from mons [left ... right]
   */
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = left; // Initial index of merged subarray

  while (i < nLeft && j < nRight) {

    results->compares++;

    if (compareTo(leftMons[i], rightMons[j], criteria) <= 0) {
      
      mons[k] = leftMons[i++];
      results->copies++;

    } else {

      mons[k] = rightMons[j++];
      results->copies++;
    }

    k++;
  }
  
  /*
   * Copy the remaining elements of leftMons, if
   * there are any remaining.
   */
  while (i < nLeft) {
    mons[k++] = leftMons[i++];
    results->copies++;
  }
  
  /*
   * Copy the remaining elements of rightMons, if
   * there are any remaining.
   */
  while (j < nRight) {
    mons[k++] = rightMons[j++];
    results->copies++;
  }

  // Free the temporary variables at the end
  free(leftMons);
  free(rightMons);
}

/*
 * O(n log(n)) sorting algorithm. Takes in a double
 * monster pointer to sort, a left and right half of
 * the given sub-array to sort from, criteria to sort
 * by, and a sort_results wrapper to keep track of the
 * number of comparisons and copies.
 */
void mergeSort(monster **mons, int left, int right, int criteria, sort_results *results) {

  if (right > left) {

    int middle = (left + right) / 2;
    
    // Sort first and second halves of given sub-array
    mergeSort(mons, left, middle, criteria, results);
    mergeSort(mons, middle + 1, right, criteria, results);
    
    merge(mons, left, middle, right, criteria, results);
  }
}

/*
 * Merge sort, switching to insertion sort at n <= 25
 */
void mergeInsertionSort(monster **mons, int low, int high, int criteria, sort_results *results) {

  if ((high - low) > 25) {

    int middle = (low + high) / 2;
    
    // Sort first and second halves of given sub-array
    mergeInsertionSort(mons, low, middle, criteria, results);
    mergeInsertionSort(mons, middle + 1, high, criteria, results);
    
    merge(mons, low, middle, high, criteria, results);

  } else {
    insertionSort(mons + low, high - low + 1, criteria, results);
  }
}

/*
 * Comparison function to return how 2 monsters
 * compare with a given criteria. Returns given
 * value at the end.
 */
int compareTo(monster *m1, monster *m2, int criteria) {

  int value;

  switch (criteria) {

    // Sort monsters by name
    case 1:
      value = strcmp(m1->name, m2->name);
      break;

    // Sort monsters by weight
    case 2:
      value =
        (m1->weight < m2->weight) ? -1 :
        (m1->weight > m2->weight) ? 1 :
        0;
      break;

    /*
     * Sort monsters by name and weight. It should be sorted
     * by name first. However, if multiple monsters have same
     * name, they should be sorted based on weight instead.
     */
    case 3:

      // Compare by name first
      value = compareTo(m1, m2, 1);

      // If the names match, run again with weight
      if (value == 0) {
        value = compareTo(m1, m2, 2);
      }
      
      break;

    // Unknown criteria
    default:
      value = 0;
  }

  return value;
}

/*
 * Comparison function to check if a double monster
 * pointer is already sorted. Loops through n number
 * of monsters and checks by criteria. If any of the
 * values are out of order, it will return 0 (unsorted).
 * If it is already sorted, 1 will be returned (sorted).
 */
int isSorted(monster **mons, int n, int criteria) {
  
  for (int i = 0; i < n - 1; i++)
    if (compareTo(mons[i], mons[i + 1], criteria) > 0)
      return 0;
  
  return 1;
}

/*
 * Printing function to print out a double monster
 * pointer with a given number of monsters. This
 * function is mostly for debugging purposes to
 * make sure a list is sorted properly.
 */
void printMonsters(monster **mons, int n) {

  for (int i = 0; i < n; i++)
    printf("%s %s %d %lf \n", mons[i]->name, mons[i]->element, mons[i]->population, mons[i]->weight);

  printf("\n");
}

/*
 * Printing function to print out the sorting results
 * to console. Prevents printing the same string and
 * value dozens of times from main. Keeps consistency.
 */
void printResults(sort_results *results) {
  printf("Total number of comparisons %lld\n", results->compares);
  printf("Total number of copy operations %lld\n", results->copies);
}

/*
 * Printing function to print out the total time taken
 * for each sorting algorithm to console.
 */
void printClocks(clock_t clocks) {
  printf("Total time taken %lf second\n", timeBetween(clocks));
}
