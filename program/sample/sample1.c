/*
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2015 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2015 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2013 by Spansion LLC, USA
 *  Copyright (C) 2011-2015 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2015 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2015 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2004-2015 by Witz Corporation
 *  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2014-2015 by eSOL Co.,Ltd., JAPAN
 *  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
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
 *  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
 *  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
 *  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
 *  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 *
 *  $Id: sample1.c 1801 2015-03-27 06:34:43Z t_ishikawa $
 */

/*
 *		����ץ�ץ����(1)������
 *
 *  ATK2-SC1�δ���Ū��ư����ǧ���뤿��Υ���ץ�ץ����
 *
 *  �ץ����γ��ס�PC�ȥܡ��ɴ֤ǥ��ꥢ���̿���Ԥ����桼������
 *  ���ޥ�ɤ˱�����ư��ȥ����Ϥ�Ԥʤ�
 *
 *  �㥳�ޥ�ɰ�����
 *  ������������
 *    '1' : �ʹߤΥ��ޥ�ɤ� Task1 ���Ф��ƹԤ�
 *    '2' : �ʹߤΥ��ޥ�ɤ� Task2 ���Ф��ƹԤ�
 *    '3' : �ʹߤΥ��ޥ�ɤ� Task3 ���Ф��ƹԤ�
 *    '4' : �ʹߤΥ��ޥ�ɤ� Task4 ���Ф��ƹԤ�
 *    '5' : �ʹߤΥ��ޥ�ɤ� Task5 ���Ф��ƹԤ�
 *  ��������������ǽ
 *    'a' : ActivateTask �ˤƥ�������ư���롥
 *    'A' : TerminateTask �ˤƥ�������λ���롥
 *    '!'(Shift+1) : ChainTask �ˤƥ�������λ����Task1 ��ư����
 *    '"'(Shift+2) : ChainTask �ˤƥ�������λ����Task2 ��ư����
 *    '#'(Shift+3) : ChainTask �ˤƥ�������λ����Task3 ��ư����
 *    '$'(Shift+4) : ChainTask �ˤƥ�������λ����Task4 ��ư����
 *    '%'(Shift+5) : ChainTask �ˤƥ�������λ����Task5 ��ư����
 *    's' : �Υ�ץꥨ��ץƥ���°���Ǥ��륿���� MainTask �ˤƺǹ�
 *          ͥ���٥����� HighPriorityTask ��ư����Schedule �ˤ�
 *          �ƥ������塼��󥰤�Ԥ�
 *    'S' : �Υ�ץꥨ��ץƥ��֥����� NonPriTask ��ư����
 *          �Υ�ץꥨ��ץƥ��֥����� NonPriTask �ˤƺǹ�ͥ����
 *          ������ HighPriorityTask ��ư������������λ����
 *    'z' : �¹���Υ��������� GetTaskID ��¹Ԥ��ơ��¹Ծ��֤� TaskID ���������
 *    'Z' : �ᥤ�󥿥������� GetTaskState ��¹Ԥ��ơ��оݥ������ξ��֤��������
 *    'x' : div̿���¹Ԥ��ơ�̤���̿���㳰��ȯ��������
 *  ������ߴ�����ǽ
 *    'd' : DisableAllInterrupts ��¹Ը塤�ϡ��ɥ������������ͤ�
 *          3��ɽ������ EnableAllInterrupts ��¹Ԥ���
 *    'D' : SuspendAllInterrupts ��¹Ը塤�ϡ��ɥ������������ͤ�
 *          3��ɽ����������� SuspendAllInterrupts ��¹Ը塤�ϡ���
 *          �������������ͤ�3��ɽ������ResumeAllInterrupts ��¹Ը塤
 *          �ϡ��ɥ������������ͤ�3��ɽ������ResumeAllInterrupts ��
 *          �¹Ԥ���
 *    'f' : SuspendOSInterrupts ��¹Ը塤�ϡ��ɥ������������ͤ�
 *          3��ɽ����������� SuspendOSInterrupts ��¹Ը塤�ϡ���
 *          �������������ͤ�3��ɽ����������� SuspendAllInterrupts
 *          ��¹Ը塤�ϡ��ɥ������������ͤ�3��ɽ������
 *          ResumeAllInterrupts ��¹Ը塤�ϡ��ɥ����������󥿤�3��
 *          ɽ������ResumeOSInterrupts ��¹Ը�ϡ��ɥ�����������
 *          �ͤ�3��ɽ������ResumeOSInterrupts ��¹Ԥ���
 *    'T' : �ϡ��ɥ������������ͤ�3��ɽ������
 *  ���꥽����������ǽ
 *    'k' : GetResource �ˤƥ꥽���� TskLevelRes ��������롥�ʤ���
 *          Task3 �ϡ����Υ꥽�������ͥ���٤��⤤���ᥨ�顼�Ȥʤ�
 *    'K' : ReleaseResource �ˤƥ꥽���� TskLevelRes ���������
 *    'i' : GetResource �ˤƥ꥽���� CntRes ������塤�ϡ��ɥ�����
 *          �������ͤ�3��ɽ������ReleaseResource �ˤƥ꥽����
 *          CntRes ���������
 *  �����٥�����浡ǽ
 *    'e' : SetEvent �ˤƥ��٥�Ȥ����ꤹ�롥Task2 �� Task3 �ʳ���
 *          ������Ƥ��ʤ����ᥨ�顼�Ȥʤ�
 *    'w' : ClearEvent �ˤƼ��������Υ��٥�Ȥ򥯥ꥢ���롥Task2 ��
 *          Task3 �ʳ��ϳ�����Ƥ��ʤ����ᥨ�顼�Ȥʤ�
 *    'E' : GetEvent �ˤƥ��٥�Ⱦ��֤�������롥Task2 �� Task3
 *          �ʳ��ϳ�����Ƥ��ʤ����ᥨ�顼�Ȥʤ�
 *    'W' : WaitEvent �ˤƼ��������Υ��٥�Ȥ��Ԥġ�Task3 �� Task4
 *          �ʳ��ϥ��顼�Ȥʤ�
 *  �����顼�ൡǽ
 *    'b' : GetAlarmBase �ˤƥ��顼�� MainCycArm �Υ��顼��١���
 *          ������������
 *    'B' : GetAlarm �ˤƥ��顼�� MainCycArm �λĤꥫ������ͤ�2��
 *          Ϣ³�Ǽ�������
 *    'v' : SetRelAlarm �ˤƥ��顼�� ActTskArm ��ư����500ms ���
 *          ������ Task1 ��ư����
 *    'V' : SetRelAlarm �ˤƥ��顼�� SetEvtArm ��ư����500ms ���
 *          ���٥�� T3Evt �����ꤹ��
 *    'n' : SetRelAlarm �ˤƥ��顼�� CallBackArm �򡤥ѥ�᡼��
 *          900ms �����λ��ñȯ���顼���������ꤹ��
 *    'N' : SetRelAlarm �ˤƥ��顼�� CallBackArm �򡤥ѥ�᡼��
 *          900ms �����λ�� 500ms �������顼���������ꤹ��
 *    'm' : SetAbsAlarm �ˤƥ��顼�� CallBackArm �򡤥ѥ�᡼��
 *          ��������900����λ��ñȯ���顼���������ꤹ��
 *    'M' : SetAbsAlarm �ˤƥ��顼�� CallBackArm �򡤥ѥ�᡼��
 *          ��������900����λ�� 500ms �������顼������ꤹ��
 *    'h' : CancelAlarm �ˤƥ��顼�� CallBackArm �򥭥�󥻥뤹��
 *  ����������ǽ
 *    'c' : �������ˤ� IncrementCounter ��¹Ԥ��������� SampleCnt
 *          �˥����ʥ����Τ���
 *          1 �����ʥ�ǥ��顼�� SampleArm ����λ����������Хå���
 *          �¹Ԥ���
 *    'C' : �������ˤ� IncrementCounter ��¹Ԥ��������� SampleCnt2
 *          �˥����ʥ����Τ���
 *          1 �����ʥ�ǥ��顼�� SampleArm1 ����λ����SampleCnt3 ��
 *          ���󥯥���Ȥ��롥 SampleCnt3 �� 1 �����ʥ�� SampleAlm2
 *          ����λ��������Хå���¹Ԥ���
 *    'j' : �������ˤ� GetCounterValue ��¹Ԥ���
 *          ���������ͤ���¸����
 *    'J' : �������ˤ� GetEalsedCounterValue ��¹Ԥ���
 *          �����ͤ������GetCounterValue �ޤ��� GetEalsedCounterValue �ˤƼ���
 *          �����ͤȤ��롥��󡤤ޤ��ϡ�GetCounterValue��¹Ԥ��Ƥ��ʤ�����0
 *          �Ȥ���
 *
 *    'r' : �������ˤ� GetISRID��¹Ԥ���
 *          ����������ƥ����Ȥ����GetISRID��ƽФ������ϥ��顼�Ȥ���
 *          INVALID_ISR���ֵѤ����
 *
 *          ����ߥ���ƥ����Ȥ����GetISRIDȯ�Ԥϡ�SystemTimerCnt�Υ�����Хå�
 *          �롼�����'n' ���ޥ�ɤǼ¹ԡˤˤƹԤ�
 *
 *          ����������ƥ����Ȥ����GetISRIDȯ�Ԥϡ�SampleCnt2�Υ�����Хå�
 *          �롼�����'C' �ޤ��� 'c' ���ޥ�ɤǼ¹ԡˤˤƹԤ�
 *
 *  ���������塼��ơ��֥����浡ǽ
 *    't' : �������塼��ơ��֥�ư������ON/OFF
 *
 *        'i' : SchtblSampleCnt�����󥿤򥤥󥯥���Ȥ���
 *              SchtblSampleCnt�����󥿤ϥ������塼��ơ��֥�ζ�ư������
 *        '1' : �ʹߤΥ��ޥ�ɤ� scheduletable1 ���Ф��ƹԤ�(�ǥե������)
 *        '2' : �ʹߤΥ��ޥ�ɤ� scheduletable2 ���Ф��ƹԤ���
 *        '3' : �ʹߤΥ��ޥ�ɤ� scheduletable3(¸�ߤ��ʤ�ID) ���Ф��ƹԤ�
 *              ���ޥ�ɤΥ��顼��ǧ�ˤ���Ѥ���
 *        's' : StartScheduleTableRel��¹Ԥ���������(5)�ǥ������塼��ơ��֥�򳫻Ϥ���
 *        'S' : StartScheduleTableAbs��¹Ԥ���������(5)�ǥ������塼��ơ��֥�򳫻Ϥ���
 *        'f' : StopScheduleTable��¹Ԥ����������塼��ơ��֥����ߤ���
 *        'n' : NextScheduleTable��¹Ԥ���scheduletable2�����ؤ���
 *        'N' : NextScheduleTable��¹Ԥ���scheduletable1�����ؤ���
 *        'g' : GetScheduleTableStatus��¹Ԥ����������塼��ơ��֥���֤��������
 *        'q' : ShutdownOS( E_OK ) OS�¹����浡ǽ��'q'��Ʊ����ǽ
 *        'Q' : ShutdownOS( E_OS_STATE ) OS�¹����浡ǽ��'Q'��Ʊ����ǽ
 *
 *  ��OS�¹����浡ǽ
 *    'p' : GetActiveApplicationMode �ˤƥ��ץꥱ�������⡼�ɤ�
 *          ��������
 *    'q' : ShutdownOS �򥳡��� E_OK �Ǽ¹Ԥ�������ץ�ץ�����
 *          ��λ����
 *    'Q' : ShutdownOS �򥳡��� E_OS_STATE �Ǽ¹Ԥ�������ץ�ץ����
 *          ��λ����
 *
 *  �㥪�֥������Ȱ�����
 *  ��OS
 *    �������ȥ��åץեå�������
 *    ����åȥ�����եå�������
 *    ���顼�եå�������
 *    �ץ쥿�����եå���̤����
 *    �ݥ��ȥ������եå���̤����
 *  ��������
 *  �ᥤ�󥿥���
 *    ������ID��MainTask
 *    ͥ���١�14
 *    ¿�ŵ�ư����1
 *    �������塼�롧�Υ�ץꥨ��ץƥ���
 *    ��ư��ư��AppMode1, AppMode2, AppMode3
 *    ���ס��桼�����󥿥ե������ʥ��ꥢ��IO��ꥳ�ޥ�ɤ��������
 *          ������б�����ư���Ԥʤ���
 *          �������顼�� MainCycArm �ˤ�ꡤ10ms���Ȥ��Ԥ������
 *          ���ޥ�ɤμ���̵ͭ��ݡ���󥰤���
 *          ���٥�ȡ�ID��MainEvt�ˤ��Ϣ�դ��Ƥ���
 *  �ǹ�ͥ���٥�����
 *    ������ID��HighPriorityTask
 *    ͥ���١�15
 *    ¿�ŵ�ư����1
 *    �������塼�롧�ե�ץꥨ��ץƥ���
 *    ��ư��ư���ʤ�
 *    ���ס���ư������Ϥ��ƽ�λ���롥�Υ�ץꥨ��ץƥ��֥�����
 *          ���鵯ư���졤�ץꥨ��ץȤ��Ƥ��뤫�ɤ����γ�ǧ��
 *  �Υ�ץꥨ��ץƥ��֥�����
 *    ������ID��NonPriTask
 *    ͥ���١�1
 *    ¿�ŵ�ư����8
 *    �������塼�롧�Υ�ץꥨ��ץƥ���
 *    ��ư��ư���ʤ�
 *    ���ס���ư������Ϥ����ǹ�ͥ���٥����� HighPriorityTask ��
 *          ��ư�塤��λ������Ϥ��ƥ�������λ����
 *  ������1
 *    ������ID��Task1
 *    ͥ���١�4
 *    �������塼�롧�ե�ץꥨ��ץƥ���
 *    ��ư��ư��AppMode2
 *    ¿�ŵ�ư����8
 *    ���ס���������������ʥᥤ�󥿥�������λ���ˤ��ư���
 *          ��ư���줹���̵�¥롼�פ����ꡤ���ޥ�ɽ�����¹Ԥ���
 *          �꥽���� TskLevelRes ���Ϣ�դ��Ƥ���
 *          �꥽���� CntRes ���Ϣ�դ��Ƥ���
 *  ������2
 *    ������ID��Task2
 *    ͥ���١�7
 *    ¿�ŵ�ư����1
 *    �������塼�롧�ե�ץꥨ��ץƥ���
 *    ��ư��ư���ʤ�
 *    ���ס���������������ʥᥤ�󥿥�������λ���ˤ��ư���
 *          ��ư���줹���̵�¥롼�פ����ꡤ���ޥ�ɽ�����¹Ԥ���
 *          �꥽���� TskLevelRes ���Ϣ�դ��Ƥ���
 *          �꥽���� CntRes ���Ϣ�դ��Ƥ���
 *          ���٥�� T2Evt ���Ϣ�դ��Ƥ���
 *  ������3
 *    ������ID��Task3
 *    ͥ���١�12
 *    ¿�ŵ�ư����1
 *    �������塼�롧�ե�ץꥨ��ץƥ���
 *    ��ư��ư��AppMode3
 *    ���ס���������������ʥᥤ�󥿥�������λ���ˤ��ư���
 *          ��ư���줹���̵�¥롼�פ����ꡤ���ޥ�ɽ�����¹Ԥ���
 *          ���٥���Ԥ����뤳�Ȥ���ǽ�Ǥ���
 *          �꥽���� CntRes ���Ϣ�դ��Ƥ���
 *          ���٥�� T3Evt ���Ϣ�դ��Ƥ���
 *  ������4
 *    ������ID��Task4
 *    ͥ���١�6
 *    ¿�ŵ�ư����5
 *    �������塼�롧�ե�ץꥨ��ץƥ���
 *    ��ư��ư���ʤ�
 *    ���ס���������������ʥᥤ�󥿥�������λ���ˤ��ư���
 *          ��ư���줹���̵�¥롼�פ����ꡤ���ޥ�ɽ�����¹Ԥ���
 *          �꥽���� TskLevelRes ���Ϣ�դ��Ƥ���
 *          �꥽���� CntRes ���Ϣ�դ��Ƥ���
 *          �����꥽���� GroupRes ���Ϣ�դ��Ƥ���
 *  ������5
 *    ������ID��Task5
 *    ͥ���١�9
 *    ¿�ŵ�ư����5
 *    �������塼�롧�ե�ץꥨ��ץƥ���
 *    ��ư��ư���ʤ�
 *    ���ס���������������ʥᥤ�󥿥�������λ���ˤ��ư���
 *          ��ư���줹���̵�¥롼�פ����ꡤ���ޥ�ɽ�����¹Ԥ���
 *          �꥽���� TskLevelRes ���Ϣ�դ��Ƥ���
 *          �꥽���� CntRes ���Ϣ�դ��Ƥ���
 *          �����꥽���� GroupRes ���Ϣ�դ��Ƥ���
 *  ������6
 *    ������ID��Task6
 *    ͥ���١�14
 *    ¿�ŵ�ư����1
 *    �������塼�롧�ե�ץꥨ��ץƥ���
 *    ��ư��ư���ʤ�
 *    ���ס���ư��å��������Ϥ������٥��(T6Evt)���Ԥ�
 *  ������7
 *    ������ID��Task7
 *    ͥ���١�14
 *    ¿�ŵ�ư����1
 *    �������塼�롧�ե�ץꥨ��ץƥ���
 *    ��ư��ư���ʤ�
 *    ���ס���ư��å��������Ϥ������٥��(T7Evt)���Ԥ�
 *  ������8
 *    ������ID��Task8
 *    ͥ���١�14
 *    ¿�ŵ�ư����1
 *    �������塼�롧�ե�ץꥨ��ץƥ���
 *    ��ư��ư���ʤ�
 *    ���ס���ư��å��������Ϥ������٥��(T8Evt)���Ԥ�
 *
 *  ������ߥ����ӥ��롼����
 *  ���ꥢ��IO���������
 *    ISRID��RxHwSerialInt
 *    ͥ���١�2
 *    ���ƥ��ꡧ2
 *    ���ס����ޥ�ɤ��������
 *  ���꥽����
 *  ��������٥�꥽����
 *    �꥽����ID��TskLevelRes
 *    �ץ�ѥƥ���ɸ��
 *  �������ѥ����󥿥꥽����
 *    �꥽����ID��CntRes
 *    �ץ�ѥƥ���ɸ��
 *  ���������롼�ץ꥽����
 *    �꥽����ID��GroupRes
 *    �ץ�ѥƥ�������
 *  �����٥��
 *  �ᥤ�󥿥������٥��
 *    ���٥��ID��MainEvt
 *  ������2���٥��
 *    ���٥��ID��T2Evt
 *  ������3���٥��
 *    ���٥��ID��T3Evt
 *  ��������
 *  �����ƥॿ���ޥ�����
 *    ������ID��MAIN_HW_COUNTER
 *    ��������͡�0��999
 *    �û��͡�1
 *  ����ץ륫����
 *    ������ID��SampleCnt
 *    ��������͡�0��99
 *    �û��͡�10
 *  �����顼��
 *  �ᥤ��������顼��
 *    ���顼��ID��MainCycArm
 *    �١���������ID��MAIN_HW_COUNTER
 *    ��������󡧥��٥������ MainEvt
 *    ��ư��ư���ʤ�
 *  ��������ư���顼��
 *    ���顼��ID��ActTskArm
 *    �١���������ID��MAIN_HW_COUNTER
 *    ��������󡧥�������ư Task1
 *    ��ư��ư���ʤ�
 *  ���٥�����ꥢ�顼��
 *    ���顼��ID��SetEvtArm
 *    �١���������ID��MAIN_HW_COUNTER
 *    ��������󡧥��٥������ T3Evt
 *    ��ư��ư���ʤ�
 *  ������Хå��¹ԥ��顼��
 *    ���顼��ID��CallBackArm
 *    �١���������ID��MAIN_HW_COUNTER
 *    ��������󡧥�����Хå��ؿ��¹�
 *    ��ư��ư���ʤ�
 *  IncrementCounter��ǧ�ѥ��顼��
 *    ���顼��ID��SampleArm
 *    �١���������ID��SampleCnt
 *    ��������󡧥�����Хå��ؿ��¹�
 *    ��ư��ư���ʤ�
 *  �����ץꥱ�������⡼��
 *  ��ư��ư�ʤ��⡼��
 *    ���ץꥱ�������⡼��ID��AppMode1
 *  Task1��ư��ư�⡼��
 *    ���ץꥱ�������⡼��ID��AppMode2
 *  Task3��ư��ư�⡼��
 *    ���ץꥱ�������⡼��ID��AppMode3
 *
 */

