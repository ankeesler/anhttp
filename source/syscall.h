// This file contains an API for a wrapper around syscalls.

#include <netinet/in.h>

int anhttpSocket(int domain, int type, int protocol);
int anhttpListen(int socket, int backlog);
int anhttpClose(int fd);
int anhttpAccept(int fd, struct sockaddr *address, socklen_t *address_len);
int anhttpBind(int socket, const struct sockaddr *address, socklen_t address_len);
