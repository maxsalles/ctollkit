/*
**
** Prefix: plt
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _CLST_LIST_IMP
#define _CLST_LIST_IMP

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "list_imp.h"

/* ========================================================================== */

int clst_current_error = CLST_NO_ERROR;

/* ========================================================================== */

struct CLSTNode* clstGetNode (CLSTList list, unsigned position) {
    struct CLSTNode* node_p = NULL;

    if (list && (position < list->size)) {
        int i;

        for (
            i = 0, node_p = list->first;
            (i < position) || (node_p == NULL);
            i ++, node_p = node_p->next
        );
    }

    return node_p;
}

/* ========================================================================== */

CLSTList clstNew (void) {
    CLSTList list_return = (CLSTList) malloc(sizeof(struct CLSTList_ST));

    if (list_return) {
        list_return->size = 0;
        list_return->first = NULL;
        list_return->last = NULL;
    } else clst_current_error = CLST_NOT_ENOUGH_SPACE;

    return list_return;
}

CLSTList pltCopy (const CLSTList list) {
    if (list) {
        int i;
        CLSTList list_return = clstNew();

        if (list_return) {
            for (i = 0; i < list->size; i ++)
                clstAppend(list_return, clstLookElement(list, i));

            return list_return;
        }

        return NULL;
    } clst_current_error = CLST_INVALID_ARGUMENT;

    return NULL;
}

void clstClear (CLSTList list) {
    if (list)
        while (list->size) clstGetFirstElement(list);
    else clst_current_error = CLST_INVALID_ARGUMENT;
}

void clstDestroy (CLSTList* list_p) {
    if (list_p) {
        clstClear(*list_p);
        free(*list_p);
        *list_p = NULL;
    } else clst_current_error = CLST_INVALID_ARGUMENT;
}

void clstAppend (CLSTList list, void* element_p) {
    if (list && element_p) {
        struct CLSTNode* node_p = (struct CLSTNode*) malloc(
            sizeof(struct CLSTNode)
        );

        if (node_p) {
            node_p->next = NULL;
            node_p->previous = list->last;
            node_p->element_p = element_p;

            if (list->last) list->last->next = node_p;
            list->last = node_p;
            if (!list->size) list->first = node_p;
            list->size ++;

        } else clst_current_error = CLST_NOT_ENOUGH_SPACE;
    } else clst_current_error = CLST_INVALID_ARGUMENT;
}

void clstInject (CLSTList list, void *element_p) {
    if (list && element_p) {
        struct CLSTNode* node_p = (struct CLSTNode*) malloc(
            sizeof(struct CLSTNode*)
        );

        if (node_p) {
            node_p->next = list->first;
            node_p->previous = NULL;
            node_p->element_p = element_p;

            if (list->first) list->first->previous = node_p;
            list->first = node_p;
            list->size ++;
        } else clst_current_error = CLST_NOT_ENOUGH_SPACE;
    } else clst_current_error = CLST_INVALID_ARGUMENT;
}

void clstInsert (CLSTList list, unsigned position, void* element_p) {
    struct CLSTNode* node_p = NULL;

    if (list && element_p && (position < list->size)) {
        if (position == list->size - 1) clstAppend(list, element_p);
        else if (position == 0) clstInject(list, element_p);
        else {
            node_p = (struct CLSTNode*) malloc(sizeof(struct CLSTNode*));
            struct CLSTNode* current_node_p = clstGetNode(list, position);

            if (node_p) {
                node_p->next = current_node_p;
                node_p->previous = current_node_p->previous;
                node_p->element_p = element_p;

                current_node_p->previous->next = node_p;
                current_node_p->previous = node_p;

                list->size ++;
            } else clst_current_error = CLST_NOT_ENOUGH_SPACE;
        }
    } else clst_current_error = CLST_INVALID_ARGUMENT;
}

void clstSetElement (CLSTList list, unsigned position, void* element_p) {
    struct CLSTNode* node_p = clstGetNode(list, position);

    if (node_p) node_p->element_p = element_p;
}

void* clstLookElement (const CLSTList list, unsigned position) {
    if (list && (position < list->size))
        return clstGetNode(list, position)->element_p;
    else clst_current_error = CLST_INVALID_ARGUMENT;

    return NULL;
}

