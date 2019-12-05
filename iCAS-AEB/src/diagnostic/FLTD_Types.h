

#if !defined _FLTD_TYPES_
#define _FLTD_TYPES_

typedef unsigned char      	FLTD_BOOL;    /* BOOL datatype */
typedef unsigned char      	FLTD_U8;      /* Unsigned 8Bit datatype */
typedef signed char       	FLTD_S8;      /* Signed 8Bit datatype */
typedef unsigned  int    	FLTD_U16;     /* Unsigned 16Bit datatype */
typedef signed  int      	FLTD_S16;     /* Signed 16Bit datatype */
typedef unsigned long      	FLTD_U32;     /* Unsigned 32Bit datatype */
typedef signed long        	FLTD_S32;     /* Signed 32Bit datatype */

typedef unsigned char *    	FLTD_PU8;     /* Pointer to 8Bit datatype */
typedef signed char *      	FLTD_PS8;     /* Pointer to signed 8Bit datatype */
typedef unsigned  int *  	FLTD_PU16;    /* Pointer to unsigned 16Bit datatype */
typedef signed  int *    	FLTD_PS16;    /* Pointer to signed 16Bit datatype */
typedef unsigned long  *   	FLTD_PU32;    /* Pointer to unsigned 32Bit datatype */
typedef signed long  *     	FLTD_PS32;    /* Pointer to signed 32Bit datatype */


#ifndef NULL
	#define NULL		  	0u
#endif

#ifndef FALSE
	#define FALSE		 	(FLTD_BOOL)0u
#endif
#ifndef TRUE
	#define TRUE		   	(FLTD_BOOL)1u
#endif

#ifndef STD_OFF
	#define STD_OFF		   	(FLTD_BOOL)0u
#endif
#ifndef STD_ON
	#define STD_ON         	(FLTD_BOOL)1u
#endif

#ifndef STD_LOW
	#define STD_LOW		  	(FLTD_BOOL)0u
#endif
#ifndef STD_HIGH
	#define STD_HIGH      	(FLTD_BOOL)1u
#endif

#endif   /* _FLTD_TYPES_*/
