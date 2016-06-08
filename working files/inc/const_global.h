#ifndef __CONST_GLOBAL__
#define __CONST_GLOBAL__

#define N_BIG   8
#define N_SMALL 2

//Величина, яка необхідна для періодичної (період 1  мс   ) генерації переривань каналом 1 таймеру 2 з прескаллером 2000 = (1999 + 1)
#define TIM2_CCR1_VAL                   30
//Величина, яка необхідна для періодичної (період 10 мс   ) генерації переривань каналом 1 таймеру 4 з прескаллером 600 = (599 + 1)
#define TIM4_CCR1_VAL                   1000
//Величина, яка необхідна для періодичної (період 1 мс   ) генерації переривань каналом 2 таймеру 4 з прескаллером 600 = (599 + 1)
#define TIM4_CCR2_VAL                   100
//Величина, яка необхідна для періодичної (як мінімум, період 10 мкс   ) генерації переривань каналом 3 таймеру 4 з прескаллером 600 = (599 + 1)
#define TIM4_CCR3_VAL                   1
//Величина, яка необхідна для періодичної (період 0,625 мс) генерації переривань каналом 1 таймеру 3 з прескаллером 1 = (0 + 1)
#define TIM5_CCR1_2_3_VAL               37500

#define MAX_NUMBER_LINES_VMP            8

#define DELTA_TIME_FOR_TIMERS           1
#define PERIOD_SIGNAL_OUTPUT_MODE_2     1000 /*мс*/

#define NUMBER_ANALOG_CANALES_VAL_1     6
#define NUMBER_ANALOG_CANALES_VAL_2     3

#define NUMBER_ANALOG_CANALES           (                               \
                                         NUMBER_ANALOG_CANALES_VAL_1  + \
                                         NUMBER_ANALOG_CANALES_VAL_2    \
                                        )

#define NUMBER_INPUTS_1                 5
#define NUMBER_INPUTS_2                 5
#define NUMBER_INPUTS                   (NUMBER_INPUTS_1 + NUMBER_INPUTS_2)
#define NUMBER_OUTPUTS_1                6
#define NUMBER_OUTPUTS_2                4
#define NUMBER_OUTPUTS                  (NUMBER_OUTPUTS_1 + NUMBER_OUTPUTS_2)

#define NUMBER_LEDS                     8

//#define NUMBER_DEFINED_ELEMENTS         6
#define NUMBER_DEFINED_FUNCTIONS        8
#define NUMBER_DEFINED_TRIGGERS         4
#define NUMBER_DEFINED_AND              8
#define NUMBER_DEFINED_OR               8
#define NUMBER_DEFINED_XOR              8
#define NUMBER_DEFINED_NOT              16

#define NUMBER_DEFINED_BUTTONS          6

#define NUMBER_IN_AND                   8
#define NUMBER_IN_OR                    8

#define NUMBER_GROUP_USTAVOK            4

enum _configuration {
MTZ_BIT_CONFIGURATION = 0,
ZDZ_BIT_CONFIGURATION,
APV_BIT_CONFIGURATION,
UROV_BIT_CONFIGURATION,
ZOP_BIT_CONFIGURATION,
UMIN_BIT_CONFIGURATION,
UMAX_BIT_CONFIGURATION,
AVR_BIT_CONFIGURATION,
EL_BIT_CONFIGURATION,

TOTAL_NUMBER_PROTECTION
};

/*****************************************/
//Константи для ранжування функціональних кнопок
/*****************************************/
enum __rang_button {
RANG_BUTTON_RESET_LEDS  = 0,
RANG_BUTTON_RESET_RELES,
RANG_BUTTON_MISCEVE_DYSTANCIJNE,
RANG_BUTTON_VKL_VV,
RANG_BUTTON_OTKL_VV,
RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV,

RANG_BUTTON_OTKL_AVR,
RANG_BUTTON_SBROS_BLOCK_AVR,

RANG_BUTTON_DF1_IN,
RANG_BUTTON_DF2_IN,
RANG_BUTTON_DF3_IN,
RANG_BUTTON_DF4_IN,
RANG_BUTTON_DF5_IN,
RANG_BUTTON_DF6_IN,
RANG_BUTTON_DF7_IN,
RANG_BUTTON_DF8_IN,
RANG_BUTTON_DT1_SET,
RANG_BUTTON_DT1_RESET,
RANG_BUTTON_DT2_SET,
RANG_BUTTON_DT2_RESET,
RANG_BUTTON_DT3_SET,
RANG_BUTTON_DT3_RESET,
RANG_BUTTON_DT4_SET,
RANG_BUTTON_DT4_RESET
};

#define NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON     6
#define NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON         0
#define NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON         0
#define NUMBER_APV_SIGNAL_FOR_RANG_BUTTON         0
#define NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON        0
#define NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON         0
#define NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON        0
#define NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON        0
#define NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON         2
#define NUMBER_EL_SIGNAL_FOR_RANG_BUTTON          16

#define NUMBER_TOTAL_SIGNAL_FOR_RANG_BUTTON       (                                            \
                                                   NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON     + \
                                                   NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_APV_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON        + \
                                                   NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON        + \
                                                   NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON        + \
                                                   NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_EL_SIGNAL_FOR_RANG_BUTTON            \
                                                  ) 
/*****************************************/

/*****************************************/
//Константи для ранжування дискретних входів
/*****************************************/
enum __rang_input {
RANG_INPUT_BLOCK_VKL_VV = 0,
RANG_INPUT_RESET_LEDS,
RANG_INPUT_RESET_RELES,
RANG_INPUT_MISCEVE_DYSTANCIJNE,
RANG_INPUT_STATE_VV,
RANG_INPUT_OTKL_VID_ZOVN_ZAHYSTIV,
RANG_INPUT_VKL_VV,
RANG_INPUT_CTRL_VKL,
RANG_INPUT_OTKL_VV,
RANG_INPUT_CTRL_OTKL,
RANG_INPUT_1_GRUPA_USTAVOK,
RANG_INPUT_2_GRUPA_USTAVOK,
RANG_INPUT_3_GRUPA_USTAVOK,
RANG_INPUT_4_GRUPA_USTAVOK,
RANG_INPUT_RESET_BLOCK_READY_TU_VID_ZAHYSTIV,

RANG_INPUT_BLOCK_MTZ1,
RANG_INPUT_BLOCK_MTZ2,
RANG_INPUT_BLOCK_USK_MTZ2,
RANG_INPUT_BLOCK_MTZ3,
RANG_INPUT_BLOCK_MTZ4,

RANG_INPUT_PUSK_ZDZ_VID_DV,

RANG_INPUT_STAT_BLK_APV,

RANG_INPUT_PUSK_UROV_VID_DV,

RANG_INPUT_BLOCK_ZOP,

RANG_INPUT_BLOCK_UMIN1,
RANG_INPUT_START_UMIN1,
RANG_INPUT_BLOCK_UMIN2,
RANG_INPUT_START_UMIN2,

RANG_INPUT_BLOCK_UMAX1,
RANG_INPUT_BLOCK_UMAX2,

RANG_INPUT_OTKL_AVR,
RANG_INPUT_SBROS_BLOCK_AVR,
RANG_INPUT_STAT_BLOCK_AVR,

RANG_INPUT_DF1_IN,
RANG_INPUT_DF2_IN,
RANG_INPUT_DF3_IN,
RANG_INPUT_DF4_IN,
RANG_INPUT_DF5_IN,
RANG_INPUT_DF6_IN,
RANG_INPUT_DF7_IN,
RANG_INPUT_DF8_IN,
RANG_INPUT_DT1_SET,
RANG_INPUT_DT1_RESET,
RANG_INPUT_DT2_SET,
RANG_INPUT_DT2_RESET,
RANG_INPUT_DT3_SET,
RANG_INPUT_DT3_RESET,
RANG_INPUT_DT4_SET,
RANG_INPUT_DT4_RESET,
};

