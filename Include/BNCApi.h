//ֽ��ѭ��ģ��
#ifndef _BNC_API_H
#define _BNC_API_H

#include "Apidef.h"

#define MAX_BOXNUM 6

#pragma pack(push,1)


// error code
typedef enum _enum_brh_op_errs {
	BNC_NO_ERROR = 0,			/**< Returned by synchronious method when there is no error */
	// API error �� From 1 to 1000 ��
	BNC_API_NOT_OPENED = 0x01,			/**< The library was not opened by a previous bnr_Open= , call */
	BNC_API_FILE_NOT_FOUND = 0x02,			/**< A file given in parameter can not be found */
	BNC_API_NO_MEMORY = 0x03,			/**< Insufficient memory available */
	BNC_API_INVALID_PARAMETER = 0x04,			/**< One of the parameter given in the function call is invalid */
	BNC_API_INVALID_HANDLE = 0x05,			/**< The API was not able to get a valid hande from Windows system. */
	BNC_API_MISSING_DEPENDENCY = 0x06,			/**< The API was not able to delay-load something it needs = e.g. a DLL,. */
	BNC_API_ACCESS_DENIED = 0x07,			/**< Acces of this command is denied. */

	// self define
	BNC_EJECT_SUCCESS = 997,			// �˳�����ʶ��ģ��ɹ�
	BNC_ERR_EVENT_FAILURE = 998,			// ���������¼�ʧ�ܡ�
	BNC_ERR_TIMEOUT = 999,			/** �Զ��壬�첽������ʱ. */

	// XFS error �� From 1001 to 10000 ��
	//BRH_ERR_NOT_USED					= -1,			/**< Field not used. */ 
	BNC_ERR_ILLEGAL = 1010,			/**< Illegal request. */
	BNC_ERR_NOHARDWARE = 1011,			/**< The module is not connected to the BNR. */
	BNC_ERR_NOEXIST = 1013,			/**< The requested item =reports or other data, does not exist. */
	BNC_ERR_FAILURE = 1015,			/**< The operation failed. */
	BNC_ERR_BUSY = 1017,			/**< The BNR is busy =moving or about to move bill,. */
	BNC_ERR_PARAMETER_INVALID = 1018,			/**< One of the parameters given was invalid. */
	BNC_ERR_NOT_SUPPORTED = 1022,			/**< The operation is not supported by this firmware. */
	BNC_ERR_CANCELLED = 1021,			/**< The operation was cancelled. */
	BNC_ERR_FIRMWARE = 1023,			/**< Error during firmware update or no runnable firmware in device. */
	BNC_ERR_HARDWAREERROR = 1025,			/**< Error occurred that is hardware related. */
	/* ----Cash Module error---- */
	BNC_ERR_CDR_OFFSET = 6071,
	BNC_ERR_CDR_CASHIN_ACTIVE = 6072,			/**< The device has already issued a cashInStart command. */
	BNC_ERR_CDR_CASH_DEVICE_ERROR = 6073,			/**< A selected cash device caused an error. */
	BNC_ERR_CDR_CASH_UNIT_ERROR = 6074,			/**< A selected cash unit caused an error. */
	BNC_ERR_CDR_INVALID_CASH_UNIT = 6080,			/**< Invalid cash unit ID. */
	BNC_ERR_CDR_INVALID_CURRENCY = 6081,			/**< The currency is not available = defined, in the BNR. */
	BNC_ERR_CDR_INVALID_MIXNUMBER = 6085,			/**< The number refers to a defined and reserved mix algorithm. */
	BNC_ERR_CDR_NOT_DISPENSABLE = 6087,			/**< The amount is not dispensable. */
	BNC_ERR_CDR_NO_BILLS = 6088,			/**< There were no bills on the stacker to present.*/
	BNC_ERR_CDR_NO_CASHIN_STARTED = 6089,			/**< CashInStart was not called. */
	BNC_ERR_CDR_TOO_MANY_BILLS = 6092,			/**< The request would require too many bills to be dispensed. */
	BNCBRH_ERR_CDR_USER_ERROR = 2001,         /**< A person has stopped the device operation. i.e. manupulating the outlet flap or inserting a bill at the inlet when it is not expected. */

	// USB error �� From 10001 ��
	BNC_USB_CRC = 10000 + 0x01,
	BNC_USB_BTSTUFF = 10000 + 0x02,
	BNC_USB_DATA_TOGGLE_MISMATCH = 10000 + 0x03,
	BNC_USB_STALL_PID = 10000 + 0x04,
	BNC_USB_DEV_NOT_RESPONDING = 10000 + 0x05,
	BNC_USB_PID_CHECK_FAILURE = 10000 + 0x06,
	BNC_USB_UNEXPECTED_PID = 10000 + 0x07,
	BNC_USB_DATA_OVERRUN = 10000 + 0x08,
	BNC_USB_DATA_UNDERRUN = 10000 + 0x09,
	BNC_USB_BUFFER_OVERRUN = 10000 + 0x0C,
	BNC_USB_BUFFER_UNDERRUN = 10000 + 0x0D,
	BNC_USB_NOT_ACCESSED = 10000 + 0x0F,
	BNC_USB_FIFO = 10000 + 0x10,
	BNC_USB_ENDPOINT_HALTED = 10000 + 0x30,
	BNC_USB_NO_MEMORY = 10000 + 0x0100,
	BNC_USB_INVALID_URB_FUNCTION = 10000 + 0x0101,
	BNC_USB_INVALID_PARAMETER = 10000 + 0x0102,
	BNC_USB_ERROR_BUSY = 10000 + 0x0103,
	BNC_USB_REQUEST_FAILED = 10000 + 0x0104,
	BNC_USB_INVALID_PIPE_HANDLE = 10000 + 0x0105,
	BNC_USB_NO_BANDWIDTH = 10000 + 0x0106,
	BNC_USB_INTERNAL_HC_ERROR = 10000 + 0x0107,
	BNC_USB_ERROR_SHORT_TRANSFER = 10000 + 0x0108,
	BNC_USB_BAD_START_FRAME = 10000 + 0x0109,
	BNC_USB_ISOCH_REQUEST_FAILED = 10000 + 0x010A,
	BNC_USB_FRAME_CONTROL_OWNED = 10000 + 0x010B,
	BNC_USB_FRAME_CONTROL_NOT_OWNED = 10000 + 0x010C,
	BNC_USB_CANCELED = 10000 + 0x0200,
	BNC_USB_CANCELING = 10000 + 0x0201,
	BNC_USB_ALREADY_CONFIGURED = 10000 + 0x0202,  /**< Device is already configured. */
	BNC_USB_UNCONFIGURED = 10000 + 0x0203,  /**< Device is unconfigured. */
	BNC_USB_NO_SUCH_DEVICE = 10000 + 0x0204,  /**< The specified Device doesn't exists. */
	BNC_USB_DEVICE_NOT_FOUND = 10000 + 0x0205,  /**< The specified Device not found in system. */
	BNC_USB_NOT_SUPPORTED = 10000 + 0x0206,  /**< Operation isn't supported by Driver */
	BNC_USB_IO_PENDING = 10000 + 0x0207,  /**< I/O operation is still in progress */
	BNC_USB_IO_TIMEOUT = 10000 + 0x0208,  /**< Request timeout */
	BNC_USB_DEVICE_REMOVED = 10000 + 0x0209,  /**< The USB device was removed = power off or disconnected,. */
	BNC_USB_PIPE_NOT_LINKED = 10000 + 0x020A,  /**< Pipe not linked */
	BNC_USB_CONNECTED_PIPES = 10000 + 0x020B,  /**< Device cannot be reconfigured because pipe connections already exist. */
	BNC_USB_DEVICE_LOCKED = 10000 + 0x020C,  /**< The device is already locked by another application. */

}ENUM_BRH_ERRS;

