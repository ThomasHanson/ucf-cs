


# Programming Assignment :two:

This program is intended to implement the circular doubly linked list and queue data structures.

## Problem: Who Will Survive?

Before beginning to tackle this assignment, it should be known that this assignment is meant to be considered as a game, with no relation with reality. It is meant to help practice some problem-solving strategies.

Horror Kingdom has trapped G groups of soldiers of their opponent. They want to execute them. They found out a strategy in which the prisoners will kill each other and at the end one prisoner will be alive and he will be released. The kingdom has 10 execution grounds, one after another. Each ground has a name and are numbered with a sequence number starting from 1 to 10. As part of the strategy, each group is placed to an execution ground. The groups are numbered based on the assigned execution ground number. Note that G is assumed to be less than or equal to 10 and as a result some grounds could be empty. 

Each group g<sub>i</sub> has n<sub>i</sub> (n<sub>i</sub> ≥ 2) number of soldiers. As part of the process, they labeled each soldier of a group with a sequence number starting from 1 and ending at n<sub>i</sub>. All the n<sub>i</sub> number of prisoners of group g<sub>i</sub> are standing in a circle and waiting to be executed. However, due to distraction it was found out that all prisoners in all the groups were standing in reverse order instead of proper order.

After realizing the wrong order of sequence, they reversed the circle to the correct order.
**Note:** the nodes have not just changed their labels, they have physically changed their order.

The execution process is divided into two phases.

## Phase 1 Execution:

In Phase 1, the execution happens within the group and this phase of execution for a group g<sub>i</sub> stops when the total number of soldiers for the group reduced to a threshold th<sub>i</sub> (th<sub>i</sub> < n<sub>i</sub>). Now, they will start the executing process. The counting out begins from the first soldier in the circle of the group and proceeds around the circle in a fixed direction. In each step, a certain number of people k<sub>i - 1</sub> (k<sub>i<sub>th</sub></sub> > 0) are skipped and the next person is executed. The elimination proceeds around the circle, which is becoming smaller and smaller as the executed people are removed. As mentioned, the execution process for the group g<sub>i</sub> will stop when the group has th<sub>i</sub>.

In summary, for a group g<sub>i</sub>, you have the total number of soldiers n<sub>i</sub> (n<sub>i</sub> ≥ 2), and a number k<sub>i</sub> (k<sub>i</sub> > 0), which indicates that k<sub>i - 1</sub> persons are skipped and k<sub>i<sub>th</sub></sub> person is killed in circle. There is a threshold th<sub>i</sub> (th<sub>i</sub> < n<sub>i</sub>) that indicates to stop killing when the number of solders of the group reduced to th<sub>i</sub>. The same process should be applied to all the groups according to their own n, k and th. The remaining solders will be transferred to phase 2.

### Example 1

A group has n = 5, k = 2, and th = 2

Phase 1:
* First, the soldier at position 2 is killed.
* Then the soldier at position 4 is killed.
* Then soldier at position 1 is killed. 
* As there are only two persons remaining (soldiers 3 and 5), the execution process for this phase for the group will stop. 
* The remaining soldiers will be transferred to phase 2 

### Example 2

A group has n = 7, k = 3, and th = 3

Phase 1:
* The soldiers at positions 3, 6, 2, and 7 will be executed.
* The remaining soldiers 1, 4, and 5 will be transferred to phase 2.

## Phase 2 Execution:

In phase 2, the execution will happen across the groups with the following strategy:
* The highest solder number across all the fronts of the groups will be executed.
* If the highest solder number is standing in the fronts of multiple groups, the soldier standing on the smallest execution ground number will be executed first to break the tie.
* Keep following until there is only one solder remaining among all the groups and that solder will be the winner and will be released!

Please see the example from the sample input/output for better clarification.

## Input Specification

The input has to be read from `in.txt` file. The first line of the file contains the number of groups G captured by the kingdom. The next G lines contain the information of the groups.

