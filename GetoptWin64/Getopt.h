/* Getopt for Microsoft C  
This code is a modification of the Free Software Foundation, Inc. 
Getopt library for parsing command line argument the purpose was
to provide a Microsoft Visual C friendly derivative. This code
provides functionality for both Unicode and Multibyte builds.

Date: 02/03/2011 - Ludvik Jerabek - Initial Release
Version: 1.0
Comment: Supports getopt, getopt_long, and getopt_long_only
and POSIXLY_CORRECT environment flag
License: LGPL

Revisions:

02/03/2011 - Ludvik Jerabek - Initial Release
02/20/2011 - Ludvik Jerabek - Fixed compiler warnings at Level 4
07/05/2011 - Ludvik Jerabek - Added no_argument, required_argument, optional_argument defs
08/03/2011 - Ludvik Jerabek - Fixed non-argument runtime bug which caused runtime exception
08/09/2011 - Ludvik Jerabek - Added code to export functions for DLL and LIB
02/15/2012 - Ludvik Jerabek - Fixed _GETOPT_THROW definition missing in implementation file
08/01/2012 - Ludvik Jerabek - Created separate functions for char and wchar_t characters so single dll can do both unicode and ansi
06/12/2019 - Jiri Jaros     - Removed register variables - deprecated in VS 2017

**DISCLAIMER**
THIS MATERIAL IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING, BUT Not LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE, OR NON-INFRINGEMENT. SOME JURISDICTIONS DO NOT ALLOW THE
EXCLUSION OF IMPLIED WARRANTIES, SO THE ABOVE EXCLUSION MAY NOT
APPLY TO YOU. IN NO EVENT WILL I BE LIABLE TO ANY PARTY FOR ANY
DIRECT, INDIRECT, SPECIAL OR OTHER CONSEQUENTIAL DAMAGES FOR ANY
USE OF THIS MATERIAL INCLUDING, WITHOUT LIMITATION, ANY LOST
PROFITS, BUSINESS INTERRUPTION, LOSS OF PROGRAMS OR OTHER DATA ON
YOUR INFORMATION HANDLING SYSTEM OR OTHERWISE, EVEN If WE ARE
EXPRESSLY ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
*/
#ifndef __GETOPT_H_
#define __GETOPT_H_

#ifdef _GETOPT_API
#undef _GETOPT_API
#endif

#if defined(EXPORTS_GETOPT) && defined(STATIC_GETOPT)
#error "The preprocessor definitions of EXPORTS_GETOPT and STATIC_GETOPT can only be used individually"
#elif defined(STATIC_GETOPT)
#pragma message("Warning static builds of getopt violate the Lesser GNU Public License")
#define _GETOPT_API
#elif defined(EXPORTS_GETOPT)
#pragma message("Exporting getopt library")
#define _GETOPT_API __declspec(dllexport)	
#else
#pragma message("Importing getopt library")
#define _GETOPT_API __declspec(dllimport)
#endif


#include <string.h>
#include <wchar.h>

// Standard GNU options
#define	null_argument		0 /*Argument Null*/
#define	no_argument			0 /*Argument Switch Only*/
#define required_argument	1 /*Argument Required*/
#define optional_argument	2 /*Argument Optional*/

// Shorter Versions of options
#define ARG_NULL 0 /*Argument Null*/
#define ARG_NONE 0 /*Argument Switch Only*/
#define ARG_REQ 1  /*Argument Required*/
#define ARG_OPT 2  /*Argument Optional*/

// Change behavior for C\C++
#ifdef __cplusplus
#define _BEGIN_EXTERN_C extern "C" {
#define _END_EXTERN_C }
#define _GETOPT_THROW throw()
#else
#define _BEGIN_EXTERN_C
#define _END_EXTERN_C
#define _GETOPT_THROW
#endif

_BEGIN_EXTERN_C

extern char *optarg_a;
extern wchar_t *optarg_w;
extern int optind;
extern int opterr;
extern int optopt;

// Ansi
struct option_a
{
	const char* name;
	int has_arg;
	int *flag;
	char val;
};

// Unicode
struct option_w
{
	const wchar_t* name;
	int has_arg;
	int *flag;
	wchar_t val;
};

// Ansi
int getopt_a(int argc, char *const *argv, const char *optstring) _GETOPT_THROW;
int getopt_long_a(int ___argc, char *const *___argv, const char *__shortopts, const struct option_a *__longopts, int *__longind) _GETOPT_THROW;
int getopt_long_only_a(int ___argc, char *const *___argv, const char *__shortopts, const struct option_a *__longopts, int *__longind) _GETOPT_THROW;

// Unicode
int getopt_w(int argc, wchar_t *const *argv, const wchar_t *optstring) _GETOPT_THROW;
int getopt_long_w(int ___argc, wchar_t *const *___argv, const wchar_t *__shortopts, const struct option_w *__longopts, int *__longind) _GETOPT_THROW;
int getopt_long_only_w(int ___argc, wchar_t *const *___argv, const wchar_t *__shortopts, const struct option_w *__longopts, int *__longind) _GETOPT_THROW;

#ifdef _UNICODE
	#define getopt getopt_w
	#define getopt_long getopt_long_w
	#define getopt_long_only getopt_long_only_w
	#define option option_w
	#define optarg optarg_w
#else
	#define getopt getopt_a
	#define getopt_long getopt_long_a
	#define getopt_long_only getopt_long_only_a
	#define option option_a
	#define optarg optarg_a
#endif

_END_EXTERN_C

// Undefine so the macros are not included
#undef _BEGIN_EXTERN_C
#undef _END_EXTERN_C
#undef _GETOPT_THROW
#undef _GETOPT_API

#endif  // __GETOPT_H_