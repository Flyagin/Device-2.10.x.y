#include "header.h"

/*****************************************************/
//������� ����� ������������
/*****************************************************/
void make_ekran_configuration(unsigned int configuration_edit_temp)
{
#define MAX_COL_LCD_PART1 10

  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EKRAN_CONFIGURATION][MAX_COL_LCD_PART1] = 
  {
    {
     "���       ",
     "���       ",
     "���       ",
     "����      ",
     "���(���)  ",
     "�����     ",
     "������    ",
     " ���      ",
     "����.���. "
    },
    {
     "���       ",
     "���       ",
     "���       ",
     "����      ",
     "���(���)  ",
     "����     ",
     "������    ",
     " ���      ",
     "����.���. "
    },
    {
     "OCP       ",
     "���       ",
     "AR        ",
     "CBFP      ",
     "NPSP      ",
     "Umin      ",
     "Umax      ",
     " ���      ",
     "Ext.logic "
    },
    {
     "��K       ",
     "���       ",
     "�KK       ",
     "Ѳ��K     ",
     "�KK       ",
     "�����     ",
     "������    ",
     " ���      ",
     "����.���. "
    }
  };
  const unsigned char information_on[MAX_NAMBER_LANGUAGE][MAX_COL_LCD - MAX_COL_LCD_PART1] = 
  {
    "���.  ",
    "����.",
    "On    ",
    "����. "
  };
  const unsigned char information_off[MAX_NAMBER_LANGUAGE][MAX_COL_LCD - MAX_COL_LCD_PART1] = 
  {
    "����. ",
    "����. ",
    "Off   ",
    "њ��. "
  };
  
  unsigned char name_string_tmp[MAX_ROW_FOR_EKRAN_CONFIGURATION][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(int index_1 = 0; index_1 < MAX_ROW_FOR_EKRAN_CONFIGURATION; index_1++)
  {
    for(int index_2 = 0; index_2 < MAX_COL_LCD_PART1; index_2++)
      name_string_tmp[index_1][index_2] = name_string[index_language][index_1][index_2];
  }
  
  /*******************************************************/
  //������� ��������
  /*******************************************************/
  for(unsigned int i = 0; i< MAX_ROW_FOR_EKRAN_CONFIGURATION; i++)
  {
    unsigned int configuration_temp;
    
    //���� �� �� � ����� �����������, �� ������ ��� �� �������� ������� ���������
    //������ ����� �� ��������� ��� �����������
    if(current_ekran.edition == 0) configuration_temp = current_settings.configuration;
    else configuration_temp = configuration_edit_temp;
    
    if ((configuration_temp & (1<<i)) == 0)
    {
      for (unsigned int j = MAX_COL_LCD_PART1; j < MAX_COL_LCD; j++)
        name_string_tmp[i][j] = information_off[index_language][j - MAX_COL_LCD_PART1];
    }
    else
    {
      for (unsigned int j = MAX_COL_LCD_PART1; j < MAX_COL_LCD; j++)
        name_string_tmp[i][j] = information_on[index_language][j - MAX_COL_LCD_PART1];
    }
  }
  /*******************************************************/
    
  int position_temp = current_ekran.index_position;
  int index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
    if (index_of_ekran < MAX_ROW_FOR_EKRAN_CONFIGURATION)
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran][j];
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = (MAX_COL_LCD_PART1 - 1);
  //³���������� ������ �� ��������
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if (current_ekran.edition == 0)   current_ekran.cursor_blinking_on = 0;
  else   current_ekran.cursor_blinking_on = 1;

  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
  
#undef MAX_COL_LCD_PART1  
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
