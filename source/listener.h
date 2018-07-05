// Listener socket operations.

#include "anhttp/anhttp.h"
#include "thread.h"
#include "connection_queue.h"

// Create a socket on which to listen.
// Returns -1 if something went wrong.
int anhttpCreateListener(const char *address, int port);

// Close a listener socket.
// Returns -1 if something went wrong.
int anhttpCloseListener(int listener);

// Listen on a socket for connections.
// Use the thread argument to stop the listener thread when necessary.
// The listener thread will write connections to the connectionQ.
// If the listener falls over, it will write a -1 fd to the connectionQ.
// Returns an error indicating whether or not the listener was started successfully.
//AnhttpError_t anhttpStartListener(int listener, anhttpThread_t *thread, anhttpConnectionQueue_t *connectionQ);
