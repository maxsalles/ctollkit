/*
**
** Prefix: err
** $ Herond Robaina Salles
*/

#ifndef _ERR_IMP
#define _ERR_IMP

#define ERR_FIRST_ERROR_ID (0)
#define ERR_LAST_ERROR_ID  (25)

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

/* ========================================================================== */

struct ERRError_ST {
    int id;
    const char* message;
};

struct ERRNodeErrorStack_ST {
    ERRError error;
    struct ERRNodeErrorStack_ST* next;
    struct ERRNodeErrorStack_ST* previous;
};

struct ERRErrorStack_ST {
    unsigned size;
    struct ERRNodeErrorStack_ST* first;
    struct ERRNodeErrorStack_ST* last;
};

/* ========================================================================== */

static int clean_stack_each_begin = 1;

static struct ERRErrorStack_ST global_error_stack = { 0, NULL, NULL };

/* ========================================================================== */

static struct ERRError_ST begin_st
    = { 0, NULL };

static struct ERRError_ST argument_list_too_long_st
    = { 1, "Argument list too long." };

static struct ERRError_ST permission_denied_st
    = { 2, "Permission denied." };

static struct ERRError_ST address_in_use_st
    = { 3, "Address in use." };

static struct ERRError_ST address_not_available_st
    = { 4, "Address not available." };

static struct ERRError_ST address_family_not_supported_st
    = { 5, "Address family not supported." };

static struct ERRError_ST resource_unavailable_st
    = { 6, "Resource unavailable." };

static struct ERRError_ST connection_already_in_progress_st
    = { 7, "Connection already in progress." };

static struct ERRError_ST device_or_resource_busy_st
    = { 8, "Device or resource busy." };

static struct ERRError_ST connection_aborted_st
    = { 9, "Connection aborted." };

static struct ERRError_ST connection_refused_st
    = { 10, "Connection refused." };

static struct ERRError_ST connection_reset_st
    = { 11, "Connection reset." };

static struct ERRError_ST destination_address_required_st
    = { 12, "Destination address required." };

static struct ERRError_ST argument_out_of_domain_of_function_st
    = { 13, "Argument out of domain of function." };

static struct ERRError_ST file_exists_st
    = { 14, "File exists." };

static struct ERRError_ST file_too_large_st
    = { 15, "File too large." };

static struct ERRError_ST identifier_removed_st
    = { 16, "Identifier removed." };

static struct ERRError_ST invalid_argument_st
    = { 17, "Invalid argument." };

static struct ERRError_ST message_too_large_st
    = { 18, "Message too large." };

static struct ERRError_ST no_buffer_space_available_st
    = { 19, "No buffer space available." };

static struct ERRError_ST file_format_invalid_st
    = { 20, "File format invalid." };

static struct ERRError_ST no_locks_available_st
    = { 21, "No locks available." };

static struct ERRError_ST not_enough_space_st
    = { 22, "Not enough space." };

static struct ERRError_ST result_too_large_st
    = { 23, "Result too large." };

static struct ERRError_ST null_access_pointer_st
    = { 24, "Null pointer." };

static struct ERRError_ST division_by_zero_st
    = { 25, "Division by zero." };

/* ========================================================================== */

const ERRError ERR_ARGUMENT_LIST_TOO_LONG = &argument_list_too_long_st;
const ERRError ERR_PERMISSION_DENIED = &permission_denied_st;
const ERRError ERR_ADDRESS_IN_USE = &address_in_use_st;
const ERRError ERR_ADDRESS_NOT_AVAILABLE = &address_not_available_st;

const ERRError ERR_ADDRESS_FAMILY_NOT_SUPPORTED =
    &address_family_not_supported_st;

const ERRError ERR_RESOURCE_UNAVAILABLE = &resource_unavailable_st;

const ERRError ERR_CONNECTION_ALREADY_IN_PROGRESS =
    &connection_already_in_progress_st;

const ERRError ERR_DEVICE_OR_RESOURCE_BUSY = &device_or_resource_busy_st;
const ERRError ERR_CONNECTION_ABORTED = &connection_aborted_st;
const ERRError ERR_CONNECTION_REFUSED = &connection_refused_st;
const ERRError ERR_CONNECTION_RESET = &connection_reset_st;

const ERRError ERR_DESTINATION_ADDRESS_REQUIRED =
    &destination_address_required_st;

const ERRError ERR_ARGUMENT_OUT_OF_DOMAIN_OF_FUNCTION =
    &argument_out_of_domain_of_function_st;

const ERRError ERR_FILE_EXISTS = &file_exists_st;
const ERRError ERR_FILE_TOO_LARGE = &file_too_large_st;
const ERRError ERR_IDENTIFIER_REMOVED = &identifier_removed_st;
const ERRError ERR_INVALID_ARGUMENT = &invalid_argument_st;
const ERRError ERR_MESSAGE_TOO_LARGE = &message_too_large_st;

const ERRError ERR_NO_BUFFER_SPACE_AVAILABLE =
    &no_buffer_space_available_st;

const ERRError ERR_FILE_FORMAT_INVALID = &file_format_invalid_st;
const ERRError ERR_NO_LOCKS_AVAILABLE = &no_locks_available_st;
const ERRError ERR_NOT_ENOUGH_SPACE = &not_enough_space_st;
const ERRError ERR_RESULT_TOO_LARGE = &result_too_large_st;
const ERRError ERR_ACCESS_NULL_POINTER = &null_access_pointer_st;
const ERRError ERR_DIVISION_BY_ZERO = &division_by_zero_st;

/* ========================================================================== */

