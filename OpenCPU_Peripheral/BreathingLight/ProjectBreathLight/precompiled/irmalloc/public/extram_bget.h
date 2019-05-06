/*
    Interface definitions for bget.c, the memory management package.
*/

typedef long bufsize;
void extram_bpool(void *buffer, bufsize len);
void *extram_bget(bufsize size);
void *extram_bgetz(bufsize size);
void *extram_bgetr(void *buffer, bufsize newsize);
void extram_brel(void *buf);
void extram_bectl(int (*compact)(bufsize sizereq, int sequence), void *(*acquire)(bufsize size), void (*release)(void *buf), bufsize pool_incr);
void extram_bstats(bufsize *curalloc, bufsize *totfree, bufsize *maxfree, long *nget, long *nrel);
void extram_bstatse(bufsize *pool_incr, long *npool, long *npget, long *nprel, long *ndget, long *ndrel);
void extram_bufdump(void *buf);
void extram_bpoold(void *pool, int dumpalloc, int dumpfree);
int extram_bpoolv(void *pool);
