#include "header.h"

/*****************************************************/
//����� ������ ������ ��� ���������
/*****************************************************/
inline void find_new_ADC_canal_to_read(unsigned int command_word_adc_diff, unsigned int *point_active_index_command_word_adc)
{
  unsigned int command_word_adc_diff_tmp = command_word_adc_diff;
  
  unsigned int command_word_adc_diff_val_1 = command_word_adc_diff_tmp & maska_canaliv_fapch_1;
  unsigned int command_word_adc_diff_val_2 = command_word_adc_diff_tmp & maska_canaliv_fapch_2;
    
  if (
      ((status_adc_read_work & DATA_VAL_2_READ) != 0) &&
      (command_word_adc_diff_val_2 != 0) &&
      (
       ((status_adc_read_work & DATA_VAL_1_READ) == 0) ||
       (command_word_adc_diff_val_1 == 0) ||
       (command_word_adc_diff_val_1 == maska_canaliv_fapch_1)
      )   
     )  
  {
    command_word_adc_diff_tmp = command_word_adc_diff_val_2;
  }
  else
  {
    if (
        ((status_adc_read_work & DATA_VAL_1_READ) != 0) &&
        (command_word_adc_diff_val_1 != 0) 
       )  
    {
      command_word_adc_diff_tmp = command_word_adc_diff_val_1;
    }
    else
    {
      command_word_adc_diff_tmp &= (unsigned int)(~(maska_canaliv_fapch_1 | maska_canaliv_fapch_2));
    }
  }
  
  while ((command_word_adc_diff_tmp & (1 << (*point_active_index_command_word_adc))) == 0)
  {
    /*
    �� �� �������� ������, ���� ����� ������������
    */
    *point_active_index_command_word_adc = (*point_active_index_command_word_adc + 1) % NUMBER_INPUTs_ADCs;
  }
}
/*****************************************************/

/*****************************************************/
//��������� �������� ����� � ���
/*****************************************************/
void control_reading_ADCs(unsigned int TN1_TN2_meas)
{
  //���������� ������ �������� ����� � �������� �� ������ ����� ������������
  if (adc_DATA_VAL_1_read != 0)
  {
    adc_DATA_VAL_1_read = false;
    status_adc_read_work |= DATA_VAL_1_READ;
      
    /*
    ������ �� ���� ���� ��������������� ������� ����� �������������� �� 
    ����� ������ �� ����������� ������� ������ ������� ���������
    */
    command_word_adc      &= (unsigned int)(~maska_canaliv_fapch_1);
    command_word_adc_work &= (unsigned int)(~maska_canaliv_fapch_1);
        
    command_word_adc |= READ_DATA_VAL_1;
    if (TN1_TN2_meas != 1) command_word_adc |= READ_I;
  }

  if (adc_DATA_VAL_2_read != 0)
  {
    adc_DATA_VAL_2_read = false;
    status_adc_read_work |= DATA_VAL_2_READ;
      
    /*
    ������ �� ���� ���� ��������������� ������������ �������������� �� 
    ����� ������ �� ����������� ������� ������ ������� ���������
    */
    command_word_adc      &= (unsigned int)(~maska_canaliv_fapch_2);
    command_word_adc_work &= (unsigned int)(~maska_canaliv_fapch_2);
        
    command_word_adc |= READ_DATA_VAL_2;
    if (TN1_TN2_meas == 1) command_word_adc |= READ_I;
  }

  
  if (adc_TEST_VAL_read != 0) 
  {
    adc_TEST_VAL_read = false;
    status_adc_read_work |= TEST_VAL_READ;
      
    command_word_adc |= READ_TEST_VAL;
  }
  
  unsigned int command_word_adc_diff = command_word_adc ^ command_word_adc_work;
  if (command_word_adc_diff != 0)
  {
    /*
    � ������, �� ������� �� ���������
    */
    find_new_ADC_canal_to_read(command_word_adc_diff, &active_index_command_word_adc);
      
    /*
    ����� active_index_command_word_adc ����� � ����� input_adc �� �����, 
    ���� ����� ����������
    */
      
    /*
    ���������, ���� ����� �������� ���
    */
    unsigned int active_adc_old = ((GPIO_SELECT_ADC->ODR & GPIO_SELECTPin_ADC) == 0) ? 1 : 2;

    /*
    ���������, ���� ����� ����� ������������ ��� � �� ��� ����� ��������
    */
    unsigned int active_adc_new = input_adc[active_index_command_word_adc][0];
    unsigned int command_word = input_adc[active_index_command_word_adc][1];
    
    //��������� ��������� ����
    if (
        (state_reading_ADCs == STATE_READING_ADCs_NONE) ||
        (state_reading_ADCs == STATE_READING_READ     )
       )
    {
      state_reading_ADCs = STATE_READING_WRITE;
      /*
      ��������� ��������� ���
      */
      switch (active_adc_new)
      {
      case 1:
        {
          //���1
          GPIO_SELECT_ADC->BSRRH = GPIO_SELECTPin_ADC;
          break;
        }
        case 2:
        {
          //���2
          GPIO_SELECT_ADC->BSRRL = GPIO_SELECTPin_ADC;
          break;
        }
      default:
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(50);
        } 
      }
    }
    else
    {
      if (active_adc_old == active_adc_new)
      {
        state_reading_ADCs = STATE_READING_WRITE_READ;
      }
      else
      {
        state_reading_ADCs = STATE_READING_READ;
        command_word = 0;
      }
    }
    
    if (command_word != 0)
    {
      /*
      �������, �� ����� ������ ���� �������� ����� ����������
      */
      command_word_adc_work |= (1 << active_index_command_word_adc);
    }

    //�������� �������� �����
    while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //�������, ���� SPI ����� ������
    GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //����������� chip_select
    SPI_ADC->DR = (uint16_t)command_word;                   //³���������� �������� �����
    
    channel_answer = channel_request;
    channel_request = (active_adc_new - 1)*NUMBER_CANALs_ADC + ((command_word >> 10) & 0xf);
  }
  else 
  {
    if (
        (state_reading_ADCs == STATE_READING_READ     ) ||
        (state_reading_ADCs == STATE_READING_ADCs_NONE)
       )
    {
      //�� ������ ��� ���������
      state_reading_ADCs = STATE_READING_ADCs_NONE;

      command_word_adc = 0;
      command_word_adc_work = 0;
      active_index_command_word_adc = 0;
    }
    else
    {
      /*
      ����� �� �������� �������� � ���������� ��������, ���� ����� �����
      ���� �������������
      */
      state_reading_ADCs = STATE_READING_READ;
      while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //�������, ���� SPI ����� ������
      GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //����������� chip_select
      SPI_ADC->DR = 0;                                        //³���������� ����� (��� ���, ��� ���� ���������� ����� �� ������������)
    
      channel_answer = channel_request;
    }
  }
}
/*****************************************************/

/*************************************************************************
����������� ���������� ��������
 *************************************************************************/
void operate_test_ADCs(void)
{
  /*******************************************************
  ������������� ���������� �������� ����������� �����
  *******************************************************/
  unsigned int temp;

  //GND ��� ���1
  _SET_BIT(clear_diagnostyka, ERROR_GND_ADC1_TEST_COARSE_BIT);
  unsigned int gnd_tmp = 0;
  for (unsigned int i = 0; i < NUMBER_GND_ADC1; i++)
  {
    temp = output_adc[index_GND_ADC1[i]].value;
    gnd_adc1_averange_sum[i] += temp;
    gnd_adc1_averange_sum[i] -= gnd_adc1_moment_value[i][index_array_of_one_value];
    gnd_adc1_moment_value[i][index_array_of_one_value] = temp;
    gnd_tmp += gnd_adc1_averange[i] = gnd_adc1_averange_sum[i] >> VAGA_NUMBER_POINT;
    if (temp > 0xA1) _SET_BIT(set_diagnostyka, ERROR_GND_ADC1_TEST_COARSE_BIT);
  }
  gnd_adc1 = gnd_tmp / NUMBER_GND_ADC1;
  
  //GND ��� ���2
  _SET_BIT(clear_diagnostyka, ERROR_GND_ADC2_TEST_COARSE_BIT);
  gnd_tmp = 0;
  for (unsigned int i = 0; i < NUMBER_GND_ADC2; i++)
  {
    temp = output_adc[index_GND_ADC2[i]].value;
    gnd_adc2_averange_sum[i] += temp;
    gnd_adc2_averange_sum[i] -= gnd_adc2_moment_value[i][index_array_of_one_value];
    gnd_adc2_moment_value[i][index_array_of_one_value] = temp;
    gnd_tmp += gnd_adc2_averange[i] = gnd_adc2_averange_sum[i] >> VAGA_NUMBER_POINT;
    if (temp > 0xA1) _SET_BIT(set_diagnostyka, ERROR_GND_ADC2_TEST_COARSE_BIT);
  }
  gnd_adc2 = gnd_tmp / NUMBER_GND_ADC2;
  
  //VREF ��� ���1
  _SET_BIT(clear_diagnostyka, ERROR_VREF_ADC1_TEST_COARSE_BIT);
  temp = output_adc[C_VREF_ADC1].value;
  vref_adc1_averange_sum += temp;
  vref_adc1_averange_sum -= vref_adc1_moment_value[index_array_of_one_value];
  vref_adc1_moment_value[index_array_of_one_value] = temp;
  vref_adc1 = vref_adc1_averange_sum >> VAGA_NUMBER_POINT;
  if ((temp < 0x614) || (temp > 0x9EB)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC1_TEST_COARSE_BIT);
  
  //VREF ��� ���2
  _SET_BIT(clear_diagnostyka, ERROR_VREF_ADC2_TEST_COARSE_BIT);
  temp = output_adc[C_VREF_ADC2].value;
  vref_adc2_averange_sum += temp;
  vref_adc2_averange_sum -= vref_adc2_moment_value[index_array_of_one_value];
  vref_adc2_moment_value[index_array_of_one_value] = temp;
  vref_adc2 = vref_adc2_averange_sum >> VAGA_NUMBER_POINT;
  if ((temp < 0x614) || (temp > 0x9EB)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC2_TEST_COARSE_BIT);

  //VDD ��� ���1
  _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC1_TEST_COARSE_BIT);
  temp = output_adc[C_VDD_ADC1].value; 
  vdd_adc1_averange_sum += temp;
  vdd_adc1_averange_sum -= vdd_adc1_moment_value[index_array_of_one_value];
  vdd_adc1_moment_value[index_array_of_one_value] = temp;
  vdd_adc1 = vdd_adc1_averange_sum >> VAGA_NUMBER_POINT;
  if ((temp <0x6F2) || (temp > 0xD48)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC1_TEST_COARSE_BIT);

  //VDD ��� ���2
  _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC2_TEST_COARSE_BIT);
  temp = output_adc[C_VDD_ADC2].value; 
  vdd_adc2_averange_sum += temp;
  vdd_adc2_averange_sum -= vdd_adc2_moment_value[index_array_of_one_value];
  vdd_adc2_moment_value[index_array_of_one_value] = temp;
  vdd_adc2 = vdd_adc2_averange_sum >> VAGA_NUMBER_POINT;
  if ((temp <0x6F2) || (temp > 0xD48)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC2_TEST_COARSE_BIT);

  //�� ������ ���� �������� �� ��� ����������  
  if((++index_array_of_one_value) == NUMBER_POINT)
    index_array_of_one_value = 0;
  else if (index_array_of_one_value > NUMBER_POINT)
  {
    //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
    total_error_sw_fixed(21);
  }
  /*******************************************************/
}
/*************************************************************************/

/*************************************************************************
����������� ��� ��� ������������ ���'�
 *************************************************************************/
