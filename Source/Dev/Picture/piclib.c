#include "config.h"
#include "piclib.h"



void *pic_memalloc (u32 size)			
{
	return (void*)mymalloc(SRAMIN,size);
}
//�ͷ��ڴ�
void pic_memfree (void* mf)		 
{
	myfree(SRAMIN,mf);
}