#define NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT     15
#define NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT         5
#define NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT         1
#define NUMBER_APV_SIGNAL_FOR_RANG_INPUT         1
#define NUMBER_UROV_SIGNAL_FOR_RANG_INPUT        1
#define NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT         1
#define NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT        4
#define NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT        2
#define NUMBER_AVR_SIGNAL_FOR_RANG_INPUT         3
#define NUMBER_EL_SIGNAL_FOR_RANG_INPUT          16

#define NUMBER_TOTAL_SIGNAL_FOR_RANG_INPUT       (                                          \
                                                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + \
                                                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       + \
                                                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       + \
                                                  NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT       + \
                                                  NUMBER_AVR_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_EL_SIGNAL_FOR_RANG_INPUT           \
                                                 ) 
/*****************************************/

/*****************************************/
//Константи для ранжування дискретних виходів-свтодіодів-О-функцій-реєстраторів
/*****************************************/
enum __rang_output_led_df_reg {
RANG_BLOCK_VKL_VV = 0,
RANG_RESET_LEDS,
RANG_RESET_RELES,
RANG_MISCEVE_DYSTANCIJNE,
RANG_STATE_VV,
RANG_OTKL_VID_ZOVN_ZAHYSTIV,
RANG_VKL_VV,
RANG_CTRL_VKL,
RANG_OTKL_VV,
RANG_CTRL_OTKL,
RANG_PRYVID_VV,
RANG_PEREVYSHCHENNJA_Inom_VYMK,
RANG_KRYTYCHNYJ_RESURS_VYMYKACHA,
RANG_VYCHERPANYJ_RESURS_VYMYKACHA,
RANG_DEFECT,
RANG_AVAR_DEFECT,
RANG_WORK_A_REJESTRATOR,
RANG_WORK_D_REJESTRATOR,
RANG_VIDKL_VID_ZAKHYSTIV,
RANG_WORK_BO,
RANG_WORK_BV,
RANG_1_GRUPA_USTAVOK,
RANG_2_GRUPA_USTAVOK,
RANG_3_GRUPA_USTAVOK,
RANG_4_GRUPA_USTAVOK,
RANG_INVERS_DV_GRUPA_USTAVOK,
RANG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV,
RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV,
RANG_READY_TU,

RANG_BLOCK_MTZ1,
RANG_BLOCK_MTZ2,
RANG_BLOCK_USK_MTZ2,
RANG_BLOCK_MTZ3,
RANG_BLOCK_MTZ4,
RANG_SECTOR_VPERED_MTZN1,
RANG_SECTOR_NAZAD_MTZN1,
RANG_PO_MTZ1,
RANG_PO_MTZN1_VPERED,
RANG_PO_MTZN1_NAZAD,
RANG_PO_U_MTZPN1,
RANG_PO_MTZPN1,
RANG_MTZ1,
RANG_SECTOR_VPERED_MTZN2,
RANG_SECTOR_NAZAD_MTZN2,
RANG_PO_MTZ2,
RANG_PO_MTZN2_VPERED,
RANG_PO_MTZN2_NAZAD,
RANG_PO_U_MTZPN2,
RANG_PO_MTZPN2,
RANG_MTZ2,
RANG_SECTOR_VPERED_MTZN3,
RANG_SECTOR_NAZAD_MTZN3,
RANG_PO_MTZ3,
RANG_PO_MTZN3_VPERED,
RANG_PO_MTZN3_NAZAD,
RANG_PO_U_MTZPN3,
RANG_PO_MTZPN3,
RANG_MTZ3,
RANG_SECTOR_VPERED_MTZN4,
RANG_SECTOR_NAZAD_MTZN4,
RANG_PO_MTZ4,
RANG_PO_MTZN4_VPERED,
RANG_PO_MTZN4_NAZAD,
RANG_PO_U_MTZPN4,
RANG_PO_MTZPN4,
RANG_MTZ4,
RANG_PO_BLOCK_U_MTZN,
RANG_NCN_MTZ,

RANG_PUSK_ZDZ_VID_DV,
RANG_ZDZ,

RANG_STAT_BLK_APV,
RANG_APV1,
RANG_APV2,
RANG_APV3,
RANG_APV4,
RANG_APV_WORK,

RANG_PUSK_UROV_VID_DV,
RANG_PO_UROV,
RANG_UROV1,
RANG_UROV2,

RANG_BLOCK_ZOP,
RANG_PO_ZOP,
RANG_ZOP,

RANG_BLOCK_UMIN1,
RANG_START_UMIN1,
RANG_BLOCK_UMIN2,
RANG_START_UMIN2,
RANG_PO_UMIN1,
RANG_PO_UBLK_UMIN1,
RANG_PO_IBLK_UMIN1,
RANG_UMIN1,
RANG_PO_UMIN2,
RANG_PO_UBLK_UMIN2,
RANG_PO_IBLK_UMIN2,
RANG_UMIN2,

RANG_BLOCK_UMAX1,
RANG_PO_UMAX1,
RANG_UMAX1,
RANG_BLOCK_UMAX2,
RANG_PO_UMAX2,
RANG_UMAX2,

RANG_OUTPUT_LED_DF_REG_OTKL_AVR,
RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR,
RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR,
RANG_OUTPUT_LED_DF_REG_BLOCK_AVR_VID_ZAKHYSTIV,
RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN1,
RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX1,
RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2,
RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2,
RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_AVR,
RANG_OUTPUT_LED_DF_REG_PUSK_AVR,

RANG_DF1_IN,
RANG_DF1_OUT,
RANG_DF2_IN,
RANG_DF2_OUT,
RANG_DF3_IN,
RANG_DF3_OUT,
RANG_DF4_IN,
RANG_DF4_OUT,
RANG_DF5_IN,
RANG_DF5_OUT,
RANG_DF6_IN,
RANG_DF6_OUT,
RANG_DF7_IN,
RANG_DF7_OUT,
RANG_DF8_IN,
RANG_DF8_OUT,
RANG_DT1_SET,
RANG_DT1_RESET,
RANG_DT1_OUT,
RANG_DT2_SET,
RANG_DT2_RESET,
RANG_DT2_OUT,
RANG_DT3_SET,
RANG_DT3_RESET,
RANG_DT3_OUT,
RANG_DT4_SET,
RANG_DT4_RESET,
RANG_DT4_OUT,
RANG_D_AND1,
RANG_D_AND2,
RANG_D_AND3,
RANG_D_AND4,
RANG_D_AND5,
RANG_D_AND6,
RANG_D_AND7,
RANG_D_AND8,
RANG_D_OR1,
RANG_D_OR2,
RANG_D_OR3,
RANG_D_OR4,
RANG_D_OR5,
RANG_D_OR6,
RANG_D_OR7,
RANG_D_OR8,
RANG_D_XOR1,
RANG_D_XOR2,
RANG_D_XOR3,
RANG_D_XOR4,
RANG_D_XOR5,
RANG_D_XOR6,
RANG_D_XOR7,
RANG_D_XOR8,
RANG_D_NOT1,
RANG_D_NOT2,
RANG_D_NOT3,
RANG_D_NOT4,
RANG_D_NOT5,
RANG_D_NOT6,
RANG_D_NOT7,
RANG_D_NOT8,
RANG_D_NOT9,
RANG_D_NOT10,
RANG_D_NOT11,
RANG_D_NOT12,
RANG_D_NOT13,
RANG_D_NOT14,
RANG_D_NOT15,
RANG_D_NOT16,
RANG_ERROR_CONF_EL
};

