#ifndef __CASDEVSTRUCT_H
#define __CASDEVSTRUCT_H

//////////////////////////////////////////////////////////////////////////
//
//	����ģ�飺
//	CAS006:	���ڵ����ĺ���Ӳ��ģ��
//	CAS006A:������ATMӲ������ģ��
//	CAS006B:���������˺��ߡ���������Ӳ��ģ��
//
//////////////////////////////////////////////////////////////////////////

//========Ӳ�����Ͷ���================================
#define COIN_TYPEA				1
#define COIN_TYPEB				2

//========���ñ�־����================================
#define HOPPER_ENABLE			0
#define HOPPER_DISABLE			0x80

//========��Ӳ�ҷ�����==============================
#define COIN_2_SHOPPER			1	// ���뻺��������
#define COIN_2_COINCASE1		2	// ����Ǯ��1
#define COIN_2_OUTLET			3	// ������ҿ�
#define COIN_2_COINCASE2		4	// ����Ǯ��2


//========IBUTTON״̬����========================================
													// ������					δ��⵽�����				��⵽������
#define S_MHOPPER1_IBUTTON		0x01				// ��Hopper1�ӱ���			0: δ��⵽�ӱ���1 �����	1: ��⵽�ӱ���1 ������
#define S_MHOPPER2_IBUTTON		0x02				// ��Hopper2�ӱ���			0: δ��⵽�ӱ���2 �����	1: ��⵽�ӱ���2 ������
#define S_RETRACT_VALT1			0x04				// Ӳ�һ�����1				0: δ��⵽������1 �����	1: ��⵽������1 ������
#define S_RETRACT_VALT2			0x08				// Ӳ�һ�����2				0: δ��⵽������2 �����	1: ��⵽������2 ������
#define S_EEPROM				0x10				// EEPROM					0: δ��⵽EEPROM �����	1: ��⵽EEPROM ������
#define S_COIN_SHUTTER			0x20				// Ӳ��բ��״̬				0: Ӳ��բ�Źر�				1: Ӳ��բ�Ŵ�  
#define S_CHANNEL_STATUS		0x40				// ͨ���˶�״̬				0: ���˶�					1: �˶�
#define S_BUTTON_RESERVED		0x80

#define S_RECEIVER_STATUS		0x01				// ���չ���״̬				0: ������					1: ����
#define S_CHANGE_STATUS			0x02				// ���㹦��״̬				0: ������					1: ����

//========����������========================================
													// ������					δ��⵽�����			��⵽������
#define S_BUCKLE1_LOWER			0x0000000000000001	// �ӱҿ�1λ���´�����		0: ����������			1: ������δ��
#define S_BUCKLE1_UPPER			0x0000000000000002	// �ӱҿ�1λ���ϴ�����		0: ����������			1: ������δ��
#define S_BUCKLE2_LOWER			0x0000000000000004	// �ӱҿ�2λ���´�����		0: ����������			1: ������δ��
#define S_BUCKLE2_UPPER			0x0000000000000008	// �ӱҿ�2λ���ϴ�����		0: ����������			1: ������δ��
#define S_ROUTER_RIGHT			0x0000000000000010	// �������ұߴ�����			0: ����������			1: ������δ��
#define S_ROUTER_LEFT			0x0000000000000020	// ��������ߴ�����			0: ����������			1: ������δ��
#define S_ESCROW1_RIGHT			0x0000000000000040	// �ݴ���1�Ҵ�����			0: ����������			1: ������δ��
#define S_ESCROW1_CENTER		0x0000000000000080	// �ݴ���1�д�����			0: ����������			1: ������δ��

#define S_ESCROW1_LEFT			0x0000000000000100	// �ݴ���1�󴫸���			0: ����������			1: ������δ��
#define S_ESCROW2_RIGHT			0x0000000000000200	// �ݴ���2�Ҵ�����			0: ����������			1: ������δ��
#define S_ESCROW2_CENTER		0x0000000000000400	// �ݴ���2�д�����			0: ����������			1: ������δ��
#define S_ESCROW2_LEFT			0x0000000000000800	// �ݴ���2�󴫸���			0: ����������			1: ������δ��
#define S_MAGNET1_IN_POS		0x0000000000001000	// �����1��λ���			0: ����������			1: ������δ��
#define S_MAGNET2_IN_POS		0x0000000000002000	// �����2��λ���			0: ����������			1: ������δ��
#define S_MHOPPER1				0x0000000000004000	// ��������1���Ҵ�����		0: �б�					1: �ޱ�
#define S_MHOPPER2				0x0000000000008000	// ��������2���Ҵ�����		0: �б�					1: �ޱ�

#define S_THOPPER1				0x0000000000010000	// �߼���СHopper1			0: �б�					1: �ޱ�
#define S_THOPPER2				0x0000000000020000	// �߼���СHopper2			0: �б�					1: �ޱ�
#define S_EHOPPER1				0x0000000000040000	// ����������1���Ҵ�����	0: �б�					1: �ޱ�
#define S_EHOPPER2				0x0000000000080000	// ����������2���Ҵ�����	0: �б�					1: �ޱ�
#define S_EHOPPER3				0x0000000000100000	// ����������3���Ҵ�����	0: �б�					1: �ޱ�
#define S_EHOPPER4				0x0000000000200000	// ����������4���Ҵ�����	0: �б�					1: �ޱ�
#define S_PLATE1_OPEN			0x0000000000400000	// �ӱ���1�����			0: ����������			1: ������δ��
#define S_PLATE1_CLOSE			0x0000000000800000	// �ӱ���1����ر�			0: ����������			1: ������δ��

#define S_PLATE2_OPEN			0x0000000001000000	// �ӱ���2�����			0: ����������			1: ������δ��
#define S_PLATE2_CLOSE			0x0000000002000000	// �ӱ���2����ر�			0: ����������			1: ������δ��
#define S_COINCASE_IN_POS		0x0000000004000000	// Ӳ��Ǯ�䵽λ������		0: ����������			1: ������δ��
#define S_CHANNEL_MOTOR			0x0000000008000000	// ͨ�����ת��������		0: ����������			1: ������δ��
#define S_COIN_IN				0x0000000010000000	// Ͷ����ڴ�����			0: �б�					1: �ޱ�
#define S_COIN_OUT1				0x0000000020000000	// Ͷ�ҳ��ڴ�����1			0: �б�					1: �ޱ�
#define S_BRACKET_POS			0x0000000040000000	// �ϼ�λ�ô�����			0: �б�					1: �ޱ�
#define S_CAM_SENSOR			0x0000000080000000	// ͹�ִ�����				0: ����������			1: ������δ��

#define S_CHANNEL1				0x0000000100000000	// ͨ��������1				0: ����������			1: ������δ��
#define S_CHANNEL2				0x0000000200000000	// ͨ��������2				0: ����������			1: ������δ��
#define S_COIN_OUT2				0x0000000400000000	// Ͷ�ҳ��ڴ�����2			0: �б�					1: �ޱ�
#define S_SHUTTER_OPEN			0x0000000800000000	// բ�ſ�������				0: ����������			1: ������δ����������
#define S_SHUTTER_CLOSE			0x0000001000000000	// բ�Źش�����				0: ����������			1: ������δ����������
#define S_COINCASE_IN_POS2		0x0000002000000000	// Ӳ��Ǯ��2��λ������		0: ����������			1: ������δ����CAS006B��
#define S_SENSOR_RESERVED56		0x0000004000000000
#define S_SENSOR_RESERVED57		0x0000008000000000

#define S_SENSOR_RESERVED60		0x0000010000000000
#define S_SENSOR_RESERVED61		0x0000020000000000
#define S_SENSOR_RESERVED62		0x0000040000000000
#define S_SENSOR_RESERVED63		0x0000080000000000
#define S_SENSOR_RESERVED64		0x0000100000000000
#define S_SENSOR_RESERVED65		0x0000200000000000
#define S_SENSOR_RESERVED66		0x0000400000000000
#define S_SENSOR_RESERVED67		0x0000800000000000

