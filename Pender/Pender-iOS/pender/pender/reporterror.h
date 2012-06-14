/* Stolen without modification the excellent docs at egachine.berlios.de
 * http://egachine.berlios.de/embedding-sm-best-practice/embedding-sm-best-practice.html#errorhandler
 */

#ifndef pender_reporterror_h
#define pender_reporterror_h

#include "jsapi.h"
#include <string.h>

//! throw an JavaScript Error exception

#define EJS_THROW_ERROR(cx,obj,msg) do{				\
    return ejs_throw_error(cx,obj,msg);				\
}while(0)

inline
JSBool
ejs_throw_error(JSContext* cx, JSObject* obj, const char* msg)
{
    JSString* jsstr;
    // if we get errors during error reporting we report those
    if ( ((jsstr=JS_NewStringCopyZ(cx, msg)))
        && (JS_AddNamedRoot(cx,&jsstr,"jsstr")) ) {
        jsval dummy;						
        // We can't use JS_EvaluateScript since the stack would be wrong
        JSFunction *func;
        JSObject* fobj;
        const char* fbody="throw new Error(msg);";
        const char* argnames[]={"msg"};
        if ((func=JS_CompileFunction(cx, obj, NULL,
                                     1, argnames,
                                     fbody, strlen(fbody),	
                                     NULL, 0))) {
            // root function
            if ( ((fobj = JS_GetFunctionObject(func)))
                && (JS_AddNamedRoot(cx, &fobj, "fobj")) ) {
                jsval args[]={STRING_TO_JSVAL(jsstr)};
                JS_CallFunction(cx, obj, func, 1, args, &dummy);
                JS_RemoveRoot(cx, &fobj);
            }
        }
        JS_RemoveRoot(cx,&jsstr);
    }
    
    return JS_FALSE;
}

#endif