#define NUMBER_GENERAL_SIGNAL_FOR_RANG     29
#define NUMBER_MTZ_SIGNAL_FOR_RANG         39
#define NUMBER_ZDZ_SIGNAL_FOR_RANG         2
#define NUMBER_APV_SIGNAL_FOR_RANG         6
#define NUMBER_UROV_SIGNAL_FOR_RANG        4
#define NUMBER_ZOP_SIGNAL_FOR_RANG         3
#define NUMBER_UMIN_SIGNAL_FOR_RANG        12
#define NUMBER_UMAX_SIGNAL_FOR_RANG        6
#define NUMBER_AVR_SIGNAL_FOR_RANG         10
#define NUMBER_EL_SIGNAL_FOR_RANG          69

#define NUMBER_TOTAL_SIGNAL_FOR_RANG       (                                                      \
                                                              NUMBER_GENERAL_SIGNAL_FOR_RANG    + \
                                                              NUMBER_MTZ_SIGNAL_FOR_RANG        + \
                                                              NUMBER_ZDZ_SIGNAL_FOR_RANG        + \
                                                              NUMBER_APV_SIGNAL_FOR_RANG        + \
                                                              NUMBER_UROV_SIGNAL_FOR_RANG       + \
                                                              NUMBER_ZOP_SIGNAL_FOR_RANG        + \
                                                              NUMBER_UMIN_SIGNAL_FOR_RANG       + \
                                                              NUMBER_UMAX_SIGNAL_FOR_RANG       + \
                                                              NUMBER_AVR_SIGNAL_FOR_RANG        + \
                                                              NUMBER_EL_SIGNAL_FOR_RANG           \
                                                             ) 

/*****************************************/

enum __mtz_const {
  RANG_BLOCK_MTZ = 0,
  RANG_BLOCK_USK_MTZ,
  RANG_SECTOR_VPERED_MTZN,
  RANG_SECTOR_NAZAD_MTZN,
  RANG_PO_MTZ,
  RANG_PO_MTZN_VPERED,
  RANG_PO_MTZN_NAZAD,
  RANG_PO_U_MTZPN,
  RANG_PO_MTZPN,
  RANG_MTZ,
  /*************************************/
  MTZ_SETTINGS_LENGTH
};

enum __mtz_levels_const {
  MTZ_LEVEL1 = 0,
  MTZ_LEVEL2,
  MTZ_LEVEL3,
  MTZ_LEVEL4,
  /*************************************/
  NUMBER_LEVEL_MTZ //Количество ступеней МТЗ
};

enum __mtz_abc_const {
  PHASE_A_INDEX = 0,
  PHASE_B_INDEX,
  PHASE_C_INDEX
};

enum __mtz_abc_direction_const {
  MTZ_NEVYZN = 0,
  MTZ_VPERED,
  MTZ_NAZAD
};

/*****************************************/
//Макски сигналів, які активовуються або з д.входів, або з інтирфейсів чи функціональних кнопок
/*****************************************/

#define MASKA_FOR_INPUT_SIGNALS_0        (unsigned int)(              \
    (1 << (RANG_BLOCK_VKL_VV - 0))                            /* 0*/  \
  | (1 << (RANG_RESET_LEDS - 0))                              /* 1*/  \
  | (1 << (RANG_RESET_RELES - 0))                             /* 2*/  \
  | (1 << (RANG_MISCEVE_DYSTANCIJNE - 0))                     /* 3*/  \
  | (1 << (RANG_STATE_VV - 0))                                /* 4*/  \
  | (1 << (RANG_OTKL_VID_ZOVN_ZAHYSTIV - 0))                  /* 5*/  \
  | (1 << (RANG_VKL_VV - 0))                                  /* 6*/  \
  | (1 << (RANG_CTRL_VKL - 0))                                /* 7*/  \
  | (1 << (RANG_OTKL_VV - 0))                                 /* 8*/  \
  | (1 << (RANG_CTRL_OTKL - 0))                               /* 9*/  \
  | (1 << (RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV - 0))       /*27*/  \
  | (1 << (RANG_BLOCK_MTZ1 - 0))                              /*29*/  \
  | (1 << (RANG_BLOCK_MTZ2 - 0))                              /*30*/  \
  | (1 << (RANG_BLOCK_USK_MTZ2 - 0))                          /*31*/  \
)

#define MASKA_FOR_INPUT_SIGNALS_1        (unsigned int)(              \
    (1 << (RANG_BLOCK_MTZ3 - 32))                             /*32*/  \
  | (1 << (RANG_BLOCK_MTZ4 - 32))                             /*33*/  \
)

#define MASKA_FOR_INPUT_SIGNALS_2        (unsigned int)(            \
  | (1 << (RANG_PUSK_ZDZ_VID_DV - 64))                        /*75*/\
)
    
#define MASKA_FOR_INPUT_SIGNALS_3        (unsigned int)(              \
  | (1 << (RANG_STAT_BLK_APV - 96))                           /*115*/ \
)
    
#define MASKA_FOR_INPUT_SIGNALS_4        (unsigned int)(              \
    (1 << (RANG_PUSK_UROV_VID_DV - 128))                      /*132*/ \
  | (1 << (RANG_BLOCK_ZOP - 128))                             /*136*/ \
  | (1 << (RANG_BLOCK_UMIN1 - 128))                           /*139*/ \
  | (1 << (RANG_START_UMIN1 - 128))                           /*140*/ \
  | (1 << (RANG_BLOCK_UMIN2 - 128))                           /*141*/ \
  | (1 << (RANG_START_UMIN2 - 128))                           /*142*/ \
  | (1 << (RANG_BLOCK_UMAX1 - 128))                           /*151*/ \
  | (1 << (RANG_BLOCK_UMAX2 - 128))                           /*154*/ \
  | (1 << (RANG_REG_OTKL_AVR - 128))\
  | (1 << (RANG_REG_SBROS_BLOCK_AVR  - 128))\
  | (1 << (RANG_STAT_BLOCK_AVR - 128))\
  | (1 << (RANG_DF1_IN - 128))                                /*157*/ \
  | (1 << (RANG_DF2_IN - 128))                                /*159*/ \
)
    
#define MASKA_FOR_INPUT_SIGNALS_5        (unsigned int)(              \
    (1 << (RANG_DF3_IN - 160))                                /*161*/ \
  | (1 << (RANG_DF4_IN - 160))                                /*163*/ \
  | (1 << (RANG_DF5_IN - 160))                                /*165*/ \
  | (1 << (RANG_DF6_IN - 160))                                /*167*/ \
  | (1 << (RANG_DF7_IN - 160))                                /*169*/ \
  | (1 << (RANG_DF8_IN - 160))                                /*171*/ \
  | (1 << (RANG_DT1_SET - 160))                               /*173*/ \
  | (1 << (RANG_DT1_RESET - 160))                             /*174*/ \
  | (1 << (RANG_DT2_SET - 160))                               /*176*/ \
  | (1 << (RANG_DT2_RESET - 160))                             /*177*/ \
  | (1 << (RANG_DT3_SET - 160))                               /*179*/ \
  | (1 << (RANG_DT3_RESET - 160))                             /*180*/ \
  | (1 << (RANG_DT4_SET - 160))                               /*182*/ \
  | (1 << (RANG_DT4_RESET - 160))                             /*183*/ \
)

#define MASKA_FOR_INPUT_SIGNALS_6                  0
#define MASKA_FOR_INPUT_SIGNALS_7                  0
/*****************************************/

