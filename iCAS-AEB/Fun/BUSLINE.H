/*
 * Bus_Line.h
 *
 *  Created on: 2015-5-21
 *      Author: zhangguangyao
 *  CAN0接控制CAN，获取毫米波雷达、MB摄像头数据，控制器从CAN0对外发调试数据
 *  CAN1接  整车KAN，获取车速和方向盘转角信息
 */

#ifndef BUS_LINE_H_
#define BUS_LINE_H_

#ifdef   BUS_LINE_GLOBALS
	#define  BUS_LINE_EXT
#else
	#define  BUS_LINE_EXT  extern
#endif


/*CAN0接控制CAN，获取毫米波雷达、MB摄像头数据，控制器从CAN0对外发调试数据
  CAN1接  整车KAN，获取车速和方向盘转角信息*/
/*-------------------------------CAN0 接受ID地址--------------------------------*/
#define REC_CAN0ID_0   0x118  //整车制动踏板状态ID    CAN0 Receive CANID 11Bit  Can0Rec0data[0][0]-Can0Rec0data[0][7]
#define REC_CAN0ID_1   0x126  //毫米波雷达ID    CAN0 Receive CANID 11Bit  Can0Rec0data[1][0]-Can0Rec0data[1][7]
#define REC_CAN0ID_2   0x130  //CAN0 Receive CANID 11Bit  Can0Rec0data[2][0]-Can0Rec0data[2][7]
#define REC_CAN0ID_3   3      //CAN0 Receive CANID 11Bit  Can0Rec0data[3][0]-Can0Rec0data[3][7]
#define REC_CAN0ID_4   4      //CAN0 Receive CANID 11Bit  Can0Rec0data[4][0]-Can0Rec0data[4][7]
#define REC_CAN0ID_5   0x16E  //MB摄像头ID     CAN0 Receive CANID 11Bit  Can0Rec0data[5][0]-Can0Rec0data[5][7]
#define REC_CAN0ID_6   0x119  //MB摄像头ID     CAN0 Receive CANID 11Bit  Can0Rec0data[6][0]-Can0Rec0data[6][7]
#define REC_CAN0ID_7   0x70      //MB摄像头ID     CAN0 Receive CANID 11Bit  Can0Rec0data[7][0]-Can0Rec0data[7][7]
#define REC_CAN0ID_8   0x279  //APA制动请求
#define REC_CAN0ID_9   0x278  //MB摄像头ID
#define REC_CAN0ID_10  10     //MB摄像头ID
#define REC_CAN0ID_11  11     //MB摄像头ID
#define REC_CAN0ID_12  12     //MB摄像头ID
#define REC_CAN0ID_13  13
#define REC_CAN0ID_14  13
#define REC_CAN0ID_15  15
#define REC_CAN0ID_16  16
#define REC_CAN0ID_17  17
#define REC_CAN0ID_18  18
#define REC_CAN0ID_19  19
#define REC_CAN0ID_20  20
#define REC_CAN0ID_21  21
#define REC_CAN0ID_22  22
#define REC_CAN0ID_23  23
#define REC_CAN0ID_24  24
#define REC_CAN0ID_25  25
#define REC_CAN0ID_26  26
#define REC_CAN0ID_27  27
#define REC_CAN0ID_28  28
#define REC_CAN0ID_29  29
#define REC_CAN0ID_30  30
#define REC_CAN0ID_31  31
#define REC_CAN0ID_32  32
#define REC_CAN0ID_33  33
#define REC_CAN0ID_34  34
#define REC_CAN0ID_35  35
#define REC_CAN0ID_36  36
#define REC_CAN0ID_37  37
#define REC_CAN0ID_38  38
#define REC_CAN0ID_39  39
#define REC_CAN0ID_40  40
#define REC_CAN0ID_41  41
#define REC_CAN0ID_42  42
#define REC_CAN0ID_43  43
#define REC_CAN0ID_44  44
#define REC_CAN0ID_45  45
#define REC_CAN0ID_46  46
#define REC_CAN0ID_47  47
#define REC_CAN0ID_48  48
#define REC_CAN0ID_49  49
#define REC_CAN0ID_50  50
#define REC_CAN0ID_51  51
#define REC_CAN0ID_52  52
#define REC_CAN0ID_53  53
#define REC_CAN0ID_54  54
#define REC_CAN0ID_55  55
#define REC_CAN0ID_56  56
#define REC_CAN0ID_57  57
#define REC_CAN0ID_58  58
#define REC_CAN0ID_59  59
#define REC_CAN0ID_60  60
#define REC_CAN0ID_61  61
#define REC_CAN0ID_62  62
#define REC_CAN0ID_63  63
#define REC_CAN0ID_64  64

