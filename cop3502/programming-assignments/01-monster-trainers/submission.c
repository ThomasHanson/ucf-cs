/* COP 3502C Assignment 1
This program is written by: Thomas Hanson */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "leak_detector_c.h"

#define MAX_STRING_LENGTH 50

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

/*
 * Monster functions
 */
monster* createMonster(char *name, char *element, int population);

monster** readMonsters(FILE *inFile, int *monsterCount);

void freeMonsters(int monsterCount, monster **monsters);

/*
 * Region functions
 */
region* createRegion(char *name, int numMonsters, int totalPopulation, monster **monsters);

region **readRegions(FILE *inFile, int *regionCount, monster **monsters, int numMonsters);

void freeRegions(int regionCount, region **regions);

/*
 * Trainer functions
 */
trainer* createTrainer(char *name, int numRegions, region **regions, int captures);

trainer** readTrainers(FILE *inFile, int *trainerCount, int numRegions, region **regions);

void freeTrainers(int trainerCount, trainer **trainers);

/*
 * Utility functions
 */
void memoryExit(char *error);
int findMonster(monster **monsters, int monsterCount, char *name);

int main(void) {

  // Check for memory leaks
  atexit(report_mem_leak);

  FILE *inFile = fopen("in.txt", "r");

  if (!inFile) {
    printf("Could not find input file!\n");
    exit(1);
  }

  FILE *outFile = fopen("out.txt", "w");

  int
    monsterCount = 0,
    regionCount = 0,
    trainerCount = 0;
  
  monster **monsters = readMonsters(inFile, &monsterCount);
  region **regions = readRegions(inFile, &regionCount, monsters, monsterCount);
  trainer **trainers = readTrainers(inFile, &trainerCount, regionCount, regions);

  for (int i = 0; i < trainerCount; i++) {

    trainer *trainer = trainers[i];

    fprintf(outFile, "%s\n", trainer->name);

    for (int j = 0; j < trainer->visits->numRegions; j++) {

      region *region = trainer->visits->regions[j];
      fprintf(outFile, "%s\n", region->name);

      for (int k = 0; k < region->numMonsters; k++) {

        monster *monster = region->monsters[k];

        int finalVal = round((1.0 * monster->population / region->totalPopulation) * trainer->visits->captures);

        if (finalVal > 0)
          fprintf(outFile, "%d %s\n", finalVal, monster->name);
      }
    }

    if (i + 1 < trainerCount)
      fprintf(outFile, "\n");
  }
  
  freeMonsters(monsterCount, monsters);
  freeRegions(regionCount, regions);
  freeTrainers(trainerCount, trainers);
    
  fclose(inFile);
  fclose(outFile);

  return 0;
}

/*
 * This function returns a dynamically allocated
 * monster filled with the provided parameters.
 */
monster* createMonster(char *name, char *element, int population) {

  monster *newMonster = malloc(sizeof(monster));

  if (!newMonster)
    memoryExit("new monster");

  newMonster->name = malloc((MAX_STRING_LENGTH + 1) * sizeof(char));
  
  if (!newMonster->name)
    memoryExit("monster name");

  strcpy(newMonster->name, name);

  newMonster->element = malloc((MAX_STRING_LENGTH + 1) * sizeof(char));

  if (!newMonster->element)
    memoryExit("monster element");

  strcpy(newMonster->element, element);

  newMonster->population = population;

  return newMonster;
}

/*
 * This function returns an array of double pointers
 * where each monster pointer points to the dynamically
 * allocated monsters, with information from the provided
 * input file.
 */
monster** readMonsters(FILE *inFile, int *monsterCount) {
    
  fscanf(inFile, "%d monsters", monsterCount);
    
  monster **monsters = malloc(*monsterCount * sizeof(monster*));

  if (!monsters)
    memoryExit("double monster");
    
  char
    name[MAX_STRING_LENGTH + 1],
    element[MAX_STRING_LENGTH + 1];

  int population;
    
  /*
   * For each monster, find parameters and call
   * helper function createMonster(...)
   */
  for (int i = 0; i < *monsterCount; i++) {
    fscanf(inFile, "%s %s %d", name, element, &population);
    monsters[i] = createMonster(name, element, population);
  }
  
  return monsters;
}

/*
 * Frees all memory associated to array of monster pointers.
 */
void freeMonsters(int monsterCount, monster **monsters) {
    
  for (int i = 0; i < monsterCount; i++) {
    free(monsters[i]->name);
    free(monsters[i]->element);
    free(monsters[i]);
  }

  free(monsters);
}

/*
 * This function returns a dynamically allocated
 * region filled with the provided parameters.
 */
region* createRegion(char *name, int numMonsters, int totalPopulation, monster **monsters) {

  region *newRegion = malloc(sizeof(region));

  if (!newRegion)
    memoryExit("new region");

  newRegion->name = malloc((MAX_STRING_LENGTH + 1) * sizeof(char));

  if (!newRegion->name)
    memoryExit("region name");

  strcpy(newRegion->name, name);

  newRegion->numMonsters = numMonsters;
  newRegion->totalPopulation = totalPopulation;
  newRegion->monsters = monsters;

  return newRegion;
}