// ����״̬
typedef struct 
{
	BYTE byMHopper1Button;	// ��Hopper1�ӱ���			0: δ��⵽�ӱ���1 �����	1: ��⵽�ӱ���1 ������
	BYTE byMHopper2Button;	// ��Hopper2�ӱ���			0: δ��⵽�ӱ���2 �����	1: ��⵽�ӱ���2 ������
	BYTE byRetractValt1;	// Ӳ�һ�����1				0: δ��⵽������1 �����	1: ��⵽������1 ������
	BYTE byRetractValt2;	// Ӳ�һ�����2				0: δ��⵽������2 �����	1: ��⵽������2 ��������CAS006B��
	BYTE byEEPROM;			// EEPROM					0: δ��⵽EEPROM �����	1: ��⵽EEPROM ������
	BYTE byCoinShutter;		// Ӳ��բ��״̬				0: Ӳ��բ�Źر�				1: Ӳ��բ�Ŵ򿪣�������
	BYTE byChannelStatus;	// ͨ���˶�״̬				0: ���˶�					1: �˶���CAS006��
	BYTE byReserved17;

	BYTE byReceiverStatus;	// ���չ���״̬����״ֻ̬�ڳ�ʼ��ģ��ʱ�Ż�ı䣩	0: ������	1: ����
	BYTE byChangeStatus;	// ���㹦��״̬����״ֻ̬�ڳ�ʼ��ģ��ʱ�Ż�ı䣩	0: ������	1: ����
	BYTE byReserved22;
	BYTE byReserved23;
	BYTE byReserved24;
	BYTE byReserved25;
	BYTE byReserved26;
	BYTE byReserved27;
}tiButtonStatus;

// ������״̬
typedef struct 
{
							// ������					δ��⵽�����			��⵽������
	BYTE byBuckle1Lower;	// �ӱҿ�1λ���´�����		0: ����������			1: ������δ��
	BYTE byBuckle1Upper;	// �ӱҿ�1λ���ϴ�����		0: ����������			1: ������δ��
	BYTE byBuckle2Lower;	// �ӱҿ�2λ���´�����		0: ����������			1: ������δ��
	BYTE byBuckle2Upper;	// �ӱҿ�2λ���ϴ�����		0: ����������			1: ������δ��
	BYTE byRouterRight;		// �������ұߴ�����			0: ����������			1: ������δ��
	BYTE byRouterLeft;		// ��������ߴ�����			0: ����������			1: ������δ��
	BYTE byEscrow1Right;	// �ݴ���1�Ҵ�����			0: ����������			1: ������δ��
	BYTE byEscrow1Center;	// �ݴ���1�д�����			0: ����������			1: ������δ��
	
	BYTE byEscrow1Left;		// �ݴ���1�󴫸���			0: ����������			1: ������δ��
	BYTE byEscrow2Right;	// �ݴ���2�Ҵ�����			0: ����������			1: ������δ����CAS006��
	BYTE byEscrow2Center;	// �ݴ���2�д�����			0: ����������			1: ������δ����CAS006��
	BYTE byEscrow2Left;		// �ݴ���2�󴫸���			0: ����������			1: ������δ����CAS006��
	BYTE byMagnet1InPos;	// �����1��λ���			0: ����������			1: ������δ��
	BYTE byMagnet2InPos;	// �����2��λ���			0: ����������			1: ������δ��
	BYTE byMHopper1;		// ��������1���Ҵ�����		0: �б�					1: �ޱ�
	BYTE byMHopper2;		// ��������2���Ҵ�����		0: �б�					1: �ޱ�
	
	BYTE byTHopper1;		// �߼���СHopper1			0: �б�					1: �ޱң�CAS006B��
	BYTE byTHopper2;		// �߼���СHopper2			0: �б�					1: �ޱң�CAS006B��
	BYTE byEHopper1;		// ����������1���Ҵ�����	0: �б�					1: �ޱң�CAS006��
	BYTE byEHopper2;		// ����������2���Ҵ�����	0: �б�					1: �ޱң�CAS006��
	BYTE byEHopper3;		// ����������3���Ҵ�����	0: �б�					1: �ޱң�CAS006��
	BYTE byEHopper4;		// ����������4���Ҵ�����	0: �б�					1: �ޱң�CAS006��
	BYTE byPlate1Open;		// �ӱ���1�����			0: ����������			1: ������δ��
	BYTE byPlate1Close;		// �ӱ���1����ر�			0: ����������			1: ������δ��
	
	BYTE byPlate2Open;		// �ӱ���2�����			0: ����������			1: ������δ��
	BYTE byPlate2Close;		// �ӱ���2����ر�			0: ����������			1: ������δ��
	BYTE byCoincaseInPos;	// Ӳ��Ǯ�䵽λ������		0: ����������			1: ������δ��
	BYTE byChannelMotor;	// ͨ�����ת��������		0: ����������			1: ������δ��
	BYTE byCoinIn;			// Ͷ����ڴ�����			0: �б�					1: �ޱ�
	BYTE byCoinOut1;		// Ͷ�ҳ��ڴ�����1			0: �б�					1: �ޱ�
	BYTE byBracketPos;		// �ϼ�λ�ô�����			0: �б�					1: �ޱ�
	BYTE byCamSensor;		// ͹�ִ�����				0: ����������			1: ������δ��
	
	BYTE byChannel1;		// ͨ��������1				0: ����������			1: ������δ����������
	BYTE byChannel2;		// ͨ��������2				0: ����������			1: ������δ����������
	BYTE byCoinOut2;		// Ͷ�ҳ��ڴ�����2			0: �б�					1: �ޱ�		 ��������
	BYTE byShutterOpen;		// բ�ſ�������				0: ����������			1: ������δ����������
	BYTE byShutterClose;	// բ�Źش�����				0: ����������			1: ������δ����������
	BYTE byCoincase2InPos;	// Ӳ��Ǯ��2��λ������		0: ����������			1: ������δ����CAS006B��
	BYTE byReserved56;
	BYTE byReserved57;

	BYTE byReserved60;
	BYTE byReserved61;
	BYTE byReserved62;
	BYTE byReserved63;
	BYTE byReserved64;
	BYTE byReserved65;
	BYTE byReserved66;
	BYTE byReserved67;
}tSensorStatus;

