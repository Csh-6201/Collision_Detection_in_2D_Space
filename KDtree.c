#include <stdio.h>
#include <stdlib.h>
#include "KDtree.h"


Point* read_points(char* filename, int* numPoints) {

	FILE* fptr;
	int count = 0;
	int x, y;
	int index = 0;

	fptr = fopen(filename, "r");
	if (!fptr) {
		return NULL;
	}

	// Count the number of points in the file
	while (fscanf(fptr, "%d %d", &x, &y) == 2) {
		count++;
	}

	// Allocate memory for all the points
	Point* points = (Point*)malloc(count * sizeof(Point));
	if (!points) {
		fclose(fptr);
		return NULL;
	}

	// Rewind the file to start reading points, and store the data
	rewind(fptr);
	while (fscanf(fptr, "%d %d", &x, &y) == 2) {
		points[index].x = x;
		points[index].y = y;
		index++;
	}
	fclose(fptr);

	*numPoints = count;
	return points;

}




Node* build_tree(Node* root, int death);

int find_collisions();

void destroy_tree(Node* root);



//free every node in tree(need change)
void free_tree(Node* treenode) {

	if (treenode == NULL) {
		return;
	}
	else {
		free_tree(treenode->left);
		free_tree(treenode->right);
	}

	free(treenode);

}