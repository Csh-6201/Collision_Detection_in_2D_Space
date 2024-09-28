#ifndef KDTree_H
#define KDTree_H

typedef struct Point {
	int x;
	int y;
}Point;

typedef struct treenode {
	Point point;
	struct treenode* left;
	struct treenode* right;
}Node;

Point* read_points(char* filename, int* numPoints);

Node* create_node(Point point);

int compareX(const void* a, const void* b);

int compareY(const void* a, const void* b);

Node* build_tree(Point* points, int num, int death);

//bool ptpdistance(Node* treenode, int cx, int cy, int radius);

//int find_collisions();

//void free_tree(Node* root);



#endif

