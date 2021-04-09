# stm32.readme

# Objetivo
 Como fazer um projeto utilizando o compilador Keil mdk com  simulação no  Proteus Labcenter.
 

# Softwares necessários
* Proteus  https://www.labcenter.com/
* Keil uVision (MDK-ARM) [link](https://www.keil.com/download/product/)

# Introdução 
Nesse projeto iremos gerar um código no compilador Keil mdk para o acionamento de um motor de passo.

# Inicilizando o Keil

- **1º Passo:** Após baixar o Keil Uvision no computador, será necessário criar  um novo projeto (New Project) localizado na parte superior do compilador, clique em **Project -> New Uvison Project** e crie um novo projeto e salve onde preferir no computador.

<a href="https://imgur.com/lhk6OW6"><img src="https://imgur.com/lhk6OW6.jpg" title="source: imgur.com" /></a>

- **2º Passo:** Após a criação de um novo projeto, vamos escolher o chip a ser utilizado no projeto, nesse caso foi escolhido o  STM32 F103R6, na caixa de pesquisa (Search) poderá escrever esse código (F103R6) que o software já vai localizar automaticamente, ou se preferir pode seguir o seguinte caminho **STMicroeletronics -> STM32F1 Series -> STM32F103 -> STM32F103R6** selecione o chip e clique "Ok"

<a href="https://imgur.com/AMruIOs"><img src="https://imgur.com/AMruIOs.jpg" title="source: imgur.com" /></a>

**Observação:** Caso não aparece nenhum chip para escolha logo após a criação do projeto, será necessário instalar o seu pacote no "Pack Instaler" no Keil Uvision. 
Feche a janela que abriu para escolha de chip e clique no icone onde a seta está apontando na imagem abaixo:

<a href="https://imgur.com/kcs5Z91"><img src="https://imgur.com/kcs5Z91.jpg" title="source: imgur.com" /></a>

Logo após vai abrir uma outra janela, que possivelmente demore alguns segundo para que carregue todos os seus arquivos, será necessário aguardar um pouco. Carregando vai aparecer algo parecido com a imagem abaixo:

<a href="https://imgur.com/myP7YUe"><img src="https://imgur.com/myP7YUe.jpg" title="source: imgur.com" /></a>

Na aba **Device** siga o caminho **STMicroeletronics -> STM32F1 Series -> STM32F103 -> STM32F103R6** após seguir esse caminho, na parte de **pack** vai aparecer (Device Specific) e logo de frente na aba **Action** vai está escrito **Install** clique em install.

<a href="https://imgur.com/esAnGLU"><img src="https://imgur.com/esAnGLU.jpg" title="source: imgur.com" /></a>

Após a instalação, a janela vai ficar dessa forma:

<a href="https://imgur.com/fYy9n1g"><img src="https://imgur.com/fYy9n1g.jpg" title="source: imgur.com" /></a>

Feita a instalação do pacote do chip, volte ao **1º Passo** e reinicie o projeto, agora já com o chip instalado. 

- **3º Passo:** Após fazer o 2º passo e escolher o chip, o software vai abrir outra janela chamada **Manage Run-Time Environment** onde escolherá os seus Componentes de Softwares (Softwares Components) nesse projeto será necessárioo uso de 5 componentes, siga e selecione os componetes de acordo as imagens abaixo:

- Primeira Janela: 

<a href="https://imgur.com/a48E6vg"><img src="https://imgur.com/a48E6vg.jpg" title="source: imgur.com" /></a>

- Segunda Janela: Selecione **CMSIS -> CORE**

<a href="https://imgur.com/pWpFviR"><img src="https://imgur.com/pWpFviR.jpg" title="source: imgur.com" /></a>

- Terceira Janela: Selecione **Device -> Startup**

<a href="https://imgur.com/TbFLGQX"><img src="https://imgur.com/TbFLGQX.jpg" title="source: imgur.com" /></a>

- Quarta Janela: Ainda com **Device** selecionado clique em **StdPeriph Drivers** e depois escolha **Framework, GPIO & RCC**:

<a href="https://imgur.com/ZFAdTQI"><img src="https://imgur.com/ZFAdTQI.jpg" title="source: imgur.com" /></a>

Logo Após de escolher os componetes de softwares, clique em Ok.

**4º Passo:** Após o clicar Ok em componetes de softwares, a janela vai fechar e o software voltar para a tela principal do Keil Uvision.

<a href="https://imgur.com/ra1EGpw"><img src="https://imgur.com/ra1EGpw.jpg" title="source: imgur.com" /></a>

Na janela **Projetc** clique no (+) ao lado do icone **Target 1** vai abrir outras ramificações iguais a imagem a abaixo:

<a href="https://imgur.com/PKhx7lu"><img src="https://imgur.com/PKhx7lu.jpg" title="source: imgur.com" /></a>

Clique com o botão direito do mouse em cima do icone **Source Group** e selecione **"" Add New Item to Group 'Souce Group 1'...""** de acordo com a imagem abaixo:

<a href="https://imgur.com/VM4R9OR"><img src="https://imgur.com/VM4R9OR.jpg" title="source: imgur.com" /></a>

Clicando em **"" Add New Item to Group 'Souce Group 1'...""** vai abrir uma outra janela onde você vai selecionar **C File (.c)** e na barra nomeada por **Name:** escreva **main** e clique em **Add**:

<a href="https://imgur.com/90ZpJG4"><img src="https://imgur.com/90ZpJG4.jpg" title="source: imgur.com" /></a>

A janela irá fechar e a parte principal do Keil Uvision onde era cinza vai ficar branca e esperando que incie o código:

<a href="https://imgur.com/RgTVDvG"><img src="https://imgur.com/RgTVDvG.jpg" title="source: imgur.com" /></a>

## Iniciando o Código:

- Para começar o código, inclua 3 blibliotecas:

```javascript
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
```
 - Conforme a imagem abaixo:

 <a href="https://imgur.com/AD7yJg3"><img src="https://imgur.com/AD7yJg3.jpg" title="source: imgur.com" /></a>
 
 - Colocando as  funções que vão ser usadas no decorrer do código, são elas:

```javascript
void PORTB_GPIO_Configuration(void);  
void Delay(__IO uint32_t nCount);			
void NMI_Handler(void);
void SetClk(uint32_t PLLMul);
```
- Conforme a imagem abaixo:

<a href="https://imgur.com/AD7yJg3"><img src="https://imgur.com/AD7yJg3.jpg" title="source: imgur.com" /></a>

- Escreva a variavel do tipo Clock para o cristal interno e também uma variavel tipo **int** para a função de **delay** inciando ela a 500ms:

```javascript
RCC_ClocksTypeDef ClksFreq;
int delay_time = 500;
```
- Conforme a imagem abaixo:

<a href="https://imgur.com/lTHFDup"><img src="https://imgur.com/lTHFDup.jpg" title="source: imgur.com" /></a>

- Escreva o programa principal **(int main)** e logo após inicie o **clock** e também o PORT do chip em que utilizará o pino de saida dele, nesse código foi configurado o PORT B, seguindo as instruções abaixo:

```javascript
int main()
{
	//==================System Clock Init==================
	//Inicia o clock
	SetClk(2);
  //======================GPIO Init======================
	PORTB_GPIO_Configuration();
```


- Nesse código iremos utilizar um botão que habilta o acionamento do motor.

 ```javascript
 
 if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_4) == 0) {  //button  M1
 
 ```
 - Configuração de acionamento do Motor no modo  Wave drive
 
  ```javascript
 while(1)
	{

		
	 	if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_4) == 0) {  //button  M1
	
		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);       // IN1 -1
		GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);   //  IN2 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_RESET);  //  IN3 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_3, Bit_RESET); //  IN4 -0
		Delay(10);

		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);    // IN1 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);     //  IN2 -1
		GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_RESET);  //  IN3 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_3, Bit_RESET); //  IN4 -0
		Delay(10);	
	
		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);    // IN1 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);   //  IN2 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_SET);    //  IN3 -1
		GPIO_WriteBit(GPIOB, GPIO_Pin_3, Bit_RESET); //  IN4 -0
		Delay(10);;	
	
		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);     // IN1 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);    //  IN2 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_RESET);   //  IN3 -0
		GPIO_WriteBit(GPIOB, GPIO_Pin_3, Bit_SET);    //  IN4 -1
		Delay(10);	

		}

	}
  ```
  
  - Habilite o PORTB GPIO_PIN_0 -> GPIO_PIN_3 como saída e GPIO_PIN_4 como entrada :
  ```javascript
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
```
- Para efeitos de simulçao desse código no proteus utilizaremos o cristal  interno do chip 

```javascript
void NMI_Handler()
{
	//Clear CSS interrupt flag - RCC (REGISTER CLOCK CONTROL) 
	RCC->CIR |= RCC_CIR_CSSC; // |= INVERSÃO 
	//Wait couple of time, if it recovers
	//feasible to restart again
	Delay(100);
	//Try to start HSE (HIGH SPEED EXTERNAL)- TENTA LIGAR DE NOVO O CLOCK EXTERNO 
	RCC_HSEConfig(RCC_HSE_ON);
	//Delay to start crystal
	Delay(1);
	if (RCC_WaitForHSEStartUp() == SUCCESS)
	{
		//If starts - set HSE as system clock source
		RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
		//Stop HSI
    //DESLIGA O HIGH SPEED INTERNAL - CLOCK INTERNO
		RCC_HSICmd(DISABLE);
	}
}
```
- Configuração do  Clock:

```javascript
//CONFIGURAÇÃO DO CLOCK 

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
```


- Criando uma função Delay :

```javascript
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
```
## Gerando o Arquivo .HEX 

  Para que esse cógido seja simulado no Software Proteus, é necessário gerar o arquivo **.hex**

- Clique no icone em qual tem uma varinha de condão que é nomeado por **Options for Target**:

<a href="https://imgur.com/WCAMeV4"><img src="https://imgur.com/WCAMeV4.jpg" title="source: imgur.com" /></a>

- Na janela que irá abrir selecione **Output -> "Create HEX file"** e aperte Ok:

<a href="https://imgur.com/WvRdCEm"><img src="https://imgur.com/WvRdCEm.jpg" title="source: imgur.com" /></a>

- Pronto, agora o Keil irá criar um arquivo .hex na hora de compilar o seu código.

## Inicializando o Proteus :
- Com o Protteus já instalado vamos criar um novo projeto.
<a href="https://imgur.com/qzlWRKT"><img src="https://imgur.com/qzlWRKT.jpg" title="source: imgur.com" /></a>

## Fazendo o Esquemático:

 O objetivo desse circuito é fazer o chaveameto des quadro MosfetS através da programação feita no Keil,cada Mosfet é responsável por acionar uma fase do motor

 <a href="https://imgur.com/2KotTtf"><img src="https://i.imgur.com/2KotTtf.png" title="source: imgur.com" /></a>
 
 - Para esse projeto iremos utilizar o Mosfet IRLZ34N
 
 <a href="https://imgur.com/Jpw2xrm"><img src="https://i.imgur.com/Jpw2xrm.png" title="source: imgur.com" /></a>
 
-  O uso botão é para habilitar o acionamento do motor
 
 <a href="https://imgur.com/VvOFfmn"><img src="https://i.imgur.com/VvOFfmn.png" title="source: imgur.com" /></a>
 
 - Vamos usar um Step Motor 

 <a href="https://imgur.com/Mbx2QSI"><img src="https://i.imgur.com/Mbx2QSI.png" title="source: imgur.com" /></a>
 
 -  Modo de ligação do Motor 

 <a href="https://imgur.com/baZpvuV"><img src="https://i.imgur.com/baZpvuV.png" title="source: imgur.com" /></a>
   
   As letras A,B,C e D são as quatro fases do motor que serão acionadas pelos Mosfets 
   
 - Configuração do Motor 

  clicando duas vezes sobre o componentes podemos editar alguns parâmetros do  motor 
  
  <a href="https://imgur.com/mpvDgk5"><img src="https://i.imgur.com/mpvDgk5.png" title="source: imgur.com" /></a>
  
  - Para essa simulação usaremos o microcontrolador STM32F103R6
    
    <a href="https://imgur.com/PTj7gxt"><img src="https://i.imgur.com/PTj7gxt.png" title="source: imgur.com" /></a>
   
  - Ligação do STM32
    
    <a href="https://imgur.com/my2ZZyq"><img src="https://i.imgur.com/my2ZZyq.png" title="source: imgur.com" /></a>
    
    De acordo com a programação feita no KEIl , escolhemos o PORTB, sendo que PB0,PB1,PB2 e PB3 são **inputs** e PB4 é **output**
    IN1,IN2,IN3 e IN4 são os sinais que acionam os Mosfets
    
   ## Circuito Completo 
   <a href="https://imgur.com/R9v6R95"><img src="https://i.imgur.com/R9v6R95.png" title="source: imgur.com" /></a>
   
   - Uma outra configuração necessária, é da alimentação do chip em que está sedo utilizado, para fazer essa configuração vá até **Design** na parte superior do proteus e depois clique em **Configura Power Rails...*

<a href="https://imgur.com/HkvJorl"><img src="https://imgur.com/HkvJorl.jpg" title="source: imgur.com" /></a>

- Na janela que abrir na parte de **Unconnected power nets:** vão ter duas alimentações **VDDA & VSSA** selecione os dois e depois clique em **Add** ec lique Ok:

<a href="https://imgur.com/6hVaMjR"><img src="https://i.imgur.com/6hVaMjR.png" title="source: imgur.com" /></a>


- Agora é hora de configurar a frequência do cristal interno do chip:

Clique com o botão direito em cima do chip e depois escolha **Edit Properties**

<a href="https://imgur.com/Iy63ZHs"><img src="https://imgur.com/Iy63ZHs.jpg" title="source: imgur.com" /></a>

Vai abrir uma janela chamada **Edit Component** na parte nomeada como **Crystal Frequency:** escreva **16MHz**:

<a href="https://imgur.com/uEPyrQU"><img src="https://imgur.com/uEPyrQU.jpg" title="source: imgur.com" /></a>

Após selecionar a frequência do chip, devemos incluir o arquivo .Hex, esse arquivo está localizado na pasta onde foi salvo o projeto feito no keil 

<a href="https://imgur.com/NBnSkgA"><img src="https://i.imgur.com/NBnSkgA.png" title="source: imgur.com" /></a>


# Simulando:

Após fazer toda configuração descrita anteriormente, agora basta executar sua simalação no Proteus 

<a href="https://imgur.com/3PipbvW"><img src="https://i.imgur.com/3PipbvW.gif" title="source: imgur.com" /></a>
