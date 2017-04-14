/* Joey Nelson
*/

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct bst_node {
    int val;
    struct bst_node *left;
    struct bst_node *right;
    int nLeft;
    int nRight;

};
typedef struct bst_node NODE;


struct bst {
    NODE *root;
    int total;
};

int getLeft(BST_PTR t){
	return t->root->nLeft;
}

int getRight(BST_PTR t){
	return t->root->nRight;
}

BST_PTR bst_create(){
  BST_PTR t = malloc(sizeof(struct bst));
  t->root = NULL;
  t->total = 0;
  return t;
}

static void inorderArray(NODE *r, int* a, int* i)
{ 
  if(r==NULL) return;

  inorderArray(r->left, a, i);

  a[*i] = r->val;
  *i = *i + 1;

  inorderArray(r->right, a, i);

}

int* bst_to_array(BST_PTR t)
{
	int size = bst_size(t);
	int* a = (int*)malloc(sizeof(int) * size);

	int i = 0;
	inorderArray(t->root, a, &i);

	return a;
}

static int ith(NODE* r, int i)
{
	if(i <= r->nLeft)
	{
		return ith(r->left, i);
	} 	

	if(i == r->nLeft + 1)
	{
		return r->val;
	}

	if(i > r->nLeft + 1)
	{
		return ith(r->right, i - (r->nLeft + 1));
	}

	return 0;
}

int bst_get_ith(BST_PTR t, int i)
{
	if(i > bst_size(t))
	{
		printf("Error, not enough nodes in BST");
		return 0;
	}

	int result = ith(t->root, i);
	return result;
}

static void geq(NODE* r, int x, int* res)
{
	if(r == NULL)
		return;
	
	if(x > r->val)
		geq(r->right, x, res);

	if(x < r->val)
	{
		*res = *res + r->nRight + 1;
		geq(r->left, x, res);
	}

	if(x == r->val)
	{
		*res = *res + r->nRight + 1;
		return;	
	}
}

int bst_num_geq(BST_PTR t, int x)
{
	int res = 0;
	geq(t->root, x, &res);
	
	return res;
}

static void leq(NODE* r, int x, int* res)
{
	if(r == NULL)
	{
		return;
	}

	if(x > r->val)
	{
		*res = *res + r->nLeft + 1;
		leq(r->right, x, res);
	}

	if(x < r->val)
	{
		leq(r->left, x, res);
	}

	if(x == r->val)
	{
		*res = *res + r->nLeft + 1;
		return;	
	}
}

int bst_num_leq(BST_PTR t, int x)
{
	int res = 0;
	leq(t->root, x, &res);
	
	return res;
}

static void nearest(NODE* r, int x, int* res, int* close)
{
	if(r == NULL)
	{
		return;
	}

	if(*res == -1 && *close == -1)
	{	
		*res = r->val;
		*close = abs(r->val - x);
	}

	if(r->val < x)
	{	
		if(abs(r->val - x) < *close)
		{
			*close = abs(r->val - x);
			*res = r->val;
		}

		nearest(r->right, x, res, close);
	}

	if(r->val > x)
	{
		if(abs(r->val - x) < *close)
		{
			*close = abs(r->val - x);
			*res = r->val;
		}

		nearest(r->left, x, res, close);
	}

	if(r->val == x)
	{
		*res = r->val;
		*close = 0;
		return;
	}
}

int bst_get_nearest(BST_PTR t, int x)
{
	if(t->root == NULL)
	{
		printf("Error, empty tree\n");
		return 0;
	}

	int res = -1;
	int close = -1;
	nearest(t->root, x, &res, &close);

	return res;
}

static void free_r(NODE *r){
    if(r==NULL) return;
    free_r(r->left);
    free_r(r->right);
    free(r);
}
void bst_free(BST_PTR t){
    free_r(t->root);
    free(t);
}

static NODE * insert(NODE *r, int x){
    NODE *leaf;
    if(r == NULL){
      leaf = malloc(sizeof(NODE));
      leaf->left = NULL;
      leaf->right = NULL;
      leaf->val = x;
      leaf->nLeft = 0;
      leaf->nRight = 0;
      return leaf;
    }

    if(r->val == x)
        return r;
    if(x < r->val){
	r->nLeft = r->nLeft + 1;
        r->left = insert(r->left, x);
        return r;
    }
    else {
	r->nRight = r->nRight + 1;
        r->right = insert(r->right, x);
        return r;
    }
}

