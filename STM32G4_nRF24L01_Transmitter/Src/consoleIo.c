// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include <string.h>

extern uint8_t usb_cdc_received_buffer[];
extern uint8_t usb_cdc_received_buffer_len;

/*static int getch_noblock() {
    if (_kbhit())
        return _getch();
    else
        return EOF;
}*/

eConsoleError ConsoleIoInit(void)
{
	return CONSOLE_SUCCESS;
}
eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
	uint8_t i = 0;

	if(usb_cdc_received_buffer_len > 0)
	{
		for(i= 0;(( EOF != usb_cdc_received_buffer[i] ) && ( i < bufferLength ));i++ )
		{
			buffer[i] = (uint8_t) usb_cdc_received_buffer[i];
		}
		memset(usb_cdc_received_buffer,'\0',usb_cdc_received_buffer_len);
		usb_cdc_received_buffer_len = 0;
	}

	*readLength = i;
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSend(const uint8_t *buffer, const uint32_t bufferLength, uint32_t *sentLength)
{
	printf("%s",(char*)buffer);
	*sentLength = bufferLength;
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}

