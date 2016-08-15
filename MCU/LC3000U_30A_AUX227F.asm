;***********************************************************
;*  ������ƣ�LC3000U_30A����MCU��س���                   *
;*  �ļ����ƣ�LC3000U_30A_AUX227E.asm                      *
;*  ����ʱ�䣺2016.07                                      *
;*  Ӳ���汾��LC3000U_30A                                  *
;*  ����汾��2.2.7���������                              *
;*  ��    �ߣ�Faust Wang                                   *
;*  EMail��   13825655055@126.com                          *
;***********************************************************



;===========================================================
;Ӳ��������
;-----------------------------------------------------------
;1.����MCU�� STC15F2K60S2
;2.����ģ�飺
;3.��    �룺
;4.��    ����
;5.��    Դ��
;===========================================================
;���������
;-----------------------------------------------------------
;4.24M����
;3.����1,�Զ���Э��,N,8,1,9600;�����ʷ�����Ϊ��ʱ��2,����Ƶ
;2.��ʱ��1Ϊ�������,����Ƶ;
;1.��ʱ��0Ϊͨ�ö�ʱ��,��Ƶ;
;===========================================================



;-----------------------------------------------------------
;227C�汾,20160704���罻���Žܻ����ԣ�
;1.�յ�����2ʱ���粨��1δ�������8F 00 00 00 00
;2.���50�����ϴ�����
;3.���������ʱ�ϴ�����ʱ
;4.��ԭ����ȡ��ǿֵ�������Ϊ�������в�ѯ��־λģʽ
;5.�ҵ�������ϴ�һ��AUֵ,����Ϊ��������
;6.��ϸ��Ѱ�����


;Դ���ݳ���4,
;�ҵ��½��غ󣬻��˼���,�����˲���


;***********************************************************
;���¼�¼
;-----------------------------------------------------------
;-----------------------------------------------------------
;��Ŀ:���Ӽ�Ȩ����
;ʱ��:2016-07-24
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:�ٵ�ʱ����������8
;ʱ��:2016-07-11
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:DDC112��������ݼ�ȥ4096
;ʱ��:2016-07-03
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:DDC112����ʽ�汾,Դ��216B��226B
;ʱ��:2016-07-03
;����:Faust Wang
;===========================================================

;-----------------------------------------------------------
;-----------------------------------------------------------
;��Ŀ:�ڽӽ�����ȡ����,�����ӵڶ�������˲�
;ʱ��:2016-07-03
;����:Faust Wang
;;-----------------------------------------------------------
;��Ŀ:��ѡ������Ϊ:1ms,1/2�ֶ�,768ǰ��ֵ,����ǰ�������4�ֽ�
;ʱ��:2016-07-02
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:�Ľ������ģʽ,��������Ѱ�Ҽ�����ߵ�ķ���
;ʱ��:2016-07-02
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:������ʱ,���������ݸ�ʽ��Ϊ���Բ���
;ʱ��:2016-06-29
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:���������ı�ģʽ,˫����ʱҲ����Ҫ���³�ʼ��
;ʱ��:2016-06-29
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:�Ż��޸Ĳ���ʱ�Ļ�Ӧģʽ��
;     1.���İ�ÿ�ζ����Ͳ���1�Ͳ���2,���20ms
;     2.MCU���յ�2����������ʱ,�Ż�Ӧ84 00 00 00 00
;     3.���İ��ղ�����Ӧ,��ʱ�ط�;
;ʱ��:2016-06-28
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:����ż�������ĸı䲨����ִ�е�����
;ʱ��:2016-06-12
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:�����ϴ�����ͨ�����ݲ�һ�µ����
;     �յ�ת��ָ������ʱ,��ʱ50������ִ�У�Ȼ���ٷ�������,�Աܿ��ϴ�����ʱ���жϸ���
;ʱ��:2016-05-11
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:���ٶ�ȡ��ǰAUֵʱ���Ա�ӿ��ϴ��ٶ�
;ʱ��:2016-05-2
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:������ʱ,�޸Ĳ���λ�ò������,ֱ��ȥ�µ�λ��
;ʱ��:2016-04-30
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:�汾��Ϊ214
;     ������ʱ,���50�����ϴ�һ��
;     ˫����ʱ,����ĳ���ֻ�ϴ�һ��
;ʱ��:2016-04-29
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:�ӿ�˫�����ڶ��ٶ�
;ʱ��:2016-03-21
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:�Ľ��ظ��Ծ���,ÿ�ν���1������,���˺����2������
;ʱ��:2016-03-21
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:DDC101�汾��30A�Ļ����汾��
;ʱ��:2016-03-06
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:1.������30AӲ���汾
;     2.���ӷֿ�MCU����ģʽѡ���ⲿ���ߣ�
;ʱ��:2016-03-05
;����:Faust Wang
;===========================================================
;-----------------------------------------------------------
;��Ŀ:���Ӳ���ѡ��ͻ��ֳ���ѡ��
;ʱ��:2015-12-27
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:����ϴ��ٶ�
;ʱ��:2015-12-27
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:���ơ�����ģʽ���͡��Զ�ģʽ��
;ʱ��:2015-12-23
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:����ͨ�������붨��,�汾��λV0.2.6
;ʱ��:2015-12-20
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:�����Ϊ24MHz
;ʱ��:2015-11-23
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:���Ӵ���������˲�
;ʱ��:2015-11-08
;����:Faust Wang
;-----------------------------------------------------------
;��Ŀ:���Ӳ���������ٻ������
;ʱ��:2015-11-08
;����:Faust Wang
;-----------------------------------------------------------
;===========================================================
;===========================================================
;STC11 Series SFR
;-----------------------------------------------------------
P0       EQU    080h;
P1       EQU    090h;
P2       EQU    0A0h;
P3       EQU    0B0h;
P4       EQU    0C0H;
PSW      EQU    0D0h;
ACC      EQU    0E0h;
B        EQU    0F0h;
SP       EQU    081h;
DPL      EQU    082h;
DPH      EQU    083h;
PCON     EQU    087h;
TCON     EQU    088h;
TMOD     EQU    089h;
TL0      EQU    08Ah;
TL1      EQU    08Bh;
TH0      EQU    08Ch;
TH1      EQU    08Dh;
SCON     EQU    098h;
SBUF     EQU    099h;
;S2BUF    EQU    09BH;
SADDR    EQU    0A9h;
SADEN    EQU    0B9h;
TL2      EQU    0CCh;
TH2      EQU    0CDh;
DEECON   EQU    0F1h;
DEEDAT   EQU    0F2h;
DEEADR   EQU    0F3h;

IP1      EQU    0F8h;
IP1H     EQU    0F7h;

T2L      EQU    0D7H;
T2H      EQU    0D6H;
;-----------------------------
P_SW1    EQU    0A2H
P_SW2    EQU    0BAH
AUXR     EQU    08EH; T0x12 T1x12 UART_M0x6 BRTR S2SMOD BRTx12 EXTRAM S1BRS  0000,0000
AUXR1    EQU    0A2H;   -   PCA_P4 SPI_P4  S2_P4  GF2    ADRJ   -    DPS  0000,0000
                      ;PCA_P4: 0,ȱʡPCA ��P1��;  
                      ;        1,PCA/PWM ��P1���л���P4��;
                      ;          ECI ��P1.2�л���P4.1�ڣ�
                      ;          PCA0/PWM0 ��P1.3�л���P4.2��
                      ;          PCA1/PWM1 ��P1.4�л���P4.3��
                      ;SPI_P4: 0, ȱʡSPI ��P1��
                      ;        1,SPI ��P1���л���P4 ��;
                      ;          SPICLK ��P1.7 �л���P4.3��
                      ;          MISO ��P1.6�л���P4.2��
                      ;          MOSI ��P1.5�л���P4.1��
                      ;          SS ��P1.4 �л���P4.0��
                      ;S2_P4:  0, ȱʡUART2 ��P1��
                      ;        1��UART2 ��P1���л���P4��;
                      ;           TxD2 ��P1.3 �л���P4.3��
                      ;           RxD2 ��P1.2 �л���P4.2��
                      ;GF2: ͨ�ñ�־λ

                      ;ADRJ:   0,10 λA/D ת������ĸ�8 λ����ADC_RES �Ĵ���, ��2 λ����ADC_RESL �Ĵ���
                      ;        1,10 λA/D ת����������2 λ����ADC_RES �Ĵ����ĵ�2 λ, ��8 λ����ADC_RESL �Ĵ���

                      ;DPS:    0,ʹ��ȱʡ����ָ��DPTR0
                      ;        1,ʹ����һ������ָ��DPTR1

WAKE_CLKO  EQU  08FH; PCAWAKEUP  RXD_PIN_IE  T1_PIN_IE  T0_PIN_IE  LVD_WAKE  _  T1CLKO  T0CLKO  0000,0000B
    ;b7 - PCAWAKEUP : PCA �жϿɻ��� powerdown��
    ;b6 - RXD_PIN_IE : �� P3.0(RXD) �½�����λ RI ʱ�ɻ��� powerdown(�������Ӧ�ж�)��
    ;b5 - T1_PIN_IE : �� T1 ���½�����λ T1 �жϱ�־ʱ�ɻ��� powerdown(�������Ӧ�ж�)��
    ;b4 - T0_PIN_IE : �� T0 ���½�����λ T0 �жϱ�־ʱ�ɻ��� powerdown(�������Ӧ�ж�)��
    ;b3 - LVD_WAKE : �� CMPIN �ŵ͵�ƽ��λ LVD �жϱ�־ʱ�ɻ��� powerdown(�������Ӧ�ж�)��
    ;b2 - 
    ;b1 - T1CLKO : ���� T1CKO(P3.5) ����� T1 ������壬Fck1 = 1/2 T1 �����
    ;b0 - T0CLKO : ���� T0CKO(P3.4) ����� T0 ������壬Fck0 = 1/2 T1 �����

CLK_DIV    EQU  097H; //Clock Divder          -     -      -       -     -  CLKS2 CLKS1 CLKS0 xxxx,x000
BUS_SPEED  EQU  0A1H; //Stretch register      -     -    ALES1   ALES0   -   RWS2  RWS1  RWS0 xx10,x011
   ;ALES1 and ALES0:
     ;00 : The P0 address setup time and hold time to ALE negative edge is one clock cycle
     ;01 : The P0 address setup time and hold time to ALE negative edge is two clock cycles.
     ;10 : The P0 address setup time and hold time to ALE negative edge is three clock cycles. (default)
     ;11 : The P0 address setup time and hold time to ALE negative edge is four clock cycles.
   ;RWS2,RWS1,RWS0:
     ;000 : The MOVX read/write pulse is 1 clock cycle. 
     ;001 : The MOVX read/write pulse is 2 clock cycles.
     ;010 : The MOVX read/write pulse is 3 clock cycles.
     ;011 : The MOVX read/write pulse is 4 clock cycles. (default)
     ;100 : The MOVX read/write pulse is 5 clock cycles.
     ;101 : The MOVX read/write pulse is 6 clock cycles.
     ;110 : The MOVX read/write pulse is 7 clock cycles.
     ;111 : The MOVX read/write pulse is 8 clock cycles.

IE       EQU    0A8H;  //�жϿ��ƼĴ���    EA  ELVD  EADC   ES   ET1  EX1  ET0  EX0  0x00,0000
IE2      EQU    0AFH;     -   -   -  -   -  -  ESPI  ES2  0000,0000B
    EA   BIT    IE.7;
    ELVD BIT    IE.6; //��ѹ����ж�����λ
    EADC BIT    IE.5; //ADC �ж�����λ
    ES   BIT    IE.4;
    ET1  BIT    IE.3;
    EX1  BIT    IE.2;
    ET0  BIT    IE.1;
    EX0  BIT    IE.0;

IP0      EQU    0B8H; //�ж����ȼ���λ PPCA  PLVD  PADC  PS   PT1  PX1  PT0  PX0   0000,0000
IPH0     EQU    0B7H; //�ж����ȼ���λ PPCAH PLVDH PADCH PSH PT1H PX1H PT0H PX0H   0000,0000
IP2      EQU    0B5H; //               -     -     -     -   -    -    PSPI PS2    xxxx,xx00
IPH2     EQU    0B6H; //               -     -     -     -   -    -    PSPIH PS2H  xxxx,xx00
    PPCA BIT    IP0.7;  //PCA ģ���ж����ȼ�
    PLVD BIT    IP0.6;  //��ѹ����ж����ȼ�
    PADC BIT    IP0.5;  //ADC �ж����ȼ�
    PS   BIT    IP0.4;
    PT1  BIT    IP0.3;
    PX1  BIT    IP0.2;
    PT0  BIT    IP0.1;
    PX0  BIT    IP0.0;

P0M0     EQU    094H; //          0000,0000
P0M1     EQU    093H; //          0000,0000
P1M0     EQU    092H; //          0000,0000
P1M1     EQU    091H; //          0000,0000
P2M0     EQU    096H; //          0000,0000
P2M1     EQU    095H; //          0000,0000
P3M0     EQU    0B2H; //          0000,0000
P3M1     EQU    0B1H; //          0000,0000
P4M0     EQU    0B4H; //          0000,0000
P4M1     EQU    0B3H; //          0000,0000
P5M0     EQU    0CAH; //          0000,0000
P5M1     EQU    0C9H; //          0000,0000

P1ASF    EQU    09DH; //P1 analog special function
P4SW     EQU    0BBH; //Port-4 switch	  -  LVD_P4.6 ALE_P4.5 NA_P4.4  -   -   -   -	  x000,xxxx
P5       EQU    0C8H; //8 bitPort5      -    -    -    -   P5.3  P5.2  P5.1  P5.0     xxxx,1111

S2CON    EQU    09AH; //S2 Control S2SM0 S2SM1 S2SM2 S2REN S2TB8 S2RB8 S2TI S2RI      00000000B
S2BUF    EQU    09BH; //S2 Serial Buffer                                              xxxx,xxxx
BRT      EQU    09CH; //S2 Baud-Rate Timer                                            0000,0000

WDT_CONTR EQU   0C1H; //Watch-Dog-Timer Control register
   ;WDT_FLAG  -  EN_WDT  CLR_WDT  IDLE_WDT  PS2  PS1  PS0    xx00,0000


CCON     EQU    0D8H; //PCA ���ƼĴ�����   CF  CR   -   -   -   -  CCF1 CCF0  00xx,xx00
  CF     BIT    CCON.7; //PCA�����������־,��Ӳ���������λ,�����������0
  CR     BIT    CCON.6; //1:���� PCA ����������, �����������0��
  CCF1   BIT    CCON.1; //PCA ģ��1 �жϱ�־, ��Ӳ����λ, �����������0
  CCF0   BIT    CCON.0; //PCA ģ��0 �жϱ�־, ��Ӳ����λ, �����������0

CMOD     EQU    0D9H; //PCA ����ģʽ�Ĵ���  CIDL  -   -   -  CPS2   CPS1  CPS0  ECF   0xxx,x000

    ;CIDL: idle ״̬ʱ PCA �������Ƿ��������, 0: ��������, 1: ֹͣ������
    ;CPS2,CPS1,CPS0: PCA ����������Դѡ��λ
    ;CPS2   CPS1   CPS0
    ;0      0      0    ϵͳʱ��Ƶ�� fosc/12��
    ;0      0      1    ϵͳʱ��Ƶ�� fosc/2��
    ;0      1      0    Timer0 �����
    ;0      1      1    �� ECI/P3.4 ��������ⲿʱ�ӣ���� fosc/2��
    ;1      0      0    ϵͳʱ��Ƶ�ʣ�  Fosc/1
    ;1      0      1    ϵͳʱ��Ƶ��/4��Fosc/4
    ;1      1      0    ϵͳʱ��Ƶ��/6��Fosc/6
    ;1      1      1    ϵͳʱ��Ƶ��/8��Fosc/8

    ;ECF: PCA����������ж�����λ, 1--���� CF(CCON.7) �����жϡ�

PCA_CL   EQU    0E9H; //PCA ��������λ                        0000,0000
PCA_CH   EQU    0F9H; //PCA ��������λ                        0000,0000
CCAPM0   EQU    0DAH; //PCA ģ��0 PWM �Ĵ���  -  ECOM0 CAPP0 CAPN0 MAT0 TOG0 PWM0 ECCF0  x000,0000
CCAPM1   EQU    0DBH; //PCA ģ��1 PWM �Ĵ���  -  ECOM1 CAPP1 CAPN1 MAT1 TOG1 PWM1 ECCF1  x000,0000
CCAPM2   EQU    0DCH
    ;ECOMn = 1:����ȽϹ��ܡ�
    ;CAPPn = 1:���������ش�����׽����
    ;CAPNn = 1:�����½��ش�����׽���ܡ�
    ;MATn  = 1:��ƥ���������ʱ, ���� CCON �е� CCFn ��λ��
    ;TOGn  = 1:��ƥ���������ʱ, CEXn ����ת��
    ;PWMn  = 1:�� CEXn ����Ϊ PWM �����
    ;ECCFn = 1:���� CCON �е� CCFn �����жϡ�

    ;ECOMn  CAPPn  CAPNn  MATn  TOGn  PWMn  ECCFn
    ;  0      0      0     0     0     0     0   0x00   δ�����κι��ܡ�
    ;  x      1      0     0     0     0     x   0x21   16λCEXn�����ش�����׽���ܡ�
    ;  x      0      1     0     0     0     x   0x11   16λCEXn�½��ش�����׽���ܡ�
    ;  x      1      1     0     0     0     x   0x31   16λCEXn����(�ϡ�����)������׽���ܡ�
    ;  1      0      0     1     0     0     x   0x49   16λ�����ʱ����
    ;  1      0      0     1     1     0     x   0x4d   16λ�������������
    ;  1      0      0     0     0     1     0   0x42   8λ PWM��

    ;ECOMn  CAPPn  CAPNn  MATn  TOGn  PWMn  ECCFn
    ;  0      0      0     0     0     0     0   0x00   �޴˲���
    ;  1      0      0     0     0     1     0   0x42   ��ͨ8λPWM, ���ж�
    ;  1      1      0     0     0     1     1   0x63   PWM����ɵͱ�߿ɲ����ж�
    ;  1      0      1     0     0     1     1   0x53   PWM����ɸ߱�Ϳɲ����ж�
    ;  1      1      1     0     0     1     1   0x73   PWM����ɵͱ�߻��ɸ߱�Ͷ��ɲ����ж�

CCAP0L   EQU    0EAH; //PCA ģ�� 0 �Ĳ�׽/�ȽϼĴ����� 8 λ��                                    0000,0000
CCAP0H   EQU    0FAH; //PCA ģ�� 0 �Ĳ�׽/�ȽϼĴ����� 8 λ��                                    0000,0000
CCAP1L   EQU    0EBH; //PCA ģ�� 1 �Ĳ�׽/�ȽϼĴ����� 8 λ��                                    0000,0000
CCAP1H   EQU    0FBH; //PCA ģ�� 1 �Ĳ�׽/�ȽϼĴ����� 8 λ��                                    0000,0000
CCAP2L   EQU    0ECH
CCAP2H   EQU    0FCH
PCA_PWM0 EQU    0F2H; //PCA ģ��0 PWM �Ĵ����� -   -   -   -   -   -  EPC0H EPC0L   xxxx,xx00
PCA_PWM1 EQU    0F3H; //PCA ģ��1 PWM �Ĵ����� -   -   -   -   -   -  EPC1H EPC1L   xxxx,xx00
PCA_PWM2 EQU    0F4H
    ;B1(EPCnH): �� PWM ģʽ�£��� CCAPnH ��� 9 λ����
    ;B0(EPCnL): �� PWM ģʽ�£��� CCAPnL ��� 9 λ����

ADC_CONTR  EQU   0BCH; //A/D ת�����ƼĴ��� ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHS0 0000,0000
ADC_RES    EQU   0BDH;  //A/D ת�������8λ ADCV.9 ADCV.8 ADCV.7 ADCV.6 ADCV.5 ADCV.4 ADCV.3 ADCV.2	 0000,0000
ADC_RESL   EQU   0BEH;  //A/D ת�������2λ                                           ADCV.1 ADCV.0	 0000,0000

SPCTL      EQU  0CEH; //SPI Control Register  SSIG  SPEN  DORD  MSTR  CPOL  CPHA  SPR1  SPR0  0000,0100
SPSTAT     EQU  0CDH; //SPI Status Register   SPIF  WCOL   -     -     -     -     -     -    00xx,xxxx
SPDAT      EQU  0CFH; //SPI Data Register                                                     0000,0000

IAP_DATA   EQU  0C2H;
IAP_ADDRH  EQU  0C3H;
IAP_ADDRL  EQU  0C4H;
IAP_CMD    EQU  0C5H; IAP Mode Table          0    -    -      -    -    -   MS1   MS0   0xxx,xx00
IAP_TRIG   EQU  0C6H;
IAP_CONTR  EQU  0C7H; IAP Control Register  IAPEN SWBS SWRST CFAIL  -   WT2  WT1   WT0   0000,x000

IAP_Byte_Read  EQU   1
IAP_Byte_PGM   EQU   2
IAP_SEC_Erase  EQU   3
IAP_Waite      EQU   3
;----------------------------------------------------------

;==========================================================
;BIT Registers
;-------------------
;PSW
;-------------------
CY       BIT    PSW.7;
AC       BIT    PSW.6;
F0       BIT    PSW.5;
RS1      BIT    PSW.4;
RS0      BIT    PSW.3;
OV       BIT    PSW.2;
P        BIT    PSW.0;
;------------------
;TCON
;------------------
TF1      BIT    TCON.7;
TR1      BIT    TCON.6;
TF0      BIT    TCON.5;
TR0      BIT    TCON.4;
IE1      BIT    TCON.3;
IT1      BIT    TCON.2;
IE0      BIT    TCON.1;
IT0      BIT    TCON.0;
;-------------------
;SCON
;-------------------
SM0      BIT    SCON.7;  alternatively "FE"
FE       BIT    SCON.7;
SM1      BIT    SCON.6;
SM2      BIT    SCON.5;
REN      BIT    SCON.4;
TB8      BIT    SCON.3;
RB8      BIT    SCON.2;
TI       BIT    SCON.1;
RI       BIT    SCON.0;
;----------------------
;==========================================================
;��������


;----------------------------------------------------------
WEIGHT1         EQU     1
WEIGHT2         EQU     1
WEIGHT3         EQU     2
WEIGHT4         EQU     3
WEIGHT5         EQU     3
WEIGHT6         EQU     2
WEIGHT7         EQU     1
WEIGHT8         EQU     1
TOTAL_WEIGHT    EQU     14
;----------------------------------------------------------
TBWORD          EQU     5AH     ;ͬ����
HEXBytes        EQU       4

TIniValH        EQU    000H     ;��ʱ����ֵ���ֽ�
TIniValL        EQU    000H     ;��ʱ����ֵ���ֽ�

MzTH_STX        EQU    055H
MzTH_ETX        EQU    0AAH


T2049US_H       EQU    0BFH       ;2.049ms,244Hz  @8MHz@����Ƶ
T2049US_L       EQU    0F8H

T1MS_H          EQU    0E0H       ;1ms,500HZ   @8MHz@����Ƶ
T1MS_L          EQU    0C0H

T500US_H        EQU    0F0H       ;500us,1KHZ  @8MHz@����Ƶ
T500US_L        EQU    060H

T250US_H        EQU    0F8H       ;250us,2KHZ  @8MHz@����Ƶ
T250US_L        EQU    030H

T100US_H        EQU    0FCH       ;100us,5KHZ  @8MHz@����Ƶ
T100US_L        EQU    0E0H

T050US_H        EQU    0FEH       ;50us,10KHZ  @8MHz@����Ƶ
T050US_L        EQU    070H

T03125US_H      EQU    0FFH       ;31.25us,16KHZ  @8MHz@����Ƶ
T03125US_L      EQU    006H

T025US_H        EQU    0FFH       ;25us,20KHZ  @8MHz@����Ƶ
T025US_L        EQU    038H

T010US_H        EQU    0FFH       ;10us,50KHZ  @8MHz@1��Ƶ
T010US_L        EQU    0B0H

CCP_S0          EQU    10H    ;P_SW1.4
CCP_S1          EQU    20H    ;P_SW1.5
;----------------------------------------------------------
;Function Code in Communication
;----------------------------------------------------------
CMD_Read        EQU     03H
CMD_Write       EQU     10H

CMD_S_PARA      EQU     81H
CMD_S_InitStart EQU     82H
CMD_S_InitStop  EQU     83H
CMD_S_CtrWord   EQU     84H
CMD_S_MotorStep EQU     85H
CMD_S_MotorAuto EQU     86H     ;�Զ�ת��

CMD_R_PARA      EQU     88H
CMD_R_VER       EQU     89H
CMD_R_AUA       EQU     8AH
CMD_R_AUB       EQU     8CH
;----------------------------------------------------------
Back_IllegalF   EQU     01H     ;�Ƿ�������
Back_IllegalDA  EQU     02H     ;�Ƿ����ݵ�ַ
Back_IllegalDV  EQU     03H     ;�Ƿ�����ֵ
Back_SlaDevFail EQU     04H     ;���豸����ʧ��
Back_DevACK     EQU     05H     ;���豸Ӧ��
Back_DevBusy    EQU     06H     ;���豸æ
;----------------------------------------------------------
;�����洢��ַ(ָ���ڲ�EEPROM)
;----------------------------------------------------------
A_DevPara       EQU    000H     ;�豸�����洢��ַ,15+1BCH
A_1DevPara      EQU    020H
A_2DevPara      EQU    040H

A_DevSN         EQU    000H
;----------------------------------------------------------
;==========================================================
;CPU�ڲ�RAM������
;-----------------------------------------------------------
Cnt_Byte        EQU     10H     ;��ȡ��д��I2C,MEMʱ�������ֽڼ�����
SORT_Ind        EQU     11H     ;����ʱ������ָ��
DevNumber       EQU     12H     ;������ַ
REG_TMR1        EQU     13H
REG_TMR2        EQU     14H
TMR_T0_1S       EQU     15H

