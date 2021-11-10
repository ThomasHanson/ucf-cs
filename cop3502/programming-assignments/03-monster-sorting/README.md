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

## Input

There are 6 input files provided with the assignment with the different number of monsters. Your code should read each of the files and process them. 

The file name indicates the number of monsters available in the file. You can assume the file names and the number of monsters are fixed in your code and you can hardcode the names and the sizes if you wish. 

Each line of a file represents a monster where:
* First string represents the monster name (max length is 10 characters)
* Next string represents the element (max length is 10 characters)
* Next integer represents the population (>=50 )
* Last floating value represents the weight.

For each criterion, you need to load the data of each file into a monster array and then sort the array using each of the mentioned sorting algorithms based on the criterion (specified by criteria number).

You should write a wrapper function for each algorithm that takes the array, reference of a sort_result structure, and other necessary parameters. While sorting, you should keep track the number of comparison and number of assignment operation happening within the specific algorithm.

Make sure to copy the original array before passing to a sorting algorithm as you will need the original array for another sorting algorithm.

## Output

Your code should produce some console output and also some files.

In the console, you should print:
* Whether your array is sorted or not, by checking it.
* Which sorting algorithm you are calling, with which criterion.
* How many seconds it took to process.
* Whether your array is sorted or not.
* Number of comparison and copy operations.

