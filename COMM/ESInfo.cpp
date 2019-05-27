#include "StdAfx.h"
#include "ESInfo.h"
#include "SysException.h"
#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CESInfo CESInfo::theInstance;

CESInfo& CESInfo::GetInstance()
{
	return theInstance;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��

@retval     ��

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CESInfo::CESInfo()
{
    try {
        // ���ڻ�
        Initialize();
    }
    catch (...) {
        // �����쳣��Ϣ
    }
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��

@retval     ��

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CESInfo::~CESInfo()
{
}

////////////////////////////////////////////////////////////////////////////
///**
//@brief      ��Ŀ¼�������ӷ�б��
//
//@param      (i)CString sPath    Ŀ¼
//
//@retval     CString     �������б�ܵ�Ŀ¼��
//
//@exception  none
//*/
//////////////////////////////////////////////////////////////////////////
//CString CESInfo::AddBackslash(CString sPath)
//{
//	if(sPath.IsEmpty()){
//		return sPath;
//	}
//
//    return sPath.TrimRight(_T("\\")) + _T("\\");
//}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡ���ڰ�װ�İ汾��Ϣ

@param       �� 

@retval      CString 

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
CString CESInfo::GetInitialVersion()
{
    return m_DeviceIni->GetDataString(_T("APPLICATION"), _T("InitialVersion"));
}

////////////////////////////////////////////////////////////////////////////
///**
//@brief       �Ƿ���ʾ����ǰ��
//
//@param       ��
//
//@retval      bool true:����ǰ�� ; false:������ǰ��
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
bool CESInfo::IsTopmost()
{
    return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("TopMost"), 1) == 0 ? false : true;
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      

@param

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsFunctionKeyEnabled()
{
	 return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("FunctionKeyEnable"), 1) != 0 ;
}

//////////////////////////////////////////////////////////////////////////
/*
@brief  �Ƿ��������������    

@param

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsTaskManagerEnabled()
{
	return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("TaskManagerEnabled"), 1) != 0 ;
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      �Ƿ���������

@param

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
bool    CESInfo::IsDesktopEnabled()
{
	return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("DesktopEnabled"), 1) != 0 ;
}

////////////////////////////////////////////////////////////////////////////
///**
//@brief       �Ƿ���ʾ�����
//
//@param       ��
//
//@retval      bool true:��ʾ ; false:����ʾ
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
bool CESInfo::CanShowCursor()
{
    return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("ShowCursor")) == 0 ? false : true;
}
//
////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡ������Ŀ¼
//
//@param       �� 
//
//@retval      CString
//
//@exception   ��
//*/
//////////////////////////////////////////////////////////////////////////
CString CESInfo::GetDataPath()
{
    return AddBackslash(m_DeviceIni->GetDataString(_T("APPLICATION"), _T("DataPath")));
}

////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡ����Ŀ¼
//
//@param       �� 
//
//@retval      CString
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
CString CESInfo::GetBackupPath()
{
    return AddBackslash(m_DeviceIni->GetDataString(_T("APPLICATION"), _T("BackupPath")));
}

////////////////////////////////////////////////////////////////////////////
/*
@brief       ��ȡ��־Ŀ¼

@param       none

@retval      CString

@exception   ��
*/
////////////////////////////////////////////////////////////////////////////
CString CESInfo::GetLogPath()
{
	CString strLogPath =  m_DeviceIni->GetDataString(_T("APPLICATION"), _T("LogPath"),_T(""));
	if(strLogPath == _T("")){
		strLogPath = GetDataPath() + _T("\\Log");
	}
	else{
		strLogPath = AddBackslash(strLogPath);
	}
	return strLogPath;
}

////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡ�������δ����������
//
//@param       �� 
//
//@retval      UINT
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
UINT CESInfo::GetLimitedDaysOfUnSendData()
{
	return m_DeviceIni->GetDataInt(_T("TXNDATA"),_T("UnsendMaxDay"),7);
}

////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡ�������ݱ�������
//
//@param       �� 
//
//@retval      UINT
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
UINT CESInfo::GetLimitedDaysOfSendData()
{
	return m_DeviceIni->GetDataInt(_T("TXNDATA"),_T("SendedMaxDay"),10);
}

//////////////////////////////////////////////////////////////////////////
/*
@brief   ȡ�ý��״����� ����λ���룩  

@param      

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetTransactionPackageInterval()
{
	return m_DeviceIni->GetDataInt(_T("INTERVAL"), _T("TRANSACTION_PACKAGE"),30);
}
//////////////////////////////////////////////////////////////////////////
/*
@brief      ȡ��ҵ�����ݴ�����ʱ�䣨��λ���룩

@param      

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetBusinessPackageInterval()
{
	return m_DeviceIni->GetDataInt(_T("INTERVAL"), _T("BUSINESS_PACKAGE"),30);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡBOM ���Ʋ����� �ϴ�·��

@param       �� 

@retval      CString

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
CString CESInfo::GetBomExportPath()
{
	return AddBackslash(m_DeviceIni->GetDataString(_T("MOVEDISK"), _T("ExportPath")));
}


//////////////////////////////////////////////////////////////////////////
/**
@brief       �Ƿ��¼Debug��Ϣ

@param       ��

@retval      bool true:��¼Debug��Ϣ ; false:����¼Debug��Ϣ

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
 bool CESInfo::IsWriteDebug()
 {
    return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("WriteDebug")) == 0 ? false : true;
 }

 //////////////////////////////////////////////////////////////////////////
 /**
 @brief       �Ƿ����ػ�����

 @param       ��

 @retval      bool true:�����ػ����� ; false:�������ػ�����

 @exception   ��
 */
 //////////////////////////////////////////////////////////////////////////
 bool CESInfo::IsUsedGuardian()
 {
	 return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("IsUsedGuardian")) == 0 ? false : true;
 }

