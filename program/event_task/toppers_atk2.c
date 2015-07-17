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

TASK(dip_task);
TASK(led_task);


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
 * dip_task
 */
TASK(dip_task){
	uint8 dsw_state;
	uint8 pre_dsw_state = 0;

	syslog(LOG_INFO, "dip_task Start!");

	for(;;) {
		/* DSW���ּ��� */
		dsw_state = switch_dip_sense();

		/* DSW����Ƚ�� */
		if(dsw_state != pre_dsw_state){
			if(((dsw_state & DSW1) == DSW1) && ((pre_dsw_state & DSW1) != DSW1)){
				syslog(LOG_INFO, "DSW1 ON");
				SetEvent(led_task, DSW1_ON);
			}

			if(((dsw_state & DSW1) != DSW1) && ((pre_dsw_state & DSW1) == DSW1)){
				syslog(LOG_INFO, "DSW1 OFF");
				SetEvent(led_task, DSW1_OFF);
			}

			if(((dsw_state & DSW2) == DSW2) && ((pre_dsw_state & DSW2) != DSW2)){
				syslog(LOG_INFO, "DSW2 ON");
				SetEvent(led_task, DSW2_ON);
			}

			if(((dsw_state & DSW2) != DSW2) && ((pre_dsw_state & DSW2) == DSW2)){
				syslog(LOG_INFO, "DSW2 OFF");
				SetEvent(led_task, DSW2_OFF);
			}

			if(((dsw_state & DSW3) == DSW3) && ((pre_dsw_state & DSW3) != DSW3)){
				syslog(LOG_INFO, "DSW3 ON");
				SetEvent(led_task, DSW3_ON);
			}

			if(((dsw_state & DSW3) != DSW3) && ((pre_dsw_state & DSW3) == DSW3)){
				syslog(LOG_INFO, "DSW3 OFF");
				SetEvent(led_task, DSW3_OFF);
			}

			if(((dsw_state & DSW4) == DSW4) && ((pre_dsw_state & DSW4) != DSW4)){
				syslog(LOG_INFO, "DSW4 ON");
				SetEvent(led_task, DSW4_ON);
			}

			if(((dsw_state & DSW4) != DSW4) && ((pre_dsw_state & DSW4) == DSW4)){
				syslog(LOG_INFO, "DSW4 OFF");
				SetEvent(led_task, DSW4_OFF);
			}

			pre_dsw_state = dsw_state;

			Schedule();
		}
	}
}	/* TASK( dip_task ) */


/*
 * led_task
 */
TASK(led_task){
	uint8 led_state;
	EventMaskType mask;

	syslog(LOG_INFO, "led_task Start!");

	for(;;){
		WaitEvent(DSW1_ON|DSW1_OFF|DSW2_ON|DSW2_OFF|DSW3_ON|DSW3_OFF|DSW4_ON|DSW4_OFF);
		GetEvent(led_task, &mask);
		ClearEvent(mask);

		led_state = 0;

		/* ����Ƚ�� */
		if((mask & DSW1_ON) == DSW1_ON){
			led_state |= LED1;
		}

		if((mask & DSW2_ON) == DSW2_ON){
			led_state |= LED2;
		}

		if((mask & DSW3_ON) == DSW3_ON){
			led_state |= LED3;
		}

		if((mask & DSW4_ON) == DSW4_ON){
			led_state |= LED4;
		}

		/* LED����� */
		led_out(led_state);
	}
}	/* TASK( led_task ) */

