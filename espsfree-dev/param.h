/*
  This material contains proprietary software of Entropic Speech, Inc.   
  Any reproduction, distribution, or publication without the the prior	   
  written permission of Entropic Speech, Inc. is strictly prohibited.
  Any public distribution of copies of this work authorized in writing by
  Entropic Speech, Inc. must bear the notice			
 								
      "Copyright (c) 1987-1990 Entropic Speech, Inc.
       Copyright (c) 1990-1995 Entropic Research Laboratory, Inc.
                     All rights reserved."
 				

  @(#)param.h	1.16 2/20/96 ESI
*/

#ifndef param_H
#define param_H

#ifdef __cplusplus
extern "C" {
#endif

#include <espsfree/esps.h>

/*  This file defines data structures used by the parser and
   symbol table routines. */
struct fnode {
	float f_car;
	struct fnode *f_cdr;
	};
struct inode {
	int i_car;
	struct inode *i_cdr;
	};
struct cnode {
	char *c_car;
	struct cnode *c_cdr;
	};
typedef union {
	int ival;
	char *sval;
#ifdef SUN386i
	float dval;
#else
	double dval;
#endif
	char cval;
	struct fnode *flist;
	struct inode *ilist;
	struct cnode *clist;
	} YYSTYPE;
/* symbol definition */
struct symbol {
	char *s_name;		/* name of symbol */
	YYSTYPE s_value;	/* value of symbol */
	char *s_pstring;	/* prompt string */
	short s_type;		/* type of the symbol */
	char s_prompt;		/* prompt flag. 
				   2 = prompt, 1 = already prompted,
				   0 = non-prompt case */
	char s_used;		/* nonzero if this structure is used */
	char s_com;		/* nonzero if symbol from esps common */
	char **s_choices;	/* list of choices for value */
	int s_nchoices;		/* number of choices */
	float s_min;		/* minimum value */	
	float s_max;		/* maximum value */
	int s_minmax;		/* min/max given */
	int s_sequence;		/* sequence of definition; 1 first */
};
#define ST_UNDEF  0
#define ST_INT    1
#define ST_CHAR   2
#define ST_FLOAT  3
#define ST_STRING 4
#define ST_IARRAY 5
#define ST_FARRAY 6

#define SC_NOCOMMON   1
#define SC_CHECK_FILE 2
#define SPS_COMMON ".espscom"    /* default spscommon file */

/* declare parameter file functions */

int
make_symbol ARGS((char *name, YYSTYPE value, int type, int prompt,
		  char *pstring, int limits, double *MINMAX, char **choices));

int
symtype ARGS((char *name));

int
symsize ARGS((char *name));

char **
symlist ARGS((int *nparams));

int
symdefinite ARGS((char *name));

char **
symchoices ARGS((char *name, int *nchoices));

int
symrange ARGS((char *name, float *min, float *max));

char *
symprompt ARGS((char *name));

char
getsym_c ARGS((char *name));

char
getsymdef_c ARGS((char *name));

char *
getsym_s ARGS((char *name));

char *
getsymdef_s ARGS((char *name));

int
getsym_i ARGS((char *name));

int
getsymdef_i ARGS((char *name));

double
getsym_d ARGS((char *name));

double
getsymdef_d ARGS((char *name));

int
getsym_ia ARGS((char *name, int *arr, int maxval));

int
getsymdef_ia ARGS((char *name, int *arr, int maxval));

int
getsym_da ARGS((char *name, double *arr, int maxval));

int
getsymdef_da ARGS((char *name, double *arr, int maxval));

int
getsym_fa ARGS((char *name, float *arr, int maxval));

int
getsymdef_fa ARGS((char *name, float *arr, int maxval));

int
putsym_s ARGS((char *symbol, char *value));

int
fputsym_s ARGS((char *symbol, char *value, char *file));

int
putsym_i ARGS((char *symbol, int value));

int
fputsym_i ARGS((char *symbol, int value, char *file));

int
putsym_f ARGS((char *symbol, double value));
/* value is specified as float in pre-ANSI style in putsym.c;
 * therefore it is passed as double.
 */

int
fputsym_f ARGS((char *symbol, double value, char *file));
/* value is specified as float in pre-ANSI style in putsym.c;
 * therefore it is passed as double.
 */

int
read_param ARGS((char *param));

int
read_params ARGS((char *param, int flag, char *check_file));

void
init_table ARGS((void));

void
symerr_exit ARGS((void));


#ifdef __cplusplus
}
#endif

#endif /* param_H */