REG_MAX187H     EQU     16H
REG_MAX187L     EQU     17H

REG_TEMP1       EQU     16H
REG_TEMP2       EQU     17H
REG_TEMP3       EQU     18H
REG_TEMP4       EQU     19H
REG_TEMP5       EQU     1AH

REG_Grade       EQU     1BH

CounterRxd      EQU     1CH     ;UART���ռ�����
LengthRxd       EQU     1DH     ;UART�����ֽڳ���
CounterTxd      EQU     1EH     ;UART���ͼ�����
LengthTxd       EQU     1FH     ;UART�����ֽڳ���
;--------------------------
GeneralF1       EQU     20H
GeneralF2       EQU     21H
GeneralF3       EQU     22H
GeneralF4       EQU     23H

REG_DDC1_L      EQU     24H     ;27-20
REG_DDC1_M      EQU     25H     ;2F-28
REG_DDC1_H      EQU     26H     ;37-30

REG_DDC2_L      EQU     28H     ;47-40
REG_DDC2_M      EQU     29H     ;4F-48
REG_DDC2_H      EQU     2AH     ;57-50

REG_IntegConst  EQU     2CH
TMP_AUH_H       EQU     2DH
TMP_AUH_M       EQU     2EH
TMP_AUH_L       EQU     2FH

BufferPARA      EQU     30H
DeutTungst      EQU     30H
TimeConst       EQU     31H
PARA3           EQU     32H
PARA4           EQU     33H
VER1            EQU     34H
VER2            EQU     35H
VER3            EQU     36H

REG_DATA1       EQU     38H      ;��������ʱ�Ĵ���
REG_DATA2       EQU     39H
REG_DATA3       EQU     3AH
REG_DATA4       EQU     3BH

REG_StepH       EQU     3CH
REG_StepL       EQU     3DH
Cnt_Roll_H      EQU     3EH
Cnt_Roll_L      EQU     3FH

WaveLenth1_H    EQU     40H
WaveLenth1_L    EQU     41H
WaveLenth2_H    EQU     42H
WaveLenth2_L    EQU     43H

WaveL_Temp1_H   EQU     44H
WaveL_Temp1_L   EQU     45H
WaveL_Temp2_H   EQU     46H
WaveL_Temp2_L   EQU     47H

REG_AUH_H       EQU     48H
REG_AUH_M       EQU     49H
REG_AUH_L       EQU     4AH

SAVE_AUH_H      EQU     4BH
SAVE_AUH_M      EQU     4CH
SAVE_AUH_L      EQU     4DH

Save_WaveLenth_H EQU    4EH
Save_WaveLenth_L EQU    4FH

Cnt_CW          EQU    50H              ;ǰ������������,��ֹת��ȥ������
Cnt_CCW         EQU    51H              ;
Cnt_Repeat      EQU    52H              ;ת��ȥ�󷴸�Ѱ�Ҵ���,3�κ�ȫ������
Cnt_ForStep     EQU    53H              ;ÿ�������ֵλ��ʱ,�Ʋ���
Cnt_FindBig     EQU    54H              ;Ѱ����ߵ�Ĵ���

Ind_AUH_2ST     EQU    55H              ;�����˲����ݻ�����ָ��
Ind_PositAUH    EQU    55H              ;���ֵ������ָ��
REG_PositAUH    EQU    56H              ;����20�ζ�ȡ�ж������ֵ��λ��

REG_2WL_SWT     EQU    57H
;----------------------------------------------------------
BufferAD1       EQU    080H      ;ADת������洢��1
BufferAD2       EQU    0B0H      ;ADת������洢��2

BufferEeprom    EQU    0D0H     ;EEPROM��д������,32�ֽ�
BufferAUH       EQU    0E0H

BufferBCD       EQU    0F0H
BufferHEX       EQU    0F8H

BufferRxd       EQU    000H     ;���пڽ������ݻ�����000H~0FFH,256�ֽ�
BufferTxd       EQU    000H     ;���пڷ������ݻ�����000H~0FFH,256�ֽ�

BufferTEMP      EQU    040H     ;��ʱ�۲�Ĵ���

Buffer_AUH      EQU    080H

Buffer_StorageAU  EQU   020H    ;����������ʱ������,8�ֽ�
Buffer_Weight     EQU   030H    ;��Ȩ����ʱ��Դ���ݻ�����,60�ֽ�
;----------------------------------------------------------
;----------------------------------------------------------
;20H,21H����λѰַ�ռ�
;----------------------------------
B_TMR           BIT     00H
B_5MS           BIT     01H
B_SECOND        BIT     02H
B_Rcving        BIT     02H

B_InitStart     BIT     03H
B_InitStop      BIT     04H
B_MotorStep     BIT     05H
B_MotorAuto     BIT     06H

B_GET_nAU       BIT     07H     ;��λ����ȡ���ݱ�־
B_InitOK        BIT     08H
B_WaveLoc2      BIT     09H     ;˫����ʱ,��դ���ڲ���2λ��ʱ��λ

B_AUH_BIG       BIT     0AH
B_AUH_SMALL     BIT     0BH

B_DIR1          BIT     0CH
B_DIR2          BIT     0DH
B_TempDir       BIT     0EH
B_WaveDual      BIT     0FH

B_WaveChangeOK  BIT     10H

B_TungstenLamp  BIT     11H
B_Wav2Dir_Temp  BIT     12H
B_Wav1Dir_Temp  BIT     13H
B_NEW_WaveDual  BIT     14H
B_AU_SENT       BIT     15H

B_RD_AUH        BIT     16H
B_LevelBig      BIT     17H
;----------------------------------------------------------
;MCU Pin define
;----------------------------------------------------------
;IN_DATA2        BIT     P0.3     ;
OUT_RST         BIT     P0.2     ;
OUT_FDS         BIT     P0.1     ;
OUT_RSET        BIT     P0.0     ;

XTAL1           BIT     P1.7
XTAL2           BIT     P1.6     ;
DDS_P_RST       BIT     P1.5     ;
DDS_P_WCLK      BIT     P1.4     ;
DDS_P_FQUD      BIT     P1.3     ;
DDS_P_DATA      BIT     P1.2
AUX_RES2        BIT     P1.1
AUX_RES1        BIT     P1.0

OUT_DTE         BIT     P2.7     ;
OUT_SCLK        BIT     P2.6     ;
;IN_DATA1        BIT     P2.5     ;
AUX_LED         BIT     P2.4
IN_OF2          BIT     P2.3
IN_OF1          BIT     P2.2     ;
OUT_SETIN       BIT     P2.1
A_MCU_MOD       BIT     P2.0

XuRXD1          BIT     P3.7
XuTXD1          BIT     P3.6
OUT_SYSCLK      BIT     P3.5
A_PUL           BIT     P3.4
P33_INT1        BIT     P3.3
P32_INT0        BIT     P3.2
EA_STOP         BIT     P3.2
BM_TXD          BIT     P3.1
BM_RXD          BIT     P3.0

A_DIR           BIT     P5.5
A_RST           BIT     P5.4

BEEP            BIT     P1.0
;---------------------------------------
;ddc112
;---------------------------------------
AD_RANGE0       BIT     P3.5
AD_RANGE1       BIT     P0.2
AD_RANGE2       BIT     P0.1

OUT_DXMIT1      BIT     P2.6
OUT_DXMIT2      BIT     P2.6
OUT_SCLK1       BIT     P2.7
OUT_SCLK2       BIT     P2.7

OUT_CONV1       BIT     P2.1
OUT_CONV2       BIT     P2.1

IN_VALID1       BIT     P2.5
IN_VALID2       BIT     P0.3
IN_DATA1        BIT     P2.2
IN_DATA2        BIT     P2.3
;==========================================================
;**********************************************************
;**********************************************************
;==========================================================
            ORG    0000H

            LJMP   ERR_PIT      ;0000H
            LJMP   INT_EXT0     ;0003H,INT_EXT0
            NOP                 ;0006H
            NOP                 ;0007H
            LJMP   ERR_PIT      ;0008H
            LJMP   INT_TMR0     ;000BH,INT_TMR0
            NOP                 ;000EH
            NOP                 ;000FH
            LJMP   ERR_PIT      ;0010H
            LJMP   INT_EXT1     ;0013H,INT_EXT1
            NOP                 ;0016H
            NOP                 ;0017H
            LJMP   ERR_PIT      ;0018H
            LJMP   INT_TMR1     ;001BH,INT_TMR1
            NOP                 ;001EH
            NOP                 ;001FH
            LJMP   ERR_PIT      ;0020H
            LJMP   INT_UART     ;0023H,INT_UART
            NOP                 ;0026H
            NOP                 ;0027H
            LJMP   ERR_PIT      ;0028H
            LJMP   ERR_PIT      ;002BH,INT_ADC
            NOP                 ;002EH
            NOP                 ;002FH
            LJMP   ERR_PIT      ;0030H
            LJMP   ERR_PIT      ;0033H,INT_LVD
            NOP                 ;0036H
            NOP                 ;0037H
            LJMP   ERR_PIT      ;0038H
            LJMP   ERR_PIT      ;003BH,INT_PCA
;==========================================================
;==========================================================
ERR_PIT:    MOV    IE,#0
            MOV    IE2,#0
            MOV    DPTR,#ERR_PIT1
            PUSH   DPL
            PUSH   DPH
            RETI
ERR_PIT1:   MOV    DPTR,#START
            PUSH   DPL
            PUSH   DPH
            RETI
;===========================================================
;===========================================================
START:      MOV    SP,#58H                   ;�������ö�ջ
            LCALL  INIT_IO
            LCALL  INIT_SFR
            LCALL  INIT_FLAG
            LCALL  INIT_LED
            LCALL  INIT_PARA
            LCALL  INIT_IM481H
            LCALL  INIT_DDC112
            LCALL  INIT_INT
;            LCALL  INIT_AD9850
;            LCALL  INIT_DDC101
;***********************************************************
;***********************************************************
;===========================================================
MainA11:      
            JNB    B_InitOK,MainA13          ;δ��ʼ������դ,��ת
            JNB    B_WaveDual,MainA11A
            AJMP   MainB10
            
MainA11A:   ;JB     B_AU_SENT,MainA12
            
            ;LCALL  SEND_nAU                  ;�Ӳ������ϴ�
            ;SETB   B_AU_SENT                 ;����ʱ���,�²������ϴ�һ��
            ;LCALL  DELAY50M
            LCALL  DELAY1MS
            
MainA12:    ;MOV    REG_TMR_SendAU,#10        ;���0.2���л�һ�λ��ϴ�һ��
            ;MOV    REG_TMR_SendAU,#5         ;���0.1���л�һ�λ��ϴ�һ��
            ;MOV    REG_TMR_SendAU,#1         ;���0.05���л�һ�λ��ϴ�һ��
MainA13:    
            JBC    B_InitStop,MainA15
            JBC    B_MotorStep,MainA21       ;ת��ָ������
            JBC    B_MotorAuto,MainA22       ;�趨�Զ���ת
            JBC    B_GET_nAU,MainA23         ;���İ��ȡ���ݱ�־
            JBC    B_InitStart,MainA24       ;ȥ�����
            JBC    B_WaveChangeOK,MainA25    ;�����յ�2�鲨���޸�����

MainA14:    JB     EA_STOP,MainA16           ;���ǿ��ͣת״̬
            LCALL  Delay1MS
            JB     EA_STOP,MainA16
            LCALL  Delay1MS
            JB     EA_STOP,MainA16
            
MainA15:    LCALL  CLK_OFF_P34               ;ǿ��ͣת
            LCALL  DELAY20MS
            AJMP   MainA11
            
MainA16:    JNB    B_InitOK,MainA11
            LCALL  DELAY1MS
            ;DJNZ   REG_TMR_SendAU,MainA13
            
            AJMP   MainA11
;----------------------------------------------------------
MainA21:    LCALL  DELAY20MS
            LCALL  SET_MOTOR_ROLL            ;ת��ָ������
            CLR    B_WaveLoc2
            CLR    B_initOK
            ;LCALL  SEND_nAU                  ;ÿת�����Զ�λ���ϴ�һ��
            LCALL  DELAY20MS
            AJMP   MainA11
;-----------------------------------------------------------
MainA22:    LCALL  AUTO_ROLL_ON              ;�Զ���ת
            LCALL  DELAY50M
            AJMP   MainA11
;-----------------------------------------------------------
MainA23:    LCALL  DELAY10MS                 ;����AUֵ
            LCALL  SEND_nAU
            LCALL  DELAY20MS
            AJMP   MainA11
;-----------------------------------------------------------
MainA24:    AJMP   MainB24
;-----------------------------------------------------------
MainA25:    LCALL  DELAY20MS
            JB     B_InitOK,MainA26
            
            LCALL  LOAD_WavData              ;װ������
            LCALL  SEND_WaveChg_echo         ;�����޸ĳɹ�����֡
            LCALL  DELAY20MS
            
            AJMP   MainA11
            ;---------------------------
MainA26:    JNB    B_NEW_WaveDual,MainA27
            LCALL  ROLLBACK_AAA              ;�������л���˫����ģʽ,��ת�ص�ԭ��
            LCALL  LOAD_WavData              ;װ������
            LCALL  SEND_WaveChg_echo         ;�����޸ĳɹ�����֡
            LCALL  DELAY20MS
            AJMP   MainB26

MainA27:    LCALL  LOAD_WavData
            LCALL  ROLL_WL1                  ;ת���µ�λ��  
            LCALL  SEND_WaveChg_echo         ;�����޸ĳɹ�����֡
            LCALL  DELAY20MS
            AJMP   MainA11
;***********************************************************
;-----------------------------------------------------------
MainB10:    CPL    B_DIR2                    ;����ת����һλ��
            CPL    B_WaveLoc2
            LCALL  ROLL_WL2
            LCALL  SEND_nAU
            
Mainb11:    MOV    REG_2WL_SWT,#2
MainB12:    ;MOV    REG_TMR_SendAU,#50        ;���0.1���л�һ�λ��ϴ�һ��
            ;MOV    REG_TMR_SendAU,#2         ;�����ϴ����ʱ��
MainB13:    JBC    B_InitStop,MainB15
            JBC    B_MotorStep,MainB21
            JBC    B_MotorAuto,MainB22
            JBC    B_GET_nAU,MainB23
            JBC    B_InitStart,MainB24
            JNB    B_WaveChangeOK,MainB14

            CLR    B_WaveChangeOK
            LCALL  DELAY20MS
            LCALL  SEND_WaveChg_echo         ;�����ı�,����
            LCALL  DELAY20MS
            
            JNB    B_WaveLoc2,MainBX1
            LCALL  ROLLBack_WL2               ;ת�ص�����1λ��
             
MainBX1:    LCALL  ROLLBack_WL1              ;ת�ص�ԭ��
            
            JNB    B_NEW_WaveDual,MainBX2
            LCALL  LOAD_WavData              ;װ���²�������
            AJMP   MainB26
            
MainBX2:    MOV    Save_WaveLenth_H,#0       ;��ʱ��˫������Ϊ������ʱ,�ѷ���ԭ��,Ӧ������ֵ����
            MOV    Save_WaveLenth_L,#0
            
            LCALL  LOAD_WavData              ;װ���²�������
            LCALL  ROLL_WL1                  ;ת���µ�λ��  
            AJMP   MainA11
;---------------------------------------
MainB14:    JB     EA_STOP,MainB16
            LCALL  Delay1MS
            JB     EA_STOP,MainB16
            LCALL  Delay1MS
            JB     EA_STOP,MainB16
            
MainB15:    LCALL  CLK_OFF_P34
            LCALL  DELAY20MS
            AJMP   MainA11
;---------------------------------------
MainB16:    JB     B_InitOK,MainB17
            AJMP   MainA11                   ;δ��ʼ��,�ȴ�
            
MainB17:    LCALL  DELAY1MS                  ;���0.1�뷢��
            ;DJNZ   REG_TMR_SendAU,MainB13
            DJNZ   REG_2WL_SWT,MainB12
            AJMP   MainA11
;----------------------------------------------------------
MainB21:    LCALL  DELAY20MS
            LCALL  SET_MOTOR_ROLL            ;ת��ָ������
            CLR    B_WaveLoc2
            CLR    B_initOK
            ;LCALL  SEND_nAU                  ;ÿת�����Զ�λ���ϴ�һ��
            LCALL  DELAY20MS
            AJMP   MainA11
;-----------------------------------------------------------
MainB22:    LCALL  AUTO_ROLL_ON              ;�Զ���ת
            LCALL  DELAY100M
            AJMP   MainA11
;-----------------------------------------------------------
MainB23:    LCALL  DELAY50M
            LCALL  SEND_nAU
            LCALL  DELAY50M
            AJMP   MainA11
;-----------------------------------------------------------
MainB24:    LCALL  Find_A1
            LCALL  SET_Range                 ;��ԭ�����,������ʱ�����
            JB     B_InitOK,MainB25
            AJMP   MainA11

MainB25:    LCALL  SEND_InitOK
            LCALL  DELAY20MS
            ;----------------------------
MainB26:    JB     B_WaveDual,MainB27A
            LCALL  ROLL_AWL1
            AJMP   MainB27B
            
MainB27A:   LCALL  ROLL_WL1                  ;��ʼ������ת������1λ��
MainB27B:   LCALL  ROLL_WL2                  ;ת��������2λ��
            JB     B_WaveDual,MainB27C
            AJMP   MainA11                   ;ֱ��תȥ���͵�ǰAUֵ
            
MainB27C:   SETB   B_WaveLoc2                ;ָ�򲨳�2λ��
            LCALL  SEND_nAU                  ;���͵�ǰAUֵ
            AJMP   MainB11                   ;תȥ�����л�����
;***********************************************************
;===========================================================
INIT_IO:    MOV    P0M1, #00000000B    ;˫˫˫˫˫������
            MOV    P0M0, #00000111B
            MOV    P0,   #11111110B    ;-,-,-,-,IN_DATA2,OUT_RST,OUT_FDS,OUT_RSET
            ;----------------------
            MOV    P1M1, #00000000B    ;˫˫��������˫˫
            MOV    P1M0, #00111100B    ;
            MOV    P1,   #11111111B    ;XTAL1,XTAL2,DDS_P_RST,DDS_P_WCLK,DDS_P_FQUD,DDS_P_DATA,AUX_RES2,AUX_RES1
            ;----------------------
            MOV    P2M1, #00010000B    ;����˫��˫˫��˫
            MOV    P2M0, #11010010B
            MOV    P2,   #11111111B    ;OUT_DTE,OUT_SCLK,IN_DATA1,AUX_LED,IN_OF2,IN_OF1,OUT_SETIN,A_MCU_MOD
            ;----------------------
            MOV    P3M1, #00000000B    ;˫˫����˫˫˫˫
            MOV    P3M0, #00110000B
            MOV    P3,   #11111111B    ;XuRXD1,XuTXD1,OUT_SYSCLK,A_PUL,P33_INT1,P32_INT0,BM_TXD,BM_RXD
            ;----------------------
            MOV    P4M1, #00000000B    ;˫
            MOV    P4M0, #00000000B
            MOV    P4,   #11111111B    ;1
            
            MOV    P5M1, #00000000B    ;˫  ˫  ˫      ˫ ˫     ˫  ˫  ˫  ˫
            MOV    P5M0, #00000000B
            MOV    P5,   #11111111B    ;---,---,A_DIR,A_RST,---,---,---,---
            RET
;===========================================================
INIT_RAM:   CLR    RS0
            CLR    RS1
            MOV    R0,#8
            MOV    R1,#247
ClearRamLP: MOV    @R0,#0
            INC    R0
            DJNZ   R1,ClearRamLP
            RET
;===========================================================
INIT_SFR:
INIT_SFR1:  ;MOV    SP,       #50H
            MOV    WDT_CONTR,#0         ;WDTδ����
            MOV    PCON,     #00000000B
            MOV    SCON,     #01000000B ;RS232 MODE 1
            MOV    TMOD,     #00000000B ;T0,TIMER0,16λ��ʱ,T1 TIMER0,16λ�Զ���װ
            MOV    TCON,     #00000000B ;
            MOV    AUXR,     #11010101B ;T0/T1/T2����Ƶ,;T2Ϊ����1�Ĳ����ʷ�����
                                        ;
            JNB    A_MCU_MOD,INIT_SFR2  ;����ñ����ʹΪ���İ����ģʽ
            MOV    AUXR1,    #00100000B ;ʹ��DPTR0,CCP��P24P25P26,����1��P30/P31
            AJMP   INIT_SFR3
            
INIT_SFR2:  MOV    AUXR1,    #01100000B ;ʹ��DPTR0,CCP��P24P25P26,����1��P36/P37
INIT_SFR3:  MOV    P_SW2,    #00000000B ;
            MOV    P1ASF,    #00000000B ;��ģ������
            MOV    ADC_CONTR,#00000000B ;ADδ����
            MOV    P4SW,     #01110000B ;P46P45P44��ΪIO��
            ;MOV    WAKE_CLKO,#00000010B ;P3.4���ʱ��
            MOV    WAKE_CLKO,#00000000B ;�����ʱ��
            ;MOV    CLK_DIV,  #11000000B ;ʱ�Ӳ���Ƶ,��ʱ�����MCLK/4=2M
            MOV    CLK_DIV,  #00000000B ;ʱ�Ӳ���Ƶ,�������ʱ��
            MOV    IE,       #00000000B ;
            MOV    IE2,      #00000000B ;
            ;MOV    IPH0,     #00010101B
            MOV    IP0,      #00010000B ;---PCA,LVD,ADC,UART,T1,EX1,T0,EX0,UART�����ȼ�
            ;MOV    BRT,#220                  ;����������,9600
            ;-------------------------------------------------------------
            ;MOV    T2H,#0FEH            ;9600������(11.0592MHz,1T)
            ;MOV    T2L,#0E0H
            
            ;MOV    T2H,#0FFH            ;9600������(8MHz,1T)
            ;MOV    T2L,#030H
            
            MOV    T2H,#0FDH            ;9600������(24MHz,1T)
            MOV    T2L,#08FH
            ;------------------------------------
            ;MOV    TH0,#063H           ;T0�ж�����Ϊ5����(8MHz,1T)
            ;MOV    TL0,#0C0H
            
            ;MOV    TH0,#0D8H           ;T0�ж�����Ϊ5����(24MHz,12T)
            ;MOV    TL0,#0F0H
            ;------------------------------------
            RET
;===========================================================
INIT_FLAG:
            CLR    B_Rcving
            CLR    B_MotorAuto
            CLR    B_MotorStep
            CLR    B_GET_nAU
            CLR    B_InitStart
            CLR    B_InitStop
            CLR    B_TempDir
            CLR    B_WaveDual
            CLR    B_WaveLoc2
            CLR    B_InitOK
            CLR    B_TungstenLamp
            CLR    B_RD_AUH
            RET
;===========================================================
INIT_LED:
            CLR    AUX_LED              ;������˸
            LCALL  DELAY200M
            SETB   AUX_LED
            LCALL  DELAY100M
            
            CLR    AUX_LED
            LCALL  DELAY200M
            SETB   AUX_LED
            LCALL  DELAY100M
            
            CLR    AUX_LED
            LCALL  DELAY200M
            SETB   AUX_LED
            LCALL  DELAY100M
            
            CLR    AUX_LED              ;��������
            RET
;===========================================================
INIT_INT:   SETB   REN
            SETB   ES
            CLR    IE0
            CLR    IE1
            SETB   IT0
            SETB   IT1
            ;SETB   ET0
            ;SETB   ET1
            ;SETB   EX0
            ;SETB   EX1
            SETB   EA
            ;SETB   TR0
            ;SETB   TR1
            LCALL  DELAY50M
            RET
;===========================================================
;�ڵ�������,��ʼ����,�ߵ��µ�λ��
;-----------------------------------------------------------
ROLL_AWL1:  MOV    A,Save_WaveLenth_H
            JNZ    R_WL1_AA1
            MOV    A,Save_WaveLenth_L
            JNZ    R_WL1_AA1
            LCALL  DELAY50M
            RET                         ;������Ϊ0,��ת
            
R_WL1_AA1:  MOV    C,B_DIR1
            CLR    C
            MOV    A_DIR,C
            MOV    REG_Grade,#6
            MOV    A,Save_WaveLenth_H
            MOV    REG_DATA3,A
            MOV    A,Save_WaveLenth_L
            MOV    REG_DATA4,A
            LCALL  SET_MOTOR_ROLL
            CLR    B_WaveLoc2
            LCALL  DELAY50M
            RET
;===========================================================
;-----------------------------------------------------------
ROLL_WL1:   MOV    A,WaveLenth1_H
            JNZ    R_WL1_A1
            MOV    A,WaveLenth1_L
            JNZ    R_WL1_A1
            LCALL  DELAY50M
            
            LCALL  SEND_WaveChg_Necho        ;���Ͳ���δ������֡
            LCALL  DELAY50M
            
            RET                         ;������Ϊ0,��ת
            
R_WL1_A1:   MOV    C,B_DIR1
            MOV    A_DIR,C
            MOV    REG_Grade,#6
            MOV    A,WaveLenth1_H
            MOV    REG_DATA3,A
            MOV    A,WaveLenth1_L
            MOV    REG_DATA4,A
            LCALL  SET_MOTOR_ROLL
            CLR    B_WaveLoc2
            LCALL  DELAY50M
            RET
;===========================================================
;��ת��ԭ��λ��
;-----------------------------------------------------------
RollBack_WL1:
            MOV    A,WaveLenth1_H
            JNZ    RB_WL1_A1
            MOV    A,WaveLenth1_L
            JNZ    RB_WL1_A1
            RET                         ;������Ϊ0,��ת
            