/*
 * This function returns an array of double pointers
 * where each region pointer points to the dynamically
 * allocated regions, with information from the provided
 * input file.
 */
region** readRegions(FILE *inFile, int *regionCount, monster **monsters, int numMonsters) {

  fscanf(inFile, "%d regions", regionCount);
 
  region **regions = malloc(*regionCount * sizeof(region*));

  if (!regions)
    memoryExit("double regions");
  
  char
    name[MAX_STRING_LENGTH + 1],
    monsterName[MAX_STRING_LENGTH + 1];

  int regionMonsterCount;
 
  for (int i = 0; i < *regionCount; i++) {
 
    int totalPopulation = 0;
 
    fscanf(inFile, "%s", name);
    fscanf(inFile, "%d monsters", &regionMonsterCount);
        
    monster **regionMonsters = malloc(regionMonsterCount * sizeof(monster*));

    if (!regionMonsters)
      memoryExit("regions monsters");
    
    for (int j = 0; j < regionMonsterCount; j++) {
 
      fscanf(inFile, "%s", monsterName);
 
      for (int k = 0; k < numMonsters; k++) {
        
        if (strcmp(monsterName, monsters[k]->name) == 0) {

          // Makes sure we are not adding duplicate populations together
          if (findMonster(monsters, k, monsterName) == -1)
            totalPopulation += monsters[k]->population;

          regionMonsters[j] = monsters[k];
        }
      }
    }

    regions[i] = createRegion(name, regionMonsterCount, totalPopulation, regionMonsters);
  }
 
  return regions;
}

/*
 * Frees all memory associated to array of region pointers.
 */
void freeRegions(int regionCount, region **regions) {

  for (int i = 0; i < regionCount; i++) {
    free(regions[i]->monsters);
    free(regions[i]->name);
    free(regions[i]);
  }
    
  free(regions);
}

/*
 * This function returns a dynamically allocated
 * trainer filled with the provided parameters.
 */
trainer* createTrainer(char *name, int numRegions, region **regions, int captures) {
 
  trainer *newTrainer = malloc(sizeof(trainer));

  if (!newTrainer)
    memoryExit("new trainer");

  itinerary *visits = malloc(sizeof(itinerary));

  if (!visits)
    memoryExit("itinerary");
 
  newTrainer->name = malloc((MAX_STRING_LENGTH + 1) * sizeof(char));

  if (!newTrainer->name)
    memoryExit("trainer name");

  strcpy(newTrainer->name, name);

  visits->regions = malloc(numRegions * sizeof(region*));

  if (!visits->regions)
    memoryExit("itinerary regions");
 
  visits->numRegions = numRegions;
  visits->captures = captures;

  newTrainer->visits = visits;
 
  return newTrainer;
}

/*
 * This function returns an array of double pointers
 * where each trainer pointer points to the dynamically
 * allocated trainers, with information from the provided
 * input file.
 */
trainer** readTrainers(FILE *inFile, int *trainerCount, int numRegions, region **regions) {
    
  fscanf(inFile, "%d Trainers", trainerCount);
    
  trainer **trainers = malloc(*trainerCount * sizeof(trainer*));

  if (!trainers)
    memoryExit("double trainer");
    
  char
    trainerName[MAX_STRING_LENGTH + 1],
    regionName[MAX_STRING_LENGTH + 1];
    
  int captures, trainerRegionCount;
  
  /*
   * For each trainer, scan the name,
   * captures, and region, accordingly.
   * Use createTrainer(...) to fill in
   * the values.
   */
  for (int i = 0; i < *trainerCount; i++) {
        
    fscanf(inFile, "%s", trainerName);
    fscanf(inFile, "%d captures", &captures);
    fscanf(inFile, "%d regions", &trainerRegionCount);
    
    trainers[i] = createTrainer(trainerName, trainerRegionCount, regions, captures);
    
    for (int j = 0; j < trainerRegionCount; j++) {
        
      fscanf(inFile, "%s", regionName);

      for (int k = 0; k < numRegions; k++)
        if (strcmp(regionName, regions[k]->name) == 0)
          trainers[i]->visits->regions[j] = regions[k];
    }
  }

  return trainers;
}

/*
 * Frees all memory associated to array of trainer pointers.
 */
void freeTrainers(int trainerCount, trainer **trainers) {
    
  for (int i = 0; i < trainerCount; i++) {
    free(trainers[i]->name);
    free(trainers[i]->visits->regions);
    free(trainers[i]->visits);
    free(trainers[i]);
  }
    
  free(trainers);
}

/*
 * Helper function to safely exit program when memory
 * allocation fails. It takes in a character array to
 * identify which pointer failed when printing.
 */
void memoryExit(char *error) {
  printf("Could not allocate %s pointer!\n", error);
  exit(1);
}

/*
 * Helper function that will return the index of a
 * monster if it exists within the given array. If
 * it cannot be found, it will return -1.
 */
int findMonster(monster **monsters, int monsterCount, char *name) {

  for (int i = 0; i < monsterCount; i++)
    if (strcmp(monsters[i]->name, name) == 0)
      return i;
  
  return -1;
}
