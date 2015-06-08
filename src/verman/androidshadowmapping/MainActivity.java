package verman.androidshadowmapping;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.app.Activity;
import android.opengl.GLSurfaceView;

public class MainActivity extends Activity 
{
	private static AssetManager mAssetManager;
	private GLSurfaceView mSurfaceView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		//Initialize the assets manager and pass it to JNI
		mAssetManager = getAssets();
		LibJNIWrapper.CreateAssetMgr(mAssetManager);
		
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
