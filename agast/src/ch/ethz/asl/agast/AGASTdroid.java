package ch.ethz.asl.agast;

import ch.ethz.asl.agast.AGASTdroidView;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;

public class AGASTdroid extends Activity {
	private static final String TAG = "Sample::Activity";
	
	 public AGASTdroid() {
	        Log.i(TAG, "Instantiated new " + this.getClass());
	    }
	
	/** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	 Log.i(TAG, "onCreate");
         super.onCreate(savedInstanceState);
         requestWindowFeature(Window.FEATURE_NO_TITLE);
         setContentView(new AGASTdroidView(this));
    }
  
}