void Fourier(unsigned int number_val_group, unsigned int TN1_TN2_meas)
{
  unsigned int index_first_U_canal, number_canals, number_U_canals, max_number_canals;
  int *data_sin_U, *data_cos_U;
  
  switch (number_val_group)
  {
  case INDEX_U_1_MEAS:
    {
      max_number_canals = NUMBER_ANALOG_CANALES_I + NUMBER_ANALOG_CANALES_U_1;
      number_U_canals = NUMBER_ANALOG_CANALES_U_1;

      if (TN1_TN2_meas != 1) number_canals = max_number_canals;
      else number_canals = number_U_canals;
      
      index_first_U_canal = I_Ua1;
      data_sin_U = data_sin_U_1;
      data_cos_U = data_cos_U_1;
      
      break;
    }
  case INDEX_U_2_MEAS:
    {
      max_number_canals = NUMBER_ANALOG_CANALES_I + NUMBER_ANALOG_CANALES_U_2;
      number_U_canals = NUMBER_ANALOG_CANALES_U_2;

      if (TN1_TN2_meas == 1) number_canals = max_number_canals;
      else number_canals = number_U_canals;
      
      index_first_U_canal = I_Ua2;
      data_sin_U = data_sin_U_2;
      data_cos_U = data_cos_U_2;
      
      break;
    }
  default:
    {
      //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
      total_error_sw_fixed(22);
    }
  }
  
  unsigned int index_data_sin_cos_array_tmp;
  unsigned int max_size_data_sin_cos;
  unsigned int index_sin_cos_array_tmp = index_sin_cos_array[number_val_group - INDEX_U_1_MEAS];

  unsigned int bank_ortogonal_tmp = bank_ortogonal;

  //������� ������, �� ����'���� �� ��1 �� ��2
  if (max_number_canals == number_canals)
  {
    index_data_sin_cos_array_tmp = index_data_sin_cos_array[INDEX_I_MEAS];
    max_size_data_sin_cos = NUMBER_POINT*NUMBER_ANALOG_CANALES_I;
  
    for (int i = 0; i < NUMBER_ANALOG_CANALES_I; i++)
    {
      //������� ������ �������� ��� ����� ����������
      int temp_value_1 = ADCs_data[I_Ia + i];
      int temp_value_2;
      unsigned int i_ort_tmp = 2*(I_Ia + i);

      //����������� SIN
      ortogonal_irq[i_ort_tmp] -= data_sin_I[index_data_sin_cos_array_tmp];
      temp_value_2 = (int)((float)temp_value_1*sin_data_f[index_sin_cos_array_tmp]);
      data_sin_I[index_data_sin_cos_array_tmp] = temp_value_2;
      ortogonal_irq[i_ort_tmp] += temp_value_2;
    
      //����������� COS
      ortogonal_irq[i_ort_tmp + 1] -= data_cos_I[index_data_sin_cos_array_tmp];
      temp_value_2 = (int)((float)temp_value_1*cos_data_f[index_sin_cos_array_tmp]);
      data_cos_I[index_data_sin_cos_array_tmp] = temp_value_2;
      ortogonal_irq[i_ort_tmp + 1] += temp_value_2;
      
      //��������� ��� ����� ������
      ortogonal[i_ort_tmp    ][bank_ortogonal_tmp] = ortogonal_irq[i_ort_tmp    ];
      ortogonal[i_ort_tmp + 1][bank_ortogonal_tmp] = ortogonal_irq[i_ort_tmp + 1];
      
      if((++index_data_sin_cos_array_tmp) >= max_size_data_sin_cos) index_data_sin_cos_array_tmp = 0;
    }
    index_data_sin_cos_array[INDEX_I_MEAS] = index_data_sin_cos_array_tmp;
  }
  
  index_data_sin_cos_array_tmp = index_data_sin_cos_array[number_val_group];
  max_size_data_sin_cos = NUMBER_POINT*number_U_canals;

  //�������� ������, �� � �����������
  for (unsigned int i = 0; i < number_U_canals; i++)
  {
    //������� ������ �������� ��� ����� ����������
    int temp_value_1 = ADCs_data[index_first_U_canal + i];
    int temp_value_2;
    unsigned int i_ort_tmp = 2*(index_first_U_canal + i);

    //����������� SIN
    ortogonal_irq[i_ort_tmp] -= data_sin_U[index_data_sin_cos_array_tmp];
    temp_value_2 = (int)((float)temp_value_1*sin_data_f[index_sin_cos_array_tmp]);
    data_sin_U[index_data_sin_cos_array_tmp] = temp_value_2;
    ortogonal_irq[i_ort_tmp] += temp_value_2;
    
    //����������� COS
    ortogonal_irq[i_ort_tmp + 1] -= data_cos_U[index_data_sin_cos_array_tmp];
    temp_value_2 = (int)((float)temp_value_1*cos_data_f[index_sin_cos_array_tmp]);
    data_cos_U[index_data_sin_cos_array_tmp] = temp_value_2;
    ortogonal_irq[i_ort_tmp + 1] += temp_value_2;
  
    //��������� ��� ����� ������
    ortogonal[i_ort_tmp    ][bank_ortogonal_tmp] = ortogonal_irq[i_ort_tmp    ];
    ortogonal[i_ort_tmp + 1][bank_ortogonal_tmp] = ortogonal_irq[i_ort_tmp + 1];
    
    if((++index_data_sin_cos_array_tmp) >= max_size_data_sin_cos) index_data_sin_cos_array_tmp = 0;
  }
  index_data_sin_cos_array[number_val_group] = index_data_sin_cos_array_tmp;
  
  if((++index_sin_cos_array_tmp) >= NUMBER_POINT) index_sin_cos_array_tmp = 0;
  index_sin_cos_array[number_val_group - INDEX_U_1_MEAS] = index_sin_cos_array_tmp;
}
/*************************************************************************/

/*************************************************************************
�������� ������� ��� ������ ����� 1
*************************************************************************/
void fapch_val_1()
{
  unsigned int bank_measurement_high_tmp = bank_measurement_high;
  int index_1 = -1;
  unsigned int maska_canaliv_fapch_tmp = 0;

  /*****
  ������ ������ �� ����� ������ ������������� �������
  *****/  
  if (measurement_high[bank_measurement_high_tmp][IM_UA1] >= PORIG_FOR_FAPCH)
  {
    index_1 = INDEX_PhK_UA1;
    maska_canaliv_fapch_tmp = READ_Ua1;
  }
  else if (measurement_high[bank_measurement_high_tmp][IM_UB1] >= PORIG_FOR_FAPCH)
  {
    index_1 = INDEX_PhK_UB1;
    maska_canaliv_fapch_tmp = READ_Ub1;
  }
  else if (measurement_high[bank_measurement_high_tmp][IM_UC1] >= PORIG_FOR_FAPCH)
  {
    index_1 = INDEX_PhK_UC1;
    maska_canaliv_fapch_tmp = READ_Uc1;
  }
  delta_phi_index_1 = index_1;
  maska_canaliv_fapch_1 = maska_canaliv_fapch_tmp;
  /*****/

  uint32_t step_val_tmp;
  /*****/
  //������� ��1
  /*****/
  step_val_tmp = step_val_1;
  if (
      (index_1 >= 0) &&
      (fix_perechid_cherez_nul[index_1] != 0)
     )   
  {
    fix_perechid_cherez_nul[index_1] = 0;
    
    fix_perechid_cherez_nul_TN1_TN2 |= (1 << INDEX_U_1_MEAS);
    
    unsigned int delta_tick;
    long long tick_tmp;
    int delta_value;
    unsigned int tick_p1, x1_tmp, x2_tmp;
      
    /*��������� ��� �������� ����� 0 ������������ ���� � ����������� ����� ������������ ��� ��1*/
    delta_value = perechid_cherez_nul[index_1][0].y2 - perechid_cherez_nul[index_1][0].y1;
    x1_tmp = perechid_cherez_nul[index_1][0].x1;
    x2_tmp = perechid_cherez_nul[index_1][0].x2;
    if (x2_tmp > x1_tmp) delta_tick = x2_tmp - x1_tmp;
    else
    {
      long long delta_tick_64 = x2_tmp + 0x100000000 - x1_tmp;
      delta_tick = delta_tick_64;
    }
    tick_tmp = ((long long)perechid_cherez_nul[index_1][0].x1) - ((long long)perechid_cherez_nul[index_1][0].y1)*((long long)delta_tick)/((long long)delta_value);
    if (tick_tmp < 0) 
    {
      tick_tmp += 0x100000000;
      tick_p1 = (unsigned int)tick_tmp;
    }
    else
    {
      if (tick_tmp < 0x100000000) tick_p1 = (unsigned int)tick_tmp;
      else 
      {
        tick_tmp -= 0x100000000;
        tick_p1 = (unsigned int)tick_tmp;
      }
    }

    /*��������� ��� �������� ����� 0 ��������� ���� � ����������� ����� ������������ ��� ��1*/
    delta_value = perechid_cherez_nul[index_1][1].y2 - perechid_cherez_nul[index_1][1].y1;
    x1_tmp = perechid_cherez_nul[index_1][1].x1;
    x2_tmp = perechid_cherez_nul[index_1][1].x2;
    if (x2_tmp > x1_tmp) delta_tick = x2_tmp - x1_tmp;
    else
    {
      long long delta_tick_64 = x2_tmp + 0x100000000 - x1_tmp;
      delta_tick = delta_tick_64;
    }
    tick_tmp = ((long long)perechid_cherez_nul[index_1][1].x1) - ((long long)perechid_cherez_nul[index_1][1].y1)*((long long)delta_tick)/((long long)delta_value);
    if (tick_tmp < 0) 
    {
      tick_tmp += 0x100000000;
      tick_c1 = (unsigned int)tick_tmp;
    }
    else
    {
      if (tick_tmp < 0x100000000) tick_c1 = (unsigned int)tick_tmp;
      else 
      {
        tick_tmp -= 0x100000000;
        tick_c1 = (unsigned int)tick_tmp;
      }
    }
    /***/
      
    if (tick_c1 > tick_p1) delta_tick = tick_c1 - tick_p1;
    else
    {
      long long delta_tick_64 = tick_c1 + 0x100000000 - tick_p1;
      delta_tick = delta_tick_64;
    }
    tick_period_1 = delta_tick;
    
    /*****
    ���������� �������
    *****/
    if (
        (tick_period_1 <= MAX_TICK_PERIOD) &&
        (tick_period_1 >= MIN_TICK_PERIOD)
       ) 
    {
      frequency_val_1 = (float)MEASUREMENT_TIM_FREQUENCY/(float)tick_period_1;

      step_val_tmp = tick_period_1 >> VAGA_NUMBER_POINT;
      if ((tick_period_1 - (step_val_tmp << VAGA_NUMBER_POINT)) >= (1 << (VAGA_NUMBER_POINT - 1))) step_val_tmp++;
    }
    else
    {
      step_val_tmp = TIM5_CCR1_2_3_VAL;
      if (tick_period_1 > MAX_TICK_PERIOD) frequency_val_1 = -2; /*������� ����� ������ ����������� ���������� MIN_FREQUENCY*/
      else frequency_val_1 = -3; /*������� ���� ������ ����������� ���������� MAX_FREQUENCY*/
    }
    /****/
  }
  else
  {
    if (index_1 < 0)
    {
      step_val_tmp = TIM5_CCR1_2_3_VAL;
      frequency_val_1 = -1; /*������� �� ���������*/
      
      reset_delta_phi = true;
      periodical_tasks_CALC_DELTA_PHI = true;
    }
  }
  /*****/

  /*****/
  //���� ��1
  /*****/
  if (step_val_1 != step_val_tmp)
  {
    //����� ������ ������� �������������
    step_val_1 = step_val_tmp;

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
//    if (TIM_GetITStatus(TIM5, TIM_IT_CC1) == RESET)
//    {
//      uint32_t capture_new;
//      unsigned int delta;
//      TIM5->CCR1 = (capture_new = (previous_tick_VAL_1 + (delta = step_val_1)));
//    
//      unsigned int repeat;
//      unsigned int previous_tick;
//      do
//      {
//        repeat = 0;
//        uint32_t current_tick = TIM5->CNT;
//
//        uint32_t delta_time = 0;
//        if (capture_new < current_tick)
//        {
//          uint64_t delta_time_64 = capture_new + 0x100000000 - current_tick;
//          delta_time = delta_time_64;
//        }
//        else delta_time = capture_new - current_tick;
//
//        if ((delta_time > delta) || (delta_time == 0))
//        {
//          if (TIM_GetITStatus(TIM5, TIM_IT_CC1) == RESET)
//          {
//            if (delta < step_val_tmp)
//            {
//              uint32_t delta_tick;
//              if (current_tick < previous_tick)
//              {
//                uint64_t delta_tick_64 = current_tick + 0x100000000 - previous_tick;
//                delta_tick = delta_tick_64;
//              }
//              else delta_tick = current_tick - previous_tick;
//              
//              delta = delta_tick + 1;
//            }
//            else if (delta == step_val_tmp)
//              delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
//            else
//            {
//              //���������� ����� ����� �� ���� � ����
//              total_error_sw_fixed(81);
//            }
//            TIM5->CCR1 = (capture_new = (TIM5->CNT +  delta));
//            previous_tick = current_tick;
//            repeat = 0xff;
//          }
//        }
//      }
//      while (repeat != 0);
//    }
    /***********************************************************/
  }
  
  if ((command_restart_monitoring_frequency & (1 << 0)) != 0)
  {
    frequency_val_1_min = 50;
    frequency_val_1_max = 50;
    
    command_restart_monitoring_frequency &= (unsigned int)(~(1 << 0));
  }
  else
  {
    if (frequency_val_1 >= 0)
    {
      if (frequency_val_1 > frequency_val_1_max) frequency_val_1_max = frequency_val_1;
      if (frequency_val_1 < frequency_val_1_min) frequency_val_1_min = frequency_val_1;
    }
  }
  /*****/
}
/*****************************************************/