static int errInsert (ERRErrorStack stack, ERRError error) {
    if (stack && error) {
        struct ERRNodeErrorStack_ST* node = (struct ERRNodeErrorStack_ST*)
            malloc(sizeof(struct ERRNodeErrorStack_ST));
            
        if (node) {
            node->error = error;
            node->next = NULL;
            node->previous = stack->last;
            
            if (stack->last) stack->last->next = node;
            else stack->first = node;
            
            stack->last = node;
            if (error->id != begin_st.id) stack->size ++;
        } else return 0;

        return 1;
    }

    return 0;
}

/* ========================================================================== */

ERRError errNew (void) {
    static int current_id = ERR_LAST_ERROR_ID + 1;
    ERRError error_return = (ERRError) malloc(sizeof(struct ERRError_ST));
    
    if (error_return) {
        error_return->id = current_id ++;
        error_return->message = NULL;
    } else errInsert(&global_error_stack, ERR_NOT_ENOUGH_SPACE);

    return error_return;
}

ERRError errNewcs (const char* message) {
    ERRError error_return = errNew();

    if (message && error_return)
        error_return->message = message;
        
    return error_return;
}

ERRErrorStack errNewStack (void) {
    ERRErrorStack stack_return = (ERRErrorStack) malloc(
        sizeof(struct ERRErrorStack_ST)
    );
    
    if (stack_return) {
        stack_return->size = 0;
        stack_return->first = NULL;
        stack_return->last = NULL;
    } else errInsert(&global_error_stack, ERR_NOT_ENOUGH_SPACE);
    
    return stack_return;
}

const char* errGetMessage (ERRError error) {
    if (error)
        return error->message;
    else errInsert(&global_error_stack, ERR_INVALID_ARGUMENT);
    
    return NULL;
}

void errDestroy (ERRError* error) {
    if (error && *error && ((*error)->id < ERR_FIRST_ERROR_ID ||
        (*error)->id > ERR_LAST_ERROR_ID)) {
        
        free(*error);
        *error = NULL;
    }
}

void errCleanStack(ERRErrorStack stack) {
    stack = stack == ERR_GLOBAL_STACK ? &global_error_stack : stack;
    
    {
        struct ERRNodeErrorStack_ST* current_error = NULL;
        
        while ((current_error = stack->first)) {
            stack->first = stack->first->next;
            if (current_error->error->id != begin_st.id) stack->size --;
            free(current_error);
        }
        
        stack->last = NULL;
    }
}

void errDestroyStack (ERRErrorStack* stack) {
    if (stack && *stack) {
        errCleanStack(*stack);
        free(*stack);
        *stack = NULL;
    }
}

void errEnable (int option) {
    switch (option) {
    case ERR_CLEAN_STACK_EACH_BEGIN:
        clean_stack_each_begin = 1;
        break;
    default:
        errInsert(&global_error_stack, ERR_INVALID_ARGUMENT);
    }
}

void errDisable (int option) {
    switch (option) {
    case ERR_CLEAN_STACK_EACH_BEGIN:
        clean_stack_each_begin = 0;
        break;
    default:
        errInsert(&global_error_stack, ERR_INVALID_ARGUMENT);
    }
}

void errAssert
    (int assertion, void (*action) (ERRErrorStack stack), ERRErrorStack stack) {
    
    if (action && !assertion) action(stack);
}

void errRaise (ERRError error) {
    if (error) errInsert(&global_error_stack, error);
    else errInsert(&global_error_stack, ERR_INVALID_ARGUMENT);
}


void errPush (ERRErrorStack stack, ERRError error) {
    if (error && stack) errInsert(stack, error);
    else errInsert(&global_error_stack, ERR_INVALID_ARGUMENT);
}

void errLocalBegin (ERRErrorStack stack) {
    if (stack) {
        if (clean_stack_each_begin) errCleanStack(stack);
        
        errInsert(stack, &begin_st);
    } else errInsert(&global_error_stack, ERR_INVALID_ARGUMENT);
}

void errBegin (void) {
    errLocalBegin(&global_error_stack);
}

int errLocalRescue (ERRErrorStack stack, ERRError error) {
    if (error) {
        if (stack) {
            struct ERRNodeErrorStack_ST* current_error = stack->last;

            while (current_error) {
                if (current_error->error->id == error->id) return 1;
                if (current_error->error->id == begin_st.id) return 0;
                
                current_error = current_error->previous;
            }
        }
    } else if (stack && stack->size) return 1;
    
    return 0;
}

int errRescue (ERRError error) {
    return errLocalRescue(&global_error_stack, error);
}

/*
void errDump (FILE* file);
void errStackDump (ERRErrorStack stack, FILE* file);

*/

void errPrint (ERRError error) {
    if (error)
        printf("EXCEPTION: (id %3i) %s",
            error->id, error->message ? error->message : ""
        );
    else errInsert(&global_error_stack, ERR_INVALID_ARGUMENT);
}

void errPrintln (ERRError error) {
    if (error)
        printf("EXCEPTION: (id %3i) %s\n",
            error->id, error->message ? error->message : ""
        );
    else errInsert(&global_error_stack, ERR_INVALID_ARGUMENT);
}

void errPrintStack (ERRErrorStack stack) {
    stack = stack == ERR_GLOBAL_STACK ? &global_error_stack : stack;
    
    printf("\n%s\n%3i exceptions.\n", stack == &global_error_stack ?
        "Stack global error." : "Stack local error.", stack->size
    );
    
    {
        int i = 1;
        struct ERRNodeErrorStack_ST* current_error = stack->first;

        while (current_error) {
            if (current_error->error->id != begin_st.id) {
                printf("%3i. ", i ++);
                errPrintln(current_error->error);
            }
            
            current_error = current_error->next;
        }
    }
}

/* ========================================================================== */

#endif
