#include "piclib.h"
#include "bmp.h"
#include "ff.h"
#include "string.h"
#include "exfuns.h"
#include "ov7725.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//ͼƬ���� ��������-bmp���벿��	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/15
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//����˵�� 
//V1.1 20140722
//�޸�minibmp_decode����,ʹͼƬ���趨�������������ʾ
//////////////////////////////////////////////////////////////////////////////////

//��ʹ���ڴ����
#if BMP_USE_MALLOC == 0	
FIL f_bfile;
u8 bmpreadbuf[BMP_DBUF_SIZE];
#endif 				    

 //�ļ������������⸲�ǣ�
//��ϳ�:����"0:PHOTO/PIC13141.bmp"���ļ���
void camera_new_pathname(u8 *pname)
{	 
	u8 res;					 
	u16 index=0;
	while(index<0XFFFF)
	{
//  	sprintf((char*)pname,"PIC%05d.bmp",index);
   	sprintf((char*)pname,"0:PHOTO/PIC%05d.bmp",index);
		res=f_open(ftemp,(const TCHAR*)pname,FA_READ);//���Դ�����ļ�
		if(res==FR_NO_FILE)break;		//���ļ���������=����������Ҫ��.
		index++;
	}
}	


//BMP���뺯��
//����ǰLCD��Ļ��ָ�������ͼ,��Ϊ16λ��ʽ��BMP�ļ� RGB565��ʽ.
//����Ϊrgb565����Ҫ����,��Ҫ����ԭ���ĵ�ɫ��λ����������.���������Ѿ�����������.
//����Ϊrgb555��ʽ����Ҫ��ɫת��,��ʱ��ȽϾ�,���Ա���Ϊ565������ٵİ취.
//filename:���·��
//x,y:����Ļ�ϵ���ʼ����  
//mode:ģʽ.0,�����������ļ��ķ�ʽ����;1,���֮ǰ�����ļ�,�򸲸�֮ǰ���ļ�.���û��,�򴴽��µ��ļ�.
//����ֵ:0,�ɹ�;����,������.  
u8 bmp_encode(u8 *filename,u16 x,u16 y,u16 width,u16 height,u8 mode)
{				
	FIL* f_bmp;
	u16 bmpheadsize;			//bmpͷ��С	   	
 	BITMAPINFO hbmp;			//bmpͷ	 
	u8 res=0;
	u16 tx,ty;				   	//ͼ��ߴ�
	u16 *databuf;				//���ݻ�������ַ	   	
	u16 pixcnt;				   	//���ؼ�����
	u16 bi4width;		       	//ˮƽ�����ֽ���	
  u16 color;	//HZJ	
	if(width==0||height==0)return PIC_WINDOW_ERR;	//�������
//	if((x+width-1)>lcddev.width)return PIC_WINDOW_ERR;		//�������
//	if((y+height-1)>lcddev.height)return PIC_WINDOW_ERR;	//������� 
// 	if(width> 240 )return PIC_WINDOW_ERR;		//�������  //HZJ
//	if(height> 320)return PIC_WINDOW_ERR;	//�������   //HZJ
		if(width> 320 )return PIC_WINDOW_ERR;		//�������  //HZJ
	  if(height> 240)return PIC_WINDOW_ERR;	//�������   //HZJ
	
#if BMP_USE_MALLOC == 1	//ʹ��malloc	
	databuf=(u16*)pic_memalloc(1024);		//��������bi4width��С���ֽڵ��ڴ����� ,��240�����,480���ֽھ͹���.
	if(databuf==NULL)return PIC_MEM_ERR;		//�ڴ�����ʧ��.
	f_bmp=(FIL *)pic_memalloc(sizeof(FIL));	//����FIL�ֽڵ��ڴ����� 
	if(f_bmp==NULL)								//�ڴ�����ʧ��.
	{		 
		pic_memfree(databuf);
		return PIC_MEM_ERR;				
	} 	 
#else
	databuf=(u16*)bmpreadbuf;
	f_bmp=&f_bfile;
#endif	      
	bmpheadsize=sizeof(hbmp);//�õ�bmp�ļ�ͷ�Ĵ�С   
	mymemset((u8*)&hbmp,0,sizeof(hbmp));//��������뵽���ڴ�.	    
	hbmp.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);//��Ϣͷ��С
	hbmp.bmiHeader.biWidth=width;	 	//bmp�Ŀ��
	hbmp.bmiHeader.biHeight=height; 	//bmp�ĸ߶�
	hbmp.bmiHeader.biPlanes=1;	 		//��Ϊ1
	hbmp.bmiHeader.biBitCount=16;	 	//bmpΪ16λɫbmp
	hbmp.bmiHeader.biCompression=BI_BITFIELDS;//ÿ�����صı�����ָ�������������
 	hbmp.bmiHeader.biSizeImage=hbmp.bmiHeader.biHeight*hbmp.bmiHeader.biWidth*hbmp.bmiHeader.biBitCount/8;//bmp��������С
 				   
	hbmp.bmfHeader.bfType=((u16)'M'<<8)+'B';//BM��ʽ��־
	hbmp.bmfHeader.bfSize=bmpheadsize+hbmp.bmiHeader.biSizeImage;//����bmp�Ĵ�С
  hbmp.bmfHeader.bfOffBits=bmpheadsize;//����������ƫ��

	hbmp.RGB_MASK[0]=0X00F800;	 		//��ɫ����
	hbmp.RGB_MASK[1]=0X0007E0;	 		//��ɫ����
	hbmp.RGB_MASK[2]=0X00001F;	 		//��ɫ����

	if(mode==1)res=f_open(f_bmp,(const TCHAR*)filename,FA_READ|FA_WRITE);//���Դ�֮ǰ���ļ�
 	if(mode==0||res==0x04)res=f_open(f_bmp,(const TCHAR*)filename,FA_WRITE|FA_CREATE_NEW);//ģʽ0,���߳��Դ�ʧ��,�򴴽����ļ�		   
 	if((hbmp.bmiHeader.biWidth*2)%4)//ˮƽ����(�ֽ�)��Ϊ4�ı���
	{
		bi4width=((hbmp.bmiHeader.biWidth*2)/4+1)*4;//ʵ��Ҫд��Ŀ������,����Ϊ4�ı���.	
	}else bi4width=hbmp.bmiHeader.biWidth*2;		//�պ�Ϊ4�ı���	 
 	if(res==FR_OK)//�����ɹ�
	{
		res=f_write(f_bmp,(u8*)&hbmp,bmpheadsize,&bw);//д��BMP�ײ�  
		for(ty=height-1;hbmp.bmiHeader.biHeight;ty--)
		{
			pixcnt=0;
 			for(tx=0;pixcnt!=(bi4width/2);)
			{
				//�ڶ�����ǰ���븴λ��ָ�룬�ο�����
				//HZJ Begin
			OV7725_RCK_L;
			color =(u8) OV7725_DATA ;	//������
			OV7725_RCK_H; 
			color<<=8;  
			OV7725_RCK_L;
			color|= (u8)OV7725_DATA ;	//������
			OV7725_RCK_H; 
		  //HZJ  End
				
				if(pixcnt<hbmp.bmiHeader.biWidth)databuf[pixcnt]= color;//0xf800;////HZJ Want ADD!!!!  //LCD_ReadPoint(tx,ty);//��ȡ������ֵ 
				else databuf[pixcnt]=0Xffff;//�����ɫ������.  
				pixcnt++;
				tx++;
			}
			hbmp.bmiHeader.biHeight--;
      res=f_write(f_bmp,(u8*)databuf,bi4width,&bw);//д������
		}
	  f_close(f_bmp);
	}	    
#if BMP_USE_MALLOC == 1	//ʹ��malloc	
	pic_memfree(databuf);	 
	pic_memfree(f_bmp);		 
#endif	
	return res;
}



















