#ifndef __LOADDLL_H__
#define __LOADDLL_H__

typedef LONG (WINAPI *POS_Port_OpenAFun)(LPSTR szName, INT iPort, BOOL bFile, LPSTR szFilePath);
typedef LONG (WINAPI *POS_Port_OpenWFun)(LPWSTR szName, INT iPort, BOOL bFile, LPWSTR szFilePath);
typedef LONG (WINAPI *POS_Output_PrintStringAFun)(LONG iPrintID, LPCSTR lpBuffer);
typedef LONG (WINAPI *POS_Output_PrintStringWFun)(LONG iPrintID, LPCWSTR lpBuffer);
typedef LONG (WINAPI *POS_Output_PrintDataFun)(LONG iPrintID, LPCSTR lpBuffer, INT iLen);
typedef LONG (WINAPI *POS_Port_CloseFun)(LONG iPrinterID);
typedef LONG (WINAPI *POS_Control_CutPaperFun)(LONG iPrinterID, LONG iType, LONG iLines);
typedef LONG (WINAPI *POS_Control_CashDrawFun)(LONG iPrinterID, LONG iPort, LONG iTime1, LONG iTime2);
typedef LONG (WINAPI *POS_Status_QueryStatusFun)(LONG iPrinterID);
typedef LONG (WINAPI *POS_Status_RTQueryStatusFun)(LONG iPrinterID);
typedef LONG (WINAPI *POS_Status_RTQueryTypeStatusFun)(LONG iPrinterID,INT n);
typedef LONG (WINAPI *POS_Output_DownloadBmpToFlashAFun)(LONG iPrinterID, LPCSTR szPath);
typedef LONG (WINAPI *POS_Output_DownloadBmpToFlashNumAFun)(LONG iPrinterID, LPCSTR szPath,int m);
typedef LONG (WINAPI *POS_Output_PrintBmpDirectAFun)(LONG iPrinterID, LPCSTR lpFilePath);
typedef LONG (WINAPI *POS_Output_PrintBmpDirectWFun)(LONG iPrinterID, LPCWSTR lpFilePath);
typedef LONG (WINAPI *POS_Output_PrintBarcodeAFun)(LONG iPrinterID, INT iType, INT iWidth, INT iHeight, INT hri, LPCSTR lpString);
typedef LONG (WINAPI *POS_Output_PrintBarcodeWFun)(LONG iPrinterID, INT iType, INT iWidth, INT iHeight, INT hri, LPCWSTR lpString);
typedef LONG (WINAPI *POS_Output_PrintFontStringAFun)(LONG iPrinterID, INT iFont,INT iThick, INT iWidth,INT iHeight,INT iUnderLine, LPCSTR lpString);
typedef LONG (WINAPI *POS_Output_PrintBmpInFlashFun)(long, long, long);
typedef LONG (WINAPI *POS_Input_PrinterIdFun)(LONG iPrintID, LPCSTR lpBuffer);
typedef LPCSTR (WINAPI *POS_Input_ReadPrinterFun)(LONG iPrintID, LPCSTR lpBuffer);
typedef LONG (WINAPI *POS_Control_BlackMarkFun)(LONG iPrinterID);
typedef LONG (WINAPI *POS_Status_QueryTaskStatusFun)(LONG iPrinterID,INT second);
typedef LONG (WINAPI *POS_Output_PrintFlashBmpFun)(LONG iPrintID, INT n);
typedef LONG (WINAPI *POS_Output_PrintOneDimensionalBarcodeAFun)(LONG iPrinterID, INT iType, INT iWidth, INT iHeight, INT hri, LPCSTR lpString);
typedef LONG (WINAPI *POS_Output_PrintTwoDimensionalBarcodeAFun)(LONG iPrinterID, INT iType, INT parameter1, INT parameter2, INT parameter3, LPCSTR lpString);
typedef LONG (WINAPI *POS_Output_PrintTwoDimensionalBarcodeWFun)(LONG iPrinterID, INT iType, INT parameter1, INT parameter2, INT parameter3, LPCWSTR lpString);
typedef LONG (WINAPI *POS_Output_DownloadRamBmpAFun)(LONG iPrinterID, LPCSTR lpFilePath);
typedef LONG (WINAPI *POS_Output_DownloadRamBmpWFun)(LONG iPrinterID, LPCWSTR lpFilePath);
typedef LONG (WINAPI *POS_Output_PrintRamBmpFun)(LONG iPrintID, INT n);
typedef LONG (WINAPI *POS_Control_PrintTestpageFun)(LONG iPrintID);
typedef LONG (WINAPI *Color24_GrayBWFun)(LPCTSTR szSourceFile,LPCTSTR szTargetFile);
typedef LONG (WINAPI *POS_Control_SetRotaryPrintFun)(LONG iPrinterID, INT n);
typedef LONG (WINAPI *POS_Control_OppositeColorFun)(LONG iPrinterID, BOOL bOppsite);
typedef LONG (WINAPI *POS_Control_SetInvertedPrintFun)(LONG iPrinterID,INT n);
typedef LONG (WINAPI *POS_Control_AlignTypeFun)(LONG iPrinterID,LONG iAlignType);
typedef LONG (WINAPI *POS_Output_SendLocalFileAFun)(LONG iPrinterID, LPCSTR lpFilePath);
typedef LONG (WINAPI *POS_Control_ReSetFun)(LONG iPrinterID);
typedef LONG (WINAPI *POS_Control_SetPrintFontCFun)(LONG iPrinterID,BOOL iDoubleWidth,BOOL iDoubleHeight,BOOL iUnderLine);

