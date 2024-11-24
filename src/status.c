#include "libhttpc.h"

#include <string.h>


#define STATUS(X) LibHTTPC_Status_##X

/* 1xx */
#define S_CONTINUE                  "Continue"
#define S_SWITCHING_PROTOCOLS       "Switching protocols"
/* 2xx */
#define S_OK                        "OK"
#define S_CREATED                   "Created"
#define S_ACCEPTED                  "Accepted"
#define S_NONAUTHORITATIVE_INFO     "Non-Authoritative Information"
#define S_NO_CONTENT                "No Content"
#define S_RESET_CONTENT             "Reset Content"
#define S_PARTIAL_CONTENT           "Partial Content"
/* 3xx */
#define S_MULTIPLE_CHOICES          "Multiple Choices"
#define S_MOVED_PERMANENTLY         "Moved Permanently"
#define S_FOUND                     "Found"
#define S_SEE_OTHER                 "See Other"
#define S_NOT_MODIFIED              "Not Modified"
#define S_USE_PROXY                 "Use Proxy"
#define S_TEMPORARY_REDIRECT        "Temporary Redirect"
/* 4xx */
#define S_BAD_REQUEST               "Bad Request"
#define S_UNAUTHORIZED              "Unauthorized"
#define S_PAYMENT_REQUIRED          "Payment Required"
#define S_FORBIDDEN                 "Forbidden"
#define S_NOT_FOUND                 "Not Found"
#define S_METHOD_NOT_ALLOWED        "Method Not Allowed"
#define S_NOT_ACCEPTABLE            "Not Acceptable"
#define S_PROXY_AUTH_REQUIRED       "Proxy Authentication Required"
#define S_REQUEST_TIMEOUT           "Request Timeout"
#define S_CONFLICT                  "Conflict"
#define S_GONE                      "Gone"
#define S_LENGTH_REQUIRED           "Length Required"
#define S_PRECONDITION_FAILED       "Precondition Failed"
#define S_ENTITY_TOO_LARGE          "Request Entity Too Large"
#define S_URI_TOO_LONG              "Request-URI Too Long"
#define S_UNSUPPORTED_MEDIA_TYPE    "Unsupported Media Type"
#define S_RANGE_NOT_SATISFIABLE     "Requested Range Not Satisfiable"
#define S_EXPECTATION_FAILED        "Expectation Failed"
/* 5xx */
#define S_INTERNAL_SERVER_ERROR     "Internal Server Error"
#define S_NOT_IMPLEMENTED           "Not Implemented"
#define S_BAD_GATEWAY               "Bad Gateway"
#define S_SERVICE_UNAVAILABLE       "Service Unavailable"
#define S_GATEWAY_TIMEOUT           "Gateway Timeout"
#define S_HTTP_VER_NOT_SUPPORTED    "HTTP Version Not Supported"

#define CHECK()                         \
    do                                  \
    {                                   \
        /* 1xx */                       \
        CASE(CONTINUE);                 \
        CASE(SWITCHING_PROTOCOLS);      \
        /* 2xx */                       \
        CASE(OK);                       \
        CASE(CREATED);                  \
        CASE(ACCEPTED);                 \
        CASE(NONAUTHORITATIVE_INFO);    \
        CASE(NO_CONTENT);               \
        CASE(RESET_CONTENT);            \
        CASE(PARTIAL_CONTENT);          \
        /* 3xx */                       \
        CASE(MULTIPLE_CHOICES);         \
        CASE(MOVED_PERMANENTLY);        \
        CASE(FOUND);                    \
        CASE(SEE_OTHER);                \
        CASE(NOT_MODIFIED);             \
        CASE(USE_PROXY);                \
        /* 306 is unused in HTTP/1.1 */ \
        CASE(TEMPORARY_REDIRECT);       \
        /* 4xx */                       \
        CASE(BAD_REQUEST);              \
        CASE(UNAUTHORIZED);             \
        CASE(PAYMENT_REQUIRED);         \
        CASE(FORBIDDEN);                \
        CASE(NOT_FOUND);                \
        CASE(METHOD_NOT_ALLOWED);       \
        CASE(NOT_ACCEPTABLE);           \
        CASE(PROXY_AUTH_REQUIRED);      \
        CASE(REQUEST_TIMEOUT);          \
        CASE(CONFLICT);                 \
        CASE(GONE);                     \
        CASE(LENGTH_REQUIRED);          \
        CASE(PRECONDITION_FAILED);      \
        CASE(ENTITY_TOO_LARGE);         \
        CASE(URI_TOO_LONG);             \
        CASE(UNSUPPORTED_MEDIA_TYPE);   \
        CASE(RANGE_NOT_SATISFIABLE);    \
        CASE(EXPECTATION_FAILED);       \
        /* 5xx */                       \
        CASE(INTERNAL_SERVER_ERROR);    \
        CASE(NOT_IMPLEMENTED);          \
        CASE(BAD_GATEWAY);              \
        CASE(SERVICE_UNAVAILABLE);      \
        CASE(GATEWAY_TIMEOUT);          \
        CASE(HTTP_VER_NOT_SUPPORTED);   \
    } while(0)

const char *LibHTTPC_dumpStatus(enum LibHTTPC_Status status)
{
    switch (status)
    {
#define CASE(X) case STATUS(X): return S_##X;
    CHECK();
#undef CASE
    }
    return NULL;
}