RB_WL1_A1:  MOV    C,B_DIR1
            CPL    C
            MOV    A_DIR,C
            MOV    REG_Grade,#6
            MOV    A,WaveLenth1_H
            MOV    REG_DATA3,A
            MOV    A,WaveLenth1_L
            MOV    REG_DATA4,A
            LCALL  SET_MOTOR_ROLL
            
            CLR    B_WaveLoc2
            LCALL  DELAY50M
            RET
;===========================================================
;�������л���˫����ʱ,��ת��ԭ��λ��
;-----------------------------------------------------------
RollBack_AAA:
            MOV    A,Save_WaveLenth_H
            JNZ    RB_WL1_AA1
            MOV    A,Save_WaveLenth_L
            JNZ    RB_WL1_AA1
            RET                         ;������Ϊ0,��ת
            
RB_WL1_AA1: ;MOV    C,B_DIR1
            ;CPL    C
            ;MOV    A_DIR,C
            SETB   A_DIR                ;��������ԭ��ʱ˳ʱ��
            MOV    REG_Grade,#6
            MOV    A,Save_WaveLenth_H
            MOV    REG_DATA3,A
            MOV    A,Save_WaveLenth_L
            MOV    REG_DATA4,A
            LCALL  SET_MOTOR_ROLL
            
            CLR    B_WaveLoc2
            LCALL  DELAY50M
            RET
;===========================================================
ROLL_WL2:   MOV    A,WaveLenth2_H
            JNZ    R_WL2_A1
            MOV    A,WaveLenth2_L
            JNZ    R_WL2_A1
            
            CLR    B_WaveDual
            RET                         ;������Ϊ0,��ת
            
R_WL2_A1:   MOV    C,B_DIR2
            MOV    A_DIR,C
            MOV    REG_Grade,#6
            MOV    A,WaveLenth2_H
            MOV    REG_DATA3,A
            MOV    A,WaveLenth2_L
            MOV    REG_DATA4,A
            LCALL  SET_MOTOR_ROLL
            
            SETB   B_WaveDual
            RET
;===========================================================
;��ת��ԭ��λ��
;-----------------------------------------------------------
RollBack_WL2:
            MOV    A,WaveLenth2_H
            JNZ    RB_WL2_A1
            MOV    A,WaveLenth2_L
            JNZ    RB_WL2_A1
            
            ;CLR    B_WaveDual
            CLR    B_WaveLoc2
            RET                         ;������Ϊ0,��ת
            
RB_WL2_A1:  MOV    C,B_DIR2
            CPL    C
            MOV    A_DIR,C
            MOV    REG_Grade,#6
            MOV    A,WaveLenth2_H
            MOV    REG_DATA3,A
            MOV    A,WaveLenth2_L
            MOV    REG_DATA4,A
            LCALL  SET_MOTOR_ROLL
            
            CLR    B_WaveLoc2
            LCALL  DELAY50M
            RET
;===========================================================
LOAD_WavData:                                ;װ���²�������
            JNB    B_NEW_WaveDual,LWD2
            
LWD1:       MOV    C,B_Wav1Dir_Temp          ;����2��Ϊ0,����˫����ģʽװ��
            MOV    B_DIR1,C
            MOV    A,WaveL_Temp1_H
            MOV    WaveLenth1_H,A
            MOV    A,WaveL_Temp1_L
            MOV    WaveLenth1_L,A
            
            MOV    C,B_Wav2Dir_Temp
            MOV    B_DIR2,C
            MOV    A,WaveL_Temp2_H
            MOV    WaveLenth2_H,A
            MOV    A,WaveL_Temp2_L
            MOV    WaveLenth2_L,A
            
            SETB   B_WaveDual
            
            RET
;-------------------------------------------------            
LWD2:       CLR    B_WaveDual
            MOV    A,Save_WaveLenth_H        ;�����ϴβ�������ֵ
            CJNE   A,WaveL_Temp1_H,LWD3
LWD3:       JC     LWD_OldSmall1
            CJNE   A,WaveL_Temp1_H,LWD_OldBig
            
            MOV    A,Save_WaveLenth_L
            CJNE   A,WaveL_Temp1_L,LWD4
LWD4:       JC     LWD_OldSmall1
            CJNE   A,WaveL_Temp1_L,LWD_OldBig

LDW_OldEqual:
            SETB   B_DIR1
            MOV    WaveLenth1_H,#0
            MOV    WaveLenth1_L,#0
            AJMP   LDW6

LWD_OldBig:
            SETB   B_DIR1                    ;ԭֵ��,Ҫ˳ʱ����ת
            
            CLR    C
            MOV    A,Save_WaveLenth_L
            SUBB   A,WaveL_Temp1_L
            MOV    WaveLenth1_L,A
            
            MOV    A,Save_WaveLenth_H
            SUBB   A,WaveL_Temp1_H
            MOV    WaveLenth1_H,A
            AJMP   LDW6

LWD_OldSmall1:
            CLR    B_DIR1                    ;ԭֵС,Ҫ��ʱ����ת
            
            CLR    C
            MOV    A,WaveL_Temp1_L
            SUBB   A,Save_WaveLenth_L
            MOV    WaveLenth1_L,A
            
            MOV    A,WaveL_Temp1_H
            SUBB   A,Save_WaveLenth_H
            MOV    WaveLenth1_H,A
;-------------------------------------------------
LDW6:       MOV    A,WaveL_Temp1_H           ;���浱ǰ��������ֵ
            MOV    Save_WaveLenth_H,A
            MOV    A,WaveL_Temp1_L
            MOV    Save_WaveLenth_L,A
            
            MOV    C,B_Wav2Dir_Temp
            MOV    B_DIR2,C
            MOV    A,WaveL_Temp2_H
            MOV    WaveLenth2_H,A
            MOV    A,WaveL_Temp2_L
            MOV    WaveLenth2_L,A
            
            RET
;===========================================================
;-----------------------------------------------------------
;��ʼ����դ
;�Զ�������תʱ,���T1�ļ�ʱ������;ָ��������ʱ,����ɿصķ�ת����;
;2;56ϸ��������,0.9�ȵ��,תһȦ��������Ϊ102400,ÿ��Լ284.4������,1nm��Ӧ��������ԼΪ14��
;���ҵ�뮵��������ߵļ�ֵλ��,����Ϊ656.1nm,���չ�ʽ����,�����λ��Ϊ27.2774��;
;-------------------------------------------------------------
;ȷ����㣺1.��ʼ��һ���ٶ���ת���õ����ֵ��
;          2.�ٴ���ת���õ������ֵ�������ֵʱ��ֹͣ����תһ��;
;          3.��תѰ�ҹ�ǿֵ��

;-------------------------------------------------------------------------------
;ȷ����㲽��1.��һ���ٶ���ת,�õ����ֵ,�����REG_AUH_H,REG_AUH_M,REG_AUH_L
;-------------------------------------------------------------------------------
Find_A1:    SETB   AD_RANGE2            ;��ԭ��ʱ,������ʱ����Ϊ����350pc
            SETB   AD_RANGE1
            SETB   AD_RANGE0
            
            MOV    Cnt_Repeat,#0
            CLR    B_InitOK
            
            MOV    REG_Grade,#6              ;6���ٶ��Դ�
            CLR    A_DIR                     ;��ʱ��-��������
            LCALL  AUTO_ROLL_ON
            LCALL  READ_CLR_AUH              ;Ԥ��һ��?
            
            MOV    REG_AUH_H,#0
            MOV    REG_AUH_M,#0
            MOV    REG_AUH_L,#0
            
            MOV    REG_TEMP5,#100
Find_A2:    LCALL  READ_AUH
            DJNZ   REG_TEMP5,Find_A2
            
            MOV    REG_TEMP5,#100
Find_A3:    LCALL  READ_AUH
            DJNZ   REG_TEMP5,Find_A3

            MOV    REG_TEMP5,#100
Find_A4:    LCALL  READ_AUH
            DJNZ   REG_TEMP5,Find_A4
            
            MOV    REG_TEMP5,#150
Find_A5:    LCALL  READ_AUH
            DJNZ   REG_TEMP5,Find_A5
            
            MOV    REG_TEMP5, #30            ;����ʱ��Ϊ1.0����Ķ�ȡ����ֵ
            ;MOV    REG_TEMP5,#150            ;����ʱ��Ϊ0.8����Ķ�ȡ����ֵ
            ;MOV    REG_TEMP5,#220            ;����ʱ��Ϊ0.6����Ķ�ȡ����ֵ
Find_A6:    LCALL  READ_AUH
            DJNZ   REG_TEMP5,Find_A6
            
            AJMP   FIND_AA
            JNB    B_TungstenLamp,FIND_AA
            
            MOV    REG_TEMP5,#250
Find_A7:    LCALL  READ_AUH
            DJNZ   REG_TEMP5,Find_A7
             
            MOV    REG_TEMP5,#250
Find_A8:    LCALL  READ_AUH
            DJNZ   REG_TEMP5,Find_A8
            
            MOV    REG_TEMP5,#50
Find_A9:    LCALL  READ_AUH
            DJNZ   REG_TEMP5,Find_A9
            
Find_AA:    LCALL  CLK_OFF_P34               ;ת��1Ȧ,ֹͣ
            LCALL  DELAY50M
            
            MOV    A,REG_AUH_H               ;�����ȡ���ķ�ֵ
            MOV    SAVE_AUH_H,A
            MOV    A,REG_AUH_M
            MOV    SAVE_AUH_M,A
            MOV    A,REG_AUH_L
            MOV    SAVE_AUH_L,A
            
            ;-------------------------------------����ʱ���
            ;MOV    A,#0A1H
            ;LCALL  SEND_AUH
            ;LCALL  DELAY1S
;===========================================================
;ȷ����㲽��2.�ٴ���ת,�õ������ֵ�������ֵʱ,ֹͣ����תһ��;
;-----------------------------------------------------------
Find_B1:    MOV    REG_Grade,#6              ;�ڶ����ý�С���ٶ���ת�Ա����׵õ��ϴ�ֵ---̫������
            CLR    A_DIR                     ;��ʱ��-��������
            LCALL  AUTO_ROLL_ON

Find_B2:    JNB    B_InitStop,Find_BX
            CLR    B_InitStop
            LCALL  CLK_OFF_P34               ;ֹͣ
            RET

Find_BX:    LCALL  READ_CLR_AUH

            MOV    A,REG_AUH_H
            CJNE   A,SAVE_AUH_H,Find_B3
Find_B3:    JC     Find_B_SMALL              ;��λС
            CJNE   A,SAVE_AUH_H,Find_B_BIG   ;��λ��,ת�ϴ���
            
            MOV    A,REG_AUH_M
            CJNE   A,SAVE_AUH_M,Find_B4
Find_B4:    JC     Find_B_SMALL              ;��λС
            CJNE   A,SAVE_AUH_M,Find_B_BIG   ;��λ��,ת�ϴ���
            
            MOV    A,REG_AUH_L
            CJNE   A,SAVE_AUH_L,Find_B5
Find_B5:    JNC    Find_B_BIG
            ;---------------------------
Find_B_SMALL:
            CLR    C
            MOV    A,SAVE_AUH_L
            SUBB   A,REG_AUH_L
            MOV    R4,A
            
            MOV    A,SAVE_AUH_M
            SUBB   A,REG_AUH_M
            MOV    R5,A
            
            MOV    A,SAVE_AUH_H
            SUBB   A,REG_AUH_H
            MOV    R6,A
            ;---------------------------
            MOV    A,R6
            JNZ    Find_B2
            
            JNB    B_TungstenLamp,Find_B_SMAZ
            
            MOV    A,R5
            CJNE   A,#20,Find_B_SMAY         ;�ٵ�ʱ�Ľӽ�ֵ
Find_B_SMAY:JC     Find_B_SMA2
            AJMP   Find_B2                   ;��С����
            
            
Find_B_SMAZ:MOV    A,R5
            CJNE   A,#150,Find_B_SMA0         ;뮵�ʱ�Ľӽ�ֵ
Find_B_SMA0:JC     Find_B_SMA2
            AJMP   Find_B2                   ;��С����
            
;            JNZ    Find_B2
;            MOV    A,R4
;            CJNE   A,#250,Find_B_SMA1
;Find_B_SMA1:JC     Find_B_SMA2
;            AJMP   Find_B2
            
            
Find_B_SMA2:LCALL  CLK_OFF_P34
            AJMP   Find_B_STP                ;�Ѿ��ӽ����ֵ
            ;---------------------------
Find_B_BIG: LCALL  CLK_OFF_P34               ;ֹͣ
            
            MOV    SAVE_AUH_H,REG_AUH_H      ;ˢ��Ϊ���ֵ
            MOV    SAVE_AUH_M,REG_AUH_M
            MOV    SAVE_AUH_L,REG_AUH_L
            
Find_B_STP: LCALL  DELAY20MS
            SETB   A_DIR                     ;˳ʱ���ת
            MOV    REG_Grade,#4
            MOV    REG_DATA3,#001H           ;��תԼ1��(102400*1/360=284=0x011C)
            MOV    REG_DATA4,#01CH
            LCALL  SET_MOTOR_ROLL
            LCALL  DELAY50M
            
            ;-------------------------------------����ʱ���
            ;MOV    A,#0A2H
            ;LCALL  SEND_AUH
            ;LCALL  DELAY1S
;===========================================================
;ȷ����㲽��3.������ת������ǿֵ;
;-----------------------------------------------------------
Find_C1:
            CLR    B_AUH_BIG
            MOV    REG_Grade,#1              ;2���ٶ���ת
            CLR    A_DIR                     ;��ʱ��-��������
            LCALL  AUTO_ROLL_ON

Find_C2:    JNB    B_InitStop,Find_CX
            CLR    B_InitStop
            LCALL  CLK_OFF_P34
            RET
            
Find_CX:    LCALL  READ_CLR_AUH
            
            MOV    A,REG_AUH_H
            CJNE   A,SAVE_AUH_H,Find_C3
Find_C3:    JC     Find_C_Small              ;��λС
            CJNE   A,SAVE_AUH_H,Find_C_BIG
            
            MOV    A,REG_AUH_M
            CJNE   A,SAVE_AUH_M,Find_C4
Find_C4:    JC     Find_C_Small              ;��λС
            CJNE   A,SAVE_AUH_M,Find_C_BIG
            
            MOV    A,REG_AUH_L
            CJNE   A,SAVE_AUH_L,Find_C5
Find_C5:    JC     Find_C_Small
;-------------------------------------------------
Find_C_BIG: MOV    SAVE_AUH_H,REG_AUH_H      ;ˢ��Ϊ���ֵ
            MOV    SAVE_AUH_M,REG_AUH_M
            MOV    SAVE_AUH_L,REG_AUH_L
            
            SETB   B_AUH_BIG
            AJMP   Find_C2                   ;���������ض�
;-------------------------------------------------
Find_C_Small:
            CLR    C
            MOV    A,SAVE_AUH_L
            SUBB   A,REG_AUH_L
            MOV    R4,A
            
            MOV    A,SAVE_AUH_M
            SUBB   A,REG_AUH_M
            MOV    R5,A
            
            MOV    A,SAVE_AUH_H
            SUBB   A,REG_AUH_H
            MOV    R6,A
            ;-------------------------------------
            MOV    A,R6
            JZ     Find_C_Sma1
            JNB    B_AUH_BIG,Find_C2         ;δ���ϴ�ֵ
            
            LCALL  CLK_OFF_P34
            LCALL  DELAY20MS
            SETB   A_DIR                     ;ת������,�����ض�
            MOV    REG_Grade,#2
            MOV    REG_DATA3,#002H           ;��תԼ2��(102400*2/360=569=0x0239)
            MOV    REG_DATA4,#039H
            LCALL  SET_MOTOR_ROLL
            LCALL  DELAY10MS
            CLR    B_AUH_BIG
            AJMP   Find_C1
            ;---------------------------
Find_C_SMa1:MOV    A,R5
            CJNE   A,#3,Find_C_Sma2
Find_C_Sma2:JC     Find_C_SMA3
            JNB    B_AUH_BIG,Find_C2         ;δ���ϴ�ֵ
            
            LCALL  CLK_OFF_P34
            LCALL  DELAY20MS
            SETB   A_DIR                     ;ת������,�����ض�
            MOV    REG_Grade,#2
            MOV    REG_DATA3,#001H           ;��תԼ2��(102400*1/360=284=0x011C)
            MOV    REG_DATA4,#01CH
            LCALL  SET_MOTOR_ROLL
            LCALL  DELAY10MS
            CLR    B_AUH_BIG
            AJMP   Find_C1
            ;---------------------------
Find_C_Sma3:LCALL  CLK_OFF_P34
            LCALL  DELAY20MS
            JNB    B_AUH_BIG,Find_C_Sma4
            SETB   A_DIR                     ;ת������,����������΢��
            MOV    REG_Grade,#2
            MOV    REG_DATA3,#000H           ;��תԼ2��(102400*2/360=569)
            MOV    REG_DATA4,#0B0H
            LCALL  SET_MOTOR_ROLL
            LCALL  DELAY10MS
            
Find_C_Sma4:LCALL  CLK_OFF_P34               ;ֹͣ
            LCALL  DELAY50M

            ;-------------------------------------����ʱ���
            ;MOV    A,#0A3H
            ;LCALL  SEND_AUH
            ;LCALL  DELAY1S
;===========================================================
;ȷ����㲽��4.΢��Ѱ������ǿֵ(�Ѿ��ӽ���ԭ�������ֵ);
;-----------------------------------------------------------
Find_D1:    

Find_D2:    MOV    Cnt_CW,#0
            MOV    Cnt_CCW,#0
            CLR    B_LevelBig
            CLR    B_AUH_BIG
            CLR    B_AUH_Small
            CLR    B_InitOK

Find_D3:    JNB    B_InitStop,Find_DX1       ;�Ƿ��˳�
            CLR    B_InitStop
            CLR    B_InitOK
            RET
            
Find_DX1:   INC    Cnt_CW
            MOV    A,Cnt_CW
            JNZ    Find_DX2
            INC    Cnt_CCW
Find_DX2:   MOV    A,Cnt_CCW
            CJNE   A,#2,Find_DX3
Find_DX3:   JC     Find_DX4
            
            SETB   A_DIR                     ;ת������,�����ض�
            MOV    REG_Grade,#3
            MOV    REG_DATA3,#003H           ;��תԼ2��(102400*2/360=569)
            MOV    REG_DATA4,#020H
            LCALL  SET_MOTOR_ROLL
            LCALL  DELAY10MS
            CLR    B_AUH_BIG
            
            INC    Cnt_Repeat
            MOV    A,Cnt_Repeat
            CJNE   A,#3,Find_DY1
Find_DY1:   JC     Find_DY2
            AJMP   Find_A1                   ;����,ȫ������
Find_DY2:   
            
            CLR    C
            MOV    A,SAVE_AUH_L
            SUBB   A,#0
            MOV    R4,A
            
            MOV    A,SAVE_AUH_M
            SUBB   A,#30H
            MOV    R5,A
            
            MOV    A,SAVE_AUH_H
            SUBB   A,#0
            MOV    R6,A
            
            MOV    SAVE_AUH_L,R4
            MOV    SAVE_AUH_M,R5
            MOV    SAVE_AUH_H,R6             ;δ�ҵ����ֵ,���洢ֵ��С����
            
            
            AJMP   Find_C1
            
Find_DX4:   CLR    A_DIR                     ;������ʱ��ת��
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            
            JNB    B_LevelBig,Find_DX5
            MOV    REG_DATA4,#001H           ;�Ѿ��ӽ����,��ϸ��ģʽ
            AJMP   Find_DX6
            
Find_DX5:   MOV    REG_DATA4,#003H
Find_DX6:   LCALL  SET_MOTOR_ROLL
            
            LCALL  READ_CLR_AUH
            LCALL  AUH_Compare
            JNC    Find_DX7
            
            MOV    SAVE_AUH_H,REG_AUH_H      ;ˢ��Ϊ���ֵ
            MOV    SAVE_AUH_M,REG_AUH_M
            MOV    SAVE_AUH_L,REG_AUH_L
            SETB   B_AUH_BIG
            SETB   B_LevelBig                ;��λ�ϴ��־
            AJMP   Find_D3
            
Find_DX7:   CLR    C
            MOV    A,SAVE_AUH_L
            SUBB   A,REG_AUH_L
            MOV    R4,A
            
            MOV    A,SAVE_AUH_M
            SUBB   A,REG_AUH_M
            MOV    R5,A
            
            MOV    A,SAVE_AUH_H
            SUBB   A,REG_AUH_H
            MOV    R6,A
            
            MOV    A,R6
            CJNE   A,#2,FIND_DX8
FIND_DX8:   JC     FIND_DX9
            SETB   B_LevelBig                ;�Ѿ��ӽ���,��λ�ϴ��־
            
FIND_DX9:   JB     B_AUH_BIG,FIND_DXA     ;Ѱ���½���
            AJMP   Find_D3
            
FIND_DXA:   
            ;AJMP   Find_Xa1
            
            ;-------------------------------------
            ;�˴�Ҳ����ֱ���˳�,��㲻̫��,��Լ����0.25
            ;-------------------------------------
            ;MOV    A,#0A4H
            ;LCALL  SEND_AUH
            ;LCALL  DELAY1S
            
            
            LCALL  DELAY5MS
            SETB   A_DIR                     ;����10������Ѱ��
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#0
            MOV    REG_DATA4,#010
            LCALL  SET_MOTOR_ROLL
            MOV    Cnt_ForStep,#0
            LCALL  DELAY5MS
            
            MOV    SAVE_AUH_H,#0             ;�Ƚ����ֵ���������Ҳ������ֵ
            MOV    SAVE_AUH_M,#0
            MOV    SAVE_AUH_L,#0
            
FIND_DXB1:  MOV    A,#Buffer_AUH
            MOV    Ind_AUH_2ST,A             ;������ʱ�Ĵ���ָ��
            MOV    Cnt_ForStep,#16
            
FIND_DXB2:  LCALL  DELAY1MS
            LCALL  READ_CLR_AUH              ;��ȡ��ǰ��ǿ16��
            MOV    A,Ind_AUH_2ST
            MOV    R0,A                      ;ȡ����ǰָ��
            
            MOV    A,REG_AUH_H
            MOVX   @R0,A
            INC    R0
            INC    Ind_AUH_2ST
            MOV    A,REG_AUH_M
            MOVX   @R0,A
            INC    R0
            INC    Ind_AUH_2ST
            MOV    A,REG_AUH_L
            MOVX   @R0,A
            INC    R0
            INC    Ind_AUH_2ST
            
            DJNZ   Cnt_ForStep,FIND_DXB2
            ;-------------------------------------
            MOV    R0,#Buffer_AUH
            MOV    R1,#BufferAD1             ;�������Ƶ��ʺ�����Ƚϵ�λ��
            MOV    R2,#48
FIND_DXB3:  MOVX   A,@R0
            MOV    @R1,A
            INC    R0
            INC    R1
            DJNZ   R2,FIND_DXB3
            
            MOV    R0,#BufferAD1
            MOV    Cnt_Byte,#16
            LCALL  SORT3Byte                 ;����
            
            MOV    R0,#BufferAD1
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#14
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#12
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#10
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#8
            
            
            
            MOV    A,R0            ;��ǰ��Ч������ַ
            LCALL  WEIGHT_A1       ;��Ȩ����
            
            MOV    R0,#Buffer_Weight
            MOV    R1,#TOTAL_WEIGHT
            LCALL  DDM_A3
            ;LCALL  DDM3            ;ȡƽ��ֵ
            
            
            LCALL  AUH_XB_Compare
            JNC    FIND_DXB4
            
            MOV    SAVE_AUH_H,R6             ;ˢ�����ֵ
            MOV    SAVE_AUH_M,R5
            MOV    SAVE_AUH_L,R4
            
            CLR    A_DIR                     ;��ǰһ��
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#0
            MOV    REG_DATA4,#010
            LCALL  SET_MOTOR_ROLL
            
            AJMP   FIND_DXB1                  ;�����µ����ֵ�������ض�
            
FIND_DXB4:
            
            
            
            SETB   B_InitOK
            RET
;-------------------------------------------------
;��ǰ10����������и����,����������
;-------------------------------------------------
Find_XA1:   ;MOV    A,#0A4H
            ;LCALL  SEND_AUH
            ;LCALL  DELAY1S
            
            LCALL  DELAY5MS
            SETB   A_DIR                     ;����һ�����ղŵ����ֵλ��
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL
            MOV    Cnt_ForStep,#0
            LCALL DELAY5MS
            
Find_XA2:   CLR    A_DIR                     ;������ǰ��10��
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL
            
            LCALL  READ_CLR_AUH
            LCALL  AUH_Compare
            JNC    Find_XA3
            
            MOV    SAVE_AUH_H,REG_AUH_H      ;ˢ��Ϊ���ֵ
            MOV    SAVE_AUH_M,REG_AUH_M
            MOV    SAVE_AUH_L,REG_AUH_L
            MOV    Cnt_ForStep,#0            ;���ֽϴ�ֵ,���¿�ʼ��20��
            AJMP   Find_XA2                  ;�����µ����ֵ�������ض�
            
Find_XA3:   INC    Cnt_ForStep
            MOV    A,Cnt_ForStep
            CJNE   A,#10,Find_XA4
Find_XA4:   JC     Find_XA2
            
            ;MOV    A,#0A5H
            ;LCALL  SEND_AUH
            ;LCALL  DELAY1S
;-------------------------------------------------
;���¶�ȡ16��,����λ�þ�ֵ
;-------------------------------------------------
Find_XB0:   MOV    R0,#BufferAUH
            MOV    R2,#32
Find_XB1:   MOV    A,#0                      ;Ŀ�����㻺����
            MOV    @R0,A
            INC    R0
            DJNZ   R2,Find_XB1
 
            MOV    A,#BufferAUH              ;���ֵλ�õĻ�����ָ��
            MOV    Ind_PositAUH,A            ;ָ��Ĵ���
            MOV    Cnt_FindBig,#16           ;��16��
            ;---------------------------
