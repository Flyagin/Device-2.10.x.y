#include "header.h"

/*****************************************************/
//������� ���������� ������ ��� ��� ������������
/*****************************************************/
unsigned int action_after_changing_of_configuration(unsigned int new_configuration, __SETTINGS *target_label)
{
  unsigned int error_window = 0;
  
  /************************/
  //������ ���������� �� �� ����������� ����� �� � ������ ���, ��� ��������� �������� ������ ������������
  /************************/
  //�������� ���
  if ((new_configuration & ( 1<< MTZ_BIT_CONFIGURATION )) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_MTZ)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_MTZ) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_MTZ) 
       )  
       ||  
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_MTZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_MTZ_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_MTZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_MTZ_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_MTZ)
      )
      error_window |= (1 << MTZ_BIT_CONFIGURATION );
  }
  //�������� ���
  if ((new_configuration & (1<<ZDZ_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZDZ) ||
       (current_ekran.current_level == EKRAN_CONTROL_ZDZ        )
      )
      error_window |= (1 << ZDZ_BIT_CONFIGURATION );
  }
  //�������� ���
  if ((new_configuration & (1<<APV_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_APV)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_TIMEOUT_GROUP1_APV) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_TIMEOUT_GROUP4_APV) 
       )  
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_APV        )
      )
      error_window |= (1 << APV_BIT_CONFIGURATION );
  }
  //�������� ����
  if ((new_configuration & (1<<UROV_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UROV)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UROV) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UROV        )
      )
      error_window |= (1 << UROV_BIT_CONFIGURATION );
  }
  //�������� ���(���)
  if ((new_configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZOP)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZOP) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_ZOP        )
      )
      error_window |= (1 << ZOP_BIT_CONFIGURATION );
  }
  //�������� Umin
  if ((new_configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMIN)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMIN) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UMIN        )
      )
      error_window |= (1 << UMIN_BIT_CONFIGURATION );
  }
  //�������� Umax
  if ((new_configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMAX)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMAX) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UMAX        )
      )
      error_window |= (1 << UMAX_BIT_CONFIGURATION );
  }
  //�������� ���
  if ((new_configuration & (1<<AVR_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_AVR)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_AVR) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_AVR_UMIN_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_AVR_UMAX_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GENERAL_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_UMAX_GROUP4   )
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_AVR        )
      )
      error_window |= (1 << AVR_BIT_CONFIGURATION );
  }
  //�������� "�������� ���������"
  if ((new_configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CTRL_PHASE)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CTRL_PHASE) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_CTRL_PHASE) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_CTRL_PHASE_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_CTRL_PHASE_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_CTRL_PHASE_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_CTRL_PHASE_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_CTRL_PHASE)
      )
      error_window |= (1 << CTRL_PHASE_BIT_CONFIGURATION );
  }
  //�������� "��������� �����"
  if ((new_configuration & (1<<EL_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level >= EKRAN_EXTENDED_LIGIC) &&
       (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16)  
      )
      error_window |= (1 << EL_BIT_CONFIGURATION );
  }
  /************************/
  
  if (error_window == 0)
  {
    //������� ���� ����������� � ������� ���������
    target_label->configuration = new_configuration;
    
    unsigned int maska[N_SMALL] = {0, 0}, maska_1[N_BIG] = {0, 0, 0, 0, 0, 0, 0}, maska_2 = 0;
  
    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<MTZ_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ ���
      target_label->control_mtz &= (unsigned int)(~(CTR_MTZ_1 | CTR_MTZ_2 | CTR_MTZ_3 | CTR_MTZ_4));
   
      //������� ������ ��� � ���
      target_label->control_apv &= (unsigned int)(~(CTR_APV_STARTED_FROM_MTZ1 | CTR_APV_STARTED_FROM_MTZ2 | CTR_APV_STARTED_FROM_MTZ3  | CTR_APV_STARTED_FROM_MTZ4));

      //������� ������ ��� � ���
      target_label->control_zdz &= (unsigned int)(~(CTR_ZDZ_STARTED_FROM_MTZ1 | CTR_ZDZ_STARTED_FROM_MTZ2 | CTR_ZDZ_STARTED_FROM_MTZ3  | CTR_ZDZ_STARTED_FROM_MTZ4));
      
      //������� ������ ��� � ����
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_MTZ1 | CTR_UROV_STARTED_FROM_MTZ2 | CTR_UROV_STARTED_FROM_MTZ3 | CTR_UROV_STARTED_FROM_MTZ4));
      
      //������� ����� ������� ���
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + 
                  i
                 )
                );

      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_MTZ_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG + 
                  i
                 )
                );
      
      maska_2 = 0;
      for (int i = 0; i < NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<ZDZ_BIT_CONFIGURATION)) == 0)
    {
      //������� ���
      target_label->control_zdz &= (unsigned int)(~CTR_ZDZ_STATE);

      //������� ������ ��� � ����
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_ZDZ);
      
      //������� ���� ������� ���
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_ZDZ_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ���
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<APV_BIT_CONFIGURATION)) == 0)
    {
      //������� ���
      target_label->control_apv &= (unsigned int)(~(CTR_APV_STAGE_1 | CTR_APV_STAGE_2 | CTR_APV_STAGE_3 | CTR_APV_STAGE_4));
   
      //������� ���� ������� ���
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_APV_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT     +
                  i
                 )
                );

      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_APV_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG     +
                  i
                 )
                );
      
      maska_2 = 0;
      for (int i = 0; i < NUMBER_APV_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON     + 
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ���� ����� ����� � ������������
    if ((target_label->configuration & (1<<UROV_BIT_CONFIGURATION)) == 0)
    {
      //������� ����
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STATE);
   
        //������� ���� ������� ����
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_UROV_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_UROV_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //������ �� ������� ��� ���������� �����, �� ���������� �� ����
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ����
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ���(���) ����� ����� � ������������
    if ((target_label->configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
    {
      //������� ���(���)
      target_label->control_zop &= (unsigned int)(~CTR_ZOP_STATE);
   
      //������� ������� ���(���) � ����
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_ZOP1);

      //������� ���� ������� ���(���)
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_ZOP_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���(���)
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���(���)
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� Umin ����� ����� � ������������
    if ((target_label->configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ Umin
      target_label->control_Umin &= (unsigned int)(~(CTR_UMIN1 | CTR_UMIN2));
   
      //������� ������ Umin � ����
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_UMIN1 | CTR_UROV_STARTED_FROM_UMIN2));
      
      //������� ����� ������� Umin
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_UMIN_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG       +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //������ �� ������� ��� ���������� �����, �� ���������� �� Umin
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� Umin
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� Umax ����� ����� � ������������
    if ((target_label->configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ Umax
      target_label->control_Umax &= (unsigned int)(~(CTR_UMAX1 | CTR_UMAX2));

      //������� ������ Umax � ����
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_UMAX1 | CTR_UROV_STARTED_FROM_UMAX2));
   
      //������� ����� ������� Umax
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_UMAX_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG       +
                  i
                 )
                );


      maska_2 = 0;
      for (int i = 0; i < NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //������ �� ������� ��� ���������� �����, �� ���������� �� Umax
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� Umax
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<AVR_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ ���
      target_label->control_avr &= (unsigned int)(~CTR_AVR);
   
      //������� ����� ������� ���
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_AVR_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT       +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_AVR_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG       +
                  i
                 )
                );


      maska_2 = 0;
      for (int i = 0; i < NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //������ �� ������� ��� ���������� �����
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� "�������� ���������" ����� ����� � ������������
    if ((target_label->configuration & (1<<CTRL_PHASE_BIT_CONFIGURATION)) == 0)
    {
      //������� �� "�������� ���������"
      target_label->control_ctrl_phase &= (unsigned int)(~CTR_CTRL_PHASE_U | CTR_CTRL_PHASE_PHI | CTR_CTRL_PHASE_F | CTR_CTRL_PHASE_SEQ_TN1 | CTR_CTRL_PHASE_SEQ_TN2);
   
      //������� ����� ������� "�������� ���������"
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_AVR_SIGNAL_FOR_RANG_INPUT       +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG       +
                  NUMBER_AVR_SIGNAL_FOR_RANG       +
                  i
                 )
                );


      maska_2 = 0;
      for (int i = 0; i < NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //������ �� ������� ��� ���������� �����
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //"��������� �����"
    maska[0] = 0;
    maska[1] = 0;
    unsigned int array_full[N_BIG] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};
    unsigned int *point_to_mask_array;
    for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
    maska_2 = 0;
    if ((target_label->configuration & (1<<EL_BIT_CONFIGURATION)) == 0)
    {
      //��������� �� ������� ��������� �����
      
      //������� ����� ������� ��������� �����
      for (int i = 0; i < NUMBER_EL_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_AVR_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_INPUT +
                  i
                 )
                );
     
      for (int i = 0; i < NUMBER_EL_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG       +
                  NUMBER_AVR_SIGNAL_FOR_RANG        +
                  NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG +
                  i
                 )
                );


      for (int i = 0; i < NUMBER_EL_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_CTRL_PHASE_SIGNAL_FOR_RANG_BUTTON
                           )
               );
      
      point_to_mask_array = array_full;
    }
