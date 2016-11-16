#include "header.h"

/*****************************************************/
//ĳ��������� ���
/*****************************************************/
inline void diagnostyca_adc_execution(void)
{
  if (gnd_adc1 >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC1_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC1_TEST_BIT);

  if (gnd_adc2 >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC2_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC2_TEST_BIT);

  if ((vref_adc1 <0x709) || (vref_adc1 > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC1_TEST_BIT);
  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC1_TEST_BIT);

  if ((vref_adc2 <0x709) || (vref_adc2 > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC2_TEST_BIT);
  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC2_TEST_BIT);

  if ((vdd_adc1 <0x8F9) || (vdd_adc1 > 0xC24)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC1_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC1_TEST_BIT);

  if ((vdd_adc2 <0x8F9) || (vdd_adc2 > 0xC24)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC2_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC2_TEST_BIT);
}
/*****************************************************/

/*****************************************************/
//����� ���������� �����
/*****************************************************/
inline unsigned int norma_value(unsigned long long y)
{
  unsigned long long temp=y;
  unsigned int rezultat =0;
  if (temp == 0) return 0;

  while(temp !=0)
  {
    temp = temp>>1;
    rezultat++;
  }
  return rezultat-1;
}
/*****************************************************/

/*****************************************************/
//����� ���������� ����� ���� int
/*****************************************************/
inline unsigned int get_order(int value)
{
  unsigned int i = 0;

  if (value == 0) return 1;  
  if (value < 0) value =-value;

  while ((value >> (++i)) != 0); 

  return i;    
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����������� ������� ����������� ������  � �������������� ���������� �����
/*****************************************************/
unsigned int sqrt_64(unsigned long long y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned long long temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = (unsigned long long)c*(unsigned long long)c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����������� ������� ����������� ������  � �������������� ���������� �����
/*****************************************************/
inline unsigned int sqrt_32(unsigned int y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned int temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = c*c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//���������� ������ ��������� �����������
/*****************************************************/
inline void velychyna_zvorotnoi_poslidovnosti(int ortogonal_local_calc[])
{
  int ortogonal_tmp[2];
  int mul_x1, mul_x2, mul_x3, mul_x4, mul_y1, mul_y2, mul_y3, mul_y4;
  
  mul_x1 = (      ortogonal_local_calc[2*FULL_ORT_Ib    ]>>1 );
  mul_y1 = (0x376*ortogonal_local_calc[2*FULL_ORT_Ib    ]>>10);

  mul_x2 = (0x376*ortogonal_local_calc[2*FULL_ORT_Ib + 1]>>10);
  mul_y2 = (      ortogonal_local_calc[2*FULL_ORT_Ib + 1]>>1 );

  mul_x3 = (      ortogonal_local_calc[2*FULL_ORT_Ic    ]>>1 );
  mul_y3 = (0x376*ortogonal_local_calc[2*FULL_ORT_Ic    ]>>10);

  mul_x4 = (0x376*ortogonal_local_calc[2*FULL_ORT_Ic + 1]>>10);
  mul_y4 = (      ortogonal_local_calc[2*FULL_ORT_Ic + 1]>>1 );

  //�������� �����������
  ortogonal_tmp[0] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia    ] - mul_x1  + mul_x2  - mul_x3 - mul_x4)))>>10;
  ortogonal_tmp[1] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia + 1] - mul_y1  - mul_y2  + mul_y3 - mul_y4)))>>10;
  measurement[IM_I2] = (unsigned int)((unsigned long long)( MNOGNYK_I_DIJUCHE  *(sqrt_32((unsigned int)ortogonal_tmp[0]*ortogonal_tmp[0] + (unsigned int)ortogonal_tmp[1]*ortogonal_tmp[1])) ) >> (VAGA_DILENNJA_I_DIJUCHE   + 4));

  //����� �����������
  ortogonal_tmp[0] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia    ] - mul_x1  - mul_x2  - mul_x3 + mul_x4)))>>10;
  ortogonal_tmp[1] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia + 1] + mul_y1  - mul_y2  - mul_y3 - mul_y4)))>>10;
  measurement[IM_I1] = (unsigned int)((unsigned long long)( MNOGNYK_I_DIJUCHE  *(sqrt_32((unsigned int)ortogonal_tmp[0]*ortogonal_tmp[0] + (unsigned int)ortogonal_tmp[1]*ortogonal_tmp[1])) ) >> (VAGA_DILENNJA_I_DIJUCHE   + 4));
}
/*****************************************************/

/*****************************************************/
//������������ ��� � ����������� �������
/*****************************************************/
inline void directional_mtz(int ortogonal_local_calc[], unsigned int number_group_stp) 
{
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  unsigned int index_FULL_ORT_Uab, index_FULL_ORT_Ubc, index_FULL_ORT_Uca;
  if (TN1_TN2 == 1)
  {
    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
    
    index_FULL_ORT_Uab = FULL_ORT_Uab2;
    index_FULL_ORT_Ubc = FULL_ORT_Ubc2;
    index_FULL_ORT_Uca = FULL_ORT_Uca2;
  }
  else
  {
    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
    
    index_FULL_ORT_Uab = FULL_ORT_Uab1;
    index_FULL_ORT_Ubc = FULL_ORT_Ubc1;
    index_FULL_ORT_Uca = FULL_ORT_Uca1;
  }

  for (unsigned int mtz = 0; mtz < 4; mtz++)
  {
    int a_cos_fi, a_sin_fi;
    switch (mtz)
    {
    case 0:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_1_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_1_angle_sin[number_group_stp];
        
        break;
      }
    case 1:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_2_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_2_angle_sin[number_group_stp];
        
        break;
      }
    case 2:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_3_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_3_angle_sin[number_group_stp];
        
        break;
      }
    case 3:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_4_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_4_angle_sin[number_group_stp];
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(54);
      }
    }
    a_sin_fi = -a_sin_fi; //� ������: "���������, ��� ����", ����� �� � �� ���� ��������

    //������ ��������� �� ������������ ���
    /*
    �� ����������� �������� ��� ���������� ����� ������� ���� ����������� � � ������ (15 �� + ����) = 16-�������� �����
    */
    int amp_cos_U_fi;
    int amp_sin_U_fi;
  
    for (unsigned int i = 0; i < 3; i++)
    {
      unsigned int index_I, index_U;
      unsigned int index_I_ort, index_U_ort;
      switch (i)
      {
      case 0:
        {
          index_I = IM_IA;
          index_U = index_IM_UBC;

          index_I_ort = FULL_ORT_Ia;
          index_U_ort = index_FULL_ORT_Ubc;

          break;
        }
      case 1:
        {
          index_I = IM_IB;
          index_U = index_IM_UCA;

          index_I_ort = FULL_ORT_Ib;
          index_U_ort = index_FULL_ORT_Uca;

          break;
        }
      case 2:
        {
          index_I = IM_IC;
          index_U = index_IM_UAB;

          index_I_ort = FULL_ORT_Ic;
          index_U_ort = index_FULL_ORT_Uab;

          break;
        }
      default:
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(60);
        }
      }

      unsigned int porig_Uxy;
      if (Uxy_bilshe_porogu[i] == 0) porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE*KOEF_POVERNENNJA_SECTOR_BLK/100;
      else porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE;
      unsigned int Uxy_bilshe_porogu_tmp = Uxy_bilshe_porogu[i] = (measurement[index_U] >= porig_Uxy);
      
      unsigned int porig_Ix;
      if (Ix_bilshe_porogu[i] == 0) porig_Ix = PORIG_CHUTLYVOSTI_CURRENT*KOEF_POVERNENNJA_SECTOR_BLK/100;
      else porig_Ix = PORIG_CHUTLYVOSTI_CURRENT;
      unsigned int Ix_bilshe_porogu_tmp = Ix_bilshe_porogu[i]  = (measurement[index_I] >= porig_Ix );

      if (
          (Uxy_bilshe_porogu_tmp != 0) &&
          (Ix_bilshe_porogu_tmp  != 0)
         )
      {
#define SIN_I   ortogonal_local_calc[2*index_I_ort    ]
#define COS_I   ortogonal_local_calc[2*index_I_ort + 1]
#define SIN_U   ortogonal_local_calc[2*index_U_ort    ]
#define COS_U   ortogonal_local_calc[2*index_U_ort + 1]

        amp_cos_U_fi = (COS_U*a_cos_fi - SIN_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //� ����������� �� ��������� ���������� �������������
        amp_sin_U_fi = (SIN_U*a_cos_fi + COS_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //� ����������� �� ��������� ���������� �������������

        //���������� COS � SIN ���� ������ �� (U[i]+fi) � I[i]
        int cos_fi, sin_fi;
        /*
        � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
        �������, �� ����������� �������� ������������� ��� ������ ���� ���� 0x6E51, ��� ����� ������� 
        0x120FC, �� ������� �� �� ���� 0x7C87B7BC  - 31 ���� ����� (���� ���� ���)
        ����� �� ���������� � ��� int.
        */
        cos_fi = amp_cos_U_fi*COS_I + amp_sin_U_fi*SIN_I;
        sin_fi = -(amp_sin_U_fi*COS_I - amp_cos_U_fi*SIN_I);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������

#undef SIN_I
#undef COS_I
#undef SIN_U
#undef COS_U

        /*
        � ���� ��������� ����������� ��������, �� COS � SIN ������ ������ � ������� ���� ���� 31-���� �����
        ������� ���������� ������� ������� ������ 7-������ ������� + ����
        ��� ��� �� �������� ������������ ����� �����������, �� ���������� ������ �������
        COS � SIN ���� = 31 - (7 + 1) = 23
        7 - �� ���������� ��������� ������� ������� �������
        1 - �� ���������� �� �� ���������⳺�� ������� (ab+cd)
        */
        unsigned int order_cos, order_sin, max_order, shift = 0;
        order_cos = get_order(cos_fi);
        order_sin = get_order(sin_fi);
        if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
        if (max_order > 23) shift = max_order - 23;
  
        /*
        ��� ���� � ����� ���� ���������� ��������� - �� ��� � ������ �� ����� ����������� ����,
        ��� ���� � �������� ������� ���������� ���������.
        ��� ���� ��� � ������������?..
        */

        //���������� �������
        int sin_fi1_minus_fi2;
        int *sector;
        if ((sin_fi >= 0) && (cos_fi >= 0))
        {
          //1-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;
          
          if (sector_directional_mtz[mtz][i] != 1)
            sector = sector_1_mtz_tznp;
          else
            sector = sector_2_mtz_tznp;
          
#define COS_SECTOR sector[0]    
#define SIN_SECTOR sector[1]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 <= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR   
        }
        else if ((sin_fi >= 0) && (cos_fi < 0))
        {
          //2-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          if (sector_directional_mtz[mtz][i] != 2)
            sector = sector_1_mtz_tznp;
          else
            sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[2]    
#define SIN_SECTOR sector[3]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 >= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
        }
        else if ((sin_fi < 0) && (cos_fi < 0))
        {
          //3-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          if (sector_directional_mtz[mtz][i] != 2)
            sector = sector_1_mtz_tznp;
          else
            sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[4]    
#define SIN_SECTOR sector[5]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 <= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
        }
        else
        {
          //4-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          if (sector_directional_mtz[mtz][i] != 1)
            sector = sector_1_mtz_tznp;
          else
            sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[6]    
#define SIN_SECTOR sector[7]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 >= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
        }
      }
      else
      {
        sector_directional_mtz[mtz][i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������ ���������
/*****************************************************/
inline void calc_power(int ortogonal_local_calc[]) 
{
  unsigned int index_FULL_ORT_Ua, index_FULL_ORT_Ub, index_FULL_ORT_Uc;
  if (TN1_TN2 == 1)
  {
    index_FULL_ORT_Ua = FULL_ORT_Ua2;
    index_FULL_ORT_Ub = FULL_ORT_Ub2;
    index_FULL_ORT_Uc = FULL_ORT_Uc2;
  }
  else
  {
    index_FULL_ORT_Ua = FULL_ORT_Ua1;
    index_FULL_ORT_Ub = FULL_ORT_Ub1;
    index_FULL_ORT_Uc = FULL_ORT_Uc1;
  }

  /*
  ����������� ����� � ����� ������� ��������� � ���������� ������
  
  .    . .     . .     . .
  S = UaIa* + UbIb* + UcIc*
  */
  
#define IA_SIN          ortogonal_local_calc[2*FULL_ORT_Ia + 1]
#define IA_COS          ortogonal_local_calc[2*FULL_ORT_Ia + 0]
#define UA_SIN          ortogonal_local_calc[2*index_FULL_ORT_Ua + 1]
#define UA_COS          ortogonal_local_calc[2*index_FULL_ORT_Ua + 0]
  
#define IB_SIN          ortogonal_local_calc[2*FULL_ORT_Ib + 1]
#define IB_COS          ortogonal_local_calc[2*FULL_ORT_Ib + 0]
#define UB_SIN          ortogonal_local_calc[2*index_FULL_ORT_Ub + 1]
#define UB_COS          ortogonal_local_calc[2*index_FULL_ORT_Ub + 0]

#define IC_SIN          ortogonal_local_calc[2*FULL_ORT_Ic + 1]
#define IC_COS          ortogonal_local_calc[2*FULL_ORT_Ic + 0]
#define UC_SIN          ortogonal_local_calc[2*index_FULL_ORT_Uc + 1]
#define UC_COS          ortogonal_local_calc[2*index_FULL_ORT_Uc + 0]
  
  long long Re_UaIa, Im_UaIa;
  if (measurement[IM_IA] >= PORIG_I_ENERGY)
  {
    Re_UaIa = UA_COS*IA_COS + UA_SIN*IA_SIN;
    Im_UaIa = UA_SIN*IA_COS - UA_COS*IA_SIN;
  
  }
  else
  {
    Re_UaIa = 0;
    Im_UaIa = 0;
  }
  
  long long Re_UbIb, Im_UbIb;
  if (measurement[IM_IB] >= PORIG_I_ENERGY)
  {
    Re_UbIb = UB_COS*IB_COS + UB_SIN*IB_SIN;
    Im_UbIb = UB_SIN*IB_COS - UB_COS*IB_SIN;
  
  }
  else
  {
    Re_UbIb = 0;
    Im_UbIb = 0;
  }
  
  long long Re_UcIc, Im_UcIc;
  if (measurement[IM_IC] >= PORIG_I_ENERGY)
  {
    Re_UcIc = UC_COS*IC_COS + UC_SIN*IC_SIN;
    Im_UcIc = UC_SIN*IC_COS - UC_COS*IC_SIN;
  
  }
  else
  {
    Re_UcIc = 0;
    Im_UcIc = 0;
  }

#undef IA_SIN
#undef IA_COS
#undef UA_SIN
#undef UA_COS
  
#undef IB_SIN
#undef IB_COS
#undef UB_SIN
#undef UB_COS
  
#undef IC_SIN
#undef IC_COS
#undef UC_SIN
#undef UC_COS

  long long P_adc_x16 = Re_UaIa + Re_UbIb + Re_UcIc; /*  ������� ��������� � ������� ��� � � �������� ���������, �� � ������� � 16 ����*/
  long long Q_adc_x16 = Im_UaIa + Im_UbIb + Im_UcIc; /*��������� ��������� � ������� ��� � � �������� ���������, �� � ������� � 16 ����*/
  
  /*
  ���� ����������� �� ����������� MNOGNYK_I_DIJUCHE_FLOAT � MNOGNYK_U_DIJUCHE_FLOAT,
  � ���� ������� �� 16x16 - �� �������� ����� = ����/�����/����
  
  �� ������ ������� ����� � ���/����/���. 
  
  ��� ����� ������� �� �� 1000
  */
  
  //������� ���������
  double P_float = ((double)P_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int P_tmp = (int)(P_float); // � ������� �� ���

  //��������� ���������
  double Q_float = ((double)Q_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int Q_tmp  = (int)(Q_float); // � ������� �� ����

  unsigned int bank_for_enegry_tmp = bank_for_enegry;  
  int *energy_array;
  
  //������� ���������
  if (P_tmp >= 0) energy_array = P_plus;
  else energy_array = P_minus;
  *(energy_array + bank_for_enegry_tmp) += abs(P_tmp);
  
  //��������� ���������
  if     ((Q_tmp >= 0) && (P_tmp >= 0)) energy_array = Q_1q;
  else if((Q_tmp >= 0) && (P_tmp <  0)) energy_array = Q_2q;
  else if((Q_tmp <  0) && (P_tmp <  0)) energy_array = Q_3q;
  else                                  energy_array = Q_4q;
  *(energy_array + bank_for_enegry_tmp) += abs(Q_tmp);
  
  if (++lichylnyk_1s_po_20ms >= MAIN_FREQUENCY)
  {
    if (lichylnyk_1s_po_20ms > MAIN_FREQUENCY)
    {
      //���������� ����� ����� �� ���� � ����
      total_error_sw_fixed(64);
    }

    //����������� ���� ��� ���������� ����� ����� s ��������� �������� � ������ �����
    bank_for_enegry = bank_for_enegry_tmp = (bank_for_enegry_tmp + 1) & 0x1;
    P_plus[bank_for_enegry_tmp] = 0;
    P_minus[bank_for_enegry_tmp] = 0;
    Q_1q[bank_for_enegry_tmp] = 0;
    Q_2q[bank_for_enegry_tmp] = 0;
    Q_3q[bank_for_enegry_tmp] = 0;
    Q_4q[bank_for_enegry_tmp] = 0;
    
    lichylnyk_1s_po_20ms = 0;
    if (periodical_tasks_CALC_ENERGY_DATA == 0)
    {
      //������� ����������� � ���� ����������
      _SET_BIT(clear_diagnostyka, LOSE_ENERGY_DATA);
    }
    else
    {
      //���������� ����������� � ���� ����������
      _SET_BIT(set_diagnostyka, LOSE_ENERGY_DATA);
    }
    periodical_tasks_CALC_ENERGY_DATA = true;
  }
  
}
/*****************************************************/

/*****************************************************/
//���������� ���������
/*****************************************************/
inline void calc_measurement(unsigned int number_group_stp)
{
  int ortogonal_local[2*NUMBER_ANALOG_CANALES];
  //����������� ������� �������� ���������� ������� � ����������� �������

  //������� ����� �������� � ������� ����
  /*
  ������� ��� ����������� ������������ ��� ����������� ������� �� ����� ������� � ��������� �� 2 (��������� 2/�),
  �� �� �� ������ ������� ��������
  */
  /*
  �������� ���� ���������� ���������, �� ���� ����������� ������� ������� ������� �� �����/������� �� �����,
  � ���� ��������� ������� �� 2/� (������� �� ��������� �������, ��� ���� � ����� ����),
  �� ��������� ���������� ���������� ���� ���� ���������� ���������� �������� �������
  ����� ��� 3I0            - �� 19 �� + ���� = ((11 �� + ����)*16*16)
        ��� ������ ������ - �� 15 �� + ���� = ((11 �� + ����)*16   )
  ������� ��� �� ����� �� ����� ������� �� �������� � �� ���� �������� ����� ���������� � ���� ��������, ��
  ������ ����� ����� �������� �� �������� - ������������ �� ����, �� (15 �� *2) = 30 �� �� 32 �� unsigned int
  � �� ���� ������� ��������� �� 16, ��� �������� ������� ����������
  
  ��� 3I0 ������� ������������ - ���� ����� ���:
  1.  
  ����� 16-������ ��������� ������� ����� � ������������� ��� 3I0,
  ��� ����������� ������� �� ����� 15-���������� ����� + ����.
  ����� 16-������ ��������� ������� ��� � ����������� ���������
    
  2.����������� 64-���� ����������.
    
  �� 17 ��������� 2014 ���� ��������������� ������ �����.
  ��� �������� ������� ��� ���������� ����� ����� �������. ���������, �� ����� ����
  ��'����� � ���, �� ���� ���������� ������� ������� - �� ����� ����� �������� ������
  ����� ������ �� �������� �������� - � ��� �������� ����� ����� �������
    
  ���� ������ ����������� ������ ����� � 17 ��������� 2014 ����  
  
  ��� ���������� ������� � 18 ��������� 2014 ���� � ������� �������� sin/cos ���
  ����� ������ ������������
  */
  
  unsigned int bank_ortogonal_tmp = (bank_ortogonal + 1) & 0x1;
  for(unsigned int i=0; i<(2*NUMBER_ANALOG_CANALES); i++ )
  {
    ortogonal_local[i] = ortogonal[i][bank_ortogonal_tmp];
  }
  bank_ortogonal = bank_ortogonal_tmp;

  unsigned int copy_to_low_tasks = (semaphore_measure_values_low == 0) ? true : false;
  if (copy_to_low_tasks == true) current_delta_phi();
  
  /*******************************************************/
  //����������, �� ���������� ���� ���������
  /*******************************************************/
  if (changed_ustuvannja == CHANGED_ETAP_ENDED_EXTRA_ETAP) /*�� � �����, �� ��� ��� ���������� ��� �������� �� � ������ �������� �������(� ��� ����� ����� ��� �� ���������)*/
  {
    //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
    for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
    {
      phi_ustuvannja_meas[i] = phi_ustuvannja[i];
      phi_ustuvannja_sin_cos_meas[2*i    ] = phi_ustuvannja_sin_cos[2*i    ];
      phi_ustuvannja_sin_cos_meas[2*i + 1] = phi_ustuvannja_sin_cos[2*i + 1];
    }
      
    //�������, �� ���� ������� �������� �������
    changed_ustuvannja = CHANGED_ETAP_NONE;
  }
  /*****************************************************/

  /***
  ��������� ���� � ������� ����������� ��� ����������������� �����
  ***/
  for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    float sin_alpha = ((float)ortogonal_local[2*i    ])/((float)((1 << (VAGA_NUMBER_POINT - 1))));
    float cos_alpha = ((float)ortogonal_local[2*i + 1])/((float)((1 << (VAGA_NUMBER_POINT - 1))));
    
    float sin_beta;
    float cos_beta;
    if (i < I_Ua2)
    {
      sin_beta =  phi_ustuvannja_sin_cos_meas[2*i    ];
      cos_beta =  phi_ustuvannja_sin_cos_meas[2*i + 1];
    }
    else
    {
       unsigned int frequency_locking_bank_tmp = frequency_locking_bank & 0x1;
       sin_beta = phi_ustuvannja_sin_cos_meas[2*i    ]*frequency_locking_cos[frequency_locking_bank_tmp] + phi_ustuvannja_sin_cos_meas[2*i + 1]*frequency_locking_sin[frequency_locking_bank_tmp];
       cos_beta = phi_ustuvannja_sin_cos_meas[2*i + 1]*frequency_locking_cos[frequency_locking_bank_tmp] - phi_ustuvannja_sin_cos_meas[2*i    ]*frequency_locking_sin[frequency_locking_bank_tmp];
    }
    
    unsigned int new_index = index_converter_Ib_p[i];
    int ortogonal_sin = ortogonal_calc[2*new_index    ] = (int)(sin_alpha*cos_beta + cos_alpha*sin_beta);
    int ortogonal_cos = ortogonal_calc[2*new_index + 1] = (int)(cos_alpha*cos_beta - sin_alpha*sin_beta);

    
    //������� ����������� ��� ���������� ����
    if (copy_to_low_tasks == true)
    {
      ortogonal_calc_low[2*new_index    ] = ortogonal_sin;
      ortogonal_calc_low[2*new_index + 1] = ortogonal_cos;
    }
  }
  /***/
  
  /*
  ---------------------------------------------------------------------------------------------------------
  150� (150 000��) - ������������ ������ �����
  ����������� ����������� � ��  - Koef_1 = 84,978173543997808495193432804655 ��� ������ ������ (5439/64 = 84,984375)
  
  ��� ��� 150� ����������� ������� �������� ������������� ���� ����
  150000/Koef_1 = 1765,0303364589078874793160507446
  ���� ���������, �� ������ � ��������� � 16 ���, �� ����������� �������� ������������� ���� ����
  16*150000/Koef_1 = 28240,485383342526199669056811914 < 28241(0x6E51) �� � 15 ���� ����� (+ �������� ����)
  ---------------------------------------------------------------------------------------------------------

  ---------------------------------------------------------------------------------------------------------
  150� (150 000��) - ����������� ����� �������
  ����������� ����������� � ��  - Koef_1 = 64,883134509545420915167731259667 ��� ������ ������ (4152/64 = 64,875)
  
  ��� ��� 150� ����������� ������� �������� ������������� ���� ����
  150000/Koef_1 = 2311,848851536795430557291797995
  ���� ���������, �� ������ � ��������� � 16 ���, �� ����������� �������� ������������� ���� ����
  16*150000/Koef_1 = 36989,581624588726888916668767919 < 36990(0x907E) �� � 16 ���� ����� (+ �������� ����) - ����� ����� �������� 17-����
  
  ���� � ����� ������� ������������� ����� �������, ��, ���� ���������� �� ������� �������� � ��� �������, ��  �����������
  �������� ������������� ���� ����
  2*16*150000/Koef_1 = 73979,163249177453777833337535838 < 73980(0x120FC) �� � 17 ���� ����� (+ �������� ����) - ����� ����� �������� 18-����
  ---------------------------------------------------------------------------------------------------------
  
  ---------------------------------------------------------------------------------------------------------
  2� (2 000�� * 10 = 20 000(������� ��)) - ������������ ����� 3I0
  ����������� ����������� � ����� ��  - Koef_1* = 169,95634708799561699038686560931 ��� 3I0  ��� 3I0 ��� �������� � ������� �������� (170/1 = 170)

  
  ��� ��� 2� ����������� ������� �������� ������������� ���� ����
  20000/Koef_1* = 117,67727621049018824880803941698
  ���� ���������, �� ������ � ��������� � 16 ��� (��������� � 256 ��� �� ��� �������� �� 16), �� ����������� �������� ������������� ���� ����
  16*20000/Koef_1* = 1882,8364193678430119809286306717 < 1883(0x075B) �� � 11 ���� ����� (+ �������� ����)
  ---------------------------------------------------------------------------------------------------------
  */
  
  /***/
  //����������� ���� �������� ����� ������������ ���'�
  /***/
  for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
#if (I_Ia == 0)
    if (i <= I_Ic)
#else
    if ((i >= I_Ia) && (i <= I_Ic))
#endif
    {
      unsigned int delta_index = (i - I_Ia);
      unsigned int index_m = IM_IA + delta_index;
      unsigned int index_ort = FULL_ORT_Ia + delta_index;
      
      measurement[index_m] = ( MNOGNYK_I_DIJUCHE*(sqrt_32((unsigned int)(ortogonal_calc[2*index_ort]*ortogonal_calc[2*index_ort]) + (unsigned int)(ortogonal_calc[2*index_ort+1]*ortogonal_calc[2*index_ort+1]))) ) >> (VAGA_DILENNJA_I_DIJUCHE + 4);
    }
    else
    {
      unsigned int delta_index = (i - I_Ua1);
      unsigned int index_m = IM_UA1 + delta_index;
      unsigned int index_ort = FULL_ORT_Ua1 + delta_index;
      
      measurement[index_m] = ( MNOGNYK_U_DIJUCHE*(sqrt_32((unsigned int)(ortogonal_calc[2*index_ort]*ortogonal_calc[2*index_ort]) + (unsigned int)(ortogonal_calc[2*index_ort+1]*ortogonal_calc[2*index_ort+1]))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
    }
    
  }
  /***/

  int _x, _y;
  //Ubc1
  _x = ortogonal_calc[2*FULL_ORT_Ubc1 + 0] = ortogonal_calc[2*FULL_ORT_Ub1    ] - ortogonal_calc[2*FULL_ORT_Uc1    ];
  _y = ortogonal_calc[2*FULL_ORT_Ubc1 + 1] = ortogonal_calc[2*FULL_ORT_Ub1 + 1] - ortogonal_calc[2*FULL_ORT_Uc1 + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Ubc1 + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Ubc1 + 1] = _y;
  }
  measurement[IM_UBC1] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
  
  //Uca1
  _x = ortogonal_calc[2*FULL_ORT_Uca1 + 0] = ortogonal_calc[2*FULL_ORT_Uc1    ] - ortogonal_calc[2*FULL_ORT_Ua1    ];
  _y = ortogonal_calc[2*FULL_ORT_Uca1 + 1] = ortogonal_calc[2*FULL_ORT_Uc1 + 1] - ortogonal_calc[2*FULL_ORT_Ua1 + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Uca1 + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Uca1 + 1] = _y;
  }
  measurement[IM_UCA1] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);

  //Uab1
  _x = ortogonal_calc[2*FULL_ORT_Uab1 + 0] = ortogonal_calc[2*FULL_ORT_Ua1    ] - ortogonal_calc[2*FULL_ORT_Ub1    ];
  _y = ortogonal_calc[2*FULL_ORT_Uab1 + 1] = ortogonal_calc[2*FULL_ORT_Ua1 + 1] - ortogonal_calc[2*FULL_ORT_Ub1 + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Uab1 + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Uab1 + 1] = _y;
  }
  measurement[IM_UAB1] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);

  //Ubc2
  _x = ortogonal_calc[2*FULL_ORT_Ubc2 + 0] = ortogonal_calc[2*FULL_ORT_Ub2    ] - ortogonal_calc[2*FULL_ORT_Uc2    ];
  _y = ortogonal_calc[2*FULL_ORT_Ubc2 + 1] = ortogonal_calc[2*FULL_ORT_Ub2 + 1] - ortogonal_calc[2*FULL_ORT_Uc2 + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Ubc2 + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Ubc2 + 1] = _y;
  }
  measurement[IM_UBC2] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
  
  //Uca2
  _x = ortogonal_calc[2*FULL_ORT_Uca2 + 0] = ortogonal_calc[2*FULL_ORT_Uc2    ] - ortogonal_calc[2*FULL_ORT_Ua2    ];
  _y = ortogonal_calc[2*FULL_ORT_Uca2 + 1] = ortogonal_calc[2*FULL_ORT_Uc2 + 1] - ortogonal_calc[2*FULL_ORT_Ua2 + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Uca2 + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Uca2 + 1] = _y;
  }
  measurement[IM_UCA2] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);

  //Uab2
  _x = ortogonal_calc[2*FULL_ORT_Uab2 + 0] = ortogonal_calc[2*FULL_ORT_Ua2    ] - ortogonal_calc[2*FULL_ORT_Ub2    ];
  _y = ortogonal_calc[2*FULL_ORT_Uab2 + 1] = ortogonal_calc[2*FULL_ORT_Ua2 + 1] - ortogonal_calc[2*FULL_ORT_Ub2 + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Uab2 + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Uab2 + 1] = _y;
  }
  measurement[IM_UAB2] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
  /***/

  /***/
  //���� ����� ����� ������� (��1 �� ��2)
  /***/
  TN1_TN2 = choose_tn1_tn2(active_functions);
  /***/

  /***/
  //������������ ������� ��� ��� (��� �������)
  /***/
  directional_mtz(ortogonal_calc, number_group_stp);
  /***/

  /***/
  //����������� ����� ��������� �����������
  /***/
  velychyna_zvorotnoi_poslidovnosti(ortogonal_calc);
  /***/
  
  if(++number_inputs_for_fix_one_period >= 20)
  {
    /***/
    //���������� ������� ����������� (��� �� 20��)
    /***/
    calc_power(ortogonal_calc);
    /***/
    
    number_inputs_for_fix_one_period = 0;
  }
}
/*****************************************************/

/*****************************************************/
//������ ������� ���������� �����
/*****************************************************/
inline void input_scan(void)
{
  unsigned int state_inputs_into_pin, temp_state_inputs_into_pin; //���� � ��� ������� �������� ����� ������� �� ����� ��������� (���)
  static unsigned int state_inputs_into_pin_trigger; //� ��� ����� ���������� ��������� ���� ���, � ������� ���� �� ���������� .�� ���������� ��� ���� �� ���� ���������� ������� �������

  /***************************/
  //� ��� ������ ������ ����� ����� ��������� (���), �� ���������� �� �������� �����
  /*
  -----------------------------
  �������� ��������� � �������� ��� ����� state_inputs_into_pin
    "�     ������ " - ������� ������������� ��� (1)
    "���� �������" - ������� ���������     ��� (0)
  -----------------------------
  */
  unsigned int temp_state_inputs_into_pin_1 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_1) & ((1 << NUMBER_INPUTS_1) - 1);
  unsigned int temp_state_inputs_into_pin_2 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_2) & ((1 << NUMBER_INPUTS_2) - 1);
  temp_state_inputs_into_pin = temp_state_inputs_into_pin_1 | (temp_state_inputs_into_pin_2 << NUMBER_INPUTS_1);
  
  //������� �������, ��� �������� ����� �������� ��������� �� ������
  state_inputs_into_pin = 0;
  for (unsigned int index = 0; index < NUMBER_INPUTS; index++)
  {
    if ((temp_state_inputs_into_pin & (1 << index)) != 0) 
    {
      if (index < NUMBER_INPUTS_1)
        state_inputs_into_pin |= 1 << (NUMBER_INPUTS_1 - index - 1);
      else
        state_inputs_into_pin |= 1 << index;
    }
  }
  /***************************/
  
  /***************************/
  //������� ������� ������� ���������� �����
  /***************************/
  for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
  {
    unsigned int maska = 1<<i;
    int max_value_timer = current_settings_prt.dopusk_dv[i];

    if (global_timers[INDEX_TIMER_INPUT_START + i] < 0)
    {
      //������� �� ���� ����� ����������� ����� ����������� ����� ���, ���� �������� ������� � ��'�����
      //�� ������ �� ������ �� ��������� � ��������� ������
      
      //���������� �� ��������� ���� ����� ������� ������������ �����
      if ((state_inputs_into_pin & maska) != (state_inputs & maska))
      {
        //���� ���� ����� �������, �� �������� 䳿 �� ��� �����

        //1-��: �����'������� ������� ���� �����
        state_inputs_into_pin_trigger &= ~maska;
        state_inputs_into_pin_trigger |= (state_inputs_into_pin & maska);

        //2-��: ��������� ������ ������� ����������� �����
        global_timers[INDEX_TIMER_INPUT_START + i] = 0;
      }
    }
    else
    {
      //���� ������ ��������� �������� 䳿 � ��������
      if (global_timers[INDEX_TIMER_INPUT_START + i] < max_value_timer)
      {
        //���� ������ �� �� ����� �� ����� ���������, �� ������ �������� ���� ��������
        global_timers[INDEX_TIMER_INPUT_START + i] += DELTA_TIME_FOR_TIMERS;
        
        //� �������, ���� ��� ������� �� ���� �������� ������
        //� �� ���������� �� �� ������� ������� "� ������"->"���� �������"
        //�� ����� ������� �� ��� ���������� ������� ������� ������, �� ������ �� ���� � - 
        //� �� ������, �� ����� �������� n�����, �� �������� "� ������"->"���� �������" �� ������ ���������� ������� �� ����������� 
        if ((current_settings_prt.type_of_input_signal & maska) != 0)
        {
           if ((state_inputs_into_pin_trigger & maska) == 0)
           {
             if ((state_inputs_into_pin & maska) != 0)
               global_timers[INDEX_TIMER_INPUT_START + i] = -1;
           }
        }
      }
    }
    
    //���� �������� ������� ������� ����������� � ����� ������������� �������, �� ����������, �� �������� ������� ����� �����
    if (global_timers[INDEX_TIMER_INPUT_START + i] >= max_value_timer)
    {
      //����������, �� ���� ��� ������� � �������� �� ������, ���� ��� �� ������ ������� ������� ������� ����������� �����
      unsigned int state_1, state_2;
        
      state_1 = state_inputs_into_pin_trigger & maska;
      state_2 = state_inputs_into_pin  & maska;
        
      if (state_1 == state_2)
      {
        //���� ��� ����� ����������, �� �� �������, �� �������� ��� ����� ����������� ����� � ������� ����� ���� �����
        //��� ����� ��������� �� ��� �������    ����� 1 - �� �������� ����, � 0 - �� �������� ����
        //                        ��� ���������� ����� 0 - �� �������� ����, � 1 - �� �������� ����
          state_inputs &=  ~maska;
          state_inputs |=   state_2;
      }
        
      //� ����-����� ������, �� ������� ���� �����, �� �, � ������� ������ ������� ���������� �� ����, �� ������������� � �������� ��'���� ��������
      global_timers[INDEX_TIMER_INPUT_START + i] = -1;
    }
  }
  /***************************/
  
  /***************************/
  //���������, ���� ������ � ����� ��������
  /***************************/
  active_inputs = (state_inputs ^ current_settings_prt.type_of_input);
  /***************************/
  
}
/*****************************************************/

