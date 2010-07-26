/*
**
** Prefix: lst
** $ Herond Robaina Salles
*/

#ifndef _LST_IMP
#define _LST_IMP

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "error.h"

/* ========================================================================== */

struct LSTListNode_ST {
    void* elem;
    int tokem;
    struct LSTListNode_ST* next;
    struct LSTListNode_ST* previous;
};

struct LSTList_ST {
    int type;
    unsigned size;
    
    struct LSTListNode_ST* first;
    struct LSTListNode_ST* last;
};

typedef struct LSTList_ST* LSTList;

/* ========================================================================== */

enum LSTRemoveElemetOptions_EN {
    LST_ALL_OCCURRENCES, LST_FIRST_OCCURRENCE, LST_LAST_OCCURRENCE
};

enum LSTType_EN { LST_LINEAR, LST_CIRCULAR };

/* ========================================================================== */

LSTList lstNew (int type) {
    LSTList list_return = (LSTList) malloc(sizeof(struct LSTList_ST));

    if (list_return) {
        switch (type) {
        case LST_LINEAR:
            list_return->type = LST_LINEAR;
            break;
        case LST_CIRCULAR:
            list_return->type = LST_LINEAR;
            break;
        default:
            list_return->type = LST_LINEAR;
        }
        
        list_return->size = 0;
        list_return->first = NULL;
        list_return->last = NULL;
    }
    
    return list_return;
}

LSTList lstCopy (const LSTList list) {
    LSTList list_return = lstNew();

    if (list_return) {
        int i, tokem;
        void* elem;

        errBegin();
        for (i = 0; i < list->size; i ++) {
            elem = lstGet(list, i, &tokem);
            lstInsertWithTokem(list, elem, tokem);

            if (errRescue(ERR_NOT_ENOUGH_SPACE)) {
                lstDestroy(&list_return);
                
                return NULL
            }
        }
    }

    return list_return;
}


void lstMerge (LSTList list, const LSTList list2) {
    if (list2->size) {
        LSTList list_aux = lstCopy(list);
        
        if (list_aux) {
            if (list->size) {
                list_aux->first->previous = list->last;
                list->last->next = list_aux->first;
            } else list->first = list_aux->first;
            
            list->last = list_aux->last;
            free(list_aux);
        }
    }
}

void lstDestroy (LSTList* list) {
    if (list && *list) {
        lstClean(*list);
        free(*list);
        
        *list = NULL;
    } else errRaise(ERR_ACCESS_NULL_POINTER);
}

void lstClean (LSTList list) {
    if (list) {
        struct LSTListNode_ST* current_node = list->first;
        struct LSTListNode_ST* next_node = list->first;
        
        while (current_node) {
            next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
        
        list->size = 0;
        list->first = NULL;
        list->last = NULL;
    }
}

void lstInsert (LSTList list, void* elem, unsigned position) {
    lstInsertWithTokem(list, elem, position, LST_NULL_TOKEN);
}
/*
void lstInsertWithTokem
    (LSTList list, void* elem, unsigned position, int token);

void lstInsertBeginning (LSTList list, void* elem);
void lstAppend (LSTList list, void* elem);

void* lstGet (const LSTList list, unsigned position, int* token_p);
void* lstGetElement (const LSTList list, unsigned position);
int lstGetTokem (const LSTList list, unsigned position);
void* lstGetFirstElement (const LSTList list);
void* lstGetLastElement (const LSTList list);
unsigned lstGetPosition (const LSTList list, const void* elem);
int lstGetType (const LSTList list);

unsigned lstSize (const LSTList list);

int lstRemove (LSTList list, unsigned position);
int lstRemoveElement (LSTList list, const void* element, int option);

void lstSort
    (LSTList list, int (*comparator) (const void* elem_1, const void* elem_2));

void lstSetInsertCallback
    (LSTList list, void* (*insert) (void* elem, int token));
    
void lstSetCopyCallback
    (LSTList list, void* (*copy) (void* elem, int token));
    
void lstSetCleanCallback
    (LSTList list, void (*clean) (void* elem, int token));
    
void lstPrint (const LSTList list);
*/

/* ========================================================================== */

#endif
