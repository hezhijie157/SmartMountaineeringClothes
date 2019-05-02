#ifndef __PICLIB_H
#define __PICLIB_H	  

#include "malloc.h"

#define PIC_FORMAT_ERR		0x27	//��ʽ����
#define PIC_SIZE_ERR		0x28	//ͼƬ�ߴ����
#define PIC_WINDOW_ERR		0x29	//�����趨����
#define PIC_MEM_ERR			0x11	//�ڴ����


void *pic_memalloc (u32 size);	//pic�����ڴ�
void pic_memfree (void* mf);	//pic�ͷ��ڴ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif






