Find_XB2:   LCALL  DELAY5MS
            SETB   A_DIR
            MOV    REG_Grade,#1              ;���˻�19�������
            MOV    REG_DATA3,#0
            MOV    REG_DATA4,#19
            LCALL  SET_MOTOR_ROLL
            ;LCALL  DELAY5MS
            
            MOV    SAVE_AUH_H,#0             ;����ο�ֵ
            MOV    SAVE_AUH_H,#0
            MOV    SAVE_AUH_H,#0
            MOV    Cnt_ForStep,#0            ;�����н������Ĵ���
            MOV    REG_PositAUH,#0           ;�������λ�üĴ���
;------------------------------
;�н�20��
;------------------------------
Find_XB3:   LCALL  DELAY5MS
            LCALL  READ_CLR_AUH
            LCALL  AUH_Compare               ;������ǰ��ǿֵ���Ƚ�
            JNC    Find_XB4
            
            MOV    SAVE_AUH_H,REG_AUH_H      ;ˢ�����ֵ
            MOV    SAVE_AUH_M,REG_AUH_M
            MOV    SAVE_AUH_L,REG_AUH_L
            
            MOV    A,Cnt_ForStep
            MOV    REG_PositAUH,A             ;���浱ǰ���ֵλ��
            
Find_XB4:   INC    Cnt_ForStep
            MOV    A,Cnt_ForStep
            CJNE   A,#20,Find_XB5
Find_XB5:   JNC    Find_XB6
            
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H           ;��ǰһ��
            LCALL  SET_MOTOR_ROLL
            AJMP   Find_XB3                  ;ÿ���ȡ20��
;-----------------------------
Find_XB6:   MOV    A,Ind_PositAUH
            MOV    R0,A
            MOV    @R0,REG_PositAUH          ;���汾�����ֵλ��
            INC    Ind_PositAUH
            DJNZ   Cnt_FindBig,Find_XB2
            
            MOV    R0,#BufferAD1
            MOV    R2,#48
Find_XB7:   MOV    A,#0                      ;���㻺����
            MOV    @R0,A
            INC    R0
            DJNZ   R2,Find_XB7
            ;-------------------------------------
            MOV    R0,#BufferAUH             ;��Դ���ݱ任Ϊ�ʺ�����ĸ�ʽ
            MOV    R1,#BufferAD1
            INC    R1
            INC    R1
            MOV    R2,#16
Find_XB8:   MOV    A,@R0
            MOV    @R1,A
            INC    R0
            INC    R1
            INC    R1
            INC    R1
            DJNZ   R2,Find_XB8
            ;-------------------------------------
            
            ;-------------------------------------
            ;��Ӳ���,�����Ƶ���չRAM������۲�
            ;-------------------------------------
            MOV    R0,#BufferAUH
            MOV    R1,#3
            MOV    R2,#16
Find_XB9:   MOV    A,@R0
            MOVX   @R1,A
            INC    R0
            INC    R1
            DJNZ   R2,Find_XB9
            
            
            MOV    R0,#BufferAD1
            MOV    Cnt_Byte,#16
            LCALL  SORT3Byte                 ;����
            
            MOV    R0,#BufferAD1
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#14
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#12
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#10
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#8
            
            
            
            MOV    A,R0            ;��ǰ��Ч������ַ
            LCALL  WEIGHT_A1       ;��Ȩ����
            
            MOV    R0,#Buffer_Weight
            MOV    R1,#TOTAL_WEIGHT
            LCALL  DDM_A3
            
            ;LCALL  DDM3            ;ȡƽ��ֵ
            
            
            
            MOV    A,R4
            CJNE   A,#6,Find_XBA
Find_XBA:   JNC    Find_XBB
            
            MOV    Cnt_Repeat,#0
            AJMP   Find_DY2                  ;�����쳣,�����ض�

Find_XBB:
            CLR    C
            MOV    A,#19
            SUBB   A,R4
            
            SETB   A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,A               ;���˲���
            LCALL  SET_MOTOR_ROLL

            ;LCALL  SEND_22DATA
            ;LCALL  DELAY50M
            
            ;LCALL  SEND_32DATA
            ;LCALL  DELAY1S

            SETB   B_InitOK
            RET
;-----------------------------------------------------------            
            
            MOV    A,SAVE_AUH_H
            MOV    REG_AUH_H,A
            MOV    A,SAVE_AUH_M
            MOV    REG_AUH_M,A
            MOV    A,SAVE_AUH_L
            MOV    REG_AUH_L,A
            MOV    A,#0B0H
            LCALL  SEND_AUH
            LCALL  DELAY20MS                 ;��ʾ�洢�����ֵ
            
            LCALL  READ_CLR_AUH
            MOV    A,#0B1H
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            ;--------------------------------------
            LCALL  DELAY20MS
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL

            LCALL  READ_CLR_AUH
            MOV    A,#0B2H
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            ;--------------------------------------
            LCALL  DELAY20MS
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL

            LCALL  READ_CLR_AUH
            MOV    A,#0B3H
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            ;--------------------------------------
            LCALL  DELAY20MS
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL

            LCALL  READ_CLR_AUH
            MOV    A,#0B4H
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            ;--------------------------------------
            LCALL  DELAY20MS
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL

            LCALL  READ_CLR_AUH
            MOV    A,#0B5H
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            ;--------------------------------------
            LCALL  DELAY20MS
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL

            LCALL  READ_CLR_AUH
            MOV    A,#0B6H
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            ;--------------------------------------
            LCALL  DELAY20MS
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL

            LCALL  READ_CLR_AUH
            MOV    A,#0B7H
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            ;--------------------------------------
            LCALL  DELAY20MS
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL

            LCALL  READ_CLR_AUH
            MOV    A,#0B8H
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            ;--------------------------------------
            LCALL  DELAY20MS
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL

            LCALL  READ_CLR_AUH
            MOV    A,#0B9H
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            ;--------------------------------------
            LCALL  DELAY20MS
            CLR    A_DIR
            MOV    REG_Grade,#1
            MOV    REG_DATA3,#000H
            MOV    REG_DATA4,#001H
            LCALL  SET_MOTOR_ROLL

            LCALL  READ_CLR_AUH
            MOV    A,#0BAH
            LCALL  SEND_AUH
            LCALL  DELAY20MS
            
            SETB   B_InitOK
            RET
;-------------------------------------------------
;-----------------------------------------------------------
Find_F1:    SETB   A_DIR                     ;��תһ���ƫ
            MOV    REG_Grade,#1
            ;-----------------------------
            MOV    REG_DATA3,#000H
            ;MOV    REG_DATA4,REG_StepInit
            RR     A
            RR     A
            RR     A
            RR     A
            ANL    A,#00001111B
            MOV    REG_DATA4,A
            ;------------------------------
            ;MOV    REG_DATA3,#000H           ;��ת2������
            ;MOV    REG_DATA4,#002H
            LCALL  SET_MOTOR_ROLL
            
Find_F2:    LCALL  READ_CLR_AUH
            SETB   B_InitOK
            
             ;-------------------------------------����ʱ���
            MOV    A,#0A5H
            LCALL  SEND_AUH
            LCALL  DELAY1S
            RET
;===========================================================
AUH_XB_Compare:
            MOV    A,R6
            CJNE   A,SAVE_AUH_H,AUH_XB_A1
AUH_XB_A1:  JC     AUH_XB_Small              ;��λС
            CJNE   A,SAVE_AUH_H,AUH_XB_BIG
            
            MOV    A,R5
            CJNE   A,SAVE_AUH_M,AUH_XB_A2
AUH_XB_A2:  JC     AUH_XB_Small              ;��λС
            CJNE   A,SAVE_AUH_M,AUH_XB_BIG
            
            MOV    A,R4
            CJNE   A,SAVE_AUH_L,AUH_XB_A3
AUH_XB_A3:  JC     AUH_XB_Small              ;����λ���,��λС

AUH_XB_BIG: SETB   C
            RET
            
AUH_XB_Small:
            CLR    C
            RET
;===========================================================
AUH_Compare:
            MOV    A,REG_AUH_H
            CJNE   A,SAVE_AUH_H,AUH_C_A1
AUH_C_A1:   JC     AUH_C_Small              ;��λС
            CJNE   A,SAVE_AUH_H,AUH_C_BIG
            
            MOV    A,REG_AUH_M
            CJNE   A,SAVE_AUH_M,AUH_C_A2
AUH_C_A2:   JC     AUH_C_Small              ;��λС
            CJNE   A,SAVE_AUH_M,AUH_C_BIG
            
            MOV    A,REG_AUH_L
            CJNE   A,SAVE_AUH_L,AUH_C_A3
AUH_C_A3:   JC     AUH_C_Small              ;����λ���,��λС

AUH_C_BIG:  SETB   C
            RET
            
AUH_C_Small:CLR    C
            RET
;***********************************************************
;===========================================================
;��ȡ��ǿֵ������
;-----------------------------------------------------------
READ_nAU:
            LCALL  READ_AU1AU2
                     
            MOV    R0,#BufferAD2
            MOV    Cnt_Byte,#16
            ;MOV    Cnt_Byte,#8     ;��ȡ��������16���Ϊ8��
            LCALL  SORT3Byte       ;����
            MOV    R0,#BufferAD2
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#14
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#12
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#10
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#8
            
            MOV    A,R0            ;��ǰ��Ч������ַ
            LCALL  WEIGHT_A1       ;��Ȩ����
            
            MOV    R0,#Buffer_Weight
            MOV    R1,#TOTAL_WEIGHT
            LCALL  DDM_A3
            
            ;LCALL  DDM3            ;ȡƽ��ֵ
            LCALL  GET_AAA_DATA
            
            MOV    R0,#Buffer_StorageAU
            MOV    A,R7
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R6
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R5
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R4
            MOVX   @R0,A
            INC    R0
            ;---------------------------
            MOV    R0,#BufferAD1
            MOV    Cnt_Byte,#16
            ;MOV    Cnt_Byte,#8     ;��ȡ��������16���Ϊ8��
            LCALL  SORT3Byte       ;����
            MOV    R0,#BufferAD1
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#14
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#12
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#10
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#8
            
            MOV    A,R0            ;��ǰ��Ч������ַ
            LCALL  WEIGHT_A1       ;��Ȩ����
            
            MOV    R0,#Buffer_Weight
            MOV    R1,#TOTAL_WEIGHT
            LCALL  DDM_A3
            
            ;LCALL  DDM3            ;ȡƽ��ֵ
            LCALL  GET_AAA_DATA
            
            MOV    R0,#Buffer_StorageAU
            INC    R0
            INC    R0
            INC    R0
            INC    R0
            
            MOV    A,R7
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R6
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R5
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R4
            MOVX   @R0,A
            INC    R0
            
            RET
;===========================================================
;��ȡ16������,�洢��AD1AD2
;-----------------------------------------------------------
READ_AU1AU2:
            MOV    R0,#BufferAD1
            MOV    R1,#BufferAD2
            MOV    R2,#16       ;��ȡ16��,2�����ݹ�96�ֽ�
            ;MOV    R2,#8       ;��ȡ8��,2�����ݹ�48�ֽ�
            
READ_AA1:   LCALL  READ_ADDC101
            MOV    A,REG_DDC1_H
            MOV    @R0,A
            INC    R0
            MOV    A,REG_DDC1_M
            MOV    @R0,A
            INC    R0
            MOV    A,REG_DDC1_L
            MOV    @R0,A
            INC    R0
            
            MOV    A,REG_DDC2_H
            MOV    @R1,A
            INC    R1
            MOV    A,REG_DDC2_M
            MOV    @R1,A
            INC    R1
            MOV    A,REG_DDC2_L
            MOV    @R1,A
            INC    R1
            
            MOV    A,REG_IntegConst
            MOV    R7,A
READ_AA2:   LCALL  DELAY1MS
            DJNZ   R7,READ_AA2
            
            ;LCALL  DELAY1MS
            ;LCALL  DELAY1MS
            ;LCALL  DELAY1MS
            ;LCALL  DELAY1MS
            ;LCALL  DELAYB100US
            ;LCALL  DELAYB100US
            DJNZ   R2,READ_AA1
            
            RET
;===========================================================
;���Դ�״̬�¶�ȡ����ǿֵ,����REG_AUH_H,REG_AUH_M,REG_AUH_L
;��ȡ���ʱ���Ӱ�����ֵ
;-----------------------------------------------------------
READ_CLR_AUH:                           ;��0��ʼ��ȡ������
            MOV    REG_AUH_H,#0
            MOV    REG_AUH_M,#0
            MOV    REG_AUH_L,#0
;-----------------------------------------------------------
READ_AUH:                               ;�����ϴ�����
            MOV    R0,#BufferAD1
            MOV    R1,#BufferAD2
            MOV    R2,#16               ;��ȡ16��,2�����ݹ�96�ֽ�
            
RD_AUH_A0:  
            
            SETB   B_RD_AUH
            LCALL  READ_DDC112
            CLR    B_RD_AUH

;            JB    B_TungstenLamp,RD_AUH_AX1
;            LCALL  DELAYB100US      
;RD_AUH_AX1: DJNZ   R2,RD_AUH_A0
            
            MOV    R0,#BufferAD1   ;ָ��α�ֵ
            MOV    Cnt_Byte,#16
            LCALL  SORT3Byte       ;����
            MOV    R0,#BufferAD1
            MOV    R1,#16
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#14
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#12
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#10
            
            INC    R0
            INC    R0
            INC    R0
            MOV    R1,#08
            
            
            
            MOV    A,R0            ;��ǰ��Ч������ַ
            LCALL  WEIGHT_A1       ;��Ȩ����
            
            MOV    R0,#Buffer_Weight
            MOV    R1,#TOTAL_WEIGHT
            LCALL  DDM_A3
            
            ;LCALL  DDM3            ;ȡƽ��ֵ
            ;-------------------------------------
            ;����Ϊ���ӵ��ٵƽ���������,�����
            ;-------------------------------------
            JNB    B_TungstenLamp,RD_AUH_AX2
            
            CLR    C                         ;�ٵ�ʱ�������ݳ���2
            MOV    A,R6
            RRC    A
            MOV    R6,A
            
            MOV    A,R5
            RRC    A
            MOV    R5,A
            
            MOV    A,R4
            RRC    A
            MOV    R4,A
            
            CLR    C                         ;�ٵ�ʱ�������ݳ���2
            MOV    A,R6
            RRC    A
            MOV    R6,A
            
            MOV    A,R5
            RRC    A
            MOV    R5,A
            
            MOV    A,R4
            RRC    A
            MOV    R4,A
            
            CLR    C                         ;�ٵ�ʱ�������ݳ���2
            MOV    A,R6
            RRC    A
            MOV    R6,A
            
            MOV    A,R5
            RRC    A
            MOV    R5,A
            
            MOV    A,R4
            RRC    A
            MOV    R4,A
           ;--------------------------------------

RD_AUH_AX2:
            MOV    A,R6
            CJNE   A,REG_AUH_H,RD_AUH_A3
RD_AUH_A3:  JC     RD_AUH_Small
            CJNE   A,REG_AUH_H,RD_AUH_Big
            
            MOV    A,R5
            CJNE   A,REG_AUH_M,RD_AUH_A4
RD_AUH_A4:  JC     RD_AUH_Small
            CJNE   A,REG_AUH_M,RD_AUH_Big
            
            MOV    A,R4
            CJNE   A,REG_AUH_L,RD_AUH_A5
RD_AUH_A5:  JC     RD_AUH_Small
            CJNE   A,REG_AUH_L,RD_AUH_Big
            
RD_AUH_Small:                                ;���ζ�ȡ����Сֱ���˳�
            RET
            
RD_AUH_BIG:                                  ;���ζ�ȡ���ݴ�,����
            MOV    A,R6
            MOV    REG_AUH_H,A
            
            MOV    A,R5
            MOV    REG_AUH_M,A
            
            MOV    A,R4
            MOV    REG_AUH_L,A
            RET
;===========================================================
;��ȡ��ǿֵ������
;��ȡ���ʱ���Ӱ�����ֵ
;-----------------------------------------------------------
SEND_AA_nAU:

            MOV    R0,#BufferTxd
            MOV    R1,#Buffer_StorageAU
            
            MOV    A,#08AH
            MOVX   @R0,A
            INC    R0
            
            MOVX   A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            
            MOVX   A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            
            MOVX   A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            
            MOVX   A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            
            SETB   TI
;---------------------------------------
            LCALL  DELAY10MS
;---------------------------------------            
            MOV    R0,#BufferTxd
            MOV    R1,#Buffer_StorageAU
            INC    R1
            INC    R1
            INC    R1
            INC    R1
            
            MOV    A,#08BH
            MOVX   @R0,A
            INC    R0
            
            MOVX   A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            
            MOVX   A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            
            MOVX   A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            
            MOVX   A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            
            SETB   TI
            
            RET
;===========================================================
;��ȡ��ǿֵ������
;��ȡ���ʱ���Ӱ�����ֵ
;-----------------------------------------------------------
SEND_nAU:
            MOV    R0,#BufferAD1
            MOV    R1,#BufferAD2
            MOV    R2,#16        ;��ȡ16��,2�����ݹ�96�ֽ�
            LCALL  READ_DDC112
            
            MOV    R0,#BufferAD2   ;ָ������ֵ
            MOV    Cnt_Byte,#16
            LCALL  SORT3Byte       ;����
            MOV    R0,#BufferAD2
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#14          ;�������ֵ
            
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#12          ;�������ֵ
            
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#10          ;�������ֵ
            
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#08          ;�������ֵ
            
            
            MOV    A,R0            ;��ǰ��Ч������ַ
            LCALL  WEIGHT_A1       ;��Ȩ����
            
            MOV    R0,#Buffer_Weight
            MOV    R1,#TOTAL_WEIGHT
            LCALL  DDM_A3
            
            ;LCALL  DDM3            ;ȡƽ��ֵ
            LCALL  GET_AAA_DATA
            ;---------------------------
            MOV    R0,#BufferTxd
            
            JB     B_WaveLoc2,RD_nAU2
            MOV    A,#08AH
            AJMP   RD_nAU3
            
RD_nAU2:    MOV    A,#08CH
RD_nAU3:    MOVX   @R0,A
            INC    R0
            
            MOV    A,R7
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R6
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R5
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R4
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            
            SETB   TI
;---------------------------------------
            LCALL  DELAY10MS
;---------------------------------------            
            MOV    R0,#BufferAD1   ;ָ������ֵ
            MOV    Cnt_Byte,#16
            LCALL  SORT3Byte       ;����
            MOV    R0,#BufferAD1
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#14          ;�������ֵ
            
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#12          ;�������ֵ
            
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#10          ;�������ֵ
            
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#08          ;�������ֵ
            
            
            MOV    A,R0            ;��ǰ��Ч������ַ
            LCALL  WEIGHT_A1       ;��Ȩ����
            
            MOV    R0,#Buffer_Weight
            MOV    R1,#TOTAL_WEIGHT
            LCALL  DDM_A3
            
            ;LCALL  DDM3            ;ȡƽ��ֵ
            LCALL  GET_AAA_DATA
            ;---------------------------
            MOV    R0,#BufferTxd
            
            JB     B_WaveLoc2,RD_nAU4
            MOV    A,#08BH
            AJMP   RD_nAU5
            
RD_nAU4:    MOV    A,#08DH
RD_nAU5:    MOVX   @R0,A
            INC    R0
            
            MOV    A,R7
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R6
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R5
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R4
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            
            SETB   TI
            
            RET
;-------------------------------------------------
;===========================================================
;��ȡ21λ����
;----------------------------------------------------------
READ_ADDC101:
            LCALL  SYNC_FDS
            MOV    A,REG_IntegConst
            MOV    R7,A
RD_ADDC_A1: LCALL  DELAY1MS
            DJNZ   R7,RD_ADDC_A1
            
            LCALL  SYNC_FDS
            MOV    A,REG_IntegConst
            MOV    R7,A
RD_ADDC_A2: LCALL  DELAY1MS
            DJNZ   R7,RD_ADDC_A2
            
            LCALL  SYNC_FDS
            MOV    A,REG_IntegConst
            MOV    R7,A
RD_ADDC_A3: LCALL  DELAY1MS
            DJNZ   R7,RD_ADDC_A3
            
            LCALL  SYNC_FDS
            MOV    A,REG_IntegConst
            MOV    R7,A
RD_ADDC_A4: LCALL  DELAY1MS
            DJNZ   R7,RD_ADDC_A4
            
            LJMP   DDC101_nRD
;===========================================================
;��ȡ21λ����
;----------------------------------------------------------
READ_DDC101:
            LCALL  SYNC_FDS             ;ʹFDS��SYSCLKͬ��,4��
            ;LCALL  DELAY1MS
            ;LCALL  DELAY1MS
            
            JB     B_TungstenLamp,RD_DDC_A1
            LCALL  DELAYB100US
RD_DDC_A1:  LCALL  DELAYB100US
            
            LCALL  SYNC_FDS
            ;LCALL  DELAY1MS
            ;LCALL  DELAY1MS
            
            JB     B_TungstenLamp,RD_DDC_A2
            LCALL  DELAYB100US
RD_DDC_A2:  LCALL  DELAYB100US
            
            LCALL  SYNC_FDS
            ;LCALL  DELAY1MS
            ;LCALL  DELAY1MS
            
            JB     B_TungstenLamp,RD_DDC_A3
            LCALL  DELAYB100US
RD_DDC_A3:  LCALL  DELAYB100US
            
            LCALL  SYNC_FDS
            ;LCALL  DELAY1MS
            ;LCALL  DELAY1MS
            
            JB     B_TungstenLamp,RD_DDC_A4
            LCALL  DELAYB100US
RD_DDC_A4:  LCALL  DELAYB100US
            
            ;LCALL  DDC101_nRD
;===========================================================
;DDC101��ȡ�ӳ���
;-----------------------------------------------------------
DDC101_nRD:
            MOV    REG_DDC1_L,#0
            MOV    REG_DDC1_M,#0
            MOV    REG_DDC1_H,#0
            
            MOV    REG_DDC2_L,#0
            MOV    REG_DDC2_M,#0
            MOV    REG_DDC2_H,#0
            
            CLR    OUT_SCLK
            NOP
            CLR    OUT_DTE
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    34H,C         ;3        ;BIT1,MSB
            MOV    C,IN_DATA2    ;2
            MOV    54H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    33H,C         ;3        ;BIT2
            MOV    C,IN_DATA2    ;2
            MOV    53H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    32H,C         ;3        ;BIT3
            MOV    C,IN_DATA2    ;2
            MOV    52H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    31H,C         ;3        ;BIT4
            MOV    C,IN_DATA2    ;2
            MOV    51H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    30H,C         ;3        ;BIT5
            MOV    C,IN_DATA2    ;2
            MOV    50H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2FH,C         ;3        ;BIT6
            MOV    C,IN_DATA2    ;2
            MOV    4FH,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2EH,C         ;3        ;BIT7
            MOV    C,IN_DATA2    ;2
            MOV    4EH,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2DH,C         ;3        ;BIT8
            MOV    C,IN_DATA2    ;2
            MOV    4DH,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2CH,C         ;3        ;BIT9
            MOV    C,IN_DATA2    ;2
            MOV    4CH,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2BH,C         ;3        ;BIT10
            MOV    C,IN_DATA2    ;2
            MOV    4BH,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2AH,C         ;3        ;BIT11
            MOV    C,IN_DATA2    ;2
            MOV    4AH,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    29H,C         ;3        ;BIT12
            MOV    C,IN_DATA2    ;2
            MOV    49H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    28H,C         ;3        ;BIT13
            MOV    C,IN_DATA2    ;2
            MOV    48H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    27H,C         ;3        ;BIT14
            MOV    C,IN_DATA2    ;2
            MOV    47H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    26H,C         ;3        ;BIT15
            MOV    C,IN_DATA2    ;2
            MOV    46H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    25H,C         ;3        ;BIT16
            MOV    C,IN_DATA2    ;2
            MOV    45H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    24H,C         ;3        ;BIT17
            MOV    C,IN_DATA2    ;2
            MOV    44H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    23H,C         ;3        ;BIT18
            MOV    C,IN_DATA2    ;2
            MOV    43H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    22H,C         ;3        ;BIT19
            MOV    C,IN_DATA2    ;2
            MOV    42H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    21H,C         ;3        ;BIT20
            MOV    C,IN_DATA2    ;2
            MOV    41H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_SCLK      ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    20H,C         ;3        ;BIT21,LSB
            MOV    C,IN_DATA2    ;2
            MOV    40H,C         ;3
            
            CLR    B_TMR
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            CLR    OUT_SCLK      ;3
            CLR    B_TMR         ;3
            NOP
            NOP
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US      ;����4΢��
;-------------------------------------------------
            SETB   OUT_DTE
            
            MOV    A,REG_DDC1_H
            CJNE   A,#00010000B,XCOMP1
XCOMP1:     JC     XCOMP2
            MOV    REG_DDC1_H,#0
            MOV    REG_DDC1_M,#0
            MOV    REG_DDC1_L,#0
            
XCOMP2:     MOV    A,REG_DDC2_H
            CJNE   A,#00010000B,XCOMP3
XCOMP3:     JC     XCOMP4
            MOV    REG_DDC2_H,#0
            MOV    REG_DDC2_M,#0
            MOV    REG_DDC2_L,#0
            
XCOMP4:     RET
;===========================================================
SYNC_FDS:   JNB    P3.5,$
            NOP
            JB     P3.5,$
            NOP
            JNB    P3.5,$
            
            CLR    B_TMR
            CLR    B_TMR
            
            CLR    OUT_FDS        ;�˴���P3.4ͬ���½�
            LCALL  DELAY8US
            SETB   OUT_FDS
            RET
