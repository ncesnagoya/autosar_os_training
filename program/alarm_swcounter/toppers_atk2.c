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
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
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
 *  内部関数プロトタイプ宣言
 */
sint32 main(void);

TASK(main_task);
TASK(hpri_task);
TASK(event_task);
ALARMCALLBACK(func_alarm_callback);

TickType sw_cnt_val = 0;

/*
 *  ユーザメイン関数
 *
 *  アプリケーションモードの判断と，カーネル起動
 */
sint32
main(void){
	/*
	 *  カーネル起動
	 */
	StartOS(AppMode1);

	while(1){
	}
}   /* main */


/*
 *  スタートアップフックルーチン
 */
#ifdef CFG_USE_STARTUPHOOK
void
StartupHook(void){
	/* システムログ機能の初期化 */
	syslog_initialize();

	/* 出力するログ情報の重要度設定 */
	syslog_msk_log(LOG_UPTO(LOG_INFO));

	/* シリアルIOモジュール初期化処理 */
	InitSerial();

	/* カーネル起動メッセージの出力 */
	print_banner();

	/* PSW初期化 */
	switch_push_init();

	/* DSW初期化 */
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
		/* DSW状態取得 */
		dsw_state = switch_dip_sense();

		/* DSW状態判定 */
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
 * hpri_task(高優先度タスク)
 */
TASK(hpri_task){
	syslog(LOG_INFO, "hpri_task Start!");
	syslog(LOG_INFO, "hpri_task End!");

	TerminateTask();
}	/* TASK( hpri_task ) */


/*
 * event_task(イベント待ちタスク)
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
 * アラームコールバック関数
 */
ALARMCALLBACK(func_alarm_callback){
	syslog(LOG_INFO, "func_alarm_callback() : called!");
}


/*
 * PSW1割込み(ISR2)
 */
ISR(psw1_int){
	IncrementCounter(SW_Cnt);
	GetCounterValue(SW_Cnt, &sw_cnt_val);
	syslog(LOG_INFO, "SW_Cnt = %d", sw_cnt_val);
}