/*****************************************************/
//������� ������� �������
/*****************************************************/
inline void clocking_global_timers(void)
{
  //����������� �������� �����
  input_scan();
  
  //����������� �� ����� ������� �����
  for (unsigned int i = (INDEX_TIMER_INPUT_START + NUMBER_INPUTS); i < MAX_NUMBER_GLOBAL_TIMERS; i++)
  {
    if (global_timers[i] >= 0)
    {
      //������ ������ ����, �� ������ ����� ��������� � ��� ����, �� �������� ������� �� ��'����

      //���������� �� ����� ���������� �������� �������, ���� �� �� �� �������� ����� ���������
      if (global_timers[i] <= (0x7fffffff - DELTA_TIME_FOR_TIMERS)) global_timers[i] += DELTA_TIME_FOR_TIMERS;
    }
  }
  
  if (++timer_prt_signal_output_mode_2 >= PERIOD_SIGNAL_OUTPUT_MODE_2)
  {
    timer_prt_signal_output_mode_2 = 0;
    output_timer_prt_signal_output_mode_2 ^= true;
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������� ������� - �� ����������� ���� ������������� ����� ��� �������
/*****************************************************/
inline void df_handler(volatile unsigned int *p_active_functions, unsigned int *p_changed_state_with_start_new_timeout)
{
  /*
  ������� ��������� ������� � source_activation_df
  ������� ����� ��� �������� ������� � maska_active_df
  */
  unsigned int source_activation_df = 0;
  unsigned int state_df = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    unsigned int number_byte_in, number_bit_in, number_byte_out, number_bit_out;
    switch (i)
    {
    case 0:
      {
        number_byte_in = RANG_DF1_IN >> 5;
        number_bit_in = RANG_DF1_IN & 0x1f;

        number_byte_out = RANG_DF1_OUT >> 5;
        number_bit_out = RANG_DF1_OUT & 0x1f;
        
        break;
      }
    case 1:
      {
        number_byte_in = RANG_DF2_IN >> 5;
        number_bit_in = RANG_DF2_IN & 0x1f;

        number_byte_out = RANG_DF2_OUT >> 5;
        number_bit_out = RANG_DF2_OUT & 0x1f;
        
        break;
      }
    case 2:
      {
        number_byte_in = RANG_DF3_IN >> 5;
        number_bit_in = RANG_DF3_IN & 0x1f;

        number_byte_out = RANG_DF3_OUT >> 5;
        number_bit_out = RANG_DF3_OUT & 0x1f;
        
        break;
      }
    case 3:
      {
        number_byte_in = RANG_DF4_IN >> 5;
        number_bit_in = RANG_DF4_IN & 0x1f;

        number_byte_out = RANG_DF4_OUT >> 5;
        number_bit_out = RANG_DF4_OUT & 0x1f;
        
        break;
      }
    case 4:
      {
        number_byte_in = RANG_DF5_IN >> 5;
        number_bit_in = RANG_DF5_IN & 0x1f;

        number_byte_out = RANG_DF5_OUT >> 5;
        number_bit_out = RANG_DF5_OUT & 0x1f;
        
        break;
      }
    case 5:
      {
        number_byte_in = RANG_DF6_IN >> 5;
        number_bit_in = RANG_DF6_IN & 0x1f;

        number_byte_out = RANG_DF6_OUT >> 5;
        number_bit_out = RANG_DF6_OUT & 0x1f;
        
        break;
      }
    case 6:
      {
        number_byte_in = RANG_DF7_IN >> 5;
        number_bit_in = RANG_DF7_IN & 0x1f;

        number_byte_out = RANG_DF7_OUT >> 5;
        number_bit_out = RANG_DF7_OUT & 0x1f;
        
        break;
      }
    case 7:
      {
        number_byte_in = RANG_DF8_IN >> 5;
        number_bit_in = RANG_DF8_IN & 0x1f;

        number_byte_out = RANG_DF8_OUT >> 5;
        number_bit_out = RANG_DF8_OUT & 0x1f;
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(43);
        break;
      }
    }

    if (i < NUMBER_DEFINED_FUNCTIONS/*current_settings_prt.number_defined_df*/)
    {
      /***
      ������� ��������� ��-��
      ***/
      source_activation_df |= ((p_active_functions[number_byte_in] & (1 << number_bit_in) ) >> number_bit_in ) << i;
      //���������� ��, �� �� ��� ���������� �������� ������� �� ����� ������-����������� (��� ��������� ����� ������ ��� ���������)
      if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= 0)
      {
        //������ ���������, ��� ��� ���������
        //���� ������� ����� ������� ������, �� ��������� ���������� ����� ������, ��� ���������
        //���� ��� ������������ ������ ������ ����� �� ���� ������ ����� ������� �����������, �� ������� ��������� �������
        source_activation_df |= (1 << i);
      
        //³������, ������� ��������� ����������� � ��������� ���� � ����� ���������� �������
        p_active_functions[number_byte_in] |= (1 << number_bit_in);
      
        //� �������, ���� ������ ����� �� ����� ������������ ��������, �� ������� ������ ����� �������
        if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
          global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = -1;
      }
      /***/

      /***
      ���������� ����� �� ����� ���� �������� ��-��
      ***/
      state_df |= ((p_active_functions[number_byte_out] & ((unsigned int)(1 << number_bit_out))) != 0) << i;
      /***/
    }
    else
    {
      //�������, �� �� ����� ������� � ������
      global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = -1;
      global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
      global_timers[INDEX_TIMER_DF_WORK_START + i] = -1;
      
      etap_execution_df[i] = NONE_DF;
    }
  }
  
  //���������, �� ������������� ���������� ������� ����� ��� �������� �������-�������
  unsigned int source_blk_df = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS/*current_settings_prt.number_defined_df*/; i++)
  {
    if (
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 6] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ������ �������
      if(
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i    ] & p_active_functions[0] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 1] & p_active_functions[1] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 2] & p_active_functions[2] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 3] & p_active_functions[3] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 4] & p_active_functions[4] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 5] & p_active_functions[5] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 6] & p_active_functions[6] ) != 0)
        )
      {
        source_activation_df |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 6] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ��������� �������
      if(
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i    ] & ((unsigned int)(~p_active_functions[0])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 1] & ((unsigned int)(~p_active_functions[1])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 2] & ((unsigned int)(~p_active_functions[2])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 3] & ((unsigned int)(~p_active_functions[3])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 4] & ((unsigned int)(~p_active_functions[4])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 5] & ((unsigned int)(~p_active_functions[5])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 6] & ((unsigned int)(~p_active_functions[6])) ) != 0 )
        )
      {
        source_activation_df |= (1<< i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 6] !=0)
       )
    {
      //�������, ���� ������� ��������� �������� �� ������� ����������
      if(
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i    ] & p_active_functions[0] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 1] & p_active_functions[1] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 2] & p_active_functions[2] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 3] & p_active_functions[3] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 4] & p_active_functions[4] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 5] & p_active_functions[5] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 6] & p_active_functions[6] ) != 0 )
        )
      {
        source_blk_df |= (1<< i);
      }
    }
    
    //��������� � ������ ������� ���� ������ ����������� �������
    switch (etap_execution_df[i])
    {
    case NONE_DF:
      {
        if ((source_activation_df & (1<<i)) != 0)
        {
           if (current_settings_prt.timeout_pause_df[i] > 0)
           {
             //�������, ���� � ����� ���������� ��, ����� ��������� ������ �����
             //��������� ������������� ������� �����
             global_timers[INDEX_TIMER_DF_PAUSE_START + i] = 0;
             //������� ���� ��������� ������ ����� �� ���������� ���������� ���� �����
             etap_execution_df[i] = START_TIMER_PAUSE_DF;
           }
           else
           {
             //�������, ���� ������ ����� ����� ����, ����� ����� ����� ������������ �� � ��������� ������ ������

             //������������ ���� ���� �� � "��������"
             state_df |= (1 << i);
             //��������� ������������� ������� ������
             global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
             //���������� �� ������������� ������� ������ - �������� ����� ���� �� ����������� ���������� (���� ���� ����� ����������)
             etap_execution_df[i] = EXECUTION_DF;
           }
           
           //Գ������ ��� ���� ����� � �������� ��������������� ���� ��������
           *p_changed_state_with_start_new_timeout |= (1 << i);
        }
        break;
      }
    case START_TIMER_PAUSE_DF:
      {
        //����� ��� ���� ���� ������� �����
        //����������, �� �� �� ��������� � ���� ��������� ����� ��� �������
        if ((source_activation_df & (1<< i)) != 0)
        {
          //����������, �� ����������� ������ ������� �����
          if (global_timers[INDEX_TIMER_DF_PAUSE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
          {
            if ((*p_changed_state_with_start_new_timeout & (1 << i)) == 0)
            {
              //���������� ��� ������ ������� �����
              global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
              //������������ ���� ���� �� � "��������"
              state_df |= (1 << i);
              //��������� ������������� ������� ������
              global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
              //���������� �� ������������� ������� ������ - �������� ����� ���� �� ����������� ���������� (���� ���� ����� ����������)
              etap_execution_df[i] = EXECUTION_DF;
           
              //Գ������ ��� ���� ����� � �������� ��������������� ���� ��������
              *p_changed_state_with_start_new_timeout |= (1 << i);
            }
          }
        }
        else
        {
          //��������� ����� �� ���������� ������ ������� �����, ���� ������� ��� ������ �� ���� ������������ �������
          global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
          etap_execution_df[i] = NONE_DF;
           
          //³���� �������� ��� ���� ����� � �������� ��������������� ���� ��������
          *p_changed_state_with_start_new_timeout &= (unsigned int)(1 << i);
        }
        break;
      }
    case EXECUTION_DF:
      {
        //�������� ������ ���� �� �������� �� ���� ��
        if ((current_settings_prt.type_df & (1<<i)) != 0)
        {
          //���� �� ��������
          //����� ������ ����� �������� �� ������ ������ �� ����������� ���� ����������� �������
          if ((source_activation_df & (1<< i)) != 0)
          {
            //������� �� � �������, � ���� ������ ������ �������� � ��������� �������
            global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
          }
        }

        //����������, �� ����������� ������ ������� ������
        /*
        ������ ����������� ��������� �� � ������� ���� �� �������� � ������� � ��������
        �������� �� ��� ������� ��� � ���� ��������� ���������, ��� � ���� �����, ����
        ������� � ��������� � ������� �������, �� ��� ���� ����� ������ ������ � 0, 
        ����� �� ���� ����������� � 0, ��� ���� ������� "������ ������" ��� ���� ������� ���� 0,
        �� �� ������ ������ ������� ������ ������� ���� ����������, �� �� ���������.
        ���� ��� �� � �������� ��������, �� �� �� ���� �������������� ����� ���� ������ ������
        �������� ���� ������� � ������� ���� � �� � ���������� � ������� � ��������
        */
        if (
            (global_timers[INDEX_TIMER_DF_WORK_START + i] >= ((int)current_settings_prt.timeout_work_df[i])) &&
            (
             !( 
               ((current_settings_prt.type_df & (1 << i)) != 0) && 
               ((source_activation_df         & (1 << i)) != 0) 
              )
            )  
           )
        {
          if ((*p_changed_state_with_start_new_timeout & (1 << i)) == 0)
          {
            //���������� ��� ������ ������� ������
            global_timers[INDEX_TIMER_DF_WORK_START + i] = -1;
            //���������� �� � �������� ����
            state_df &= ~(1 << i);
          
            //����������, �� ��� ����� ������� � ���������� ����������� ������� ��, �� ������� � ��������� ����
            if ((source_activation_df & (1<< i)) == 0)
            {
              //���������� � ����� ��������� ����
              etap_execution_df[i] = NONE_DF;
            }
            else 
            {
              //���� ������� ������� ���� �� �� �������, �� ���������� �� ���������� ���� ����������
              etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
            }
          }
        }
        break;
      }
    case WAITING_DEACTIVATION_SOURCE_DF:
      {
        //� ����� ����� �� ���������� ����, ���� ������� ��������� �� �� ���� �����
        if ((source_activation_df & (1 << i)) == 0)
        {
          //���������� � ����� ��������� ����
          etap_execution_df[i] = NONE_DF;
        }
        break;
      }
    default: break;
    }
  }

  //������������, ��� ������� �� � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ������ ��-��, ���� �� ���� ��-��
  ������ ���� �������� ���������, ��� �������� ��������� ���� ���� �������� �������� ��, � �� ��,
  �� ����� ��������������. � �������� � ������� ����� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ���������/�����������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    //������������, ��� ������� ��
    unsigned int index_df;
    switch (i)
    {
    case 0:
      {
       index_df = RANG_DF1_OUT;
        break;
      }
    case 1:
      {
        index_df = RANG_DF2_OUT;
        break;
      }
    case 2:
      {
        index_df = RANG_DF3_OUT;
        break;
      }
    case 3:
      {
        index_df = RANG_DF4_OUT;
        break;
      }
    case 4:
      {
        index_df = RANG_DF5_OUT;
        break;
      }
    case 5:
      {
        index_df = RANG_DF6_OUT;
        break;
      }
    case 6:
      {
        index_df = RANG_DF7_OUT;
        break;
      }
    case 7:
      {
        index_df = RANG_DF8_OUT;
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(44);
        break;
      }
    }
      
    if ((state_df & (1 << i)) != 0 )
    {
      /*
      �� ������� ����� � ��������
      ��� ����� ���, �� ��������� �������� ���� ���� ������� �� ����� ������ ���� - 
      ����������, �� �� ��� ���������� �� 
      */     
      if ((source_blk_df & (1<< i)) == 0 ) _SET_BIT(p_active_functions, index_df);
      else _CLEAR_BIT(p_active_functions, index_df);
    }
    else
    {
      _CLEAR_BIT(p_active_functions, index_df);
    }
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������� ������ - �� ����������� ���� ������������� �������������� �������
/*****************************************************/
inline void dt_handler(volatile unsigned int *p_active_functions)
{
  /*
  ��������� ���� ������������ ������ ������� � state_defined_triggers
  ������� ������������ ������� � source_set_dt
  ������� �������� ������� � source_reset_dt
  */
  unsigned int state_defined_triggers = 0, source_set_dt = 0, source_reset_dt = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS/*current_settings_prt.number_defined_dt*/; i++)
  {
    unsigned int number_byte_set, number_bit_set, number_byte_reset, number_bit_reset;
    unsigned int index_dt;
    switch (i)
    {
    case 0:
      {
        number_byte_set = RANG_DT1_SET >> 5;
        number_bit_set = RANG_DT1_SET & 0x1f;

        number_byte_reset = RANG_DT1_RESET >> 5;
        number_bit_reset = RANG_DT1_RESET & 0x1f;
        
        index_dt = RANG_DT1_OUT;
        
        break;
      }
    case 1:
      {
        number_byte_set = RANG_DT2_SET >> 5;
        number_bit_set = RANG_DT2_SET & 0x1f;

        number_byte_reset = RANG_DT2_RESET >> 5;
        number_bit_reset = RANG_DT2_RESET & 0x1f;
        
        index_dt = RANG_DT2_OUT;
        
        break;
      }
    case 2:
      {
        number_byte_set = RANG_DT3_SET >> 5;
        number_bit_set = RANG_DT3_SET & 0x1f;

        number_byte_reset = RANG_DT3_RESET >> 5;
        number_bit_reset = RANG_DT3_RESET & 0x1f;
        
        index_dt = RANG_DT3_OUT;
        
        break;
      }
    case 3:
      {
        number_byte_set = RANG_DT4_SET >> 5;
        number_bit_set = RANG_DT4_SET & 0x1f;

        number_byte_reset = RANG_DT4_RESET >> 5;
        number_bit_reset = RANG_DT4_RESET & 0x1f;
        
        index_dt = RANG_DT4_OUT;
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(55);
        break;
      }
    }

    state_defined_triggers |= ( (p_active_functions[index_dt >> 5] & ( 1 << (index_dt & 0x1f) ) ) >> (index_dt & 0x1f) ) << i;
    /***
    ������� ������������ � �������� ��
    ***/
    source_set_dt   |= ((p_active_functions[number_byte_set  ] & (1 << number_bit_set  ) ) >> number_bit_set   ) << i;
    source_reset_dt |= ((p_active_functions[number_byte_reset] & (1 << number_bit_reset) ) >> number_bit_reset ) << i;
    /***/
  }
  
  //���������, �� ��������������/���������� ���������� ������ ����� ��� �������� �������-�������
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS/*current_settings_prt.number_defined_dt*/; i++)
  {
    if (
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 6] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ������ �������
      if(
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i    ] & p_active_functions[0]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 6] & p_active_functions[6]) != 0)
        )
      {
        source_set_dt |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 6] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ��������� �������
      if(
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i    ] & ((unsigned int)(~p_active_functions[0])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 1] & ((unsigned int)(~p_active_functions[1])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 2] & ((unsigned int)(~p_active_functions[2])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 3] & ((unsigned int)(~p_active_functions[3])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 4] & ((unsigned int)(~p_active_functions[4])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 5] & ((unsigned int)(~p_active_functions[5])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 6] & ((unsigned int)(~p_active_functions[6])) ) != 0 )
        )
      {
        source_set_dt |= (1<< i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 6] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ������ �������
      if(
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i    ] & p_active_functions[0]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 6] & p_active_functions[6]) != 0)
        )
      {
        source_reset_dt |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 6] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ��������� �������
      if(
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i    ] & ((unsigned int)(~p_active_functions[0])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 1] & ((unsigned int)(~p_active_functions[1])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 2] & ((unsigned int)(~p_active_functions[2])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 3] & ((unsigned int)(~p_active_functions[3])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 4] & ((unsigned int)(~p_active_functions[4])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 5] & ((unsigned int)(~p_active_functions[5])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 6] & ((unsigned int)(~p_active_functions[6])) ) != 0 )
        )
      {
        source_reset_dt |= (1<< i);
      }
    }

    //��������� � ������ ������� ����� ������ ������������� ������ (������������ �� ��������)
    if ((source_set_dt   & (1 << i)) != 0) state_defined_triggers |= (1 << i);
    if ((source_reset_dt & (1 << i)) != 0) state_defined_triggers &= (unsigned int)(~(1 << i));
  }

  //������������, ��� ������� �� � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������� ��-��, ���� �� ���� ��-�
  ������ ���� �������� ������������/��������, ��� �������� ������������/�������� ���� ���� �������� �������� ��, � �� ��,
  �� ����� ��������������. � �������� � �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
  {
    //������������, ��� ������� ��
    unsigned int index_dt;
    switch (i)
    {
    case 0:
      {
       index_dt = RANG_DT1_OUT;
        break;
      }
    case 1:
      {
       index_dt = RANG_DT2_OUT;
        break;
      }
    case 2:
      {
       index_dt = RANG_DT3_OUT;
        break;
      }
    case 3:
      {
       index_dt = RANG_DT4_OUT;
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(56);
        break;
      }
    }
      
    if ((state_defined_triggers & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_dt);
    else _CLEAR_BIT(p_active_functions, index_dt);
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������ "�"
/*****************************************************/
inline void d_and_handler(volatile unsigned int *p_active_functions)
{
  unsigned int state_defined_and = 0;

  //��������� ���� ��� ������������ "�" (�� ����������� ���� �� �� � �������� �����)
  for (unsigned int i = 0; i < NUMBER_DEFINED_AND/*current_settings_prt.number_defined_and*/; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 0] & p_active_functions[0]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 0]) && 
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 1] & p_active_functions[1]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 1]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 2] & p_active_functions[2]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 2]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 3] & p_active_functions[3]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 3]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 4] & p_active_functions[4]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 4]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 5] & p_active_functions[5]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 5]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 6] & p_active_functions[6]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 6])
       )
    {
      state_defined_and |= (1 << i);
    }
  }

  //������������, ��� ������� ���������� "�" � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������ �-"�", ���� �� ���� �-"�"
  ������ ���� �������� , ��� �������� ���� ���� �������� �������� �-"�", � �� ��,
  �� ����� ��������������. � �������� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
  {
    //������������, ��� ������� �-"�"
    unsigned int index_d_and = RANG_D_AND1 + i;
      
    if ((state_defined_and & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_and);
    else _CLEAR_BIT(p_active_functions, index_d_and);
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������ "���"
/*****************************************************/
inline void d_or_handler(volatile unsigned int *p_active_functions)
{
  unsigned int state_defined_or = 0;

  //��������� ���� ��� ������������ "���" (�� ����������� ���� �� �� � �������� �����)
  for (unsigned int i = 0; i < NUMBER_DEFINED_OR/*current_settings_prt.number_defined_or*/; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 0] & p_active_functions[0]) != 0) || 
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 6] & p_active_functions[6]) != 0)
       )
    {
      state_defined_or |= (1 << i);
    }
  }

  //������������, ��� ������� ���������� "���" � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������ �-"���", ���� �� ���� �-"���"
  ������ ���� �������� , ��� �������� ���� ���� �������� �������� �-"���", � �� ��,
  �� ����� ��������������. � �������� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
  {
    //������������, ��� ������� �-"���"
    unsigned int index_d_or = RANG_D_OR1 + i;
      
    if ((state_defined_or & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_or);
    else _CLEAR_BIT(p_active_functions, index_d_or);
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������ "����.���"
/*****************************************************/
inline void d_xor_handler(volatile unsigned int *p_active_functions)
{
  unsigned int state_defined_xor = 0;

  //��������� ���� ��� ������������ "����.���" (�� ����������� ���� �� �� � �������� �����)
  for (unsigned int i = 0; i < NUMBER_DEFINED_XOR/*current_settings_prt.number_defined_xor*/; i++)
  {
    unsigned int temp_array[N_BIG];
    temp_array[0] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 0] & p_active_functions[0];
    temp_array[1] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 1] & p_active_functions[1];
    temp_array[2] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 2] & p_active_functions[2];
    temp_array[3] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 3] & p_active_functions[3];
    temp_array[4] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 4] & p_active_functions[4];
    temp_array[5] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 5] & p_active_functions[5];
    temp_array[6] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 6] & p_active_functions[6];
    
    if (
        (temp_array[0] != 0) || 
        (temp_array[1] != 0) ||
        (temp_array[2] != 0) ||
        (temp_array[3] != 0) ||
        (temp_array[4] != 0) ||
        (temp_array[5] != 0) ||
        (temp_array[6] != 0)
       )
    {
      unsigned int signals = 0;
      for (unsigned int j = 0; j < N_BIG; j++)
      {
        for (unsigned int k = 0; k < 32; k++)
        {
          if ((temp_array[j] & (1 << k)) != 0) signals++;
        }
      }
      if (signals == 1) state_defined_xor |= (1 << i);
    }
  }

  //������������, ��� ������� ���������� "����.���" � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������ �-"����.���", ���� �� ���� �-"����.���"
  ������ ���� �������� , ��� �������� ���� ���� �������� �������� �-"����.���", � �� ��,
  �� ����� ��������������. � �������� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
  {
    //������������, ��� ������� �-"����.���"
    unsigned int index_d_xor = RANG_D_XOR1 + i;
      
    if ((state_defined_xor & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_xor);
    else _CLEAR_BIT(p_active_functions, index_d_xor);
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������ "��"
/*****************************************************/
inline void d_not_handler(volatile unsigned int *p_active_functions)
{
  unsigned int state_defined_not = 0;

  //��������� ���� ��� ������������ "��" (�� ����������� ���� �� �� � �������� �����)
  for (unsigned int i = 0; i < NUMBER_DEFINED_NOT/*current_settings_prt.number_defined_not*/; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 0] & p_active_functions[0]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 1] & p_active_functions[1]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 2] & p_active_functions[2]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 3] & p_active_functions[3]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 4] & p_active_functions[4]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 5] & p_active_functions[5]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 6] & p_active_functions[6]) == 0)
       )
    {
      state_defined_not |= (1 << i);
    }
  }

  //������������, ��� ������� ���������� "��" � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������ �-"��", ���� �� ���� �-"��"
  ������ ���� �������� , ��� �������� ���� ���� �������� �������� �-"��", � �� ��,
  �� ����� ��������������. � �������� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
  {
    //������������, ��� ������� �-"��"
    unsigned int index_d_not = RANG_D_NOT1 + i;
      
    if ((state_defined_not & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_not);
    else _CLEAR_BIT(p_active_functions, index_d_not);
  }
}
/*****************************************************/

/*****************************************************/
//������������� ������ ��������  ��� ������� ���2 (����������� �������)
/*
-------------------------------------------------
�(c) = K*T�/( ((I/I�)^alpha) - 1 )
-------------------------------------------------
*/
/*****************************************************/
inline int timeout_dependent_general(unsigned int i, unsigned int number_group_stp)
{
  int timeout_result = 0;
  int type_mtz2_tmp = current_settings_prt.type_mtz2;
  
  if (
      (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_A) &&
      (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_RTV_I)
     )   
  {
    unsigned int Iust = current_settings_prt.setpoint_mtz_2[number_group_stp];
    if (i > Iust)
    {
      register float timeout = (((float)current_settings_prt.timeout_mtz_2[number_group_stp])/1000.0f);
      register float timeout_dependent = 0;
      
      if (
          (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_A) &&
          (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_C)
         )   
      {
        register float K;
        register float alpha;

        switch (type_mtz2_tmp)
        {
          case TYPE_MTZ_DEPENDENT_A:
          {
            K = 0.14f;
            alpha = 0.02f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_B:
          {
            K = 13.5f;
            alpha = 1.0f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_C:
          {
            K = 80.0f;
            alpha = 2.0f;
            break;
          }
        default:
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(42);
          }
        }
    
        register float I_div_Iusy = ((float)i)/((float)Iust);
        register float rising_to_power = powf(I_div_Iusy, alpha);
        if (
            (isnan(rising_to_power) != 0) || 
            (isinf(rising_to_power) != 0) ||
            (rising_to_power <= 1)
          )
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(57);
        }
  
        timeout_dependent = K*timeout/(rising_to_power - 1);
      }
      else if (
               (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_RT_80) &&
               (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_RTV_I)
              )   
      {
        register float I_div_Iusy = ((float)i)/((float)Iust);
        I_div_Iusy = I_div_Iusy - 1.0f;

        register float K;
        register float alpha;

        switch (type_mtz2_tmp)
        {
        case TYPE_MTZ_DEPENDENT_RT_80:
          {
            K = 20.0f;
            alpha = 1.8f;
          
            I_div_Iusy /= 6.0f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_RTV_I:
          {
            K = 30.0f;
            alpha = 3.0f;
            break;
          } 
        default:
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(87);
          }
        }
      
        register float rising_to_power = powf(I_div_Iusy, alpha);
        if (
            (isnan(rising_to_power) != 0) || 
            (isinf(rising_to_power) != 0) ||
            (rising_to_power <= 0)
           )
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(86);
        }
      
        timeout_dependent = 1.0f/(K*rising_to_power)+ timeout;
      }

      int timeout_dependent_int = (int)timeout_dependent;
      if (timeout_dependent_int > (TIMEOUT_MTZ2_MAX/1000)) timeout_dependent = (TIMEOUT_MTZ2_MAX/1000);
      else if (timeout_dependent_int < 0) timeout_dependent = 0;
    
      timeout_result = (int)(timeout_dependent*1000.0f);
    }
    else timeout_result = TIMEOUT_MTZ2_MAX;
  }
  
  return timeout_result;
}
/*****************************************************/

/*****************************************************/
// ���
/*****************************************************/
inline void mtz_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  if (TN1_TN2 == 1)
  {
    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
  }
  else
  {
    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
  }

  unsigned int tmp_value;
  
  unsigned int po_mtz_x;
  unsigned int direction_ABC_tmp;
  unsigned int po_mtzn_x_vpered_setpoint;
  unsigned int po_mtzn_x_nazad_setpoint;
  unsigned int po_block_u_mtzn_x_setpoint;
  unsigned int po_i_ncn_setpoint;
  unsigned int po_u_ncn_setpoint;
  unsigned int po_u_mtzpn_x_setpoint;
  unsigned int po_mtzpn_x_setpoint;
  
  /******������������� ����� ���������� ��� 4-� ��������*******/
  _Bool ctr_mtz_nespr_kil_napr = (current_settings_prt.control_mtz & CTR_MTZ_NESPR_KIL_NAPR) != 0; //������. ����. ���. (�)
  
  //�� I���
  po_i_ncn_setpoint = previous_state_mtz_po_incn ?
            i_nom_const * KOEF_POVERNENNJA_MTZ_I_DOWN / 100 :
            i_nom_const;
  
  previous_state_mtz_po_incn = ((measurement[IM_IA] <= po_i_ncn_setpoint) &&
                                (measurement[IM_IB] <= po_i_ncn_setpoint) &&
                                (measurement[IM_IC] <= po_i_ncn_setpoint));
  
  //�� U���
  po_u_ncn_setpoint = previous_state_mtz_po_uncn ?
            u_linear_nom_const * U_DOWN / 100 :
            u_linear_nom_const;
  
  previous_state_mtz_po_uncn = ((measurement[index_IM_UAB] <= po_u_ncn_setpoint) ||
                                (measurement[index_IM_UBC] <= po_u_ncn_setpoint) ||
                                (measurement[index_IM_UCA] <= po_u_ncn_setpoint));
  
  ctr_mtz_nespr_kil_napr = ctr_mtz_nespr_kil_napr && previous_state_mtz_po_incn && previous_state_mtz_po_uncn; //������������� ����� ���������� (_AND3)
  
  //������������� ����� ����������
  if (ctr_mtz_nespr_kil_napr)
    _SET_BIT(p_active_functions, RANG_NCN_MTZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_NCN_MTZ);
  /******������������� ����� ���������� ��� 4-� ��������*******/
  
  for (int mtz_level = 0; mtz_level < NUMBER_LEVEL_MTZ; mtz_level++) 
  {
    //�
    /*��������� ��� ���*/
    tmp_value = (*type_mtz_arr[mtz_level] == 1)                                  << 0; //������������
    tmp_value |= (*type_mtz_arr[mtz_level] == 2)                                 << 1; //� ������
    tmp_value |= (*type_mtz_arr[mtz_level] == 0)                                 << 2; //�������
    tmp_value |= (
                  (mtz_level == MTZ_LEVEL2)
                  && (*type_mtz_arr[mtz_level] >= TYPE_MTZ_DEPENDENT_A)
                  && (*type_mtz_arr[mtz_level] <= TYPE_MTZ_DEPENDENT_RTV_I) 
                 )                                                               << 3; //��������� (���� mtz_level == 1 (2-� ������� ���))
    
    /******�� ����***********************/
    //������� �� ���� � ������ �����������
    po_mtz_x = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]) != 0) ?
            *(setpoint_mtz[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz[mtz_level] + number_group_stp);
    
    tmp_value |= ((measurement[IM_IA] >= po_mtz_x) ||
          (measurement[IM_IB] >= po_mtz_x) ||
          (measurement[IM_IC] >= po_mtz_x)) << 4; //�� ����
    /******�� ����***********************/
    
    //�
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ]) != 0) << 5; //���� ���.
    //��
    tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_BLOCK_MTZ]) == 0) << 6; //���������� ����
    //�
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_VPERED]) != 0) << 7; //�����: ���. ����
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_NAZAD]) != 0) << 8; //�����: ���. ���
    
    /******������ ����� ������/�����**********/
    //�������� �������������� ��� �,�,�
    direction_ABC_tmp = (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_VPERED) << 0; //�������� �������������� ���� � ������
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_VPERED) << 1; //�������� �������������� ���� B ������
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_VPERED) << 2; //�������� �������������� ���� C ������
    
    _OR3(direction_ABC_tmp, 0, direction_ABC_tmp, 1, direction_ABC_tmp, 2, direction_ABC_tmp, 3);
    
    //������ ����� ������
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 3))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_VPERED_MTZN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_VPERED_MTZN]);
    
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_NAZAD) << 4; //�������� �������������� ���� � �����
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_NAZAD) << 5; //�������� �������������� ���� B �����
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_NAZAD) << 6; //�������� �������������� ���� C �����
    
    _OR3(direction_ABC_tmp, 4, direction_ABC_tmp, 5, direction_ABC_tmp, 6, direction_ABC_tmp, 7);
    
    //������ ����� �����
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 7))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_NAZAD_MTZN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_NAZAD_MTZN]);
    
    //������� �� ����1 ����. � ������ �����������
    po_mtzn_x_vpered_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]) != 0) ?
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp);
    
    direction_ABC_tmp |= (measurement[IM_IA] >= po_mtzn_x_vpered_setpoint) << 8; //���������� � �������� ���� �� ���� � (������)
    direction_ABC_tmp |= (measurement[IM_IB] >= po_mtzn_x_vpered_setpoint) << 9; //���������� � �������� ���� �� ���� B (������)
    direction_ABC_tmp |= (measurement[IM_IC] >= po_mtzn_x_vpered_setpoint) << 10; //���������� � �������� ���� �� ���� C (������)
    
    //������� �� ����1 ����. � ������ �����������
    po_mtzn_x_nazad_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]) != 0) ?
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp);
    
    direction_ABC_tmp |= (measurement[IM_IA] >= po_mtzn_x_nazad_setpoint) << 11; //���������� � �������� ���� �� ���� � (�����)
    direction_ABC_tmp |= (measurement[IM_IB] >= po_mtzn_x_nazad_setpoint) << 12; //���������� � �������� ���� �� ���� B (�����)
    direction_ABC_tmp |= (measurement[IM_IC] >= po_mtzn_x_nazad_setpoint) << 13; //���������� � �������� ���� �� ���� C (�����)
    
    _AND2(direction_ABC_tmp, 8, direction_ABC_tmp, 0, direction_ABC_tmp, 14);
    _AND2(direction_ABC_tmp, 9, direction_ABC_tmp, 1, direction_ABC_tmp, 15);
    _AND2(direction_ABC_tmp, 10, direction_ABC_tmp, 2, direction_ABC_tmp, 16);
    
    _AND2(direction_ABC_tmp, 11, direction_ABC_tmp, 4, direction_ABC_tmp, 17);
    _AND2(direction_ABC_tmp, 12, direction_ABC_tmp, 5, direction_ABC_tmp, 18);
    _AND2(direction_ABC_tmp, 13, direction_ABC_tmp, 6, direction_ABC_tmp, 19);
    
    _OR3(direction_ABC_tmp, 14, direction_ABC_tmp, 15, direction_ABC_tmp, 16, tmp_value, 12);
    _OR3(direction_ABC_tmp, 17, direction_ABC_tmp, 18, direction_ABC_tmp, 19, tmp_value, 13);
    /******������ ����� ������/�����**********/
    
    /******�� U ����. �����***********************/
    //������� �� U ����. ����� � ������ �����������
    po_block_u_mtzn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN) != 0) ?
           PORIG_CHUTLYVOSTI_VOLTAGE :
           PORIG_CHUTLYVOSTI_VOLTAGE * U_DOWN / 100;
    
    tmp_value |= ((measurement[index_IM_UAB] <= po_block_u_mtzn_x_setpoint) ||
                  (measurement[index_IM_UBC] <= po_block_u_mtzn_x_setpoint) ||
                  (measurement[index_IM_UCA] <= po_block_u_mtzn_x_setpoint)) << 14; //�� U ����. �����
    
    //�� U ����. �����
    if (_GET_OUTPUT_STATE(tmp_value, 14))
      _SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
    /******�� U ����. �����***********************/
    
    //������������� ����� ���������� ��� ������� ����
    tmp_value |= (
                   !(_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]) != 0 ||
                     _CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD])  != 0 ||
                     _CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN])     != 0)
                   &&
                   ctr_mtz_nespr_kil_napr
                 ) << 15;
    
    /******�� U ������***********************/
    po_u_mtzpn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_U_MTZPN]) != 0) ?
            *(setpoint_mtz_U[mtz_level] + number_group_stp) * U_DOWN / 100:
            *(setpoint_mtz_U[mtz_level] + number_group_stp) ;
    
    tmp_value |= ((measurement[index_IM_UAB] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[index_IM_UBC] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[index_IM_UCA] <= po_u_mtzpn_x_setpoint)) << 16; //�� U ������
    
    //�� U ������
    if (_GET_OUTPUT_STATE(tmp_value, 16))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_U_MTZPN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_U_MTZPN]);
    /******�� U ������***********************/
    
    /******�� ������***********************/
    po_mtzpn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]) != 0) ?
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100:
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp);
    
    tmp_value |= ((measurement[IM_IA] >= po_mtzpn_x_setpoint)   ||
                  (measurement[IM_IB] >= po_mtzpn_x_setpoint) ||
                  (measurement[IM_IC] >= po_mtzpn_x_setpoint)) << 17; //�� ������
    /******�� ������***********************/
    
    if ((mtz_level == MTZ_LEVEL2) || (mtz_level == MTZ_LEVEL3))
    { 
      //����� ��� 2-� ��� 3-� ��������
      //��
      tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_BLOCK_USK_MTZ]) == 0) << 9; //���������� ��������� ��� 2
      //�
      tmp_value |= ((current_settings_prt.control_mtz & mtz_prysk_const_menu_settings_prt[mtz_level - MTZ_LEVEL2][CTR_MTZ_PRYSKORENNJA]/*CTR_MTZ_2_PRYSKORENA*/) != 0) << 10; //���2 ����������
      //��
      tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_STATE_VV) != 0) << 18; //��������� ��
      //M
      tmp_value |= ((current_settings_prt.control_mtz & mtz_prysk_const_menu_settings_prt[mtz_level - MTZ_LEVEL2][CTR_MTZ_PRYSKORENA]/*CTR_MTZ_2_PRYSKORENNJA*/) != 0) << 11; //��������� ���2 ���.
    }
    
    if (_GET_OUTPUT_STATE(tmp_value, 15)) 
    {
      //���� ������������� ������������� ����� ���������� ��� ������� ����
      _CLEAR_STATE(tmp_value, 16); //������� �� U ������
    }
    
    _OR2_INVERTOR(tmp_value, 14, tmp_value, 15, tmp_value, 14);
    
    if (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]) != 0) 
    {
      _SET_STATE(tmp_value, 19);
    } 
    else 
    {
      if (mtz_level == 1)
      {
        //������ ��� 2-�� ������� ��� ������������ 19-�� ������� ����� �����������
        //������ "���������" (tmp_value 3)
        if (_GET_OUTPUT_STATE(tmp_value, 14)) 
        {
          _OR3(tmp_value, 2, tmp_value, 3, tmp_value, 15, tmp_value, 19);
        }
        else 
        {
          _OR4(tmp_value, 0, tmp_value, 2, tmp_value, 3, tmp_value, 15, tmp_value, 19);
        }
      }
      else 
      {
        if (_GET_OUTPUT_STATE(tmp_value, 14))
        {
          _OR2(tmp_value, 2, tmp_value, 15, tmp_value, 19);
        } 
        else
        {
          _OR3(tmp_value, 0, tmp_value, 2, tmp_value, 15, tmp_value, 19);
        }
      }
    }
    
    _AND2(tmp_value, 5, tmp_value, 6, tmp_value, 20);
    
    //�� ����
    _AND3(tmp_value, 19, tmp_value, 4, tmp_value, 20, tmp_value, 21);
    if (_GET_OUTPUT_STATE(tmp_value, 21))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]);
    
    //�� ����� ������
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 7, tmp_value, 12, tmp_value, 14, tmp_value, 22);
    if (_GET_OUTPUT_STATE(tmp_value, 22))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]);
    
    //�� ����� �����
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 8, tmp_value, 13, tmp_value, 14, tmp_value, 23);
    if (_GET_OUTPUT_STATE(tmp_value, 23)) 
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]);
    
    //�� ������
    _AND4(tmp_value, 1, tmp_value, 20, tmp_value, 16, tmp_value, 17, tmp_value, 24);
    if (_GET_OUTPUT_STATE(tmp_value, 24))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]);
    
    if ((mtz_level != MTZ_LEVEL2) && (mtz_level != MTZ_LEVEL3))
    { 
      //��� ��� ������� ��� 2-� � 3-�
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ], *(timeout_mtz[mtz_level] + number_group_stp), tmp_value, 21, tmp_value, 25);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_N_VPERED], *(timeout_mtz_n_vpered[mtz_level] + number_group_stp), tmp_value, 22, tmp_value, 26);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_N_NAZAD], *(timeout_mtz_n_nazad[mtz_level] + number_group_stp), tmp_value, 23, tmp_value, 27);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_PO_NAPRUZI], *(timeout_mtz_po_napruzi[mtz_level] + number_group_stp), tmp_value, 24, tmp_value, 28);
      _OR4(tmp_value, 25, tmp_value, 26, tmp_value, 27, tmp_value, 28, tmp_value, 31);
    }
    else 
    {
      unsigned int tmp = 0;
      _AND2(tmp_value, 18, tmp_value, 11, tmp, 0);
      _TIMER_IMPULSE(mtz_prysk_tmr_const[mtz_level - MTZ_LEVEL2][INDEX_TIMER_MTZ_VVID_PR]/*INDEX_TIMER_MTZ2_VVID_PR*/, *(timeout_mtz_vvid_prysk[mtz_level - MTZ_LEVEL2] + number_group_stp)/*current_settings_prt.timeout_mtz_2_vvid_pr[number_group_stp]*/, temp_states_for_mtz, (mtz_level - MTZ_LEVEL2), tmp, 0, tmp, 1);
      _OR2(tmp, 1, tmp_value, 10, tmp, 2);
      _AND2(tmp_value, 9, tmp, 2, tmp, 3);
      _INVERTOR(tmp, 3, tmp, 4);
      _INVERTOR(tmp_value, 3, tmp, 23); /*��������� ������� � ��������� ��������*/
      _AND3(tmp, 4, tmp_value, 3, tmp_value, 21, tmp, 5);
      _AND2(tmp, 3, tmp_value, 21, tmp, 6);
      _AND3(tmp, 4, tmp_value, 21, tmp, 23, tmp, 7); /*������������ ������� � ��������� �������*/
      _AND2(tmp, 4, tmp_value, 22, tmp, 8);
      _AND2(tmp, 3, tmp_value, 22, tmp, 9);
      _AND2(tmp, 4, tmp_value, 23, tmp, 10);
      _AND2(tmp, 3, tmp_value, 23, tmp, 11);
      _AND2(tmp, 4, tmp_value, 24, tmp, 12);
      _AND2(tmp, 3, tmp_value, 24, tmp, 13);
      
      unsigned int i_max = measurement[IM_IA];
      if (i_max < measurement[IM_IB]) i_max = measurement[IM_IB];
      if (i_max < measurement[IM_IC]) i_max = measurement[IM_IC];
      _TIMER_T_0_LOCK(INDEX_TIMER_MTZ2_DEPENDENT, timeout_dependent_general(i_max, number_group_stp), tmp, 5, p_global_trigger_state_mtz2, 0);
      _TIMER_T_0(mtz_prysk_tmr_const[mtz_level - MTZ_LEVEL2][INDEX_TIMER_MTZ_PR]/*INDEX_TIMER_MTZ2_PR*/, *(timeout_mtz_prysk[mtz_level - MTZ_LEVEL2] + number_group_stp)/*current_settings_prt.timeout_mtz_2_pr[number_group_stp]*/, tmp, 6, tmp, 15);
      _TIMER_T_0(mtz_tmr_const[mtz_level - MTZ_LEVEL2][INDEX_TIMER_MTZ]/*INDEX_TIMER_MTZ2*/, *(timeout_mtz[mtz_level - MTZ_LEVEL2] + number_group_stp)/*current_settings_prt.timeout_mtz_2[number_group_stp]*/, tmp, 7, tmp, 16);
      _TIMER_T_0(mtz_tmr_const[mtz_level - MTZ_LEVEL2][INDEX_TIMER_MTZ_N_VPERED]/*INDEX_TIMER_MTZ2_N_VPERED*/, *(timeout_mtz_n_vpered[mtz_level - MTZ_LEVEL2] + number_group_stp)/*current_settings_prt.timeout_mtz_2_n_vpered[number_group_stp]*/, tmp, 8, tmp, 17);
      _TIMER_T_0(mtz_prysk_tmr_const[mtz_level - MTZ_LEVEL2][INDEX_TIMER_MTZ_N_VPERED_PR]/*INDEX_TIMER_MTZ2_N_VPERED_PR*/, *(timeout_mtz_n_vpered_prysk[mtz_level - MTZ_LEVEL2] + number_group_stp)/*current_settings_prt.timeout_mtz_2_n_vpered_pr[number_group_stp]*/, tmp, 9, tmp, 18);
      _TIMER_T_0(mtz_tmr_const[mtz_level - MTZ_LEVEL2][INDEX_TIMER_MTZ_N_NAZAD]/*INDEX_TIMER_MTZ2_N_NAZAD*/, *(timeout_mtz_n_nazad[mtz_level - MTZ_LEVEL2] + number_group_stp)/*current_settings_prt.timeout_mtz_2_n_nazad[number_group_stp]*/, tmp, 10, tmp, 19);
      _TIMER_T_0(mtz_prysk_tmr_const[mtz_level - MTZ_LEVEL2][INDEX_TIMER_MTZ_N_NAZAD_PR]/*INDEX_TIMER_MTZ2_N_NAZAD_PR*/, *(timeout_mtz_n_nazad_prysk[mtz_level - MTZ_LEVEL2] + number_group_stp)/*current_settings_prt.timeout_mtz_2_n_nazad_pr[number_group_stp]*/, tmp, 11, tmp, 20);
      _TIMER_T_0(mtz_tmr_const[mtz_level - MTZ_LEVEL2][INDEX_TIMER_MTZ_PO_NAPRUZI]/*INDEX_TIMER_MTZ2_PO_NAPRUZI*/, *(timeout_mtz_po_napruzi[mtz_level - MTZ_LEVEL2] + number_group_stp)/*current_settings_prt.timeout_mtz_2_po_napruzi[number_group_stp]*/, tmp, 12, tmp, 21);
      _TIMER_T_0(mtz_prysk_tmr_const[mtz_level - MTZ_LEVEL2][INDEX_TIMER_MTZ_PO_NAPRUZI_PR]/*INDEX_TIMER_MTZ2_PO_NAPRUZI_PR*/, *(timeout_mtz_po_napruzi_prysk[mtz_level - MTZ_LEVEL2] + number_group_stp)/*current_settings_prt.timeout_mtz_2_po_napruzi_pr[number_group_stp]*/, tmp, 13, tmp, 22);
      
      _OR6(p_global_trigger_state_mtz2, 0, tmp, 15, tmp, 16, tmp, 17, tmp, 18, tmp, 19, tmp_value, 29);
      _OR3(tmp, 20, tmp, 21, tmp, 22, tmp_value, 30);
      _OR2(tmp_value, 29, tmp_value, 30, tmp_value, 31);
    }
    
    //����.����
    if (_GET_OUTPUT_STATE(tmp_value, 31))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_MTZ]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_MTZ]);
  }
}
/*****************************************************/

