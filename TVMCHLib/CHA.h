#include "CHAApi.h"
#include "CASDev.h"
#include "AFCLogApi.h"

DWORD m_hCH;
#define	CHTRS_RES_OK				0L	// �����ɹ�
#define CHTRS_RES_FAILED            1L  // ����ʧ��
#define SHOPPER_EMPTY               0L
#define CHA_HOPPRT_A_MAX			900 //������A����������������
#define CHA_HOPPRT_B_MAX			900 //������B����������������
#define CHA_HOPPRT_A_MIN			10  //������A�����������С����	
#define CHA_HOPPRT_B_MIN			10  //������B�����������С����
#define CHA_SHOPPRT_A_MAX           900 //����������A�������
#define CHA_SHOPPRT_B_MAX           900 //����������B�������
#define CHA_COINCASE_A_MAX          3000//Ǯ��A�������

void CHA_SetCHADevReturn(const int errCode, const tDevReturn* l_s, tCHADevReturn* pDevStatus);