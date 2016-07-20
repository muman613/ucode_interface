/*****************************************
 Copyright � 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
   @file rmascii.h
   @brief 7-bit ASCII string handling functions

   @author Mathieu Lacage
   @date 15/10/2001
   @ingroup rmcoreapi
*/

#ifndef __RMASCII_H__
#define __RMASCII_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

/** the maximum length for an internal string */
#define RM_MAX_STRING 2048

/**
   @returns the number of characters in the string. This does not
   include the trailing 0.
 */
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMasciiLength (const RMascii *string);


/**
   Returns TRUE if the strings are equal (case sensitive)

   @param a     
   @param b     
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMbool RMCompareAscii (const RMascii *a,
						const RMascii *b);


/**
   Returns TRUE if the rank first characters of 
   strings are equal (case sensitive)

   @param a     
   @param b     
   @param rank  
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMbool RMNCompareAscii (const RMascii *a,
						 const RMascii *b,
						 RMuint32 rank);

/**
   Returns TRUE if the rank first characters of 
   strings are equal (case insensitive)

   @param a     
   @param b     
   @param rank  
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMbool RMNCompareAsciiCaseInsensitively (const RMascii *a,
								const RMascii *b,
								RMuint32 rank);


/**
   Returns TRUE if the strings are equal (case insensitive)

   @param a     
   @param b     
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMbool RMCompareAsciiCaseInsensitively (const RMascii *a,
								 const RMascii *b);


/**
   @returns a newly-allocated copy of the input parameter.
 */
RM_LIBRARY_IMPORT_EXPORT RMascii *RMMallocAndDuplicateAscii (const RMascii *string);


/**
   allocates a string with size characters.
 */
RM_LIBRARY_IMPORT_EXPORT RMascii *RMMallocAscii (RMuint32 sizeWithoutTrailingZero);

///
/**
   Copy string src in dest.
 */
RM_LIBRARY_IMPORT_EXPORT void RMCopyAscii (RMascii *dest, const RMascii *src);

///
/**
   Copy n characters at most from string src to string dest.
   
   Behaves just like strncpy: ``not more than n bytes of src are
   copied. Thus, if there is no null byte among the first n bytes of
   src, the result will not be null-terminated. In the case where the
   length of src is less than that of n, the remainder of dest will be
   padded with nulls.''
*/
RM_LIBRARY_IMPORT_EXPORT void RMNCopyAscii (RMascii *dest, const RMascii *src, RMuint32 n);

///
/**
   @param str1 first string to concatenate
   @param ... list of strings to concatenate. Last one must be NULL.
   @returns a newly allocated string containing all the input strings
            concatenated.
 */
RM_LIBRARY_IMPORT_EXPORT RMascii * RMCatAscii(const RMascii* str1, ...);

///
/**
   copy src at the end of dest.
 */
RM_LIBRARY_IMPORT_EXPORT void RMAppendAscii (RMascii *dest, const RMascii *src);

///
/**
   XXX: should not be used.
   free the corresponding string.
 */
RM_LIBRARY_IMPORT_EXPORT void RMFreeAscii (RMascii *string);

///
/**
   copy in lowStr a low-case version of str.
 */
RM_LIBRARY_IMPORT_EXPORT void RMasciiToLower (const RMascii *str, RMascii *lowStr);

///
/**
   @returns the low-case version of character.
 */
RM_LIBRARY_IMPORT_EXPORT RMascii RMasciiCharacterToLower (RMascii character);

///
/**
   copy in upperStr an upper-case version of str.
 */
RM_LIBRARY_IMPORT_EXPORT void RMasciiToUpper (const RMascii *str, RMascii *upperStr);

///
/**
   @returns the upper-case version of character.
 */
RM_LIBRARY_IMPORT_EXPORT RMascii RMasciiCharacterToUpper (RMascii character);


/**
   translate in string str all occurences of character &lt;in> in character &lt;out>.  
*/
RM_LIBRARY_IMPORT_EXPORT void RMTranslateAscii(RMascii *str, RMascii in, RMascii out);

///
/**
   @param str string to parse.
   @param value the value the string represents. Contains zero if the input 
          string could not be parsed.
 */
RM_LIBRARY_IMPORT_EXPORT void RMasciiToUInt8 (const RMascii *str, RMuint8 *value);

///
/**
   @param str string to parse.
   @param value the value the string represents. Contains zero if the input 
          string could not be parsed.
 */
RM_LIBRARY_IMPORT_EXPORT void RMasciiToUInt16 (const RMascii *str, RMuint16 *value);

///
/**
   @param str string to parse.
   @param value the value the string represents. Contains zero if the input 
          string could not be parsed.
 */
RM_LIBRARY_IMPORT_EXPORT void RMasciiToInt32(const RMascii *str, RMint32 *value);

