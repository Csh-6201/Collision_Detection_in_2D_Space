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

//Node* build_tree(Node *root, int death);

//bool ptpdistance(Node* treenode, int cx, int cy, int radius);

//int find_collisions();

//void free_tree(Node* root);



#endif

