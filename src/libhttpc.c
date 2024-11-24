#include "libhttpc.h"


void LibHTTPC(LibHTTPC_Malloc *malloc, LibHTTPC_Realloc *realloc)
{
    LibHTTPC_malloc = malloc;
    LibHTTPC_realloc = realloc;
}