/*-------------------------------CAN1 接受ID地址--------------------------------*/
#define REC_CAN1ID_0   0x1E5 //方向盘转角ID  CAN1 Receive CANID 11Bit  Can1Recdata[0][0]-Can1Recdata[0][7]
#define REC_CAN1ID_1   0x348 //车速ID      CAN1 Receive CANID 11Bit  Can1Recdata[1][0]-Can1Recdata[1][7]
#define REC_CAN1ID_2   2     //           CAN1 Receive CANID 11Bit  Can1Recdata[2][0]-Can1Recdata[2][7]
#define REC_CAN1ID_3   3     //           CAN1 Receive CANID 11Bit  Can1Recdata[3][0]-Can1Recdata[3][7]
#define REC_CAN1ID_4   4     //线控制动ID    CAN1 Receive CANID 11Bit  Can1Recdata[4][0]-Can1Recdata[4][7]
#define REC_CAN1ID_5   6  //CAN1 Receive CANID 11Bit  Can1Recdata[5][0]-Can1Recdata[5][7]
#define REC_CAN1ID_6   7  //CAN1 Receive CANID 11Bit  Can1Recdata[6][0]-Can1Recdata[6][7]
#define REC_CAN1ID_7   8  //CAN1 Receive CANID 11Bit  Can1Recdata[7][0]-Can1Recdata[7][7]
#define REC_CAN1ID_8   9  //CAN1 Receive CANID 11Bit  Can1Recdata[8][0]-Can1Recdata[8][7]
#define REC_CAN1ID_9   10 //CAN1 Receive CANID 11Bit  Can1Recdata[9][0]-Can1Recdata[9][7]

/*-------------------------------CAN0 发送ID地址--------------------------------*/
#define TRS_CAN0ID_0   0   //CAN1 MessageObject4 CANID 11Bit  Can1Revdata[0][0]-Can1Revdata[0][7]
#define TRS_CAN0ID_1   0x16C   //CAN1 MessageObject5 CANID 11Bit  Can1Revdata[1][0]-Can1Revdata[1][7]
//#define TRS_CAN0ID_1   0x94   //CAN1 MessageObject5 CANID 11Bit  Can1Revdata[1][0]-Can1Revdata[1][7]
//#define TRS_CAN0ID_2   0x95   //CAN1 MessageObject6 CANID 11Bit  Can1Revdata[2][0]-Can1Revdata[2][7]
#define TRS_CAN0ID_2   0x16A   //CAN1 MessageObject6 CANID 11Bit  Can1Revdata[2][0]-Can1Revdata[2][7]
//#define TRS_CAN0ID_3   0x96   //CAN1 MessageObject7 CANID 11Bit  Can1Revdata[3][0]-Can1Revdata[3][7]
#define TRS_CAN0ID_3   0x16F   //CAN1 MessageObject7 CANID 11Bit  Can1Revdata[3][0]-Can1Revdata[3][7]
//#define TRS_CAN0ID_4   0x97   //CAN1 MessageObject8 CANID 11Bit  Rev
//#define TRS_CAN0ID_5   0x16A   //CAN1 MessageObject9 CANID 11Bit  Rev

