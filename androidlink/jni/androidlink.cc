/*
 * Copyright (C) 2012 Simon Lynen, Autonomous Systems Lab ETH Zürich
 *
 * All rights reserved.
 *
 * simon.lynen@mavt.ethz.ch
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Autonomous Systems Lab, ETH Zurich nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <androidlink/androidlink.h>

#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <sstream>

#include <geometry_msgs/PointStamped.h>

#ifndef JNIEXPORT
#define JNIEXPORT
#endif

#ifndef JNICALL
#define JNICALL
#endif
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_INFO,"ANDROIDLINK",x)

extern "C"{

JNIEXPORT void JNICALL
Java_ch_ethz_asl_androidlink_AndroidLink_startLinkServer( JNIEnv* env,
		jobject thiz )
{
	D("ANDROIDLINK starting LINKSERVER");
	AndroidLink::Instance();
//	for(int i = 0;i<10;++i){
//		geometry_msgs::PoseStamped msg;
//		AndroidLink::Instance()->publish_pose(msg);
//		boost::this_thread::sleep(boost::posix_time::milliseconds(500));
//	}
}
JNIEXPORT void JNICALL
Java_ch_ethz_asl_androidlink_AndroidLink_stopLinkServer( JNIEnv* env,
		jobject thiz )
{
	D("ANDROIDLINK stopping LINKSERVER");
	AndroidLink::stop();
}

JNIEXPORT void JNICALL
Java_ch_ethz_asl_androidlink_AndroidLink_publishPlane( JNIEnv* env,
		jobject thiz, double p1, double p2, double p3, double n1, double n2, double n3){
	geometry_msgs::PointStamped p; //point
	geometry_msgs::PointStamped n; //normal

	p.point.x = p1;
	p.point.y = p2;
	p.point.z = p3;

	n.point.x = n1;
	n.point.y = n2;
	n.point.z = n3;

	AndroidLink::Instance()->publish_plane(p,n);

}
}




ServerThread* AndroidLink::inst_ = NULL;
