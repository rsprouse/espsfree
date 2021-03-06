/*
  This material contains proprietary software of Entropic Speech, Inc.   
  Any reproduction, distribution, or publication without the prior	   
  written permission of Entropic Speech, Inc. is strictly prohibited.
  Any public distribution of copies of this work authorized in writing by
  Entropic Speech, Inc. must bear the notice			
 								
      "Copyright (c) 1989 Entropic Speech, Inc.; All rights reserved"
 				
  This module provides the machine independent i/o routines.  This
  version can read and write files in the format for the Sun 386i,
  the DEC Station 3100, for all other Suns, Masscomp, HP, and 
  Convex with IEEE floating point.
 	
  Some changes will be needed to handle VAX floating point.


  Alan Parker, ESI, May 1989.

*/

static char *sccs_id = "@(#)miio.c	1.19 11/25/96	ERL";



#include <stdio.h>
/* RLS: Get rid of 'incompatible implicit declaration' warnings. */
#include <stdlib.h>
/* End of additions */
#include <espsfree/esps.h>

static union {
	double d_val;
#ifndef DEC_ALPHA
	long i_val[2];
#else
	int i_val[2];
#endif
	char byte[8];
       } u1;

static union {
	float f_val;
#ifndef DEC_ALPHA
	long l_val;
#else
	int l_val;
#endif
	char byte[4];
       } u2;

static union {
	short s_val;
	char byte[2];
       } u3;


static void
miio_input_error(s)
char *s;
{
	Fprintf(stderr,
	 "miio_get_%s: not enough bytes to make up the requested data type.\n",
	 s);
	Fprintf(stderr,
	 "miio_get_%s: something is very wrong with your data file.\n",s);
	exit(1);
}


/* this function returns 1 for those machines that by default produce 
   ESPS standard format files
*/
int
edr_default(mach)
int mach;
{
	if (mach == MASSCOMP_CODE || mach == SUN3_CODE || mach == SUN4_CODE ||
	    mach == CONVEX_CODE || mach == HP300_CODE || mach == MACII_CODE ||
	    mach == SG_CODE || mach == HP800_CODE || mach == SONY_RISC_CODE || 
	    mach == SONY_68K_CODE || mach == APOLLO_68K_CODE ||
	    mach == STARDENT_3000_CODE || mach == IBM_RS6000_CODE ||
	    mach == HP700_CODE || mach == HP400_CODE) 
		return 1;
	else
		return 0;
}

/* this section is used by these machines only;  they do not require
conversions, but can detect Sun 386i, DS3100, or DEC_ALPHA code and handle it
*/

#if defined(M5500) || defined(M5600) || defined(SUN3) || defined(SUN4) || defined(HP300) || defined(CONVEX) || defined(MACII) || defined(SG) || defined(HP800) || defined(SONY) || defined(APOLLO_68K) || defined(STARDENT_3000) || defined(IBM_RS6000) || defined(HP400) || defined(HP700)

/* this section is defined for those machines that do EDR by default */


int
miio_get_double(ptr, n, flag, mach, fp)
double *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count = 0;		/* count of items read */

/* 
 check arguments
*/
	spsassert(ptr, "miio_get_double: ptr is NULL");	
	spsassert(fp,  "miio_get_double: fp is NULL");
	spsassert(n >= 0, "miio_get_double: n not > 0");
	spsassert(flag == NO || flag == YES, "miio_get_double: bad flag");

	if (n == 0) return(0);

	if (flag == YES || edr_default(mach))  
