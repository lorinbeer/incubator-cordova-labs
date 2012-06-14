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

#ifndef pender_glaid_util_h
#define pender_glaid_util_h

/**
 * determines if argument is the result of an exponentiation of base 2 and
 * exponent n
 * Behaviour:
 * if 2^n = numb : for some integer n, then return true
 * if 2^n != numb: for any integer n, then return false
 * if numb < 1   : return false
 * 
 * @param numb integer to test
 * return true if arg is a power of 2, false otherwise
 */
extern inline bool powerof2( int numb ) {

    if( numb < 1 || numb & numb - 1 ) { 
        return false; 
    }
    else { 
        return true; 
    }

}



#endif
