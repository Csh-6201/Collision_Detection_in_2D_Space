#include <stdio.h>
#include <stdlib.h>
#include "KDtree.h"

Node* build_tree(Node* root, int death);

int find_collisions();

void destroy_tree(Node* root);



//free every node in tree
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