;===========================================================
;DDC101�����ӳ���
;-----------------------------------------------------------
DDC101_nWR:
            CLR    OUT_SETIN
            CLR    OUT_RSET
            LCALL  DELAY5MS
            SETB   OUT_RSET
            
            CLR    OUT_SCLK
            SETB   C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            CLR    C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            CLR    C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            SETB   C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            SETB   C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            CLR    C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            CLR    C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            CLR    C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            SETB   C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            CLR    C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            CLR    C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            SETB   C
            MOV    OUT_SETIN,C
            LCALL  DELAY1US
            SETB   OUT_SCLK             ;��ʱ�����Ѿ�������
            LCALL  DELAY1US
            ;----------------------
            CLR    OUT_SCLK
            CLR    OUT_SETIN
            LCALL  DELAY10MS
            
            RET
;============================================================
;��Ȩ����
;-----------------------------------------------------------
WEIGHT_A1:
;---------------------------------------
;��Դ�����Ƶ�Ŀ�껺������Դ������ַ��A
;---------------------------------------
WEI_MoveData1:
            MOV    R0,#Buffer_Weight         ;Ŀ�껺��������չRAM
            MOV    R1,A
WEI_MoveData2:
            MOV    A,@R1                     ;ȡ��1������
            MOV    R5,A
            INC    R1
            MOV    A,@R1
            MOV    R6,A
            INC    R1
            MOV    A,@R1
            MOV    R7,A
            INC    R1
            
            MOV    R3,#WEIGHT1
            LCALL  FILL_Data
            ;---------------------------
            MOV    A,@R1                     ;ȡ��1������
            MOV    R5,A
            INC    R1
            MOV    A,@R1
            MOV    R6,A
            INC    R1
            MOV    A,@R1
            MOV    R7,A
            INC    R1
            
            MOV    R3,#WEIGHT2
            LCALL  FILL_Data
             ;---------------------------
            MOV    A,@R1                     ;ȡ��1������
            MOV    R5,A
            INC    R1
            MOV    A,@R1
            MOV    R6,A
            INC    R1
            MOV    A,@R1
            MOV    R7,A
            INC    R1
            
            MOV    R3,#WEIGHT3
            LCALL  FILL_Data
             ;---------------------------
            MOV    A,@R1                     ;ȡ��1������
            MOV    R5,A
            INC    R1
            MOV    A,@R1
            MOV    R6,A
            INC    R1
            MOV    A,@R1
            MOV    R7,A
            INC    R1
            
            MOV    R3,#WEIGHT4
            LCALL  FILL_Data
             ;---------------------------
            MOV    A,@R1                     ;ȡ��1������
            MOV    R5,A
            INC    R1
            MOV    A,@R1
            MOV    R6,A
            INC    R1
            MOV    A,@R1
            MOV    R7,A
            INC    R1
            
            MOV    R3,#WEIGHT5
            LCALL  FILL_Data
             ;---------------------------
            MOV    A,@R1                     ;ȡ��1������
            MOV    R5,A
            INC    R1
            MOV    A,@R1
            MOV    R6,A
            INC    R1
            MOV    A,@R1
            MOV    R7,A
            INC    R1
            
            MOV    R3,#WEIGHT6
            LCALL  FILL_Data
             ;---------------------------
            MOV    A,@R1                     ;ȡ��1������
            MOV    R5,A
            INC    R1
            MOV    A,@R1
            MOV    R6,A
            INC    R1
            MOV    A,@R1
            MOV    R7,A
            INC    R1
            
            MOV    R3,#WEIGHT7
            LCALL  FILL_Data
             ;---------------------------
            MOV    A,@R1                     ;ȡ��1������
            MOV    R5,A
            INC    R1
            MOV    A,@R1
            MOV    R6,A
            INC    R1
            MOV    A,@R1
            MOV    R7,A
            INC    R1
            
            MOV    R3,#WEIGHT8
            LCALL  FILL_Data
            ;---------------------------
            RET
;---------------------------------------

;---------------------------------------
;��Դ�������������,���������R3
;---------------------------------------
FILL_Data:
Fill_D1:    MOV    A,R5
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R6
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R7
            MOVX   @R0,A
            INC    R0
            
            DJNZ   R3,Fill_D1
            RET
;---------------------------------------

;===========================================================
READ_DDC112:
            AJMP   QQQQ
            SETB   OUT_CONV1
            LCALL  DELAY1US
            JB     IN_VALID1,$     ;�ȴ�������Ч
            CLR    B_TMR
            CLR    B_TMR
            LCALL  DELAY1US
            CLR    OUT_SCLK1       ;ʱ��Ҫ����Ϊ�͵�ƽ
            CLR    B_TMR
            CLR    B_TMR
            LCALL  DELAY1US
            CLR    OUT_DXMIT1      ;�����������
            CLR    B_TMR
            CLR    B_TMR           ;��ʱ������׼����
            LCALL  DELAY1US
            LCALL  DDC112_nRD      ;����40bit����
            LCALL  DELAY100US
            LCALL  DELAY1MS
            
            CLR    OUT_CONV1
            LCALL  DELAY1US
            JB     IN_VALID1,$     ;�ȴ�������Ч
            CLR    B_TMR
            CLR    B_TMR
            LCALL  DELAY1US
            CLR    OUT_SCLK1       ;ʱ��Ҫ����Ϊ�͵�ƽ
            CLR    B_TMR
            CLR    B_TMR
            LCALL  DELAY1US
            CLR    OUT_DXMIT1      ;�����������
            CLR    B_TMR
            CLR    B_TMR           ;��ʱ������׼����
            LCALL  DELAY1US
            LCALL  DDC112_nRD      ;����40bit����
            LCALL  DELAY100US
            LCALL  DELAY1MS
            
QQQQ:       ;SETB   OUT_CONV1
            ;LCALL  DELAY1US
			CPL    OUT_CONV1
			LCALL  DELAY100US
            LCALL  DELAY100US
			LCALL  DELAY100US
            LCALL  DELAY100US
			LCALL  DELAY100US
			LCALL  DELAY100US
            LCALL  DELAY100US
			LCALL  DELAY100US
            LCALL  DELAY100US
			LCALL  DELAY100US
            CPL    OUT_CONV1

RD112_A1:   
			LCALL  DELAY100US
            LCALL  DELAY100US
			LCALL  DELAY100US
            LCALL  DELAY100US
			LCALL  DELAY100US
            MOV    R3,#250
RD112_AX1:  JNB    IN_VALID1,RD112_AX2
            ;LCALL  DELAY10US
            DJNZ   R3,RD112_AX1
            CPL    OUT_CONV1
            AJMP   RD112_A1
            
RD112_AX2:  CLR    B_TMR
            CLR    B_TMR
            LCALL  DELAY1US
            CLR    OUT_SCLK1       ;ʱ��Ҫ����Ϊ�͵�ƽ
            CLR    B_TMR
            CLR    B_TMR
            LCALL  DELAY1US
            CLR    OUT_DXMIT1      ;�����������
            CLR    B_TMR
            CLR    B_TMR           ;��ʱ������׼����
            LCALL  DDC112_nRD      ;����40bit����

            MOV    A,REG_DDC1_H	   ;ת�����ݵ�������
            MOV    @R0,A
            INC    R0
            MOV    A,REG_DDC1_M
            MOV    @R0,A
            INC    R0
            MOV    A,REG_DDC1_L
            MOV    @R0,A
            INC    R0
            
            MOV    A,REG_DDC2_H
            MOV    @R1,A
            INC    R1
            MOV    A,REG_DDC2_M
            MOV    @R1,A
            INC    R1
            MOV    A,REG_DDC2_L
            MOV    @R1,A
            INC    R1
            
//            LCALL  DELAY100US	   ;�Žܻ��޸�@2016-05-23����conv�ź�ʱ�����ʱ500us��Ϊ1ms��Ч���ǳ�����
//            LCALL  DELAY100US
//            LCALL  DELAY100US
//            LCALL  DELAY100US
//            LCALL  DELAY100US            
            
            JNB    B_RD_AUH,RD112_A3
            
            JB     B_TungstenLamp,RD112_AX3
            LCALL  DELAY100US           ;��ԭ��ʱ���ٵȴ�ʱ��
            LCALL  DELAY100US
            LCALL  DELAY100US
            ;LCALL  DELAY100US
            ;LCALL  DELAY100US
            ;LCALL  DELAY100US
            
RD112_AX3:  LCALL  DELAY100US
            LCALL  DELAY100US
            ;LCALL  DELAY100US
            ;LCALL  DELAY100US
            ;LCALL  DELAY100US
            ;LCALL  DELAY100US
            
            ;LCALL  DELAY100US
            ;LCALL  DELAY100US
            ;LCALL  DELAY100US
            
            AJMP   RD112_A4
            
RD112_A3:   LCALL  DELAY100US
            LCALL  DELAY100US
            LCALL  DELAY100US
            LCALL  DELAY100US
            LCALL  DELAY100US
            ;LCALL  DELAY1MS
            
RD112_A4:   CPL    OUT_CONV1	  ;ȡ��
            ;LCALL  DELAY1US
            DJNZ   R2,RD112_A1	 ;��ȡ�����Ƿ���
            SETB   OUT_CONV1
            RET
;===========================================================
;DDC112��ȡ�ӳ���
;-----------------------------------------------------------
DDC112_nRD:
            MOV    REG_DDC1_L,#0
            MOV    REG_DDC1_M,#0
            MOV    REG_DDC1_H,#0
            
            MOV    REG_DDC2_L,#0
            MOV    REG_DDC2_M,#0
            MOV    REG_DDC2_H,#0
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    33H,C         ;3        ;BIT20,MSB
            MOV    C,IN_DATA2    ;2
            MOV    53H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    32H,C         ;3        ;BIT19
            MOV    C,IN_DATA2    ;2
            MOV    52H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    31H,C         ;3        ;BIT18
            MOV    C,IN_DATA2    ;2
            MOV    51H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    30H,C         ;3        ;BIT17
            MOV    C,IN_DATA2    ;2
            MOV    50H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2FH,C         ;3        ;BIT16
            MOV    C,IN_DATA2    ;2
            MOV    4FH,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2EH,C         ;3        ;BIT15
            MOV    C,IN_DATA2    ;2
            MOV    4EH,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2DH,C         ;3        ;BIT14
            MOV    C,IN_DATA2    ;2
            MOV    4DH,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2CH,C         ;3        ;BIT13
            MOV    C,IN_DATA2    ;2
            MOV    4CH,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2BH,C         ;3        ;BIT12
            MOV    C,IN_DATA2    ;2
            MOV    4BH,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    2AH,C         ;3        ;BIT11
            MOV    C,IN_DATA2    ;2
            MOV    4AH,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    29H,C         ;3        ;BIT10
            MOV    C,IN_DATA2    ;2
            MOV    49H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    28H,C         ;3        ;BIT9
            MOV    C,IN_DATA2    ;2
            MOV    48H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    27H,C         ;3        ;BIT8
            MOV    C,IN_DATA2    ;2
            MOV    47H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
		    CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    26H,C         ;3        ;BIT7
            MOV    C,IN_DATA2    ;2
            MOV    46H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    25H,C         ;3        ;BIT6
            MOV    C,IN_DATA2    ;2
            MOV    45H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    24H,C         ;3        ;BIT5
            MOV    C,IN_DATA2    ;2
            MOV    44H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    23H,C         ;3        ;BIT4
            MOV    C,IN_DATA2    ;2
            MOV    43H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    22H,C         ;3        ;BIT3
            MOV    C,IN_DATA2    ;2
            MOV    42H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    21H,C         ;3        ;BIT2
            MOV    C,IN_DATA2    ;2
            MOV    41H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            SETB   OUT_SCLK1     ;3,��ʱ��Ч�����Ѿ�����
            MOV    C,IN_DATA1    ;2
            MOV    20H,C         ;3        ;BIT1
            MOV    C,IN_DATA2    ;2
            MOV    40H,C         ;3
            
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR
;-------------------------------------------------
            MOV    R3,#20
DDC112RD_LP:SETB   OUT_SCLK1      ;����ͨ��1����
            CLR    B_TMR
            CLR    B_TMR
			CLR    B_TMR         ;�Žܻ����@2016-05-24
         
            CLR    OUT_SCLK1     ;3
            CLR    B_TMR         ;3
			CLR    B_TMR         ;�Žܻ����@2016-05-24
			CLR    B_TMR

            DJNZ   R3,DDC112RD_LP
;-------------------------------------------------
            SETB   OUT_DXMIT1      ;����������������ź�
;-------------------------------------------------
            ;LJMP   DDC112RD_8
DDC112RD_1: 
            MOV    A,REG_DDC1_H
            JNZ    DDC112RD_3
            MOV    A,REG_DDC1_M
            CJNE   A,#00010001B,DDC112RD_2
DDC112RD_2: JNC    DDC112RD_3

            MOV    REG_DDC1_H,#0             ;��Ч����
            MOV    REG_DDC1_M,#0
            MOV    REG_DDC1_L,#0
            AJMP   DDC112RD_5
            
DDC112RD_3: CLR    C
            MOV    A,REG_DDC1_L
            SUBB   A,#0
            MOV    R4,A
            
            MOV    A,REG_DDC1_M
            SUBB   A,#10H
            MOV    R5,A
            
            MOV    A,REG_DDC1_H
            SUBB   A,#0
            MOV    R6,A
            
            MOV    REG_DDC1_H,R6
            MOV    REG_DDC1_M,R5
            MOV    REG_DDC1_L,R4
;-------------------------------------------------
DDC112RD_5: 
            MOV    A,REG_DDC2_H
            JNZ    DDC112RD_7
            MOV    A,REG_DDC2_M
            CJNE   A,#00010001B,DDC112RD_6
DDC112RD_6: JNC    DDC112RD_7

            MOV    REG_DDC2_H,#0             ;��Ч����
            MOV    REG_DDC2_M,#0
            MOV    REG_DDC2_L,#0
            AJMP   DDC112RD_8
            
DDC112RD_7: CLR    C
            MOV    A,REG_DDC2_L
            SUBB   A,#0
            MOV    R4,A
            
            MOV    A,REG_DDC2_M
            SUBB   A,#10H
            MOV    R5,A
            
            MOV    A,REG_DDC2_H
            SUBB   A,#0
            MOV    R6,A
            
            MOV    REG_DDC2_H,R6
            MOV    REG_DDC2_M,R5
            MOV    REG_DDC2_L,R4
;-------------------------------------------------
DDC112RD_8:
            RET

            ;-------------------------------------
            ;����2
            ;------------------------------------
            CLR   C
            MOV   A,REG_DDC1_H
            RRC   A
            MOV   REG_DDC1_H,A
            
            MOV   A,REG_DDC1_M
            RRC   A
            MOV   REG_DDC1_M,A
            
            MOV   A,REG_DDC1_L
            RRC   A
            MOV   REG_DDC1_L,A

            CLR   C
            MOV   A,REG_DDC2_H
            RRC   A
            MOV   REG_DDC2_H,A
            
            MOV   A,REG_DDC2_M
            RRC   A
            MOV   REG_DDC2_M,A
            
            MOV   A,REG_DDC2_L
            RRC   A
            MOV   REG_DDC2_L,A
            
            RET
            ;-------------------------------------
            ;����4
            ;-------------------------------------
            CLR   C
            MOV   A,REG_DDC1_H
            RRC   A
            MOV   REG_DDC1_H,A
            
            MOV   A,REG_DDC1_M
            RRC   A
            MOV   REG_DDC1_M,A
            
            MOV   A,REG_DDC1_L
            RRC   A
            MOV   REG_DDC1_L,A

            CLR   C
            MOV   A,REG_DDC2_H
            RRC   A
            MOV   REG_DDC2_H,A
            
            MOV   A,REG_DDC2_M
            RRC   A
            MOV   REG_DDC2_M,A
            
            MOV   A,REG_DDC2_L
            RRC   A
            MOV   REG_DDC2_L,A
            
            RET
            ;-------------------------------------
            ;����8
            ;-------------------------------------
            CLR   C
            MOV   A,REG_DDC1_H
            RRC   A
            MOV   REG_DDC1_H,A
            
            MOV   A,REG_DDC1_M
            RRC   A
            MOV   REG_DDC1_M,A
            
            MOV   A,REG_DDC1_L
            RRC   A
            MOV   REG_DDC1_L,A

            CLR   C
            MOV   A,REG_DDC2_H
            RRC   A
            MOV   REG_DDC2_H,A
            
            MOV   A,REG_DDC2_M
            RRC   A
            MOV   REG_DDC2_M,A
            
            MOV   A,REG_DDC2_L
            RRC   A
            MOV   REG_DDC2_L,A
            
            RET
;=================================================
;-------------------------------------------------
SET_RANGE:
            MOV    A,TimeConst
            CJNE   A,#8,SET_R1
            CLR    AD_RANGE2       ;50pc
            CLR    AD_RANGE1
            SETB   AD_RANGE0
            RET
            
SET_R1:     CJNE   A,#4,SET_R2
            CLR    AD_RANGE2       ;150pc
            SETB   AD_RANGE1
            SETB   AD_RANGE0
            RET

SET_R2:     CJNE   A,#2,SET_R3
            SETB   AD_RANGE2       ;250pc
            CLR    AD_RANGE1
            SETB   AD_RANGE0
            RET

SET_R3:     CJNE   A,#1,SET_R4
            SETB   AD_RANGE2       ;350pc
            SETB   AD_RANGE1
            SETB   AD_RANGE0
            RET

SET_R4:     ;CJNE   A,#8,SET_R1
            CLR    AD_RANGE2       ;50pc
            CLR    AD_RANGE1
            SETB   AD_RANGE0
            RET
;---------------------------------------
INIT_AD9850:
            CLR    DDS_P_WCLK
            CLR    DDS_P_FQUD
            LCALL  DELAY5US
            
            CLR    DDS_P_RST
            LCALL  DELAY5US
            SETB   DDS_P_RST
            LCALL  DELAY5US
            CLR    DDS_P_RST
            LCALL  DELAY5US
            
            CLR    DDS_P_WCLK
            LCALL  DELAY5US
            SETB   DDS_P_WCLK
            LCALL  DELAY5US
            CLR    DDS_P_WCLK
            LCALL  DELAY5US
            
            CLR    DDS_P_FQUD
            LCALL  DELAY5US
            SETB   DDS_P_FQUD
            LCALL  DELAY5US
            CLR    DDS_P_FQUD
            LCALL  DELAY1MS
            
            ;LCALL  SEND_DDS_DATA
            
            RET    
;===========================================================
GET_DDS_DATA:
            MOV    A,REG_DATA1
            ANL    A,#07FH
            MOV    REG_DATA1,A
            
            MOV    A,REG_DATA2
            ANL    A,#07FH
            MOV    REG_DATA2,A
            
            MOV    A,REG_DATA3
            ANL    A,#07FH
            MOV    REG_DATA3,A
            
            MOV    A,REG_DATA4
            ANL    A,#07FH
            MOV    REG_DATA4,A
;--------------------------------------- 
            CLR    C
            MOV    A,REG_DATA3
            RRC    A
            MOV    REG_DATA3,A
            
            MOV    A,REG_DATA4
            MOV    ACC.7,C
            MOV    REG_DATA4,A
;---------------------------------------            
            CLR    C
            MOV    A,REG_DATA2
            RRC    A
            MOV    REG_DATA2,A
            
            MOV    A,REG_DATA3
            MOV    ACC.6,C
            MOV    REG_DATA3,A
            
            CLR    C
            MOV    A,REG_DATA2
            RRC    A
            MOV    REG_DATA2,A
            
            MOV    A,REG_DATA3
            MOV    ACC.7,C
            MOV    REG_DATA3,A
 ;--------------------------------------
            CLR    C
            MOV    A,REG_DATA1
            RRC    A
            MOV    REG_DATA1,A
            
            MOV    A,REG_DATA2
            MOV    ACC.5,C
            MOV    REG_DATA2,A
            
            CLR    C
            MOV    A,REG_DATA1
            RRC    A
            MOV    REG_DATA1,A
            
            MOV    A,REG_DATA2
            MOV    ACC.6,C
            MOV    REG_DATA2,A
            
            CLR    C
            MOV    A,REG_DATA1
            RRC    A
            MOV    REG_DATA1,A
            
            MOV    A,REG_DATA2
            MOV    ACC.7,C
            MOV    REG_DATA2,A
            
            RET
;===========================================================
;MAX187(SOL-16) ��ȡ����
;-----------------------------------------------------------
MAX187_CS       BIT     P1.3
MAX187_DATA     BIT     P1.4
MAX187_SCLK     BIT     P1.5
;-----------------------------------------------------------
MAX187_READ:
            MOV    REG_MAX187H,#0
            MOV    REG_MAX187L,#0
            MOV    B,#0
            
            SETB   MAX187_CS
            CLR    MAX187_SCLK
            SETB   B_TMR
            
            CLR    MAX187_CS           ;MAX187��Ч
            LCALL  DELAY10US           ;ת������Ϊ8.5us;
            LCALL  DELAY10US
            
            SETB   MAX187_SCLK         ;����ǰ��λ
            LCALL  DELAY1US
            CLR    MAX187_SCLK
            
            MOV    R2,#12
MAX187_RD_LOOP:
            SETB   MAX187_SCLK
            LCALL  DELAY1US
            MOV    C,MAX187_DATA
            
            MOV    A,REG_MAX187L
            RLC    A
            MOV    REG_MAX187L,A
            MOV    A,REG_MAX187H
            RLC    A
            MOV    REG_MAX187H,A
            
            CLR    MAX187_SCLK
            LCALL  DELAY1US
            DJNZ   R2,MAX187_RD_LOOP
            
            RET
;===========================================================
INIT_IM481H:
            SETB   A_RST                ;��ʼ�ߵ�ƽ,�������ͨ,�͵�ƽ��λIM481H
            SETB   A_PUL                ;��ʼ�ߵ�ƽ,�������ͨ,�͵�ƽ��IM481H�������
            CLR    A_DIR                ;��ʱ��-��������
            LCALL  DELAY50M
            CLR    A_RST                ;IM481H��λ����
            LCALL  DELAY50M
            RET
;===========================================================
INIT_DDC112:
            LCALL  SET_RANGE
            SETB   OUT_DXMIT1      ;DXMITΪ��ʱ,SCLKΪ��
            CLR    OUT_SCLK1
            SETB   OUT_CONV1		   ;CONV:�ߵ͸ߣ�������������ģʽ
            LCALL  DELAY50M
            CLR    OUT_CONV1
            LCALL  DELAY50M
            SETB   OUT_CONV1
            LCALL  DELAY50M
            RET
;===========================================================
INIT_DDC101:
            CLR    OUT_SCLK
            CLR    OUT_SETIN
            CLR    OUT_RSET
            CLR    OUT_RST
            LCALL  DELAY1S
            SETB   OUT_RSET
            SETB   OUT_RST
            LCALL  DELAY100M

            LCALL  CLK_ON_P35                ;��DDC101���2MHz����
            LCALL  DDC101_nWR                ;����DDC101
            LCALL  DDC101_nWR
            RET
;===========================================================
AB_ATR0:    MOV    R2,A
            ANL    A,#0FH
            XCH    A,R2
            SWAP   A
            ANL    A,#0FH
            CLR    C
            ;ADD    A,#30H
            MOV    @R0,A
            INC    R0
            MOV    A,R2
            ;ADD    A,#30H
            MOV    @R0,A
            INC    R0
            RET
;==========================================================
;ˢ�²���
;----------------------------------------------------------
Refresh_Para:
            MOV    R0,#BufferPARA
            MOV    R1,#BufferEeprom
            MOV    R2,#8
Refresh_P1: MOV    A,@R0
            MOV    @R1,A
            INC    R0
            INC    R1
            DJNZ   R2,Refresh_p1
            
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#0
            LCALL  EraseEeprom_Sec
            
            MOV    R0,#BufferEeprom
            MOV	   R2,#8
            LCALL  TXBCH	                   ;�õ�BCHУ����
            MOV    R0,#BufferEeprom
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#A_DevPara
            MOV    R2,#9
            LCALL  WrEeprom
            MOV    R0,#BufferEeprom
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#A_1DevPara
            MOV    R2,#9
            LCALL  WrEeprom
            MOV    R0,#BufferEeprom
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#A_2DevPara
            MOV    R2,#9
            LCALL  WrEeprom
            LCALL  INIT_PARA
            LCALL  SET_RANGE
            
            RET
;==========================================================
INIT_PARA:  
            MOV    DEVNUMBER,#01H
            ;MOV    AlarmCnt,#10
ChkPara2:   MOV    R6,#3                     ;д��ʧ����д����
CHKPARA3:   MOV    R7,#5                     ;������ض���������
RdParalp:   MOV    R0,#BufferEeprom
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#A_DevPara      ;Դ���ݵ�ַ
            MOV    R2,#9                     ;8 PARA ADD 1 BCH
            LCALL  ReadEeprom
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#A_1DevPara
            MOV    R2,#9
            LCALL  ReadEeprom
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#A_2DevPara
            MOV    R2,#9
            LCALL  ReadEeprom                ;����3�����
;----------------------------------------------------------
            MOV    R0,#BufferEeprom
            MOV	   R2,#9
            LCALL  BCH_CHECK                 ;����BCHУ��
            JNZ    ReadParaErr
            MOV    R2,#9
            LCALL  BCH_CHECK
            JNZ    ReadParaErr
            MOV    R2,#9
            LCALL  BCH_CHECK
            JNZ    ReadParaErr
;----------------------------------------------------------
            MOV    R0,#BufferEeprom
            MOV    B,@R0                     ;��1�����
            MOV    A,#BufferEeprom
            ADD    A,#9
            MOV    R0,A
            MOV    A,@R0                     ;��2�����
            CJNE   A,B,ReadParaErr
            MOV    A,#BufferEeprom
            ADD    A,#18
            MOV    R0,A
            MOV    A,@R0                     ;��3�����
            CJNE   A,B,ReadParaErr
;----------------------------------------------------------
;            CJNE   A,#0,CHK_ADDR
;            LJMP   ReadParaErr
;CHK_ADDR:   CJNE   A,#255,CFG_GOOD
;            LJMP   ReadParaErr
CFG_GOOD:   LJMP   CFG_GOOOD
;----------------------------------------------------------
ReadParaErr:DJNZ   R7,RDPARALP               ;�ظ���ȡ������

PITCH_A2:   MOV    R2,#9
            MOV    R0,#BufferEeprom
            LCALL  BCH_CHECK
            JZ     WRITE_PARA
            
PITCH_B1:   MOV    R1,#BufferEeprom
            MOV    A,R1
            ADD    A,#9
            MOV    R0,A
            MOV    R2,#9
PITCH_B2:   MOV    A,@R0
            MOV    @R1,A
            INC    R0
            INC    R1
            DJNZ   R2,PITCH_B2
            MOV    R0,#BufferEeprom
            MOV    R2,#9
            MOV    R0,#BufferEeprom
            LCALL  BCH_CHECK
            JZ     WRITE_PARA
            
PITCH_C1:   MOV    R1,#BufferEeprom
            MOV    A,R1
            ADD    A,#18
            MOV    R0,A
            MOV    R2,#9
PITCH_C2:   MOV    A,@R0
            MOV    @R1,A
            INC    R0
            INC    R1
            DJNZ   R2,PITCH_C2
            MOV    R0,#BufferEeprom
            MOV    R2,#9
            MOV    R0,#BufferEeprom
            LCALL  BCH_CHECK
            JZ     WRITE_PARA
            
PITCH_C6:   MOV    R0,#BufferEeprom
            MOV    @R0,#0                    ;DeutTungst,뮵�
            INC    R0
            MOV    @R0,#001                  ;TimeConst,1/8---------8/50,4/150,2/250,1/350
            INC    R0
            MOV    @R0,#012H                 ;PARA3
            INC    R0
            MOV	   @R0,#012H                 ;PARA4
            INC    R0
            MOV	   @R0,#002H                 ;VER1��������İ汾��Ϊ2.x.x��
            INC    R0
            MOV    @R0,#002H                 ;VER2
            INC    R0
            MOV    @R0,#007H                 ;VER3
            INC    R0
            MOV    @R0,#0                    ;RES1
            MOV    R2,#8
            MOV    R0,#BufferEeprom
            LCALL  TXBCH                     ;BCH
WRITE_PARA:      
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#0
            LCALL  EraseEeprom_Sec
            
            MOV    R0,#BufferEeprom
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#A_DevPara
            MOV    R2,#9
            LCALL  WrEeprom
            MOV    R0,#BufferEeprom
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#A_1DevPara
            MOV    R2,#9
            LCALL  WrEeprom
            MOV    R0,#BufferEeprom
            MOV    IAP_ADDRH,#0
            MOV    IAP_ADDRL,#A_2DevPara
            MOV    R2,#9
            LCALL  WrEeprom
            DJNZ   R6,CHKPARAQ
            LJMP   CHKPARA5
CHKPARAQ:   LJMP   CHKPARA3                  ;������д5��
CHKPARA5:   
            ;LCALL  DISP_PARA_Err
            ;DJNZ   AlarmCnt,CHKPARA6
            LJMP   ERR_PIT
;CHKPARA6:   LJMP   CHKPARA2
;----------------------------------------------------------
CFG_GOOOD:  MOV    R0,#BufferEeprom
            MOV    R2,#8
            MOV    R1,#BufferPARA
SHIFT_CFG:  MOV    A,@R0
            MOV    @R1,A
            INC    R0
            INC    R1
            DJNZ   R2,SHIFT_CFG
            
            MOV    A,DeutTungst
            JZ     CFG_G2
            SETB   B_TungstenLamp            ;�ٵ�
            AJMP   CFG_G3
CFG_G2:     CLR    B_TungstenLamp            ;뮵�
            ;-----------------------------------------
CFG_G3:     MOV    A,TimeConst
            CJNE   A,#8,CFG_H2
            MOV    REG_IntegConst,#2
            AJMP   CFG_H5
            
CFG_H2:     CJNE   A,#4,CFG_H3
            MOV    REG_IntegConst,#4
            AJMP   CFG_H5

CFG_H3:     CJNE   A,#2,CFG_H4
            MOV    REG_IntegConst,#8
            AJMP   CFG_H5

CFG_H4:     
            MOV    REG_IntegConst,#16
            
CFG_H5:     RET
;===========================================================
;�����תָ������
;-----------------------------------------------------------
SET_MOTOR_ROLL:           
            MOV    REG_StepH,REG_DATA3
            MOV    REG_StepL,REG_DATA4
            
            MOV    A,REG_Grade
            CJNE   A,#1,SMR1
            LCALL  TURN_0STEP           ;250Hz
            AJMP   SMR6
SMR1:    
            CJNE   A,#2,SMR2
            LCALL  TURN_1STEP           ;500Hz
            AJMP   SMR6
SMR2:    
            CJNE   A,#3,SMR3
            LCALL  TURN_2STEP           ;1000Hz
            AJMP   SMR6
SMR3:    
            CJNE   A,#4,SMR4
            LCALL  TURN_3STEP           ;2500Hz
            AJMP   SMR6
SMR4:    
            CJNE   A,#5,SMR5
            LCALL  TURN_4STEP           ;5000Hz
            AJMP   SMR6
SMR5:    
            CJNE   A,#6,SMR6
            LCALL  TURN_5STEP           ;10000Hz
SMR6:       RET
;===========================================================
;������������Զ���ת:
;-----------------------------------------------------------
AUTO_ROLL_ON: 
            SETB   A_PUL                ;��ʼʱΪ�ߵ�ƽ,�����ͨ����ʹIM481H������Ϊ�͵�ƽ
            ;CLR    A_DIR                ;��ʱ��-��������
            
            
A_R_ON_0:   MOV    A,REG_Grade
            
            CJNE   A,#1,A_R_ON_1
            MOV    TH1,#044H            ;250Hz@24MHz
            MOV    TL1,#080H
            AJMP   A_R_ON_7
A_R_ON_1:    
            CJNE   A,#2,A_R_ON_2
            MOV    TH1,#0A2H            ;500Hz@24MHz
            MOV    TL1,#040H
            AJMP   A_R_ON_7
A_R_ON_2:    
            CJNE   A,#3,A_R_ON_3
            MOV    TH1,#0D1H            ;1000Hz@24MHz
            MOV    TL1,#020H
            AJMP   A_R_ON_7
A_R_ON_3:    
            CJNE   A,#4,A_R_ON_4
            MOV    TH1,#0EDH            ;2500Hz@24MHz
            MOV    TL1,#040H
            AJMP   A_R_ON_7
A_R_ON_4:    
            CJNE   A,#5,A_R_ON_5
            MOV    TH1,#0F6H            ;5000Hz@24MHz
            MOV    TL1,#0A0H
            AJMP   A_R_ON_7
A_R_ON_5:    
            CJNE   A,#6,A_R_ON_6
            MOV    TH1,#0FBH            ;10000Hz@24MHz
            MOV    TL1,#050H
            AJMP   A_R_ON_7
            
A_R_ON_6:   AJMP   CLK_OFF_P34         ;���ݷǷ�,ֱ��ͣת
            

A_R_ON_7:   
;-----------------------------------------------------------
CLK_ON_P34: MOV    A,WAKE_CLKO
            ORL    A,#00000010B         ;P34���ʱ��
            MOV    WAKE_CLKO,A
            ;MOV    TH1,#0FBH            ;P34���10KHz�����IMH481
            ;MOV    TL1,#050H
            SETB   TR1
            RET
;-----------------------------------------------------------
;P35�̶����2MHz����,��DDC101;
;-----------------------------------------------------------
CLK_ON_P35: MOV    A,WAKE_CLKO
            ORL    A,#00000001B         ;P35���ʱ��
            MOV    WAKE_CLKO,A
            MOV    TH0,#0FFH            ;P35���2MHz����
            MOV    TL0,#0FAH
            SETB   TR0
            LCALL  DELAY5MS
            RET
;----------------------------------------------------------
CLK_OFF_P34:
            CLR    TR1
            CLR    ET1
            CLR    TF1
            MOV    A,WAKE_CLKO
            ANL    A,#11111101B
            MOV    WAKE_CLKO,A          ;P34�����ʱ��
            SETB   P3.4                 ;A_PUL��Ĭʱ��Ϊ�ߵ�ƽ,�����ͨ����ʹIM481H������Ϊ�͵�ƽ
            LCALL  DELAY1MS
            SETB   P3.4
            RET
;----------------------------------------------------------
CLK_OFF_P35:
            CLR    TR0
            CLR    ET0
            CLR    TF0
            MOV    A,WAKE_CLKO
            ANL    A,#11111110B
            MOV    WAKE_CLKO,A          ;P35�����ʱ��
            CLR    P3.5                 ;DDC101��CLK��ĬʱΪ�͵�ƽ
            RET
;===========================================================
;���������ת����
;�������Ƶ��ԼΪ250Hz
;-----------------------------------------------------------
TURN_0STEP: 
            MOV    Cnt_Roll_H,REG_StepH
            MOV    Cnt_Roll_L,REG_StepL
            SETB   A_PUL                ;��ʼʱΪ�ߵ�ƽ,�����ͨ����ʹIM481H������Ϊ�͵�ƽ
T_0STEP_A1: 
            MOV    A,Cnt_Roll_L
            JNZ    T_0STEP_A2
            MOV    A,Cnt_Roll_H
            JNZ    T_0STEP_A2
            AJMP   T_0STEP_A9           ;������Ϊ0ֱ���˳�
            
T_0STEP_A2: CLR    A_PUL                ;IM481H�����
            LCALL  DELAY1MS
            LCALL  DELAY1MS
            SETB   A_PUL                ;IM481H�����
            LCALL  DELAY1MS
            LCALL  DELAY1MS
            
            MOV    A,Cnt_Roll_L
            JNZ    T_0STEP_A3
            
            MOV    Cnt_Roll_L,#0FFH
            MOV    A,Cnt_Roll_H
            DEC    A
            MOV    Cnt_Roll_H,A
            AJMP   T_0STEP_A2
            ;---------------------------
T_0STEP_A3: MOV    A,Cnt_Roll_L
            DEC    A
            MOV    Cnt_Roll_L,A         ;���ֽڼ�1
            JNZ    T_0STEP_A2

            MOV    A,Cnt_Roll_H
            JZ     T_0STEP_A9           ;������ȫ������
            AJMP   T_0STEP_A2
T_0STEP_A9: 
            SETB   A_PUL
            RET

;===========================================================
;���������ת����
;�������Ƶ��ԼΪ500Hz
;-----------------------------------------------------------
TURN_1STEP: 
            MOV    Cnt_Roll_H,REG_StepH
            MOV    Cnt_Roll_L,REG_StepL
            SETB   A_PUL                ;��ʼʱΪ�ߵ�ƽ,�����ͨ����ʹIM481H������Ϊ�͵�ƽ
T_1STEP_A1: 
            MOV    A,Cnt_Roll_L
            JNZ    T_1STEP_A2
            MOV    A,Cnt_Roll_H
            JNZ    T_1STEP_A2
            LJMP   T_1STEP_A9           ;������Ϊ0ֱ���˳�
            
T_1STEP_A2: CLR    A_PUL                ;IM481H�����
            LCALL  DELAY1MS
            ;LCALL  DELAY1MS
            SETB   A_PUL                ;IM481H�����
            LCALL  DELAY1MS
            ;LCALL  DELAY1MS
            
            MOV    A,Cnt_Roll_L
            JNZ    T_1STEP_A3
            
            MOV    Cnt_Roll_L,#0FFH
            MOV    A,Cnt_Roll_H
            DEC    A
            MOV    Cnt_Roll_H,A
            LJMP   T_1STEP_A2
            ;---------------------------
T_1STEP_A3: MOV    A,Cnt_Roll_L
            DEC    A
            MOV    Cnt_Roll_L,A         ;���ֽڼ�1
            JNZ    T_1STEP_A2

            MOV    A,Cnt_Roll_H
            JZ     T_1STEP_A9           ;������ȫ������
            LJMP   T_1STEP_A2
T_1STEP_A9: 
            SETB   A_PUL
            RET
;===========================================================
;���������ת����
;�������Ƶ��ԼΪ1000Hz
;-----------------------------------------------------------
TURN_2STEP: 
            MOV    Cnt_Roll_H,REG_StepH
            MOV    Cnt_Roll_L,REG_StepL
            SETB   A_PUL                ;��ʼʱΪ�ߵ�ƽ,�����ͨ����ʹIM481H������Ϊ�͵�ƽ
T_2STEP_A1: 
            MOV    A,Cnt_Roll_L
            JNZ    T_2STEP_A2
            MOV    A,Cnt_Roll_H
            JNZ    T_2STEP_A2
            LJMP   T_2STEP_A9           ;������Ϊ0ֱ���˳�
            
T_2STEP_A2: CLR    A_PUL                ;IM481H�����
            LCALL  DELAY100US
            LCALL  DELAY100US
            LCALL  DELAY100US
            LCALL  DELAY100US
            LCALL  DELAY100US
            SETB   A_PUL                ;IM481H�����
            LCALL  DELAY100US
            LCALL  DELAY100US
            LCALL  DELAY100US
            LCALL  DELAY100US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            
            MOV    A,Cnt_Roll_L
            JNZ    T_2STEP_A3
            
            MOV    Cnt_Roll_L,#0FFH
            MOV    A,Cnt_Roll_H
            DEC    A
            MOV    Cnt_Roll_H,A
            LJMP   T_2STEP_A2
            ;---------------------------
T_2STEP_A3: MOV    A,Cnt_Roll_L
            DEC    A
            MOV    Cnt_Roll_L,A         ;���ֽڼ�1
            JNZ    T_2STEP_A2

            MOV    A,Cnt_Roll_H
            JZ     T_2STEP_A9           ;������ȫ������
            LJMP   T_2STEP_A2
T_2STEP_A9: 
            SETB   A_PUL
            RET
;===========================================================
;���������ת����
;�������Ƶ��ԼΪ2500Hz
;-----------------------------------------------------------
TURN_3STEP: 
            MOV    Cnt_Roll_H,REG_StepH
            MOV    Cnt_Roll_L,REG_StepL
            SETB   A_PUL                ;��ʼʱΪ�ߵ�ƽ,�����ͨ����ʹIM481H������Ϊ�͵�ƽ
T_3STEP_A1: 
            MOV    A,Cnt_Roll_L
            JNZ    T_3STEP_A2
            MOV    A,Cnt_Roll_H
            JNZ    T_3STEP_A2
            LJMP   T_3STEP_A9           ;������Ϊ0ֱ���˳�
            
T_3STEP_A2: CLR    A_PUL                ;IM481H�����
            LCALL  DELAY100US
            LCALL  DELAY100US
            SETB   A_PUL                ;IM481H�����
            LCALL  DELAYA100US
            LCALL  DELAYA100US
            LCALL  DELAY1US
            ;LCALL  DELAY1US
            ;CLR    B_TMR
            ;CLR    B_TMR
            
            MOV    A,Cnt_Roll_L
            JNZ    T_3STEP_A3
            
            MOV    Cnt_Roll_L,#0FFH
            MOV    A,Cnt_Roll_H
            DEC    A
            MOV    Cnt_Roll_H,A
            LJMP   T_3STEP_A2
            ;---------------------------
T_3STEP_A3: MOV    A,Cnt_Roll_L
            DEC    A
            MOV    Cnt_Roll_L,A         ;���ֽڼ�1
            JNZ    T_3STEP_A2

            MOV    A,Cnt_Roll_H
            JZ     T_3STEP_A9           ;������ȫ������
            LJMP   T_3STEP_A2
T_3STEP_A9: 
            SETB   A_PUL
            RET
;===========================================================
;���������ת����
;�������Ƶ��ԼΪ5000Hz
;-----------------------------------------------------------
TURN_4STEP: 
            MOV    Cnt_Roll_H,REG_StepH
            MOV    Cnt_Roll_L,REG_StepL
            SETB   A_PUL                ;��ʼʱΪ�ߵ�ƽ,�����ͨ����ʹIM481H������Ϊ�͵�ƽ
T_4STEP_A1: 
            MOV    A,Cnt_Roll_L
            JNZ    T_4STEP_A2
            MOV    A,Cnt_Roll_H
            JNZ    T_4STEP_A2
            LJMP   T_4STEP_A9           ;������Ϊ0ֱ���˳�
            
T_4STEP_A2: CLR    A_PUL                ;IM481H�����
            LCALL  DELAY100US
            SETB   A_PUL                ;IM481H�����
            LCALL  DELAYA100US
            
            MOV    A,Cnt_Roll_L
            JNZ    T_4STEP_A3
            
            MOV    Cnt_Roll_L,#0FFH
            MOV    A,Cnt_Roll_H
            DEC    A
            MOV    Cnt_Roll_H,A
            LJMP   T_4STEP_A2
            ;---------------------------
T_4STEP_A3: MOV    A,Cnt_Roll_L
            DEC    A
            MOV    Cnt_Roll_L,A         ;���ֽڼ�1
            JNZ    T_4STEP_A2

            MOV    A,Cnt_Roll_H
            JZ     T_4STEP_A9           ;������ȫ������
            LJMP   T_4STEP_A2
T_4STEP_A9: 
            SETB   A_PUL
            RET
;===========================================================
;���������ת����:   1.���ÿ��0.9��,ÿȦ400��,256ϸ��ʱһȦΪ102400����,ÿ�ȵ�������Ϊ284.444��
;                      ����ÿ��8nm����,��ʵ��0.1nm�ľ���,������Ϊ3-4��
;                      ����ÿ������Ķ�Ӧ8/284.444=0.02815nm
;                      ��1nm��������Ϊ35.5
;                    2.��ת������REG_STEPH,REG_STEPL
;                    3.��ʱ��1���ʱ������
;-----------------------------------------------------------
TURN_5STEP: 
            MOV    Cnt_Roll_H,REG_StepH
            MOV    Cnt_Roll_L,REG_StepL
            SETB   A_PUL                ;��ʼʱΪ�ߵ�ƽ,�����ͨ����ʹIM481H������Ϊ�͵�ƽ
T_5STEP_A1: 
            MOV    A,Cnt_Roll_L
            JNZ    T_5STEP_A2
            MOV    A,Cnt_Roll_H
            JNZ    T_5STEP_A2
            AJMP   T_5STEP_A9           ;������Ϊ0ֱ���˳�
            
T_5STEP_A2: CLR    A_PUL                ;IM481H�����
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY10US
            LCALL  DELAY5US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            ;LCALL  DELAY1US
            
            SETB   A_PUL                ;IM481H�����
            LCALL  DELAY10US
            LCALL  DELAY5US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            LCALL  DELAY1US
            ;LCALL  DELAY1US
            
            
            CLR    B_TMR
            CLR    B_TMR
            CLR    B_TMR
            CLR    B_TMR
            CLR    B_TMR
            CLR    B_TMR
            CLR    B_TMR
            CLR    B_TMR
            NOP
            NOP
            
            MOV    A,Cnt_Roll_L
            JNZ    T_5STEP_A3
            
            MOV    Cnt_Roll_L,#0FFH
            MOV    A,Cnt_Roll_H
            DEC    A
            MOV    Cnt_Roll_H,A
            AJMP   T_5STEP_A2
            ;---------------------------
T_5STEP_A3: MOV    A,Cnt_Roll_L
            DEC    A
            MOV    Cnt_Roll_L,A         ;���ֽڼ�1
            JNZ    T_5STEP_A2

            MOV    A,Cnt_Roll_H
            JZ     T_5STEP_A9           ;������ȫ������
            AJMP   T_5STEP_A2
T_5STEP_A9: 
            SETB   A_PUL
            RET
;===========================================================
;���������ת����:   1.���ÿ��0.9��,ÿȦ400��,256ϸ��ʱһȦΪ102400����
;                    2.��ת������REG_STEPH,REG_STEPL
;                    3.��ʱ��1���ʱ������
;-----------------------------------------------------------
TURN_nSTEP: 
            MOV    Cnt_Roll_H,#0        ;Ԥ��ת�����������
            MOV    Cnt_Roll_L,#0
            SETB   A_PUL                ;��ʼʱΪ�ߵ�ƽ,�����ͨ����ʹIM481H������Ϊ�͵�ƽ
            CLR    A_DIR                ;��ʱ��-��������
            
            MOV    TL1,#0C0H            ;245HZ
            MOV    TH1,#038H
            CLR    TF1
            SETB   TR1                  ;������ʱ��,�������
            
T_nSTEP_A1: JNB    A_PUL,T_nSTEP_A1     ;�ȴ�������
T_nSTEP_A2: JB     A_PUL,$              ;�ȴ��������ɱ�����
            INC    Cnt_Roll_L
            MOV    A,Cnt_Roll_L
            JNZ    T_nSTEP_A3
            INC    Cnt_Roll_H
            ;---------------------------
T_nSTEP_A3: MOV    A,Cnt_Roll_H
            CJNE   A,#REG_StepH,T_nSTEP_A4
T_nSTEP_A4: JC     T_nSTEP_A1
            CJNE   A,#REG_StepH,T_nSTEP_A6
            MOV    A,Cnt_Roll_L
            CJNE   A,#REG_StepL,T_nSTEP_A5
T_nSTEP_A5: JC     T_nSTEP_A1

T_nSTEP_A6: 
            CLR    TR1
            CLR    ET1
            CLR    TF1
            RET
;==========================================================
INT_EXT0:   
            PUSH   B
            PUSH   PSW
            PUSH   ACC
            PUSH   Cnt_Byte
            SETB   RS0
            CLR    RS1
            
            CLR    EX0
            ;SETB   B_KEY

INT_EX0END:
            POP    Cnt_Byte
            POP    ACC
            POP    PSW
            POP    B
            RETI
;==========================================================
INT_EXT1:   
            PUSH   B
            PUSH   PSW
            PUSH   ACC
            PUSH   Cnt_Byte
            
            SETB   RS0
            CLR    RS1
            
            CLR    EX1
;---------------------------------------
            ;LCALL  RD_LCDTXD
;---------------------------------------

INT1_KEY_END:
            POP    Cnt_Byte
            POP    ACC
            POP    PSW
            POP    B
            RETI
;==========================================================
;��ʱ��0�жϴ���
;----------------------------------------------------------
INT_TMR0:   
            PUSH   B
            PUSH   PSW
            PUSH   ACC
            PUSH   Cnt_Byte
            SETB   RS0
            CLR    RS1
            
            ;MOV    TH0,#063H           ;T0�ж�����Ϊ5����(8MHz,1T)
            ;MOV    TL0,#0C0H

            MOV    TH0,#0FFH           ;T0�ж�����Ϊ5����(24MHz,12T)
            MOV    TL0,#0FAH
            ;------------------------------------

INT_T0_MH1: ;SETB   B_5MS
            
            INC    TMR_T0_1S
            MOV    A,TMR_T0_1S
            CJNE   A,#200,INT_T0A
INT_T0A:    JC     INT_T0F
            ;SETB   B_SECOND
            
            MOV    TMR_T0_1S,#0
            
INT_T0F:    POP    Cnt_Byte
            POP    ACC
            POP    PSW
            POP    B

            RETI
;===========================================================
;��ʱ��1�жϴ���
;----------------------------------------------------------
INT_TMR1:   PUSH   B
            PUSH   PSW
            PUSH   ACC
            PUSH   Cnt_Byte
            SETB   RS0
            CLR    RS1
            
;            INC    Cnt_TmrL                  ;ÿ10�����1
;            MOV    A,Cnt_TmrL
;            CJNE   A,#100,INT_T1A            ;1��
;INT_T1A:    JC     INT_T1B
;            INC    Cnt_TmrH
;            MOV    Cnt_TmrL,#0
;INT_T1B:    MOV    TH1,#0DCH                 ;11.0592M����,��������12/11.0592=1.085΢��,(10000H-0DC00H)*(12/11.0592)=10ms
;            MOV    TL1,#000H
;            MOV    A,Cnt_TmrH
;            CJNE   A,#10,INT_T1C             ;10��
;INT_T1C:    JC     INT_T1D
;            SETB   B_Obstruct                ;��λת����ʱ����
;            CLR    TR1
            
INT_T1D:    POP    Cnt_Byte
            POP    ACC
            POP    PSW
            POP    B
            RETI
;==========================================================
INT_UART:   CLR    EA                        ;���п��жϷ����ӳ���
            ;ANL    PCON,#0FCH
            ORL    AUXR1,#1                  ;ʹ��DPTR1
            PUSH   B
            PUSH   PSW
            PUSH   ACC
            PUSH   Cnt_Byte
            SETB   RS0
            CLR    RS1
            JNB    RI,UART_NEXT
            LCALL  UART_RXDSA
            LJMP   UART_END
UART_NEXT:  JNB    TI,UART_END
            LCALL  UART_TXDA
UART_END:   POP    Cnt_Byte
            POP    ACC
            POP    PSW
            POP    B
            ANL    AUXR1,#0FEH               ;ʹ��DPTR0
            SETB   EA
            RETI
;==========================================================
UART_RXDSA: CLR    RI
            
            ;---------------------------
            ;��������ʱ�˳�����
            ;---------------------------
            ;JNB    TI,UART_RXD01
            ;;CLR    B_Rcving
            ;LJMP   RXD_TXD1
            
            ;ANL    CounterRxd,#0
            ANL    CounterTxd,#0
            CLR   TI
            ;---------------------------
            
UART_RXD01: MOV    A,SBUF
            
UART_RXD5:  MOV    R2,A                ;�ݴ���յ��������ֽ�
            
            JB     B_Rcving,UART_RXD65
            ANL    A,#0F0H
            CJNE   A,#080H,UART_RXD63    ;�߰��ֽ�Ϊ80H
            LJMP   UART_RXD64
            
UART_RXD63: LJMP   RXD_IGNORE
            
UART_RXD64: SETB   B_RCVING
            LJMP   UART_RXD66
            
UART_RXD65: MOV    A,R2
            JNB    ACC.7,UART_RXD66      ;���λΪ0
            LJMP   RXD_IGNORE
            
