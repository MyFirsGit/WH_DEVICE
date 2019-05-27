#ifndef __CASDEVDEF_H
#define __CASDEVDEF_H

//========�����붨��========================================

#define E_CAS_BASE			    	17000				// �������ֵ

#define W_CAS_BRACKETPULLOUT		E_CAS_BASE+1		// 17001 ���ʱģ���мܱ�����
#define W_CAS_HOPPERJAM				E_CAS_BASE+2		// 17002 �Զ�����ʱ����һ��HOPPER����ʧ��
#define W_CAS_FILEIDENTICAL			E_CAS_BASE+5		// 17005 �����ص��ļ��汾�ͽ��ʰ汾��ͬ��ȡ������

#define E_CAS_THRESHOLD				E_CAS_BASE+10		// 17010 ���ش���ֵ

#define E_CAS_FILEFIND				E_CAS_THRESHOLD+0	// 17010 û���ҵ�ָ���������ļ�
#define E_CAS_PARAMETER				E_CAS_THRESHOLD+1	// 17011 ��������ȷ
#define E_CAS_NOCHANGE				E_CAS_THRESHOLD+2	// 17012 ���㣬����ʧ��
#define E_CAS_ESCROW1CENTER			E_CAS_THRESHOLD+3	// 17013 �ݴ���1�Ҳ����м�λ��
#define E_CAS_ESCROW1LEFT			E_CAS_THRESHOLD+4	// 17014 �ݴ���1�Ҳ������λ��
#define E_CAS_ESCROW1RIGHT			E_CAS_THRESHOLD+5	// 17015 �ݴ���1�Ҳ����ұ�λ��
#define E_CAS_ESCROW2CENTER			E_CAS_THRESHOLD+6	// 17016 �ݴ���2�Ҳ����м�λ��
#define E_CAS_ESCROW2LEFT			E_CAS_THRESHOLD+7	// 17017 �ݴ���2�Ҳ������λ��
#define E_CAS_ESCROW2RIGHT			E_CAS_THRESHOLD+8	// 17018 �ݴ���2�Ҳ����ұ�λ��
#define E_CAS_BUCKLE1DOWN			E_CAS_THRESHOLD+9	// 17019 �ӱҿ�1�Ҳ����±�λ��
#define E_CAS_BUCKLE1UP				E_CAS_THRESHOLD+10	// 17020 �ӱҿ�1�Ҳ����ϱ�λ��
#define E_CAS_BUCKLE2DOWN			E_CAS_THRESHOLD+11	// 17021 �ӱҿ�2�Ҳ����±�λ��
#define E_CAS_BUCKLE2UP				E_CAS_THRESHOLD+12	// 17022 �ӱҿ�2�Ҳ����ϱ�λ��
#define E_CAS_CHANNEL2OUT			E_CAS_THRESHOLD+13	// 17023 ����ͨ����������ڴ���
#define E_CAS_CHANNEL2RV			E_CAS_THRESHOLD+14	// 17024 ����ͨ������������䴫��
#define E_CAS_MHOPPER1DISP			E_CAS_THRESHOLD+15	// 17025 ��������1����ʧ��
#define E_CAS_MHOPPER1JAM			E_CAS_THRESHOLD+16	// 17026 ��������1����
#define E_CAS_MHOPPER2DISP			E_CAS_THRESHOLD+17	// 17027 ��������2����ʧ��
#define E_CAS_MHOPPER2JAM			E_CAS_THRESHOLD+18	// 17028 ��������2����
#define E_CAS_SHOPPER1DISP			E_CAS_THRESHOLD+19	// 17029 ����������1����ʧ��(CAS007 ��������3����ʧ��)
#define E_CAS_SHOPPER1JAM			E_CAS_THRESHOLD+20	// 17030 ����������1����(CAS007 ��������3����)
#define E_CAS_SHOPPER2DISP			E_CAS_THRESHOLD+21	// 17031 ����������2����ʧ��(CAS007 ��������4����ʧ��)
#define E_CAS_SHOPPER2JAM			E_CAS_THRESHOLD+22	// 17032 ����������2����(CAS007 ��������4����)
#define E_CAS_COINRECVFAULT			E_CAS_THRESHOLD+23	// 17033 Ӳ�ҽ���������
#define E_CAS_IBUTTON1				E_CAS_THRESHOLD+24	// 17034 �ӱ���1 iButton����
#define E_CAS_IBUTTON2				E_CAS_THRESHOLD+25	// 17035 �ӱ���2 iButton����
#define E_CAS_RV1IBUTTONERROR		E_CAS_THRESHOLD+26	// 17036 ������1 iButton����
#define E_CAS_RV2IBUTTONERROR		E_CAS_THRESHOLD+27	// 17037 ������2 iButton����
#define E_CAS_WRITELOG				E_CAS_THRESHOLD+28	// 17038 дLogʧ��
#define E_CAS_READLOG				E_CAS_THRESHOLD+29	// 17039 ��Logʧ��
#define E_CAS_CAMJAM				E_CAS_THRESHOLD+30	// 17040 ͹�ֶ�ת
#define E_CAS_CAMMOTOR				E_CAS_THRESHOLD+31	// 17041 ͹��������
#define E_CAS_COININJAM				E_CAS_THRESHOLD+32	// 17042 Ͷ�ҿڿ���
#define E_CAS_G40RUSIG				E_CAS_THRESHOLD+33	// 17043 Ӳ�ҽ������˱��ź��쳣
#define E_CAS_ESCROW1SENSOR			E_CAS_THRESHOLD+34	// 17044 �ݴ���1����������
#define E_CAS_ESCROW2SENSOR			E_CAS_THRESHOLD+35	// 17045 �ݴ���2����������
#define E_CAS_BUCKLE1SENSOR			E_CAS_THRESHOLD+36	// 17046 �ӱҿ�1����������
#define E_CAS_BUCKLE2SENSOR			E_CAS_THRESHOLD+37	// 17047 �ӱҿ�2����������
#define E_CAS_CHANNELSENSOR			E_CAS_THRESHOLD+38	// 17048 ����ͨ������������
#define E_CAS_EEPROM				E_CAS_THRESHOLD+39	// 17049 EEPROM����
#define E_CAS_G40TIMEOUT			E_CAS_THRESHOLD+40	// 17050 Ӳ�ҽ�������ʱ
#define E_CAS_G40DATA				E_CAS_THRESHOLD+41	// 17051 Ӳ�ҽ������������ݴ�
#define E_CAS_DEVBUSY				E_CAS_THRESHOLD+42	// 17052 �豸æ
#define E_CAS_ADDBOX1IMPERFECT		E_CAS_THRESHOLD+43	// 17053 �ӱ���1�ӱ�δ���
#define E_CAS_ADDBOX2IMPERFECT		E_CAS_THRESHOLD+44	// 17054 �ӱ���2�ӱ�δ���
#define E_CAS_ADDBOXIMPERFECT		E_CAS_THRESHOLD+45	// 17055 �ӱ���1��2�ӱ�δ���
#define E_CAS_DEVPOS				E_CAS_THRESHOLD+46	// 17056 ģ��λ���쳣
#define E_CAS_SHOPPER3DISP			E_CAS_THRESHOLD+47	// 17057 ����������3����ʧ��
#define E_CAS_SHOPPER3JAM			E_CAS_THRESHOLD+48	// 17058 ����������3����
#define E_CAS_SHOPPER4DISP			E_CAS_THRESHOLD+49	// 17059 ����������4����ʧ��
#define E_CAS_SHOPPER4JAM			E_CAS_THRESHOLD+50	// 17060 ����������4����
#define E_CAS_CHANNELRUN			E_CAS_THRESHOLD+51	// 17061 Ӳ�Ҵ���ͨ����ת����
#define E_CAS_COININSENSOR			E_CAS_THRESHOLD+52	// 17062 Ӳ��ͨ����SENSOR����
#define E_CAS_COINOUTSENSOR1		E_CAS_THRESHOLD+53	// 17063 Ӳ��ͨ����SENSOR1����
#define E_CAS_COINCASEEXIST			E_CAS_THRESHOLD+54	// 17064 Ӳ��Ǯ����sensor����
#define E_CAS_BHOPPER1SENSOR		E_CAS_THRESHOLD+55	// 17065 ��HOPPER1 SENSOR����
#define E_CAS_BHOPPER2SENSOR		E_CAS_THRESHOLD+56	// 17066 ��HOPPER2 SENSOR����
#define E_CAS_SHOPPER1SENSOR		E_CAS_THRESHOLD+57	// 17067 СHOPPER1 SENSOR����(CAS007 ��HOPPER3 SENSOR����)
#define E_CAS_SHOPPER2SENSOR		E_CAS_THRESHOLD+58	// 17068 СHOPPER2 SENSOR����(CAS007 ��HOPPER4 SENSOR����)
#define E_CAS_SHOPPER3SENSOR		E_CAS_THRESHOLD+59	// 17069 СHOPPER3 SENSOR����
#define E_CAS_SHOPPER4SENSOR		E_CAS_THRESHOLD+60	// 17070 СHOPPER4 SENSOR����
#define E_CAS_SHUTTEROPEN			E_CAS_THRESHOLD+61	// 17071 Ӳ��բ�Ŵ�ʧ��
#define E_CAS_SHUTTERCLOSE			E_CAS_THRESHOLD+62	// 17072 Ӳ��բ�Źر�ʧ��
#define E_CAS_FILENOTFINISH			E_CAS_THRESHOLD+63	// 17073 �ļ�δ������
#define E_CAS_POWERDOWN				E_CAS_THRESHOLD+64	// 17074 ��Դ��ѹ�ͣ��޷���������
#define E_CAS_NO_HOPPER				E_CAS_THRESHOLD+65	// 17075 Hopper�����ڻ򲻿���
#define E_CAS_RFID_REQUEST			E_CAS_THRESHOLD+66	// 17076 ��Ӧ���޿���/��ģ��δ����
#define E_CAS_RFID_AUTHEN			E_CAS_THRESHOLD+67	// 17077 ��Ӧ������֤ʧ�� 
#define E_CAS_RFID_PARAMETER		E_CAS_THRESHOLD+68	// 17078 ��дRFIDʱ������ 
//17076~17081 Ϊ�豸���������루�����˵���飩

