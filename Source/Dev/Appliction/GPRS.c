#include "config.h"
char Uart1_Buf[UART1_BUF_LEN];//����1���ջ���
u8 First_Int = 0;
char server_ip_port_cmd[45];
int reg;
/*************  ���ر�������	**************/
char error_result[20];

static char  *phone_num = "AT+CMGS=\"13055767056\""; //�޸���������޸ĵ绰����

int ret;

/*******************************************************************************
* ������ : Find
* ����   : ���Ҵ���1��������Uart1_Buf���Ƿ��� ��a��
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
* ������ : CLR_Buf
* ����   : �������1��������
*******************************************************************************/
void CLR_Buf(void)
{
	u16 k;
	for(k=0;k<UART1_BUF_LEN;k++)      //��������������
	{
		Uart1_Buf[k] = 0x00;
	}
    First_Int = 0;              //�����ַ�������ʼ�洢λ��
}

/*******************************************************************************
* ������ : UART1_Send_Command
* ����   : ����1��������
*******************************************************************************/
void UART1_Send_Command(char* s)
{
	CLR_Buf(); //��ս������ݵ�buffer
	UART1_SendBuffer(s); //�����ַ���
	UART1_SendBuffer("\r\n"); //���Զ����� \r\n�����ַ�
}

/*******************************************************************************
* ������ : UART1_Send_AT_Command
* ����   : ����1����AT�������
*******************************************************************************/
u8 UART1_Send_AT_Command(char *b,char *a,u8 wait_time,u32 interval_time)         
{
	u8 i;
	i = 0;
	while(i < wait_time)    //�ڵȴ�ʱ���ڲ鿴�Ƿ���Ӧ�����û���ҵ� �ͼ����ٷ�һ��ָ�� �ٽ��в���Ŀ���ַ���                
	{
		UART1_Send_Command(b);//����1���� b �ַ��� �����Զ�����\r\n  �൱�ڷ�����һ��ָ��
		Delay(interval_time); //�ȴ�һ��ʱ�� ��50�Ļ����� 50*20ms = 1��
		if(Find(a))            //������ҪӦ����ַ��� a
		{
			return 1;
		}
		i++;
	}
	return 0;
}

/*******************************************************************************
* ������ : UART1_Send_Command_END
* ����   : ����1���ͽ�������
*******************************************************************************/
void UART1_Send_Command_END(char *s)
{
	CLR_Buf(); //��ս������ݵ�buffer
	UART1_SendBuffer(s); //�����ַ���
}

u8 UART1_Send_AT_Command_End(char *b,char *a,u8 wait_time,u32 interval_time)         
{
	u8 i;
	i = 0;
	while(i < wait_time)    //���û���ҵ� �ͼ����ٷ�һ��ָ�� �ٽ��в���Ŀ���ַ���                
	{
		UART1_Send_Command_END(b);//����1���� b �ַ��� ���ﲻ����\r\n 
		Delay(interval_time); //�ȴ�һ��ʱ�� ��50�Ļ����� 50*20ms = 1��
		if(Find(a))            //������ҪӦ����ַ��� a
		{
			return 1;
		}
		i++;
	}
	
	return 0;
}