/*****************************************************/
// ���
/*****************************************************/
inline void zdz_handler(volatile unsigned int *p_active_functions)
{
  unsigned int tmp_value;
  //M
  tmp_value = ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ1) != 0) << 0; //���� �� ���1 : ���/����
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ2) != 0) << 1; //���� �� ���2 : ���/����
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ3) != 0) << 2; //���� �� ���3 : ���/����
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ4) != 0) << 3; //���� �� ���4 : ���/����
  
  for (int mtz_level = 0; mtz_level < NUMBER_LEVEL_MTZ; mtz_level++) {
    //����� �� �� active ������ ��� ������� �������������� �� ���������� ���� mtz_handler()
    tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]) != 0) << (4 + mtz_level); //�� ���x
    tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]) != 0) << (8 + mtz_level); //�� ����� ������
    tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]) != 0) << (12 + mtz_level);  //�� ����� �����
    tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]) != 0) << (16 + mtz_level); //�� ������
  }
  //�
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STATE) != 0) << 20;
  //��
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_ZDZ_VID_DV) != 0) << 21; //���� ��� �� ��
  
  _OR4(tmp_value, 4, tmp_value, 8, tmp_value, 12, tmp_value, 16, tmp_value, 22);
  _OR4(tmp_value, 5, tmp_value, 9, tmp_value, 13, tmp_value, 17, tmp_value, 23);
  _OR4(tmp_value, 6, tmp_value, 10, tmp_value, 14, tmp_value, 18, tmp_value, 24);
  _OR4(tmp_value, 7, tmp_value, 11, tmp_value, 15, tmp_value, 19, tmp_value, 25);
  
  _AND2(tmp_value, 0, tmp_value, 22, tmp_value, 26);
  _AND2(tmp_value, 1, tmp_value, 23, tmp_value, 27);
  _AND2(tmp_value, 2, tmp_value, 24, tmp_value, 28);
  _AND2(tmp_value, 3, tmp_value, 25, tmp_value, 29);
  
  _OR4(tmp_value, 26, tmp_value, 27, tmp_value, 28, tmp_value, 29, tmp_value, 30);
  
  unsigned int tmp_value2 = 0;
  _AND3(tmp_value, 30, tmp_value, 21, tmp_value, 20, tmp_value2, 0);
  _OR4_INVERTOR(tmp_value, 0, tmp_value, 1, tmp_value, 2, tmp_value, 3, tmp_value2, 1);
  _AND3(tmp_value2, 1, tmp_value, 21, tmp_value, 20, tmp_value2, 2);
  
  _OR2(tmp_value2, 0, tmp_value2, 2, tmp_value2, 3);
  
  //����. ���
  if (_GET_OUTPUT_STATE(tmp_value2, 3))
    _SET_BIT(p_active_functions, RANG_ZDZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_ZDZ);
}
/*****************************************************/

/*****************************************************/
// ���(���)
/*****************************************************/
inline void zop_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  /*******************************/
  //������� � �������� ����� ������ ������ ��������� ����������� � ����������������
  /*******************************/
  unsigned int i2_current = measurement[IM_I2], i1_current = measurement[IM_I1];
  /*******************************/
  
  /*******************************/
  //1 ������ ���(���)
  /*******************************/
  if ((current_settings_prt.control_zop & CTR_ZOP_STATE) != 0)
  {
    //1 ������ ���(���) ��������
    unsigned int setpoint; //������� - � ���� ���������� ����������� ��������
    unsigned int setpoint_i1, setpoint_i2;
    unsigned int previous_state_po_zop1;
    
    if (i1_bilshe_porogu == 0) setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2;
    unsigned int i1_bilshe_porogu_tmp = i1_bilshe_porogu = (i1_current >= setpoint_i1);
    
    if (i2_bilshe_porogu == 0) setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2;
    unsigned int i2_bilshe_porogu_tmp = i2_bilshe_porogu = (i2_current >= setpoint_i2);
    
    //���� �� ���(���) �� �� �������, �� ����� ��������� �� ������ ���������� - �������, ��� ��������� �� ������� � ������� ���� �� ��������� ����
    //���� �� ���(���) ��� ����������, �� ����� ��������� �� ������� ���������� - �������� ������� �� ������� ������ �� ����������� ����������
    if(( previous_state_po_zop1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_ZOP) ) == 0 )
    {
      //�������� �� ������ �����������
      setpoint = current_settings_prt.setpoint_zop[number_group_stp];
    }
    else
    {
      //�������� �� ������ ����������
      setpoint = current_settings_prt.setpoint_zop[number_group_stp]*KOEF_POVERNENNJA_GENERAL/100;
    }
    
    //�����������, ��� ������� ������ "�� ���"
    /*
    I2
    -- >= K
    I1
    ������� �������� ������ � ��� � ����������� �� 1000, ,�� 0,010 ������� 10, � 1,000 ������� 1000,
    �� K*1000 = SETPOINT =>
        SETPOINT
    K = --------  =>
         1000
    I2    SETPOINT
    -- >= ---------
    I1     1000
    
    ������ ��������� � ����� ����������� �� ����� � ���� �������������, �� ���� � � ��������� ��������� (��������), � ��� �������� �� ���������
    
    (I2*1000) >= (SETPOINT*I1)
    */
    if (
        (i1_bilshe_porogu_tmp != 0) &&
        (i2_bilshe_porogu_tmp != 0) &&
        ((i2_current*1000) >= (i1_current*setpoint))                            && 
        (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_ZOP) == 0)
       )
    {
      //���� ����� ��������� ��������� ������ ��������� �����������
      if(previous_state_po_zop1 == 0)
      {
        //������������ ������ "�� ���"
        _SET_BIT(p_active_functions, RANG_PO_ZOP);
      
        //��������� ������ ���(���), ���� �� �� �� ���������
        global_timers[INDEX_TIMER_ZOP] = 0;
      }
    }
    else 
    {
      //�� ���� ����� ��������� ��������� ������ ��������� �����������
      if(previous_state_po_zop1 != 0)
      {
        //������� ������ "�� ���"
        _CLEAR_BIT(p_active_functions, RANG_PO_ZOP);
        //�� � ������ ����� �������� ������� "����. ���"
        _CLEAR_BIT(p_active_functions, RANG_ZOP);
        //���� ������ �� �� ��������? �� ������� ����
        if ( global_timers[INDEX_TIMER_ZOP] >=0) global_timers[INDEX_TIMER_ZOP] = -1;
      }
    }
    
    if(global_timers[INDEX_TIMER_ZOP] >= current_settings_prt.timeout_zop[number_group_stp])
    {
      //���� ��������� �������� ���(���) �� ������������ ������ "����. ���"
      _SET_BIT(p_active_functions, RANG_ZOP);

      //������� ������ ���(���)
      global_timers[INDEX_TIMER_ZOP] = -1;
    }
  }
  else
  {
    //����� ������� �� ������� � �������, �� �� 1 ������ ���(���) ����������
    _CLEAR_BIT(p_active_functions, RANG_PO_ZOP);
    _CLEAR_BIT(p_active_functions, RANG_ZOP);
    global_timers[INDEX_TIMER_ZOP] = -1;

  }  
}
/*****************************************************/

/*****************************************************/
// �����1
/*****************************************************/
void umin1_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int index_IM_UA, index_IM_UB, index_IM_UC;
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  if (TN1_TN2 == 1)
  {
    index_IM_UA = IM_UA2;
    index_IM_UB = IM_UB2;
    index_IM_UC = IM_UC2;

    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
  }
  else
  {
    index_IM_UA = IM_UA1;
    index_IM_UB = IM_UB1;
    index_IM_UC = IM_UC1;

    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
  }

  _Bool previous_state_po_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMIN1) > 0;
  _Bool previous_state_po_ublk_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1) > 0;
  _Bool previous_state_po_iblk_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN1) > 0;
  
  unsigned int setpoint1 = previous_state_po_umin1 ?
          current_settings_prt.setpoint_Umin1[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_Umin1[number_group_stp];
  
  _Bool Uab_is_smaller_than_Umin1 = measurement[index_IM_UAB] <= setpoint1;
  _Bool Ubc_is_smaller_than_Umin1 = measurement[index_IM_UBC] <= setpoint1;
  _Bool Uca_is_smaller_than_Umin1 = measurement[index_IM_UCA] <= setpoint1;
  
  _Bool Ua_is_smaller_than_Umin1 = measurement[index_IM_UA] <= setpoint1;
  _Bool Ub_is_smaller_than_Umin1 = measurement[index_IM_UB] <= setpoint1;
  _Bool Uc_is_smaller_than_Umin1 = measurement[index_IM_UC] <= setpoint1;
  
  unsigned int setpoint2 = previous_state_po_ublk_umin1 ?
          KOEF_MIN_UMIN * U_DOWN / 100 : KOEF_MIN_UMIN;
          
  _Bool Ua_or_Ub_or_Uc_is_smaller_than_250mV = (measurement[index_IM_UA] <= setpoint2) || (measurement[index_IM_UB] <= setpoint2) || (measurement[index_IM_UC] <= setpoint2);
  _Bool Uab_or_Ubc_or_Uca_is_smaller_than_250mV = (measurement[index_IM_UAB] <= setpoint2) || (measurement[index_IM_UBC] <= setpoint2) || (measurement[index_IM_UCA] <= setpoint2);
  
  unsigned int setpoint3 = previous_state_po_iblk_umin1 ?
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp] * KOEF_POVERNENNJA_GENERAL / 100 :
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp];
  
  _Bool Ia_or_Ic_is_larger_than_Iust = (measurement[IM_IA] >= setpoint3) ||
                                       (measurement[IM_IB] >= setpoint3) || 
                                       (measurement[IM_IC] >= setpoint3);
  //�
  unsigned int tmp_value = ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) != 0)                    << 0;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN1_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_IBLK) != 0)                                                       << 5;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMIN1) != 0)                                     << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_START_UMIN1) != 0)                                     << 7;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) 
  {
    //������
    _AND4(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_or_Ic_is_larger_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin1
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  } 
  else 
  {
    //��������
    _AND4(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_or_Ic_is_larger_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin1
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //�� I���. Umin1
  if (Ia_or_Ic_is_larger_than_Iust)
    _SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);
  
  //�� Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 15))
    _SET_BIT(p_active_functions, RANG_PO_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMIN1);
  
  _TIMER_T_0(INDEX_TIMER_UMIN1, current_settings_prt.timeout_Umin1[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //����. Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 16))
    _SET_BIT(p_active_functions, RANG_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMIN1);
}
/*****************************************************/

/*****************************************************/
// �����2
/*****************************************************/
void umin2_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int index_IM_UA, index_IM_UB, index_IM_UC;
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  if (TN1_TN2 == 1)
  {
    index_IM_UA = IM_UA2;
    index_IM_UB = IM_UB2;
    index_IM_UC = IM_UC2;

    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
  }
  else
  {
    index_IM_UA = IM_UA1;
    index_IM_UB = IM_UB1;
    index_IM_UC = IM_UC1;

    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
  }

  _Bool previous_state_po_umin2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMIN2) > 0;
  _Bool previous_state_po_ublk_umin2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2) > 0;
  _Bool previous_state_po_iblk_umin2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN2) > 0;
  
  unsigned int setpoint1 = previous_state_po_umin2 ?
          current_settings_prt.setpoint_Umin2[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_Umin2[number_group_stp];
  
  _Bool Uab_is_smaller_than_Umin2 = measurement[index_IM_UAB] <= setpoint1;
  _Bool Ubc_is_smaller_than_Umin2 = measurement[index_IM_UBC] <= setpoint1;
  _Bool Uca_is_smaller_than_Umin2 = measurement[index_IM_UCA] <= setpoint1;
  
  _Bool Ua_is_smaller_than_Umin2 = measurement[index_IM_UA] <= setpoint1;
  _Bool Ub_is_smaller_than_Umin2 = measurement[index_IM_UB] <= setpoint1;
  _Bool Uc_is_smaller_than_Umin2 = measurement[index_IM_UC] <= setpoint1;
  
  unsigned int setpoint2 = previous_state_po_ublk_umin2 ?
          KOEF_MIN_UMIN * U_DOWN / 100 : KOEF_MIN_UMIN;
          
  _Bool Ua_or_Ub_or_Uc_is_smaller_than_250mV = (measurement[index_IM_UA] <= setpoint2) || (measurement[index_IM_UB] <= setpoint2) || (measurement[index_IM_UC] <= setpoint2);
  _Bool Uab_or_Ubc_or_Uca_is_smaller_than_250mV = (measurement[index_IM_UAB] <= setpoint2) || (measurement[index_IM_UBC] <= setpoint2) || (measurement[index_IM_UCA] <= setpoint2);
  
  unsigned int setpoint3 = previous_state_po_iblk_umin2 ?
          current_settings_prt.setpoint_Umin2_Iblk[number_group_stp] * KOEF_POVERNENNJA_GENERAL / 100 :
          current_settings_prt.setpoint_Umin2_Iblk[number_group_stp];
  
  _Bool Ia_or_Ic_is_larger_than_Iust = (measurement[IM_IA] >= setpoint3) ||
                                       (measurement[IM_IB] >= setpoint3) || 
                                       (measurement[IM_IC] >= setpoint3);
  //�
  unsigned int tmp_value = ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) != 0)                    << 0;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN2_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_IBLK) != 0)                                                       << 5;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMIN2) != 0)                                    << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_START_UMIN2) != 0)                                    << 7;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0))
  {
    //������
    _AND4(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_or_Ic_is_larger_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin2
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    
  } 
  else 
  {
    //��������
    _AND4(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_or_Ic_is_larger_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin2
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //�� I���. Umin2
  if (Ia_or_Ic_is_larger_than_Iust)
    _SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_IBLK_UMIN2);
  
  //�� Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 15))
    _SET_BIT(p_active_functions, RANG_PO_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMIN2);
  
  _TIMER_T_0(INDEX_TIMER_UMIN2, current_settings_prt.timeout_Umin2[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //����. Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 16))
    _SET_BIT(p_active_functions, RANG_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMIN2);
}
/*****************************************************/

/*****************************************************/
// ������1
/*****************************************************/
void umax1_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int index_IM_UA, index_IM_UB, index_IM_UC;
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  if (TN1_TN2 == 1)
  {
    index_IM_UA = IM_UA2;
    index_IM_UB = IM_UB2;
    index_IM_UC = IM_UC2;

    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
  }
  else
  {
    index_IM_UA = IM_UA1;
    index_IM_UB = IM_UB1;
    index_IM_UC = IM_UC1;

    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
  }

  _Bool previous_state_po_umax1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMAX1) > 0;
  
  unsigned int setpoint1 = previous_state_po_umax1 ?
          current_settings_prt.setpoint_Umax1[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_Umax1[number_group_stp];
  
  _Bool Uab_is_larger_than_Umax1 = measurement[index_IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_Umax1 = measurement[index_IM_UBC] >= setpoint1;
  _Bool Uca_is_larger_than_Umax1 = measurement[index_IM_UCA] >= setpoint1;
  
  _Bool Ua_is_larger_than_Umax1 = measurement[index_IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_Umax1 = measurement[index_IM_UB] >= setpoint1;
  _Bool Uc_is_larger_than_Umax1 = measurement[index_IM_UC] >= setpoint1;
  
  //�
  unsigned int tmp_value = ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) != 0)                    << 0;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX1_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX1) != 0)                                                            << 3;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMAX1) != 0)                                    << 4;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) 
  {
    _AND4(Ua_is_larger_than_Umax1, 0, Ub_is_larger_than_Umax1, 0, Uc_is_larger_than_Umax1, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Ua_is_larger_than_Umax1, 0, Ub_is_larger_than_Umax1, 0, Uc_is_larger_than_Umax1, 0, tmp_value, 6);
  } 
  else 
  {
    _AND4(Uab_is_larger_than_Umax1, 0, Ubc_is_larger_than_Umax1, 0, Uca_is_larger_than_Umax1, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Uab_is_larger_than_Umax1, 0, Ubc_is_larger_than_Umax1, 0, Uca_is_larger_than_Umax1, 0, tmp_value, 6);
  }
  
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _AND2(tmp_value, 6, tmp_value, 2, tmp_value, 7);
  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 8);
  _INVERTOR(tmp_value, 4, tmp_value, 4);
  _AND3(tmp_value, 8, tmp_value, 4, tmp_value, 3, tmp_value, 9);
  
  //�� Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9))
    _SET_BIT(p_active_functions, RANG_PO_UMAX1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMAX1);
  
  _TIMER_T_0(INDEX_TIMER_UMAX1, current_settings_prt.timeout_Umax1[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //����. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10))
    _SET_BIT(p_active_functions, RANG_UMAX1);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMAX1);
}
/*****************************************************/

/*****************************************************/
// ������2
/*****************************************************/
void umax2_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int index_IM_UA, index_IM_UB, index_IM_UC;
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  if (TN1_TN2 == 1)
  {
    index_IM_UA = IM_UA2;
    index_IM_UB = IM_UB2;
    index_IM_UC = IM_UC2;

    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
  }
  else
  {
    index_IM_UA = IM_UA1;
    index_IM_UB = IM_UB1;
    index_IM_UC = IM_UC1;

    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
  }

  _Bool previous_state_po_umax2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMAX2) > 0;
  
  unsigned int setpoint1 = previous_state_po_umax2 ?
          current_settings_prt.setpoint_Umax2[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_Umax2[number_group_stp];
  
  _Bool Uab_is_larger_than_Umax2 = measurement[index_IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_Umax2 = measurement[index_IM_UBC] >= setpoint1;
  _Bool Uca_is_larger_than_Umax2 = measurement[index_IM_UCA] >= setpoint1;
  
  _Bool Ua_is_larger_than_Umax2 = measurement[index_IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_Umax2 = measurement[index_IM_UB] >= setpoint1;
  _Bool Uc_is_larger_than_Umax2 = measurement[index_IM_UC] >= setpoint1;
  
  //�
  unsigned int tmp_value = ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) != 0)                    << 0;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX2_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX2) != 0)                                                            << 3;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMAX2) != 0)                                    << 4;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) 
  {
    _AND4(Ua_is_larger_than_Umax2, 0, Ub_is_larger_than_Umax2, 0, Uc_is_larger_than_Umax2, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Ua_is_larger_than_Umax2, 0, Ub_is_larger_than_Umax2, 0, Uc_is_larger_than_Umax2, 0, tmp_value, 6);
  } 
  else 
  {
    _AND4(Uab_is_larger_than_Umax2, 0, Ubc_is_larger_than_Umax2, 0, Uca_is_larger_than_Umax2, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Uab_is_larger_than_Umax2, 0, Ubc_is_larger_than_Umax2, 0, Uca_is_larger_than_Umax2, 0, tmp_value, 6);
  }
  
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _AND2(tmp_value, 6, tmp_value, 2, tmp_value, 7);
  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 8);
  _INVERTOR(tmp_value, 4, tmp_value, 4);
  _AND3(tmp_value, 8, tmp_value, 4, tmp_value, 3, tmp_value, 9);
  
  //�� Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9))
    _SET_BIT(p_active_functions, RANG_PO_UMAX2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMAX2);
  
  _TIMER_T_0(INDEX_TIMER_UMAX2, current_settings_prt.timeout_Umax2[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //����. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10))
    _SET_BIT(p_active_functions, RANG_UMAX2);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMAX2);
}
/*****************************************************/

/*****************************************************/
// ���� ��1/��2
/*****************************************************/
uint32_t choose_tn1_tn2(volatile unsigned int *p_active_functions)
{
  uint32_t logic_tn1_tn2_0 = 0;
  static uint32_t static_logic_tn1_tn2_0; 
  
  logic_tn1_tn2_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_K1_AVR) != 0) << 0; /* 1�+ */
  logic_tn1_tn2_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_K2_AVR) != 0) << 1;
  logic_tn1_tn2_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_STATE_VV) != 0) << 2;
  
  _INVERTOR(logic_tn1_tn2_0, 0, logic_tn1_tn2_0, 3);
  _INVERTOR(logic_tn1_tn2_0, 1, logic_tn1_tn2_0, 4);
  _INVERTOR(logic_tn1_tn2_0, 2, logic_tn1_tn2_0, 5);
  
//  _AND2(logic_tn1_tn2_0, 0, logic_tn1_tn2_0, 1, logic_tn1_tn2_0, 6); /*1�- 2�-*/
//  _AND2(logic_tn1_tn2_0, 3, logic_tn1_tn2_0, 5, logic_tn1_tn2_0, 7);
  _AND2(logic_tn1_tn2_0, 0, logic_tn1_tn2_0, 4, logic_tn1_tn2_0, 8); /*1�- 2�+*/
  _AND2(logic_tn1_tn2_0, 5, logic_tn1_tn2_0, 8, logic_tn1_tn2_0, 9);
  
  uint32_t stp_0 = _GET_OUTPUT_STATE(static_logic_tn1_tn2_0, 0) ?  KOEF_MIN_UMIN * U_DOWN / 100 : KOEF_MIN_UMIN;
  uint32_t stp_1 = _GET_OUTPUT_STATE(static_logic_tn1_tn2_0, 1) ?  KOEF_MIN_UMIN * U_DOWN / 100 : KOEF_MIN_UMIN;
          
  if ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) == 0)
  {
    //˳���
    if (
        (measurement[IM_UAB1] >= stp_0) &&
        (measurement[IM_UBC1] >= stp_0) &&
        (measurement[IM_UCA1] >= stp_0)
       )
    {
      static_logic_tn1_tn2_0 |= (1 << 0);
    }
    else
    {
      static_logic_tn1_tn2_0 &= (uint32_t)(~(1 << 0));
    }

    if (
        (measurement[IM_UAB2] >= stp_1) &&
        (measurement[IM_UBC2] >= stp_1) &&
        (measurement[IM_UCA2] >= stp_1)
       )
    {
      static_logic_tn1_tn2_0 |= (1 << 1);
    }
    else
    {
      static_logic_tn1_tn2_0 &= (uint32_t)(~(1 << 1));
    }
  }
  else
  {
    //����
    if (
        (measurement[IM_UA1] >= stp_0) &&
        (measurement[IM_UB1] >= stp_0) &&
        (measurement[IM_UC1] >= stp_0)
       )
    {
      static_logic_tn1_tn2_0 |= (1 << 0);
    }
    else
    {
      static_logic_tn1_tn2_0 &= (uint32_t)(~(1 << 0));
    }

    if (
        (measurement[IM_UA2] >= stp_1) &&
        (measurement[IM_UB2] >= stp_1) &&
        (measurement[IM_UC2] >= stp_1)
       )
    {
      static_logic_tn1_tn2_0 |= (1 << 1);
    }
    else
    {
      static_logic_tn1_tn2_0 &= (uint32_t)(~(1 << 1));
    }
  }

  /*������������ �� ������*/
  //�� I���
  uint32_t stp_tmp = _GET_OUTPUT_STATE(static_logic_tn1_tn2_0, 2) ?  i_nom_const * KOEF_POVERNENNJA_MTZ_I_DOWN / 100 : i_nom_const;
  if(
     (measurement[IM_IA] <= stp_tmp) &&
     (measurement[IM_IB] <= stp_tmp) &&
     (measurement[IM_IC] <= stp_tmp)
    )
  {
    static_logic_tn1_tn2_0 |= (1 << 2);
  }
  else
  {
    static_logic_tn1_tn2_0 &= (uint32_t)(~(1 << 2));
  }
  
  //�� U1���
  stp_tmp = _GET_OUTPUT_STATE(static_logic_tn1_tn2_0, 3) ?  u_linear_nom_const * U_DOWN / 100 : u_linear_nom_const;
  if(
     (measurement[IM_UAB1] <= stp_tmp) ||
     (measurement[IM_UBC1] <= stp_tmp) ||
     (measurement[IM_UCA1] <= stp_tmp)
    )
  {
    static_logic_tn1_tn2_0 |= (1 << 3);
  }
  else
  {
    static_logic_tn1_tn2_0 &= (uint32_t)(~(1 << 3));
  }
  
  //�� U2���
  stp_tmp = _GET_OUTPUT_STATE(static_logic_tn1_tn2_0, 4) ?  u_linear_nom_const * U_DOWN / 100 : u_linear_nom_const;
  if(
     (measurement[IM_UAB2] <= stp_tmp) ||
     (measurement[IM_UBC2] <= stp_tmp) ||
     (measurement[IM_UCA2] <= stp_tmp)
    )
  {
    static_logic_tn1_tn2_0 |= (1 << 4);
  }
  else
  {
    static_logic_tn1_tn2_0 &= (uint32_t)(~(1 << 4));
  }

  _AND2(static_logic_tn1_tn2_0, 2, static_logic_tn1_tn2_0, 3, logic_tn1_tn2_0, 10); /*���1�*/
  _AND2(static_logic_tn1_tn2_0, 2, static_logic_tn1_tn2_0, 4, logic_tn1_tn2_0, 11); /*���2�*/
  /*����������� �� ������*/
  
//  _INVERTOR(logic_tn1_tn2_0, 10, logic_tn1_tn2_0, 12);
  _INVERTOR(logic_tn1_tn2_0, 11, logic_tn1_tn2_0, 13);
  
//  _INVERTOR(static_logic_tn1_tn2_0, 1, logic_tn1_tn2_0, 14);
  _INVERTOR(static_logic_tn1_tn2_0, 0, logic_tn1_tn2_0, 15);
  
//  _OR2(logic_tn1_tn2_0, 14, logic_tn1_tn2_0, 11, logic_tn1_tn2_0, 16);
  _OR2(logic_tn1_tn2_0, 15, logic_tn1_tn2_0, 10, logic_tn1_tn2_0, 17);
  
//  _AND2(static_logic_tn1_tn2_0, 0, logic_tn1_tn2_0, 12, logic_tn1_tn2_0, 18);
  _AND2(static_logic_tn1_tn2_0, 1, logic_tn1_tn2_0, 13, logic_tn1_tn2_0, 19);
  
//  _AND3(logic_tn1_tn2_0, 3, logic_tn1_tn2_0, 18, logic_tn1_tn2_0, 2, logic_tn1_tn2_0, 20);
  _AND3(logic_tn1_tn2_0, 8, logic_tn1_tn2_0, 19, logic_tn1_tn2_0, 2, logic_tn1_tn2_0, 21);
  
//  _AND4(logic_tn1_tn2_0, 18, logic_tn1_tn2_0, 2, logic_tn1_tn2_0,  8, logic_tn1_tn2_0, 16, logic_tn1_tn2_0, 22);
  _AND4(logic_tn1_tn2_0, 19, logic_tn1_tn2_0, 2, logic_tn1_tn2_0, 17, logic_tn1_tn2_0,  3, logic_tn1_tn2_0, 23);
  
//  _AND3(logic_tn1_tn2_0, 18, logic_tn1_tn2_0,  2, logic_tn1_tn2_0, 16, logic_tn1_tn2_0, 24);
  _AND3(logic_tn1_tn2_0,  8, logic_tn1_tn2_0, 17, logic_tn1_tn2_0,  2, logic_tn1_tn2_0, 25);
  
//  _OR3(logic_tn1_tn2_0, 20, logic_tn1_tn2_0, 22, logic_tn1_tn2_0, 24, logic_tn1_tn2_0, 26);
  _OR3(logic_tn1_tn2_0, 21, logic_tn1_tn2_0, 23, logic_tn1_tn2_0, 25, logic_tn1_tn2_0, 27);
  
//  _OR3(logic_tn1_tn2_0, 26, logic_tn1_tn2_0, 6, logic_tn1_tn2_0, 7, logic_tn1_tn2_0, 28);
  _OR2(logic_tn1_tn2_0, 27, logic_tn1_tn2_0, 9, logic_tn1_tn2_0, 29);

  uint32_t tn1_tn2 = 0;
//  if (_GET_OUTPUT_STATE(logic_tn1_tn2_0, 28)) tn1_tn2 = 0;
  /*else*/ if (_GET_OUTPUT_STATE(logic_tn1_tn2_0, 29))  tn1_tn2 = 1;
//  else
//  {
//    //� ��� ����� �������� ������ tn1_tn2 = 0
//  }
  
  if (tn1_tn2 == 0) 
  {
//    _SET_BIT(p_active_functions, RANG_TN1);
    _CLEAR_BIT(p_active_functions, RANG_TN2);
  }
  else
  {
    _SET_BIT(p_active_functions, RANG_TN2);
//    _CLEAR_BIT(p_active_functions, RANG_TN1);
  }

  return tn1_tn2;
}
/*****************************************************/

/*****************************************************/
// ���
/*****************************************************/
void avr_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int logic_AVR_0 = 0;
  unsigned int logic_AVR_1 = 0;
//  unsigned int logic_AVR_2 = 0;
  unsigned int logic_AVR_3 = 0;
