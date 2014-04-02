#include "caut.h"


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
ATTITUDEDATA   AttiData;

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
GYRODATA*       GyroData;

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



void    CaptureSunEclipse(TIME* Time,ATTI* Atti,SSDATA* SSData,CaptureSSDATA* CaptureSun,unsigned int SmodeNE5num,
	GYRODATA* GyroData,INPara* InPara)
{
        
	unsigned int i;
	float tmpSqrtSumDW=0, tmpSub, tmpT;

	if( Time==0 )
		return;
	if( Atti==0 )
		return;
	if( SSData==0)
		return;
	if(CaptureSun ==0 )
		return;
	if(GyroData ==0)
		return;
	if(InPara ==0 )
		return;
	
	
	tmpT = ((float)(Time->T-Time->tec1)) / 8.0f;
	int c;
	float result;

	c = (int)(tmpT/Time->Tec3);
	
	if(tmpT < 0)
	{
	   result = result + Time->Tec3;
	}
	else 
	result = tmpT - c * Time->Tec3;
   	 
  
	
	if(((Atti->BZ12 == 0)||(Atti->BZ12 == 1)||(Atti->BZ12 == 2)||(Atti->BZ12 == 4)||(Atti->BZ12 == 5))
     &&(SSData->Ls != 0))
	{
		CaptureSun->Eclipse = 0;
		SmodeNE5num ++;/* 阳照区累计30分钟不为巡航子模式的故障的计数器。当子模式=5时，清0 */
	}
	
	//else if(Time.Tec2 < fmod_s(tmpT, Time.Tec3))
	else if(Time->Tec2 < result)
	{
		CaptureSun->Eclipse = 0;
		SmodeNE5num ++;/* 阳照区累计30分钟不为巡航子模式的故障的计数器。当子模式=5时，清0 */
	}
	else
	{
		CaptureSun->Eclipse = 1;
		CaptureSun->Smode = 6;
	}

	for(i = 0; i < 3; i++)
	{
		tmpSub = GyroData->xw[i] -InPara->WT[i];
		tmpSqrtSumDW += tmpSub * tmpSub;
	}
	//CaptureSun.SqrtSumDW = sqrt_s(tmpSqrtSumDW);
        CaptureSun->SqrtSumDW =  tmpSqrtSumDW;
	return;
}
void testme(){

	TIME*    Time;
	ATTI*    Atti;
	SSDATA*         SSData;
	CaptureSSDATA*  CaptureSun;
	unsigned int    SmodeNE5num;
	GYRODATA*       GyroData;
	INPara*  InPara;
	
	CAUT_INPUT( Time);
	CAUT_INPUT(Atti);
	CAUT_INPUT(SSData);
	CAUT_INPUT(CaptureSun);
	CAUT_INPUT(SmodeNE5num);
	CAUT_INPUT(GyroData);
	CAUT_INPUT(InPara);


	CaptureSunEclipse(Time,Atti,SSData,CaptureSun,SmodeNE5num,
	GyroData,InPara);
}