/*************************************************************************
�������� ������� ��� ������ ����� 2
*************************************************************************/
void fapch_val_2()
{
  unsigned int bank_measurement_high_tmp = bank_measurement_high;
  int index_2 = -1;
  unsigned int maska_canaliv_fapch_tmp = 0;

  /*****
  ������ ������ �� ����� ������ ������������� �������
  *****/  
  if (measurement_high[bank_measurement_high_tmp][IM_UA2] >= PORIG_FOR_FAPCH)
  {
    index_2 = INDEX_PhK_UA2;
    maska_canaliv_fapch_tmp = READ_Ua2;
  }
  else if (measurement_high[bank_measurement_high_tmp][IM_UB2] >= PORIG_FOR_FAPCH)
  {
    index_2 = INDEX_PhK_UB2;
    maska_canaliv_fapch_tmp = READ_Ub2;
  }
  else if (measurement_high[bank_measurement_high_tmp][IM_UC2] >= PORIG_FOR_FAPCH)
  {
    index_2 = INDEX_PhK_UC2;
    maska_canaliv_fapch_tmp = READ_Uc2;
  }
  delta_phi_index_2 = index_2;
  maska_canaliv_fapch_2 = maska_canaliv_fapch_tmp;
  /*****/

  uint32_t step_val_tmp;
  /*****/
  //������� ��2
  /*****/
  step_val_tmp = step_val_2;
  if (
      (index_2 >= 0) &&
      (fix_perechid_cherez_nul[index_2] != 0)
     )   
  {
    fix_perechid_cherez_nul[index_2] = 0;

    fix_perechid_cherez_nul_TN1_TN2 |= (1 << INDEX_U_2_MEAS);

    unsigned int delta_tick;
    long long tick_tmp;
    int delta_value;
    unsigned int tick_p2, x1_tmp, x2_tmp;
      
    /*��������� ��� �������� ����� 0 ������������ ���� � ����������� ����� ������������ ��� ��2*/
    delta_value = perechid_cherez_nul[index_2][0].y2 - perechid_cherez_nul[index_2][0].y1;
    x1_tmp = perechid_cherez_nul[index_2][0].x1;
    x2_tmp = perechid_cherez_nul[index_2][0].x2;
    if (x2_tmp > x1_tmp) delta_tick = x2_tmp - x1_tmp;
    else
    {
      long long delta_tick_64 = x2_tmp + 0x100000000 - x1_tmp;
      delta_tick = delta_tick_64;
    }
    tick_tmp = ((long long)perechid_cherez_nul[index_2][0].x1) - ((long long)perechid_cherez_nul[index_2][0].y1)*((long long)delta_tick)/((long long)delta_value);
    if (tick_tmp < 0) 
    {
      tick_tmp += 0x100000000;
      tick_p2 = (unsigned int)tick_tmp;
    }
    else
    {
      if (tick_tmp < 0x100000000) tick_p2 = (unsigned int)tick_tmp;
      else 
      {
        tick_tmp -= 0x100000000;
        tick_p2 = (unsigned int)tick_tmp;
      }
    }

    /*��������� ��� �������� ����� 0 ��������� ���� � ����������� ����� ������������ ��� ��2*/
    delta_value = perechid_cherez_nul[index_2][1].y2 - perechid_cherez_nul[index_2][1].y1;
    x1_tmp = perechid_cherez_nul[index_2][1].x1;
    x2_tmp = perechid_cherez_nul[index_2][1].x2;
    if (x2_tmp > x1_tmp) x1_tmp = x2_tmp - x1_tmp;
    else
    {
      long long delta_tick_64 = x2_tmp + 0x100000000 - x1_tmp;
      delta_tick = delta_tick_64;
    }
    tick_tmp = ((long long)perechid_cherez_nul[index_2][1].x1) - ((long long)perechid_cherez_nul[index_2][1].y1)*((long long)delta_tick)/((long long)delta_value);
    if (tick_tmp < 0) 
    {
      tick_tmp += 0x100000000;
      tick_c2 = (unsigned int)tick_tmp;
    }
    else
    {
      if (tick_tmp < 0x100000000) tick_c2 = (unsigned int)tick_tmp;
      else 
      {
        tick_tmp -= 0x100000000;
        tick_c2 = (unsigned int)tick_tmp;
      }
    }
    /***/
      
    if (tick_c2 > tick_p2) delta_tick = tick_c2 - tick_p2;
    else
    {
      long long delta_tick_64 = tick_c2 + 0x100000000 - tick_p2;
      delta_tick = delta_tick_64;
    }
    tick_period_2 = delta_tick;
    
    /*****
    ���������� �������
    *****/
    if (
        (tick_period_2 <= MAX_TICK_PERIOD) &&
        (tick_period_2 >= MIN_TICK_PERIOD)
       ) 
    {
      frequency_val_2 = (float)MEASUREMENT_TIM_FREQUENCY/(float)tick_period_2;

      step_val_tmp = tick_period_2 >> VAGA_NUMBER_POINT;
      if ((tick_period_2 - (step_val_tmp << VAGA_NUMBER_POINT)) >= (1 << (VAGA_NUMBER_POINT - 1))) step_val_tmp++;
    }
    else
    {
      step_val_tmp = TIM5_CCR1_2_3_VAL;
      if (tick_period_2 > MAX_TICK_PERIOD) frequency_val_2 = -2; /*������� ����� ������ ����������� ���������� MIN_FREQUENCY*/
      else frequency_val_2 = -3; /*������� ���� ������ ����������� ���������� MAX_FREQUENCY*/
    }
    /****/
  }
  else
  {
    if (index_2 < 0)
    {
      step_val_tmp = TIM5_CCR1_2_3_VAL;
      frequency_val_2 = -1; /*������� �� ���������*/
      
      reset_delta_phi = true;
      periodical_tasks_CALC_DELTA_PHI = true;
    }
  }
  /*****/

  /*****/
  //���� ��2
  /*****/
  if (step_val_2 != step_val_tmp)
  {
    //����� ������ ������� �������������
    step_val_2 = step_val_tmp;

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
//    if (TIM_GetITStatus(TIM5, TIM_IT_CC2) == RESET)
//    {
//      uint32_t capture_new;
//      unsigned int delta;
//      TIM5->CCR2 = (capture_new = (previous_tick_VAL_2 + (delta = step_val_2)));
//    
//      unsigned int repeat;
//      unsigned int previous_tick;
//      do
//      {
//        repeat = 0;
//        uint32_t current_tick = TIM5->CNT;
//
//        uint32_t delta_time = 0;
//        if (capture_new < current_tick)
//        {
//          uint64_t delta_time_64 = capture_new + 0x100000000 - current_tick;
//          delta_time = delta_time_64;
//        }
//        else delta_time = capture_new - current_tick;
//
//        if ((delta_time > delta) || (delta_time == 0))
//        {
//          if (TIM_GetITStatus(TIM5, TIM_IT_CC2) == RESET)
//          {
//            if (delta < step_val_tmp)
//            {
//              uint32_t delta_tick;
//              if (current_tick < previous_tick)
//              {
//                uint64_t delta_tick_64 = current_tick + 0x100000000 - previous_tick;
//                delta_tick = delta_tick_64;
//              }
//              else delta_tick = current_tick - previous_tick;
//              
//              delta = delta_tick + 1;
//            }
//            else if (delta == step_val_tmp)
//              delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
//            else
//            {
//              //���������� ����� ����� �� ���� � ����
//              total_error_sw_fixed(82);
//            }
//            TIM5->CCR2 = (capture_new = (TIM5->CNT +  delta));
//            previous_tick = current_tick;
//            repeat = 0xff;
//          }
//        }
//      }
//      while (repeat != 0);
//    }
    /***********************************************************/
  }
  
  if ((command_restart_monitoring_frequency & (1 << 1)) != 0)
  {
    frequency_val_2_min = 50;
    frequency_val_2_max = 50;
    
    command_restart_monitoring_frequency &= (unsigned int)(~(1 << 1));
  }
  else
  {
    if (frequency_val_2 >= 0)
    {
      if (frequency_val_2 > frequency_val_2_max) frequency_val_2_max = frequency_val_2;
      if (frequency_val_2 < frequency_val_2_min) frequency_val_2_min = frequency_val_2;
    }
  }
  /*****/
}
/*****************************************************/

