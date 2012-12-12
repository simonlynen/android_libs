package ch.ethz.asl.androidlink;
import java.util.List;

import com.jme3.math.Vector3f;

public class AndroidLink {
	public AndroidLink(){
		startLinkServer();
	}
	
	public void stop(){
		stopLinkServer();
	}
	
	public void publishplane(List<Vector3f> plane){
		Vector3f point = plane.get(0);
		Vector3f d1 = plane.get(0).subtract(plane.get(1));
		Vector3f d2 = plane.get(1).subtract(plane.get(2));
		Vector3f norm = d1.cross(d2);
		publishPlane((double)point.x, (double)point.y, (double)point.z, (double)norm.x, (double)norm.y, (double)norm.z);
	}
	private native void publishPlane(double p1, double p2, double p3, double n1, double n2, double n3);
	private native void startLinkServer();
	private native void stopLinkServer();
	
	static {
		System.loadLibrary("QCAR");
		System.loadLibrary("qcartracker");
		System.loadLibrary("javacppbridge");
		System.loadLibrary("sensorhandler_native");
//		System.loadLibrary("androidlink");
	}
}
