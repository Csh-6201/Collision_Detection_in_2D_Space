#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "KDtree.h"

// @brief read all the points from the file
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

// @brief partition the array, fucntion as quickselect helper
int partition(Point* points, int low, int high, int axis) {

	Point pivot = points[high];
	int leftwall = low;
	int i;

	for (i = low; i < high; i++) {

		if (axis == 0) {
			if (points[i].x < pivot.x) {
				swap(&points[i], &points[leftwall]);
				leftwall++;
			}
		}
		else {
			if (points[i].y < pivot.y) {
				swap(&points[i], &points[leftwall]);
				leftwall++;
			}
		}

	}

	swap(&points[leftwall], &points[high]);
	return leftwall;

}

// @brief rearrange the array, find the k-th index in the array (recursively locating the midium of the array)
void quickselect(Point* points, int low, int high, int k, int axis) {

	if (low == high) {
		return;
	}
		
	int pivotIndex = partition(points, low, high, axis);

	if (pivotIndex == k) {
		return;
	}
	else if (pivotIndex > k) {
		quickselect(points, low, pivotIndex - 1, k, axis);
	}
	else {
		quickselect(points, pivotIndex + 1, high, k, axis);
	}

}

// @brief build the tree by quickselect
Node* build_tree(Point* points, int num, int depth) {

	// Base case: no points to split, return NULL
	if (num <= 0) {
		return NULL;
	}
	
	// x-axis = 0, y-axis = 1
	int axis = depth % 2;
	int mid_index = num / 2;
	quickselect(points, 0, num - 1, mid_index, axis);
	Node* root = create_node(points[mid_index]);

	// In C, arrays are closely related to pointers. 
	// points + index: passing a pointer to the element at position index in the array.
	// The elements in the array are stored in contiguous memory.
	root->left = build_tree(points, mid_index, depth + 1);
	root->right = build_tree(&points[mid_index + 1], num - mid_index - 1, depth + 1);

	return root;
}

// @brief check if the point is in the given circle
bool check_distance(Point point, Point center, int radius) {

	int dx = point.x - center.x;
	int dy = point.y - center.y;
	
	if (dx * dx + dy * dy <= radius * radius) {
		return true;
	}
	else {
		return false;
	}

}

// @brief recursively find the amount of the point in the given circle
int find_collisions(Node* root, Point center, int radius, int depth) {

	// Base case
	if (root == NULL) {
		return 0;
	}

	int count = 0;
	if (check_distance(root->point, center, radius)) {
		count++;
	}

	// x-axis = 0, y-axis = 1
	int axis = depth % 2;
	if (axis == 0) {
		if (center.x - radius <= root->point.x) {
			count += find_collisions(root->left, center, radius, depth + 1);
		}
		if (center.x + radius >= root->point.x) {
			count += find_collisions(root->right, center, radius, depth + 1);
		}
	}
	else if (axis == 1) {
		if (center.y - radius <= root->point.y) {
			count += find_collisions(root->left, center, radius, depth + 1);
		}
		if (center.y + radius >= root->point.y) {
			count += find_collisions(root->right, center, radius, depth + 1);
		}
	}

	return count;

}


// @brief recursively free every node in the tree
void free_tree(Node* treenode) {

	if (treenode == NULL) {
		return;
	}
	
	free_tree(treenode->left);
	free_tree(treenode->right);
	free(treenode);

}


// Function to print the k-d tree (pre-order traversal)
//void print_tree(Node* root, int depth) {
//	if (root == NULL) {
//		return;
//	}
//
//	// Print the current node
//	printf("Depth %d: (%d, %d)\n", depth, root->point.x, root->point.y);
//
//	// Recursively print the left and right subtrees
//	print_tree(root->left, depth + 1);
//	print_tree(root->right, depth + 1);
//}


/*for quicksort
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
*/