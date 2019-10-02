#ifndef __INFRARED_INIT_H
#define __INFRARED_INIT_H 
#include "sys.h"
#define L_front PFin(5)// PF5     左前方
#define L_rear PFin(6)// PF6      左后方
#define L_above_C PFin(4)// PF4   左上角
#define L_below_C PFin(1)// PF1	  左下角
#define R_above_C PFin(3)// PF3   右上角
#define R_below_C PFin(2)// PF2	  右下角
#define R_front PFin(7)// PF7     右前方
#define L_above PFin(11)// PF11	  左上方
#define R_above PFin(12)// PF12   右上方
void infrared_INIT(void);//初始化		 				    
#endif


