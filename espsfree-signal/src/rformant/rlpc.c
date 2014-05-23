#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "clapack.h"
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

void ludcmp(C1,npoles,indx,f,failed)
     double C1[][NPMAX];
     int npoles;
     int *indx;
     double *f;
     int *failed;
{
  int n,m,nmax,k;
  double big,dum,sum,temp;
  double vv[NPMAX];
  *failed = 0;
  
  *f=1.0;
  //printf("ludcmp: starting\n");
  for (m=1;m<=npoles;m++) {
    //printf("ludcmp: m loop %d of %d\n", m, npoles);
    big=0.0;
    for (n=1;n<=npoles;n++)
      if ((temp=fabs(C1[m][n])) > big) big=temp;
    //printf("ludcmp: checking for singularity\n");
    if (big == 0.0) {
      //printf("ludcmp: singular matrix\n");
      *failed = 1;
      m = npoles;
    }
    //printf("ludcmp: assigning to vv\n");
    vv[m]=1.0/big;
    //printf("ludcmp: assigned to vv\n");
  }
  //printf("ludcmp: finished m loop\n", m, npoles);
  nmax = -1;
  for (n=1;n<=npoles;n++) {
    //printf("ludcmp: n loop %d of %d\n", n, npoles);
    for (m=1;m<n;m++) {
      //printf("ludcmp: mn1 loop %d of %d\n", m, n);
      sum=C1[m][n];
      for (k=1;k<m;k++) sum -= C1[m][k]*C1[k][n];
      C1[m][n]=sum;
    }
    //printf("ludcmp: finished mn loop\n", m, npoles);
    big=0.0;
    for (m=n;m<=npoles;m++) {
      //printf("ludcmp: mn2 loop %d of %d\n", m, npoles);
      sum=C1[m][n];
      //printf("ludcmp: mn2 loop summing\n");
      for (k=1;k<n;k++) sum -= C1[m][k]*C1[k][n];
      //printf("ludcmp: mn2 loop summed\n");
      //printf("ludcmp: mn2 loop assigning\n");
      C1[m][n]=sum;
      //printf("ludcmp: mn2 loop assigned\n");
      //printf("ludcmp: big is %0.4f\n", big);
      //printf("ludcmp: sum is %0.4f\n", sum);
      //printf("ludcmp: m is %d\n", m);
      //printf("ludcmp: vv[m] is %0.4f\n", vv[m]);
      //if (isinf(vv[m])) {
       // //printf("ludcmp: vv[m] is infinite\n");
      //}
      if (!isinf(vv[m]) && ((dum=vv[m]*fabs(sum)) >= big)) {
	big=dum;
	nmax=m;
      }
      //printf("ludcmp: done comparing vv[m] to big\n", vv[m]);
      //printf("ludcmp: m is %d; n is %d; npoles is %d\n", m, n, npoles);
    }
    //printf("ludcmp: n is %d; nmax is %d\n", n, nmax);
    if (nmax == -1) {
      // TODO: do we ever end up here without first triggering a singular matrix warning?
      //printf("ludcmp: nmax value invalid\n");
      *failed = 1;
    }
    else if (n != nmax) {
      //printf("ludcmp: n is %d\n", n);
      for (k=1;k<=npoles;k++) {
        //printf("ludcmp: k is %d\n", k);
	dum=C1[nmax][k];
	C1[nmax][k]=C1[n][k];
	C1[n][k]=dum;
      }
      //printf("ludcmp: finished k loop\n");
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
  if (*failed) {
    //printf("ludcmp: did fail\n");
  }
  else {
    //printf("ludcmp: did succeed\n");
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
void matrix_inverse(C1,C2,npoles,failed)
     double C1[][NPMAX];
     double C2[][NPMAX];
     int npoles;
     int *failed;
{
  int m,n;
  int indx[NPMAX];
  double col[NPMAX];
  double f;
  
  *failed = 0;
  int ludfail;
  //printf("matrix_inverse: calling ludcmp\n");
  ludcmp(C1,npoles,indx,&f,&ludfail);
  //printf("matrix_inverse: called ludcmp\n");
  if (ludfail) {
      //printf("matrix_inverse: call to ludcmp failed\n");
      *failed = ludfail;
  }
  else {
    //printf("matrix_inverse: call to ludcmp succeeded\n");
    for (n=1;n<=npoles;n++) {
      for (m=1;m<=npoles;m++) col[m]=0.0;
      col[n]=1.0;
      lubksb(C1,npoles,indx,col);
      for (m=1;m<=npoles;m++) C2[m][n]=col[m];
    }
  }
  if (*failed) {
    //printf("matrix_inverse: did fail\n");
  }
  else {
    //printf("matrix_inverse: did succeed\n");
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

/*
double *createArray(M,w,h)
double **M;
int w,h;
{
  double *A = (double *)malloc(w*h*sizeof(double));
  int i,j;
  for (i = 0; i < h; ++i)
    for (j = 0; j < w; ++j)
      A[i*w+j] = M[i][j];
  return A;
}
void convertArray(L,M,w,h)
double *L,**M;
int w,h;
{
  int i,j;
  for (i = 0; i < h; ++i)
    for (j = 0; j < w; ++j)
      M[i][j] = L[i*w+j];
}
*/
/* Attempt to use LAPACK for matrix inversion */
/* Sample code found at: https://www.google.com/codesearch/p?hl=en#iFPFsVthp5c/pub/users/manocha/MARS/mars_v1_01.tar.Z|BWtb8SrPE14/C/invmat.c&q=dgetri%20lang:c&d=6 */
/*
void invertMatrix(SRC, INV, size)
double **SRC,**INV;
int size;
{
  double *A;
  int *IPIV;
  int LWORK;
  double *WORK;
  // for status return from dgetrf and dgetri
  int INFO;

  A = createArray(SRC,size,size);
  IPIV = (int *)malloc((size+1)*sizeof(int));
  LWORK = size * size;
  WORK = (double *)malloc(LWORK*sizeof(double));
  //dgetrf_(&size,&size,A,&size,IPIV,&INFO);
  //dgetri_(&size,A,&size,IPIV,WORK,&LWORK,&INFO);
  clapack_dgetrf(size,size,size,A,size,IPIV);
  clapack_dgetri(size,size,A,size,IPIV);

  convertArray(A,INV,size,size);
}
*/

/* robust algorithm */
void rlpc(d, datap, npoles, ndata, iterate, failed) 
     double *d;
     short *datap;
     short npoles;
     short ndata;
     short iterate;
     int *failed;
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
    *failed = 0;
    sd=residual(npoles,ndata,d,data,e);
    correlation_matrix(data,e,npoles,ndata,C1,sd);
    int invfail;
    //printf("rlpc: calling matrix_inverse\n");
    matrix_inverse(C1,C2,npoles,&invfail);
    //printf("rlpc: called matrix_inverse\n");
    if (invfail) {
      //printf("rlpc: call to matrix_inverse failed\n");
      *failed = invfail;
    }
    else {
      //printf("rlpc: call to matrix_inverse succeeded\n");
      matrix_negation(C2,npoles);
      matrix_mulpn(C2,npoles,&C1[0][0],d);
    }
  }
}
