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


Node* create_node(Point point) {

	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->point = point;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;

}


// A comparison function that determines the order of the elements
// If int_a < int_b: This means a should come before b, return -1.
// If int_a > int_b: This means a should come after b, return 1.
// If int_a == int_b : This means both elements are equal, return 0
int compareX(const void* a, const void* b) {
	
	// (Point*)a: converts the void * pointer a into an Point * pointer
	// *(Point*)a: dereferences the Point * pointer
	int a_x = (*(Point*)a).x;
	int b_x = (*(Point*)b).x;

	if (a_x > b_x) {
		return 1;
	}
	else if (a_x < b_x) {
		return -1;
	}
	else {
		return 0;
	}

}


int compareY(const void* a, const void* b) {
	
	int a_y = (*(Point*)a).y;
	int b_y = (*(Point*)b).y;

	if (a_y > b_y) {
		return 1;
	}
	else if (a_y < b_y) {
		return -1;
	}
	else {
		return 0;
	}

}


Node* build_tree(Point* points, int num, int depth) {

	// Base case: no points to split, return NULL
	if (num <= 0) {
		return NULL;
	}

	int axis = depth % 2;

	// x-axis = 0, y-axis = 1
	if (axis == 0) {
		qsort(points, num, sizeof(Point), compareX);
	}
	else if (axis == 1) {
		qsort(points, num, sizeof(Point), compareY);
	}

	int mid_index = num / 2;
	
	Node* root = create_node(points[mid_index]);

	// In C, arrays are closely related to pointers. 
	// points + index: passing a pointer to the element at position index in the array.
	// The elements in the array are stored in contiguous memory.
	root->left = build_tree(points, mid_index, depth + 1);
	root->right = build_tree(points + mid_index + 1, num - mid_index - 1, depth + 1);

	return root;
}

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

// Function to print the k-d tree (pre-order traversal)
void print_tree(Node* root, int depth) {
	if (root == NULL) {
		return;
	}

	// Print the current node
	printf("Depth %d: (%d, %d)\n", depth, root->point.x, root->point.y);

	// Recursively print the left and right subtrees
	print_tree(root->left, depth + 1);
	print_tree(root->right, depth + 1);
}
