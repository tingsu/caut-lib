#include "caut.h"
 
#define INT2Status        (volatile unsigned int *)0x1300C004  /* 中断2的中断寄存器 */
#define INT2Mask          (volatile unsigned int *)0x1300C000  /* 中断2的中断寄存器 */
#define INT2Clear         (volatile unsigned int *)0x1300C008  /* 中断2的中断寄存器 */
unsigned int WorkModeFlg;
/* SIO板 */
/* 关联部件：4路动量轮 */
#define START_MW1_DA_CS       ((volatile unsigned int *)(0x10000000))   /* 启动第1路动量轮电压控制 §写 */
#define START_MW2_DA_CS       ((volatile unsigned int *)(0x10000004))   /* 启动第2路动量轮电压控制 §写 */
#define START_MW3_DA_CS       ((volatile unsigned int *)(0x10000008))   /* 启动第3路动量轮电压控制 §写 */
#define START_MW4_DA_CS       ((volatile unsigned int *)(0x1000000C))   /* 启动第4路动量轮电压控制 §写 */
/* 8252口地址 */
#define LTU_TBR_CS            ( *((volatile int * )0x10000040) )
#define LTU_RBR_CS            ( *((volatile int * )0x10000040) )
#define LTU_UCR_CS            ( *((volatile int * )0x10000044) )
#define LTU_USR_CS            ( *((volatile int * )0x10000044) )
#define LTU_MCR_CS            ( *((volatile int * )0x10000048) )
#define LTU_BRSR_CS           ( *((volatile int * )0x1000004C) )
#define LTU_MSR_CS            ( *((volatile int * )0x1000004C) )

/* 通过多路选择器选择LTU通道，由数据线的D[3:0]进行译码选择，映射关系为0000-1110:LTU1-LTU15,1111:自测试 §写 */
#define LTU_SELECT_CS         (*((volatile unsigned int *)(0x10000050)))
#define RD_MW1_COUNT          ((volatile unsigned int *)(0x10000064) )   /* 读第1路动量轮计数器     §读 */
#define RD_MW2_COUNT          ((volatile unsigned int *)(0x1000006C) )   /* 读第2路动量轮计数器     §读 */
#define RD_MW3_COUNT          ((volatile unsigned int *)(0x10000074) )   /* 读第3路动量轮计数器     §读 */
#define RD_MW4_COUNT          ((volatile unsigned int *)(0x1000007C) )   /* 读第4路动量轮计数器     §读 */
#define START_GD_COUNT        ((volatile unsigned int *)(0x10000080) )   /* 启动滚动发动机计数      §写 */
#define START_FY_COUNT        ((volatile unsigned int *)(0x10000084) )   /* 启动俯仰发动机计数      §写 */
#define START_PH_COUNT        ((volatile unsigned int *)(0x10000088) )   /* 启动偏航发动机计数      §写 */
#define START_GK_COUNT        ((volatile unsigned int *)(0x1000008C) )   /* 启动轨控发动机计数      §写 */

/* PIO板 */
#define RD_SLSP_CS1           ((volatile unsigned int *)(0x11000000) )   /* 塔架星箭分离信号     §读 */
#define RD_SLSP_CS2           ((volatile unsigned int *)(0x11000004) )   /* 塔架星箭分离信号     §读 */
#define RD_SLSP_CS3           ((volatile unsigned int *)(0x11000008) )   /* 塔架星箭分离信号     §读 */
#define RD_UPS_STATUS_CS      ((volatile unsigned int *)(0x11000010) )   /* 推进系统的7位状态量     §读 */
#define OPEN_VALVE_CS         ((volatile unsigned int *)(0x11000014) )   /* 对推进系统3路自锁阀进行打开操作 §写 */
#define CLOSE_VALVE_CS        ((volatile unsigned int *)(0x11000018) )   /* 对推进系统3路自锁阀进行关闭操作§写 */
#define CONNECT_B_BRANCH_CS   ((volatile unsigned int *)(0x1100001C) )   /* 控制B分支推力器接通     §写 */
#define BOOT_490N_CS          ((volatile unsigned int *)(0x11000020) )   /* 控制490N发动机的打开    §写 */
#define SHUTDOWN_490N_CS      ((volatile unsigned int *)(0x11000024) )   /* 控制490N发动机的关闭    §写 */
#define POWER_ON_490N_CS      ((volatile unsigned int *)(0x11000028) )   /* 打开UPS电源            §写 */
#define POWER_OFF_490N_CS     ((volatile unsigned int *)(0x1100002C) )   /* 关闭UPS电源            §写 */
#define CONTROL_10N_CS        ((volatile unsigned int *)(0x11000030) )   /* 控制12路10N发动机的喷气  §写 */
#define READ_MW_DIR_CS        ((volatile unsigned int *)(0x11000040) )   /* 读4路动量轮的转速方向   §读*/
#define READ_EE_FLAG_CS       ((volatile unsigned int *)(0x11000050) )   /* 读应急标志              §读 */
#define READ_SDC_LSTATUS_CS   ((volatile unsigned int *)(0x11000060) )   /* 读SDC低16位状态         §读 */
#define READ_SDC_HSTATUS_CS   ((volatile unsigned int *)(0x11000064) )   /* 读SDC高16位状态         §读 */
#define CONTROL_SDC_CS        ((volatile unsigned int *)(0x1100006C) )   /* 6路SDC开关控制          §写 */
#define RD_DUTY_MACHINE_CS    (*(volatile unsigned int *)(0x11000070) )  /* 读当班机编码信息        §读 */


/* 1553b寄存器地址定义 */
#define INTERRUPT_MASK_REG              (0x0000)
#define CONFIGURATION_1_REG             (0x0001)
#define CONFIGURATION_2_REG             (0x0002)
#define START_RESET_REG                 (0x0003)
#define COMMAND_STACK_POINTER_REG       (0x0003)
#define BC_CONTROLL_WORD_REG            (0x0004)
#define RT_SUBADDR_CONTROL_WORD_REG     (0x0004)
#define TIME_TAG_REG                    (0x0005)
#define INTERRUPT_STATUS_REG            (0x0006)
#define CONFIGURATION_3_REG             (0x0007)
#define CONFIGURATION_4_REG             (0x0008)
#define CONFIGURATION_5_REG             (0x0009)
#define RT_DATA_STACK_ADDR_REG          (0x000A)
#define MONITOR_DATA_STACK_ADDR_REG     (0x000A)
#define BC_FRAME_TIME_REMAINING_REG     (0x000B)
#define BC_MESSAGE_TIME_REMAINING_REG   (0x000C)
#define BC_FRAME_TIME_REG               (0x000D)
#define RT_LAST_COMMAND_REG             (0x000D)
#define MT_TRIGGER_REG                  (0x000D)
#define RT_STATUS_WORD_REG              (0x000E)
#define RT_BIT_WORD_REG                 (0x000F)
#define RT_COMMAND_STACK_POINT_A        (0x0100)
/* 1553b用户分配的MEM空间定义 */
#define RT_A_RECEIVE_SUBADDR(i)         ( 0x0140 + (i) )
#define RT_A_TRANSMIT_SUBADDR(i)        ( 0x0160 + (i) )
#define RT_A_BROADCAST_SUBADDR(i)       ( 0x0180 + (i) )
#define RT_A_CONTROL_WORD_SUBADDR(i)    ( 0x01A0 + (i) )

