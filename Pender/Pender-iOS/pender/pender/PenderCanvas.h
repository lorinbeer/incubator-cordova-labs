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

#ifndef pender_PenderCanvas_h
#define pender_PenderCanvas_h

#include <GLKit/GLKit.h>

class PenderCanvas {
    
public:

    //==========================================================================
    //==========================================================================

    PenderCanvas();

    //==========================================================================
    // State
    //==========================================================================

    void save(); // push state on state stack
    void restore(); // pop state stack and restore state
    
    //==========================================================================
    // Transforms
    //==========================================================================
    
    void scale( float x, float y );
    
    void rotate( float angle );
    
    void translate( float x, float y );
    
    void transform( double a, double b, double c, 
                    double d, double e, double f  );

    void setTransform( double a, double b, double c, 
                       double d, double e, double f  );

    //==========================================================================
    // Image
    //==========================================================================
    
    void drawImage( int image, float dx, float dy);
    
    void drawImage( int image, float dx, float dy, float dw, float dh);
    
    void drawImage( int  image, float sx, float sy, float sw, float sh, 
                   float dx, float dy, float dw, float dh  );
    
         
};

#endif
