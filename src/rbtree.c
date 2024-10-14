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


void delete_rbtree_nodes(node_t *node, node_t *nil) {
  if (node != nil) {
    // reclame left child, right child, and then current node.
    delete_rbtree_nodes(node->left, nil); 
    delete_rbtree_nodes(node->right, nil);
    free(node);
  }
}

void delete_rbtree(rbtree *t) {
  if (t != NULL) {
    // reclaim all node of tree recursively
    delete_rbtree_nodes(t->root, t->nil);  // 트리의 모든 노드 해제
    // reclaim sentinel node, and root node
    free(t->nil); 
    free(t);
  }
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

// reverse of left_rotate
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
      else{
        // case 2
        if (z == z->parent->right){
          z = z->parent;
          left_rotate(t,z);
        }
        // case 3
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t,z->parent->parent);
      }
    }

    // reverse left-right
    // (when parent of z is right child)
    else {
      node_t* y = z->parent->parent->left;
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color= RBTREE_RED;
        z = z->parent->parent;
      }

      else{
        if (z==z->parent->left){
          z = z->parent;
          right_rotate(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t,z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
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

  z->parent = y;
  // if tree was vacant
  if (y == t->nil)
    t->root = z;

  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;

  rb_insert_fixup(t,z);
  
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t* tmp = t->root;

  // if tree is vacant
  if (tmp == t->nil)
    return NULL;

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

  // if tree is vacant
  if (tmp == t->nil)
    return NULL;

  // just go left till meet nill node
  while (tmp->left != t->nil)
  {
    tmp = tmp->left;
  }

  return tmp;
}

node_t *rbtree_max(const rbtree *t) {
  // create tmp and put root node
  node_t* tmp = t->root;

    // if tree is vacant
  if (tmp == t->nil)
    return NULL;

  // just go right till meet nill node
  while (tmp->right != t->nil)
  {
    tmp = tmp->right;
  }
  return tmp;
}

// transplant v node to place of u node
void rb_transplant(rbtree *t, node_t* u, node_t* v){
  if (u->parent == t->nil)
    t->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
}

void rb_erase_fixup(rbtree* t, node_t* x){
  while (x != t->root && x->color == RBTREE_BLACK)
  {
    if (x == x->parent->left){
      node_t* w = x->parent->right;
      // case 1
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t,x->parent);
        w = x->parent->right;
      }
      // case 2
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }
      // case 3
      else{
        if (w->right->color == RBTREE_BLACK){
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t,w);
          w = x->parent->right;
        }
        // case 4
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t,x->parent);
        x = t->root;
      }
    }

    // reverse left <-> right
    else{
      node_t* w = x->parent->left;
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t,x->parent);
        w = x->parent->left;
      }
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{
        if (w->left->color == RBTREE_BLACK){
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t,w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t,x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t *y = p;
  color_t y_original_color = y->color;

  if (p->left == t->nil){
    node_t *x = p->right;
    rb_transplant(t,p,p->right);
  }
  else if (p->right == t->nil){
    node_t*x = p->left;
    rb_transplant(t,p,p->left);
  }
  else {
    y = rbtree_min(p->right);
    y_original_color = y->color;
    node_t* x = y->right;
    if (y != p->right){
      rb_transplant(t,y,y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    else{
      x->parent = y;
    }
    rb_transplant(t,p,y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }

  if (y_original_color == RBTREE_BLACK)
    //rb_erase_fixup(t,x);


  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array

  return 0;
}
