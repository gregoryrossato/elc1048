#include <stdint.h>
#include <stdio.h>

#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void tarefa_1(void);
void tarefa_2(void);
void tarefa_3(void);
void tarefa_4(void);
void produtor(void);
void consumidor(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4		(TAM_MINIMO_PILHA + 24)
#define TAM_PRODUTOR		(TAM_MINIMO_PILHA + 24)
#define TAM_CONSUMIDOR		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)
#define TAM_BUFFER              10

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_3[TAM_PILHA_3];
uint32_t PILHA_TAREFA_4[TAM_PILHA_4];
uint32_t PILHA_PRODUTOR[TAM_PRODUTOR];
uint32_t PILHA_CONSUMIDOR[TAM_CONSUMIDOR];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

semaforo_t cheio = {0, NULL};
semaforo_t vazio = {TAM_BUFFER, NULL};

uint32_t buffer[TAM_BUFFER];
uint8_t e=0, f=0, read;

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 1);
	
	CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 2);
        
        CriaTarefa(tarefa_3, "Tarefa 3", PILHA_TAREFA_3, TAM_PILHA_3, 3);
        
        CriaTarefa(tarefa_4, "Tarefa 4", PILHA_TAREFA_4, TAM_PILHA_4, 4);
        
        CriaTarefa(produtor, "Produtor", PILHA_PRODUTOR, TAM_PRODUTOR, 5);
        
        CriaTarefa(consumidor, "Consumidor", PILHA_CONSUMIDOR, TAM_CONSUMIDOR, 1);
	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}

//semaforo_t SemaforoTeste = [0,0];

/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */
void tarefa_1(void)
{
	volatile uint16_t a = 0;
	for(;;)
	{
		a++;
		TarefaContinua(2);
	
	}
}

void tarefa_2(void)
{
	volatile uint16_t b = 0;
	for(;;)
	{
		b++;
		TarefaSuspende(2);	
	}
}

void tarefa_3(void)
{
	volatile uint16_t c = 0;
	for(;;)
	{
		c++;
		TarefaSuspende(100);	
	}
}

void tarefa_4(void)
{
        volatile uint16_t d = 0;
        for(;;)
        {
                d++;
                TarefaEspera(100);
        }
}

void produtor(){
  
  while(1){ 

    SemaforoAguarda(&vazio);    
    buffer[e]=500%10;        
    e++;
    if(e == TAM_BUFFER){
      e=0; 
    }                 
    SemaforoLibera(&cheio);
    TarefaEspera(3);
  }
}

void consumidor(){
  
  while(1){
    SemaforoAguarda(&cheio);
    read = buffer[f]; 
    f++;
    if(f == TAM_BUFFER){
      f=0;   
    }           
    SemaforoLibera(&vazio);
  }
} 
    