typedef struct 
{
	tiButtonStatus siButtonStatus;
	tSensorStatus  sSensorStatus;
}tCASStatus;

// Ӳ����Ϣ
typedef struct 
{
	int  iMHopper1Num;			// ��Hopper1Ӳ�Ҹ��������ط�Χ-32768~32767
	int  iMHopper2Num;			// ��Hopper2Ӳ�Ҹ��������ط�Χ-32768~32767
	int  iSHopper1Num;			// СHopper1Ӳ�Ҹ��������ط�Χ-32768~32767
	int  iSHopper2Num;			// СHopper2Ӳ�Ҹ��������ط�Χ-32768~32767
	int  iSHopper3Num;			// СHopper3Ӳ�Ҹ��������ط�Χ-32768~32767
	int  iSHopper4Num;			// СHopper4Ӳ�Ҹ��������ط�Χ-32768~32767

	int  iCoincase1Coin1;		// Ӳ��Ǯ��1Ӳ��1���������ط�Χ-32768~32767
	int	 iCoincase1Coin2;		// Ӳ��Ǯ��1Ӳ��2���������ط�Χ-32768~32767
	int  iCoincase2Coin1;		// Ӳ��Ǯ��2Ӳ��1���������ط�Χ-32768~32767
	int	 iCoincase2Coin2;		// Ӳ��Ǯ��2Ӳ��2���������ط�Χ-32768~32767

	BYTE byEscrow1Num;			// �ݴ���1Ӳ�Ҹ���
	BYTE byEscrow2Num;			// �ݴ���2Ӳ�Ҹ���
	BYTE byEscrow3Num;			// �ݴ���3Ӳ�Ҹ���
	BYTE byEscrow4Num;			// �ݴ���4Ӳ�Ҹ���

	BYTE byMHopper1Type;		// ��Hopper1Ӳ�����͡�MSBΪHOPDISABLEλ��1��ʾ��ֹ��0��ʾʹ��
	BYTE byMHopper2Type;		// ��Hopper1Ӳ�����͡�MSBΪHOPDISABLEλ��1��ʾ��ֹ��0��ʾʹ��
	BYTE bySHopper1Type;		// СHopper1Ӳ�����͡�MSBΪHOPDISABLEλ��1��ʾ��ֹ��0��ʾʹ��
	BYTE bySHopper2Type;		// СHopper2Ӳ�����͡�MSBΪHOPDISABLEλ��1��ʾ��ֹ��0��ʾʹ��
	BYTE bySHopper3Type;		// СHopper3Ӳ�����͡�MSBΪHOPDISABLEλ��1��ʾ��ֹ��0��ʾʹ��
	BYTE bySHopper4Type;		// СHopper4Ӳ�����͡�MSBΪHOPDISABLEλ��1��ʾ��ֹ��0��ʾʹ��

	BYTE byEjectCoinNum;		// ���ν����˱���
								// �ݴ���1��Ӳ�����ͺ�СHopper1��Ӳ������һ��
								// �ݴ���2��Ӳ�����ͺ�СHopper2��Ӳ������һ��
								// �ݴ���3��Ӳ�����ͺ�СHopper3��Ӳ������һ��
								// �ݴ���4��Ӳ�����ͺ�СHopper4��Ӳ������һ��
	
}tCoinInfo;