#include "Os.h"
#include "t_syslog.h"
#include "t_stdlib.h"
#include "sysmod/serial.h"
#include "sysmod/syslog.h"
#include "sample1.h"

#include "sysmod/banner.h"
#include "target_sysmod.h"
#include "target_serial.h"
#include "target_hw_counter.h"


#define GetHwCnt(x, y)
#define GetAppModeInfo()	(0)

/*
 *  �ե�����̾�����ֹ�λ����Ѥ��ѿ�
 */
extern const char8	*fatal_file_name;   /* �ե�����̾ */
extern sint32		fatal_line_num;     /* ���ֹ� */

/*
 *  �����ؿ��ץ�ȥ��������
 */
sint32 main(void);
TASK(MainTask);
TASK(HighPriorityTask);
TASK(NonPriTask);
TASK(Task1);
TASK(Task2);
TASK(Task3);
TASK(Task4);
TASK(Task5);
TASK(Task6);
TASK(Task7);
TASK(Task8);
ALARMCALLBACK(SysTimerAlmCb);
static void TaskProk(uint8 task_no);
static uint8 GetCommand(void);
static void PutActTsk(uint8 task_no);
static void PutActNonPriTsk(void);
static void PutTermTsk(uint8 task_no);
static void PutChainTsk(uint8 from_task_no, uint8 to_task_no);
static void PutSchedule(void);
static void PutTaskID(void);
static void PutTaskState(uint8 task_no);
static void PutDisAllInt(void);
static void PutSusAllInt(void);
static void PutSusOSInt(void);
static void PutHwCnt3(void);
static void PutGetCntRes(void);
static void PutGetTskRes(void);
static void PutRelTskRes(void);
static void PutSetEvt(uint8 task_no);
static void PutClrEvt(uint8 task_no);
static void PutGetEvt(uint8 task_no);
static void PutWaitEvt(uint8 task_no);
static void PutArmBase(void);
static void PutArmTick(void);
static void PutSetRel(uint8 alarm_no, uint8 tick_no, uint8 cycle_no);
static void PutSetAbs(uint8 alarm_no, uint8 tick_no, uint8 cycle_no);
static void PutCanArm(void);
static void PutAppMode(void);
static void schedule_table_sample_routine(void);

