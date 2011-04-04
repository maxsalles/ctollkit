/*
**
** Prefix: plt
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _CLST_LIST_LIB
#define _CLST_LIST_LIB

#include <errno.h>

/* ========================================================================== */

#define CLST_DEFAULT_COMPARATOR (clstDefaultComparator)

/* ========================================================================== */

enum CLSTErros_EN {
    CLST_NO_ERROR = 0,
    CLST_NOT_ENOUGH_SPACE = ENOMEM,
    CLST_INVALID_ARGUMENT = EINVAL
};

struct CLSTList_ST;

typedef struct CLSTList_ST* CLSTList;

/* ========================================================================== */

CLSTList clstNew (void);

CLSTList clstCopy (const CLSTList list);

void clstClear (CLSTList list);

void clstDestroy (CLSTList* list_p);

void clstAppend (CLSTList list, void* element_p);

void clstInject (CLSTList list, void* element_p);

void clstInsert (CLSTList list, unsigned position, void* element_p);

void clstSetElement (CLSTList list, unsigned position, void* element_p);

void* clstLookElement (const CLSTList list, unsigned position);

void* clstLookLastElement (const CLSTList list);

void* clstLookFirstElement (const CLSTList list);

void* clstGetElement (CLSTList list, unsigned position);

void* clstGetLastElement (CLSTList list);

void* clstGetFirstElement (CLSTList list);

void clstReverse (CLSTList list);

unsigned clstGetLength (const CLSTList list);

CLSTList clstSearch (
    const CLSTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
);

void* clstSearchElement (
    const CLSTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
);

int clstGetError (void);

/* ========================================================================== */

void clstPrint (const CLSTList list);

/* ========================================================================== */

int clstDefaultComparator (
    const void* element_p,
    void* element_of_comparison_p
);

/* ========================================================================== */

#endif

