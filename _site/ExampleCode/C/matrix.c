#include <R.h>
#include <Rmath.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <R_ext/RS.h>
#include <R_ext/Lapack.h>
#include <R_ext/BLAS.h> 


// A will be written over with Ainv
 void matinv(double *A, int N)
{
	int *IPIV= (int *) malloc(N*sizeof(int));
	int info;
	F77_CALL(dgetrf)(&N, &N, A, &N, IPIV, &info );
	
	if (info < 0)
	error("argument %d of Lapack routine %s had invalid value",
	      -info, "dgetrf");
    if (info > 0)
	error("Lapack routine %s: system is exactly singular: U[%d,%d] = 0",
	      "dgetrf", info, info);
	
	int LWORK=N*N;
	double *WORK = (double *) malloc(LWORK*sizeof(double));
		
	//dgetri_(&N, A, &N, IPIV, WORK, &LWORK, &info);
	F77_CALL(dgetri)(&N, A, &N, IPIV, WORK, &LWORK, &info);
	
	free(IPIV);
	free(WORK);
	
    if (info < 0)
	error("argument %d of Lapack routine %s had invalid value",
	      -info, "dgetri");
    if (info > 0)
	error("Lapack routine %s: system is exactly singular: U[%d,%d] = 0",
	      "dgetri", info, info);

}


//Z=sweep(op(X),v,MARGINopX,"*");
 void sweep_prod(double *X, double *v, double *Z, int nrX, int ncX, char transX, int MARGINopX){
    if(Z == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(EXIT_FAILURE);
    }
    int nrz, ncz;
    int i,j;
    if(transX=='T'){
        nrz=ncX;
        ncz=nrX;
        for(i=0;i<nrz;i++){
            for(j=0;j<ncz;j++){
                if(MARGINopX==1){
                    Z[i+nrz*j]=X[j+nrX*i]*v[i];
                }
                if(MARGINopX==2){
                    Z[i+nrz*j]=X[j+nrX*i] * v[j];
                }
            }
        }
    }else if(transX=='N'){
        nrz=nrX;
        ncz=ncX;
        for(i=0;i<nrz;i++){
            for(j=0;j<ncz;j++){
                if(MARGINopX==1){
                    Z[i+nrz*j]=X[i+nrX*j]*v[i];
                }
                if(MARGINopX==2){
                    Z[i+nrz*j]=X[i+nrX*j] * v[j];
                }	
            }
        }
    }else{
        error("transX must be N or T");
    }
}
//matrix prodoct
//nrx number of rows of x
//ncx number of columns of x
//z :=      alpha*op( x)*op( y ) + beta*C,

 void matprod(double *x, int nrx, int ncx,
		    double *y, int nry, int ncy,  double *z, char transa, char transb, double alpha, double beta)
{
int nrxop,ncxop,nryop,ncyop;
    if(transa=='N'){
    nrxop=nrx;
    ncxop=ncx;
    }else if(transa=='T'){
    nrxop=ncx;
    ncxop=nrx;
    }else{
    error("transa must be N or T\n");
    }
    if(transb=='N'){
    nryop=nry;
    ncyop=ncy;
    }else if(transb=='T'){
    nryop=ncy;
    ncyop=nry;
    }else{
    error("transb must be N or T\n");
    }
    
    if(ncxop!=nryop){
    error("ncxop must be equal to nryop in matrix multiplication\n");
    } 
    // printf("nrxop:%d, ncxop:%d, nryop:%d,ncyop:%d\n",nrxop,ncxop,nryop,ncyop);
    //printf("transa:%c, transb:%c,\n",transa,transb);
     
	 F77_CALL(dgemm)(&transa, &transb, &nrxop, &ncyop, &ncxop, &alpha,
			    x, &nrx, y, &nry, &beta, z, &nrxop);
   
}
//it destructs the matrix x.
//Eigen values for symmetric matrix in ascending order
 void sEigenValue(double *x, int n, double *values)
{
    int lwork, info = 0;
    char jobv[2] = "N", uplo[2] = "L", range[2] = "A";
    double  *work,  *z=NULL, tmp;
    int liwork, *iwork, itmp, m;
    double vl = 0.0, vu = 0.0, abstol = 0.0;
    /* valgrind seems to think vu should be set, but it is documented
     not to be used if range='a' */
    int il, iu, *isuppz;
    double *rx = (double *) calloc(n*n, sizeof(double));
    memcpy(rx,x,n*n*sizeof(double));

  
    isuppz = (int *) calloc(2*n, sizeof(int));
    /* ask for optimal size of work arrays */
    lwork = -1; liwork = -1;
    F77_CALL(dsyevr)(jobv, range, uplo, &n, rx, &n,
                     &vl, &vu, &il, &iu, &abstol, &m, values,
                     z, &n, isuppz,
                     &tmp, &lwork, &itmp, &liwork, &info);
    if (info != 0)
        error("error code from Lapack routine dsyevr");
    lwork = (int) tmp;
    liwork = itmp;
    
    work = (double *) calloc(lwork, sizeof(double));
    iwork = (int *) calloc(liwork, sizeof(int));
    F77_CALL(dsyevr)(jobv, range, uplo, &n, rx, &n,
                     &vl, &vu, &il, &iu, &abstol, &m, values,
                     z, &n, isuppz,
                     work, &lwork, iwork, &liwork, &info);
    free(work);
    free(iwork);
    free(isuppz);
    free(rx);
    if (info != 0)
        error("error code from Lapack routine dsyevr");
    
}

