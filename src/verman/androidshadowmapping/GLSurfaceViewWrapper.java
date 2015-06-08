package verman.androidshadowmapping;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class GLSurfaceViewWrapper extends GLSurfaceView 
{
	private final GLRendererWrapper mRenderer;
	
	public GLSurfaceViewWrapper(Context context) {
		super(context);
		
        //Create an OpenGL ES 2.0 context
        setEGLContextClientVersion(2);
        setEGLConfigChooser(8,8,8,8,16,0);

        mRenderer = new GLRendererWrapper();             

        //Set the Renderer for drawing on the GLSurfaceView
        setRenderer(mRenderer);       
	}
}
