/*
 * ccp_interface.h
 *
 *  Created on: 2015-5-21
 *      Author: zhangguangyao
 */
#include "ccppar.h"

#ifndef CCP_INTERFACE_H_
#define CCP_INTERFACE_H_

#define BSWAP_32(x) \
    (INT32U)((((INT32U)(x) & 0xff000000) >> 24) | \
              (((INT32U)(x) & 0x00ff0000) >> 8) | \
              (((INT32U)(x) & 0x0000ff00) << 8) | \
              (((INT32U)(x) & 0x000000ff) << 24) \
             )

BYTE ccpSend( BYTEPTR msg );
MTABYTEPTR ccpGetPointer( BYTE addr_ext, DWORD addr );

void ccpUserBackground( void );

void disable_interrupt();                                // I-bit SET
void enable_interrupt();                                 // I-bit CLEAR
// ------------------------------------------------------------------------

#endif /* CCP_INTERFACE_H_ */