#define AddrLastCmd         (volatile unsigned int *)0x13000000  /* 命令指令存放地址 */
#define Address_1_1553b     (volatile unsigned int *)0x13005080  /* 发送接收OBDH重要数据1的地址 */
#define Address_2_1553b     (volatile unsigned int *)0x13005100  /* 发送接收OBDH重要数据2的地址 */
#define Address_3_1553b     (volatile unsigned int *)0x13005180  /* 发送接收OBDH重要数据3的地址 */
#define Address_4_1553b     (volatile unsigned int *)0x13005200  /* 发送接收OBDH重要数据4的地址 */
#define Address_5_1553b     (volatile unsigned int *)0x13005280  /* 发送接收OBDH重要数据5的地址 */
#define Address_6_1553b     (volatile unsigned int *)0x13005300  /* 发送接收OBDH重要数据6的地址 */
#define Address_7_1553b     (volatile unsigned int *)0x13005380  /* 发送接收OBDH重要数据7的地址 */
#define Address_8_1553b     (volatile unsigned int *)0x13005400  /* 发送接收OBDH重要数据8的地址 */
#define Address_9_1553b     (volatile unsigned int *)0x13005480  /* 发送接收OBDH重要数据9的地址 */
#define Address_10_1553b    (volatile unsigned int *)0x13005500  /* 发送接收GNC重要数据1的地址 */
#define Address_11_1553b    (volatile unsigned int *)0x13005580  /* 发送接收GNC重要数据2的地址 */
#define Address_12_1553b    (volatile unsigned int *)0x13005600  /* 发送接收GNC重要数据3的地址 */
#define Address_13_1553b    (volatile unsigned int *)0x13005680  /* 发送接收GNC重要数据4的地址 */
#define Address_TR18_1553b  (volatile unsigned int *)0x13005780  /* 向OBDH发送的时间码地址 */
#define Address_TR19_1553b  (volatile unsigned int *)0x13005800  /* 发送姿态数据地址 */
#define Address_TR20_1553b  (volatile unsigned int *)0x13005880  /* 发送GNC数字遥测量参数地址 296字节 */
#define Address_TR21_1553b  (volatile unsigned int *)0x13005C80  /* 发送GNC内存数据地址 1088字节 */
#define Address_RE18_1553b  (volatile unsigned int *)0x13006C80  /* 接收时间码地址 */
#define Address_RE21_1553b  (volatile unsigned int *)0x13006D80  /* 接收遥控注入数据地址 */
#define Address_RE26_1553b  (volatile unsigned int *)0x13006F80  /* 接收内存地址及长度 */
#define Address_RE31_1553b  (volatile unsigned int *)0x13007000  /* 子地址31指令存放地址 */
#define Address_TR31_1553b  (volatile unsigned int *)0x13007080  /* 子地址31指令存放地址 */
/*  时间地址*/
#define Address_TIME_GPT    (volatile unsigned int *)0x01F80088  /* 内部定时器口地址 */

#define FIRSTWORKMODE     (unsigned int *)0x2017000  /* 工作模式字3取2之一 */
#define SECONDWORKMODE    (unsigned int *)0x2019400  /* 工作模式字3取2之二 */
#define THIRDWORKMODE     (unsigned int *)0x201b800  /* 工作模式字3取2之三 */

#define TR32_WORKMODE              Tr32_uint(WorkModeFlg)//(Tr32_uint(FIRSTWORKMODE,SECONDWORKMODE,THIRDWORKMODE))/* 工作模式字3取2 */
#define TR32_WORKMODE_VALUE(x)     WorkModeFlg=x//(Tr32_uint_value(FIRSTWORKMODE,SECONDWORKMODE,THIRDWORKMODE,(x)))/* 工作模式字写3区 */

/* 三角函数值 */
#define COS15           0.9659258263f
#define COS45           0.7071067812f
#define COS46P92        0.6830188573f
#define COS75           0.2588190451f
#define COS79P45        0.1830935078f
#define COS90           0.0f
#define COS100P54       -0.1829219225f
#define COS133P08       -0.6830188573f
#define SIN_epsilon     0.3963196067f         /* ε=23.3483度 */
#define COS_epsilon     0.9181126125f         /* ε=23.3483度 */
#define FloatZero       1e-7f
#define RAD_DEGREE      57.2957795f

#define CONST_2PI       6.2831853f
#define CONST_PI        3.1415927f
#define CONST_HalfPI    1.5707963f

#define CONST_ae        384747981.0f
#define CONST_as        1.49598e11f
#define CONST_DMl      	2.6392045e-6f     /* 白道平近点角变化率(Ml)'=2.6392045e-6 rad/s */
#define CONST_DMs      	1.99096875e-7f    /* (Ms)'=1.99096875e-7 */
#define CONST_ee       	0.054880f         /* ee = 0.054880 */
#define CONST_eeee      0.0030118144f     /* ee*ee = 0.0030118144f */
#define CONST_es       	0.016705291f      /* es=0.016705291f */
#define CONST_eses     	0.0002790667f     /* es*es=0.016705291f */
#define CONST_Gm        4.902800269e12f   /* 月球引力常数＝4.902800269e12 米3/秒2 */
#define CONST_ie      	0.08953251f       /* ie=0.08953251 rad */
#define CONST_Rm        1738000.0f        /* 月球参考椭球赤道半径＝1738000 米 */
#define CONST_ws       -1.3426259f        /* ωs=-1.3426259frad */
#define CONST_we        0.806342f         /* ωe=0.806342rad */
#define DELAYNUM        1500              /* LTU通讯延时等待次数 */

#define flg_valid       0xeb90146f       /* 有效 */
#define flg_invalid     0xCCCCCCCC       /* 无效 */
#define Switch_Cmd_Valid  0x5aeb         /* 切机命令字：切机 */

#define IDTask64msOr256ms       1        /* 控制周期任务 */       
#define IDStarDirection         2        /* 恒星定向 */ 
#define IDInertialAdjustAtti    3        /* 惯性调姿 */ 
#define IDOrbitDirection        4        /* 轨控定向 */ 
#define IDUVAroundMoon          5        /* 紫外环月 */ 
#define IDSTSAroundMoon         6        /* 星光环月 */       
#define IDGyroAroundMoon        7        /* 陀螺环月 */ 
#define IDSunDirection          8        /* 太阳定向 */ 
#define IDMWControl             9        /* 动量轮控制 */ 
#define IDWorkModeFlgManage     10       /* 工作模式自主转换的管理程序 */ 
#define IDJetPhase              11       /* 相平面计算 */       
#define IDPulseJet              12       /* 脉冲调宽 */ 
#define IDCaptureAndPointSun    13       /* 太阳捕获及对日定向 4.6 */ 
#define IDModifySTS             14       /* 星敏感器的姿态修正 */ 
#define IDDiagnoseLTU           15       /* 控制周期任务 */ 
#define IDNOControl           16         /* 无控模式 */

