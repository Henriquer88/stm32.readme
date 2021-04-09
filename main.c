#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stdbool.h"

// Protótipo de função 
void PORTB_GPIO_Configuration(void);  
void Delay(__IO uint32_t nCount);			
void NMI_Handler(void);
void SetClk(uint32_t PLLMul);

// Variavel do tipo clock para o cristal
RCC_ClocksTypeDef ClksFreq;

int delay_time = 500;


int main()
{
	//==================System Clock Init==================
	//Inicia o clock
	SetClk(2); 
	//======================GPIO Init======================
	PORTB_GPIO_Configuration();
	while(1)
	{
//Delay(delay_time);
	 	if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_4) == 0) {  //button  M1
	
		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);     // IN1 -1
		GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);  //  IN2 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_RESET); //  IN3 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_3, Bit_RESET); //  IN4 -0
		Delay(10);

		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);     // IN1 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);      //  IN2 -1
		GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_RESET);   //  IN3 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_3, Bit_RESET); //  IN4 -0
		Delay(10);	
	
		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);     // IN1 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);    //  IN2 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_SET);     //  IN3 -1
		GPIO_WriteBit(GPIOB, GPIO_Pin_3, Bit_RESET); //  IN4 -0
		Delay(10);;	
	
		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);     // IN1 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);    //  IN2 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_RESET);   //  IN3 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_3, Bit_SET);    //  IN4 -1
		Delay(10);	

		}

	}
}
//Initialise GPIOA port
void PORTB_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//Allow clock to GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//Configure output pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//Configure Input Pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}
void NMI_Handler()
{
	//Clear CSS interrupt flag
	RCC->CIR |= RCC_CIR_CSSC;
	//Wait couple of time, if it recovers
	//feasible to restart again
	Delay(100);
	//Try to start HSE
	RCC_HSEConfig(RCC_HSE_ON);
	//Delay to start crystal
	Delay(1);
	if (RCC_WaitForHSEStartUp() == SUCCESS)
	{
		//If starts - set HSE as system clock source
		RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
		//Stop HSI
		RCC_HSICmd(DISABLE);
		//Change blink delay time for green LED
		delay_time = 20;
	}
	else GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	//If crystal does not started - stay on HSI
	//Light up LED on GPIO_Pin_8
}


void SetClk(uint32_t PLLMul) {
      RCC_DeInit();
	  //Run HSE
	  RCC_HSEConfig(RCC_HSE_ON);
	  //Wait until HSE starts up
	  while(RCC_WaitForHSEStartUp() != SUCCESS);
	  //Turn on Clock Security System
	  RCC->CR |= RCC_CR_CSSON;
	  //Make HSE as system main clock source
	  //RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	  //Power off HSI to reduce energy
	  RCC_HSICmd(DISABLE);

      // PLL provides frequency multiplier of (HSI/2) i.e. 4MHz x ...
      RCC_PLLConfig(RCC_PLLSource_HSE_Div2, PLLMul);
      // Enable PLL
      RCC_PLLCmd(ENABLE);
      // Wait till PLL is ready
      while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
      // Select PLL as system clock source
      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
      // Wait till PLL is used as system clock source
      while (RCC_GetSYSCLKSource() != 0x08);
      // AHB, AP2 and AP1 clock are necessary for the peripherals to function
      // HCLK for AHB = SYSCLK (max is SYSCLK, up to 72MHz)
      RCC_HCLKConfig(RCC_SYSCLK_Div1);
      // PCLK2 for APB2 = HCLK (max is SYSCLK, up to 72MHz)
      RCC_PCLK2Config(RCC_HCLK_Div1);
      // PCLK1 for APB1 = HCLK (HCLK <= 36MHz)
      RCC_PCLK1Config(RCC_HCLK_Div1);

      RCC_GetClocksFreq(&ClksFreq); // update SYSCLK, HCLK, PCLK1 and PCLK2 in ClksFreq
}


//Dumbest delay function
void Delay(__IO uint32_t nCount)
{
	uint32_t i = 0;
	for (; nCount != 0; i++)
	{
		if (i == 1000)
		{
			i = 0;
			nCount--;
		}
	}
}

