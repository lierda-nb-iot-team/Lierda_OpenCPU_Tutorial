#ifndef BACKTRACE_H_
#define BACKTRACE_H_
#include "neulfw.h"
#include <unwind.h>

/** @defgroup libNEUL_BACKTRACE Hi21XX Backtrace
 * Hi21XX Backtrace
 * @ingroup HI21XX_MODULES
 * @{
 * */


#define BACKTRACE_DEPTH 10

/** A structure to hold a stack backtrace */
typedef struct
{
    int depth;
    unsigned entries[BACKTRACE_DEPTH];
} backtrace_t;

#if defined  (STACKDUMP)
#define STACKDUMP_DEPTH 20
typedef struct
{
    int depth;
    unsigned entries[STACKDUMP_DEPTH];
} stackdump_t;
#endif

/* Note that, for these functions to work, GCC needs to get the -funwind-tables
 * option so that backtracing information is built in. */

/**Record a backtrace into preserve memory.
 */
void record_backtrace(void);

/** Get a recorded backtrace, if any, and then invalidate it.
 *
 * @return  true if there was a valid backtrace, false otherwise.
 * @param[out] out  Some memory to write the backtrace into.
 */
bool get_backtrace(backtrace_t *out);

/**Record a backtrace into preserve memory and then loop forever.
 *
 * With the watchdog on, it'll reset us.
 */
void record_backtrace_and_die(void);

#if defined (STACKDUMP)
inline uint32 trace_get_sp(void)
{
    register uint32 uwSpSave;
    __asm volatile(     \
        "mov %0, sp"          \
        : "=r"(uwSpSave));
    return uwSpSave;
}

void record_call_stack(uint32 stack_pointer);

bool get_stackdump(stackdump_t *out);
#endif

/** @} end of group libNEUL_BACKTRACE */

#endif /* BACKTRACE_H_ */

