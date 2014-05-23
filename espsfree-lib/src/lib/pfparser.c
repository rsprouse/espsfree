#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 14 "pfparser.y"
/*---------------------------------------------------------------------------+
| pfparser.y - Joseph T. Buck						     |
|              minor modifications by Ajaipal S. Virdy                       |
| This is a YACC parser for parameter files. It calls three external	     |
| functions:								     |
| make_symbol, which creates a new symbol; yylex, the lexical analyzer	     |
| (built by LEX); and yyerror, for error messages.			     |
|									     |
| v1.2: fix lint complaints						     |
| Support for SPS Common file added                                          |
+---------------------------------------------------------------------------*/
static char *sccsid = "%W% %G% ERL";

#include <stdio.h>
#include <esps/param.h>
#include <esps/spsassert.h>
#include <esps/epaths.h>

#define PROMPT 1
#define NOPROMPT 0
#define CVMAX 127
#define CVMIN 0
static YYSTYPE tmpsym;
char msgbuf[80]; /* buffer for error messages */
#define newval(val,type) (tmpsym.type = val, tmpsym)
#define NULL_FNODE ((struct fnode *) 0)
#define NULL_INODE ((struct inode *) 0)
#define NULL_CNODE ((struct cnode *) 0)
#if !defined(IBM_RS6000) && !defined(OS5) && !defined(DEC_ALPHA) && !defined(LINUX_OR_MAC)
#if defined(SG) || defined(hpux) 
int sprintf ();
#else
char *sprintf();
#endif
char *malloc();
#endif
static double *getlimit();
static int setlimit();
static char **choice_list = NULL;
static char **get_choice();
char *savestring();

