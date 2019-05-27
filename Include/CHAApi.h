#ifndef _CHA_API_H_
#define _CHA_API_H_

#include "Apidef.h"

//#ifdef __cplusplus
//extern "C" {
//#endif


#pragma pack(push,1)

typedef enum _ch_err_detail {
	CH_RES_OK				= 0,	// �����ɹ�
	CH_SET_PARAM_ERR            = 1,	// �趨ֵ�������쳣
	CH_FUNC_PARAM_ERR           = 2,	// ���������쳣
	CH_SEQUENCE_ERR	            = 3,	// ��������˳���쳣
	CH_FUNC_ERR_RETURN	        = 4,	// ���������쳣
	CH_LOGIC_ERR	            = 5,	// �߼��쳣
	CH_OTHER_ERR                = 6,    // ��������   
	CH_OPEN_FAILED				= 11,	// ��ʱ	���ڴ�ʧ��
	CH_ALREADY_OPENED			= 12,	// ��ʱ	�����ظ���
	CH_CLOSE_FAILED				= 13,	// �ر�ʱ	���ڹر�ʧ��
	CH_ALREADY_CLOSED			= 14,	// �ر�ʱ	�����ظ��ر�
	CH_NOT_OPEN					= 15,	// ͨ��ʱ	����δ��
	CH_CMD_EXCEPTION			= 16,	// ͨ��ʱ	�����쳣
	CH_SEND_EXCEPTION			= 17,	// ͨ��ʱ	�����쳣
	CH_RECEIVE_EXCEPTION		= 18,	// ͨ��ʱ	�����쳣
	CH_DESERIALIZE_EXCEPTION	= 19,	// ͨ��ʱ	�����ظ���Ϣ�쳣
	CH_RECEIVE_TIMEOUT			= 20,	// ͨ��ʱ	���ճ�ʱ


	CHTRS_RES_WINERR           = 1001, // ϵͳ����

	CHTRS_ERR_HANDLE           = 1003, // The handle is invalid.
	CHTRS_RES_ERR_CHREAD       = 1100, // Could not create thread. Window error.
	CHTRS_RES_ERR_TIMEOUT      = 1101, // Timeout. Could not finished task in time.
	CHTRS_RES_RESET            = 1102, // Operation was terminate because of reseting.
	CHTRS_RES_STRANGE          = 1103, // Unrecognizable response.
	CHTRS_RECV_EMPTY           = 1104, // There is no data to receive.

	CHTRS_HTDL_ERR_FULL        = 1201, // Could not open connection because the conneciton pool is full
	CHTRS_HTDL_ERR_OPNTO       = 1202, // The operation could not finish in time.
	CHTRS_HTDL_ERR_WORKNG      = 1203, // Could not allocate workspace, out of memory.
	CHTRS_HTDL_ERR_SQUENG      = 1204, // Could not allocate the queue, out of memory.
	CHTRS_HTDL_ERR_RBUFNG      = 1206, // Could not allocate buffer for receiving data, out of memory.
	CHTRS_HTDL_ERR_SENDFAIL    = 1207, // Sending error. Unknow reason.
	CHTRS_HTDL_ERR_PORT        = 1208, // Could not open the specified serial port.
	CHTRS_HTDL_ERR_CTSOFF      = 1209, // Serial port does not support CTS (clear-to-send) event
	CHTRS_HTDL_ERR_SQUE        = 1210, // ���Ͷ�����
	CHTRS_HTDL_ERR_RQUE        = 1211, // Too many items are queueing to be received

	CHTRS_MTX_ERR_ENQUIRE      = 1300, // ENQ����ʧ�ܣ����ܷ��ͱ���
	CHTRS_MTX_ERR_SEND         = 1301, // ����������Ȼ����ʧ��

	CHTRS_RFID_A_SUM_ERR       = 1500, // Ʊ��A��RFID����SUMֵ�쳣
	CHTRS_RFID_B_SUM_ERR       = 1501, // Ʊ��B��RFID����SUMֵ�쳣
	CHTRS_RFID_A_B_SUM_ERR     = 1502, // Ʊ��A��B��RFID����SUMֵ�쳣

	CHTRS_MSG_EMPTY				= 1350, // The message is empty now.
	CHTRS_MSG_OVRFLW	        = 1351, // The buffer is too small to store message.
	CHTRS_CMD_INVALID	        = 1352, // Unsupported command.
	CHTRS_CMD_PARAM				= 1400, // Invalid parameter.
	CHTRS_CMD_REJECT	        = 1401  // Too many commands are queuing, could not send command.
}CH_ERR_DETAIL;
// ����״̬�ṹ��
/*
�ṹ���б���˵��
	uiProviderId	ģ�鳧�ұ�ʶ�����Ž�0x01������0x02������ 0x03�����0x04������0x06��ŷķ��0x05������0x07��
	uiModuleType	ģ�����ͱ�ʶ��0x04Ӳ�Ҵ���ģ�顣
	uiType	״̬���ͣ�0-������1-���棻2-���ϣ�3-ֻ����ģʽ��4-ֻ����ģʽ��
	uiErrorType	��׼״̬���룭ע1 
	uiErrorCode	ԭʼ״̬���룭ע2
	cReverse	Ԥ����Ϣ
ע1�������׼״̬���붨��;ģ���п��ܷ��ض��״̬���롣
ע2��Ϊ��ͬģ�鳧���ṩ��ԭʼ״̬���룬ͬʱÿ��ԭʼ״̬���붼�ܹ���Ӧ��Ψһ�ı�׼״̬�����У�ԭʼ�����Ӧ��׼״̬�������Ϊ���һ����λ��ͨ����ֵ��������ʾ����ϸ�Ĵ���ԭ�򼰹��ϵ㶨λ��
*/
typedef struct
{
	UINT uiProviderId;
	UINT uiModuleType;
	UINT uiType;
	UINT uiErrorType[16];
	UINT uiErrorCode[16];
	char cReverse[8];
} tCHADevReturn;

