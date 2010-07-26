/*
**
** Prefix: lst
** $ Herond Robaina Salles
*/

#ifndef _LST_LIB
#define _LST_LIB

#include "error.h"

/* ========================================================================== */

struct LSTList_ST;

typedef struct LSTList_ST* LSTList;

/* ========================================================================== */

enum LSTRemoveElemetOptions_EN {
    LST_ALL_OCCURRENCES, LST_FIRST_OCCURRENCE, LST_LAST_OCCURRENCE
};

enum LSTType_EN { LST_LINEAR, LST_CIRCULAR };

/* ========================================================================== */

/*
LSTList lstNew (int type);
LSTList lstCopy (const LSTList list);
void lstMerge (LSTList list, const LSTList list2);

void lstDestroy (LSTList* list);

void lstClean (LSTList list);

void lstInsert (LSTList list, void* elem, unsigned position);

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
