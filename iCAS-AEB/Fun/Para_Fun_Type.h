/*
 * Para_Fun_Type.h
 *
 *  Created on: 2015-5-21
 *      Author: zhangguangyao
 */

#ifndef PARA_FUN_TYPE_H_
#define PARA_FUN_TYPE_H_

#ifndef TRUE
	#define TRUE  (1U)
#endif

#ifndef FALSE
	#define FALSE (0U)
#endif

#ifndef ENABLE
	#define ENABLE TRUE
#endif

#ifndef DISABLE
	#define DISABLE FALSE
#endif

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned int   INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   int   INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */
#endif /* PARA_FUN_TYPE_H_ */