UART_RXD66: MOV    A,CounterRxd
            ADD    A,#BufferRxd
            MOV    R0,A
            MOV    A,R2
            MOVX   @R0,A               ;������ջ�����
            
            INC    CounterRxd
            MOV    A,CounterRxd
            CJNE   A,#5,UART_RXD67     ;4�ֽ�����֡
UART_RXD67: JNC    UART_RXDX1
            RET

UART_RXDX1: CLR    B_RCVING
            MOV    R0,#BufferRXD
            
            INC    R0
            MOVX   A,@R0
            JB     ACC.7,UART_RXD_DatErr
            
            INC    R0
            MOVX   A,@R0
            JB     ACC.7,UART_RXD_DatErr
            
            INC    R0
            MOVX   A,@R0
            JB     ACC.7,UART_RXD_DatErr
            
            INC    R0
            MOVX   A,@R0
            JB     ACC.7,UART_RXD_DatErr
            LJMP   UART_RXD71
UART_RXD_DatErr:
            MOV    R0,#BufferTxd
            MOV    A,#8FH                     ;���ݷǷ�
           
            MOVX   @R0,A
            MOV    LengthTxd,#1
            ANL    CounterTxd,#0
            LJMP   RXD_TXD0
            
UART_RXD71: MOV    R0,#BufferRxd
            MOVX   A,@R0
            CJNE   A,#CMD_S_PARA,UART_RXD82
            LCALL  SetPara
            LJMP   RXD_TXD0
UART_RXD82: CJNE   A,#CMD_S_InitStart,UART_RXD83
            LCALL  SET2_InitStart
            LJMP   RXD_TXD0
UART_RXD83: CJNE   A,#CMD_S_InitStop,UART_RXD84
            LCALL  SET3_InitStop
            LJMP   RXD_TXD0
UART_RXD84: CJNE   A,#CMD_S_CtrWord,UART_RXD85
            LCALL  SET4_MOTOR_WORD
            LJMP   RXD_TXD0
UART_RXD85: CJNE   A,#CMD_S_MotorStep,UART_RXD86
            LCALL  SET5_MOTOR_Step
            LJMP   RXD_TXD0
UART_RXD86: CJNE   A,#CMD_S_MotorAuto,UART_RXD96
            LCALL  SET6_MOTOR_Auto
            LJMP   RXD_TXD0
            
UART_RXD96: CJNE   A,#CMD_R_PARA,UART_RXD97
            LCALL  GetPARA
            LJMP   RXD_TXD1
UART_RXD97: CJNE   A,#CMD_R_VER,UART_RXD98
            LCALL  GetVER
            LJMP   RXD_TXD1
UART_RXD98: CJNE   A,#CMD_R_AUA,UART_RXDA1
            ;LCALL  GetAU
            SETB   B_GET_nAU
            RET
            LJMP   RXD_TXD1
UART_RXDA1: LJMP   RXD_IGNORE

RXD_TXD0:   ;LCALL  ManagePro
RXD_TXD1:   LCALL  UART_TXDA
RXD_END:    RET

RXD_IGNORE: CLR    B_Rcving               ;��Ч����
            ANL    CounterRxd,#0
            ANL    LengthRxd,#0
            ANL    CounterTxd,#0
            ANL    LengthTxd,#0
            LJMP   RXD_END
;==========================================================
SetPara:    
            MOV    R0,#BufferRxd
            INC    R0
            MOV    R1,#BufferPARA
            MOV    R2,#4
SETDP12:    MOVX   A,@R0
            MOV    @R1,A
            INC    R0
            INC    R1
            DJNZ   R2,SETDP12
            
            LCALL  Refresh_Para
            
            MOV    R0,#BufferTxd
            MOV    A,#CMD_S_PARA
            MOVX   @R0,A
            MOV    LengthTxd,#1
            ANL    CounterTxd,#0

            RET
;==========================================================
SET2_InitStart: 
            SETB   B_InitStart
            CLR    B_initOK
            
            MOV    R0,#BufferRXD
            INC    R0
            INC    R0
            INC    R0
            INC    R0
            MOVX   A,@R0
            ANL    A,#07FH
            ;MOV    REG_StepInit,A       ;����΢������
            
SET_IStart_OK:
            MOV    R0,#BufferTxd
            MOV    A,#CMD_S_InitStart
            MOVX   @R0,A
            MOV    LengthTxd,#1
            ANL    CounterTxd,#0

            RET
            
SET_IStart_Err:
            MOV    R0,#BufferTxd
            MOV    A,#8FH
            MOVX   @R0,A
            MOV    LengthTxd,#1
            ANL    CounterTxd,#0

            RET
;==========================================================
SET3_InitStop: 
            SETB   B_InitStop
            CLR    B_InitOK
            CLR    B_MotorStep
            CLR    B_MotorAuto
            CLR    B_GET_nAU
            
            ;MOV    R0,#BufferRXD
            ;INC    R0
            ;INC    R0
            ;INC    R0
            ;INC    R0
            ;MOVX   A,@R0
            ;ANL    A,#07FH
            ;MOV    REG_StepInit,A       ;����΢������
            
SET_IStop_OK:
            ;LCALL  CLK_OFF_P34                ;ֱ��ͣת
            ;CLR    B_InitOK
            
            MOV    R0,#BufferTxd
            MOV    A,#CMD_S_InitStop
            MOVX   @R0,A
            MOV    LengthTxd,#1
            ANL    CounterTxd,#0

            RET
            
SET_IStop_Err:
            MOV    R0,#BufferTxd
            MOV    A,#8FH
            MOVX   @R0,A
            MOV    LengthTxd,#1
            ANL    CounterTxd,#0

            RET
;==========================================================
SET4_MOTOR_WORD:
            MOV    R0,#BufferRXD
            INC    R0
            MOVX   A,@R0
            
SET_Word0:  CJNE   A,#0,SET_Word1
            LJMP   SET_WordErr                 ;Ϊ0������

SET_Word1:  MOV    C,ACC.4
            MOV    B_TempDir,C                 ;�ݴ浱ǰ����ת������
            
            ANL    A,#11101111B
            CJNE   A,#1,SET_Word2
            
            MOV    C,B_TempDir
            MOV    B_Wav1Dir_Temp,C          ;��������ʱ�Ĵ�����,�������޸����ڽ��еĲ���
            
            MOV    R0,#BufferRXD
            INC    R0
            MOVX   A,@R0                      ;ȡ������������
            MOV    A,#0                       ;���ֽ�ӦΪ0
            MOV    REG_DATA1,A
           
            INC    R0
            MOVX   A,@R0
            MOV    REG_DATA2,A
            
            INC    R0
            MOVX   A,@R0
            MOV    REG_DATA3,A
           
            INC    R0
            MOVX   A,@R0
            MOV    REG_DATA4,A
            
            LCALL  GET_DDS_DATA               ;�õ������Ŀ�����,�����REG_DATA
            MOV    A,REG_DATA3
            MOV    WaveL_Temp1_H,A           ;��������ʱ�Ĵ�����,�������޸����ڽ��еĲ���
            MOV    A,REG_DATA4
            MOV    WaveL_Temp1_L,A
            
            LJMP   SET_Word3
            
SET_Word2:  CJNE  A,#2,SET_WordErr
            
            MOV    C,B_TempDir
            MOV    B_Wav2Dir_Temp,C          ;��������ʱ�Ĵ�����,�������޸����ڽ��еĲ���
            
            MOV    R0,#BufferRXD
            INC    R0
            MOVX   A,@R0                     ;ȡ������������
            MOV    A,#0                      ;���ֽ�ӦΪ0
            MOV    REG_DATA1,A
           
            INC    R0
            MOVX   A,@R0
            MOV    REG_DATA2,A
            
            INC    R0
            MOVX   A,@R0
            MOV    REG_DATA3,A
           
            INC    R0
            MOVX   A,@R0
            MOV    REG_DATA4,A
            
            LCALL  GET_DDS_DATA               ;�õ������Ŀ�����,�����REG_DATA
            MOV    A,REG_DATA3
            MOV    WaveL_Temp2_H,A           ;��������ʱ�Ĵ�����,�������޸����ڽ��еĲ���
            MOV    A,REG_DATA4
            MOV    WaveL_Temp2_L,A
            
            MOV    A,WaveL_Temp2_H
            JNZ    SET_WORDX1
            MOV    A,WaveL_Temp2_L
            JNZ    SET_WORDX1
            
            CLR    B_NEW_WaveDual            ;�µĵ�˫������־
            AJMP   SET_WORDX2
            
SET_WORDX1: SETB   B_NEW_WaveDual  
            
SET_WORDX2: SETB   B_WaveChangeOK            ;�����յ�2�鲨���ı�����
;---------------------------------------
SET_Word3:
            ;------------------------------
            ;�޸�˫����ʱҲ���˳�����ģʽ
            ;------------------------------
            ;JNB    B_WaveDual,SET_Word4
            ;CLR    B_initOK                  ;����˫����״̬ʱ,���ò������˳��Զ�ģʽ
            
SET_Word4:  MOV    R0,#BufferTxd
            MOV    A,#CMD_S_CtrWord
            MOVX   @R0,A
            MOV    LengthTxd,#1
            ANL    CounterTxd,#0
            RET

SET_WordErr:MOV    R0,#BufferTxd
            MOV    A,#8FH
            MOVX   @R0,A
            MOV    LengthTxd,#1
            ANL    CounterTxd,#0
            RET
;==========================================================
;��դת��ָ������
;----------------------------------------------------------
SET5_MOTOR_Step:
           SETB   B_MotorStep                ;��λ���ת��ָ������
           
           MOV    R0,#BufferRXD
           INC    R0
           MOVX   A,@R0
           JB     ACC.4,SET_StepX1
           CLR    A_DIR                      ;��ʱ��-��������
           AJMP   SET_StepX2
           
SET_StepX1:SETB   A_DIR                      ;˳ʱ��
SET_StepX2:MOV    R0,#BufferRXD
           INC    R0
           MOVX   A,@R0
           ANL    A,#11101111B
           CJNE   A,#7,SET_Step1
SET_Step1: JC     SET_Step2
           LJMP   SET_Step8                   ;����6�Ƿ�
;---------------------------------------           
SET_Step2: JNZ    SET_Step3
           LCALL  CLK_OFF_P34                ;ֱ��ͣת
           CLR    B_MotorStep
           LJMP   SET_Step7
           
SET_Step3: MOV    REG_Grade,A
           
           MOV    R0,#BufferRXD
           INC    R0
           INC    R0
           MOVX   A,@R0
           CJNE   A,#4,SET_Step4
SET_Step4: JC     SET_Step5
           LJMP   SET_Step8                   ;����3�Ƿ�
;---------------------------------------
SET_Step5: MOV    R0,#BufferRXD
           INC    R0
           MOVX   A,@R0                      ;ȡ�����������
           MOV    A,#0                       ;���ֽ�ӦΪ0
           MOV    REG_DATA1,A
          
           INC    R0
           MOVX   A,@R0
           MOV    REG_DATA2,A
           
           INC    R0
           MOVX   A,@R0
           MOV    REG_DATA3,A
           
           INC    R0
           MOVX   A,@R0
           MOV    REG_DATA4,A
           
           LCALL  GET_DDS_DATA               ;�õ������Ŀ�����,�����REG_DATA
           
SET_Step7: MOV    R0,#BufferTxd
           MOV    A,#CMD_S_MotorStep
           
           CLR    B_InitOK                  ;�˳����Զ�ģʽ��
           
           LJMP   SET_Step9
           
SET_Step8: MOV    R0,#BufferTxd
           MOV    A,#8FH                     ;���ݷǷ�
           CLR    B_MotorStep                ;�����ת
           
SET_Step9: MOVX   @R0,A
           MOV    LengthTxd,#1
           ANL    CounterTxd,#0
           RET
;==========================================================
;��դ�����Զ���ת
;----------------------------------------------------------
SET6_MOTOR_Auto:

           SETB   B_MotorAuto                ;��λ������ʱ仯
           
           MOV    R0,#BufferRXD
           INC    R0
           MOVX   A,@R0
           JB     ACC.4,SET_AutoX1
           CLR    A_DIR                      ;��ʱ��-��������
           AJMP   SET_AutoX2
           
SET_AutoX1: SETB   A_DIR                      ;˳ʱ��
           
SET_AutoX2:MOV    R0,#BufferRXD
           INC    R0
           MOVX   A,@R0
           ANL    A,#11101111B
           CJNE   A,#7,SET_Auto1
SET_Auto1: JC     SET_Auto2
           LJMP   SET_Auto8                   ;����6�Ƿ�
;---------------------------------------           
SET_Auto2: JNZ    SET_Auto3
           LCALL  CLK_OFF_P34                ;ֱ��ͣת
           CLR    B_MotorAuto
           LJMP   SET_Auto7
           
SET_Auto3: MOV    REG_Grade,A
           
           MOV    R0,#BufferRXD
           INC    R0
           INC    R0
           MOVX   A,@R0
           CJNE   A,#4,SET_Auto4
SET_Auto4: JC     SET_Auto5
           LJMP   SET_Auto8                   ;����3�Ƿ�
;---------------------------------------
SET_Auto5: MOV    R0,#BufferRXD
           INC    R0
           MOVX   A,@R0                      ;ȡ�����������
           MOV    A,#0                       ;���ֽ�ӦΪ0
           MOV    REG_DATA1,A
          
           INC    R0
           MOVX   A,@R0
           MOV    REG_DATA2,A
           
           INC    R0
           MOVX   A,@R0
           MOV    REG_DATA3,A
           
           INC    R0
           MOVX   A,@R0
           MOV    REG_DATA4,A
           
           LCALL  GET_DDS_DATA               ;�õ������Ŀ�����,�����REG_DATA
           
SET_Auto7: MOV    R0,#BufferTxd
           MOV    A,#CMD_S_MotorAuto
           
           CLR    B_InitOK                  ;�˳����Զ�ģʽ��
           
           LJMP   SET_Auto9
           
SET_Auto8: MOV    R0,#BufferTxd
           MOV    A,#8FH                     ;���ݷǷ�
           CLR    B_MotorAuto                ;�����ת

SET_Auto9: MOVX   @R0,A
           MOV    LengthTxd,#1
           ANL    CounterTxd,#0
           RET
;==========================================================
GetPara:    
            MOV    R0,#BufferTxd
            MOV    A,#CMD_R_PARA
            MOVX   @R0,A
            INC    R0
            
            MOV    A,BufferPARA
            ANL    A,#7FH
            MOVX   @R0,A
            INC    R0
            MOV    A,TimeConst
            ANL    A,#7FH
            MOVX   @R0,A
            INC    R0
            MOV    A,PARA3
            ANL    A,#7FH
            MOVX   @R0,A
            INC    R0
            MOV    A,PARA4
            ANL    A,#7FH
            MOVX   @R0,A
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0

            RET
;==========================================================
GetVER:     
            MOV    R0,#BufferTxd
            MOV    A,#CMD_R_VER
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOV    A,#0EH              ;E�汾
            MOVX   @R0,A
            INC    R0
            
            MOV    A,VER1
            ANL    A,#7FH
            MOVX   @R0,A
            INC    R0
            MOV    A,VER2
            ANL    A,#7FH
            MOVX   @R0,A
            INC    R0
            MOV    A,VER3
            ANL    A,#7FH
            MOVX   @R0,A
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            RET
;==========================================================
GetAU:

            SETB   B_GET_nAU
            
            RET
;==========================================================
UART_TXDA:  CLR    TI                  ;���ڷ����ӳ���
            ;SETB   TRCTL
            ;LCALL  DELAY1MS
            ;SETB   B_Sent              ;��λ����״̬��־
            ;JB     B_SYNC,UART_TXD0
            ;MOV    A,#TBWORD           ;����3��ͬ����
            ;MOV    SBUF,A
            ;INC    CounterTxd
            ;MOV    A,CounterTxd
            ;CJNE   A,#3,UART_TXD_END
            ;SETB   B_SYNC
            ;ANL    CounterTxd,#0
            ;LJMP   UART_TXD_END
UART_TXD0:  MOV    A,CounterTxd
            CJNE   A,LengthTxd,UART_TXD1
UART_TXD1:  JC     UART_TXD2
            ;CLR    B_SYNC
            ANL    CounterRxd,#0
            ANL    CounterTxd,#0
            ;CLR    TRCTL
            ;CLR    B_Sent
            LJMP   UART_TXD_END           ;��������
UART_TXD2:  MOV    A,#BufferTxd
            ADD    A,CounterTxd
            MOV    R0,A
            MOVX   A,@R0
            MOV    SBUF,A
            INC    CounterTxd
UART_TXD_END:
            RET
;==========================================================
TXBCH:      MOV    A,R2            ;����BCHУ����
            PUSH   ACC
            CLR    A
TXBCH1:     XRL    A,@R0
            INC    R0
            DJNZ   R2,TXBCH1
            MOV    @R0,A
            POP    ACC
            MOV    R2,A
            RET
;----------------------------------------------------------
TXBCH3:     CLR    A
TXBCH4:     MOV    B,A
            MOVX   A,@R0
            XRL    A,B
            INC    R0
            DJNZ   R2,TXBCH4
            MOVX   @R0,A
            RET
;==========================================================
ManagePro:  MOV    R0,#BufferTxd
            MOVX   @R0,A                   ;������
            INC    R0
            MOV    B,A
            MOV    A,DevNumber                ;�豸��
            MOVX   @R0,A
            MOV    A,B
            XRL    A,DevNumber
            MOV    B,A
            INC    R0
            MOV    A,#0
            MOVX   @R0,A
            MOV    A,B
            XRL    A,#0
            MOV    B,A
            INC    R0
            MOV    A,#0FFH
            MOVX   @R0,A
            MOV    A,B
            XRL    A,#0FFH
            MOV    B,A
            INC    R0
            MOVX   @R0,A         ;BCH
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            RET

;===========================================================
;����ָ����ֵ
;-----------------------------------------------------------
SEND_32DATA:
            MOV    R0,#BufferTxd
            MOV    A,#0DDH              ;����ͷ
            MOVX   @R0,A
            INC    R0
            
            MOV    R1,#BufferAD1
            MOV    R2,#48
SEND_32D_LP:
            MOV    A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            DJNZ   R2,SEND_32D_LP
            
            MOV    A,Cnt_ForStep
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0DDH
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#51
            ANL    CounterTxd,#0
            
            SETB   TI
            
            RET
;===========================================================
;����ָ����ֵ
;-----------------------------------------------------------
SEND_22DATA:
            MOV    R0,#BufferTxd
            MOV    A,#0EEH              ;����ͷ
            MOVX   @R0,A
            INC    R0
            
            MOV    R1,#BufferTEMP
            MOV    R2,#16
SEND_22D_LP:
            MOVX   A,@R1
            MOVX   @R0,A
            INC    R0
            INC    R1
            DJNZ   R2,SEND_22D_LP
            
            MOV    A,R4
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0EEH
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#19
            ANL    CounterTxd,#0
            
            SETB   TI
            
            RET
;===========================================================
;����ָ����ֵ
;-----------------------------------------------------------
SEND_4DATA:
            MOV    R0,#BufferTxd
            MOV    A,R2
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R3
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R4
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R5
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#4
            ANL    CounterTxd,#0
            
            SETB   TI
            
            RET
;===========================================================
;���Ͳ�����ͬ����
;-----------------------------------------------------------
SEND_WaveChg_Necho:
            MOV    R0,#BufferTxd
            MOV    A,#08FH
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0

            SETB   TI
            
            RET
;===========================================================
;���Ͳ����ı����������
;-----------------------------------------------------------
SEND_WaveChg_echo:
            MOV    R0,#BufferTxd
            MOV    A,#084H
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            
            CLR    B_AU_SENT
            
            SETB   TI
            
            RET
;===========================================================
;�����ҵ����
;-----------------------------------------------------------
SEND_InitOK:
            MOV    R0,#BufferTxd
            MOV    A,#082H
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            
            SETB   TI
            
            RET
;===========================================================
;����AUH��ֵ,���ʹ�����A
;-----------------------------------------------------------
SEND_AUH:
            MOV    R0,#BufferTxd
            ;MOV    A,#082H
            MOVX   @R0,A
            INC    R0
            
            MOV    A,#0
            MOVX   @R0,A
            INC    R0
            
            MOV    A,REG_AUH_H
            MOVX   @R0,A
            INC    R0
            
            MOV    A,REG_AUH_M
            MOVX   @R0,A
            INC    R0
            
            MOV    A,REG_AUH_L
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            
            SETB   TI
            
            RET
;===========================================================
;����AUB��ֵ
;-----------------------------------------------------------
SEND_AUB:
            ;CLR    TR0
            ;CLR    TR1
            
            MOV    R0,#BufferAD1   ;ָ��α�ֵ
            MOV    Cnt_Byte,#16
            LCALL  SORT3Byte       ;����
            MOV    R0,#BufferAD1
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#14          ;�������ֵ
            
            INC    R0              ;������Сֵ
            INC    R0
            INC    R0
            MOV    R1,#12          ;�������ֵ
            LCALL  DDM3            ;ȡƽ��ֵ
            LCALL  GET_AAA_DATA
            ;---------------------------
            MOV    R0,#BufferTxd
            MOV    A,#08BH
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R7
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R6
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R5
            MOVX   @R0,A
            INC    R0
            
            MOV    A,R4
            MOVX   @R0,A
            INC    R0
            
            MOV    LengthTxd,#5
            ANL    CounterTxd,#0
            
            SETB   TI
            
            RET
;=================================================
GET_AAA_DATA:
            CLR    C
            MOV    A,R4
            RLC    A
            
            MOV    A,R5
            RLC    A
            MOV    R5,A
            
            
            MOV    A,R6
            RLC    A
            MOV    R6,A
            
            MOV    A,R7
            RLC    A
            MOV    R7,A
            ;---------------------------
            CLR    C
            MOV    A,R5
            RLC    A
            
            MOV    A,R6
            RLC    A
            MOV    R6,A
            
            MOV    A,R7
            RLC    A
            MOV    R7,A
            ;---------------------------
            CLR    C
            MOV    A,R6
            RLC    A
            
            MOV    A,R7
            RLC    A
            MOV    R7,A
            ;---------------------------
            MOV    A,R7
            ANL    A,#07FH
            MOV    R7,A
            
            MOV    A,R6
            ANL    A,#07FH
            MOV    R6,A
            
            MOV    A,R5
            ANL    A,#07FH
            MOV    R5,A
            
            MOV    A,R4
            ANL    A,#07FH
            MOV    R4,A
            
            RET
;==========================================================
;==========================================================
;BCHУ��,�ֽ�����R2,������R0,�����ACC
;----------------------------------------------------------
BCH_CHECK:  ANL    B,#0
BCH_CHECK1: MOV    A,@R0           ;ACC IS SUM,R2 IS LENGTH
            XRL    A,B
            INC    R0
            MOV    B,A
            DJNZ   R2,BCH_CHECK1
            RET
;----------------------------------------------------------
BCH_CHECK3: PUSH   B
            ANL    B,#0          ;Դ������ERAM��BCHУ��
BCH_CHECK4: MOVX   A,@R0
            XRL    A,B
            MOV    B,A
            INC    R0
            DJNZ   R2,BCH_CHECK4
            POP    B
            RET
;==========================================================
;Read Eeprom.
;Source Address=R0,Target Address=R1,Length=R2
;----------------------------------------------------------
ReadEeprom: 
ReadEelp:   MOV    IAP_CONTR,#IAP_WAITE
            ORL    IAP_CONTR,#80H
            MOV    IAP_CMD,#IAP_Byte_READ
            MOV    IAP_TRIG,#05AH
            MOV    IAP_TRIG,#0A5H
            
            NOP
            NOP
            
            MOV    @R0,IAP_DATA
            INC    IAP_ADDRL
            INC    R0
            DJNZ   R2,ReadEeLp
            
            MOV    IAP_CONTR,#0
            MOV    IAP_CMD,#0
            MOV    IAP_TRIG,#0
            MOV    IAP_ADDRH,#0FFH
            MOV    IAP_ADDRL,#0FFH
            
            RET
;==========================================================
;WRITE EEPROM.
;SOURCE ADDRESS=R0,TARGET ADDRESS=R1,LENGTH=R2
;----------------------------------------------------------
WrEeprom:   
WreeLP:     MOV    IAP_DATA,@R0
            MOV    IAP_CONTR,#IAP_WAITE
            ORL    IAP_CONTR,#80H
            MOV    IAP_CMD,#IAP_Byte_PGM
            MOV    IAP_TRIG,#05AH
            MOV    IAP_TRIG,#0A5H
            
            NOP
            NOP
            
            INC    IAP_ADDRL
            INC    R0
            DJNZ   R2,WreeLP
            
            MOV    IAP_CONTR,#0
            MOV    IAP_CMD,#0
            MOV    IAP_TRIG,#0
            MOV    IAP_ADDRH,#0FFH
            MOV    IAP_ADDRL,#0FFH
            
            RET
;==========================================================
EraseEeprom_Sec:
            MOV    IAP_CONTR,#IAP_WAITE
            ORL    IAP_CONTR,#80H
            MOV    IAP_CMD,#IAP_SEC_Erase
            MOV    IAP_TRIG,#05AH
            MOV    IAP_TRIG,#0A5H
            
            NOP
            NOP
            NOP
            NOP
            
            MOV    IAP_CONTR,#0
            MOV    IAP_CMD,#0
            MOV    IAP_TRIG,#0
            MOV    IAP_ADDRH,#0FFH
            MOV    IAP_ADDRL,#0FFH
            
            RET
;==========================================================
;4�ֽ�HEX��תΪ5�ֽ�BCD��
;Դ����BufferHEX,���ֽ���ǰ;Ŀ������BufferBCD,���ֽ���ǰ
;�ֽ���HEXBytes,ʹ��R0,R1,R2,R3,A,B,PSW
;----------------------------------------------------------
HEX4TOBCD5A:MOV    R0,#BufferHEX
            MOV    A,R0
            ADD    A,#4
            MOV    R1,A
            MOV    R2,#4