// ����ṹ 
typedef struct 
{
	BYTE byMHopper1Num;		// ��Hopper1������
	BYTE byMHopper2Num;		// ��Hopper2������
	
	BYTE bySHopper1Num;		// СHopper1������
	BYTE bySHopper2Num;		// СHopper2������
	BYTE bySHopper3Num;		// СHopper3������
	BYTE bySHopper4Num;		// СHopper4������
}tChange;

// ���ս��
typedef struct 
{
	BYTE byEscrow1Num;		// �ݴ���1Ӳ�Ҹ���
	BYTE byEscrow2Num;		// �ݴ���2Ӳ�Ҹ���
	BYTE byEscrow3Num;		// �ݴ���3Ӳ�Ҹ���
	BYTE byEscrow4Num;		// �ݴ���4Ӳ�Ҹ���
	BYTE byEjectCoinNum;	// ���ν����˱���
}tReceiveCoinNum;

// ���ý��
typedef struct 
{
	WORD wMHopper1Num;		// ��Hopper1Ӳ�Ҹ��������÷�Χ0~32767
	WORD wMHopper2Num;		// ��Hopper2Ӳ�Ҹ��������÷�Χ0~32767	
	WORD wSHopper1Num;		// СHopper1�����������÷�Χ0~32767
	WORD wSHopper2Num;		// СHopper2�����������÷�Χ0~32767
	WORD wSHopper3Num;		// СHopper3�����������÷�Χ0~32767
	WORD wSHopper4Num;		// СHopper4�����������÷�Χ0~32767

	WORD wCoincase1Coin1;	// Ӳ��Ǯ��1Ӳ��1���������÷�Χ0~32767
	WORD wCoincase1Coin2;	// Ӳ��Ǯ��1Ӳ��2���������÷�Χ0~32767
	WORD wCoincase2Coin1;	// Ӳ��Ǯ��2Ӳ��1���������÷�Χ0~32767	
	WORD wCoincase2Coin2;	// Ӳ��Ǯ��2Ӳ��2���������÷�Χ0~32767	

	BYTE byEscrow1Num;		// �ݴ���1Ӳ�Ҹ���
	BYTE byEscrow2Num;		// �ݴ���2Ӳ�Ҹ���
	BYTE byEscrow3Num;		// �ݴ���3Ӳ�Ҹ���
	BYTE byEscrow4Num;		// �ݴ���4Ӳ�Ҹ���

	BYTE byMHopper1Type;	// ��Hopper1Ӳ�����ͣ�Ӳ������1~0x7F����hopper1Ӳ�����ͣ�CAS-007��
	BYTE byMHopper2Type;	// ��Hopper1Ӳ�����ͣ�Ӳ������1~0x7F����hopper2Ӳ�����ͣ�CAS-007��
	BYTE bySHopper1Type;	// СHopper1Ӳ�����ͣ�Ӳ������1~0x7F����hopper3Ӳ�����ͣ�CAS-007��
	BYTE bySHopper2Type;	// СHopper2Ӳ�����ͣ�Ӳ������1~0x7F����hopper4Ӳ�����ͣ�CAS-007��
	BYTE bySHopper3Type;	// СHopper3Ӳ�����ͣ�Ӳ������1~0x7F����װHopper���ã�CAS-007��
	BYTE bySHopper4Type;	// СHopper4Ӳ�����ͣ�Ӳ������1~0x7F��
	
}tSetCoinNum;

