#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int a[] = {8, 2, 6, 9, 11, 3, 7, 5, 3, 15, 82, 33, 19, 49, 72, 22, 23, 30, 50};

	BST_PTR t = bst_create();

	for(i = 0; i < 19; i++)
		bst_insert(t, a[i]);

	int* b;
	b = bst_to_array(t);
	
	printf("Initial array:\n");
	for(i = 0; i < bst_size(t); i++)
		printf("%i\n", b[i]);

	bst_remove(t, 6);

	printf("\nRemoved 6:\n");
	b = bst_to_array(t);

	for(i = 0; i < bst_size(t); i++)
		printf("%i\n", b[i]);

	printf("\nSize: %i\n", bst_size(t));

	int x = bst_get_ith(t, 6);
	printf("\n6th smallest: %i\n", x);

	printf("\nNumber of nodes greater than or equal to 22: %i\n", bst_num_geq(t, 22));

	printf("\nNumber of nodes less than or equal to 50: %i\n", bst_num_leq(t, 50));

	printf("\nRoot node subtrees, Left: Right\n");
	printf("%i: %i\n", getLeft(t), getRight(t)); 

	printf("\nNode closest to 48: ");
	printf("%i\n", bst_get_nearest(t, 48));

return 0;
}
