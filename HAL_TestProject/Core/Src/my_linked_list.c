#include "my_linked_list.h"

void InitializeList(LinkedList *list)
{
	list->head->data = 0;
	list->head->next = NULL;

	list->tail->data = 0;
	list->tail->next = NULL;
}

uint8_t GetDecimal(UART_HandleTypeDef *huart, uint8_t var[], uint8_t size)
{
	uint8_t dec = 0;
	uint16_t controlValue = 0;
	uint8_t multiplier = 1;
	uint8_t digitValue = 0;
	uint8_t currentDigit = size;

	    // Start from the least significant digit (rightmost)
	    for (uint8_t i = size ; i > 0; i--) {

	    	if( var[i-1] != ASCII_Char_Space && var[i-1] )
	    	{

	    		if( var[i-1] < 48 || var[i-1] > 57 )
	    		{
	    			uint8_t errorNotNumber[] = "\n\n\n\r ERROR: Your input has characters other than a number.\n\n\r Please do not enter characters other than numbers\n\r";
	    			HAL_UART_Transmit(huart, errorNotNumber, sizeof(errorNotNumber), 500);
	    			return 0;
	    		}

	    		digitValue = var[i-1] - ASCII_Char_0;

		        controlValue += digitValue * multiplier;
		        multiplier *= 10;

		        currentDigit--;
	    	}
	    	else{currentDigit--;}

	    }
	    if( controlValue > 255 )
	    {
	    	uint8_t errorOverLimit[] = "\n\n\n\r ERROR: Your input is over the size limit, Please enter numbers lower than 256.\n\r";
	    	HAL_UART_Transmit(huart, errorOverLimit, sizeof(errorOverLimit), 500);
	    	return 0;
	    }
	    else
	    {
	    	dec = (uint8_t)controlValue;
	    	return dec;
	    }

	    return 0;
}

void AddHead(LinkedList *list, uint8_t data)
{
	Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = data;
    new_node->index = 1;

	if( list->tail == NULL )
	{
		list->tail = new_node;
		new_node->next = NULL;
	}
	else
	{
		new_node->next = list->head;
		Node *temp = new_node;

		while( temp->next != NULL)
		{
			temp->next->index = temp->index + 1;

			temp = temp->next;
		}
	}

	list->head = new_node;

}

void AddTail(LinkedList *list, uint8_t data)
{
	Node *new_node = (Node *) malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;

	if( list->head == NULL )
	{
		list->head = new_node;
		new_node->index = 1;
	}
	else
	{
		list->tail->next = new_node;
		new_node->index = list->tail->index + 1;
	}
	list->tail = new_node;

}

Node *GetNode(LinkedList *list, uint8_t index)
{
	Node *tempNode = list->head;

	while( tempNode != NULL)
	{
		if( tempNode->index == index )
		{
			return tempNode;
		}

		tempNode = tempNode->next;
	}

	return NULL;
}

HAL_StatusTypeDef CheckNode(LinkedList *list, Node *node)
{
	Node *tempNode = list->head;

	while( tempNode != NULL )
	{
		if( tempNode == node)
		{
			return HAL_OK;
		}
		tempNode = tempNode->next;
	}

	return HAL_ERROR;

}

void Delete(LinkedList *list, Node *node)
{
	if( node == list->head )
	{
		if( list->head->next == NULL )
		{
			list->head = list->tail = NULL;
		}
		else
		{
			list->head = list->head->next;

			Node *temp = list->head;
			while(temp != NULL)
			{
				temp->index = temp->index - 1;

				temp = temp->next;
			}

		}
	}
	else
	{
		Node *temp = list->head;
		while( temp != NULL && temp->next != node )
		{
			temp = temp->next;
		}
		if( temp != NULL )
		{
			temp->next = node->next;

			while(temp->next != NULL)
			{
				temp->next->index = temp->next->index - 1;

				temp = temp->next;
			}

			if( node->next == NULL )
			{
				list->tail = temp;
			}
		}
	}

	free(node);
}

StateType_t IsEmpty(LinkedList *list)
{
	if( list->head == NULL && list->tail == NULL )
	{
		return STATE_ON;
	}

	return STATE_OFF;

}

void WriteIndex(LinkedList *list, UART_HandleTypeDef *huart, Node *node)
{

		uint8_t node_index = node->index;
		uint8_t digit = 0;
		uint8_t temp = node_index;

		while (temp) {

			// Increment number of digits
		    digit++;

		    // Truncate the last
		    // digit from the number
		    temp /= 10;
		}

		uint8_t indexArray[digit];
	    uint8_t count = digit - 1;
	    while (node_index) {

	        // Separate last digit from
	        // the number and add ASCII
	        // value of character '0' is 48
	        indexArray[count] = node_index % 10 + ASCII_Char_0;

	        count--;
	        // Truncate the last
	        // digit from the number
	        node_index /= 10;
	    }

	    for( uint8_t i = 0; i < sizeof(indexArray); i++)
	    {
	    		HAL_UART_Transmit(huart, &indexArray[i], 1, HAL_MAX_DELAY);
	    }

}

void WriteData(LinkedList *list, UART_HandleTypeDef *huart, Node *node)
{

	uint8_t node_data = node->data;
	uint8_t digit = 0;
	uint8_t temp = node_data;

	while (temp) {

		// Increment number of digits
	    digit++;

	    // Truncate the last
	    // digit from the number
	    temp /= 10;
	}

	uint8_t dataArray[digit];
    uint8_t count = digit - 1;
    while (node_data) {

        // Separate last digit from
        // the number and add ASCII
        // value of character '0' is 48
        dataArray[count] = node_data % 10 + ASCII_Char_0;

        count--;
        // Truncate the last
        // digit from the number
        node_data /= 10;
    }

    for( uint8_t i = 0; i < sizeof(dataArray); i++)
    {
    		HAL_UART_Transmit(huart, &dataArray[i], 1, HAL_MAX_DELAY);
    }

}

void DisplayLinkedList(LinkedList *list, UART_HandleTypeDef *huart)
{
	uint8_t title[] = "\n Linked List\n\r";
	HAL_UART_Transmit(huart, title, sizeof(title), HAL_MAX_DELAY);

	if( IsEmpty(list) )
	{
		uint8_t emptyList[] = "\n List is Empty\n\r";
		HAL_UART_Transmit(huart, emptyList, sizeof(emptyList), HAL_MAX_DELAY);
	}

	Node *temp = list->head;

	while (temp != NULL)
	{

		WriteIndex( list, huart, GetNode(list, temp->index) );
		HAL_UART_Transmit(huart, (uint8_t *)"- ", 2, HAL_MAX_DELAY);

		WriteData(list, huart, temp);
		HAL_UART_Transmit(huart, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);

		temp = temp->next;
	}
}
