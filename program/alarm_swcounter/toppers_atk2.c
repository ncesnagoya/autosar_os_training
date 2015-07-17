/*
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2013 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2013 by FUJISOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2013 by FUJITSU VLSI LIMITED, JAPAN
 *  Copyright (C) 2011-2013 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2013 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2013 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2013 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2013 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2004-2013 by Witz Corporation, JAPAN
 *
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 *
 *  $Id: toppers_atk2.c 919 2014-01-09 11:19:14Z fsi-asanoto $
 */

#include "Os.h"
#include "t_syslog.h"
#include "t_stdlib.h"
#include "sysmod/serial.h"
#include "sysmod/syslog.h"
#include "toppers_atk2.h"

#include "sysmod/banner.h"
#include "target_sysmod.h"
#include "target_serial.h"

#include "device.h"

/*
 *  �����ؿ��ץ�ȥ��������
 */
sint32 main(void);

TASK(main_task);
TASK(hpri_task);
TASK(event_task);
ALARMCALLBACK(func_alarm_callback);

TickType sw_cnt_val = 0;

/*
 *  �桼���ᥤ��ؿ�
 *
 *  ���ץꥱ�������⡼�ɤ�Ƚ�Ǥȡ������ͥ뵯ư
 */
sint32
main(void){
	/*
	 *  �����ͥ뵯ư
	 */
	StartOS(AppMode1);

	while(1){
	}
}   /* main */


/*
 *  �������ȥ��åץեå��롼����
 */
#ifdef CFG_USE_STARTUPHOOK
void
StartupHook(void){
	/* �����ƥ����ǽ�ν���� */
	syslog_initialize();

	/* ���Ϥ��������ν��������� */
	syslog_msk_log(LOG_UPTO(LOG_INFO));

	/* ���ꥢ��IO�⥸�塼���������� */
	InitSerial();

	/* �����ͥ뵯ư��å������ν��� */
	print_banner();

	/* PSW����� */
	switch_push_init();

	/* DSW����� */
	switch_dip_init();
}   /* StartupHook */
#endif /* CFG_USE_STARTUPHOOK */


/*
 * main_task
 */
TASK(main_task){
	uint8 dsw_state;
	uint8 pre_dsw_state = 0;

	syslog(LOG_INFO, "main_task Start!");

	for(;;) {
		/* DSW���ּ��� */
		dsw_state = switch_dip_sense();

		/* DSW����Ƚ�� */
		if(((dsw_state & DSW1) == DSW1) && ((pre_dsw_state & DSW1) != DSW1)){
			syslog(LOG_INFO, "main_task : SetRelAlarm(alarm_callback, 10, 0).");
			SetRelAlarm(alarm_callback, 10, 0);
		}

		if(((dsw_state & DSW1) != DSW1) && ((pre_dsw_state & DSW1) == DSW1)){
			syslog(LOG_INFO, "main_task : CancelAlarm(alarm_callback).");
			CancelAlarm(alarm_callback);
		}

		if(((dsw_state & DSW2) == DSW2) && ((pre_dsw_state & DSW2) != DSW2)){
			syslog(LOG_INFO, "main_task : SetRelAlarm(alarm_callback, 10, 10).");
			SetRelAlarm(alarm_callback, 10, 10);
		}

		if(((dsw_state & DSW2) != DSW2) && ((pre_dsw_state & DSW2) == DSW2)){
			syslog(LOG_INFO, "main_task : CancelAlarm().");
			CancelAlarm(alarm_callback);
		}

		if(((dsw_state & DSW3) == DSW3) && ((pre_dsw_state & DSW3) != DSW3)){
			syslog(LOG_INFO, "main_task : SetRelAlarm(alarm_event, 5, 5).");
			SetRelAlarm(alarm_event, 5, 5);
		}

		if(((dsw_state & DSW3) != DSW3) && ((pre_dsw_state & DSW3) == DSW3)){
			syslog(LOG_INFO, "main_task : CancelAlarm(alarm_event).");
			CancelAlarm(alarm_event);
		}

		if(((dsw_state & DSW4) == DSW4) && ((pre_dsw_state & DSW4) != DSW4)){
			syslog(LOG_INFO, "main_task : SetRelAlarm(alarm_act_task, 2, 2).");
			SetRelAlarm(alarm_act_task, 2, 2);
		}

		if(((dsw_state & DSW4) != DSW4) && ((pre_dsw_state & DSW4) == DSW4)){
			syslog(LOG_INFO, "main_task : CancelAlarm(alarm_act_task).");
			CancelAlarm(alarm_act_task);
		}

		pre_dsw_state = dsw_state;
	}
}	/* TASK( main_task ) */


/*
 * hpri_task(��ͥ���٥�����)
 */
TASK(hpri_task){
	syslog(LOG_INFO, "hpri_task Start!");
	syslog(LOG_INFO, "hpri_task End!");

	TerminateTask();
}	/* TASK( hpri_task ) */


/*
 * event_task(���٥���Ԥ�������)
 */
TASK(event_task){
	syslog(LOG_INFO, "event_task Start!");

	for(;;){
		WaitEvent(EVENT_WUP);
		syslog(LOG_INFO, "event_task : Wake Up!!");
		ClearEvent(EVENT_WUP);
	}

	TerminateTask();
}	/* TASK( event_task ) */


/*
 * ���顼�ॳ����Хå��ؿ�
 */
ALARMCALLBACK(func_alarm_callback){
	syslog(LOG_INFO, "func_alarm_callback() : called!");
}


/*
 * PSW1�����(ISR2)
 */
ISR(psw1_int){
	IncrementCounter(SW_Cnt);
	GetCounterValue(SW_Cnt, &sw_cnt_val);
	syslog(LOG_INFO, "SW_Cnt = %d", sw_cnt_val);
}