// ��ҽṹ 
typedef struct _tClearCoin
{
	BOOL bClearMHopper1; // ��������2��ұ�־
	BOOL bClearMHopper2; // ��������1��ұ�־
	BOOL bClearChange1;  // ���䡢������1��ұ�־
	BOOL bClearChange2;  // ���䡢������2��ұ�־

}tCHAClearCoin;

// ģ������������Ϣ�ṹ�� �����࣬��ǰ�汾ʹ�õڶ��ֽṹ
/*
ģ������������Ϣ�ṹ���б���˵��
	uiCoinBoxNum	Ӳ����������
	uiBoxType	�������ͣ�1���ӱ��䣻2��ѭ���䣻3���ݴ�����4��������������5�������䡣
	uiBoxNo	������ţ���ʼֵΪ0��ͬһ����������ŵ����źţ�����ӱ�������4������ŷֱ�Ϊ1��4��
	uiCoinValue	��λ�֣����������ܴ��Ӳ�ҵ������ֶ�ֵֻ��Ϊ100��50��0�� ����0��ʾ����ȷ������������
	uiCoinNum	������Ӳ�ҵ����� 
	uiCoinMaxNum	�������ܴ���Ӳ���������� 
	uiBoxStatus	����״̬�� 0-������1-δ��װ��2-������3-������4-�ѿգ�5-���ա���״̬Ϊģ��Ӳ������״̬��ͨ�������жϵ�״̬����λ�������ж�
*/
typedef struct
{
	UINT uiBoxType;
	UINT uiBoxNo;
	UINT uiCoinValue;
	UINT uiCoinNum;
	UINT uiCoinMaxNum;
	UINT uiBoxStatus;
} tCoinBoxValueInfo;
typedef struct
{
	UINT uiCoinBoxNum;
	tCoinBoxValueInfo* pCoinBoxValueInfo;
} tCHACoinBoxInfo;
//////////////////////////////////////////////////////////////////////////
// �ṹ��Ӳ����������
typedef struct _struct_box_info  
{
	WORD OneY_inHopper;							   //1ԪHopper���е�Ӳ������ 
	WORD HalfY_inHopper;                           //5��Hopper���е�Ӳ������ 
	WORD OneY_preparation;                         //1Ԫ�������е�Ӳ������
	WORD HalfY_preparation;                        //5�Ǳ������е�Ӳ������
	WORD OneY_inRecover;						   //1Ԫ�������е�Ӳ������
	WORD OneY_maxthreshold_inRecover;				//������1Ԫ������ֵ

	_struct_box_info()
	{
		OneY_inHopper=0;
		HalfY_inHopper=0;
		OneY_preparation=0;
		HalfY_preparation=0;
		OneY_inRecover=0;
		OneY_maxthreshold_inRecover=200;
	}
}tCoinBoxInfo;
// ����Ӳ����Ϣ�ṹ��
typedef struct
{
	tCoinBoxValueInfo stCoinBoxValueInfo[3];
	UINT uiEjectCoinNum;
} tCHACoinValueInfo;

