#ifndef __PICLIB_H
#define __PICLIB_H	  

#include "malloc.h"

#define PIC_FORMAT_ERR		0x27	//格式错误
#define PIC_SIZE_ERR		0x28	//图片尺寸错误
#define PIC_WINDOW_ERR		0x29	//窗口设定错误
#define PIC_MEM_ERR			0x11	//内存错误


void *pic_memalloc (u32 size);	//pic申请内存
void pic_memfree (void* mf);	//pic释放内存
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif






























