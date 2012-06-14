package com.pender;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.ScriptableObject;

import java.nio.*;

import javax.microedition.khronos.egl.*;
import javax.microedition.khronos.opengles.*;

import net.rim.device.api.ui.*;
import net.rim.device.api.ui.container.*;
import net.rim.device.api.system.*;
import net.rim.device.api.opengles.*;

class PenderScreen extends FullScreen implements Runnable
{
    private EGL11 _egl;
    private EGLDisplay _eglDisplay;
    private EGLConfig _eglConfig;
    private EGLSurface _eglSurface;
    private EGLContext _eglContext;
    private GL10 _gl;

    private Bitmap _offscreenBitmap;
    private Graphics _offscreenGraphics;

    private FloatBuffer _vertexArray;
    private FloatBuffer _colorArray;

    private boolean _running;
    private boolean _paused;

    PenderScreen()
    {
        super(FullScreen.DEFAULT_MENU | FullScreen.DEFAULT_CLOSE);
    }

    private void initialize()
    {
        // Get EGL interface
        _egl = (EGL11)EGLContext.getEGL();

        // Get the EGL display
        _eglDisplay = _egl.eglGetDisplay(EGL11.EGL_DEFAULT_DISPLAY);

        // Initialize the display for EGL setting the version to null
        _egl.eglInitialize(_eglDisplay, null);

        // Choose an EGL config
        EGLConfig[] configs = new EGLConfig[1];
        int[] numConfigs = new int[1];
        int[] attrs =
        {
            EGL11.EGL_RED_SIZE,   5,
            EGL11.EGL_GREEN_SIZE, 6,
            EGL11.EGL_BLUE_SIZE,  5,
            EGL11.EGL_NONE
        };
        _egl.eglChooseConfig(_eglDisplay, attrs, configs, 1, numConfigs);
        _eglConfig = configs[0];

        // Create an EGL window surface
        _eglSurface = _egl.eglCreateWindowSurface
            (_eglDisplay, _eglConfig, this, null);

        // Create an EGL context
        createEGLContext();

        // Specify vertices and colors for a triangle
        float[] vertices =
        {
            -0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };
        float[] colors =
        {
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f
        };
        _vertexArray = ByteBuffer.allocateDirect(3 * 3 * 4).asFloatBuffer();
        _vertexArray.put(vertices);
        _vertexArray.rewind();
        _colorArray = ByteBuffer.allocateDirect(4 * 3 * 4).asFloatBuffer();
        _colorArray.put(colors);
        _colorArray.rewind();
        
        
        mCanvas = new PenderCanvas();
        
        System.out.println("Test of imbedded rhino platform");
        System.out.println("Test of imbedded rhino platform");
        System.out.println("Test of imbedded rhino platform");
        System.out.println("Test of imbedded rhino platform");
        System.out.println("Test of imbedded rhino platform");
        System.out.println("Test of imbedded rhino platform");
        System.out.println("Test of imbedded rhino platform");
        
        
        
        Context ctx = Context.enter();
	    mJSScope = ctx.initStandardObjects();
    	ctx.setOptimizationLevel(-1);
    
    	Object jscanvas = Context.javaToJS(mCanvas,mJSScope);
 	    ScriptableObject.putProperty(mJSScope, "Canvas", jscanvas);

    	Context.exit();
    }

    private void createEGLContext()
    {
        // Create an EGL context
        _eglContext = _egl.eglCreateContext
            (_eglDisplay, _eglConfig, EGL10.EGL_NO_CONTEXT, null);

        // Get the GL interface for the new context
        _gl = (GL10)_eglContext.getGL();

        // Make the new context current
        _egl.eglMakeCurrent
           (_eglDisplay, _eglSurface, _eglSurface, _eglContext);
    }