void* clstLookLastElement (const CLSTList list) {
    if (list && list->size) return list->last->element_p;
    clst_current_error = CLST_INVALID_ARGUMENT;

    return NULL;
}

void* clstLookFirstElement (const CLSTList list) {
    if (list && list->size) return list->first->element_p;
    clst_current_error = CLST_INVALID_ARGUMENT;

    return NULL;
}

void* clstGetElement (CLSTList list, unsigned position) {
    if (list && list->size) {
        if (! position) return clstGetFirstElement(list);
        else if (position == list->size - 1) return clstGetLastElement(list);
        else {
            struct CLSTNode* node = clstGetNode(list, position);
            void* element_p = node->element_p;

            node->previous->next = node->next;
            node->next->previous = node->previous;
            list->size --;
            free(node);

            return element_p;
        }
    }

    clst_current_error = CLST_INVALID_ARGUMENT;

    return NULL;
}

void* clstGetLastElement (CLSTList list) {
    if (list && list->size) {
        struct CLSTNode* last_node = list->last;
        void* element_p = list->last->element_p;

        if (list->last->previous) list->last->previous->next = NULL;
        else list->first = NULL;
        list->last = list->last->previous;
        list->size --;
        free(last_node);

        return element_p;
    }

    clst_current_error = CLST_INVALID_ARGUMENT;

    return NULL;
}

void* clstGetFirstElement (CLSTList list) {
    if (list && list->size) {
        struct CLSTNode* first_node = list->first;
        void* element_p = list->first->element_p;

        if (list->first->next) list->first->next->previous = NULL;
        else list->last = NULL;
        list->first = list->first->next;
        list->size --;
        free(first_node);

        return element_p;
    }

    clst_current_error = CLST_INVALID_ARGUMENT;

    return NULL;
}

void clstReverse (CLSTList list) {
    int i;
    void* element_p = NULL;

    for (i = 0; i < list->size / 2; i ++) {
        element_p = clstLookElement(list, i);
        clstSetElement(list, i, clstLookElement(list, list->size - 1 - i));
        clstSetElement(list, list->size - 1 - i, element_p);
    }
}

unsigned clstGetLength (const CLSTList list) {
    if (list) return list->size;
    else clst_current_error = CLST_INVALID_ARGUMENT;

    return 0;
}

CLSTList clstSearch (
    const CLSTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
) {
    if (list && element_of_comparison_p) {
        int i;
        struct CLSTNode* node_p = NULL;
        CLSTList list_return = clstNew();

        comparator = comparator ? comparator : CLST_DEFAULT_COMPARATOR;

        if (list_return) {
            for (
                i = 0, node_p = list->first;
                i < list->size;
                i ++, node_p = node_p->next
            ) if (comparator(node_p->element_p, element_of_comparison_p))
                clstAppend(list_return, node_p->element_p);

            return list_return;
        }
    } else clst_current_error = CLST_INVALID_ARGUMENT;

    return NULL;
}

void* clstSearchElement (
    const CLSTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
) {
    if (list && element_of_comparison_p) {
        int i;
        struct CLSTNode* node_p = NULL;

        comparator = comparator ? comparator : CLST_DEFAULT_COMPARATOR;

        for (
            i = 0, node_p = list->first;
            i < list->size;
            i ++, node_p = node_p->next
        ) if (comparator(node_p->element_p, element_of_comparison_p))
            return node_p->element_p;

    } else clst_current_error = CLST_INVALID_ARGUMENT;

    return NULL;
}

int clstGetError (void) {
    int error_return = clst_current_error;

    clst_current_error = CLST_NO_ERROR;

    return error_return;
}

/* ========================================================================== */

void clstPrint (const CLSTList list) {
    if (list) {
        int i = 0;
        struct CLSTNode* node_p = NULL;

        for (node_p = list->first; i < list->size; node_p = node_p->next, i ++)
            printf("%i:%p ", i, node_p->element_p);

        puts("");
    }
}

/* ========================================================================== */

int clstDefaultComparator (
    const void* element_p,
    void* element_of_comparison_p
) {
    return element_p == element_of_comparison_p;
}

/* ========================================================================== */

#endif

