/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmforbid.h

  @author Emmanuel Michon
  @date   2002-11-04
*/

/* Note:
 * ----
 * This header file is NOT guarded against multiple inclusions. This is 
 * intended so that the behaviour of the header can change every time it is 
 * included.
 *
 * This header will alias the basic types of the C and C++ languages to 
 * non-compilable gibberish unless the ALLOW_OS_CODE preprocessor macro is
 * defined. In effect, this file enforces the absence of use of basic types in
 * our code.
 * 
 * If this file was guarded against multiple inclusion, then the first use of 
 * the file (over which you have no control: it could be included in your source
 * through a chain of includes) would determine whether the basic types of the
 * language are allowed or not. In any case, it would prevent you from choosing
 * the behavior you want.
 * 
 * The fact that this header is unguarded is not without consequences: 
 *  - only preprocessor directives are allowed. Function prototypes, struct
 *    definitions, variable declarations, and in general anything related to
 *    the C or C++ languages is not allowed.
 *  - anything that is #define'd in here must previously be #undef'd in order
 *    to avoid redefinition complaints.
 */

#undef char
#undef short
#undef long
#undef float
#undef double

#ifndef ALLOW_OS_CODE

#define char NOTCOMPILABLE
#define short NOTCOMPILABLE
#define long NOTCOMPILABLE
#define float NOTCOMPILABLE
#define double NOTCOMPILABLE
/* Note: 
 * ----
 * unsigned int is needed to override new()
 * int is needed to write main()
 *
 * NOT aliasing these two types to NOTCOMPILABLE.
 */
#endif /* ALLOW_OS_CODE */

