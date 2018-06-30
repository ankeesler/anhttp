// This file contains an API for a wrapper around syscalls.

int anhttpSocket(int domain, int type, int protocol);
int anhttpListen(int socket, int backlog);