// how about an iterative version?
static NODE *insert_i(NODE *r, int x){

  return NULL;

}


void bst_insert(BST_PTR t, int x){
    
	if(!bst_contains(t, x)){
    		t->root = insert(t->root, x);
		t->total = t->total + 1;
	}
}

int bst_contains(BST_PTR t, int x){
    NODE *p = t->root;

    while(p != NULL){

        if(p->val == x)
            return 1;
        if(x < p->val){
            p = p->left;
        }
        else
            p = p->right;
    }
    return 0;  
}

static int min_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->left != NULL)
      r = r->left;
  return r->val;
}

static int max_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->right != NULL)
      r = r->right;
  return r->val;
}

static NODE *remove_r(NODE *r, int x, int *success){
NODE   *tmp;
int sanity;

  if(r==NULL){
    *success = 0;
    return NULL;
  }
  if(r->val == x){
    *success = 1;

    if(r->left == NULL){
        tmp = r->right;
        free(r);
        return tmp;
    }
    if(r->right == NULL){
        tmp = r->left;
        free(r);
        return tmp;
    }
    // if we get here, r has two children
    r->val = min_h(r->right);
    r->nRight = r->nRight - 1;
    r->right = remove_r(r->right, r->val, &sanity);
    if(!sanity)
        printf("ERROR:  remove() failed to delete promoted value?\n");
    return r;
  }
  if(x < r->val){
    r->nLeft = r->nLeft - 1;
    r->left = remove_r(r->left, x, success);
  }
  else {
    r->nRight = r->nRight - 1;
    r->right = remove_r(r->right, x, success);
  }
  return r;

}


int bst_remove(BST_PTR t, int x){
    int success = 0;
    if(bst_contains(t, x)){
    	t->root = remove_r(t->root, x, &success);
        t->total = t->total - 1;
    }

    return success;
}
static int size(NODE *r){
//THIS FUNCTION IS NO LONGER USED

//    if(r==NULL) return 0;
//    return size(r->left) + size(r->right) + 1;
}
int bst_size(BST_PTR t){

    return t->total;
}

static int height(NODE *r){
    int l_h, r_h;

    if(r==NULL) return -1;
    l_h = height(r->left);
    r_h = height(r->right);
    return 1 + (l_h > r_h ? l_h : r_h);

}
int bst_height(BST_PTR t){
    return height(t->root);

}

int bst_min(BST_PTR t){
    return min_h(t->root);
}

int bst_max(BST_PTR t){
    return max_h(t->root);
}

static void indent(int m){
    int i;
    for(i=0; i<m; i++)
        printf("-");
}

static void inorder(NODE *r){
  if(r==NULL) return;
  inorder(r->left);
  printf("[%d]\n", r->val);
  inorder(r->right);

}
void bst_inorder(BST_PTR t){

  printf("========BEGIN INORDER============\n");
  inorder(t->root);
  printf("=========END INORDER============\n");

}

static void preorder(NODE *r, int margin){
  if(r==NULL) {
    indent(margin);
    printf("NULL \n");
  } else {
    indent(margin);
    printf("%d\n", r->val);
    preorder(r->left, margin+3);
    preorder(r->right, margin+3);
  }
}

void bst_preorder(BST_PTR t){

  printf("========BEGIN PREORDER============\n");
  preorder(t->root, 0);
  printf("=========END PREORDER============\n");

}

/* 
 * Complete the (recursive) helper function for the post-order traversal.
 * Remember: the indentation needs to be proportional to the height of the node!
 */
static void postorder(NODE *r, int margin){
    /* FILL IN FUNCTION */
}

// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void bst_postorder(BST_PTR t){

  printf("========BEGIN POSTORDER============\n");
  postorder(t->root, 0);
  printf("=========END POSTORDER============\n");

}

/* 
 * Write the (recursive) helper function from_arr, used by
 * bst_from_sorted_arr(...). The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */
static NODE * from_arr(int *a, int n){
int m;
NODE *root;

    if(n <= 0) return NULL;
    m = n/2;
    root = malloc(sizeof(NODE));
    root->val = a[m];
    root->left = from_arr(a, m);
    root->right = from_arr(&(a[m+1]), n-(m+1));
    return root;

}

BST_PTR bst_from_sorted_arr(int *a, int n){

  BST_PTR t = bst_create();

  t->root = from_arr(a, n);

  return t;
}
