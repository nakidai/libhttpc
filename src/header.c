#include "libhttpc.h"

#include <ctype.h>


#define HEADER(X) LibHTTPC_Header_##X

/* General headers */
#define S_CACHE_CONTROL         "Cache-Control"
#define S_CONNECTION            "Connection"
#define S_DATE                  "Date"
#define S_PRAGMA                "Pragma"
#define S_TRAILER               "Trailer"
#define S_TRANSFER_ENCODING     "Transfer-Encoding"
#define S_UPGRADE               "Upgrade"
#define S_VIA                   "Via"
#define S_WARNING               "Warning"
/* Request headers */
#define S_ACCEPT                "Accept"
#define S_ACCEPT_CHARSET        "Accept-Charset"
#define S_ACCEPT_ENCODING       "Accept-Encoding"
#define S_ACCEPT_LANGUAGE       "Accept-Language"
#define S_AUTHORIZATION         "Authorization"
#define S_EXPECT                "Expect"
#define S_FROM                  "From"
#define S_HOST                  "Host"
#define S_IF_MATCH              "If-Match"
#define S_IF_MODIFIED_SINCE     "If-Modified-Since"
#define S_IF_NONE_MATCH         "If-None-Match"
#define S_IF_RANGE              "If-Range"
#define S_IF_UNMODIFIED_SINCE   "If-Unmodified-Since"
#define S_MAX_FORWARDS          "Max-Forwards"
#define S_PROXY_AUTHORIZATION   "Proxy-Authorization"
#define S_RANGE                 "Range"
#define S_REFERER               "Referer"
#define S_TE                    "TE"
#define S_USER_AGENT            "User-Agent"
/* Response headers */
#define S_ACCEPT_RANGES         "Accept-Ranges"
#define S_AGE                   "Age"
#define S_ETAG                  "ETag"
#define S_LOCATION              "Location"
#define S_PROXY_AUTHENTICATE    "Proxy-Authenticate"
#define S_RETRY_AFTER           "Retry-After"
#define S_SERVER                "Server"
#define S_VARY                  "Vary"
#define S_WWW_AUTHENTICATE      "WWW-Authenticate"
/* Entity headers */
#define S_ALLOW                 "Allow"
#define S_CONTENT_ENCODING      "Content-Encoding"
#define S_CONTENT_LANGUAGE      "Content-Language"
#define S_CONTENT_LENGTH        "Content-Length"
#define S_CONTENT_LOCATION      "Content-Location"
#define S_CONTENT_MD5           "Content-MD5"
#define S_CONTENT_RANGE         "Content-Range"
#define S_CONTENT_TYPE          "Content-Type"
#define S_EXPIRES               "Expires"
#define S_LAST_MODIFIED         "Last-Modified"

static int strieq(const char *a, const char *b)
{
    while (*a && tolower(*a) == tolower(*b)) ++a, ++b;
    return tolower(*a) == tolower(*b);
}

#define CHECK()                     \
    do                              \
    {                               \
        /* General headers */       \
        CASE(CACHE_CONTROL);        \
        CASE(CONNECTION);           \
        CASE(DATE);                 \
        CASE(PRAGMA);               \
        CASE(TRAILER);              \
        CASE(TRANSFER_ENCODING);    \
        CASE(UPGRADE);              \
        CASE(VIA);                  \
        CASE(WARNING);              \
        /* Request headers */       \
        CASE(ACCEPT);               \
        CASE(ACCEPT_CHARSET);       \
        CASE(ACCEPT_ENCODING);      \
        CASE(ACCEPT_LANGUAGE);      \
        CASE(AUTHORIZATION);        \
        CASE(EXPECT);               \
        CASE(FROM);                 \
        CASE(HOST);                 \
        CASE(IF_MATCH);             \
        CASE(IF_MODIFIED_SINCE);    \
        CASE(IF_NONE_MATCH);        \
        CASE(IF_RANGE);             \
        CASE(IF_UNMODIFIED_SINCE);  \
        CASE(MAX_FORWARDS);         \
        CASE(PROXY_AUTHORIZATION);  \
        CASE(RANGE);                \
        CASE(REFERER);              \
        CASE(TE);                   \
        CASE(USER_AGENT);           \
        /* Response headers */      \
        CASE(ACCEPT_RANGES);        \
        CASE(AGE);                  \
        CASE(ETAG);                 \
        CASE(LOCATION);             \
        CASE(PROXY_AUTHENTICATE);   \
        CASE(RETRY_AFTER);          \
        CASE(SERVER);               \
        CASE(VARY);                 \
        CASE(WWW_AUTHENTICATE);     \
        /* Entity headers */        \
        CASE(ALLOW);                \
        CASE(CONTENT_ENCODING);     \
        CASE(CONTENT_LANGUAGE);     \
        CASE(CONTENT_LENGTH);       \
        CASE(CONTENT_LOCATION);     \
        CASE(CONTENT_MD5);          \
        CASE(CONTENT_RANGE);        \
        CASE(CONTENT_TYPE);         \
        CASE(EXPIRES);              \
        CASE(LAST_MODIFIED);        \
    } while(0)

enum LibHTTPC_HeaderType LibHTTPC_loadHeader(const char *header)
{
#define CASE(X) if (!strieq((S_##X), header)) return HEADER(X)
    CHECK();
#undef CASE
    return HEADER(EXTENSION_HEADER);
}

const char *LibHTTPC_dumpHeader(enum LibHTTPC_HeaderType header)
{
    switch (header)
    {
#define CASE(X) case HEADER(X): return S_##X;
    CHECK();
#undef CASE
    }
    return NULL;
}
