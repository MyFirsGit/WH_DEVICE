
//����ӡ������port���壺
#define POS_PT_COM			1000L
#define POS_PT_LPT			1001L
#define POS_PT_USB			1002L
#define POS_PT_NET			1003L

// ��ӡ�������붨�壺
#define POS_ES_PAPERENDING  6L //ֽ����
#define POS_ES_DRAWERHIGH   5L //Ǯ��ߵ�ƽ
#define POS_ES_CUT          4L //�е�δ��λ
#define POS_ES_DOOROPEN     3L //ֽ���ſ�
#define	POS_ES_HEAT         2L //��ͷ����
#define POS_ES_PAPEROUT     1L //��ӡ��ȱֽ
#define POS_ES_SUCCESS      0L //�ɹ�/���ͳɹ�/״̬����/��ӡ���
#define POS_ES_INVALIDPARA  -1L //��������
#define POS_ES_WRITEFAIL    -2L //дʧ��
#define POS_ES_READFAIL     -3L //��ʧ��
#define POS_ES_NONMONOCHROMEBITMAP -4L //�ǵ�ɫλͼ
#define POS_ES_OVERTIME     -5L //��ʱ/д��ʱ/����ʱ/��ӡδ���
#define POS_ES_FILEOPENERROR -6L //�ļ�/ͼƬ��ʧ��
#define POS_ES_OTHERERRORS   -100L //����ԭ���µĴ���

// barcode type
#define POS_BT_UPCA			4001L
#define POS_BT_UPCE			4002L
#define POS_BT_JAN13		4003L
#define POS_BT_JAN8			4004L
#define POS_BT_CODE39		4005L
#define POS_BT_ITF			4006L
#define POS_BT_CODABAR		4007L
#define POS_BT_CODE93		4073L
#define POS_BT_CODE128		4074L

//Dimensional barcode type
#define POS_BT_PDF417		4100L
#define POS_BT_DATAMATRIX	4101L
#define POS_BT_QRCODE		4102L

// HRI type
#define POS_HT_NONE			4011L
#define POS_HT_UP			4012L
#define POS_HT_DOWN			4013L
#define POS_HT_BOTH			4014L

//TSPL
#define TSPL_PRINTER_STATUS_OUTPAPER 1L	//��ӡ��ȱֽ
#define TSPL_PRINTER_STATUS_WORK 2L	//��ӡ��
#define TSPL_PRINTER_STATUS_ENCLOSURENOCLOSE 3L	//����δ��
#define TSPL_PRINTER_STATUS_ERROR 4L	//��ӡ���ڲ�����

#define TSPL_PARAM_LESS_EQUAL_ZERO		-2L		//����С�ڵ���0
#define TSPL_PARAM_GREAT_RANGE          -3L		//��������ָ����Χ
#define TSPL_SUCCESS					0L
#define TSPL_IDERROR					-1L


//
//const int  PRINT_MOVEDOWN_ROWNUM = 0x08;   //��ӡ����ӡ�����ֽ����
//const int  Printer_WAIT_TIME = 30000;     //��ӡ���ȴ�ʱ��
//const int  BOX_WAIT_TIME = 5000;     //��Ǯ��ȴ�ʱ��
//
//
//static const unsigned long  COMMAND_Printer_CONNECT = 0x5101  ; //�򿪴���
//static const unsigned long  COMMAND_Printer_PRINT = 0x5102  ;   //��ӡ����
//static const unsigned long  COMMAND_Printer_CLOSE = 0x5103  ;   //�رմ�ӡ��
//static const unsigned long  COMMAND_Printer_OPENBOX = 0x5104  ;  //�ر�Ǯ��
