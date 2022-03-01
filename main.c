
#include "rbtree.h"
#include <assert.h>
#include <stdlib.h>

bool long_lt(void *k1, void *k2)
{
	return (long)(k1) < (long)(k2);
}

int main()
{
	RBTree *t = new_rbtree(long_lt);
    RBNode *n;
    int exists[10000] = {0};

    /* insert */
    int i;
    for (i = 0; i < 0x2000; ++i) {
        long key = rand() % 9999;
        long value = key / 2;
        if (!exists[key]) {
            n = rbtree_get(t, (void *)key);
            assert(!n);
            n = new_rbnode((void *)key, (void *)value);
            rbtree_insert(t, n);
            n = rbtree_get(t, (void *)key);
            assert(n);
            assert((long)n->value == (long)n->key / 2);
            exists[key] = 1;
        }
    }

    printf("all passed\n");
    return 0;
}