//���ṹ��˵��
//��������״̬�����ṹ�� 
typedef  struct 
{
	//������Ϣ
	UINT uiProviderId; //ģ�鳧�ұ�ʶ
	int iType;   //�������ͣ�0-������1-���棻2-����
	int iStdErrorCode;  //ͳһά���Ĵ������
	//2.ģ���ԭʼ��Ϣ������λ������ʾά���� 
	int iErrorCode;  //������� ���ɲ�ͬģ�鳧���ṩ��  
	char acDevReturn[128]; //  Ӳ��������Ϣ 
	char acReserve[128]; //  ������Ϣ    
} tBncDevReturn;

// �豸��ϸ״̬
typedef struct tBncSysDevStatus
{
	bool bIsCollectBoxInstalled;
	bool bIsChangeBoxInstalled;
	tBncSysDevStatus(){
		bIsChangeBoxInstalled = true;
		bIsCollectBoxInstalled = true;
	}
};
typedef struct bnc_face_accpted_table {
	bool bIsBanknote1Yuan;
	bool bIsBanknote5Yuan;
	bool bIsBanknote10Yuan;
	bool bIsBanknote20Yuan;
	bool bIsBanknote50Yuan;
	bool bIsBanknote100Yuan;
	bnc_face_accpted_table()
	{
		bIsBanknote1Yuan = false;
		bIsBanknote5Yuan = false;
		bIsBanknote10Yuan = false;
		bIsBanknote20Yuan = false;
		bIsBanknote50Yuan = false;
		bIsBanknote100Yuan = false;
	}

}BNC_FACE_ACEPTED_TABLE;
//����ʼ��������Ϣ
typedef struct
{
	UINT uiOutNumber;//�˳�����
	UINT uiRetractNumber;//��������
}tBncInitNumInfo;

