

#ifndef _FLT_TYPES_
#define _FLT_TYPES_

typedef unsigned char      	FLT_BOOL;    /* BOOL datatype */
typedef unsigned char      	FLT_U8;      /* Unsigned 8Bit datatype */
typedef signed char       	FLT_S8;      /* Signed 8Bit datatype */
typedef unsigned  int    	FLT_U16;     /* Unsigned 16Bit datatype */
typedef signed  int      	FLT_S16;     /* Signed 16Bit datatype */
typedef unsigned long      	FLT_U32;     /* Unsigned 32Bit datatype */
typedef signed long        	FLT_S32;     /* Signed 32Bit datatype */

typedef unsigned char *    	FLT_PU8;     /* Pointer to 8Bit datatype */
typedef signed char *      	FLT_PS8;     /* Pointer to signed 8Bit datatype */
typedef unsigned  int *  	FLT_PU16;    /* Pointer to unsigned 16Bit datatype */
typedef signed  int *    	FLT_PS16;    /* Pointer to signed 16Bit datatype */
typedef unsigned long  *   	FLT_PU32;    /* Pointer to unsigned 32Bit datatype */
typedef signed long  *     	FLT_PS32;    /* Pointer to signed 32Bit datatype */


#ifndef NULL
	#define NULL		  	0u
#endif

#ifndef FALSE
	#define FALSE		 	(FLT_BOOL)0u
#endif
#ifndef TRUE
	#define TRUE		   	(FLT_BOOL)1u
#endif

#ifndef STD_OFF
	#define STD_OFF		   	(FLT_BOOL)0u
#endif
#ifndef STD_ON
	#define STD_ON         	(FLT_BOOL)1u
#endif

#ifndef STD_LOW
	#define STD_LOW		  	(FLT_BOOL)0u
#endif
#ifndef STD_HIGH
	#define STD_HIGH      	(FLT_BOOL)1u
#endif

#endif   /* _FLTD_TYPES_*/
