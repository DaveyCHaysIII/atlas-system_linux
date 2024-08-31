#include <stdio.h>
#include <stdlib.h>
#include "laps.h"

/**
 * newCarNode- function to make a new car
 * @id: the name of the car
 *
 * Return: pointer to new node
 */

CarNode *newCarNode(int id)
{
	CarNode *node = (CarNode *)malloc(sizeof(CarNode));

	if (!node)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	node->id = id;
	node->laps = 0;
	node->left = node->right = NULL;
	return (node);
}

/**
 * insertCarNode- inserts a new car into the bst
 * @node: the node in question
 * @id: the id to pass to the new node
 *
 * Return: pointer to inserted node
 */

CarNode *insertCarNode(CarNode *node, int id)
{
	if (node == NULL)
	{
		printf("Car %d joined the race\n", id);
		return (newCarNode(id));
	}

	if (id < node->id)
	{
		node->left = insertCarNode(node->left, id);
	}
	else if (id > node->id)
	{
		node->right = insertCarNode(node->right, id);
	}
	else
	{
		node->laps++;
	}
	return (node);
}

/**
 * printRaceState- prints the state of the race
 * @node: the root node of the bst
 */

void printRaceState(CarNode *node)
{
	if (node != NULL)
	{
		printRaceState(node->left);
		printf("Car %d [%d laps]\n", node->id, node->laps);
		printRaceState(node->right);
	}
}

/**
 * freeCarNodes- frees the bst
 * @node: root of bst
 */

void freeCarNodes(CarNode *node)
{
	if (node != NULL)
	{
		freeCarNodes(node->left);
		freeCarNodes(node->right);
		free(node);
	}
}

/**
 * race_state- initializes race
 * @id: array of ids to initialize
 * @size: size of id array
 */

void race_state(int *id, size_t size)
{
	if (size == 0)
	{
		freeCarNodes(root);
		root = NULL;
		return;
	}
	for (size_t i = 0; i < size; i++)
	{
		root = insertCarNode(root, id[i]);
	}
	printf("Race state:\n");
	printRaceState(root);
}

