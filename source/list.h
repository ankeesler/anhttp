// This is a "generic" array-list implementation.

typedef struct {
    long *elements;
    int length;
    int size;
} anhttpList_t;

// Initialize the list with an initial size.
void anhttpListInit(anhttpList_t *list, int size);

// Free the memory associated with the list.
void anhttpListFree(anhttpList_t *list);

// Get the length of the list.
#define anhttpListLength(list) ((list)->length)

// Get an item in the list.
#define anhttpListGet(list, i) ((list)->elements[(i)])

// Add something to the list.
#define anhttpListAdd(list, element) _anhttpListAdd((list), (long)(element))
void _anhttpListAdd(anhttpList_t *list, long element);
