#include <stdio.h>
#include <string.h>
#include <jni.h>
#include <complex>
#include <sstream>

#ifndef JNIEXPORT
#define JNIEXPORT
#endif

#ifndef JNICALL
#define JNICALL
#endif

extern "C"{

static long
dgtsv(long N, long NRHS, double *DL, double *D, double *DU, double *B,
		long LDB)
{
	extern void dgtsv_(const long *Np, const long *NRHSp, double *DL,
			double *D, double *DU, double *B, const long *LDBp,
			long *INFOp);
	long info;
	dgtsv_(&N, &NRHS, DL, D, DU, B, &LDB, &info);
	return info;
}

/* return current time in milliseconds */
static double
now_ms(void)
{
	struct timespec res;
	clock_gettime(CLOCK_REALTIME, &res);
	return 1000.0*res.tv_sec + (double)res.tv_nsec/1e6;
}

JNIEXPORT jstring JNICALL
Java_ch_ethz_asl_lapack_HelloLAPACK_stringFromJNI( JNIEnv* env,
		jobject thiz )
{


	double l[] = {
			-1, -2, -1, -1
	};

	double d[] = {
			2, 2, 3, 3, 1
	};

	double u[] = {
			-1, -1, -1, -2
	};

	double x[] = {
			1, 2, 3, 2, 1
	};

	std::stringstream ss;

	ss<<"Testing LAPACK - BLAS: "<<std::endl;

	ss<<std::endl<<"solving: A*X = B";

	int i, info;

	//	ss<<std::endl<<"l: ";
	//	for (i=0; i<5; ++i)
	//		ss<<l[i]<<" ";
	//	ss<<std::endl<<"d: ";
	//	for (i=0; i<5; ++i)
	//		ss<<d[i]<<" ";
	//	ss<<std::endl<<"u: ";
	//	for (i=0; i<5; ++i)
	//		ss<<u[i]<<" ";
	//	ss<<std::endl<<"x: ";
	//	for (i=0; i<5; ++i)
	//		ss<<x[i]<<" ";

	char* charptr;
	double* dblptr;
	int* intptr;
	long* longptr;

	extern void f2c_dtrsm(char* SIDE, char* UPLO, char* TRANSA, char* DIAG, int* M, int* N, double* alpha, double* A, int* lda, double* B, int* ldb);
	f2c_dtrsm(charptr, charptr, charptr, charptr, intptr, intptr, dblptr, dblptr, intptr, dblptr, intptr);


	info = dgtsv(5, 1, l, d, u, x, 5);
	if (info != 0)
		ss<<"failure with error "<<info<<std::endl;

	ss<<std::endl<<"result: ";
	for (i=0; i<5; ++i)
		ss<<x[i]<<" ";

	double correct_solution[] = {
			6.5, 12.0, 15.5, 19.5, 20.5
	};
	ss<<std::endl;
	ss<<std::endl<<"Should be same as: "<<std::endl;
	for (i=0; i<5; ++i)
		ss<<correct_solution[i]<<" ";

	if(info==0)
		ss<<std::endl<<"done."<<std::endl;

	return env->NewStringUTF(ss.str().c_str());
}
}
