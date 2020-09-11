/**
 * \file
 * \author Thomas A. Werne <thomas.a.werne@jpl.nasa.gov>
 * \author Josh Schoolcraft <joshua.schoolcraft@jpl.nasa.gov>
 * \brief Utility macros
 *
 * \copyright
 * Copyright 2009-2015, by the California Institute of Technology.
 * ALL RIGHTS RESERVED.  United States Government Sponsorship
 * acknowledged.
 *
 * \defgroup UTILS Miscellaneous Utilities
 * \{
 *  \ingroup OS
 ********************************************************************/

#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "protos_error.h"
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * API variable-like macro definitions
 ******************************************************************************/

/// Byte
#define B 1

/******************************************************************************/

/// Kilobyte
#define KB 1024*(B)

/******************************************************************************/

/// Megabyte
#define MB 1024*(KB)

/*******************************************************************************
 * API function-like macro definitions
 ******************************************************************************/

#define ALIGN(x, a) ((uint32_t)(x) & ~((a) - 1))

/******************************************************************************/

#define STRINGIFY(s) #s
#define S(s) STRINGIFY(s)

/******************************************************************************/

#define SWAB(a, b)      \
    do {                \
        uint8_t _c = b; \
        b = a;          \
        a = _c;         \
    } while(0)

/******************************************************************************/

/**
 * \brief Return the address of the last element of an array.
 *
 * This macro is useful for looping over compile-time defined arrays.
 *
 * \note Parameter must not have side effects.
 *
 * \param[in] array is compile-time array.
 *
 * \returns the address of the last array element.
 */
#define ARRAY_END(array) ((array) + ARRAY_LENGTH(array))

/******************************************************************************/

/**
 * \brief Return the length of an array
 *
 * \note Parameters must not have side effects.
 *
 * \param[in] array is an array.
 *
 * \returns the length of the array
 */
#define ARRAY_LENGTH(array) (sizeof(array)/sizeof(*array))

/******************************************************************************/

/**
 * \brief Macro to multiply a value by a constant
 *
 * Basically, a manually unrolled shift+add routine.  The optimizer should clean
 * it.
 *
 * \param[in] v is a variable
 * \param[in] c is a constant
 *
 * \note Both parameters are used multiple times, so neither should have side
 * effects.
 *
 * \returns (v*c)
 */
#define CONST_MULT(v, c)                                \
    ((((c) & (1L << 31)) ? ((v) << 31) : 0) +  \
     (((c) & (1L << 30)) ? ((v) << 30) : 0) +  \
     (((c) & (1L << 29)) ? ((v) << 29) : 0) +  \
     (((c) & (1L << 28)) ? ((v) << 28) : 0) +  \
     (((c) & (1L << 27)) ? ((v) << 27) : 0) +  \
     (((c) & (1L << 26)) ? ((v) << 26) : 0) +  \
     (((c) & (1L << 25)) ? ((v) << 25) : 0) +  \
     (((c) & (1L << 24)) ? ((v) << 24) : 0) +  \
     (((c) & (1L << 23)) ? ((v) << 23) : 0) +  \
     (((c) & (1L << 22)) ? ((v) << 22) : 0) +  \
     (((c) & (1L << 21)) ? ((v) << 21) : 0) +  \
     (((c) & (1L << 20)) ? ((v) << 20) : 0) +  \
     (((c) & (1L << 19)) ? ((v) << 19) : 0) +  \
     (((c) & (1L << 18)) ? ((v) << 18) : 0) +  \
     (((c) & (1L << 17)) ? ((v) << 17) : 0) +  \
     (((c) & (1L << 16)) ? ((v) << 16) : 0) +  \
     (((c) & (1L << 15)) ? ((v) << 15) : 0) +  \
     (((c) & (1L << 14)) ? ((v) << 14) : 0) +  \
     (((c) & (1L << 13)) ? ((v) << 13) : 0) +  \
     (((c) & (1L << 12)) ? ((v) << 12) : 0) +  \
     (((c) & (1L << 11)) ? ((v) << 11) : 0) +  \
     (((c) & (1L << 10)) ? ((v) << 10) : 0) +  \
     (((c) & (1L <<  9)) ? ((v) <<  9) : 0) +  \
     (((c) & (1L <<  8)) ? ((v) <<  8) : 0) +  \
     (((c) & (1L <<  7)) ? ((v) <<  7) : 0) +  \
     (((c) & (1L <<  6)) ? ((v) <<  6) : 0) +  \
     (((c) & (1L <<  5)) ? ((v) <<  5) : 0) +  \
     (((c) & (1L <<  4)) ? ((v) <<  4) : 0) +  \
     (((c) & (1L <<  3)) ? ((v) <<  3) : 0) +  \
     (((c) & (1L <<  2)) ? ((v) <<  2) : 0) +  \
     (((c) & (1L <<  1)) ? ((v) <<  1) : 0) +  \
     (((c) & (1L <<  0)) ? ((v) <<  0) : 0))

/******************************************************************************/

