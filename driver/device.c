#include "Os.h"
#include "device.h"
#include "prc_sil.h"

/*
 * LED接続ポート
 * 
 * 拡張I/OボードのLED1-3はプログラマブル入出力ポート4に
 * 次のように接続されている．
 *  D1 : P8_4
 *  D2 : P8_5
 *  D3 : P8_6
 *  D4 : P8_7
 */

#define LED1_PORT  0x10
#define LED2_PORT  0x20
#define LED3_PORT  0x40
#define LED4_PORT  0x80

#define LED_PORT_MASK (LED4_PORT|LED3_PORT|LED2_PORT|LED1_PORT)

/*
 *  LED接続ポート初期化
 */ 
void
led_init(void){
	uint16 wk;

	/* PMC8 設定 */
	wk = sil_reh_mem((void *) PMC(8));
	wk &= ~LED_PORT_MASK;
	sil_wrh_mem((void *) PMC(8), wk);

	/* PM8 設定 */
	wk = sil_reh_mem((void *) PM(8));
	wk &= ~LED_PORT_MASK;
	sil_wrh_mem((void *) PM(8), wk);

	/* All Off */
	led_out(LED_OFF);
}


/*
 *  LED接続ポート書き込み
 */ 
void
led_out(uint8 led_data){
	uint16 wk;
	uint16 ptn = 0;

	if (led_data & LED1){
		ptn |= LED1_PORT;
	}
	if (led_data & LED2){
		ptn |= LED2_PORT;
	}
	if (led_data & LED3){
		ptn |= LED3_PORT;
	}
	if (led_data & LED4){
		ptn |= LED4_PORT;
	}

	ptn = ~ptn & LED_PORT_MASK;
	wk = sil_reh_mem((void *) P(8));
	wk &= ~LED_PORT_MASK;
	wk |= ptn;
	sil_wrh_mem((void *) P(8), wk);
}


/*
 * DIPスイッチ接続ポート
 * 
 * 拡張I/OボードのSW1-4はプログラマブル入出力ポート
 * にインバータを介して接続されている．
 *  DSW1 : P0_7
 *  DSW2 : P0_8
 *  DSW3 : P0_9
 *  DSW4 : P0_10
 */

#define DSW1_PORT  0x0080
#define DSW2_PORT  0x0100
#define DSW3_PORT  0x0200
#define DSW4_PORT  0x0400

#define DSW_PORT_MASK (DSW4_PORT|DSW3_PORT|DSW2_PORT|DSW1_PORT)

/*
 * DIPスイッチ接続ポート初期化
 */
void
switch_dip_init(void){
	uint16 wk;

	/* PMC0 設定 */
	wk = sil_reh_mem((void *) PMC(0));
	wk &= ~DSW_PORT_MASK;
	sil_wrh_mem((void *) PMC(0), wk);

	/* PM0 設定 */
	wk = sil_reh_mem((void *) PM(0));
	wk |= DSW_PORT_MASK;
	sil_wrh_mem((void *) PM(0), wk);

	/* PIBC0 設定 */
	wk = sil_reh_mem((void *) PIBC(0));
	wk |= DSW_PORT_MASK;
	sil_wrh_mem((void *) PIBC(0), wk);
}

/*
 * DIPスイッチ状態の読み込み
 */
uint8
switch_dip_sense(void){
	uint16 wk;
	uint16 ptn = 0;

	wk = sil_reh_mem((void *) PPR(0));

	if (!(wk & DSW1_PORT)){
		ptn |= DSW1;
	}
	if (!(wk & DSW2_PORT)){
		ptn |= DSW2;
	}
	if (!(wk & DSW3_PORT)){
		ptn |= DSW3;
	}
	if (!(wk & DSW4_PORT)){
		ptn |= DSW4;
	}

	return(ptn);
}


/*
 * PUSHスイッチ接続ポート
 * 
 *  PSW1 : P8_0 (INTP4) : 第3兼用
 *  PSW2 : P8_1 (INTP5) : 第3兼用
 */
#define PSW1_PORT  0x0001
#define PSW2_PORT  0x0002
#define PSW_PORT_MASK  0x0003

#define PSW_PORT_PFCAE_INIT  0x0000
#define PSW_PORT_PFCE_INIT   0x0003
#define PSW_PORT_PFC_INIT    0x0000
#define PSW_PORT_PMC_INIT    0x0003
#define PSW_PORT_PM_INIT     0x0003
#define PSW_PORT_PIBC_INIT   0x0003

#define FCLA0CTL4_INTPL 0xFFC34030
#define FCLA0CTL5_INTPL 0xFFC34034

/*
 * PUSHスイッチ接続ポート初期化
 */
void
switch_push_init(void){
	uint16 wk;

	/* PFCAE8 設定 */
	wk = sil_reh_mem((void *) PFCAE(8));
	wk &= ~PSW_PORT_MASK;
	wk |= (PSW_PORT_PFCAE_INIT & PSW_PORT_MASK);
	sil_wrh_mem((void *) PFCAE(8), wk);

	/* PFCE8 設定 */
	wk = sil_reh_mem((void *) PFCE(8));
	wk &= ~PSW_PORT_MASK;
	wk |= (PSW_PORT_PFCE_INIT & PSW_PORT_MASK);
	sil_wrh_mem((void *) PFCE(8), wk);

	/* PFC8 設定 */
	wk = sil_reh_mem((void *) PFC(8));
	wk &= ~PSW_PORT_MASK;
	wk |= (PSW_PORT_PFC_INIT & PSW_PORT_MASK);
	sil_wrh_mem((void *) PFC(8), wk);

	/* PMC8 設定 */
	wk = sil_reh_mem((void *) PMC(8));
	wk &= ~PSW_PORT_MASK;
	wk |= (PSW_PORT_PMC_INIT & PSW_PORT_MASK);
	sil_wrh_mem((void *) PMC(8), wk);

	/* PM8 設定 */
	wk = sil_reh_mem((void *) PM(8));
	wk &= ~PSW_PORT_MASK;
	wk |= (PSW_PORT_PM_INIT & PSW_PORT_MASK);
	sil_wrh_mem((void *) PM(8), wk);

	/* PIBC8 設定 */
	wk = sil_reh_mem((void *) PIBC(8));
	wk &= ~PSW_PORT_MASK;
	wk |= (PSW_PORT_PIBC_INIT & PSW_PORT_MASK);
	sil_wrh_mem((void *) PIBC(8), wk);

	/* エッジ検出立ち下がり */
	sil_wrb_mem((void *)FCLA0CTL4_INTPL, 0x02);
	sil_wrb_mem((void *)FCLA0CTL5_INTPL, 0x02);
}


/*
 * PUSHスイッチ状態の読み込み
 */
uint8
switch_push_sense(void){
	uint16 wk;
	uint16 mask;

	wk = sil_reh_mem((void *) PPR(8));
	mask =0;
	if(!(wk & PSW1_PORT)) {
		mask |= PSW1;
	}
	if(!(wk & PSW2_PORT)) {
		mask |= PSW2;
	}

	return(mask);
}
