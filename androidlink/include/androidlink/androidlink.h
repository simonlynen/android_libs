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

#ifndef ANDROIDLINK_H_
#define ANDROIDLINK_H_

#include <android/log.h>

#ifdef LOGI
#undef LOGI
#endif
#ifdef LOGD
#undef LOGD
#endif
#ifdef TAG
#undef TAG
#endif

#define TAG "ANDROIDLINK"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

#include <jni.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "androidlink/androidlink_server.h"
#include "androidlink/packedmessage.h"
#include "androidlink.pb.h"

using namespace std;
namespace asio = boost::asio;
struct ServerThread{
private:
	boost::asio::io_service io_service;
	boost::thread* workerThread;
	void run(){
		io_service.run();
	}
	AndroidLinkServer* inst_;
public:
	AndroidLinkServer* Instance(){
		assert(inst_);
		return inst_;
	}
	ServerThread(int port){
		try {
			inst_ = new AndroidLinkServer(io_service, port);
		}
		catch (std::exception& e) {
			std::stringstream ss;
			ss <<"ANDROIDLINKSERVER CRASH "<< e.what() << std::endl;
			LOGD(ss.str().c_str());
		}
		workerThread = new boost::thread(&ServerThread::run, this);
	}
	void stop(){
		io_service.stop();
		workerThread->interrupt();
		workerThread->join();
	}
	~ServerThread(){
		delete inst_;
		inst_ = 0;
	}
};

class AndroidLink{
public:
	static AndroidLinkServer* Instance(){

		using namespace std;
		namespace asio = boost::asio;
		if(!inst_){

			unsigned port = 4050;
			std::stringstream ss;
			ss<<"ANDROIDLINKSERVER Serving on port "<<port;
			LOGD(ss.str().c_str());
			inst_ = new ServerThread(port);

		}
		return inst_->Instance();
	}
	static void stop(){
		return inst_->stop();
	}

private:
	static ServerThread* inst_;
	AndroidLink(){
		inst_ = 0;
	}
	~AndroidLink(){
		if(inst_){
			delete inst_;
		}
	}
	AndroidLink(const AndroidLink&) {}
};


#endif /* ANDROIDLINK_H_ */
