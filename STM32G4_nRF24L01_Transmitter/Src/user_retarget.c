/*
 * user_retarget.c
 *
 *  Created on: Jan 4, 2022
 *      Author: bot-10
 */

#include "user_retarget.h"
#include "usbd_cdc_if.h"

extern uint8_t g_enable_debugging;
extern uint8_t usb_cdc_transmit_buffer[];
extern uint8_t usb_cdc_transmit_buffer_len;

int _write(int file, char *ptr, int len)
{

	if(g_enable_debugging == 1)
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

