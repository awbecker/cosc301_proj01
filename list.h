#ifndef __LIST_H__
#define __LIST_H__

struct node{
	int value;
	struct node *next;
};

void list_insert(int num, struct node **head);

void list_print(const struct node *head);

#endif // __LIST_H__
