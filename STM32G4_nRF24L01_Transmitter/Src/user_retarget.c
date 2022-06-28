/*
 * user_retarget.c
 *
 *  Created on: Jan 4, 2022
 *      Author: bot-10
 */

#include "user_retarget.h"


extern uint8_t g_enable_debugging;
extern uint8_t g_enable_debugging_vl53l0x;
extern uint8_t g_enable_debugging_STMC;
extern uint8_t usb_cdc_transmit_buffer_len;
extern uint8_t usb_cdc_transmit_buffer[];    //Used to enable writing to USB serial port


int _write(int file, char *ptr, int len)
{

	if(g_enable_debugging == 0 )
	{
		usb_cdc_transmit_buffer_len = len;
		memcpy(usb_cdc_transmit_buffer,ptr,usb_cdc_transmit_buffer_len);

	   while(!(CDC_Transmit_FS( (uint8_t *) ptr, usb_cdc_transmit_buffer_len)  == USBD_BUSY))
	   {
		   ;
	   }
	   memset(usb_cdc_transmit_buffer,'\0',usb_cdc_transmit_buffer_len);
	   return usb_cdc_transmit_buffer_len;
	}
	else
	{
		return 0;
	}
}

