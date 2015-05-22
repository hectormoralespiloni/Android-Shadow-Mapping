package verman.androidshadowmapping;

public class LibJNIWrapper 
{
	static {
        System.loadLibrary("AndroidShadowMapping");
    }
 
	public static native void OnStop();
    public static native void OnSurfaceCreated();
    public static native void NativeInit(int width, int height);
    public static native void LoadShader(int technique, String vs, String ps, String[] attributes, String[] uniforms);
    public static native void OnDrawFrame();
}
