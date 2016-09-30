#ifndef __CONST_MENU_AVR__
#define __CONST_MENU_AVR__

#define EKRAN_SETPOINT_AVR_GROUP1   (EKRAN_SETPOINT_UMAX_GROUP4 + 1)
#define EKRAN_SETPOINT_AVR_GROUP2   (EKRAN_SETPOINT_AVR_GROUP1  + 1)
#define EKRAN_SETPOINT_AVR_GROUP3   (EKRAN_SETPOINT_AVR_GROUP2  + 1)
#define EKRAN_SETPOINT_AVR_GROUP4   (EKRAN_SETPOINT_AVR_GROUP3  + 1)
#define EKRAN_TIMEOUT_AVR_GROUP1    (EKRAN_TIMEOUT_UMAX_GROUP4  + 1)
#define EKRAN_TIMEOUT_AVR_GROUP2    (EKRAN_TIMEOUT_AVR_GROUP1   + 1)
#define EKRAN_TIMEOUT_AVR_GROUP3    (EKRAN_TIMEOUT_AVR_GROUP2   + 1)
#define EKRAN_TIMEOUT_AVR_GROUP4    (EKRAN_TIMEOUT_AVR_GROUP3   + 1)
#define EKRAN_CONTROL_AVR           (EKRAN_CONTROL_UMAX  + 1)

#define MAX_ROW_FOR_SETPOINT_AVR        8
#define MAX_ROW_FOR_TIMEOUT_AVR         14
#define MAX_ROW_FOR_CONTROL_AVR         4

#define INDEX_ML_STPAVR_TN1_U1_MIN              0
#define INDEX_ML_STPAVR_TN1_U2_LOW_WORK         1
#define INDEX_ML_STPAVR_TN2_U2_MIN              2
#define INDEX_ML_STPAVR_TN2_U1_LOW_WORK         3
#define INDEX_ML_STPAVR_TN1_U1_MAX              4
#define INDEX_ML_STPAVR_TN1_U2_HIGH_WORK        5
#define INDEX_ML_STPAVR_TN2_U2_MAX              6
#define INDEX_ML_STPAVR_TN2_U1_HIGH_WORK        7

#define INDEX_ML_TMOAVR_BLK_K1          0
#define INDEX_ML_TMOAVR_PUSK_K1         1
#define INDEX_ML_TMOAVR_D_DIJI_K1       2
#define INDEX_ML_TMOAVR_VVIMK_REZ_K1    3
#define INDEX_ML_TMOAVR_VVIMK_K1        4
#define INDEX_ML_TMOAVR_VYMK_ROB_K1     5
#define INDEX_ML_TMOAVR_VYMK_K1         6
#define INDEX_ML_TMOAVR_BLK_K2          7
#define INDEX_ML_TMOAVR_PUSK_K2         8
#define INDEX_ML_TMOAVR_D_DIJI_K2       9
#define INDEX_ML_TMOAVR_VVIMK_REZ_K2    10
#define INDEX_ML_TMOAVR_VVIMK_K2        11
#define INDEX_ML_TMOAVR_VYMK_ROB_K2     12
#define INDEX_ML_TMOAVR_VYMK_K2         13

#define COL_SETPOINT_AVR_TN1_U1_MIN_BEGIN     5
#define COL_SETPOINT_AVR_TN1_U1_MIN_COMMA     8
#define COL_SETPOINT_AVR_TN1_U1_MIN_END       9

#define COL_SETPOINT_AVR_TN1_U2_LOW_WORK_BEGIN     5
#define COL_SETPOINT_AVR_TN1_U2_LOW_WORK_COMMA     8
#define COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END       9

#define COL_SETPOINT_AVR_TN2_U2_MIN_BEGIN     5
#define COL_SETPOINT_AVR_TN2_U2_MIN_COMMA     8
#define COL_SETPOINT_AVR_TN2_U2_MIN_END       9

#define COL_SETPOINT_AVR_TN2_U1_LOW_WORK_BEGIN     5
#define COL_SETPOINT_AVR_TN2_U1_LOW_WORK_COMMA     8
#define COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END       9

#define COL_SETPOINT_AVR_TN1_U1_MAX_BEGIN     5
#define COL_SETPOINT_AVR_TN1_U1_MAX_COMMA     8
#define COL_SETPOINT_AVR_TN1_U1_MAX_END       9