//  unsigned int logic_AVR_4 = 0;

  logic_AVR_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV) != 0) << 0;
  logic_AVR_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_APV_WORK) != 0) << 1;
  logic_AVR_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_OTKL_VV) != 0) << 2;
  logic_AVR_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_OTKL_AVR) != 0) << 3;
  logic_AVR_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_OTKL_VID_ZOVN_ZAHYSTIV) != 0) << 4;
  logic_AVR_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_PRYVID_VV) != 0) << 5;
  _OR6(logic_AVR_0, 0, logic_AVR_0, 1, logic_AVR_0, 2, logic_AVR_0, 3, logic_AVR_0, 4, logic_AVR_0, 5, logic_AVR_0, 6);
  
  logic_AVR_0 |= ((current_settings_prt.control_avr & CTR_AVR_BLK) == 0) << 7;
  logic_AVR_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_SBROS_BLOCK_AVR) != 0) << 8;
  _OR2(logic_AVR_0, 7, logic_AVR_0, 8, logic_AVR_0, 9);

  logic_AVR_0 |= ((current_settings_prt.control_avr & CTR_AVR) != 0) << 11;
  logic_AVR_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_STATE_VV) == 0) << 12;

  logic_AVR_0 |= ((current_settings_prt.control_avr & CTR_AVR_UMAX) != 0) << 16;
  _INVERTOR(logic_AVR_0, 16, logic_AVR_0, 17);
  
  unsigned int setpoint_avr_tn1_U1_Umin = (_CHECK_SET_BIT(p_active_functions, RANG_PO_AVR_TN1_U1_MIN) == 0) ?
    current_settings_prt.setpoint_avr_tn1_U1_Umin[number_group_stp] :
    (current_settings_prt.setpoint_avr_tn1_U1_Umin[number_group_stp]*U_DOWN/100);
  logic_AVR_1 |= (
                  (measurement[IM_UAB1] <= setpoint_avr_tn1_U1_Umin) &&
                  (measurement[IM_UBC1] <= setpoint_avr_tn1_U1_Umin) &&
                  (measurement[IM_UCA1] <= setpoint_avr_tn1_U1_Umin)
                 ) << 0;   
  //"�� U1min < U1x"
  if (_GET_OUTPUT_STATE(logic_AVR_1, 0)) _SET_BIT(p_active_functions, RANG_PO_AVR_TN1_U1_MIN);
  else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_TN1_U1_MIN);
    
  unsigned int setpoint_avr_tn1_U2_low_work = (_CHECK_SET_BIT(p_active_functions, RANG_PO_AVR_TN1_U2_LOW_WORK) == 0) ?
    current_settings_prt.setpoint_avr_tn1_U2_low_work[number_group_stp] :
    (current_settings_prt.setpoint_avr_tn1_U2_low_work[number_group_stp]*U_UP/100);
  logic_AVR_1 |= (
                  (measurement[IM_UAB2] >= setpoint_avr_tn1_U2_low_work) &&
                  (measurement[IM_UBC2] >= setpoint_avr_tn1_U2_low_work) &&
                  (measurement[IM_UCA2] >= setpoint_avr_tn1_U2_low_work)
                 ) << 1;   
  //"�� U2min > U2x"
  if (_GET_OUTPUT_STATE(logic_AVR_1, 1)) _SET_BIT(p_active_functions, RANG_PO_AVR_TN1_U2_LOW_WORK);
  else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_TN1_U2_LOW_WORK);

  unsigned int setpoint_avr_tn1_U1_max = (_CHECK_SET_BIT(p_active_functions, RANG_PO_AVR_TN1_U1_MAX) == 0) ?
    current_settings_prt.setpoint_avr_tn1_U1_Umax[number_group_stp] :
    (current_settings_prt.setpoint_avr_tn1_U1_Umax[number_group_stp]*U_UP/100);
  logic_AVR_1 |= (
                  (measurement[IM_UAB1] >= setpoint_avr_tn1_U1_max) &&
                  (measurement[IM_UBC1] >= setpoint_avr_tn1_U1_max) &&
                  (measurement[IM_UCA1] >= setpoint_avr_tn1_U1_max)
                 ) << 21;   

  //"�� U1max > U1x"
  if (_GET_OUTPUT_STATE(logic_AVR_1, 21)) _SET_BIT(p_active_functions, RANG_PO_AVR_TN1_U1_MAX);
  else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_TN1_U1_MAX);

  unsigned int setpoint_avr_tn1_U2_high_work = (_CHECK_SET_BIT(p_active_functions, RANG_PO_AVR_TN1_U2_HIGH_WORK) == 0) ?
    current_settings_prt.setpoint_avr_tn1_U2_high_work[number_group_stp] :
    (current_settings_prt.setpoint_avr_tn1_U2_high_work[number_group_stp]*U_DOWN/100);
  logic_AVR_1 |= (
                  (measurement[IM_UAB2] <= setpoint_avr_tn1_U2_high_work) &&
                  (measurement[IM_UBC2] <= setpoint_avr_tn1_U2_high_work) &&
                  (measurement[IM_UCA2] <= setpoint_avr_tn1_U2_high_work)
                 ) << 22;   
  //"�� U2max < U2x"
  if (_GET_OUTPUT_STATE(logic_AVR_1, 22)) _SET_BIT(p_active_functions, RANG_PO_AVR_TN1_U2_HIGH_WORK);
  else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_TN1_U2_HIGH_WORK);

  
  _AND2(logic_AVR_1, 21, logic_AVR_0, 16, logic_AVR_1, 24);
  _OR2(logic_AVR_1, 0, logic_AVR_1, 24, logic_AVR_1, 26);
  _OR2(logic_AVR_1, 22, logic_AVR_0, 17, logic_AVR_1, 27);
  
  logic_AVR_1 |= (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_K1_AVR) != 0) << 2;
  _TIMER_IMPULSE(INDEX_TIMER_AVR_PUSK_K1, current_settings_prt.timeout_avr_pusk_k1[number_group_stp], previous_states_AVR_0, 1, logic_AVR_1, 2, logic_AVR_1, 3);
  
  logic_AVR_1 |= (_CHECK_SET_BIT(p_active_functions, RANG_STAT_BLOCK_AVR_1) != 0) << 4;
  
  logic_AVR_1 |= (_CHECK_SET_BIT(p_active_functions, RANG_OZT_AVR_1) != 0) << 16;
  _AND2(logic_AVR_1, 3, logic_AVR_1, 0, logic_AVR_1, 28);

  unsigned int setpoint_avr_tn2_U2_Umin = (_CHECK_SET_BIT(p_active_functions, RANG_PO_AVR_TN2_U2_MIN) == 0) ?
    current_settings_prt.setpoint_avr_tn2_U2_Umin[number_group_stp] :
    (current_settings_prt.setpoint_avr_tn2_U2_Umin[number_group_stp]*U_DOWN/100);
  logic_AVR_3 |= (
                  (measurement[IM_UAB2] <= setpoint_avr_tn2_U2_Umin) &&
                  (measurement[IM_UBC2] <= setpoint_avr_tn2_U2_Umin) &&
                  (measurement[IM_UCA2] <= setpoint_avr_tn2_U2_Umin)
                 ) << 0;   
  //"�� U2min < U2x"
  if (_GET_OUTPUT_STATE(logic_AVR_3, 0)) _SET_BIT(p_active_functions, RANG_PO_AVR_TN2_U2_MIN);
  else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_TN2_U2_MIN);
    
  unsigned int setpoint_avr_tn2_U1_low_work = (_CHECK_SET_BIT(p_active_functions, RANG_PO_AVR_TN2_U1_LOW_WORK) == 0) ?
    current_settings_prt.setpoint_avr_tn2_U1_low_work[number_group_stp] :
    (current_settings_prt.setpoint_avr_tn2_U1_low_work[number_group_stp]*U_UP/100);
  logic_AVR_3 |= (
                  (measurement[IM_UAB1] >= setpoint_avr_tn2_U1_low_work) &&
                  (measurement[IM_UBC1] >= setpoint_avr_tn2_U1_low_work) &&
                  (measurement[IM_UCA1] >= setpoint_avr_tn2_U1_low_work)
                 ) << 1;   
  //"�� U1min > U1x"
  if (_GET_OUTPUT_STATE(logic_AVR_3, 1)) _SET_BIT(p_active_functions, RANG_PO_AVR_TN2_U1_LOW_WORK);
  else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_TN2_U1_LOW_WORK);

  unsigned int setpoint_avr_tn2_U2_max = (_CHECK_SET_BIT(p_active_functions, RANG_PO_AVR_TN2_U2_MAX) == 0) ?
    current_settings_prt.setpoint_avr_tn2_U2_Umax[number_group_stp] :
    (current_settings_prt.setpoint_avr_tn2_U2_Umax[number_group_stp]*U_UP/100);
  logic_AVR_3 |= (
                  (measurement[IM_UAB2] >= setpoint_avr_tn2_U2_max) &&
                  (measurement[IM_UBC2] >= setpoint_avr_tn2_U2_max) &&
                  (measurement[IM_UCA2] >= setpoint_avr_tn2_U2_max)
                 ) << 21;   

  //"�� U2max > U2x"
  if (_GET_OUTPUT_STATE(logic_AVR_3, 21)) _SET_BIT(p_active_functions, RANG_PO_AVR_TN2_U2_MAX);
  else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_TN2_U2_MAX);

  unsigned int setpoint_avr_tn2_U1_high_work = (_CHECK_SET_BIT(p_active_functions, RANG_PO_AVR_TN2_U1_HIGH_WORK) == 0) ?
    current_settings_prt.setpoint_avr_tn2_U1_high_work[number_group_stp] :
    (current_settings_prt.setpoint_avr_tn2_U1_high_work[number_group_stp]*U_DOWN/100);
  logic_AVR_3 |= (
                  (measurement[IM_UAB1] <= setpoint_avr_tn2_U1_high_work) &&
                  (measurement[IM_UBC1] <= setpoint_avr_tn2_U1_high_work) &&
                  (measurement[IM_UCA1] <= setpoint_avr_tn2_U1_high_work)
                 ) << 22;   
  //"�� U1max < U1x"
  if (_GET_OUTPUT_STATE(logic_AVR_3, 22)) _SET_BIT(p_active_functions, RANG_PO_AVR_TN2_U1_HIGH_WORK);
  else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_TN2_U1_HIGH_WORK);

  _AND2(logic_AVR_3, 21, logic_AVR_0, 16, logic_AVR_3, 24);
  _OR2(logic_AVR_3, 0, logic_AVR_3, 24, logic_AVR_3, 26);
  _OR2(logic_AVR_3, 22, logic_AVR_0, 17, logic_AVR_3, 27);
  
  logic_AVR_3 |= (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_K2_AVR) != 0) << 2;
  _TIMER_IMPULSE(INDEX_TIMER_AVR_PUSK_K2, current_settings_prt.timeout_avr_pusk_k2[number_group_stp], previous_states_AVR_0, 2, logic_AVR_3, 2, logic_AVR_3, 3);
  
  logic_AVR_3 |= (_CHECK_SET_BIT(p_active_functions, RANG_STAT_BLOCK_AVR_2) != 0) << 4;
  
  logic_AVR_3 |= (_CHECK_SET_BIT(p_active_functions, RANG_OZT_AVR_2) != 0) << 16;
  _AND2(logic_AVR_3, 3, logic_AVR_3, 0, logic_AVR_3, 28);

  logic_AVR_1 |= (_CHECK_SET_BIT(p_active_functions, RANG_KOM3_ON_AVR) != 0) << 5;
  logic_AVR_3 |= (_CHECK_SET_BIT(p_active_functions, RANG_KOM4_ON_AVR) != 0) << 5;
  do
  {
    //"���.3 ���.���" (�� �������� �� �� �������� ��� ����� ��������, ��� ������� ��� ��������� ��������)
    if (_GET_OUTPUT_STATE(logic_AVR_1, 5)) _SET_BIT(p_active_functions, RANG_KOM3_ON_AVR);
    else  _CLEAR_BIT(p_active_functions, RANG_KOM3_ON_AVR);
    
    //"���.4 ���.���" (�� �������� �� �� �������� ��� ����� ��������, ��� ������� ��� ��������� ��������)
    if (_GET_OUTPUT_STATE(logic_AVR_3, 5)) _SET_BIT(p_active_functions, RANG_KOM4_ON_AVR);
    else  _CLEAR_BIT(p_active_functions, RANG_KOM4_ON_AVR);
    
    _OR2(logic_AVR_1, 5, logic_AVR_3, 5, logic_AVR_0, 14);
    _OR2(logic_AVR_0, 14, logic_AVR_0, 6, logic_AVR_0, 15);
    
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_AVR_0, 9), previous_states_AVR_0, 0, logic_AVR_0, 15, trigger_AVR_0, 0);
    _INVERTOR(trigger_AVR_0, 0, logic_AVR_0, 10);
    //"����.���"
    if (_GET_OUTPUT_STATE(trigger_AVR_0, 0)) _SET_BIT(p_active_functions, RANG_BLOCK_AVR);
    else  _CLEAR_BIT(p_active_functions, RANG_BLOCK_AVR);

    _AND3(logic_AVR_0, 10, logic_AVR_0, 11, logic_AVR_0, 12, logic_AVR_0, 13);
    
    _AND2(logic_AVR_1, 5, logic_AVR_0, 7, logic_AVR_1, 29);
    _AND2(logic_AVR_3, 5, logic_AVR_0, 7, logic_AVR_3, 29);
  
    _OR2(logic_AVR_1, 29, logic_AVR_1, 4, logic_AVR_1, 6);
    _TIMER_0_T(INDEX_TIMER_AVR_BLK_K1, current_settings_prt.timeout_avr_blk_k1[number_group_stp], logic_AVR_1, 6, logic_AVR_1, 7);
    _INVERTOR(logic_AVR_1, 7, logic_AVR_1, 8);
    
    _OR2(logic_AVR_3, 29, logic_AVR_3, 4, logic_AVR_3, 6);
    _TIMER_0_T(INDEX_TIMER_AVR_BLK_K2, current_settings_prt.timeout_avr_blk_k2[number_group_stp], logic_AVR_3, 6, logic_AVR_3, 7);
    _INVERTOR(logic_AVR_3, 7, logic_AVR_3, 8);
    
    _AND5(logic_AVR_0, 13, logic_AVR_1, 8, logic_AVR_1, 26, logic_AVR_1, 1, logic_AVR_1, 27, logic_AVR_1, 9);
    //"�� ��� �.1"
    if (_GET_OUTPUT_STATE(logic_AVR_1, 9)) _SET_BIT(p_active_functions, RANG_PO_AVR_K1);
    else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_K1);
    
    _AND5(logic_AVR_0, 13, logic_AVR_3, 8, logic_AVR_3, 26, logic_AVR_3, 1, logic_AVR_3, 27, logic_AVR_3, 9);
    //"�� ��� �.2"
    if (_GET_OUTPUT_STATE(logic_AVR_3, 9)) _SET_BIT(p_active_functions, RANG_PO_AVR_K2);
    else  _CLEAR_BIT(p_active_functions, RANG_PO_AVR_K2);

    _AND2(logic_AVR_1, 9, logic_AVR_1, 16, logic_AVR_1, 17);
    _OR2_INVERTOR(logic_AVR_1, 3, logic_AVR_1, 17, logic_AVR_1, 18);
    _AND2(logic_AVR_1, 9, logic_AVR_1, 18, logic_AVR_1, 19);

    _AND2(logic_AVR_3, 9, logic_AVR_3, 16, logic_AVR_3, 17);
    _OR2_INVERTOR(logic_AVR_3, 3, logic_AVR_3, 17, logic_AVR_3, 18);
    _AND2(logic_AVR_3, 9, logic_AVR_3, 18, logic_AVR_3, 19);
    
    _AND2(logic_AVR_1, 0, logic_AVR_1, 19, logic_AVR_1, 30);
    _AND3(logic_AVR_1, 19, logic_AVR_0, 16, logic_AVR_1, 21, logic_AVR_1, 25);
    
    _AND2(logic_AVR_3, 0, logic_AVR_3, 19, logic_AVR_3, 30);
    _AND3(logic_AVR_3, 19, logic_AVR_0, 16, logic_AVR_3, 21, logic_AVR_3, 25);

    _TIMER_T_0(INDEX_TIMER_AVR_VYMK_ROB_K1_UMIN, current_settings_prt.timeout_avr_vymk_rob_k1_Umin[number_group_stp], logic_AVR_1, 30, logic_AVR_1, 10);
    _TIMER_T_0(INDEX_TIMER_AVR_VYMK_ROB_K1_UMAX, current_settings_prt.timeout_avr_vymk_rob_k1_Umax[number_group_stp], logic_AVR_1, 25, logic_AVR_1, 23);
    _OR3(logic_AVR_1, 10, logic_AVR_1, 23, logic_AVR_1, 17, logic_AVR_1, 20);
    _TIMER_0_T(INDEX_TIMER_AVR_VYMK_K1, current_settings_prt.timeout_avr_vymk_k1[number_group_stp], logic_AVR_1, 20, logic_AVR_1, 11);
    //"���.1 ����.���"
    if (_GET_OUTPUT_STATE(logic_AVR_1, 11)) _SET_BIT(p_active_functions, RANG_KOM1_OFF_AVR);
    else  _CLEAR_BIT(p_active_functions, RANG_KOM1_OFF_AVR);
    
    _TIMER_T_0(INDEX_TIMER_AVR_VYMK_ROB_K2_UMIN, current_settings_prt.timeout_avr_vymk_rob_k2_Umin[number_group_stp], logic_AVR_3, 30, logic_AVR_3, 10);
    _TIMER_T_0(INDEX_TIMER_AVR_VYMK_ROB_K2_UMAX, current_settings_prt.timeout_avr_vymk_rob_k2_Umax[number_group_stp], logic_AVR_3, 25, logic_AVR_3, 23);
    _OR3(logic_AVR_3, 10, logic_AVR_3, 23, logic_AVR_3, 17, logic_AVR_3, 20);
    _TIMER_0_T(INDEX_TIMER_AVR_VYMK_K2, current_settings_prt.timeout_avr_vymk_k2[number_group_stp], logic_AVR_3, 20, logic_AVR_3, 11);
    //"���.2 ����.���"
    if (_GET_OUTPUT_STATE(logic_AVR_3, 11)) _SET_BIT(p_active_functions, RANG_KOM2_OFF_AVR);
    else  _CLEAR_BIT(p_active_functions, RANG_KOM2_OFF_AVR);
    
    _AND2(logic_AVR_1, 28, logic_AVR_1, 9, logic_AVR_1, 12);
    _AND2(logic_AVR_3, 28, logic_AVR_3, 9, logic_AVR_3, 12);

    _TIMER_T_0(INDEX_TIMER_AVR_VVIMK_REZ_K1, current_settings_prt.timeout_avr_vvimk_rez_k1[number_group_stp], logic_AVR_1, 12, logic_AVR_1, 13);
    _TIMER_0_T(INDEX_TIMER_AVR_VVIMK_K1, current_settings_prt.timeout_avr_vvimk_k1[number_group_stp], logic_AVR_1, 13, logic_AVR_1, 14);
    //"���.1 ���.���"
    if (_GET_OUTPUT_STATE(logic_AVR_1, 14)) _SET_BIT(p_active_functions, RANG_KOM1_ON_AVR);
    else  _CLEAR_BIT(p_active_functions, RANG_KOM1_ON_AVR);

    _TIMER_T_0(INDEX_TIMER_AVR_VVIMK_REZ_K2, current_settings_prt.timeout_avr_vvimk_rez_k2[number_group_stp], logic_AVR_3, 12, logic_AVR_3, 13);
    _TIMER_0_T(INDEX_TIMER_AVR_VVIMK_K2, current_settings_prt.timeout_avr_vvimk_k2[number_group_stp], logic_AVR_3, 13, logic_AVR_3, 14);
    //"���.2 ���.���"
    if (_GET_OUTPUT_STATE(logic_AVR_3, 14)) _SET_BIT(p_active_functions, RANG_KOM2_ON_AVR);
    else  _CLEAR_BIT(p_active_functions, RANG_KOM2_ON_AVR);

    _TIMER_T_0(INDEX_TIMER_AVR_D_DIJI_K1, current_settings_prt.timeout_avr_d_diji_k1[number_group_stp], logic_AVR_1, 12, logic_AVR_1, 15);
    _TIMER_0_T(INDEX_TIMER_AVR_TMP_1MS_K1, 1, logic_AVR_1, 15, logic_AVR_1, 5);


    _TIMER_T_0(INDEX_TIMER_AVR_D_DIJI_K2, current_settings_prt.timeout_avr_d_diji_k2[number_group_stp], logic_AVR_3, 12, logic_AVR_3, 15);
    _TIMER_0_T(INDEX_TIMER_AVR_TMP_1MS_K2, 1, logic_AVR_3, 15, logic_AVR_3, 5);
  }
  while(
        (_GET_OUTPUT_STATE(logic_AVR_1, 5) != (_CHECK_SET_BIT(p_active_functions, RANG_KOM3_ON_AVR) != 0)) ||
        (_GET_OUTPUT_STATE(logic_AVR_3, 5) != (_CHECK_SET_BIT(p_active_functions, RANG_KOM4_ON_AVR) != 0))
       );
  /*���� �� ������ � ����� �����, �� ����������� �� logic_AVR_1.5 ����� ����� ������� "���.3 ���.���" � logic_AVR_3.5 ����� ����� ������� "���.4 ���.���"*/
}
/*****************************************************/

/*****************************************************/
// "�������� ���������"
/*****************************************************/
void ctrl_phase_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  static unsigned int TN1_bilshe_porogu, TN2_bilshe_porogu;
  unsigned int setpoint_TN1, setpoint_TN2;
    
  if (TN1_bilshe_porogu == 0) setpoint_TN1 = PORIG_FOR_FAPCH*U_DOWN/100;
  else setpoint_TN1 = PORIG_FOR_FAPCH;
  if (TN2_bilshe_porogu == 0) setpoint_TN2 = PORIG_FOR_FAPCH*U_DOWN/100;
  else setpoint_TN2 = PORIG_FOR_FAPCH;
  
  TN1_bilshe_porogu = (measurement[IM_UA1] >= setpoint_TN1) && (measurement[IM_UB1] >= setpoint_TN1) && (measurement[IM_UC1] >= setpoint_TN1);
  TN2_bilshe_porogu = (measurement[IM_UA2] >= setpoint_TN2) && (measurement[IM_UB2] >= setpoint_TN2) && (measurement[IM_UC2] >= setpoint_TN2);

  unsigned int logic_CTRL_PHASE_0 = 0;
  
  static unsigned int state_delta_U, state_delta_phi, state_delta_f;
  if ((TN1_bilshe_porogu != 0) && (TN2_bilshe_porogu != 0))
  {
    //г����� ������
    unsigned int setpoint_U;
    setpoint_U = (state_delta_U == 0) ? current_settings_prt.setpoint_ctrl_phase_U[number_group_stp] : current_settings_prt.setpoint_ctrl_phase_U[number_group_stp]*U_DOWN/100;
    unsigned int Ua1 = measurement[IM_UA1];
    unsigned int Ua2 = measurement[IM_UA2];
    unsigned int Ub1 = measurement[IM_UB1];
    unsigned int Ub2 = measurement[IM_UB2];
    unsigned int Uc1 = measurement[IM_UC1];
    unsigned int Uc2 = measurement[IM_UC2];
    state_delta_U = ((unsigned int)(abs(Ua1 - Ua2)) >= setpoint_U) && 
                    ((unsigned int)(abs(Ub1 - Ub2)) >= setpoint_U) && 
                    ((unsigned int)(abs(Uc1 - Uc2)) >= setpoint_U);
    
    //г����� ���
    unsigned int setpoint_phi;
    setpoint_phi = (state_delta_phi == 0) ? current_settings_prt.setpoint_ctrl_phase_phi[number_group_stp] : current_settings_prt.setpoint_ctrl_phase_phi[number_group_stp]*KOEF_POVERNENNJA_GENERAL/100;
    unsigned int bank_phi_angle_high_tmp = bank_phi_angle_high;
    int phi_Ua1 = phi_angle_high[bank_phi_angle_high_tmp][FULL_ORT_Ua1];
    int phi_Ua2 = phi_angle_high[bank_phi_angle_high_tmp][FULL_ORT_Ua2];
    int phi_Ub1 = phi_angle_high[bank_phi_angle_high_tmp][FULL_ORT_Ub1];
    int phi_Ub2 = phi_angle_high[bank_phi_angle_high_tmp][FULL_ORT_Ub2];
    int phi_Uc1 = phi_angle_high[bank_phi_angle_high_tmp][FULL_ORT_Uc1];
    int phi_Uc2 = phi_angle_high[bank_phi_angle_high_tmp][FULL_ORT_Uc2];
    state_delta_phi = ((phi_Ua1 >= 0) && (phi_Ua2 >= 0) && ((unsigned int)(abs(phi_Ua1 - phi_Ua2)) >= setpoint_phi)) && 
                      ((phi_Ub1 >= 0) && (phi_Ub2 >= 0) && ((unsigned int)(abs(phi_Ub1 - phi_Ub2)) >= setpoint_phi)) && 
                      ((phi_Uc1 >= 0) && (phi_Uc2 >= 0) && ((unsigned int)(abs(phi_Uc1 - phi_Uc2)) >= setpoint_phi));

    //г����� ������
    unsigned int setpoint_f;
    setpoint_f = (state_delta_f == 0) ? current_settings_prt.setpoint_ctrl_phase_f[number_group_stp] : current_settings_prt.setpoint_ctrl_phase_f[number_group_stp]*KOEF_POVERNENNJA_GENERAL/100;
    int frequency_val_1_int = (int)frequency_val_1;
    int frequency_val_2_int = (int)frequency_val_2;
    state_delta_f = (frequency_val_1_int >= 0) && (frequency_val_2_int >= 0) && (((unsigned int)(abs(1000*frequency_val_1_int - 1000*frequency_val_2_int))) >= setpoint_f);

    logic_CTRL_PHASE_0 |= ((state_delta_U   != 0) && ((current_settings_prt.control_ctrl_phase & CTR_CTRL_PHASE_U  ) != 0)) << 0;
    logic_CTRL_PHASE_0 |= ((state_delta_phi != 0) && ((current_settings_prt.control_ctrl_phase & CTR_CTRL_PHASE_PHI) != 0)) << 1;
    logic_CTRL_PHASE_0 |= ((state_delta_f   != 0) && ((current_settings_prt.control_ctrl_phase & CTR_CTRL_PHASE_F  ) != 0)) << 2;
  }
  else
  {
    state_delta_U = 0;
    state_delta_phi = 0;
    state_delta_f = 0;
  }
  
  _TIMER_T_0(INDEX_TIMER_CTRL_PHASE_U  , current_settings_prt.timeout_ctrl_phase_U  [number_group_stp], logic_CTRL_PHASE_0, 0, logic_CTRL_PHASE_0, 3);
  _TIMER_0_T(INDEX_TIMER_CTRL_PHASE_U_D, current_settings_prt.timeout_ctrl_phase_U_d[number_group_stp], logic_CTRL_PHASE_0, 3, logic_CTRL_PHASE_0, 4);

  _TIMER_T_0(INDEX_TIMER_CTRL_PHASE_PHI  , current_settings_prt.timeout_ctrl_phase_phi  [number_group_stp], logic_CTRL_PHASE_0, 1, logic_CTRL_PHASE_0, 5);
  _TIMER_0_T(INDEX_TIMER_CTRL_PHASE_PHI_D, current_settings_prt.timeout_ctrl_phase_phi_d[number_group_stp], logic_CTRL_PHASE_0, 5, logic_CTRL_PHASE_0, 6);

  _TIMER_T_0(INDEX_TIMER_CTRL_PHASE_F  , current_settings_prt.timeout_ctrl_phase_f  [number_group_stp], logic_CTRL_PHASE_0, 2, logic_CTRL_PHASE_0, 7);
  _TIMER_0_T(INDEX_TIMER_CTRL_PHASE_F_D, current_settings_prt.timeout_ctrl_phase_f_d[number_group_stp], logic_CTRL_PHASE_0, 7, logic_CTRL_PHASE_0, 8);

  logic_CTRL_PHASE_0 |= ((sequence_TN1 == CONST_SEQ_FAIL) && ((current_settings_prt.control_ctrl_phase & CTR_CTRL_PHASE_SEQ_TN1) != 0) && (TN1_bilshe_porogu != 0)) << 9;
  logic_CTRL_PHASE_0 |= ((sequence_TN2 == CONST_SEQ_FAIL) && ((current_settings_prt.control_ctrl_phase & CTR_CTRL_PHASE_SEQ_TN2) != 0) && (TN2_bilshe_porogu != 0)) << 10;
  
  _TIMER_T_0(INDEX_TIMER_CTRL_PHASE_TMP1_100MS, 100, logic_CTRL_PHASE_0, 9 , logic_CTRL_PHASE_0, 11);
  _TIMER_T_0(INDEX_TIMER_CTRL_PHASE_TMP2_100MS, 100, logic_CTRL_PHASE_0, 10, logic_CTRL_PHASE_0, 12);
  
  if (_GET_OUTPUT_STATE(logic_CTRL_PHASE_0, 4)) _SET_BIT(p_active_functions, RANG_ERROR_DELTA_U_CTRL_PHASE);
  else  _CLEAR_BIT(p_active_functions, RANG_ERROR_DELTA_U_CTRL_PHASE);
  
  if (_GET_OUTPUT_STATE(logic_CTRL_PHASE_0, 6)) _SET_BIT(p_active_functions, RANG_ERROR_DELTA_PHI_CTRL_PHASE);
  else  _CLEAR_BIT(p_active_functions, RANG_ERROR_DELTA_PHI_CTRL_PHASE);
  
  if (_GET_OUTPUT_STATE(logic_CTRL_PHASE_0, 8)) _SET_BIT(p_active_functions, RANG_ERROR_DELTA_F_CTRL_PHASE);
  else  _CLEAR_BIT(p_active_functions, RANG_ERROR_DELTA_F_CTRL_PHASE);
  
  if (_GET_OUTPUT_STATE(logic_CTRL_PHASE_0, 11)) _SET_BIT(p_active_functions, RANG_ERROR_SEC_TN1_CTRL_PHASE);
  else  _CLEAR_BIT(p_active_functions, RANG_ERROR_SEC_TN1_CTRL_PHASE);
  
  if (_GET_OUTPUT_STATE(logic_CTRL_PHASE_0, 12)) _SET_BIT(p_active_functions, RANG_ERROR_SEC_TN2_CTRL_PHASE);
  else  _CLEAR_BIT(p_active_functions, RANG_ERROR_SEC_TN2_CTRL_PHASE);
}
/*****************************************************/

/*****************************************************/
// ���������� � ��
/*****************************************************/
void ready_tu(volatile unsigned int *p_active_functions)
{
  unsigned int tmp_value = (_CHECK_SET_BIT(p_active_functions, RANG_PRYVID_VV) == 0)                  << 0;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV) != 0)                    << 1;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) != 0)      << 2;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_AVAR_DEFECT) == 0)                            << 3;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_MISCEVE_DYSTANCIJNE) == 0)                    << 6;
  
  _Bool ctrl_ready_tu = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_READY_TU) == 0);
  
  if (!previous_states_ready_tu && _GET_OUTPUT_STATE(tmp_value, 1)) {
    previous_states_ready_tu = 0;
  }
  
  _OR2(tmp_value, 2, ctrl_ready_tu, 0, tmp_value, 7);
  _D_TRIGGER(1, 0, _GET_OUTPUT_STATE(tmp_value, 7), previous_states_ready_tu, 0, tmp_value, 1, trigger_ready_tu, 0);
  
  _AND4(tmp_value, 0, tmp_value, 3, !trigger_ready_tu, 0, tmp_value, 6, tmp_value, 5);
  
  //���������� � ��
  if (_GET_OUTPUT_STATE(tmp_value, 5))
    _SET_BIT(p_active_functions, RANG_READY_TU);
  else
    _CLEAR_BIT(p_active_functions, RANG_READY_TU);
}
/*****************************************************/

/*****************************************************/
// ����
/*****************************************************/
inline void urov_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  /*******************************/
  //��������� ������������ ������� ����� ��� ����
  /*******************************/
  unsigned int max_faze_current = measurement[IM_IA];
  if (max_faze_current < measurement[IM_IB]) max_faze_current = measurement[IM_IB];
  if (max_faze_current < measurement[IM_IC]) max_faze_current = measurement[IM_IC];
  /*******************************/
  
  /*******************************/
  if(
     (( current_settings_prt.control_urov & CTR_UROV_STATE) != 0) &&
     (
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_MTZ1   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ1             ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_MTZ2   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ2             ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_MTZ3   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ3             ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_MTZ4   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ4             ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_ZDZ    ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ZDZ              ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_ZOP1   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ZOP              ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_UMIN1  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMIN1            ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_UMIN2  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMIN2            ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_UMAX1  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMAX1            ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_UMAX2  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMAX2            ) != 0)) ||
      (                                                                               (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_UROV_VID_DV ) != 0))
     )     
    )
  {
    //� ����� ������� ����
    
    unsigned int setpoint; //������� - � ���� ���������� ����������� ��������
    unsigned int previous_state_po_urov;
    
    //���� �� ���� �� �� �������, �� ����� ��������� �� ������ ���������� - �������, ��� ��������� �� ������� � ������� ���� �� ��������� ����
    //���� �� ���� ��� ����������, �� ����� ��������� �� ������� ���������� - �������� ������� �� ������� ������ �� ����������� ����������
    if(( previous_state_po_urov = _CHECK_SET_BIT(p_active_functions, RANG_PO_UROV) ) ==0 )
    {
      //�������� �� ������ �����������
      setpoint = current_settings_prt.setpoint_urov[number_group_stp];
    }
    else
    {
      //�������� �� ������ ����������
      setpoint = current_settings_prt.setpoint_urov[number_group_stp]*KOEF_POVERNENNJA_GENERAL/100;
    }
    
    //�����������, ��� ������� ������ "�� ����"
    if (max_faze_current >= setpoint)
    {
      //������������ ������ ���� �������� ���� �������
      if(previous_state_po_urov == 0)
      {
        //������������ ������ "�� ����"
        _SET_BIT(p_active_functions, RANG_PO_UROV);
      
        //��������� ������� ����1 � ����2, ���� ���� �� �� �������
        global_timers[INDEX_TIMER_UROV1] = 0;
        global_timers[INDEX_TIMER_UROV2] = 0;
      }
    }
    else 
    {
      //������������ ������ ���� ����� �������
      if(previous_state_po_urov != 0)
      {
        //������� ������ "�� ����"
        _CLEAR_BIT(p_active_functions, RANG_PO_UROV);
        //�� � ������ ����� �������� ������� "����. ����1" � "����. ����2"
        _CLEAR_BIT(p_active_functions, RANG_UROV1);
        _CLEAR_BIT(p_active_functions, RANG_UROV2);
        //���� ������� �� �� ������, �� ������� ��
        if ( global_timers[INDEX_TIMER_UROV1] >=0) global_timers[INDEX_TIMER_UROV1] = -1;
        if ( global_timers[INDEX_TIMER_UROV2] >=0) global_timers[INDEX_TIMER_UROV2] = -1;
      }
    }
    
    //���������� �� ������ ����1 �������� �������� �� ��������
    if(global_timers[INDEX_TIMER_UROV1] >= current_settings_prt.timeout_urov_1[number_group_stp])
    {
      //���� ��������� �������� ����1 �� ������������ ������ "����. ����1"
      _SET_BIT(p_active_functions, RANG_UROV1);

      //������� ������ ����1
      global_timers[INDEX_TIMER_UROV1] = -1;
    }

    //���������� �� ������ ����2 �������� �������� �� ��������
    if(global_timers[INDEX_TIMER_UROV2] >= current_settings_prt.timeout_urov_2[number_group_stp])
    {
      //���� ��������� �������� ����2 �� ������������ ������ "����. ����2"
      _SET_BIT(p_active_functions, RANG_UROV2);

      //������� ������ ����2
      global_timers[INDEX_TIMER_UROV2] = -1;
    }
  }
  else
  {
    //����� ������� �� ������� � �������, �� �� ���� ����������
    _CLEAR_BIT(p_active_functions, RANG_PO_UROV);
    _CLEAR_BIT(p_active_functions, RANG_UROV1);
    _CLEAR_BIT(p_active_functions, RANG_UROV2);
    global_timers[INDEX_TIMER_UROV1] = -1;
    global_timers[INDEX_TIMER_UROV2] = -1;
  }  
}
  /*******************************/
/*****************************************************/

