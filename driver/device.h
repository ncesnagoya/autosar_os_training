/*
 * 
 * �ǥХ������ؿ����γ������
 *
 */
#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Os.h"

/*
 * LED��ON/OFF�ѥ�����
 */
#define LED1             0x01
#define LED2             0x02
#define LED3             0x04
#define LED4             0x08
#define LED_OFF          0x00

/*
 *  LED��³�ݡ��Ƚ����
 */ 
extern void led_init(void);

/*
 *  LED��³�ݡ��Ƚ񤭹���
 */ 
extern void led_out(uint8 led_data);


/*
 * DIP�����å���³�ӥå�
 */
#define DSW1             0x01
#define DSW2             0x02
#define DSW3             0x04
#define DSW4             0x08


/*
 * DIP�����å���³�ݡ��Ƚ����
 */
extern void switch_dip_init(void);

/*
 * DIP�����å����֤��ɤ߹���
 */
extern uint8 switch_dip_sense(void);

/*
 * �ݡ���1��PUSH�����å���³�ӥå�
 */
#define PSW1             0x01
#define PSW2             0x02
#define PSW_MASK         (PSW2|PSW1)

/*
 * PUSH�����å���³�ݡ��Ƚ����
 */
extern void switch_push_init(void);

/*
 * PUSH�����å����֤��ɤ߹���
 */
extern uint8 switch_push_sense(void);



/*
 * INT3(PSW2)������ֹ�
 */
#define INT3_INHNO   4
#define SW9_INHNO    4


/*
 * PSW2����߽����
 */
extern void sw9_int_init(void);

/*
 * PSW1������ֹ�
 */
#define INT4_INHNO   9
#define SW8_INHNO    9


/*
 * INT4(PSW1)����߽����
 */
extern void sw8_int_init(void);

/*
 * LED�ȥ����å��ξ��֥ޥ���
 */
#define ON              1     /* LED�䥹���å�ON����             */
#define OFF             0     /* LED�䥹���å�OFF����            */


/*
 * LED�ȥ����å��θ������ꡦ�ɤ߹��ߴؿ���
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