///
/**
   @param str string to parse.
   @param value the value the string represents. Contains zero if the input 
          string could not be parsed.
 */
RM_LIBRARY_IMPORT_EXPORT void RMasciiToUInt32(const RMascii *str, RMuint32 *value);

///
/**
   @param str string to parse.
   @param value the value the string represents. Contains zero if the input 
          string could not be parsed.
 */
RM_LIBRARY_IMPORT_EXPORT void RMasciiToInt64(const RMascii *str, RMint64 *value);
RM_LIBRARY_IMPORT_EXPORT void RMasciiToUInt64(const RMascii *str, RMuint64 *value);

///
/**
   @param str string to parse.
   @param value the value the string represents. Contains zero if the input 
          string could not be parsed.
 */
RM_LIBRARY_IMPORT_EXPORT void RMasciiToReal(const RMascii *str, RMreal *value);

///
/**
   @param str hexadecimal string to parse.
   @param value the value the string represents. Contains zero if the input 
          string could not be parsed.
 */
RM_LIBRARY_IMPORT_EXPORT void RMasciiHexToUint16(const RMascii *str, RMuint16 *value);
RM_LIBRARY_IMPORT_EXPORT void RMasciiHexToUint32(const RMascii *str, RMuint32 *value);
RM_LIBRARY_IMPORT_EXPORT void RMasciiHexToUint64(const RMascii *str, RMuint64 *value);

///
/**
   @param str the string to parse.
   @param token the token to find.
   @param tokenized_str an allocated string, large enough to contain the input string. Will be
			used to store the extracted string
   @param location a pointer to the first character AFTER the token within the input string
			(can point to an empty string). Can be used as the input in subsequent
			calls to continue tokenizing the string. A NULL value is valid and will
			simply result in location not being used.

   @return TRUE if the token was found, FALSE otherwise

   Example Usage :
   while ( RMTokenizeAscii( string, '.', tokenized, &location) ) {
	RMDBGLOG((ENABLE, "Got Token %s\n", tokenized));
	first_str = location;
   }
   RMDBGLOG((ENABLE, "Remaining Data %s\n", tokenized));
 */
RMbool RMTokenizeAscii (const RMascii *str, RMascii token, RMascii *tokenized_str, const RMascii **location);

///
/**
   @param str the string to parse.
   @param character the character to find.
   @param location a pointer to the first occurence of the character
              within the input string.
 */
RM_LIBRARY_IMPORT_EXPORT RMbool RMFindAsciiCharacter (const RMascii *str, 
						      RMascii character, 
						      RMascii **location);
///
/**
   Returns the offset possition of the searched string in the original string (case sensitive)

   @param str the string to parse.
   @param stringToFind the string to find.
   @param location a pointer to the first occurence of the string to find
              within the input string.
   @return -1 if the string is not found, or the position inside the main string of the substring
 */
RM_LIBRARY_IMPORT_EXPORT RMint32 RMFindAsciiString (const RMascii *str, 
						    const RMascii *stringToFind, 
						    RMascii **location);

///
/**
   Returns the offset possition of the searched string in the original
   string (case insensitive)

   @param str the string to parse.
   @param stringToFind the string to find.
   @param location a pointer to the first occurence of the string to find
              within the input string.
   @return -1 if the string is not found, or the position inside the main string of the substring
 */
RM_LIBRARY_IMPORT_EXPORT RMint32 RMFindAsciiStringCaseInsensitively(const RMascii *str, 
								    const RMascii *stringToFind, 
								    RMascii **location);

///
/**
   check if a byte is a digit character or not

   @param c     
   @return TRUE if c >= '0' and c <= '9', FALSE otherwise
*/

RM_LIBRARY_IMPORT_EXPORT RMbool RMasciiCharacterIsDigit (RMuint8 c);


/// 
/**
   convert an ascii character into the corresonding hexa value.
   example : 'F' will become 0xF

   @param c     
   @return value in hexa of 'c' symbol
*/

RM_LIBRARY_IMPORT_EXPORT RMstatus RMasciiHexCharacterToUInt8(RMascii c, RMuint8 *value);

///
/**
   @param str hexadecimal or decimal string to parse.
   @param value the value the string represents. Contains zero if the input 
          string could not be parsed.
   @return RM_OK if OK, or RM_FATALINVALIDPOINTER if on of the input pointer is NULL
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMasciiAutoToUint16(const RMascii *str, RMuint16 *value);
RM_LIBRARY_IMPORT_EXPORT RMstatus RMasciiAutoToUint32(const RMascii *str, RMuint32 *value);
RM_LIBRARY_IMPORT_EXPORT RMstatus RMasciiAutoToUint64(const RMascii *str, RMuint64 *value);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMASCII_H__
