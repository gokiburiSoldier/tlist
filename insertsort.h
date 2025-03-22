#ifndef __INSERT_SORT
#define __INSERT_SORT

namespace insertsort {
    template<class T> struct node_t {
        int id;
        T val;
        node_t *left, *right;
    };
}

#endif
