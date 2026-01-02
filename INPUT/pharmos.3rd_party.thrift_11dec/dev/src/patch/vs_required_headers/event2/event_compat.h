#pragma once

#define EV_READ 0
#define EV_PERSIST 0
#define EV_WRITE 0

#define F_GETFD 0
#define F_SETFD 0
#define FD_CLOEXEC 0

#include <winsock2.h>
typedef SOCKET evutil_socket_t;

int EVUTIL_SOCKET_ERROR()
{
    return -1;
}

void event_set(struct event*, evutil_socket_t, short, void (*)(evutil_socket_t, short, void*), void*)
{
}

const char* event_get_version()
{
    return "";
}

const char* event_base_get_method(const struct event_base* base)
{
    return "";
}

int event_base_loop(struct event_base* base, int flags)
{
    return 0;
}

int event_base_loopbreak(struct event_base* event_base)
{
    return 0;
}

struct event_base* event_base_new()
{
    return nullptr;
}

int event_base_set(struct event_base* eb, struct event* ev)
{
    return 0;
}

int event_add(struct event* ev, int i)
{
    return 0;
}

short event_del(event* ev)
{
    return 0;
}

void event_base_free(struct event_base* eb)
{
}

int evutil_socketpair(int family, int type, int protocol, evutil_socket_t fd[2])
{
    return 0;
}

int evutil_make_socket_nonblocking(evutil_socket_t fd)
{
    return 0;
}
