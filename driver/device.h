/*
 * 
 * デバイス操作関数群の外部宣言
 *
 */
#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Os.h"

/*
 * LEDのON/OFFパターン
 */
#define LED1             0x01
#define LED2             0x02
#define LED3             0x04
#define LED4             0x08
#define LED_OFF          0x00

/*
 *  LED接続ポート初期化
 */ 
extern void led_init(void);

/*
 *  LED接続ポート書き込み
 */ 
extern void led_out(uint8 led_data);


/*
 * DIPスイッチ接続ビット
 */
#define DSW1             0x01
#define DSW2             0x02
#define DSW3             0x04
#define DSW4             0x08


/*
 * DIPスイッチ接続ポート初期化
 */
extern void switch_dip_init(void);

/*
 * DIPスイッチ状態の読み込み
 */
extern uint8 switch_dip_sense(void);

/*
 * ポート1のPUSHスイッチ接続ビット
 */
#define PSW1             0x01
#define PSW2             0x02
#define PSW_MASK         (PSW2|PSW1)

/*
 * PUSHスイッチ接続ポート初期化
 */
extern void switch_push_init(void);

/*
 * PUSHスイッチ状態の読み込み
 */
extern uint8 switch_push_sense(void);



/*
 * INT3(PSW2)割込み番号
 */
#define INT3_INHNO   4
#define SW9_INHNO    4


/*
 * PSW2割込み初期化
 */
extern void sw9_int_init(void);

/*
 * PSW1割込み番号
 */
#define INT4_INHNO   9
#define SW8_INHNO    9


/*
 * INT4(PSW1)割込み初期化
 */
extern void sw8_int_init(void);

/*
 * LEDとスイッチの状態マクロ
 */
#define ON              1     /* LEDやスイッチON状態             */
#define OFF             0     /* LEDやスイッチOFF状態            */


/*
 * LEDとスイッチの個別設定・読み込み関数群
 */
extern void set_led1_state(unsigned char state);
extern void set_led2_state(unsigned char state);
extern void set_led3_state(unsigned char state);
extern void set_led4_state(unsigned char state);
extern unsigned char get_sw1_state(void);
extern unsigned char get_sw2_state(void);
extern unsigned char get_sw3_state(void);
extern unsigned char get_sw4_state(void);
extern unsigned char get_sw7_state(void);
extern unsigned char get_sw8_state(void);

#endif /* _DEVICE_H_ */
