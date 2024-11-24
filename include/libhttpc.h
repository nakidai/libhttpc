#ifndef __LIBHTTPC_H__
#define __LIBHTTPC_H__

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>


/**
 * Just typedef to make libhttpc_malloc definition more readable
 * @see LibHTTPC_malloc
 */
typedef void *LibHTTPC_Malloc(size_t);
/**
 * Just typedef to make libhttpc_realloc definition more readable
 * @see libhttpc_realloc
 */
typedef void *LibHTTPC_Realloc(void *, size_t);

/**
 * Enum that contains all headers that are supported by the HTTP/1.1
 */
enum LibHTTPC_Header
{
    /* General headers */
    LibHTTPC_Header_CACHE_CONTROL,
    LibHTTPC_Header_CONNECTION,
    LibHTTPC_Header_DATE,
    LibHTTPC_Header_PRAGMA,
    LibHTTPC_Header_TRAILER,
    LibHTTPC_Header_TRANSFER_ENCODING,
    LibHTTPC_Header_UPGRADE,
    LibHTTPC_Header_VIA,
    LibHTTPC_Header_WARNING,
    /* Request headers */
    LibHTTPC_Header_ACCEPT,
    LibHTTPC_Header_ACCEPT_CHARSET,
    LibHTTPC_Header_ACCEPT_ENCODING,
    LibHTTPC_Header_ACCEPT_LANGUAGE,
    LibHTTPC_Header_AUTHORIZATION,
    LibHTTPC_Header_EXPECT,
    LibHTTPC_Header_FROM,
    LibHTTPC_Header_HOST,
    LibHTTPC_Header_IF_MATCH,
    LibHTTPC_Header_IF_MODIFIED_SINCE,
    LibHTTPC_Header_IF_NONE_MATCH,
    LibHTTPC_Header_IF_RANGE,
    LibHTTPC_Header_IF_UNMODIFIED_SINCE,
    LibHTTPC_Header_MAX_FORWARDS,
    LibHTTPC_Header_PROXY_AUTHORIZATION,
    LibHTTPC_Header_RANGE,
    LibHTTPC_Header_REFERER,
    LibHTTPC_Header_TE,
    LibHTTPC_Header_USER_AGENT,
    /* Response headers */
    LibHTTPC_Header_ACCEPT_RANGES,
    LibHTTPC_Header_AGE,
    LibHTTPC_Header_ETAG,
    LibHTTPC_Header_LOCATION,
    LibHTTPC_Header_PROXY_AUTHENTICATE,
    LibHTTPC_Header_RETRY_AFTER,
    LibHTTPC_Header_SERVER,
    LibHTTPC_Header_VARY,
    LibHTTPC_Header_WWW_AUTHENTICATE,
    /* Entity headers */
    LibHTTPC_Header_ALLOW,
    LibHTTPC_Header_CONTENT_ENCODING,
    LibHTTPC_Header_CONTENT_LANGUAGE,
    LibHTTPC_Header_CONTENT_LENGTH,
    LibHTTPC_Header_CONTENT_LOCATION,
    LibHTTPC_Header_CONTENT_MD5,
    LibHTTPC_Header_CONTENT_RANGE,
    LibHTTPC_Header_CONTENT_TYPE,
    LibHTTPC_Header_EXPIRES,
    LibHTTPC_Header_LAST_MODIFIED,

    LibHTTPC_Header_EXTENSION_HEADER,
};

/**
 * Enum that contains all methods that are supported by the HTTP/1.1
 */
enum LibHTTPC_Method
{
    LibHTTPC_Method_OPTIONS,
    LibHTTPC_Method_GET,
    LibHTTPC_Method_HEAD,
    LibHTTPC_Method_POST,
    LibHTTPC_Method_PUT,
    LibHTTPC_Method_DELETE,
    LibHTTPC_Method_TRACE,
    LibHTTPC_Method_CONNECT,
    LibHTTPC_Method_EXTENSION_METHOD,
};

/**
 * Enum that contains all statuses that are supported by the HTTP/1.1
 */
enum LibHTTPC_Status
{
    /* 1xx */
    LibHTTPC_Status_CONTINUE               = 100,
    LibHTTPC_Status_SWITCHING_PROTOCOLS    = 101,
    /* 2xx */
    LibHTTPC_Status_OK                     = 200,
    LibHTTPC_Status_CREATED                = 201,
    LibHTTPC_Status_ACCEPTED               = 202,
    LibHTTPC_Status_NONAUTHORITATIVE_INFO  = 203,
    LibHTTPC_Status_NO_CONTENT             = 204,
    LibHTTPC_Status_RESET_CONTENT          = 205,
    LibHTTPC_Status_PARTIAL_CONTENT        = 206,
    /* 3xx */
    LibHTTPC_Status_MULTIPLE_CHOICES       = 300,
    LibHTTPC_Status_MOVED_PERMANENTLY      = 301,
    LibHTTPC_Status_FOUND                  = 302,
    LibHTTPC_Status_SEE_OTHER              = 303,
    LibHTTPC_Status_NOT_MODIFIED           = 304,
    LibHTTPC_Status_USE_PROXY              = 305,
    /* 306 is unused in HTTP/1.1 */
    LibHTTPC_Status_TEMPORARY_REDIRECT     = 307,
    /* 4xx */
    LibHTTPC_Status_BAD_REQUEST            = 400,
    LibHTTPC_Status_UNAUTHORIZED           = 401,
    LibHTTPC_Status_PAYMENT_REQUIRED       = 402,
    LibHTTPC_Status_FORBIDDEN              = 403,
    LibHTTPC_Status_NOT_FOUND              = 404,
    LibHTTPC_Status_METHOD_NOT_ALLOWED     = 405,
    LibHTTPC_Status_NOT_ACCEPTABLE         = 406,
    LibHTTPC_Status_PROXY_AUTH_REQUIRED    = 407,
    LibHTTPC_Status_REQUEST_TIMEOUT        = 408,
    LibHTTPC_Status_CONFLICT               = 409,
    LibHTTPC_Status_GONE                   = 410,
    LibHTTPC_Status_LENGTH_REQUIRED        = 411,
    LibHTTPC_Status_PRECONDITION_FAILED    = 412,
    LibHTTPC_Status_ENTITY_TOO_LARGE       = 413,
    LibHTTPC_Status_URI_TOO_LONG           = 414,
    LibHTTPC_Status_UNSUPPORTED_MEDIA_TYPE = 415,
    LibHTTPC_Status_RANGE_NOT_SATISFIABLE  = 416,
    LibHTTPC_Status_EXPECTATION_FAILED     = 417,
    /* 5xx */
    LibHTTPC_Status_INTERNAL_SERVER_ERROR  = 500,
    LibHTTPC_Status_NOT_IMPLEMENTED        = 501,
    LibHTTPC_Status_BAD_GATEWAY            = 502,
    LibHTTPC_Status_SERVICE_UNAVAILABLE    = 503,
    LibHTTPC_Status_GATEWAY_TIMEOUT        = 504,
    LibHTTPC_Status_HTTP_VER_NOT_SUPPORTED = 505,
};