/*-------------------------------CAN1 发送ID地址--------------------------------*/
#define TRS_CAN1ID_0   0   //CAN1 MessageObject10 CANID 11Bit  Can1Revdata[0][0]-Can1Revdata[0][7]
#define TRS_CAN1ID_1   0   //CAN1 MessageObject11 CANID 11Bit  Can1Revdata[1][0]-Can1Revdata[1][7]
#define TRS_CAN1ID_2   0   //CAN1 MessageObject12 CANID 11Bit  Can1Revdata[2][0]-Can1Revdata[2][7]
#define TRS_CAN1ID_3   0   //CAN1 MessageObject13 CANID 11Bit  Can1Revdata[3][0]-Can1Revdata[3][7]
#define TRS_CAN1ID_4   0   //CAN1 MessageObject14 CANID 11Bit  Rev
#define TRS_CAN1ID_5   0   //CAN1 MessageObject15 CANID 11Bit  Rev



#define CAN0TRS0_ENABLE  0 //使能TRS_CAN0ID_0报文发送   1enable 0disable
#define CAN0TRS1_ENABLE  1 //使能TRS_CAN0ID_1报文发送   1enable 0disable
#define CAN0TRS2_ENABLE  1 //使能TRS_CAN0ID_2报文发送   1enable 0disable
#define CAN0TRS3_ENABLE  1 //使能TRS_CAN0ID_3报文发送   1enable 0disable
#define CAN0TRS4_ENABLE  0 //使能TRS_CAN0ID_4报文发送   1enable 0disable
#define CAN0TRS5_ENABLE  0 //使能TRS_CAN0ID_5报文发送   1enable 0disable

#define CAN1TRS0_ENABLE  0 //使能TRS_CAN1ID_0报文发送   1enable 0disable
#define CAN1TRS1_ENABLE  0 //使能TRS_CAN1ID_1报文发送   1enable 0disable
#define CAN1TRS2_ENABLE  0 //使能TRS_CAN1ID_2报文发送   1enable 0disable
#define CAN1TRS3_ENABLE  0 //使能TRS_CAN1ID_3报文发送   1enable 0disable
#define CAN1TRS4_ENABLE  0 //使能TRS_CAN1ID_4报文发送   1enable 0disable
#define CAN1TRS5_ENABLE  0 //使能TRS_CAN1ID_5报文发送   1enable 0disable


#define RIGHTMSG  0x0FF0

#define CAN0ID_NUM  64 //CAN0接收ID数量，根据接收的ID个数进行修改
#define CAN1ID_NUM  10 //CAN1接收ID数量，根据接收的ID个数进行修改


BUS_LINE_EXT INT16U    CAN0ID_u16_Sig; //CAN0 接收ID变量
BUS_LINE_EXT INT16U    CAN1ID_u16_Sig; //CAN1 接收ID变量
BUS_LINE_EXT INT16U    Can0ID_u16a64_Sig[64];//CAN0 接收ID数组，用于存放64个CANID；如ID增加了需要修改此数值大小
BUS_LINE_EXT INT16U    Can1ID_u16a10_Sig[10];//CAN1 接收ID数组，用于存放10个CANID；如ID增加了需要修改此数值大小

/*************************************************************/
/*                         CAN发送参数定义                   */
/*************************************************************/
BUS_LINE_EXT INT16S PedalLocation_CAN;       //踏板行程值
BUS_LINE_EXT INT16S PedalForce_CAN;          //踏板力值
BUS_LINE_EXT INT16S Set_Cylinder_CAN;        //主缸推杆行程
BUS_LINE_EXT INT16S CylinderLocation_CAN;    //主缸推杆行程
BUS_LINE_EXT INT16S MasterCylinderPrs_CAN;   //主缸压力
BUS_LINE_EXT INT16S MotorCurrent_CAN;        //电机电流
BUS_LINE_EXT INT16S Tempreture_CAN;          //温度
BUS_LINE_EXT INT16S SetPrs_CAN;              //目标压力
BUS_LINE_EXT INT16S PedalSpeed_CAN;          //踏板推杆速度
BUS_LINE_EXT INT16S PedalSpeedFlag_CAN;      //踏板推杆速度符号位
BUS_LINE_EXT INT16S Set_Current_CAN;         //目标电流
BUS_LINE_EXT INT16S motorDuty_CAN;           //占空比
BUS_LINE_EXT INT16S m_iPWMP_CAN;             //比例项
BUS_LINE_EXT INT16S m_iPWMI_CAN;             //积分项
BUS_LINE_EXT INT16S m_iPWMD_CAN;             //微分项
BUS_LINE_EXT INT16S MCTimer;                 //芯片时间
BUS_LINE_EXT INT16S feedBackCurrent_CAN;
BUS_LINE_EXT INT16S ExCurrent_CAN;
BUS_LINE_EXT INT16S FrcCylinder_CAN;
BUS_LINE_EXT INT16S CarMotorCurrent_CAN;
BUS_LINE_EXT INT16S Current_AD_CAN;
BUS_LINE_EXT INT16S m_iPWMP_CAN_POS;             //比例项
BUS_LINE_EXT INT16S m_iPWMI_CAN_POS;             //积分项
BUS_LINE_EXT INT16S m_iPWMD_CAN_POS;             //微分项
BUS_LINE_EXT INT16S m_iPWMD_CAN_POS;
BUS_LINE_EXT INT16S m_iPWMD_CAN_CreCurrent;
BUS_LINE_EXT INT16S SetCurrent_CAN;             //位置标定的目标电流曲线
BUS_LINE_EXT INT16S TargetCurrent_CAN;
BUS_LINE_EXT INT16S Receive_ACC;
BUS_LINE_EXT INT16S Tx_ACC;



