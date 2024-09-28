#include <stdio.h>
#include <stdlib.h>
#include "KDtree.h"

int main(int argc, char *argv){

    int numPoints;
    Point* points = read_points("points.txt", &numPoints);

    //test of read_points
    for (int i = 0; i < numPoints; i++) {
        printf("Point %d: (%d, %d)\n", i + 1, points[i].x, points[i].y);
    }
     
    free(points);
    //free_tree(&root);
    
}


/*
    //test of read_points
    for (int i = 0; i < numPoints; i++) {
        printf("Point %d: (%d, %d)\n", i + 1, points[i].x, points[i].y);
    }
*/