/* 加速度计 */
typedef struct
{
    float   as[2];              /* 加速度计输出 */
    float   as0[2];             /* 加速度计零位偏差 */
}ACCELERATE;
ACCELERATE  Acce;

/*姿态数据块的数据*/
typedef struct
{
    unsigned int    BZ0;
    unsigned int    BZ1;
    unsigned int    BZ2;
    unsigned int    BZ3;
    unsigned int    BZ4;
    unsigned int    BZ5;
    unsigned int    BZ5a;
    unsigned int    BZ6;
    unsigned int    BZ7;
    unsigned int    BZ8;
    unsigned int    BZ9;
    unsigned int    BZ10;
    unsigned int    BZ11;
    unsigned int    BZ12;
    unsigned int    BZ13;
    unsigned int    BZ14;
    unsigned int    BZ15;
    unsigned int    BZ16;
    unsigned int    BZ17;
    unsigned int    BZ18;
    unsigned int    BZ19;
    unsigned int    BZ20;
    unsigned int    BZ21;
    unsigned int    BZ22;
    unsigned int    BZ23;
    unsigned int    BZ24;
    unsigned int    BZ25;
    unsigned int    BZ26;
	unsigned int    ZT10;
	unsigned int    ZT14;
	unsigned int    BZUV;
    unsigned int    PR1;
    unsigned int    PR2;
    unsigned int    PR3;
    unsigned int    PR4;
    unsigned int    PR5;
    unsigned int    PR6;
    unsigned int    PR7;
    unsigned int    PR8;
    unsigned int    PR9;
    unsigned int    PR10;
    unsigned int    PR11;
    unsigned int    PR12;
    unsigned int    PR13;
    unsigned int    PR14;
    unsigned int    PR15;
    unsigned int    PR16;

    float       q[4];
	float       qg[4];
    float       qTI[4];
    float       qOI[4];
    float       qBT[4];
    float       qBO[4];
    float       qGI[4];
    float       Deltaq[4];
    float       A0[3];
    float       AOI[3][3];
    float       ABO[3][3];
    float       ABI[3][3];
    float       ABT[3][3];
} ATTI;
ATTI    Atti;

/* 姿态角速度数据结构 */
typedef struct
 {
    float  A[3];             /* 姿态角估值 */
    float  Rate[3];          /* 姿态角速度估值 */
    float  AC[3];            /* 姿态角控制量 */
    float  RateC[3];         /* 姿态角速度控制量 */

    float  As[3];            /* 用于太阳定向模式中 */
    float  At[3];            /* 姿态角 */
    float  RateC0[3];        /* 姿态角速度 */

    float  Az[3];            /* 紫外输出 */
	float  Az1[3];           /* 紫外输出 */
	float  Az2[3];           /* 紫外输出 */
    float  DeltaAz[3];       /* 紫外误差估计 */
    float  DeltaA[3];        /* 紫外计算的姿态偏差 */
    float  DeltaAsz[3];      /*  */
    float  DeltaAszS[3];     /*  */
    float  Asz[3];           /*  */
}ATTITUDEDATA;


/* 帆板数据 */
typedef struct
 {
    float DeltaAlphaF1; /* A组帆板转角误差 */
    float DeltaAlphaF2; /* B组帆板转角误差 */
    float DeltaAlphaF1Star;
    float DeltaAlphaF2Star;
    float WF1;          /* A组帆板驱动机构指令角速度 */
    float WF2;          /* B组帆板驱动机构指令角速度 */
    unsigned int AlphaFT;/* 帆板转角设置 */
    unsigned int WFT;    /* 帆板角速度设置 */
}BAPTADATA;
BAPTADATA      BAPTAData;

/* 帆板控制命令 */
typedef struct
{
	unsigned int    channelL;        /* 左帆板通道号 */
	unsigned int    channelR;        /* 右帆板通道号 */
	unsigned int    CmdL[2];		 /* 左帆板控制指令 */
	unsigned int    CmdR[2];         /* 左帆板控制指令 */
}BAPTACTRL;
BAPTACTRL	   BAPTACtrl;

/* 计算的卫星轨道数据结构 */
typedef struct
{

	float  f;                /* 卫星根数之真近点角 */
	float  w0;               /* 卫星轨道角速度ω0 */
	float  rho;              /* 月球半张角ρ rad*/
	float  rEM;              /* 地月距 */
	float  rES;              /*  */
	float  r;                /* 月心距 米 */
	float  u;                /*  */
	float  M;                /*  */
	float  E;                /*  */
	float  dt;               /*  */
	float  LOmegae;          /*  */
	float  we;               /*  */
	float  Me;               /*  */
	float  ue;               /*  */
	float  Ms;               /* 太阳在惯性坐标系的分量 */
	float  us;               /* 太阳在惯性坐标系的分量 */
	float  Ei[3];			 /* 地心矢量在月心地球赤道惯性坐标系中的分量 */
	float  Eo[3];            /* 地心方向单位矢量Eox,Eoy,Eoz */
	float  Si[3];            /* 太阳矢量在月心地球赤道惯性坐标系的方位 */
	float  So[3];            /* 太阳向量在轨道坐标系的方位Sox,Soy,Soz */
}CalOrbitDATA;
CalOrbitDATA   CalOrbit;

/* 太阳捕获数据 */
typedef struct
{
	unsigned int Smode;         /*  */
	unsigned int TCount;        /*  */
	unsigned int TSmode;        /*  */
	unsigned int Eclipse;       /*  */
	float		 SqrtSumDW;     /*  */
}CaptureSSDATA;
      /* 太阳捕获数据 */

typedef struct
{
    volatile unsigned int Address;     /* 下传数据首地址 */
    volatile unsigned int num;         /* 下传数据字节的长度 */
}DOWNLOAD;
DOWNLOAD  DownLoad;                    /* 下传数据 */

/* 滤波系数块 */
typedef struct
{
    float   mKSAq;          /* 滤波系数KSA前三行修正因子 */
    float   mKSAb;          /* 滤波系数KSA后三行修正因子 */
    float   mKSBq;          /* 滤波系数KSB前三行修正因子 */
    float   mKSBb;          /* 滤波系数KSB后三行修正因子 */
    float   mKSCq;          /* 滤波系数KSC前三行修正因子 */
    float   mKSCb;          /* 滤波系数KSC后三行修正因子 */
}FILTER;
FILTER  Filter;

/* 天线数据 */
typedef struct
{
    float   Bae;        /*  */
    float   Bbe;        /* βae;βbe */
    float   Es[3];      /*  */
    float   Eb[3];      /*  */
    float   Baf;        /*  */
    float   Bbf;        /* 天线角度控制指令。βaf;βbf */
    float   Gda0_a;     /* 天线A轴零位补偿指令 */
    float   Gda0_b;     /* 天线B轴零位补偿指令 */
    unsigned int Bafcmd;
    unsigned int Bbfcmd;
    float   Bm;         /* 注入量，初值90度 */
    unsigned int ABKeepZeroNum;     /*  */
    float   BaeT;
    float   BbeT;
    unsigned int ZeroFlg;/* 天线双轴已归零的标志 */
}GDADATA;
GDADATA        GDAData;