/*
 *  �����ǡ����Хåե�
 */
static volatile uint8		command_tbl[8];         /* ���ޥ�ɰ��Ϥ��ơ��֥� */

/*
 *  ��������ǡ����ơ��֥�
 */
/* ̵�����٥�ȥޥ����� */
#define invalid_mask	(EventMaskType) (0)

/* ���٥�ȥޥ����ơ��֥� */
static const EventMaskType	event_mask_tbl[] = {
	invalid_mask,
	T2Evt,
	T3Evt,
	invalid_mask,
	invalid_mask
};

/* ������ID�ơ��֥� */
static const TaskType		task_id_tbl[] = {
	Task1,
	Task2,
	Task3,
	Task4,
	Task5
};

/* ���顼��ID�ơ��֥� */
static const AlarmType		alarm_id_tbl[] = {
	ActTskArm,
	SetEvtArm,
	CallBackArm
};

/* �ƥ��å��ͥơ��֥� */
static const TickType		tick_tbl[] = {
	(TickType) 500,
	(TickType) 900
};

/* ���������ͥơ��֥� */
static const TickType		cycle_tbl[] = {
	(TickType) 0,
	(TickType) COUNTER_MIN_CYCLE
};

/* ���٥�ȥޥ���̾ʸ����ơ��֥� */
static const char8			*event_name_tbl[] = {
	"Invalid",
	"T2Evt",
	"T3Evt",
	"Invalid",
	"Invalid"
};

