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

Node* build_tree(Point* points, int num, int depth);

bool check_distance(Point point, Point center, int radius);

int find_collisions(Node* root, Point center, int radius, int depth);

void free_tree(Node* root);

#endif