/*****************************************************/
//����������� �� ���������� ����� �� ������ SPI, ���� ��������� ����������� �������
/*****************************************************/
void SPI_ADC_IRQHandler(void)
{
//#ifdef SYSTEM_VIEWER_ENABLE
//  SEGGER_SYSVIEW_RecordEnterISR();
//#endif

  //Գ����� ���� � ����������� ������� ����� �� ���
  semaphore_adc_irq  = true;
  
  //Գ����� ��� ���������
  uint32_t tick_output_adc_tmp = TIM5->CNT;
  
  //�� ������ ������� ������ chip_select
  GPIO_SPI_ADC->BSRRL = GPIO_NSSPin_ADC;
  uint16_t read_value = SPI_ADC->DR;

  static uint32_t tick_output_adc_p;
  /*
  �������� ������� ���
  */
  if (
      (state_reading_ADCs == STATE_READING_WRITE_READ) ||
      (state_reading_ADCs == STATE_READING_READ)
     )
  {
    unsigned int shift = ((GPIO_SELECT_ADC->ODR & GPIO_SELECTPin_ADC) == 0) ? 0 : NUMBER_CANALs_ADC;
    unsigned int number_canal = shift + ((read_value >> 12) & 0xf);
    
    output_adc[number_canal].tick = tick_output_adc_p;
    
    static uint32_t error_spi_adc;
    if(channel_answer != number_canal) 
    {
      if (error_spi_adc < 3 ) error_spi_adc++;
      if (error_spi_adc >= 3 )_SET_BIT(set_diagnostyka, ERROR_SPI_ADC_BIT);
    }
    else 
    {
      error_spi_adc = 0;
      
      _SET_BIT(clear_diagnostyka, ERROR_SPI_ADC_BIT);
      output_adc[number_canal].value = read_value & 0xfff;
    }
  }
  tick_output_adc_p = tick_output_adc_tmp;
  /***/
  
  //�������� �������� � ������� ���
  unsigned int TN1_TN2_meas = TN1_TN2;
  control_reading_ADCs(TN1_TN2_meas);
  
  /*
  �������� �� �������� ����� ���, ���� �� ������ ��� ���������
  */
  if (state_reading_ADCs == STATE_READING_ADCs_NONE)
  {
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
    /*******************************************************/
    //����������, �� ���������� ���� ���������
    /*******************************************************/
    if (changed_ustuvannja == CHANGED_ETAP_ENDED) /*�� � �����, �� ��� ��� ���������� ��� �������� �� � ������ ������������ �������� (� ��� ����� ����� ��� �� ���������)*/
    {
      //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
      for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
      {
        ustuvannja_meas[k] = ustuvannja[k];
      }
      
      //�������, �� ���� ������� ������������ ��������, ��� �� ����� �������� �������� �������
      changed_ustuvannja = CHANGED_ETAP_ENDED_EXTRA_ETAP;
    }
    /*****************************************************/

    /*
    ������� �������� ������������� ������
    */
    unsigned int command_word = 0;
    if ((status_adc_read_work & DATA_VAL_1_READ) != 0)
    {
      command_word |= (1 << I_Ua1) | (1 << I_Ub1) | (1 << I_Uc1);
      if (TN1_TN2_meas != 1) command_word |= (1 << I_Ia ) | (1 << I_Ib ) | (1 << I_Ic );
    }
      
    if ((status_adc_read_work & DATA_VAL_2_READ) != 0)
    {
      command_word |= (1 << I_Ua2) | (1 << I_Ub2) | (1 << I_Uc2);
      if (TN1_TN2_meas == 1) command_word |= (1 << I_Ia ) | (1 << I_Ib ) | (1 << I_Ic );
    }

    if (TN1_TN2_meas_global != TN1_TN2_meas)
    {
      TN1_TN2_meas_global = TN1_TN2_meas;
    
//      for (int i = 0; i < NUMBER_ANALOG_CANALES_I; i++) 
//      {
//        if (TN1_TN2_meas == 1)
//        {
//          ADCs_data_raw[I_Ia + i].tick = penultimate_tick_VAL_2;
//        }
//        else
//        {
//          ADCs_data_raw[I_Ia + i].tick = penultimate_tick_VAL_1;
//        }
//      }
    }
    
    uint32_t _x1, _x2, _DX, _dx;
    int _y1, _y2;
    long long _y;
      
    uint32_t _x = previous_tick_VAL_1;
    
    unsigned int gnd_adc  = gnd_adc2; 
    unsigned int vref_adc = vref_adc2; 

    /*****/
    //������� �������� Ua1
    /*****/
    if ((command_word & (1 << I_Ua1)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ua1].tick;
      _y1 = ADCs_data_raw[I_Ua1].value;
        
      _y2 = output_adc[C_Ua1_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ua1_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ua1])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ua1_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Ua1_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ua1])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);
      
      if ((_y >= 0) && (ADCs_data[I_Ua1] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_UA1][0].x1 = poperednij_perechid.Ua1_x1;
        perechid_cherez_nul[INDEX_PhK_UA1][0].y1 = poperednij_perechid.Ua1_y1;
        perechid_cherez_nul[INDEX_PhK_UA1][0].x2 = poperednij_perechid.Ua1_x2;
        perechid_cherez_nul[INDEX_PhK_UA1][0].y2 = poperednij_perechid.Ua1_y2;
          
        //�������� �������
        poperednij_perechid.Ua1_x1 = perechid_cherez_nul[INDEX_PhK_UA1][1].x1 = penultimate_tick_VAL_1;
        poperednij_perechid.Ua1_y1 = perechid_cherez_nul[INDEX_PhK_UA1][1].y1 = ADCs_data[I_Ua1];
        poperednij_perechid.Ua1_x2 = perechid_cherez_nul[INDEX_PhK_UA1][1].x2 = _x;
        poperednij_perechid.Ua1_y2 = perechid_cherez_nul[INDEX_PhK_UA1][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UA1] = 0xff;
      }
      ADCs_data[I_Ua1] = _y;
      
      ADCs_data_raw[I_Ua1].tick = _x2;
      ADCs_data_raw[I_Ua1].value = _y2;
    }
    /*****/
    
    /*****/
    //������� �������� Ub1
    /*****/
    if ((command_word & (1 << I_Ub1)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ub1].tick;
      _y1 = ADCs_data_raw[I_Ub1].value;
        
      _y2 = output_adc[C_Ub1_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ub1_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ub1])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ub1_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Ub1_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ub1])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);
 
      if ((_y >= 0) && (ADCs_data[I_Ub1] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_UB1][0].x1 = poperednij_perechid.Ub1_x1;
        perechid_cherez_nul[INDEX_PhK_UB1][0].y1 = poperednij_perechid.Ub1_y1;
        perechid_cherez_nul[INDEX_PhK_UB1][0].x2 = poperednij_perechid.Ub1_x2;
        perechid_cherez_nul[INDEX_PhK_UB1][0].y2 = poperednij_perechid.Ub1_y2;
          
        //�������� �������
        poperednij_perechid.Ub1_x1 = perechid_cherez_nul[INDEX_PhK_UB1][1].x1 = penultimate_tick_VAL_1;
        poperednij_perechid.Ub1_y1 = perechid_cherez_nul[INDEX_PhK_UB1][1].y1 = ADCs_data[I_Ub1];
        poperednij_perechid.Ub1_x2 = perechid_cherez_nul[INDEX_PhK_UB1][1].x2 = _x;
        poperednij_perechid.Ub1_y2 = perechid_cherez_nul[INDEX_PhK_UB1][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UB1] = 0xff;
      }
      ADCs_data[I_Ub1] = _y;
      
      ADCs_data_raw[I_Ub1].tick = _x2;
      ADCs_data_raw[I_Ub1].value = _y2;
    }
    /*****/
    
    /*****/
    //������� �������� Uc1
    /*****/
    if ((command_word & (1 << I_Uc1)) != 0)
    {
      _x1 = ADCs_data_raw[I_Uc1].tick;
      _y1 = ADCs_data_raw[I_Uc1].value;
        
      _y2 = output_adc[C_Uc1_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Uc1_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Uc1])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Uc1_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Uc1_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Uc1])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      if ((_y >= 0) && (ADCs_data[I_Uc1] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_UC1][0].x1 = poperednij_perechid.Uc1_x1;
        perechid_cherez_nul[INDEX_PhK_UC1][0].y1 = poperednij_perechid.Uc1_y1;
        perechid_cherez_nul[INDEX_PhK_UC1][0].x2 = poperednij_perechid.Uc1_x2;
        perechid_cherez_nul[INDEX_PhK_UC1][0].y2 = poperednij_perechid.Uc1_y2;
          
        //�������� �������
        poperednij_perechid.Uc1_x1 = perechid_cherez_nul[INDEX_PhK_UC1][1].x1 = penultimate_tick_VAL_1;
        poperednij_perechid.Uc1_y1 = perechid_cherez_nul[INDEX_PhK_UC1][1].y1 = ADCs_data[I_Uc1];
        poperednij_perechid.Uc1_x2 = perechid_cherez_nul[INDEX_PhK_UC1][1].x2 = _x;
        poperednij_perechid.Uc1_y2 = perechid_cherez_nul[INDEX_PhK_UC1][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UC1] = 0xff;
      }
      ADCs_data[I_Uc1] = _y;
      
      ADCs_data_raw[I_Uc1].tick = _x2;
      ADCs_data_raw[I_Uc1].value = _y2;
    }
    /*****/

    if (TN1_TN2_meas == 1) _x = previous_tick_VAL_2;
    
    gnd_adc  = gnd_adc1; 
    vref_adc = vref_adc1; 

    /*****/
    //������� �������� Ia
    /*****/
    if ((command_word & (1 << I_Ia)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ia].tick;
      _y1 = ADCs_data_raw[I_Ia].value;
        
      _y2 = output_adc[C_Ia_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ia_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ia])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ia_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Ia_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ia])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ia] = _y;
      
      ADCs_data_raw[I_Ia].tick = _x2;
      ADCs_data_raw[I_Ia].value = _y2;
    }
    /*****/

    /*****/
    //������� �������� Ib
    /*****/
    if ((command_word & (1 << I_Ib)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ib].tick;
      _y1 = ADCs_data_raw[I_Ib].value;
        
      _y2 = output_adc[C_Ib_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ib_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ib])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ib_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Ib_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ib])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ib] = _y;
      
      ADCs_data_raw[I_Ib].tick = _x2;
      ADCs_data_raw[I_Ib].value = _y2;
    }
    /*****/
    
    /*****/
    //������� �������� Ic
    /*****/
    if ((command_word & (1 << I_Ic)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ic].tick;
      _y1 = ADCs_data_raw[I_Ic].value;
        
      _y2 = output_adc[C_Ic_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ic_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ic])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ic_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Ic_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ic])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ic] = _y;
      
      ADCs_data_raw[I_Ic].tick = _x2;
      ADCs_data_raw[I_Ic].value = _y2;
    }
    /*****/
    
    _x = previous_tick_VAL_2;
    
    gnd_adc  = gnd_adc2; 
    vref_adc = vref_adc2; 

    /*****/
    //������� �������� Ua2
    /*****/
    if ((command_word & (1 << I_Ua2)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ua2].tick;
      _y1 = ADCs_data_raw[I_Ua2].value;
        
      _y2 = output_adc[C_Ua2_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ua2_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ua2])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ua2_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Ua2_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ua2])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      if ((_y >= 0) && (ADCs_data[I_Ua2] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_UA2][0].x1 = poperednij_perechid.Ua2_x1;
        perechid_cherez_nul[INDEX_PhK_UA2][0].y1 = poperednij_perechid.Ua2_y1;
        perechid_cherez_nul[INDEX_PhK_UA2][0].x2 = poperednij_perechid.Ua2_x2;
        perechid_cherez_nul[INDEX_PhK_UA2][0].y2 = poperednij_perechid.Ua2_y2;
          
        //�������� �������
        poperednij_perechid.Ua2_x1 = perechid_cherez_nul[INDEX_PhK_UA2][1].x1 = penultimate_tick_VAL_2;
        poperednij_perechid.Ua2_y1 = perechid_cherez_nul[INDEX_PhK_UA2][1].y1 = ADCs_data[I_Ua2];
        poperednij_perechid.Ua2_x2 = perechid_cherez_nul[INDEX_PhK_UA2][1].x2 = _x;
        poperednij_perechid.Ua2_y2 = perechid_cherez_nul[INDEX_PhK_UA2][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UA2] = 0xff;
      }
      ADCs_data[I_Ua2] = _y;
      
      ADCs_data_raw[I_Ua2].tick = _x2;
      ADCs_data_raw[I_Ua2].value = _y2;
    }
    /*****/

     /*****/
    //������� �������� Ub2
    /*****/
    if ((command_word & (1 << I_Ub2)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ub2].tick;
      _y1 = ADCs_data_raw[I_Ub2].value;
        
      _y2 = output_adc[C_Ub2_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ub2_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ub2])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ub2_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Ub2_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ub2])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      if ((_y >= 0) && (ADCs_data[I_Ub2] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_UB2][0].x1 = poperednij_perechid.Ub2_x1;
        perechid_cherez_nul[INDEX_PhK_UB2][0].y1 = poperednij_perechid.Ub2_y1;
        perechid_cherez_nul[INDEX_PhK_UB2][0].x2 = poperednij_perechid.Ub2_x2;
        perechid_cherez_nul[INDEX_PhK_UB2][0].y2 = poperednij_perechid.Ub2_y2;
          
        //�������� �������
        poperednij_perechid.Ub2_x1 = perechid_cherez_nul[INDEX_PhK_UB2][1].x1 = penultimate_tick_VAL_2;
        poperednij_perechid.Ub2_y1 = perechid_cherez_nul[INDEX_PhK_UB2][1].y1 = ADCs_data[I_Ub2];
        poperednij_perechid.Ub2_x2 = perechid_cherez_nul[INDEX_PhK_UB2][1].x2 = _x;
        poperednij_perechid.Ub2_y2 = perechid_cherez_nul[INDEX_PhK_UB2][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UB2] = 0xff;
      }
      ADCs_data[I_Ub2] = _y;
      
      ADCs_data_raw[I_Ub2].tick = _x2;
      ADCs_data_raw[I_Ub2].value = _y2;
    }
    /*****/
    
    gnd_adc  = gnd_adc1; 
    vref_adc = vref_adc1; 

    /*****/
    //������� �������� Uc2
    /*****/
    if ((command_word & (1 << I_Uc2)) != 0)
    {
      _x1 = ADCs_data_raw[I_Uc2].tick;
      _y1 = ADCs_data_raw[I_Uc2].value;
        
      _y2 = output_adc[C_Uc2_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Uc2_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Uc2])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Uc2_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Uc2_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Uc2])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      if ((_y >= 0) && (ADCs_data[I_Uc2] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_UC2][0].x1 = poperednij_perechid.Uc2_x1;
        perechid_cherez_nul[INDEX_PhK_UC2][0].y1 = poperednij_perechid.Uc2_y1;
        perechid_cherez_nul[INDEX_PhK_UC2][0].x2 = poperednij_perechid.Uc2_x2;
        perechid_cherez_nul[INDEX_PhK_UC2][0].y2 = poperednij_perechid.Uc2_y2;
          
        //�������� �������
        poperednij_perechid.Uc2_x1 = perechid_cherez_nul[INDEX_PhK_UC2][1].x1 = penultimate_tick_VAL_2;
        poperednij_perechid.Uc2_y1 = perechid_cherez_nul[INDEX_PhK_UC2][1].y1 = ADCs_data[I_Uc2];
        poperednij_perechid.Uc2_x2 = perechid_cherez_nul[INDEX_PhK_UC2][1].x2 = _x;
        poperednij_perechid.Uc2_y2 = perechid_cherez_nul[INDEX_PhK_UC2][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UC2] = 0xff;
      }
      ADCs_data[I_Uc2] = _y;
      
      ADCs_data_raw[I_Uc2].tick = _x2;
      ADCs_data_raw[I_Uc2].value = _y2;
    }
    /*****/

    unsigned int head_data_for_oscylograph_tmp = head_data_for_oscylograph;
    unsigned int x2, x1, delta_x; 

    if ((status_adc_read_work & DATA_VAL_1_READ) != 0)
    {
      //�������� �� ��������� ����������� ���
      static int current_vector[2][2];
      static unsigned int index_of_currnet_vector;
      static unsigned int ready_vectors; 
      sequence_TN1 = sequence_phases(current_vector, &index_of_currnet_vector, &ready_vectors, /*ADCs_data_raw*/ADCs_data, I_Ua1, IM_UA1);
      
      /*
      ��������� ���������� ��������� ��� ��� ������������ ���'�
      */
      Fourier(INDEX_U_1_MEAS, TN1_TN2_meas);
      
      //������� ��� ��� ��������� �������

      //�������, �� ��������
      x1 = rozshyrena_vyborka.U_1_time_p = penultimate_tick_VAL_1;
      x2 = rozshyrena_vyborka.U_1_time_c = previous_tick_VAL_1;
      for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_U_1; i++) 
      {
        rozshyrena_vyborka.U_1_data_p[i] = rozshyrena_vyborka.U_1_data_c[i];
        rozshyrena_vyborka.U_1_data_c[i] = ADCs_data[I_Ua1 + i];
      }

      //������, �� ����'���� �� ��1
      if (TN1_TN2_meas != 1)
      {
        rozshyrena_vyborka.I_time_p = x1;
        rozshyrena_vyborka.I_time_c = x2;
        for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_I; i++) 
        {
          rozshyrena_vyborka.I_data_p[i] = rozshyrena_vyborka.I_data_c[i];
          rozshyrena_vyborka.I_data_c[i] = ADCs_data[I_Ia + i];
        }
      }

      /*******************************************************
      ���������� �������������� ������� ��� ������ ����� 1
      *******************************************************/
      if (head_data_for_oscylograph_tmp != VAL_1_tail_data_for_oscylograph)
      {
        if (x2 > x1) delta_x = x2 - x1;
        else
        {
          long long delta_x_64 = x2 + 0x100000000 - x1;
          delta_x = delta_x_64;
        }

        while (head_data_for_oscylograph_tmp != VAL_1_tail_data_for_oscylograph)
        {
          unsigned int VAL_1_tail_data_for_oscylograph_tmp = VAL_1_tail_data_for_oscylograph;
    
          unsigned int x = data_for_oscylograph[VAL_1_tail_data_for_oscylograph_tmp].time_stemp;
        
          unsigned int dx;
          if (x >= x1) dx = x - x1;
          else
          {
            long long dx_64 = x + 0x100000000 - x1;
            dx = dx_64;
          }
          
          if (dx > delta_x) 
          {
            break;
          }
          
          //������, �� ����'���� �� ��1
          if (TN1_TN2_meas != 1)
          {
            for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_I; i++)
            {
              int y1 = rozshyrena_vyborka.I_data_p[i], y2 = rozshyrena_vyborka.I_data_c[i];
              long long y;
              if (dx <= delta_x)
              {
                y = ((long long)(y2 - y1))*((long long)dx)/((long long)delta_x) + ((long long)y1);
              }
              else
              {
                y = 0;
              }
              data_for_oscylograph[VAL_1_tail_data_for_oscylograph_tmp].data[I_Ia + i] = y;
            }
          }

          //�������, �� ��������
          for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_U_1; i++)
          {
            int y1 = rozshyrena_vyborka.U_1_data_p[i], y2 = rozshyrena_vyborka.U_1_data_c[i];
            long long y;
            if (dx <= delta_x)
            {
              y = ((long long)(y2 - y1))*((long long)dx)/((long long)delta_x) + ((long long)y1);
            }
            else
            {
              y = 0;
            }
            data_for_oscylograph[VAL_1_tail_data_for_oscylograph_tmp].data[I_Ua1 + i] = y;
          }
          data_for_oscylograph[VAL_1_tail_data_for_oscylograph_tmp].VAL_1_fix = 0xff;

          if (++VAL_1_tail_data_for_oscylograph >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) VAL_1_tail_data_for_oscylograph = 0;
        }
      }
      /******************************************************/
      
      /*
      �������� �������� �� ���������� ������� � ��������� �������
      */
      fapch_val_1();
    
      status_adc_read_work &= (unsigned int)(~DATA_VAL_1_READ);

      /**************************************************/
      //����������� ����������� ��� ���������� ������ ����� ����� ������������ �������
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_VAL_1;
      /**************************************************/
    }
    if ((status_adc_read_work & DATA_VAL_2_READ) != 0)
    {
      //�������� �� ��������� ����������� ���
      static int current_vector[2][2];
      static unsigned int index_of_currnet_vector;
      static unsigned int ready_vectors; 
      sequence_TN2 = sequence_phases(current_vector, &index_of_currnet_vector, &ready_vectors, /*ADCs_data_raw*/ADCs_data, I_Ua2, IM_UA2);
      /*
      ��������� ���������� ��������� ��� ��� ������������ ���'� ���
      ���������� ������� ����� 2
      */
      Fourier(INDEX_U_2_MEAS, TN1_TN2_meas);
      
      //������� ��� ��� ��������� �������

      //�������, �� ��������
      x1 = rozshyrena_vyborka.U_2_time_p = penultimate_tick_VAL_2;
      x2 = rozshyrena_vyborka.U_2_time_c = previous_tick_VAL_2;
      for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_U_2; i++) 
      {
        rozshyrena_vyborka.U_2_data_p[i] = rozshyrena_vyborka.U_2_data_c[i];
        rozshyrena_vyborka.U_2_data_c[i] = ADCs_data[I_Ua2 + i];
      }

      //������, �� ����'���� �� ��2
      if (TN1_TN2_meas == 1)
      {
        rozshyrena_vyborka.I_time_p = x1;
        rozshyrena_vyborka.I_time_c = x2;
        for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_I; i++) 
        {
          rozshyrena_vyborka.I_data_p[i] = rozshyrena_vyborka.I_data_c[i];
          rozshyrena_vyborka.I_data_c[i] = ADCs_data[I_Ia + i];
        }
      }

      /*******************************************************
      ���������� �������������� ������� ��� ������ ����� 2
      *******************************************************/
      if (head_data_for_oscylograph_tmp != VAL_2_tail_data_for_oscylograph)
      {
        if (x2 > x1) delta_x = x2 - x1;
        {
          long long delta_x_64 = x2 + 0x100000000 - x1;
          delta_x = delta_x_64;
        }

        while (head_data_for_oscylograph_tmp != VAL_2_tail_data_for_oscylograph)
        {
          unsigned int VAL_2_tail_data_for_oscylograph_tmp = VAL_2_tail_data_for_oscylograph;
    
          unsigned int x = data_for_oscylograph[VAL_2_tail_data_for_oscylograph_tmp].time_stemp;
        
          unsigned int dx;
          if (x >= x1) dx = x - x1;
          {
            long long dx_64 = x + 0x100000000 - x1;
            dx = dx_64;
          }
          
          if (dx > delta_x) break;

          
          //������, �� ����'���� �� ��2
          if (TN1_TN2_meas == 1)
          {
            for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_I; i++)
            {
              int y1 = rozshyrena_vyborka.I_data_p[i], y2 = rozshyrena_vyborka.I_data_c[i];
              long long y;
              if (dx <= delta_x)
              {
                y = ((long long)(y2 - y1))*((long long)dx)/((long long)delta_x) + ((long long)y1);
              }
              else
              {
                y = 0;
              }
              data_for_oscylograph[VAL_2_tail_data_for_oscylograph_tmp].data[I_Ia + i] = y;
            }
          }

          //�������, �� ��������
          for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_U_2; i++)
          {
            int y1 = rozshyrena_vyborka.U_2_data_p[i], y2 = rozshyrena_vyborka.U_2_data_c[i];
            long long y;
            if (dx <= delta_x)
            {
              y = ((long long)(y2 - y1))*((long long)dx)/((long long)delta_x) + ((long long)y1);
            }
            else
            {
              y = 0;
            }
            data_for_oscylograph[VAL_2_tail_data_for_oscylograph_tmp].data[I_Ua2 + i] = y;
          }
          data_for_oscylograph[VAL_2_tail_data_for_oscylograph_tmp].VAL_2_fix = 0xff;

          if (++VAL_2_tail_data_for_oscylograph >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) VAL_2_tail_data_for_oscylograph = 0;
        }
      }
      /******************************************************/
      
      /*
      �������� �������� �� ���������� ������� � ��������� ������� ��� 
      ����� ������������ ������� 2
      */
      fapch_val_2();
    
      status_adc_read_work &= (unsigned int)(~DATA_VAL_2_READ);

      /**************************************************/
      //����������� ����������� ��� ���������� ������ ����� ����� ������������ �������
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_VAL_2;
      /**************************************************/
    }
    if ((fix_perechid_cherez_nul_TN1_TN2 & ((1 << INDEX_U_1_MEAS) | (1 << INDEX_U_2_MEAS))) == ((1 << INDEX_U_1_MEAS) | (1 << INDEX_U_2_MEAS))) 
    {
      if (semaphore_delta_phi == 0)
      {
        fix_perechid_cherez_nul_TN1_TN2_work = fix_perechid_cherez_nul_TN1_TN2;
        fix_perechid_cherez_nul_TN1_TN2 = 0;

        frequency_val_1_work = frequency_val_1;
        tick_period_1_work = tick_period_1;
        tick_c1_work = tick_c1;
        delta_phi_index_1_work_middle = delta_phi_index_1;

        frequency_val_2_work = frequency_val_2;
        tick_period_2_work = tick_period_2;
        tick_c2_work = tick_c2;
        delta_phi_index_2_work_middle = delta_phi_index_2;
        
        periodical_tasks_CALC_DELTA_PHI = true;
      }
    }
    
    /********************************************************
    ������� ����� ������� ������� � �������� �������� ��� ����������� ����������
    ********************************************************/
    unsigned int number_postfault_slices = 0;
    if (head_data_for_oscylograph_tmp != tail_data_for_oscylograph)
    {
      while (
             (head_data_for_oscylograph_tmp != tail_data_for_oscylograph) &&
             (data_for_oscylograph[tail_data_for_oscylograph].VAL_1_fix != 0) &&
             (data_for_oscylograph[tail_data_for_oscylograph].VAL_2_fix != 0)
            )
      {
        unsigned int tail_data_for_oscylograph_tmp = tail_data_for_oscylograph;
        for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
        {
          int data_tmp = data_for_oscylograph[tail_data_for_oscylograph_tmp].data[i];
          
          //�������� ����������
          current_data[index_array_of_current_data_value++] = data_tmp;
          
          if((prescaler_ar & MASKA_BIT_FOR_PRESCALER) == 0)
          {
            //����� ������� ���������� ������� ��� ����������� ����������
//            array_ar[index_array_ar_current++] = data_tmp;
            AR_WRITE(index_array_ar_current, data_tmp);
          }
        }
        //������ ��������� �����������
        if (index_array_of_current_data_value >= (NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT)) index_array_of_current_data_value = 0;/*����� ��� �� ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/

        //����� ���������� ������� ��� ����������� ����������
        unsigned int *label_to_active_functions_source = data_for_oscylograph[tail_data_for_oscylograph_tmp].active_functions;
        if((prescaler_ar & MASKA_BIT_FOR_PRESCALER) != 0)
        {
          for (unsigned int i = 0; i < N_BIG; i++)  active_functions_trg[i] = *(label_to_active_functions_source + i);
        }
        else
        {
          for (unsigned int i = 0; i < N_BIG; i++)  active_functions_trg[i] |= *(label_to_active_functions_source + i);

          unsigned short int *label_to_active_functions_trg = (unsigned short int*)active_functions_trg;
          for(unsigned int i = 0; i < number_word_digital_part_ar; i++) 
          {
//            array_ar[index_array_ar_current++] = *(label_to_active_functions_trg + i);
            AR_WRITE(index_array_ar_current, *(label_to_active_functions_trg + i));
          }
          //������ ������ ��'������� ������� ��� ����������� ����������
          if (index_array_ar_current >= SIZE_BUFFER_FOR_AR) index_array_ar_current = 0;/*����� ���� � ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/
          
          //������������ ������� ���� ������� � ������ ���������� �� ������������� ������ ��'������� ������� ��� ����������� ����������
          if (
              (data_for_oscylograph[tail_data_for_oscylograph_tmp].state_ar_record == STATE_AR_START) ||
              (data_for_oscylograph[tail_data_for_oscylograph_tmp].state_ar_record == STATE_AR_SAVE_SRAM_AND_SAVE_FLASH)
             )
          {
            number_postfault_slices++;
          }
        }
        prescaler_ar++;
    
        data_for_oscylograph[tail_data_for_oscylograph_tmp].VAL_1_fix = 0;
        data_for_oscylograph[tail_data_for_oscylograph_tmp].VAL_2_fix = 0;

        if (++tail_data_for_oscylograph >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) tail_data_for_oscylograph = 0;
      }
    }
    /**************************************************/
    //��� ����������� ����������� ��� ����� � ���������� ������� �������
    /**************************************************/
    if (wait_of_receiving_current_data  == true) wait_of_receiving_current_data  = false;
    /**************************************************/

    //��������� ���������� ������������
    if ((state_ar_record == STATE_AR_START) || (state_ar_record == STATE_AR_SAVE_SRAM_AND_SAVE_FLASH))
    {
      static unsigned int uncopied_postfault_time_sapmles;

      /*
      ��� ����� ��� ������������� ������ � ������� ������� � �����
      */
        
      if (state_ar_record == STATE_AR_START)
      {
        int difference;
        /*
        ������� number_postfault_slices ������������ ���� ������� � �����,
        �� ��� ���������� ����� ���� ������������� ������ �� index_array_ar_current
        ������ ������� ������� ������� � ������ ���
        */
        /*
        ������������ ���� ������� �������� �������� ������������ ������ � 
        ��������� �������� �� � ����� "��������" ��� ����, ��� ������ �������� 
        ���� "������������", ����� �������, ������
        */
        difference = index_array_ar_current - number_postfault_slices*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar);
        if (difference >= 0) index_array_ar_heat = difference;
        else index_array_ar_heat = difference + SIZE_BUFFER_FOR_AR;

        //������������ ���� "��������"
        difference = index_array_ar_heat - (current_settings_prt.prefault_number_periods << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar);
        if (difference >= 0) index_array_ar_tail = difference;
        else index_array_ar_tail = difference + SIZE_BUFFER_FOR_AR;
          
        //��������� ������ ����� ���� �������� ��� ������������� ������
        /*
        !!!� ������ ���� ������� ���� � �� ������� ������� �������, ��� �����
        ���� ������� � ����� ���� ��� �������� �� �������� � ������ � ������� ������,
        � ������� �� �������� �� �������!!!
        */
        uncopied_postfault_time_sapmles = (current_settings_prt.postfault_number_periods << VAGA_NUMBER_POINT_AR);

        /*
        ��� �� ���� ��������, �� ����������� �� ������� �� �� ������� ���� �����
        ����, �� �� ����� ������ �� ������������� ������ - �� ������� �� ����� ����, �� ���� ��� 
        ����� ���� ������� � ���������� ���������.
        */
        unsigned int tail_data_for_oscylograph_tmp = tail_data_for_oscylograph;
        while (head_data_for_oscylograph_tmp != tail_data_for_oscylograph_tmp)
        {
           data_for_oscylograph[tail_data_for_oscylograph_tmp++].state_ar_record = state_ar_record;
           if (tail_data_for_oscylograph_tmp >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) tail_data_for_oscylograph_tmp = 0;
        }

        //���������� � ���� ������ ����������� ���������� "�������� � ��������"
        state_ar_record = STATE_AR_SAVE_SRAM_AND_SAVE_FLASH;

      }
        
      /*
      ������������ ���� "��������" � ���������� ������������ ������ � ����� 
      ��������, �� ���� �������� ���������� �� �������, �� �� ����� ���� � 
      ����� index_array_ar_heat ����������� �������� ���� "��������" �� ��������� 
      number_postfault_slices ����. 
      ��� ������ ��� ������ number_postfault_slices ���� � �����
      index_array_ar_current ������� � ������� ���� "����������" ������ ������� 
      ������� ��� ����������� ����������.
      */

      /*
      �������� ��������� �������� ������������ ������ (����������� �� ������� ����� �
      �� ���� ��������, ���� � ��������� ������ ����� ������ � ������������ 
      ������������� �������� ����������� � ������������� ������ � ����������
      "��������" � "��������")
      */
      int difference_before, difference_after;
      unsigned int index_array_ar_tail_tmp = index_array_ar_tail;
      difference_before = (index_array_ar_heat - index_array_ar_tail_tmp);
      if (difference_before < 0) difference_before += SIZE_BUFFER_FOR_AR;
      difference_after = (index_array_ar_current - index_array_ar_tail_tmp);
      if (difference_after < 0) difference_after += SIZE_BUFFER_FOR_AR;
      if ((difference_after - difference_before) != number_postfault_slices*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar))
      {
        //��������� ��������, ��� ��������� ������������� 
        _SET_BIT(set_diagnostyka, ERROR_AR_OVERLOAD_BUFFER_BIT);
      }
      else
      {
        //���� ��������� ��������, ��� ��������� �������������
        _SET_BIT(clear_diagnostyka, ERROR_AR_OVERLOAD_BUFFER_BIT);
      }

      //������������ ���� "��������" � ������� ����, �� �� ����� �������� �� ������������� ������
      if (uncopied_postfault_time_sapmles >= number_postfault_slices)
      {
        index_array_ar_heat = index_array_ar_current;
        uncopied_postfault_time_sapmles -= number_postfault_slices;
      }
      else
      {
        int difference = index_array_ar_current - (number_postfault_slices - uncopied_postfault_time_sapmles);
        if (difference >= 0) index_array_ar_heat = difference;
        else index_array_ar_heat = difference + SIZE_BUFFER_FOR_AR;

        uncopied_postfault_time_sapmles = 0;
      }

      if (uncopied_postfault_time_sapmles == 0)
      {
        /*
        �� ���������� ���� ��� �������� � ���� ���������� ����� ������ 
        ����������� ���������� � ����� ����� ������ ��� ������� �� �� �� �������
        */
        state_ar_record = STATE_AR_ONLY_SAVE_FLASH;

        /*
        ��� �� ���� ��������, �� ����������� �� ������� ��� ������� ��� �����
        ����, �� ����� ������ �� ������������� ������, ��� �� ���� �� ��������,
        �� �� ���� ��������� ��� - �� ������� �� ����� ����, �� ���� ��� 
        �������� �� ������������ �����.
        */
        unsigned int tail_data_for_oscylograph_tmp = tail_data_for_oscylograph;
        while (head_data_for_oscylograph_tmp != tail_data_for_oscylograph_tmp)
        {
           data_for_oscylograph[tail_data_for_oscylograph_tmp++].state_ar_record = state_ar_record;
           if (tail_data_for_oscylograph_tmp >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) tail_data_for_oscylograph_tmp = 0;
        }
      }
        
    }
    /*******************************************************/
    
    if ((status_adc_read_work & TEST_VAL_READ) != 0)
    {
      //����� ���������� ���������� ��������
      operate_test_ADCs();
    
      status_adc_read_work &= (unsigned int)(~TEST_VAL_READ);

      /**************************************************/
      //����������� ����������� ��� ���������� �������� �������
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_TEST_VAL;
      /**************************************************/
      
      /**************************************************/
      //���� ����� ����� ���������� �� ���� ������
      /**************************************************/
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
      {
        //����� ���������������� ����� � ����������� ��� �������� I2C
        _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
      /**************************************************/
    }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
  }

  if ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0)
  {
    //����� ���� �� ������� �������� control_reading_ADCs
    
    /*
    ������� � ���� ���������� ������� ������� control_reading_ADCs �� ������
    ������� ����������� �� ������� ��������� ��� ������ �� ���������
    */
    
    /*
    ����������� ��������� ����������, ��� ���� �� �������� ��� ���� ����� �����
    �� ��������� �� ����� �� ���������
    */
    __disable_interrupt();
    
    /*
    ��������, �� ���� ����� ����� �� ��������� � ���� �� ������ ������� �����
    ����� �� ���������, �� ������������ ��������� ������� ��������� � �����������
    ������� ( chip select ����������� � 1)
    */
    if (
        (adc_DATA_VAL_1_read == false) &&
        (adc_DATA_VAL_2_read == false) &&
        (adc_TEST_VAL_read   == false)
       )
    {
      semaphore_adc_irq  = false;
    }
    
    /*
    ���������� ��������� ����������
    */
     __enable_interrupt();
  }
  else semaphore_adc_irq  = false;

  
  if (semaphore_adc_irq  != false)
  {
    /*
    �� ����� ���� ���� ����� � ������ �������: ���� ��� ����� �� ��� ��� �� ���������
    � ������� ��������� ������� ������� control_reading_ADCs �� �������� ����������
    �������� __disable_interrupt ��� ������� ���������.
    
    ������ � ���� ������� ������� control_reading_ADCs. �������� �� ����, ��
    chip_select ������ ����������� � ������� ���� (�� �� ������� �������� 
    if ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0)) � ����� semaphore_adc_irq ��
    �� ���� false, � ��� ����� ����� ������ ��������� � ����������� �������
    */
    
    control_reading_ADCs(TN1_TN2_meas);
    
    /*
    ������� ���������. ���� �������� �� �� � ���������� ������� ����������� �����, �� ������� �� SPI
    ����������. ��� ��� ��������� ��� ����� �� �����, �� ������ ������� control_reading_ADCs
    ��� ����������� ����, �� ��� �� ��������� "������ � ����"  ������ ������
    ��������� - � �� ������� ����� ���, ���� chip_select ���� �������� ���� ������������ � ������� �����
    
    � ������������ chip_select ����� � ������� ����� ����� ���� ����� ����������� ����������� ��
    ����� SPI
    */
    semaphore_adc_irq  = false;
  }
  