/* ������̾ʸ����ơ��֥� */
static const char8			*task_name_tbl[] = {
	"Task1",
	"Task2",
	"Task3",
	"Task4",
	"Task5"
};

/* ����������ʸ����ơ��֥� */
static const char8			*task_state_tbl[] = {
	"SUSPENDED",
	"RUNNING",
	"READY",
	"WAITING",
};

/* ���顼��̾ʸ����ơ��֥� */
static const char8			*alarm_name_tbl[] = {
	"ActTskArm",
	"SetEvtArm",
	"CallBackArm"
};

/*
 *  API���顼���ޥ���
 *
 *  ErrorHook��ͭ���ξ���ErrorHook����
 *  ���顼������Ϥ�, ErrorHook��̵���ξ���
 *  �ʲ��Υޥ����ꥨ�顼�����Ϥ�Ԥ�
 */
#if defined(CFG_USE_ERRORHOOK)
#define error_log(api)	(api)
#else /* !defined( CFG_USE_ERRORHOOK ) */
#define	error_log(api)										   \
	{														   \
		StatusType ercd;									   \
		ercd = api;     /* ��API�¹� */						   \
		if (ercd != E_OK) {									   \
			syslog(LOG_INFO, "Error:%d", atk2_strerror(ercd)); \
		}													   \
	}
#endif /* defined( CFG_USE_ERRORHOOK ) */

/*
 *  �桼���ᥤ��ؿ�
 *
 *  ���ץꥱ�������⡼�ɤ�Ƚ�Ǥȡ������ͥ뵯ư
 */
sint32
main(void)
{
	AppModeType	crt_app_mode;

	/*
	 *  ���ץꥱ�������⡼�ɤ�Ƚ��
	 */
	switch (GetAppModeInfo()) {
	case 0:
		crt_app_mode = AppMode1;
		break;
	case 1:
		crt_app_mode = AppMode2;
		break;
	default:
		crt_app_mode = AppMode3;
		break;
	}

	/*
	 *  �����ͥ뵯ư
	 */
	StartOS(crt_app_mode);

	while (1) {
	}
}   /* main */

/*
 *  �ᥤ�󥿥���
 *
 *  �桼�����ޥ�ɤμ����ȡ����ޥ�ɤ��Ȥν����¹�
 */
TASK(MainTask)
{
	uint8		command;
	uint8		task_no;
	uint32		i;

	TickType	val = 0U;
	TickType	eval = 0U;

	/*
	 *  �������ֹ桦���ޥ�ɥХåե������
	 */
	task_no = (uint8) (0);
	for (i = 0U; i < (sizeof(command_tbl) / sizeof(command_tbl[0])); i++) {
		command_tbl[i] = 0U;
	}

	/*
	 *  MainCycArm��������顼��Ȥ�������
	 */
	SetRelAlarm(MainCycArm, TICK_FOR_10MS, TICK_FOR_10MS);

	/*
	 *  ���ޥ�ɼ¹ԥ롼��
	 */
	while (1) {
		WaitEvent(MainEvt);     /* 10ms�κ�Ȼ����Ԥ� */
		ClearEvent(MainEvt);

		/*
		 *  ���ϥ��ޥ�ɼ���
		 */
		syslog(LOG_INFO, "Input Command:");
		command = GetCommand();

		/*
		 *  ���ϥ��ޥ�ɥ����å�
		 */
		if ((command <= (uint8) (0x1fU)) || (command >= (uint8) (0x80U))) {
			syslog(LOG_INFO, "Not ASCII character");
		}
		else {
#ifndef OMIT_ECHO
			syslog(LOG_INFO, "%c", command);
#endif /* OMIT_ECHO */

			/*
			 *  ���ޥ��Ƚ��
			 */
			switch (command) {
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
				/*
				 *  �����оݥ��������ѹ�
				 */
				task_no = (uint8) (command - '1');
				break;
			case 'A':
			case '!':
			case '"':
			case '#':
			case '$':
			case '%':
			case 'z':
			case 'k':
			case 'K':
			case 'l':
			case 'i':
			case 'w':
			case 'W':
				/*
				 *  �������ؤΥ��ޥ������
				 */
				command_tbl[task_no] = command;
				break;
			/*
			 *  �ʹߤϥᥤ�󥿥����ǥ��ޥ�ɽ���
			 */
			case 'a':
				PutActTsk(task_no);
				break;
			case 's':
				PutSchedule();
				break;
			case 'S':
				PutActNonPriTsk();
				break;
			case 'Z':
				PutTaskState(task_no);
				break;
			case 'x':
				syslog(LOG_INFO, "call RAISE_CPU_EXCEPTION");
				RAISE_CPU_EXCEPTION;
				break;
			case 'd':
				PutDisAllInt();
				break;
			case 'D':
				PutSusAllInt();
				break;
			case 'f':
				PutSusOSInt();
				break;
			case 'T':
				PutHwCnt3();
				break;
			case 'e':
				PutSetEvt(task_no);
				break;
			case 'E':
				PutGetEvt(task_no);
				break;
			case 'b':
				PutArmBase();
				break;
			case 'B':
				PutArmTick();
				PutArmTick();
				break;
			case 'v':
				/* SetRelAlarm(ActTskArm, 500, 0)��¹� */
				PutSetRel(0U, 0U, 0U);
				break;
			case 'V':
				/* SetRelAlarm(SetEvtArm, 500, 0)��¹� */
				PutSetRel(1U, 0U, 0U);
				break;
			case 'n':
				/* SetRelAlarm(CallBackArm, 900, 0)��¹� */
				PutSetRel(2U, 1U, 0U);
				break;
			case 'N':
				/* SetRelAlarm(CallBackArm, 900, 500)��¹� */
				PutSetRel(2U, 1U, 1U);
				break;
			case 'm':
				/* SetAbsAlarm(CallBackArm, 900, 0)��¹� */
				PutSetAbs(2U, 1U, 0U);
				break;
			case 'M':
				/* SetAbsAlarm(CallBackArm, 900, 500)��¹� */
				PutSetAbs(2U, 1U, 1U);
				break;
			case 'h':
				/* CancelAlarm(CallBackArm)��¹� */
				PutCanArm();
				break;
			case 'c':
				syslog(LOG_INFO, "Call IncrementCounter(SampleCnt)");
				IncrementCounter(SampleCnt);
				break;
			case 'C':
				syslog(LOG_INFO, "Call IncrementCounter(SampleCnt2)");
				IncrementCounter(SampleCnt2);
				break;
			case 'j':
				syslog(LOG_INFO, "GetCounterValue(MAIN_HW_COUNTER, val)");
				GetCounterValue(MAIN_HW_COUNTER, &val);
				syslog(LOG_INFO, " val = %d", val);
				break;
			case 'J':
				syslog(LOG_INFO, "Pre val = %d", val);
				syslog(LOG_INFO, "GetElapsedValue(MAIN_HW_COUNTER, val ,eval)");
				GetElapsedValue(MAIN_HW_COUNTER, &val, &eval);
				syslog(LOG_INFO, " val = %d", val);
				syslog(LOG_INFO, " eval = %d", eval);
				break;
			case 'r':
				syslog(LOG_INFO, "GetISRID() Call from Task Context");
				syslog(LOG_INFO, "GetISRID() = %d", GetISRID());
				break;
			case 'p':
				PutAppMode();
				break;
			case 't':
				schedule_table_sample_routine();
				break;
			case 'q':
				ShutdownOS(E_OK);
				break;
			case 'Q':
				ShutdownOS(E_OS_STATE);
				break;
			default:
				/* �嵭�Υ��ޥ�ɰʳ��ξ�硤������Ԥ�ʤ� */
				break;
			}
		}
	}

	/*
	 *  �����ˤϤ��ʤ�
	 */
	syslog(LOG_INFO, "MainTask TERMINATE");
	error_log(TerminateTask());
}   /* TASK( MainTask ) */