/**
 * \brief A type-agnostic max operation
 *
 * \param[in] x operand 1
 * \param[in] y operand 2
 *
 * \note \p x and \p y are evaluated twice, so do NOT use arguments with side
 * effects
 *
 * \returns \p x if \p x > \p y, else \p y
 */
#ifndef MAX
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

/******************************************************************************/

/**
 * \brief A type-agnostic min operation
 *
 *
 * \param[in] x operand 1
 * \param[in] y operand 2
 *
 * \note \p x and \p y are evaluated twice, so do NOT use arguments with side
 * effects
 *
 * \returns \p x if \p x < \p y, else \p y
 */
#ifndef MIN
#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#endif

/******************************************************************************/

/**
 * \brief Bit-shifting helper
 *
 * \param[in] val is a number to bitmask.
 * \param[in] nbits is the number of bits to keep.
 * \param[in] discard is the number of bits to throw away (on the right).
 * \param[in] posn is the final starting position of the LSB.
 *
 * \return input value as a shifted and masked bitfield.
 */
#define PACK_BITS(val, nbits, discard, posn) \
    ((((((1ULL << (uint8_t)(nbits)) - 1) & (val)) >> (uint8_t)(discard))) << (uint8_t)(posn))

/******************************************************************************/

/**
 * \brief Bit-shifting helper
 *
 * \param[in] val is a number to bitmask.
 * \param[in] nbits is the number of bits to keep.
 * \param[in] start is the starting bit
 * \param[in] posn is the final starting position of the LSB.
 *
 * \return input value as a shifted and masked bitfield.
 */
#define UNPACK_BITS(val, nbits, start, posn) \
    ((((1ULL << (uint8_t)(nbits)) - 1) & ((val) >> (uint8_t)(start))) << (uint8_t)(posn))

/******************************************************************************/

#define MULT(dest, op1, op2)                        \
    do {                                            \
        typeof(op1) _op1 = op1;                     \
        typeof(op2) _op2 = op2;                     \
        dest = 0;                                   \
                                                    \
        for (; _op2 != 0; _op2 >>= 1, _op1 <<= 1) { \
            if (_op2 & 1) {                         \
                dest += _op1;                       \
            }                                       \
        }                                           \
    } while(0)

/******************************************************************************/

#define ATOMIC(code)    \
    do {                \
        enter_crit();   \
        code;           \
        exit_crit();    \
    } while(0)

/******************************************************************************/

/**
 * \brief Our calloc
 *
 * \warning Implemented using a macro, so nmemb and size cannot have side
 * effects
 *
 */
#define protos_calloc(nmemb, size)  \
    protos_memset(protos_malloc((nmemb)*(size)), '\0', (nmemb)*(size))

/******************************************************************************/

/**
 * \brief Simple macro for creating an alias to a variable
 */
#define ALIAS(src, tgt) typeof((tgt)) src = (tgt)

/******************************************************************************/
/**
 * \brief Simple macro for a warning-less cast from integer to pointer.
 *
 * \note The c430 compiler is very strict about typecasting because of the
 * oddball 24-bit addressing architecture.
 *
 */
#define FORCE_CAST(type, var) *(type *)(&(var))

/******************************************************************************/

// Taken from linux standard headers
#define FIELD_OFFSET(t, f) (uint16_t)&(((t *)0)->f)

/*******************************************************************************
 * API type definitions
 ******************************************************************************/

/*******************************************************************************
 * BSP function declarations
 ******************************************************************************/

/**
 * \name BSP-defined functions
 * \{
 */

/**
 * \brief Check if a pointer points to a readable (non-SFR) location
 *
 * Nominally, this function can be used to ensure that a pointer does not point to
 * NULL. It can also ensure a pointer does not reference memory-mapped registers.
 *
 * \param[in] ptr is the pointer to test.
 *
 * \returns EOK if pointer is in readable memory, EINVAL otherwise.
 *
 * \note TI MSP430F2618 Implementation of check_readable()
 */
err_t check_readable(const void *ptr) ;

/******************************************************************************/

/**
 * \brief Check if a pointer points to a writable location
 *
 * Nominally, this function can be used to ensure that pointers do not point to
 * NULL.  It can also ensure pointers do not reference memory-mapped registers
 * or flash code space.
 *
 * \param[in] ptr is the pointer to test.
 *
 * \returns EOK if pointer is in writable RAM, EINVAL otherwise.
 *
  * \note Implemented by BSP:
 * <ul>
 *   <li>TI MSP430F2618: check_writable_msp430f2618()
 * </ul>
 */
err_t check_writable(const void *ptr);

/******************************************************************************/

/**
 * \brief Clear all the RAM in a system
 */
void wipe_ram(void);

/******************************************************************************/

/** Enter a critical section*/
void enter_crit(void);

/** Exit a critical section*/
void exit_crit(void);

/** Our malloc */
void *protos_malloc(size_t size);

/** Our memset */
void *protos_memset(void *dst, int val, unsigned int len);

/** Our memcpy */
void *protos_memcpy(void *dst, const void *src, size_t size);

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* UTILS_H_ */
/** \} */