/* 陀螺数据结构 */
typedef struct
{
    float  DeltaG[8];          /* 六陀螺一控制周期内角度增量,+2个加速度计 */
    float  b[3];               /* XYZ轴陀螺常值漂移 */
    float  xw[3];              /* 修正后的陀螺三轴角速度 */
    float  xwTI[3];            /*  */
    float  xwBT[3];            /*  */
    float  DG[3];
    int    GC[6];              /* 陀螺故障诊断的积分 */
    unsigned int WorkStatus[6];/* 六陀螺数据工作状态标志 */
    float  NormW;              /* 陀螺角速度的模 */     
}GYRODATA;
GYRODATA       GyroData;

/* 注入的卫星轨道数据结构 */
typedef struct
 {
	unsigned int  t0;        /* 初始参数注入时刻 */
	float  a0;          		 /* 注入时刻选取的参考轨道根数之半长轴 */
	float  a;                /* 注入的一组二体轨道根数之半长轴 */
	float  e;                /* 注入的一组二体轨道根数之偏心率 */
	float  i;                /* 注入的一组二体轨道根数之倾角 */
	float  LOmega;           /* 注入的一组二体轨道根数之升交点赤径 */
	float  w;                /* 注入的一组二体轨道根数之近地点幅角 */
	float  M;                /* 注入的一组二体轨道根数之初始平近点角 */
}InOrbitDATA;
InOrbitDATA    InOrbit;

/* 地面注入参数 */
typedef struct
{
	float mg;                   /* 陀螺故障判别阀值因子 */
	float mqa;                  /* 系统故障判别阀值因子 */
	float LOmegal0;             /* 轨道 */
	float Ms0;                  /* 轨道 */
	float Orbit[74];            /* 轨道 */
	float WT[3];
	float ul0;
	float Dul0;
	float ie;                   /* 白道相对赤道的平均倾角 */
}INPara;


/* 喷气控制的数据结构 */
typedef struct
 {
	float           TJ[3];                  /* 各轴喷气脉宽 */
	float           Thetapst[3];            /* 上周期喷气时的姿态数据 */
	float           Jet_TotalTime_Temp[6];  /* 各轴喷气总计脉宽 */
	unsigned int    Jet_TotalTime[6];       /* 各轴喷气总计脉宽 */
	unsigned int    Jet_Num[6];             /* 各轴喷气次数 */
	unsigned int    StFlag[3];              /* 各轴喷气状态 1 正喷，产生正力矩 */
	float           PW[3];                  /* 各轴喷气脉宽 */
	unsigned int	ALL[3];					/* 喷管全开标志 */
}JPC_DATA;
JPC_DATA       JPCData;

/* K参数 */
typedef struct
 {
    float A[3];              /* 紫外滤波系数的修正因子 Phi,Theta,Psi */
    float d[3];              /* 紫外滤波系数的修正因子 dx,dy,dz */
    float RY[5][3];          /* 紫外-太阳定姿系数修正因子 */
    float P[3][2];           /* 紫外-太阳定姿系数修正因子 */
}KPara;
KPara          K;


/* 选通LTU的标志 */
typedef struct
{
	unsigned int GyroAcce1; /* 惯性元件主份 */
	unsigned int GyroAcce2;	/* 惯性元件备份 */
	unsigned int IdleAcce1;	/* 空。设置空变量的原因：LTUSelect()内使用for循环，
	                           需要此结构内变量顺序与LTUPowerStatusFlg相应位相对应 */
	unsigned int IdleAcce2;	/* 空 */
	unsigned int SS1;       /* 太阳主份 */
	unsigned int SS2;       /* 太阳备份 */
	unsigned int UV1;       /* 紫外1 */
	unsigned int UV2;       /* 紫外2 */
	unsigned int STS1;      /* 星敏1 */
	unsigned int STS2;      /* 星敏2 */
	unsigned int STS3;	    /* 星敏3 */
	unsigned int IdleMW1;	/* 空 */
	unsigned int IdleMW2;	/* 空 */
	unsigned int IdleMW3;	/* 空 */
	unsigned int IdleMW4;	/* 空 */
	unsigned int BAPTAL;    /* 左帆板 flg_valid/flg_invalid：主份/备份 */
	unsigned int BAPTAR;    /* 右帆板 flg_valid/flg_invalid：主份/备份 */
	unsigned int GDA;       /* 天线   flg_valid/flg_invalid：主份/备份 */
}LTUSelectFlg;
LTUSelectFlg   LTUSelect;       /* LTU选通的标志 */

/* LTU的通讯数据 */
typedef struct
 {
	unsigned int SS1[12];        /* 太阳主份 */
	unsigned int SS2[12];        /* 太阳备份 */
	unsigned int GyroAcce1[33];  /* 惯性元件主份采集数据 */
	unsigned int GyroAcce2[33];	 /* 惯性元件备份采集数据 */
	int 		 GyroAcceTele1[8];   /* 惯性元件主份采集数据 */
	int 		 GyroAcceTele2[8];	 /* 惯性元件备份采集数据 */
	unsigned int GyroAcce1Old[18];   /* 惯性元件主份上次处理出的脉冲数 */
	unsigned int GyroAcce2Old[18];	 /* 惯性元件备份上次处理出的脉冲数 */
	unsigned int UV1[8];         /* 紫外1 */
	unsigned int UV2[8];         /* 紫外2 */
	unsigned int STS1[30];       /* 星敏1 */
	unsigned int STS2[30];       /* 星敏2 */
	unsigned int STS3[30];	     /* 星敏3 */
	unsigned int BAPTAL1[3];     /* 左帆板主份*/
	unsigned int BAPTAL2[3];     /* 左帆板备份 */
	unsigned int BAPTAR1[3];     /* 右帆板主份 */
	unsigned int BAPTAR2[3];     /* 右帆板备份 */
	unsigned int GDA1[5];        /* 天线主份 */
	unsigned int GDA2[5];        /* 天线备份 */
}LTUDATA;
LTUDATA        LTUData;			 /* LTU通讯数据 */

