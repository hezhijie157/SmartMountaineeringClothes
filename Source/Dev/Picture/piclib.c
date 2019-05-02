#include "config.h"
#include "piclib.h"



void *pic_memalloc (u32 size)			
{
	return (void*)mymalloc(SRAMIN,size);
}
//ÊÍ·ÅÄÚ´æ
void pic_memfree (void* mf)		 
{
	myfree(SRAMIN,mf);
}























