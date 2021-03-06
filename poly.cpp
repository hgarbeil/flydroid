extern "C"{
#include "nrutil.h"
#include "nr.h"
}


void  poly1d (double x, double p[], int np) ;
void  poly3d (double x, double p[], int np) ;

/*
void svdfit (double x[], double y[], double sig[], int ndata, double a[], int ma,
        double **u, double **v, double w[], double *chisq,
        void (*funcs)(double, double [], int)) ;
*/

void polyfit (double *x, double *y, int npts, int degree, double *coefs)
{

	double **u, **v, *w, chisq=0.f ;
	double *wt ;
	int ncoefs = degree + 1 ;
	wt = new double [npts] ;

	u = dmatrix (1, npts, 1, ncoefs) ;	
	v = dmatrix (1, ncoefs, 1, ncoefs) ;	
	w = dvector (1, ncoefs) ;

	for (int i =0 ; i<npts; i++) *(wt+i) = 1.0f ;

	if (degree==1) {
		svdfit_d (x-1, y-1, wt-1, npts, coefs-1,
			ncoefs, u, v, w, &chisq, poly1d) ; 
	}
	if (degree==3) {
		svdfit_d (x-1, y-1, wt-1, npts, coefs-1,
			ncoefs, u, v, w, &chisq, poly3d) ; 
	}

	free_dmatrix (u, 1, npts, 1, ncoefs) ;
	free_dmatrix (v, 1, ncoefs, 1, ncoefs) ;
	free_dvector (w, 1,  ncoefs) ;
	delete [] wt ;


}

void polyfit (double *x, double *y, int npts, int degree, double *coefs, double *yf)
{
	int i ;
	double **u, **v, *w, chisq=0.f ;
	double *wt ;
	int ncoefs = degree + 1 ;
	wt = new double [npts] ;

	u = dmatrix (1, npts, 1, ncoefs) ;	
	v = dmatrix (1, ncoefs, 1, ncoefs) ;	
	w = dvector (1, ncoefs) ;

	for (i =0 ; i<npts; i++) *(wt+i) = 1.0f ;

	if (degree==1) {
		svdfit_d (x-1, y-1, wt-1, npts, coefs-1,
			ncoefs, u, v, w, &chisq, poly1d) ; 
	        for (i=0; i<npts; i++) 
		 *(yf+i) = coefs[0]+ coefs[1] * *(x+i) ;
	}
	if (degree==3) {
		svdfit_d (x-1, y-1, wt-1, npts, coefs-1,
			ncoefs, u, v, w, &chisq, poly3d) ; 
	        for (i=0; i<npts; i++) 
		 *(yf+i) = coefs[0]+ coefs[1] * *(x+i) +
		 	coefs[2] * *(x+i) * *(x+i) + coefs[3] * *(x+i) * 
		 	*(x+i) * *(x+i) ; 
	}

	free_dmatrix (u, 1, npts, 1, ncoefs) ;
	free_dmatrix (v, 1, ncoefs, 1, ncoefs) ;
	free_dvector (w, 1,  ncoefs) ;
	delete [] wt ;


}

void  poly1d (double x, double p[], int np) {
	p[1]=1.f ;
	p[2]=x ;
}
void  poly3d (double x, double p[], int np) {
	p[1]=1.f ;
	p[2]=x ;
	p[3]=x*x ;
	p[4]=x*x*x ;
}
/*
int main (int argc, char *argv[]){
	int i ;
	double x[10], y[10], coefs[4] ;

	for (i=0; i<10; i++) {
		x[i] = i ;
		y[i] = 17 + 3.2 * x[i] + 2.7 * x[i] * x[i] + 1.1*
			x[i]*x[i] *x[i] ;
	}
	polyfit (x, y, 10, 3, coefs) ;
	for (i=0; i<4 ; i++) {
		printf ("%f\r\n", coefs[i] ) ;
	}

}

*/
