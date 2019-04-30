/******************************************************************************
 * @内容	LED头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_LED_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_LED_H_
#include "lierdaGPIO.h"
#include "neulfw.h"

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
//定义使用LEDX BIT
#define LED10 0X01<<1
#define LED11 0X01<<2
#define LED12 0X01<<3


typedef enum
{
  LED_OFF = 0,
  LED_ON  = 1,
  LED_TOGGLE = 2,
}LEDState_TypeDef;


//LED初始化
void Lierda_Led_Init(void);
//设置板载LED灯的状态
void LEDx_StateSet(uint8 LEDx,LEDState_TypeDef state);




#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_LED_H_ */
