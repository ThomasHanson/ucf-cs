# Programming Assignment :three:

This assignment is intended to make you implement several different sorting algorithms, and the means to analyze their performance. This assignment includes a program and an analysis.

## Problem: Sorting algorithms by sorting monsters

You’ve been given a scattered list of small monsters present in the Knightrola region. You need to evaluate six means of comparison-based sort to get these monsters in order. You need to implement six sorting algorithms for sorting the monsters:
* Selection sort
* Bubble sort
* Insertion sort
* Quick sort
* Merge sort
* Merge sort, switching to insertion sort at 𝑛 ≤ 25

You will need to sort them based on the following criteria. Note that you will use the same criteria number in our code: 
1. Sort monsters by name
2. Sort monsters by weight
3. Sort monsters by name and weight (It should be sorted by name first. However, if multiple monsters have same name, they should be sorted based on weight.)

Consider the following names and weights:
* abc 8.0
* bcd 5.0 
* abc 5.5

Should be sorted into:
* abc 5.5
* abc 8.0
* bcd 5.0

In order to store the monsters and there finding from sorting, you must use the following structures:

```c
typedef struct monster {

  int id;
  char name[64];
  char element[64];
  int population;
  double weight;

} monster;

typedef struct {
  long long int compares;
  long long int copies;
} sort_results;
```
