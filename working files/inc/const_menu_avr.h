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

#define INDEX_ML_STPAVR_MIN1            0
#define INDEX_ML_STPAVR_MAX1            1
#define INDEX_ML_STPAVR_MIN2            2
#define INDEX_ML_STPAVR_MAX2            3
#define INDEX_ML_STPAVR_MAX3            4
#define INDEX_ML_STPAVR_MAX4            5
#define INDEX_ML_STPAVR_MAX5            6
#define INDEX_ML_STPAVR_MAX6            7

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

#define COL_SETPOINT_AVR_MIN1_BEGIN     5
#define COL_SETPOINT_AVR_MIN1_COMMA     8
#define COL_SETPOINT_AVR_MIN1_END       9

#define COL_SETPOINT_AVR_MAX1_BEGIN     5
#define COL_SETPOINT_AVR_MAX1_COMMA     8
#define COL_SETPOINT_AVR_MAX1_END       9

#define COL_SETPOINT_AVR_MIN2_BEGIN     5
#define COL_SETPOINT_AVR_MIN2_COMMA     8
#define COL_SETPOINT_AVR_MIN2_END       9

#define COL_SETPOINT_AVR_MAX2_BEGIN     5
#define COL_SETPOINT_AVR_MAX2_COMMA     8
#define COL_SETPOINT_AVR_MAX2_END       9

#define COL_SETPOINT_AVR_MAX3_BEGIN     5
#define COL_SETPOINT_AVR_MAX3_COMMA     8
#define COL_SETPOINT_AVR_MAX3_END       9

#define COL_SETPOINT_AVR_MAX4_BEGIN     5
#define COL_SETPOINT_AVR_MAX4_COMMA     8
#define COL_SETPOINT_AVR_MAX4_END       9

#define COL_SETPOINT_AVR_MAX5_BEGIN     5
#define COL_SETPOINT_AVR_MAX5_COMMA     8
#define COL_SETPOINT_AVR_MAX5_END       9

#define COL_SETPOINT_AVR_MAX6_BEGIN     5
#define COL_SETPOINT_AVR_MAX6_COMMA     8
#define COL_SETPOINT_AVR_MAX6_END       9

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
