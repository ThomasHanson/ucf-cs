/* COP 3502C Assignment 2
This program is written by: Thomas Hanson */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define MAX_GROUPS 10

typedef struct soldier {
    int sequenceNumber;
    struct soldier *next, *prev;
} soldier;

typedef struct queue {
    soldier *head, *tail;
    int gNum, nodeCount, k, th;
    char *name;
} queue;

// global output file so we can call various functions
FILE* outfile;

/*
 * Creats a new soldier with a designated
 * sequence number
 */
soldier* createSoldier(int sequence) {
    
    // allocates the proper memory for the soldier
    soldier *soldier = malloc(sizeof(soldier));
    
    soldier->sequenceNumber = sequence;
    
    // initializes the soldier pointers
    soldier->next = soldier->prev = NULL;
    
    // returns our new soldiuer
    return soldier;
}

/*
 * Checks to see if the queue is empty
 */
int isEmpty(queue *q) {
    return !q->head;
}

/*
 * Peeks the queue and returns the head
 * soldiers sequence number. Returns -1
 * if the queue is empty.
 */
int peek(queue *q) {
    return isEmpty(q) ? -1 : q->head->sequenceNumber;
}

/*
 * Displays the queue from the head to the tail
 */
void display(queue *q) {
    
    if (isEmpty(q))
        return;
    
    // assigns the values to traverse the queue
    soldier *head = q->head;
    soldier *current = head;
    
    fprintf(outfile, "%d %s %d", q->gNum, q->name, head->sequenceNumber);
    
    // keep traversing
    head = head->next;
    
    while (current != head) {
        fprintf(outfile, " %d", head->sequenceNumber);
        head = head->next;
    }
    
    fprintf(outfile, "\n");
}

/*
 * Enqueues a new soldier value
 */
void enqueue(queue *q, int sequenceNumber) {
    
    // create a new soldier from scratch
    soldier *new = createSoldier(sequenceNumber);
    
    /*
     * If there is no head, make the new
     * value the head. Then point the next
     * to itself to make a circle.
     */
    if (!q->head) {
        
        q->head = new;
        q->head->next = q->head->prev = q->head;
        
        return;
    }
    
    /*
     * If there is a head, create the circular
     * principle, and point all other next/prev
     * pointers to this value.
     */
     
    new->next = q->head;
    new->prev = q->head->prev;
    
    new->prev->next = new;
    
    // Assign head and tail values
    q->head->prev = new;
    q->tail = new;
}

/*
 * Dequeues the first value in the list
 */
int dequeue(queue *q) {
    
    if (isEmpty(q))
        return -1;
    
    // create temporary value to free later
    soldier *temp;
    
    // save the head value we dequeue to return
    int value = q->head->sequenceNumber;
    
    /*
     * If the next value IS the head, set to null and free
     */
    if(q->head->next == q->head) {
        
        q->head = NULL;
        free(q->head);
        
    } else {
        
        /*
         * Set temp to head, keep traversing, and
         * reassign next and prev pointers accordingly
         */
        
        temp = q->head;
        
        while(temp->next != q->head) {
            temp = temp->next;
        }
        
        temp->next = q->head->next;
        q->head->next->prev = temp;
        
        free(q->head);
        q->head = temp->next;
    }
    
    // readjust the number of soldiers
    q->nodeCount--;
  
    return value;
}

/*
 * Reverses the original input values
 * and enqueues them into our queue
 */
void createReverseCircle(queue *q) {
    
    for (int i = q->nodeCount; i > 0; i--) {
        enqueue(q, i);
    }
}

/*
 * Fixes our values so they are in
 * the right order and we can start
 * our phase1 function.
 */
void rearrangeCircle(queue *q) {
    
   if (isEmpty(q))
        return;
    
    // create our temp/current values for traversing
    soldier *current = q->head;
    soldier *temp;
    
    do {
        
        /*
         * We need the temp variable to swap variables.
         * Our goal is to flip the next and prev pointers
         * so that it will print correctly.
         */
        temp = current->prev;
        
        current->prev = current->next;
        current->next = temp;
        
        current = current->next;
        
    } while (current != q->head);
    
    // keep traversing
    q->head = q->head->next;
}

/*
 * Runs our phase 1 to kill until we reach our threshold
 */
