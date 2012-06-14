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


/*
 * ImageWrapper.h
 * Pender-iOS
 *
 * Created by Lorin Beer
 * email: lorin@adobe.com
 */

#ifndef pender_ImageWrapper_h
#define pender_ImageWrapper_h

#include "Image.h"
#include "reporterror.h"

#define EJS_THROW_ERROR(cx,obj,msg) do{				\
    return ejs_throw_error(cx,obj,msg);				\
}while(0)

extern "C" {
    static void ImageWrapper_finalize(JSContext *cx, JSObject *obj);
    
    static JSClass ImageWrapper_class = {
        "Image", JSCLASS_HAS_PRIVATE,
        JS_PropertyStub,  JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
        JS_EnumerateStub, JS_ResolveStub,
        JS_ConvertStub,  ImageWrapper_finalize, JSCLASS_NO_OPTIONAL_MEMBERS
    };
    
    /*static JSBool ImageWrapper_initTexture( JSContext * cx, 
                                      JSObject * obj, 
                                      uintN argc, 
                                      jsval * argv,
                                      jsval * rval)
    {
        if ( !JS_InstanceOf( cx, obj, &ImageWrapper_class, argv ) ) {
            return JS_FALSE; 
        }
        Image * image = static_cast<Image * > ( JS_GetPrivate(cx,obj) );
        if (!image) {
            EJS_THROW_ERROR(cx,obj,"no valid Image object");
        }
        return JS_NewNumberValue(cx,image->initTexture(<#CGImageRef *image#>, <#GLuint &texid#>),rval);
    }*/
    
    /*
     * 
     */
    static JSFunctionSpec ImageWrapper_methods[] = {

        {0,0,0,0,0}

    };
    
    /*
     * constructor
     */
    static JSBool ImageWrapper_cons (JSContext *cx, 
                                     JSObject *obj, 
                                     uintN argc, 
                                     jsval *argv, 
                                     jsval *rval) 
    {

        if (!JS_IsConstructing(cx)) {
            EJS_THROW_ERROR(cx,obj,"not yet implemented");
        }
        char * str = "0000.png";
        return JS_SetPrivate(cx,obj,(void *)new Image( str ) );
    }

    /*
     * destructor
     */
    static void ImageWrapper_finalize(JSContext *cx, JSObject *obj)
    {
        assert(JS_GET_CLASS(cx, obj) == &ImageWrapper_class);
        Image * image =static_cast<Image *>(JS_GetPrivate(cx,obj));
        if (image) delete image;
    }

    static JSObject* ImageWrapper_proto = NULL;

}

JSBool ImageWrapper_init( JSContext *cx, JSObject *global )
{
    if ( !(ImageWrapper_proto 
            = JS_InitClass(cx, global, NULL, &ImageWrapper_class,
                           ImageWrapper_cons, 0, NULL, 
                           ImageWrapper_methods, NULL, NULL)))
        return JS_FALSE;
    return JS_TRUE;
}

#endif