//����Ʊϵ�н�����Ϣ�ṹ��
typedef struct tBncSetInhibitItem
{
	int  iValue;    //����λΪ��
	bool  bAccepted; //�Ƿ����  
	tBncSetInhibitItem(){
		bAccepted = false;
	}
};
typedef struct tBncSetInhibitList
{ 
	int iNumOfItems; //�ֽ������
	tBncSetInhibitItem  *psBncCashInfo;//�ֽ������ַָ��
	tBncSetInhibitList(){
		iNumOfItems = 0;
		psBncCashInfo = NULL;
	}
	bool IsAccepted(const int nValue)
	{
		for(int nIndex = 0; nIndex < iNumOfItems; nIndex++)
		{
			if (psBncCashInfo[nIndex].iValue == nValue)
			{
				return psBncCashInfo[nIndex].bAccepted;
			}
		}
		return false;
	}
};

//���ֽ���Ϣ�ṹ��
typedef struct _BncCashItem
{
	unsigned int  iValue; //���ճ�Ʊ����λΪ��
	unsigned int  iCount; //��Ʊ����
}tBncCashItem;
typedef struct _BncCashInfo
{
	int iNumOfItems; //�ֽ������
	tBncCashItem  *psBncCashInfo;
	_BncCashInfo(){
		iNumOfItems = 0;
		psBncCashInfo = NULL;
	}
}tBncCashInfo;
// Ѻ������
typedef struct tBncEnCashInfo{
	DWORD dwCashIntoAmount;

	WORD wRecyclerAIntoCount;
	WORD wRecyclerBIntoCount;
	WORD wRecyclerCIntoCount;
	WORD wRecyclerDIntoCount;

	WORD wCashBox_CNY1_IntoCount;
	WORD wCashBox_CNY5_IntoCount;
	WORD wCashBox_CNY10_IntoCount;
	WORD wCashBox_CNY20_IntoCount;
	WORD wCashBox_CNY50_IntoCount;
	WORD wCashBox_CNY100_IntoCount;

	tBncEnCashInfo(){
		dwCashIntoAmount = 0;

		wRecyclerAIntoCount = 0;
		wRecyclerBIntoCount = 0;
		wRecyclerCIntoCount = 0;
		wRecyclerDIntoCount = 0;

		wCashBox_CNY1_IntoCount = 0;
		wCashBox_CNY5_IntoCount = 0;
		wCashBox_CNY10_IntoCount = 0;
		wCashBox_CNY20_IntoCount = 0;
		wCashBox_CNY50_IntoCount = 0;
		wCashBox_CNY100_IntoCount = 0;
	}

};//Ѻ������
//��ֽ��Ǯ��״̬�ṹ��
typedef struct 
{
	int iModuleStatus; /* 0 ������1 �踴λ 2 �쳣 */
	int iBoxStatus;  /* 0 ��װ���������� 1 ���� 2 �� 3 δ��װ */
	int iInStacker; /* 0 �ޣ� 1 �г�Ʊ���ݴ� */
}tBncStatus;

