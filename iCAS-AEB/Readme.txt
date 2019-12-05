Project: LEVDEO_YEMA_AUTO_ICAS_AEB
Author : Gao Zhengzhong
Date   : 2019.11.15
JWD Automotive Co., Ltd. 

LEVDEO_YEMA_AUTO_ICAS_AEB_MCU
git@github.com:gao-zhengzhong/iCAS-AEB.git

软件版本号规则：
<硬件版本号>.<主版本号>.<子版本号>.<修订版本号>.<日期>_版本阶段
例：HW01.1.1.00.20191115_alpha

版本号修改规则：
*主版本号  ：当功能模块有较大变动，例如增加多个模块或整体架构发生变化
*子版本号  ：当功能有一定的增加或变化，例如功能模块需求变更
*修订版本号：Bug修复或是一些小的变动

软件版本阶段说明：
*Alpha  ：此版本主要以实现软件功能为主，只在软件开发内部交流
*Beta   ：此版本无严重错误，但存在一些缺陷
*RC     ：此版本基本不存在导致错误的BUG
*Release：此版本为最终交付用户使用版本

2019.11.15
版本信息：
HW02.1.1.00.20191115_alpha
1.实现功能：
	1)增加故障诊断功能
	2)增加EEPROM存储功能
2.解决问题：
3.优化处理：
	1)优化助力制动算法
	2)优化ADC,PWM,CAN模块
4.存在问题：