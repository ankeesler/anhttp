#include <sys/socket.h>

int anhttpSocket(int domain, int type, int protocol) {
    return socket(domain, type, protocol);
}

int anhttpListen(int socket, int backlog) {
    return listen(socket, backlog);
}