#define COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_BEGIN     5
#define COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_COMMA     8
#define COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END       9

#define COL_SETPOINT_AVR_TN2_U2_MAX_BEGIN     5
#define COL_SETPOINT_AVR_TN2_U2_MAX_COMMA     8
#define COL_SETPOINT_AVR_TN2_U2_MAX_END       9

#define COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_BEGIN     5
#define COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_COMMA     8
#define COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END       9

#define COL_TMO_AVR_BLK_K1_BEGIN        4
#define COL_TMO_AVR_BLK_K1_COMMA        6
#define COL_TMO_AVR_BLK_K1_END          8

#define COL_TMO_AVR_PUSK_K1_BEGIN       4
#define COL_TMO_AVR_PUSK_K1_COMMA       6
#define COL_TMO_AVR_PUSK_K1_END         8

#define COL_TMO_AVR_D_DIJI_K1_BEGIN     4
#define COL_TMO_AVR_D_DIJI_K1_COMMA     6
#define COL_TMO_AVR_D_DIJI_K1_END       8

#define COL_TMO_AVR_VVIMK_REZ_K1_BEGIN  4
#define COL_TMO_AVR_VVIMK_REZ_K1_COMMA  6
#define COL_TMO_AVR_VVIMK_REZ_K1_END    8

#define COL_TMO_AVR_VVIMK_K1_BEGIN      4
#define COL_TMO_AVR_VVIMK_K1_COMMA      6
#define COL_TMO_AVR_VVIMK_K1_END        8

#define COL_TMO_AVR_VYMK_ROB_K1_BEGIN   4
#define COL_TMO_AVR_VYMK_ROB_K1_COMMA   6
#define COL_TMO_AVR_VYMK_ROB_K1_END     8

#define COL_TMO_AVR_VYMK_K1_BEGIN       4
#define COL_TMO_AVR_VYMK_K1_COMMA       6
#define COL_TMO_AVR_VYMK_K1_END         8

#define COL_TMO_AVR_BLK_K2_BEGIN        4
#define COL_TMO_AVR_BLK_K2_COMMA        6
#define COL_TMO_AVR_BLK_K2_END          8

#define COL_TMO_AVR_PUSK_K2_BEGIN       4
#define COL_TMO_AVR_PUSK_K2_COMMA       6
#define COL_TMO_AVR_PUSK_K2_END         8

#define COL_TMO_AVR_D_DIJI_K2_BEGIN     4
#define COL_TMO_AVR_D_DIJI_K2_COMMA     6
#define COL_TMO_AVR_D_DIJI_K2_END       8

#define COL_TMO_AVR_VVIMK_REZ_K2_BEGIN  4
#define COL_TMO_AVR_VVIMK_REZ_K2_COMMA  6
#define COL_TMO_AVR_VVIMK_REZ_K2_END    8

#define COL_TMO_AVR_VVIMK_K2_BEGIN      4
#define COL_TMO_AVR_VVIMK_K2_COMMA      6
#define COL_TMO_AVR_VVIMK_K2_END        8

#define COL_TMO_AVR_VYMK_ROB_K2_BEGIN   4
#define COL_TMO_AVR_VYMK_ROB_K2_COMMA   6
#define COL_TMO_AVR_VYMK_ROB_K2_END     8

#define COL_TMO_AVR_VYMK_K2_BEGIN       4
#define COL_TMO_AVR_VYMK_K2_COMMA       6
#define COL_TMO_AVR_VYMK_K2_END         8

#define INDEX_CTR_AVR                           0
#define CTR_AVR                                 (1 << INDEX_CTR_AVR)
#define INDEX_CTR_AVR_UMAX_K1                   1
#define CTR_AVR_UMAX_K1                         (1 << INDEX_CTR_AVR_UMAX_K1)
#define INDEX_CTR_AVR_UMAX_K2                   2
#define CTR_AVR_UMAX_K2                         (1 << INDEX_CTR_AVR_UMAX_K2)
#define INDEX_CTR_AVR_OTKL_BLK                  3
#define CTR_AVR_OTKL_BLK                        (1 << INDEX_CTR_AVR_OTKL_BLK)

#define CTR_AVR_MASKA                           (CTR_AVR                       |\
                                                 CTR_AVR_UMAX_K1               |\
                                                 CTR_AVR_UMAX_K2               |\
                                                 CTR_AVR_OTKL_BLK)

#endif