// ������״̬�ṹ�壨ĳЩ���һ�ʹ�ø����ͽṹ��
/*
	������״̬�ṹ���б���˵��
	uiSensorNum	����������
	uiSensorID	������ID
	uiStatus	0��δ�ڵ���1���ڵ���
*/
typedef struct
{
	UINT uiSensorID;
	UINT uiStatus;
} tSensorStatusEx;
typedef struct
{
	UINT uiSensorNum;
	tSensorStatusEx* pSensorStatus;
} tCHASensorStatus;

// ������λ���ݴ�������
typedef enum CH_SENSOR_POS{
	BYTE_IN_CH_POS_00	= 0x01,
	BYTE_IN_CH_POS_01	= 0x02,
	BYTE_IN_CH_POS_02	= 0x04,
	BYTE_IN_CH_POS_03	= 0x08,
	BYTE_IN_CH_POS_04	= 0x10,
	BYTE_IN_CH_POS_05	= 0x20,
	BYTE_IN_CH_POS_06	= 0x40,
	BYTE_IN_CH_POS_07	= 0x80,
};

// ģ��״̬�����Ҳ�ͬ����ȡ��ʽ��ͬ���ýṹ��lib�㸳ֵ����λ��Ӧ��
typedef struct _struct_dev_status
{
	// ��е״̬��ϸ��Ϣ
	WORD wHopperACnt;			//Aѭ����������Ӳ������
	WORD wHopperBCnt;			//Bѭ����������Ӳ������
	WORD wPreparationACnt;		//A��������Ӳ������
	WORD wPreparationBCnt;		//B��������Ӳ������
	WORD wRecoverCnt;			//��������Ӳ������(������ʵ��5��Ӳ�һ�����ʹ�ã����Դ˴��������ִ�������ֻ��1ԪӲ��ʹ��)
	
	// ����
	bool bIsCoinModuleStandby;	// Ӳ��ģ���Ƿ�λ��true:��λ��false��δ��λ
	bool bIsMoneyBoxExist;		// �������Ƿ�λ
	// Hopper A
	bool bIsHopperAFull;		// Hopper �Ƿ���
	bool bIsHopperAEmpty;		// Hopper �Ƿ��
	// Hopper B
	bool bIsHopperBFull;		// Hopper �Ƿ���
	bool bIsHopperBEmpty;		// Hopper �Ƿ��
	// ����Ǯ��A
	bool bIsChangeBoxAInstall;	// Change BoxA�Ƿ�װ
	bool bIsChangeBoxAFull;		// Change BoxA�Ƿ���
	bool bIsChangeBoxAEmpty;	// Change BoxA�Ƿ��
	// ����Ǯ��B
	bool bIsChangeBoxBInstall;	// Change BoxB�Ƿ�װ
	bool bIsChangeBoxBFull;		// Change BoxB�Ƿ���
	bool bIsChangeBoxBEmpty;	// Change BoxB�Ƿ��
	_struct_dev_status()
	{
		wHopperACnt = 0;
		wHopperBCnt = 0;
		wPreparationACnt = 0;
		wPreparationBCnt = 0;
		wRecoverCnt = 0;
		bIsCoinModuleStandby = false;
		bIsMoneyBoxExist = true;
		bIsHopperAFull = false;
		bIsHopperAEmpty = false;
		bIsHopperBFull = false;
		bIsHopperBEmpty = false;
		bIsChangeBoxAInstall = false;
		bIsChangeBoxAFull = false;
		bIsChangeBoxAEmpty = false;
		bIsChangeBoxBInstall = false;
		bIsChangeBoxBFull = false;
		bIsChangeBoxBEmpty = false;
	}
	inline void Deserialize(const BYTE* data)
	{
		BYTE MechanismStatus[10] = {0};
		memcpy(MechanismStatus,data + 10,10);

		bIsCoinModuleStandby = !(MechanismStatus[0] & BYTE_IN_CH_POS_03);
		bIsHopperAFull		 = (MechanismStatus[2] & BYTE_IN_CH_POS_04);
		bIsHopperAEmpty		 = (MechanismStatus[2] & BYTE_IN_CH_POS_00);

		bIsHopperBFull		 = (MechanismStatus[3] & BYTE_IN_CH_POS_04);
		bIsHopperBEmpty		 = (MechanismStatus[3] & BYTE_IN_CH_POS_00);

		bIsChangeBoxAInstall = !(MechanismStatus[4] & BYTE_IN_CH_POS_05);
		bIsChangeBoxAFull	 = (MechanismStatus[4] & BYTE_IN_CH_POS_04);
		bIsChangeBoxAEmpty	 = (MechanismStatus[4] & BYTE_IN_CH_POS_00);

		bIsChangeBoxBInstall = !(MechanismStatus[5] & BYTE_IN_CH_POS_05);
		bIsChangeBoxBFull	 = (MechanismStatus[5] & BYTE_IN_CH_POS_04);
		bIsChangeBoxBEmpty	 = (MechanismStatus[5] & BYTE_IN_CH_POS_00);
	}
} tCHADevStatus;

