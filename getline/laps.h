#ifndef MAIN_H
#define MAIN_H
#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>

/**
 * struct CarNode- node of a binary search tree for a car
 * @id: id of the car
 * @laps: lap the car is on
 * @left: pointer to left child
 * @right: pointer to right child
 */

typedef struct CarNode
{
	int id;
	int laps;
	struct CarNode *left;
	struct CarNode *right;
} CarNode;

CarNode *newCarNode(int id);
CarNode *insertCarNode(CarNode *node, int id);
void printRaceState(CarNode *node);
void freeCarNodes(CarNode *node);
void race_state(int *id, size_t size);

#endif