//#ifdef SYSTEM_VIEWER_ENABLE
//  SEGGER_SYSVIEW_RecordExitISR();
//#endif
}
/*****************************************************/

/*****************************************************/
//����������� ����
/*****************************************************/
void calc_angle(void) 
{
  //������� ����������
  semaphore_measure_values_low1 = 1;
  for (unsigned int i = 0; i < (NUMBER_ANALOG_CANALES + 8); i++ ) 
  {
    measurement_low[i] = measurement_middle[i];
  }
  semaphore_measure_values_low1 = 0;
              
  int ortogonal_low_tmp[2*FULL_ORT_MAX];
  int delta_phi_synchro_tmp;
  
  //����������� ������� �������� ���������� ������� � ������� �������
  semaphore_measure_values_low = 1;
  for(unsigned int i = 0; i < (2*FULL_ORT_MAX); i++ )
  {
      ortogonal_low_tmp[i] = ortogonal_calc_low[i];
  } 
  delta_phi_synchro_tmp = delta_phi_synchro;
  //������ ������� �������� ���������� ������� � ������� �������
  semaphore_measure_values_low = 0;
  
  //���������, ���� ������ ������ �� ������
  __full_ort_index index_base = FULL_ORT_Ua1;

  /***
  ���������, ���� ������� ������ ����� ����� �� ������
  ***/
  __full_ort_index index_last = FULL_ORT_Uca2;
  /***/
  
  int base_index_for_angle_tmp = -1;
  __full_ort_index index = index_base;
  while( index <= index_last)
  {
    unsigned int index_m;
    switch (index)
    {
    case FULL_ORT_Ua1:
      {
        index_m = IM_UA1;
        break;
      }
    case FULL_ORT_Ub1:
      {
        index_m = IM_UB1;
        break;
      }
    case FULL_ORT_Uc1:
      {
        index_m = IM_UC1;
        break;
      }
    case FULL_ORT_Ua2:
      {
        index_m = IM_UA2;
        break;
      }
    case FULL_ORT_Ub2:
      {
        index_m = IM_UB2;
        break;
      }
    case FULL_ORT_Uc2:
      {
        index_m = IM_UC2;
        break;
      }
    case FULL_ORT_Uab1:
      {
        index_m = IM_UAB1;
        break;
      }
    case FULL_ORT_Ubc1:
      {
        index_m = IM_UBC1;
        break;
      }
    case FULL_ORT_Uca1:
      {
        index_m = IM_UCA1;
        break;
      }
    case FULL_ORT_Uab2:
      {
        index_m = IM_UAB2;
        break;
      }
    case FULL_ORT_Ubc2:
      {
        index_m = IM_UBC2;
        break;
      }
    case FULL_ORT_Uca2:
      {
        index_m = IM_UCA2;
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(61);
      }
    }
  
    if (measurement_low[index_m] >= PORIG_CHUTLYVOSTI_VOLTAGE)
    {
      base_index_for_angle_tmp = index;
      break; //����� �� ����� while
    }
    index++;
  }
  base_index_for_angle = base_index_for_angle_tmp;
  
  if (base_index_for_angle_tmp >= 0)
  {
    //���������� �������� �������, ������� ����� ������ ������ ����
    int ortogonal_base[2] = {ortogonal_low_tmp[2*base_index_for_angle_tmp], ortogonal_low_tmp[2*base_index_for_angle_tmp + 1]};
    
#define SIN_BASE   ortogonal_base[0]
#define COS_BASE   ortogonal_base[1]

    unsigned int amplituda_base = sqrt_64((unsigned long long)((long long)SIN_BASE*(long long)SIN_BASE) + (unsigned long long)((long long)COS_BASE*(long long)COS_BASE));
    if (amplituda_base != 0)
    {
      for (__full_ort_index index_tmp = index_base; index_tmp < FULL_ORT_MAX; index_tmp++)
      {
        if (index_tmp == index)
        {
          phi_angle[index_tmp] = 0;
          continue;
        }
        else
        {
          unsigned int porig_chutlyvosti;
          unsigned int index_m;
          switch (index_tmp)
          {
          case FULL_ORT_Ua1:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UA1;
              break;
            }
          case FULL_ORT_Ub1:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UB1;
              break;
            }
          case FULL_ORT_Uc1:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UC1;
              break;
            }
          case FULL_ORT_Ua2:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UA2;
              break;
            }
          case FULL_ORT_Ub2:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UB2;
              break;
            }
          case FULL_ORT_Uc2:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UC2;
              break;
            }
          case FULL_ORT_Uab1:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UAB1;
              break;
            }
          case FULL_ORT_Ubc1:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UBC1;
              break;
            }
          case FULL_ORT_Uca1:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UCA1;
              break;
            }
          case FULL_ORT_Uab2:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UAB2;
              break;
            }
          case FULL_ORT_Ubc2:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UBC2;
              break;
            }
          case FULL_ORT_Uca2:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE;
              index_m = IM_UCA2;
              break;
            }
          case FULL_ORT_Ia:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_CURRENT;
              index_m = IM_IA;
              break;
            }
          case FULL_ORT_Ib:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_CURRENT;
              index_m = IM_IB;
              break;
            }
          case FULL_ORT_Ic:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_CURRENT;
              index_m = IM_IC;
              break;
            }
          default:
            {
              //���������� ����� ����� �� ���� � ����
              total_error_sw_fixed(62);
            }
          }
      
          if (measurement_low[index_m] >= porig_chutlyvosti)
          {
            //����������� ���
#define SIN_TARGET ortogonal_low_tmp[2*index_tmp]
#define COS_TARGET ortogonal_low_tmp[2*index_tmp + 1]

            unsigned int amplituda_target = sqrt_64((unsigned long long)((long long)SIN_TARGET*(long long)SIN_TARGET) + (unsigned long long)((long long)COS_TARGET*(long long)COS_TARGET));
      
            if (amplituda_target != 0)
            {
              //���������� COS � SIN ���� ������ �� ���������
              long long cos_fi = COS_TARGET*COS_BASE + SIN_TARGET*SIN_BASE;
              long long sin_fi = -(SIN_TARGET*COS_BASE - COS_TARGET*SIN_BASE);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������

#undef SIN_TARGET
#undef COS_TARGET
      
              float sin_fi_f = ( ((float)sin_fi) / ((float)amplituda_target) ) / ((float)amplituda_base);
              if (sin_fi_f > 1) sin_fi_f = 1;
              else if (sin_fi_f < -1) sin_fi_f = -1;
      
              float angle_f = asin(sin_fi_f)*180 / PI;
              int angle_int = (int)(angle_f*10); //������ ������� �� �������
              if (angle_int < 0) angle_int = -angle_int;
      
              if ((sin_fi >= 0) && (cos_fi >= 0))
              {
                //1-�� ��������
                //angle_int ���������� ��� ����
              }
              else if ((sin_fi >= 0) && (cos_fi <  0))
              {
                //2-�� ��������
                angle_int = 1800 - angle_int;
              }
              else if ((sin_fi <  0) && (cos_fi <  0))
              {
                //3-�� ��������
                angle_int = 1800 + angle_int;
              }
              else
              {
                //4-�� ��������
                angle_int = 3600 - angle_int;
              }
    
              if ((angle_int <= -3600) || (angle_int >= 3600)) angle_int %= 3600;
              while (angle_int < 0) angle_int += 3600;
      
              phi_angle[index_tmp] = angle_int;
      
            }
            else
            {
              phi_angle[index_tmp] = -1;
            }

          }
          else
          {
            //������ ������������� ������� ����� ������ - ��� ������������
            phi_angle[index_tmp] = -1;
          }
        }
      }
    }
    else
    {
      //�������� �������� ������� ���������� �� ���������� ��� ���� ������� ���� 0 (� �����, �� ���� �������� �� ���� � ����� ��������). �� �������������.
      for (__full_ort_index index_tmp = FULL_ORT_Ua1; index_tmp < FULL_ORT_MAX; index_tmp++) phi_angle[index_tmp] = -1;
    }

