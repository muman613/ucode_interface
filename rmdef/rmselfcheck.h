/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmselfcheck.h
  @brief  

  -long description-

  @author Emmanuel Michon
  @date   2011-06-30
*/

#ifndef __RMSELFCHECK_H__
#define __RMSELFCHECK_H__

#ifndef __ASSEMBLY__
extern inline void check_rmdef_at_build(void);
extern inline void check_rmdef_at_build(void) 
{
	RMuint32 v=1;

	/*
	  assert little endian
	  looks nice but actually, does not work (compiler bug) see bug#32419
	*/
	RM_BUILD_ASSERT(*(RMuint8 *)&v==1);

	// see bug#5593
	RM_BUILD_ASSERT(sizeof(RMuint32)==4);

	RM_BUILD_ASSERT(sizeof(RMalignment)==4);

	// that will be an issue on amd64 builds. some code, but not all code, will be wrong.
	// comment this line out if you really want to proceed.
	//RM_BUILD_ASSERT(sizeof(NULL)==4);
}

/**
   when in doubt doing porting work, call this function at startup
   if it returns you're ok
*/
extern inline void check_rmdef_at_runtime(void);
extern inline void check_rmdef_at_runtime(void) 
{
	RMuint32 v=0x89;
	
	if (*(RMuint8 *)&v!=0x89) {
		//RMDBGLOG((ENABLE,"compiler not little-endian. Fix.\n"));
		while (1) { };
	}

#if 0
	// warning: comparison is always false due to limited range of data type
	// warning handled as ERROR!
	if (*(RMascii *)&v==0x89) {
		//RMDBGLOG((ENABLE,"compiler uses unsigned char for char. Fix.\n"));
		while (1);
	}
#endif
}
#endif

#endif /* __RMSELFCHECK_H__ */
