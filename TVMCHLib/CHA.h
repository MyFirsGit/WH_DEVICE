#include "CHAApi.h"
#include "CASDev.h"
#include "AFCLogApi.h"

DWORD m_hCH;
#define	CHTRS_RES_OK				0L	// 操作成功
#define CHTRS_RES_FAILED            1L  // 操作失败
#define SHOPPER_EMPTY               0L
#define CHA_HOPPRT_A_MAX			900 //找零器A允许找零的最大容量
#define CHA_HOPPRT_B_MAX			900 //找零器B允许找零的最大容量
#define CHA_HOPPRT_A_MIN			10  //找零器A允许找零的最小容量	
#define CHA_HOPPRT_B_MIN			10  //找零器B允许找零的最小容量
#define CHA_SHOPPRT_A_MAX           900 //缓存找零器A最大容量
#define CHA_SHOPPRT_B_MAX           900 //缓存找零器B最大容量
#define CHA_COINCASE_A_MAX          3000//钱箱A最大容量

void CHA_SetCHADevReturn(const int errCode, const tDevReturn* l_s, tCHADevReturn* pDevStatus);