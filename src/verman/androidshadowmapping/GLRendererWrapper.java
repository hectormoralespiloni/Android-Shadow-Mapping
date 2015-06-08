package verman.androidshadowmapping;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;

public class GLRendererWrapper implements Renderer
{
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		//Creates a GLES surface
		LibJNIWrapper.OnSurfaceCreated();
	}
	
	@Override
	public void onDrawFrame(GL10 gl) {
		LibJNIWrapper.OnDrawFrame();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		LibJNIWrapper.NativeInit(width, height);
	}
}
