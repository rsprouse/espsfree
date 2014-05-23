#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "rlpc.h"

#define DATMAX 8820
#define NPMAX 30
#define TINY 1.0e-20

/* rlpc.c */

double min(x,y)
     double x;
     double y;
{
	if (x>y) return y;
	else return x;
}

double max(x,y)
     double x;
     double y;
{
	if (x>y) return x;
	else return y;
}

double residual(npoles,ndata,d,data,e)
     int npoles;
     int ndata;
     double *d;
     double *data;
     double *e;
{
	int n,i;
	double sum;
	double s=0.0;
	double ss = 0.0;

	for (n=npoles+1;n<ndata;n++) {
		sum=0.0;
		for (i=1;i<=npoles;i++) sum += d[i]*data[n-i];
		e[n]=data[n]+sum;
		s += e[n];
		ss += e[n]*e[n];
	}
	n=ndata-npoles-1;
	/* return the standard deviation of the residual */
	return(sqrt(((double)n*ss-s*s)/((double)n*(n-1))));

}

double weight(x,sd)
     double x;
     double sd;
{
  double y;
  y=(sd*min(1.5,max(x/sd,-1.5)))/x;
  return(y);
}
void correlation_matrix(data, e, npoles,ndata,
			C1,sd)
     double *data;
     double *e;
     int npoles;
     int ndata;
     double C1[][NPMAX];
     double sd;
{
  int i,j,n;
  
  for (i=0;i<=npoles;i++) {  /* count from 0 for the n,n-j vector */
    for (j=1;j<=npoles;j++) {
      C1[i][j]=0.0;
      for (n=npoles+1;n<ndata;n++) {
	C1[i][j] += data[n-i]*data[n-j]*weight(e[n],sd);
      }
    }
  }
}

void ludcmp(C1,npoles,indx,f)
     double C1[][NPMAX];
     int npoles;
     int *indx;
     double *f;
{
  int n,m,nmax,k;
  double big,dum,sum,temp;
  double vv[NPMAX];
  
  *f=1.0;
  for (m=1;m<=npoles;m++) {
    big=0.0;
    for (n=1;n<=npoles;n++)
      if ((temp=fabs(C1[m][n])) > big) big=temp;
    if (big == 0.0) printf("singular matrix in routine LUDCMP\n");
    vv[m]=1.0/big;
  }
  for (n=1;n<=npoles;n++) {
    for (m=1;m<n;m++) {
      sum=C1[m][n];
      for (k=1;k<m;k++) sum -= C1[m][k]*C1[k][n];
      C1[m][n]=sum;
    }
    big=0.0;
    for (m=n;m<=npoles;m++) {
      sum=C1[m][n];
      for (k=1;k<n;k++) sum -= C1[m][k]*C1[k][n];
      C1[m][n]=sum;
      if ((dum=vv[m]*fabs(sum)) >= big) {
	big=dum;
	nmax=m;
      }
    }
    if (n != nmax) {
      for (k=1;k<=npoles;k++) {
	dum=C1[nmax][k];
	C1[nmax][k]=C1[n][k];
	C1[n][k]=dum;
      }
      *f = -(*f);
      vv[nmax]=vv[n];
    }
    indx[n]=nmax;
    if (C1[n][n] == 0.0) C1[n][n]=TINY;
    if (n != npoles) {
      dum=1.0/(C1[n][n]);
      for (m=n+1;m<=npoles;m++) C1[m][n] *= dum;
    }
  }
}
void lubksb(C1,npoles,indx,b)
     double C1[][NPMAX];
     int npoles;
     int *indx;
     double *b;
{
  int m=0,n=0,ip,k;
  double sum;
  
  for (m=1;m<=npoles;m++) {
    ip=indx[m];
    sum=b[ip];
    b[ip]=b[m];
    if (n)
      for (k=n;k<=m-1;k++) sum -= C1[m][k]*b[k];
    else if (sum) n=m;
    b[m]=sum;
  }
  for (m=npoles;m>=1;m--) {
    sum=b[m];
    for (k=m+1;k<=npoles;k++) sum -= C1[m][k]*b[k];
    b[m]=sum/C1[m][m];
  }
}
void matrix_inverse(C1,C2,npoles)
     double C1[][NPMAX];
     double C2[][NPMAX];
     int npoles;
{
  int m,n;
  int indx[NPMAX];
  double col[NPMAX];
  double f;
  
  ludcmp(C1,npoles,indx,&f);
  for (n=1;n<=npoles;n++) {
    for (m=1;m<=npoles;m++) col[m]=0.0;
    col[n]=1.0;
    lubksb(C1,npoles,indx,col);
    for (m=1;m<=npoles;m++) C2[m][n]=col[m];
  }
}
void matrix_negation(C2,npoles)
     double C2[][NPMAX];
     int npoles;
{
  int i,j;
  
  for (j=1;j<=npoles;j++) {
    for (i=1;i<=npoles;i++) C2[i][j] = (-1)*C2[i][j];
  }
}
void matrix_mulpn(C2,npoles,c,C)
     double C2[][NPMAX];
     int npoles;
     double c[NPMAX];
     double C[NPMAX];
{
  int i,j;
  
  for (i=1;i<=npoles;i++) {
    C[i]=0.0;
    for (j=1;j<=npoles;j++) C[i] += C2[i][j]*c[j];
  }
}

/* robust algorithm */
void rlpc(d, datap, npoles, ndata, iterate) 
     double *d;
     short *datap;
     short npoles;
     short ndata;
     short iterate;
{
  
  short i;
  static double data[DATMAX+1];  /* the residual signal */
  static double e[DATMAX+1];  /* the residual signal */
  static double C1[NPMAX][NPMAX];
  static double C2[NPMAX][NPMAX];
  static double c[NPMAX]; /* vector */
  double sd;
  
  for (i=0;i<ndata;i++) data[i]=datap[i]; 
  
  for (i=0;i<iterate;i++) {
    sd=residual(npoles,ndata,d,data,e);
    correlation_matrix(data,e,npoles,ndata,C1,sd);
    matrix_inverse(C1,C2,npoles);
    matrix_negation(C2,npoles);
    matrix_mulpn(C2,npoles,&C1[0][0],d);
  }
}
