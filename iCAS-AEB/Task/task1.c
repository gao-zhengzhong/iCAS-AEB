/*
 * Task1.c
 *
 *  Created on: 2019-3-5
 *      Author: Administrator
 */
#include"MAIN.h"
#include"iCasBrake.h"

/*
*********************************************************************************************************
*                                                MACROS
*********************************************************************************************************
*/

#define ReceivePC_ID           0x31       // ��λ����ʶ��
#define SendPC_ID0             0x21       // ���ͱ�ʶ��
#define SendPC_ID1             0x22       // ���ͱ�ʶ��
#define data_len_TX            8          // �������ݳ���
#define PWM_MAX   760
#define PWM_MIN   370
#define PRESSURE_MAX 1000                 // 200+80*10
#define PRESSURE_MIN 200                  // 200+80*0
#define INIT_PRESSURE 220
#define INTERRUPTTIME 50
// #define MotorDuty PWMDTY01

#define ABS(a) ((a)>0?(a):(-(a)))
#define SIGN(a) ((a)>0?1:((a)<0?-1:0))

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void task1(void);                        //������䣺�ϵ��Լ졢��������ģʽ���ϵ��⡢�ϵ�ģʽ������ģʽ
void task1PowerUpTest_v_s(void);         //�ϵ��Լ�
void task1Normal_v_s(void);              //��������ģʽ��AD����������ϵͳ����
void task1PowerDownTest_v_s(void);       //�ϵ���
void task1PowerDown_v_s(void);           //�ϵ�ģʽ
void task1Fault_v_s(void);               //����ģʽ

