#ifndef __INFRARED_INIT_H
#define __INFRARED_INIT_H 
#include "sys.h"
#define L_front PFin(5)// PF5     ��ǰ��
#define L_rear PFin(6)// PF6      ���
#define L_above_C PFin(4)// PF4   ���Ͻ�
#define L_below_C PFin(1)// PF1	  ���½�
#define R_above_C PFin(3)// PF3   ���Ͻ�
#define R_below_C PFin(2)// PF2	  ���½�
#define R_front PFin(7)// PF7     ��ǰ��
#define L_above PFin(11)// PF11	  ���Ϸ�
#define R_above PFin(12)// PF12   ���Ϸ�
void infrared_INIT(void);//��ʼ��		 				    
#endif


