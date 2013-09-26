#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_insert(int num, struct node **head){
  	struct node *newnode = malloc(sizeof(struct node));
  	newnode->value = num;
	while(*head){
		if(num <= (*head)->value){
			newnode->next = *head;
			*head = newnode;
			//printf("%d\n", num);
			return;
		}
		if(! (*head)->next){
			newnode->next = NULL;
			(*head)->next = newnode;
			return;
		}
		if(num < (*head)->next->value){
			struct node *tmp = (*head)->next;
			(*head)->next = newnode;
			newnode->next = tmp;
			//printf("%d\n", num);
			return;
		}
		
		*head = (*head)->next;
	}
	newnode->next = NULL;
	*head = newnode;
	//printf("%d\n", num);
}

void list_print(const struct node *head){
	while(head){
		printf("%d\n", head->value);
		head = head->next;
	}
	//printf("%s\n", "-------------------");
}
