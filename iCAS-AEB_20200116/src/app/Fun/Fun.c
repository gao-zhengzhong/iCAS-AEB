/*
 * Fun.c
 *
 *  Created on: 2019-3-8
 *      Author: Administrator
 */

#define   FUN_GLOBALS
#include "MAIN.h"
/*
*********************************************************************************************************
*                                                MACROS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
FP32 TempADTab[50] =
{1002.5793, 987.5587, 964.3300, 930.5421, 884.4136, 856.3534, 824.9348, 790.2895, 752.7188, 712.6531,
670.7021, 627.5324, 583.8639, 540.4084, 497.8097, 456.6134, 417.2502, 380.0265, 345.1465, 312.7312,
282.8052, 255.3540, 230.3063, 207.5516, 186.9913, 183.1306, 179.3513, 175.6530, 172.0337, 168.4915,
165.0270, 161.6379, 158.3247, 155.0832, 151.9153, 148.8197, 145.7935, 142.8366, 139.9474, 137.1258,
134.3701, 131.6782, 129.0516, 126.4864, 123.9822, 121.5402, 119.1564, 116.8317, 114.5638, 112.3519 };

INT8U TempValueTab[50] =
{-40,-30,-20,-10,0,5,10,15,20,25,
30,35,40,45,50,55,60,65,70,75,
80,85,90,95,100,101,102,103,104,105,
106,107,108,109,110,111,112,113,114,115,
116,117,118,119,120,121,122,123,124,125};

//温度检测
INT8S RealTempreture=0;
INT8U temploc=0;
INT8U TempDiagNum=0;
INT8U TempDiagflag=0;
INT8U TempPtottIndex=100;
INT8U TempProttNum=0;

/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
/*!************************************************************************************
*	@fn	        INT8U IGStatus_v_g(void)
*	@brief	    IG信号获取函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    IG_ON代表状态IG为On;IG_OFF代表状态IG为Off
*	@note       在Task4.c的Task4()函数中调用
*	@Data       2019-3-12
****************************************************************************************/

INT8U IGStatus_v_g(void)
{
	static INT8U IgOffCntTime=0;
	static INT8U IgOnCntTime=0;
	IgStatus=IG_STATUS;//获取IG状态

	if(IgStatus==0)//IG信号判断
	{
		    IgOnCntTime=0;
		    IgOffCntTime++;//关闭IG时间累加计数
			if(IgOffCntTime>=IG_OFF_DURATION)//时间判断
			{

				IgOffCntTime=IG_OFF_DURATION;
				return IG_OFF;//返回状态IG OFF
			}
	}
	else
	{
		IgOffCntTime=0;
		IgOnCntTime++;//打开IG时间累加计数
		if(IgOnCntTime>=IG_ON_DURATION)//时间判断
		{

			IgOffCntTime=IG_ON_DURATION;
			return IG_ON;//返回状态IG ON
		}
	}

	return IG_ON;
}
/*!************************************************************************************
*	@fn	        void TimingStart_v_g(void)
*	@brief	           时序有关定时器初始化
*	@author     ZhangGuangYao
*	@param[in]	void
*	@return	    void
*	@note       在Task3.c的task3PowerUpTest_v_s()函数中调用
*	@Data       2019-3-12
****************************************************************************************/

INT8U Driver_v_g(void)
{
	static INT8U DelayT;
	PREDRIVER_ENABLE_OFF;//预驱使能关闭
	DelayT++;//延时计数
	if(DelayT==PREDRIVER_ON_DELAYTIME)//预驱延时40个周期，一个周期2ms
	{
	PREDRIVER_ENABLE_ON; //预驱使能打开
	DelayT=0;            //计数清0
	return 1;
	}
	return 0;
}

/*!************************************************************************************
*	@fn	        void FineTab(void)  二分查找算法 ->查温度表
*	@brief	           查找数据在表中对应的位置 表中数据从大到小
*	@author     Deng
*	@param[in]	表地址、表长度、要查找的数据
*	@return	           数据在表中的位置
*	@note       在  FaultDiag.c 的  Account_temp(INT16U data) 函数中调用
*	@Data       2019-9-6
****************************************************************************************/

INT8U FineTab(FP32 *a, INT8U TabLong, INT16U data)//表中数据从大到小
{
	INT8U st, ed, m=0;
	INT8U i;

    st = 0;
    ed = TabLong - 1;
    i = 0;

    if (data >= a[st]) return st;
    else if (data <= a[ed]) return ed;

    while (st < ed)
    {
        m = (st + ed) / 2;

        if (data == a[m]) break;
        if (data < a[m] && data > a[m + 1]) break;

        if (data > a[m]) ed = m;
        else st = m;

        if (i++ > TabLong) break;
    }

    if (st > ed) return 0;

    return m;
}

/*!************************************************************************************
*	@fn	        void Account_temp(void)
*	@brief	           计算温度
*	@author     DENG
*	@param[in]	温度采样值
*	@return	           实际温度
*	@note       在Task3.c的task3Normal_v_s()函数中调用
*	@Data       2019-9-6
****************************************************************************************/

INT8S Account_temp(INT16U data)
{
	FP32 temp;
	temp=0;

    temploc = FineTab(TempADTab, 50, data);

    temp = (TempADTab[temploc] - data) / \
    		(TempADTab[temploc] - TempADTab[temploc + 1]) * \
    		(TempValueTab[temploc + 1] - TempValueTab[temploc]) + \
    		TempValueTab[temploc];

    return (INT8S)temp;
}
