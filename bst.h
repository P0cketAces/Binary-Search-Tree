
// typedef int ELEM_TYPE;

typedef struct bst *BST_PTR;

extern BST_PTR bst_create();

extern void bst_free(BST_PTR t);

/** TODO:  modify for augmentations  **/
extern void bst_insert(BST_PTR t, int x);

/** TODO:  modify for augmentations  **/
extern int bst_remove(BST_PTR t, int x);

extern int bst_contains(BST_PTR t, int x);

/** TODO:  make O(1) **/
extern int bst_size(BST_PTR t);

extern int bst_height(BST_PTR t);

/** EXTRA CREDIT:  bst_min and bst_max modified to be O(1) 
	These will require modification of other functions. 
	They are not terribly difficult but since they are
	extra credit, you are REQUIRED to include a separate
	README file which does the following:

	    - states that you did indeed complete the functions.

	    - what other functions needed to be modified and 
		a description of the mofifications.  This should
		include an argument that the runtime of those
		functions has not been altered.

	Points:  These will account for (only) a 10% bonus if working
	correclty.
**/
extern int bst_min(BST_PTR t);

extern int bst_max(BST_PTR t);

/************************************************************/


extern void bst_inorder(BST_PTR t);

extern void bst_preorder(BST_PTR t);

extern void bst_postorder(BST_PTR t);

extern BST_PTR bst_from_sorted_arr(int *a, int n);

/*** TODO ***/

extern int * bst_to_array(BST_PTR t);

extern int bst_get_ith(BST_PTR t, int i);

extern int bst_get_nearest(BST_PTR t, int x);

extern int bst_num_geq(BST_PTR t, int x);

extern int bst_num_leq(BST_PTR t, int x);