//������Ǯ��ṹ�� 
typedef struct
{
	UINT uiBoxType;   //�������ͣ�0-�ϱ��� 1-1Ԫֽ����, 2-5Ԫֽ����, 3-10Ԫֽ����, 4-20Ԫֽ����, 5-50Ԫֽ����, 6-100Ԫֽ����*
	UINT uiBoxNo;     /**������ţ�0 ~ 6 ���У� 0�ŷϱ��� 1��Ϊ5Ԫ�����䣬2��Ϊ1Ԫ������ */
	UINT uiBillValue; /**��λ�֣����������ܴ��ֽ�ҵ�������0��ʾ����ȷ�������������*/
	UINT uiBillNum;   /**������ֽ�ҵ�����*/
	UINT uiBillMaxNum;/**�������ܴ���ֽ����������*/
	UINT uiBoxStatus; /**������״̬��0-������1-δ��װ��2-������3-������4-�ѿգ�5-����,��״̬Ϊģ��Ӳ������״̬��ͨ�������жϵ�״̬����λ�������ж�*/
} tBncCashBoxValueInfo;

//��ģ������������Ϣ�ṹ��
typedef  struct
{
	tBncCashBoxValueInfo pCashBoxValueInfo[MAX_BOXNUM];
	tBncCashBoxValueInfo stCashNGBoxValueInfo;
}tBncBillBoxInfo;

//���䳮�ṹ��/���Ǯ�䷴��
typedef struct
{
	UINT uiAmount;				      //����
	UINT uiDispenseNumber[MAX_BOXNUM];//ÿ��Ǯ����Ҫ��Ǯ������
	UINT uiOutNumber[MAX_BOXNUM];    //ʵ��ÿ��Ǯ���Ǯ�����������أ������ǣ�ѭ��1.ѭ��2��ѭ��3��ѭ��4��������
	UINT uiRejectNumber[MAX_BOXNUM]; //����������ÿ��Ǯ��ϳ����յ����������أ�
} tBncChangeNum;
//����ƽṹ��
typedef struct
{
	UINT uiNGBoxAccInNum;       //�ۼƽ���ϳ�������
	UINT uiBoxAccOutNum;       //�ۼƳ�������
} tBncAuditCashNum;
//��RFID��Ϣ�ṹ��
typedef struct
{
	unsigned char uzCashBoxID[4]; // Ǯ����
	unsigned char uzOperateID[3]; // ����ԱID
	unsigned char uzDeviceID[4];// �豸ID
	unsigned char ucCashBoxStatus;// Ǯ��λ��״̬
	unsigned char ucCashBoxOperateStatus;// ������Ǯ��״̬
	unsigned char ucBillType;// ���ִ���
	unsigned char usBillCnt;// ����
	unsigned int  uiBillAmount;// ֽ���ܽ��
	unsigned char ucStationCode[2];// ��վ����
	unsigned char ucInstallPosit;// ��װλ��
	unsigned int  uiBlockOperateTime;// �����ʱ��
	unsigned char ucOperateTime[7];// ������ʱ��
	unsigned short usCheckField;// У���ֶ�
}tBncRfidInfo;
#pragma pack(pop)

