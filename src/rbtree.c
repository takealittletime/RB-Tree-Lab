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

void left_rotate(rbtree* t, node_t* x){
  node_t* y = x->right;
  // rotate left subtree of y to right subtree
  y->left = x->right;
  // if left subtree of y isn't vacant, x will be parent of subtree
  if (y->left != t->nil){
    y->left->parent = x;
  }
  // parent of x will be parent of y
  y->parent = x->parent;
  // if x is root node, y will be root node
  if (x->parent == t->nil)
    t->root =y;
  // if x is left child, y will be left child
  else if (x == x->parent->left)
    x->parent->left = y;
  // if x is right child, y will be right child
  else
    x->parent->right = y;
  // x will be left child of y
  y->left = x;
  x->parent = y;
}

// writing yet...
void right_rotate(rbtree* t, node_t* y){
  node_t* x = y->left;
  y->left = x->right;
  if (x->right != t->nil){
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == t->nil)
    t->root = x;
  else if (y == y->parent->right)
    y->parent->right = x;
  else
    y->parent->left = x;
  x->right = y;
  y->parent = x;
}

void rb_insert_fixup(rbtree *t, node_t* z){
  while ( z->parent->color == RBTREE_RED)
  {
    // is parent of z left child? 
    if (z->parent == z->parent->parent->left){
      // y is uncle of z
      node_t* y = z->parent->parent->right;
      // case 1
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      // case 2
      else{
        if (z == z->parent->right){
          z = z->parent;
          left_rotate(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t,z->parent->parent);
      }
    }
  }
  
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
