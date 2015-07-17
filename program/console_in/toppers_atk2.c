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
TASK(led_task);


/*
 *  ユーザメイン関数
 *
 *  アプリケーションモードの判断と，カーネル起動
 */
sint32
main(void){
	led_init();
	led_out(LED1);

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

	/* LED初期化 */
	led_init();

}   /* StartupHook */
#endif /* CFG_USE_STARTUPHOOK */


uint8 led_state = 0;

/*
 * main_task
 */
TASK(main_task){
	uint8 c;

	syslog(LOG_INFO, "main_task Start!");

	for(;;) {
		c = '\0';
		do{
			WaitEvent(EVENT_CONSOLE_IN);
			ClearEvent(EVENT_CONSOLE_IN);
			RecvPolSerialChar(&c);
		}while(c == '\0');

		if(c == '1'){
			led_state &= ~(LED2|LED3|LED4);
			led_state |= LED2;
		}
		else if(c == '2'){
			led_state &= ~(LED2|LED3|LED4);
			led_state |= LED3;
		}
		else if(c == '3'){
			led_state &= ~(LED2|LED3|LED4);
			led_state |= LED4;
		}
		else if(c == '4'){
			led_state &= ~(LED2|LED3|LED4);
		}

		led_out(led_state);
	}
}	/* TASK( main_task ) */


/*
 * ループ回数
 */
#define DELAY_LOOP 0x800000L

/*
 * ビジーループ関数
 */ 
void
busy_wait(void){
	long i;
	for(i = 0; i < DELAY_LOOP; i++);
}


/*
 * led_task
 */
TASK(led_task){
	syslog(LOG_INFO, "led_task Start!");

	for(;;){
		led_state ^= LED1;
		led_out(led_state);
		busy_wait();
	}
}	/* TASK( led_task ) */
