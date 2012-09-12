#include <string.h>
#include <jni.h>
#include <cvd/image_io.h>
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
Java_ch_ethz_asl_libcvd_HelloLibCVD_stringFromJNI( JNIEnv* env,
		jobject thiz )
{
	using namespace CVD;

	std::stringstream ss;

	ss<<"Testing libCVD: "<<std::endl;

	ImageRef size;
	size.x = 400;
	size.y = 400;

	Image<byte> in(size, 123);

	ImageRef pos;

	  pos.x = 0;
	  pos.y = in.size().y / 2;

	  ss<<"posx: "<<pos.x<<std::endl;
	  ss<<"posy: "<<pos.y<<std::endl;

	  ss << "Pixel at x=10, y=3 = " << (int)in[3][10] << std::endl;
	  ss << "Pixel at x=0, and half way down = " << (int)in[pos] << std::endl;

	return env->NewStringUTF(ss.str().c_str());
}
}