//---------------ztongli.2017.0104---------------
//设置页宽页高
typedef LONG (WINAPI *CallPageSetupTSPL)(LONG iPrintID,INT PageWidth, INT PageHeight);
CallPageSetupTSPL							PageSetupTSPL		=	NULL;
//画线
typedef LONG (WINAPI *CallDrawLineTSPL)(LONG iPrintID,INT StartX, INT StartY, INT LineWidth, INT LineHeight);
CallDrawLineTSPL							DrawLineTSPL		=	NULL;
//TL51打印
typedef LONG (WINAPI *CallPrintTSPL51)(LONG iPrintID,INT Set, INT Copy);
CallPrintTSPL51								PrintTSPL51			=	NULL;
//画矩形
typedef LONG (WINAPI *CallDrawBorderTSPL)(LONG iPrintID,INT LineWidth, INT top_left_x, INT top_left_y, INT bottom_right_x, INT bottom_right_y);
CallDrawBorderTSPL							DrawBorderTSPL		=	NULL;
//文字
typedef LONG (WINAPI *CallDrawTextTSPL)(LONG iPrintID,INT start_x, INT start_y, BOOL isSimplifiedChinese, INT xMultiplication,INT yMultiplication, INT rotate, LPCSTR content);
CallDrawTextTSPL							DrawTextTSPL		= NULL;
//一维条码
typedef LONG (WINAPI *CallDrawBarCodeTSPL)(LONG iPrintID,INT start_x, INT start_y, CString type, INT height, BOOL isReadable,INT rotate, INT narrowWidth, INT wideWidth, LPCSTR content);
CallDrawBarCodeTSPL							DrawBarCodeTSPL		= NULL;
//清空缓冲区
typedef LONG (WINAPI *CallClearBuffTSPL)(LONG iPrintID);
CallClearBuffTSPL						ClearBuffTSPL		    = NULL;
//二维条码
typedef LONG (WINAPI *CallDraw2DBarCodeTSPL)(LONG iPrintID,INT start_x, INT start_y, CString Max ,CString content);
CallDraw2DBarCodeTSPL						Draw2DBarCodeTSPL	= NULL;
//下载位图
typedef LONG (WINAPI *CallDownLoadBitMapTSPL)(LONG iPrintID,BOOL isMoveFlash,CString PathName);
CallDownLoadBitMapTSPL						DownLoadBitMapTSPL	= NULL;
//将图片刷到缓冲区
typedef LONG (WINAPI *CallPutBitMapTSPL)(LONG iPrintID,INT start_x, INT start_y,CString fileName);
CallPutBitMapTSPL						PutBitMapTSPL	= NULL;
//得到打印机状态
typedef LONG (WINAPI *CallGetPrinterStatusTSPL)(LONG iPrintID);
CallGetPrinterStatusTSPL						GetPrinterStatusTSPL	= NULL;
//控制蜂鸣器发出一声响
typedef LONG (WINAPI *CallDriveBeepTSPL)(LONG iPrintID);
CallDriveBeepTSPL						DriveBeepTSPL	= NULL;
//设置国际字符集
typedef LONG (WINAPI *CallSetCharsetNameTSPL)(LONG iPrintID,CString CharsetName);
CallSetCharsetNameTSPL						SetCharsetNameTSPL	= NULL;
//控制进纸或退纸距离
typedef LONG (WINAPI *CallSetPaperbackOrPaperFeedTSPL)(LONG iPrintID,BOOL isFeedBack, INT mDot);
CallSetPaperbackOrPaperFeedTSPL					SetPaperbackOrPaperFeedTSPL	= NULL;
//指定的区域反相打印命令
typedef LONG (WINAPI *CallReverseAreaTSPL)(LONG iPrintID,INT start_x, INT start_y, INT width, INT height);
CallReverseAreaTSPL					ReverseAreaTSPL	= NULL;
//选择字符代码页
typedef LONG (WINAPI *CallSelectCodePageTSPL)(LONG iPrintID,INT value);
CallSelectCodePageTSPL					SelectCodePageTSPL	= NULL;
//设置标签间垂直间距
typedef LONG (WINAPI *CallSetGAPTSPL)(LONG iPrintID,DOUBLE value);
CallSetGAPTSPL						SetGAPTSPL	= NULL;
//定义标签的参考坐标原点命令
typedef LONG (WINAPI *CallSetLabelReferenceTSPL)(LONG iPrintID,INT x,INT y);
CallSetLabelReferenceTSPL						SetLabelReferenceTSPL	= NULL;
//TL21打印
typedef LONG (WINAPI *CallPrintTSPL21)(LONG iPrintID,INT Set);
CallPrintTSPL21						PrintTSPL21	= NULL;
//用于确认机型是TL21便于内部区别指令以及相关条件
typedef LONG (WINAPI *CallSetIs21)();
CallSetIs21						SetIs21	= NULL;
//---------------ztongli.2017.0104---------------


