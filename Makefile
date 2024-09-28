all: a5
a5: a5.c KDtree.c
	gcc a5.c KDtree.c -o a5