/*****************************************************/
//���
/*****************************************************/
inline void apv_handler(volatile unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int logic_APV_0 = 0;
  unsigned int logic_APV_1 = 0;

  //������� ��������
  logic_APV_1 |= (start_restart != 0) << 19;
  //������� ����������� ��� ������� ��������
  start_restart = 0;

  //"�������� ����������"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_STAT_BLK_APV) != 0) << 0;
  _INVERTOR(logic_APV_0, 0, logic_APV_0, 1);

  //�:"���� �� ���1"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ1) != 0) << 2;
  //"���1"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_MTZ1) != 0) << 3;
  _AND2(logic_APV_0, 2, logic_APV_0, 3, logic_APV_0, 4);

  //�:"���� �� ���2"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ2) != 0) << 5;
  //"���2"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_MTZ2) != 0) << 6;
  _AND2(logic_APV_0, 5, logic_APV_0, 6, logic_APV_0, 7);

  //�:"���� �� ���3"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ3) != 0) << 8;
  //"���3"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_MTZ3) != 0) << 9;
  _AND2(logic_APV_0, 8, logic_APV_0, 9, logic_APV_0, 10);

  //�:"���� �� ���4"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ4) != 0) << 11;
  //"���4"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_MTZ4) != 0) << 12;
  _AND2(logic_APV_0, 11, logic_APV_0, 12, logic_APV_0, 13);
  
  _OR4(logic_APV_0, 4, logic_APV_0, 7, logic_APV_0, 10, logic_APV_0, 13, logic_APV_0, 14);
  _TIMER_0_T(INDEX_TIMER_APV_TMP1, 1, logic_APV_0, 14, logic_APV_0, 15);

  //"���/���� �� ��"
  logic_APV_0 |= 0/*(_CHECK_SET_BIT(p_active_functions, RANG_ACHR_CHAPV_VID_DV) != 0)*/ << 17;
  //�:"���� �� ��"
  logic_APV_1 |= 0/*((current_settings_prt.control_achr_chapv & CTR_CHAPV_VID_DV) != 0)*/ << 22;
  
  _AND2(logic_APV_0, 17, logic_APV_1, 22, logic_APV_0, 18);
  
  _TIMER_0_T(INDEX_TIMER_ACHR_CHAPV, MAX_VALUE_TIMER_FOR_COUNT_SIGNAL_ACHR_CHAPV, logic_APV_0, 18, logic_APV_0, 19);

  _OR2_INVERTOR(logic_APV_0, 15, logic_APV_0, 19, logic_APV_0, 20);

  //"���� ��������"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_STATE_VV) != 0) << 21;
  _TIMER_IMPULSE(INDEX_TIMER_APV_BLOCK_VID_VV, current_settings_prt.timeout_apv_block_vid_VV[number_group_stp], previous_states_APV_0, 0, logic_APV_0, 21, logic_APV_0, 22);

  //�:"���"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_1) != 0) << 23;
  _INVERTOR(logic_APV_0, 23, logic_APV_0, 24);

  //�:"���2"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_2) != 0) << 25;
  _INVERTOR(logic_APV_0, 25, logic_APV_0, 26);

  //�:"���3"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_3) != 0) << 27;
  _INVERTOR(logic_APV_0, 27, logic_APV_0, 28);

  //�:"���4"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_4) != 0) << 29;
  _INVERTOR(logic_APV_0, 29, logic_APV_0, 30);

  //������� �������� ����������� ���������� ���� �� ������� �� ������������� � ���������� ����
  logic_APV_0 |= _GET_OUTPUT_STATE(previous_states_APV_0, 1) << 31;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 2) <<  0;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 3) <<  1;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 4) <<  2;
  
  unsigned int previous_trigger_APV_0;
  
  /*
  ������� �������� �� �������, �� � ���� do-while ������ �� ����������,
  ��� ���� ����������� �� ��� ������ �� �������� ������, ���� �, ��������, ����
  �������� �������� ��� �������.
  ��� ����������� ����������� ��� �������, �� �� ������� ��� ����� ������, �
  � ���� ������ ����� ����������
  */
  _CLEAR_BIT(p_active_functions, RANG_APV1);
  _CLEAR_BIT(p_active_functions, RANG_APV2);
  _CLEAR_BIT(p_active_functions, RANG_APV3);
  _CLEAR_BIT(p_active_functions, RANG_APV4);
  do
  {
    /***
    Գ����� �������� ���� �������, �� ����, �������, �������� � �� ����
    ����� ���� �������� ���������� ������������ �������
    ***/
    _CLEAR_STATE(previous_states_APV_0, 1);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_0, 31) << 1;
    _CLEAR_STATE(previous_states_APV_0, 2);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_1,  0) << 2;
    _CLEAR_STATE(previous_states_APV_0, 3);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_1,  1) << 3;
    _CLEAR_STATE(previous_states_APV_0, 4);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_1,  2) << 4;
    
    previous_trigger_APV_0 = trigger_APV_0;
    /***/
    
    _OR2(logic_APV_1, 2, logic_APV_1, 1, logic_APV_1, 3);
    
    
    //���1
    _OR6(logic_APV_1, 19, logic_APV_0, 14,                   trigger_APV_0, 1, trigger_APV_0, 2, trigger_APV_0, 3, logic_APV_0, 31, logic_APV_1, 4);
    _OR6(logic_APV_0, 18, logic_APV_0, 22, logic_APV_0, 24, logic_APV_1, 3, logic_APV_1, 0, logic_APV_1, 4, logic_APV_1, 8);
    _D_TRIGGER(_GET_OUTPUT_STATE(logic_APV_0, 1),  0, _GET_OUTPUT_STATE(logic_APV_1, 8), previous_states_APV_0, 5, logic_APV_0, 20, trigger_APV_0, 0);                 
    _TIMER_T_0(INDEX_TIMER_APV_1, current_settings_prt.timeout_apv_1[number_group_stp], trigger_APV_0, 0, logic_APV_1, 9);
    /*
    ��� ������ ����������� � ����� p_active_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� ������� (�������� ��� ������� ����������� �����
    ������ do-while).
    */
    if (_GET_OUTPUT_STATE(logic_APV_1, 9)) _SET_BIT(p_active_functions, RANG_APV1);
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV1, current_settings_prt.timeout_apv_block_vid_apv1[number_group_stp], logic_APV_1, 9, logic_APV_0, 31);

    //���2
    _AND2_INVERTOR(logic_APV_0, 31, logic_APV_0, 15, logic_APV_1, 10);
    _OR6(logic_APV_1, 19, logic_APV_0, 14, trigger_APV_0, 0,                   trigger_APV_0, 2, trigger_APV_0, 3, logic_APV_1,  0, logic_APV_1, 5);
    _OR6(logic_APV_0, 18, logic_APV_0, 24, logic_APV_0, 26, logic_APV_1, 2, logic_APV_1, 1, logic_APV_1, 5, logic_APV_1, 11);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_1, 11), previous_states_APV_0, 6, logic_APV_1, 10, trigger_APV_0, 1);    
    _TIMER_T_0(INDEX_TIMER_APV_2, current_settings_prt.timeout_apv_2[number_group_stp], trigger_APV_0, 1, logic_APV_1, 12);
    /*
    ��� ������ ����������� � ����� p_active_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� ������� (�������� ��� ������� ����������� �����
    ������ do-while).
    */
    if (_GET_OUTPUT_STATE(logic_APV_1, 12)) _SET_BIT(p_active_functions, RANG_APV2);
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV2, current_settings_prt.timeout_apv_block_vid_apv2[number_group_stp], logic_APV_1, 12, logic_APV_1, 0);

    //���3
    _AND2_INVERTOR(logic_APV_1, 0, logic_APV_0, 15, logic_APV_1, 13);
    _OR6(logic_APV_1, 19, logic_APV_0, 14, trigger_APV_0, 0, trigger_APV_0, 1,                   trigger_APV_0, 3, logic_APV_1,  1, logic_APV_1, 6);
    _OR5(logic_APV_0, 18, logic_APV_0, 24, logic_APV_0, 28, logic_APV_1, 2, logic_APV_1, 6, logic_APV_1, 14);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_1, 14), previous_states_APV_0, 7, logic_APV_1, 13, trigger_APV_0, 2);                 
    _TIMER_T_0(INDEX_TIMER_APV_3, current_settings_prt.timeout_apv_3[number_group_stp], trigger_APV_0, 2, logic_APV_1, 15);
    /*
    ��� ������ ����������� � ����� p_active_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� ������� (�������� ��� ������� ����������� �����
    ������ do-while).
    */
    if (_GET_OUTPUT_STATE(logic_APV_1, 15)) _SET_BIT(p_active_functions, RANG_APV3);
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV3, current_settings_prt.timeout_apv_block_vid_apv3[number_group_stp], logic_APV_1, 15, logic_APV_1, 1);

    //���4
    _AND2_INVERTOR(logic_APV_1, 1, logic_APV_0, 15, logic_APV_1, 16);
    _OR6(logic_APV_1, 19, logic_APV_0, 14, trigger_APV_0, 0, trigger_APV_0, 1, trigger_APV_0, 2,                   logic_APV_1,  2, logic_APV_1, 7);
    _OR4(logic_APV_0, 18, logic_APV_0, 24, logic_APV_0, 30, logic_APV_1, 7, logic_APV_1, 17);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_1, 17), previous_states_APV_0, 8, logic_APV_1, 16, trigger_APV_0, 3);                 
    _TIMER_T_0(INDEX_TIMER_APV_4, current_settings_prt.timeout_apv_4[number_group_stp], trigger_APV_0, 3, logic_APV_1, 18);
    /*
    ��� ������ ����������� � ����� p_active_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� ������� (�������� ��� ������� ����������� �����
    ������ do-while).
    */
    if (_GET_OUTPUT_STATE(logic_APV_1, 18)) _SET_BIT(p_active_functions, RANG_APV4);
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV4, current_settings_prt.timeout_apv_block_vid_apv4[number_group_stp], logic_APV_1, 18, logic_APV_1, 2);
  }
  while (
         (_GET_OUTPUT_STATE(logic_APV_0, 31) != _GET_OUTPUT_STATE(previous_states_APV_0, 1)) ||
         (_GET_OUTPUT_STATE(logic_APV_1,  0) != _GET_OUTPUT_STATE(previous_states_APV_0, 2)) ||
         (_GET_OUTPUT_STATE(logic_APV_1,  1) != _GET_OUTPUT_STATE(previous_states_APV_0, 3)) ||
         (_GET_OUTPUT_STATE(logic_APV_1,  2) != _GET_OUTPUT_STATE(previous_states_APV_0, 4)) ||
         ( trigger_APV_0                     !=  previous_trigger_APV_0                    )  
        );
  
  _Bool work_apv = 0;
  _OR4(trigger_APV_0, 0, trigger_APV_0, 1, trigger_APV_0, 2, trigger_APV_0, 3, work_apv, 0);
  
  //������ ���
  if (work_apv) _SET_BIT(p_active_functions, RANG_APV_WORK);
  else  _CLEAR_BIT(p_active_functions, RANG_APV_WORK);
  
}
/*****************************************************/

/*****************************************************/
//������� ��������� ������� ��������� � ����������
/*****************************************************/
inline void on_off_handler(volatile unsigned int *p_active_functions)
{
  static unsigned int previous_active_functions[N_BIG];
  unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0};

  /*********************/
  //�������� ����������� �������
  /*********************/
  //������  ����������
  if (global_timers[INDEX_TIMER_VIDKL_VV] >= 0)
  {
    //������ �� ����� �������� � �� ����� ����� ����� ��������� ���� ������
    if (global_timers[INDEX_TIMER_VIDKL_VV] >= current_settings_prt.timeout_swch_off)
    {
      //������ �������� ����� ������������� ��������
      global_timers[INDEX_TIMER_VIDKL_VV] = -1;
      //³������ � ����� �������, �� ����� �����������, �� ���� �� �� ���� ������������
      _CLEAR_BIT(p_active_functions, RANG_WORK_BO);
    }
    //����������� ������ ����� �� ������, �� ������ ���������� �� �� ���� ��������� � ����������� � ����� ����������� �������,
    //��� �� ����� ���� �� ��������, ��� ���������� ��������� �������� �� ���� ��� � ������� ��������� ������ ����� ��
    global_timers[INDEX_TIMER_BLK_VKL_VV] = 0;
  }
    
  //������  ���������� ���������
  if (global_timers[INDEX_TIMER_BLK_VKL_VV] >= 0)
  {
    //������ ���������� ��������� �� ����� �������� � �� ����� ����� ����� ��������� ���� ������
    if (global_timers[INDEX_TIMER_BLK_VKL_VV] >= current_settings_prt.timeout_swch_udl_blk_on)
    {
      //������ �������� ����� ������������� ��������
      global_timers[INDEX_TIMER_BLK_VKL_VV] = -1;
    }
  }

  //������  ���������
  if (global_timers[INDEX_TIMER_VKL_VV] >= 0)
  {
    //������ �� ����� �������� � �� ����� ����� ����� ��������� ���� ������

    //���� �� ����� ������ ������ ��������� ������, ��� ����, �� ������� �� � ���������� ��������� �� �� ������, �� ������ ��������� ����� �������
    if ((global_timers[INDEX_TIMER_VIDKL_VV] >= 0) || (global_timers[INDEX_TIMER_BLK_VKL_VV] >=0))
    {
      global_timers[INDEX_TIMER_VKL_VV] = -1;
      //³������ � ����� �������, �� ����� �����������, �� ���� �B �� ���� ������������
      _CLEAR_BIT(p_active_functions, RANG_WORK_BV);
    }
    else
    {
      //����������, �� ������ ��������� �� �������� ����� ������������ ��������
      if (global_timers[INDEX_TIMER_VKL_VV] >= current_settings_prt.timeout_swch_on)
      {
        //������ �������� ����� ������������� ��������
        global_timers[INDEX_TIMER_VKL_VV] = -1;
        //³������ � ����� �������, �� ����� �����������, �� ���� �B �� ���� ������������
        _CLEAR_BIT(p_active_functions, RANG_WORK_BV);
      }
    }
  }
  /*********************/

  /*********************/
  //������ ������������ ���� ����������, �� �� ���� ��������� ��������� ��������
  /*********************/
  /*
  ��� ������ �������������� ����� � ������ ��������, ���� �� ������������ ���� ����� �������,
  � ���� ���� ������� - �� ������������
  */
  _CLEAR_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV);
  if (
      ((p_active_functions[0] & current_settings_prt.ranguvannja_off_cb[0]) != 0) ||
      ((p_active_functions[1] & current_settings_prt.ranguvannja_off_cb[1]) != 0) ||
      ((p_active_functions[2] & current_settings_prt.ranguvannja_off_cb[2]) != 0) ||
      ((p_active_functions[3] & current_settings_prt.ranguvannja_off_cb[3]) != 0) ||
      ((p_active_functions[4] & current_settings_prt.ranguvannja_off_cb[4]) != 0) ||
      ((p_active_functions[5] & current_settings_prt.ranguvannja_off_cb[5]) != 0) ||
      ((p_active_functions[6] & current_settings_prt.ranguvannja_off_cb[6]) != 0)
     )
  {
    //� ����� ��������� ���� ���������
    _SET_BIT(p_active_functions, RANG_WORK_BO);

    //��������� (��� ���������� ���������� � 0, ���� �� ������� ������ ��������� ��) �������: ����� ��, ����������� ��.
    global_timers[INDEX_TIMER_VIDKL_VV  ] = 0;
    global_timers[INDEX_TIMER_BLK_VKL_VV] = 0;
    
    //������� ��������� ����� ���������
    _CLEAR_BIT(p_active_functions, RANG_WORK_BV);
    //������� ������ ���� ���������
    global_timers[INDEX_TIMER_VKL_VV] = -1;  

    /*
    ������� ������ "³��������� �� �������" (�� ����� �������� ����� �������
    ��������� ������� "������ ��" ����-���� �������� �� ����������� "�����. ��")
    */
    //������� ����������� ����� ��� ���������� ������� "����.��"
    for (unsigned int i = 0; i < N_BIG; i++ )  maska[i] = (unsigned int)(~0);
    _CLEAR_BIT(maska, RANG_OTKL_VV);
    if (
        ((p_active_functions[0] & maska[0]) != 0) ||
        ((p_active_functions[1] & maska[1]) != 0) ||
        ((p_active_functions[2] & maska[2]) != 0) ||
        ((p_active_functions[3] & maska[3]) != 0) ||
        ((p_active_functions[4] & maska[4]) != 0) ||
        ((p_active_functions[5] & maska[5]) != 0) ||
        ((p_active_functions[6] & maska[6]) != 0)
       )
    {
      //��������� �� �������
      _SET_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV);
      
      unsigned int temp_array_of_outputs[N_BIG];
      for (unsigned int i = 0; i < N_BIG; i++ ) temp_array_of_outputs[i] = (p_active_functions[i] & maska[i]);
          
      /*****************************************************
      ��������� ���������� ��� ������� ���������� ��� ����
      *****************************************************/
      unsigned char *label_to_time_array;
      if (copying_time == 0) label_to_time_array = time;
      else label_to_time_array = time_copy;
          
      //���1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ1);
      }
      
      //���2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ2);
      }
      
      //���3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ3) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ3);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ3][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ3);
      }
      
      //���4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ4) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ4);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ4][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ4);
      }
      
      //���
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZDZ) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_ZDZ) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ZDZ);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZDZ][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZDZ);
      }
      
      //����1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UROV1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UROV1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV1);
      }
      
      //����2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UROV2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UROV2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV2);
      }
      
      //���
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZOP) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_ZOP) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ZOP);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZOP);
      }
      
      //Umin1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMIN1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMIN1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN1);
      }
      
      //Umin2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMIN2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMIN2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN2);
      }
      
      //Umax1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMAX1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMAX1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX1);
      }
      
      //Umax2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMAX2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMAX2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX2);
      }
      
      //³��������� �� ������� �������
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OTKL_VID_ZOVN_ZAHYSTIV) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_OTKL_VID_ZOVN_ZAHYSTIV) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_OTKL_VID_ZOVN_ZAHYSTIV);
      }
      
      //³��������� �� ����� ������� (��� ���������� �� ������� "����.��")
      if(
         (
          (temp_array_of_outputs[0] != 0) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0) ||
          (temp_array_of_outputs[6] != 0)
         )
         &&
         (
          ((previous_active_functions[0] & temp_array_of_outputs[0])!= temp_array_of_outputs[0]) ||
          ((previous_active_functions[1] & temp_array_of_outputs[1])!= temp_array_of_outputs[1]) ||
          ((previous_active_functions[2] & temp_array_of_outputs[2])!= temp_array_of_outputs[2]) ||
          ((previous_active_functions[3] & temp_array_of_outputs[3])!= temp_array_of_outputs[3]) ||
          ((previous_active_functions[4] & temp_array_of_outputs[4])!= temp_array_of_outputs[4]) ||
          ((previous_active_functions[5] & temp_array_of_outputs[5])!= temp_array_of_outputs[5]) ||
          ((previous_active_functions[6] & temp_array_of_outputs[6])!= temp_array_of_outputs[6])
         ) 
        )   
      {
        info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_INSHYKH_SYGNALIV);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_INSHYKH_SYGNALIV][i] = *(label_to_time_array + i);
      }
      /*****************************************************/
    }
  }

  /*********************/
  //���� ������������ ���� ���������
  /*********************/
  if (
      (global_timers[INDEX_TIMER_VIDKL_VV  ] < 0) && 
      (global_timers[INDEX_TIMER_BLK_VKL_VV] < 0) &&
      (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_VKL_VV) == 0)
     )
  {
    //������� �� �������� ������� �� � ���������� ��������� ��, � ����� ���� ������� ���������� ��������� ��
    //���� ����������, �� ���� ����� ������� ��

    if (
        ((p_active_functions[0] & current_settings_prt.ranguvannja_on_cb[0]) != 0) ||
        ((p_active_functions[1] & current_settings_prt.ranguvannja_on_cb[1]) != 0) ||
        ((p_active_functions[2] & current_settings_prt.ranguvannja_on_cb[2]) != 0) ||
        ((p_active_functions[3] & current_settings_prt.ranguvannja_on_cb[3]) != 0) ||
        ((p_active_functions[4] & current_settings_prt.ranguvannja_on_cb[4]) != 0) ||
        ((p_active_functions[5] & current_settings_prt.ranguvannja_on_cb[5]) != 0) ||
        ((p_active_functions[6] & current_settings_prt.ranguvannja_on_cb[6]) != 0)
      )
    {
      //³������ � ����� �������, �� ����� �����������, �� �� ����� ���������� ���� �� (���� �� �� �� ��������)
      _SET_BIT(p_active_functions, RANG_WORK_BV);

      //��������� (��� ���������� ���������� � 0, ���� �� ������� ������ ��������� ��) ������ ������ ��
      global_timers[INDEX_TIMER_VKL_VV] = 0;
    }
  }
  else
  {
    //�� ����� ������ ���� ���� ��� ����� ���� ���������� ��
    global_timers[INDEX_TIMER_VKL_VV] = -1;
    _CLEAR_BIT(p_active_functions, RANG_WORK_BV);
  }
  /*********************/

  /*********************/
  //������� ���������� ���� ������� ��� ������� ���������/���������
  /*********************/
  for (unsigned int i = 0; i < N_BIG; i++) previous_active_functions[i] = p_active_functions[i];
  /*********************/
}
/*****************************************************/

/*****************************************************/
//�������� ������� ��������
/*****************************************************/
void control_VV(volatile unsigned int *p_active_functions)
{
  unsigned int logic_control_VV_0 = 0;

  //"�������� ���."
  logic_control_VV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_CTRL_VKL ) != 0) << 0;
  //"�������� ����."
  logic_control_VV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_CTRL_OTKL) != 0) << 1;
  
  _XOR_INVERTOR(logic_control_VV_0, 0, logic_control_VV_0, 1, logic_control_VV_0, 2);

  _TIMER_T_0(INDEX_TIMER_PRYVOD_VV, current_settings_prt.timeout_pryvoda_VV, logic_control_VV_0, 2, logic_control_VV_0, 3);

  //�:"�������� ��"
  logic_control_VV_0 |= ((current_settings_prt.control_switch & CTR_PRYVOD_VV) != 0) << 4;
  
  _AND2(logic_control_VV_0, 3, logic_control_VV_0, 4, logic_control_VV_0, 5);
  
  if (_GET_OUTPUT_STATE(logic_control_VV_0, 5))
    _SET_BIT(p_active_functions, RANG_PRYVID_VV);
  else
    _CLEAR_BIT(p_active_functions, RANG_PRYVID_VV);
}
/*****************************************************/

/*****************************************************/
//���������� ������������ ��� ��������� ������� ��������
/*****************************************************/
void make_koef_for_resurs(void)
{
  float tmp_1, tmp_2;
  
  tmp_1 = (float)current_settings.setpoint_r_kom_st_Inom/(float)current_settings.setpoint_r_kom_st_Inom_vymk;
  tmp_1  = log10f(tmp_1);

  tmp_2 = (float)current_settings.setpoint_Inom_vymk/(float)current_settings.setpoint_Inom;
  tmp_2  = log10f(tmp_2);
  
  //�������, �� ����������� ��� ���������� ������� �������� ����� ������ �����
  koef_resurs_changed = CHANGED_ETAP_EXECUTION;

  K_resurs = tmp_1/tmp_2;
  
  //�������, �� ����������� ��� ���������� ������� �������� ����� � ������� �� ������ �������� �������
  koef_resurs_changed = CHANGED_ETAP_ENDED;
}
/*****************************************************/

/*****************************************************/
//˳������� �������
/*****************************************************/
inline void resurs_vymykacha_handler(volatile unsigned int *p_active_functions)
{
  static unsigned int previous_active_functions[N_BIG];
  
  if (restart_counter != 0)
  {
    //����� ������ ������� ������� ������� ��������
    resurs_vymykacha = current_settings_prt.setpoint_pochatkovyj_resurs;
    resurs_vidkljuchennja = current_settings_prt.setpoint_pochatkova_k_vymk;
    
     restart_counter = 0;

    //��������� ����� � EEPROM
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT);

    //�������, �� �������� ������� ������� ��������
    information_about_restart_counter |= ((1 << USB_RECUEST)|(1 << RS485_RECUEST));
  }
  
  /*******************************/
  //��������� ������������ ������� ����� �� ��� ������ ����� ��������� (��)
  /*******************************/
  static unsigned int max_faze_current_vv;
  if (_CHECK_SET_BIT(p_active_functions, RANG_WORK_BO) != 0)
  {
    unsigned int max_faze_current_tmp = measurement[IM_IA];
    if (max_faze_current_tmp < measurement[IM_IB]) max_faze_current_tmp = measurement[IM_IB];
    if (max_faze_current_tmp < measurement[IM_IC]) max_faze_current_tmp = measurement[IM_IC];
    max_faze_current_tmp = max_faze_current_tmp*current_settings_prt.TCurrent/1000;
  
    if (_CHECK_SET_BIT(previous_active_functions, RANG_WORK_BO) == 0)
    {
      //����������� ����� ������ ��
      max_faze_current_vv = max_faze_current_tmp;
    }
    else if (_CHECK_SET_BIT(previous_active_functions, RANG_WORK_BO) != 0)
    {
      //�� �������� ���� ������
      if (max_faze_current_vv < max_faze_current_tmp) max_faze_current_vv = max_faze_current_tmp;
    }
    
    if (max_faze_current_vv > current_settings_prt.setpoint_Inom_vymk) 
    {
      _SET_BIT(p_active_functions, RANG_PEREVYSHCHENNJA_Inom_VYMK);
    }
    else
    {
      _CLEAR_BIT(p_active_functions, RANG_PEREVYSHCHENNJA_Inom_VYMK);
    }
  }
  /*******************************/
  
  if (
      ((current_settings_prt.control_switch & CTR_RESURS_VV) != 0) &&
      (_CHECK_SET_BIT(previous_active_functions, RANG_WORK_BO) != 0) &&
      (_CHECK_SET_BIT(p_active_functions , RANG_WORK_BO) == 0)
     ) 
  {
    //����������� ���������� "������ ��"
    
    /*******************************/
    //������������ ������ �������a
    /*******************************/
    unsigned int N = 0;
    if (max_faze_current_vv >= current_settings_prt.setpoint_Inom_vymk) {
      N = (unsigned int) ceilf((float)current_settings_prt.setpoint_r_kom_st_Inom/(float)current_settings_prt.setpoint_r_kom_st_Inom_vymk);
    } else if (max_faze_current_vv <= current_settings_prt.setpoint_Inom) {
      N = 1;
    } else {
      float I_div_Inom = (float)max_faze_current_vv / (float)current_settings_prt.setpoint_Inom;
      float lg_I_div_Inom = log10f(I_div_Inom);
      float lg_N = K_resurs_prt * lg_I_div_Inom;
      float N_ = powf(10, lg_N);
      N = (unsigned int) ceilf(N_);
      if ((((float)N) - N_) >= 0.5f)
      {
        N--;
      }
      
    }
    
    if (resurs_vymykacha <= N) {
      resurs_vymykacha = 0;
    } else {
      resurs_vymykacha -= N;
    }
    
    //�������� ����� �����������
    if ((0xffffffff - resurs_vidkljuchennja) >= 1)
    {
      //��������� ������� �� ������� ������������
      resurs_vidkljuchennja++;
    }

    //��������� ����� � EEPROM
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT);
  }
  
  if (resurs_vymykacha <= current_settings_prt.setpoint_krytychnyj_resurs) 
  {
    _SET_BIT(p_active_functions, RANG_KRYTYCHNYJ_RESURS_VYMYKACHA);
  }
  else
  {
    _CLEAR_BIT(p_active_functions, RANG_KRYTYCHNYJ_RESURS_VYMYKACHA);
  }

  if (resurs_vymykacha == 0) 
  {
    _SET_BIT(p_active_functions, RANG_VYCHERPANYJ_RESURS_VYMYKACHA);
  }
  else
  {
    _CLEAR_BIT(p_active_functions, RANG_VYCHERPANYJ_RESURS_VYMYKACHA);
  }
 

  /*********************/
  //������� ���������� ���� ������� ��� ������� ���������/���������
  /*********************/
  for (unsigned int i = 0; i < N_BIG; i++) previous_active_functions[i] = p_active_functions[i];
  /*********************/
}
/*****************************************************/

/*****************************************************/
//�������� �� ����������� ���������� ������ �����������/����������� ����������
/*****************************************************/
inline unsigned int stop_regisrator(volatile unsigned int* carrent_active_functions, unsigned int* ranguvannja_registrator)
{
  unsigned int stop = 0;

  {
    if (
        ((carrent_active_functions[0] & ranguvannja_registrator[0]) == 0) &&
        ((carrent_active_functions[1] & ranguvannja_registrator[1]) == 0) &&
        ((carrent_active_functions[2] & ranguvannja_registrator[2]) == 0) &&
        ((carrent_active_functions[3] & ranguvannja_registrator[3]) == 0) &&
        ((carrent_active_functions[4] & ranguvannja_registrator[4]) == 0) &&
        ((carrent_active_functions[5] & ranguvannja_registrator[5]) == 0) &&
        ((carrent_active_functions[6] & ranguvannja_registrator[6]) == 0)
      )
    {
      //�����������, �� � ���� ������� ��������� ���������� ����� �� �������
      
      if (
          ((carrent_active_functions[0] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_0) == 0) &&
          ((carrent_active_functions[1] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_1) == 0) &&
          ((carrent_active_functions[2] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_2) == 0) &&
          ((carrent_active_functions[3] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_3) == 0) &&
          ((carrent_active_functions[4] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_4) == 0) &&
          ((carrent_active_functions[5] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_5) == 0) &&
          ((carrent_active_functions[6] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_6) == 0)
        )
      {
        //�����������, �� �� �������, �� ������ ���������� ��������� �������� ����� ������
          
        //����������, �� �� �������, �� ������� � ����� ����� ��������
        unsigned int global_timers_work = 0, i = INDEX_TIMER_DF_PAUSE_START;
        while ((i < NEXT_TIMER) && (global_timers_work == 0))
        {
          if (global_timers[i] >= 0) 
          {
            if (
                (
                 (i != INDEX_TIMER_PRYVOD_VV) ||
                 (  
                  ((current_settings_prt.control_switch & CTR_PRYVOD_VV) != 0) &&
                  (global_timers[i] < current_settings_prt.timeout_pryvoda_VV) 
                 )   
                ) 
               )
            global_timers_work = 1;
          }
          i++;
        }
          
        if (global_timers_work == 0)
        {
          //�����������, �� �� �������, �� �������� � ����� ��������
        
          //�������, �� ��������� ���� ���� ���������
          stop = 0xff;
        }
      }
    }
  }
  
  return stop;
}
/*****************************************************/

/*****************************************************/
//����������� ����������� ������� ������ ����������� ����������
/*****************************************************/
void fix_undefined_error_dr(volatile unsigned int* carrent_active_functions)
{
  //����������� ������� � ������� � ��������� ���������
  _SET_BIT(set_diagnostyka, ERROR_DR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_DEFECT);
  //���������� ����� ������ � ����������� � ���� "�� ����� ������ ���� �� � ���������� ����������� �� ����������" 
  state_dr_record = STATE_DR_NO_RECORD;
  //������� ������ ������ ����������� ����������
  _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
}
/*****************************************************/

/*****************************************************/
//������� ���������� ������������� ������� ������ 
/*****************************************************/
inline void start_monitoring_max_phase_current(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� ������������� ������� ������
  number_max_phase_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_phase_max_dr[ 0] = measurement[IM_IA];
  measurements_phase_max_dr[ 1] = measurement[IM_IB];
  measurements_phase_max_dr[ 2] = measurement[IM_IC];
  measurements_phase_max_dr [3] = measurement[IM_I2];
  measurements_phase_max_dr[ 4] = measurement[IM_I1];
  measurements_phase_max_dr[ 5] = measurement[IM_UA1];
  measurements_phase_max_dr[ 6] = measurement[IM_UB1];
  measurements_phase_max_dr[ 7] = measurement[IM_UC1];
  measurements_phase_max_dr[ 8] = measurement[IM_UA2];
  measurements_phase_max_dr[ 9] = measurement[IM_UB2];
  measurements_phase_max_dr[10] = measurement[IM_UC2];
  measurements_phase_max_dr[11] = measurement[IM_UAB1];
  measurements_phase_max_dr[12] = measurement[IM_UBC1];
  measurements_phase_max_dr[13] = measurement[IM_UCA1];
  measurements_phase_max_dr[14] = measurement[IM_UAB2];
  measurements_phase_max_dr[15] = measurement[IM_UBC2];
  measurements_phase_max_dr[16] = measurement[IM_UCA2];
  measurements_phase_max_dr[17] = (unsigned int)frequency_val_1_int;
  measurements_phase_max_dr[18] = (unsigned int)frequency_val_2_int;
  
  //��������� ����������� ������ ����� �� ������ ������
  max_phase_current_dr = measurements_phase_max_dr[0];
  if (max_phase_current_dr < measurements_phase_max_dr[1]) max_phase_current_dr = measurements_phase_max_dr[1];
  if (max_phase_current_dr < measurements_phase_max_dr[2]) max_phase_current_dr = measurements_phase_max_dr[2];

  //Գ����� ��� � ������� ������� ��������� ������
  measurements_phase_max_dr[19] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� ������������� ������� ������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� ������������� ������� ������
/*****************************************************/
inline void continue_monitoring_max_phase_current(unsigned int time_tmp)
{
  //��������, �� �� � ����� ������ ����� ������, �� ��� �� �������� ������������
  if (
      (max_phase_current_dr < measurement[IM_IA]) ||
      (max_phase_current_dr < measurement[IM_IB]) ||
      (max_phase_current_dr < measurement[IM_IC])
     )
  {
    //����������� ��� ��� ��������� �������� ����� � ������� ������� ������������� �� ���
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_phase_max_dr[ 0] = measurement[IM_IA];
    measurements_phase_max_dr[ 1] = measurement[IM_IB];
    measurements_phase_max_dr[ 2] = measurement[IM_IC];
    measurements_phase_max_dr [3] = measurement[IM_I2];
    measurements_phase_max_dr[ 4] = measurement[IM_I1];
    measurements_phase_max_dr[ 5] = measurement[IM_UA1];
    measurements_phase_max_dr[ 6] = measurement[IM_UB1];
    measurements_phase_max_dr[ 7] = measurement[IM_UC1];
    measurements_phase_max_dr[ 8] = measurement[IM_UA2];
    measurements_phase_max_dr[ 9] = measurement[IM_UB2];
    measurements_phase_max_dr[10] = measurement[IM_UC2];
    measurements_phase_max_dr[11] = measurement[IM_UAB1];
    measurements_phase_max_dr[12] = measurement[IM_UBC1];
    measurements_phase_max_dr[13] = measurement[IM_UCA1];
    measurements_phase_max_dr[14] = measurement[IM_UAB2];
    measurements_phase_max_dr[15] = measurement[IM_UBC2];
    measurements_phase_max_dr[16] = measurement[IM_UCA2];
    measurements_phase_max_dr[17] = (unsigned int)frequency_val_1_int;
    measurements_phase_max_dr[18] = (unsigned int)frequency_val_2_int;

    max_phase_current_dr = measurements_phase_max_dr[0];
    if (max_phase_current_dr < measurements_phase_max_dr[1]) max_phase_current_dr = measurements_phase_max_dr[1];
    if (max_phase_current_dr < measurements_phase_max_dr[2]) max_phase_current_dr = measurements_phase_max_dr[2];

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_phase_max_dr[19] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� �������� �����/����� ������� 
/*****************************************************/
inline void start_monitoring_min_U(unsigned int time_tmp)
{
  unsigned int index_IM_UA, index_IM_UB, index_IM_UC;
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  if (TN1_TN2 == 1)
  {
    index_IM_UA = IM_UA2;
    index_IM_UB = IM_UB2;
    index_IM_UC = IM_UC2;

    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
  }
  else
  {
    index_IM_UA = IM_UA1;
    index_IM_UB = IM_UB1;
    index_IM_UC = IM_UC1;

    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
  }

  //�������� ������� ���������� ������� �������� �����/����� �������
  number_min_U_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_U_min_dr[ 0] = measurement[IM_IA];
  measurements_U_min_dr[ 1] = measurement[IM_IB];
  measurements_U_min_dr[ 2] = measurement[IM_IC];
  measurements_U_min_dr [3] = measurement[IM_I2];
  measurements_U_min_dr[ 4] = measurement[IM_I1];
  measurements_U_min_dr[ 5] = measurement[IM_UA1];
  measurements_U_min_dr[ 6] = measurement[IM_UB1];
  measurements_U_min_dr[ 7] = measurement[IM_UC1];
  measurements_U_min_dr[ 8] = measurement[IM_UA2];
  measurements_U_min_dr[ 9] = measurement[IM_UB2];
  measurements_U_min_dr[10] = measurement[IM_UC2];
  measurements_U_min_dr[11] = measurement[IM_UAB1];
  measurements_U_min_dr[12] = measurement[IM_UBC1];
  measurements_U_min_dr[13] = measurement[IM_UCA1];
  measurements_U_min_dr[14] = measurement[IM_UAB2];
  measurements_U_min_dr[15] = measurement[IM_UBC2];
  measurements_U_min_dr[16] = measurement[IM_UCA2];
  measurements_U_min_dr[17] = (unsigned int)frequency_val_1_int;
  measurements_U_min_dr[18] = (unsigned int)frequency_val_2_int;
  
  if ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) == 0)
  {
    //��������� �������� ����� ������� �� ������ ������
    min_voltage_dr = measurement[index_IM_UAB];
    if (min_voltage_dr > measurement[index_IM_UBC]) min_voltage_dr = measurement[index_IM_UBC];
    if (min_voltage_dr > measurement[index_IM_UCA]) min_voltage_dr = measurement[index_IM_UCA];
  }
  else
  {
    //��������� �������� ����� ������� �� ������ ������
    min_voltage_dr = measurement[index_IM_UA];
    if (min_voltage_dr > measurement[index_IM_UB]) min_voltage_dr = measurement[index_IM_UB];
    if (min_voltage_dr > measurement[index_IM_UC]) min_voltage_dr = measurement[index_IM_UC];
  }

  //Գ����� ��� � ������� ������� ��������� ������
  measurements_U_min_dr[19] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� �������� �����/����� �������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� �������� �����/����� �������
/*****************************************************/
inline void continue_monitoring_min_U(unsigned int time_tmp)
{
  unsigned int index_IM_UA, index_IM_UB, index_IM_UC;
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  if (TN1_TN2 == 1)
  {
    index_IM_UA = IM_UA2;
    index_IM_UB = IM_UB2;
    index_IM_UC = IM_UC2;

    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
  }
  else
  {
    index_IM_UA = IM_UA1;
    index_IM_UB = IM_UB1;
    index_IM_UC = IM_UC1;

    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
  }

  //��������, �� �� � ����� ����������� ������ �����, �� �� �� ������� ���������
  if (
      (
       ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) == 0) &&
       (  
        (min_voltage_dr > measurement[index_IM_UAB]) ||
        (min_voltage_dr > measurement[index_IM_UBC]) ||
        (min_voltage_dr > measurement[index_IM_UCA])
       )
      )   
      || 
      (
       ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) != 0) &&
       (  
        (min_voltage_dr > measurement[index_IM_UA]) ||
        (min_voltage_dr > measurement[index_IM_UB]) ||
        (min_voltage_dr > measurement[index_IM_UC])
       )
     )
    )    
  {
    //����������� ��� ��� ��������� ����������� ������ � ������� ������� ������������� �� ���
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_U_min_dr[ 0] = measurement[IM_IA];
    measurements_U_min_dr[ 1] = measurement[IM_IB];
    measurements_U_min_dr[ 2] = measurement[IM_IC];
    measurements_U_min_dr [3] = measurement[IM_I2];
    measurements_U_min_dr[ 4] = measurement[IM_I1];
    measurements_U_min_dr[ 5] = measurement[IM_UA1];
    measurements_U_min_dr[ 6] = measurement[IM_UB1];
    measurements_U_min_dr[ 7] = measurement[IM_UC1];
    measurements_U_min_dr[ 8] = measurement[IM_UA2];
    measurements_U_min_dr[ 9] = measurement[IM_UB2];
    measurements_U_min_dr[10] = measurement[IM_UC2];
    measurements_U_min_dr[11] = measurement[IM_UAB1];
    measurements_U_min_dr[12] = measurement[IM_UBC1];
    measurements_U_min_dr[13] = measurement[IM_UCA1];
    measurements_U_min_dr[14] = measurement[IM_UAB2];
    measurements_U_min_dr[15] = measurement[IM_UBC2];
    measurements_U_min_dr[16] = measurement[IM_UCA2];
    measurements_U_min_dr[17] = (unsigned int)frequency_val_1_int;
    measurements_U_min_dr[18] = (unsigned int)frequency_val_2_int;

    if ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) == 0)
    {
      //��������� �������� ����� ������� �� ������ ������
      min_voltage_dr = measurement[index_IM_UAB];
      if (min_voltage_dr > measurement[index_IM_UBC]) min_voltage_dr = measurement[index_IM_UBC];
      if (min_voltage_dr > measurement[index_IM_UCA]) min_voltage_dr = measurement[index_IM_UCA];
    }
    else
    {
      //��������� �������� ����� ������� �� ������ ������
      min_voltage_dr = measurement[index_IM_UA];
      if (min_voltage_dr > measurement[index_IM_UB]) min_voltage_dr = measurement[index_IM_UB];
      if (min_voltage_dr > measurement[index_IM_UC]) min_voltage_dr = measurement[index_IM_UC];
    }

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_U_min_dr[19] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� ����������� �����/����� ������� 
/*****************************************************/
inline void start_monitoring_max_U(unsigned int time_tmp)
{
  unsigned int index_IM_UA, index_IM_UB, index_IM_UC;
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  if (TN1_TN2 == 1)
  {
    index_IM_UA = IM_UA2;
    index_IM_UB = IM_UB2;
    index_IM_UC = IM_UC2;

    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
  }
  else
  {
    index_IM_UA = IM_UA1;
    index_IM_UB = IM_UB1;
    index_IM_UC = IM_UC1;

    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
  }

  //�������� ������� ���������� ������� ����������� �����/����� �������
  number_max_U_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_U_max_dr[ 0] = measurement[IM_IA];
  measurements_U_max_dr[ 1] = measurement[IM_IB];
  measurements_U_max_dr[ 2] = measurement[IM_IC];
  measurements_U_max_dr [3] = measurement[IM_I2];
  measurements_U_max_dr[ 4] = measurement[IM_I1];
  measurements_U_max_dr[ 5] = measurement[IM_UA1];
  measurements_U_max_dr[ 6] = measurement[IM_UB1];
  measurements_U_max_dr[ 7] = measurement[IM_UC1];
  measurements_U_max_dr[ 8] = measurement[IM_UA2];
  measurements_U_max_dr[ 9] = measurement[IM_UB2];
  measurements_U_max_dr[10] = measurement[IM_UC2];
  measurements_U_max_dr[11] = measurement[IM_UAB1];
  measurements_U_max_dr[12] = measurement[IM_UBC1];
  measurements_U_max_dr[13] = measurement[IM_UCA1];
  measurements_U_max_dr[14] = measurement[IM_UAB2];
  measurements_U_max_dr[15] = measurement[IM_UBC2];
  measurements_U_max_dr[16] = measurement[IM_UCA2];
  measurements_U_max_dr[17] = (unsigned int)frequency_val_1_int;
  measurements_U_max_dr[18] = (unsigned int)frequency_val_2_int;
  
  if ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) == 0)
  {
    //��������� ���������� ����� ������� �� ������ ������
    max_voltage_dr = measurement[index_IM_UAB];
    if (max_voltage_dr < measurement[index_IM_UBC]) max_voltage_dr = measurement[index_IM_UBC];
    if (max_voltage_dr <measurement[index_IM_UCA]) max_voltage_dr = measurement[index_IM_UCA];
  }
  else
  {
    //��������� ���������� ����� ������� �� ������ ������
    max_voltage_dr = measurement[index_IM_UA];
    if (max_voltage_dr < measurement[index_IM_UB]) max_voltage_dr = measurement[index_IM_UB];
    if (max_voltage_dr <measurement[index_IM_UC]) max_voltage_dr = measurement[index_IM_UC];
  }

  //Գ����� ��� � ������� ������� ��������� ������
  measurements_U_max_dr[19] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� ����������� �����/����� �������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� ����������� �����/����� �������
