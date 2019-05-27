// CASDev.h: interface for the OCASDev class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CASDEV_H__F07F2DC3_A28E_4199_9596_25F0F8C46765__INCLUDED_)
#define AFX_CASDEV_H__F07F2DC3_A28E_4199_9596_25F0F8C46765__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODevBase.h"
#include "CASDevDef.h"
#include "CASDevStruct.h"

class AFX_EXT_CLASS OCASDev
{
public:
	OCASDev();
	virtual ~OCASDev();
	
public:	
	// ����ͨ�Ų���
	int iSetCommPara(tDevReturn* p_psrStatus);
	int	iSetCommParaEx(tDevReturn* p_psrStatus);
	
	// ��������
	// ��ʼ��
	int iInit(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// ��ģ��״̬
	int iGetDevStatus(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// ��ȡ�豸�Ƿ����
	int iGetStatus(tDevReturn* p_psrStatus);

	// ��ȡ�豸����
	int iGetDevCapability(UINT *p_puiCapability, UINT p_uiNumber);
	
	// ���ý���Ӳ������
	int iSetReceiveType(BYTE p_byReceiveType, tDevReturn* p_psrStatus);
	// ��ʼ����Ӳ��
	int iStartReceiveCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// ֹͣ����Ӳ��
	int iStopReceiveCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// ��ȡ���ս��
	int iGetReceiveNumber(tReceiveCoinNum* p_psReceiveCoinNum, tDevReturn* p_psrStatus);
	
	// ���ݴ����е�Ӳ�ҵ�����������������Ǯ��
	int iAcceptCoin(BYTE p_byEscrow1Dir, BYTE p_byEscrow2Dir, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// ���ݴ����е�Ӳ�ҵ�����������������Ǯ�䣬�ɶ�̬���ڲ�������������
	int iAcceptCoinEx(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);

	// �˳�Ӳ��
	int iEjectCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	
	// ��ʼ�ӱ�
	int iStartAddCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// ֹͣ�ӱ�
	int iStopAddCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);	
	
	// �߼��䳮
	int iDenominate(UINT p_uiChange, tChange* p_psChange, tDevReturn* p_psrStatus);
	// ����Ҫ���Hopper�г�Ӳ�ҵ����ҿ�
	int iChange(tChange p_sChange, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// ����Ҫ���Hopper�г�Ӳ�ҵ����ҿڣ��ɶ�̬�����ÿ��Hopper��������
	int iChangeEx(UINT p_uiChange, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);

	// ǿ�����ø�Hopper��Ӳ��Ǯ���е�Ӳ����
	int iSetCoinNumber(tSetCoinNum p_sCoinNum, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// �����¼
	int iSaveRecord(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);

	// ���
	int iClearCoin(tClearCoin p_sClearCoin, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);

	// дiButton����
	int iSetiButton(BYTE p_byiButtonNo, BYTE p_byAddress, BYTE p_byDataLen, LPBYTE p_pbyiButtonData, tDevReturn* p_psrStatus);
	// ��iButton����
	int iGetiButton(BYTE p_byiButtonNo, BYTE p_byAddress, BYTE p_byDataLen, LPBYTE p_pbyiButtonData, tDevReturn* p_psrStatus);
	// ���iButton����
	int iCleariButton(BYTE p_byiButtonNo, tDevReturn* p_psrStatus);
	// ��iButton ID
	int iGetiButtonID(BYTE p_byiButtonNo, LPBYTE p_pbyiBtnID, tDevReturn* p_psrStatus);
	
	// ����������
	int iBeep(BYTE p_byBeepCount, BYTE p_byBeepTime, BYTE p_byBeepInterval, tDevReturn *p_psrStatus);
	
	// ��ȡӲ�����ʳ���汾��
	int iGetDevVersion(LPTSTR p_pcDevVersion, BYTE& p_byDataLen, tDevReturn* p_psrStatus);
	// ��ȡģ������
	int iGetDevType(LPTSTR p_pcDevType, BYTE& p_byDataLen, tDevReturn* p_psrStatus);
	// ��ȡ��̬��汾��
	int iGetVersion(LPTSTR p_pcVersion);
	// ��ȡCPLD�汾��
	int iGetCPLDVersion(LPTSTR p_pcCPLDVersion, BYTE& p_byDataLen, tDevReturn* p_psrStatus);
	
	// д���к�
	int iSetSerialNumber(LPCTSTR p_pcSerialNo, const BYTE p_byDataLen, tDevReturn* p_psrStatus);
	// ��ȡ���к�
	int iGetSerialNumber(LPTSTR p_pcSerialNo, BYTE& p_byDataLen, tDevReturn* p_psrStatus); 
	
	//added by hguang 2010-09-02
	// �����ļ�
	int iDownloadFile(LPCTSTR p_pcFilePath, tDevReturn* p_psrStatus);
	//�ļ����ؽ���
	int iGetCurFileProgress(tCoinSystem_Pdl_Progress *p_psPdlProgress);
	//end added

	// ODevBase���е�������	
	// ��ȡ����״̬�ṹ��
	tDevReturn tGetErrorFlag();	
	// ��ȡӲ�������־
	int iGetErrorFlag();
	
	// ����������߼��豸��
	void vGetLogicalDevName(LPTSTR p_pcLogicalDevName);	
	// �����������߼��豸��
	void vSetLogicalDevName(LPCTSTR p_pcLogicalDevName);
	
	// ������ջ�����
	void vClearRecvBuf();	
	// �ر�ͨѶ
	int iCloseComm();

	//	ά���ӿڣ�ֻ�ڲ���ʱ����ʱʹ�ã�Ӧ���в�ʹ��
	// ��ѯ͹��ת���Ĵ������˱���
	int iGetCamInfo(LPWORD p_pwLoopNum, LPWORD p_pwEjectNum, tDevReturn* p_psrStatus);
	
	// �ݴ�������
	int iEscrowControl(BYTE p_byDevNo, BYTE p_byAction, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// ����������
	int iRouterControl(BYTE p_byDevNo, BYTE p_byAction, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// ������������
	int iMHopperControl(BYTE p_byDevNo,	BYTE p_byAction, WORD p_wDispNum, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// ��������������
	int iSHopperControl(BYTE p_byDevNo,	BYTE p_byAction, WORD p_wDispNum, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// ͹�ֿ���
	int iCamControl(BYTE p_byLoopNum, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// Ӳ�ҽ���������
	int iCoinReceiverControl(BYTE p_byAction, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// բ�ſ���
	int iShutterControl(BYTE p_byAction, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	
	//added by hguang 2010-09-06
	int iReadLogDataEx(UINT p_uiStartAddress,	UINT p_uiLogLength,BYTE* p_pbyLogData,tDevReturn* p_psStatus);		
	int iReadLogInfoEx(tCoinLog p_tLogInfo[10],tDevReturn* p_psStatus);
    int iClearLog(tDevReturn* p_psStatus);

	//ά���ӿ�
	int iWriteLogDataEx(UINT p_uiStartAddress,	UINT p_uiLogLength,BYTE* p_pbyLogData,tDevReturn* p_psStatus);
	//end added
		
	//added by hguang 2013-08-26	
	//��RFID дһ��Block ����
	int iRFWriteBlock(const tCAS006_IN_RWRFID* p_psWRFID, const tCAS006_DATA* p_psData, tDevReturn *p_psStatus);
	
	//��RFID ��һ��Block ����
	int iRFReadBlock(const tCAS006_IN_RWRFID* p_psRRFID, tCAS006_DATA* p_psData, tDevReturn *p_psStatus);
	
	//��ȡRFID ��������
	int iGetRFIDCardInfo(const tCAS006_IN_CARD_INFO* p_psCardInfo, tCAS006_DATA* p_psData, tDevReturn *p_psStatus);
	
	//��ȡǮSN ��
	int iGetCoinBoxSerialNumber(const tCAS006_IN_CARD_INFO* p_psCardInfo, tCAS006_DATA* p_psData, tDevReturn* p_psStatus);

	//����Ǯ�����к�
	int iSetCoinBoxSerialNumber(const tCAS006_IN_CARD_INFO* p_psCardInfo, const tCAS006_DATA* p_psData, tDevReturn* p_psStatus);
	ODevBase* GetDevBase();

	//added by hguang 2011-12-14
	//���
	int iClearCoinEx(tClearCoin p_sClearCoin, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	
	//��ָ��������Ӳ��
	int iClearCoin(const tCAS006_ClearNum* p_psClearNum, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psStatus);
private:
	 //OCASBase m_pCASBase;
	class OCASBase* m_pCASBase;
};

#endif // !defined(AFX_CASDEV_H__F07F2DC3_A28E_4199_9596_25F0F8C46765__INCLUDED_)