/*****************************************************************************/
/*                                                                           */
// ���½ӿ���LIBʵ�֣���DLL��ʹ�ã���������ṩdll��ɷ���TIMģ��ʵ�֣��������
// �ṩ����Э�飬�����װ��Э�����ʵ�����½ӿ�
/* # wang feng                                                               */
/*****************************************************************************/
//��ͨ�Ŵ��ڴ�
// ����˵�������ô˽ӿڿɴ򿪵Ͳ㴮��ͨ�š�
// ����˵������23��
// 1	unsigned int	uiCommPort	In	����ͨ�ź�
// 2	unsigned int	uiBaudRate	In	������
// ����ֵ˵��
// 1	Int	0	�ɹ�
// 2	Int	1	���ڴ򿪳���
AFC_API_DLL_IMP int  BNC_open(unsigned int uiCommPort, unsigned int uiBaudRate,CString path, CString fileName);

//����ʼ��
// ����˵���� ��ʼ��ģ�飬���ģ���Ӳ������ģ��ָ�����ʼ״̬�ȡ�
// ����˵�����±�
// 1	tBncInitNumInfo *	pNumInfo	Out	�˳��ͻ���Ǯ����Ϣ
// 2	tBNDDevReturn	pDevStatus	Out	            �豸����״̬
// ����ֵ˵�����±�
// 1	Int	0	�ɹ�
// 2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int BNC_Init(tBncInitNumInfo *pNumInfo, tBncDevReturn * pDevStatus);

//��ͨ�Ŵ��ڹر�
//  ����˵�������ô˽ӿڿɹرյͲ㴮��ͨ�š�
// 	����ֵ˵��
// 	1	Int	0	�ɹ�
// 	2	Int	1	�رմ���
AFC_API_DLL_IMP int BNC_close();	

//����ȡģ��̼��汾
AFC_API_DLL_IMP int BNC_GetVersion(char* pVersion, tBncDevReturn * p_psStatus);
// ����˵�������ڻ�ȡ����ģ���ڵ�firmware�汾�ţ����ģ���У���Ŀǰֻ���GRG��ֽ��ģ����Ч��
// ����˵��
// 1	char*	pVersion	Out	�̼��汾������У�
// 2	tBncDevReturn &	p_psStatus	Out	����״̬��Ϣ
// ����ֵ˵������27��
// 1	Int	0	�ɹ�
// 2	Int	1	�رմ���


//������ʶ����ó�Ʊ
//  ����˵�����������������ÿɽ��յĳ�Ʊ�����ڽ�ֹ���յ��泮���˳���
// 	����˵������3��
// 	1	tBncSetInhibitList *	p_psBuyTicketSetInhibitList	In	������Ʊʱ��Ʊ������Ϣ�ṹ������
// 	2	tBncSetInhibitList *	p_psRechargeSetInhibitList	In	���ó�ֵʱ��Ʊ������Ϣ�ṹ������
// 	3	tBncDevReturn *	p_psStatus	Out	����BNA���ص��߼�������
// 	����ֵ˵��
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int  BNC_SetPrevalue(tBncSetInhibitList *p_psBuyTicketSetInhibitList, tBncSetInhibitList *p_psRechargeSetInhibitList, tBncDevReturn * p_psStatus);

//����λ
// ����˵������������������ͨ���еĳ�Ʊ����о�ָ�����������
// ����˵��
// 1	Int	iMode	In	���ͨ�����г�Ʊ������ѡ��Ĳ����� p_iResetMode �趨��������Ϊ��
//0��������ϵͳ���ݴ����ĳ�Ʊѹ��Ǯ��,���ʧ������ͣ�������
//1��������ϵͳ���ݴ����ĳ�Ʊ�˳�,���ʧ������ͣ�������
// Ĭ��Ϊ 0 ��ʽ
// 2	Int	iRetryTimes	In	��λ���Դ���
// 3	tBncInitNumInfo *	pNumInfo	Out	�˳��ͻ���Ǯ����Ϣ
// 4	tBncDevReturn *	p_psStatus	Out	����BNC���ص��߼�������
// ����ֵ˵��
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int BNC_Reset(int iMode, int iRetryTimes, tBncInitNumInfo *pNumInfo,tBncDevReturn * p_psStatus);