/*
*********************************************************************************************************
*                                             C ENTRY POINT
*********************************************************************************************************
*/
/*!************************************************************************************
*	@fn	        void task1(void)
*	@brief	         ����1����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��CCU60.c��CCU60_viNodeI2()�����е��ã��ú���ΪOSϵͳ������亯��
*	@Data       2019-3-12
****************************************************************************************/
void task1(void){

	   MCTimer++;
	   if(MCTimer>30000)
		   MCTimer = 0;

	   switch(SystemMode_u8_Sig)
		{
		case PowerUpTestMode:
			task1PowerUpTest_v_s();
		break;

		case NormalMode:
			task1Normal_v_s();
		break;

		case FaultMode:
			task1Fault_v_s();
		break;

		case PowerDownTestMode:
			task1PowerDownTest_v_s();
		break;

		case PowerDownMode:
			task1PowerDown_v_s();
		break;

		default:

		break;

		}


}
/*!************************************************************************************
*	@fn	        void task1PowerUpTest_v_s(void)
*	@brief	         ����1�ϵ���Ժ���
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task1PowerUpTest_v_s(void){

}

/*!************************************************************************************
*	@fn	        void task1Normal_v_s(void)
*	@brief	         ����1����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е��ã�����icas-brake�㷨���ڴ˺�����
*	@Data       2019-3-12
****************************************************************************************/
void task1Normal_v_s(void)                                 //AD��������������
{
	    /*---------------------��������--------------------*/
	     Motor_Cur_AD=SingleADSample_v_g(0,CUR_SAMPLE_ADC0);
		 /*---------------------ѹ������������--------------------*/
		 BrakePressure_AD=SingleADSample_v_g(1,BRAKE_PRESSURE_ADC1);
		 /*---------------------�����г̲���--------------------*/
		 ADC0_vStartSeq2ReqChNum(0,0,0,2); //�������
		 while(ADC0_uwBusy());
	     while(ADC1_uwBusy());
	     Mastercyler_AD1  = ADC0_uwGetResultData_RESULT_REG_1;
	     Mastercyler_AD2  = ADC1_uwGetResultData_RESULT_REG_1;

	     /*---------------------̤���г̲���--------------------*/
		 ADC0_vStartSeq2ReqChNum(0,0,0,0); //�������
		 while(ADC0_uwBusy());
	     while(ADC1_uwBusy());
	     Pedal_location_AD1  = ADC0_uwGetResultData_RESULT_REG_0;
	     Pedal_location_AD2  = ADC1_uwGetResultData_RESULT_REG_0;
	     /*--------------------�ƶ������źż�Ԥ��״̬�źŲ���-----------------*/
	     BrakeSW=BRAKE_SIGNEL;
	 	 PreDriverStatus=PRE_ERR_SIGNEL;
	 	/*--------------------AB���ѹ����-----------------*/
    	 AphasePwr_AD=SingleADSample_v_g(0,APHASE_BATT_SAMPLE_ADC0); //A���ѹ����
    	 BphasePwr_AD=SingleADSample_v_g(0,BPHASE_BATT_SAMPLE_ADC0); //B���ѹ����

    	 /*--------------------icas-brake�����㷨--------------------------*/
    	 AD_Filtration();    //AD��������
         AD_to_real();       //AD����ת����ʵ��ֵ

        // BrakeSysMode = APA_BrakeFlag;
     /*--------------------------̤���Ԥ���ж��߼�--------------------------*/
         APA_Count ++;
         if(APA_Count >80) {
        	 APA_BrakeFlag = 0;
        	 APA_TargetPrs = 0;
        	 BrakeSysMode = 0;
        	 APA_Count = 0;
         }

         if((Pedal_location_AD1 > (Pedal_Init_loc_AD + 30))&&(BrakeSysMode!=BoosterBrakeMode))
         {
        	 BrakeSysMode=BoosterBrakeMode;
        	 AebStandMode =0;
        	 AEB_State_now =0;
        	 TTC=20;
         }


         if(BrakeSysMode==BoosterBrakeMode)         //  ����ģʽ�ж�
         {
        	 MC_Location_PID();
         }

         else if(BrakeSysMode == APABrakeMode)       //  APAģʽ�ж�
         {
        	 APAFunction();
         }

         else if(BrakeSysMode==AebBrakeMode)        //  AEBģʽ�ж�
	     {
		    MC_Presure_PID(Aeb_targetpress_value);
	     }

         Real_To_Can();                             //   CAN��������

	 	 /*--------------------PWM��ֵ���ײ�ӿ�----------------------------*/
	 	 PWMA_u16_Sig=((INT32U)MotorPwm_Ctrl*2000)>>12;
		 if(PWMA_u16_Sig>1900)
		 {
		 		PWMA_u16_Sig=1900;
		 }
		 else if(PWMA_u16_Sig<100)
		 {
			 PWMA_u16_Sig=100;
		 }
		 else
		 {
		 }
	 	 PWMB_u16_Sig=2000-PWMA_u16_Sig;



}
/*!************************************************************************************
*	@fn	        void AD_SampleTest (void)
*	@brief	         ����1�µ�����������
*	@author     Matt Dou
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void AD_SampleTest(void){                                                //AD��������
	        Motor_Cur_AD=SingleADSample_v_g(0,CUR_SAMPLE_ADC0);             //�����������

	        BrakePressure_AD=SingleADSample_v_g(1,BRAKE_PRESSURE_ADC1);  //����ѹ������

	        ADC0_vStartSeq2ReqChNum(0,0,0,2); //�������
	          while(ADC0_uwBusy());
	          while(ADC1_uwBusy());
	        Mastercyler_AD1  = ADC0_uwGetResultData_RESULT_REG_1;        //�����г�1����
	        Mastercyler_AD2  = ADC1_uwGetResultData_RESULT_REG_1;        //�����г�2����

	        ADC0_vStartSeq2ReqChNum(0,0,0,0); //�������
	          while(ADC0_uwBusy());
	          while(ADC1_uwBusy());
	        Pedal_location_AD1  = ADC0_uwGetResultData_RESULT_REG_0;     //̤���г�1����
	        Pedal_location_AD2  = ADC1_uwGetResultData_RESULT_REG_0;     //̤���г�2����

	        BrakeSW=BRAKE_SIGNEL;                                        //�ƶ��ź�
	        PreDriverStatus=PRE_ERR_SIGNEL;

	        AphasePwr_AD=SingleADSample_v_g(0,APHASE_BATT_SAMPLE_ADC0); //A���ѹ����
	        BphasePwr_AD=SingleADSample_v_g(0,BPHASE_BATT_SAMPLE_ADC0); //B���ѹ����
}

/*!************************************************************************************
*	@fn	        void task1PowerDownTest_v_s(void)
*	@brief	         ����1�µ����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task1PowerDownTest_v_s(void){

}
/*!************************************************************************************
*	@fn	        void task1PowerDown_v_s(void)
*	@brief	         ����1�µ�ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task1PowerDown_v_s(void){

}
/*!************************************************************************************
*	@fn	        void task1Fault_v_s(void)
*	@brief	         ����1����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task1Fault_v_s(void)
{

}
