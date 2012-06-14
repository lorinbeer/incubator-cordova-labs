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

#include <QuartzCore/QuartzCore.h>
#include <OpenGLES/ES1/gl.h>
//#include <OpenGLES/ES1/glext.h>


#include "Image.h"

#include "glaid_util.h"


//==============================================================================
//
//==============================================================================

Image::Image( char * imagepath ):
    mImagePath(0),
    mTexid(0),
    mPoly(){
    
    NSLog(@"THERE IS ONLY ONE PLACE CALLING US!");
    NSString * str = [NSString stringWithUTF8String:imagepath];
        
    CGImageRef img = [UIImage imageNamed: str].CGImage;
    
    initTexture( &img, mTexid );

    
}

Image::Image( NSString * imagepath ):
    mImagePath(0),
    mTexid(0),
    mPoly(){

    //I hear this caches the image, will look into that
    CGImageRef img = [UIImage imageNamed: imagepath].CGImage;
    initTexture( &img, mTexid );
    
}

//==============================================================================
//
//==============================================================================

void Image::initTexture( CGImageRef * image, GLuint & texid ) {
    GLubyte * imgData = NULL;
    CGContextRef imgContext;
    size_t width  = 0;
    size_t height = 0;
    
    if( !powerof2( height ) && !powerof2( width ) )
    {
        NSLog( @"Error: Image dimensions not a power of 2" );
        
    }
    else {
        
        
        
    }
    if( image ) {

        width = CGImageGetWidth( *image );
        imgData = (GLubyte *) calloc(width * height * 4, sizeof(GLubyte));
        imgContext = CGBitmapContextCreate(  imgData, 
                                             width, 
                                             height, 
                                             8, 
                                             width * 4, 
                                             CGImageGetColorSpace(*image), 
                                             kCGImageAlphaPremultipliedLast);
        
        CGContextDrawImage( imgContext, 
                            CGRectMake(0.0, 0.0, 
                            (CGFloat)width, 
                            (CGFloat)height), 
                            *image);

        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 
                      width, height, 0, GL_RGBA, 
                      GL_UNSIGNED_BYTE, imgData);
        
        //cleanup
        free(imgData); //release image data
        CGContextRelease( imgContext );  //release the context

    }
}

//==============================================================================
//
//==============================================================================


//==============================================================================
//==============================================================================