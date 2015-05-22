package verman.androidshadowmapping;

import android.os.Bundle;
import android.app.Activity;
import android.opengl.GLSurfaceView;

public class MainActivity extends Activity 
{
	private GLSurfaceView mSurfaceView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

        //Create a GLSurfaceView instance and set it
        //as the ContentView for this Activity.
        mSurfaceView = new GLSurfaceViewWrapper(this);
        setContentView(mSurfaceView);
	}
	
	@Override
	protected void onStop() {		
		super.onStop();
		LibJNIWrapper.OnStop();
	}
}
