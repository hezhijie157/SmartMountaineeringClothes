#include "config.h"
char Uart1_Buf[UART1_BUF_LEN];//串口1接收缓存
u8 First_Int = 0;
char server_ip_port_cmd[45];
int reg;
/*************  本地变量声明	**************/
char error_result[20];

static char  *phone_num = "AT+CMGS=\"13055767056\""; //修改这里可以修改电话号码

int ret;

/*******************************************************************************
* 函数名 : Find
* 描述   : 查找串口1接收数组Uart1_Buf中是否有 “a”
*******************************************************************************/
u8 Find(char *a)
{ 
	if(strstr(Uart1_Buf, a)!=NULL)
	{
		return 1;
	}	
	else
	{
		return 0;
	}		
}

/*******************************************************************************
* 函数名 : CLR_Buf
* 描述   : 清除串口1缓存数据
*******************************************************************************/
void CLR_Buf(void)
{
	u16 k;
	for(k=0;k<UART1_BUF_LEN;k++)      //将缓存内容清零
	{
		Uart1_Buf[k] = 0x00;
	}
    First_Int = 0;              //接收字符串的起始存储位置
}

/*******************************************************************************
* 函数名 : UART1_Send_Command
* 描述   : 串口1发送命令
*******************************************************************************/
void UART1_Send_Command(char* s)
{
	CLR_Buf(); //清空接收数据的buffer
	UART1_SendBuffer(s); //发出字符串
	UART1_SendBuffer("\r\n"); //再自动发送 \r\n两个字符
}

/*******************************************************************************
* 函数名 : UART1_Send_AT_Command
* 描述   : 串口1发送AT相关命令
*******************************************************************************/
u8 UART1_Send_AT_Command(char *b,char *a,u8 wait_time,u32 interval_time)         
{
	u8 i;
	i = 0;
	while(i < wait_time)    //在等待时间内查看是否有应答。如果没有找到 就继续再发一次指令 再进行查找目标字符串                
	{
		UART1_Send_Command(b);//串口1发送 b 字符串 他会自动发送\r\n  相当于发送了一个指令
		Delay(interval_time); //等待一定时间 传50的话就是 50*20ms = 1秒
		if(Find(a))            //查找需要应答的字符串 a
		{
			return 1;
		}
		i++;
	}
	return 0;
}

/*******************************************************************************
* 函数名 : UART1_Send_Command_END
* 描述   : 串口1发送结束命令
*******************************************************************************/
void UART1_Send_Command_END(char *s)
{
	CLR_Buf(); //清空接收数据的buffer
	UART1_SendBuffer(s); //发出字符串
}

u8 UART1_Send_AT_Command_End(char *b,char *a,u8 wait_time,u32 interval_time)         
{
	u8 i;
	i = 0;
	while(i < wait_time)    //如果没有找到 就继续再发一次指令 再进行查找目标字符串                
	{
		UART1_Send_Command_END(b);//串口1发送 b 字符串 这里不发送\r\n 
		Delay(interval_time); //等待一定时间 传50的话就是 50*20ms = 1秒
		if(Find(a))            //查找需要应答的字符串 a
		{
			return 1;
		}
		i++;
	}
	
	return 0;
}

