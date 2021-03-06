/*****************************************************************************
 *   type.h:  Type definition Header file for NXP LPC17xx Family
 *   Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.25  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/

#ifndef __TYPE_H__
#define __TYPE_H__


#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef CONST
#define CONST    const
#endif


#ifndef false
#define false   (0)
#endif

#ifndef true
#define true    (1)
#endif


/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef char			CHAR;
typedef signed char		SCHAR;
typedef unsigned char	UCHAR;
typedef unsigned char   uchar;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WCHAR;
#if !defined(DEBUGBYPC)
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
#endif
/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

#pragma pack(1)

/**************Attributes for graphics:***********************************
    图片的头部为文本数据,其字节数总数为 (cLabels) * (cByteALine + 1);
文本的存储格式为: cByteALine个字节为字符数据,其后紧跟一个字节标示有效字符个数
Graphic:Offset_of_Dots = (cLabels) * (cByteALine + 1);图像点阵在图片中的位置
Graphic:Size_In_Bytes = cGrapSize-Offset_of_Dots;   图像点阵的字节数
Graphic:Width_In_Bytes = cGrapCols*cWidthAChar/8;   每行图像点阵的字节数
Graphic:Dots_Line_Max = Size_In_Bytes / Width_In_Bytes; 图像点阵行数
************************************************************************/
struct GRAPH_DEFINE
{
    unsigned short cGrapCols;   // 图片宽度(以字符单位,每个字符的宽度为cWidthAChar)
    unsigned short cLabels;     // 图片中包含的叠加文字行数
    unsigned short cPrintAt;    // 图片默认打印位置
    unsigned short cWidthAChar; // 单个字符的宽度(点数)
    unsigned short cHighAChar;  // 字符点阵高度(暂时没有使用)
    unsigned short cByteALine;  // 如果图片叠加字符串,为字符串的宽度(以字符单位),最多24个字符
    unsigned long cGrapSize;    // 图像数据字节数=图像点阵字节数+(cByteALine+1)*cLabels
                                // 图像点阵开始位置为:(cByteALine+1)*cLabels
};

/********************************************************************
    老收款机图片.GRB的文件头数据,无叠加文字时,没有6,7,8,9四行(5字节).
********************************************************************/
struct GRB_DEFINE
{
    BYTE cTextFlag;         //0 有无文本的标志，#80h表示有
    BYTE cWidth;            //1 图形宽度，字节数
    BYTE cHeight;           //2 图形行数，实际高度为cHeight*cHighAChar点行
    BYTE cPrintAt;          //3 图形打印位置(离左边界距离)
    BYTE cLabels;           //4 图形中字符行数
    WORD cTextOffset;       //5,6 文本区的地址
    BYTE cHighAChar;        //7 行高，点数
    WORD cGraSize;          //8,9 附加:图像点阵字节数
    char cName[128];        //10 文件名结束符
};
#pragma pack(4)
///////////////////////////////////////////////////////////////

#define BIT0	0x00000001
#define BIT1	0x00000002
#define BIT2	0x00000004
#define BIT3	0x00000008
#define BIT4	0x00000010
#define BIT5	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT8	0x00000100
#define BIT9	0x00000200
#define BIT10	0x00000400
#define BIT11	0x00000800
#define BIT12	0x00001000
#define BIT13	0x00002000
#define BIT14	0x00004000
#define BIT15	0x00008000
#define BIT16	0x00010000L
#define BIT17	0x00020000L
#define BIT18	0x00040000L
#define BIT19	0x00080000L
#define BIT20	0x00100000L
#define BIT21	0x00200000L
#define BIT22	0x00400000L
#define BIT23	0x00800000L
#define BIT24	0x01000000L
#define BIT25	0x02000000L
#define BIT26	0x04000000L
#define BIT27	0x08000000L
#define BIT28	0x10000000L
#define BIT29	0x20000000L
#define BIT30	0x40000000L
#define BIT31	0x80000000L

#define BIT(w,i)	    (w & (i))       //test bit on w
#define SETBIT(w,i)	    (w |= (i))      //set bit on w
#define CLRBIT(w,i)	    (w &= ~(i))     //clear bit on w
#define INVBIT(w,i)	    (w ^= (i))      //incert bit on w

#endif  /* __TYPE_H__ */
