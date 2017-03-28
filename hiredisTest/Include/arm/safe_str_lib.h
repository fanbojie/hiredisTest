/*------------------------------------------------------------------
* safe_str_lib.h -- Safe C Library String APIs
*
* October 2008, Bo Berry
*
* Copyright (c) 2008, 2009 Cisco Systems, Inc.
*
* Permission is hereby granted, free of charge, to any person 
* obtaining a copy of this software and associated documentation 
* files (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, 
* publish, distribute, sublicense, and/or sell copies of the Software, 
* and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be 
* included in all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*------------------------------------------------------------------
*/


#ifndef __SAFE_STR_LIB_H__
#define __SAFE_STR_LIB_H__


/* This include file is used to promote portability to other environments */
#include "safe_lib.h"



/*
* The shortest string is a null string!! 
*/
#ifndef RSIZE_MIN_STR 
#define RSIZE_MIN_STR      ( 1 )
#endif


/*
* CONFIGURE: maximum sring length
*/
#ifndef RSIZE_MAX_STR 
#define RSIZE_MAX_STR      ( 0xFFFFFFFF ) //4096
#endif


/*
* CONFIGURE: The makeup of a password 
*/
#define SAFE_STR_MIN_LOWERCASE     ( 2 )
#define SAFE_STR_MIN_UPPERCASE     ( 2 )
#define SAFE_STR_MIN_NUMBERS       ( 1 )
#define SAFE_STR_MIN_SPECIALS      ( 1 )

#ifndef SAFE_STR_PASSWORD_MIN_LENGTH 
#define SAFE_STR_PASSWORD_MIN_LENGTH   ( 6 )
#endif

