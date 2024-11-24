#include "libhttpc.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>


char *LibHTTPC_dumpResponse(struct LibHTTPC_Response *response, char *buf, size_t buf_len)
{
    char status[10];

    if (!response->version)
        response->version = "HTTP/1.1";
    if (!response->status)
        response->status = LibHTTPC_Status_OK;
    if (!response->phrase)
        response->phrase = LibHTTPC_dumpStatus(LibHTTPC_Status_OK);

    snprintf(status, sizeof(status), "%d", response->status);

#define append(X) strncat(buf, (X), buf_len - strlen(buf))
    append(response->version);
    append("");
    append(status);
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
