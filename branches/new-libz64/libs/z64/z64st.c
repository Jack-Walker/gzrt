/***********************
* Zelda 64 Scene Table *
***********************/
#include <z64.h>
#include <glib.h>

/* Table identifier - MM */
static const guint8 
table_ident_mm[] =
{
	0xFA, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xDF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};


/* Table terminator - MM */
static const guint8 
table_term_mm[] =
{
    0x12, 0x00, 0x41, 0x02, 0x12, 0x01, 0x41,
	0x02, 0x12, 0x02, 0x41, 0x02
};

/* Table identifier - OoT */
static const guint8 
table_ident_oot[] =
{
	0x57, 0x09, 0x41, 0x83, 0x57, 0x09, 0x41, 0x83,
	0x57, 0x09, 0x41, 0x83, 0x57, 0x09, 0x41, 0x83,
    0x5C, 0x08, 0x41, 0x83, 0x5C, 0x08, 0x41, 0x83,
	0x5C, 0x08, 0x41, 0x83, 0x5C, 0x08, 0x41, 0x83 
};


/* Table terminator - OoT */
static const guint8 
table_term_oot[] =
{
	0xDB, 0x06, 0x00, 0x24
};