/*
// ����Ӳ����Ϣ�ṹ��
	����Ӳ����Ϣ�ṹ���б���˵��
	uiCoinValue	��λ�֣�����Ӳ�ҵ������ֶ�ֵֻ��Ϊ100��50��
	uiCoinNum	��Ӧ�������Ӳ�ҵ����� 
	uiCoinTypeNum	������Ӳ��������������������֣�

*/
typedef struct
{
	UINT uiCoinValue;
	UINT uiCoinNum;
} tCoinChangeInfo;

// ���ý��ṹ
typedef struct _tSetCoinNum
{
	int uiMHopper1Num; // ��������2Ӳ�Ҹ�����С��1100��	//�人11����ר��
	int uiMHopper2Num; // ��������1Ӳ�Ҹ�����С��1100��	//�人11����ר��

	UINT uiCoinBoxCoinANum; // Ӳ��Ǯ��Ӳ��A����������Ӳ��BС��3000��
	UINT uiCoinBoxCoinBNum; // Ӳ��Ǯ��Ӳ��B����������Ӳ��AС��3000��

	BYTE byEscrow1Num; // �ݴ���1Ӳ������С��70��
	BYTE byEscrow2Num; // �ݴ���2Ӳ������С��70��

	BYTE byMHopper1Type; // ��������2Ӳ�����ͣ�1 = 1ԪӲ�ң�2 = 5��Ӳ�ҡ�	//�人11����ר��
	BYTE byMHopper2Type; // ��������1Ӳ�����ͣ�1 = 1ԪӲ�ң�2 = 5��Ӳ�ҡ�	//�人11����ר��
		
	BYTE byEjectCoinNum; // �˱Ҹ���

}tCHASetCoinNum;

// ��Ʊ�ṹ
typedef struct _tCoinInfo
{ 
	char acCurrency[4]; // ����
	int iCount;			// ����
	long lDenomination; // ���
	char cSerial;		// ��Ʊ����(���Ļ������'4','5')
}tCHACoinInfo;

/*
typedef struct
{
	UINT uiCoinTypeNum;
	tCoinChangeInfo* pCoinChangeInfo;
} tCHAChangeNum;
*/
typedef struct 
{
	WORD wMHopper1Num; // ѭ��������1������	
	WORD wMHopper2Num; // ѭ������2������	
	WORD wChange1Num;//	������1
	WORD wChange2Num;// ������2
}tCHAChangeNum;

typedef struct COIN_ACCEPTABLE_{
	bool CH_COIN_ALLOW_1 ;
	bool CH_COIN_ALLOW_05;
	COIN_ACCEPTABLE_()
	{
		CH_COIN_ALLOW_1 = true;
		CH_COIN_ALLOW_05= true;
	}

}COIN_ACCEPTABLE;

//
typedef struct _ch_operator_coin_num_info
{
	unsigned short escrow1;		// �ݴ�1Ӳ�����仯
	unsigned short escrow2_05;	// �ݴ�2Ӳ�����仯
	unsigned short hopper1;		// hopper1Ӳ�����仯
	unsigned short hopper2;		// hopper2Ӳ�����仯
	unsigned short reject;		// ���ν����˱�

	_ch_operator_coin_num_info(){
		escrow1   =0;    
		escrow2_05=0;   
		hopper1    =0;  
		hopper2    =0;    
	}

} CH_OPERATOR_COIN_NUM_INFO;

#pragma pack(pop)