/*
 *  �ǹ�ͥ���٥�����
 *
 *  �ƥ������Υץꥨ��ץȳ�ǧ��
 */
TASK(HighPriorityTask)
{
	syslog(LOG_INFO, "HighPriorityTask ACTIVATE");
	error_log(TerminateTask());
}   /* TASK( HighPriorityTask ) */


/*
 *  �Υ�ץꥨ��ץƥ��֥�����
 *
 *  �¹���ϥץꥨ��ץȤ��ʤ����Ȥγ�ǧ��
 */
TASK(NonPriTask)
{
	syslog(LOG_INFO, "NonPriTask ACTIVATE");
	syslog(LOG_INFO, "Call ActivateTask(HighPriorityTask)");
	error_log(ActivateTask(HighPriorityTask));
	syslog(LOG_INFO, "NonPriTask TERMINATE");

	error_log(TerminateTask());
}   /* TASK( NonPriTask ) */


/*
 *  ����¹ԥ�����1
 */
TASK(Task1)
{
	TaskProk(0U);
}   /* TASK( Task1 ) */


/*
 *  ����¹ԥ�����2
 */
TASK(Task2)
{
	TaskProk(1U);
}   /* TASK( Task2 ) */


/*
 *  ����¹ԥ�����3
 */
TASK(Task3)
{
	TaskProk(2U);
}   /* TASK( Task3 ) */


/*
 *  ����¹ԥ�����4
 */
TASK(Task4)
{
	TaskProk(3U);
}   /* TASK( Task4 ) */


/*
 *  ����¹ԥ�����5
 */
TASK(Task5)
{
	TaskProk(4U);
}   /* TASK( Task5 ) */


/*
 *  ����¹ԥ�������������
 *
 *  �ᥤ�󥿥����������Τ��줿���ޥ�ɤ��Ȥν����¹�
 */
static void
TaskProk(uint8 task_no)
{
	uint8 command;          /* ���ޥ������Хåե� */

	/*
	 *  ��������ư������
	 */
	syslog(LOG_INFO, "%s ACTIVATE", task_name_tbl[task_no]);

	/*
	 *  ���ޥ�ɼ¹ԥ롼��
	 */
	while (1) {

		/*
		 *  ���ޥ�ɼ���
		 */
		while (command_tbl[task_no] == '\0') {
		}
		command = command_tbl[task_no];
		command_tbl[task_no] = 0U;

		/*
		 *  ���ޥ��Ƚ��
		 */
		switch (command) {
		case 'A':
			PutTermTsk(task_no);
			break;
		case '!':
		case '"':
		case '#':
		case '$':
		case '%':
			PutChainTsk(task_no, (command - '!'));
			break;
		case 'z':
			PutTaskID();
			break;
		case 'k':
			PutGetTskRes();
			break;
		case 'K':
			PutRelTskRes();
			break;
		case 'i':
			PutGetCntRes();
			break;
		case 'w':
			PutClrEvt(task_no);
			break;
		case 'W':
			PutWaitEvt(task_no);
			break;
		default:
			/* �嵭�Υ��ޥ�ɰʳ��ξ�硤�����ϹԤ�ʤ� */
			break;
		}
	}
}   /* TaskProk */

/*
 *  ���ޥ�ɼ�������
 */
static uint8
GetCommand(void)
{
	uint8 command;          /* ���ޥ�ɼ����Хåե� */

	/*
	 *  ���ޥ�ɤ��������ޤǥ롼��
	 */
	command = '\0';
	do {
		WaitEvent(MainEvt);     /* 10ms�������� */
		ClearEvent(MainEvt);
		RecvPolSerialChar(&command);    /* �����Хåե��ݡ���� */
		if (command == '\n') {
			command = '\0';
		}
	} while (command == '\0');


	return(command);
}   /* GetCommand */

/*
 *  ActivateTask �¹ԡ������Ͻ���
 */
static void
PutActTsk(uint8 task_no)
{
	syslog(LOG_INFO, "Call ActivateTask(%s)", task_name_tbl[task_no]);

	error_log(ActivateTask(task_id_tbl[task_no]));

}   /* PutActTsk	*/

/*
 *  ActivateTask �¹�(NonPriTask)�������Ͻ���
 */
static void
PutActNonPriTsk(void)
{
	syslog(LOG_INFO, "Call ActivateTask(NonPriTask)");

	error_log(ActivateTask(NonPriTask));
}   /* PutActNonPriTsk */

/*
 *  TerminateTask �¹ԡ������Ͻ���
 */
static void
PutTermTsk(uint8 task_no)
{
	StatusType ercd;        /* ���顼������ */

	syslog(LOG_INFO, "%s TERMINATE", task_name_tbl[task_no]);

	ercd = TerminateTask();
	ShutdownOS(ercd);
}

/*
 *  ChainTask �¹ԡ������Ͻ���
 */
static void
PutChainTsk(uint8 from_task_no, uint8 to_task_no)
{
	StatusType ercd;            /* ���顼������ */

	syslog(LOG_INFO, "Call ChainTask(%s)", task_name_tbl[to_task_no]);
	syslog(LOG_INFO, "%s TERMINATE", task_name_tbl[from_task_no]);

	ercd = ChainTask(task_id_tbl[to_task_no]);
	if (ercd == E_OS_LIMIT) {
		syslog(LOG_INFO, "Call TerminateTask()");
		syslog(LOG_INFO, "Because of ChainTask E_OS_LIMIT return");
		ercd = TerminateTask();
	}
	ShutdownOS(ercd);
}   /* PutChainTsk */

/*
 *  Schedule �¹ԡ������Ͻ���
 */
static void
PutSchedule(void)
{
	syslog(LOG_INFO, "Call ActivateTask(HighPriorityTask)");

	error_log(ActivateTask(HighPriorityTask));
	syslog(LOG_INFO, "Call Schedule()");

	error_log(Schedule());
	syslog(LOG_INFO, "Retrun Schedule()");
}   /* PutSchedule	*/

/*
 *  GetTaskID �¹ԡ������Ͻ���
 */
static void
PutTaskID(void)
{
	TaskType task_id;           /* ������ID�����Хåե� */

	error_log(GetTaskID(&task_id));

	syslog(LOG_INFO, "TaskID:%d", task_id);
}   /* PutTaskID	*/

/*
 *  GetTaskState �¹ԡ������Ͻ���
 */
static void
PutTaskState(uint8 task_no)
{
	TaskStateType state;        /* ������ID�����Хåե� */

	error_log(GetTaskState(task_id_tbl[task_no], &state));

	syslog(LOG_INFO, task_name_tbl[task_no]);
	syslog(LOG_INFO, " State:%s", task_state_tbl[state]);
}   /* PutTaskState	*/

/*
 *  DisableAllInterrupts/EnableAllInterrupts �¹ԡ������Ͻ���
 */
static void
PutDisAllInt(void)
{
	syslog(LOG_INFO, "Call DisableAllInterrupts");

	DisableAllInterrupts();

	PutHwCnt3();
	syslog(LOG_INFO, "Call EnableAllInterrupts");

	EnableAllInterrupts();
}   /* PutDisAllInt	*/

/*
 *  SuspendAllInterrupts/ResumeAllInterrupts �¹ԡ������Ͻ���
 */
static void
PutSusAllInt(void)
{
	syslog(LOG_INFO, "Call SuspendAllInterrupts");

	SuspendAllInterrupts();

	PutHwCnt3();
	syslog(LOG_INFO, "Call SuspendAllInterrupts");

	SuspendAllInterrupts();

	PutHwCnt3();
	syslog(LOG_INFO, "Call ResumeAllInterrupts");

	ResumeAllInterrupts();

	PutHwCnt3();
	syslog(LOG_INFO, "Call ResumeAllInterrupts");

	ResumeAllInterrupts();
}   /* PutSusAllInt	*/

/*
 *  SuspendOSInterrupts/ResumeOSInterrupts �¹ԡ������Ͻ���
 */
