/*
**
** Prefix: plt
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _CLST_LIST_LIB_IMP
#define _CLST_LIST_LIB_IMP

#include "list.h"

/* ========================================================================== */

struct CLSTNode {
    void* element_p;
    struct CLSTNode* next;
    struct CLSTNode* previous;
};

struct CLSTList_ST {
    unsigned size;
    struct CLSTNode* first;
    struct CLSTNode* last;
};

/* ========================================================================== */

extern int clst_current_error;

/* ========================================================================== */

struct CLSTNode* clstGetNode (CLSTList list, unsigned position);

/* ========================================================================== */

#endif