/*****************************************/
//Макски всіх сигналів МСЗ
/*****************************************/
#define MASKA_MTZ_SIGNALS_0        (unsigned int)(                   \
     (1 << (RANG_BLOCK_MTZ1 - 0))                             /* 29*/\
   | (1 << (RANG_BLOCK_MTZ2 - 0))                             /* 30*/\
   | (1 << (RANG_BLOCK_USK_MTZ2 - 0))                         /* 31*/\
)

#define MASKA_MTZ_SIGNALS_1        (unsigned int)(                   \
     (1 << (RANG_BLOCK_MTZ3 - 32))                            /* 32*/\
   | (1 << (RANG_BLOCK_MTZ4 - 32))                            /* 33*/\
   | (1 << (RANG_SECTOR_VPERED_MTZN1 - 32))                   /* 34*/\
   | (1 << (RANG_SECTOR_NAZAD_MTZN1 - 32))                    /* 35*/\
   | (1 << (RANG_PO_MTZ1 - 32))                               /* 36*/\
   | (1 << (RANG_PO_MTZN1_VPERED - 32))                       /* 37*/\
   | (1 << (RANG_PO_MTZN1_NAZAD - 32))                        /* 38*/\
   | (1 << (RANG_PO_U_MTZPN1 - 32))                           /* 39*/\
   | (1 << (RANG_PO_MTZPN1 - 32))                             /* 40*/\
   | (1 << (RANG_MTZ1 - 32))                                  /* 41*/\
   | (1 << (RANG_SECTOR_VPERED_MTZN2 - 32))                   /* 42*/\
   | (1 << (RANG_SECTOR_NAZAD_MTZN2 - 32))                    /* 43*/\
   | (1 << (RANG_PO_MTZ2 - 32))                               /* 44*/\
   | (1 << (RANG_PO_MTZN2_VPERED - 32))                       /* 45*/\
   | (1 << (RANG_PO_MTZN2_NAZAD - 32))                        /* 46*/\
   | (1 << (RANG_PO_U_MTZPN2 - 32))                           /* 47*/\
   | (1 << (RANG_PO_MTZPN2 - 32))                             /* 48*/\
   | (1 << (RANG_MTZ2 - 32))                                  /* 49*/\
   | (1 << (RANG_SECTOR_VPERED_MTZN3 - 32))                   /* 50*/\
   | (1 << (RANG_SECTOR_NAZAD_MTZN3 - 32))                    /* 51*/\
   | (1 << (RANG_PO_MTZ3 - 32))                               /* 52*/\
   | (1 << (RANG_PO_MTZN3_VPERED - 32))                       /* 53*/\
   | (1 << (RANG_PO_MTZN3_NAZAD - 32))                        /* 54*/\
   | (1 << (RANG_PO_U_MTZPN3 - 32))                           /* 55*/\
   | (1 << (RANG_PO_MTZPN3 - 32))                             /* 56*/\
   | (1 << (RANG_MTZ3 - 32))                                  /* 57*/\
   | (1 << (RANG_SECTOR_VPERED_MTZN4 - 32))                   /* 58*/\
   | (1 << (RANG_SECTOR_NAZAD_MTZN4 - 32))                    /* 59*/\
   | (1 << (RANG_PO_MTZ4 - 32))                               /* 60*/\
   | (1 << (RANG_PO_MTZN4_VPERED - 32))                       /* 61*/\
   | (1 << (RANG_PO_MTZN4_NAZAD - 32))                        /* 62*/\
   | (1 << (RANG_PO_U_MTZPN4 - 32))                           /* 63*/\
)

#define MASKA_MTZ_SIGNALS_2        (unsigned int)(                   \
     (1 << (RANG_PO_MTZPN4 - 64))                             /* 64*/\
   | (1 << (RANG_MTZ4 - 64))                                  /* 65*/\
   | (1 << (RANG_PO_BLOCK_U_MTZN - 64))                       /* 66*/\
   | (1 << (RANG_NCN_MTZ - 64))                               /* 67*/\
)

#define MASKA_MTZ_SIGNALS_3                  0
#define MASKA_MTZ_SIGNALS_4                  0
#define MASKA_MTZ_SIGNALS_5                  0
#define MASKA_MTZ_SIGNALS_6                  0
#define MASKA_MTZ_SIGNALS_7                  0
/*****************************************/
     
/*****************************************/
//Макски всіх сигналів ЗДЗ
/*****************************************/
#define MASKA_ZDZ_SIGNALS_0                  0
#define MASKA_ZDZ_SIGNALS_1                  0

#define MASKA_ZDZ_SIGNALS_2        (unsigned int)(                  \
     (1 << (RANG_PUSK_ZDZ_VID_DV - 64))                       /*75*/\
   | (1 << (RANG_ZDZ - 64))                                   /*76*/\
)

#define MASKA_ZDZ_SIGNALS_3                  0
#define MASKA_ZDZ_SIGNALS_4                  0
#define MASKA_ZDZ_SIGNALS_5                  0
#define MASKA_ZDZ_SIGNALS_6                  0
#define MASKA_ZDZ_SIGNALS_7                  0
/*****************************************/
     
/*****************************************/
//Макски всіх сигналів АПВ
/*****************************************/
#define MASKA_APV_SIGNALS_0                  0
#define MASKA_APV_SIGNALS_1                  0
#define MASKA_APV_SIGNALS_2                  0
     
#define MASKA_APV_SIGNALS_3        (unsigned int)(                   \
     (1 << (RANG_STAT_BLK_APV - 96))                          /*115*/\
   | (1 << (RANG_APV1 - 96))                                  /*116*/\
   | (1 << (RANG_APV2 - 96))                                  /*117*/\
   | (1 << (RANG_APV3 - 96))                                  /*118*/\
   | (1 << (RANG_APV4 - 96))                                  /*119*/\
   | (1 << (RANG_APV_WORK - 96))                              /*120*/\
)

#define MASKA_APV_SIGNALS_4                  0
#define MASKA_APV_SIGNALS_5                  0
#define MASKA_APV_SIGNALS_6                  0
#define MASKA_APV_SIGNALS_7                  0
/*****************************************/

/*****************************************/
//Макски всіх сигналів ПРВВ
/*****************************************/
#define MASKA_UROV_SIGNALS_0                 0
#define MASKA_UROV_SIGNALS_1                 0
#define MASKA_UROV_SIGNALS_2                 0

#define MASKA_UROV_SIGNALS_3       (unsigned int)(                   \
     (1 << (RANG_PUSK_UROV_VID_DV - 128))                     /*132*/\
   | (1 << (RANG_PO_UROV - 128))                              /*133*/\
   | (1 << (RANG_UROV1 - 128))                                /*134*/\
   | (1 << (RANG_UROV2 - 128))                                /*135*/\
)

#define MASKA_UROV_SIGNALS_4                 0
#define MASKA_UROV_SIGNALS_5                 0
#define MASKA_UROV_SIGNALS_6                 0
#define MASKA_UROV_SIGNALS_7                 0
/*****************************************/

/*****************************************/
//Макски всіх сигналів ЗЗП
/*****************************************/
#define MASKA_ZOP_SIGNALS_0                  0
#define MASKA_ZOP_SIGNALS_1                  0
#define MASKA_ZOP_SIGNALS_2                  0
#define MASKA_ZOP_SIGNALS_3                  0

#define MASKA_ZOP_SIGNALS_4        (unsigned int)(                   \
     (1 << (RANG_BLOCK_ZOP - 128))                            /*136*/\
   | (1 << (RANG_PO_ZOP - 128))                               /*137*/\
   | (1 << (RANG_ZOP - 128))                                  /*138*/\
)