//added by hguang 2010-08-31
#define E_CAS_FILEOPEN				E_CAS_THRESHOLD+72	// 17082 ���ļ�ʧ��
#define E_CAS_FILELENGTH			E_CAS_THRESHOLD+73	// 17083 �ļ�̫��
#define E_CAS_FILEREAD				E_CAS_THRESHOLD+74	// 17084 ���ļ�ʧ��
#define E_CAS_LOGWRITE				E_CAS_THRESHOLD+75	// 17085 д�����־����̫��������1024�ֽڣ�
#define E_CAS_PDLVERSION			E_CAS_THRESHOLD+76  // 17086 ������Ľ��ʰ汾�������ļ��汾��һ��
//end added

#define E_CAS_COINCASEFULL			E_CAS_THRESHOLD+77	// 17087 Ǯ����
#define E_CAS_UNINIT				E_CAS_THRESHOLD+78	// 17088 ģ��δ��ʼ��
#define E_CAS_UNKNOWN				E_CAS_THRESHOLD+79	// 17089 δ֪��
#define E_CAS_PARAMWRONG			E_CAS_THRESHOLD+80	// 17090 �ӿڲ�����
#define E_CAS_DEVCFG				E_CAS_THRESHOLD+81	// 17091 �豸���ô�
#define E_CAS_UNSUPPORT				E_CAS_THRESHOLD+82	// 17092 ��֧�ֵĹ���
#define E_CAS_COMMCFG    			E_CAS_THRESHOLD+83	// 17093 �������ô�
#define E_CAS_RECEIVENAK			E_CAS_THRESHOLD+84	// 17094 �յ�NAK,���������д�
#define E_CAS_REVDATAWRONG			E_CAS_THRESHOLD+85	// 17095 ���յ�����������
#define E_CAS_SENDENQERROR			E_CAS_THRESHOLD+86	// 17096 ����ENQ����
#define E_CAS_SENDCMDERROR		    E_CAS_THRESHOLD+87	// 17097 ���������
#define E_CAS_ACKTIMEOUT			E_CAS_THRESHOLD+88	// 17098 �ȴ�ACK��ʱ
#define E_CAS_RESPTIMEOUT			E_CAS_THRESHOLD+89	// 17099 �ȴ���Ӧ��ʱ

#endif	// #ifndef __CASDEVDEF_H