static void
PutSusOSInt(void)
{
	syslog(LOG_INFO, "Call SuspendOSInterrupts");

	SuspendOSInterrupts();

	PutHwCnt3();
	syslog(LOG_INFO, "Call SuspendOSInterrupts");

	SuspendOSInterrupts();

	PutHwCnt3();
	syslog(LOG_INFO, "Call SuspendAllInterrupts");

	SuspendAllInterrupts();

	PutHwCnt3();
	syslog(LOG_INFO, "Call ResumeAllInterrupts");

	ResumeAllInterrupts();

	PutHwCnt3();
	syslog(LOG_INFO, "Call ResumeOSInterrupts");

	ResumeOSInterrupts();

	PutHwCnt3();
	syslog(LOG_INFO, "Call ResumeOSInterrupts");

	ResumeOSInterrupts();
}   /* PutSusOSInt */

/*
 *  �����ư��ƥ�����HW�������ͤΥ����Ͻ���
 */
static void
PutHwCnt3(void)
{
	uint8	isr1_cnt = 0U;      /* C1ISR ��������ͼ����Хåե� */
	uint8	isr2_cnt = 0U;      /* C2ISR ��������ͼ����Хåե� */
	uint8	cnt;                /* ���ϲ�������� */

	for (cnt = 0U; cnt < 3U; cnt++) {
		GetHwCnt(&isr1_cnt, &isr2_cnt);
		syslog(LOG_INFO, "C1ISR Cnt:%d, C2ISR Cnt:%d",
			   isr1_cnt, isr2_cnt);
	}
}   /* PutHwCnt3 */

/*
 *  GetResource/ReleaseResource �¹�(�����󥿥꥽����)�������Ͻ���
 */
static void
PutGetCntRes(void)
{
	syslog(LOG_INFO, "Call GetResource(CntRes)");
	error_log(GetResource(CntRes));

	PutHwCnt3();
	syslog(LOG_INFO, "Call ReleaseResource(CntRes)");

	error_log(ReleaseResource(CntRes));
}   /* PutGetCntRes	*/

/*
 *  GetResource �¹�(��������٥�)�������Ͻ���
 */
static void
PutGetTskRes(void)
{
	syslog(LOG_INFO, "Call GetResource(TskLevelRes)");

	error_log(GetResource(TskLevelRes));
}   /* PutGetTskRes */

/*
 *  ReleaseResource �¹�(��������٥�)�������Ͻ���
 */
static void
PutRelTskRes(void)
{
	syslog(LOG_INFO, "Call ReleaseResource(TskLevelRes)");

	error_log(ReleaseResource(TskLevelRes));
}

/*
 *  SetEvent �¹ԡ������Ͻ���
 */
static void
PutSetEvt(uint8 task_no)
{
	syslog(LOG_INFO, "Call SetEvent(%s, %s)",
		   task_name_tbl[task_no], event_name_tbl[task_no]);

	error_log(SetEvent(task_id_tbl[task_no], event_mask_tbl[task_no]));
}   /* PutSetEvt */

/*
 *  ClearEvent �¹ԡ������Ͻ���
 */
static void
PutClrEvt(uint8 task_no)
{
	syslog(LOG_INFO, "Call ClearEvent(%s)", event_name_tbl[task_no]);

	error_log(ClearEvent(event_mask_tbl[task_no]));
}   /* PutClrEvt */

/*
 *  GetEvent �¹ԡ������Ͻ���
 */
static void
PutGetEvt(uint8 task_no)
{
	EventMaskType mask;             /* ���٥�ȥޥ��������Хåե� */

	error_log(GetEvent(task_id_tbl[task_no], &mask));

	syslog(LOG_INFO, "%s Event Mask:0x%x", task_name_tbl[task_no], mask);
}   /* PutGetEvt */

/*
 *  WaitEvent �¹ԡ������Ͻ���
 */
static void
PutWaitEvt(uint8 task_no)
{
	syslog(LOG_INFO, "Call WaitEvent(%s)", event_name_tbl[task_no]);

	error_log(WaitEvent(event_mask_tbl[task_no]));
	syslog(LOG_INFO, "Return WaitEvent(%s)", event_name_tbl[task_no]);
}   /* PutWaitEvt */

/*
 *  GetAlarmBase �¹ԡ������Ͻ���
 */
static void
PutArmBase(void)
{
	AlarmBaseType info;             /* ���顼��١�����������Хåե� */

	error_log(GetAlarmBase(MainCycArm, &info));

	syslog(LOG_INFO, "MainCycArm Base:");
	syslog(LOG_INFO, "\tMAXALLOWEDVALUE=%d", info.maxallowedvalue);
	syslog(LOG_INFO, "\tTICKSPERBASE=%d", info.ticksperbase);
	syslog(LOG_INFO, "\tMINCYCLE=%d", info.mincycle);
}   /* PutArmBase */

/*
 *  PutArmTick �¹ԡ������Ͻ���
 */
static void
PutArmTick(void)
{
	TickType tick;              /* �Ĥ�ƥ��å������Хåե� */

	error_log(GetAlarm(MainCycArm, &tick));

	syslog(LOG_INFO, "MainCycArm Tick:%d", tick);
}   /* PutArmTick */

/*
 *  SetRelAlarm �¹ԡ������Ͻ���
 */
static void
PutSetRel(uint8 alarm_no, uint8 tick_no, uint8 cycle_no)
{
	syslog(LOG_INFO, "Call SetRelAlarm(%s, %d, %d)",
		   alarm_name_tbl[alarm_no], tick_tbl[tick_no], cycle_tbl[cycle_no]);

	error_log(SetRelAlarm(alarm_id_tbl[alarm_no],
						  tick_tbl[tick_no], cycle_tbl[cycle_no]));
}   /* PutSetRel	*/

/*
 *  SetAbsAlarm �¹ԡ������Ͻ���
 */
static void
PutSetAbs(uint8 alarm_no, uint8 tick_no, uint8 cycle_no)
{
	syslog(LOG_INFO, "Call SetAbsAlarm(%s, %d, %d)",
		   alarm_name_tbl[alarm_no], tick_tbl[tick_no], cycle_tbl[cycle_no]);

	error_log(SetAbsAlarm(alarm_id_tbl[alarm_no],
						  tick_tbl[tick_no], cycle_tbl[cycle_no]));
}   /* PutSetAbs */

/*
 *  CancelAlarm �¹ԡ������Ͻ���
 */
static void
PutCanArm(void)
{
	syslog(LOG_INFO, "Call CancelAlarm(CallBackArm)");

	error_log(CancelAlarm(CallBackArm));
}   /* PutCanArm */

/*
 *  GetActiveApplicationMode �¹ԡ������Ͻ���
 */
static void
PutAppMode(void)
{
	switch (GetActiveApplicationMode()) {
	case AppMode1:
		syslog(LOG_INFO, "ActiveApplicationMode:AppMode1");
		break;
	case AppMode2:
		syslog(LOG_INFO, "ActiveApplicationMode:AppMode2");
		break;
	case AppMode3:
		syslog(LOG_INFO, "ActiveApplicationMode:AppMode3");
		break;
	default:
		syslog(LOG_INFO, "ActiveApplicationMode:Non");
		break;
	}
}   /* PutAppMode */


/*
 *  ���顼�եå��롼����
 */