//����ȡģ��״̬
//  ����˵�������ô˽ӿڿɻ�ȡģ�鵱ǰ״̬����ϸ��Ϣ�鿴���ؽṹ�塣
// 	����˵��
// 	tBncDevReturn *	p_psStatus	Out	����BNC���ص��߼�������
// 	����ֵ˵��
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int BNC_GetStatus(tBncDevReturn * p_psStatus);

// ��ȡģ����ϸ״̬
AFC_API_DLL_IMP int BNC_GetSysDevStatus(tBncSysDevStatus* p_psSysStatus);

typedef struct _TAcceptorState
{
	BYTE  CurrentOCCode;
	char  CurrentCode[3];
	char  SequenceNr;
	BYTE  NrOfDocumentInintermediateStorage;
	char  ResolutionMode;
	BYTE  ValidationMode;
	BYTE  WorkMode;
}TAcceptorState;
// �ṹ�巵�ص�״̬��Ϣ;�����Ӳ��������Ϣ�ַ��������ݸ�ʽ����:
// [CurrentCode],[CurrentOCCode],[NrOfDocumentInintermediateStorage],[ResolutionMode],[SequenceNr] ,[ ValidationMode] ,[WorkMode] 

//����ȡ�����Ϣ
// 	����˵������ȡ�豸�������Ϣ��
// 	����˵�����±�
// 	1	tBncAuditCashNum *	pBncAuditCashNum	Out	���������Ϣ
// 	2	tBncDevReturn *	pDevStatus	Out	����״̬��Ϣ
// 	����ֵ˵�����±�
// 	1	int	0��ִ�гɹ���1��ִ��ʧ�ܡ�
AFC_API_DLL_IMP int BNC_GetAuditData(tBncAuditCashNum *pBncAuditCashNum, tBncDevReturn *pDevStatus);

//����ȡ����������Ϣ
// 	�������壺
// 	����˵������ȡǮ��ṹ����Ϣ��
// 	����˵�����±�
// 	1	tBncBillBoxInfo *	pBillBoxInfo	Out	����Ǯ��ṹ����Ϣ
// 	2	tBncDevReturn *	pDevStatus	Out	����״̬��Ϣ
// 	����ֵ����80��
// 	1	int	0��ִ�гɹ���1��ִ��ʧ�ܡ�
AFC_API_DLL_IMP int BNC_GetBillBoxInfo(tBncBillBoxInfo *pBillBoxInfo, tBncDevReturn *pDevStatus);

//����������������Ϣ
// 	�������壺
// 	����˵������������������Ϣ������ֽ��������
// 	����˵�����±�
// 	1	UNIT	uiSlotID	In	��λID
// 	2	tBncBillBoxInfo *	pBillBoxInfo	In	����������Ϣ
// 	3	tBncDevReturn *	pDevStatus	Out	����״̬��Ϣ
// 	����ֵ���±�
// 	1	int	0��ִ�гɹ���1��ִ��ʧ�ܡ�
AFC_API_DLL_IMP int BNC_SetBillBoxInfo(UINT uiSlotID, tBncBillBoxInfo *pBillBoxInfo, tBncDevReturn *pDevStatus);


//����ʼ���ճ�Ʊ
// 	����˵������о����Ԥ�����״̬��ָʾ�ƿ�ʼ��˸��ʾ�û�Ͷ��ֽ�ҡ�ʵ���鳮���˳�����Ʊѹ���ݴ����ȹ��ܡ�
// 	����˵�����±�
// 	1	tBncDevReturn *	p_psStatus	Out	����BNC���ص��߼�������
// 	����ֵ˵�����±�
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
// 	��ע���������̻߳����߳���������ʹֽ��ģ�����ȴ�����ֽ�ҵĹ���״̬�����򽫽������������ǳɹ�����ֽ�һ��������߳��е���BNC_Stop����ʹ�ú����˳����С�
AFC_API_DLL_IMP int BNC_Start(tBncDevReturn * p_psStatus);

