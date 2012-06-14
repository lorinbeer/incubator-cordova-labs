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

#include <iostream>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>


#include "PenderCanvas.h"
#include "Polygon.h"
#include "glaid_util.h"



PenderCanvas::PenderCanvas() {

    glClearColor( 1.0, 1.0, 1.0, 1.0 );

}

//==============================================================================
// State
//==============================================================================

void PenderCanvas::save() {

    NSLog(@"PenderCanvas instance save function");
    
    Polygon * poly = new Polygon();
    
    poly->draw();
    

}

void PenderCanvas::restore() {}

//==============================================================================
// Transforms
//==============================================================================

void PenderCanvas::scale( float x, float y ){
    
   // glScalef( x, y, 1.f ); //z coordinate is always set to 1.0

}

void PenderCanvas::rotate( float angle ){

   // glRotatef( angle, 0.f, 0.f, 0.f );
    
}

void PenderCanvas::translate( float x, float y ){

   // glTranslatef( x, y, 0.f ); //z coordinate is always set to 0.0

}

void PenderCanvas::transform( double a, double b, double c, 
                              double d, double e, double f  ){}

void PenderCanvas::setTransform( double a, double b, double c, 
                                 double d, double e, double f  ){}


//==========================================================================
// Image
//==========================================================================

void PenderCanvas::drawImage( int image, float dx, float dy){
    
   // glFrontFace( GL_CW );
    
   // glEnableClientState( GL_VERTEX_ARRAY );
    
  //  glVertexPointer( 3, GL_FLOAT, 0, 
    
  //                  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
}

void PenderCanvas::drawImage( int image, float dx, float dy, float dw, float dh){}

void PenderCanvas::drawImage( int  image, float sx, float sy, float sw, float sh, 
                                          float dx, float dy, float dw, float dh  ){}


//==============================================================================
//==============================================================================