/*-----------制动能量回收----------*/
BUS_LINE_EXT INT16S VCU_BrkPdlSts;           //踏板制动状态
BUS_LINE_EXT INT16S VCU_MotToqReq;           //动力电机制动请求
BUS_LINE_EXT INT16S VCU_VehOperatingMd;      //车辆能量模式01纯点  02混动  03燃油
BUS_LINE_EXT INT16S MCU_MotActuToq;          //电机当前制动扭矩
BUS_LINE_EXT INT16S MCU_MotToqLmt;           //电机允许最大扭矩（为负值）
BUS_LINE_EXT INT16S VCU_VehicleSpeed;        //整车车速信息
BUS_LINE_EXT INT16S MCU_MotActuSpd;          //
BUS_LINE_EXT INT8U VCU_AllowFeedbackFlag;   //允许回收状态位
BUS_LINE_EXT INT8U iCAS_BrakeFlagBit;       //刹车状态位
BUS_LINE_EXT INT8U iCAS_MotorState;         //电机状态位
BUS_LINE_EXT INT8U iCAS_BrakeFault_Level;   //制动故障等级
BUS_LINE_EXT INT8U APA_BrakeFlag;           //自主泊车请求标志位
BUS_LINE_EXT INT8U APA_FeedBackFlag;        //自主泊车返回标志位
BUS_LINE_EXT INT8U APA_FeedBackValue;       //自主泊车返回值
BUS_LINE_EXT INT8U APA_TargetPrs;           //自主泊车压力请求
BUS_LINE_EXT INT8U APA_EmgBrakeFlag;        //APA_紧急制动标志
BUS_LINE_EXT INT16U APA_Count;


BUS_LINE_EXT INT16S Test_toqRequest;
BUS_LINE_EXT FP32 Test_fricbrakeCylinder;
BUS_LINE_EXT FP32 Test_target_Cylinder;
BUS_LINE_EXT INT16S Test_BrakeToqRequest;
BUS_LINE_EXT INT16S BrakeState_CAN;
BUS_LINE_EXT INT16S Test_cof_CAN;
BUS_LINE_EXT INT16S Test_u_CAN;
BUS_LINE_EXT INT16S Test_BrakeCount_CAN;



BUS_LINE_EXT void    CanSendMsg_v_g(INT8U ubObjNr, INT8U *ubpubData,INT8U Len); //CAN 发送函数
BUS_LINE_EXT INT8U   CanRecMsg_v_g (INT8U ubObjNr, INT8U *ubpubData,INT8U *Len);//CAN 查询接收 函数
BUS_LINE_EXT void    Can0RecDeal_v_g(INT16U CanId);//CAN0 接收数据处理 函数
BUS_LINE_EXT void    Can1RecDeal_v_g();//CAN1 接收数据处理 函数
BUS_LINE_EXT void    CanEnbale_v_g(void);//CAN Transfer 使能函数
BUS_LINE_EXT void    CanTx_v_g(void);//CAN0及CAN1发送函数

#endif /* BUS_LINE_H_ */
