#ifndef __RETARGET_H
#define __RETARGET_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdio.h>
#include "stat.h"
#include <errno.h>
#include "stm32f4xx_hal.h"

	 void RetargetInit(UART_HandleTypeDef *huart);
	 int _isatty(int fd);
	 int _write(int fd, char * ptr, int len);
	 int _close(int fd);
	 int _read(int fd, char* ptr, int len);
	 int _fstat(int fd, struct stat* st);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_CONF_H */