POS_Port_OpenAFun							POS_Port_OpenA							= NULL;
POS_Port_OpenWFun							POS_Port_OpenW							= NULL;
POS_Port_CloseFun							POS_Port_Close							= NULL;	
POS_Output_PrintStringAFun					POS_Output_PrintStringA 				= NULL;
POS_Output_PrintStringWFun					POS_Output_PrintStringW 				= NULL;
POS_Output_PrintDataFun						POS_Output_PrintData					= NULL;
POS_Control_CutPaperFun						POS_Control_CutPaper					= NULL;
POS_Control_CashDrawFun						POS_Control_CashDraw					= NULL;
POS_Status_QueryStatusFun					POS_Status_QueryStatus					= NULL;
POS_Status_RTQueryStatusFun					POS_Status_RTQueryStatus				= NULL;
POS_Status_RTQueryTypeStatusFun 			POS_Status_RTQueryTypeStatus        	= NULL;
POS_Output_DownloadBmpToFlashAFun           POS_Output_DownloadBmpToFlashA      	= NULL;
POS_Output_DownloadBmpToFlashNumAFun        POS_Output_DownloadBmpToFlashNumA   	= NULL;
POS_Output_PrintBmpDirectAFun	            POS_Output_PrintBmpDirectA          	= NULL;
POS_Output_PrintBmpDirectWFun	            POS_Output_PrintBmpDirectW          	= NULL;
POS_Output_PrintBarcodeAFun		            POS_Output_PrintBarcodeA            	= NULL;
POS_Output_PrintBarcodeWFun		            POS_Output_PrintBarcodeW            	= NULL;
POS_Output_PrintFontStringAFun	            POS_Output_PrintFontStringA         	= NULL;
POS_Output_PrintBmpInFlashFun				POS_Output_PrintBmpInFlash          	= NULL;
POS_Input_PrinterIdFun						POS_Input_PrinterId						= NULL;
POS_Input_ReadPrinterFun					POS_Input_ReadPrinter					= NULL;
POS_Control_BlackMarkFun        			POS_Control_BlackMark   				= NULL;
POS_Status_QueryTaskStatusFun   			POS_Status_QueryTaskStatus          	= NULL;
POS_Output_PrintFlashBmpFun     			POS_Output_PrintFlashBmp            	= NULL;
POS_Output_PrintOneDimensionalBarcodeAFun   POS_Output_PrintOneDimensionalBarcodeA  = NULL;
POS_Output_PrintTwoDimensionalBarcodeAFun   POS_Output_PrintTwoDimensionalBarcodeA  = NULL;
POS_Output_PrintTwoDimensionalBarcodeWFun   POS_Output_PrintTwoDimensionalBarcodeW  = NULL;
POS_Output_DownloadRamBmpAFun               POS_Output_DownloadRamBmpA          	= NULL;
POS_Output_DownloadRamBmpWFun               POS_Output_DownloadRamBmpW          	= NULL;
POS_Output_PrintRamBmpFun                   POS_Output_PrintRamBmp              	= NULL;
POS_Control_PrintTestpageFun    			POS_Control_PrintTestpage           	= NULL;
Color24_GrayBWFun               			Color24_GrayBW                      	= NULL;
POS_Control_SetRotaryPrintFun   			POS_Control_SetRotaryPrint          	= NULL;
POS_Control_OppositeColorFun    			POS_Control_OppositeColor           	= NULL;
POS_Control_SetInvertedPrintFun 			POS_Control_SetInvertedPrint        	= NULL;
POS_Control_AlignTypeFun 			        POS_Control_AlignType        	        = NULL;
POS_Output_SendLocalFileAFun                POS_Output_SendLocalFileA               = NULL;
POS_Control_ReSetFun                        POS_Control_ReSet                       = NULL;
POS_Control_SetPrintFontCFun                POS_Control_SetPrintFontC               = NULL;