//    else
//    {
//      //������� ����� ����� ��� ������� ��������� �����, �� ������� � ������������ � ��������� �������
//      unsigned int array_defined_logic[NUMBER_DEFINED_ELEMENTS][2] =
//      {
//        {target_label->number_defined_df , NUMBER_DEFINED_FUNCTIONS},
//        {target_label->number_defined_dt , NUMBER_DEFINED_TRIGGERS },
//        {target_label->number_defined_and, NUMBER_DEFINED_AND      },
//        {target_label->number_defined_or , NUMBER_DEFINED_OR       },
//        {target_label->number_defined_xor, NUMBER_DEFINED_XOR      },
//        {target_label->number_defined_not, NUMBER_DEFINED_NOT      }
//      };
//      const unsigned int input_signals[NUMBER_DEFINED_ELEMENTS]  = {1, 2, 0, 0, 0, 0};
//      const unsigned int others_signals[NUMBER_DEFINED_ELEMENTS] = {2, 3, 1, 1, 1, 1};
//      const unsigned int button_signals[NUMBER_DEFINED_ELEMENTS] = {1, 2, 0, 0, 0, 0};
//      
//      unsigned int input_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
//                                 NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
//                                 NUMBER_MTZ04_SIGNAL_FOR_RANG_INPUT      +
//                                 NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
//                                 NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         +
//                                 NUMBER_TZNP_SIGNAL_FOR_RANG_INPUT       +
//                                 NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
//                                 NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT +
//                                 NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
//                                 NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
//                                 NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       +
//                                 NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT       +
//                                 NUMBER_VMP_SIGNAL_FOR_RANG_INPUT;
//      
//      unsigned int others_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
//                                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
//                                  NUMBER_MTZ04_SIGNAL_FOR_RANG      +
//                                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
//                                  NUMBER_ZZ_SIGNAL_FOR_RANG         +
//                                  NUMBER_TZNP_SIGNAL_FOR_RANG       +
//                                  NUMBER_APV_SIGNAL_FOR_RANG        +
//                                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
//                                  NUMBER_UROV_SIGNAL_FOR_RANG       +
//                                  NUMBER_ZOP_SIGNAL_FOR_RANG        +
//                                  NUMBER_UMIN_SIGNAL_FOR_RANG       +
//                                  NUMBER_UMAX_SIGNAL_FOR_RANG       +
//                                  NUMBER_VMP_SIGNAL_FOR_RANG;
//      
//      unsigned int button_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
//                                  NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
//                                  NUMBER_MTZ04_SIGNAL_FOR_RANG_BUTTON      +
//                                  NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
//                                  NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
//                                  NUMBER_TZNP_SIGNAL_FOR_RANG_BUTTON       +
//                                  NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
//                                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON +
//                                  NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
//                                  NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
//                                  NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON       +
//                                  NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON       +
//                                  NUMBER_VMP_SIGNAL_FOR_RANG_BUTTON;
//      
//      for (unsigned int index = 0; index < NUMBER_DEFINED_ELEMENTS; index++)
//      {
//        //������� ����� ������� ��������� �����
//        for (unsigned int i = 0; i < input_signals[index]*(array_defined_logic[index][1] - array_defined_logic[index][0]); i++)
//          _SET_BIT(maska, (input_shift + input_signals[index]*array_defined_logic[index][0] + i));
//        
//        input_shift += input_signals[index]*array_defined_logic[index][1];
//     
//        for (unsigned int i = 0; i < others_signals[index]*(array_defined_logic[index][1] - array_defined_logic[index][0]); i++)
//          _SET_BIT(maska_1, (others_shift + others_signals[index]*array_defined_logic[index][0] + i));
//        
//        others_shift += others_signals[index]*array_defined_logic[index][1];
//
//        for (unsigned int i = 0; i < button_signals[index]*(array_defined_logic[index][1] - array_defined_logic[index][0]); i++)
//          maska_2 |= 1 << (button_shift + button_signals[index]*array_defined_logic[index][0] + i);
//        
//        button_shift += button_signals[index]*array_defined_logic[index][1];
//      }
//      
//      point_to_mask_array = maska_1;
//    }

    //������ �� ������� ��� ���������� �����, �� ���������� �� ��������� �����
    for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      target_label->ranguvannja_buttons[i] &= ~maska_2;
    //������ �� ������� ��� ���������� �����, �� ���������� �� ��������� �����
    for (int i = 0; i < NUMBER_INPUTS; i++)
    {
      target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
      target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
    }
    //������ �� ������� ��� ���������� ������
    for (int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
    }
    //������ �� ������� ��� ���������� �������������
    for (int i = 0; i < NUMBER_LEDS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
    }
    //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
    for (unsigned int j = 0; j < N_BIG; j++ ) 
    {
      target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
      target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
      target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
      target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
    }
    //������� �� ������� ��� ���������� �������������� �������
    for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~point_to_mask_array[j];
        target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~point_to_mask_array[j];
        target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~point_to_mask_array[j];
      }
    }
    //������� �� ������� ��� ���������� �������������� ������
    for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~point_to_mask_array[j];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~point_to_mask_array[j];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~point_to_mask_array[j];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~point_to_mask_array[j];
      }
    }
  
    //������� �� ������� ��� ���������� ������������ "�"
    for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~point_to_mask_array[j];
    }
  
    //������� �� ������� ��� ���������� ������������ "���"
    for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~point_to_mask_array[j];
    }
  
    //������� �� ������� ��� ���������� ������������ "����.���"
    for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~point_to_mask_array[j];
    }
  
    //������� �� ������� ��� ���������� ������������ "��"
    for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~point_to_mask_array[j];
    }
  }
  
  return error_window;
}
/*****************************************************/

