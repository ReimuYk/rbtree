#include <malloc.h>

#define color_t int
#define BLACK 1
#define RED 0

#define bool int
#define true 1
#define false 0

struct _RBNode {
	void *key;
	void *value;
	struct _RBNode *left;
	struct _RBNode *right;
	struct _RBNode *parent;
	color_t color;
};

typedef struct _RBNode RBNode;

typedef bool (*rbnode_lt_t)(void *k1, void *k2);

typedef struct {
	RBNode *root;
	rbnode_lt_t rbnode_lt;
} RBTree;

static inline RBTree* new_rbtree(rbnode_lt_t rbnode_lt)
{
	RBTree *ret = (RBTree *)malloc(sizeof(*ret));
	ret->root = NULL;
	ret->rbnode_lt = rbnode_lt;
	return ret;
}

static inline RBNode* new_rbnode(void *key, void *value)
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

static inline bool is_black_node(RBNode *node)
{
	return (node->color == BLACK);
}

static inline bool is_red_node(RBNode *node)
{
	return (node->color == RED);
}

static inline void node_swap(RBNode *node1, RBNode *node2)
{
	void *tmp;

	tmp = node1->key;
	node1->key = node2->key;
	node2->key = tmp;

	tmp = node1->value;
	node1->value = node2->value;
	node2->value = tmp;
}