/*****************************************************/
inline void continue_monitoring_max_U(unsigned int time_tmp)
{
  unsigned int index_IM_UA, index_IM_UB, index_IM_UC;
  unsigned int index_IM_UAB, index_IM_UBC, index_IM_UCA;
  if (TN1_TN2 == 1)
  {
    index_IM_UA = IM_UA2;
    index_IM_UB = IM_UB2;
    index_IM_UC = IM_UC2;

    index_IM_UAB = IM_UAB2;
    index_IM_UBC = IM_UBC2;
    index_IM_UCA = IM_UCA2;
  }
  else
  {
    index_IM_UA = IM_UA1;
    index_IM_UB = IM_UB1;
    index_IM_UC = IM_UC1;

    index_IM_UAB = IM_UAB1;
    index_IM_UBC = IM_UBC1;
    index_IM_UCA = IM_UCA1;
  }

  //��������, �� �� � ����� ����������� ������ �����, �� �� �� ������� ������������
  if (
      (
       ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) == 0) &&
       (  
        (max_voltage_dr < measurement[index_IM_UAB]) ||
        (max_voltage_dr < measurement[index_IM_UBC]) ||
        (max_voltage_dr < measurement[index_IM_UCA])
       )
      )   
      || 
      (
       ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) != 0) &&
       (  
        (max_voltage_dr < measurement[index_IM_UA]) ||
        (max_voltage_dr < measurement[index_IM_UB]) ||
        (max_voltage_dr < measurement[index_IM_UC])
       )
     )
    )    
  {
    //����������� ��� ��� ��������� ����������� ������ � ������� ������� ������������� �� ���
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_U_max_dr[ 0] = measurement[IM_IA];
    measurements_U_max_dr[ 1] = measurement[IM_IB];
    measurements_U_max_dr[ 2] = measurement[IM_IC];
    measurements_U_max_dr [3] = measurement[IM_I2];
    measurements_U_max_dr[ 4] = measurement[IM_I1];
    measurements_U_max_dr[ 5] = measurement[IM_UA1];
    measurements_U_max_dr[ 6] = measurement[IM_UB1];
    measurements_U_max_dr[ 7] = measurement[IM_UC1];
    measurements_U_max_dr[ 8] = measurement[IM_UA2];
    measurements_U_max_dr[ 9] = measurement[IM_UB2];
    measurements_U_max_dr[10] = measurement[IM_UC2];
    measurements_U_max_dr[11] = measurement[IM_UAB1];
    measurements_U_max_dr[12] = measurement[IM_UBC1];
    measurements_U_max_dr[13] = measurement[IM_UCA1];
    measurements_U_max_dr[14] = measurement[IM_UAB2];
    measurements_U_max_dr[15] = measurement[IM_UBC2];
    measurements_U_max_dr[16] = measurement[IM_UCA2];
    measurements_U_max_dr[17] = (unsigned int)frequency_val_1_int;
    measurements_U_max_dr[18] = (unsigned int)frequency_val_2_int;

    if ((current_settings_prt.control_transformator & CTR_TRANSFORMATOR_LINE_PHASE) == 0)
    {
      //��������� ���������� ����� ������� �� ������ ������
      max_voltage_dr = measurement[index_IM_UAB];
      if (max_voltage_dr < measurement[index_IM_UBC]) max_voltage_dr = measurement[index_IM_UBC];
      if (max_voltage_dr <measurement[index_IM_UCA]) max_voltage_dr = measurement[index_IM_UCA];
    }
    else
    {
      //��������� ���������� ����� ������� �� ������ ������
      max_voltage_dr = measurement[index_IM_UA];
      if (max_voltage_dr < measurement[index_IM_UB]) max_voltage_dr = measurement[index_IM_UB];
      if (max_voltage_dr <measurement[index_IM_UC]) max_voltage_dr = measurement[index_IM_UC];
    }

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_U_max_dr[19] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� ������������� ������  ��������� �����������
/*****************************************************/
inline void start_monitoring_max_ZOP(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� ������������� 3I0
  number_max_ZOP_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_ZOP_max_dr[ 0] = measurement[IM_IA];
  measurements_ZOP_max_dr[ 1] = measurement[IM_IB];
  measurements_ZOP_max_dr[ 2] = measurement[IM_IC];
  measurements_ZOP_max_dr [3] = measurement[IM_I2];
  measurements_ZOP_max_dr[ 4] = measurement[IM_I1];
  measurements_ZOP_max_dr[ 5] = measurement[IM_UA1];
  measurements_ZOP_max_dr[ 6] = measurement[IM_UB1];
  measurements_ZOP_max_dr[ 7] = measurement[IM_UC1];
  measurements_ZOP_max_dr[ 8] = measurement[IM_UA2];
  measurements_ZOP_max_dr[ 9] = measurement[IM_UB2];
  measurements_ZOP_max_dr[10] = measurement[IM_UC2];
  measurements_ZOP_max_dr[11] = measurement[IM_UAB1];
  measurements_ZOP_max_dr[12] = measurement[IM_UBC1];
  measurements_ZOP_max_dr[13] = measurement[IM_UCA1];
  measurements_ZOP_max_dr[14] = measurement[IM_UAB2];
  measurements_ZOP_max_dr[15] = measurement[IM_UBC2];
  measurements_ZOP_max_dr[16] = measurement[IM_UCA2];
  measurements_ZOP_max_dr[17] = (unsigned int)frequency_val_1_int;
  measurements_ZOP_max_dr[18] = (unsigned int)frequency_val_2_int;
  
  //Գ����� ��� � ������� ������� ��������� ������
  measurements_ZOP_max_dr[19] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� ������������� ������ ��������� �����������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� ������������� ������ ��������� �����������
/*****************************************************/
inline void continue_monitoring_max_ZOP(unsigned int time_tmp)
{
  //��������, �� �� � ����� ����� ��������� ����������� ������, �� ��� �� �������� ������������
/*
      _I2 - ����� ��������� ����������� ��� ������������ ������������� ������������� �������� I2/I1
      _I1 - ����� ����� ����������� ��� ������������ ������������� ������������� �������� I2/I1
      
      I2 -  ������� ����� ��������� �����������
      I1 -  ������� ����� ����� �����������
      
      ����� ���������� ���������:
      _I2     I2
      ---  < --- /x �� _I1*I1  
      _I1     I1
      
      (_I2*I1 < I2*_I1)  - �� � �����, �� ����� � ����� ���(���) �� ��������� ���
*/
  unsigned int I2, I1, _I1, _I2;
   I2 = measurement[IM_I2];
   I1 = measurement[IM_I1];
  _I2 = measurements_ZOP_max_dr[3];
  _I1 = measurements_ZOP_max_dr[4];
  if (
      ( (_I1 >  0) && ( ((_I2*I1) < (I2*_I1)) || (I1 == 0) ) ) ||
      ( (_I1 == 0) && (I1 == 0) && ( _I2 < I2 ) ) 
     )
  {
    //����������� ��� ��� ��������� ����� ��������� ����������� � ������� ������� ������
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_ZOP_max_dr[ 0] = measurement[IM_IA];
    measurements_ZOP_max_dr[ 1] = measurement[IM_IB];
    measurements_ZOP_max_dr[ 2] = measurement[IM_IC];
    measurements_ZOP_max_dr [3] = measurement[IM_I2];
    measurements_ZOP_max_dr[ 4] = measurement[IM_I1];
    measurements_ZOP_max_dr[ 5] = measurement[IM_UA1];
    measurements_ZOP_max_dr[ 6] = measurement[IM_UB1];
    measurements_ZOP_max_dr[ 7] = measurement[IM_UC1];
    measurements_ZOP_max_dr[ 8] = measurement[IM_UA2];
    measurements_ZOP_max_dr[ 9] = measurement[IM_UB2];
    measurements_ZOP_max_dr[10] = measurement[IM_UC2];
    measurements_ZOP_max_dr[11] = measurement[IM_UAB1];
    measurements_ZOP_max_dr[12] = measurement[IM_UBC1];
    measurements_ZOP_max_dr[13] = measurement[IM_UCA1];
    measurements_ZOP_max_dr[14] = measurement[IM_UAB2];
    measurements_ZOP_max_dr[15] = measurement[IM_UBC2];
    measurements_ZOP_max_dr[16] = measurement[IM_UCA2];
    measurements_ZOP_max_dr[17] = (unsigned int)frequency_val_1_int;
    measurements_ZOP_max_dr[18] = (unsigned int)frequency_val_2_int;

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_ZOP_max_dr[19] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//���������� ���������� ������������� ������
/*
  type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE        - ���������� ���������� ������������� ������� ������
  type_current == IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE              - ���������� ���������� �������� �������
  type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE              - ���������� ���������� ����������� �������
  type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP          - ���������� ���������� ������������� ������ ��������� �����������
*/
/*****************************************************/
inline void end_monitoring_min_max_measurement(unsigned int type_current, volatile unsigned int* carrent_active_functions)
{
  if(
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE   ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE         ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE         ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP     )
    )
  {
    int step = number_max_phase_dr   + 
               number_min_U_dr       +
               number_max_U_dr       +
               number_max_ZOP_dr;
    
    //�������� �� ���������� ������ ����������� ������������
    if(
       ( (number_max_phase_dr   > 0) || ( (number_max_phase_dr   == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE  )) == 0) ) ) &&
       ( (number_min_U_dr       > 0) || ( (number_min_U_dr       == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE        )) == 0) ) ) &&
       ( (number_max_U_dr       > 0) || ( (number_max_U_dr       == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE        )) == 0) ) ) &&
       ( (number_max_ZOP_dr     > 0) || ( (number_max_ZOP_dr     == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP    )) == 0) ) ) &&
       ( (step > 0) && (step <= MAX_NUMBER_FIX_MAX_MEASUREMENTS)) 
      )
    {
      unsigned char *input_data_point, *output_data_point;
      
      //��������� ������� �����  ������ �������� ���
      if(type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)
      {
        input_data_point = (unsigned char *)(measurements_phase_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)
      {
        input_data_point = (unsigned char *)(measurements_U_min_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)
      {
        input_data_point = (unsigned char *)(measurements_U_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)
      {
        input_data_point = (unsigned char *)(measurements_ZOP_max_dr);
      }
      
      //��������� ������ ���� ��� ����� ��������
      step -= 1; //���� ��  ��������� ���������� � 0, � �� � 1 (step ����������� �� ����� 1(�� ��������� ����), ���� ��'������ ����� �� ���� ����)
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE  )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE  ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE        )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE        ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE        )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE        ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP    )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP    ))
        step -= 1;
      
      if(step >= 0)
      {
        output_data_point = (buffer_for_save_dr_record + FIRST_INDEX_FIRST_BLOCK_DR +step*sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS);
        
        for(unsigned int i = 0; i < (sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS); i++)
        {
          if(i != (sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS - 1))
          {
            *(output_data_point + i) = *(input_data_point + i);
          }
          else
          {
            //� ������� ���� ������, �� ������� ����� � Little-endian ������� �������� ����� ���������� �������� ������, ���� ���� ������, �� ����� ���������� ������������ �����
            *(output_data_point + i) = type_current;
          }
        }

        //������ ������, �� �� �� ���䳿 ���������� 
        state_current_monitoring &= ~(1<<type_current);
      }
      else
      {
        //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
        fix_undefined_error_dr(carrent_active_functions);
      }
    }
    else
    {
      //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
      fix_undefined_error_dr(carrent_active_functions);
    }
  }
  else
  {
    //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
    fix_undefined_error_dr(carrent_active_functions);
  }
}
/*****************************************************/

/*****************************************************/
//������ ������� ������ ����� � DataFalsh
/*****************************************************/
inline void command_start_saving_record_dr_into_dataflash(void)
{
  //� �������� �� ���������� ����� ���������� ����������� �����������, �� ������� ����� � �� �� ���������
  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);
  info_rejestrator_dr.saving_execution = 1;
        
  //����������� ����� ������� ������
  part_writing_dr_into_dataflash = 0;
  //����������� ������� ������ � ��������� DataFlash
  control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR;
}
/*****************************************************/

/*****************************************************/
//������� ������� ����� ����������� ������ ����������� ����������
/*****************************************************/
inline void routine_for_queue_dr(void)
{
  if(
     (state_dr_record == STATE_DR_MAKE_RECORD)            || /*����� ����� ��������� ��� �������� �� ����� � DataFlsh ��� ���������� �������  ������ ������, �� ����� ���������� �����    ���������, � �� ������ ����� ����������� ���������� ������ ������������ ������*/
     (state_dr_record == STATE_DR_CUT_RECORD)             || /*����� ����� ��������� ��� �������� �� ����� � DataFlsh   � ���������  �������� ������ ������, �� ����� ���������� ����� �� ���������, �    ������ ����� ����������� ���������� ������ ������������ ������*/
     (number_records_dr_waiting_for_saving_operation != 0)  
    )
  {
    if ((control_tasks_dataflash & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR) == 0)
    {
      //�� ����� ������ ������ � Datafalsh �� �����������
      unsigned char *buffer_source, *buffer_target;
        
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++)
        {
          *(buffer_target + i) = *(buffer_source + i);
          *(buffer_source + i) = 0xff;
        }
        number_records_dr_waiting_for_saving_operation = 0;
      }
      else if (number_records_dr_waiting_for_saving_operation == 1)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target +i ) = *(buffer_source + i);
        
        if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
        {
          buffer_target = buffer_for_save_dr_record_level_1;
          buffer_source = buffer_for_save_dr_record;
          for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
          {
            *(buffer_target + i) = *(buffer_source + i);
            *(buffer_source + i) = 0xff;
          }
          number_records_dr_waiting_for_saving_operation = 1;
        }
        else number_records_dr_waiting_for_saving_operation = 0;
      }
      else
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target + i) = *(buffer_source + i);
        buffer_target = buffer_for_save_dr_record_level_1;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
        {
          *(buffer_target + i) = *(buffer_source + i);
          *(buffer_source + i) = 0xff;
        }
        number_records_dr_waiting_for_saving_operation = 1;
      }
        
      //������ ������� ������ ����� � DataFalsh
      command_start_saving_record_dr_into_dataflash();
    }
    else
    {
      //�� ����� ������ ������ � Datafalsh �����������
      //����� ��� �������� ����� ��������� � �����
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        //�� ����� ������ ��� ����, ������ - � ����� ��� ������������ ����� � DataFalsh, ����� ����� ������ � ���� ����
        //��������� ������� ����� � ����� buffer_for_save_dr_record_level_1
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
        {
          buffer_for_save_dr_record_level_1[i] = buffer_for_save_dr_record[i];
          buffer_for_save_dr_record[i] = 0xff;
        }
    
        //�������, �� ���� ����� ����� ������� ���� �� ������������ ����� � dataFalsh
        number_records_dr_waiting_for_saving_operation = 1;
      }
      else if (number_records_dr_waiting_for_saving_operation >= 1)
      {
         if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
         {
          //�� ����� ������ ��� ����, ������ - � ����� ��� ������������ ����� � DataFalsh, �� ���� ����������� ����� ����� � ����� buffer_for_save_dr_record_level_1
          /*
          ���� ����� ����� �������� � ����� ������ ����� buffer_for_save_dr_record, ��� �������� ������� ������. �� ������ � ����
          � ���� ���� ������ ������ ����� �����, �� ������ ��������� ������� ������ �����
          */
          number_records_dr_waiting_for_saving_operation = 2;
         }
      }
    }
    
    if (state_dr_record == STATE_DR_MAKE_RECORD)
    {
      //�������, �� �� ����� �������� ��������� �����
      state_dr_record = STATE_DR_NO_RECORD;
    }
    else if (state_dr_record == STATE_DR_CUT_RECORD)
    {
      //�������, �� ����� ��������� ��������� ����� �����
      state_dr_record = STATE_DR_FORCE_START_NEW_RECORD;
    }
      
  }
}
/*****************************************************/

/*****************************************************/
//������� ������� ����� ����������� ����������
/*****************************************************/
inline void digital_registrator(volatile unsigned int* carrent_active_functions)
{
  static unsigned int previous_active_functions[N_BIG];
  
  static unsigned int number_items_dr;
  static unsigned int number_changes_into_dr_record;
  static unsigned int time_from_start_record_dr;
  static unsigned int blocking_continue_monitoring_min_U;
  
  //�� �������� �������� ����� � ���� �������, ���� ��� ������ ���������� ������ ������
  if(state_dr_record == STATE_DR_EXECUTING_RECORD)
  {
    //���������� �� �� ������� �����, �� ������� ���� ������ �������� ������������ ������
    unsigned int temp_value_for_max_min_fix_measurement = (
                                                            number_max_phase_dr   + 
                                                            number_min_U_dr       +
                                                            number_max_U_dr       +
                                                            number_max_ZOP_dr
                                                          );
    if(temp_value_for_max_min_fix_measurement > MAX_NUMBER_FIX_MAX_MEASUREMENTS)
    {
      //����, ���������� �������� ���� �� ���� � ��������, ��� ���� ������, ������� ��������� ������ ����������� ����������
      fix_undefined_error_dr(carrent_active_functions);

      /*
      ������� ������ ������ ����������� ���������� � ����� ��������� �������� �������
      �� �� ������ ��� ����, ��� � ������� ����� ������ ������ ���� ����������� ��������� ������ ����������� ����������
      */
      _CLEAR_BIT(previous_active_functions, RANG_WORK_D_REJESTRATOR);
    }
    else
    {
      //���������� �� ����� ����� ������ ��������� ������������ ������ �����
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_PHASE_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_PHASE_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_PHASE_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_PHASE_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_PHASE_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_PHASE_SIGNALES_5) != 0) ||
         ((carrent_active_functions[6] & MASKA_MONITOTYNG_PHASE_SIGNALES_6) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) == 0)
        {
          //� ����� ������ ����� ��������� ������������� ������� ������
          temp_value_for_max_min_fix_measurement++;
        }
      }

      //���������� �� ����� ����� ������ ��������� �������� �������
      if (
          (blocking_continue_monitoring_min_U == 0) ||
          (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_BV) != 0)  
         )
      {
        if(
           ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMIN_SIGNALES_0) != 0) ||
           ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMIN_SIGNALES_1) != 0) ||
           ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMIN_SIGNALES_2) != 0) ||
           ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMIN_SIGNALES_3) != 0) ||
           ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMIN_SIGNALES_4) != 0) ||
           ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMIN_SIGNALES_5) != 0) ||
           ((carrent_active_functions[6] & MASKA_MONITOTYNG_UMIN_SIGNALES_6) != 0)
          )
        {
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) == 0)
          {
            //� ����� ������ ����� ��������� �������� ����� �������
            temp_value_for_max_min_fix_measurement++;
          }
        }
      }
      
      //���������� �� ����� ����� ������ ��������� ����������� �������
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMAX_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMAX_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMAX_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMAX_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMAX_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMAX_SIGNALES_5) != 0) ||
         ((carrent_active_functions[6] & MASKA_MONITOTYNG_UMAX_SIGNALES_6) != 0)
      )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) == 0)
        {
          //� ����� ������ ����� ��������� ����������� ����� �������
          temp_value_for_max_min_fix_measurement++;
        }
      }
      
      //���������� �� ����� ����� ������ ��������� ������������ ����� ��������� �����������
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_ZOP_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_ZOP_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_ZOP_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_ZOP_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_ZOP_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_ZOP_SIGNALES_5) != 0) ||
         ((carrent_active_functions[6] & MASKA_MONITOTYNG_ZOP_SIGNALES_6) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) == 0)
        {
          //� ����� ������ ����� ��������� ������������� ������ ���������� �����������
          temp_value_for_max_min_fix_measurement++;
        }
      }
    
      if(temp_value_for_max_min_fix_measurement > MAX_NUMBER_FIX_MAX_MEASUREMENTS)
      {
        //������� ��������, �� ������� ���� ������ �������� ������������ ���������
        //����� ��������� ��������� ������� ����� � ������ ��������� �����

        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_ITEMS_DR      ] = number_items_dr;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR    ] = number_changes_into_dr_record        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR + 1] = (number_changes_into_dr_record >> 8) & 0xff;

        //���������� �� ����� ��������� ��������� ������������� ������� ������
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE, carrent_active_functions);

        //���������� �� ����� ��������� ��������� �������� �������
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);

        //���������� �� ����� ��������� ��������� ����������� �������
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE, carrent_active_functions);

        //���������� �� ����� ��������� ��������� ������������� ������ ������� �����������
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP, carrent_active_functions);
        
        //������ 䳿 �������� ����� � ���� �������, ���� ������� end_monitoring_min_max_measurement �� ����������� ������� � �� ������� state_dr_record � STATE_DR_NO_RECORD
        if(state_dr_record != STATE_DR_NO_RECORD)
        {
          //�������� ������� ������������ ������������ ������ ��� ����
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_PHASE_DR  ] = number_max_phase_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MIN_U_DR      ] = number_min_U_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_U_DR      ] = number_max_U_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_ZOP_DR    ] = number_max_ZOP_dr;

          //�������, �� ����� ��� ������ �� ����� ������ ����� �����, �� ��������� ����� ��� ��������� ���������
          state_dr_record = STATE_DR_CUT_RECORD;
        
          //������� ������ ������ ����������� ����������
          _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
        
          //����������� ����� ������ � ����� ��� ������
          routine_for_queue_dr();
        }
        /*
        ������� ������ ������ ����������� ���������� � ����� ��������� �������� �������
        �� �� ������ ��� ����, ��� � ������� ����� ������ ������ ���� ����������� ��������� ������ ����������� ����������
        */
        _CLEAR_BIT(previous_active_functions, RANG_WORK_D_REJESTRATOR);
        
      }
    }
  }
  
  switch (state_dr_record)
  {
  case STATE_DR_NO_RECORD:
  case STATE_DR_FORCE_START_NEW_RECORD:
    {
      //���������� ������� ����������� �������  ������ ����������� ����������
      _SET_BIT(clear_diagnostyka, ERROR_DR_UNDEFINED_BIT);
      if(number_records_dr_waiting_for_saving_operation < (WIGHT_OF_DR_WAITING - 1))
      {
        //�� �������� ������, �� �� ����� �� ���� ����� ����� � ��� � ����� ���, ���� ������� ����������� ��� ������ �����
        _SET_BIT(clear_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
      }
      
      //�� ������� ������ ������ �� ���������� ��������� �� ���������
      
      //��������, �� ����� ����� ������� ����������� ����������
      if (
          (
           ((carrent_active_functions[0] & current_settings_prt.ranguvannja_digital_registrator[0]) != 0) ||
           ((carrent_active_functions[1] & current_settings_prt.ranguvannja_digital_registrator[1]) != 0) ||
           ((carrent_active_functions[2] & current_settings_prt.ranguvannja_digital_registrator[2]) != 0) ||
           ((carrent_active_functions[3] & current_settings_prt.ranguvannja_digital_registrator[3]) != 0) ||
           ((carrent_active_functions[4] & current_settings_prt.ranguvannja_digital_registrator[4]) != 0) ||
           ((carrent_active_functions[5] & current_settings_prt.ranguvannja_digital_registrator[5]) != 0) ||
           ((carrent_active_functions[6] & current_settings_prt.ranguvannja_digital_registrator[6]) != 0) ||
           (state_dr_record == STATE_DR_FORCE_START_NEW_RECORD)
          )   
         )
      {
        //� ����� ������� ����������� ����������
        
        //����������, �� ��� ������� ������ ������ �� �� �������� ��������� ����������
        if(number_records_dr_waiting_for_saving_operation < WIGHT_OF_DR_WAITING)
        {
          //����� �������� ����� �����
          
          //���������� ����� ������ �� ���������� ����������� � ���� "��� ������ ������ ����������"
          state_dr_record = STATE_DR_EXECUTING_RECORD;
          //����������� ������� �������
          _SET_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
        
          //�������� ���� ������� ������
          buffer_for_save_dr_record[FIRST_INDEX_START_START_RECORD_DR] = LABEL_START_RECORD_DR;
         
          //�������� ��� ������� ������
          unsigned char *label_to_time_array;
          if (copying_time == 0) label_to_time_array = time;
          else label_to_time_array = time_copy;
          for(unsigned int i = 0; i < 7; i++) buffer_for_save_dr_record[FIRST_INDEX_DATA_TIME_DR + i] = *(label_to_time_array + i);
          
           //�'�� ������
          for(unsigned int i=0; i< MAX_CHAR_IN_NAME_OF_CELL; i++) 
            buffer_for_save_dr_record[FIRST_INDEX_NAME_OF_CELL_DR + i] = current_settings_prt.name_of_cell[i] & 0xff;
          
          //������� ������ ���� ������� � ������� ������� ������
          time_from_start_record_dr = 0;
          
          //������� ������� �������� ������������ ������/������
          number_max_phase_dr = 0;
          number_min_U_dr = 0;
          number_max_U_dr = 0;
          number_max_ZOP_dr = 0;
          
          //������ ����������� ��� ��������� ������������ ������
          state_current_monitoring = 0;
          
          //���������� �� ����� ����� ��������� ������������ ������ �����
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_PHASE_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_PHASE_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_PHASE_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_PHASE_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_PHASE_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_PHASE_SIGNALES_5) != 0) ||
             ((carrent_active_functions[6] & MASKA_MONITOTYNG_PHASE_SIGNALES_6) != 0)
            )
          {
            start_monitoring_max_phase_current(time_from_start_record_dr);
          }

          //������ ���������� ���������� �������� �������
          blocking_continue_monitoring_min_U = 0;
          //���������� �� ����� ����� ��������� �������� �������
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMIN_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMIN_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMIN_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMIN_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMIN_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMIN_SIGNALES_5) != 0) ||
             ((carrent_active_functions[6] & MASKA_MONITOTYNG_UMIN_SIGNALES_6) != 0)
            )
          {
            start_monitoring_min_U(time_from_start_record_dr);
          }
          //����������, �� ����� ����� ��������� ��������� �������� ������� ���� ��������� ��������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
          {
            if (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_BO) != 0)
            {
              blocking_continue_monitoring_min_U = 0xff;
              end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);
            }
          }

          //���������� �� ����� ����� ��������� ����������� �������
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMAX_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMAX_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMAX_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMAX_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMAX_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMAX_SIGNALES_5) != 0) ||
             ((carrent_active_functions[6] & MASKA_MONITOTYNG_UMAX_SIGNALES_6) != 0)
            )
          {
            start_monitoring_max_U(time_from_start_record_dr);
          }

          //���������� �� ����� ����� ��������� ������������ ����� ��������� �����������
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_ZOP_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_ZOP_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_ZOP_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_ZOP_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_ZOP_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_ZOP_SIGNALES_5) != 0) ||
             ((carrent_active_functions[6] & MASKA_MONITOTYNG_ZOP_SIGNALES_6) != 0)
            )
          {
            start_monitoring_max_ZOP(time_from_start_record_dr);
          }
      
          //�������� ��������� c��� ������� ����� �����
          //̳��� ���� ������������ ����� ������� �� ������� ������� ������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  0] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  1] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  2] = 0xff;
          //��������� ����
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  3] =  previous_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  4] = (previous_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  5] = (previous_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  6] = (previous_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  7] =  previous_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  8] = (previous_active_functions[1] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  9] = (previous_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 10] = (previous_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 11] =  previous_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 12] = (previous_active_functions[2] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 13] = (previous_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 14] = (previous_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 15] =  previous_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 16] = (previous_active_functions[3] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 17] = (previous_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 18] = (previous_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 19] =  previous_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 20] = (previous_active_functions[4] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 21] = (previous_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 22] = (previous_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 23] =  previous_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 24] = (previous_active_functions[5] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 25] = (previous_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 26] = (previous_active_functions[5] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 27] =  previous_active_functions[6]        & 0xff;
          //����� ��������� � ��� ������� ������� ���
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 28] = 0;

          //������� ������� ����� ����
          number_items_dr = 1;
      
          //���������� ������� ��� �������
          number_changes_into_dr_record = 0;
          unsigned int number_changes_into_current_item;
          _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
          number_changes_into_dr_record += number_changes_into_current_item;
      
          //�������� ������� c��� �������
          //̳��� ����
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  0] =  time_from_start_record_dr        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  2] = (time_from_start_record_dr >> 16) & 0xff;
          //������� ���� �������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  3] =  carrent_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  4] = (carrent_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  5] = (carrent_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  6] = (carrent_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  7] =  carrent_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  8] = (carrent_active_functions[1] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  9] = (carrent_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 10] = (carrent_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 11] =  carrent_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 12] = (carrent_active_functions[2] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 13] = (carrent_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 14] = (carrent_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 15] =  carrent_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 16] = (carrent_active_functions[3] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 17] = (carrent_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 18] = (carrent_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 19] =  carrent_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 20] = (carrent_active_functions[4] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 21] = (carrent_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 22] = (carrent_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 23] =  carrent_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 24] = (carrent_active_functions[5] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 25] = (carrent_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 26] = (carrent_active_functions[5] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 27] =  carrent_active_functions[6]        & 0xff;
          
          //ʳ������ ��� ������� � �������� �� ��������� ������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 28] = number_changes_into_current_item & 0xff;
        }
        else
        {
          //����������� �������, �� � ����� �� ������ ����������� ���������� ���, �� �� ���� ������ ������
          _SET_BIT(set_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_DEFECT);
        }
      }
      else state_dr_record = STATE_DR_NO_RECORD;
      
      break;
    }
  case STATE_DR_EXECUTING_RECORD:
    {
      //�������� ��� � ������� ������� ������
      time_from_start_record_dr++;
      //������� �� ����� ���� ��� ������ ������

      //��������-�������� ������������ ���������� �������
      
      //���������� �� ����� ����� ��������� ������������ ������ �����
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_PHASE_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_PHASE_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_PHASE_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_PHASE_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_PHASE_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_PHASE_SIGNALES_5) != 0) ||
         ((carrent_active_functions[6] & MASKA_MONITOTYNG_PHASE_SIGNALES_6) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
          continue_monitoring_max_phase_current(time_from_start_record_dr);
        else
          start_monitoring_max_phase_current(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE, carrent_active_functions);
      }

      //���������� �� ����� ����� �������� ��������� �������� �������
      if (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_BV) != 0)
      {
        //������ ���������� ���������� �������� �������
        blocking_continue_monitoring_min_U = 0;
      }
      //���������� �� ����� ����� ��������� �������� �������
      if (blocking_continue_monitoring_min_U == 0)
      {
        if(
           ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMIN_SIGNALES_0) != 0) ||
           ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMIN_SIGNALES_1) != 0) ||
           ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMIN_SIGNALES_2) != 0) ||
           ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMIN_SIGNALES_3) != 0) ||
           ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMIN_SIGNALES_4) != 0) ||
           ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMIN_SIGNALES_5) != 0) ||
           ((carrent_active_functions[6] & MASKA_MONITOTYNG_UMIN_SIGNALES_6) != 0)
          )
        {
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
            continue_monitoring_min_U(time_from_start_record_dr);
          else
            start_monitoring_min_U(time_from_start_record_dr);
        }
        else
        {
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);
        }
      }
      //����������, �� ����� ����� ��������� ��������� �������� ������� ���� ��������� ��������
      if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
      {
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_BO) != 0)
        {
          blocking_continue_monitoring_min_U = 0xff;
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);
        }
      }
      
      //���������� �� ����� ����� ��������� ����������� �������
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMAX_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMAX_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMAX_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMAX_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMAX_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMAX_SIGNALES_5) != 0) ||
         ((carrent_active_functions[6] & MASKA_MONITOTYNG_UMAX_SIGNALES_6) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
          continue_monitoring_max_U(time_from_start_record_dr);
        else
          start_monitoring_max_U(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE, carrent_active_functions);
      }
      
      //���������� �� ����� ����� ��������� ������������ ����� ��������� �����������
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_ZOP_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_ZOP_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_ZOP_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_ZOP_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_ZOP_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_ZOP_SIGNALES_5) != 0) ||
         ((carrent_active_functions[6] & MASKA_MONITOTYNG_ZOP_SIGNALES_6) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
          continue_monitoring_max_ZOP(time_from_start_record_dr);
        else
          start_monitoring_max_ZOP(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP, carrent_active_functions);
      }
      
      //������ 䳿 �������� ����� � ���� �������, ���� ������� end_monitoring_min_max_measurement �� ����������� ������� � �� ������� state_dr_record � STATE_DR_NO_RECORD
      if(state_dr_record != STATE_DR_NO_RECORD)
      {
        //����������, �� �� ���� ����� ����������� ������
        //���� ���� ����� ���� - �� ������� ������ ���������� ����������� ����������, �� �� ����������� � ������� ��������
        if (stop_regisrator(carrent_active_functions, current_settings_prt.ranguvannja_digital_registrator) != 0)
        {
          //������� ������ ������ ����������� ����������
          _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);

          //���������� ����� ������ �� ���������� ����������� � ���� "���������� ������������ ����� � ��������� DataFlash"
          state_dr_record = STATE_DR_MAKE_RECORD;
        }
      
        //���������� �� �������� ���� ������� � �������� �� ��������� ������. ���� ���� ���� �, �� ������ ����� ��� ������� � �����
        if (
            ((carrent_active_functions[0] != previous_active_functions[0])) ||
            ((carrent_active_functions[1] != previous_active_functions[1])) ||
            ((carrent_active_functions[2] != previous_active_functions[2])) ||
            ((carrent_active_functions[3] != previous_active_functions[3])) ||
            ((carrent_active_functions[4] != previous_active_functions[4])) ||
            ((carrent_active_functions[5] != previous_active_functions[5])) ||
            ((carrent_active_functions[6] != previous_active_functions[6]))
           )
        {
          //�������� ���� ������� �� ������� � ��������� ������ �������

          //�������� �� ���� ������� ����� ����
          number_items_dr++;
      
          //���������� ������� ��� �������
          unsigned int number_changes_into_current_item;
          _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
          number_changes_into_dr_record += number_changes_into_current_item;
      
          //�������� ������� c��� �������
          //̳��� ����
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  0] =  time_from_start_record_dr        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  2] = (time_from_start_record_dr >> 16) & 0xff;
          //������� ���� �������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  3] =  carrent_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  4] = (carrent_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  5] = (carrent_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  6] = (carrent_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  7] =  carrent_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  8] = (carrent_active_functions[1] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 +  9] = (carrent_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 10] = (carrent_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 11] =  carrent_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 12] = (carrent_active_functions[2] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 13] = (carrent_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 14] = (carrent_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 15] =  carrent_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 16] = (carrent_active_functions[3] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 17] = (carrent_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 18] = (carrent_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 19] =  carrent_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 20] = (carrent_active_functions[4] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 21] = (carrent_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 22] = (carrent_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 23] =  carrent_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 24] = (carrent_active_functions[5] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 25] = (carrent_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 26] = (carrent_active_functions[5] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 27] =  carrent_active_functions[6]        & 0xff;

          //ʳ������ ��� ������� � �������� �� ��������� ������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*29 + 28] = number_changes_into_current_item & 0xff;
        }
        
        //����������, �� ����� ����� ���������� ������
        if (
            (state_dr_record == STATE_DR_MAKE_RECORD)                  ||
            (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)  ||  
            ((number_items_dr + 1)     >= MAX_EVENTS_IN_ONE_RECORD  )  
           )
        {
          //���� ����� ����������� ������, ��� � ����� ���������� ������ - ��������� ���������� ������ � ������ ������� �� �����
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_ITEMS_DR      ] = number_items_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR    ] =  number_changes_into_dr_record       & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR + 1] = (number_changes_into_dr_record >> 8) & 0xff;

          //���������� �� ����� ��������� ��������� ������������� ������� ������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE, carrent_active_functions);

          //���������� �� ����� ��������� ��������� �������� �������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);

          //���������� �� ����� ��������� ��������� ����������� �������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE, carrent_active_functions);

          //���������� �� ����� ��������� ��������� ������������� ������ �����������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP, carrent_active_functions);
        
          //������ 䳿 �������� ����� � ���� �������, ���� ������� end_monitoring_min_max_measurement �� ����������� ������� � �� ������� state_dr_record � STATE_DR_NO_RECORD
          if(state_dr_record != STATE_DR_NO_RECORD)
          {
            //�������� ������� ������������ ������������ ��������� ��� ����
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_PHASE_DR  ] = number_max_phase_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MIN_U_DR      ] = number_min_U_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_U_DR      ] = number_max_U_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_ZOP_DR    ] = number_max_ZOP_dr;

            //���������� ����� ������ �� ���������� ����������� � ���� "���������� ������������ ����� � DataFlash"
            if (state_dr_record != STATE_DR_MAKE_RECORD)
            {
              if (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)
              {
                //���� �������� ����������� �� ���� ������, �� ������ ������� ��������� ����� ��� ����������� ���� ����� ������ � ���������� �����
                state_dr_record = STATE_DR_MAKE_RECORD;
              }
              else
              {
                //���� �������� ����������� �� ��������� ����������� ������� ���� (��� ���� �������, ��� ������ �� ���������, ��� ���� �'������� � �����������), �� ������ ������� ��������� ����� ��� �� ���������� ������ ������ ����� �����
                state_dr_record = STATE_DR_CUT_RECORD;
              }
            }
          }
        
          //������� ������ ������ ����������� ����������
          _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
        }
      }

      break;
    }
  default:
    {
      //�� ��� ���� �������� ����� �� ���� � �����
      fix_undefined_error_dr(carrent_active_functions);
      break;
    }
  }
  
  //����������, �� ����� ����� ����������� ����� �������� �� ����� � DataFlash
  routine_for_queue_dr();

  /*********************/
  //������� ���������� ���� ������� ��� ������� ���������/���������
  /*********************/
  for (unsigned int i = 0; i < N_BIG; i++) previous_active_functions[i] = carrent_active_functions[i];
  /*********************/
}
/*****************************************************/