#define MASKA_ZOP_SIGNALS_5                  0
#define MASKA_ZOP_SIGNALS_6                  0
#define MASKA_ZOP_SIGNALS_7                  0
/*****************************************/

/*****************************************/
//Макски всіх сигналів ЗНмін
/*****************************************/
#define MASKA_UMIN_SIGNALS_0                 0
#define MASKA_UMIN_SIGNALS_1                 0
#define MASKA_UMIN_SIGNALS_2                 0
#define MASKA_UMIN_SIGNALS_3                 0
     
#define MASKA_UMIN_SIGNALS_4       (unsigned int)(                                     \
     (1 << (RANG_BLOCK_UMIN1 - 128))                          /*139*/\
   | (1 << (RANG_START_UMIN1 - 128))                          /*140*/\
   | (1 << (RANG_BLOCK_UMIN2 - 128))                          /*141*/\
   | (1 << (RANG_START_UMIN2 - 128))                          /*142*/\
   | (1 << (RANG_PO_UMIN1 - 128))                             /*143*/\
   | (1 << (RANG_PO_UBLK_UMIN1 - 128))                        /*144*/\
   | (1 << (RANG_PO_IBLK_UMIN1 - 128))                        /*145*/\
   | (1 << (RANG_UMIN1 - 128))                                /*146*/\
   | (1 << (RANG_PO_UMIN2 - 128))                             /*147*/\
   | (1 << (RANG_PO_UBLK_UMIN2 - 128))                        /*148*/\
   | (1 << (RANG_PO_IBLK_UMIN2 - 128))                        /*149*/\
   | (1 << (RANG_UMIN2 - 128))                                /*150*/\
)

#define MASKA_UMIN_SIGNALS_5                 0
#define MASKA_UMIN_SIGNALS_6                 0
#define MASKA_UMIN_SIGNALS_7                 0
/*****************************************/

/*****************************************/
//Макски всіх сигналів ЗНмакс
/*****************************************/
#define MASKA_UMAX_SIGNALS_0                 0
#define MASKA_UMAX_SIGNALS_1                 0
#define MASKA_UMAX_SIGNALS_2                 0
#define MASKA_UMAX_SIGNALS_3                 0
     
#define MASKA_UMAX_SIGNALS_4       (unsigned int)(                                     \
     (1 << (RANG_BLOCK_UMAX1 - 128))                          /*151*/\
   | (1 << (RANG_PO_UMAX1 - 128))                             /*152*/\
   | (1 << (RANG_UMAX1 - 128))                                /*153*/\
   | (1 << (RANG_BLOCK_UMAX2 - 128))                          /*154*/\
   | (1 << (RANG_PO_UMAX2 - 128))                             /*155*/\
   | (1 << (RANG_UMAX2 - 128))                                /*156*/\
)

#define MASKA_UMAX_SIGNALS_5                 0
#define MASKA_UMAX_SIGNALS_6                 0
#define MASKA_UMAX_SIGNALS_7                 0
/*****************************************/

/*****************************************/
//Макски всіх сигналів розширеної логіки
/*****************************************/
#define MASKA_EL_SIGNALS_0                  0
#define MASKA_EL_SIGNALS_1                  0
#define MASKA_EL_SIGNALS_2                  0
#define MASKA_EL_SIGNALS_3                  0

#define MASKA_EL_SIGNALS_4        (unsigned int)(                     \
    (1 << (RANG_DF1_IN - 128))                                /*157*/ \
  | (1 << (RANG_DF1_OUT - 128))                               /*158*/ \
  | (1 << (RANG_DF2_IN - 128))                                /*159*/ \
)
    
#define MASKA_EL_SIGNALS_5        (unsigned int)(                     \
    (1 << (RANG_DF2_OUT - 160))                               /*160*/ \
  | (1 << (RANG_DF3_IN - 160))                                /*161*/ \
  | (1 << (RANG_DF3_OUT - 160))                               /*162*/ \
  | (1 << (RANG_DF4_IN - 160))                                /*163*/ \
  | (1 << (RANG_DF4_OUT - 160))                               /*164*/ \
  | (1 << (RANG_DF5_IN - 160))                                /*165*/ \
  | (1 << (RANG_DF5_OUT - 160))                               /*166*/ \
  | (1 << (RANG_DF6_IN - 160))                                /*167*/ \
  | (1 << (RANG_DF6_OUT - 160))                               /*168*/ \
  | (1 << (RANG_DF7_IN - 160))                                /*169*/ \
  | (1 << (RANG_DF7_OUT - 160))                               /*170*/ \
  | (1 << (RANG_DF8_IN - 160))                                /*171*/ \
  | (1 << (RANG_DF8_OUT - 160))                               /*172*/ \
  | (1 << (RANG_DT1_SET - 160))                               /*173*/ \
  | (1 << (RANG_DT1_RESET - 160))                             /*174*/ \
  | (1 << (RANG_DT1_OUT - 160))                               /*175*/ \
  | (1 << (RANG_DT2_SET - 160))                               /*176*/ \
  | (1 << (RANG_DT2_RESET - 160))                             /*177*/ \
  | (1 << (RANG_DT2_OUT - 160))                               /*178*/ \
  | (1 << (RANG_DT3_SET - 160))                               /*179*/ \
  | (1 << (RANG_DT3_RESET - 160))                             /*180*/ \
  | (1 << (RANG_DT3_OUT - 160))                               /*181*/ \
  | (1 << (RANG_DT4_SET - 160))                               /*182*/ \
  | (1 << (RANG_DT4_RESET - 160))                             /*183*/ \
  | (1 << (RANG_DT4_OUT - 160))                               /*184*/ \
  | (1 << (RANG_D_AND1 - 160))                                /*185*/ \
  | (1 << (RANG_D_AND2 - 160))                                /*186*/ \
  | (1 << (RANG_D_AND3 - 160))                                /*187*/ \
  | (1 << (RANG_D_AND4 - 160))                                /*188*/ \
  | (1 << (RANG_D_AND5 - 160))                                /*189*/ \
  | (1 << (RANG_D_AND6 - 160))                                /*190*/ \
  | (1 << (RANG_D_AND7 - 160))                                /*191*/ \
)

#define MASKA_EL_SIGNALS_6        (unsigned int)(                     \
    (1 << (RANG_D_AND8 - 192))                                /*192*/ \
  | (1 << (RANG_D_OR1 - 192))                                 /*193*/ \
  | (1 << (RANG_D_OR2 - 192))                                 /*194*/ \
  | (1 << (RANG_D_OR3 - 192))                                 /*195*/ \
  | (1 << (RANG_D_OR4 - 192))                                 /*196*/ \
  | (1 << (RANG_D_OR5 - 192))                                 /*197*/ \
  | (1 << (RANG_D_OR6 - 192))                                 /*198*/ \
  | (1 << (RANG_D_OR7 - 192))                                 /*199*/ \
  | (1 << (RANG_D_OR8 - 192))                                 /*200*/ \
  | (1 << (RANG_D_XOR1 - 192))                                /*201*/ \
  | (1 << (RANG_D_XOR2 - 192))                                /*202*/ \
  | (1 << (RANG_D_XOR3 - 192))                                /*203*/ \
  | (1 << (RANG_D_XOR4 - 192))                                /*204*/ \
  | (1 << (RANG_D_XOR5 - 192))                                /*205*/ \
  | (1 << (RANG_D_XOR6 - 192))                                /*206*/ \
  | (1 << (RANG_D_XOR7 - 192))                                /*207*/ \
  | (1 << (RANG_D_XOR8 - 192))                                /*208*/ \
  | (1 << (RANG_D_NOT1 - 192))                                /*209*/ \
  | (1 << (RANG_D_NOT2 - 192))                                /*210*/ \
  | (1 << (RANG_D_NOT3 - 192))                                /*211*/ \
  | (1 << (RANG_D_NOT4 - 192))                                /*212*/ \
  | (1 << (RANG_D_NOT5 - 192))                                /*213*/ \
  | (1 << (RANG_D_NOT6 - 192))                                /*214*/ \
  | (1 << (RANG_D_NOT7 - 192))                                /*215*/ \
  | (1 << (RANG_D_NOT8 - 192))                                /*216*/ \
  | (1 << (RANG_D_NOT9 - 192))                                /*217*/ \
  | (1 << (RANG_D_NOT10 - 192))                               /*218*/ \
  | (1 << (RANG_D_NOT11 - 192))                               /*219*/ \
  | (1 << (RANG_D_NOT12 - 192))                               /*220*/ \
  | (1 << (RANG_D_NOT13 - 192))                               /*221*/ \
  | (1 << (RANG_D_NOT14 - 192))                               /*222*/ \
  | (1 << (RANG_D_NOT15 - 192))                               /*223*/ \
)