#line 66 "y.tab.c"
#define INT 257
#define CHR 258
#define STRING 259
#define FLT 260
#define INTVAL 261
#define FLOVAL 262
#define IDENT 263
#define STRVAL 264
#define CHRVAL 265
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    1,    1,    1,    1,    1,    1,    8,    8,
    3,    3,    2,    2,    4,    4,   10,   10,    6,    6,
    6,    5,    5,    5,   11,   11,    7,    7,   12,   12,
   12,   22,   22,   13,   13,   13,   14,   14,   14,    9,
    9,   21,   21,   15,   15,   16,   16,   17,   17,   18,
   18,   19,   19,   20,   20,
};
short yylen[] = {                                         2,
    0,    2,    3,    3,    3,    3,    2,    1,    2,    1,
    1,    3,    1,    3,    1,    3,    1,    3,    5,    5,
    3,    5,    5,    3,    5,    3,    5,    3,    1,    2,
    2,    0,    2,    0,    6,    2,    1,    1,    1,    1,
    1,    1,    1,    3,    3,    1,    3,    3,    3,    1,
    3,    3,    3,    1,    3,
};
short yydefred[] = {                                      0,
    0,    0,    0,   10,    0,    8,    0,    0,    0,    7,
    0,    0,   13,    0,    9,    0,   17,    0,    0,   11,
    2,    0,    0,   15,    0,    0,    0,    4,    0,    0,
    5,    0,    0,    3,    0,    0,    6,    0,   30,   31,
   24,   40,   41,    0,    0,    0,   14,   26,   43,   42,
    0,   18,   21,   38,   37,   39,    0,    0,    0,   12,
   28,    0,   16,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   49,    0,   48,   33,
    0,   22,   23,   25,   45,    0,   44,   19,   20,   27,
   51,    0,    0,   36,   47,    0,    0,    0,    0,    0,
   53,    0,   52,    0,   55,   35,
};
short yydgoto[] = {                                       7,
    8,   12,   19,   23,   13,   20,   24,    9,   65,   16,
   17,   27,   82,   72,   59,   73,   46,   66,   94,   99,
   51,   68,
};
short yysindex[] = {                                    -58,
  -34, -230,  -42,    0, -223,    0,    0,  -58, -220,    0,
  -16,  -37,    0,  -16,    0,  -36,    0,  -16,  -33,    0,
    0,  -16,  -31,    0,  -14,   -8, -111,    0, -230, -224,
    0, -209, -114,    0, -223, -250,    0, -220,    0,    0,
    0,    0,    0, -217,   -3,   -3,    0,    0,    0,    0,
   -3,    0,    0,    0,    0,    0, -227,   -3,   -3,    0,
    0,   -3,    0,  -64,   20,  -60, -198,    9,    9,    9,
  -57,   25,  -54,    9,    9,    9,    0, -241,    0,    0,
  -87,    0,    0,    0,    0, -202,    0,    0,    0,    0,
    0, -202, -237,    0,    0,   29,  -53,   30,  -50, -202,
    0, -188,    0,  -15,    0,    0,
};
short yyrindex[] = {                                     77,
    0,    0,    0,    0,    0,    0,    0,   77,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -121,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -29,  -29,    0,    0,    0,    0,
  -29,    0,    0,    0,    0,    0,    0,  -29,  -29,    0,
    0,  -29,    0,    0,  -46,    0,    0,  -28,  -28,  -28,
    0,  -45,    0,  -28,  -28,  -28,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -44,    0,    0,
    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                     74,
    0,    0,    0,    0,   54,   49,   47,    0,   59,    0,
   55,   28,  -18,  -30,    0,    2,    0,   11,    0,  -12,
    0,  -41,
};
#define YYTABLESIZE 221
short yytable[] = {                                      15,
    6,   29,   58,   92,   69,   61,   29,   32,   57,   70,
   35,   44,   38,   62,   32,   34,   74,   75,   97,   42,
   76,   28,   31,   43,   10,   34,   98,   37,   71,   32,
   34,   48,   11,   54,   55,   93,   49,   56,   64,   18,
   50,   30,   22,   42,   25,   33,   26,   43,   39,   36,
   83,   84,   40,   14,   67,   88,   89,   90,   54,   55,
   77,   96,   56,   78,   79,   80,   81,   85,   86,  104,
   87,  101,  100,  102,  103,   98,    1,  106,   50,   46,
   54,   21,   47,   60,   63,   45,   52,   95,   91,  105,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   29,    0,    0,    0,    0,   29,
   29,   53,   29,   29,   41,    0,   54,   55,    0,   42,
   56,    0,    0,   43,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    1,    2,    3,
    4,    5,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   14,
};
short yycheck[] = {                                      42,
   59,  123,   33,   91,   46,  256,   44,   44,  123,   51,
   44,  123,   44,  264,   44,   44,   58,   59,  256,  261,
   62,   59,   59,  265,   59,   59,  264,   59,  256,   59,
   59,  256,  263,  261,  262,  123,  261,  265,  256,  263,
  265,   14,  263,  261,   61,   18,   63,  265,   63,   22,
   69,   70,   61,  263,   58,   74,   75,   76,  261,  262,
  125,   92,  265,   44,  125,  264,   58,  125,   44,  100,
  125,  125,   44,   44,  125,  264,    0,   93,  125,  125,
  125,    8,   29,   35,   38,   27,   32,   86,   78,  102,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  256,   -1,   -1,   -1,   -1,  261,
  262,  256,  264,  265,  256,   -1,  261,  262,   -1,  261,
  265,   -1,   -1,  265,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  256,  257,  258,
  259,  260,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  263,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 265
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'*'",0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,"'='",0,
"'?'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"INT","CHR","STRING","FLT","INTVAL","FLOVAL","IDENT","STRVAL","CHRVAL",
};
char *yyrule[] = {
"$accept : file",
"file :",
"file : statement file",
"statement : FLT fdlist ';'",
"statement : INT idlist ';'",
"statement : CHR cdlist ';'",
"statement : string sdlist ';'",
"statement : error ';'",
"statement : ';'",
"string : CHR '*'",
"string : STRING",
"fdlist : fdecl",
"fdlist : fdlist ',' fdecl",
"idlist : idecl",
"idlist : idlist ',' idecl",
"sdlist : sdecl",
"sdlist : sdlist ',' sdecl",
"cdlist : cdecl",
"cdlist : cdlist ',' cdecl",
"fdecl : IDENT assop dval prompt limits",
"fdecl : IDENT assop farray prompt limits",
"fdecl : IDENT assop error",
"idecl : IDENT assop ival prompt limits",
"idecl : IDENT assop iarray prompt limits",
"idecl : IDENT assop error",
"cdecl : IDENT assop cval prompt limits",
"cdecl : IDENT assop error",
"sdecl : IDENT assop STRVAL prompt limits",
"sdecl : IDENT assop error",
"assop : '='",
"assop : '=' '?'",
"assop : '?' '='",
"prompt :",
"prompt : ':' STRVAL",
"limits :",
"limits : ':' '[' dval ',' dval ']'",
"limits : ':' carray",
"dval : FLOVAL",
"dval : INTVAL",
"dval : CHRVAL",
"ival : INTVAL",
"ival : CHRVAL",
"cval : CHRVAL",
"cval : INTVAL",
"farray : '{' fvlist '}'",
"farray : '{' error '}'",
"fvlist : dval",
"fvlist : dval ',' fvlist",
"iarray : '{' ivlist '}'",
"iarray : '{' error '}'",
"ivlist : ival",
"ivlist : ival ',' ivlist",
"carray : '{' cvlist '}'",
"carray : '{' error '}'",
"cvlist : STRVAL",
"cvlist : STRVAL ',' cvlist",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 185 "pfparser.y"
/* fcons and icons build up linked lists of values, like Lisp cons. */
static struct fnode *
fcons(v,list)
#ifdef SUN386i
float v;
#else
double v;
#endif
struct fnode *list;
{

    struct fnode *p = (struct fnode *) malloc(sizeof(struct fnode));
    p->f_car = v;
    p->f_cdr = list;
    return p;
}

static struct inode *
icons(v,list)
int v;
struct inode *list;
{

    struct inode *p = (struct inode *) malloc(sizeof(struct inode));
    p->i_car = v;
    p->i_cdr = list;
    return p;
}

static struct cnode *
ccons(v,list)
char *v;
struct cnode *list;
{

    struct cnode *p = (struct cnode *) malloc(sizeof(struct cnode));
    p->c_car = v;
    p->c_cdr = list;
    return p;
}






static bad_decl(name)
char *name;
{
sprintf(msgbuf,"Bad declaration for %s",name);
yyerror(msgbuf);
return 0;
}

/* include the lexical analyzer */
#include "pflexan.c"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

char	*ctime();
char	*getenv();
int	stat();
char	*strcpy(), *getsym_s();

#ifdef XXXX
int	yacc_errors; 
#endif

char	*home;
char	*com;
char	common_file[80];
FILE	*com_fp = NULL;	 /* file pointer to SPS Common file */

/* codes for use between here and lex_open ONLY */

#define FAIL -1
#define NOPARAM -1
#define NOCOMM -2
#define NOBOTH -3

/* globals used by parameter/common stuff */
int Common_on;		/* 1 if common processing is enabled */
int Esps_verbose;	/* Esps verbosity level */
int In_common;

extern int debug_level;

#define DEFAULT_VERBOSITY 2	/* default common verbosity level */
int read_params_called=0;

int
read_params (param, flag, check_file)
char *param;	
int flag;
char *check_file;
{

  /* routine to read and parse a parameter file */

  struct stat	combuf;		/* struct for determining status */
  struct stat	parambuf;	/* struct for determining status */
  char *fp_param = NULL;		/* full path to param file */
  int param_ok=0;
  int did_common=0;
  int status = 0;
  FILE *junk_fp;
  int with_param;	/* non-zero means param != null */

  In_common = 0;
  read_params_called = 1;
  if(getenv("USE_ESPS_COMMON") != NULL && 
     strcmp(getenv("USE_ESPS_COMMON"),"off") == 0)
    Common_on = 0;
  else
    Common_on = 1;

  if(getenv("ESPS_VERBOSE") != NULL) 
    Esps_verbose = atoi(getenv("ESPS_VERBOSE"));
  else
    Esps_verbose = DEFAULT_VERBOSITY;	/* default verbosity level */

  if(Common_on) {
    if((com = getenv("ESPSCOM")) == NULL) {
      if((home = getenv("HOME")) == NULL)
	home = ".";
      (void) strcpy(common_file,home);
      (void) strcat(common_file,"/");
      (void) strcat(common_file,SPS_COMMON);
    }
    else
      (void) strcpy(common_file,com);
  }

  if (param == NULL) {
    with_param = 0;
    /*    param = savestring("params");  */
  }  else
    with_param = 1;

  if(param)
    fp_param = FIND_ESPS_PARAM_FILE(NULL,param);

  if (fp_param != NULL) {
	
    if (debug_level || (Esps_verbose > 1)) 
      fprintf(stderr, "read_params: using param file %s\n", fp_param);

    if(lex_open(fp_param) == FAIL) 	/* process parameter file */
      status = NOPARAM;
    else {
      yacc_errors = 0;
      yyparse();
      fclose(fd_param);
      if (yacc_errors > 0)
	exit(2);
      param_ok = 1;
    }
  } else {
    if ( with_param ) 
      fprintf(stderr, 
	      "read_params: warning - could not find param file %s\n", 
	      param);
  }

  if(!Common_on || flag == SC_NOCOMMON) 
    return status;	/* don't process SPS Common */

  if((junk_fp = fopen(common_file,"r")) != NULL) { /* Common exists */

    int verbose_tmp = Esps_verbose;

    (void)fclose(junk_fp);
    if (stat(common_file, &combuf) != 0) {
      fprintf(stderr,"read_params: cannot stat common file %s\n",
	      common_file);
      fprintf(stderr,"This should not happen.\n");
      exit (1);
    }


    if (param_ok && stat(fp_param, &parambuf) != 0) {
      fprintf(stderr,"read_params: cannot stat param file %s\n",
	      fp_param);
      fprintf(stderr,"This should not happen.\n");
      exit (1);
    }

    if (combuf.st_mode & S_IFDIR) {
      fprintf(stderr,
              "read_params: Warning, ESPS Common file %s is a directory.\n",
	      common_file);
      fprintf(stderr, "It is not being processed.\n");
    } else {
      if ((param_ok && 
	   (combuf.st_mtime>=parambuf.st_mtime)) || !param_ok) {
	status = lex_open(common_file);	/* process common file */
	spsassert(status == 0,"read_params: lex_open failed");
	yacc_errors = 0;
	In_common = 1;  /* this tells make_symbol that we are in common */
	yyparse();
	(void)fclose(fd_param);
	if (yacc_errors > 0)
	  exit(2);
	did_common = 1;
	In_common = 0;
      }
    }

    Esps_verbose = 0;
    if((check_file != NULL) &&  ( (symtype("filename") == ST_UNDEF) || 
				  (strcmp(check_file,getsym_s("filename")) != 0)) ) {
      init_table();		/* clear symbol table */
      if(param_ok) {
	status = lex_open(fp_param);	/* process param again */
	spsassert(status == 0,"read_params: lex_open failed");
	yacc_errors = 0;
	yyparse();
	(void)fclose(fd_param);
	if (yacc_errors > 0)
	  exit(2);
      }
      did_common = 0;
    }
    Esps_verbose = verbose_tmp;
  }
  else {
    if (status == NOPARAM) return NOBOTH;  
    if (status == 0) return NOCOMM;
  }
  if (did_common && debug_level)
    fprintf(stderr,"read_params: Common processed.\n");
  return status;

} /* end read_param() */

int
read_param(param)
char *param;
{
    read_params(param,SC_NOCOMMON,NULL);
    return 0;
}

double MinMax[2];

static
int
setlimit(min,max)
double min, max;
{
	MinMax[0]=min;
	MinMax[1]=max;
	return 1;
}

static
double *
getlimit()
{
	return MinMax;
}
	

static
set_choice(v)
struct cnode *v;
{
	int i=0;
	struct cnode *ptr = v;

	while(ptr != NULL) {
		i++;
		ptr = ptr->c_cdr;
	}
		
	choice_list = (char **)malloc(sizeof(char *)*(i+1));
		
	ptr = v;
	i=0;
	while(ptr != NULL) {
		choice_list[i++] = savestring(ptr->c_car);
		ptr = ptr->c_cdr;
	}
	choice_list[i] = NULL;
	return i;
}

static
char **
get_choice()
{
	char **list = choice_list;

	choice_list = NULL;
	return list;
}
#line 600 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 63 "pfparser.y"
{ yyval.ival = 1; }
break;
case 2:
#line 64 "pfparser.y"
{ yyval.ival = yyvsp[-1].ival && yyvsp[0].ival; }
break;
case 3:
#line 67 "pfparser.y"
{ yyval.ival = yyvsp[-1].ival; }
break;
case 4:
#line 68 "pfparser.y"
{ yyval.ival = yyvsp[-1].ival; }
break;
case 5:
#line 69 "pfparser.y"
{ yyval.ival = yyvsp[-1].ival; }
break;
case 6:
#line 70 "pfparser.y"
{ yyval.ival = yyvsp[-1].ival; }
break;
case 7:
#line 73 "pfparser.y"
{ yyerror("Illegal statement");
			  yyerrok;
			  yyval.ival = 0;
			}
break;
case 8:
#line 78 "pfparser.y"
{ yyerror("Null statement ignored");
			  yyval.ival = 1;
		        }
break;
case 12:
#line 89 "pfparser.y"
{ yyval.ival = yyvsp[-2].ival && yyvsp[0].ival; }
break;
case 14:
#line 92 "pfparser.y"
{ yyval.ival = yyvsp[-2].ival && yyvsp[0].ival; }
break;
case 16:
#line 95 "pfparser.y"
{ yyval.ival = yyvsp[-2].ival && yyvsp[0].ival; }
break;
case 18:
#line 98 "pfparser.y"
{ yyval.ival = yyvsp[-2].ival && yyvsp[0].ival; }
break;
case 19:
#line 105 "pfparser.y"
{ yyval.ival = make_symbol(yyvsp[-4].sval,newval(yyvsp[-2].dval,dval),
				ST_FLOAT,yyvsp[-3].ival,yyvsp[-1].sval,yyvsp[0].ival,getlimit(),get_choice()); }
break;
case 20:
#line 108 "pfparser.y"
{ yyval.ival = make_symbol(yyvsp[-4].sval,newval(yyvsp[-2].flist,flist),
				ST_FARRAY,yyvsp[-3].ival,yyvsp[-1].sval,yyvsp[0].ival,getlimit(),get_choice());}
break;
case 21:
#line 110 "pfparser.y"
{ yyval.ival = bad_decl(yyvsp[-2].sval);}
break;
case 22:
#line 113 "pfparser.y"
{ yyval.ival = make_symbol(yyvsp[-4].sval,newval(yyvsp[-2].ival,ival),
				ST_INT,yyvsp[-3].ival,yyvsp[-1].sval,yyvsp[0].ival,getlimit(),get_choice()); }
break;
case 23:
#line 116 "pfparser.y"
{ yyval.ival = make_symbol(yyvsp[-4].sval,newval(yyvsp[-2].ilist,ilist),
				ST_IARRAY,yyvsp[-3].ival,yyvsp[-1].sval,yyvsp[0].ival,getlimit(),get_choice());}
break;
case 24:
#line 118 "pfparser.y"
{ yyval.ival = bad_decl(yyvsp[-2].sval);}
break;
case 25:
#line 121 "pfparser.y"
{ yyval.ival = make_symbol(yyvsp[-4].sval,newval(yyvsp[-2].cval,cval),
				ST_CHAR,yyvsp[-3].ival,yyvsp[-1].sval,yyvsp[0].ival,getlimit(),get_choice()); }
break;
case 26:
#line 123 "pfparser.y"
{ yyval.ival = bad_decl(yyvsp[-2].sval);}
break;
case 27:
#line 126 "pfparser.y"
{ yyval.ival = make_symbol(yyvsp[-4].sval,newval(yyvsp[-2].sval,sval),
				ST_STRING,yyvsp[-3].ival,yyvsp[-1].sval,yyvsp[0].ival,getlimit(),get_choice()); }
break;
case 28:
#line 128 "pfparser.y"
{ yyval.ival = bad_decl(yyvsp[-2].sval);}
break;
case 29:
#line 132 "pfparser.y"
{ yyval.ival = NOPROMPT; }
break;
case 30:
#line 133 "pfparser.y"
{ yyval.ival = PROMPT; }
break;
case 31:
#line 134 "pfparser.y"
{ yyval.ival = PROMPT; }
break;
case 32:
#line 137 "pfparser.y"
{ yyval.sval = NULL; }
break;
case 33:
#line 138 "pfparser.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 34:
#line 141 "pfparser.y"
{ yyval.ival = 0; }
break;
case 35:
#line 142 "pfparser.y"
{ yyval.ival = setlimit(yyvsp[-3].dval,yyvsp[-1].dval); }
break;
case 36:
#line 143 "pfparser.y"
{ yyval.ival = set_choice(yyvsp[0].clist); }
break;
case 38:
#line 148 "pfparser.y"
{ yyval.dval = (double)yyvsp[0].ival;}
break;
case 39:
#line 149 "pfparser.y"
{ yyval.dval = (double)yyvsp[0].cval;}
break;
case 41:
#line 152 "pfparser.y"
{ yyval.ival = (int)yyvsp[0].cval; }
break;
case 43:
#line 156 "pfparser.y"
{ if (yyvsp[0].ival <= CVMAX && yyvsp[0].ival >= CVMIN) yyval.cval = (char)yyvsp[0].ival;
			  else {
			    sprintf (msgbuf,"%d won't fit in a char",yyvsp[0].ival);
			    yyerror (msgbuf);
			    yyval.cval = 0;
			}}
break;
case 44:
#line 163 "pfparser.y"
{ yyval.flist = yyvsp[-1].flist; }
break;
case 45:
#line 165 "pfparser.y"
{ yyerror("Bad array declaration"); yyval.flist = NULL; }
break;
case 46:
#line 167 "pfparser.y"
{ yyval.flist = fcons(yyvsp[0].dval, NULL_FNODE); }
break;
case 47:
#line 168 "pfparser.y"
{ yyval.flist = fcons(yyvsp[-2].dval,yyvsp[0].flist); }
break;
case 48:
#line 170 "pfparser.y"
{ yyval.ilist = yyvsp[-1].ilist; }
break;
case 49:
#line 172 "pfparser.y"
{ yyerror("Bad array declaration"); yyval.ilist = NULL; }
break;
case 50:
#line 174 "pfparser.y"
{ yyval.ilist = icons(yyvsp[0].ival,NULL_INODE); }
break;
case 51:
#line 175 "pfparser.y"
{ yyval.ilist = icons(yyvsp[-2].ival,yyvsp[0].ilist); }
break;
case 52:
#line 177 "pfparser.y"
{ yyval.clist = yyvsp[-1].clist; }
break;
case 53:
#line 179 "pfparser.y"
{ yyerror("Bad array declaration"); yyval.clist = NULL; }
break;
case 54:
#line 181 "pfparser.y"
{ yyval.clist = ccons(yyvsp[0].sval,NULL_CNODE); }
break;
case 55:
#line 182 "pfparser.y"
{ yyval.clist = ccons(yyvsp[-2].sval,yyvsp[0].clist); }
break;
#line 981 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