///*****************************************************/
////������� ���������� ������ ��� ��� ������� �������� ��������� �����
///*****************************************************/
//void action_after_changing_number_el(__SETTINGS *target_label, unsigned int element)
//{
//  unsigned int maska[N_SMALL] = {0, 0}, maska_1[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0}, maska_2 = 0;
//
//  //������� ����� ����� ��� ������� ��������� �����, �� ������� � ������������ � ��������� �������
//  unsigned int array_defined_logic[NUMBER_DEFINED_ELEMENTS][2] =
//  {
//    {target_label->number_defined_df , NUMBER_DEFINED_FUNCTIONS},
//    {target_label->number_defined_dt , NUMBER_DEFINED_TRIGGERS },
//    {target_label->number_defined_and, NUMBER_DEFINED_AND      },
//    {target_label->number_defined_or , NUMBER_DEFINED_OR       },
//    {target_label->number_defined_xor, NUMBER_DEFINED_XOR      },
//    {target_label->number_defined_not, NUMBER_DEFINED_NOT      }
//  };
//  const unsigned int input_signals[NUMBER_DEFINED_ELEMENTS]  = {1, 2, 0, 0, 0, 0};
//  const unsigned int others_signals[NUMBER_DEFINED_ELEMENTS] = {2, 3, 1, 1, 1, 1};
//  const unsigned int button_signals[NUMBER_DEFINED_ELEMENTS] = {1, 2, 0, 0, 0, 0};
//  
//  unsigned int input_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
//                             NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
//                             NUMBER_MTZ04_SIGNAL_FOR_RANG_INPUT      +
//                             NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
//                             NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         +
//                             NUMBER_TZNP_SIGNAL_FOR_RANG_INPUT       +
//                             NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
//                             NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT +
//                             NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
//                             NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
//                             NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       +
//                             NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT       +
//                             NUMBER_VMP_SIGNAL_FOR_RANG_INPUT;
//      
//  unsigned int others_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
//                              NUMBER_MTZ_SIGNAL_FOR_RANG        +
//                              NUMBER_MTZ04_SIGNAL_FOR_RANG      +
//                              NUMBER_ZDZ_SIGNAL_FOR_RANG        +
//                              NUMBER_ZZ_SIGNAL_FOR_RANG         +
//                              NUMBER_TZNP_SIGNAL_FOR_RANG       +
//                              NUMBER_APV_SIGNAL_FOR_RANG        +
//                              NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
//                              NUMBER_UROV_SIGNAL_FOR_RANG       +
//                              NUMBER_ZOP_SIGNAL_FOR_RANG        +
//                              NUMBER_UMIN_SIGNAL_FOR_RANG       +
//                              NUMBER_UMAX_SIGNAL_FOR_RANG       +
//                              NUMBER_VMP_SIGNAL_FOR_RANG;
//      
//  unsigned int button_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
//                              NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
//                              NUMBER_MTZ04_SIGNAL_FOR_RANG_BUTTON      +
//                              NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
//                              NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
//                              NUMBER_TZNP_SIGNAL_FOR_RANG_BUTTON       +
//                              NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
//                              NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON +
//                              NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
//                              NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
//                              NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON       +
//                              NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON       +
//                              NUMBER_VMP_SIGNAL_FOR_RANG_BUTTON;
//      
//  for (unsigned int index = 0; index < element; index++)
//  {
//    input_shift  += input_signals[index]*array_defined_logic[index][1];
//    others_shift += others_signals[index]*array_defined_logic[index][1];
//    button_shift += button_signals[index]*array_defined_logic[index][1];
//  }
//  
//  //������� ����� ������� �������� ��������� �����
//  for (unsigned int i = 0; i < input_signals[element]*(array_defined_logic[element][1] - array_defined_logic[element][0]); i++)
//    _SET_BIT(maska, (input_shift + input_signals[element]*array_defined_logic[element][0] + i));
//    
//  for (unsigned int i = 0; i < others_signals[element]*(array_defined_logic[element][1] - array_defined_logic[element][0]); i++)
//    _SET_BIT(maska_1, (others_shift + others_signals[element]*array_defined_logic[element][0] + i));
//    
//  for (unsigned int i = 0; i < button_signals[element]*(array_defined_logic[element][1] - array_defined_logic[element][0]); i++)
//    maska_2 |= 1 << (button_shift + button_signals[element]*array_defined_logic[element][0] + i);
//    
//  //������ �� ������� ��� ���������� �����, �� ���������� �� ��������� �����
//  for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
//    target_label->ranguvannja_buttons[i] &= ~maska_2;
//  //������ �� ������� ��� ���������� �����, �� ���������� �� ��������� �����
//  for (int i = 0; i < NUMBER_INPUTS; i++)
//  {
//    target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
//    target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
//  }
//  //������ �� ������� ��� ���������� ������
//  for (int i = 0; i < NUMBER_OUTPUTS; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
//  }
//  //������ �� ������� ��� ���������� �������������
//  for (int i = 0; i < NUMBER_LEDS; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
//  }
//  //������ �� ������� ��� ���������� �����������, ����������� ����������, ����� ��������� � ���������
//  for (unsigned int j = 0; j < N_BIG; j++ ) 
//  {
//    target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
//    target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
//    target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
//    target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
//  }
//  //������� �� ������� ��� ���������� �������������� �������
//  for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) 
//    {
//      target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
//      target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
//      target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
//    }
//  }
//  //������� �� ������� ��� ���������� �������������� ������
//  for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) 
//    {
//      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
//      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
//      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
//      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
//    }
//  }
//  
//  //������� �� ������� ��� ���������� ������������ "�"
//  for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
//  }
//  
//  //������� �� ������� ��� ���������� ������������ "���"
//  for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
//  }
//  
//  //������� �� ������� ��� ���������� ������������ "����.���"
//  for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
//  }
//  
//  //������� �� ������� ��� ���������� ������������ "��"
//  for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
//  }
//}
///*****************************************************/

