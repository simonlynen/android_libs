package ch.ethz.asl.androidlink;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.support.v4.app.NavUtils;

public class MainActivity extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        startLinkServer();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

    public native void startLinkServer();

	static {
		System.loadLibrary("QCAR");
		System.loadLibrary("qcartracker");
		System.loadLibrary("javacppbridge");
		System.loadLibrary("sensorhandler_native");
		System.loadLibrary("androidlink");
	}
}