static HINSTANCE hInst = NULL;
//static char szPath[] = "..\\..\\SDK\\POS_SDK.dll";
static char szPath[] = "POS_SDK.dll";
int LoadSDKLibrary()
{
	hInst = LoadLibraryA(szPath);
	if(hInst == NULL)
	{
		return -1;
	}

	POS_Port_OpenA = (POS_Port_OpenAFun)GetProcAddress(hInst, "POS_Port_OpenA");
	if(NULL == POS_Port_OpenA)
		goto ERR_END;

	POS_Port_OpenW = (POS_Port_OpenWFun)GetProcAddress(hInst, "POS_Port_OpenW");
	if(NULL == POS_Port_OpenW)
		goto ERR_END;

	POS_Output_PrintData = (POS_Output_PrintDataFun)GetProcAddress(hInst, "POS_Output_PrintData");
	if(NULL == POS_Output_PrintData)
		goto ERR_END;

	POS_Port_Close = (POS_Port_CloseFun)GetProcAddress(hInst, "POS_Port_Close");
	if(NULL == POS_Port_Close)
		goto ERR_END;

	POS_Output_PrintStringA = (POS_Output_PrintStringAFun)GetProcAddress(hInst, "POS_Output_PrintStringA");
	if(NULL == POS_Output_PrintStringA)
		goto ERR_END;

	POS_Output_PrintStringW = (POS_Output_PrintStringWFun)GetProcAddress(hInst, "POS_Output_PrintStringW");
	if(NULL == POS_Output_PrintStringW)
		goto ERR_END;

	POS_Control_CutPaper = (POS_Control_CutPaperFun)GetProcAddress(hInst, "POS_Control_CutPaper");
	if(NULL == POS_Control_CutPaper)
		goto ERR_END;

	POS_Control_CashDraw = (POS_Control_CashDrawFun)GetProcAddress(hInst, "POS_Control_CashDraw");
	if(NULL == POS_Control_CashDraw)
		goto ERR_END;

	POS_Status_QueryStatus = (POS_Status_QueryStatusFun)GetProcAddress(hInst, "POS_Status_QueryStatus");
	if(NULL == POS_Status_QueryStatus)
		goto ERR_END;

	POS_Status_RTQueryStatus = (POS_Status_RTQueryStatusFun)GetProcAddress(hInst, "POS_Status_RTQueryStatus");
	if(NULL == POS_Status_RTQueryStatus)
		goto ERR_END;

	POS_Status_RTQueryTypeStatus = (POS_Status_RTQueryTypeStatusFun)GetProcAddress(hInst, "POS_Status_RTQueryTypeStatus");
	if(NULL == POS_Status_RTQueryTypeStatus)
		goto ERR_END;

	POS_Control_BlackMark = (POS_Control_BlackMarkFun)GetProcAddress(hInst, "POS_Control_BlackMark");
	if(NULL == POS_Control_BlackMark)
		goto ERR_END;

	POS_Status_QueryTaskStatus = (POS_Status_QueryTaskStatusFun)GetProcAddress(hInst, "POS_Status_QueryTaskStatus");
	if(NULL == POS_Status_QueryTaskStatus)
		goto ERR_END;

	POS_Output_PrintFlashBmp = (POS_Output_PrintFlashBmpFun)GetProcAddress(hInst, "POS_Output_PrintFlashBmp");
	if(NULL == POS_Output_PrintFlashBmp)
		goto ERR_END;

	POS_Output_DownloadBmpToFlashA = (POS_Output_DownloadBmpToFlashAFun)GetProcAddress(hInst, "POS_Output_DownloadBmpToFlashA");
	if(NULL == POS_Output_DownloadBmpToFlashA)
		goto ERR_END;

	POS_Output_DownloadBmpToFlashNumA = (POS_Output_DownloadBmpToFlashNumAFun)GetProcAddress(hInst, "POS_Output_DownloadBmpToFlashNumA");
	if(NULL == POS_Output_DownloadBmpToFlashNumA)
		goto ERR_END;

	POS_Output_PrintBmpDirectA = (POS_Output_PrintBmpDirectAFun)GetProcAddress(hInst, "POS_Output_PrintBmpDirectA");
	if(NULL == POS_Output_PrintBmpDirectA)
		goto ERR_END;

	POS_Output_PrintBmpDirectW = (POS_Output_PrintBmpDirectWFun)GetProcAddress(hInst, "POS_Output_PrintBmpDirectW");
	if(NULL == POS_Output_PrintBmpDirectW)
		goto ERR_END;

	POS_Output_PrintBarcodeA = (POS_Output_PrintBarcodeAFun)GetProcAddress(hInst, "POS_Output_PrintBarcodeA");
	if(NULL == POS_Output_PrintBarcodeA)
		goto ERR_END;

	POS_Output_PrintBarcodeW = (POS_Output_PrintBarcodeWFun)GetProcAddress(hInst, "POS_Output_PrintBarcodeW");
	if(NULL == POS_Output_PrintBarcodeW)
		goto ERR_END;

	POS_Output_PrintFontStringA = (POS_Output_PrintFontStringAFun)GetProcAddress(hInst, "POS_Output_PrintFontStringA");
	if(NULL == POS_Output_PrintFontStringA)
		goto ERR_END;

	POS_Output_PrintBmpInFlash = (POS_Output_PrintBmpInFlashFun)GetProcAddress(hInst, "POS_Output_PrintBmpInFlash");
	if(NULL == POS_Output_PrintBmpInFlash)
		goto ERR_END;

	POS_Input_PrinterId = (POS_Input_PrinterIdFun)GetProcAddress(hInst, "POS_Input_PrinterId");
	if(NULL == POS_Input_PrinterId)
		goto ERR_END;

	POS_Input_ReadPrinter = (POS_Input_ReadPrinterFun)GetProcAddress(hInst, "POS_Input_ReadPrinter");
	if(NULL == POS_Input_ReadPrinter)
		goto ERR_END;

	POS_Output_PrintOneDimensionalBarcodeA = (POS_Output_PrintOneDimensionalBarcodeAFun)GetProcAddress(hInst, "POS_Output_PrintOneDimensionalBarcodeA");
	if(NULL == POS_Output_PrintOneDimensionalBarcodeA)
		goto ERR_END;

	POS_Output_PrintTwoDimensionalBarcodeA = (POS_Output_PrintTwoDimensionalBarcodeAFun)GetProcAddress(hInst, "POS_Output_PrintTwoDimensionalBarcodeA");
	if(NULL == POS_Output_PrintTwoDimensionalBarcodeA)
		goto ERR_END;

	POS_Output_PrintTwoDimensionalBarcodeW = (POS_Output_PrintTwoDimensionalBarcodeWFun)GetProcAddress(hInst, "POS_Output_PrintTwoDimensionalBarcodeW");
	if(NULL == POS_Output_PrintTwoDimensionalBarcodeW)
		goto ERR_END;

	POS_Output_DownloadRamBmpA = (POS_Output_DownloadRamBmpAFun)GetProcAddress(hInst, "POS_Output_DownloadRamBmpA");
	if(NULL == POS_Output_DownloadRamBmpA)
		goto ERR_END;

	POS_Output_DownloadRamBmpW = (POS_Output_DownloadRamBmpWFun)GetProcAddress(hInst, "POS_Output_DownloadRamBmpW");
	if(NULL == POS_Output_DownloadRamBmpW)
		goto ERR_END;

	POS_Output_PrintRamBmp = (POS_Output_PrintRamBmpFun)GetProcAddress(hInst, "POS_Output_PrintRamBmp");
	if(NULL == POS_Output_PrintRamBmp)
		goto ERR_END;

	POS_Control_PrintTestpage = (POS_Control_PrintTestpageFun)GetProcAddress(hInst, "POS_Control_PrintTestpage");
	if(NULL == POS_Control_PrintTestpage)
		goto ERR_END;

	Color24_GrayBW = (Color24_GrayBWFun)GetProcAddress(hInst, "Color24_GrayBW");
	if(NULL == Color24_GrayBW)
		goto ERR_END;

	POS_Control_SetRotaryPrint = (POS_Control_SetRotaryPrintFun)GetProcAddress(hInst, "POS_Control_SetRotaryPrint");
	if(NULL == POS_Control_SetRotaryPrint)
		goto ERR_END;

	POS_Control_OppositeColor = (POS_Control_OppositeColorFun)GetProcAddress(hInst, "POS_Control_OppositeColor");
	if(NULL == POS_Control_OppositeColor)
		goto ERR_END;

	POS_Control_SetInvertedPrint = (POS_Control_SetInvertedPrintFun)GetProcAddress(hInst, "POS_Control_SetInvertedPrint");
	if(NULL == POS_Control_SetInvertedPrint)
		goto ERR_END;

	POS_Control_AlignType = (POS_Control_AlignTypeFun)GetProcAddress(hInst, "POS_Control_AlignType");
	if(NULL == POS_Control_AlignType)
		goto ERR_END;

	POS_Output_SendLocalFileA = (POS_Output_SendLocalFileAFun)GetProcAddress(hInst, "POS_Output_SendLocalFileA");
	if(NULL == POS_Output_SendLocalFileA)
		goto ERR_END;

	POS_Control_ReSet = (POS_Control_ReSetFun)GetProcAddress(hInst, "POS_Control_ReSet");
	if(NULL == POS_Control_ReSet)
		goto ERR_END;

	POS_Control_SetPrintFontC = (POS_Control_SetPrintFontCFun)GetProcAddress(hInst, "POS_Control_SetPrintFontC");
	if(NULL == POS_Control_SetPrintFontC)
		goto ERR_END;

	//------------------ztongli.20170104---------------
	PageSetupTSPL = (CallPageSetupTSPL)GetProcAddress(hInst, "PageSetupTSPL");
	if(NULL == PageSetupTSPL)
		goto ERR_END;

	DrawLineTSPL = (CallDrawLineTSPL)GetProcAddress(hInst, "DrawLineTSPL");
	if(NULL == DrawLineTSPL)
		goto ERR_END;

	PrintTSPL51 = (CallPrintTSPL51)GetProcAddress(hInst, "PrintTSPL51");
	if(NULL == PrintTSPL51)
		goto ERR_END;

	DrawBorderTSPL = (CallDrawBorderTSPL)GetProcAddress(hInst, "DrawBorderTSPL");
	if(NULL == DrawBorderTSPL)
		goto ERR_END;

	DrawTextTSPL = (CallDrawTextTSPL)GetProcAddress(hInst, "DrawTextTSPL");
	if(NULL == DrawTextTSPL)
		goto ERR_END;

	DrawBarCodeTSPL = (CallDrawBarCodeTSPL)GetProcAddress(hInst, "DrawBarCodeTSPL");
	if(NULL == DrawBarCodeTSPL)
		goto ERR_END;

	ClearBuffTSPL = (CallClearBuffTSPL)GetProcAddress(hInst, "ClearBuffTSPL");
	if(NULL == ClearBuffTSPL)
		goto ERR_END;

Draw2DBarCodeTSPL = (CallDraw2DBarCodeTSPL)GetProcAddress(hInst, "Draw2DBarCodeTSPL");
	if(NULL == Draw2DBarCodeTSPL)
		goto ERR_END;

	DownLoadBitMapTSPL = (CallDownLoadBitMapTSPL)GetProcAddress(hInst, "DownLoadBitMapTSPL");
	if(NULL == DownLoadBitMapTSPL)
		goto ERR_END;

	PutBitMapTSPL = (CallPutBitMapTSPL)GetProcAddress(hInst, "PutBitMapTSPL");
	if(NULL == PutBitMapTSPL)
		goto ERR_END;

	GetPrinterStatusTSPL = (CallGetPrinterStatusTSPL)GetProcAddress(hInst, "GetPrinterStatusTSPL");
	if(NULL == GetPrinterStatusTSPL)
		goto ERR_END;

	DriveBeepTSPL = (CallDriveBeepTSPL)GetProcAddress(hInst, "DriveBeepTSPL");
	if(NULL == DriveBeepTSPL)
		goto ERR_END;

	SetCharsetNameTSPL = (CallSetCharsetNameTSPL)GetProcAddress(hInst, "SetCharsetNameTSPL");
	if(NULL == SetCharsetNameTSPL)
		goto ERR_END;

	SetPaperbackOrPaperFeedTSPL = (CallSetPaperbackOrPaperFeedTSPL)GetProcAddress(hInst, "SetPaperbackOrPaperFeedTSPL");
	if(NULL == SetPaperbackOrPaperFeedTSPL)
		goto ERR_END;

	ReverseAreaTSPL = (CallReverseAreaTSPL)GetProcAddress(hInst, "ReverseAreaTSPL");
	if(NULL == ReverseAreaTSPL)
		goto ERR_END;

	SelectCodePageTSPL = (CallSelectCodePageTSPL)GetProcAddress(hInst, "SelectCodePageTSPL");
	if(NULL == SelectCodePageTSPL)
		goto ERR_END;

	SetGAPTSPL = (CallSetGAPTSPL)GetProcAddress(hInst, "SetGAPTSPL");
	if(NULL == SetGAPTSPL)
		goto ERR_END;

	SetLabelReferenceTSPL = (CallSetLabelReferenceTSPL)GetProcAddress(hInst, "SetLabelReferenceTSPL");
	if(NULL == SetLabelReferenceTSPL)
		goto ERR_END;

	SetLabelReferenceTSPL = (CallSetLabelReferenceTSPL)GetProcAddress(hInst, "SetLabelReferenceTSPL");
	if(NULL == SetLabelReferenceTSPL)
		goto ERR_END;

	PrintTSPL21 = (CallPrintTSPL21)GetProcAddress(hInst, "PrintTSPL21");
	if(NULL == PrintTSPL21)
		goto ERR_END;

	SetIs21 = (CallSetIs21)GetProcAddress(hInst, "SetIs21");
	if(NULL == SetIs21)
		goto ERR_END;

	return 0;

ERR_END:
	FreeLibrary(hInst);
	hInst = NULL;
	return -1;
}

void FreeSDKLibrary()
{
	if(hInst)
	{
 		FreeLibrary(hInst);
		hInst = NULL;
	}
}
	
#endif