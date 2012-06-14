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

#include "Polygon.h"

//==============================================================================
//
//==============================================================================

typedef struct {
    float Position[3];
    float Color[4];
} Vertex1;
 
const Vertex1 Vertices1[] = {
    {{1, -1, 0}, {1, 0, 0, 1}},
    {{1, 1, 0}, {0, 1, 0, 1}},
    {{-1, 1, 0}, {0, 0, 1, 1}},
    {{-1, -1, 0}, {0, 0, 0, 1}}
};
 
const GLubyte Indices1[] = {
    0, 1, 2,
    2, 3, 0
};

//==============================================================================

Polygon::Polygon():
mVertices(),
mColour(),
mIndices() {

    
    //TODO move to square class
    float temppos[] = { 1, -1, 0,
                        1,  1, 0,
                       -1,  1, 0,
                       -1, -1, 0  };

    float indices[] = { 0, 1, 2, 
                        2, 3, 0 };
    
    mVertices.assign( temppos, temppos+12 );
    mIndices.assign( indices, indices+6 );
    
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW);
 
    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO );
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices1), Indices1, GL_STATIC_DRAW);
    
    
/*
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );
    glBufferData( GL_ARRAY_BUFFER, 
                  sizeof(temppos), 
                  temppos, 
                  GL_STATIC_DRAW );

    glGenBuffers( 1, &mIBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mIBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 
                  sizeof(indices), 
                  indices, 
                  GL_STATIC_DRAW );
                  */
    /*              
    glEnableVertexAttribArray(GLKVertexAttribPosition);        
    glVertexAttribPointer( GLKVertexAttribPosition, 
                           3, 
                           GL_FLOAT, 
                           GL_FALSE, 
                           sizeof(temppos), 
                           0 );

    */
    glEnableVertexAttribArray(GLKVertexAttribPosition);        
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex1), (const GLvoid *) offsetof(Vertex1, Position));
    glEnableVertexAttribArray(GLKVertexAttribColor);
    glVertexAttribPointer(GLKVertexAttribColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex1), (const GLvoid *) offsetof(Vertex1, Color));


}

Polygon::~Polygon() {


    
}

//==============================================================================
//
//==============================================================================

void Polygon::draw() {
        GLubyte indices[] = { 0, 1, 2, 
                        2, 3, 0 };
                        
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mIBO );
 
  
    glDrawElements( GL_TRIANGLES, 
                    sizeof(indices) / sizeof(indices[0]) , 
                    GL_UNSIGNED_BYTE, 
                    0 );

}

//==============================================================================
//
//==============================================================================



//==============================================================================
//
//==============================================================================


//==============================================================================
//
//==============================================================================