//��ֹͣ���ճ�Ʊ
// 	����˵������оֹͣ���ճ�Ʊ��ָʾ��Ϩ��
// 	����˵�����±�
// 	1	tBncDevReturn *	p_psStatus	Out	����BNA���ص��߼�������
//      tBncCashInfo *p_psCashInfo  Out �����ѽ��ճ�Ʊ����
// 	����ֵ˵�����±�
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int BNC_Stop(tBncEnCashInfo *p_psCashInfo,tBncDevReturn * p_psStatus);

//����ȡʶ��Ʊ��Ϣ
// 	����˵������ȡ��о���յĳ�Ʊ��Ϣ��
// 	����˵�����±�
// 	1	tBncCashInfo *	p_psCashInfo	Out	���س�Ʊ��Ϣ�ṹ�壬��ʱǮ�����Ϣ
// 	2	BYTE&	p_byOperation	Out	���һ�Ŵ���ֽ�ҵ�״̬ 
// 		0:û�г�Ʊ����; 
// 		1:�޷�ʶ��ĳ�Ʊ�˳����˳���; 
// 		2:�û����˳��ڰѳ�Ʊ������ʶ�����ȡ�������˳��ģ�ȡ��; 
// 		3:��Ʊ�����ֱ�ǿ��ק��; 
// 		4:��Ʊ������; 
// 		5:�泮�������; 
// 		6:��Ʊ�������ҳ�ʱ����ֹͣ����; 
// 		7:�˳����г�Ʊδȡ�߳�ʱ; 
// 		8:�볮�����ݴ����г�Ʊ���ڴ���; 
// 		9:Ǯ���Ѿ�ȡ��; 
// 		10:Ǯ������; 
// 		11:��о�����ڳ�ʱ������(��������); 
// 		12:δ֪��������ͣ����
// 	3	tBncDevReturn *	p_psStatus	Out	����BNC���ص��߼�������
// 
// 	����ֵ˵�����±�
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
// 
// 	��ע������BNC_Start��ִ�гɹ��󣬵��øú�������ȡ��ʱǮ�������һ��ֽ�ҵĴ�����Ϣ��
// 	e)	����G&D��ֽ��ģ�飬p_byOperation���Ի�ȡ0��1��3��5��
// 	f)	����MEI��ֽ��ģ�飬p_byOperation���Ի�ȡ0��1��3��5��
// 	g)	����G&D��ֽ��ģ�飬p_byOperation���Ի�ȡ0��1��5��6��7��9��10��
// 	h)	����Ǯ��������Ǯ����ȡ�ߣ���о���ϣ�δ֪������������󣬿���ͨ��BNA_ GetStatu��Ӳ��������Ϣ���жϻ�ȡ��
AFC_API_DLL_IMP int  BNC_GetCashInfo(tBncCashInfo *p_psCashInfo, BYTE& p_byOperation, tBncDevReturn *p_psStatus);

//��ѹ��
// 	����˵�������ݴ�����ֽ��ȫ��ѹ��Ǯ�䡣
// 	����˵�����±�
// 	1	tBncDevReturn *	p_psStatus	Out	����BNC���ص��߼�������
// 	����ֵ˵�����±�
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int  BNC_Encash(tBncDevReturn *p_psStatus);

//���˳�
// 	����˵�������ݴ�����ֽ��ȫ���˳���
// 	����˵�����±�
// 	1	tBncDevReturn *	p_psStatus	Out	����BNA���ص��߼�������
// 	����ֵ˵�����±�
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int  BNC_Refund(tBncDevReturn *p_psStatus);


//����ȡǮ��ID
// 	����˵�������ô˽ӿڿɻ�ȡǮ��ID����ϸ��Ϣ�鿴���ؽṹ�塣
// 	����˵�����±�
// 	1	char*	p_BoxID	Out	��ȡǮ��ID
// 	2	tBncDevReturn *	p_psStatus	Out	����BNC���ص��߼�������
// 
// 	����ֵ˵�����±�
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int BNC_GetBoxID(char * p_BoxID, tBncDevReturn * p_psStatus);

