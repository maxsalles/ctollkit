/*
**
** Prefix: err
** $ Herond Robaina Salles
*/

#ifndef _ERR_LIB
#define _ERR_LIB

#define ERR_ANY_ERROR    (NULL)
#define ERR_GLOBAL_STACK (NULL)

#include <stdio.h>

/* ========================================================================== */

struct ERRError_ST;
struct ERRErrorStack_ST;

typedef struct ERRError_ST* ERRError;
typedef struct ERRErrorStack_ST* ERRErrorStack;

enum ERRInternOption_EN { ERR_CLEAN_STACK_EACH_BEGIN };

/* ========================================================================== */

const ERRError ERR_ARGUMENT_LIST_TOO_LONG;
const ERRError ERR_PERMISSION_DENIED;
const ERRError ERR_ADDRESS_IN_USE;
const ERRError ERR_ADDRESS_NOT_AVAILABLE;
const ERRError ERR_ADDRESS_FAMILY_NOT_SUPPORTED;
const ERRError ERR_RESOURCE_UNAVAILABLE;
const ERRError ERR_CONNECTION_ALREADY_IN_PROGRESS;
const ERRError ERR_DEVICE_OR_RESOURCE_BUSY;
const ERRError ERR_CONNECTION_ABORTED;
const ERRError ERR_CONNECTION_REFUSED;
const ERRError ERR_CONNECTION_RESET;
const ERRError ERR_DESTINATION_ADDRESS_REQUIRED;
const ERRError ERR_ARGUMENT_OUT_OF_DOMAIN_OF_FUNCTION;
const ERRError ERR_FILE_EXISTS;
const ERRError ERR_FILE_TOO_LARGE;
const ERRError ERR_IDENTIFIER_REMOVED;
const ERRError ERR_INVALID_ARGUMENT;
const ERRError ERR_MESSAGE_TOO_LARGE;
const ERRError ERR_NO_BUFFER_SPACE_AVAILABLE;
const ERRError ERR_FILE_FORMAT_INVALID;
const ERRError ERR_NO_LOCKS_AVAILABLE;
const ERRError ERR_NOT_ENOUGH_SPACE;
const ERRError ERR_RESULT_TOO_LARGE;
const ERRError ERR_ACCESS_NULL_POINTER;
const ERRError ERR_DIVISION_BY_ZERO;

/* ========================================================================== */

ERRError errNew (void);
ERRError errNewcs (const char* message);
ERRErrorStack errNewStack (void);

const char* errGetMessage (ERRError error);

void errDestroy (ERRError* error);
void errCleanStack(ERRErrorStack stack);
void errDestroyStack (ERRErrorStack* stack);

void errEnable (int option);
void errDisable (int option);
void errAssert
    (int assertion, void (*action) (ERRErrorStack stack), ERRErrorStack stack);

void errRaise (ERRError error);
void errPush (ERRErrorStack stack, ERRError error);

void errBegin (void);
void errLocalBegin (ERRErrorStack stack);
int errRescue (ERRError error);
int errLocalRescue (ERRErrorStack stack, ERRError error);

/*
void errDump (FILE* file);
void errStackDump (ERRErrorStack stack, FILE* file);

*/

void errPrint (ERRError error);
void errPrintln (ERRError error);
void errPrintStack (ERRErrorStack stack);

/* ========================================================================== */

#endif
