#include "linklist.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

doubly_linked_list* init_list(void)
{
	doubly_linked_list* new_list = malloc(sizeof(doubly_linked_list));
	new_list->size = 0;
	new_list->first = NULL;
	new_list->last = NULL;
	return new_list;
}


int size_of_list(doubly_linked_list* list)
{
	if (list == NULL)
		return 0;

	return list->size;
}


doubly_linked_list* copy_int_list(doubly_linked_list* original_list)
{
	doubly_linked_list* new_list = init_list();

	if (original_list == NULL)
		return new_list;

	doubly_linked_node* current_node = original_list->first;
	while (current_node != NULL) {
		doubly_linked_node* new_node = malloc(sizeof(doubly_linked_node));
		new_node->data = current_node->data;
		insert_at_tail(new_list, new_node);
		current_node = current_node->next;
	}

	return new_list;
}


void print_int_list_curses(doubly_linked_list* list)
{
	if (list == NULL)
		return;

	doubly_linked_node* current_node = list->first;
	while (current_node != NULL) {
		printw("%d ", current_node->data);
		current_node = current_node->next;
	}
}


bool list_contains_node(doubly_linked_list* list, doubly_linked_node* node)
{
	if (list == NULL || node == NULL)
		return false;

	doubly_linked_node* current_node = list->first;
	while (current_node != NULL) {
		if (node == current_node)
			return true;
		current_node = current_node->next;
	}

	return false;
}


doubly_linked_node* find_max_node(doubly_linked_list* list)
{
	if (list == NULL)
		return NULL;

	doubly_linked_node* max_node = list->first;
	doubly_linked_node* current_node = max_node->next;
	while (current_node != NULL) {
		if (current_node->data > max_node->data)
			max_node = current_node;
		current_node = current_node->next;
	}

	return max_node;
}


doubly_linked_node* find_min_node(doubly_linked_list* list)
{
	if (list == NULL)
		return NULL;

	doubly_linked_node* min_node = list->first;
	doubly_linked_node* current_node = min_node->next;
	while (current_node != NULL) {
		if (current_node->data < min_node->data)
			min_node = current_node;
		current_node = current_node->next;
	}

	return min_node;
}


void insert_at_head(doubly_linked_list* list, doubly_linked_node* new_node)
{
	if (list == NULL)
		return;

	new_node->previous = NULL;

	if (list->first == NULL) {
		new_node->next = NULL;
		list->last = new_node;
	}
	else {
		doubly_linked_node* old_first_node = list->first;
		new_node->next = old_first_node;
		old_first_node->previous = new_node;   
	}

	list->first = new_node;
	list->size += 1;
}


void insert_at_tail(doubly_linked_list* list, doubly_linked_node* new_node)
{
	if (list == NULL)
		return;

	new_node->next = NULL;

	if (list->last == NULL) {
		list->first = new_node;
		new_node->previous = NULL;
	}
	else {
		doubly_linked_node* old_last_node = list->last;
		old_last_node->next = new_node;
		new_node->previous = old_last_node;
	}

	list->last = new_node;
	list->size += 1;
}


void insert_before_index(doubly_linked_list* list, doubly_linked_node* new_node, const int index)
{
	if (list == NULL || new_node == NULL)
		return;

	doubly_linked_node* current_node = list->first;
	int current_index = 0;
	while (current_node != NULL && current_index != index) {
		current_node = current_node->next;
		current_index++;
	}

	// TODO
}


void update_node(doubly_linked_node* node, const int new_data)
{
	if (node == NULL)
		return;

	node->data = new_data;
}


void delete_head(doubly_linked_list* list)
{
	if (list == NULL)
		return;

	doubly_linked_node* old_first_node = list->first;
	if (old_first_node != NULL) {
		if (old_first_node == list->last) {
			list->first = NULL;
			list->last = NULL;
		}
		else {
			doubly_linked_node* new_first_node = old_first_node->next;
			new_first_node->previous = NULL;
			list->first = new_first_node;
		}
		free(old_first_node);
		list->size -= 1;
	}
}


void delete_tail(doubly_linked_list* list)
{
	if (list == NULL)
		return;

	doubly_linked_node* old_last_node = list->last;
	if (old_last_node != NULL) {
		if (old_last_node == list->first) {
			list->first = NULL;
			list->last = NULL;
		}
		else {
			doubly_linked_node* new_last_node = old_last_node->previous;
			new_last_node->next = NULL;
			list->last = new_last_node;
		}
		free(old_last_node);
		list->size = list->size - 1;
	}
}


void unlink_node(doubly_linked_list* list, doubly_linked_node* node)
{
	if (list == NULL || node == NULL)
		return;

	bool previous_node_is_null = (node->previous == NULL);
	bool next_node_is_null = (node->next == NULL);

	if (previous_node_is_null && next_node_is_null) {
		// The node doesn't link to anything.
		list->first = NULL;
		list->last = NULL;
	}
	else if (next_node_is_null) {
		// The node only links to a preceding node.
		// It must be the tail of the list.
		list->last = node->previous;
		node->previous->next = NULL;
	}
	else if (previous_node_is_null) {
		// The node only links to a succeeding node.
		// It must be the head of the list.
		list->first = node->next;
		node->next->previous = NULL;
	}
	else {
		// The node is between two other nodes.
		node->previous->next = node->next;
		node->next->previous = node->previous;
	}

	list->size -= 1;
}


void delete_node(doubly_linked_list* list, doubly_linked_node* node)
{
	if (list != NULL && node != NULL) {
		unlink_node(list, node);
		free(node);
	}
}


void delete_list(doubly_linked_list* list)
{
	if (list == NULL)
		return;

	doubly_linked_node* current_node = list->first;
	while (current_node != NULL) {
		doubly_linked_node* next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}

	free(list);
}

