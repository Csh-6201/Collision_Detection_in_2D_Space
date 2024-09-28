#include <stdio.h>
#include <stdlib.h>
#include "KDtree.h"

int main(int argc, char *argv){

    int numPoints;
    int death = 0;
    Point* points = read_points("points.txt", &numPoints);

     
    free(points);
    //free_tree(&root);
    
}


/*
    //test of read_points
    for (int i = 0; i < numPoints; i++) {
        printf("Point %d: (%d, %d)\n", i + 1, points[i].x, points[i].y);
    }
*/


/*
//test of build_tree
int main() {
    // Test points
    Point points[] = {
        {3, 6},
        {17, 15},
        {13, 15},
        {6, 12},
        {9, 1},
        {2, 7},
        {10, 19}
    };

    int numPoints = sizeof(points) / sizeof(points[0]);

    // Build the k-d tree
    Node* root = build_tree(points, numPoints, 0);

    // Print the k-d tree to verify it
    printf("k-d Tree (pre-order traversal):\n");
    print_tree(root, 0);

    // Free memory for the tree (you should implement a function to free the tree)
    // free_tree(root); // Not implemented in this example

    return 0;
}
*/
