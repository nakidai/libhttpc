#include "config.h"
#include "libhttpc.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#ifdef LibHTTPC_SOCK
#include <sys/socket.h>
#endif


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

    if (!buf)
    {
        if (!LibHTTPC_malloc)
            return NULL;

        size_t buf_len = (
            1
            + strlen(response->version) + 1
            + strlen(status) + 1
            + strlen(response->phrase) + 2
            + 2
        );
        for (size_t i = 0; i < response->header_count; ++i)
            buf_len += (
                strlen(response->headers[i].name)
                + 2
                + strlen(response->headers[i].value)
                + 2
            );
        if (response->body)
            buf_len += strlen(response->body);
        buf = malloc(buf_len);
        if (!buf)
            return NULL;

        *buf = '\0';
    }

#define append(X) strncat(buf, (X), buf_len - strlen(buf))
    WRITE();
#undef append

    return buf;
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