#ifndef SAFE_STR_PASSWORD_MAX_LENGTH 
#define SAFE_STR_PASSWORD_MAX_LENGTH   ( 32 )
#endif
#ifdef __cplusplus
extern "C"
{
#endif


	/* string compare */
	extern errno_t
		strcasecmp_s(const char *dest, rsize_t dmax, 
		const char *src, int *indicator);


	/* find a substring _ case insensitive */ 
	extern errno_t
		strcasestr_s(char *dest, rsize_t dmax, 
		const char *src, rsize_t slen, char **substring);


	/* string concatenate */
	extern errno_t
		strcat_s(char *dest, rsize_t dmax, const char *src);


	/* string compare */
	extern errno_t
		strcmp_s(const char *dest, rsize_t dmax, 
		const char *src, int *indicator);


	/* fixed field string compare */
	extern errno_t
		strcmpfld_s(const char *dest, rsize_t dmax,
		const char *src, int *indicator);


	/* string copy */
	extern errno_t
		strcpy_s(char *dest, rsize_t dmax, const char *src);


	/* fixed char array copy */
	extern errno_t
		strcpyfld_s(char *dest, rsize_t dmax, const char *src, rsize_t slen);


	/* copy from a null terminated string to fixed char array */
	extern errno_t
		strcpyfldin_s(char *dest, rsize_t dmax, const char *src, rsize_t slen);


	/* copy from a char array to null terminated string */
	extern errno_t
		strcpyfldout_s(char *dest, rsize_t dmax, const char *src, rsize_t slen);


	/* computes excluded prefix length */ 
	extern errno_t
		strcspn_s(const char *dest, rsize_t dmax,
		const char *src,  rsize_t slen, rsize_t *count); 


	/* returns a pointer to the first occurrence of c in dest */ 
	extern errno_t
		strfirstchar_s(char *dest, rsize_t dmax, char c, char **first); 


	/* returns index of first difference */ 
	extern  errno_t
		strfirstdiff_s(const char *dest, rsize_t dmax, 
		const char *src, rsize_t *index);


	/* validate alphanumeric string */ 
	extern boolean
		strisalphanumeric_s(const char *str, rsize_t slen);  


	/* validate ascii string */ 
	extern boolean
		strisascii_s(const char *str, rsize_t slen);  


	/* validate string of digits */ 
	extern boolean
		strisdigit_s(const char *str, rsize_t slen);  


	/* validate hex string */ 
	extern boolean
		strishex_s(const char *str, rsize_t slen);  


	/* validate lower case */ 
	extern boolean
		strislowercase_s(const char *str, rsize_t slen); 


	/* validate mixed case */ 
	extern boolean
		strismixedcase_s(const char *str, rsize_t slen); 


	/* validate password */ 
	extern boolean
		strispassword_s(const char *str, rsize_t slen);  


	/* validate upper case */ 
	extern boolean
		strisuppercase_s(const char *str, rsize_t slen); 


	/* returns  a pointer to the last occurrence of c in s1 */
	extern errno_t
		strlastchar_s(char *str, rsize_t smax, char c, char **first);


	/* returns index of last difference */
	extern  errno_t
		strlastdiff_s(const char *dest, rsize_t dmax, 
		const char *src, rsize_t *index);


	/* left justify */
	extern errno_t
		strljustify_s(char *dest, rsize_t dmax); 


	/* fitted string concatenate */
	extern errno_t
		strncat_s(char *dest, rsize_t dmax, const char *src, rsize_t slen);


	/* fitted string copy */
	extern errno_t
		strncpy_s(char *dest, rsize_t dmax, const char *src, rsize_t slen);


	/* string length */
	extern rsize_t
		strnlen_s (const char *s, rsize_t s1max);


	/* get pointer to first occurrence from set of char */ 
	extern errno_t
		strpbrk_s(char *dest, rsize_t dmax,
		char *src,  rsize_t slen, char **first);  


	/* searches for a prefix */ 
	extern errno_t
		strprefix_s(const char *dest, rsize_t dmax, const char *src);


	/* removes leading and trailing white space */ 
	extern errno_t
		strremovews_s(char *dest, rsize_t dmax); 


	/* computes inclusive prefix length */ 
	extern errno_t
		strspn_s(const char *dest, rsize_t dmax,
		const char *src,  rsize_t slen, rsize_t *count); 


	/* find a substring */ 
	extern errno_t
		strstr_s(char *dest, rsize_t dmax, 
		const char *src, rsize_t slen, char **substring);


#ifndef __STDC_WANT_SECURE_LIB__ 
	/* string tokenizer */
	extern char * 
		strtok_s(char *s1, rsize_t *s1max, char *s2, char **ptr);
#endif

	/* convert string to lowercase */ 
	extern errno_t
		strtolowercase_s(char *str, rsize_t slen); 


	/* convert string to uppercase */ 
	extern errno_t
		strtouppercase_s(char *str, rsize_t slen); 


	/* zero an entire string with nulls */
	extern errno_t
		strzero_s(char *dest, rsize_t dmax); 

	/* wide string copy */
	extern errno_t
		wcscpy_s(wchar_t *dest, rsize_t dmax, const wchar_t *src);

	/* fitted wide string copy */
	extern errno_t 
		wcsncpy_s(wchar_t *dest, rsize_t dmax, const wchar_t *src, rsize_t slen);

	/* string concatenate */
	extern errno_t
		wcscat_s (wchar_t *dest, rsize_t dmax, const wchar_t *src);

	/* fitted string concatenate */
	extern errno_t
		wcsncat_s (wchar_t *dest, rsize_t dmax, const wchar_t *src, rsize_t slen);

#ifndef __STDC_WANT_SECURE_LIB__ 
	/* string token */
	extern wchar_t *
		wcstok_s (wchar_t *dest, rsize_t *dmax, wchar_t *src, wchar_t **ptr);
#endif
	
	/* find a substring */ 
	extern errno_t
		wcsstr_s(wchar_t *dest, rsize_t dmax, const wchar_t *src, rsize_t slen, wchar_t **substring);

	/* wide string compare */
	extern errno_t 
		wcscmp_s(const wchar_t *dest, rsize_t dmax,const wchar_t *src, int *indicator);

	/* wide string compare case insensitive*/
	extern errno_t 
		wcsicmp_s(const wchar_t *dest, rsize_t dmax,const wchar_t *src, int *indicator);

	/* validate alphanumeric string*/
	extern boolean
		wcsisalphanumeric_s(const wchar_t *dest, rsize_t dmax);

	/* validate ascii string */
	extern boolean
		wcsisascii_s(const wchar_t *dest, rsize_t dmax);

	/* validate digit string*/
	extern boolean
		wcsisdigit_s(const wchar_t *dest, rsize_t dmax);

	/* validate hex string*/
	extern boolean 
		wcsishex_s(const wchar_t *dest, rsize_t dmax);

	/* find a char */ 
	extern errno_t 
		wcschr_s(wchar_t *dest, rsize_t dmax, const wchar_t ch, wchar_t **substring);

	extern errno_t 
		wcsrchr_s(wchar_t *dest, rsize_t dmax, const wchar_t ch, wchar_t **substring);

	/* counted wide string compare */
	extern errno_t 
		wcsncmp_s(const wchar_t *dest,const wchar_t *src,  rsize_t n,int *indicator);

	/* counted wide string compare case insensitive*/
	extern errno_t 
		wcsnicmp_s(const wchar_t *dest,const wchar_t *src,rsize_t n,int *indicator);

	/* string length */
	rsize_t
		wcsnlen_s (const wchar_t *dest, rsize_t dmax);

#ifdef __cplusplus
};
#endif

#endif   /* __SAFE_STR_LIB_H__ */