SAVEHEXLP:  MOV    A,@R0               ;����Դ����
            MOV    @R1,A
            INC    R0
            INC    R1
            DJNZ   R2,SAVEHEXLP
            MOV    R0,#BufferHEX
            MOV    A,@R0
            INC    R0
            INC    R0
            INC    R0
            XCH    A,@R0               ;������ߺ�����ֽ�
            MOV    R0,#BUFFERHEX
            MOV    @R0,A
            INC    R0
            MOV    A,@R0
            INC    R0
            XCH    A,@R0
            DEC    R0
            MOV    @R0,A
            MOV    R1,#BufferBCD       ;Ŀ���ַ
            MOV    R2,#HEXBytes        ;4�ֽ�HEX��
            INC    R2                  ;5�ֽ�BCD��
            MOV    A,#0
HEX4TOBCD5C:MOV    @R1,A               ;Ԥ�����Ŀ�껺����
            INC    R1
            DJNZ   R2,HEX4TOBCD5C
            MOV    A,#HEXBytes
            MOV    B,#8
            MUL    AB
            MOV    R3,A
HEX4TOBCD5D:MOV    R0,#BufferHEX
            MOV    R2,#HEXBytes
            CLR    C
HEX4TOBCD5E:MOV    A,@R0               ;N�ֽ�2����������1λ,��λ��CY
            RLC    A
            MOV    @R0,A
            INC    R0
            DJNZ   R2,HEX4TOBCD5E
            MOV    R2,#HEXBytes
            INC    R2
            MOV    R1,#BufferBCD
HEX4TOBCD5F:MOV    A,@R1
            ADDC   A,@R1
            DA     A
            MOV    @R1,A
            INC    R1
            DJNZ   R2,HEX4TOBCD5F
            DJNZ   R3,HEX4TOBCD5D
            
            MOV    R0,#BufferBCD       ;R0ָ���1λ
            MOV    A,#BufferBCD
            ADD    A,#4
            MOV    R1,A                ;R1ָ���5λ
            MOV    A,@R1
            MOV    B,@R0
            MOV    @R1,B
            MOV    @R0,A
            INC    R0
            DEC    R1
            MOV    A,@R1
            MOV    B,@R0
            MOV    @R1,B
            MOV    @R0,A
            
            MOV    R0,#BufferHEX
            MOV    A,R0
            ADD    A,#4
            MOV    R1,A
            MOV    R2,#4
TAKEHEXLP:  MOV    A,@R1               ;�ָ�Դ����
            MOV    @R0,A
            INC    R0
            INC    R1
            DJNZ   R2,TAKEHEXLP
            RET
;================================================
;���ֽ���������
;Cnt_Byte:  �ݼ��Ƚϴ���
;SORT_Ind:  ÿ�αȽ�ǰ������ָ��
;R7:        �Ƚϴ���������
;------------------------------------------------
SORT3Byte:  
            ;--------------------------
SRT3B1:     CLR    F0                   ;������־��ʼ��
            MOV    A,Cnt_Byte           ;ȡ�ϱ�Ƚϴ���
            DEC    A                    ;������ϱ����һ��
            MOV    Cnt_Byte,A           ;���汾�����
            MOV    R7,A                 ;���Ƶ���������
            JZ     SRT3B8               ;��Ϊ�㣬�������
            
            MOV    A,R0
            MOV    SORT_Ind,A        ;��������ָ��
;--------------------------------------
SRT3B2:     MOV    A,@R0       ;��
            MOV    R1,A
            INC    R0
            MOV    A,@R0       ;��
            MOV    R2,A
            INC    R0
            MOV    A,@R0       ;��
            MOV    R3,A
            
            INC    R0          ;ָ����һ������
            
            MOV    A,@R0       ;��
            MOV    R4,A
            INC    R0
            MOV    A,@R0       ;��
            MOV    R5,A
            INC    R0
            MOV    A,@R0       ;��
            MOV    R6,A
            ;--------------------------
            MOV    A,R4
            MOV    B,R1
            CJNE   A,B,SRT3X1
SRT3X1:     JC     SRT3B3      ;С�ڽ���
            CJNE   A,B,SRT3B7  ;���ڲ�����
            MOV    A,R5
            MOV    B,R2
            CJNE   A,B,SRT3X2
SRT3X2:     JC     SRT3B3      ;С�ڽ���
            CJNE   A,B,SRT3B7  ;���ڲ�����
            MOV    A,R6
            MOV    B,R3
            CJNE   A,B,SRT3X3
SRT3X3:     JNC    SRT3B7      ;���ڵ��ڲ�����
;--------------------------------------
SRT3B3:     SETB   F0          ;����������־
            DEC    R0
            DEC    R0
            DEC    R0
            DEC    R0
            DEC    R0

            MOV    A,R4
            MOV    @R0,A
            INC    R0
            MOV    A,R5
            MOV    @R0,A
            INC    R0
            MOV    A,R6
            MOV    @R0,A
            
            INC    R0
            MOV    A,R1
            MOV    @R0,A
            INC    R0
            MOV    A,R2
            MOV    @R0,A
            INC    R0
            MOV    A,R3
            MOV    @R0,A
;--------------------------------------
SRT3B7:     DEC    R0                 ;���ص��ڶ������ݵĸ��ֽ�
            DEC    R0
            DJNZ   R7,SRT3B2          ;��ɱ���ıȽϴ���
            MOV    A,SORT_Ind         ;�ָ�������ַ
            MOV    R0,A
            JB     F0,SRT3B1          ;���������й������������������
SRT3B8:     RET
;================================================
;˫�ֽ���������
;R5:�ݼ��Ƚϴ���
;R6:ÿ�αȽ�ǰ������ָ��
;R7:�Ƚϴ���������
;------------------------------------------------
SORT2Byte:  MOV    R5,#16      ;�Ƚϴ���
            ;--------------------------
SRT2B1:     CLR    F0          ;������־��ʼ��
            MOV    A,R5        ;ȡ�ϱ�Ƚϴ���
            DEC    A           ;������ϱ����һ��
            MOV    R5,A        ;���汾�����
            MOV    R7,A        ;���Ƶ���������
            JZ     SRT2B8      ;��Ϊ�㣬�������
            
            MOV    A,R0
            MOV    R6,A        ;��������ָ��
;--------------------------------------
SRT2B2:     MOV    A,@R0       ;��ȡһ�����ݸ�
            MOV    R1,A
            INC    R0
            MOV    A,@R0       ;��
            MOV    R2,A
            ;--------------------------
            INC    R0          ;ָ����һ������
            MOV    A,@R0       ;�ٶ�ȡһ�����ݸ�
            MOV    R3,A
            INC    R0
            MOV    A,@R0
            MOV    R4,A
            ;--------------------------
            MOV    A,R3
            MOV    B,R1
            CJNE   A,B,SRT2X1
SRT2X1:     JC     SRT2B3      ;С�ڽ���
            CJNE   A,B,SRT2B7  ;���ڲ�����
            MOV    A,R4
            MOV    B,R2
            CJNE   A,B,SRT2X2
SRT2X2:     JNC    SRT2B7      ;���ڵ��ڲ�����            
;--------------------------------------
SRT2B3:     SETB   F0          ;����������־
            DEC    R0
            DEC    R0
            DEC    R0
            MOV    A,R3
            MOV    @R0,A
            INC    R0
            MOV    A,R4
            MOV    @R0,A
            
            INC    R0
            MOV    A,R1
            MOV    @R0,A
            INC    R0
            MOV    A,R2
            MOV    @R0,A
;--------------------------------------
SRT2B7:     DEC    R0           ;���ص��ڶ������ݵĸ��ֽ�
            DJNZ   R7,SRT2B2    ;��ɱ���ıȽϴ���
            MOV    A,R6         ;�ָ�������ַ
            MOV    R0,A
            JB     F0,SRT2B1   ;���������й������������������
SRT2B8:     RET
;================================================
;���ܣ������ֽ�ʮ�������޷������ݿ��ƽ��ֵ
;������������ݿ����ַ��R0��(��չRAM),���ֽ������ܸ�����R1
;������Ϣ��ƽ��ֵ��R7R6R5R4��.
;Ӱ����Դ��PSW��A��R2��R6 ��ջ����4�ֽ�
;------------------------------------------------
DDM_A3:     MOV    A,R1
            MOV    R2,A           ;��ʼ������ָ��
            CLR    A              ;��ʼ���ۼӺ�
            MOV    R4,A
            MOV    R5,A
            MOV    R6,A
            MOV    R7,A
            
DM_A30:     MOVX   A,@R0         ;��
            MOV    REG_TEMP1,A
            INC    R0
            MOVX   A,@R0         ;��
            MOV    REG_TEMP2,A
            INC    R0
            MOVX   A,@R0         ;��
            INC    R0
            
            ADD    A,R4           ;�ۼӵ��ۼӺ���
            MOV    R4,A
            
            MOV    A,REG_TEMP2
            ADDC   A,R5
            MOV    R5,A
            
            MOV    A,REG_TEMP1
            ADDC   A,R6
            MOV    R6,A
            
            JNC    DM_A31
            INC    R7
DM_A31:     DJNZ   R2,DM_A30

            AJMP  DIV_A43
;****************************************************
;* ���ֽ�/���ֽ��޷������������� *
;****************************************************
;R7R6R5R4 / R2R1R0 --> R7R6R5R4...REG_TEMP3/REG_TEMP2/REG_TEMP1
;����ʹ�ã�A��B��REG_TEMP4/REG_TEMP3/REG_TEMP2/REG_TEMP1
;-----------------------------------------------------------
DIV_A43:    MOV    A,R1
            MOV    R0,A                 ;����
            CLR    A
            MOV    R2,A
            MOV    R1,A
            MOV    REG_TEMP1, A
            MOV    REG_TEMP2, A
            MOV    REG_TEMP3, A
            MOV    REG_TEMP4, A
 
            MOV    R3, #32              ;ѭ������
            CLR C
DIV43_ALOOP:
            MOV A, R4
            RLC A
            MOV R4, A
            MOV A, R5
            RLC A
            MOV R5, A
            MOV A, R6
            RLC A
            MOV R6, A
            MOV A, R7
            RLC A
            MOV R7, A
            
            MOV A, REG_TEMP1       ;REG_TEMP3REG_TEMP2REG_TEMP1 <-- R7R6R5R4 <-- C
            RLC A
            MOV REG_TEMP1, A
            MOV A, REG_TEMP2
            RLC A
            MOV REG_TEMP2, A
            MOV A, REG_TEMP3
            RLC A
            MOV REG_TEMP3, A
            
            MOV    F0, C
            CLR    C
;IF (REG_TEMP3/REG_TEMP2/REG_TEMP1 >= R2R1R0) REG_TEMP3/REG_TEMP2/REG_TEMP1 -= R2R1R0;
            MOV    A, REG_TEMP1
            SUBB   A, R0
            MOV    REG_TEMP4, A
            MOV    A, REG_TEMP2
            SUBB   A, R1
            MOV    B, A
            MOV    A, REG_TEMP3
            SUBB   A, R2
            JNC    DIV32_A2
            JNB    F0, DIV32_A3          ;�������Ͳ������
            CPL    C
DIV32_A2:
            MOV    REG_TEMP1, REG_TEMP4
            MOV    REG_TEMP2, B
            MOV    REG_TEMP3, A
DIV32_A3:
            CPL    C
            DJNZ R3, DIV43_ALOOP
;---------------------------------------------------
SL_R7_AR4:   MOV A, R4
            RLC A
            MOV R4, A
            MOV A, R5
            RLC A
            MOV R5, A
            MOV A, R6
            RLC A
            MOV R6, A
            MOV A, R7
            RLC A
            MOV R7, A
            
            RET
;================================================
;���ܣ������ֽ�ʮ�������޷������ݿ��ƽ��ֵ
;������������ݿ����ַ��R0��,���ֽ������ܸ�����R1
;������Ϣ��ƽ��ֵ��R7R6R5R4��.
;Ӱ����Դ��PSW��A��R2��R6 ��ջ����4�ֽ�
;------------------------------------------------
DDM3:       MOV    A,R1
            MOV    R2,A           ;��ʼ������ָ��
            CLR    A              ;��ʼ���ۼӺ�
            MOV    R4,A
            MOV    R5,A
            MOV    R6,A
            MOV    R7,A
            
DM30:       MOV    A,@R0         ;��
            MOV    REG_TEMP1,A
            INC    R0
            MOV    A,@R0         ;��
            MOV    REG_TEMP2,A
            INC    R0
            MOV    A,@R0         ;��
            INC    R0
            
            ADD    A,R4           ;�ۼӵ��ۼӺ���
            MOV    R4,A
            
            MOV    A,REG_TEMP2
            ADDC   A,R5
            MOV    R5,A
            
            MOV    A,REG_TEMP1
            ADDC   A,R6
            MOV    R6,A
            
            JNC    DM31
            INC    R7
DM31:       DJNZ   R2,DM30

            AJMP  DIV_43
;****************************************************
;* ���ֽ�/���ֽ��޷������������� *
;****************************************************
;R7R6R5R4 / R2R1R0 --> R7R6R5R4...REG_TEMP3/REG_TEMP2/REG_TEMP1
;����ʹ�ã�A��B��REG_TEMP4/REG_TEMP3/REG_TEMP2/REG_TEMP1
;-----------------------------------------------------------
DIV_43:     MOV    A,R1
            MOV    R0,A                 ;����
            CLR    A
            MOV    R2,A
            MOV    R1,A
            MOV    REG_TEMP1, A
            MOV    REG_TEMP2, A
            MOV    REG_TEMP3, A
            MOV    REG_TEMP4, A
 
            MOV    R3, #32              ;ѭ������
            CLR C
DIV43_LOOP:
            MOV A, R4
            RLC A
            MOV R4, A
            MOV A, R5
            RLC A
            MOV R5, A
            MOV A, R6
            RLC A
            MOV R6, A
            MOV A, R7
            RLC A
            MOV R7, A
            
            MOV A, REG_TEMP1       ;REG_TEMP3REG_TEMP2REG_TEMP1 <-- R7R6R5R4 <-- C
            RLC A
            MOV REG_TEMP1, A
            MOV A, REG_TEMP2
            RLC A
            MOV REG_TEMP2, A
            MOV A, REG_TEMP3
            RLC A
            MOV REG_TEMP3, A
            
            MOV    F0, C
            CLR    C
;IF (REG_TEMP3/REG_TEMP2/REG_TEMP1 >= R2R1R0) REG_TEMP3/REG_TEMP2/REG_TEMP1 -= R2R1R0;
            MOV    A, REG_TEMP1
            SUBB   A, R0
            MOV    REG_TEMP4, A
            MOV    A, REG_TEMP2
            SUBB   A, R1
            MOV    B, A
            MOV    A, REG_TEMP3
            SUBB   A, R2
            JNC    DIV32_2
            JNB    F0, DIV32_3          ;�������Ͳ������
            CPL    C
DIV32_2:
            MOV    REG_TEMP1, REG_TEMP4
            MOV    REG_TEMP2, B
            MOV    REG_TEMP3, A
DIV32_3:
            CPL    C
            DJNZ R3, DIV43_LOOP
;---------------------------------------------------
SL_R7_R4:   MOV A, R4
            RLC A
            MOV R4, A
            MOV A, R5
            RLC A
            MOV R5, A
            MOV A, R6
            RLC A
            MOV R6, A
            MOV A, R7
            RLC A
            MOV R7, A
            RET
;================================================
;���ܣ���˫�ֽ�ʮ�������޷������ݿ��ƽ��ֵ
;������������ݿ����ַ��R0�У�˫�ֽ������ܸ�����R7��
;������Ϣ��ƽ��ֵ��R4��R5�С�
;Ӱ����Դ��PSW��A��R2��R6 ��ջ����4�ֽ�
;------------------------------------------------
DDM2:       MOV    A,R7
            MOV    R2,A           ;��ʼ������ָ��
            CLR    A              ;��ʼ���ۼӺ�
            MOV    R3,A
            MOV    R4,A
            MOV    R5,A
DM20:       MOV    A,@R0         ;��ȡһ�����ݵĸ��ֽ�
            MOV    B,A
            INC    R0
            MOV    A,@R0         ;��ȡһ�����ݵĵ��ֽ�
            INC    R0
            ADD    A,R5           ;�ۼӵ��ۼӺ���
            MOV    R5,A
            MOV    A,B
            ADDC   A,R4
            MOV    R4,A
            JNC    DM21
            INC    R3
DM21:       DJNZ   R2,DM20        ;�ۼ���ȫ������
;--------------------------------------------------
;���ֽڶ������޷��������Ե��ֽڶ�������
;�����������������R3��R4��R5�У�������R7�С�
;������Ϣ��OV=0 ʱ��˫�ֽ�����R4��R5�У�OV=1 ʱ�����
;Ӱ����Դ��PSW��A��B��R2��R7 ��ջ���� ���ֽ�
;--------------------------------------------------
DV31:       CLR    C
            MOV    A,R3
            SUBB   A,R7
            JC     DV30
            SETB   OV          ;�����
            RET
DV30:       MOV    R2,#10H     ;��R3R4R5��R7����R4R5
DM23:       CLR    C
            MOV    A,R5
            RLC    A
            MOV    R5,A
            MOV    A,R4
            RLC    A
            MOV    R4,A
            MOV    A,R3
            RLC    A
            MOV    R3,A
            MOV    F0,C
            CLR    C
            SUBB   A,R7
            ANL    C,/F0
            JC     DM24
            MOV    R3,A
            INC    R5
DM24:       DJNZ   R2,DM23
            MOV    A,R3           ;��������
            ADD    A,R3
            JC     DM25
            SUBB   A,R7
            JC     DM26
DM25:       INC    R5
            MOV    A,R5
            JNZ    DM26
            INC    R4
DM26:       CLR    OV
            RET                   ;����R4R5�� 
;==========================================================
;˫�ֽڶ������޷���������
;��������R2R3R4R5,������R6R7
;OV=0,����R4R5,������R2R3,OV=1���
;ʹ��ACC,PSW,R1,R2,R3,R4,R5,R6,R7
;----------------------------------------------------------
DIVD_42A:
DIVD:       CLR    C
            MOV    A,R3
            SUBB   A,R7
            MOV    A,R2
            SUBB   A,R6
            JC     DIVD1
            SETB   OV
            MOV    R2,#0
            MOV    R3,#0
            RET
DIVD1:      MOV    B,#10H              ;����˫�ֽ���
DIVD2:      CLR    C                   ;�����̺���������1λ
            MOV    A,R5
            RLC    A
            MOV    R5,A
            MOV    A,R4
            RLC    A
            MOV    R4,A
            MOV    A,R3
            RLC    A
            MOV    R3,A
            XCH    A,R2
            RLC    A
            XCH    A,R2
            MOV    F0,C                ;�������λ
            CLR    C
            SUBB   A,R7                ;(R2R3-R6R7)
            MOV    R1,A
            MOV    A,R2
            SUBB   A,R6
            ANL    C,/F0               ;�жϽ��
            JC     DIVD3
            MOV    R2,A                ;����������µ�����
            MOV    A,R1
            MOV    R3,A                ;����
            INC    R5                  ;�̵ĵ�λ��1
DIVD3:      DJNZ   B,DIVD2             ;������ʮ��λ��(R4R5)
            
DIVDEND:    RET
;==========================================================
;==========================================================
BEEPALARM:  LCALL  BEEP50M
            LCALL  DELAY50M
            LCALL  BEEP50M
            LCALL  DELAY50M
            LCALL  BEEP50M
            LCALL  DELAY1S
            ;LCALL  DELAY1S
            RET
BEEPSHOW:   LCALL  BEEP50M
            LCALL  DELAY50M
            LCALL  BEEP50M
            LCALL  DELAY1S
            LCALL  DELAY1S
            ;LCALL  DELAY1S
            RET
BEEP1SHOW:  LCALL  BEEP50M
            LCALL  DELAY50M
            LCALL  BEEP50M
            LCALL  DELAY1S
            RET
BEEP0SHOW:  LCALL  BEEP50M
            LCALL  DELAY50M
            LCALL  BEEP50M
            ;LCALL  DELAY1S
            ;LCALL  DELAY1S
            ;LCALL  DELAY1S
            RET
;==========================================================
BEEP50M:    SETB   BEEP
            LCALL  DELAY50M
            CLR    BEEP
            RET
;==========================================================
;4(LCALL)+4(RET)+3=11*(1/11M)=1US
;---------------------------------------
;DELAY1US:   NOP                 ;3
;            NOP
;            NOP
;            RET                 ;4
;---------------------------------------
;DELAY1US:			                  ;@8.000MHz(8)
;	          RET                 ;4
;---------------------------------------
DELAY1US:			                  ;@24.000MHz(24)
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          NOP
	          
	          RET                 ;4
;---------------------------------------
DELAY5US:			                  ;@24.000MHz(120)
	          NOP
	          
	          CLR    B_TMR           ;3X37=111
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          RET                    ;4
;---------------------------------------
DELAY8US:			                   ;@24.000MHz(192)
            NOP
	          
	          CLR    B_TMR           ;3X61=183
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;20
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;30
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;40
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;50
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;60
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          ;CLR    B_TMR
	          
	          ;CLR    B_TMR
	          ;CLR    B_TMR
	          ;CLR    B_TMR
	          ;CLR    B_TMR
	          ;CLR    B_TMR
	          ;CLR    B_TMR
	          
	          RET                    ;4
;---------------------------------------
DELAY10US:			                   ;@24.000MHz(240)
            NOP
            NOP
            NOP
            NOP
            NOP
            
DELAYA10US: NOP
            NOP
	          
	          CLR    B_TMR           ;3X75=225
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;20
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;30
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;40
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;50
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;60
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR          ;70
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          
	          RET                    ;4
;---------------------------------------
DELAY100US:
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          
	          RET
;---------------------------------------
DELAYA100US:
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          NOP
	          
	          
	          ;LCALL  DELAY10US
	          
	          RET
;---------------------------------------
DELAYB100US:
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY10US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          LCALL  DELAY1US
	          ;LCALL  DELAY1US
	          ;LCALL  DELAY1US
	          ;LCALL  DELAY1US
	          
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          CLR    B_TMR
	          NOP
	          
	          
	          ;LCALL  DELAY10US
	          
	          RET
;---------------------------------------
DELAY1MS:		
	          MOV    REG_TMR1,#100
NEXT_D1MS:
	          LCALL  DELAYA10US
	          DJNZ   REG_TMR1,NEXT_D1MS
	          RET
;----------------------------------------------------------
DELAY5MS:		
	          MOV    REG_TMR1,#100
NEXT_D5MS1: MOV    REG_TMR2,#5
NEXT_D5MS2: LCALL  DELAYA10US
	          DJNZ   REG_TMR2,NEXT_D5MS2
	          DJNZ   REG_TMR1,NEXT_D5MS1
	          RET
;----------------------------------------------------------
DELAY10MS:	 
            MOV    REG_TMR1,#100
NEXT_D10MS1:MOV    REG_TMR2,#10
NEXT_D10MS2:LCALL  DELAYA10US
	          DJNZ   REG_TMR2,NEXT_D10MS2
	          DJNZ   REG_TMR1,NEXT_D10MS1
	          RET
;----------------------------------------------------------
DELAY20MS:	 
            MOV    REG_TMR1,#100
NEXT_D20MS1:MOV    REG_TMR2,#20
NEXT_D20MS2:LCALL  DELAYA10US
	          DJNZ   REG_TMR2,NEXT_D20MS2
	          DJNZ   REG_TMR1,NEXT_D20MS1
	          RET
;----------------------------------------------------------
DELAY50M:   
            MOV    REG_TMR1,#100
NEXT_D50MS1:MOV    REG_TMR2,#50
NEXT_D50MS2:LCALL  DELAYA10US
	          DJNZ   REG_TMR2,NEXT_D50MS2
	          DJNZ   REG_TMR1,NEXT_D50MS1
            RET
;----------------------------------------------------------
DELAY100M:  
            MOV    REG_TMR1,#100
NEXT_D100MS1:MOV    REG_TMR2,#100
NEXT_D100MS2:LCALL  DELAYA10US
	          DJNZ   REG_TMR2,NEXT_D100MS2
	          DJNZ   REG_TMR1,NEXT_D100MS1
            RET
;----------------------------------------------------------
DELAY200M:  
            MOV    REG_TMR1,#100
NEXT_D200MS1:MOV    REG_TMR2,#200
NEXT_D200MS2:LCALL  DELAYA10US
	          DJNZ   REG_TMR2,NEXT_D200MS2
	          DJNZ   REG_TMR1,NEXT_D200MS1
            RET
;----------------------------------------------------------
DELAY500M:  
            MOV    REG_TMR1,#250
NEXT_D500MS1:MOV    REG_TMR2,#200
NEXT_D500MS2:LCALL  DELAYA10US
	          DJNZ   REG_TMR2,NEXT_D500MS2
	          DJNZ   REG_TMR1,NEXT_D500MS1
	          RET
;----------------------------------------------------------
DELAY1S:    
            MOV    REG_TMR1,#250
NEXT_D1S1:  MOV    REG_TMR2,#200
NEXT_D1S2:  LCALL  DELAYA10US
	          DJNZ   REG_TMR2,NEXT_D1S2
	          DJNZ   REG_TMR1,NEXT_D1S1
	          
	          MOV    REG_TMR1,#250
NEXT_D1S3:  MOV    REG_TMR2,#200
NEXT_D1S4:  LCALL  DELAYA10US
	          DJNZ   REG_TMR2,NEXT_D1S4
	          DJNZ   REG_TMR1,NEXT_D1S3
            RET
;----------------------------------------------------------

;==========================================================
;----------------------------------------------------------
            ORG    03FFBH              ;������β��
            NOP                        ;03FFBH
            NOP                        ;03FFCH
            LJMP   ERR_PIT             ;03FFDH
;----------------------------------------------------------
            END