#undef SIN_BASE
#undef COS_BASE
    
  }
  else
  {
    //�� ����������� ������� ����������, ������� ����� ����� ������������� ����
    for (__full_ort_index index_tmp = FULL_ORT_Ua1; index_tmp < FULL_ORT_MAX; index_tmp++) phi_angle[index_tmp] = -1;
  }
  
  /***
  ��������� ���� ��� ���� ����������� ������
  ***/
  unsigned int bank_phi_angle_high_tmp = (bank_phi_angle_high ^ 0x1) & 0x1;
  for (__full_ort_index index_tmp = FULL_ORT_Ua1; index_tmp < FULL_ORT_MAX; index_tmp++) phi_angle_high[bank_phi_angle_high_tmp][index_tmp] = phi_angle[index_tmp];
  bank_phi_angle_high = bank_phi_angle_high_tmp;
  /***/
    
  
  /***
  ������������ �� ����1 � ����2
  ***/
  unsigned int frequency_locking_bank_tmp = (frequency_locking_bank ^ 0x1) & 0x1;
  if (
      (delta_phi_synchro_tmp != UNDEF_PHI) &&
      (delta_phi_index_1_work_low >= INDEX_PhK_UA1)  && (delta_phi_index_1_work_low <= INDEX_PhK_UC1) &&
      (delta_phi_index_2_work_low >= INDEX_PhK_UA2)  && (delta_phi_index_2_work_low <= INDEX_PhK_UC2)
     )   
  {
    //����� ���������� ���������� ��� ������������
    int phi_angle_fapch1;
    switch (delta_phi_index_1_work_low)
    {
    case INDEX_PhK_UA1:
      {
        phi_angle_fapch1 = phi_angle[FULL_ORT_Ua1];
        break;
      }
    case INDEX_PhK_UB1:
      {
        phi_angle_fapch1 = phi_angle[FULL_ORT_Ub1];
        break;
      }
    case INDEX_PhK_UC1:
      {
        phi_angle_fapch1 = phi_angle[FULL_ORT_Uc1];
        break;
      }
   default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(84);
      }
    }
        
    int phi_angle_fapch2;
    switch (delta_phi_index_2_work_low)
    {
    case INDEX_PhK_UA2:
      {
        phi_angle_fapch2 = phi_angle[FULL_ORT_Ua2];
        break;
      }
    case INDEX_PhK_UB2:
      {
        phi_angle_fapch2 = phi_angle[FULL_ORT_Ub2];
        break;
      }
    case INDEX_PhK_UC2:
      {
        phi_angle_fapch2 = phi_angle[FULL_ORT_Uc2];
        break;
      }
   default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(85);
      }
    }
        
    if (
        (phi_angle_fapch1 >= 0) &&
        (phi_angle_fapch2 >= 0)
       )   
    {
      frequency_locking_phi += (phi_angle_fapch2 - phi_angle_fapch1 - delta_phi_synchro_tmp);
      if ((frequency_locking_phi <= -3600) || (frequency_locking_phi >= 3600)) frequency_locking_phi %= 3600;
      while (frequency_locking_phi < 0) frequency_locking_phi += 3600;

      float radian_frequency_locking_phi = PI*((float)frequency_locking_phi)/1800.0f; /*��� � ��� ������������� � ������ �� �������, ���� � �� ����� �� 1800, � �� �� 180*/
      frequency_locking_cos[frequency_locking_bank_tmp] = arm_cos_f32(radian_frequency_locking_phi);
      frequency_locking_sin[frequency_locking_bank_tmp] = arm_sin_f32(radian_frequency_locking_phi);
    }
    else
    {
      frequency_locking_phi = 0;
      frequency_locking_cos[frequency_locking_bank_tmp] = 1.0f;
      frequency_locking_sin[frequency_locking_bank_tmp] = 0.0f;
    }
  }
  else
  {
    frequency_locking_phi = 0;
    frequency_locking_cos[frequency_locking_bank_tmp] = 1.0f;
    frequency_locking_sin[frequency_locking_bank_tmp] = 0.0f;
  }
  frequency_locking_bank = frequency_locking_bank_tmp;
  /***/
}