/* LTU的通讯错误计数标志 */
typedef struct
 {
	unsigned int GyroAcce1; 	/* 惯性元件主份 */
	unsigned int GyroAcce2;		/* 惯性元件备份 */
	unsigned int IdleAcce1;		/* 空 */
	unsigned int IdleAcce2;		/* 空 */
	unsigned int SS1;       	/* 太阳主份 */
	unsigned int SS2;       	/* 太阳备份 */
	unsigned int UV1;       	/* 紫外1 */
	unsigned int UV2;       	/* 紫外2 */
	unsigned int STS1;      	/* 星敏1 */
	unsigned int STS2;      	/* 星敏2 */
	unsigned int STS3;	    	/* 星敏3 */
	unsigned int BAPTAL1;   	/* 左帆板主份 */
	unsigned int BAPTAL2;   	/* 左帆板备份 */
	unsigned int BAPTAR1;   	/* 右帆板主份 */
	unsigned int BAPTAR2;   	/* 右帆板备份 */
	unsigned int GDA1;      	/* 天线主份 */
	unsigned int GDA2;      	/* 天线备份 */

	unsigned int OldGyroAcce1; 	/* 惯性元件主份 */
	unsigned int OldGyroAcce2;	/* 惯性元件备份 */
	unsigned int OldIdleAcce1;	/* 空 */
	unsigned int OldIdleAcce2;	/* 空 */
	unsigned int OldSS1;       	/* 太阳主份 */
	unsigned int OldSS2;       	/* 太阳备份 */
	unsigned int OldUV1;       	/* 紫外1 */
	unsigned int OldUV2;       	/* 紫外2 */
	unsigned int OldSTS1;      	/* 星敏1 */
	unsigned int OldSTS2;      	/* 星敏2 */
	unsigned int OldSTS3;	    /* 星敏3 */
	unsigned int OldBAPTAL1;   	/* 左帆板主份 */
	unsigned int OldBAPTAL2;   	/* 左帆板备份 */
	unsigned int OldBAPTAR1;   	/* 右帆板主份 */
	unsigned int OldBAPTAR2;   	/* 右帆板备份 */
	unsigned int OldGDA1;      	/* 天线主份 */
	unsigned int OldGDA2;      	/* 天线备份 */

	unsigned int ValveGyroAcce1;/* 惯性元件主份 */
	unsigned int ValveGyroAcce2;/* 惯性元件备份 */
	unsigned int ValveIdleAcce1;/* 空 */
	unsigned int ValveIdleAcce2;/* 空 */
	unsigned int ValveSS1;      /* 太阳主份 */
	unsigned int ValveSS2;      /* 太阳备份 */
	unsigned int ValveUV1;      /* 紫外1 */
	unsigned int ValveUV2;      /* 紫外2 */
	unsigned int ValveSTS1;     /* 星敏1 */
	unsigned int ValveSTS2;     /* 星敏2 */
	unsigned int ValveSTS3;	    /* 星敏3 */
	unsigned int ValveBAPTAL1;  /* 左帆板主份 */
	unsigned int ValveBAPTAL2;  /* 左帆板备份 */
	unsigned int ValveBAPTAR1;  /* 右帆板主份 */
	unsigned int ValveBAPTAR2;  /* 右帆板备份 */
	unsigned int ValveGDA1;     /* 天线主份 */
	unsigned int ValveGDA2;     /* 天线备份 */
	
	unsigned int IdleGyroAcce1;	/* 当不需要进行错误次数累计时，将发生的错误堆积至Idle */
	unsigned int IdleGyroAcce2;
	unsigned int Idle;
}LTUError;
LTUError       LTUErrorNum;      /* LTU通讯错误计数 */

/* LTU的自检信息 */
typedef struct
 {
	unsigned int    SS1[2];        /* 接收到的太敏1的自检数据 */
	unsigned int    SS2[2];        /* 接收到的太敏2的自检数据 */
	unsigned int    GyroAcce1[3];  /* 接收到的惯性单元1的自检数据 */
	unsigned int    GyroAcce2[3];  /* 接收到的惯性单元2的自检数据 */
	unsigned int    UV1[4];        /* 接收到的紫外1的自检数据 */
	unsigned int    UV2[4];        /* 接收到的紫外2的自检数据 */
	unsigned int    STS1[9];       /* 接收到的星敏1的自检数据 */
	unsigned int    STS2[9];       /* 接收到的星敏2的自检数据 */
	unsigned int    STS3[9];       /* 接收到的星敏3的自检数据 */
	unsigned int    BAPTAL1[2];    /* 接收到的太阳帆板1主份的自检数据 */
	unsigned int    BAPTAL2[2];    /* 接收到的太阳帆板1备份的自检数据 */
	unsigned int    BAPTAR1[2];    /* 接收到的太阳帆板2主份的自检数据 */
	unsigned int    BAPTAR2[2];    /* 接收到的太阳帆板2备份的自检数据 */
	unsigned int    GDA1[3];       /* 接收到的天线1的自检数据 */
	unsigned int    GDA2[3];       /* 接收到的天线2的自检数据 */
}LTUSelfCheck;
LTUSelfCheck   LTUCheck;


/* 动量轮数据 */
typedef struct
{
    float  H[4];                /* Hx,Hy,Hz,Hs */
    float  V[4];                /* Vx,Vy,Vz,Vs */
    float  Vh[4];               /* Vhx,Vhy,Vhz,Vhs */
    float  Vf[4];               /* Vfx,Vfy,Vfz,Vfs */
    float  Ih[4];               /* Ihx,Ihy,Ihz,Ihs */
    float  DeltaH[4];           /* ΔHx,ΔHy,ΔHz,ΔHs */
    float  I[3];                /* Iφ,Iθ,Iψ*/
    float  IStar[3];            /* Iφ*,Iθ*,Iψ* */
    float  K_IC[3][3];          /* K_ICx,K_ICy,K_ICz */
    float  K_PC[3][3];          /* K_PCx,K_PCy,K_PCz */
    float  K_DC[3][3];          /* K_DCx,K_DCy,K_DCz */
    float  Vc[3];               /* Vcx,Vcy,Vcz*/
    float  Cv;
    float  Kf[4];               /* 动量轮的动摩擦力矩系数 */
    float  Vf0[4];              /* Vf0>=0,表示动量轮静摩擦力矩相应的补偿电压 */
    float  Kfv[4];              /*  */
    float  VcStar[3];
    float  HT[3];
    float  J0[3][3];
    float  CwhXYZS[3][4];
    float  DwhXYZS[4][3];
	float  CwhXYZ[3][4];
    float  DwhXYZ[4][3];
	float  CwhXYS[3][4];
    float  DwhXYS[4][3];
	float  CwhXZS[3][4];
    float  DwhXZS[4][3];
	float  CwhYZS[3][4];
    float  DwhYZS[4][3];
    unsigned int StartInitFlg;  /* 轮子启动与保持计算中积分项清零标志 */
    unsigned int PIDInitFlg;    /* 轮子PID控制计算中积分项清零标志 */
/* 动量轮系数块 2 顺序固定 */
    float  C_UT;            /* 飞轮电压-力矩系数 */
    float  Tf;              /* 轮控滤波时间常数 */
    float  K_PH;            /* 飞轮角动量保持控制P参数 */
    float  K_IH;            /* 飞轮角动量保持控制I参数 */
    float  mDeltaH;         /* 飞轮喷气卸载阀值的修正因子 */
    float  H0[4];           /* Hx0,Hy0,Hz0,Hs0 */
}MWDATA;
MWDATA         MWData;


