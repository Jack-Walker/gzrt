/*****************************
* Zelda 64 Function Database *
*****************************/
#ifndef __ZFDB_H__

#define ZFDB_VERSION    "v0"

/* Deps */
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <string.h>
#include "sqlite3.h"

/* Data types */
typedef uint32_t    u32;
typedef uint8_t     u8;
typedef int16_t     s16;
typedef const char  cchar;

/* Boolean */
typedef enum { FALSE, TRUE } bool;

/* Shared macros */
#define U32(x)              \
(                           \
    ((u8*)(x))[0] << 24 |   \
    ((u8*)(x))[1] << 16 |   \
    ((u8*)(x))[2] <<  8 |   \
    ((u8*)(x))[3]           \
)

/* Actions */
enum AppAction
{
    ACTION_UNSET,
    ACTION_IMPORT_DUMP,
    ACTION_IMPORT_TEXT,
    ACTION_DUMP_HEADER
};

/* Flags */
enum AppFlags
{
    FLAG_SHOW_DEBUG = (1 << 1)
};

/* The function entry data type */
struct Function
{
    u32     address;
    cchar * name;
    cchar * args;
    cchar * retrn;
    cchar * lib;
    cchar * desc;
};

/* Configuration struct */
struct Config
{
    enum AppAction action;
    int flags;
};

/* No debug? */
#ifdef FINAL
# define kprintf(fmt, ...)
# define dumpQuery(q)
#endif

/* Print a string */
#define MESSAGE(x, ...) { fprintf( stderr, x, ##__VA_ARGS__ ); fflush(stderr); }

extern char *strdup(const char *s);

/*
 *  Global variables
 */
extern struct Config   config;
extern struct timeval  start;
extern sqlite3       * db;
extern char          * dbname;
extern char          * dbtablename;
extern u32             fsize;
extern char          * fname;
extern u8            * fbuff;

/*
 *  Functions - general purpose
 */
extern double timeDiff ( struct timeval * a, struct timeval * b );


/*
 *  Functions - important
 */
extern bool validAddress ( u32 addr );


/*
 *  Functions - application core
 */
extern void showLogo ( void );
extern void quitError ( int code, char * fmt, ... );
extern int  kprintf ( char * fmt, ... );
extern void kdump ( void );
extern int dumpQuery ( char * q );
extern void showUsage ( int argc, char ** argv );


/*
 *  Functions - database
 */
extern int  dbOpen ( void );
extern int  dbClose ( void );
extern void dbCheckOpen ( void );
extern bool dbTableExists ( char * name );
extern int  dbCreateTable ( void );
extern int  dbBeginTransaction ( void );
extern int  dbCommit ( void );
extern int  dbInsertFunction ( u32 address, char * name, char * args, char * ret, char * lib, char * desc );
extern bool dbFunctionExists ( u32 addr );


/*
 *  Functions - control flow
 */
extern void zfdbInit ( void );
extern void zfdbDeinit ( void );


/*
 *  Functions - MIPS interpreter
 */
extern void mips_process_file ( void );

#endif /* __ZFDB_H__ */

