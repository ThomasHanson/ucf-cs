
# Programming Assignment :one:

This assignment is intended to make you do a lot of work with dynamic memory allocation, pointers, and arrays of pointers.

## Problem: The Monster Trainers Need Your Help

Several small monster trainers have come to you for advice regarding expeditions they're planning into various regions. You are writing a program to estimate how many monsters they can expect to capture in each region.

* You've got a Small Monster Index that tells you the name, type, and relative commonality of all the small monsters in question.
  * (A monster’s absolute commonality is the same in each region. A monster’s relative commonality will change region by region as calculations are performed)
* You've also got an atlas that tells you about the relevant regions and which small monsters are present in them.
* Each trainer tells you which regions they're visiting, and how many monsters they intend to capture per region.
* To estimate the number of a given monster M, a trainer will capture in a region R:
  * Divide the relative population of M in R by R's total relative population.
  * Multiply the result by the total number of captures the trainer intends per region.  
  * Round this result to the nearest integer.

## Data Structures

The structures you'll use for the monsters, regions, itineraries, and trainers are shown in the sidebar. You must use these structures in your code. However, you are free to add more structures if you need.

You'll need to allocate, read, compute upon, output from, and subsequently free:
* The monster index.
  * The names and elements of each monster in the index.
* The region atlas.
  * The names and monster lists of each region.
* The list of trainers.
  * The names and itineraries of each trainer.
  * The region list of each itinerary.

```c
typedef struct monster {
    char *name;
    char *element;
    int population;
} monster;

typedef struct region {
    char *name;
    int numMonsters;
    int totalPopulation;
    monster **monsters;
} region;

typedef struct itinerary {
    int numRegions;
    region **regions;
    int captures;
} itinerary;

typedef struct trainer {
    char *name;
    itinerary *visits;
} trainer;
```

## Input Specification

The input will be taken from the `in.txt` file. There are blank lines in the sample input to make them more readable. You should completely ignore blank lines.

The first line of the file contains the number of monsters `monsterCount`, followed by the word "monsters," as an indication that this number is count of monsters.

The next `monsterCount` lines contain information of monsters, with each line containing two strings and one integer. 
* The first string is the monster name (single word string with maximum length is 50).
* The second string is the element of the monster (single word string with maximum length is 50).
* The integer represents the population of the monster (maximum value is 1 million).

The next section of the input file is region information. The file contains the number of regions `regionCount`, followed by the word regions.
* The first line of a region contains the name of the region.
* The second line contains the number of different monsters `regionMonsterCount`, followed by the word "monsters" again. The next `regionMonsterCount` lines contain the name of different monsters in the region.

The last section of input contains trainer information. The next line of input contains the number of trainers `trainerCount`, followed by the word "trainers." For each trainer in our input file:
* The first line represents the trainer name (single word string with maximum length is 50).
* The second line contains the number of captures, followed by the word "captures."
* The next line contains the number of regions `trainerRegionCount`, followed by the word "regions."
* The final line contains the name of the region the trainer is visiting.

## Output Specification

The output of the program must be written to the `out.txt` file. It should contain the exact same format as specified in the sample output. The output should contain each trainer name, followed by the number of monsters the trainer will capture from each region.

Follow the output format as shown in the sample output. Note that we will test your code with diff command to match your output file with our output file.

Print order should generally be consistent with input:
* Print the trainers in the order you got them.
* Within the trainers, print the regions in the order you got the visits.
* Within the regions, print the monster counts in the order they show up in the atlas for that region.
* Print blank lines between each trainer.

## Example Input & Output

### Example Input

```
8 monsters
StAugustine Grass 12
Zoysia Grass 8
WholeWheat Bread 6
MultiGrain Bread 10
Rye Bread 10
Cinnamon Spice 5
Pepper Spice 10
Pumpkin Spice 30

3 regions

Rome
4 monsters 
StAugustine
Zoysia
WholeWheat
Pepper

Helve
5 monsters
StAugustine
WholeWheat
MultiGrain
Rye
Cinnamon

Aria 
5 monsters
Zoysia
MultiGrain
Cinnamon
Pepper
Pumpkin

3 trainers

Alice
5 captures
2 regions
Rome
Aria

Bob
4 captures
3 regions
Rome
Helve
Aria

Carol
10 captures
1 region
Aria
```

### Example Output

*See the mapping example discussed below to understand how the output is generated.*

```
Alice
Rome 
2 StAugustine
1 Zoysia  
1 WholeWheat
1 Pepper  
Aria
1 Zoysia  
1 MultiGrain  
1 Pepper  
2 Pumpkin

Bob
Rome
1 StAugustine
1 Zoysia  
1 WholeWheat
1 Pepper
Helve  
1 StAugustine
1 WholeWheat
1 MultiGrain  
1 Rye  
Aria  
1 Zoysia  
1 MultiGrain  
1 Pepper  
2 Pumpkin

Carol  
Aria  
1 Zoysia  
2 MultiGrain
1 Cinnamon
2 Pepper  
5 Pumpkin
```

