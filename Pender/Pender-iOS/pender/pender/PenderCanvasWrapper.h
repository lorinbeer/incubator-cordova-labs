/**
 * Copyright 2012 Lorin Beer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef pender_PenderCanvasWrapper_h
#define pender_PenderCanvasWrapper_h

#include <string.h>

#include "PenderCanvas.h"
#include "reporterror.h"

#define EJS_THROW_ERROR(cx,obj,msg) do{				\
return ejs_throw_error(cx,obj,msg);				    \
}while(0)

extern "C" {

    static void PenderCanvasWrapper_finalize(JSContext *cx, JSObject *obj);
    
    static JSClass PenderCanvasWrapper_class = {
        "Canvas", JSCLASS_HAS_PRIVATE,
        JS_PropertyStub,  JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
        JS_EnumerateStub, JS_ResolveStub,
        JS_ConvertStub, PenderCanvasWrapper_finalize, JSCLASS_NO_OPTIONAL_MEMBERS
    };

    //==========================================================================

    static JSBool PenderCanvasWrapper_save( JSContext * cx,
                                           JSObject * obj,
                                           uintN argc,
                                           jsval * argv,
                                           jsval * rval ) {
        
        if ( !JS_InstanceOf( cx, obj, &PenderCanvasWrapper_class, argv ) ) {
            return JS_FALSE; 
        }
        
        PenderCanvas * canvas = static_cast<PenderCanvas * > ( JS_GetPrivate(cx,obj) );
        
        if (!canvas) {
            
            EJS_THROW_ERROR(cx,obj,"no valid Canvas object");
            
        }
        
        canvas->save();
        
        return 0;
        
    }

    //==========================================================================
    
    static JSBool PenderCanvasWrapper_restore( JSContext * cx,
                                           JSObject * obj,
                                           uintN argc,
                                           jsval * argv,
                                           jsval * rval ) {
        
        if ( !JS_InstanceOf( cx, obj, &PenderCanvasWrapper_class, argv ) ) {
            return JS_FALSE; 
        }
        
        PenderCanvas * canvas = static_cast<PenderCanvas * > ( JS_GetPrivate(cx,obj) );
        
        if (!canvas) {
            
            EJS_THROW_ERROR(cx,obj,"no valid Canvas object");
            
        }
        
        //canvas->restore();
        
        return 0;
        
    }    
    
    //==========================================================================
    /**
     * wrapper for scale   
     * void scale( float x, float y )
     */
    static JSBool PenderCanvasWrapper_scale( JSContext * cx,
                                             JSObject * obj,
                                             uintN argc,
                                             jsval * argv,
                                             jsval * rval ) {
        
        if ( !JS_InstanceOf( cx, obj, &PenderCanvasWrapper_class, argv ) ) {
            return JS_FALSE; 
        }
        
        PenderCanvas * canvas = static_cast<PenderCanvas * > ( JS_GetPrivate(cx,obj) );
        
        if (!canvas) {
            
            EJS_THROW_ERROR(cx,obj,"no valid Canvas object");
            
        }
        
        //canvas->scale( x , y );
        
        return 0;
        
    }    

    //==========================================================================
    
    /**
     * wrapper for rotate  
     * void rotate( float angle )
     */
    static JSBool PenderCanvasWrapper_rotate( JSContext * cx,
                                              JSObject * obj,
                                              uintN argc,
                                              jsval * argv,
                                              jsval * rval ) {
        
        if ( !JS_InstanceOf( cx, obj, &PenderCanvasWrapper_class, argv ) ) {
            return JS_FALSE; 
        }
        
        PenderCanvas * canvas = static_cast<PenderCanvas * > ( JS_GetPrivate(cx,obj) );
        
        if (!canvas) {
            
            EJS_THROW_ERROR(cx,obj,"no valid Canvas object");
            
        }
        
        //canvas->rotate( angle );
        
        return 0;
        
    } 

    //==========================================================================
    
    /**
     * wrapper for translate  
     * void translate( float x, float y )
     */
    static JSBool PenderCanvasWrapper_translate( JSContext * cx,
                                                 JSObject * obj,
                                                 uintN argc,
                                                 jsval * argv,
                                                 jsval * rval ) {
        
        jsdouble x = 0.0;
        jsdouble y = 0.0;
        
        if ( !JS_InstanceOf( cx, obj, &PenderCanvasWrapper_class, argv ) ) {
            return JS_FALSE; 
        }
        
        PenderCanvas * canvas = static_cast<PenderCanvas * > ( JS_GetPrivate(cx,obj) );
    
        if (!canvas) {
            
            EJS_THROW_ERROR(cx,obj,"no valid Canvas object");
            
        }
        
        if( argc != 2 ) {
         
            EJS_THROW_ERROR(cx,obj,"incorrect number of parameters");
            
        }
        
        if( !JS_ValueToNumber( cx, argv[0] , &x ) || 
            !JS_ValueToNumber( cx, argv[1] , &y )    ) {
            
            EJS_THROW_ERROR(cx,obj,"incorrect parameter type");
            
        }
        
        //canvas->translate( x, y );
        
        return 0;
        
    }
    
    //==========================================================================

    /**
     * wrapper for canvas transform   
     * void transform( double a, double b, double c, 
     *                 double d, double e, double f  )
     */
    static JSBool PenderCanvasWrapper_transform( JSContext * cx,
                                                 JSObject * obj,
                                                 uintN argc,
                                                 jsval * argv,
                                                 jsval * rval ) {
        
        if ( !JS_InstanceOf( cx, obj, &PenderCanvasWrapper_class, argv ) ) {
            return JS_FALSE; 
        }
        
        PenderCanvas * canvas = static_cast<PenderCanvas * > ( JS_GetPrivate(cx,obj) );
        
        if (!canvas) {
            
            EJS_THROW_ERROR(cx,obj,"no valid Canvas object");
            
        }
        
        //canvas->translate( float x, float y )
        
        return 0;
        
    }
    
    //==========================================================================
    
    /**
     * wrapper for canvas setTransform
     * void setTransform( double a, double b, double c, 
     *                    double d, double e, double f  )
     */
    static JSBool PenderCanvasWrapper_setTransform( JSContext * cx,
                                                     JSObject * obj,
                                                     uintN argc,
                                                     jsval * argv,
                                                     jsval * rval ) {
        
        if ( !JS_InstanceOf( cx, obj, &PenderCanvasWrapper_class, argv ) ) {
            return JS_FALSE; 
        }
        
        PenderCanvas * canvas = static_cast<PenderCanvas * > ( JS_GetPrivate(cx,obj) );
        
        if (!canvas) {
            
            EJS_THROW_ERROR(cx,obj,"no valid Canvas object");
            
        }
        
        //canvas->translate( float x, float y )
        
        return 0;
        
    }
 
    //==========================================================================
    
    /**
     * wrapper for drawImage functions
     * draw image is overloaded, we differentiate by number of arguments
     *
     * void drawImage( int image, float dx, float dy);
     *
     * void drawImage( int image, float dx, float dy, float dw, float dh);
     *
     * void drawImage(image, sx, sy, sWidth, sHeight, dx, dy, dWidth, dHeight);
     *
     */
    static JSBool PenderCanvasWrapper_drawImage( JSContext * cx,
                                                 JSObject * obj,
                                                 uintN argc,
                                                 jsval * argv,
                                                 jsval * rval ) {
        
        if ( !JS_InstanceOf( cx, obj, &PenderCanvasWrapper_class, argv ) ) {
            return JS_FALSE; 
        }
        
        PenderCanvas * canvas = static_cast<PenderCanvas * > ( JS_GetPrivate(cx,obj) );
        
        if (!canvas) {
            
            EJS_THROW_ERROR(cx,obj,"no valid Canvas object");
            
        }
        
        //canvas->translate( float x, float y )
        
        return 0;
        
    }
    
    //==========================================================================
    
    //==========================================================================

    //==========================================================================
        
    //==========================================================================
    
    //==========================================================================
    
    //==========================================================================
    
    //==========================================================================
    
    //==========================================================================
    
    /*
     * 
     */
    static JSFunctionSpec PenderCanvasWrapper_methods[] = {
        
        { "save", PenderCanvasWrapper_save, 0, 0, 0 },
        
        { "restore", PenderCanvasWrapper_restore, 0, 0, 0 },
        
        { "scale", PenderCanvasWrapper_scale, 0, 0, 0 },
        
        { "rotate", PenderCanvasWrapper_rotate, 0, 0, 0 },
        
        { "translate", PenderCanvasWrapper_translate, 0, 0, 0 },
        
        { "transform", PenderCanvasWrapper_transform, 0, 0, 0 },
        
        { "setTransform", PenderCanvasWrapper_setTransform, 0, 0, 0 },
        
        { "drawImage", PenderCanvasWrapper_drawImage, 0, 0, 0 },
        
        {0,0,0,0,0}
        
    };
    
    /*
     * constructor
     */
    static JSBool PenderCanvasWrapper_cons (JSContext *cx, 
                                            JSObject *obj, 
                                            uintN argc, 
                                            jsval *argv, 
                                            jsval *rval) {   
        if (!JS_IsConstructing(cx)) {
            EJS_THROW_ERROR(cx,obj,"not yet implemented");
        }
        return JS_SetPrivate(cx,obj,(void *)new PenderCanvas() );
    }
    
    /*
     * destructor
     */
    static void PenderCanvasWrapper_finalize(JSContext *cx, JSObject *obj)
    {
        assert(JS_GET_CLASS(cx, obj) == &PenderCanvasWrapper_class);
        PenderCanvas * canvas =static_cast<PenderCanvas *>(JS_GetPrivate(cx,obj));
        if (canvas) delete canvas;
    }
    
    static JSObject* PenderCanvasWrapper_proto = NULL;
    
}

JSBool PenderCanvasWrapper_init( JSContext *cx, JSObject *global )
{
    if ( !(PenderCanvasWrapper_proto 
           = JS_InitClass(cx, global, NULL, &PenderCanvasWrapper_class,
                          PenderCanvasWrapper_cons, 0, NULL, 
                          PenderCanvasWrapper_methods, NULL, NULL)))
        return JS_FALSE;
    return JS_TRUE;
}

#endif