//get determinatn
 double determinant(double *X, int n, int useLog)
{
    int info,sign=1;
    double modulus = 0.0;
    double *A=(double*)calloc(n*n,sizeof(double)); 
    memcpy(A,X, n*n*sizeof(double));
    int *jpvt = (int *) R_alloc(n, sizeof(int));
    F77_CALL(dgetrf)(&n, &n, A, &n, jpvt, &info);
    if (info < 0)
	error("error code from Lapack routine dgetrf");
    else if (info > 0) {
	modulus =
	    (useLog ? R_NegInf : 0.);
    }
    else {
	for (int i = 0; i < n; i++) if (jpvt[i] != (i + 1)) sign = -sign;
	if (useLog) {
	    modulus = 0.0;
	    size_t N1 = n+1;
	    for (int i = 0; i < n; i++) {
		double dii = A[i * N1]; /* i*N1=i+i*n ith diagonal element */
		modulus += log(dii < 0 ? -dii : dii);
		if (dii < 0) sign = -sign;
	    }
	} else {
	    modulus = 1.0;
	    size_t N1 = n+1;
	    for (int i = 0; i < n; i++) modulus *= A[i * N1];
	    if (modulus < 0) {
		modulus = -modulus;
		sign = -sign;
	    }
	}
    }
    free(A);
  
    return modulus;
}
//nrx: number of rows in x
//ncx: number of columns in x
 void symmatprod(double *x, int nrx, int ncx, double *z,char trans, double alpha, double beta)
{
    char *uplo = "U";
    int N, K, LDA=nrx;
    if(trans == 'T'){
        N=ncx;
        K=nrx;
    }
    if(trans == 'N' ){
        N=nrx;
        K=ncx;
    }
    
    
    if (nrx > 0 && ncx > 0) {
        F77_CALL(dsyrk)(uplo, &trans, &N, &K, &alpha, x, &LDA, &beta, z, &N);
        for (int i = 1; i < N ; i++)
            for (int j = 0; j < i; j++) z[i + N *j] = z[j + N * i];
    } else { /* zero-extent operations should return zeroes */
        for(int i = 0; i < N*N; i++) z[i] = 0;
    }
    
}

SEXP C_symmatprod(SEXP R_x, SEXP R_trans)
{
    PROTECT(R_x = AS_NUMERIC(R_x));
    int dimx[2];
    SEXP Rdimx;
    PROTECT(Rdimx=getAttrib(R_x,R_DimSymbol));
    if(isNull(Rdimx)){
        dimx[0]=length(R_x);
        dimx[1]=1;
    }else{
        dimx[0] =INTEGER(Rdimx)[0];
        dimx[1]=INTEGER(Rdimx)[1];
        
    }
    int trans=INTEGER_VALUE(R_trans);
    double *x;
    x=NUMERIC_POINTER(R_x);
   
    SEXP R_z;
    
    PROTECT(R_z=allocMatrix(REALSXP,dimx[trans],dimx[trans]));
    
    // printf("dimension of Z is %d,%d\n",dimx[transa],dimy[!transb]);
    
    double *z;
    z=NUMERIC_POINTER(R_z);
    char transLetters[3]="NT";
    symmatprod(x, dimx[0], dimx[1],z, transLetters[trans],1,0);
    
    UNPROTECT(3);
    return(R_z);

}


//functions directly used by R, not included in header file
SEXP C_matprod(SEXP R_x, SEXP R_y, SEXP R_transa, SEXP R_transb)
{
    PROTECT(R_x=AS_NUMERIC(R_x));
    PROTECT(R_y=AS_NUMERIC(R_y));
    int dimx[2],dimy[2];
    SEXP Rdimx, Rdimy;
     PROTECT(Rdimx=getAttrib(R_x,R_DimSymbol));
     PROTECT(Rdimy=getAttrib(R_y,R_DimSymbol));
    if(isNull(Rdimx)){
        dimx[0]=length(R_x);
        dimx[1]=1;
    }else{
        dimx[0] =INTEGER(Rdimx)[0];
        dimx[1]=INTEGER(Rdimx)[1];
        
    }
    if(isNull(Rdimy)){
        dimy[0]=length(R_y);
        dimy[1]=1;
    }else{
        dimy[0] =INTEGER(Rdimy)[0];
        dimy[1]=INTEGER(Rdimy)[1];
    }

    int transa=INTEGER_VALUE(R_transa);
    int transb=INTEGER_VALUE(R_transb);
    double *x;
    x=NUMERIC_POINTER(R_x);
    double *y;
    y=NUMERIC_POINTER(R_y);
    
    SEXP R_z;
    
    
    PROTECT(R_z=allocMatrix(REALSXP,dimx[transa],dimy[!transb]));
    
   // printf("dimension of Z is %d,%d\n",dimx[transa],dimy[!transb]);
    
    char trans[3]="NT";
    
    double *z;
    z=NUMERIC_POINTER(R_z);
    
    matprod(x, dimx[0], dimx[1], y, dimy[0],  dimy[1],   z,  trans[transa],  trans[transb],1,0);
    
    UNPROTECT(5);
    return(R_z);
    
}



SEXP C_matinv(SEXP R_A)
{
    PROTECT(R_A=AS_NUMERIC(R_A));
    SEXP Rdimx;
    PROTECT(Rdimx=getAttrib(R_A,R_DimSymbol));
    int M, N;
    if(isNull(Rdimx)){
        if(length(R_A)==1){
            M=1;
            N=1;
        }else{
            error("X must be a matrix or scaler\n");
        }
    }else{
        M=INTEGER(Rdimx)[0];
        N=INTEGER(Rdimx)[1];
        if(M!=N)error("must be square matrix\n");
    }
    SEXP R_z;
    PROTECT(R_z=allocMatrix(REALSXP,N,N));
    double *z;
    z=NUMERIC_POINTER(R_z);
    memcpy(z, REAL(R_A), sizeof(double)*N * N);
    matinv(z,N);
    UNPROTECT(3);
    return(R_z);
}

//test speed in R