/*****************************************************/
//�������, ��� ������� ������� �� ��������, ���� ����������� �� ������� � RS-485 ����� � ����������� �����������
/*****************************************************/
void calculate_namber_bit_waiting_for_rs_485(void)
{
  unsigned int number_bits_rs_485_waiting_tmp = 10;
  
  //ϳ��������� ������� �� � ����
  if (current_settings.pare_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  if (current_settings.number_stop_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  
  //���������� ��������
  unsigned int multiplicator;
  switch (current_settings.speed_RS485)
  {
  case 0:
    {
      multiplicator = 12; //9600
      break;
    }
  case 1:
    {
      multiplicator = 8;  //14400
      break;
    }
  case 2:
    {
      multiplicator = 6;  //19200
      break;
    }
  case 3:
    {
      multiplicator = 4;  //28800
      break;
    }
  case 4:
    {
      multiplicator = 3;  //38400
      break;
    }
  case 5:
    {
      multiplicator = 2;  //57600
      break;
    }
  default:
    {
      multiplicator = 1;  //115200
      break;
    }
  }
  number_bits_rs_485_waiting_tmp *= (multiplicator*current_settings.time_out_1_RS485);
  number_bits_rs_485_waiting_tmp /= 10;
  
  number_bits_rs_485_waiting = number_bits_rs_485_waiting_tmp;
}
/*****************************************************/

/******************************************************
//�������, ��� ����� ���� � ���������� � ������� ����� ��������� � EEPROM
-----------------------------------------------------
setting_rang: 0 - ����� �������
              1 - ����� ����������
              2 - ���������� ��� ��������

source:       0 - ������� ���������
              1 - ���������
              2 - USB
              3 - RS-485
---------------------------------------------------
******************************************************/
void fix_change_settings(unsigned int setting_rang, unsigned int source)
{
  if (setting_rang < 2)
  {
    unsigned char *point_to_target;
  
    if (setting_rang == 0) point_to_target = (&current_settings)->time_setpoints;
    else point_to_target = (&current_settings)->time_ranguvannja;
    
    //�������� ��� ������� ���
    unsigned char *label_to_time_array;
    if (copying_time == 0) label_to_time_array = time;
    else label_to_time_array = time_copy;
    for (unsigned int i = 0; i < 7; i++) *(point_to_target + i) = *(label_to_time_array + i);
    *(point_to_target + 7) = (unsigned char)(source & 0xff);
  }
  
  //�������, �� ������� �������� � �� ����� ���� � ������� ������� ��������� � ������� � ���� ������ ������� �������
  changed_settings = CHANGED_ETAP_ENDED;
  if (_CHECK_SET_BIT(active_functions, RANG_SETTINGS_CHANGED) == 0) current_settings_interfaces = current_settings;
  
  //��������� ����� � EEPROM
  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
}
/*****************************************************/

/*****************************************************/
/*
��������� �������� ��� � ������������ ����� ����������
*/
/*****************************************************/
unsigned int set_new_settings_from_interface(unsigned int source)
{
  unsigned int error = 0;
  
  //�������� �� ��������� ���
  unsigned char *label_to_time_array;
  if (copying_time == 0) label_to_time_array = time;
  else label_to_time_array = time_copy;
  
  if ((type_of_settings_changed & (1 << DEFAULT_SETTINGS_SET_BIT)) != 0)
  {
    for (unsigned int i = 0; i < 7; i++) current_settings_interfaces.time_setpoints[i] = current_settings_interfaces.time_ranguvannja[i] = *(label_to_time_array + i);
    current_settings_interfaces.time_setpoints[7] = current_settings_interfaces.time_ranguvannja[7] = 0;
  }
  
  if ((type_of_settings_changed & (1 << SETTINGS_DATA_CHANGED_BIT)) != 0)
  {
    for (unsigned int i = 0; i < 7; i++) current_settings_interfaces.time_setpoints[i] = *(label_to_time_array + i);
    current_settings_interfaces.time_setpoints[7] = source;
  }
  
  if ((type_of_settings_changed & (1 << RANGUVANNJA_DATA_CHANGED_BIT)) != 0)
  {
    for (unsigned int i = 0; i < 7; i++) current_settings_interfaces.time_ranguvannja[i] = *(label_to_time_array + i);
    current_settings_interfaces.time_ranguvannja[7] = source;
  }
  
  unsigned int reconfiguration_RS_485 = 0, reconfiguration_RS_485_with_reset_usart = 0;
  if (
      (current_settings.speed_RS485 != current_settings_interfaces.speed_RS485) ||
      (current_settings.pare_bit_RS485 != current_settings_interfaces.pare_bit_RS485) ||
      (current_settings.number_stop_bit_RS485 != current_settings_interfaces.number_stop_bit_RS485) ||
      (current_settings.time_out_1_RS485 != current_settings_interfaces.time_out_1_RS485)
     )
  {
    //�������, �� ����� ����������������� ��������� RS-485
    reconfiguration_RS_485 = 1;
    
    if (
        (current_settings.speed_RS485 != current_settings_interfaces.speed_RS485) ||
        (current_settings.pare_bit_RS485 != current_settings_interfaces.pare_bit_RS485) ||
        (current_settings.number_stop_bit_RS485 != current_settings_interfaces.number_stop_bit_RS485)
       )
    {
      //�������, �� ����� ����������������� USART ��� ���������� RS-485
      reconfiguration_RS_485_with_reset_usart = 1;
    }
  }
  
  unsigned int change_timeout_ar = 0;
  if (
      (current_settings.prefault_number_periods != current_settings_interfaces.prefault_number_periods) ||
      (current_settings.postfault_number_periods != current_settings_interfaces.postfault_number_periods)
     ) 
  {
    //�������, �� ��������� �� ����� ���� �������� 䳿 �� ��� ������� �������� ����������� ����������
    change_timeout_ar = 1;
    
    unsigned int semaphore_read_state_ar_record_copy = semaphore_read_state_ar_record;

    /*������������ ������� - ���� ����� ������ � ����, �� ���� ������ ������ ���� 
    ���� �� ��� - �� �� ��� ���� ������������ ����� ����� �������� �� �����, ���� � ��� ��� ���� �����,
    �� �� �� �������������� �, �������, ��������� ������ ����������� ���������� �� �����*/
    semaphore_read_state_ar_record = 1;

    if (
        (state_ar_record == STATE_AR_NO_RECORD      ) ||
        (state_ar_record == STATE_AR_TEMPORARY_BLOCK)
       )   
    {
      /*�� ����� ������ �� ��� ����� �������� ����������� ��������� �������,
      ���� ��� ���� ������� ��������� ��������� ������������ ���� ������
      ����������� ���������� � ������������ �����*/
      state_ar_record = STATE_AR_TEMPORARY_BLOCK; 
      
    }
    else
    {
      //�������� ��������� ����������, �� ��� ������ ����������� ����������
      error = ERROR_SLAVE_DEVICE_BUSY;
      semaphore_read_state_ar_record = semaphore_read_state_ar_record_copy;
    }
  }
  
  unsigned int set_password_USB = false;
  if (
      (current_settings.password_interface_USB != current_settings_interfaces.password_interface_USB) &&
      (current_settings_interfaces.password_interface_USB != 0)  
     )   
  {
    set_password_USB = true;
  }
  
  unsigned int set_password_RS485 = false;
  if (
      (current_settings.password_interface_RS485 != current_settings_interfaces.password_interface_RS485) &&
      (current_settings_interfaces.password_interface_RS485 != 0)  
     )   
  {
    set_password_RS485 = true;
  }
  
  if (error == 0)
  {
    if ((type_of_settings_changed & (1 << DEFAULT_SETTINGS_SET_BIT)) != 0)
    {
      //���������� ���� � ��������� ����
      for(unsigned int i=0; i<MAX_LEVEL_MENU; i++)
      {
        if ((i == EKRAN_LEVEL_PASSWORD) || (i == EKRAN_LEVEL_SET_NEW_PASSWORD1) || (i == EKRAN_LEVEL_SET_NEW_PASSWORD2)) position_in_current_level_menu[i] = INDEX_LINE_NUMBER_1_FOR_LEVEL_PASSWORD;
        else  position_in_current_level_menu[i] = 0;
        previous_level_in_current_level_menu[i] = -1;
      }
  
      //���������� ����������� ����� ������
      current_ekran.current_level = EKRAN_MAIN;
      current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
      current_ekran.position_cursor_y = current_ekran.index_position;
      current_ekran.edition = 0;
      current_ekran.cursor_on = 0;
      current_ekran.cursor_blinking_on = 0;  
    }
    
    if (set_password_USB   != false) password_set_USB   = 1;
    if (set_password_RS485 != false) password_set_RS485 = 1;
    
    //�������, �� ���� ��������� ����� ������ �����
    changed_settings = CHANGED_ETAP_EXECUTION;
              
    //������� ������ ���� � ������ ���������
    current_settings = current_settings_interfaces;
    if (reconfiguration_RS_485 != 0)
    {
      //ϳ��������� ���� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
      calculate_namber_bit_waiting_for_rs_485();
      //����������� ������� ��� ������������������ RS-485
      if (reconfiguration_RS_485_with_reset_usart != 0) make_reconfiguration_RS_485 = 0xff;
    }
    if (
        (state_ar_record == STATE_AR_TEMPORARY_BLOCK) ||
        (semaphore_read_state_ar_record != 0)  
       )
    {
      /*
      �� �������� ���� ����, ���� �������������� ������� ���������,
      ��� ���� ��������� ������ ����������� ��� ������������� �������
      ����������� ����������.
      ��� ����� ������ �� ����, �� ����� state_ar_record ���� �������
      STATE_AR_TEMPORARY_BLOCK � ����� semaphore_read_state_ar_record
      �� ���� ����. ��� �� 
      ����� �� ����������� - �� ����� ������������� ������,
      �� ��������� ������������ ���� ���� ���������������� ������.
      */
      if(
         ((change_timeout_ar != 0)) &&
         (state_ar_record == STATE_AR_TEMPORARY_BLOCK) &&
         (semaphore_read_state_ar_record != 0)  
        )
      {
        //�������� 䳿 �� ��� ������� �������� ����������� ����������
        actions_after_changing_tiomouts_ar();

        //������������ ������ ����������� ����������
        state_ar_record = STATE_AR_NO_RECORD;

        //������ �������
        semaphore_read_state_ar_record = 0;
      }
      else
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(41);
      }
    }

    fix_change_settings(2, source);

    //����������� �������, �� �� ����� ����� �������� ����������
    new_state_keyboard |= (1<<BIT_REWRITE);
  }
  
  return error;
}
/*****************************************************/

/******************************************************
³��������� �������� �������
******************************************************/
void restore_trigger_functions(unsigned int *active_functions_point)
{
  active_functions[RANG_DT1_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT1_OUT);
  active_functions[RANG_DT2_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT2_OUT);
  active_functions[RANG_DT3_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT3_OUT);
  active_functions[RANG_DT4_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT4_OUT);

  unsigned int tmp_state;

  tmp_state = _CHECK_SET_BIT(active_functions_point, RANG_BLOCK_AVR);
  trigger_AVR_0 |= ((tmp_state != 0) << 0);
  active_functions[RANG_BLOCK_AVR >> 5] |= tmp_state;
}
/*****************************************************/

/*****************************************************/
//������� ���� ���������� �� ����������
/*****************************************************/
void changing_diagnostyka_state(void)
{
  /*****
  ��������� ����� ���� ����������
  
  ��������:
  - ������� � �������� ������ ���, �� ����� ������� � �� ����� ��������� � 
    ����������
  - ϳ��� ����� ��������� ���� ��������� �������� ������ ��������� (�� 
    �������� �����!!!) ��� ��� � �������� ������
  - ���� , �� �� ������ ���������/��������������� ������� � ���������� ������
    (���� � ������ ����� ��������� ������������� ������� �������� �� 
    ������������� ��� ���, �� ���� �� ���������, � ����������� ��� ���������� 
    ������� ���� �������)

  - �������� ������� ��� � ���� ������������, �� �������� ��䳿 �� ������ 
    �������� �� ��������
  *****/
  unsigned int clear_diagnostyka_tmp[3], set_diagnostyka_tmp[3];
  
  clear_diagnostyka_tmp[0] = clear_diagnostyka[0];
  clear_diagnostyka_tmp[1] = clear_diagnostyka[1];
  clear_diagnostyka_tmp[2] = clear_diagnostyka[2];

  set_diagnostyka_tmp[0] = set_diagnostyka[0];
  set_diagnostyka_tmp[1] = set_diagnostyka[1];
  set_diagnostyka_tmp[2] = set_diagnostyka[2];
    
  diagnostyka[0] &= (unsigned int)(~clear_diagnostyka_tmp[0]); 
  diagnostyka[0] |= set_diagnostyka_tmp[0]; 

  diagnostyka[1] &= (unsigned int)(~clear_diagnostyka_tmp[1]); 
  diagnostyka[1] |= set_diagnostyka_tmp[1]; 

  diagnostyka[2] &= (unsigned int)(~clear_diagnostyka_tmp[2]); 
  diagnostyka[2] |= set_diagnostyka_tmp[2]; 
  
  diagnostyka[2] &= USED_BITS_IN_LAST_INDEX; 

  clear_diagnostyka[0] &= (unsigned int)(~clear_diagnostyka_tmp[0]);
  clear_diagnostyka[1] &= (unsigned int)(~clear_diagnostyka_tmp[1]);
  clear_diagnostyka[2] &= (unsigned int)(~clear_diagnostyka_tmp[2]);
  
  set_diagnostyka[0] &= (unsigned int)(~set_diagnostyka_tmp[0]);
  set_diagnostyka[1] &= (unsigned int)(~set_diagnostyka_tmp[1]);
  set_diagnostyka[2] &= (unsigned int)(~set_diagnostyka_tmp[2]);
  /*****/
  
  //���������, �� �������� ����
  unsigned int value_changes[3], diagnostyka_now[3];
  /*
  ������ ���� ��������� ����������, �� �� ������� ������ �� ���������� ��������,
  ���� �� ��� ������ ���� ��������� ��� ��������, �� �� �� ��������� � ��� �������
  */
  diagnostyka_now[0] = diagnostyka[0];
  diagnostyka_now[1] = diagnostyka[1];
  diagnostyka_now[2] = diagnostyka[2];
  value_changes[0] = diagnostyka_before[0] ^ diagnostyka_now[0];
  value_changes[1] = diagnostyka_before[1] ^ diagnostyka_now[1];
  value_changes[2] = diagnostyka_before[2] ^ diagnostyka_now[2];
  
  /*
  � ��������� ���������� ���� �� ������������ ����� ������� � ��������� ����� � ��������
  ����� ���� �� " ����� ����.    " � " ������� ����.  "
  ���� ������� � ��������� � ��������� �� �������� � ��� ���� �������� ���, �� ���� "��������������"
  */
  
  /*****/
  //���� " ����� ����.    "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_START_SYSTEM_BIT) != 0)
  {
    //����������� �� ���� " ����� ����.    " ������ ��� ����
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_START_SYSTEM_BIT) == 0)
    {
      /*
      ����� ���� ��䳿 " ����� ����.    " � ���������� ����
      ���� ������ ���, ��� �� ���� �� ������ � ��������� ���������� ���� ����� ����������
      - ������ ������������ �� ��� ���� ����� ����������
      - ������ �����������, �� � ������������ ���� ���������� �� ���� ���� ��������
      - � �������� ���� ���������� ����� ����� �� �����, �� ��� ������ � ����������
      */
      _CLEAR_BIT(value_changes, EVENT_START_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_START_SYSTEM_BIT);
    }
  }
  /*****/
  
  /*****/
  //���� " ������� ����.  "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT) != 0)
  {
    //����������� �� ���� " ������� ����.  " ������ ��� ����
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_RESTART_SYSTEM_BIT) == 0)
    {
      /*
      ����� ���� ��䳿 " ������� ����.  " � ���������� ����
      ���� ������ ���, ��� �� ���� �� ������ � ��������� ���������� ���� ����� ����������
      - ������ ������������ �� ��� ���� ����� ����������
      - ������ �����������, �� � ������������ ���� ���������� �� ���� ���� ��������
      - � �������� ���� ���������� ����� ����� �� �����, �� ��� ������ � ����������
      */
      _CLEAR_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_RESTART_SYSTEM_BIT);
    }
  }
  /*****/

  //����������, �� ����� ���������� 䳿 ��� ��� ����������
  if (
      (value_changes[0] != 0) ||
      (value_changes[1] != 0) ||
      (value_changes[2] != 0)
     )
  {
    //� ���, �� ����� ����������, ��� �����
    
    /*****/
    //��� ��������� ������� ����� � ��������� ���������� �������
    /*****/
    if (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) == 0)
    {
      /*
      ����� ����� ������ ����� ���, ���� ���������� �� ���� ����������� 
      ������������ ������, ������ ������, ���� ����� � ��������� ���������� ����
      ������ ���� ��� ������������ ������
      */
      
      //��������� ������� ��������� ������ � ����� ��� ���������� ���������� ����
      int number_empty_cells;
      unsigned int head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
      number_empty_cells = (int)(((unsigned int)tail) - ((unsigned int)head));
      while (number_empty_cells <= 0) number_empty_cells += MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
      if (number_empty_cells == 1)
      {
        //�� � ������� ����� ������, �� �������, �� � ��� ������� ���������� ����� ���������� ������
        _SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT);
        /*
        �������� ���� ����� ����������, ��� ����� ��������� � ������ ������� ,����
        ������ ��������� ���� ��������� ����������, ��� ���� ��������� � � ���� �� ��������
        �� ���������� ��������� ����� ���������� �� ������� ���� ������� �
        ���������, �� ����� �� ������ ����������
        */
        diagnostyka_now[0] = diagnostyka[0];
        diagnostyka_now[1] = diagnostyka[1];
        diagnostyka_now[2] = diagnostyka[2];
        
        //ϳ��������� ���� ������� ��� � ����������
        value_changes[0] = diagnostyka_before[0] ^ diagnostyka_now[0];
        value_changes[1] = diagnostyka_before[1] ^ diagnostyka_now[1];
        value_changes[2] = diagnostyka_before[2] ^ diagnostyka_now[2];
      }

      //���������� ������� ��� �������
      unsigned int number_changes = 0;
      for(unsigned int i = 0; i < (8*sizeof(value_changes)); i++)
      {
        if (_CHECK_SET_BIT(value_changes, i) != 0) number_changes++;
      }

      if(number_changes != 0)
      {
        /*
        ���������� ���� ���� ��������, �� �� ������ ����������� ��� ������������ ������
        FIFO ��� ������ ���������� ���������� ����  � �� ���� ����� ����, ��� ��� �����
        � ����� ���� ����� ������, ���� �� ����� ��������� ����������� ��� ������������.
        ���� �� �� ������ ����� �� ����������� - ���� � �� ������ ������ ������ ������, 
        �� �������� � ���� ���� ����
        */
        
        //��������� ������ � ����� ������ ���������� ������� � ����� ���� ������ ����������� ���
        unsigned int index_into_buffer_pr_err = head*SIZE_ONE_RECORD_PR_ERR;
      
        //������� ���� ������� ������
        buffer_pr_err_records[index_into_buffer_pr_err + 0] = LABEL_START_RECORD_PR_ERR;

        //��� �������� ���� � ����������
        if(
           (_CHECK_SET_BIT(diagnostyka, EVENT_START_SYSTEM_BIT   ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_RESTART_SYSTEM_BIT ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT    ) == 0)
          )
        {
          //��� �������� ����� ����������� ���� - ����� ��������� ��� � ��� �
          unsigned char *label_to_time_array;
          if (copying_time == 0) label_to_time_array = time;
          else label_to_time_array = time_copy;
          for(unsigned int i = 0; i < 7; i++) buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = *(label_to_time_array + i);
        }
        else
        {
          //�� �� �������� ����� ����������� ���� - ���� ������ �� ���� �������� ������ 0xff, � ����, ���� ��������� ��� ���������, �� �� �� ���� ��������
          for(unsigned int i = 0; i < 7; i++)  buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = 0xff;
        }

        buffer_pr_err_records[index_into_buffer_pr_err + 8] = number_changes & 0xff;
      
        //�������� ��������� ���� ����������
        buffer_pr_err_records[index_into_buffer_pr_err + 9 ] =  diagnostyka_before[0]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 10] = (diagnostyka_before[0] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 11] = (diagnostyka_before[0] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 12] = (diagnostyka_before[0] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 13] =  diagnostyka_before[1]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 14] = (diagnostyka_before[1] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 15] = (diagnostyka_before[1] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 16] = (diagnostyka_before[1] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 17] =  diagnostyka_before[2]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 18] = (diagnostyka_before[2] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 19] = (diagnostyka_before[2] >> 16) & 0xff;

        //�������� �������� ���� ����������
        buffer_pr_err_records[index_into_buffer_pr_err + 20] =  diagnostyka_now[0]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 21] = (diagnostyka_now[0] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 22] = (diagnostyka_now[0] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 23] = (diagnostyka_now[0] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 24] =  diagnostyka_now[1]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 25] = (diagnostyka_now[1] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 26] = (diagnostyka_now[1] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 27] = (diagnostyka_now[1] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 28] =  diagnostyka_now[2]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 29] = (diagnostyka_now[2] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 30] = (diagnostyka_now[2] >> 16) & 0xff;
        
        /*
        � ��������� ���������� ���� �� ������������ ����� ������� � ��������� ����� � ��������
        ����� ��䳿 �� " �������.����.  " � �� ���� �� �� ���� �������� � ������� ����������,
        �� ��, ��������, ����, ��� ���� ���� �� ���������� ��������� ������� � ������.
        ����� �� ���� "������������ ������ ������"
        ���� ������� � ��������� � ������� �� ������� � ����� �������� ��� �� � �������� ���������,
        ��� ���� ����� ���� ���������� � �����. ���� ������� �� ��������� ���� ����������, ��� � � �����
        ����������, ���� ������� �� ������� ���� ���� ����������
        */
        if (_CHECK_SET_BIT(value_changes, EVENT_STOP_SYSTEM_BIT) != 0)
        {
          /*
          C��� ��䳿 " �������.����.  " ������� (����������� ����� ���������� �������������
          ���� � ��������� ����� � �������� ����)
          ���� ������ ��� ��������
          - ������ ������������ �� � �����, ���� ����� ���� ���������� � ����� ������������ �����
          - ������ ������������ �� � �����, ���� ������� �� ������� ���� ���� ����������
          */
          _CLEAR_BIT(diagnostyka_now, EVENT_STOP_SYSTEM_BIT);
          _CLEAR_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT);
        }

        //Գ����� ��������� ����, ���� �� ��� �������� � ������� ����� ������ ��������� ��� ����
        diagnostyka_before[0] = diagnostyka_now[0];
        diagnostyka_before[1] = diagnostyka_now[1];
        diagnostyka_before[2] = diagnostyka_now[2];

        //ϳ������������� �� ������� ������ � ��������� ���������� ����
          unsigned int next_index_into_fifo_buffer = head + 1;
          while(next_index_into_fifo_buffer >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) next_index_into_fifo_buffer -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
          
          //������������ ���� �������� ������ ������ FIFO 
          head_fifo_buffer_pr_err_records = next_index_into_fifo_buffer;
      }
    }
    /*****/
  }
}
/*****************************************************/

