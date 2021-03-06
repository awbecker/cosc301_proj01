#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_insert(int num, struct node **head){
	struct node *tmp = *head;
	struct node *newnode = malloc(sizeof(struct node));
	newnode->value = num;
	while(tmp){
		if(num <= tmp->value){
			newnode->next = *head;
			*head = newnode;
			return;
		}
		if(! tmp->next){
			newnode->next = NULL;
			tmp->next = newnode;
			return;
		}
		if(num <= tmp->next->value){
			struct node *hold = tmp->next;
			tmp->next = newnode;
			newnode->next = hold;
			return;
		}
		tmp = tmp->next;
	}
	newnode->next = NULL;
	*head = newnode;
}

void list_print(const struct node *head){
	while(head){
		printf("%d\n", head->value);
		head = head->next;
	}
}

void list_clear(struct node *head){
	while(head){
		struct node *tmp = head;
		head = head->next;
		free(tmp);
	}
}
