#include "libhttpc.h"

#include <stddef.h>
#include <string.h>


struct LibHTTPC_Request *LibHTTPC_loadRequest(struct LibHTTPC_Request *request_buf, char *buf)
{
    char *next;
    int selfmalloc = 0;

    if (!buf)
        return NULL;

    if (!request_buf)
    {
        request_buf = LibHTTPC_malloc(sizeof(struct LibHTTPC_Request));
        memset(request_buf, '\0', sizeof(struct LibHTTPC_Request));
        request_buf->selfalloc = 1;
        request_buf->header_count = -1;
    }

    if (request_buf->header_count == -1)
    {
        if (!LibHTTPC_malloc || !LibHTTPC_realloc)
            return NULL;
        selfmalloc = 1;
        request_buf->header_selfalloc = 1;
        request_buf->header_count = 0;
    }

    request_buf->method = request_buf->buf = buf;

    next = strchr(request_buf->method, ' ');
    *next = '\0';
    request_buf->uri = next + 1;

    next = strchr(request_buf->uri, ' ');
    *next = '\0';
    request_buf->version = next + 1;

    next = strstr(request_buf->version, "\r\n");
    *next++ = '\0';

    for (size_t i = 0; (next = strstr(next, "\r\n")); ++next, ++i)
    {
        *next = '\0';
        next += 2;

        if (strstr(next, "\r\n") == next)
            break;

        if (selfmalloc)
        {
            ++request_buf->header_count;
            if (!request_buf->headers)
                request_buf->headers = LibHTTPC_malloc(sizeof(struct LibHTTPC_Header));
            else
                request_buf->headers = LibHTTPC_realloc(request_buf->headers, sizeof(struct LibHTTPC_Header));
        }
        if (i < request_buf->header_count)
        {
            request_buf->headers[i].name = next;
            next = strchr(next, ':');
            *next++ = '\0';
            request_buf->headers[i].value = next;
        }
    }
    request_buf->body = next + 2;

    return request_buf;
}

void LibHTTPC_Request_(struct LibHTTPC_Request *request)
{
    if (request->header_selfalloc)
        LibHTTPC_free(request->headers);
    if (request->selfalloc)
        LibHTTPC_free(request);
}
