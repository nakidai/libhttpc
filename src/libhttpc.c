#include "libhttpc.h"


void LibHTTPC(LibHTTPC_Malloc *malloc, LibHTTPC_Realloc *realloc, LibHTTPC_Free *free)
{
    LibHTTPC_malloc     = malloc;
    LibHTTPC_realloc    = realloc;
    LibHTTPC_free       = free;
}