/* 轨控命令块，包括轨控各时间参数，推力器组态、储箱组态 */
typedef struct
{
    unsigned int Tgon;
    unsigned int Thon;
    unsigned int Tgi;           /* 轨控模式开始时刻 */
    unsigned int TFireon;       /* 轨控开机时刻 */
    float   Tprohoff;           /* 轨控开关机时间参数 */
    float   TFireoff;           /* 轨控开关机时间参数 */
    float   DeltaVs;            /* 剩余速度增量 */
    float   wGK[3];             /* 变轨系数  */
    float   PhiGK1;             /* 变轨系数 */
    float   PhiGK;              /* 变轨系数 */
	int 	DeltaV1;            /* 轨控速度增量 */
	int 	DeltaV2;            /* 轨控速度增量 */
    unsigned int St_offm;
    unsigned int Gmode;
    unsigned int Tsmode;
    float   Toff;               /*  */
    float   Tc;
}ORBITCOMMAND;
ORBITCOMMAND  OrbitCmd;

/* 相平面系数数据结构 */
typedef struct
{
    float   mThetaDL;       /* 相平面限速阀值修正因子 */
    float   mThetaD;        /* 相平面死区阀值修正因子 */
    float   mThetaV;        /* 相平面步进阀值修正因子 */
    float   mThetaDV;       /* 相平面步进区阀值修正因子 */
    float   mKJ2;           /* 相平面参数KJ2修正系数 */
}PHASE;
PHASE   InPhase;


/* 脉宽控制的数据结构 */
typedef struct
 {
    float   A11[3];           /*  */
    float   H1[3];            /*  */
    float   A32[3];           /*  */
    float   A33[3];           /*  */
    float   H2[3];            /*  */
    float   H3[3];            /*  */
    float   D2[3];            /*  */
    float   A54[3];           /*  */
    float   A55[3];           /*  */
    float   H4[3];            /*  */
    float   H5[3];            /*  */
    float   D3[3];            /*  */
    float   A76[3];           /*  */
    float   A77[3];           /*  */
    float   H6[3];            /*  */
    float   H7[3];            /*  */
    float   D4[3];            /*  */
    float   Kp[3];            /* 脉冲调宽控制P系数 */
    float   Kd[3];            /* 脉冲调宽控制I系数 */
    float   Ki[3];            /* 脉冲调宽控制D系数*/
    float   HH1[3];           /* 伪速率调制器控制参数 */
    float   HH2[3];           /* 伪速率调制器控制参数 */
    float   Tm[3];            /* 伪速率调制器控制参数 */
    float   X82[2];
    float   X83[2];
    float   X1[3];            /*  */
    float   X2[3];            /*  */
    float   X3[3];            /*  */
    float   X4[3];            /*  */
    float   X5[3];            /*  */
    float   X6[3];            /*  */
    float   X7[3];            /*  */
    float   X8[3];            /*  */
    float   PWI[3];
    float   Y[3];
}PULSEDATA;
PULSEDATA      PulseData;

/* 喷气开关相平面数据结构 */
typedef struct
 {
	float  Thetapst;           /* 上一周期该轴的姿态角 */
	float  ThetaD;             /* 常数 */
	float  ThetaV;             /* 常数 */
	float  DThetaL;          /* 常数 */
	float  DThetaLL;
	float  AlphaJS;         /* 常数 */
	float  DThetaV;          /* 常数 */
	float  KJ2;             /*  */
}PHASEPLANE;
PHASEPLANE     JPCPara; 		/* 喷气开关相平面数据结构 */

typedef union
{
    volatile unsigned int    Word;

    struct
    {
        volatile unsigned High       : 16;
        volatile unsigned GNC        : 5;        /* 0-4 远程终端地址 */
        volatile unsigned tr         : 1;        /* 5    发送/接收位 */
        volatile unsigned Address    : 5;        /* 6-10 子地址、方式 */
        volatile unsigned Number     : 5;        /* 11－15 数据字计数、方式代码 */
    } Bit;
}RCV_COMMAND;

/* 太阳数据 */
typedef struct
 {
    float        DSSAngle[2];          /* 数字太阳输出的姿态角αφ,αθ */
	float        DSSAngleOld[2];       /* 数字太阳输出的姿态角αφ,αθ */
	float        ASSAngle[5];          /* 模拟太阳输出的姿态角αA1,αA21,αA22,αA31,αA32*/
	float        ASSAngleOld[5];       /* 模拟太阳输出的姿态角αA1,αA21,αA22,αA31,αA32*/
    float        AlphaF[2];            /*  */
    float        AlphaFS;              /*  */
    float        SbMatrix[3][3];       /* 理论视场码估算 */
    float        Sb[3];                /* 太阳向量估值 */
    float        STheta[3];            /*  */
    float        SPsi[3];              /*  */
    unsigned int DSSDataValidFlg[2];   /* 数字太阳数据是否有效 */
    unsigned int ASSSightValidFlg[5];  /* 模拟太阳是否视场有效SA1,SA21+SA22,SA31+SA32 */
    unsigned int LSSSightValidFlg[6];  /* 0-1太阳信息L11+L15,L12+L14,L14+L22,L23+L25,L13,L21*/
    unsigned int IsThetea1;            /*  */
    unsigned int IsPsi1;               /*  */
    unsigned int IsThetea2;            /* 俯仰数字太阳输出视场码 */
    unsigned int IsPsi2;               /* 偏航数字太阳输出视场码 */
    unsigned int Ise;                  /*  */
    unsigned int SSValid;              /* 太阳可用性判断标志 */
	unsigned int Ls;
	unsigned int BAPTAZero[2];         /* 帆板在零位标志 */
}SSDATA;



/* 星敏数据 */
typedef struct
{
    float AB[3][3];
    float BB[3][3];
    float CB[3][3];
    float ZAI[3];
    float ZBI[3];
    float ZCI[3];
    float XAI[3];
    float XBI[3];
    float XCI[3];
    float DAB[3][3];
    float DBB[3][3];
    float DCB[3][3];
    float KSA[6][3];
    float KSB[6][3];
    float KSC[6][3];
    float DeltaZA[3];
    float DeltaZB[3];
    float DeltaZC[3];
    float DeltaZR[3]; 
    float DeltaZpst[3];                
}STSDATA;
STSDATA STS;


typedef union
{
    unsigned int    Word;
    float   Float;
    struct
    {
        unsigned High   : 16;           /* 高16位 */
        unsigned Low    : 16;           /* 低16位 */
    } Half;

    struct
    {
        unsigned High_h :8;             /* 高16位中的高8位 */
        unsigned High_l :8;             /* 高16位中的低8位 */
        unsigned Low_h  :8;             /* 低16位中的高8位 */
        unsigned Low_l  :8;             /* 低16位中的低8位 */
    } Byte;

    struct
    {
        unsigned BZ1    : 4;  /* 高0－3 */
        unsigned BZ2    : 4;  /* 高4－7 */
        unsigned BZ3    : 4;  /* 高8－11 */
        unsigned BZ4    : 4;  /* 高12－15 */
        unsigned BZ5    : 4;  /* 低0－3 */
        unsigned BZ6    : 4;  /* 低4－7 */
        unsigned BZ7    : 4;  /* 低8－11 */
        unsigned BZ8    : 4;  /* 低12－15 */
    } Bit4;
}USED_WORD;
USED_WORD   GNC_Data[150];    /* GNC数字量遥测数据缓冲区 */
USED_WORD   Task_GNCData[150];/* 从OBDH收到的上行数据块 */
USED_WORD   Task_Now[255];    /* 收到的上行数据块 */
USED_WORD   Task_GNCOrbitData[150];/* 从OBDH收到的上行轨道数据块 */
USED_WORD   SendAttiData[9];  /* 要发送的姿态数据 */

