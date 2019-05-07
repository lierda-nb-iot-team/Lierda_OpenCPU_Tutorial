  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);      //时钟配置

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

 

 

/* TIM3 channel 2 pin (PA.01) configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                               //GPIO配置
  PIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

 

 

 

 /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                     //NVIC配置 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

 

 

/*TIM配置*/ 

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;                   //通道选择
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       //上升沿触发
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;    //管脚与寄存器对应关系
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;           //输入预分频。意思是控制在多少个输入周期做一次捕获，如果

//输入的信号频率没有变，测得的周期也不会变。比如选择4分频，则每四个输入周期才做一次捕获，这样在输入信号变化不频繁的情况下，

//可以减少软件被不断中断的次数。
  TIM_ICInitStructure.TIM_ICFilter = 0x0;                            //滤波设置，经历几个周期跳变认定波形稳定0x0～0xF

  TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);                 //根据参数配置TIM外设信息

  /* Select the TIM3 Input Trigger: TI2FP2 */
  TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);                //选择IC2为始终触发源

  /* Select the slave Mode: Reset Mode */
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);//TIM从模式：触发信号的上升沿重新初始化计数器和触发寄存器的更新事件

  /* Enable the Master/Slave Mode */
  TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable); //启动定时器的被动触发

  /* TIM enable counter */
  TIM_Cmd(TIM3, ENABLE);                                 //启动TIM2

  /* Enable the CC2 Interrupt Request */         
  TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);     //打开中断 

 

中断处理函数

 

void TIM3_IRQHandler(void)
{
  /* Clear TIM3 Capture compare interrupt pending bit */
  TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);                //清楚TIM的中断待处理位

  /* Get the Input Capture value */
  IC2Value = TIM_GetCapture2(TIM3);                         //读取IC2捕获寄存器的值，即为PWM周期的计数值

  if (IC2Value != 0)
  {
    /* Duty cycle computation */
    DutyCycle = (TIM_GetCapture1(TIM3) * 100) / IC2Value;         //读取IC1捕获寄存器的值，并计算占空比

    /* Frequency computation */
    Frequency = 72000000 / IC2Value;                                          //计算PWM频率。
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
  }
}