/*******************************************************************************
* 函数名 : Wait_CREG
* 描述   : 等待模块注册成功
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
u8 Wait_CREG(u8 query_times)
{
	u8 i;
	u8 k;
	u8 j;
	i = 0;
	CLR_Buf();
	while(i == 0)        			
	{

		UART1_Send_Command("AT+CREG?");
		Delay(100); 
		
		for(k=0;k<UART1_BUF_LEN;k++)      			
		{
			if((Uart1_Buf[k] == '+')&&(Uart1_Buf[k+1] == 'C')&&(Uart1_Buf[k+2] == 'R')&&(Uart1_Buf[k+3] == 'E')&&(Uart1_Buf[k+4] == 'G')&&(Uart1_Buf[k+5] == ':'))
			{
					 
				if((Uart1_Buf[k+7] == '1')&&((Uart1_Buf[k+9] == '1')||(Uart1_Buf[k+9] == '5')))
				{
					i = 1;
					return 1;
				}
				
			}
		}
		j++;
		if(j > query_times)
		{
			return 0;
		}
		
	}
	return 0;
}



/*******************************************************************************
* 函数名 : check_status
* 描述   : 检测通信状态
* 输入   :
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
int check_status(void)
{
	int ret;
	char esc_char[2];
	
	esc_char[0] = 0x1B;//退出字符
	esc_char[1] = '\0';
	
	ret = UART1_Send_AT_Command("AT","OK",5,50);//测试通信是否成功
	if(ret == 0)
	{
		UART1_SendBuffer(esc_char);//万一进入>状态，那么久发送一个ESC字符
		return COMMUNITE_ERROR;
	}
	
	ret = UART1_Send_AT_Command("AT+CPIN?","READY",3,50);//查询卡是否插上
	if(ret == 0)
	{
		return NO_SIM_CARD_ERROR;
	}
	
	ret = Wait_CREG(3);//查询卡是否注册到网络
	if(ret == 0)
	{
		return SIM_CARD_NO_REG_ERROR;
	}
    
    ret = UART1_Send_AT_Command("ATE0","OK",2,50);//关闭回显功能
	if(ret == 0)
	{
		return EAT0_ERROR;
	}
    
	return 1;
}
/*******************************************************************************
* 函数名 : send_text_config
* 描述   : 发送信息
* 输入   : *content  要发送的内容
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
int send_text_config(char *content)
{
	
	char end_char[2];
	end_char[0] = 0x1A;//结束字符
	end_char[1] = '\0';
	
	reg = UART1_Send_AT_Command("AT+CMGF=1","OK",5,50);//配置为TEXT模式
	if(!reg)
	{
		return AT_CMGF_ERROR;
	}
	
	reg = UART1_Send_AT_Command("AT+CSCS=\"GSM\"","OK",3,50);//设置字符格式
	if(reg == 0)
	{
		return AT_CSCS_ERROR;
	}
	
	reg = UART1_Send_AT_Command(phone_num,">",3,50);//输入收信人的电话号码
	if(reg == 0)
	{
		return AT_CMGS_ERROR;
	}
	
	UART1_SendBuffer(content);
	reg = UART1_Send_AT_Command_End(end_char,"OK",1,250);//发送结束符，等待返回ok,等待5S发一次，因为短信成功发送的状态时间比较长
	if(reg == 0)
	{
		return END_CHAR_ERROR;
	}
	
	return 1;
}



/*******************************************************************************
* 函数名 : SendText
* 描述   : 发送信息
* 输入   : *message  要发送的内容
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void SendText(char *message)
{
	u8  i;
		
	for(i = 0;i < STABLE_TIMES;i++)
	{
		Delay(50);
	}
	
	memset(error_result,'\0',20);

		Delay(50);
		
				ret = check_status();
				if(ret == 1)
				{
					ret = send_text_config(message);//发送TEXT短信
				}
				if(ret == 1)
				{
					DEBUG_PRINT("成功发送TEXT短信\r\n");
				}
				else
				{
					DEBUG_PRINT("短信发送失败，错误代码 : %d\r\n",ret);
				}
	
}
/*******************************************************************************
* 函数名 : send_data_to_server
* 描述   : TCP链接到服务器配置
* 输入   : *message  要发送的内容
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
int send_data_to_server(char *server_IP_and_port,char *content)
{
	u8 ret;
	char end_char[2];
	
	
	end_char[0] = 0x1A;//结束字符
	end_char[1] = '\0';
	
	ret = UART1_Send_AT_Command("AT+CIPSTATUS","CONNECT OK",3,50*2);//查询连接状态
	if(ret == 1)//说明服务器处于连接状态
	{
		ret = UART1_Send_AT_Command("AT+CIPSEND",">",3,50);//开发发送数据
		if(ret == 0)
		{
			return AT_CIPSEND_ERROR;
		}
		
		UART1_SendBuffer(content);
		
		ret = UART1_Send_AT_Command_End(end_char,"SEND OK",1,250);//发送结束符，等待返回ok,等待5S发一次，因为发送数据时间可能较长
		if(ret == 0)
		{
			return END_CHAR_ERROR;
		}
		
		return 1;
	}
	
	ret = UART1_Send_AT_Command("AT+CGATT=1","OK",3,50*20);//附着网络
	if(ret == 0)
	{
		return AT_CGATT_ERROR;
	}
	
	ret = UART1_Send_AT_Command("AT+CGACT=1,1","OK",3,50*2);//激活网络
	if(ret == 0)
	{
		return AT_CGATT1_ERROR;
	}

	memset(server_ip_port_cmd,'\0',45);
	strcpy(server_ip_port_cmd,"AT+CIPSTART=\"TCP\",");
	strcat(server_ip_port_cmd,server_IP_and_port);
	
	ret = UART1_Send_AT_Command(server_ip_port_cmd,"CONNECT OK",3,50*2);//连接服务器
	if(ret == 0)
	{
		return AT_CIPSTART_ERROR;
	}
	
	ret = UART1_Send_AT_Command("AT+CIPSEND",">",3,50);//开发发送数据
	if(ret == 0)
	{
		return AT_CIPSEND_ERROR;
	}
	
	UART1_SendBuffer(content);
	ret = UART1_Send_AT_Command_End(end_char,"SEND OK",1,250);//发送结束符，等待返回ok,等待5S发一次，因为发送数据时间可能较长
    
    if(ret == 0)
	{
		return END_CHAR_ERROR;
	}
	
	return 1;
}
/*******************************************************************************
* 函数名 : void SendTCP(void)
* 描述   : 发送到ip
* 输入   : IP_port ip地址和端口*message  要发送的内容
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void SendTCP(char *IP_port,char *message)
{
	u8  i;
	int  ret;
		
	for(i = 0;i < STABLE_TIMES;i++)
	{
		Delay(50);
	}
	
	memset(error_result,'\0',20);
	
		Delay(50);

		ret = check_status();
		if(ret == 1)
		{
//			ret = send_data_to_server("\"182.254.216.22\",8687","GA6 tcp test!");//发送数据到服务器			
				ret = send_data_to_server(IP_port,message);//发送数据到服务器					
		}
		
						if(ret == 1)
		{
			DEBUG_PRINT(/*error_result,*/"TCP成功发送到server\r\n");
			Delay(50);
			DEBUG_PRINT("TCP收到回复：\r\n");  //received:后面的内容才是回复的真正内容
			DEBUG_PRINT("%s",Uart1_Buf);
			DEBUG_PRINT("\r\n");
			
		}
		else //数据发送失败，此时可能连接时间过长导致的失败，这样就断开连接，然后就可以继续连接上了
		{
			DEBUG_PRINT(/*error_result,*/"TCP发送失败，错误代码 : %d\r\n",ret);
			UART1_Send_AT_Command("AT+CIPCLOSE","OK",3,150);//关闭链接

		}
//	}
}