/*时间的数据结构*/
typedef struct
{
    unsigned int    MS;                 /* 星时的毫秒 */
    unsigned int    S;                  /* 星时的秒 */
    unsigned int    GPT_Old;            /* 从GPT读到的值Old */
    volatile unsigned int    GPT_Now;   /* 从GPT读到的值new */
    unsigned int    T;
    unsigned int    tec1;               /* 进阴影时刻 */
    float           Tec2;               /* 阴影时长 */
    float           Tec3;               /* 阴影周期 */
	int			    STS[3];             /* 星敏遥测时间 */
    unsigned int    STSflg;             /* 星敏时间需校时标志 */
    unsigned int    CorrectSTS;         /* 星敏校时时刻 */
    unsigned int    deltaMS;            /*  */   
    volatile unsigned int    MSInt;        /* 星时的毫秒 ,接收到的校时量*/
    volatile unsigned int    SInt;         /* 星时的秒 ,接收到的校时量 */ 
    volatile unsigned int    GPT_OldInt;   /* 从GPT读到的值Old ,接收校时量时的old值 */ 
} TIME;
TIME    Time;


/* 中断中使用的变量 */
volatile unsigned int    JetStatus;      /* 喷管当前状态 */
volatile unsigned int    GNCDataflg;     /* 收到上行注入数据标志 */
volatile unsigned int    TeleMode;       /* 遥测模式 */
volatile unsigned int    flgSetFire80;   /* 80s点火标志 */

unsigned int    ASSBadNum2122; 	        /* 控制周期计数 */
unsigned int    ASSBadNum3132; 	        /* 控制周期计数 */
        /* 巡航模式内模拟太阳错误计数 */
unsigned int    AttiBadNum;             /* 姿态超差计数器 */
unsigned int    AttiGoodNum;            /* 姿态好计数器 */
unsigned int    BBranchPowerOnFlg;
unsigned int    BBranchPowerOnNum;      /* 开B分支计数 */
unsigned int    BAPTATimeNum;
unsigned int    BOOT_490Nnum;           /* 关闭轨控发动机脉冲计数 */
unsigned int    CloseLV5Num;            /* 关闭LV5计数 */
unsigned int    CmdAddrOLD;
unsigned int    Cyc_Flag;               /* 控制周期 */
float           DeltaT;
float           DeltaTOld;
        /* 数字太阳错误计数 */
unsigned int    ErrorOBDHNum;           /* 4s与OBDH通讯故障计数 */
unsigned int    FaultFlg1;              /* 异常数据块1存放标志 */
unsigned int    FaultFlg2;              /* 异常数据块2存放标志 */
unsigned int    FaultNum1;              /* 异常数据块1存放计数 */
unsigned int    FaultNum2;              /* 异常数据块2存放计数 */
unsigned int    FailureFlag;            /* 运行段故障标志 */
unsigned int    flgAllTOEE;             /* 太阳定向模式中，通知整星进应急标志*/	
unsigned int    flgOrbitData;           /* 轨道数据块注入标志 */
unsigned int    flgOpenLV14Num;         /* 开LV1,4计数 */
unsigned int    flgCLoseValve;          /* 80秒排气后,关喷管标志 */
unsigned int    flgOpenLV14;            /* 开自锁阀1,4的标志 */
unsigned int    flgCloseLV5;            /* 关自锁阀5的标志 */
unsigned int	flgReceiveTime;         /* 接收到校时的标志 */
unsigned int    flgRequirData;          /* 申请重要数据恢复标志 */
unsigned int    flgSaveData;            /* 申请重要数据保存标志 */
unsigned int    flgProgramm;            /* 收到注入程序是否正确标志 */
unsigned int    GKFlag;
unsigned int 	GNCDataNumber;          /* 有效数据长度 */
unsigned int 	GNCDataSequenceSave;    /* 注入轨道数据出错块号 */
unsigned int    GDACtrlCmd[5];
unsigned int    GyroZT10;				/* 陀螺故障数据处理ZT10 */
unsigned int    GyroAcceTNum1;          /* 陀螺数据处理间隔周期数 */
unsigned int    GyroAcceTNum2;          /* 陀螺数据处理间隔周期数 */
int             GyroAcceTele1[8];
unsigned int    ImpDataRecErrorFlg;     /* 接收重要数据错误标志 */
unsigned int    ImpGNC2[16];            /* GNC重要数据2 */
unsigned int    ImpGNC3[16];            /* GNC重要数据3 */
unsigned int    ImpGNC4[16];            /* GNC重要数据4 */
float	        InparaGyro[6];          /* Gyro采集数据最小码当量 */
float	        InparaAcceK[2];         /* Acce采集数据最小码当量 */
unsigned int    JetBadNum[3]; 	        /* 各通道连续喷气计数 */
unsigned int    JetGoodFlg;
float           Kit[3];
unsigned int    LTUPowerStatusFlg;
unsigned int 	LTUSelfCheckNum;		/* LTU自检顺序计数 */
unsigned int    MannerData;             /* 方式代码标志 */
float           MatrixVG[6][3];
float           mkpLimit;               /* 脉宽调制比例项输入限幅值 */       
unsigned int    numEE;                  /* 应急加电计数>=5有效 */
unsigned int    numRequirData;          /* 申请重要数据计数 */
unsigned int    numWM4STS;              /* 星敏感器采集，在模式4中的计数 */
unsigned int    num80s;                 /* 80s点火计数 */
unsigned int    numAttiRate;            /* 缓冲区打包间隔4次的计数 */
unsigned int    numDeltaZ;              /* 连续2次大于0.017 */
unsigned int 	numFireOff;             /* 点火后的计时时间 */
float           numSTSTime;             /* 星敏30S校时计数 */
unsigned int 	NumZm00875[3];
unsigned int    numImpGNCData;          /* 重要数据定期保存计数 10s */
unsigned int	OldInOrbitPointer;      /* 注入轨道数据的存放指针 */
unsigned int	OldProgrammPointer;     /* 注入程序的存放指针 */
unsigned int 	ProgrammSequenceSave;   /* 注入程序出错块号 */
float           qBTabs;
unsigned int    RecInSlowRotateCommNum; /* 注入的慢旋指令计数 0.256s */
unsigned int 	Rec8252CommErrorFlg; 	/* LTU通讯8252错 */
unsigned int 	RecOverTimeErrorFlg; 	/* LTU通讯超时错 */
unsigned int    Switch_Cmd;             /* 与系统软件接口,切机命令字 */
unsigned int    SLSPFlg;                /* 星箭分离的标志 */
unsigned int    SDCOutputFlg;           /* 注入的SDC块是否被相应的标志 */
unsigned int    SDCOutput;              /* 注入的SDC块的内容 */
unsigned int    SHUT_490Nnum;           /* 关轨控发动机脉冲计数 */
unsigned int    SendTeleMode;           /* 方式字 */
unsigned int 	SDCOutputZZFlg;		    /* 自主判断出的需加电部件的标志 */
unsigned int 	Shut490PowerNum;	    /* 断开490N母线电源的计数 */

