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

#ifndef pender_Image_h
#define pender_Image_h

#include "Polygon.h"

class Image {

public:
    
/*    static const GLfloat mVertices[];
    
    static GLshort mIndices[];
    
    static GLshort mTexCoords[]; */
    
    Image( char * imagePath );
    
    Image( NSString * imagePath );

    //==========================================================================
    //==========================================================================

    Polygon poly() { return mPoly; }
    
    //==========================================================================
    //==========================================================================

protected:
    
    /**
     * initializes the given CGImageRef as a texture
     */
    void initTexture( CGImageRef * image, GLuint & texid );

    
    //==========================================================================
    //==========================================================================
    
    //we hold a pointer to the image path string as an identifier
    NSString * mImagePath;
    
    //the openGL texture id, one per image
    GLuint mTexid;
    
    //
    Polygon mPoly;
    
};

#endif
