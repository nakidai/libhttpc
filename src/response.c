#include "libhttpc.h"

#include <stddef.h>
#include <string.h>


char *LibHTTPC_dumpResponse(struct LibHTTPC_Response *response, char *buf, size_t buf_len)
{
    if (!response->version || !response->status || !response->phrase)
        return NULL;

#define append(X) strncat(buf, (X), buf_len - strlen(buf))
    append(response->version);
    append("");
    append(response->status);
    append(" ");
    append(response->phrase);
    append("\r\n");
    for (size_t i = 0; i < response->header_count; ++i)
    {
        append(response->header_names[i]);
        append(": ");
        append(response->header_values[i]);
        append("\r\n");
    }
    append("\r\n");
    if (response->body)
        append(response->body);
#undef append

    return NULL;
}
