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
void busy_wait(void);

TASK(main_task);
TASK(hpri_task);


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
 * ループ回数
 */
#define DELAY_LOOP 0x8000000L

/*
 * ビジーループ関数
 */
void
busy_wait(void){
	long i;
	for(i = 0; i < DELAY_LOOP; i++);
}

uint8 main_task_end = 0;

/*
 * main_task
 */
TASK(main_task){

	syslog(LOG_INFO, "main_task Start!");

	for(;;) {
		/* 終了要求判定 */
		if(main_task_end == 1){
			main_task_end = 0;
			syslog(LOG_INFO, "main_task End!");
			TerminateTask();
		}
		syslog(LOG_INFO, "main_task is running.");
		busy_wait();
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
 * mpri_task(中優先度タスク)
 */
TASK(mpri_task){
	syslog(LOG_INFO, "mpri_task Start!");
	syslog(LOG_INFO, "mpri_task End!");
	TerminateTask();
}	/* TASK( mpri_task ) */


/*
 * lpri_task(低優先度タスク)
 */
TASK(lpri_task){
	syslog(LOG_INFO, "lpri_task Start!");
	syslog(LOG_INFO, "lpri_task End!");
	TerminateTask();
}	/* TASK( lpri_task ) */


/*
 * PSW2割込み(C2ISR)
 */
ISR(psw2_int){
	syslog(LOG_INFO, "psw2_int Start!");
	main_task_end = 1;
}


/*
 * PSW1割込み(C2ISR)
 */
ISR(psw1_int){
	uint8 dsw_state;

	syslog(LOG_INFO, "psw1_int Start!");

	/* DSW状態取得 */
	dsw_state = switch_dip_sense();

	/* DSW状態判定 */
	if(((dsw_state & DSW1) == DSW1)){
		syslog(LOG_INFO, "psw1_int : ActivateTask(hpri_task);");
		ActivateTask(hpri_task);
	}

	if(((dsw_state & DSW2) == DSW2)){
		syslog(LOG_INFO, "psw1_int : ActivateTask(mpri_task);");
		ActivateTask(mpri_task);
	}

	if(((dsw_state & DSW3) == DSW3)){
		syslog(LOG_INFO, "psw1_int : ActivateTask(lpri_task);");
		ActivateTask(lpri_task);
	}

	if(((dsw_state & DSW4) == DSW4)){
		syslog(LOG_INFO, "psw1_int : ActivateTask(main_task);");
		ActivateTask(main_task);
	}
}
