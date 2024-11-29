#include "config.h"
#include "libhttpc.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>


#define WRITE()                                             \
    do                                                      \
    {                                                       \
        append(response->version);                          \
        append(" ");                                        \
        append(status);                                     \
        append(" ");                                        \
        append(response->phrase);                           \
        append("\r\n");                                     \
        for (size_t i = 0; i < response->header_count; ++i) \
        {                                                   \
            append(response->headers[i].name);              \
            append(": ");                                   \
            append(response->headers[i].value);             \
            append("\r\n");                                 \
        }                                                   \
        append("\r\n");                                     \
        if (response->body)                                 \
            append(response->body);                         \
    } while (0)


char *LibHTTPC_dumpResponse(struct LibHTTPC_Response *response, char *buf, size_t buf_len)
{
    char status[10];

    if (!response->version)
        response->version = "HTTP/1.1";
    if (!response->status)
        response->status = LibHTTPC_Status_OK;
    if (!response->phrase)
        response->phrase = LibHTTPC_dumpStatus(response->status);

    snprintf(status, sizeof(status), "%d", response->status);

#define append(X) strncat(buf, (X), buf_len - strlen(buf))
    WRITE();
#undef append

    return NULL;
}

#ifdef LibHTTPC_SOCK
int LibHTTPC_writeResponse(int sockfd, struct LibHTTPC_Response *response)
{
    char status[10];

    if (!response->version)
        response->version = "HTTP/1.1";
    if (!response->status)
        response->status = LibHTTPC_Status_OK;
    if (!response->phrase)
        response->phrase = LibHTTPC_dumpStatus(response->status);

    snprintf(status, sizeof(status), "%d", response->status);

#define append(X)                                   \
    do                                              \
    {                                               \
        if (send(sockfd, (X), strlen(X), 0) == -1)  \
            return 1;                               \
    } while(0)
    WRITE();
#undef append

    return 0;
}
#endif