    private void destroyEGL()
    {
        _egl.eglMakeCurrent(_eglDisplay, EGL10.EGL_NO_SURFACE,
            EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
        _egl.eglDestroyContext(_eglDisplay, _eglContext);
        _egl.eglDestroySurface(_eglDisplay, _eglSurface);
    }

    private void handleContextLost()
    {
        // Destroy the EGL context
        _egl.eglMakeCurrent(_eglDisplay, EGL10.EGL_NO_SURFACE,
            EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
        _egl.eglDestroyContext(_eglDisplay, _eglContext);
        _eglContext = EGL10.EGL_NO_CONTEXT;

        // Re-create the EGL context
        createEGLContext();
    }

    /**
     * Main render loop.
     */
    public void run()
    {
        initialize();

        while (_running)
        {
            // Idle if this thread is in the background
            if (_paused)
            {
                synchronized (this)
                {
                    try
                    {
                        wait();
                    }
                    catch (InterruptedException x) { }
                }
            }

            updateBackBuffer();

            renderFrame();
            System.out.println("Test of imbedded rhino platform");
            Context ctx = Context.enter();
           
        	Scriptable mJSScope;
    	    mJSScope = ctx.initStandardObjects();
        	ctx.setOptimizationLevel(-1);
        	String str = "Canvas._drawTestImage();";
        	
        	Object result = ctx.evaluateString(mJSScope, str, "badaboosh", 0, null);
        	System.out.println("evaluated a string in JS");
        	System.out.println(Context.toString(result));
        	
        	
        	Context.exit();

            // Throttle cpu usage
            try
            {
                Thread.sleep(20);
            }
            catch (InterruptedException x) { }
        }

        destroyEGL();
    }

    private void renderFrame()
    {
        // Make the context and surface current and check for EGL_CONTEXT_LOST
        if (!_egl.eglMakeCurrent(_eglDisplay, _eglSurface, _eglSurface, _eglContext))
        {
            if (_egl.eglGetError() == EGL11.EGL_CONTEXT_LOST)
                handleContextLost();
        }

        // Signal that OpenGL rendering is about to begin
        _egl.eglWaitNative(EGL10.EGL_CORE_NATIVE_ENGINE, _offscreenGraphics);

        render(_gl);

        // Signal that OpenGL ES rendering is complete
        _egl.eglWaitGL();

        // Swap the window surface to the display
        _egl.eglSwapBuffers(_eglDisplay, _eglSurface);
    }

    private void render(GL10 gl)
    {
        // Set the GL viewport
        gl.glViewport(0, 0, getWidth(), getHeight());

        // Clear the surface
        gl.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);

        // Set the projection matrix
        gl.glMatrixMode(GL10.GL_PROJECTION);
        gl.glLoadIdentity();
        GLUtils.gluPerspective
            (gl, 45.0f, (float)getWidth()/(float)getHeight(), 0.15f, 10.0f);

        // Draw the triangle
        gl.glMatrixMode(GL10.GL_MODELVIEW);
        gl.glLoadIdentity();
        gl.glTranslatef(0.0f, 0.0f, -3.0f);
        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
        gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
        gl.glVertexPointer(3, GL10.GL_FLOAT, 0, _vertexArray);
        gl.glColorPointer(4, GL10.GL_FLOAT, 0, _colorArray);
        gl.glDrawArrays(GL10.GL_TRIANGLES, 0, 3);
    }

    /**
     * Called by the UI system to paint the screen.
     */
    protected void paint(Graphics g)
    {
        if (_offscreenBitmap != null)
            g.drawBitmap(0, 0, _offscreenBitmap.getWidth(),
                _offscreenBitmap.getHeight(), _offscreenBitmap, 0, 0);
    }

    /**
     * Called when the visibility of the screen changes.
     *
     * @param visible true if the screen is being made visible,
     * false if hidden
     */
    protected void onVisibilityChange(boolean visible)
    {
        if (visible)
        {
            resume();
        }
        else
        {
            pause();
        }
    }

    /**
     * Called when the screen is closing.
     */
    public void close()
    {
        _running = false;
        synchronized (this) { notifyAll(); }

        super.close();
    }

    /**
     * Keeps the back buffer in sync with the screen size.
     */
    private void updateBackBuffer()
    {
        if (_offscreenBitmap != null)
        {
            if (_offscreenBitmap.getWidth() == getWidth() &&
                _offscreenBitmap.getHeight() == getHeight())
                return; // no change needed
        }

        _offscreenBitmap = new Bitmap(getWidth(), getHeight());
        _offscreenGraphics = Graphics.create(_offscreenBitmap);
    }

    private void pause()
    {
        _paused = true;
    }

    private void resume()
    {
        if (_running)
        {
            // Pause the render loop
            _paused = false;
            synchronized (this) { notifyAll(); }
        }
        else
        {
            // Start the render thread.
            _running = true;
            new Thread(this).start();
        }
    }
    
    
    /**
     * 
     */
     private PenderCanvas mCanvas;
     private Scriptable mJSScope;
}





/*

{
    public PenderScreen()
    {        
        // Set the displayed title of the screen       
        setTitle("Rhino Test");
        System.out.println("Test of imbedded rhino platform");
        Context ctx = Context.enter();
       
    	Scriptable mJSScope;
	    mJSScope = ctx.initStandardObjects();
    	ctx.setOptimizationLevel(-1);
    
    	String str = "function foo(x) { return x+5;} foo(5);";
    	Object result = ctx.evaluateString(mJSScope, str, "badaboosh", 0, null);
    	System.out.println("evaluated a string in JS");
    	System.out.println(ctx.toString(result));
    	
    	
    	Context.exit();
    }
}
*/