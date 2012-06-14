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

/**
 *  Polygon.h
 *  basic geometry object
 */

#ifndef pender_Polygon_h
#define pender_Polygon_h

#import <GLKit/GLKit.h>
//#import <OpenGLES/ES2/gl.h>
//#import <OpenGLES/ES2/glext.h>

#include <vector> 

//==============================================================================

//==============================================================================

class Polygon {
 
public:
    
    //==========================================================================
    
    Polygon();
    
    //==========================================================================
    
    ~Polygon();
    
    //==========================================================================
    
    GLuint vbo() { return mVBO; }
    
    //==========================================================================
    
    GLuint ibo() { return mIBO; }
    
    //==========================================================================
    //
    //==========================================================================
    
    void draw();
    
    //==========================================================================
    
    
protected:
    
    /**
     *
     * param data 
     * param buff buffer object id will be placed here
     */
     /*
     void initBuffer( const std::vector<GLfloat> & data, GLuint &buff ) {

        const GLfloat * dataptr = &data[0];

        glGenBuffers( 1, &buff );
        glBindBuffer( GL_ARRAY_BUFFER, buff );
        glBufferData( GL_ARRAY_BUFFER, 
                      sizeof(dataptr), 
                      dataptr, 
                      GL_STATIC_DRAW);

        glBindBuffer( GL_ARRAY_BUFFER, 0 ); //unbind buff
        
    }
*/
    //==========================================================================
    //
    //==========================================================================
    
    GLuint mVBO; //Vertex Buffer Object
    
    GLuint mIBO; //Index Buffer Object
    
    //==========================================================================
    
    std::vector< GLfloat > mVertices;
    
    std::vector< GLfloat > mColour;
    
    std::vector< GLfloat > mIndices;
    
    //==========================================================================
    
};

#endif