/*****************************************************/
//����������� ����������� ������� ������ ����������� ����������
/*****************************************************/
void fix_undefined_error_ar(volatile unsigned int* carrent_active_functions)
{
  //����������� ������� � ������� � ��������� ���������
  _SET_BIT(set_diagnostyka, ERROR_AR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_DEFECT);
  //���������� ����� ������ � ����������� � ���� "�� ����� ������ ���� �� � ���������� ����������� �� ����������" 
  continue_previous_record_ar = 0; /*�������, �� �� �� ������ ����������� ��� ������ ��������� ����������� ����������*/
  state_ar_record = STATE_AR_NO_RECORD;
  //������� ������ ������ ����������� ����������
  _CLEAR_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);

  //����������� ������� ������ ��������� ��� ����������� ���������� � EEPROM
  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
  //³��������� ������������ ��������� ��� ����������� ����������
  /*
  ������ �������� ���������, ����� ���� ��� � ����
  */
  info_rejestrator_ar.saving_execution = 0;
  /*
  ������� ������ ������ ����� ������ ������ ��������, � �� �������, ��, ���� ��� ���� ������ ���
  ������� ������, �� ���� �������. ���� ����� �������, �� ���� � ����������� ��������� �� ����� ���� ����
  ����������� ������� ������� ������, �� ����� ������� � ��� � ���������, ����� ������� ������ ����� 
  � ������ ������� �� ������� �����
  */
  unsigned int max_number_records_ar_tmp = max_number_records_ar;
  if (info_rejestrator_ar.number_records >= max_number_records_ar_tmp) 
    info_rejestrator_ar.number_records = max_number_records_ar_tmp - 1; /*����� ��� �� ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/
}
/*****************************************************/

/*****************************************************/
//������� ������� ����� ����������� ����������
/*****************************************************/
inline void analog_registrator(volatile unsigned int* carrent_active_functions)
{
  static unsigned int unsaved_bytes_of_header_ar;

  //���������� ������� ����������� �������  ������ ����������� ����������
  _SET_BIT(clear_diagnostyka, ERROR_AR_UNDEFINED_BIT);

  if (continue_previous_record_ar != 0)
  {
    /*
    �� �������� ������, �� ���� ��������� ������� ����������� ����������, �� ���������
    � ������ ���������� ���������, � ����� ��� ������������� ��������� ��������� ����� ����� �� 
    ������ ��������, �� �� ������� ��������� ������������� (� ����-���� ��� �� ��
    ���������� ����������� �������� ������ ����������� ����������, �� ��� ���� ����������
    �����������. �� ���� ������ ������������� ��������� ������ ������ ������)
    */
    if(
       ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) == 0) &&
       ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) == 0) &&
       ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) == 0) &&
       ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) == 0) &&
       ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) == 0) &&
       ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) == 0) &&
       ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) == 0)
      ) 
    {
      //����� ������������� ��������� ������� ������ ������ ��������
      continue_previous_record_ar = 0;
    }
  }

  switch (state_ar_record)
  {
  case STATE_AR_NO_RECORD:
    {
      if(semaphore_read_state_ar_record == 0)
      {
        /*
        ������� ���� ��������, �� ��� ��������� ����� ������ ����������� ���������� ���������� ���������� ������ ���������� ����������
        ������ ������� semaphore_read_state_ar_record ��� ����, �� ���� ������ ����������� ���������� STATE_AR_NO_RECORD ������,
        �� ����� ���� �������� �� ���� ������, ���� ������ ���������� ������� ���� ��� ��������� ����������� ������ ����������� ����������
        */
        _SET_BIT(clear_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
      }

      //��������, �� ����� ����� ������� ����������� ����������
      if (
          (
           ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
           ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
           ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
           ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
           ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
           ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0) ||
           ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) != 0)
          )
          &&  
          (continue_previous_record_ar == 0) /*��� ��������� ����� ��.���������� (���� ���� ����) ��� �� ������� ��������� ���� ���� � ����� ���� ����� �������*/ 
         )
      {
        //����������, �� ��� ������� ������ ������ � ��� �� ��� ������ �������������� ���������� ���������
        if(semaphore_read_state_ar_record == 0)
        {
          //� ����� ������� ����������� ����������
          continue_previous_record_ar = 0xff; /*������� ����-���� ������, �� ������������ �������� ��.����������, �� ��������� ������ ����������� ����������*/
    
          //����� �������� ����� �����
          
          //�������� ���� ������� ������
          header_ar.label_start_record = LABEL_START_RECORD_AR;
          //�������� ��� ������� ������
          unsigned char *label_to_time_array;
          if (copying_time == 0) label_to_time_array = time;
          else label_to_time_array = time_copy;
          for(unsigned int i = 0; i < 7; i++) header_ar.time[i] = *(label_to_time_array + i);
          //���������� ������������� TT
          header_ar.TCurrent = current_settings_prt.TCurrent;
          //���������� ������������� T�
          header_ar.TVoltage = current_settings_prt.TVoltage;
          //�'�� ������
          for(unsigned int i=0; i<MAX_CHAR_IN_NAME_OF_CELL; i++)
            header_ar.name_of_cell[i] = current_settings_prt.name_of_cell[i] & 0xff;
          
          //�������, �� �� �� �� �� "��������" ����� �������� � ����� ��� ����������� ����������
          copied_number_samples = 0;
          //��������� �������� ������� ������� �������, �� ����� ���� ������� � ��������� dataFlash2
          total_number_samples = ((current_settings_prt.prefault_number_periods + current_settings_prt.postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar);

          //���������,�� ������ ��������� ����������� ���������� �� ����������� � ����� ����� ������ ��� ����������� ��� ��� ������ � DataFlash
          unsaved_bytes_of_header_ar = sizeof(__HEADER_AR);

          //��������� � ��� ������ ����������
          temporary_address_ar = info_rejestrator_ar.next_address;

          //���������, �� ���� �� ���� ������������ ����� ��� ������
          count_to_save = 0;
          //����������� ����-���� ���������� ������ ����� �� ��������� ����� ����� ��� ������
          permit_copy_new_data = 0xff;

          //����� ������ ������������ ��� ������� ��������� ����������� ����������� � ������������ ����� � ����� ��� ������ � DataFlash
          if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
          {
            //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
            fix_undefined_error_ar(carrent_active_functions);
          }
          else
          {
            //���������� ����� ������ �� ���������� ����������� � ���� "����� ������ ������"
            state_ar_record = STATE_AR_START;
            //����������� ������� �������
            _SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);

            //� �������� �� ���������� ����� ���������� ����������� �����������, �� ������� ����� � �� �� ���������
            _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            info_rejestrator_ar.saving_execution = 1;
          }
        }
        else
        {
          //����������� �������, �� ��������� ���������� ��������� � ������� (���� ��, �� ��� �������� ������ ����� ��������)
          _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_DEFECT);
        }
      }
      break;
    }
  case STATE_AR_START:
    {
      //ͳ���� �� �� ��������, ���� �� ����������� ����� STATE_AR_SAVE_SRAM_AND_SAVE_FLASH,  ��� STATE_AR_ONLY_SAVE_FLASH
      break;
    }
  case STATE_AR_SAVE_SRAM_AND_SAVE_FLASH:
  case STATE_AR_ONLY_SAVE_FLASH:
    {
      if (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)
      {
        /*
        ���� ������������ ����� ������������ �� ������
        */
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR) != 0)
        {
          //������ ������ ������ ����������� ����������
          _CLEAR_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);
        }
        
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR) == 0)
        {
          /*
          ��������� ����� ��� ������, ���� ������ ������� ������ ����������� ����������� ��� ������
          */
          if  (continue_previous_record_ar == 0)
          {
            /*
            ����������, �� ���� ����� ������� ������ ������� �� �������, 
            ���� �� ������ ����� �� ��������� �������
            */
            if (
                ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
                ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
                ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
                ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
                ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
                ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0) ||
                ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) != 0)
               ) 
            {
              //����������� �������, �� ��������� ���������� ��������� � ������� (���� ��, �� ����������� ��������� �����)
              _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
              _SET_BIT(carrent_active_functions, RANG_DEFECT);
            }
          }
        }
      }
      
      if (permit_copy_new_data != 0)
      {
        /*
        ����� ������ ������������ ��� ������� ��������� ����������� ����������� 
        � ������������ ����� � ����� ��� ������ � DataFlash ����� ���, ���� � �����
        �� �� ��������
        */
        if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
        {
          //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
          fix_undefined_error_ar(carrent_active_functions);
        }
      }
      else
      {
        if (
            (copied_number_samples == total_number_samples) &&
            (count_to_save == 0                           ) && 
            (
             (control_tasks_dataflash &
              (
               TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR | 
               TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR
              )
             ) == 0
            )   
           )
        {
          //����� ������� ������ ������������ ����������
          unsigned int index_array_ar_heat_tmp = index_array_ar_heat;/*�� ����� ��� ����, �� ��������� ���� ����������� ��� �������� ������ � ��������� volatile*/
          unsigned int index_array_ar_tail_tmp = index_array_ar_tail;/*�� ����� ��� ����, �� ��������� ���� ����������� ��� �������� ������ � ��������� volatile*/
          if(
             (index_array_ar_tail_tmp == index_array_ar_heat_tmp) &&
             (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)  
            )  
          {
            //�������� ����� ������� ������ ����������� ����������
            state_ar_record = STATE_AR_NO_RECORD;

            //����������� ������� ������ ��������� ����������� ���������� � EEPROM
            _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            //��������� ���� ������ ���������� ������, ���� ������� ������ � ������ �����������, �� ����� ��� �����
            if ((temporary_address_ar + size_one_ar_record) > (NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2))
              temporary_address_ar = 0; 
            info_rejestrator_ar.next_address = temporary_address_ar;
            info_rejestrator_ar.saving_execution = 0;
            unsigned int max_number_records_ar_tmp = max_number_records_ar;
            if (info_rejestrator_ar.number_records < max_number_records_ar_tmp) info_rejestrator_ar.number_records += 1;
            else info_rejestrator_ar.number_records = max_number_records_ar_tmp;
          }
          else
          {
            /*� ������ ������ ����������� ���������� ������� ���, ���� �����
            �� ����������������� ���������� ������ ����������� ����������
            
            �� ������ ������ ������� �������� ����, �� �� ��������� ����������
            ����������� ������� ����������� ������� �������
            */
            fix_undefined_error_ar(carrent_active_functions);
          }
        }
        else
        {
          //����� ������ ������� �� ����� ������������ �����
          if (
              (count_to_save != 0 ) 
              && 
              (
               (control_tasks_dataflash &
                (
                 TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR | 
                 TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR
                )
               ) == 0
              )   
             )
          {
            /*
            ������ ������� �� ����� ����� ����� ����� ��� ���� �� ��� ����� �����
            ���������� ����������� ����� � ���� � ��� ��� ��� ������
            */
            
            if (((temporary_address_ar & 0x1ff) + count_to_save) <= SIZE_PAGE_DATAFLASH_2)
            {
              //���� ������� ��� ��������� ������� ���� ��� ������ (� ���� ������� ��� ���������� � ������ ������)
              
              if (count_to_save == SIZE_PAGE_DATAFLASH_2) control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
              else control_tasks_dataflash |= TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
            }
            else
            {
              //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
              fix_undefined_error_ar(carrent_active_functions);
            }
          }
        }

      }
      break;
    }
  case STATE_AR_TEMPORARY_BLOCK:
    {
      //�� ����� ������ ���� ������� �������� �������� ������ ����������� �����������
      //��������, �� ����� ����� ������� ����������� ����������
      if (
          ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
          ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
          ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
          ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
          ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
          ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0) ||
          ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) != 0)
         )
      {
        //����������� �������, �� ��������� ���������� ��������� � �������
        _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
        _SET_BIT(carrent_active_functions, RANG_DEFECT);
      }
      break;
    }
  default:
    {
      //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
      fix_undefined_error_ar(carrent_active_functions);
      break;
    }
  }
}
/*****************************************************/


/*****************************************************/
//������� ������� � ��� ����������� �� ���� ��������
/*****************************************************/
inline void main_protection(void)
{
  copying_active_functions = 1; //�������, �� ����� ���������� �������� �������� �������
  
  //������� � �������, �� ���������� �� �����, ������� � ��������� � ����������
  const unsigned int maska_input_signals[N_BIG] = 
  {
    MASKA_FOR_INPUT_SIGNALS_0, 
    MASKA_FOR_INPUT_SIGNALS_1, 
    MASKA_FOR_INPUT_SIGNALS_2, 
    MASKA_FOR_INPUT_SIGNALS_3, 
    MASKA_FOR_INPUT_SIGNALS_4, 
    MASKA_FOR_INPUT_SIGNALS_5, 
    MASKA_FOR_INPUT_SIGNALS_6 
  };
  for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_input_signals[i]);
  
  /**************************/
  //��������, �� ����� �������� ������ �������
  /**************************/
  if (reset_trigger_function_from_interface !=0)
  {
    if ((reset_trigger_function_from_interface & (1 << USB_RECUEST)) != 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++) trigger_functions_USB[i] = 0;
      
      information_about_restart_counter  &= (unsigned int)(~(1 << USB_RECUEST));
      information_about_clean_energy     &= (unsigned int)(~(1 << USB_RECUEST));
    }
    if ((reset_trigger_function_from_interface & (1 << RS485_RECUEST)) != 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++) trigger_functions_RS485[i] = 0;
      
      information_about_restart_counter  &= (unsigned int)(~(1 << RS485_RECUEST));
      information_about_clean_energy     &= (unsigned int)(~(1 << RS485_RECUEST));
    }
    
    //������� �� �� �������� ������� �� �Ѳ� �����������
    reset_trigger_function_from_interface = 0;
  }
  /**************************/

  /**************************/
  //����������� �������� ������ - ����� ��������������� ����������, �� ��� ��� ����� �� ������������ ���������� ������� � ������
  /**************************/
  if ((pressed_buttons !=0) || (activation_function_from_interface != 0))
  {
    unsigned int temp_value_for_activated_function = 0;
    
    //��������� � �������
    if (pressed_buttons != 0)
    {
      for (unsigned int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        if ((pressed_buttons & (1 << i)) != 0)
          temp_value_for_activated_function |= current_settings_prt.ranguvannja_buttons[i];
      }

      //������� �������� ������, �� �� ��� ����������
      pressed_buttons =0;
    }
    
    //��������� � ����������
    if (activation_function_from_interface != 0)
    {
      temp_value_for_activated_function |= activation_function_from_interface;
      
      //������� ������ ��������� ������� � ���������, �� �� ��� ����������
      activation_function_from_interface = 0;
    }
    
    //����  ������� �������������� ����� ������ �� ���������� �� � ���������� ����� �������, �� ����� ���� ����� ���������
    if(temp_value_for_activated_function != 0) 
    {
      //���������� �������
      for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        unsigned int tmp_state_df = 0;
        switch (i)
        {
        case 0:
          {
            tmp_state_df = _GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DF1_IN);
            if (tmp_state_df) 
              _SET_BIT(active_functions, RANG_DF1_IN);

            break;
          }
        case 1:
          {
            tmp_state_df = _GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DF2_IN);
            if (tmp_state_df) 
              _SET_BIT(active_functions, RANG_DF2_IN);

            break;
          }
        case 2:
          {
            tmp_state_df = _GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DF3_IN);
            if (tmp_state_df) 
              _SET_BIT(active_functions, RANG_DF3_IN);

            break;
          }
        case 3:
          {
            tmp_state_df = _GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DF4_IN);
            if (tmp_state_df) 
              _SET_BIT(active_functions, RANG_DF4_IN);

            break;
          }
        case 4:
          {
            tmp_state_df = _GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DF5_IN);
            if (tmp_state_df) 
              _SET_BIT(active_functions, RANG_DF5_IN);

            break;
          }
        case 5:
          {
            tmp_state_df = _GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DF6_IN);
            if (tmp_state_df) 
              _SET_BIT(active_functions, RANG_DF6_IN);

            break;
          }
        case 6:
          {
            tmp_state_df = _GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DF7_IN);
            if (tmp_state_df) 
              _SET_BIT(active_functions, RANG_DF7_IN);

            break;
          }
        case 7:
          {
            tmp_state_df = _GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DF8_IN);
            if (tmp_state_df) 
              _SET_BIT(active_functions, RANG_DF8_IN);

            break;
          }
        default: break;
        }
        
        if (tmp_state_df != 0)
        {
          //����� �� ������������ ��x, ���� ����� ��������� ������ �� �����������,
          //��� ����, ��� ���� ��� ��� ����� ���� ������� � ����� ������� �����
          if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] <0)
          {
            //��������� ������ ������ ����������� ���� ������� � ��������� ���� (������� ��������� �����)
            //������ ������ ����� �� ���� ��������, ���� �� �� �� �������
            global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = 0;
          }
        }
        
      }
      
      //���������� ������
      for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        switch (i)
        {
        case 0:
          {
            if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DT1_SET)) 
              _SET_BIT(active_functions, RANG_DT1_SET);
            if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DT1_RESET)) 
              _SET_BIT(active_functions, RANG_DT1_RESET);

            break;
          }
        case 1:
          {
            if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DT2_SET)) 
              _SET_BIT(active_functions, RANG_DT2_SET);
            if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DT2_RESET)) 
              _SET_BIT(active_functions, RANG_DT2_RESET);

            break;
          }
        case 2:
          {
            if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DT3_SET)) 
              _SET_BIT(active_functions, RANG_DT3_SET);
            if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DT3_RESET)) 
              _SET_BIT(active_functions, RANG_DT3_RESET);

            break;
          }
        case 3:
          {
            if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DT4_SET)) 
              _SET_BIT(active_functions, RANG_DT4_SET);
            if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_DT4_RESET)) 
              _SET_BIT(active_functions, RANG_DT4_RESET);

            break;
          }
        default: break;
        }
      }
      
      //�������� ��������� � ����
      if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_RESET_LEDS)) 
        _SET_BIT(active_functions, RANG_RESET_LEDS);
      if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_RESET_RELES)) 
        _SET_BIT(active_functions, RANG_RESET_RELES);

      //"̳�����/�����������" ���������
      if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_MISCEVE_DYSTANCIJNE))
      {
        //���������� ������� � ������������� ������ "̳�����/�����������"
        misceve_dystancijne = (misceve_dystancijne ^ 0x1) & 0x1;
        //����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� �������� ���������� ������ � ��������� ��������������
        _SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
      }
      
      //���������-���������� ��������
      if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_VKL_VV)) 
        _SET_BIT(active_functions, RANG_VKL_VV);
      if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_OTKL_VV)) 
        _SET_BIT(active_functions, RANG_OTKL_VV);

      //�������� ���������� ��������� �� ��
      if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV)) 
        _SET_BIT(active_functions, RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV);

      //������� ���
        if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_OTKL_AVR)) 
          _SET_BIT(active_functions, RANG_OTKL_AVR);
        if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_BUTTON_SBROS_BLOCK_AVR)) 
          _SET_BIT(active_functions, RANG_SBROS_BLOCK_AVR);
    }
  }
  /**************************/

  //"̳��./�������."  � �������������� ������ ����
  active_functions[RANG_MISCEVE_DYSTANCIJNE >> 5] |= (misceve_dystancijne & 0x1) << (RANG_MISCEVE_DYSTANCIJNE & 0x1f);

  unsigned int blocking_commands_from_DI = 0;
  unsigned int active_inputs_grupa_ustavok = 0;
  /**************************/
  //����������� �������� �����
  /**************************/
  //���������� �� � ����� ������ �����
  if (active_inputs !=0)
  {
    //� ����� ������
    unsigned int temp_value_for_activated_function_2[N_SMALL] = {0,0};
    for (unsigned int i = 0; i < NUMBER_INPUTS; i++)
    {
      if ((active_inputs & (1 << i)) != 0)
      {
        temp_value_for_activated_function_2[0] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i  ];
        temp_value_for_activated_function_2[1] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i+1];
      }
    }
    
    //����  ������� �������������� ����� �� �� ���������� �� � ���������� ����� �������, �� ����� ���� ����� ���������
    if(
       (temp_value_for_activated_function_2[0] != 0) ||
       (temp_value_for_activated_function_2[1] != 0)
      ) 
    {
      //���������� �������
      for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        switch (i)
        {
        case 0:
          {
            active_functions[RANG_DF1_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF1_IN) != 0) << (RANG_DF1_IN & 0x1f);
            break;
          }
        case 1:
          {
            active_functions[RANG_DF2_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF2_IN) != 0) << (RANG_DF2_IN & 0x1f);
            break;
          }
        case 2:
          {
            active_functions[RANG_DF3_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF3_IN) != 0) << (RANG_DF3_IN & 0x1f);
            break;
          }
        case 3:
          {
            active_functions[RANG_DF4_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF4_IN) != 0) << (RANG_DF4_IN & 0x1f);
            break;
          }
        case 4:
          {
            active_functions[RANG_DF5_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF5_IN) != 0) << (RANG_DF5_IN & 0x1f);
            break;
          }
        case 5:
          {
            active_functions[RANG_DF6_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF6_IN) != 0) << (RANG_DF6_IN & 0x1f);
            break;
          }
        case 6:
          {
            active_functions[RANG_DF7_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF7_IN) != 0) << (RANG_DF7_IN & 0x1f);
            break;
          }
        case 7:
          {
            active_functions[RANG_DF8_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF8_IN) != 0) << (RANG_DF8_IN & 0x1f);
            break;
          }
        default: break;
        }
      }

      //���������� ������
      for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        switch (i)
        {
        case 0:
          {
            active_functions[RANG_DT1_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT1_SET  ) != 0) << (RANG_DT1_SET   & 0x1f);
            active_functions[RANG_DT1_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT1_RESET) != 0) << (RANG_DT1_RESET & 0x1f);
            break;
          }
        case 1:
          {
            active_functions[RANG_DT2_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT2_SET  ) != 0) << (RANG_DT2_SET   & 0x1f);
            active_functions[RANG_DT2_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT2_RESET) != 0) << (RANG_DT2_RESET & 0x1f);
            break;
          }
        case 2:
          {
            active_functions[RANG_DT3_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT3_SET  ) != 0) << (RANG_DT3_SET   & 0x1f);
            active_functions[RANG_DT3_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT3_RESET) != 0) << (RANG_DT3_RESET & 0x1f);
            break;
          }
        case 3:
          {
            active_functions[RANG_DT4_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT4_SET  ) != 0) << (RANG_DT4_SET   & 0x1f);
            active_functions[RANG_DT4_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT4_RESET) != 0) << (RANG_DT4_RESET & 0x1f);
            break;
          }
        default: break;
        }
      }
      
      //������� ������� (��� ��-�� � �������, �� ������ ����������� � �������� ��������)
      active_functions[RANG_BLOCK_VKL_VV                      >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_VKL_VV                     ) != 0) << (RANG_BLOCK_VKL_VV                      & 0x1f);
      active_functions[RANG_RESET_LEDS                        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_RESET_LEDS                       ) != 0) << (RANG_RESET_LEDS                        & 0x1f);
      active_functions[RANG_RESET_RELES                       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_RESET_RELES                      ) != 0) << (RANG_RESET_RELES                       & 0x1f);
      active_functions[RANG_MISCEVE_DYSTANCIJNE               >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_MISCEVE_DYSTANCIJNE              ) != 0) << (RANG_MISCEVE_DYSTANCIJNE               & 0x1f);
      active_functions[RANG_STATE_VV                          >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_STATE_VV                         ) != 0) << (RANG_STATE_VV                          & 0x1f);
      active_functions[RANG_PUSK_K1_AVR                       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_PUSK_K1_AVR                      ) != 0) << (RANG_PUSK_K1_AVR                       & 0x1f);
      active_functions[RANG_PUSK_K2_AVR                       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_PUSK_K2_AVR                      ) != 0) << (RANG_PUSK_K2_AVR                       & 0x1f);
      active_functions[RANG_CTRL_VKL                          >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_CTRL_VKL                         ) != 0) << (RANG_CTRL_VKL                          & 0x1f);
      active_functions[RANG_CTRL_OTKL                         >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_CTRL_OTKL                        ) != 0) << (RANG_CTRL_OTKL                         & 0x1f);
      active_functions[RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) != 0) << (RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV & 0x1f);
      active_functions[RANG_OTKL_VID_ZOVN_ZAHYSTIV            >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_OTKL_VID_ZOVN_ZAHYSTIV           ) != 0) << (RANG_OTKL_VID_ZOVN_ZAHYSTIV            & 0x1f);

      active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_1_GRUPA_USTAVOK    ) != 0) << (RANG_INPUT_1_GRUPA_USTAVOK - RANG_INPUT_1_GRUPA_USTAVOK);
      active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_2_GRUPA_USTAVOK    ) != 0) << (RANG_INPUT_2_GRUPA_USTAVOK - RANG_INPUT_1_GRUPA_USTAVOK);
      active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_3_GRUPA_USTAVOK    ) != 0) << (RANG_INPUT_3_GRUPA_USTAVOK - RANG_INPUT_1_GRUPA_USTAVOK);
      active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_4_GRUPA_USTAVOK    ) != 0) << (RANG_INPUT_4_GRUPA_USTAVOK - RANG_INPUT_1_GRUPA_USTAVOK);
      
      //������� ������� (�� ����������� � �������� ��������)
      //��������� ��
      if (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_VKL_VV ))
      {
        if (
            (_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE )) &&
            (current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE)
           ) 
        {
          //����� ���������� �������� "��������� ��" �� ���.
          blocking_commands_from_DI |= CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE;
        }
        else _SET_BIT(active_functions, RANG_VKL_VV);
      }
      if (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_OTKL_VV ))
      {
        if (
            (_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE )) &&
            (current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE)
           ) 
        {
          //����� ���������� �������� "��������� ��" �� ���.
          blocking_commands_from_DI |= CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE;
        }
        else _SET_BIT(active_functions, RANG_OTKL_VV);
      }

      //���� ��� ���
      active_functions[RANG_BLOCK_MTZ1     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ1    ) != 0) << (RANG_BLOCK_MTZ1     & 0x1f);
      active_functions[RANG_BLOCK_MTZ2     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ2    ) != 0) << (RANG_BLOCK_MTZ2     & 0x1f);
      active_functions[RANG_BLOCK_USK_MTZ2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_USK_MTZ2) != 0) << (RANG_BLOCK_USK_MTZ2 & 0x1f);
      active_functions[RANG_BLOCK_MTZ3     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ3    ) != 0) << (RANG_BLOCK_MTZ3     & 0x1f);
      active_functions[RANG_BLOCK_USK_MTZ3 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_USK_MTZ3) != 0) << (RANG_BLOCK_USK_MTZ3 & 0x1f);
      active_functions[RANG_BLOCK_MTZ4     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ4    ) != 0) << (RANG_BLOCK_MTZ4     & 0x1f);

      //���� ��� ���
      active_functions[RANG_PUSK_ZDZ_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_PUSK_ZDZ_VID_DV) != 0) << (RANG_PUSK_ZDZ_VID_DV & 0x1f);

      //���� ���
      active_functions[RANG_STAT_BLK_APV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_STAT_BLK_APV) != 0) << (RANG_STAT_BLK_APV & 0x1f);
      
      //����
//      active_functions[RANG_ACHR_CHAPV_VID_DV  >> 5] |=(_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_ACHR_CHAPV_VID_DV ) != 0) << (RANG_ACHR_CHAPV_VID_DV & 0x1f);

      //���� ��� ����
      active_functions[RANG_PUSK_UROV_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_PUSK_UROV_VID_DV) != 0) << (RANG_PUSK_UROV_VID_DV & 0x1f);

      //���� ���(���)
      active_functions[RANG_BLOCK_ZOP >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_ZOP) != 0) << (RANG_BLOCK_ZOP & 0x1f);

      //���� ��� Umin
      active_functions[RANG_BLOCK_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMIN1) != 0) << (RANG_BLOCK_UMIN1 & 0x1f);
      active_functions[RANG_START_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_START_UMIN1) != 0) << (RANG_START_UMIN1 & 0x1f);
      active_functions[RANG_BLOCK_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMIN2) != 0) << (RANG_BLOCK_UMIN2 & 0x1f);
      active_functions[RANG_START_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_START_UMIN2) != 0) << (RANG_START_UMIN2 & 0x1f);
      
      //���� ��� Umax
      active_functions[RANG_BLOCK_UMAX1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMAX1) != 0) << (RANG_BLOCK_UMAX1 & 0x1f);
      active_functions[RANG_BLOCK_UMAX2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMAX2) != 0) << (RANG_BLOCK_UMAX2 & 0x1f);
      
      //���� ��� ���
      active_functions[RANG_OTKL_AVR         >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_OTKL_AVR        ) != 0) << (RANG_OTKL_AVR         & 0x1f);
      active_functions[RANG_SBROS_BLOCK_AVR  >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_SBROS_BLOCK_AVR ) != 0) << (RANG_SBROS_BLOCK_AVR  & 0x1f);
      active_functions[RANG_STAT_BLOCK_AVR_1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_STAT_BLOCK_AVR_1) != 0) << (RANG_STAT_BLOCK_AVR_1 & 0x1f);
      active_functions[RANG_STAT_BLOCK_AVR_2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_STAT_BLOCK_AVR_2) != 0) << (RANG_STAT_BLOCK_AVR_2 & 0x1f);
      active_functions[RANG_OZT_AVR_1        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_OZT_AVR_1       ) != 0) << (RANG_OZT_AVR_1        & 0x1f);
      active_functions[RANG_OZT_AVR_2        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_OZT_AVR_2       ) != 0) << (RANG_OZT_AVR_2        & 0x1f);
    }
  }
  /**************************/

  /**************************/
  //�������� ���������� ���������� ������ ��� ��� �������, �� ����� ������������ ����� �� ���������� �������
  /**************************/
  {
    static unsigned int previous_activating_functions[N_BIG];
    //������� ����� �������, �� ����� ���������, �� ������ ����� � ������ �������� � "0" � "1"
    unsigned int temp_maska_filter_function[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
    unsigned int temp_activating_functions[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
  
    //������ "����� ���������"
    _SET_BIT(temp_maska_filter_function, RANG_RESET_LEDS);
  
    //������ "����� ����"
    _SET_BIT(temp_maska_filter_function, RANG_RESET_RELES);

    //������ "�������� ��"
    _SET_BIT(temp_maska_filter_function, RANG_VKL_VV);
    
    //������ "��������� ��"
    _SET_BIT(temp_maska_filter_function, RANG_OTKL_VV);

    //������ "�������� ���������� ��������� �� ��"
    _SET_BIT(temp_maska_filter_function, RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV);
  
    //������ "������� ���������� ���"
    _SET_BIT(temp_maska_filter_function, RANG_OTKL_AVR);
    //������ "������� ����� ���������� ���"
    _SET_BIT(temp_maska_filter_function, RANG_SBROS_BLOCK_AVR);
    
    for (unsigned int i = 0; i < N_BIG; i++)
    {
      //� ������ ��������� ����� �������� ����� � �������, ��� ��� �������� ����� ��� � ������� �� � ���������� �����
      temp_activating_functions[i] = previous_activating_functions[i] & temp_maska_filter_function[i];
  
      //� ����������� ����� �������� ����� � �������, � ���� ����������� ��� �������, ��� ����� ������
      temp_activating_functions[i] ^= (active_functions[i] & temp_maska_filter_function[i]);
  
      //����� �������� � ����������� ����� ����� � ������� � ���� ����� �������� ������ ��� "1" (����� ������� ������� � "0" � "1")
      temp_activating_functions[i] &= active_functions[i];

      /*
      ����� ���, �� ������� � �������, �� � ����� ���� ������ ������ �� ������ 
      � ����������� ����, �� ���� ������� ����������� �� ���������� �����
      ������� ��������� ���� ������� (��� ���������� ������) � ���������� �����
      ��� ��� ���������� ����� ���� ��������� ��������� ���� �������� �������
      */ 
      previous_activating_functions[i] = active_functions[i];

      //���������� ����� �������, �� ����� ����������� � ����������� ����, �� ����� �������� ������� ������ ��������� ����� ���� ����� �, � ���� ������� ��� � "0" � "1"
      active_functions[i] = (active_functions[i] & (~temp_maska_filter_function[i])) | temp_activating_functions[i];
    }
  }
  /**************************/
  
  /**************************/
  //���� ����� �������
  /**************************/
  if (count_number_set_bit(&active_inputs_grupa_ustavok, NUMBER_GROUP_USTAVOK) > 1)
    _SET_BIT(set_diagnostyka, ERROR_SELECT_GRUPY_USRAVOK);
  else
    _SET_BIT(clear_diagnostyka, ERROR_SELECT_GRUPY_USRAVOK);
   
  if (
      ((active_functions[0] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_0) != 0) ||
      ((active_functions[1] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_1) != 0) ||
      ((active_functions[2] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_2) != 0) ||
      ((active_functions[3] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_3) != 0) ||
      ((active_functions[4] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_4) != 0) ||
      ((active_functions[5] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_5) != 0) ||
      ((active_functions[6] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_6) != 0)
    )
  {
    //��� ���������� ���� ������� - ����� ������� ���������� ���, ��� ������� ����������
    _SET_BIT(active_functions, RANG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV);

    unsigned int number_group_stp_tmp = 0;
    if(( _CHECK_SET_BIT(active_functions, RANG_1_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    if(( _CHECK_SET_BIT(active_functions, RANG_2_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    if(( _CHECK_SET_BIT(active_functions, RANG_3_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    if(( _CHECK_SET_BIT(active_functions, RANG_4_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    
    if (number_group_stp_tmp != 1)
    {
      //���������� ����� ����� �� ���� � ����
      total_error_sw_fixed(52);
    }
  }
  else
  {
    //����� �������� ����� ������� - ������� �� �������� �� ��������
    _CLEAR_BIT(active_functions, RANG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV);
    setpoints_selecting(active_functions, active_inputs_grupa_ustavok);
  }

  unsigned int number_group_stp;
  if     (( _CHECK_SET_BIT(active_functions, RANG_1_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 0;
  else if(( _CHECK_SET_BIT(active_functions, RANG_2_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 1;
  else if(( _CHECK_SET_BIT(active_functions, RANG_3_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 2;
  else if(( _CHECK_SET_BIT(active_functions, RANG_4_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 3;
  else
  {
    //���������� ����� ����� �� ���� � ����
    total_error_sw_fixed(51);
  }
  /**************************/

  /***********************************************************/
  //���������� ���������
  /***********************************************************/
  calc_measurement(number_group_stp);

#ifdef DEBUG_TEST
  /***/
  //ҳ���� ��� �������
  /***/
  if (temp_value_3I0_1 != 0)
    measurement[IM_3I0]         = temp_value_3I0_1;
  if (temp_value_3I0_other != 0)
    measurement[IM_3I0_other_g] = temp_value_3I0_other;
  if (temp_value_IA != 0)
    measurement[IM_IA]          = temp_value_IA;
  if (temp_value_IC != 0)
    measurement[IM_IC]          = temp_value_IC;
  if (temp_value_UA != 0)
    measurement[IM_UA]          = temp_value_UA;
  if (temp_value_UB != 0)
    measurement[IM_UB]          = temp_value_UB;
  if (temp_value_UC != 0)
    measurement[IM_UC]          = temp_value_UC;
  if (temp_value_3U0 != 0)
    measurement[IM_3U0]         = temp_value_3U0;
  if (temp_value_I2 != 0)
    measurement[IM_I2]          = temp_value_I2;
  if (temp_value_I1 != 0)
    measurement[IM_I1]          = temp_value_I1;
  /***/
#endif
    
      
  //ĳ��������� ��������� ��� �� �����
  diagnostyca_adc_execution();
  
  //������� ���������� ��� ����������������� � ����������������� �������
  unsigned int bank_measurement_high_tmp = (bank_measurement_high ^ 0x1) & 0x1;
  if(semaphore_measure_values_low1 == 0)
  {
    for (unsigned int i = 0; i < (NUMBER_ANALOG_CANALES + 8); i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement_middle[i] = measurement[i];
    }
  }
  else
  {
    for (unsigned int i = 0; i < (NUMBER_ANALOG_CANALES + 8); i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement[i];
    }
  }
  bank_measurement_high = bank_measurement_high_tmp;
  /***********************************************************/
  
  
  /**************************/
  //������ "������������ �����"
  /**************************/
  unsigned int diagnostyka_tmp[3];
  diagnostyka_tmp[0] = diagnostyka[0];
  diagnostyka_tmp[1] = diagnostyka[1];
  diagnostyka_tmp[2] = diagnostyka[2];

  diagnostyka_tmp[0] &= (unsigned int)(~clear_diagnostyka[0]); 
  diagnostyka_tmp[0] |= set_diagnostyka[0]; 

  diagnostyka_tmp[1] &= (unsigned int)(~clear_diagnostyka[1]); 
  diagnostyka_tmp[1] |= set_diagnostyka[1]; 

  diagnostyka_tmp[2] &= (unsigned int)(~clear_diagnostyka[2]); 
  diagnostyka_tmp[2] |= set_diagnostyka[2]; 
  
  diagnostyka_tmp[2] &= USED_BITS_IN_LAST_INDEX; 

  _CLEAR_BIT(diagnostyka_tmp, EVENT_START_SYSTEM_BIT);
  _CLEAR_BIT(diagnostyka_tmp, EVENT_DROP_POWER_BIT);
  if (
      (diagnostyka_tmp[0] != 0) ||
      (diagnostyka_tmp[1] != 0) ||
      (diagnostyka_tmp[2] != 0)
     )   
  {
    _SET_BIT(active_functions, RANG_DEFECT);
  }
  else
  {
    _CLEAR_BIT(active_functions, RANG_DEFECT);
  }
  /**************************/

  /**************************/
  //������ "������������ ���������"
  /**************************/
  if (
      ((diagnostyka[0] & MASKA_AVAR_ERROR_0) != 0) ||
      ((diagnostyka[1] & MASKA_AVAR_ERROR_1) != 0) ||
      ((diagnostyka[2] & MASKA_AVAR_ERROR_2) != 0)
     )   
  {
    _SET_BIT(active_functions, RANG_AVAR_DEFECT);
  }
  else
  {
    _CLEAR_BIT(active_functions, RANG_AVAR_DEFECT);
  }
  /**************************/
  
  //����� ����� ����� ��������� ����� � ���� �������, ���� ��� ������� "��������� �������������"
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0)
  {
    //������� �������� �� �����������
    
    /**************************/
    //�������� ������� ��
    /**************************/
    control_VV(active_functions);
    /**************************/

    /**************************/
    //"�������� ���������"
    /**************************/
    if ((current_settings_prt.configuration & (1 << CTRL_PHASE_BIT_CONFIGURATION)) != 0) 
    {
      ctrl_phase_handler(active_functions, number_group_stp);
    } 
    else 
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_ctrl_phase_signals[N_BIG] = 
      {
        MASKA_CTRL_PHASE_SIGNALS_0, 
        MASKA_CTRL_PHASE_SIGNALS_1, 
        MASKA_CTRL_PHASE_SIGNALS_2,
        MASKA_CTRL_PHASE_SIGNALS_3, 
        MASKA_CTRL_PHASE_SIGNALS_4, 
        MASKA_CTRL_PHASE_SIGNALS_5, 
        MASKA_CTRL_PHASE_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_ctrl_phase_signals[i]);
      
      global_timers[INDEX_TIMER_CTRL_PHASE_U] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_U_D] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_PHI] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_PHI_D] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_F] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_F_D] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_TMP1_100MS] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_TMP2_100MS] = -1;
    }
    /**************************/
    
    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << MTZ_BIT_CONFIGURATION)) != 0)
    {
      mtz_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_mtz_signals[N_BIG] = 
      {
        MASKA_MTZ_SIGNALS_0,
        MASKA_MTZ_SIGNALS_1,
        MASKA_MTZ_SIGNALS_2, 
        MASKA_MTZ_SIGNALS_3, 
        MASKA_MTZ_SIGNALS_4, 
        MASKA_MTZ_SIGNALS_5,
        MASKA_MTZ_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_mtz_signals[i]);
      
      global_timers[INDEX_TIMER_MTZ1] = -1;
      global_timers[INDEX_TIMER_MTZ1_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ1_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ1_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ2] = -1;
      global_timers[INDEX_TIMER_MTZ2_DEPENDENT] = -1;
      global_timers[INDEX_TIMER_MTZ2_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_VPERED_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_NAZAD_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ2_PO_NAPRUZI_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_VVID_PR] = -1;
      global_timers[INDEX_TIMER_MTZ3] = -1;
      global_timers[INDEX_TIMER_MTZ3_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ3_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ3_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ4] = -1;
      global_timers[INDEX_TIMER_MTZ4_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ4_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ4_PO_NAPRUZI] = -1;
    }
    /**************************/
    
    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZDZ_BIT_CONFIGURATION)) != 0)
    {
      zdz_handler(active_functions);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_zdz_signals[N_BIG] = 
      {
        MASKA_ZDZ_SIGNALS_0, 
        MASKA_ZDZ_SIGNALS_1, 
        MASKA_ZDZ_SIGNALS_2,
        MASKA_ZDZ_SIGNALS_3, 
        MASKA_ZDZ_SIGNALS_4, 
        MASKA_ZDZ_SIGNALS_5, 
        MASKA_ZDZ_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_zdz_signals[i]);
    }
    /**************************/

    /**************************/
    //���(���)
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZOP_BIT_CONFIGURATION)) != 0)
    {
      zop_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_zop_signals[N_BIG] = 
      {
        MASKA_ZOP_SIGNALS_0, 
        MASKA_ZOP_SIGNALS_1, 
        MASKA_ZOP_SIGNALS_2,
        MASKA_ZOP_SIGNALS_3, 
        MASKA_ZOP_SIGNALS_4, 
        MASKA_ZOP_SIGNALS_5, 
        MASKA_ZOP_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_zop_signals[i]);
      global_timers[INDEX_TIMER_ZOP] = -1;
    }
    /**************************/
    
    if ((current_settings_prt.configuration & (1 << UMIN_BIT_CONFIGURATION)) != 0) 
    {
      /**************************/
      //�����1
      /**************************/
      umin1_handler(active_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //�����2
      /**************************/
      umin2_handler(active_functions, number_group_stp);
      /**************************/
    } 
    else 
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_umin_signals[N_BIG] = 
      {
        MASKA_UMIN_SIGNALS_0, 
        MASKA_UMIN_SIGNALS_1, 
        MASKA_UMIN_SIGNALS_2,
        MASKA_UMIN_SIGNALS_3, 
        MASKA_UMIN_SIGNALS_4, 
        MASKA_UMIN_SIGNALS_5, 
        MASKA_UMIN_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_umin_signals[i]);

      global_timers[INDEX_TIMER_UMIN1] = -1;
      global_timers[INDEX_TIMER_UMIN2] = -1;
    }
    
    if ((current_settings_prt.configuration & (1 << UMAX_BIT_CONFIGURATION)) != 0) 
    {
      /**************************/
      //������1
      /**************************/
      umax1_handler(active_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //������2
      /**************************/
      umax2_handler(active_functions, number_group_stp);
      /**************************/
    } 
    else 
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_umax_signals[N_BIG] = 
      {
        MASKA_UMAX_SIGNALS_0, 
        MASKA_UMAX_SIGNALS_1, 
        MASKA_UMAX_SIGNALS_2,
        MASKA_UMAX_SIGNALS_3, 
        MASKA_UMAX_SIGNALS_4, 
        MASKA_UMAX_SIGNALS_5, 
        MASKA_UMAX_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_umax_signals[i]);

      global_timers[INDEX_TIMER_UMAX1] = -1;
      global_timers[INDEX_TIMER_UMAX2] = -1;
    }
    /**************************/

    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << AVR_BIT_CONFIGURATION)) != 0) 
    {
      avr_handler(active_functions, number_group_stp);
    } 
    else 
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_avr_signals[N_BIG] = 
      {
        MASKA_AVR_SIGNALS_0, 
        MASKA_AVR_SIGNALS_1, 
        MASKA_AVR_SIGNALS_2,
        MASKA_AVR_SIGNALS_3, 
        MASKA_AVR_SIGNALS_4, 
        MASKA_AVR_SIGNALS_5, 
        MASKA_AVR_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_avr_signals[i]);
      
      global_timers[INDEX_TIMER_AVR_BLK_K1] = -1;
      global_timers[INDEX_TIMER_AVR_PUSK_K1] = -1;
      global_timers[INDEX_TIMER_AVR_D_DIJI_K1] = -1;
      global_timers[INDEX_TIMER_AVR_VVIMK_REZ_K1] = -1;
      global_timers[INDEX_TIMER_AVR_VVIMK_K1] = -1;
      global_timers[INDEX_TIMER_AVR_VYMK_ROB_K1_UMIN] = -1;
      global_timers[INDEX_TIMER_AVR_VYMK_K1] = -1;
      global_timers[INDEX_TIMER_AVR_TMP_1MS_K1] = -1;
      global_timers[INDEX_TIMER_AVR_BLK_K2] = -1;
      global_timers[INDEX_TIMER_AVR_PUSK_K2] = -1;
      global_timers[INDEX_TIMER_AVR_D_DIJI_K2] = -1;
      global_timers[INDEX_TIMER_AVR_VVIMK_REZ_K2] = -1;
      global_timers[INDEX_TIMER_AVR_VVIMK_K2] = -1;
      global_timers[INDEX_TIMER_AVR_VYMK_ROB_K2_UMIN] = -1;
      global_timers[INDEX_TIMER_AVR_VYMK_K2] = -1;
      global_timers[INDEX_TIMER_AVR_TMP_1MS_K2] = -1;

      previous_states_AVR_0 = 0;
      trigger_AVR_0 = 0;
    }
    /**************************/
    
    /**************************/
    //����
    /**************************/
    if ((current_settings_prt.configuration & (1 << UROV_BIT_CONFIGURATION)) != 0)
    {
      urov_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_urov_signals[N_BIG] = 
      {
        MASKA_UROV_SIGNALS_0, 
        MASKA_UROV_SIGNALS_1, 
        MASKA_UROV_SIGNALS_2,
        MASKA_UROV_SIGNALS_3, 
        MASKA_UROV_SIGNALS_4, 
        MASKA_UROV_SIGNALS_5, 
        MASKA_UROV_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_urov_signals[i]);

      global_timers[INDEX_TIMER_UROV1] = -1;
      global_timers[INDEX_TIMER_UROV2] = -1;
    }
    /**************************/

    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << APV_BIT_CONFIGURATION)) != 0)
    {
      apv_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_apv_signals[N_BIG] = 
      {
        MASKA_APV_SIGNALS_0, 
        MASKA_APV_SIGNALS_1, 
        MASKA_APV_SIGNALS_2,
        MASKA_APV_SIGNALS_3, 
        MASKA_APV_SIGNALS_4, 
        MASKA_APV_SIGNALS_5, 
        MASKA_APV_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_apv_signals[i]);

      global_timers[INDEX_TIMER_APV_1] = -1;
      global_timers[INDEX_TIMER_APV_2] = -1;
      global_timers[INDEX_TIMER_APV_3] = -1;
      global_timers[INDEX_TIMER_APV_4] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV1] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV2] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV3] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV4] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_VV] = -1;
      global_timers[INDEX_TIMER_APV_TMP1] = -1;

      previous_states_APV_0 = 0;
      trigger_APV_0 = 0;
    }
    /**************************/

    /**************************/
    //��������� �����
    /**************************/
    if ((current_settings_prt.configuration & (1 << EL_BIT_CONFIGURATION)) != 0)
    {
      unsigned int active_functions_tmp[NUMBER_ITERATION_EL_MAX][N_BIG];
      unsigned int iteration = 0;
	  unsigned int repeat_state = false;
      unsigned int df_changed_state_with_start_new_timeout = 0;
      do
      {
        for (unsigned int i = 0; i < iteration; i++)
        {
          if (
              (active_functions_tmp[i][0] == active_functions[0]) &&
              (active_functions_tmp[i][1] == active_functions[1]) &&
              (active_functions_tmp[i][2] == active_functions[2]) &&
              (active_functions_tmp[i][3] == active_functions[3]) &&
              (active_functions_tmp[i][4] == active_functions[4]) &&
              (active_functions_tmp[i][5] == active_functions[5]) &&
              (active_functions_tmp[i][6] == active_functions[6])
             )
          {
            repeat_state = true;
            break;
          }
        }
        if (repeat_state != false ) break;
        
        active_functions_tmp[iteration][0] = active_functions[0];
        active_functions_tmp[iteration][1] = active_functions[1];
        active_functions_tmp[iteration][2] = active_functions[2];
        active_functions_tmp[iteration][3] = active_functions[3];
        active_functions_tmp[iteration][4] = active_functions[4];
        active_functions_tmp[iteration][5] = active_functions[5];
        active_functions_tmp[iteration][6] = active_functions[6];

        d_and_handler(active_functions);
        d_or_handler(active_functions);
        d_xor_handler(active_functions);
        d_not_handler(active_functions);
        df_handler(active_functions, &df_changed_state_with_start_new_timeout);
        dt_handler(active_functions);
        
        iteration++;
      }
      while (
             (iteration < current_settings_prt.number_iteration_el)
             &&
             (
              (active_functions_tmp[iteration - 1][0] != active_functions[0]) ||
              (active_functions_tmp[iteration - 1][1] != active_functions[1]) ||
              (active_functions_tmp[iteration - 1][2] != active_functions[2]) ||
              (active_functions_tmp[iteration - 1][3] != active_functions[3]) ||
              (active_functions_tmp[iteration - 1][4] != active_functions[4]) ||
              (active_functions_tmp[iteration - 1][5] != active_functions[5]) ||
              (active_functions_tmp[iteration - 1][6] != active_functions[6])
             ) 
            );
      
      if (
          (repeat_state != false ) ||
          (iteration >= current_settings_prt.number_iteration_el)
         )
      {
        _SET_BIT(active_functions, RANG_ERROR_CONF_EL);
      }
      else
      {
        _CLEAR_BIT(active_functions, RANG_ERROR_CONF_EL);
      }
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_el_signals[N_BIG] = 
      {
        MASKA_EL_SIGNALS_0, 
        MASKA_EL_SIGNALS_1, 
        MASKA_EL_SIGNALS_2,
        MASKA_EL_SIGNALS_3, 
        MASKA_EL_SIGNALS_4, 
        MASKA_EL_SIGNALS_5, 
        MASKA_EL_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_el_signals[i]);
      
      //������� �� �������, �� ���������� �� ��������� �����
      for(unsigned int i = INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START; i < (INDEX_TIMER_DF_WORK_START + NUMBER_DEFINED_FUNCTIONS); i++)
        global_timers[i] = -1;
    }
    /**************************/

    /**************************/
    //���������-³���������
    /**************************/
    on_off_handler(active_functions);
    /**************************/
    
    /**************************/
    //���������� � ��
    /**************************/
    ready_tu(active_functions);
    /**************************/

    /**************************/
    //������ �������� (������ ����� ����� ����� ���������)
    /**************************/
    resurs_vymykacha_handler(active_functions);
    /**************************/
  }
  else
  {
    //������� �������� �����������
    
    //������� �� ������ �������, ��� �������������
    active_functions[0] &= MASKA_INFO_SIGNALES_0;
    active_functions[1] &= MASKA_INFO_SIGNALES_1;
    active_functions[2] &= MASKA_INFO_SIGNALES_2;
    active_functions[3] &= MASKA_INFO_SIGNALES_3;
    active_functions[4] &= MASKA_INFO_SIGNALES_4;
    active_functions[5] &= MASKA_INFO_SIGNALES_5;
    active_functions[6] &= MASKA_INFO_SIGNALES_6;
    
    //������������ �� ����
    state_outputs = 0;
    
    //���������� � ���������� ���� ���� �������� ����
    previous_states_APV_0 = 0;
    trigger_APV_0 = 0;

    previous_states_AVR_0 = 0;
    trigger_AVR_0 = 0;

    previous_states_ready_tu = 0;
    trigger_ready_tu = 0;
    
    //������� �� �������, �� ������� � �����
    for(unsigned int i = INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START; i < MAX_NUMBER_GLOBAL_TIMERS; i++)
      global_timers[i] = -1;
    
    //���� ��������� �� ���������� � ����������
    for(unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      etap_execution_df[i] = NONE_DF;
    }
  }

  /**************************/
  //������� ����������� ����������
  /**************************/
  analog_registrator(active_functions);
  /**************************/

  /**************************/
  //������� ����������� ����������
  /**************************/
  digital_registrator(active_functions);
  /**************************/

  /**************************/
  //������ � ���������, �� ����� ������������ � ��������������� ���'���
  /**************************/
  const unsigned int maska_trg_func_array[N_BIG] = {MASKA_TRIGGER_SIGNALES_0, MASKA_TRIGGER_SIGNALES_1, MASKA_TRIGGER_SIGNALES_2, MASKA_TRIGGER_SIGNALES_3, MASKA_TRIGGER_SIGNALES_4, MASKA_TRIGGER_SIGNALES_5, MASKA_TRIGGER_SIGNALES_6};
  unsigned int comparison_true = true;
  for (unsigned int i = 0; i < N_BIG; i++)
  {
    unsigned int tmp_data;
    if (trigger_active_functions[i] != (tmp_data = (active_functions[i] & maska_trg_func_array[i])))
    {
      comparison_true = false;
      trigger_active_functions[i] = tmp_data;
    }
  }
  if (comparison_true != true)
  {
    /*
    �������, �������� ���� ���������� � ��������������� ���'1��� ��������.
    ������ ������� �� �� ����� � ��������������� ���'���
    */
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
  }
  /**************************/

  /**************************/
  //����������� ��������� � ������ �������� � ��������� �������
  /**************************/
  for (unsigned int i = 0; i < N_BIG; i++)
  {
    unsigned int temp_data = active_functions[i];
    trigger_functions_USB[i]   |= temp_data;
    trigger_functions_RS485[i] |= temp_data;
  }

  copying_active_functions = 0; //�������, �� ���������� �������� �������� ������� ���������
  
  /*
  ������ ���� �������� �������� ������� ��� ����, ��� ���� �� ������� ������
  �����������, �� ����� ���� � ����� �������  (����� � ��'������� ����������
  ���������) ����� ��������, ��� ��������� ��������
  */
  for (unsigned int i = 0; i < N_BIG; i++) active_functions_copy[i] = active_functions[i];
  /**************************/

  /**************************/
  //���� ���������� �� ������
  /**************************/
  //�������� ����������, �� �� �������������� ������� "����� ����" - � ���� ���, �� ���������� ������� �� ����
  if (_CHECK_SET_BIT(active_functions, RANG_RESET_RELES) !=0)
  {
    state_outputs = 0;
  }
  
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0)
  {
    //�� ����������� ������� ��������, ���� ������������� ���� �����
    
    //���������, �� ���� ����� ����� ���� ����������
    for (unsigned int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      //� ���������� ����� ������� ��ò��� � ���������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
      unsigned int temp_array_of_outputs[N_BIG];
    
      for (unsigned int j = 0; j < N_BIG; j++) temp_array_of_outputs[j] = current_settings_prt.ranguvannja_outputs[N_BIG*i + j] & active_functions[j];

      //������ "������� �����������" ������ � ���������� �����: ������ ���� �� ����� ���������� � �������, ���� ����� ������ �� ��������
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_AVAR_DEFECT) !=0)
      {
        //������ "A�������� �������������"  ������ ���������� �� ����� �����
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT) == 0)
        {
          //������ "A�������� �������������" �� � ��������
          //���������� ������������ ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _SET_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT);
        }
        else
        {
          //������ "A�������� �������������" � ��������
          //���������� ���������� ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _CLEAR_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT);
        }
      }
      
      //������ "�������� �����������" ������ � ���������� �����: ������ ���� �� ����� ���������� � �������, ���� ����� ������ �� ��������
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_DEFECT) !=0)
      {
        //������ "�������� �����������"  ������ ���������� �� ����� �����
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_DEFECT) ==0)
        {
          //������ "�������� �����������" �� � ��������
          //���������� ������������ ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _SET_BIT(temp_array_of_outputs, RANG_DEFECT);
        }
        else
        {
          //������ "�������� �����������" � ��������
          //���������� ���������� ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _CLEAR_BIT(temp_array_of_outputs, RANG_DEFECT);
        }
      }

      //����������, �� � ��������� �� ����������� ��������� �� ����� ����� � ���������, �� ����� � ��������� - ����� ��������� ������
      if (
          (temp_array_of_outputs[0] !=0 ) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0) ||
          (temp_array_of_outputs[6] != 0)
         )
      {
        //��� ����������� ���� �������� ���� ���������, � ��� ���������� ���������� �� ���� ������ ���������� ���� ��� ���� �� �� ����� �������� ���� ���������, ������� �� ����������
        if ((current_settings_prt.type_of_output & (1 << i)) != 0)
        {
          //����� ����������, ���� � ���� ����� ��� �������� ����
          //³������, �� ����� ����� - ���������
          state_outputs |= (1 << i);
        }
        else
        {
          //����� ���������, ���� ���������� �� �� ��� ������ ���������� ����, �� ��� �������� ��, ������� ���� �� � ������� ������ ���������� (����������)
          if (_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_WORK_BV) == 0)
          {
            //�� ���� ���� �� ���������� ������ �� (���� ���������)
          
            //³������, �� ����� ����� - ���������
            state_outputs |= (1 << i);
          }
          else
          {
            //�� ���� ���� ���������� ������ �� (���� ���������)
          
            //³������, �� ����� ����� - ��������� ����� ���, ���� ������� �� ������� �����
            if (_CHECK_SET_BIT(active_functions, RANG_WORK_BV) != 0)
              state_outputs |= (1 << i);
            else
              state_outputs &= ~(1 << i);
          }
        }
      }
      else
      {
        //����������, �� ����� ���������, �� ����������
        if ((current_settings_prt.type_of_output & (1 << i)) == 0)
        {
          //����� ���������
        
          //³������, �� ����� ����� - ��ǲ�������
          state_outputs &= ~(1 << i);
        }
      }
    }
  }
  else
  {
    //����������� ������e ��������, ���� ���������� �� ����!!!

    //������������ �� ����
    state_outputs = 0;
  }
  
  //���������� �� ����� ���������� ���� ���������� ������ � EEPROM
  unsigned int temp_value_char_for_volatile = state_signal_outputs;
  if((state_outputs  & current_settings_prt.type_of_output) != temp_value_char_for_volatile)
  {
    state_signal_outputs = state_outputs  & current_settings_prt.type_of_output;
    //����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� �������� ���������� ������ � ��������� ��������������
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }
  
  //���� ������ � ����������� ����������� ������ ������ ���������� ������
  state_outputs_raw = ( state_outputs & ((unsigned int)(~current_settings_prt.type_of_output_modif)) ) | ((state_outputs & current_settings_prt.type_of_output_modif)*output_timer_prt_signal_output_mode_2);
  
  //�������� ���������� �� ������� �� ��� ��������� (� ����������� �������)
  unsigned int temp_state_outputs = 0;
  for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
  {
    if ((state_outputs_raw & (1 << index)) != 0)
    {
      if (index < NUMBER_OUTPUTS_1)
        temp_state_outputs |= 1 << (NUMBER_OUTPUTS_1 - index - 1);
      else
        temp_state_outputs |= 1 << index;
    }
  }
  unsigned int temp_state_outputs_1 =  temp_state_outputs                      & ((1 << NUMBER_OUTPUTS_1) - 1);
  unsigned int temp_state_outputs_2 = (temp_state_outputs >> NUMBER_OUTPUTS_1) & ((1 << NUMBER_OUTPUTS_2) - 1);
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1) = temp_state_outputs_1;
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2) = temp_state_outputs_2;
  /**************************/

  /**************************/
  //���� ���������� �� ���������
  /**************************/
  //�������� ����������, �� �� �������������� ������� "����� ���������" - � ���� ���, �� ���������� ������� ��� ���������
  if (_CHECK_SET_BIT(active_functions, RANG_RESET_LEDS) !=0)
  {
    state_leds = 0;
  }
  
  //���������, �� �������������� ����� ����� ���� ���������
  for (unsigned int i = 0; i < NUMBER_LEDS; i++)
  {
    //� ���������� ����� ������� ���������� ��������������, ���� ����������� ��������� "i"
    unsigned int temp_array_of_leds[N_BIG];
    
    //����������, �� � ��������� �� ����������� ��������� �� ����� ������������� � ���������, �� ����� � ��������� - ����� ��������� ������
    for (unsigned int j = 0; j < N_BIG; j++ ) temp_array_of_leds[j] = current_settings_prt.ranguvannja_leds[N_BIG*i + j] & active_functions[j];

    if (
        (temp_array_of_leds[0] != 0) ||
        (temp_array_of_leds[1] != 0) ||
        (temp_array_of_leds[2] != 0) ||
        (temp_array_of_leds[3] != 0) ||
        (temp_array_of_leds[4] != 0) ||
        (temp_array_of_leds[5] != 0) ||
        (temp_array_of_leds[6] != 0)
       )
    {
      //³������, �� ����� ������������� - ������
      state_leds |= (1 << i);
    }
    else
    {
      //����������, �� ����� ������������� ����������, �� ���������
      if ((current_settings_prt.type_of_led & (1 << i)) == 0)
      {
        //������������� ����������

        //³������, �� ����� ������������� - ���������
        state_leds &= ~(1 << i);
      }
    }
  }
  //���������� �� ����� ���������� ���� ��������� �������������� � EEPROM
  temp_value_char_for_volatile = state_trigger_leds;
  if((state_leds  & current_settings_prt.type_of_led) != temp_value_char_for_volatile)
  {
    state_trigger_leds = state_leds  & current_settings_prt.type_of_led;
    //����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� �������� ���������� ������ � ��������� ��������������
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }

  //�������� ���������� �� ��������������� �� ���������
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_LEDS) = state_leds;
  /**************************/

  /**************************/
  //
  /**************************/
  /**************************/
}
/*****************************************************/

/*****************************************************/
//����������� �� ������� TIM2, ���� ��������� ������� �������
/*****************************************************/
void TIM2_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //����������� �������� �� ������ 1, ���� ������ ����������� ���� 1 ��, ��� ��������������� ������� � ������ �������
    /***********************************************************************************************/
    TIM2->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
    uint32_t current_tick = TIM2->CCR1;
    
    /***********************************************************/
    //����������, �� ���������� ���� ���������
    /***********************************************************/
    if (
        (changed_settings == CHANGED_ETAP_ENDED) && /*�� � �����, �� ��� ��� ���������� ��� �������� �� � ������ �������� ������� (� ��� ����� ����� ��� �� ���������)*/
        (state_ar_record  != STATE_AR_START    )    /*�� � �����, �� �� ����� ������ �� ���� ��������� ����������� �� ����������� ������� (� ����� ���������� �� �������� ������� �������) � ������ ������� ���������� ������ ����������� ����������. �� ����� ���� ����� ������ ����������� � ������������� ������*/ 
       )   
    {
      //������� ������� ��������� � ���� ���� ������� ��� � ���� ������ (���� � �����) ����� ������� �������
      current_settings_prt = current_settings;
      
      //�������, �� ���� ������� �������� �������
      changed_settings = CHANGED_ETAP_NONE;
    }

    if (koef_resurs_changed == CHANGED_ETAP_ENDED)
    {
      //����������� ��� ��������� ������� ��������
      K_resurs_prt = K_resurs;

      //�������, �� ���� ������� �������� �������
      koef_resurs_changed = CHANGED_ETAP_NONE;
    }
    /***********************************************************/

    /***********************************************************/
    //���������� ����������� ������� ����������� � ����������� ����������
    /***********************************************************/
    //���������� ���������
    if (
        ((clean_rejestrators & CLEAN_AR) != 0 )
        &&  
        (state_ar_record == STATE_AR_NO_RECORD)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR |
                                     TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR      |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB                         |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485                       |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU
                                    )
         ) == 0
        )   
       )
    {
      //���������� ������� �������� ����������� ����������

      //����������� ������� ������ ���� ��������� � EEPROM
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
    
      //������� ��������� ���������� �� ����������� ���������
      info_rejestrator_ar.next_address = MIN_ADDRESS_AR_AREA;
      info_rejestrator_ar.saving_execution = 0;
      info_rejestrator_ar.number_records = 0;
    
      //�������, �� ����� ������ �� ��������
      number_record_of_ar_for_menu = 0xffff;
      number_record_of_ar_for_USB = 0xffff;
      number_record_of_ar_for_RS485 = 0xffff;

      //������ ������� ������� ����������� ����������
      clean_rejestrators &= (unsigned int)(~CLEAN_AR);
    }
    
    //���������� ���������
    if (
        ((clean_rejestrators & CLEAN_DR) != 0)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR | 
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                    |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                  |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU
                                    )
         ) == 0
        )
       )   
    {
      //���������� ������� �������� ����������� ���������

      //����������� ������� ������ ���� ��������� � EEPROM
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);

      //������� ��������� ���������� �� ����������� ���������
      info_rejestrator_dr.next_address = MIN_ADDRESS_DR_AREA;
      info_rejestrator_dr.saving_execution = 0;
      info_rejestrator_dr.number_records = 0;

      //�������, �� ����� ������ �� ��������
      number_record_of_dr_for_menu  = 0xffff;
      number_record_of_dr_for_USB   = 0xffff;
      number_record_of_dr_for_RS485 = 0xffff;

      //������ ������� ������� ����������� ����������
      clean_rejestrators &= (unsigned int)(~CLEAN_DR);
    }
    /***********************************************************/

    /***********************************************************/
    //���������� ������� �������� � ���������� ����� ����� ���� ��������� ������ ��������
    /***********************************************************/
    clocking_global_timers();
    /***********************************************************/
    
    /***********************************************************/
    //���������� ������� �������
    /***********************************************************/
    //ĳ��������� �����, ��� ����� ��������� ����� ��� ����� �������� ��������������� ����� ��������
    unsigned int control_state_outputs_1 = (( (~((unsigned int)(_DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1)))) >> 8) & ((1 << NUMBER_OUTPUTS_1) - 1));
    unsigned int control_state_outputs_2 = (( (~((unsigned int)(_DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2)))) >> 8) & ((1 << NUMBER_OUTPUTS_2) - 1));
    unsigned int control_state_outputs = control_state_outputs_1 | (control_state_outputs_2 << NUMBER_OUTPUTS_1);
    //������� ����� ������ � ���������� �� ������ ���������
    unsigned int temp_state_outputs = 0;
    for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
    {
      if ((state_outputs_raw & (1 << index)) != 0) 
      {
        if (index < NUMBER_OUTPUTS_1)
          temp_state_outputs |= 1 << (NUMBER_OUTPUTS_1 - index - 1);
        else
          temp_state_outputs |= 1 << index;
      }
    }
    if (control_state_outputs != temp_state_outputs) 
    {
//      _SET_BIT(set_diagnostyka, ERROR_DIGITAL_OUTPUTS_BIT);
      for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
      {
        uint32_t maska;
        if (index < NUMBER_OUTPUTS_1)
          maska = 1 << (NUMBER_OUTPUTS_1 - index - 1);
        else
          maska = 1 << index;
        
        if ((control_state_outputs & maska) != (temp_state_outputs & maska)) _SET_BIT(set_diagnostyka, (ERROR_DIGITAL_OUTPUT_1_BIT + index));
      }
    }
    
    //���������� ����������� ������� ��� ����������� ����������
    if (
        (state_ar_record  != STATE_AR_TEMPORARY_BLOCK) &&
        (changed_settings == CHANGED_ETAP_NONE       )  
       )   
    {
      //�������� ��������� ����� ���, ���� �� ��� ���� ������� ���������
      unsigned int size_one_ar_record_tmp = size_one_ar_record, max_number_records_ar_tmp = max_number_records_ar;
      if (
          ((number_word_digital_part_ar*8*sizeof(short int)) < NUMBER_TOTAL_SIGNAL_FOR_RANG)
          ||  
          (size_one_ar_record_tmp != (sizeof(__HEADER_AR) + ((current_settings_prt.prefault_number_periods + current_settings_prt.postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int)))
          ||
          (
           !(
             (size_one_ar_record_tmp* max_number_records_ar_tmp      <= ((NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2))) &&
             (size_one_ar_record_tmp*(max_number_records_ar_tmp + 1) >  ((NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2)))
            ) 
          ) 
         )
      {
        //���������� �� ������� ����� �� ����� ������������
        /*���� ������� ���� �������� �� ����� ��������� ���������, ��� ���� ���� �� ���������� - 
        �� �������� ����������� ���������� ������� � �������������� ���������� ����������� ����������.
        �� �������� ���� ���� �������, ���� � ��, ���������� ������ ����������� ������������ �� ��������!*/
        total_error_sw_fixed(5);
      }
    }

    //������� �������
    main_protection();
    /***********************************************************/

    /***********************************************************/
    //�������� �� ����������� ������� ������� ��ﳿ ����� ��� ������������
    /***********************************************************/
    //������� ����������
    if (periodical_tasks_TEST_TRG_FUNC != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_i2c_task & STATE_TRG_FUNC_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ������� ����������, ���� ����� �������� ���������
          misceve_dystancijne_ctrl = misceve_dystancijne;
          for (unsigned int i = 0; i < N_BIG; i++) trigger_active_functions_ctrl[i] = trigger_active_functions[i];
          crc_trg_func_ctrl = crc_trg_func;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_TRG_FUNC = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_TRG_FUNC_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_TRG_FUNC = false;
      }
    }

    //���������� ���������
    if (periodical_tasks_TEST_INFO_REJESTRATOR_AR != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_i2c_task & STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ��������� ���������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ��������� ���������� ����������, ���� ����� �������� ���������
          info_rejestrator_ar_ctrl = info_rejestrator_ar;
          crc_info_rejestrator_ar_ctrl = crc_info_rejestrator_ar;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
      }
    }

    //���������� ���������
    if (periodical_tasks_TEST_INFO_REJESTRATOR_DR != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_i2c_task & STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ��������� ���������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ��������� ���������� ����������, ���� ����� �������� ���������
          info_rejestrator_dr_ctrl = info_rejestrator_dr;
          crc_info_rejestrator_dr_ctrl = crc_info_rejestrator_dr;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
      }
    }
    /***********************************************************/

    //˳������� �������
    if (periodical_tasks_TEST_RESURS != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_i2c_task & STATE_RESURS_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ���������z ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_RESURS_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_RESURS_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_RESURS_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ������� ��������, ���� ����� �������� ���������
          resurs_vymykacha_ctrl = resurs_vymykacha;          
          resurs_vidkljuchennja_ctrl = resurs_vidkljuchennja;
          crc_resurs_ctrl = crc_resurs;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_RESURS = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_RESURS_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_RESURS = false;
      }
    }

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
    uint32_t capture_new;
    unsigned int delta;
    TIM2->CCR1 = (capture_new = (current_tick + (delta = TIM2_CCR1_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM2->CNT;

      uint64_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x100000000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM2, TIM_IT_CC1) == RESET)
        {
          if (delta < TIM2_CCR1_VAL)
          {
            uint64_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x100000000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM2_CCR1_VAL)
            delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
          else
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(83);
          }
          TIM2->CCR1 = (capture_new = (TIM2->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/
    
    /***********************************************************/
    //����������� ����������� ��� ��, ������� ������ �������
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_PROTECTION;
    /***********************************************************/
    /***********************************************************************************************/
  }
  else
  {
    total_error_sw_fixed(23);
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//���� ����� �������
/*****************************************************/
void setpoints_selecting(volatile unsigned int *p_active_functions, unsigned int act_inp_gr_ustavok) {
  unsigned int grupa_ustavok = 0;
  act_inp_gr_ustavok &= 0xf;
  if (current_settings_prt.grupa_ustavok < SETPOINT_GRUPA_USTAVOK_MIN ||
      current_settings_prt.grupa_ustavok > SETPOINT_GRUPA_USTAVOK_MAX) {
    //�������������� ������
    while (1);
  } else {
    grupa_ustavok = 1 << (current_settings_prt.grupa_ustavok - 1);
  }
  
  _OR4_INVERTOR(act_inp_gr_ustavok, 0, act_inp_gr_ustavok, 1, act_inp_gr_ustavok, 2, act_inp_gr_ustavok, 3, act_inp_gr_ustavok, 4);
  if (_GET_OUTPUT_STATE(act_inp_gr_ustavok, 4)) 
    _SET_BIT(p_active_functions, RANG_INVERS_DV_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_INVERS_DV_GRUPA_USTAVOK);
  
  _AND2(grupa_ustavok, 0, act_inp_gr_ustavok, 4, grupa_ustavok, 4);
  _AND2(grupa_ustavok, 1, act_inp_gr_ustavok, 4, grupa_ustavok, 5);
  _AND2(grupa_ustavok, 2, act_inp_gr_ustavok, 4, grupa_ustavok, 6);
  _AND2(grupa_ustavok, 3, act_inp_gr_ustavok, 4, grupa_ustavok, 7);
  
  unsigned int tmp = gr_ustavok_tmp;
  do {
    _AND4(act_inp_gr_ustavok, 0, gr_ustavok_tmp, 1, gr_ustavok_tmp, 2, gr_ustavok_tmp, 3, act_inp_gr_ustavok, 5);
    _INVERTOR(act_inp_gr_ustavok, 5, tmp, 0);
    
    _AND4(tmp, 0, act_inp_gr_ustavok, 1, tmp, 2, tmp, 3, act_inp_gr_ustavok, 6);
    _INVERTOR(act_inp_gr_ustavok, 6, tmp, 1);
    
    _AND4(tmp, 0, tmp, 1, act_inp_gr_ustavok, 2, tmp, 3, act_inp_gr_ustavok, 7);
    _INVERTOR(act_inp_gr_ustavok, 7, tmp, 2);
    
    _AND4(tmp, 0, tmp, 1, tmp, 2, act_inp_gr_ustavok, 3, act_inp_gr_ustavok, 8);
    _INVERTOR(act_inp_gr_ustavok, 8, tmp, 3);
    if (tmp == gr_ustavok_tmp) {
      break;
    }
    gr_ustavok_tmp = tmp;
  } while (1);
  
  _OR2(grupa_ustavok, 4, act_inp_gr_ustavok, 5, grupa_ustavok, 8);
  _OR2(grupa_ustavok, 5, act_inp_gr_ustavok, 6, grupa_ustavok, 9);
  _OR2(grupa_ustavok, 6, act_inp_gr_ustavok, 7, grupa_ustavok, 10);
  _OR2(grupa_ustavok, 7, act_inp_gr_ustavok, 8, grupa_ustavok, 11);
  
  if (_GET_OUTPUT_STATE(grupa_ustavok, 8)) 
    _SET_BIT(p_active_functions, RANG_1_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_1_GRUPA_USTAVOK);

  if (_GET_OUTPUT_STATE(grupa_ustavok, 9))
    _SET_BIT(p_active_functions, RANG_2_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_2_GRUPA_USTAVOK);

  if (_GET_OUTPUT_STATE(grupa_ustavok, 10))
      _SET_BIT(p_active_functions, RANG_3_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_3_GRUPA_USTAVOK);

  if (_GET_OUTPUT_STATE(grupa_ustavok, 11))
      _SET_BIT(p_active_functions, RANG_4_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_4_GRUPA_USTAVOK);
}
/*****************************************************/

/*****************************************************/