/*****************************************************/

/*****************************************************/
//����������� ������ ���������
/*****************************************************/
void calc_power_and_energy(void) 
{
  //��������� ���� �� ������������� ������ ��� �������
  unsigned int bank_for_enegry_tmp = (bank_for_enegry + 1) & 0x1;
  
  int P_tmp = P_plus[bank_for_enegry_tmp] - P_minus[bank_for_enegry_tmp];
  int Q_tmp = Q_1q[bank_for_enegry_tmp] + Q_2q[bank_for_enegry_tmp] - Q_3q[bank_for_enegry_tmp] - Q_4q[bank_for_enegry_tmp];

  //����������� ������
  unsigned int clean_energy_tmp = clean_energy;
  if (clean_energy_tmp != 0) 
  {
    clean_energy = 0;

    if ((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET)
    {
      //��������� ����� � EEPROM
      _SET_BIT(control_spi1_taskes, TASK_START_WRITE_ENERGY_EEPROM_BIT);
    }
    else number_minutes = PERIOD_SAVE_ENERGY_IN_MINUTES; /*���� �������� ����������, ��� ����� ���� ������ ������� �� �����*/

    //�������, �� �������� ������� ��������� ������
    information_about_clean_energy |= ((1 << USB_RECUEST)|(1 << RS485_RECUEST));
  }
  
  for (__index_energy i = INDEX_EA_PLUS; i < MAX_NUMBER_INDEXES_ENERGY; i++)
  {
    if (clean_energy_tmp != 0) energy[i] = 0;
    
    int power_data;
    switch (i)
    {
    case INDEX_EA_PLUS:
      {
        power_data = P_plus[bank_for_enegry_tmp];
        break;
      }
    case INDEX_EA_MINUS:
      {
        power_data = P_minus[bank_for_enegry_tmp];
        break;
      }
    case INDEX_ER_1:
      {
        power_data = Q_1q[bank_for_enegry_tmp];
        break;
      }
    case INDEX_ER_2:
      {
        power_data = Q_2q[bank_for_enegry_tmp];
        break;
      }
    case INDEX_ER_3:
      {
        power_data = Q_3q[bank_for_enegry_tmp];
        break;
      }
    case INDEX_ER_4:
      {
        power_data = Q_4q[bank_for_enegry_tmp];
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(65);
      }
    }
    
    if (power_data >= (PORIG_POWER_ENERGY*MAIN_FREQUENCY)) /*�� � power_data � ���� ������� ����������� �� 1�, �� ��������������� ���� 20��*/
    {
      double power_quantum = ((double)power_data)/(((double)MAIN_FREQUENCY)*DIV_kWh);
      double erergy_tmp = energy[i] + power_quantum;
      if (erergy_tmp > 999999.999) erergy_tmp = erergy_tmp - 999999.999;
      energy[i] = erergy_tmp;
    }
  }
  
  float P_float = ((float)P_tmp)/((float)MAIN_FREQUENCY);
  float Q_float = ((float)Q_tmp)/((float)MAIN_FREQUENCY);
  P = (int)P_float;
  Q = (int)Q_float;
  
  //����� ���������
  if ( (P != 0) || (Q != 0))
  {
    float in_square_root, S_float;
    in_square_root = P_float*P_float + Q_float*Q_float;
    
    if (arm_sqrt_f32(in_square_root, &S_float) == ARM_MATH_SUCCESS)
    {
      S = (unsigned int)S_float;
    }
    else
    {
      //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
      total_error_sw_fixed(53);
    }
    
    cos_phi_x1000 = (int)(1000.0f*P_float/S_float);
  }
  else
  {
    S = 0;
    cos_phi_x1000 = 0;
  }
  
}
/*****************************************************/
/*****************************************************
���������� ������ ��� �� ����� � ��������
******************************************************/
void delta_phi_routine(void)
{
  if (reset_delta_phi != false)
  {
    reset_delta_phi = false;
    delta_phi[bank_delta_phi] = UNDEF_PHI;
    speed_delta_phi[bank_delta_phi] = UNDEF_SPEED_PHI;
    
    bank_delta_phi = (bank_delta_phi ^ 0x1) & 0x1;
  }
  else
  {
    /*****/
    //г����� ��� �� ��1 � ��2
    /*****/

    semaphore_delta_phi = 1;
  
    unsigned int fix_perechid_cherez_nul_TN1_TN2_work_tmp = fix_perechid_cherez_nul_TN1_TN2_work;
    fix_perechid_cherez_nul_TN1_TN2_work = 0;

    float frequency_val_1_work_tmp = frequency_val_1_work;
    unsigned int tick_period_1_work_tmp = tick_period_1_work;
    unsigned int tick_c1_work_tmp = tick_c1_work;
    delta_phi_index_1_work_low = delta_phi_index_1_work_middle;

    float frequency_val_2_work_tmp = frequency_val_2_work;
    unsigned int tick_period_2_work_tmp = tick_period_2_work;
    unsigned int tick_c2_work_tmp = tick_c2_work;
    delta_phi_index_2_work_low = delta_phi_index_2_work_middle;
  
    semaphore_delta_phi = 0;
  
    if ((fix_perechid_cherez_nul_TN1_TN2_work_tmp & ((1 << INDEX_U_1_MEAS) | (1 << INDEX_U_2_MEAS))) == ((1 << INDEX_U_1_MEAS) | (1 << INDEX_U_2_MEAS))) 
    {
      if (
          (frequency_val_1_work_tmp > 0) &&
          (frequency_val_2_work_tmp > 0)
         ) 
      {
        //����� ������������� �������� ���� ����� ��� � ��������/c (� ������� �� ������� ������� - ���� ������ ����� 3600, � �� 360)
        speed_delta_phi[bank_delta_phi] = (int)(3600.0f*(frequency_val_1_work_tmp - frequency_val_2_work_tmp));
      
        unsigned int min_tick_period = tick_period_1_work_tmp, max_tick_period = tick_period_1_work_tmp;
        if (tick_period_2_work_tmp < min_tick_period) min_tick_period = tick_period_2_work_tmp;
        if (tick_period_2_work_tmp > max_tick_period) max_tick_period = tick_period_2_work_tmp;
        if (
            (max_tick_period <= MAX_TICK_PERIOD) &&
            (min_tick_period >= MIN_TICK_PERIOD)
           )   
        {
          //����� ����������� ������ ��� �� ��1 � ��2
          long long delta_phi_tick = ((long long)tick_c1_work_tmp) - ((long long)tick_c2_work_tmp);
          unsigned long long modul_delta_phi_tick = llabs(delta_phi_tick);
    
          if (
              (delta_phi_tick < 0) &&
              (modul_delta_phi_tick >= max_tick_period)
             )       
          {
            /*
            �������, ���� ������ �������� ��� ����������� �������� ��� �������� ��������
            ����� ���� ��1, � ���� ��� ������� ����� ���� ��2 - �� �� ������ �� �������� 
            ��� ����������� ��������
            */
            delta_phi_tick = delta_phi_tick + 0x100000000;
            modul_delta_phi_tick = llabs(delta_phi_tick);
          }
        
          while (modul_delta_phi_tick > tick_period_2_work_tmp) 
          {
            if (delta_phi_tick < 0 ) delta_phi_tick += tick_period_2_work_tmp;
            else delta_phi_tick -= tick_period_2_work_tmp;
            modul_delta_phi_tick = llabs(delta_phi_tick);
          }
          if (delta_phi_tick < 0 ) delta_phi_tick += tick_period_2_work_tmp;
    
          //����� ������������� ���� ��� � �������� (� ������� �� ������� ������� - ���� ������ ����� 3600, � �� 360)
          int delta_phi_tmp = (int)((3600.0f*((float)delta_phi_tick)*frequency_val_2_work_tmp)/((float)MEASUREMENT_TIM_FREQUENCY));
          if ((delta_phi_tmp <= -3600) || ( delta_phi_tmp >= 3600))  delta_phi_tmp %= 3600;
          while (delta_phi_tmp < 0) delta_phi_tmp += 3600;
          delta_phi[bank_delta_phi] = delta_phi_tmp;
          
          if (delta_phi[bank_delta_phi] < delta_phi_min) delta_phi_min = delta_phi[bank_delta_phi];
          if (delta_phi[bank_delta_phi] > delta_phi_max) delta_phi_max = delta_phi[bank_delta_phi];
        }
        else  delta_phi[bank_delta_phi] = UNDEF_PHI;
      }
      else 
      {
        delta_phi[bank_delta_phi] = UNDEF_PHI;
        speed_delta_phi[bank_delta_phi] = UNDEF_SPEED_PHI;
      }
    
      tick_0[bank_delta_phi] = tick_c1_work_tmp;
      //������� �����
      bank_delta_phi = (bank_delta_phi ^ 0x1) & 0x1;
    }
  }
}
/*****************************************************/

/*****************************************************
���������� ������ ��� �� ��1 � ��2 � ����-���� ������ ����
*****************************************************/
void current_delta_phi(void)
{
  //�������� ����, � ����� � ������ ���������� ���
  unsigned int bank_delta_phi_tmp = (bank_delta_phi ^ 0x1) & 0x1;
  
  if (
      (delta_phi[bank_delta_phi_tmp] != UNDEF_PHI) &&
      (speed_delta_phi[bank_delta_phi_tmp] != UNDEF_SPEED_PHI)  
     )   
  {
    //����� ������������� �������� ��� �������������
    uint32_t current_tick = TIM5->CNT;
    int deta_tick = current_tick - tick_0[bank_delta_phi_tmp];
    if (deta_tick < 0)
    {
      long long deta_tick_tmp = deta_tick;
      deta_tick_tmp += 0x100000000;
      deta_tick = deta_tick_tmp;
    }
    int delta_phi_synchro_tmp = delta_phi[bank_delta_phi_tmp] + (int)((float)speed_delta_phi[bank_delta_phi_tmp]*((float)deta_tick)/((float)MEASUREMENT_TIM_FREQUENCY));
    if ((delta_phi_synchro_tmp <= -3600) || ( delta_phi_synchro_tmp >= 3600))  delta_phi_synchro_tmp %= 3600;
    while (delta_phi_synchro_tmp < 0) delta_phi_synchro_tmp += 3600;
    delta_phi_synchro = delta_phi_synchro_tmp;
  }
  else delta_phi_synchro = UNDEF_PHI;
}
/*****************************************************/

/*****************************************************/
//�������� ��������� ����������� ���
/*****************************************************/
unsigned int sequence_phases(int p_current_vector[][2], unsigned int *p_index_of_currnet_vector, unsigned int *p_ready_vectors, /*EXTENDED_SAMPLE*/int p_data[], unsigned int index_first_c_data, unsigned int index_first_i_data)
{
  unsigned int result = CONST_SEQ_UNDEF; //��������� � �������, ���� ���� � ���� ������� ����� ������
  
  unsigned int bank_measurement_high_tmp = bank_measurement_high;
  if (
      (measurement_high[bank_measurement_high_tmp][index_first_i_data  + 0] >= PORIG_FOR_FAPCH) &&
      (measurement_high[bank_measurement_high_tmp][index_first_i_data  + 1] >= PORIG_FOR_FAPCH) &&
      (measurement_high[bank_measurement_high_tmp][index_first_i_data  + 2] >= PORIG_FOR_FAPCH)
     )  
  {
   
    int a = p_data[index_first_c_data + 0]/*.value*/*ea[0] + p_data[index_first_c_data + 1]/*.value*/*eb[0] + p_data[index_first_c_data + 2]/*.value*/*ec[0];
    int b = p_data[index_first_c_data + 0]/*.value*/*ea[1] + p_data[index_first_c_data + 1]/*.value*/*eb[1] + p_data[index_first_c_data + 2]/*.value*/*ec[1];
    
    p_current_vector[*p_index_of_currnet_vector][0] = a;
    p_current_vector[*p_index_of_currnet_vector][1] = b;
    *p_index_of_currnet_vector = (*p_index_of_currnet_vector + 1) & 0x1; //���� ���� �������� p_index_of_currnet_vector ����� �� �������� ������ (t - dt) � � �� ���� ���� ������������ ��������� �������� ������
    if (*p_ready_vectors < 2) (*p_ready_vectors)++;
 
    if (*p_ready_vectors >= 2)
    {
      long long value = ((long long)p_current_vector[*p_index_of_currnet_vector][0])*((long long)b) - 
                        ((long long)p_current_vector[*p_index_of_currnet_vector][1])*((long long)a);
      
      if (value > 0) result = CONST_SEQ_OK; //� �������
      else if (value < 0) result = CONST_SEQ_FAIL; //���� ������
      else result = CONST_SEQ_UNREAL; //������������ ����, ���� ����� �� ��� �� �������� (������� �� ���������, ��� ������������ �� �� 180 �������)
    }
    else
    {
      //�� �� ����� ��������� ������������, �� ���� ���� �������
      result = CONST_SEQ_UNDEF;
    }
    
  }
  else
  {
    //���� � ���� ������� ����� ������
    p_current_vector[0][0] = 0;
    p_current_vector[0][1] = 0;
    p_current_vector[1][0] = 0;
    p_current_vector[1][1] = 0;
    *p_index_of_currnet_vector = 0;
    *p_ready_vectors = 0;
    
    result = CONST_SEQ_UNDEF;
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
