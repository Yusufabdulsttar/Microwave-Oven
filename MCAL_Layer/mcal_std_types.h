/* 
 * File:   mcal_std_types.h
 * Author: yusuf
 *
 * Created on April 16, 2023, 2:39 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H
#define _XTAL_FREQ 8000000
/* section : Includes   */

#include "compiler.h"
#include "std_libraries.h"


/* section : Macro Function Declaration  */

/* section : Data Type Declaration  */
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long    uint32;
typedef signed char     sint8;
typedef signed short    sint16;
typedef signed long      sint32;

typedef uint8 Std_ReturnType;

/* section : Macro Declaration  */
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define E_OK            (Std_ReturnType)0x01
#define E_NOT_OK        (Std_ReturnType)0x00


/* section : Function Declaration  */


#endif	/* MCAL_STD_TYPES_H */

