/******************************************************************************
 * @brief    UNIT TEST HEADERS
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef UNIT_TEST_H_
#define UNIT_TEST_H_

/** @addtogroup COMMON_TYPES
 * @{
 * */

/**
 * Define a static function, which we want to expose for unit testing
 */
#if defined(CXXTEST) || defined (ROBOT_TEST)
#define STATIC_UNIT_TESTABLE 
#else
#define STATIC_UNIT_TESTABLE static
#endif

/**
 * Define an inline function, which we want to expose for unit testing
 */
#if defined(CXXTEST) || defined (ROBOT_TEST)
#define INLINE_UNIT_TESTABLE
#else
#define INLINE_UNIT_TESTABLE inline
#endif

/**
 * Define an inline function, which we want to expose for unit testing
 */
#if defined(CXXTEST) || defined (ROBOT_TEST)
#define STATIC_INLINE_UNIT_TESTABLE
#else
#define STATIC_INLINE_UNIT_TESTABLE static inline
#endif

#ifdef CXXTEST
/** Use this to declare functions which may have wrapper functions when running unit tests.
 *
 * Wrapped functions need C linkage to prevent their names getting mangled.
 */
#define UNIT_TEST_WRAPPABLE extern "C"
#else
#define UNIT_TEST_WRAPPABLE
#endif

#ifdef CXXTEST
/** Redirect calls to the WRAPPED function to a new target.
 *
 * You can use this in your unit tests to point the function at a new one for
 * the duration of the test.
 *
 * Redirect to NULL to have the wrapper defined by WRAPPED_FN point back to the
 * real function again (e.g. at the end of your test).
 */
