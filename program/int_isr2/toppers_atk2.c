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
 *  $Id: toppers_atk2.c 921 2014-01-10 06:44:19Z fsi-asanoto $
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
void busy_wait(void);

TASK(main_task);
TASK(hpri_task);


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

	while (1) {
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

}   /* StartupHook */
#endif /* CFG_USE_STARTUPHOOK */


/*
 * ��������ѿ�
 */
uint16 psw1_count = 0;


/*
 * �롼�ײ��
 */
#define DELAY_LOOP 0x1000000L

/*
 * �ӥ����롼�״ؿ�
 */

void
busy_wait(void){
	long i;
	for(i = 0; i < DELAY_LOOP; i++);
}


/*
 * main_task
 */
TASK(main_task){
	syslog(LOG_INFO, "main_task Start!");

	for(;;){
		/* PSW���ֽ��� */
		syslog(LOG_INFO, "psw1_count = %d", psw1_count);
		busy_wait();
    }
}	/* TASK( main_task ) */


/*
 * hpri_task(��ͥ���٥�����)
 */
TASK(hpri_task){
	/* ������ */
	syslog(LOG_INFO, "hpri_task Start!");
	syslog(LOG_INFO, "hpri_task End!");

	/* ��λ */
    TerminateTask();
}	/* TASK( hpri_task ) */


/*
 * SW8�����(C2ISR)
 */
ISR(psw1_int){
	psw1_count++;
	ActivateTask(hpri_task);
}