unsigned int    SmodeEQU5Lnum;
unsigned int    SmodeEQU5Rnum;
unsigned int    SLSPSignalNum;          /* 连续控制周期得到的分离计数 */
unsigned int    St_of[3];
unsigned int    STSDataValidFlg[3];	    /* 星敏数据有效标志 */
unsigned int    STSqFlag;	            /* 进入速率阻尼模式后，是否重新计算q初值的标志 */
unsigned int    *Task_TmpData;		    /* 从OBDH收到的上行数据块 */
unsigned int    *Task_ProgramData;	    /* 地面上行的程序注入区 */
unsigned int    *Task_FaultData1;	    /* 异常数据记录区1 */
unsigned int    *Task_FaultData2;	    /* 异常数据记录区2 */
unsigned int    *Task_FaultEndAddr1;	/* 异常数据记录区1结束地址 */
unsigned int    *Task_FaultEndAddr2;	/* 异常数据记录区2结束地址 */
float	        TeleAttiData[17][3];    /* 遥测姿态数据间隔一秒设置的缓冲区 */
unsigned int 	UV1DataValidFlg;	    /* 紫外1数据有效标志 */
unsigned int 	UV2DataValidFlg;	    /* 紫外2数据有效标志 */
unsigned int    UnloadMode;             /* 轮子卸载标志 */
unsigned int    ULS;                    /* 轮子卸载标志 */
unsigned int    WM4Cycle;               /* 轨控64ms内数周期计256ms  */
unsigned int    WMInertiaAttiCycleNum;  /* 惯性调姿模式计数器 600S */
unsigned int    WMCycleNum;
unsigned int    WMInitFlg;
extern unsigned int OSTM_Frame0;
extern unsigned int OSTM_Frame1;
extern unsigned int OSTM_Frame2;
extern unsigned int Task1024Flag;
unsigned int    ForInProgram1;
unsigned int    ForInProgram2;
unsigned int    ForInProgram3;
unsigned int    ForInProgram4;
unsigned int    ForInProgram5;
float		    ForInProgram6;
float		    ForInProgram7;
float		    ForInProgram8;
float		    ForInProgram9;
float		    ForInProgram10;
unsigned int    ForInProgramArray[30];
float		    ForInProgramArrayF[30];

	
void    CaptureSunSmode5(CaptureSSDATA*  CaptureSun,
		ATTITUDEDATA*   AttiData,
		INPara*  InPara,
		unsigned int    SmodeNE5num,
		SSDATA*         SSData,
		unsigned int    DSSErrorNum[2],
		unsigned int    ASSErrorNum[5])
{
	unsigned int i, tmpFlg=flg_invalid;
	float tmpDSSAngle[2], tmpASSAngle[5];

	if(CaptureSun==0) return;
	if(AttiData==0) return;
	if(InPara==0) return;
	if(SSData ==0) return ;

	if(CaptureSun->Smode == 5)
	{
		//if((fabs_s(AttiData->A[1]) > 0.0875f) || (fabs_s(AttiData->A[2]) > 0.0875f))
		if(( (AttiData->A[1]) > 0.0875f) || ( (AttiData->A[2]) > 0.0875f))
		{
			tmpFlg = flg_valid;
		}
		if((CaptureSun->TSmode <= 2) || ((CaptureSun->TSmode < 500) && (tmpFlg == flg_valid)))
		{
			for(i = 0; i < 3; i++)
			{
				AttiData->RateC0[i] = 0.0f;
			}
		}
		else
		{
			for(i = 0; i < 3; i++)
			{
				AttiData->RateC0[i] = InPara->WT[i];
			}
		}

		if(SmodeNE5num > 0)
		{
			SmodeNE5num--;
		}
		SmodeEQU5Lnum++;
		SmodeEQU5Rnum++;
		/* 对太阳敏感器的输出值进行剔野保护 */
		if(CaptureSun->TSmode == 0)
		{
			SSData->DSSAngleOld[0] = SSData->DSSAngle[0];
			SSData->DSSAngleOld[1] = SSData->DSSAngle[1];
			for(i = 0; i < 5; i++)
			{
				SSData->ASSAngleOld[i] = SSData->ASSAngle[i];
			}
		}			
			
		for(i = 0; i < 2; i++)
		{
			//tmpDSSAngle[i] = fabs_s(SSData->DSSAngle[i] - SSData->DSSAngleOld[i]);
			tmpDSSAngle[i] =  (SSData->DSSAngle[i] - SSData->DSSAngleOld[i]);
			if(tmpDSSAngle[i] > 0.01745329f) /* 1.0f/RAD_DEGREE */
			{
				DSSErrorNum[i]++;
				if(DSSErrorNum[i] < 5)
				{
					SSData->DSSAngle[i] = SSData->DSSAngleOld[i];
				}
			}
			else
			{
				DSSErrorNum[i] = 0;
			}
			SSData->DSSAngleOld[i] = SSData->DSSAngle[i];
		}

		for(i = 0; i < 5; i++)
		{
			//tmpASSAngle[i] = fabs_s(SSData->ASSAngle[i] - SSData->ASSAngleOld[i]);
			tmpASSAngle[i] =  (SSData->ASSAngle[i] - SSData->ASSAngleOld[i]);
			if(tmpASSAngle[i] > 0.05235988f) /* 3.0f/RAD_DEGREE */
			{
				ASSErrorNum[i]++;
				if(ASSErrorNum[i] < 5)
				{
					SSData->ASSAngle[i] = SSData->ASSAngleOld[i];
				}
			}
			else
			{
				ASSErrorNum[i]=0;
			}

			SSData->ASSAngleOld[i] = SSData->ASSAngle[i];
		}
	}
	else
	{
		SmodeEQU5Lnum = 0;
		SmodeEQU5Rnum = 0;
	}
	return;
}

void testme(){

	CaptureSSDATA*  CaptureSun;
	ATTITUDEDATA*   AttiData;
	INPara*  InPara;
	unsigned int    SmodeNE5num;
	SSDATA*         SSData;
	unsigned int    DSSErrorNum[2];
	unsigned int    ASSErrorNum[5];

	CAUT_INPUT(CaptureSun);
	CAUT_INPUT(AttiData);
	CAUT_INPUT(InPara);
	CAUT_INPUT(SmodeNE5num);
	CAUT_INPUT(SSData);
	CAUT_INPUT(DSSErrorNum);
	CAUT_INPUT(ASSErrorNum);
	
	CaptureSunSmode5(CaptureSun, AttiData, InPara, SmodeNE5num, SSData, DSSErrorNum, ASSErrorNum);
}
