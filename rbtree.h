
#ifdef __cplusplus
extern "C" {
#endif

#include <malloc.h>

#ifndef __cplusplus
	/* For c code */
	#define bool int
	#define true 1
	#define false 0
#endif

#define color_t int
#define BLACK 1
#define RED 0

typedef long rbkey_t;
typedef void * rbvalue_t;

typedef bool (*rbnode_lt_t)(rbkey_t k1, rbkey_t k2);

#ifdef __cplusplus
	struct RBNode {
		rbkey_t key;
		rbvalue_t value;
		RBNode *left;
		RBNode *right;
		RBNode *parent;
		color_t color;
	};

	struct RBTree {
		RBNode *root;
		rbnode_lt_t rbnode_lt;
	};
#else
	struct _RBNode {
		rbkey_t key;
		rbvalue_t value;
		struct _RBNode *left;
		struct _RBNode *right;
		struct _RBNode *parent;
		color_t color;
	};
	typedef struct _RBNode RBNode;
	typedef struct {
		RBNode *root;
		rbnode_lt_t rbnode_lt;
	} RBTree;
#endif

static inline RBTree* new_rbtree(rbnode_lt_t rbnode_lt)
{
	RBTree *ret = (RBTree *)malloc(sizeof(*ret));
	ret->root = NULL;
	ret->rbnode_lt = rbnode_lt;
	return ret;
}

static inline RBNode* new_rbnode(rbkey_t key, rbvalue_t value)
{
	RBNode *ret = (RBNode *)malloc(sizeof(*ret));
	ret->key = key;
	ret->value = value;
	ret->left = NULL;
	ret->right = NULL;
	ret->parent = NULL;
	ret->color = RED;
	return ret;
}

static inline void node_swap(RBNode *node1, RBNode *node2)
{
	rbkey_t k;
	rbvalue_t v;

	k = node1->key;
	node1->key = node2->key;
	node2->key = k;

	v = node1->value;
	node1->value = node2->value;
	node2->value = v;
}

void rbtree_insert(RBTree *rbtree, RBNode *new_node);
RBNode *rbtree_get(RBTree *rbtree, rbkey_t key);
int rbtree_delete(RBTree *rbtree, rbkey_t key);

/* for correctness check */
void check_is_rbtree(RBTree *rbtree);

#ifdef __cplusplus
}
#endif