```

========
Processing Criteria 1 and file 10K.txt
========
Array status: not sorted by name before calling selection sort
Array status: sorted by name after calling selection sort
Total time taken time_taken second
Total number of comparisons 49995000
Total number of copy operations 29997
Array status: not sorted by name before calling bubble sort
Array status: sorted by name after calling bubble sort
Total time taken time_taken second
Total number of comparisons 49995000
Total number of copy operations 74790471
Array status: not sorted by name before calling insertion sort
Array status: sorted by name after calling insertion sort
Total time taken time_taken second
Total number of comparisons 24940147
Total number of copy operations 24950155
Array status: not sorted by name before calling merge sort
Array status: sorted by name after calling merge sort
Total time taken time_taken second
Total number of comparisons 120572
Total number of copy operations 267232
Array status: not sorted by name before calling merge/insertion sort
Array status: sorted by name after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 143846
Total number of copy operations 245555
Array status: not sorted by name before calling quick sort
Array status: sorted by name after calling quick sort
Total time taken time_taken second
Total number of comparisons 156070
Total number of copy operations 113814

========
Processing Criteria 1 and file 20K.txt
========
Array status: not sorted by name before calling selection sort
Array status: sorted by name after calling selection sort
Total time taken time_taken second
Total number of comparisons 199990000
Total number of copy operations 59997
Array status: not sorted by name before calling bubble sort
Array status: sorted by name after calling bubble sort
Total time taken time_taken second
Total number of comparisons 199990000
Total number of copy operations 301237767
Array status: not sorted by name before calling insertion sort
Array status: sorted by name after calling insertion sort
Total time taken time_taken second
Total number of comparisons 100432578
Total number of copy operations 100452587
Array status: not sorted by name before calling merge sort
Array status: sorted by name after calling merge sort
Total time taken time_taken second
Total number of comparisons 261065
Total number of copy operations 574464
Array status: not sorted by name before calling merge/insertion sort
Array status: sorted by name after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 307095
Total number of copy operations 530611
Array status: not sorted by name before calling quick sort
Array status: sorted by name after calling quick sort
Total time taken time_taken second
Total number of comparisons 354562
Total number of copy operations 240213

========
Processing Criteria 1 and file 30K.txt
========
Array status: not sorted by name before calling selection sort
Array status: sorted by name after calling selection sort
Total time taken time_taken second
Total number of comparisons 449985000
Total number of copy operations 89997
Array status: not sorted by name before calling bubble sort
Array status: sorted by name after calling bubble sort
Total time taken time_taken second
Total number of comparisons 449985000
Total number of copy operations 679601919
Array status: not sorted by name before calling insertion sort
Array status: sorted by name after calling insertion sort
Total time taken time_taken second
Total number of comparisons 226563962
Total number of copy operations 226593971
Array status: not sorted by name before calling merge sort
Array status: sorted by name after calling merge sort
Total time taken time_taken second
Total number of comparisons 408638
Total number of copy operations 894464
Array status: not sorted by name before calling merge/insertion sort
Array status: sorted by name after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 452628
Total number of copy operations 819163
Array status: not sorted by name before calling quick sort
Array status: sorted by name after calling quick sort
Total time taken time_taken second
Total number of comparisons 544259
Total number of copy operations 375714

========
Processing Criteria 1 and file 40K.txt
========
Array status: not sorted by name before calling selection sort
Array status: sorted by name after calling selection sort
Total time taken time_taken second
Total number of comparisons 799980000
Total number of copy operations 119997
Array status: not sorted by name before calling bubble sort
Array status: sorted by name after calling bubble sort
Total time taken time_taken second
Total number of comparisons 799980000
Total number of copy operations 1208326248
Array status: not sorted by name before calling insertion sort
Array status: sorted by name after calling insertion sort
Total time taken time_taken second
Total number of comparisons 402815405
Total number of copy operations 402855414
Array status: not sorted by name before calling merge sort
Array status: sorted by name after calling merge sort
Total time taken time_taken second
Total number of comparisons 561830
Total number of copy operations 1228928
Array status: not sorted by name before calling merge/insertion sort
Array status: sorted by name after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 655316
Total number of copy operations 1142470
Array status: not sorted by name before calling quick sort
Array status: sorted by name after calling quick sort
Total time taken time_taken second
Total number of comparisons 732944
Total number of copy operations 513450

========
Processing Criteria 1 and file 50K.txt
========
Array status: not sorted by name before calling selection sort
Array status: sorted by name after calling selection sort
Total time taken time_taken second
Total number of comparisons 1249975000
Total number of copy operations 149997
Array status: not sorted by name before calling bubble sort
Array status: sorted by name after calling bubble sort
Total time taken time_taken second
Total number of comparisons 1249975000
Total number of copy operations 1890294660
Array status: not sorted by name before calling insertion sort
Array status: sorted by name after calling insertion sort
Total time taken time_taken second
Total number of comparisons 630148209
Total number of copy operations 630198218
Array status: not sorted by name before calling merge sort
Array status: sorted by name after calling merge sort
Total time taken time_taken second
Total number of comparisons 718177
Total number of copy operations 1568928
Array status: not sorted by name before calling merge/insertion sort
Array status: sorted by name after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 880433
Total number of copy operations 1487921
Array status: not sorted by name before calling quick sort
Array status: sorted by name after calling quick sort
Total time taken time_taken second
Total number of comparisons 964370
Total number of copy operations 654714

========
Processing Criteria 1 and file 60K.txt
========
Array status: not sorted by name before calling selection sort
Array status: sorted by name after calling selection sort
Total time taken time_taken second
Total number of comparisons 1799970000
Total number of copy operations 179997
Array status: not sorted by name before calling bubble sort
Array status: sorted by name after calling bubble sort
Total time taken time_taken second
Total number of comparisons 1799970000
Total number of copy operations 2712594297
Array status: not sorted by name before calling insertion sort
Array status: sorted by name after calling insertion sort
Total time taken time_taken second
Total number of comparisons 904258087
Total number of copy operations 904318097
Array status: not sorted by name before calling merge sort
Array status: sorted by name after calling merge sort
Total time taken time_taken second
Total number of comparisons 877199
Total number of copy operations 1908928
Array status: not sorted by name before calling merge/insertion sort
Array status: sorted by name after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 964549
Total number of copy operations 1757655
Array status: not sorted by name before calling quick sort
Array status: sorted by name after calling quick sort
Total time taken time_taken second
Total number of comparisons 1143044
Total number of copy operations 797163

========
Processing Criteria 2 and file 10K.txt
========
Array status: not sorted by weight before calling selection sort
Array status: sorted by weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 49995000
Total number of copy operations 29997
Array status: not sorted by weight before calling bubble sort
Array status: sorted by weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 49995000
Total number of copy operations 75574053
Array status: not sorted by weight before calling insertion sort
Array status: sorted by weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 25201344
Total number of copy operations 25211349
Array status: not sorted by weight before calling merge sort
Array status: sorted by weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 120414
Total number of copy operations 267232
Array status: not sorted by weight before calling merge/insertion sort
Array status: sorted by weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 144149
Total number of copy operations 245964
Array status: not sorted by weight before calling quick sort
Array status: sorted by weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 153588
Total number of copy operations 115215

========
Processing Criteria 2 and file 20K.txt
========
Array status: not sorted by weight before calling selection sort
Array status: sorted by weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 199990000
Total number of copy operations 59997
Array status: not sorted by weight before calling bubble sort
Array status: sorted by weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 199990000
Total number of copy operations 299253273
Array status: not sorted by weight before calling insertion sort
Array status: sorted by weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 99771084
Total number of copy operations 99791089
Array status: not sorted by weight before calling merge sort
Array status: sorted by weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 260897
Total number of copy operations 574464
Array status: not sorted by weight before calling merge/insertion sort
Array status: sorted by weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 307738
Total number of copy operations 531422
Array status: not sorted by weight before calling quick sort
Array status: sorted by weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 325464
Total number of copy operations 244473

========
Processing Criteria 2 and file 30K.txt
========
Array status: not sorted by weight before calling selection sort
Array status: sorted by weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 449985000
Total number of copy operations 89997
Array status: not sorted by weight before calling bubble sort
Array status: sorted by weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 449985000
Total number of copy operations 674556588
Array status: not sorted by weight before calling insertion sort
Array status: sorted by weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 224882189
Total number of copy operations 224912194
Array status: not sorted by weight before calling merge sort
Array status: sorted by weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 408610
Total number of copy operations 894464
Array status: not sorted by weight before calling merge/insertion sort
Array status: sorted by weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 452094
Total number of copy operations 818673
Array status: not sorted by weight before calling quick sort
Array status: sorted by weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 553261
Total number of copy operations 377085

========
Processing Criteria 2 and file 40K.txt
========
Array status: not sorted by weight before calling selection sort
Array status: sorted by weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 799980000
Total number of copy operations 119997
Array status: not sorted by weight before calling bubble sort
Array status: sorted by weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 799980000
Total number of copy operations 1192463478
Array status: not sorted by weight before calling insertion sort
Array status: sorted by weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 397527819
Total number of copy operations 397567824
Array status: not sorted by weight before calling merge sort
Array status: sorted by weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 561895
Total number of copy operations 1228928
Array status: not sorted by weight before calling merge/insertion sort
Array status: sorted by weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 655311
Total number of copy operations 1142482
Array status: not sorted by weight before calling quick sort
Array status: sorted by weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 703869
Total number of copy operations 520740

========
Processing Criteria 2 and file 50K.txt
========
Array status: not sorted by weight before calling selection sort
Array status: sorted by weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 1249975000
Total number of copy operations 149997
Array status: not sorted by weight before calling bubble sort
Array status: sorted by weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 1249975000
Total number of copy operations 1868092779
Array status: not sorted by weight before calling insertion sort
Array status: sorted by weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 622747586
Total number of copy operations 622797591
Array status: not sorted by weight before calling merge sort
Array status: sorted by weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 718213
Total number of copy operations 1568928
Array status: not sorted by weight before calling merge/insertion sort
Array status: sorted by weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 882708
Total number of copy operations 1490351
Array status: not sorted by weight before calling quick sort
Array status: sorted by weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 951302
Total number of copy operations 654051

========
Processing Criteria 2 and file 60K.txt
========
Array status: not sorted by weight before calling selection sort
Array status: sorted by weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 1799970000
Total number of copy operations 179997
Array status: not sorted by weight before calling bubble sort
Array status: sorted by weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 1799970000
Total number of copy operations 2687902794
Array status: not sorted by weight before calling insertion sort
Array status: sorted by weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 896027591
Total number of copy operations 896087596
Array status: not sorted by weight before calling merge sort
Array status: sorted by weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 877162
Total number of copy operations 1908928
Array status: not sorted by weight before calling merge/insertion sort
Array status: sorted by weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 964312
Total number of copy operations 1757673
Array status: not sorted by weight before calling quick sort
Array status: sorted by weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 1124555
Total number of copy operations 807789

========
Processing Criteria 3 and file 10K.txt
========
Array status: not sorted by name and weight before calling selection sort
Array status: sorted by name and weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 49995000
Total number of copy operations 29997
Array status: not sorted by name and weight before calling bubble sort
Array status: sorted by name and weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 49995000
Total number of copy operations 74790486
Array status: not sorted by name and weight before calling insertion sort
Array status: sorted by name and weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 24940152
Total number of copy operations 24950160
Array status: not sorted by name and weight before calling merge sort
Array status: sorted by name and weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 120572
Total number of copy operations 267232
Array status: not sorted by name and weight before calling merge/insertion sort
Array status: sorted by name and weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 143848
Total number of copy operations 245557
Array status: not sorted by name and weight before calling quick sort
Array status: sorted by name and weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 156239
Total number of copy operations 114117

========
Processing Criteria 3 and file 20K.txt
========
Array status: not sorted by name and weight before calling selection sort
Array status: sorted by name and weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 199990000
Total number of copy operations 59997
Array status: not sorted by name and weight before calling bubble sort
Array status: sorted by name and weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 199990000
Total number of copy operations 301237782
Array status: not sorted by name and weight before calling insertion sort
Array status: sorted by name and weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 100432583
Total number of copy operations 100452592
Array status: not sorted by name and weight before calling merge sort
Array status: sorted by name and weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 261065
Total number of copy operations 574464
Array status: not sorted by name and weight before calling merge/insertion sort
Array status: sorted by name and weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 307097
Total number of copy operations 530613
Array status: not sorted by name and weight before calling quick sort
Array status: sorted by name and weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 352058
Total number of copy operations 242331

========
Processing Criteria 3 and file 30K.txt
========
Array status: not sorted by name and weight before calling selection sort
Array status: sorted by name and weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 449985000
Total number of copy operations 89997
Array status: not sorted by name and weight before calling bubble sort
Array status: sorted by name and weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 449985000
Total number of copy operations 679601934
Array status: not sorted by name and weight before calling insertion sort
Array status: sorted by name and weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 226563967
Total number of copy operations 226593976
Array status: not sorted by name and weight before calling merge sort
Array status: sorted by name and weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 408638
Total number of copy operations 894464
Array status: not sorted by name and weight before calling merge/insertion sort
Array status: sorted by name and weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 452629
Total number of copy operations 819164
Array status: not sorted by name and weight before calling quick sort
Array status: sorted by name and weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 526003
Total number of copy operations 377241

========
Processing Criteria 3 and file 40K.txt
========
Array status: not sorted by name and weight before calling selection sort
Array status: sorted by name and weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 799980000
Total number of copy operations 119997
Array status: not sorted by name and weight before calling bubble sort
Array status: sorted by name and weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 799980000
Total number of copy operations 1208326263
Array status: not sorted by name and weight before calling insertion sort
Array status: sorted by name and weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 402815410
Total number of copy operations 402855419
Array status: not sorted by name and weight before calling merge sort
Array status: sorted by name and weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 561830
Total number of copy operations 1228928
Array status: not sorted by name and weight before calling merge/insertion sort
Array status: sorted by name and weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 655318
Total number of copy operations 1142472
Array status: not sorted by name and weight before calling quick sort
Array status: sorted by name and weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 725886
Total number of copy operations 513114

========
Processing Criteria 3 and file 50K.txt
========
Array status: not sorted by name and weight before calling selection sort
Array status: sorted by name and weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 1249975000
Total number of copy operations 149997
Array status: not sorted by name and weight before calling bubble sort
Array status: sorted by name and weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 1249975000
Total number of copy operations 1890294675
Array status: not sorted by name and weight before calling insertion sort
Array status: sorted by name and weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 630148214
Total number of copy operations 630198223
Array status: not sorted by name and weight before calling merge sort
Array status: sorted by name and weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 718177
Total number of copy operations 1568928
Array status: not sorted by name and weight before calling merge/insertion sort
Array status: sorted by name and weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 880437
Total number of copy operations 1487925
Array status: not sorted by name and weight before calling quick sort
Array status: sorted by name and weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 942130
Total number of copy operations 655140

========
Processing Criteria 3 and file 60K.txt
========
Array status: not sorted by name and weight before calling selection sort
Array status: sorted by name and weight after calling selection sort
Total time taken time_taken second
Total number of comparisons 1799970000
Total number of copy operations 179997
Array status: not sorted by name and weight before calling bubble sort
Array status: sorted by name and weight after calling bubble sort
Total time taken time_taken second
Total number of comparisons 1799970000
Total number of copy operations 2712594312
Array status: not sorted by name and weight before calling insertion sort
Array status: sorted by name and weight after calling insertion sort
Total time taken time_taken second
Total number of comparisons 904258092
Total number of copy operations 904318102
Array status: not sorted by name and weight before calling merge sort
Array status: sorted by name and weight after calling merge sort
Total time taken time_taken second
Total number of comparisons 877199
Total number of copy operations 1908928
Array status: not sorted by name and weight before calling merge/insertion sort
Array status: sorted by name and weight after calling merge/insertion sort
Total time taken time_taken second
Total number of comparisons 964550
Total number of copy operations 1757656
Array status: not sorted by name and weight before calling quick sort
Array status: sorted by name and weight after calling quick sort
Total time taken time_taken second
Total number of comparisons 1109563
Total number of copy operations 797058
```

Your code should produce 3 CSV files for three criteria of sorting. The filename should be criteria_x.csv where x is the criteria number. The CSV file should contain the following information in the following format:

DataSize, SelectionSortCompare, SelectionSortCopy, SelectionSortTIme, BubbleSortCompare, BubbleSortCopy, BubbleSortTime, InsertionSortCompare, InsertionSortCopy, InsertionSortTime, MergeSortCompare, MergeSortCopy, MergeSortTime, Merge_InsertionSortCompare, Merge_InsertionSortCopy, Merge_InsertionSortTime, QuickSortCompare, QuickSortCopy, QuickSortTime

100,000 values of each of the above column separated by comma
200,000 values of each of the above column separated by comma 
....... 
700,000 values of each of the above column separated by comma

## Additional Submission (PDF file)

You also need to submit a PDF file with a brief analysis report based on the experiment and comparison. Your report should contain the tables you have generated in each of the CSV files. 

Next, you mainly need to show 9 plots (3 criteria and each criterion has 3 matrices to compare [#compare, #copy, execution time]) in the report and add explanation of the plots about the performance of different sorting algorithms. In each plot, you should combine all the sorting algorithms so that you can easily compare them.
