#include "rbtree.h"

#include <stdlib.h>

//tmp/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;

// typedef int key_t;

// typedef struct node_t {
//   color_t color;
//   key_t key;
//   struct node_t *parent, *left, *right;
// } node_t;

// typedef struct {
//   node_t *root;
//   node_t *nil;  // for sentinel
// } rbtree;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rbtree *new_rbtree(void) {
  // make new rbtree
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // if rbtree is created, initialize its root node and nil node.
  if (p != NULL)
  {
    p->nil = (node_t*)calloc(1,sizeof(node_t));
    p->nil->color = RBTREE_BLACK;
    p->root = p->nil;
  }
  // return rbtree
  return p;
}

void delete_rbtree(rbtree *t) {
  // reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // create 'new node z' and fill it red
  node_t* z = (node_t*)calloc(1, sizeof(node_t));
  z->color = RBTREE_RED;
  z->key = key;
  z->left = t->nil;
  z->right = t->nil;
  z->parent = t->nil;

  // x node is for comparing, and y node will be parent node of z
  node_t* x = t->root;
  node_t* y = t->nil;

  // move node x to right place
  while (x != t->nil)
  {
    y = x;
    if (z->key < x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  // if tree was vacant
  z->parent = y;
  if (y == t->nil)
    t->root = z;

  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  
  z->left = t->nil;
  z->right = t->nil;
  
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t* tmp = t->root;

  while (tmp != t->nil)
  {
    // if found
    if (tmp->key == key)
    {
      return tmp;
    }
    // if root key is bigger than parameter
    else if ( key < tmp->key )
    {
      tmp = tmp->left;
    }
    // if root key is smaller than parameter
    else
    {
      tmp = tmp->right;
    }
  }
  
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // create tmp and put root node
  node_t* tmp = t->root;
  // just go left till meet nill node
  while (tmp != t->nil)
  {
    tmp = tmp->left;
  }

  return tmp;
}

node_t *rbtree_max(const rbtree *t) {
  // create tmp and put root node
  node_t* tmp = t->root;
  // just go right till meet nill node
  while (tmp != t->nil)
  {
    tmp = tmp->right;
  }
  return tmp;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array

  return 0;
}