//�������䳮
// 	����˵���������䳮
// 	����˵�����±�
// 	1	tBncChangeNum *	pChangeNum	In/Out	�����ֽ����������Ϣ
// 	2	tBncDevReturn *	pDevStatus	Out	����״̬��Ϣ
// 	����ֵ˵�����±�
// 	1	int	0��ִ�гɹ���1��ִ��ʧ�ܡ�
AFC_API_DLL_IMP int BNC_ChangeBill(tBncChangeNum *pChangeNum, tBncDevReturn *pDevStatus);

//��ȡ������
// 	����˵����ȡ��������
// 	����˵�����±�
// 	1	tBncDevReturn *	p_psStatus	Out	����BNC���ص��߼�������
// 	����ֵ˵�����±�
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int  BNC_Cancel (tBncDevReturn *p_psStatus);

//����ʼ����ֽ��������
// 	����˵�����˽ӿ����ڸ���ֽ�������䡣
// 	����˵�����±�
// 	1	UNIT	uiBoxType	In	ָ��ֽ�������������������ͣ�0-�ϱ��� 1-1Ԫֽ����, 2-5Ԫֽ����, 3-10
// 	Ԫֽ����, 4-20Ԫֽ����, 5-50Ԫֽ����, 6-100Ԫֽ����
// 	2	UINT	uiBoxNo	In	�ƶ�ֽ�����������0 ~ 6 ���У� 0�ŷϱ��� 1��Ϊ5Ԫ�����䣬2��Ϊ1Ԫ������
// 	3	tBncDevReturn *	pDevStatus	Out	����״̬��Ϣ
// 	����ֵ���±�
// 	1	int	0��ִ�гɹ���1��ִ��ʧ�ܡ�
AFC_API_DLL_IMP int BNC_StartReplaceBox(UINT uiBoxType, UINT uiBoxNo, tBncDevReturn *pDevStatus);

//  ֹͣ����ֽ��������
// 	����˵����ֹͣ����ֽ�������䡣
// 	����˵�����±�
// 	1	UNIT	uiBoxType	In	ָ��ֽ����������
// 	2	UNIT	uiBoxNo	In	ָ��ֽ���������
// 	2	tBncDevReturn *	p_psStatus	Out	����BNC���ص��߼�������
// 
// 	����ֵ˵�����±�
// 	1	Int	0	�ɹ�
// 	2	Int	1	�������Ϊ��
AFC_API_DLL_IMP int BNC_StopReplaceBox(UINT uiBoxType, UINT uiBoxNo, tBncDevReturn *pDevStatus);

//������Ǯ��RFID��Ϣ
// 	����˵����д��Ǯ��RFID��Ϣ��
// 	����˵�����±�
// 	1	UNIT	uiSLotID	In	��λID
// 	2	tBncRfidInfo *	pRFIDInfo	In	����RFID��Ϣ
// 	3	tBncDevReturn *	pDevStatus	Out	����״̬��Ϣ
// 	����ֵ���±�
// 	1	int	0��ִ�гɹ���1��ִ��ʧ�ܡ�
AFC_API_DLL_IMP int BNC_WriteRFIDInfo(UINT uiSLotID, tBncRfidInfo * pRFIDInfo, tBncDevReturn * pDevStatus);

//����ȡǮ��RFID��Ϣ
// 	����˵������ȡǮ��RFID��Ϣ��
// 	����˵�����±�
// 	1	UNIT	uiSLotID	In	��λID
// 	2	tBncRfidInfo *	pRFIDInfo	Out	����RFID��Ϣ
// 	3	tBncDevReturn *	pDevStatus	Out	����״̬��Ϣ
// 	����ֵ˵�����±�
// 	1	int	0��ִ�гɹ���1��ִ��ʧ�ܡ�
AFC_API_DLL_IMP int BNC_ReadRFIDInfo(UINT uiSLotID, tBncRfidInfo* pRFIDInfo, tBncDevReturn * pDevStatus);

//   ���Ǯ��
//	OUT tBncChangeNum* pBoxInfo
AFC_API_DLL_IMP int BNC_Empty(tBncChangeNum* pBoxInfo);
#endif