/*****************************************************/
//ϳ�������� ������� ����������� �������� � ������ ���'�� ������� ��� ����������� ���������� source
/*****************************************************/
unsigned int count_number_set_bit(unsigned int* source, unsigned int total_number)
{
  unsigned int count = 0;
  unsigned int offset, shift;
  
  for (unsigned int i = 0; i < total_number; i++)  
  {
    offset = i >> 5; //�� �, ��������, ������ �� 32
    shift  = (i & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32
    if ( ( (*(source + offset))  & ((unsigned int)(1 << shift)) ) != 0 ) count++;
  }

  return count;
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������
/*****************************************************/
void control_settings(void)
{
  unsigned char crc_settings_tmp = 0, temp_value_1, temp_value_2;
  unsigned char  *point_1 = (unsigned char*)(&current_settings); 
  unsigned char  *point_2 = (unsigned char*)(&current_settings_prt); 
  unsigned int i = 0, difference = 0;
  while ((difference == 0) && (i < sizeof(__SETTINGS)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_settings_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }
  
  if ((difference == 0) && (crc_settings == crc_settings_tmp))
  {
    //�������� ����������� ������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������
/*****************************************************/
void control_ustuvannja(void)
{
  unsigned char crc_ustuvannja_tmp = 0, temp_value_1, temp_value_2;
  unsigned char  *point_1; 
  unsigned char  *point_2; 
  unsigned int i = 0, difference = 0;

  /*
  � ��������� ���� ������� ������������� ���� ������ �������� �����������,
  ���� ����� ����� ���� unsigned int
  */
  unsigned int adjustment_id_tmp = ADJUSTMENT_ID;
  point_1 = (unsigned char*)(&adjustment_id_tmp); 
  while (i < sizeof(unsigned int))
  {
    temp_value_1 = *(point_1);
    crc_ustuvannja_tmp += temp_value_1;
    point_1++;
    i++;
  }
  
  point_1 = (unsigned char*)(&ustuvannja); 
  point_2 = (unsigned char*)(&ustuvannja_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(ustuvannja)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  point_1 = (unsigned char*)(&phi_ustuvannja); 
  point_2 = (unsigned char*)(&phi_ustuvannja_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(phi_ustuvannja)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  point_1 = (unsigned char*)(&phi_ustuvannja_sin_cos); 
  point_2 = (unsigned char*)(&phi_ustuvannja_sin_cos_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(phi_ustuvannja_sin_cos)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  /*
  �� ����� ������������ ����������� ������� ������, ���� ������ � ����������� ��������,
  �� �������� �������, �� �� ������ ����������������� � ������������� �� ����� ��������,
  �� ���� ������ �� ����
  */
  point_1 = (unsigned char*)(&serial_number_dev); 
  i = 0;
  while ((difference == 0) && (i < sizeof(serial_number_dev)))
  {
    temp_value_1 = *(point_1);
    crc_ustuvannja_tmp += temp_value_1;
    point_1++;
    i++;
  }
  
  if ((difference == 0) && (crc_ustuvannja == crc_ustuvannja_tmp))
  {
    //�������� ����������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ������� ����������
/*****************************************************/
void control_trg_func(void)
{
  unsigned char crc_trg_func_tmp = 0, temp_value_1;
  unsigned char  *point; 
  unsigned int i;
  
  temp_value_1 = misceve_dystancijne_ctrl & 0xff;
  crc_trg_func_tmp += temp_value_1;
  
  point = (unsigned char*)(trigger_active_functions_ctrl);
  i = 0;  
  while (i < sizeof(trigger_active_functions_ctrl))
  {
    temp_value_1 = *(point);
    crc_trg_func_tmp += temp_value_1;
    point++;
    i++;
  }
  
  if (crc_trg_func == crc_trg_func_tmp)
  {
    //�������� ����������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������� �� �����������
/*****************************************************/
unsigned int control_info_rejestrator(__INFO_REJESTRATOR* info_rejestrator_point, unsigned char crc_info_rejestrator)
{
  unsigned int result;
  unsigned char crc_info_rejestrator_tmp = 0, temp_value_1;
  unsigned char  *point = (unsigned char*)(info_rejestrator_point); 
  unsigned int i = 0;
  while (i < sizeof(__INFO_REJESTRATOR))
  {
    temp_value_1 = *(point);
    crc_info_rejestrator_tmp += temp_value_1;
    point++;
    i++;
  }
  
  if (crc_info_rejestrator == crc_info_rejestrator_tmp)
  {
    //�������� ����������� ���������� ������� ������
    result = 1;    
  }
  else
  {
    //�������� ����������� ���������� �� �������
    result = 0;    
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ��������� �������
/*****************************************************/
void control_resurs(void)
{
  unsigned char crc_resurs_tmp = 0, temp_value;
  unsigned char *point;
  
  point = (unsigned char*)(&resurs_vymykacha_ctrl); 
  for (unsigned int i = 0; i < sizeof(resurs_vymykacha_ctrl); i++)
  {
    temp_value = *(point);
    crc_resurs_tmp += temp_value;
    point++;
  }

  point = (unsigned char*)(&resurs_vidkljuchennja_ctrl); 
  for (unsigned int i = 0; i < sizeof(resurs_vidkljuchennja_ctrl); i++)
  {
    temp_value = *(point);
    crc_resurs_tmp += temp_value;
    point++;
  }

  if (crc_resurs_ctrl == crc_resurs_tmp)
  {
    //�������� ����������� ������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_RESURS_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_RESURS_EEPROM_CONTROL_BIT);
  }
  
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����� � ��������� __DATE__
/*****************************************************/
int str_to_int_DATE_Mmm(void)
{
  static const char month_names[12*3] = "JanFebMarAprMayJunJulAugSepOctNovDec";
  
  int i = 0;
  while(i < 12)
  {
    if (
        (month_names[3*i + 0] == __DATE__[0]) &&
        (month_names[3*i + 1] == __DATE__[1]) &&
        (month_names[3*i + 2] == __DATE__[2])
       )
    {
      break;
    }
    
    i++;
  } 
  
  if (i < 12)
  { 
    i += 1; /*��� ��������� ������ ���� � "1", � �� � "0"*/
    return ((i / 10) << 4) + (i % 10);
  }
  else return 0;
}
/*****************************************************/

/*****************************************************/
/*****************************************************/
//
/*****************************************************/