/**
 * Struct that contains parsed request.
 * @see LibHTTPC_loadRequest
 */
struct LibHTTPC_Request
{
    char    *buf;                    /**< Pointer to char *request */
    char    *method, *uri, *version; /**< Request line */
    char   **header_names;           /**< \ Header parallel array  */
    char   **header_values;          /**< / Header parallel array  */
    char    *body;                   /**< Pointer to body */
    size_t   header_count;           /**< Length of header array */
    int      selfalloc;              /**< Marker if request was allocated by the library */
    int      header_selfalloc;       /**< Marker if header array was allocated by the library */
};

/**
 * Struct that contains response
 * @see LibHTTPC_dumpResponse
 */
struct LibHTTPC_Response
{
    char    *buf;                       /**< Pointer to char *response */
    char    *version, *status, *phrase; /**< Response line */
    char   **header_names;              /**< \ Header parallel array */
    char   **header_values;             /**< / Header parallel array */
    char    *body;                      /**< Pointer to body */
    size_t   header_count;              /**< Length of header array */
};

/**
 * Malloc used by the library
 */
extern LibHTTPC_Malloc *LibHTTPC_malloc;
/**
 * Realloc used by the library
 */
extern LibHTTPC_Realloc *LibHTTPC_realloc;

/**
 * Setup LibHTTPC_malloc and LibHTTPC_realloc
 * @param malloc Malloc implementation
 * @param realloc Realloc implementation
 */
void LibHTTPC(LibHTTPC_Malloc *malloc, LibHTTPC_Realloc *realloc);

/**
 * Parse header name
 */
enum LibHTTPC_Header LibHTTPC_loadHeader(const char *header);
/**
 * Parse method name
 */
enum LibHTTPC_Method LibHTTPC_loadMethod(const char *method);

/**
 * Get name of the header by enum LibHTTPC_Header
 */
const char *LibHTTPC_dumpHeader(enum LibHTTPC_Header header);
/**
 * Get name of the header by enum LibHTTPC_Method
 */
const char *LibHTTPC_dumpMethod(enum LibHTTPC_Method method);
/**
 * Get name of the header by enum LibHTTPC_Status
 */
const char *LibHTTPC_dumpStatus(enum LibHTTPC_Status status);

/**
 * Load request from string. Be careful as this function will destroy buf after
 * run
 * @param[out] request_buf Pointer to buffer where to save request.
 *
 *                         request_buf.header_count should be either set to size of header_names and header_values or to
 *                         -1.
 *
 *                         If (request_buf.header_count == -1), then library will allocate header array itself and set
 *                         request_buf.header_count to amount of headers.
 *
 *                         If (request_buf == NULL), then library will allocate buffer itself using LibHTTPC_malloc and
 *                         LibHTTPC_realloc. It will also set request_buf.header_count to -1.
 *
 *                         If function wants to use malloc or realloc, but they aren't set, it will return NULL.
 * @param[in]  buf         Buffer that contains request to parse
 * @see LibHTTPC
 * @see LibHTTPC_Request_
 */
struct LibHTTPC_Request *LibHTTPC_loadRequest(struct LibHTTPC_Request *request_buf, char *buf);
/**
 * Construct C-String with resopnse that can be sent to client from
 * LibHTTPC_Response struct
 * @param[in]  response Pointer to response
 * @param[out] buf      Pointer to buffer where to save formatted response
 * @param      buf_len  Size of buf
 */
char *LibHTTPC_dumpResponse(struct LibHTTPC_Response *response, char *buf, size_t buf_len);

/**
 * Destructor for LibHTTPC_Request
 * @param request Request to free
 */
void LibHTTPC_Request_(struct LibHTTPC_Request *request);

/**
 * Not implemented yet
 */
struct LibHTTPC_Request *LibHTTPC_readRequest(
    int sockfd,
    struct LibHTTPC_Request *request_buf,
    char *buf, size_t buf_len
);

/**
 * Not implemented yet
 */
int LibHTTPC_writeResponse(int sockfd, struct LibHTTPC_Response *response);

#endif /* __LIBHTTPC_H__ */
