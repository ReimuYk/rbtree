
#include "rbtree.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <ctime>

using namespace std;

bool cmp(rbkey_t k1, rbkey_t k2)
{
    bool ret = (reinterpret_cast<rbkey_t>(k1) < reinterpret_cast<rbkey_t>(k2));
	return ret;
}

int main()
{
	RBTree *t = new_rbtree(cmp);
    RBNode *n;
    map<long, long> answer;

    srand(time(NULL));

    int i = 0;
    while (true) {
        check_is_rbtree(t);
        int op = rand() % 5;
        cout << i++ << '\t' << op << endl;
        if (op == 0) {
            /* random insert */
            long key = rand() % 0x10000;
            long value = rand() % 0x20000;
            auto it = answer.find(key);
            if (it == answer.end()) {
                answer[key] = value;
            } else {
                continue;
            }

            n = new_rbnode(reinterpret_cast<rbkey_t>(key), reinterpret_cast<rbvalue_t>(value));
            rbtree_insert(t, n);
        } else if (op == 1) {
            /* random get exists */
            if (answer.size() < 2)
                continue;
            auto it  = answer.begin();
            for (int k = 0; k < (rand() % (answer.size() - 1)); ++k) {
                ++it;
            }
            n = rbtree_get(t, reinterpret_cast<rbkey_t>(it->first));
            assert(n);
            assert(reinterpret_cast<long>(n->value) == it->second);
        } else if (op == 2) {
            /* random get */
            long key = rand() % 0x10000;
            auto it = answer.find(key);
            if (it != answer.end()) {
                n = rbtree_get(t, reinterpret_cast<rbkey_t>(key));
                assert(n);
                assert(reinterpret_cast<long>(n->value) == it->second);
            } else {
                n = rbtree_get(t, reinterpret_cast<rbkey_t>(key));
                assert(!n);
            }
        } else if (op == 3) {
            /* random delete exists */
            if (answer.size() < 2)
                continue;
            auto it  = answer.begin();
            for (int k = 0; k < (rand() % (answer.size() - 1)); ++k) {
                ++it;
            }
            n = rbtree_get(t, reinterpret_cast<rbkey_t>(it->first));
            assert(n);
            assert(reinterpret_cast<long>(n->value) == it->second);
            assert(rbtree_delete(t, reinterpret_cast<rbkey_t>(it->first)) == 0);
            answer.erase(it);
        } else if (op == 4) {
            /* random delete */
            long key = rand() % 0x10000;
            auto it = answer.find(key);
            if (it != answer.end()) {
                n = rbtree_get(t, reinterpret_cast<rbkey_t>(key));
                assert(n);
                assert(reinterpret_cast<long>(n->value) == it->second);
                assert(rbtree_delete(t, reinterpret_cast<rbkey_t>(it->first)) == 0);
                answer.erase(it);
            } else {
                n = rbtree_get(t, reinterpret_cast<rbkey_t>(key));
                assert(!n);
            }
        }
    }

    cout << "all passed" << endl;
    return 0;
}