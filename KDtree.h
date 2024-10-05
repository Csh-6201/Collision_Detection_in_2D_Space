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

static inline Node* create_node(Point point) {

	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->point = point;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;

}

static inline void swap(Point* a, Point* b) {

	Point temp = *a;
	*a = *b;
	*b = temp;

}

int partition(Point* points, int low, int high, int axis);

void quickselect(Point* points, int low, int high, int k, int axis);

Node* build_tree(Point* points, int num, int depth);

bool check_distance(Point point, Point center, int radius);

int find_collisions(Node* root, Point center, int radius, int depth);

void free_tree(Node* root);

#endif


//int compareX(const void* a, const void* b);

//int compareY(const void* a, const void* b);