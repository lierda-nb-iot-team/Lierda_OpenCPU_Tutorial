/******************************************************************************
 * @内容	LED头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_LED_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_LED_H_
#include "lierdaGPIO.h"
#include "neulfw.h"
#include "app.h"

//定义相关LED灯GPIO
#define LED_10 PIN_25
#define LED_11 PIN_23
#define LED_12 PIN_22
//打开相关LED
#define LED10_ON lierdaGPIOClear(LED_10)
#define LED11_ON lierdaGPIOClear(LED_11)
#define LED12_ON lierdaGPIOClear(LED_12)
//关闭相关LED
#define LED10_OFF lierdaGPIOSet(LED_10)
#define LED11_OFF lierdaGPIOSet(LED_11)
#define LED12_OFF lierdaGPIOSet(LED_12)
//翻转相应的LED
#define LED10_TOGGLE lierdaGPIOToggle(LED_10)
#define LED11_TOGGLE lierdaGPIOToggle(LED_11)
#define LED12_TOGGLE lierdaGPIOToggle(LED_12)



void lierda_LedSta_task(void *param);

//LED初始化
void Lierda_Led_Init(void);
void ReceiveDataled(void);
void SendDataled(void);
uint8 GetLEDState(PIN led_pin);


#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_LED_H_ */