#define WRAPPED_FP_REDIRECT(WRAPPED, TARGET) \
    ( __wrap_##WRAPPED##_fp = TARGET )

/** Declare the prototype for the function pointer needed by WRAPPED_FP_REDIRECT.
 *
 * @param   RETURN_TYPE     The return type of the wrapped function (may be void).
 * @param   NAME            The name of the wrapped function.
 * @param   ARGS            The argument list in brackets, e.g. (void) or (uint32 fred).
 */
#define WRAPPED_FP(RETURN_TYPE, NAME, ARGS) \
    /** Wrapper for NAME */                   \
    extern RETURN_TYPE (*__wrap_##NAME##_fp) ARGS

/** Define a wrapper function for the named function, and a function pointer.
 *
 * Use this without a semicolon, because function definitions don't end with a semi-colon!
 *
 * If the function pointer is NULL, the real function is called from the
 * wrapper. If it is not, the function pointed to is called instead.
 *
 * @param   RETURN_TYPE     The return type of the wrapped function (may be void).
 * @param   NAME            The name of the wrapped function.
 * @param   ARGS            The argument list in brackets, e.g. (void) or (uint32 fred).
 * @param   CALL            The list of parameters without their types, used to call the wrapped function or pointer. () for a void function.
 */
#define WRAPPED_FN(RETURN_TYPE, NAME, ARGS, CALL) \
    /* The linker's magic symbols. These need C linkage to stop the names getting mangled. */ \
    extern "C" RETURN_TYPE  __wrap_##NAME ARGS;   \
    extern "C" RETURN_TYPE  __real_##NAME ARGS;   \
    /* The function pointer we use */             \
    RETURN_TYPE (*__wrap_##NAME##_fp) ARGS;       \
    /* The wrapper */                             \
    RETURN_TYPE __wrap_##NAME ARGS                \
    {                                             \
        if (__wrap_##NAME##_fp)                   \
            return __wrap_##NAME##_fp CALL;       \
        else                                      \
            return __real_##NAME CALL;            \
    }                                             \

#define TYPE_AND_NAME_COMMA(prefix, type, name) type name,
#define TYPE_AND_NAME(prefix, type, name) type name
#define NAME_AND_COMMA(prefix, type, name) name,
#define NAME(prefix, type, name) name
#define PREFIX_NAME_EQUALS_NAME(prefix, type, name) prefix ## _ ## name = name;
#define TYPE_PREFIX_AND_NAME(prefix, type, name) type prefix ## _ ## name;

/** Define a simple wrapper which will be fixed throughout the execution of the test.
 *
 * Unlike the macros above, this one just replaces the named function at link time with no option to
 * switch to calling the real one (or a different replacement) at run time.
 *
 * The macro should be used at the top level of your _test_.h file. It will define something like this:
 *
 * for each argument, a variable you can read in your test:
 * arg_type fn_name_arg_name;
 *
 * A call counter as a variable you can read in your test:
 * unsigned fn_name_cc;
 *
 * A return value as a variable you can set in your test, before calling the function:
 * ret_type fn_name_ret;
 *
 * The linker wrapper function for the function you're replacing, __wrap_fn_name, with the correct arguments.
 *
 * Inside this function, the call counter will be incremented, each variable defined for an argument will be set to the
 * argument's value, and the return value variable will be returned.
 *
 * The FOR_EACH_ARG argument to the macro must itself be a macro which takes a prefix and two other macros,
 * which you should use to introduce each argument and the last argument. The individual argument macros should be
 * passed the prefix, the type of the C argument, and its name. For example:
 *
 * #define UP_BUFFER_ARGS(prefix, ITEM, LAST_ITEM) \
 *   ITEM(prefix, unsigned, BufferIndex) \
 *   ITEM(prefix, const char *, sName) \
 *   ITEM(prefix, void *, pBuffer) \
 *   ITEM(prefix, unsigned, BufferSize) \
 *   LAST_ITEM(prefix, unsigned, Flags)
 *
 * @param   fn_name     The function name
 * @param   ret_type    The return type
 * @param   FOR_EACH_ARG    See the description above.
 */
#define REPLACEMENT_FN_WITH_ARGS(fn_name, ret_type, FOR_EACH_ARG) \
    FOR_EACH_ARG(fn_name, TYPE_PREFIX_AND_NAME, TYPE_PREFIX_AND_NAME) \
    unsigned fn_name ## _cc; \
    ret_type fn_name ## _ret; \
    extern "C" ret_type __wrap_ ## fn_name ( \
            FOR_EACH_ARG(fn_name, TYPE_AND_NAME_COMMA, TYPE_AND_NAME) \
            ); \
    \
    ret_type __wrap_ ## fn_name ( \
            FOR_EACH_ARG(fn_name, TYPE_AND_NAME_COMMA, TYPE_AND_NAME) \
            ) \
    { \
        fn_name ## _cc ++; \
        FOR_EACH_ARG(fn_name, PREFIX_NAME_EQUALS_NAME, PREFIX_NAME_EQUALS_NAME) \
        if (0)  /* This is not executed, it's only here for type checking against the real function */ \
        { \
            fn_name ## _ret = fn_name ( \
            FOR_EACH_ARG(fn_name, NAME_AND_COMMA, NAME) \
                    ); \
        } \
        return fn_name ## _ret; \
    }

/** Define a replacement function which doesn't return anything.
 *
 * This otherwise works like REPLACEMENT_FN_WITH_ARGS, above.
 */
#define VOID_REPLACEMENT_FN_WITH_ARGS(fn_name, FOR_EACH_ARG) \
    FOR_EACH_ARG(fn_name, TYPE_PREFIX_AND_NAME, TYPE_PREFIX_AND_NAME) \
    unsigned fn_name ## _cc; \
    extern "C" void __wrap_ ## fn_name ( \
            FOR_EACH_ARG(fn_name, TYPE_AND_NAME_COMMA, TYPE_AND_NAME) \
            ); \
    \
    void __wrap_ ## fn_name ( \
            FOR_EACH_ARG(fn_name, TYPE_AND_NAME_COMMA, TYPE_AND_NAME) \
            ) \
    { \
        fn_name ## _cc ++; \
        FOR_EACH_ARG(fn_name, PREFIX_NAME_EQUALS_NAME, PREFIX_NAME_EQUALS_NAME) \
        if (0)  /* This is not executed, it's only here for type checking against the real function */ \
        { \
            fn_name ( \
            FOR_EACH_ARG(fn_name, NAME_AND_COMMA, NAME) \
                    ); \
        } \
    }

/** Define a replacement function which has no arguments.
 *
 * This otherwise works like REPLACEMENT_FN_WITH_ARGS, above, but you no longer need the FOR_EACH_ARG macro.
 */
#define REPLACEMENT_FN_WITHOUT_ARGS(fn_name, ret_type) \
    unsigned fn_name ## _cc; \
    ret_type fn_name ## _ret; \
    extern "C" ret_type __wrap_ ## fn_name (void); \
    \
    ret_type __wrap_ ## fn_name (void) \
    { \
        fn_name ## _cc ++; \
        if (0)  /* This is not executed, it's only here for type checking against the real function */ \
        { \
            fn_name ## _ret = fn_name (); \
        } \
        return fn_name ## _ret; \
    }

/** Define a replacement function which returns nothing and has no arguments.
 *
 * This otherwise works like REPLACEMENT_FN_WITH_ARGS, above, but you no longer
 * need the FOR_EACH_ARG macro or the return type.
 */
#define VOID_REPLACEMENT_FN_WITHOUT_ARGS(fn_name) \
    unsigned fn_name ## _cc; \
    extern "C" void __wrap_ ## fn_name (void) \
    \
    void __wrap_ ## fn_name (void) \
    { \
        fn_name ## _cc ++; \
        if (0)  /* This is not executed, it's only here for type checking against the real function */ \
        { \
            fn_name ## _ret = fn_name (); \
        } \
    }



#endif // UNIT_TEST

/** @} end of group COMMON_TYPES */

#endif