////////////////////////////////////////////////////////////////////////////
///**
//@brief       �Ƿ����÷���Ա��
//
//@param       ��
//
//@retval      bool true:���� ; false:������
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
bool CESInfo::IsUseFounderStaffID()
{
	return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("UseFounderStaff"),0) == 0 ? false : true;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡŷķ��Ա��ID

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetFounderStaffID()
{
	return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("FounderStaffID"), 10101028);
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      

@param      

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsFounderStaffID(int userID)
{
	return IsUseFounderStaffID() && (GetFounderStaffID() == userID);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡŷķ��Ա������

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
CString CESInfo::GetFounderStaffPassword()
{
	return m_DeviceIni->GetDataString(_T("APPLICATION"), _T("FounderStaffPassword"), _T("888888"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief        ȡ��ҵ��������ȴ�ʱ�䵥λ���룩

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////

int CESInfo::GetCloseOperationMaxWaitSeconds()
{
	return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("CloseOperationMaxWaitSeconds"),10*60);
}

//////////////////////////////////////////////////////////////////////////
/*
@brief    �Ƿ���ҪУ��δ�ͽ������ݰ�  

@param

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsValidateUnSendPackage()
{
	return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("ValidateUnSendPackage"),1) != 99;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡUSB��֤��ʽ��0������֤��1����Ҫ��֤��

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetUSBAuthFlag()
{
	return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("UsbAuthorizeManner"), 0);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡ״̬��ˢ��ʱ����

@param        

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetStatusTimerInterval()
{
	return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("StatusTimerInterval"), 1000);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡMAGAZINE���ں�

@param       none 

@retval      int

@exception   none
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetMagazineCommPort()
{
    return m_DeviceIni->GetDataInt(_T("MAGAZINE"), _T("COMM_PORT"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡConnect1BaudRate

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetMagazineBaudRate()
{
    return m_DeviceIni->GetDataInt(_T("MAGAZINE"), _T("BAUD_RATE"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡƱ��ѹƱ���������

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetPressCardMaxCount()
{
	return m_DeviceIni->GetDataInt(_T("MAGAZINE"), _T("PRESSCARD_COUNT"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡƱ���������

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetMagazineMaxCapacity()
{
	return m_DeviceIni->GetDataInt(_T("MAGAZINE"), _T("MAX_CAPACITY"));
}

////////////////////////////////////////////////////////////////////////
/*
@brief    Ʊ���ؿ���  

@param      

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsMagazineMonitorOpened()
{
	return (m_DeviceIni->GetDataInt(_T("MAGAZINE"),_T("MONITOR_SWITCH"),0) == 1);
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      Ʊ���ؼ�ʱ���

@param      

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetMagazineMonitorInterval()
{
	return m_DeviceIni->GetDataInt(_T("MAGAZINE"),_T("MONITOR_INTERVAL"),5000);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       �ж��Ƿ�ʹ�ö�д��

@param       (i)bool isRW  true:�ⲿ��д��  false:�ڲ���д��

@retval      bool true:ʹ�ö�д��  false:ʹ��ģ������

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsRWUsed(RW_TYPE rwType)
{
	return (m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("IS_USED")) == 1);
}

//////////////////////////////////////////////////////////////////////////
/*
@brief   ��д����ؿ���   

@param      

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
bool	CESInfo::IsRWMonitorOpened(RW_TYPE rwType)
{
	return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("MONITOR_SWITCH"),0)!=0;
}

//////////////////////////////////////////////////////////////////////////
/*
@brief    ��д����ؼ��  

@param		(i)RW_TYPE rwType  ��д������

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
int     CESInfo::GetRWMonitorInterval(RW_TYPE rwType)
{
	return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("MONITOR_INTERVAL"),30);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡ�ⲿ��д�����ں�

@param       (i)RW_TYPE rwType  ��д������

@retval      int ���ں�

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetRWCommPort(RW_TYPE rwType)
{
    return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("COMM_PORT"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡ�ⲿ��д�����ڲ�����

@param       (i)RW_TYPE rwType  ��д������

@retval      int ���ڲ�����

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetRWBaudRate(RW_TYPE rwType)
{
    return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("BAUD_RATE"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ȡ��ģ�⿨�������ͣ�����ʹ��

@param       (i)RW_TYPE rwType  ��д������

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetSimCardType(RW_TYPE rwType)
{
	return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("SIM_CARD_TYPE"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ȡ�ö���ʱ����

@param       (i)RW_TYPE rwType  ��д������

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int	CESInfo::GetReadCardInterval(RW_TYPE rwType)
{
	return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("READ_CARD_INTERVAL"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ȡ��ĸ���Ŀ���

@param       (i)RW_TYPE rwType  ��д������

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int	CESInfo::GetMasterCardSlot(RW_TYPE rwType)
{
	return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("CMC_Slot"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ���俨�Ŀ���

@param       (i)RW_TYPE rwType  ��д������

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int	CESInfo::GetTrandferCardSlot(RW_TYPE rwType)
{
	return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("CMCT_Slot"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       PIN��ĳ���

@param       (i)RW_TYPE rwType  ��д������

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetPinLen(RW_TYPE rwType)
{
	return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("ICMCT_PIN_Len"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ���п�ĸ�����俨��PIN��

@param       (i)RW_TYPE rwType  ��д������

@retval      CString

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetPinBuffer(RW_TYPE rwType)
{
	return m_DeviceIni->GetDataInt(GetRWTypeString(rwType), _T("ICMCT_PIN_buff"));
}
//////////////////////////////////////////////////////////////////////////
/**
@brief       �ж��Ƿ�ʹ�ô�ӡ��

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsPrinterUsed()
{
	return (m_DeviceIni->GetDataInt(_T("PRINTER"), _T("IS_USED")) == 1);
}

////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡConnect3CommPort
//
//@param       �� 
//
//@retval      int
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
int CESInfo::GetPrinterCommPort()
{
    return m_DeviceIni->GetDataInt(_T("PRINTER"), _T("COMM_PORT"));
}

////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡConnect3BaudRate
//
//@param       �� 
//
//@retval      int
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
int CESInfo::GetPrinterBaudRate()
{
   return m_DeviceIni->GetDataInt(_T("PRINTER"), _T("BAUD_RATE"));
}
////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡ��ӡ����
//
//@param       �� 
//
//@retval      int
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
int CESInfo::GetPrintType()
{
	return m_DeviceIni->GetDataInt(_T("PRINTER"),_T("PRINT_TYPE"));
}

////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡ��ӡ����
//
//@param       �� 
//
//@retval      int
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
int CESInfo::GetPrintDiret()
{
	return m_DeviceIni->GetDataInt(_T("PRINTER"),_T("PRINT_Diret"));
}
////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡ�м��
//
//@param       �� 
//
//@retval      int
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
int CESInfo::GetPrintRowDis()
{
	return m_DeviceIni->GetDataInt(_T("PRINTER"),_T("PRINT_ROWDIS"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       �ж��Ƿ�ʹ��Ʊ����ӡ��

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsCardPrinterUsed()
{
	return (m_DeviceIni->GetDataInt(_T("CARD_PRINTER"), _T("IS_USED")) == 1);
}

////////////////////////////////////////////////////////////////////////////
/*
@brief       ��ȡES1���ں�

@param       �� 

@retval      int

@exception   ��
*/
////////////////////////////////////////////////////////////////////////////
int CESInfo::GetTOKEN_ESCommPort()
{
	return m_DeviceIni->GetDataInt(_T("ES_TOKEN"), _T("COMM_PORT"));	
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       �ж��Ƿ�ʹ��ES2

@param       �� 

@retval      bool

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsTOKEN_ESUsed()
{
	return (m_DeviceIni->GetDataInt(_T("ES_TOKEN"), _T("IS_USED")) == 1);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       �ж�ָ����ģ���Ƿ�ʹ��

@param       (i)ES_MODULE_NUMBER moduleIDģ���� 

@retval      bool

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsModuleUsed(ES_MODULE_NUMBER moduleID)
{
	CString module = _T("");
	switch(moduleID)
	{
	case ES_MODULE_NUMBER_1:
		module = _T("IS_MODULE1_USED");
		break;
	case ES_MODULE_NUMBER_2:
		module = _T("IS_MODULE2_USED");
		break;
	case ES_MODULE_NUMBER_3:
		module = _T("IS_MODULE3_USED");
		break;
	}
	return (m_DeviceIni->GetDataInt(_T("ES"), module) == 1);
}

////////////////////////////////////////////////////////////////////////////
/*
@brief       ��ȡƱ����ӡ����������

@param       �� 

@retval      int

@exception   ��
*/
////////////////////////////////////////////////////////////////////////////
int CESInfo::GetCardType()
{
	return m_DeviceIni->GetDataInt(_T("CARD_PRINTER"), _T("CARD_TYPE"));	
}

////////////////////////////////////////////////////////////////////////////
/*
@brief       �������Դ���

@param       �� 

@retval      int

@exception   ��
*/
////////////////////////////////////////////////////////////////////////////
int CESInfo::GetTestSendCardCount()
{
	return m_DeviceIni->GetDataInt(_T("CARD_PRINTER"), _T("TEST_SEND_CARD_COUNT "));
}

////////////////////////////////////////////////////////////////////////////
/*
@brief       ��ȡƱ����ӡ����ӡ��ʱ�ļ���

@param       �� 

@retval      CString

@exception   ��
*/
////////////////////////////////////////////////////////////////////////////
CString CESInfo::GetPrinterTempFile()
{
	return m_DeviceIni->GetDataString(_T("CARD_PRINTER"), _T("PRT_TEMP"));
}

////////////////////////////////////////////////////////////////////////////
/*
@brief       ��ȡ��ӡ������

@param       �� 

@retval      CString

@exception   ��
*/
////////////////////////////////////////////////////////////////////////////
CString CESInfo::GetCardPrinterDriverName()
{
	return m_DeviceIni->GetDataString(_T("CARD_PRINTER"), _T("DRIVER_NAME"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       �ж��Ƿ�ʹ��ES

@param       �� 

@retval      bool

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsCARD_ESUsed()
{
	return (m_DeviceIni->GetDataInt(_T("ES"), _T("IS_USED")) == 1);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡES���ں�CommPort

@param       �� 

@retval      bool

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetCARD_ESCommPort()
{
	return m_DeviceIni->GetDataInt(_T("ES"), _T("COMM_PORT"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡES������BaudRate

@param       �� 

@retval      bool

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetCARD_ESBaudRate()
{
	return m_DeviceIni->GetDataInt(_T("ES"), _T("BAUD_RATE"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡUpsUsed

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsUPSUsed()
{
    return (m_DeviceIni->GetDataInt(_T("UPS"), _T("IS_USED")) == 1);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡUPS CommPort

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetUPSCommPort()
{
	return m_DeviceIni->GetDataInt(_T("UPS"), _T("COMM_PORT"));
}

////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡUPS BaudRate

@param       �� 

@retval      int

@exception   ��
*/
////////////////////////////////////////////////////////////////////////
int CESInfo::GetUPSBaudRate()
{
	return m_DeviceIni->GetDataInt(_T("UPS"), _T("BAUD_RATE"));
}


////////////////////////////////////////////////////////////////////////////
///**
//@brief       ��ȡUSB ʹ�õ� �̷�
//
//@param       �� 
//
//@retval      CString
//
//@exception   ��
//*/
////////////////////////////////////////////////////////////////////////////
CString CESInfo::GetBOMUSBDrive()
{
    return AddBackslash(m_DeviceIni->GetDataString(_T("MOVEDISK"), _T("USBDRIVE")));
}

////////////////////////////////////////////////////////////////////////////
/**
@brief      ȡ�����ݼ�¼���������

@param      none

@retval     int

@exception  none
*/
////////////////////////////////////////////////////////////////////////////
int CESInfo::GetStoreDay()
{
    return m_DeviceIni->GetDataInt(_T("LOG"), _T("StoreDay"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ȡ�����ݼ�¼ʵ�ʱ��������

@param      none

@retval     int

@exception  none
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetRealStoreDay()
{
	return m_DeviceIni->GetDataInt(_T("LOG"), _T("RealStoreDay"));
}

////////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡESϵͳ����ʹ�õ���������

@param       none 

@retval      CString ��������

@exception   none
*/
////////////////////////////////////////////////////////////////////////////
CString CESInfo::GetUsedAdapterName()
{
	return m_DeviceIni->GetDataString(_T("MACHINE"), _T("ESUSED_ADAPTER_NAME"));
}

//////////////////////////////////////////////////////////////////////////
/*
@brief    ȡ�ö�д���������ļ��е�����  

@param

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
CString CESInfo::GetRWTypeString(RW_TYPE rwType)
{
	switch(rwType)
	{
	case ES_TOKEN_RW1 : return _T("RW_TOKEN_ONE");
	case ES_TOKEN_RW2: return _T("RW_TOKEN_TWO");
	case ES_TOKEN_RW3 : return _T("RW_TOKEN_THREE");
	case ES_CARD_RW   : return _T("RW_ES_CARD");
	case PM_RW     : return _T("RW_PM");
	default:
		return _T("RW_ES_CARD");
	}
}

//////////////////////////////////////////////////////////////////////////
/*
@brief    ȡ�õ��ӱ�ǩ�������ļ��е�����  

@param

@retval   CString  

@exception  
*/
//////////////////////////////////////////////////////////////////////////
CString CESInfo::GetRfidTypeString(RFID_NO rfidId)
{	switch(rfidId)
	{
	case RFID_1 : return _T("RFID_ONE");
	case RFID_2 : return _T("RFID_TWO");
	case RFID_3 : return _T("RFID_THREE");
	case RFID_4 : return _T("RFID_FOUR");
	default:
		return _T("RFID");
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡRFIDUsed

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsRfidUsed(RFID_NO rfidId)
{
	return (m_DeviceIni->GetDataInt(GetRfidTypeString(rfidId), _T("IS_USED")) == 1);
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡRFID���ں�

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetRfidCommPort(RFID_NO rfidId)
{
	return m_DeviceIni->GetDataInt(GetRfidTypeString(rfidId), _T("COMM_PORT"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡRFID������

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetRfidBaudRate(RFID_NO rfidId)
{
	return m_DeviceIni->GetDataInt(GetRfidTypeString(rfidId), _T("BAUD_RATE"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡRFIDֹͣλ

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetRfidStopBit(RFID_NO rfidId)
{
	return m_DeviceIni->GetDataInt(GetRfidTypeString(rfidId), _T("STOP_BIT"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡRFID��żУ��

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
CString CESInfo::GetRfidParity(RFID_NO rfidId)
{
	return m_DeviceIni->GetDataString(GetRfidTypeString(rfidId), _T("PARITY"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡRFID�ֽڴ�С

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetRfidByteSize(RFID_NO rfidId)
{
	return m_DeviceIni->GetDataInt(GetRfidTypeString(rfidId), _T("BYTE_SIZE"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡRFID���뻺������С

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetRfidInputSize(RFID_NO rfidId)
{
	return m_DeviceIni->GetDataInt(GetRfidTypeString(rfidId), _T("INPUT_SIZE"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡRFID�����������С

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int  CESInfo::GetRfidOutputSize(RFID_NO rfidId)
{
	return m_DeviceIni->GetDataInt(GetRfidTypeString(rfidId), _T("OUTPUT_SIZE"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡ��ʱ��ʱ��

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetTxnIntervalTime()
{
	return m_DeviceIni->GetDataInt(_T("TRANSMISSION"), _T("TXN_INTERVAL_TIME"));
}

//////////////////////////////////////////////////////////////////////////
/**
@brief       ��ȡ��������Ƽ�ʱ

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetAuditInterval()
{
	return m_DeviceIni->GetDataInt(_T("TRANSMISSION"), _T("AUDITINTERVAL"));
}


//////////////////////////////////////////////////////////////////////////
/**
@brief       ҵ�����ݵ�����ʱ��

@param       �� 

@retval      int

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CESInfo::GetBusinessInterval()
{
	return m_DeviceIni->GetDataInt(_T("TRANSMISSION"), _T("BUSINESS_INTERVAL_TIME"));
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      �Ƿ�ɾ������Э��ͷ

@param      ��

@retval     bool true:ɾ����false����ɾ��

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
bool CESInfo::IsDeleteParameterHead(){
	return m_DeviceIni->GetDataInt(_T("APPLICATION"), _T("IsDeleteParameterHead"), 1) == 0 ? false:true;
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      ��ȡMTCǰ���ֽڱ���

@param      

@retval     

@exception  
*/
//////////////////////////////////////////////////////////////////////////
CString CESInfo::GetDeviceComponentCode (long moudleID)
{
	CString strMouldeID;
	strMouldeID.Format(_T("%d"),moudleID);
	return m_DeviceIni->GetDataString(_T("ES_COMPONENT_ID"),strMouldeID,_T(""));	
}