## Mapping Example

*Here’s the table of how each individual trainer’s results are computed. It also shows how rounding issues can lead to trainers capturing more monsters than they intend!*

&nbsp;

| Rome          | Raw   | Divided | Alice    | Round  | Bob  | Round
| -----------   | ----- | ------- | ------- | ----- | ------| ------|
| Coefficient   | 1.00  | 36.00    | 5.00  |    | 4.00  |    |
| StAugustine   | 12.00  | 0.33    | 1.67  | 2.00  | 1.33  | 1.00  |
| Zoysia    | 8.00  | 0.22     | 1.11  | 1.00  | 0.89   | 1.00  |
| WholeWheat  | 6.00  | 0.17     | 0.83  | 1.00  | 0.67  | 1.00  |
| Pepper    | 10.00  | 0.28    | 1.39  | 1.00  | 1.11   | 1.00  |
| **Total**    | 36.00  | 1.00    | 5.00  | 5.00  | 4.00  | 4.00  |

&nbsp;

| Helve          | Raw   | Divided | Alice | Round | Bob    | Round  |
| -----------   | ----- | ------- | ------- | ------- | ------- | ------|
| Coefficient   | 1.00  | 43.00    |     |       | 4.00  |    |
| StAugustine   | 12.00  | 0.28    |     |       | 1.12  | 1.00  |
| WholeWheat  | 6.00  | 0.14     |     |       | 0.56   | 1.00  |
| MultiGrain  | 10.00  | 0.23     |     |       | 0.93  | 1.00  |
| Rye      | 10.00  | 0.23    |     |       | 0.93   | 1.00  |
| Cinnamon    | 5.00  | 0.12    |     |       | 0.47   | 0.00  |
| **Total**    | 43.00  | 1.00    |     |       | 4.00  | 4.00  |

&nbsp;

| Aria          | Raw   | Divided | Alice  | Round  | Bob  | Round
| -----------   | ----- | ------- | ------- | ----- | ------| ------|
| Coefficient   | 1.00  | 36.00    | 5.00  |    | 4.00  |    |
| StAugustine   | 12.00  | 0.33    | 1.67  | 2.00  | 1.33  | 1.00  |
| WholeWheat  | 8.00  | 0.22     | 1.11  | 1.00  | 0.89   | 1.00  |
| MultiGrain  | 6.00  | 0.17     | 0.83  | 1.00  | 0.67  | 1.00  |
| Rye      | 10.00  | 0.28    | 1.39  | 1.00  | 1.11   | 1.00  |
| Cinnamon    | 10.00  | 0.28    | 1.39  | 1.00  | 1.11   | 1.00  |
| **Total**    | 36.00  | 1.00    | 5.00  | 5.00  | 4.00  | 4.00  |

&nbsp;

| Aria          | Raw   | Divided | Alice  | Round  | Bob  | Round  | Carol  | Round  |
| -----------   | ----- | ------- | ------- | ----- | ------| ------| ----- | ----- |
| Coefficient   | 1.00  | 63.00    | 5.00  |    | 4.00  |    | 10.00  |    |
| Zoysia     | 8.00  | 0.13    | 0.63  | 1.00  | 0.51  | 1.00  | 1.27  | 1.00  |
| MultiGrain  | 10.00  | 0.16     | 0.79  | 1.00  | 0.63   | 1.00  | 1.59  | 2.00  |
| Cinnamon    | 5.00  | 0.08     | 0.40  | 0.00  | 0.32  | 0.00  | 0.79  | 1.00  |
| Pepper    | 10.00  | 0.16    | 0.79  | 1.00  | 0.63   | 1.00  | 1.59  | 2.00  |
| Pumpkin    | 30.00  | 0.48    | 2.38  | 2.00  | 1.90   | 2.00  | 4.76  | 5.00  |
| **Total**    | 63.00  | 1.00    | 5.00  | 5.00  | 4.00  | 5.00  | 10.00  | 11.00  |

## Specific Requirements

* You have to use dynamic memory allocation.
* You have to use the provided structures.
* You may not use global variables.
* You have to implement at least the following functions:
  * ``monster* createMonster(char *name, char *element, int population)``
  * ``monster** readMonsters(FILE *inFile, int *monsterCount)``
* Reading the regions and trainers also should be done in separate functions. You may create your own to use outside of the main function.
* You need to implement one or more release memory function to release the allocated memory.
* You have to use the provided memory leak detector.
  * You must ``#include "leak_detector_c.h"`` inyourcode,and  
  * You must call ``atexit(report_mem_leak)`` as the first line of your main() function.
* You do not need to comment line by line, but comment every function and every “paragraph” of code.
* You don’t have to hold to any indentation standard, but you must indent and you must do so consistently within your own code.
