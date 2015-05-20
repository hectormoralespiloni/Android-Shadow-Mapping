package verman.androidshadowmapping;

public class LibJNIWrapper 
{
	static {
        System.loadLibrary("AndroidShadowMapping");
    }
 
	public static native void OnStop();
    public static native void OnSurfaceCreated();
    public static native void OnSurfaceChanged(int width, int height);
    public static native void OnDrawFrame();
}
