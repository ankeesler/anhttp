#include "syscall.h"

#include <sys/socket.h>
#include <unistd.h>

int anhttpSocket(int domain, int type, int protocol) {
    return socket(domain, type, protocol);
}

int anhttpListen(int socket, int backlog) {
    return listen(socket, backlog);
}

int anhttpClose(int fd) {
    return close(fd);
}

int anhttpAccept(int fd, struct sockaddr *address, socklen_t *address_len) {
    return accept(fd, address, address_len);
}

int anhttpBind(int socket, const struct sockaddr *address, socklen_t address_len) {
    return bind(socket, address, address_len);
}