For each line of a group, the first integer indicates the ground number g<sub>i</sub> (g<sub>i</sub> ≤ 10), then next item is a string that indicates the name of the execution ground (maximum length 50), the next integer indicates the number of soldier n<sub>i</sub> in the group (≤ 10,000), the next integer indicates the value of k<sub>i</sub> (n<sub>i</sub> > k<sub>i</sub> > 0) and then the next integer indicates the value of th<sub>i</sub> (n<sub>i</sub> > th<sub>i</sub> > 0) integer.

## Output Specification

The output of the program must be written to the `out.txt` file. It should contain the exact same format as specified in the sample output. The output mainly consists the steps of each simulation. The last line will contain the survived soldier number, along with the ground number.

## Example Input & Output

### Example Input

```
5
4 jubei 7 3 3
6 ukyo 5 2 3
1 samurai 10 3 2 
7 haohmaru 9 2 4 
3 galford 8 2 1
```

### Example Output

```
Initial nonempty lists status
1 samurai 10 9 8 7 6 5 4 3 2 1
3 galford 8 7 6 5 4 3 2 1
4 jubei 7 6 5 4 3 2 1
6 ukyo 5 4 3 2 1
7 haohmaru 9 8 7 6 5 4 3 2 1

After ordering nonempty lists status
1 samurai 1 2 3 4 5 6 7 8 9 10
3 galford 1 2 3 4 5 6 7 8
4 jubei 1 2 3 4 5 6 7
6 ukyo 1 2 3 4 5
7 haohmaru 1 2 3 4 5 6 7 8 9

Phase1 execution

Line# 1 samurai
Soldier# 3 executed
Soldier# 6 executed
Soldier# 9 executed
Soldier# 2 executed
Soldier# 7 executed
Soldier# 1 executed
Soldier# 8 executed
Soldier# 5 executed

Line# 3 galford
Soldier# 2 executed
Soldier# 4 executed
Soldier# 6 executed
Soldier# 8 executed
Soldier# 3 executed
Soldier# 7 executed
Soldier# 5 executed

Line# 4 jubei
Soldier# 3 executed
Soldier# 6 executed
Soldier# 2 executed
Soldier# 7 executed

Line# 6 ukyo
Soldier# 2 executed
Soldier# 4 executed

Line# 7 haohmaru
Soldier# 2 executed
Soldier# 4 executed
Soldier# 6 executed
Soldier# 8 executed
Soldier# 1 executed

Phase2 execution
Executed Soldier 4 from line 1
Executed Soldier 10 from line 1
Executed Soldier 3 from line 7
Executed Soldier 5 from line 7
Executed Soldier 7 from line 7
Executed Soldier 9 from line 7
Executed Soldier 1 from line 3
Executed Soldier 1 from line 4
Executed Soldier 4 from line 4
Executed Soldier 5 from line 4
Executed Soldier 1 from line 6
Executed Soldier 3 from line 6

Soldier 5 from line 6 will survive
```

## Implementation Restrictions

* You must use linked lists and queues in your implementation.
* You must use circular doubly linked list in your solution to get full credit.
* You need to declare doubly linked list node structure to store a soldier with sequence number as the data value.
* You have to use linked list implementation of queue.
* Create a node structure for Soldier that has a sequenceNumber and next and prev pointer.
* Create a node structure for a queue that has front and back pointers to point soldiers.
* You have to implement and use enqueue, dequeue, peek, isEmpty function for this given scenario.

In addition to the other functions of a queue like enqueue, dequeue, you code must have to implement the following functions and use them part of the solution:

```c
  soldier* createSoldier(int sequence)
```
This function takes in an integer and returns a dynamically allocated soldier structure.

```c
  void createReverseCircle(queue *q)
```
This function takes a queue reference, and creates a circular doubly linked list (in reversed order, by sequence numbers). For example, if n=5 it should produce a circular doubly linked list starting from 5 and ending at 1 as sequence number. During this process, use the create_soldier() function as well as enqueue() function to add the soldier to the queue.
```c
  void rearrangeCircle(queue *q)
```
This function takes the reference of a queue and reverse the given circular doubly linked list where the first node of the linked list is pointed by the front of the queue.

```c
  void display(queue q)
```

This function displays a given queue.

* You also have to use memory leak detector in your code (same implementation as Programming Assignment 1).
