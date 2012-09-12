#include <string.h>
#include <jni.h>
#include <TooN/lapack.h>
#include <TooN/TooN.h>
#include <TooN/SVD.h>
#include <TooN/LU.h>
#include <TooN/gaussian_elimination.h>
#include <sstream>

#ifndef JNIEXPORT
#define JNIEXPORT
#endif

#ifndef JNICALL
#define JNICALL
#endif

/* return current time in milliseconds */
static double
now_ms(void)
{
	struct timespec res;
	clock_gettime(CLOCK_REALTIME, &res);
	return 1000.0*res.tv_sec + (double)res.tv_nsec/1e6;
}

extern "C"{
JNIEXPORT jstring JNICALL
Java_ch_ethz_asl_toon_HelloTooN_stringFromJNI( JNIEnv* env,
		jobject thiz )
{
	using namespace TooN;

	std::stringstream ss;

	ss<<"Testing TooN: "<<std::endl;

	Matrix<6> A;
	A[0]=makeVector(1,2,3,4,5,6);
	A[1]=makeVector(3,6,1,3,2,1);
	A[2]=makeVector(1,3,4,0,3,0);
	A[3]=makeVector(1,5,7,2,1,7);
	A[4]=makeVector(8,3,3,0,4,6);
	A[5]=makeVector(1,2,7,3,1,9);

	ss<<"A: "<<std::endl<<A<<std::endl;

	Vector<6> b = makeVector (2,3,4,5,6,7);

	ss<<"b: "<<b<<std::endl<<std::endl;

	ss<<"Will solve Ax=b"<<std::endl<<std::endl;

	Vector<6> x1;
	Vector<6> x2;
	Vector<6> x3;

	int runs = 10000;
	double tstart;
	tstart = now_ms();
	// solve Ax=b using LU x times

	for(int i = 0;i<runs;++i){
		LU<6> luA(A);
		x1 = luA.backsub(b);
	}
	tstart = now_ms() - tstart;

	ss<<runs<<" runs using LU backsub took: "<<tstart<<" ms total and "<< tstart / runs<<" ms per run"<<std::endl<<std::endl;


	tstart = now_ms();
	// solve Ax=b using LU x times

	for(int i = 0;i<runs;++i){
		x2 = TooN::gaussian_elimination(A, b);
	}
	tstart = now_ms() - tstart;
	ss<<runs<<" runs using Gauss elim took: "<<tstart<<" ms total and "<< tstart / runs<<" ms per run"<<std::endl<<std::endl;

	tstart = now_ms();
	// solve Ax=b using SVD x times
	for(int i = 0;i<runs;++i){
		SVD<6> svdA(A);
		x3 = svdA.backsub(b);
	}
	tstart = now_ms() - tstart;

	ss<<runs<<" runs using SVD backsub took: "<<tstart<<" ms total and "<< tstart / runs<<" ms per run"<<std::endl;
	ss<<std::endl;
	ss<<"backsub: x1 "<<x1<<std::endl;
	ss<<"backsub: x2 "<<x2<<std::endl;
	ss<<"backsub: x3 "<<x3<<std::endl;


	return env->NewStringUTF(ss.str().c_str());
}
}

//namespace nmsp{
//extern "C"{
//
//static long
//dgtsv(long N, long NRHS, double *DL, double *D, double *DU, double *B,
//		long LDB)
//{
//	extern void dgtsv_(const long *Np, const long *NRHSp, double *DL,
//			double *D, double *DU, double *B, const long *LDBp,
//			long *INFOp);
//	long info;
//	dgtsv_(&N, &NRHS, DL, D, DU, B, &LDB, &info);
//	return info;
//}
//}
//
//
//extern "C"{
//JNIEXPORT jstring JNICALL
//Java_ch_ethz_asl_toon_HelloTooN_stringFromJNI( JNIEnv* env,
//		jobject thiz )
//{
//	double l[] = {
//			-1, -2, -1, -1
//	};
//
//	double d[] = {
//			2, 2, 3, 3, 1
//	};
//
//	double u[] = {
//			-1, -1, -1, -2
//	};
//
//	double x[] = {
//			1, 2, 3, 2, 1
//	};
//
//	std::stringstream ss;
//
//	ss<<"LAPACK TOON LINK: "<<std::endl;
//
//	ss<<std::endl<<"solving: A*X = B";
//
//	int i, info;
//
////	ss<<std::endl<<"l: ";
////	for (i=0; i<5; ++i)
////		ss<<l[i]<<" ";
////	ss<<std::endl<<"d: ";
////	for (i=0; i<5; ++i)
////		ss<<d[i]<<" ";
////	ss<<std::endl<<"u: ";
////	for (i=0; i<5; ++i)
////		ss<<u[i]<<" ";
////	ss<<std::endl<<"x: ";
////	for (i=0; i<5; ++i)
////		ss<<x[i]<<" ";
//
//	info = nmsp::dgtsv(5, 1, l, d, u, x, 5);
//	char* charptr;
//	double* dblptr;
//	int* intptr;
//	long* longptr;
//
//	extern void dtrsm(char* SIDE, char* UPLO, char* TRANSA, char* DIAG, int* M, int* N, double* alpha, double* A, int* lda, double* B, int* ldb);
//
//	dtrsm(charptr, charptr, charptr, charptr, intptr, intptr, dblptr, dblptr, intptr, dblptr, intptr);
//
//
//	if (info != 0)
//		ss<<"failure with error "<<info<<std::endl;
//
//	ss<<std::endl<<"result: ";
//	for (i=0; i<5; ++i)
//		ss<<x[i]<<" ";
//
//	double correct_solution[] = {
//			6.5, 12.0, 15.5, 19.5, 20.5
//	};
//	ss<<std::endl;
//	ss<<std::endl<<"Should be same as: "<<std::endl;
//	for (i=0; i<5; ++i)
//		ss<<correct_solution[i]<<" ";
//
//	if(info==0)
//		ss<<std::endl<<"done."<<std::endl;
//
//	return env->NewStringUTF(ss.str().c_str());
//}
//}
//}