void* phase1(queue *q) {
    
    // make sure there are soldiers and that k is > 0
    if (isEmpty(q) || q->nodeCount <= 0 || q->k <= 0)
        return NULL;
    
    fprintf(outfile, "\nLine# %d %s\n", q->gNum, q->name);
    
    // start traversing the queue
    soldier *current = q->head;
    
    // making sure we don't circle around or pass the threshold
    while (current->next != current && q->nodeCount > q->th) {
        
        // skip k-1 soldiers
        for (int i = 0; i < q->k - 1; i++) {
            current = current->next;
        }
        
        // create temp variable to reassign the circular queue
        soldier *temp = current;
        
        if (temp == q->head) {
            q->head = current->next;
            q->tail->next = q->head;
            
        } else if (temp == q->tail) {
            q->tail = current->prev;
            q->head->prev = q->tail;
        }
        
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        
        fprintf(outfile, "Soldier# %d executed\n", temp->sequenceNumber);
        free(temp);
        
        current = temp->next;
        
        // adjust soldier count
        q->nodeCount--;
    }
}

/*
 * Runs our phase 2 to keep going until 1 is left
 */
void phase2(queue** grounds, int survivors) {
    
    int killingGround;
    
    while (survivors > 1) {
        
        int largestSoldier = 0, lowestGround = 0, killingGround = 0;
        
        for (int g = 0; g < MAX_GROUPS; g++) {
            
            if (grounds[g]) {
                
                queue *ground = grounds[g];
                
                int head = peek(ground);
                
                if (head > largestSoldier) {
                    
                    largestSoldier = head;
                    killingGround = g;
                    
                } else if (head == largestSoldier) {
                    
                    if (g < lowestGround) {
                        killingGround = g;
                    }
                }
            }
        }
        
        survivors--;
        fprintf(outfile, "Executed Soldier %d from line %d\n", dequeue(grounds[killingGround]), killingGround + 1);
    }
    
    for (int i = 0; i < MAX_GROUPS; i++) {
        
        if (grounds[i]) {
            
            queue *ground = grounds[i];
            
            if (ground->nodeCount > 0) {
                fprintf(outfile, "\nSoldier %d from line %d will survive", ground->head->sequenceNumber, ground->gNum);
            }
        }
    }
}

/*
 * Free all of our grounds and soldiers
 */
void freeGrounds(queue** grounds) {
    
    for (int g = 0; g < MAX_GROUPS; g++) {
        
        if (grounds[g]) {
            
            queue *ground = grounds[g];
            
            free(ground->head);
            free(ground);
        }
    }
    
    free(grounds);
}

int main() {
    
    // leak detector
    atexit(report_mem_leak);
    
    // file management
    FILE *infile = fopen("int.txt", "r");
    outfile = fopen("out.txt", "w");
    
    // soldier and group properties
    char gName[51];
    int totalSurvivors, numGroups, gNum, numSoldiers, k, th;
    
    fscanf(infile, "%d", &numGroups);
    
    // allocate memory for our queue
    queue** grounds = malloc(MAX_GROUPS * sizeof(queue*));
    
    for (int i = 0; i < numGroups; i++) {
        
        fscanf(infile, "%d %s %d %d %d", &gNum, gName, &numSoldiers, &k, &th);
        
        queue *q = malloc(sizeof(queue));
        
        q->name = strdup(gName);
        
        q->gNum = gNum;
        q->nodeCount = numSoldiers;
        q->k = k;
        q->th = th;
        
        grounds[gNum - 1] = q;
    }
    
    fprintf(outfile, "Initial nonempty lists status\n");
    
    for (int g = 0; g < MAX_GROUPS; g++) {
        if (grounds[g]) {
            createReverseCircle(grounds[g]);
            display(grounds[g]);
        }
    }
    
    fprintf(outfile, "\nAfter ordering nonempty lists status\n");
    
    for (int g = 0; g < MAX_GROUPS; g++) {
        if (grounds[g]) {
            rearrangeCircle(grounds[g]);
            display(grounds[g]);
        }
    }
    
    fprintf(outfile, "\nPhase1 execution\n");
    
    for (int g = 0; g < MAX_GROUPS; g++) {
        if (grounds[g]) {
            phase1(grounds[g]);
            totalSurvivors += grounds[g]->nodeCount;
        }
    }
    
    fprintf(outfile, "\nPhase2 execution\n");
    phase2(grounds, totalSurvivors);
    
    freeGrounds(grounds);

    return 0;
}