#define MASKA_EL_SIGNALS_7        (unsigned int)(                     \
    (1 << (RANG_D_NOT16 - 224))                               /*224*/ \
  | (1 << (RANG_ERROR_CONF_EL - 225))                         /*225*/ \
)
/*****************************************/


/*****************************************/
//Макска сигналів, які мають записуватися у енергонезалежну пам'ять
/*****************************************/
#define MASKA_TRIGGER_SIGNALES_0                  0
#define MASKA_TRIGGER_SIGNALES_1                  0
#define MASKA_TRIGGER_SIGNALES_2                  0
#define MASKA_TRIGGER_SIGNALES_3                  0
#define MASKA_TRIGGER_SIGNALES_4                  0

#define MASKA_TRIGGER_SIGNALES_5               (unsigned int)(        \
     (1 << (RANG_BLOCK_AVR_VID_ZAKHYSTIV - 160))\
   | (1 << (RANG_BLOCK_KRATN_AVR         - 160))\
   | (1 << (RANG_DT1_OUT - 160))                              /*175*/ \
   | (1 << (RANG_DT2_OUT - 160))                              /*178*/ \
   | (1 << (RANG_DT3_OUT - 160))                              /*181*/ \
   | (1 << (RANG_DT4_OUT - 160))                              /*184*/ \
)     

#define MASKA_TRIGGER_SIGNALES_6                  0
#define MASKA_TRIGGER_SIGNALES_7                  0
/*****************************************/

/*****************************************/
//Макска для блокування зміни груп  уставок
/*****************************************/
#define MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_0 (unsigned int)(       \
     (1 << (RANG_WORK_BO - 0))                                /* 19*/\
   | (1 << (RANG_WORK_BV - 0))                                /* 20*/\
)

#define MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_1 (unsigned int)(       \
     (1 << (RANG_PO_MTZ1 - 32))                               /* 36*/\
   | (1 << (RANG_PO_MTZN1_VPERED - 32))                       /* 37*/\
   | (1 << (RANG_PO_MTZN1_NAZAD - 32))                        /* 38*/\
   | (1 << (RANG_PO_MTZPN1 - 32))                             /* 39*/\
   | (1 << (RANG_MTZ1 - 32))                                  /* 41*/\
   | (1 << (RANG_PO_MTZ2 - 32))                               /* 44*/\
   | (1 << (RANG_PO_MTZN2_VPERED - 32))                       /* 45*/\
   | (1 << (RANG_PO_MTZN2_NAZAD - 32))                        /* 46*/\
   | (1 << (RANG_PO_MTZPN2 - 32))                             /* 47*/\
   | (1 << (RANG_MTZ2 - 32))                                  /* 49*/\
   | (1 << (RANG_PO_MTZ3 - 32))                               /* 52*/\
   | (1 << (RANG_PO_MTZN3_VPERED - 32))                       /* 53*/\
   | (1 << (RANG_PO_MTZN3_NAZAD - 32))                        /* 54*/\
   | (1 << (RANG_PO_MTZPN3 - 32))                             /* 55*/\
   | (1 << (RANG_MTZ3 - 32))                                  /* 57*/\
   | (1 << (RANG_PO_MTZ4 - 32))                               /* 60*/\
   | (1 << (RANG_PO_MTZN4_VPERED - 32))                       /* 61*/\
   | (1 << (RANG_PO_MTZN4_NAZAD - 32))                        /* 62*/\
)

#define MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_2 (unsigned int)(       \
     (1 << (RANG_PO_MTZPN4 - 64))                             /* 64*/\
   | (1 << (RANG_MTZ4 - 64))                                  /* 65*/\
)

#define MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_3 (unsigned int)(       \
     (1 << (RANG_APV_WORK - 96))                              /*120*/\
)

#define MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_4 (unsigned int)(       \
   | (1 << (RANG_PO_UROV - 128))                              /*133*/\
   | (1 << (RANG_UROV1 - 128))                                /*134*/\
   | (1 << (RANG_UROV2 - 128))                                /*135*/\
   | (1 << (RANG_PO_ZOP - 128))                               /*137*/\
   | (1 << (RANG_ZOP - 128))                                  /*138*/\
   | (1 << (RANG_PO_UMIN1 - 128))                             /*143*/\
   | (1 << (RANG_UMIN1 - 128))                                /*146*/\
   | (1 << (RANG_PO_UMIN2 - 128))                             /*147*/\
   | (1 << (RANG_UMIN2 - 128))                                /*150*/\
   | (1 << (RANG_PO_UMAX1 - 128))                             /*152*/\
   | (1 << (RANG_UMAX1 - 128))                                /*153*/\
   | (1 << (RANG_PO_UMAX2 - 128))                             /*154*/\
   | (1 << (RANG_UMAX2 - 128))                                /*156*/\
)

#define MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_5  0
#define MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_6  0
#define MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_7  0
/*****************************************/

/*****************************************/
//Макска інформативних сигналів
/*****************************************/

#define MASKA_INFO_SIGNALES_0  (unsigned int)(                        \
     (1 << (RANG_STATE_VV - 0))                               /* 4*/  \
   | (1 << (RANG_DEFECT - 0))                                 /*14*/  \
   | (1 << (RANG_AVAR_DEFECT - 0))                            /*15*/  \
   | (1 << (RANG_WORK_A_REJESTRATOR - 0))                     /*16*/  \
   | (1 << (RANG_WORK_D_REJESTRATOR - 0))                     /*16*/  \
)     

#define MASKA_INFO_SIGNALES_1                  0
#define MASKA_INFO_SIGNALES_2                  0
#define MASKA_INFO_SIGNALES_3                  0
#define MASKA_INFO_SIGNALES_4                  0
#define MASKA_INFO_SIGNALES_5                  0
#define MASKA_INFO_SIGNALES_6                  0
#define MASKA_INFO_SIGNALES_7                  0
/*****************************************/