#ifdef CFG_USE_ERRORHOOK
void
ErrorHook(StatusType Error)
{
	/*
	 *  ���顼�װ����ȤΥѥ�᡼��������
	 */
	switch (OSErrorGetServiceId()) {
	case OSServiceId_ActivateTask:
		syslog(LOG_INFO, "Error:%s=ActivateTask(%d)", atk2_strerror(Error), OSError_ActivateTask_TaskID());
		break;
	case OSServiceId_TerminateTask:
		syslog(LOG_INFO, "Error:%s=TerminateTask()", atk2_strerror(Error));
		break;
	case OSServiceId_ChainTask:
		syslog(LOG_INFO, "Error:%s=ChainTask(%d)", atk2_strerror(Error), OSError_ChainTask_TaskID());
		break;
	case OSServiceId_Schedule:
		syslog(LOG_INFO, "Error:%s=Schedule()", atk2_strerror(Error));
		break;
	case OSServiceId_GetTaskID:
		syslog(LOG_INFO, "Error:%s=GetTaskID(0x%p)", atk2_strerror(Error), OSError_GetTaskID_TaskID());
		break;
	case OSServiceId_GetTaskState:
		syslog(LOG_INFO, "Error:%s=GetTaskState(%d, 0x%p)", atk2_strerror(Error),
			   OSError_GetTaskState_TaskID(), OSError_GetTaskState_State());
		break;
	case OSServiceId_EnableAllInterrupts:
		syslog(LOG_INFO, "Error:%s=EnableAllInterrupts()", atk2_strerror(Error));
		break;
	case OSServiceId_DisableAllInterrupts:
		syslog(LOG_INFO, "Error:%s=DisableAllInterrupts()", atk2_strerror(Error));
		break;
	case OSServiceId_ResumeAllInterrupts:
		syslog(LOG_INFO, "Error:%s=ResumeAllInterrupts()", atk2_strerror(Error));
		break;
	case OSServiceId_SuspendAllInterrupts:
		syslog(LOG_INFO, "Error:%s=SuspendAllInterrupts()", atk2_strerror(Error));
		break;
	case OSServiceId_ResumeOSInterrupts:
		syslog(LOG_INFO, "Error:%s=ResumeOSInterrupts()", atk2_strerror(Error));
		break;
	case OSServiceId_SuspendOSInterrupts:
		syslog(LOG_INFO, "Error:%s=SuspendOSInterrupts()", atk2_strerror(Error));
		break;
	case OSServiceId_GetISRID:
		syslog(LOG_INFO, "Error:%s=GetISRID()", atk2_strerror(Error));
		break;
	case OSServiceId_GetResource:
		syslog(LOG_INFO, "Error:%s=GetResource(%d)", atk2_strerror(Error), OSError_GetResource_ResID());
		break;
	case OSServiceId_ReleaseResource:
		syslog(LOG_INFO, "Error:%s=ReleaseResource(%d)", atk2_strerror(Error), OSError_ReleaseResource_ResID());
		break;
	case OSServiceId_SetEvent:
		syslog(LOG_INFO, "Error:%s=SetEvent(%d, 0x%x)", atk2_strerror(Error),
			   OSError_SetEvent_TaskID(), OSError_SetEvent_Mask());
		break;
	case OSServiceId_ClearEvent:
		syslog(LOG_INFO, "Error:%s=ClearEvent(0x%x)", atk2_strerror(Error), OSError_ClearEvent_Mask());
		break;
	case OSServiceId_GetEvent:
		syslog(LOG_INFO, "Error:%s=GetEvent(%d, 0x%p)", atk2_strerror(Error),
			   OSError_GetEvent_TaskID(), OSError_GetEvent_Event());
		break;
	case OSServiceId_WaitEvent:
		syslog(LOG_INFO, "Error:%s=WaitEvent(0x%x)", atk2_strerror(Error), OSError_WaitEvent_Mask());
		break;
	case OSServiceId_GetAlarmBase:
		syslog(LOG_INFO, "Error:%s=GetAlarmBase(0x%p)", atk2_strerror(Error), OSError_GetAlarmBase_AlarmID());
		break;
	case OSServiceId_GetAlarm:
		syslog(LOG_INFO, "Error:%s=GetAlarm(%d, 0x%p)", atk2_strerror(Error),
			   OSError_GetAlarm_AlarmID(), OSError_GetAlarm_Tick());
		break;
	case OSServiceId_SetRelAlarm:
		syslog(LOG_INFO, "Error:%s=SetRelAlarm(%d, %d, %d)", atk2_strerror(Error),
			   OSError_SetRelAlarm_AlarmID(), OSError_SetRelAlarm_increment(), OSError_SetRelAlarm_cycle());
		break;
	case OSServiceId_SetAbsAlarm:
		syslog(LOG_INFO, "Error:%s=SetAbsAlarm(%d, %d, %d)", atk2_strerror(Error),
			   OSError_SetAbsAlarm_AlarmID(), OSError_SetAbsAlarm_start(), OSError_SetAbsAlarm_cycle());
		break;
	case OSServiceId_CancelAlarm:
		syslog(LOG_INFO, "Error:%s=CancelAlarm(%d)", atk2_strerror(Error), OSError_CancelAlarm_AlarmID());
		break;
	case OSServiceId_StartScheduleTableRel:
		syslog(LOG_INFO, "Error:%s=StartScheduleTableRel(%d, %d)", atk2_strerror(Error),
			   OSError_StartScheduleTableRel_ScheduleTableID(), OSError_StartScheduleTableRel_Offset());
		break;
	case OSServiceId_StartScheduleTableAbs:
		syslog(LOG_INFO, "Error:%s=StartScheduleTableAbs(%d, %d)", atk2_strerror(Error),
			   OSError_StartScheduleTableAbs_ScheduleTableID(), OSError_StartScheduleTableAbs_Start());
		break;
	case OSServiceId_StopScheduleTable:
		syslog(LOG_INFO, "Error:%s=StopScheduleTable(%d)", atk2_strerror(Error), OSError_StopScheduleTable_ScheduleTableID());
		break;
	case OSServiceId_NextScheduleTable:
		syslog(LOG_INFO, "Error:%s=NextScheduleTable(%d, %d)", atk2_strerror(Error),
			   OSError_NextScheduleTable_ScheduleTableID_From(), OSError_NextScheduleTable_ScheduleTableID_To());
		break;
	case OSServiceId_GetScheduleTableStatus:
		syslog(LOG_INFO, "Error:%s=GetScheduleTableStatus(%d, 0x%p)", atk2_strerror(Error),
			   OSError_GetScheduleTableStatus_ScheduleTableID(), OSError_GetScheduleTableStatus_ScheduleStatus());
		break;
	case OSServiceId_GetActiveApplicationMode:
		syslog(LOG_INFO, "Error:%s=GetActiveApplicationMode()", atk2_strerror(Error));
		break;
	case OSServiceId_StartOS:
		syslog(LOG_INFO, "Error:%s=StartOS()", atk2_strerror(Error));
		break;
	case OSServiceId_ShutdownOS:
		syslog(LOG_INFO, "Error:%s=ShutdownOS()", atk2_strerror(Error));
		break;
	case OSServiceId_IncrementCounter:
		syslog(LOG_INFO, "Error:%s=IncrementCounter(%d)", atk2_strerror(Error), OSError_IncrementCounter_CounterID());
		break;
	case OSServiceId_TaskMissingEnd:
		syslog(LOG_INFO, "Error:%s=MissingEnd()", atk2_strerror(Error));
		break;
	default:
		syslog(LOG_INFO, "Error:%s=UnKnownFunc()", atk2_strerror(Error));
		break;
	}

}   /* ErrorHook */
#endif /* CFG_USE_ERRORHOOK */

/*
 *  �ץ쥿�����եå��롼����
 *
 *  ���롼�����ƽФ�
 */
#ifdef CFG_USE_PRETASKHOOK
void
PreTaskHook(void)
{
}   /* PreTaskHook */
#endif /* CFG_USE_PRETASKHOOK */

/*
 *  �ݥ��ȥ������եå��롼����
 *
 *  ���롼�����ƽФ�
 */
#ifdef CFG_USE_POSTTASKHOOK
void
PostTaskHook(void)
{
}   /* PostTaskHook */
#endif /* CFG_USE_POSTTASKHOOK */

/*
 *  �������ȥ��åץեå��롼����
 */
#ifdef CFG_USE_STARTUPHOOK
#ifdef TOPPERS_ENABLE_SYS_TIMER
extern void target_timer_initialize(void);
#endif /* TOPPERS_ENABLE_SYS_TIMER */

void
StartupHook(void)
{
#ifdef TOPPERS_ENABLE_SYS_TIMER
	target_timer_initialize();
#endif /* TOPPERS_ENABLE_SYS_TIMER */
	syslog_initialize();
	syslog_msk_log(LOG_UPTO(LOG_INFO));
	InitSerial();
	print_banner();
}   /* StartupHook */
#endif /* CFG_USE_STARTUPHOOK */

/*
 *  ����åȥ�����եå��롼����
 */