// ��ҽṹ 
typedef struct 
{
	bool bMHopper1Flag;		// ��Hopper1��ұ�־��true=��ң�false=�����
	bool bMHopper2Flag;		// ��Hopper2��ұ�־��true=��ң�false=�����
	
	bool bSHopper1Flag;		// СHopper1��ұ�־��true=��ң�false=�����
	bool bSHopper2Flag;		// СHopper2��ұ�־��true=��ң�false=�����
	bool bSHopper3Flag;		// СHopper3��ұ�־��true=��ң�false=�����
	bool bSHopper4Flag;		// СHopper4��ұ�־��true=��ң�false=�����

	BYTE byCoincase;		// ��ҷ���1=Ӳ��Ǯ��1��2=Ӳ��Ǯ��2
}tClearCoin;

// ����
typedef struct 
{
	BYTE byYear;			// ��
	BYTE byMonth;			// ��
	BYTE byDay;				// ��
}tDate;

// ʱ��
typedef struct 
{
	BYTE byHour;			// ʱ
	BYTE byMinute;			// ��
	BYTE bySecond;			// ��
}tTime;

// ����ʱ��
typedef struct 
{
	BYTE byYear;			// ��
	BYTE byMonth;			// ��
	BYTE byDay;				// ��
	BYTE byHour;			// ʱ
	BYTE byMinute;			// ��
	BYTE bySecond;			// ��
}tDateTime;

//�������ؽ���
typedef struct _tCoinSystem_Pdl_Progress
{
	char       acFileName[MAX_PATH];    //��ǰ�����ļ���
	
	int        iTotalSize;              //�ļ���С
	
	int        iCurPos;					//��ǰ����λ��	
	
}tCoinSystem_Pdl_Progress;

//�豸��־
typedef struct
{
	
	BYTE       abyLogDate[4];         //��־��¼���� ������ʱ

	UINT       uiLogStartAddress;     //��¼DwLogDate�������־��ʼ��ַ

	UINT       uiLogEndAddress;	      //��¼DwLogDate�������־������ַ	
	
}tCoinLog;

//added by hguang 2013-08-26
//��д����RFID����
typedef struct 
{
	BYTE				byBoxId;						//�����
	
	BYTE				byBlockIndex;					//RFID block��
	
	BYTE				byReserved[2];					//�����ֶ�
	
}tCAS006_IN_RWRFID;

//������Ϣ
typedef struct 
{
	BYTE				byBoxId;						//�����
	
	BYTE				byReserved[3];					//�����ֶ�
	
}tCAS006_IN_CARD_INFO;

//��/д����
typedef struct 
{		
	char				caData[64];						// д��/����������
}tCAS006_DATA;
//end added

// ָ���������
typedef struct
{
	unsigned short ushMHopper[4];					//�����������	[0] MH1 [1] MH2 [3/4]����
	unsigned short ushSHopper[4];						//�������������[0] SH1 [1] SH2 [3/4]����
	
	unsigned char byCoincase;						//��ҷ���
	unsigned char byRsv[7];							//�����ֶ�
}tCAS006_ClearNum;
#endif // __CASDEVSTRUCT_H