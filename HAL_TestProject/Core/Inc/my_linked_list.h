#ifndef INC_MY_LINKED_LIST_H_
#define INC_MY_LINKED_LIST_H_

#include <stdlib.h>
#include <string.h>
#include "main.h"


typedef enum
{
	STATE_ON  = 1,
	STATE_OFF = 0,

}StateType_t;

typedef enum
{

	ASCII_Char_Enter = 13,
	ASCII_Char_Space = 32,
	ASCII_Char_0 = 48,
	ASCII_Char_1 = 49,
	ASCII_Char_2 = 50,
	ASCII_Char_3 = 51,
	ASCII_Char_4 = 52,
	ASCII_Char_5 = 53,
	ASCII_Char_6 = 54,
	ASCII_Char_7 = 55,
	ASCII_Char_8 = 56,
	ASCII_Char_9 = 57,

}ASCII_ChartoDecimalNumbers;

typedef struct _node {
	uint8_t data;
	uint8_t index;
	struct _node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
} LinkedList;


void InitializeList(LinkedList *list);
void AddHead(LinkedList *list, uint8_t data);
void AddTail(LinkedList *list, uint8_t data);
Node *GetNode(LinkedList *list, uint8_t index);
HAL_StatusTypeDef CheckNode(LinkedList *list, Node *node);
void Delete(LinkedList *list, Node *node);
StateType_t IsEmpty(LinkedList *list);
void DisplayLinkedList(LinkedList *list, UART_HandleTypeDef *huart);
void WriteIndex(LinkedList *list, UART_HandleTypeDef *huart, Node *node);
void WriteData(LinkedList *list, UART_HandleTypeDef *huart, Node *node);
uint8_t GetDecimal(UART_HandleTypeDef *huart, uint8_t var[], uint8_t size);

#endif /* INC_MY_LINKED_LIST_H_ */
