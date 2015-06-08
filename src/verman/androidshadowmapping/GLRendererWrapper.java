package verman.androidshadowmapping;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;

public class GLRendererWrapper implements Renderer
{
	private Context appCtx;
	
	public GLRendererWrapper(Context context) {
		appCtx = context;
	}
	
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		//Creates a GLES surface
		LibJNIWrapper.OnSurfaceCreated();
		
		//Load all shaders here, will be used later on initialization
		String vs = "";//RawResourceReader.readTextFile(appCtx, R.raw.gouraud_vs);
		String ps = "";//RawResourceReader.readTextFile(appCtx, R.raw.gouraud_ps);
		String[] attributes = {"color", "position", "normal", "texCoords"};
		String[] uniforms = {"modelViewProjectionMatrix", "modelViewMatrix", "lightPosition", "useTexture", "texture0"};		
		LibJNIWrapper.LoadShader(0, vs, ps, attributes, uniforms);
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
