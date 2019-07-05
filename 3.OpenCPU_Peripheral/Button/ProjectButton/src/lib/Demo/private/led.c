/******************************************************************************
 * @内容	LED相关函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "led.h"


/******************************************************************************
* @函数名	LED初始化
* @参数	        无
* @返回值       无
******************************************************************************/
void Lierda_Led_Init(void)
{
	lierdaGPIOInit();
	lierdaGPIOClaim(LED_10,GPIO_DIRECTION_OUTPUT);  //LED_10 GPIO声明
	lierdaGPIOClaim(LED_11,GPIO_DIRECTION_OUTPUT);  //LED_11 GPIO声明
	lierdaGPIOClaim(LED_12,GPIO_DIRECTION_OUTPUT);  //LED_12 GPIO声明
}
/**
  * 函数功能: 设置板载LED灯的状态
  * 输入参数: LEDx:其中x可甚至为(1,2,3)用来选择对应的LED灯
  * 输入参数：state:设置LED灯的输出状态。
  *             可选值：LED_OFF：LED灯灭；
  *                     LED_ON： LED灯亮。
  *                     LED_TOGGLE：反转LED
  * 返 回 值: 无
  * 说    明：该函数使用类似标准库函数的编程方法，方便理解标准库函数编程思想。
  */
/******************************************************************************
* @函数名	设置板载LED灯的状态
* @参数	    LEDx:其中x可甚至为(10,11,12)用来选择对应的LED灯
* @参数		state:设置LED灯的输出状态。 可选值：LED_OFF：LED灯灭； LED_ON： LED灯亮。LED_TOGGLE：反转LED
* @返回值       无
******************************************************************************/
void LEDx_StateSet(uint8 LEDx,LEDState_TypeDef state)
{

  /* 判断设置的LED灯状态，如果设置为LED灯灭 */
  if(state==LED_OFF)
  {
    if(LEDx & LED10)
    	LED10_OFF;/* LED10灭 */

    if(LEDx & LED11)
    	LED11_OFF;/* LED11灭 */

    if(LEDx & LED12)
    	LED12_OFF;/* LED12灭 */
  }
  else if(state==LED_ON) /* 设置LED灯为亮 */
  {
    if(LEDx & LED10)
    	LED10_ON;/* LED10亮 */

    if(LEDx & LED11)
    	LED11_ON;/* LED11亮 */

    if(LEDx & LED12)
    	LED12_ON;/* LED12亮 */
  }
  else
  {
    if(LEDx & LED10)
      LED10_TOGGLE;/* 设置引脚输出反转 */

    if(LEDx & LED11)
      LED11_TOGGLE;/* 设置引脚输出反转 */

    if(LEDx & LED12)
      LED12_TOGGLE;/* 设置引脚输出反转 */
  }
}