/*****************************************/
/*
Макска для дискретного реєстратора, яка визначає, при активності яких функцій продовжувати утримувати дискретний реєстратор у активному стані
(якщо) він вже є активним до цього часу
*/
/*****************************************/
#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_0 (unsigned int)(      \
     (1 << (RANG_OTKL_VID_ZOVN_ZAHYSTIV - 0))                 /*  5*/\
   | (1 << (RANG_VKL_VV - 0))                                 /*  6*/\
   | (1 << (RANG_OTKL_VV - 0))                                /*  8*/\
   | (1 << (RANG_VIDKL_VID_ZAKHYSTIV - 0))                    /* 16*/\
   | (1 << (RANG_WORK_BO - 0))                                /* 19*/\
   | (1 << (RANG_WORK_BV - 0))                                /* 20*/\
)  

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_1 (unsigned int)(      \
     (1 << (RANG_PO_MTZ1 - 32))                               /* 36*/\
   | (1 << (RANG_PO_MTZN1_VPERED - 32))                       /* 37*/\
   | (1 << (RANG_PO_MTZN1_NAZAD - 32))                        /* 38*/\
   | (1 << (RANG_PO_MTZPN1 - 32))                             /* 40*/\
   | (1 << (RANG_MTZ1 - 32))                                  /* 41*/\
   | (1 << (RANG_PO_MTZ2 - 32))                               /* 44*/\
   | (1 << (RANG_PO_MTZN2_VPERED - 32))                       /* 45*/\
   | (1 << (RANG_PO_MTZN2_NAZAD - 32))                        /* 46*/\
   | (1 << (RANG_PO_MTZPN2 - 32))                             /* 48*/\
   | (1 << (RANG_MTZ2 - 32))                                  /* 49*/\
   | (1 << (RANG_PO_MTZ3 - 32))                               /* 52*/\
   | (1 << (RANG_PO_MTZN3_VPERED - 32))                       /* 53*/\
   | (1 << (RANG_PO_MTZN3_NAZAD - 32))                        /* 54*/\
   | (1 << (RANG_PO_MTZPN3 - 32))                             /* 56*/\
   | (1 << (RANG_MTZ3 - 32))                                  /* 57*/\
   | (1 << (RANG_PO_MTZ4 - 32))                               /* 60*/\
   | (1 << (RANG_PO_MTZN4_VPERED - 32))                       /* 61*/\
   | (1 << (RANG_PO_MTZN4_NAZAD - 32))                        /* 62*/\
)            

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_2 (unsigned int)(      \
     (1 << (RANG_PO_MTZPN4 - 64))                             /* 64*/\
   | (1 << (RANG_MTZ4 - 64))                                  /* 65*/\
)  

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_3 (unsigned int)(      \
   | (1 << (RANG_APV1 - 96))                                  /*116*/\
   | (1 << (RANG_APV2 - 96))                                  /*117*/\
   | (1 << (RANG_APV3 - 96))                                  /*118*/\
   | (1 << (RANG_APV4 - 96))                                  /*119*/\
   | (1 << (RANG_APV_WORK - 96))                              /*120*/\
)  

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_4 (unsigned int)(      \
     (1 << (RANG_PUSK_UROV_VID_DV - 128))                     /*132*/\
   | (1 << (RANG_PO_UROV - 128))                              /*133*/\
   | (1 << (RANG_UROV1 - 128))                                /*134*/\
   | (1 << (RANG_UROV2 - 128))                                /*135*/\
   | (1 << (RANG_PO_ZOP - 128))                               /*137*/\
   | (1 << (RANG_ZOP - 128))                                  /*138*/\
   | (1 << (RANG_PO_UMAX1 - 128))                             /*152*/\
   | (1 << (RANG_UMAX1 - 128))                                /*153*/\
   | (1 << (RANG_PO_UMAX2 - 128))                             /*155*/\
   | (1 << (RANG_UMAX2 - 128))                                /*156*/\
   | (1 << (RANG_OUTPUT_LED_DF_REG_OTKL_AVR - 128))             /*159*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR - 128))\
   | (1 << (RANG_OUTPUT_LED_DF_REG_PUSK_AVR - 128))\
)

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_5        0
#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_6        0
#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_7        0
/*****************************************/

/*****************************************/
//Макска моніторингу максимального фазного струму для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_PHASE_SIGNALES_0        0

#define MASKA_MONITOTYNG_PHASE_SIGNALES_1 (unsigned int)(             \
     (1 << (RANG_PO_MTZ1 - 32))                               /*36*/  \
   | (1 << (RANG_PO_MTZN1_VPERED - 32))                       /*37*/  \
   | (1 << (RANG_PO_MTZN1_NAZAD - 32))                        /*38*/  \
   | (1 << (RANG_PO_MTZPN1 - 32))                             /*40*/  \
   | (1 << (RANG_MTZ1 - 32))                                  /*41*/  \
   | (1 << (RANG_PO_MTZ2 - 32))                               /*44*/  \
   | (1 << (RANG_PO_MTZN2_VPERED - 32))                       /*45*/  \
   | (1 << (RANG_PO_MTZN2_NAZAD - 32))                        /*46*/  \
   | (1 << (RANG_PO_MTZPN2 - 32))                             /*48*/  \
   | (1 << (RANG_MTZ2 - 32))                                  /*49*/  \
   | (1 << (RANG_PO_MTZ3 - 32))                               /*52*/  \
   | (1 << (RANG_PO_MTZN3_VPERED - 32))                       /*53*/  \
   | (1 << (RANG_PO_MTZN3_NAZAD - 32))                        /*54*/  \
   | (1 << (RANG_PO_MTZPN3 - 32))                             /*56*/  \
   | (1 << (RANG_MTZ3 - 32))                                  /*58*/  \
   | (1 << (RANG_PO_MTZ4 - 32))                               /*60*/  \
   | (1 << (RANG_PO_MTZN4_VPERED - 32))                       /*61*/  \
   | (1 << (RANG_PO_MTZN4_NAZAD - 32))                        /*62*/  \
)

#define MASKA_MONITOTYNG_PHASE_SIGNALES_2 (unsigned int)(            \
     (1 << (RANG_PO_MTZPN4 - 64))                             /*64*/ \
   | (1 << (RANG_MTZ4 - 64))                                  /*65*/ \
)

#define MASKA_MONITOTYNG_PHASE_SIGNALES_3        0
#define MASKA_MONITOTYNG_PHASE_SIGNALES_4        0
#define MASKA_MONITOTYNG_PHASE_SIGNALES_5        0
#define MASKA_MONITOTYNG_PHASE_SIGNALES_6        0
#define MASKA_MONITOTYNG_PHASE_SIGNALES_7        0
/*****************************************/

/*****************************************/
//Макска моніторингу Umin для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_UMIN_SIGNALES_0        0
#define MASKA_MONITOTYNG_UMIN_SIGNALES_1        0
#define MASKA_MONITOTYNG_UMIN_SIGNALES_2        0
#define MASKA_MONITOTYNG_UMIN_SIGNALES_3        0

#define MASKA_MONITOTYNG_UMIN_SIGNALES_4 (unsigned int)(              \
     (1 << (RANG_PO_UMIN1 - 128))                             /*143*/ \
   | (1 << (RANG_UMIN1 - 128))                                /*146*/ \
   | (1 << (RANG_PO_UMIN2 - 128))                             /*147*/ \
   | (1 << (RANG_UMIN2 - 128))                                /*150*/ \
)

#define MASKA_MONITOTYNG_UMIN_SIGNALES_5        0
#define MASKA_MONITOTYNG_UMIN_SIGNALES_6        0
#define MASKA_MONITOTYNG_UMIN_SIGNALES_7        0
/*****************************************/

/*****************************************/
//Макска моніторингу Umax для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_UMAX_SIGNALES_0        0
#define MASKA_MONITOTYNG_UMAX_SIGNALES_1        0
#define MASKA_MONITOTYNG_UMAX_SIGNALES_2        0
#define MASKA_MONITOTYNG_UMAX_SIGNALES_3        0