#ifdef CFG_USE_SHUTDOWNHOOK
#ifdef TOPPERS_ENABLE_SYS_TIMER
extern void target_timer_terminate(void);
#endif /* TOPPERS_ENABLE_SYS_TIMER */

void
ShutdownHook(StatusType Error)
{
	/* ��λ������ */
	syslog(LOG_INFO, "");
	syslog(LOG_INFO, "Sample System ShutDown");
	syslog(LOG_INFO, "ShutDownCode:%s", atk2_strerror(Error));
	syslog(LOG_INFO, "");

	if (Error == E_OS_SYS_ASSERT_FATAL) {
		syslog(LOG_INFO, "fatal_file_name:%s", fatal_file_name);
		syslog(LOG_INFO, "fatal_line_num:%d", fatal_line_num);
	}

#ifdef TOPPERS_ENABLE_SYS_TIMER
	target_timer_terminate();
#endif /* TOPPERS_ENABLE_SYS_TIMER */
	TermSerial();

}   /* ShutdownHook */
#endif /* CFG_USE_SHUTDOWNHOOK */

/*
 *  �ץ�ƥ������եå��롼����
 */
#ifdef CFG_USE_PROTECTIONHOOK
ProtectionReturnType
ProtectionHook(StatusType FatalError)
{
	StatusType ercd;

	syslog(LOG_INFO, "");
	syslog(LOG_INFO, "ProtectionHook");

	if (FatalError == E_OS_STACKFAULT) {
		syslog(LOG_INFO, "E_OS_STACKFAULT");
		ercd = PRO_SHUTDOWN;
	}
	else if (FatalError == E_OS_PROTECTION_EXCEPTION) {
		syslog(LOG_INFO, "E_OS_PROTECTION_EXCEPTION");
		ercd = PRO_IGNORE;
	}
	else {
		ercd = PRO_SHUTDOWN;
	}

	return(ercd);
}
#endif /* CFG_USE_PROTECTIONHOOK */

/*
 *  �����ƥॿ���ޤˤ�륢�顼�ॳ����Хå�
 */
ALARMCALLBACK(SysTimerAlmCb)
{
	/*
	 *  ������Хå��¹ԥ�����
	 */
	syslog(LOG_INFO, "CallBackArm Expire");

}   /* ALARMCALLBACK(SysTimerAlmCb) */

/*
 *  IncrementCounter��ǧ�ѥ��顼�ॳ����Хå�
 */
ALARMCALLBACK(SampleAlmCb)
{
	/*
	 *  ������Хå��¹ԥ�����
	 */
	syslog(LOG_INFO, "SampleArm Expire");

}   /* ALARMCALLBACK( SampleAlmCb ) */

/*
 *  IncrementCounter��ǧ�ѥ��顼�ॳ����Хå�
 */
ALARMCALLBACK(SampleAlmCb2)
{
	/*
	 *  ������Хå��¹ԥ�����
	 */
	syslog(LOG_INFO, "SampleArm2 Expire");

}   /* ALARMCALLBACK( SampleAlmCb2 ) */

/*
 *  �������塼��ơ��֥�ƥ����ѥᥤ��롼��
 *
 *  �桼�����ޥ�ɤμ����ȡ����ޥ�ɤ��Ȥν����¹�
 */
static void
schedule_table_sample_routine(void)
{
	uint8					command;                /* ���ޥ�ɥХåե� */
	ScheduleTableType		scheduletable_id;       /* ���ޥ�ɰ����Хåե� */
	ScheduleTableStatusType	status;                 /* �������塼����ְ��� */
	TickType				val;                    /* �����󥿤θ����� */
	uint8					flag = FALSE;           /* �꥿���󤹤뤫Ƚ�ꤹ�뤿��Υե饰 */

	syslog(LOG_INFO, "\t[ schedule table sample routine IN, press 't' OUT ]");
	syslog(LOG_INFO, "");

	scheduletable_id = scheduletable1;
	/*
	 *  ���ޥ�ɼ¹ԥ롼��
	 */
	while (1) {

		WaitEvent(MainEvt);     /* 10ms�κ�Ȼ����Ԥ� */
		ClearEvent(MainEvt);

		/*
		 *  ���ϥ��ޥ�ɼ���
		 */
		syslog(LOG_INFO, "Input Command:");
		command = GetCommand();
		syslog(LOG_INFO, "%c", command);

		/*
		 *  ���ޥ��Ƚ��
		 */
		switch (command) {
		case '1':
			scheduletable_id = scheduletable1;
			break;
		case '2':
			scheduletable_id = scheduletable2;
			break;
		case 'i':
			IncrementCounter(SchtblSampleCnt);
			val = 0U;
			GetCounterValue(SchtblSampleCnt, &val);
			if ((val % 5U) == 0U) {
				syslog(LOG_INFO, "\tGetCounterValue(SchtblSampleCnt ) = %d", val);
			}
			break;
		case 's':
			syslog(LOG_INFO, "\tStartScheduleTableRel(scheduletable%d, 5)", scheduletable_id + 1U);
			error_log(StartScheduleTableRel(scheduletable_id, 5U));
			break;
		case 'S':
			syslog(LOG_INFO, "\tStartScheduleTableAbs(scheduletable%d, 5)", scheduletable_id + 1U);
			error_log(StartScheduleTableAbs(scheduletable_id, 5U));
			break;
		case 'f':
			syslog(LOG_INFO, "\tStopScheduleTable(scheduletable%d)", scheduletable_id + 1U);
			error_log(StopScheduleTable(scheduletable_id));
			break;
		case 'n':
			syslog(LOG_INFO, "\tNextScheduleTable(scheduletable%d, scheduletable%d)", scheduletable_id + 1U, scheduletable2 + 1U);
			error_log(NextScheduleTable(scheduletable_id, scheduletable2));
			break;
		case 'N':
			syslog(LOG_INFO, "\tNextScheduleTable(scheduletable%d, scheduletable%d)", scheduletable_id + 1U, scheduletable1 + 1U);
			error_log(NextScheduleTable(scheduletable_id, scheduletable1));
			break;
		case 'g':
			status = 0U;
			syslog(LOG_INFO, "\tGetScheduleTableStatus(scheduletable%d, status)", scheduletable_id + 1U);
			error_log(GetScheduleTableStatus(scheduletable_id, &status));
			syslog(LOG_INFO, "\tstatus = %d", status);
			break;
		case 't':
			syslog(LOG_INFO, "\t[ schedule table sample routine OUT, press 't' IN ]");
			flag = TRUE;
			break;
		case 'q':
			ShutdownOS(E_OK);
			break;
		case 'Q':
			ShutdownOS(E_OS_STATE);
			break;
		default:
			/* ���ޥ�ɤ��嵭�Υ������ʳ��ʤ�����ϹԤ�ʤ� */
			break;
		}
		/*  �ե饰��Ω�äƤ�����硤�꥿���󤹤�  */
		if (flag == TRUE) {
			return;
		}
	}
}   /* schedule_table_sample_routine */

/*
 *  �������塼��ơ��֥��ǧ�ѥ�����6
 */
TASK(Task6)
{
	/*
	 *  ��������ư������
	 */
	syslog(LOG_INFO, "Task6 ACTIVATE");
	WaitEvent(T6Evt);
	syslog(LOG_INFO, "Task6 FINISH");
	TerminateTask();
}   /* TASK( Task6 ) */


/*
 *  �������塼��ơ��֥��ǧ�ѥ�����7
 */
TASK(Task7)
{
	/*
	 *  ��������ư������
	 */
	syslog(LOG_INFO, "Task7 ACTIVATE");
	WaitEvent(T7Evt);
	syslog(LOG_INFO, "Task7 FINISH");
	TerminateTask();
}   /* TASK( Task7 ) */


/*
 *  �������塼��ơ��֥��ǧ�ѥ�����8
 */
TASK(Task8)
{
	/*
	 *  ��������ư������
	 */
	syslog(LOG_INFO, "Task8 ACTIVATE");
	WaitEvent(T8Evt);
	syslog(LOG_INFO, "Task8 FINISH");
	TerminateTask();
}   /* TASK( Task8 ) */
