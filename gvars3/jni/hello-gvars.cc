#include <string.h>
#include <jni.h>
#include <sstream>
#include <gvars3/gvars3.h>
#include <gvars3/instances.h>
#include <iostream>
#include <cstdlib>

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
Java_ch_ethz_asl_gvars3_HelloGVars_stringFromJNI( JNIEnv* env,
		jobject thiz )
{
	using namespace GVars3;

	std::stringstream ss;

	ss<<"Testing gVars3 : "<<std::endl;

	gvar3<int> an_integer("i");

	std::list<int> intlist;
	intlist.push_back(4);
	intlist.push_back(5);
	intlist.push_back(8);

	ss<<"Integerlist: "<<std::endl;
	for(std::list<int>::iterator it = intlist.begin();it!=intlist.end();++it){
		ss<<*it<<std::endl;
	}

	ss<<"variable contains: "<<*an_integer<<std::endl;

	ss<<"done."<<std::endl;
	return env->NewStringUTF(ss.str().c_str());
}
}
