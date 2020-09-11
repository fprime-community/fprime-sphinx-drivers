/**
 * \file
 * \author Thomas A. Werne <thomas.a.werne@jpl.nasa.gov>
 * \author Josh Schoolcraft <joshua.schoolcraft@jpl.nasa.gov>
 * \brief Error codes
 *
 * \copyright
 * Copyright 2009-2015, by the California Institute of Technology.
 * ALL RIGHTS RESERVED.  United States Government Sponsorship
 * acknowledged.
 ********************************************************************/

#ifndef PROTOS_ERROR_H_
#define PROTOS_ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/

#define GOTO_ON_ERR(label, call)    \
    do {                            \
        err_t _rv = (call);         \
        if (SEOK != _rv) {           \
            goto label;             \
        }                           \
    } while(0)


/******************************************************************************/

#define RET_ON_ERR(call)    \
    do {                    \
        err_t _rv = (call); \
        if (SEOK != _rv) {   \
            return _rv;     \
        }                   \
    } while(0)

/******************************************************************************/

/// Return codes for protos functions
typedef enum{
    SEOK       = 0,      ///< No problems
    SEPERM     = 1,      ///< Operation not permitted
    SENOENT    = 2,      ///< No such file or directory
    SEBADF     = 9,      ///< Bad file number
    SEAGAIN    = 11,     ///< Try again
    SEBUSY     = 16,     ///< Resource is busy
    SENODEV    = 19,     ///< No such device
    SENOTDIR   = 20,     ///< Not a directory
    SEINVAL    = 22,     ///< Invalid parameter
    SENFILE    = 23,     ///< Too many open files
    SENOSPC    = 28,     ///< Out of space
    SEOVERFLOW = 75,     ///< Overflow
    SETIMEDOUT = 110,    ///< Operation timed out
    SEFULL     = 201,    ///< Resource full
    SEMPTY    = 202,    ///< Resource empty
    SDISABLED = 203,    ///< Resource disabled
    SEOTHER    = 255     ///< Generic error
} err_t;
/******************************************************************************/

//char *protos_strerror(int err);
#ifdef __cplusplus
}
#endif

#endif /* ERROR_H_ */

