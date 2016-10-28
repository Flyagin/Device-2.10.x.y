#include "header.h"

/*****************************************************/
//������� ����� ����������� ������� ��� Umin
/*****************************************************/
void make_ekran_setpoint_avr_Umin(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_AVR_UMIN][MAX_COL_LCD] = 
  {
    {
      "  U1min < U1x   ",
      "  U2min > U2x   ",
      "  U2min < U2x   ",
      "  U1min > U1x   "
    },
    {
      "  U1min < U1x   ",
      "  U2min > U2x   ",
      "  U2min < U2x   ",
      "  U1min > U1x   "
    },
    {
      "  U1min < U1x   ",
      "  U2min > U2x   ",
      "  U2min < U2x   ",
      "  U1min > U1x   "
    },
    {
      "  U1min < U1x   ",
      "  U2min > U2x   ",
      "  U2min < U2x   ",
      "  U1min > U1x   "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_SETPOINT_AVR_UMIN<<1))//�������� �� ��� ��������� MAX_ROW_FOR_SETPOINT_AVR_UMIN ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN1_U1_UMIN)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_tn1_U1_Umin[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_tn1_U1_Umin[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_tn1_U2_low_work[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_tn1_U2_low_work[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN2_U2_UMIN)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_tn2_U2_Umin[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_tn2_U2_Umin[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_tn2_U1_low_work[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_tn2_U1_low_work[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN1_U1_UMIN)
          {
            if (
                ((j < COL_SETPOINT_AVR_TN1_U1_UMIN_BEGIN) ||  (j > COL_SETPOINT_AVR_TN1_U1_UMIN_END ))  &&
                (j != (COL_SETPOINT_AVR_TN1_U1_UMIN_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_TN1_U1_UMIN_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_TN1_U1_UMIN_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_TN1_U1_UMIN_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
          {
            if (
                ((j < COL_SETPOINT_AVR_TN1_U2_LOW_WORK_BEGIN) ||  (j > COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END ))  &&
                (j != (COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_TN1_U2_LOW_WORK_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_TN1_U2_LOW_WORK_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN2_U2_UMIN)
          {
            if (
                ((j < COL_SETPOINT_AVR_TN2_U2_UMIN_BEGIN) ||  (j > COL_SETPOINT_AVR_TN2_U2_UMIN_END )) &&
                (j != (COL_SETPOINT_AVR_TN2_U2_UMIN_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_TN2_U2_UMIN_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_TN2_U2_UMIN_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_TN2_U2_UMIN_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
          {
            if (
                ((j < COL_SETPOINT_AVR_TN2_U1_LOW_WORK_BEGIN) ||  (j > COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END ))  &&
                (j != (COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_TN2_U1_LOW_WORK_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_TN2_U1_LOW_WORK_COMMA, 0);
          }
        }
      }
        
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (current_ekran.edition == 0)
  {
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMIN)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMIN_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMIN_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_LOW_WORK)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U2_LOW_WORK_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_TN1_U2_LOW_WORK_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMIN) 
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMIN_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMIN_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_LOW_WORK)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U1_LOW_WORK_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_TN2_U1_LOW_WORK_END;
    }
    
    //ϳ������� ������ �� ������� �������
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;
    
    //������ ������� ���, ��� �� ��� ����� ������
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ������� ��� Umin
/*****************************************************/
void make_ekran_setpoint_avr_Umax(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_AVR_UMAX][MAX_COL_LCD] = 
  {
    {
      "  U1max > U1x   ",
      "  U2max < U2x   ",
      "  U2max > U2x   ",
      "  U1max < U1x   "
    },
    {
      "  U1max > U1x   ",
      "  U2max < U2x   ",
      "  U2max > U2x   ",
      "  U1max < U1x   "
    },
    {
      "  U1max > U1x   ",
      "  U2max < U2x   ",
      "  U2max > U2x   ",
      "  U1max < U1x   "
    },
    {
      "  U1max > U1x   ",
      "  U2max < U2x   ",
      "  U2max > U2x   ",
      "  U1max < U1x   "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_SETPOINT_AVR_UMAX<<1))//�������� �� ��� ��������� MAX_ROW_FOR_SETPOINT_AVR_UMAX ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN1_U1_UMAX)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_tn1_U1_Umax[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_tn1_U1_Umax[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_tn1_U2_high_work[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_tn1_U2_high_work[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN2_U2_UMAX)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_tn2_U2_Umax[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_tn2_U2_Umax[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_tn2_U1_high_work[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_tn2_U1_high_work[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN1_U1_UMAX)
          {
            if (
                ((j < COL_SETPOINT_AVR_TN1_U1_UMAX_BEGIN) ||  (j > COL_SETPOINT_AVR_TN1_U1_UMAX_END ))  &&
                (j != (COL_SETPOINT_AVR_TN1_U1_UMAX_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_TN1_U1_UMAX_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_TN1_U1_UMAX_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_TN1_U1_UMAX_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
          {
            if (
                ((j < COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_BEGIN) ||  (j > COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END ))  &&
                (j != (COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN2_U2_UMAX)
          {
            if (
                ((j < COL_SETPOINT_AVR_TN2_U2_UMAX_BEGIN) ||  (j > COL_SETPOINT_AVR_TN2_U2_UMAX_END ))  &&
                (j != (COL_SETPOINT_AVR_TN2_U2_UMAX_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_TN2_U2_UMAX_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_TN2_U2_UMAX_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_TN2_U2_UMAX_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
          {
            if (
                ((j < COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_BEGIN) ||  (j > COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END ))  &&
                (j != (COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_COMMA, 0);
          }
        }
      }
        
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (current_ekran.edition == 0)
  {
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U1_UMAX)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMAX_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_TN1_U1_UMAX_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_TN1_U2_HIGH_WORK)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_TN1_U2_HIGH_WORK_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U2_UMAX)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMAX_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_TN2_U2_UMAX_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_TN2_U1_HIGH_WORK)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_TN2_U1_HIGH_WORK_END;
    }
    
    //ϳ������� ������ �� ������� �������
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;
    
    //������ ������� ���, ��� �� ��� ����� ������
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ��� (�������)
/*****************************************************/
void make_ekran_timeout_avr_general(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_AVR_GENERAL][MAX_COL_LCD] = 
  {
    {
      " ����.��� ���.1 ",
      "   ���� ���.1   ",
      "����.�����.���.1",
      " ���.���.���.1  ",
      "   ���.���.1    ",
      "   ����.���.1   ",
      " ����.��� ���.2 ",
      "   ���� ���.2   ",
      "����.�����.���.2",
      " ���.���.���.2  ",
      "   ���.���.2    ",
      "   ����.���.2   "
    },
    {
      " ����.��� ���.1 ",
      "   ���� ���.1   ",
      " ����.䳿.���.1 ",
      " ����.���.���.1",
      "  ����.���.1   ",
      "   ����.���.1   ",
      " ����.��� ���.2 ",
      "   ���� ���.2   ",
      " ����.䳿.���.2 ",
      " ����.���.���.2",
      "  ����.���.2   ",
      "   ����.���.2   "
    },
    {
      " ����.��� ���.1 ",
      "   ���� ���.1   ",
      "����.�����.���.1",
      " ���.���.���.1  ",
      "   ���.���.1    ",
      "   ����.���.1   ",
      " ����.��� ���.2 ",
      "   ���� ���.2   ",
      "����.�����.���.2",
      " ���.���.���.2  ",
      "   ���.���.2    ",
      "   ����.���.2   "
    },
    {
      " ����.��� ���.1 ",
      "   ���� ���.1   ",
      "����.�����.���.1",
      " ���.���.���.1  ",
      "   ���.���.1    ",
      "   ����.���.1   ",
      " ����.��� ���.2 ",
      "   ���� ���.2   ",
      "����.�����.���.2",
      " ���.���.���.2  ",
      "   ���.���.2    ",
      "   ����.���.2   "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
 
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_TIMEOUT_AVR_GENERAL<<1))//�������� �� ��� ��������� MAX_ROW_FOR_TIMEOUT_AVR_GENERAL ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_BLK_K1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_blk_k1[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_blk_k1[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_PUSK_K1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_pusk_k1[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_pusk_k1[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_d_diji_k1[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_d_diji_k1[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vvimk_rez_k1[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vvimk_rez_k1[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vvimk_k1[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vvimk_k1[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VYMK_K1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vymk_k1[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vymk_k1[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_BLK_K2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_blk_k2[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_blk_k2[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_PUSK_K2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_pusk_k2[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_pusk_k2[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_d_diji_k2[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_d_diji_k2[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vvimk_rez_k2[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vvimk_rez_k2[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vvimk_k2[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vvimk_k2[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VYMK_K2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vymk_k2[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vymk_k2[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_BLK_K1)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_BLK_K1_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_BLK_K1_END )) &&
                (j != (COL_TMO_AVR_GENERAL_BLK_K1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_BLK_K1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_BLK_K1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_BLK_K1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_PUSK_K1)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_PUSK_K1_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_PUSK_K1_END )) &&
                (j != (COL_TMO_AVR_GENERAL_PUSK_K1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_PUSK_K1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_PUSK_K1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_PUSK_K1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_D_DIJI_K1_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_D_DIJI_K1_END )) &&
                (j != (COL_TMO_AVR_GENERAL_D_DIJI_K1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_D_DIJI_K1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_D_DIJI_K1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_D_DIJI_K1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_END )) &&
                (j != (COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_VVIMK_K1_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_VVIMK_K1_END )) &&
                (j != (COL_TMO_AVR_GENERAL_VVIMK_K1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_VVIMK_K1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_VVIMK_K1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_VVIMK_K1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VYMK_K1)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_VYMK_K1_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_VYMK_K1_END )) &&
                (j != (COL_TMO_AVR_GENERAL_VYMK_K1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_VYMK_K1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_VYMK_K1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_VYMK_K1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_BLK_K2)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_BLK_K2_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_BLK_K2_END )) &&
                (j != (COL_TMO_AVR_GENERAL_BLK_K2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_BLK_K2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_BLK_K2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_BLK_K2_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_PUSK_K2)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_PUSK_K2_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_PUSK_K2_END )) &&
                (j != (COL_TMO_AVR_GENERAL_PUSK_K2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_PUSK_K2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_PUSK_K2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_PUSK_K2_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_D_DIJI_K2_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_D_DIJI_K2_END )) &&
                (j != (COL_TMO_AVR_GENERAL_D_DIJI_K2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_D_DIJI_K2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_D_DIJI_K2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_D_DIJI_K2_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_END )) &&
                (j != (COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_VVIMK_K2_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_VVIMK_K2_END )) &&
                (j != (COL_TMO_AVR_GENERAL_VVIMK_K2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_VVIMK_K2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_VVIMK_K2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_VVIMK_K2_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_GENERAL_VYMK_K2)
          {
            if (
                ((j < COL_TMO_AVR_GENERAL_VYMK_K2_BEGIN) ||  (j > COL_TMO_AVR_GENERAL_VYMK_K2_END )) &&
                (j != (COL_TMO_AVR_GENERAL_VYMK_K2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_GENERAL_VYMK_K2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_GENERAL_VYMK_K2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_GENERAL_VYMK_K2_COMMA, 0);
          }
        }
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (current_ekran.edition == 0)
  {
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K1) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K1_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K1) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K1_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K1) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K1_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K1) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K1) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K1_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K1) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K1_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_BLK_K2) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K2_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_BLK_K2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_PUSK_K2) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K2_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_PUSK_K2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_D_DIJI_K2) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K2_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_D_DIJI_K2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_REZ_K2) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_REZ_K2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VVIMK_K2) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K2_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_VVIMK_K2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_GENERAL_VYMK_K2) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K2_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_GENERAL_VYMK_K2_END;
    }

    //ϳ������� ������ �� ������� �������
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;

    //������ ������� ���, ��� �� ��� ����� ������
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ��� Umin
/*****************************************************/
void make_ekran_timeout_avr_Umin(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_AVR_UMIN][MAX_COL_LCD] = 
  {
    {
      " ����.�.�.1 Umin",
      " ����.�.�.2 Umin"
    },
    {
      " ����.�.�.1 Umin",
      " ����.�.�.2 Umin"
    },
    {
      " ����.�.�.1 Umin",
      " ����.�.�.2 Umin"
    },
    {
      " ����.�.�.1 Umin",
      " ����.�.�.2 Umin"
    }
  };
  int index_language = index_language_in_array(current_settings.language);
 
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_TIMEOUT_AVR_UMIN<<1))//�������� �� ��� ��������� MAX_ROW_FOR_TIMEOUT_AVR_UMIN ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vymk_rob_k1_Umin[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vymk_rob_k1_Umin[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vymk_rob_k2_Umin[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vymk_rob_k2_Umin[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1)
          {
            if (
                ((j < COL_TMO_AVR_UMIN_VYMK_ROB_K1_BEGIN) ||  (j > COL_TMO_AVR_UMIN_VYMK_ROB_K1_END )) &&
                (j != (COL_TMO_AVR_UMIN_VYMK_ROB_K1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_UMIN_VYMK_ROB_K1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_UMIN_VYMK_ROB_K1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_UMIN_VYMK_ROB_K1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2)
          {
            if (
                ((j < COL_TMO_AVR_UMIN_VYMK_ROB_K2_BEGIN) ||  (j > COL_TMO_AVR_UMIN_VYMK_ROB_K2_END )) &&
                (j != (COL_TMO_AVR_UMIN_VYMK_ROB_K2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_UMIN_VYMK_ROB_K2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_UMIN_VYMK_ROB_K2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_UMIN_VYMK_ROB_K2_COMMA, 0);
          }
        }
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (current_ekran.edition == 0)
  {
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K1) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K1_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMIN_VYMK_ROB_K2) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K2_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_UMIN_VYMK_ROB_K2_END;
    }

    //ϳ������� ������ �� ������� �������
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;

    //������ ������� ���, ��� �� ��� ����� ������
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ��� Umax
/*****************************************************/
void make_ekran_timeout_avr_Umax(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_AVR_UMAX][MAX_COL_LCD] = 
  {
    {
      " ����.�.�.1 Umax",
      " ����.�.�.2 Umax"
    },
    {
      " ����.�.�.1 Umax",
      " ����.�.�.2 Umax"
    },
    {
      " ����.�.�.1 Umax",
      " ����.�.�.2 Umax"
    },
    {
      " ����.�.�.1 Umax",
      " ����.�.�.2 Umax"
    }
  };
  int index_language = index_language_in_array(current_settings.language);
 
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_TIMEOUT_AVR_UMAX<<1))//�������� �� ��� ��������� MAX_ROW_FOR_TIMEOUT_AVR_UMAX ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vymk_rob_k1_Umax[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vymk_rob_k1_Umax[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_vymk_rob_k2_Umax[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_vymk_rob_k2_Umax[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1)
          {
            if (
                ((j < COL_TMO_AVR_UMAX_VYMK_ROB_K1_BEGIN) ||  (j > COL_TMO_AVR_UMAX_VYMK_ROB_K1_END )) &&
                (j != (COL_TMO_AVR_UMAX_VYMK_ROB_K1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_UMAX_VYMK_ROB_K1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_UMAX_VYMK_ROB_K1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_UMAX_VYMK_ROB_K1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2)
          {
            if (
                ((j < COL_TMO_AVR_UMAX_VYMK_ROB_K2_BEGIN) ||  (j > COL_TMO_AVR_UMAX_VYMK_ROB_K2_END )) &&
                (j != (COL_TMO_AVR_UMAX_VYMK_ROB_K2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_UMAX_VYMK_ROB_K2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_UMAX_VYMK_ROB_K2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_UMAX_VYMK_ROB_K2_COMMA, 0);
          }
        }
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (current_ekran.edition == 0)
  {
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K1) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K1_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_UMAX_VYMK_ROB_K2) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K2_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_UMAX_VYMK_ROB_K2_END;
    }

    //ϳ������� ������ �� ������� �������
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;

    //������ ������� ���, ��� �� ��� ����� ������
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ����������� ���������� ��� ���
/*****************************************************/
void make_ekran_control_avr()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_AVR][MAX_COL_LCD] = 
  {
    {
      "      ���       ",
      "  ��� �� Umax   ",
      "     ��.���     "
    },
    {
      "      ���       ",
      "  ��� �� Umax  ",
      "     ��.���     "
    },
    {
      "      ���       ",
      "  ��� �� Umax   ",
      "     ��.���     "
    },
    {
      "      ���       ",
      "  ��� �� Umax   ",
      "     ��.���     "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_CONTROL_AVR<<1))//�������� �� ��� ��������� MAX_ROW_FOR_CONTROL_AVR ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
        {
          {"     ����.      ", "      ���.      "},
          {"     ����.      ", "     ����.     "},
          {"      Off       ", "       On       "},
          {"     њ��.      ", "     ����.      "}
        };
        const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
        {
          {4, 5},
          {4, 4},
          {5, 6},
          {4, 4}
        };
        
        unsigned int index_ctr = (index_of_ekran>>1);

        unsigned int temp_data;
        if(current_ekran.edition == 0) temp_data = current_settings.control_avr;
        else temp_data = edition_settings.control_avr;
          
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(temp_data >> index_ctr) & 0x1][j];
        current_ekran.position_cursor_x = cursor_x[index_language][(temp_data >> index_ctr) & 0x1];
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