/*****************************************************************************/
/*                                                                           */
/*  Function Declarations                                                    */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
// ���½ӿ���LIBʵ�֣���DLL��ʹ�ã���������ṩdll��ɷ���TIMģ��ʵ�֣��������
// �ṩ����Э�飬�����װ��Э�����ʵ�����½ӿ�
/* # wang feng                                                               */
/*****************************************************************************/
// ͨѶ����
AFC_API_DLL_IMP int CHA_CommOpen(UINT uiCommPort, UINT uiBaudRate,CString logPath,CString logName, tCHADevReturn * pDevStatus);
// ��ʼ��
/*
btXinCtl:
	0x00 �ݴ沿Ӳ���͵����ҿ�
	0x10 �ݴ沿Ӳ���͵�Hopper�������
	0x20 �ݴ沿Ӳ�ұ���ԭ��
*/
AFC_API_DLL_IMP int CHA_Init(BYTE btXinCtl,tCHADevReturn * pDevStatus);
// ��ȡ�豸״̬
AFC_API_DLL_IMP int CHA_GetDevStatus(tCHADevReturn * pDevStatus);
// ��ȡ������״̬
AFC_API_DLL_IMP int CHA_GetSensorStatus(tCHASensorStatus* pSensorStatus, tCHADevReturn * pDevStatus);
// ��ȡ����������Ϣ
AFC_API_DLL_IMP int CHA_GetCoinBoxInfo(tCHADevStatus *pCoinBoxInfo,tCHADevReturn * pDevStatus);
// ����Ӳ������
AFC_API_DLL_IMP int CHA_SetCoinBoxInfo(tCoinBoxInfo *pCoinBoxInfo,tCHADevReturn * pDevStatus);
// ��ʼ����Ӳ��
AFC_API_DLL_IMP int CHA_StartReceiveCoin(tCHADevReturn * pDevStatus);
// ��������Ӳ��
AFC_API_DLL_IMP int CHA_StopReceiveCoin(tCHADevReturn * pDevStatus);
// ��ȡ����Ӳ����Ϣ
AFC_API_DLL_IMP int CHA_GetReceiveNumber(tCHACoinValueInfo *pCoinValueInfo, tCHADevReturn * pDevStatus);
// ����Ӳ��
AFC_API_DLL_IMP int CHA_AcceptCoin(tCHACoinValueInfo *pCoinValueInfo, tCHADevReturn * pDevStatus);
// �˳�Ӳ��
AFC_API_DLL_IMP int CHA_EjectCoin(UINT * uiReturnCoinNum ,tCHADevReturn * pDevStatus);
// ����
AFC_API_DLL_IMP int CHA_ChangeCoin(tCHAChangeNum * pChangeNum,tCHADevReturn * pDevStatus);
// ��������
AFC_API_DLL_IMP int CHA_StartReplaceBOX(UINT uiBoxType, UINT uiBoxNo,UINT uiOpType,tCHADevReturn * pDevStatus);
// ֹͣ��������
AFC_API_DLL_IMP int CHA_StopReplaceBOX(UINT uiBoxType, UINT uiBoxNo, UINT uiOpType,tCHADevReturn * pDevStatus);
// ���Ӳ��
AFC_API_DLL_IMP int CHA_ClearCoin(UINT uiBoxTypeOutput, UINT uiBoxNoOutput, UINT uiBoxTypeInput, UINT uiBoxNoInput, tCoinBoxInfo *pCoinBoxInfo,UINT uiCoinNum,tCHADevReturn * pDevStatus);
// ������RFID��Ϣ
AFC_API_DLL_IMP int CHA_ReadRFIDInfo(UINT uiBoxType, UINT uiBoxNo,unsigned char RFIDInfo[36],tCHADevReturn * pDevStatus);
// д����RFID��Ϣ
AFC_API_DLL_IMP int CHA_WriteRFIDInfo(UINT uiBoxType, UINT uiBoxNo,unsigned char RFIDInfo[36],tCHADevReturn * pDevStatus);
// ��ȡģ����ʰ汾
AFC_API_DLL_IMP int CHA_GetVersion(char cVersion[32],tCHADevReturn * pDevStatus);
// ��ȡģ�����
AFC_API_DLL_IMP int CHA_GetSerialNumber(char cVersion[32],tCHADevReturn * pDevStatus);
// ��ȡ�������
AFC_API_DLL_IMP int CHA_GetAuditData(tCHACoinBoxInfo *pCoinBoxInfo,tCHADevReturn * pDevStatus);
// �ر�ͨѶ
AFC_API_DLL_IMP int CHA_CloseComm(tCHADevReturn * pDevStatus);

//#if defined (__cplusplus)
//} // end of extern "C"
//#endif

#endif