#define MASKA_MONITOTYNG_UMAX_SIGNALES_4 (unsigned int)(              \
     (1 << (RANG_PO_UMAX1 - 128))                             /*152*/ \
   | (1 << (RANG_UMAX1 - 128))                                /*153*/ \
   | (1 << (RANG_PO_UMAX2 - 128))                             /*155*/ \
   | (1 << (RANG_UMAX2 - 128))                                /*156*/ \
)

#define MASKA_MONITOTYNG_UMAX_SIGNALES_5        0
#define MASKA_MONITOTYNG_UMAX_SIGNALES_6        0
#define MASKA_MONITOTYNG_UMAX_SIGNALES_7        0
/*****************************************/

/*****************************************/
//Макска моніторингу максимального струму зворотньої послідовності для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_ZOP_SIGNALES_0                  0
#define MASKA_MONITOTYNG_ZOP_SIGNALES_1                  0
#define MASKA_MONITOTYNG_ZOP_SIGNALES_2                  0
#define MASKA_MONITOTYNG_ZOP_SIGNALES_3                  0

#define MASKA_MONITOTYNG_ZOP_SIGNALES_4 (unsigned int)(                \
     (1 << (RANG_PO_ZOP - 128))                               /*137*/  \
   | (1 << (RANG_ZOP - 128))                                  /*138*/  \
)

#define MASKA_MONITOTYNG_ZOP_SIGNALES_5                  0
#define MASKA_MONITOTYNG_ZOP_SIGNALES_6                  0
#define MASKA_MONITOTYNG_ZOP_SIGNALES_7                  0
/*****************************************/

/*****************************************/
//Відключення від захистів
/*****************************************/
typedef enum __vymknennja_vid_zakhystiv__
{
  VYMKNENNJA_VID_MTZ1,
  VYMKNENNJA_VID_MTZ2,
  VYMKNENNJA_VID_MTZ3,
  VYMKNENNJA_VID_MTZ4,

  VYMKNENNJA_VID_ZDZ,

  VYMKNENNJA_VID_UROV1,
  VYMKNENNJA_VID_UROV2,

  VYMKNENNJA_VID_ZOP,

  VYMKNENNJA_VID_UMIN1,
  VYMKNENNJA_VID_UMIN2,

  VYMKNENNJA_VID_UMAX1,
  VYMKNENNJA_VID_UMAX2,

  VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV,
  
  VYMKNENNJA_VID_INSHYKH_SYGNALIV,
    
  VYMKNENNJA_VID_MAX_NUMBER  
  
}__vymknennja_vid_zakhystiv;
/*****************************************/

/*****************************************/
//Максимальна кількість сигналів (функцій), які можуть бути зранжовані на входи/виходи/світлоіндикатори/д.реєстратор/оф
/*****************************************/
#define VAGA_MAX_FUNCTIONS_IN_INPUT             3
#define MAX_FUNCTIONS_IN_INPUT                  (1 << VAGA_MAX_FUNCTIONS_IN_INPUT)
#define VAGA_MAX_FUNCTIONS_IN_OUTPUT            4
#define MAX_FUNCTIONS_IN_OUTPUT                 (1 << VAGA_MAX_FUNCTIONS_IN_OUTPUT)
#define VAGA_MAX_FUNCTIONS_IN_LED               3
#define MAX_FUNCTIONS_IN_LED                    (1 << VAGA_MAX_FUNCTIONS_IN_LED)
#define VAGA_MAX_FUNCTIONS_IN_DF                4
#define MAX_FUNCTIONS_IN_DF                     (1 << VAGA_MAX_FUNCTIONS_IN_DF)
#define MAX_FUNCTIONS_IN_DT                     6
#define MAX_FUNCTIONS_IN_D_AND                  NUMBER_IN_AND
#define MAX_FUNCTIONS_IN_D_OR                   NUMBER_IN_OR
#define MAX_FUNCTIONS_IN_D_XOR                  2
#define MAX_FUNCTIONS_IN_D_NOT                  1
#define VAGA_MAX_FUNCTIONS_IN_DB                3
#define MAX_FUNCTIONS_IN_DB                     (1 << VAGA_MAX_FUNCTIONS_IN_DB)
#define VAGA_MAX_FUNCTIONS_IN_AREG              5
#define MAX_FUNCTIONS_IN_AREG                   (1 << VAGA_MAX_FUNCTIONS_IN_AREG)
#define VAGA_MAX_FUNCTIONS_IN_DREG              5
#define MAX_FUNCTIONS_IN_DREG                   (1 << VAGA_MAX_FUNCTIONS_IN_DREG)
/*****************************************/


/*****************************************/
//Константи для комунікації
/*****************************************/
#define MAX_CHAR_IN_NAME_OF_CELL                              32
/*****************************************/

/*****************************************/
//Константи для фіксації зміни настройок
/*****************************************/
#define CHANGED_ETAP_NONE                                     0
#define CHANGED_ETAP_EXECUTION                                1
#define CHANGED_ETAP_ENDED                                    2
#define CHANGED_ETAP_ENDED_EXTRA_ETAP                         3
/*****************************************/

/*****************************************/
//Константи для ранжування функціональних кнопок
/*****************************************/
enum __odynyci_vymirjuvannja {
INDEX_A = 0,
INDEX_V,
INDEX_SECOND,

NUMBER_ODYNYCI_VYMIRJUVANNJA
};
/*****************************************/

/*****************************************/
//Тип входів логічних елементів
/*****************************************/
#define TYPE_INPUT_0_1        0
#define TYPE_INPUT_1_0        1
/*****************************************/

/*****************************************/
//Індетифікатор типу набору юстуючих коефіцієнтів
/*****************************************/
//#define ADJUSTMENT_3I0_IA_IB_IC                             1
//#define ADJUSTMENT_3I0_IA_IC_3U0                            2
//#define ADJUSTMENT_3I0_IA_IB_IC_UA_UB_UC_UABTN2             3
//#define ADJUSTMENT_3I0_IA_IB_IC_UA_UB_UC_3U0                4
#define ADJUSTMENT_IA_IB_IC_UA1_UB1_UC1_UA2_UB2_UC2             5
#define ADJUSTMENT_ID                                         ADJUSTMENT_IA_IB_IC_UA1_UB1_UC1_UA2_UB2_UC2
/*****************************************/

/*****************************************/
//Версія програмного забезпечення
/*****************************************/
#define VERSIA_PZ                                             10
#define MODYFIKACIA_VERSII_PZ                                 0
#define ZBIRKA_VERSII_PZ                                      0
/*****************************************/

/*****************************************/
//Час компіляції
/*****************************************/

#define YEAR_VER                                              ((__DATE__[9] != ' ') ? (((__DATE__[9] - 0x30) << 4) | (__DATE__[10] - 0x30)) : (__DATE__[10] - 0x30))
#define MONTH_VER                                             str_to_int_DATE_Mmm()
#define DAY_VER                                               ((__DATE__[4] != ' ') ? (((__DATE__[4] - 0x30) << 4) | (__DATE__[5] - 0x30)) : (__DATE__[5] - 0x30))
#define HOUR_VER                                              (((__TIME__[0] - 0x30) << 4) | (__TIME__[1] - 0x30))
#define MINUTE_VER                                            (((__TIME__[3] - 0x30) << 4) | (__TIME__[4] - 0x30))
#define SECOND_VER                                            (((__TIME__[6] - 0x30) << 4) | (__TIME__[7] - 0x30))
/*****************************************/

/*****************************************/
//Версія універсальної карти памяті
/*****************************************/
#define VERSIA_GMM                                             6
#define MODYFIKACIA_VERSII_GMM                                 4
/*****************************************/
#endif