/* 
 simple, just use fread since this machine is EDR by default 
*/
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
	else if (mach == SUN386i_CODE || mach == DS3100_CODE || 
	         mach == DEC_ALPHA_CODE || mach == LINUX_OR_MAC_CODE) { 		
/* 
 translate from 386i, DS3100, LINUX_OR_MAC or ALPHA native format 
*/
	    while (n--) {
		if (fread(&u1.byte[7], 1, 1, fp) != 1) 
		  break;
		if (fread(&u1.byte[6], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[5], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[4], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[3], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[2], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[1], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[0], 1, 1, fp) != 1)
		  miio_input_error("double");
		*ptr++ = u1.d_val;
		item_count++;
	     }
	    return item_count;
	}
	else {
	    Fprintf(stderr,
	     "ESPS file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}


int
miio_get_float(ptr, n, flag, mach, fp)
float *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count=0;	/* count of items read */
/* 
 check arguments
*/
	spsassert(ptr, "miio_get_float: ptr is NULL");	
	spsassert(fp,  "miio_get_float: fp is NULL");
	spsassert(n >= 0, "miio_get_float: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_float: bad flag");

	if (n == 0) return(0);

	if (flag == YES || edr_default(mach))  
/* 
 simple, just use fread since this machine is EDR by default 
*/
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
	else if (mach == SUN386i_CODE || mach == DS3100_CODE || 
	         mach == DEC_ALPHA_CODE || mach == LINUX_OR_MAC_CODE) { 		
/* 
 translate from 386i, DS3100, or ALPHA native format 
*/
	   while (n--) {
		if (fread(&u2.byte[3], 1, 1, fp) != 1)
		  break;
		if (fread(&u2.byte[2], 1, 1, fp) != 1)
		  miio_input_error("float");
		if (fread(&u2.byte[1], 1, 1, fp) != 1)
		  miio_input_error("float");
		if (fread(&u2.byte[0], 1, 1, fp) != 1)
		  miio_input_error("float");
		*ptr++ = u2.f_val;
		item_count++;
	   }
	  return item_count;
	}
	else {
	    Fprintf(stderr,
	     "ESPS file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}

int
miio_get_long(ptr, n, flag, mach, fp)
long *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count=0;	/* count of items read */

	spsassert(ptr, "miio_get_long: ptr is NULL");	
	spsassert(fp,  "miio_get_long: fp is NULL");
	spsassert(n >= 0, "miio_get_long: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_long: bad flag");

	if (n == 0) return(0);

	if (flag == YES || edr_default(mach))  
/* 
 simple, just use fread since this machine is EDR by default 
*/
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
	else if (mach == SUN386i_CODE || mach == DS3100_CODE || 
		 mach == LINUX_OR_MAC_CODE) { 		
/* 
 translate from 386i, DS3100,  native format 
*/
	  while (n--) {
		if (fread(&u2.byte[3], 1, 1, fp) != 1)
		  break;
		if (fread(&u2.byte[2], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[1], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[0], 1, 1, fp) != 1)
		  miio_input_error("long");
		*ptr++ = u2.l_val;
		item_count++;
	  }
	  return item_count;
	}
/* 
 translate a file from DEC ALPHA native format
*/
        else if (mach == DEC_ALPHA_CODE) {
	  while (n--) {
                char dummy[4];
		if (fread(&u2.byte[3], 1, 1, fp) != 1)
		  break;
		if (fread(&u2.byte[2], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[1], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[0], 1, 1, fp) != 1)
		  miio_input_error("long");
		*ptr++ = u2.l_val;
/* just discard the extra four bytes */
		if (fread(dummy, 1, 4, fp) != 4)
		  miio_input_error("long");
		item_count++;
	  }
	  return item_count;
        }
	else {
	    Fprintf(stderr,
	     "ESPS file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}

int
miio_get_short(ptr, n, flag, mach, fp)
short *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count=0;	/* count of items read */


	spsassert(ptr, "miio_get_short: ptr is NULL");	
	spsassert(fp,  "miio_get_short: fp is NULL");
	spsassert(n >= 0, "miio_get_short: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_short: bad flag");

	if (n == 0) return(0);

	if (flag == YES || edr_default(mach)) {
/* 
 simple, just use fread since this machine is EDR by default 
*/
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
	} else if (mach == SUN386i_CODE || mach == DS3100_CODE || 
	         mach == DEC_ALPHA_CODE || mach == LINUX_OR_MAC_CODE) { 		
/* 
 translate from 386i, DS3100, or ALPHA native format 
*/
	  while (n--) {
		if (fread(&u3.byte[1], 1, 1, fp) != 1)
		  break;
		if (fread(&u3.byte[0], 1, 1, fp) != 1)
		  miio_input_error("short");
		*ptr++ = u3.s_val;
		item_count++;
	  }
	  return item_count;
	}
	else {
	    Fprintf(stderr,
	     "ESPS file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}

int
miio_get_int(ptr, n, flag, mach, fp)
int *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count=0;

	spsassert(ptr, "miio_get_int: ptr is NULL");	
	spsassert(fp,  "miio_get_int: fp is NULL");
	spsassert(n >= 0, "miio_get_int: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_int: bad flag");

	if (n == 0) return(0);

	if (flag == YES || edr_default(mach))  
/* 
 simple, just use fread since this machine is EDR by default 
*/
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
	else if (mach == SUN386i_CODE || mach == DS3100_CODE || 
	         mach == DEC_ALPHA_CODE || mach == LINUX_OR_MAC_CODE) { 		
/* 
 translate from 386i, DS3100, or ALPHA native format 
*/
	   while (n--) {
		if (fread(&u2.byte[3], 1, 1, fp) != 1)
		  break;
		if (fread(&u2.byte[2], 1, 1, fp) != 1)
		  miio_input_error("int");
		if (fread(&u2.byte[1], 1, 1, fp) != 1)
		  miio_input_error("int");
		if (fread(&u2.byte[0], 1, 1, fp) != 1)
		  miio_input_error("int");
		*ptr++ = u2.l_val;
		item_count++;
	   }
	  return item_count;
	}
	else {
	    Fprintf(stderr,
	     "ESPS file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}

int
miio_get_char(ptr, n, flag, mach, fp)
char *ptr;
int n;
int flag;
int mach;
FILE *fp;

{

	spsassert(ptr, "miio_get_char: ptr is NULL");	
	spsassert(fp,  "miio_get_char: fp is NULL");
	spsassert(n >= 0, "miio_get_char: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_char: bad flag");

	if (n == 0) return(0);
	return (fread((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_get_byte(ptr, n, flag, mach, fp)
char *ptr;
int n;
int flag;
int mach;
FILE *fp;

{

	spsassert(ptr, "miio_get_byte: ptr is NULL");	
	spsassert(fp,  "miio_get_byte: fp is NULL");
	spsassert(n >= 0, "miio_get_byte: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_byte: bad flag");

	if (n == 0) return(0);
	return (fread((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_put_double(ptr, n, flag, fp)
double *ptr;
int n;
int flag;
FILE *fp;

{
	spsassert(ptr, "miio_put_double: ptr is NULL");	
	spsassert(fp,  "miio_put_double: fp is NULL");
	spsassert(n >= 0, "miio_put_double: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_double: bad flag");

	if (n == 0) return(0);
	return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_put_float(ptr, n, flag, fp)
float *ptr;
int n;
int flag;
FILE *fp;

{
	spsassert(ptr, "miio_put_float: ptr is NULL");	
	spsassert(fp,  "miio_put_float: fp is NULL");
	spsassert(n >= 0, "miio_put_float: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_float: bad flag");

	if (n == 0) return(0);
	return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
}


int
miio_put_int(ptr, n, flag, fp)
int *ptr;
int n;
int flag;
FILE *fp;

{
	spsassert(ptr, "miio_put_int: ptr is NULL");	
	spsassert(fp,  "miio_put_int: fp is NULL");
	spsassert(n >= 0, "miio_put_int: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_int: bad flag");

	if (n == 0) return(0);
	return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_put_long(ptr, n, flag, fp)
long *ptr;
int n;
int flag;
FILE *fp;

{
	spsassert(ptr, "miio_put_long: ptr is NULL");	
	spsassert(fp,  "miio_put_long: fp is NULL");
	spsassert(n >= 0, "miio_put_long: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_long: bad flag");

	if (n == 0) return(0);
	return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_put_short(ptr, n, flag, fp)
short *ptr;
int n;
int flag;
FILE *fp;

{
	spsassert(ptr, "miio_put_short: ptr is NULL");	
	spsassert(fp,  "miio_put_short: fp is NULL");
	spsassert(n >= 0, "miio_put_short: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_short: bad flag");

	if (n == 0) return(0);
	return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_put_char(ptr, n, flag, fp)
char *ptr;
int n;
int flag;
FILE *fp;

{

	spsassert(ptr, "miio_put_char: ptr is NULL");	
	spsassert(fp,  "miio_put_char: fp is NULL");
	spsassert(n >= 0, "miio_put_char: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_char: bad flag");

	if (n == 0) return(0);
	return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_put_byte(ptr, n, flag, fp)
char *ptr;
int n;
int flag;
FILE *fp;

{

	spsassert(ptr, "miio_put_byte: ptr is NULL");	
	spsassert(fp,  "miio_put_byte: fp is NULL");
	spsassert(n >= 0, "miio_put_byte: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_byte: bad flag");

	if (n == 0) return(0);
	return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
}

#endif  /* end of machines that do EDR by default */


/* this section is for Sun386i, DS3100, and DEC_ALPHA machines
*/
#if defined(SUN386i) || defined(DS3100) || defined(DEC_ALPHA) || defined(LINUX_OR_MAC)

int
miio_get_double(ptr, n, flag, mach, fp)
double *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count = 0;		/* count of items read */

	spsassert(ptr, "miio_get_double: ptr is NULL");	
	spsassert(fp,  "miio_get_double: fp is NULL");
	spsassert(n >= 0, "miio_get_double: n not > 0");
	spsassert(flag == NO || flag == YES, "miio_get_double: bad flag");

	if (n == 0) return(0);
	if (flag == NO && (mach == SUN386i_CODE || mach == DS3100_CODE || mach == DEC_ALPHA_CODE || mach == LINUX_OR_MAC_CODE))
	/* no need to translate */
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
	else if (flag == YES || edr_default(mach)) { 		
/* translate from EDR */
	 while (n--) {
		if (fread(&u1.byte[7], 1, 1, fp) != 1) 
		  break;
		if (fread(&u1.byte[6], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[5], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[4], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[3], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[2], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[1], 1, 1, fp) != 1)
		  miio_input_error("double");
		if (fread(&u1.byte[0], 1, 1, fp) != 1)
		  miio_input_error("double");
		*ptr++ = u1.d_val;
		item_count++;
	  }
	 return item_count;
	}
	else {
	    Fprintf(stderr,
	     "ESPS (double) file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}


int
miio_get_float(ptr, n, flag, mach, fp)
float *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count=0;	/* count of items read */

	spsassert(ptr, "miio_get_float: ptr is NULL");	
	spsassert(fp,  "miio_get_float: fp is NULL");
	spsassert(n >= 0, "miio_get_float: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_float: bad flag");

	if (n == 0) return(0);
	if (flag == NO && (mach == SUN386i_CODE || mach == DS3100_CODE || mach == DEC_ALPHA_CODE || mach == LINUX_OR_MAC_CODE))
	/* no need to translate */
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
	else if (flag == YES || edr_default(mach)) { 		
	   while (n--) {
		if (fread(&u2.byte[3], 1, 1, fp) != 1)
		  break;
		if (fread(&u2.byte[2], 1, 1, fp) != 1)
		  miio_input_error("float");
		if (fread(&u2.byte[1], 1, 1, fp) != 1)
		  miio_input_error("float");
		if (fread(&u2.byte[0], 1, 1, fp) != 1)
		  miio_input_error("float");
		*ptr++ = u2.f_val;
		item_count++;
	   }
	  return item_count;
	}
	else {
	    Fprintf(stderr,
	     "ESPS (float) file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}
#ifdef DEC_ALPHA
int
miio_get_long(ptr, n, flag, mach, fp)
long *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count=0;	/* count of items read */

	spsassert(ptr, "miio_get_long: ptr is NULL");	
	spsassert(fp,  "miio_get_long: fp is NULL");
	spsassert(n >= 0, "miio_get_long: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_long: bad flag");

	if (n == 0) return(0);
	if (flag == NO && (mach == DEC_ALPHA_CODE))
	/* no need to translate */
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
	else if (flag == YES || edr_default(mach)) { 		
	  while (n--) {
		if (fread(&u2.byte[3], 1, 1, fp) != 1)
		  break;
		if (fread(&u2.byte[2], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[1], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[0], 1, 1, fp) != 1)
		  miio_input_error("long");
		*ptr++ = u2.l_val;
		item_count++;
	  }
	  return item_count;
	}
	else if (flag == NO && ((mach == DS3100_CODE) || (mach == LINUX_OR_MAC_CODE))){
	  int i_reg;
	  while (n--) {
		if (fread(&i_reg, 1, 4, fp) != 4)
		  break;
		*ptr++ = i_reg;
		item_count++;
	  }
	  return item_count;
	}
	else {
	    Fprintf(stderr,
	     "ESPS (long) file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}

#else
int
miio_get_long(ptr, n, flag, mach, fp)
long *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count=0;	/* count of items read */

	spsassert(ptr, "miio_get_long: ptr is NULL");	
	spsassert(fp,  "miio_get_long: fp is NULL");
	spsassert(n >= 0, "miio_get_long: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_long: bad flag");

	if (n == 0) return(0);
	if (flag == NO && (mach == SUN386i_CODE || mach == DS3100_CODE || mach == LINUX_OR_MAC_CODE))
	/* no need to translate */
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
/* 
 translate a file from DEC ALPHA native format
*/
        else if (flag == NO && (mach == DEC_ALPHA_CODE)) {
	  while (n--) {
                char dummy[4];
		if (fread(&u2.byte[0], 1, 1, fp) != 1)
		  break;
		if (fread(&u2.byte[1], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[2], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[3], 1, 1, fp) != 1)
		  miio_input_error("long");
		*ptr++ = u2.l_val;
/* just discard the extra four bytes */
		if (fread(dummy, 1, 4, fp) != 4)
		  miio_input_error("long");
		item_count++;
	  }
          return item_count;
        }
	else if (flag == YES || edr_default(mach)) { 		
	  while (n--) {
		if (fread(&u2.byte[3], 1, 1, fp) != 1)
		  break;
		if (fread(&u2.byte[2], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[1], 1, 1, fp) != 1)
		  miio_input_error("long");
		if (fread(&u2.byte[0], 1, 1, fp) != 1)
		  miio_input_error("long");
		*ptr++ = u2.l_val;
		item_count++;
	  }
	  return item_count;
	}
	else {
	    Fprintf(stderr,
	     "ESPS (long) file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}
#endif DEC_ALPHA

int
miio_get_short(ptr, n, flag, mach, fp)
short *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
  int item_count=0;	/* count of items read */

  spsassert(ptr, "miio_get_short: ptr is NULL");	
  spsassert(fp,  "miio_get_short: fp is NULL");
  spsassert(n >= 0, "miio_get_short: n not > 0");
  spsassert(flag == 0 || flag == 1, "miio_get_short: bad flag");

  if (n == 0) return(0);
  if (flag == NO && (mach == SUN386i_CODE || mach == DS3100_CODE ||
		     mach == DEC_ALPHA_CODE || mach == LINUX_OR_MAC_CODE)) {

    /* no need to translate */
    return(fread((char *)ptr, sizeof(*ptr), n, fp));
  } else if (flag == YES || edr_default(mach)) { 		
    while (n--) {
      if (fread(&u3.byte[1], 1, 1, fp) != 1)
	break;
      if (fread(&u3.byte[0], 1, 1, fp) != 1)
	miio_input_error("short");
      *ptr++ = u3.s_val;
      item_count++;
    }
    return item_count;
  }
  else {
    Fprintf(stderr,
	    "ESPS (short) file input routine: this file was written on a %s ",
	    machine_codes[mach]);
    Fprintf(stderr, "and cannot be read on this machine.\n");
    exit(1);
  }
}

int
miio_get_int(ptr, n, flag, mach, fp)
int *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count=0;

	spsassert(ptr, "miio_get_int: ptr is NULL");	
	spsassert(fp,  "miio_get_int: fp is NULL");
	spsassert(n >= 0, "miio_get_int: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_int: bad flag");

	if (n == 0) return(0);
	if (flag == NO && (mach == SUN386i_CODE || mach == DS3100_CODE || mach == DEC_ALPHA_CODE || mach == LINUX_OR_MAC_CODE))
	/* no need to translate */
		return (fread((char *)ptr, sizeof(*ptr), n, fp));
	else if (flag == YES || edr_default(mach)) { 		
	   while (n--) {
		if (fread(&u2.byte[3], 1, 1, fp) != 1)
		  break;
		if (fread(&u2.byte[2], 1, 1, fp) != 1)
		  miio_input_error("int");
		if (fread(&u2.byte[1], 1, 1, fp) != 1)
		  miio_input_error("int");
		if (fread(&u2.byte[0], 1, 1, fp) != 1)
		  miio_input_error("int");
		*ptr++ = u2.l_val;
		item_count++;
	   }
	  return item_count;
	}
	else {
	    Fprintf(stderr,
	     "ESPS (int) file input routine: this file was written on a %s ",
	     machine_codes[mach]);
	    Fprintf(stderr, "and cannot be read on this machine.\n");
	    exit(1);
	}
}

int
miio_get_char(ptr, n, flag, mach, fp)
char *ptr;
int n;
int flag;
int mach;
FILE *fp;

{

	spsassert(ptr, "miio_get_char: ptr is NULL");	
	spsassert(fp,  "miio_get_char: fp is NULL");
	spsassert(n >= 0, "miio_get_char: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_char: bad flag");

	if (n == 0) return(0);
	return (fread((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_get_byte(ptr, n, flag, mach, fp)
char *ptr;
int n;
int flag;
int mach;
FILE *fp;

{

	spsassert(ptr, "miio_get_byte: ptr is NULL");	
	spsassert(fp,  "miio_get_byte: fp is NULL");
	spsassert(n >= 0, "miio_get_byte: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_get_byte: bad flag");

	if (n == 0) return(0);
	return (fread((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_put_double(ptr, n, flag, fp)
double *ptr;
int n;
int flag;
FILE *fp;

{
	int i=n;

	spsassert(ptr, "miio_put_double: ptr is NULL");	
	spsassert(fp,  "miio_put_double: fp is NULL");
	spsassert(n >= 0, "miio_put_double: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_double: bad flag");

	if (n == 0) return(0);
	if (flag == NO)	/* no need to translate */
		return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
	else { 		/* translate from EDR */
	 while (n--) {
		u1.d_val = *ptr++;
		if (fwrite(&u1.byte[7], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u1.byte[6], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u1.byte[5], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u1.byte[4], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u1.byte[3], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u1.byte[2], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u1.byte[1], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u1.byte[0], 1, 1, fp) != 1)
		  return 0;
	  }
	 return i;
	}
}

int
miio_put_float(ptr, n, flag, fp)
float *ptr;
int n;
int flag;
FILE *fp;

{
	int i=n;

	spsassert(ptr, "miio_put_float: ptr is NULL");	
	spsassert(fp,  "miio_put_float: fp is NULL");
	spsassert(n >= 0, "miio_put_float: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_float: bad flag");

	if (n == 0) return(0);
	if (flag == NO)	/* no need to translate */
		return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
	else { 		/* translate from EDR */
	 while (n--) {
		u2.f_val = *ptr++;
		if (fwrite(&u2.byte[3], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u2.byte[2], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u2.byte[1], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u2.byte[0], 1, 1, fp) != 1)
		  return 0;
	  }
	 return i;
	}
}


int
miio_put_int(ptr, n, flag, fp)
int *ptr;
int n;
int flag;
FILE *fp;

{
	int i=n;

	spsassert(ptr, "miio_put_int: ptr is NULL");	
	spsassert(fp,  "miio_put_int: fp is NULL");
	spsassert(n >= 0, "miio_put_int: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_int: bad flag");

	if (n == 0) return(0);
	if (flag == NO)	/* no need to translate */
		return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
	else { 		/* translate from EDR */
	 while (n--) {
		u2.l_val = *ptr++;
		if (fwrite(&u2.byte[3], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u2.byte[2], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u2.byte[1], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u2.byte[0], 1, 1, fp) != 1)
		  return 0;
	  }
	 return i;
	}
}

int
miio_put_long(ptr, n, flag, fp)
long *ptr;
int n;
int flag;
FILE *fp;

{
	int i=n;
	spsassert(ptr, "miio_put_long: ptr is NULL");	
	spsassert(fp,  "miio_put_long: fp is NULL");
	spsassert(n >= 0, "miio_put_long: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_long: bad flag");

	if (n == 0) return(0);
	if (flag == NO)	/* no need to translate */
		return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
	else { 		/* translate from EDR */
	 while (n--) {
		u2.l_val = *ptr++;
		if (fwrite(&u2.byte[3], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u2.byte[2], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u2.byte[1], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u2.byte[0], 1, 1, fp) != 1)
		  return 0;
	  }
	 return i;
	}
}

int
miio_put_short(ptr, n, flag, fp)
short *ptr;
int n;
int flag;
FILE *fp;

{
	int i=n;

	spsassert(ptr, "miio_put_short: ptr is NULL");	
	spsassert(fp,  "miio_put_short: fp is NULL");
	spsassert(n >= 0, "miio_put_short: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_short: bad flag");

	if (n == 0) return(0);
	if (flag == NO)	/* no need to translate */
		return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
	else { 		/* translate from EDR */
	 while (n--) {
		u3.s_val = *ptr++;
		if (fwrite(&u3.byte[1], 1, 1, fp) != 1)
		  return 0;
		if (fwrite(&u3.byte[0], 1, 1, fp) != 1)
		  return 0;
	  }
	 return i;
	}
}

int
miio_put_char(ptr, n, flag, fp)
char *ptr;
int n;
int flag;
FILE *fp;

{

	spsassert(ptr, "miio_put_char: ptr is NULL");	
	spsassert(fp,  "miio_put_char: fp is NULL");
	spsassert(n >= 0, "miio_put_char: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_char: bad flag");

	if (n == 0) return(0);
	return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
}

int
miio_put_byte(ptr, n, flag, fp)
char *ptr;
int n;
int flag;
FILE *fp;

{

	spsassert(ptr, "miio_put_byte: ptr is NULL");	
	spsassert(fp,  "miio_put_byte: fp is NULL");
	spsassert(n >= 0, "miio_put_byte: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_byte: bad flag");

	if (n == 0) return(0);
	return (fwrite((char *)ptr, sizeof(*ptr), n, fp));
}

#endif

int 
miio_get_dcplx(ptr, n, flag, mach, fp)
double_cplx *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count = 0;
	spsassert(ptr, "miio_get_dcplx: ptr is NULL");
	spsassert(fp,  "miio_get_dcplx: fp is NULL");
	spsassert(n >= 0, "miio_get_dcplx: n not > 0");
	spsassert(flag == NO || flag == YES, "miio_get_dcplx: bad flag");


	if (n == 0) return 0;

	while (n--) {
		if (miio_get_double(&ptr->real, 1, flag, mach, fp) != 1)
			break;
		if (miio_get_double(&ptr->imag, 1, flag, mach, fp) != 1)
			miio_input_error("dcplx");
		ptr++;
		item_count++;
	}
	return item_count;
}

int 
miio_get_fcplx(ptr, n, flag, mach, fp)
float_cplx *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count = 0;
	spsassert(ptr, "miio_get_fcplx: ptr is NULL");
	spsassert(fp,  "miio_get_fcplx: fp is NULL");
	spsassert(n >= 0, "miio_get_fcplx: n not > 0");
	spsassert(flag == NO || flag == YES, "miio_get_fcplx: bad flag");


	if (n == 0) return 0;

	while (n--) {
		if (miio_get_float(&ptr->real, 1, flag, mach, fp) != 1)
			break;
		if (miio_get_float(&ptr->imag, 1, flag, mach, fp) != 1)
			miio_input_error("fcplx");
		ptr++;
		item_count++;
	}
	return item_count;
}

int 
miio_get_lcplx(ptr, n, flag, mach, fp)
long_cplx *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count = 0;
	spsassert(ptr, "miio_get_lcplx: ptr is NULL");
	spsassert(fp,  "miio_get_lcplx: fp is NULL");
	spsassert(n >= 0, "miio_get_lcplx: n not > 0");
	spsassert(flag == NO || flag == YES, "miio_get_lcplx: bad flag");


	if (n == 0) return 0;

	while (n--) {
		if (miio_get_long(&ptr->real, 1, flag, mach, fp) != 1)
			break;
		if (miio_get_long(&ptr->imag, 1, flag, mach, fp) != 1)
			miio_input_error("lcplx");
		ptr++;
		item_count++;
	}
	return item_count;
}

int 
miio_get_scplx(ptr, n, flag, mach, fp)
short_cplx *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count = 0;
	spsassert(ptr, "miio_get_scplx: ptr is NULL");
	spsassert(fp,  "miio_get_scplx: fp is NULL");
	spsassert(n >= 0, "miio_get_scplx: n not > 0");
	spsassert(flag == NO || flag == YES, "miio_get_scplx: bad flag");


	if (n == 0) return 0;

	while (n--) {
		if (miio_get_short(&ptr->real, 1, flag, mach, fp) != 1)
			break;
		if (miio_get_short(&ptr->imag, 1, flag, mach, fp) != 1)
			miio_input_error("scplx");
		ptr++;
		item_count++;
	}
	return item_count;
}

int 
miio_get_bcplx(ptr, n, flag, mach, fp)
byte_cplx *ptr;
int n;
int flag;
int mach;
FILE *fp;

{
	int item_count = 0;
	spsassert(ptr, "miio_get_bcplx: ptr is NULL");
	spsassert(fp,  "miio_get_bcplx: fp is NULL");
	spsassert(n >= 0, "miio_get_bcplx: n not > 0");
	spsassert(flag == NO || flag == YES, "miio_get_bcplx: bad flag");


	if (n == 0) return 0;

	while (n--) {
		if (miio_get_byte(&ptr->real, 1, flag, mach, fp) != 1)
			break;
		if (miio_get_byte(&ptr->imag, 1, flag, mach, fp) != 1)
			miio_input_error("bcplx");
		ptr++;
		item_count++;
	}
	return item_count;
}

int
miio_put_dcplx(ptr, n, flag, fp)
double_cplx *ptr;
int n;
int flag;
FILE *fp;

{

	int i=n;
	
	spsassert(ptr, "miio_put_dcplx: ptr is NULL");
	spsassert(fp, "miio_put_dcplx: fp is NULL");
	spsassert(n >= 0, "miio_put_dcplx: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_dcplx: bad flag");

	if (n == 0) return 0;

	while (n--) {
		if(miio_put_double(&ptr->real, 1, flag, fp) != 1)
			return 0;
		if(miio_put_double(&ptr->imag, 1, flag, fp) != 1)
			return 0;
		ptr++;
	}
	return i;
}


int
miio_put_fcplx(ptr, n, flag, fp)
float_cplx *ptr;
int n;
int flag;
FILE *fp;

{

	int i=n;
	
	spsassert(ptr, "miio_put_fcplx: ptr is NULL");
	spsassert(fp, "miio_put_fcplx: fp is NULL");
	spsassert(n >= 0, "miio_put_fcplx: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_fcplx: bad flag");

	if (n == 0) return 0;

	while (n--) {
		if(miio_put_float(&ptr->real, 1, flag, fp) != 1)
			return 0;
		if(miio_put_float(&ptr->imag, 1, flag, fp) != 1)
			return 0;
		ptr++;
	}
	return i;
}

int
miio_put_lcplx(ptr, n, flag, fp)
long_cplx *ptr;
int n;
int flag;
FILE *fp;

{

	int i=n;
	
	spsassert(ptr, "miio_put_lcplx: ptr is NULL");
	spsassert(fp, "miio_put_lcplx: fp is NULL");
	spsassert(n >= 0, "miio_put_lcplx: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_lcplx: bad flag");

	if (n == 0) return 0;

	while (n--) {
		if(miio_put_long(&ptr->real, 1, flag, fp) != 1)
			return 0;
		if(miio_put_long(&ptr->imag, 1, flag, fp) != 1)
			return 0;
		ptr++;
	}
	return i;
}

int
miio_put_scplx(ptr, n, flag, fp)
short_cplx *ptr;
int n;
int flag;
FILE *fp;

{

	int i=n;
	
	spsassert(ptr, "miio_put_scplx: ptr is NULL");
	spsassert(fp, "miio_put_scplx: fp is NULL");
	spsassert(n >= 0, "miio_put_scplx: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_scplx: bad flag");

	if (n == 0) return 0;

	while (n--) {
		if(miio_put_short(&ptr->real, 1, flag, fp) != 1)
			return 0;
		if(miio_put_short(&ptr->imag, 1, flag, fp) != 1)
			return 0;
		ptr++;
	}
	return i;
}

int
miio_put_bcplx(ptr, n, flag, fp)
byte_cplx *ptr;
int n;
int flag;
FILE *fp;

{

	int i=n;
	
	spsassert(ptr, "miio_put_bcplx: ptr is NULL");
	spsassert(fp, "miio_put_bcplx: fp is NULL");
	spsassert(n >= 0, "miio_put_bcplx: n not > 0");
	spsassert(flag == 0 || flag == 1, "miio_put_bcplx: bad flag");

	if (n == 0) return 0;

	while (n--) {
		if(miio_put_byte(&ptr->real, 1, flag, fp) != 1)
			return 0;
		if(miio_put_byte(&ptr->imag, 1, flag, fp) != 1)
			return 0;
		ptr++;
	}
	return i;
}
