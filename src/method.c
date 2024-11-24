#include "libhttpc.h"

#include <string.h>


#define METHOD(X) LibHTTPC_Method_##X

#define S_OPTIONS   "OPTIONS"
#define S_GET       "GET"
#define S_HEAD      "HEAD"
#define S_POST      "POST"
#define S_PUT       "PUT"
#define S_DELETE    "DELETE"
#define S_TRACE     "TRACE"
#define S_CONNECT   "CONNECT"

#define CHECK()         \
    do                  \
    {                   \
        CASE(OPTIONS);  \
        CASE(GET);      \
        CASE(HEAD);     \
        CASE(POST);     \
        CASE(PUT);      \
        CASE(DELETE);   \
        CASE(TRACE);    \
        CASE(CONNECT);  \
    } while(0)

enum LibHTTPC_Method LibHTTPC_loadMethod(const char *method)
{
#define CASE(X) if (!strcmp((S_##X), method)) return METHOD(X)
    CHECK();
#undef CASE
    return METHOD(EXTENSION_METHOD);
}

const char *LibHTTPC_dumpMethod(enum LibHTTPC_Method method)
{
    switch (method)
    {
#define CASE(X) case METHOD(X): return S_##X
    CHECK();
#undef CASE
    }
    return NULL;
}