/*******************************************************************************
* ������ : Wait_CREG
* ����   : �ȴ�ģ��ע��ɹ�
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
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
* ������ : check_status
* ����   : ���ͨ��״̬
* ����   :
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
int check_status(void)
{
	int ret;
	char esc_char[2];
	
	esc_char[0] = 0x1B;//�˳��ַ�
	esc_char[1] = '\0';
	
	ret = UART1_Send_AT_Command("AT","OK",5,50);//����ͨ���Ƿ�ɹ�
	if(ret == 0)
	{
		UART1_SendBuffer(esc_char);//��һ����>״̬����ô�÷���һ��ESC�ַ�
		return COMMUNITE_ERROR;
	}
	
	ret = UART1_Send_AT_Command("AT+CPIN?","READY",3,50);//��ѯ���Ƿ����
	if(ret == 0)
	{
		return NO_SIM_CARD_ERROR;
	}
	
	ret = Wait_CREG(3);//��ѯ���Ƿ�ע�ᵽ����
	if(ret == 0)
	{
		return SIM_CARD_NO_REG_ERROR;
	}
    
    ret = UART1_Send_AT_Command("ATE0","OK",2,50);//�رջ��Թ���
	if(ret == 0)
	{
		return EAT0_ERROR;
	}
    
	return 1;
}
/*******************************************************************************
* ������ : send_text_config
* ����   : ������Ϣ
* ����   : *content  Ҫ���͵�����
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
int send_text_config(char *content)
{
	
	char end_char[2];
	end_char[0] = 0x1A;//�����ַ�
	end_char[1] = '\0';
	
	reg = UART1_Send_AT_Command("AT+CMGF=1","OK",5,50);//����ΪTEXTģʽ
	if(!reg)
	{
		return AT_CMGF_ERROR;
	}
	
	reg = UART1_Send_AT_Command("AT+CSCS=\"GSM\"","OK",3,50);//�����ַ���ʽ
	if(reg == 0)
	{
		return AT_CSCS_ERROR;
	}
	
	reg = UART1_Send_AT_Command(phone_num,">",3,50);//���������˵ĵ绰����
	if(reg == 0)
	{
		return AT_CMGS_ERROR;
	}
	
	UART1_SendBuffer(content);
	reg = UART1_Send_AT_Command_End(end_char,"OK",1,250);//���ͽ��������ȴ�����ok,�ȴ�5S��һ�Σ���Ϊ���ųɹ����͵�״̬ʱ��Ƚϳ�
	if(reg == 0)
	{
		return END_CHAR_ERROR;
	}
	
	return 1;
}



/*******************************************************************************
* ������ : SendText
* ����   : ������Ϣ
* ����   : *message  Ҫ���͵�����
* ���   : 
* ����   : 
* ע��   : 
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
					ret = send_text_config(message);//����TEXT����
				}
				if(ret == 1)
				{
					DEBUG_PRINT("�ɹ�����TEXT����\r\n");
				}
				else
				{
					DEBUG_PRINT("���ŷ���ʧ�ܣ�������� : %d\r\n",ret);
				}
	
}
/*******************************************************************************
* ������ : send_data_to_server
* ����   : TCP���ӵ�����������
* ����   : *message  Ҫ���͵�����
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
int send_data_to_server(char *server_IP_and_port,char *content)
{
	u8 ret;
	char end_char[2];
	
	
	end_char[0] = 0x1A;//�����ַ�
	end_char[1] = '\0';
	
	ret = UART1_Send_AT_Command("AT+CIPSTATUS","CONNECT OK",3,50*2);//��ѯ����״̬
	if(ret == 1)//˵����������������״̬
	{
		ret = UART1_Send_AT_Command("AT+CIPSEND",">",3,50);//������������
		if(ret == 0)
		{
			return AT_CIPSEND_ERROR;
		}
		
		UART1_SendBuffer(content);
		
		ret = UART1_Send_AT_Command_End(end_char,"SEND OK",1,250);//���ͽ��������ȴ�����ok,�ȴ�5S��һ�Σ���Ϊ��������ʱ����ܽϳ�
		if(ret == 0)
		{
			return END_CHAR_ERROR;
		}
		
		return 1;
	}
	
	ret = UART1_Send_AT_Command("AT+CGATT=1","OK",3,50*20);//��������
	if(ret == 0)
	{
		return AT_CGATT_ERROR;
	}
	
	ret = UART1_Send_AT_Command("AT+CGACT=1,1","OK",3,50*2);//��������
	if(ret == 0)
	{
		return AT_CGATT1_ERROR;
	}

	memset(server_ip_port_cmd,'\0',45);
	strcpy(server_ip_port_cmd,"AT+CIPSTART=\"TCP\",");
	strcat(server_ip_port_cmd,server_IP_and_port);
	
	ret = UART1_Send_AT_Command(server_ip_port_cmd,"CONNECT OK",3,50*2);//���ӷ�����
	if(ret == 0)
	{
		return AT_CIPSTART_ERROR;
	}
	
	ret = UART1_Send_AT_Command("AT+CIPSEND",">",3,50);//������������
	if(ret == 0)
	{
		return AT_CIPSEND_ERROR;
	}
	
	UART1_SendBuffer(content);
	ret = UART1_Send_AT_Command_End(end_char,"SEND OK",1,250);//���ͽ��������ȴ�����ok,�ȴ�5S��һ�Σ���Ϊ��������ʱ����ܽϳ�
    
    if(ret == 0)
	{
		return END_CHAR_ERROR;
	}
	
	return 1;
}
/*******************************************************************************
* ������ : void SendTCP(void)
* ����   : ���͵�ip
* ����   : IP_port ip��ַ�Ͷ˿�*message  Ҫ���͵�����
* ���   : 
* ����   : 
* ע��   : 
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
//			ret = send_data_to_server("\"182.254.216.22\",8687","GA6 tcp test!");//�������ݵ�������			
				ret = send_data_to_server(IP_port,message);//�������ݵ�������					
		}
		
						if(ret == 1)
		{
			DEBUG_PRINT(/*error_result,*/"TCP�ɹ����͵�server\r\n");
			Delay(50);
			DEBUG_PRINT("TCP�յ��ظ���\r\n");  //received:��������ݲ��ǻظ�����������
			DEBUG_PRINT("%s",Uart1_Buf);
			DEBUG_PRINT("\r\n");
			
		}
		else //���ݷ���ʧ�ܣ���ʱ��������ʱ��������µ�ʧ�ܣ������ͶϿ����ӣ�Ȼ��Ϳ��Լ�����������
		{
			DEBUG_PRINT(/*error_result,*/"TCP����ʧ�ܣ�������� : %d\r\n",ret);
			UART1_Send_AT_Command("AT+CIPCLOSE","OK",3,150);//�ر�����

		}
//	}
}
