#include "header.h"

/*****************************************************/
//������� ����� ����������� ������� "�������� ���������"
/*****************************************************/
void make_ekran_setpoint_ctrl_phase(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_CTRL_PHASE][MAX_COL_LCD] = 
  {
    {
      "    U(���.)     ",
      "   Phi(���.)    ",
      "    f(���.)     "
    },
    {
      "    U(���.)     ",
      "   Phi(���.)    ",
      "    f(���.)     "
    },
    {
      "   U(phasing)   ",
      "  Phi(phasing)  ",
      "   f(phasing)   "
    },
    {
      "    U(���.)     ",
      "   Phi(���.)    ",
      "    f(���.)     "
    }
  };
  const unsigned char hz[MAX_NAMBER_LANGUAGE][2] = {"��", "��", "Hz", "��"};
  
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_SETPOINT_CTRL_PHASE<<1))//�������� �� ��� ��������� MAX_ROW_FOR_SETPOINT_CTRL_PHASE ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_STPCTRL_PHASE_U)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_ctrl_phase_U[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_ctrl_phase_U[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPCTRL_PHASE_PHI)
        {
          vaga = 100; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_ctrl_phase_phi[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_ctrl_phase_phi[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPCTRL_PHASE_F)
        {
          vaga = 1000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_ctrl_phase_f[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_ctrl_phase_f[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_STPCTRL_PHASE_U)
          {
            if (
                ((j < COL_SETPOINT_CTRL_PHASE_U_BEGIN) ||  (j > COL_SETPOINT_CTRL_PHASE_U_END ))  &&
                (j != (COL_SETPOINT_CTRL_PHASE_U_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_CTRL_PHASE_U_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_CTRL_PHASE_U_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_CTRL_PHASE_U_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPCTRL_PHASE_PHI)
          {
            if (
                ((j < COL_SETPOINT_CTRL_PHASE_PHI_BEGIN) ||  (j > COL_SETPOINT_CTRL_PHASE_PHI_END ))  &&
                (j != (COL_SETPOINT_CTRL_PHASE_PHI_END + 1))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_CTRL_PHASE_PHI_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_CTRL_PHASE_PHI_END + 1)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_DEGREE];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_CTRL_PHASE_PHI_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPCTRL_PHASE_F)
          {
            if (
                ((j < COL_SETPOINT_CTRL_PHASE_F_BEGIN) ||  (j > COL_SETPOINT_CTRL_PHASE_F_END )) &&
                (
                 !((j >= (COL_SETPOINT_CTRL_PHASE_F_END + 2)) && (j <= (COL_SETPOINT_CTRL_PHASE_F_END + 3)))
                )    
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_CTRL_PHASE_F_COMMA )working_ekran[i][j] = ',';
            else if ((j >= (COL_SETPOINT_CTRL_PHASE_F_END + 2)) && (j <= (COL_SETPOINT_CTRL_PHASE_F_END + 3)))
              working_ekran[i][j] = hz[index_language][j - (COL_SETPOINT_CTRL_PHASE_F_END + 2)];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_CTRL_PHASE_F_COMMA, 0);
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
    if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_U)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_U_BEGIN;
      last_position_cursor_x = COL_SETPOINT_CTRL_PHASE_U_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_PHI)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_PHI_BEGIN;
      last_position_cursor_x = COL_SETPOINT_CTRL_PHASE_PHI_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPCTRL_PHASE_F) 
    {
      current_ekran.position_cursor_x = COL_SETPOINT_CTRL_PHASE_F_BEGIN;
      last_position_cursor_x = COL_SETPOINT_CTRL_PHASE_F_END;
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
//������� ����� ����������� �������� ���
/*****************************************************/
void make_ekran_timeout_ctrl_phase(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_CTRL_PHASE][MAX_COL_LCD] = 
  {
    {
      "    U(���.)     ",
      "  U(���.) ��.   ",
      "   Phi(���.)    ",
      " Phi(���.) ��.  ",
      "    f(���.)     ",
      "  f(���.) ��.   "
    },
    {
      "    U(���.)     ",
      "  U(���.) ���.  ",
      "   Phi(���.)    ",
      " Phi(���.) ���. ",
      "    f(���.)     ",
      "  f(���.) ���.  "
    },
    {
      "    U(���.)     ",
      "  U(���.) ��.   ",
      "   Phi(���.)    ",
      " Phi(���.) ��.  ",
      "    f(���.)     ",
      "  f(���.) ��.   "
    },
    {
      "    U(���.)     ",
      "  U(���.) ��.   ",
      "   Phi(���.)    ",
      " Phi(���.) ��.  ",
      "    f(���.)     ",
      "  f(���.) ��.   "
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
    if (index_of_ekran < (MAX_ROW_FOR_TIMEOUT_CTRL_PHASE<<1))//�������� �� ��� ��������� MAX_ROW_FOR_TIMEOUT_CTRL_PHASE ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_U)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_ctrl_phase_U[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_ctrl_phase_U[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_U_D)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_ctrl_phase_U_d[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_ctrl_phase_U_d[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_PHI)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_ctrl_phase_phi[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_ctrl_phase_phi[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_PHI_D)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_ctrl_phase_phi_d[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_ctrl_phase_phi_d[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_F)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_ctrl_phase_f[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_ctrl_phase_f[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_F_D)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_ctrl_phase_f_d[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_ctrl_phase_f_d[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_U)
          {
            if (
                ((j < COL_TMO_CTRL_PHASE_U_BEGIN) ||  (j > COL_TMO_CTRL_PHASE_U_END )) &&
                (j != (COL_TMO_CTRL_PHASE_U_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_CTRL_PHASE_U_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_CTRL_PHASE_U_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_CTRL_PHASE_U_COMMA, 0);
          }
          if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_U_D)
          {
            if (
                ((j < COL_TMO_CTRL_PHASE_U_D_BEGIN) ||  (j > COL_TMO_CTRL_PHASE_U_D_END )) &&
                (j != (COL_TMO_CTRL_PHASE_U_D_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_CTRL_PHASE_U_D_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_CTRL_PHASE_U_D_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_CTRL_PHASE_U_D_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_PHI)
          {
            if (
                ((j < COL_TMO_CTRL_PHASE_PHI_BEGIN) ||  (j > COL_TMO_CTRL_PHASE_PHI_END )) &&
                (j != (COL_TMO_CTRL_PHASE_PHI_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_CTRL_PHASE_PHI_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_CTRL_PHASE_PHI_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_CTRL_PHASE_PHI_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_PHI_D)
          {
            if (
                ((j < COL_TMO_CTRL_PHASE_PHI_D_BEGIN) ||  (j > COL_TMO_CTRL_PHASE_PHI_D_END )) &&
                (j != (COL_TMO_CTRL_PHASE_PHI_D_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_CTRL_PHASE_PHI_D_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_CTRL_PHASE_PHI_D_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_CTRL_PHASE_PHI_D_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_F)
          {
            if (
                ((j < COL_TMO_CTRL_PHASE_F_BEGIN) ||  (j > COL_TMO_CTRL_PHASE_F_END )) &&
                (j != (COL_TMO_CTRL_PHASE_F_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_CTRL_PHASE_F_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_CTRL_PHASE_F_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_CTRL_PHASE_F_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOCTRL_PHASE_F_D)
          {
            if (
                ((j < COL_TMO_CTRL_PHASE_F_D_BEGIN) ||  (j > COL_TMO_CTRL_PHASE_F_D_END )) &&
                (j != (COL_TMO_CTRL_PHASE_F_D_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_CTRL_PHASE_F_D_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_CTRL_PHASE_F_D_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_CTRL_PHASE_F_D_COMMA, 0);
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
    if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U) 
    {
      current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_BEGIN;
      last_position_cursor_x = COL_TMO_CTRL_PHASE_U_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_U_D) 
    {
      current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_U_D_BEGIN;
      last_position_cursor_x = COL_TMO_CTRL_PHASE_U_D_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI) 
    {
      current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_BEGIN;
      last_position_cursor_x = COL_TMO_CTRL_PHASE_PHI_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_PHI_D) 
    {
      current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_PHI_D_BEGIN;
      last_position_cursor_x = COL_TMO_CTRL_PHASE_PHI_D_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F) 
    {
      current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_BEGIN;
      last_position_cursor_x = COL_TMO_CTRL_PHASE_F_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOCTRL_PHASE_F_D) 
    {
      current_ekran.position_cursor_x = COL_TMO_CTRL_PHASE_F_D_BEGIN;
      last_position_cursor_x = COL_TMO_CTRL_PHASE_F_D_END;
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
void make_ekran_control_ctrl_phase()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_CTRL_PHASE][MAX_COL_LCD] = 
  {
    {
      "    U(���.)     ",
      "   Phi(���.)    ",
      "    f(���.)     ",
      "     �����1     ",
      "     �����2     "
    },
    {
      "    U(���.)     ",
      "   Phi(���.)    ",
      "    f(���.)     ",
      "     �����1     ",
      "     �����2     "
    },
    {
      "   U(phasing)   ",
      "  Phi(phasing)  ",
      "   f(phasing)   ",
      "     �����1     ",
      "     �����2     "
    },
    {
      "    U(���.)     ",
      "   Phi(���.)    ",
      "    f(���.)     ",
      "     �����1     ",
      "     �����2     "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_CONTROL_CTRL_PHASE<<1))//�������� �� ��� ��������� MAX_ROW_FOR_CONTROL_CTRL_PHASE ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
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
        if(current_ekran.edition == 0) temp_data = current_settings.control_ctrl_phase;
        else temp_data = edition_settings.control_ctrl_phase;
          
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
