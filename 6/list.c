#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node* create_node(const void* data){
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL) {return NULL;}
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

LinkedList* create_list(void){
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if(list == NULL) {return NULL;}
    list->head = NULL;
    list->tail = NULL;
    list->list_count = 0;
    return list;
}

Node* push_back(LinkedList* list, const void* data){
    if(list == NULL){return NULL;}
    Node* new_node = create_node(data);
    if(new_node == NULL) {return NULL;}
    if(list->tail == NULL){
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->list_count++;
    return new_node;
}

Node* push_front(LinkedList* list, const void* data){
    if(list == NULL){return NULL;}
    Node* new_node = create_node(data);
    if(new_node == NULL) {return NULL;}
    if(list->head == NULL){
        list->head = new_node;
        list->tail = new_node;
    } else{
        new_node->next = list->head;
        list->head = new_node;
    }
    list->list_count++;
    return new_node;
}

Node* find_prev(LinkedList* list, Node* node){
    if(list == NULL || node == NULL) {return NULL;};
    for(Node* temp = list->head; temp; temp = temp->next){
        if(temp->next == node){
            return temp;
        }
    }
    return NULL;
}

Node* insert_after(LinkedList* list, Node* node, const void* data){
    if(list == NULL || node == NULL) {return NULL;};
    Node* new_node = create_node(data);
    if(new_node == NULL) {return NULL;};
    new_node->next = node->next;
    node->next = new_node;
    if(list->tail == node){
        list->tail = new_node;
    }
    list->list_count++;
    return new_node;
}

Node* insert_before(LinkedList* list, Node* node, const void* data){
    if(list == NULL || node == NULL){return NULL;};
    if(list->head == node){
        return push_front(list, data);
    }
    Node* new_node = create_node(data);
    if(new_node == NULL){return NULL;};
    Node* prev_node = find_prev(list, node);
    if(prev_node == NULL){return NULL;}
    new_node->next = node;
    prev_node->next = new_node;
    list->list_count++;

    return new_node;
}

void pop_front(LinkedList *list){
    if(list == NULL){return;}
    if(list->head == list->tail){
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else{
        Node* new_head = list->head->next;
        free(list->head);
        list->head = new_head;
    }
    if (list->list_count > 0){
        list->list_count--;
    }  
}
void pop_back(LinkedList* list){
    if(list == NULL) {return;}
    if(list->head == list->tail){
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else{
        Node* new_tail = find_prev(list, list->tail);
        if (new_tail == NULL) return;
        free(list->tail);
        list->tail = new_tail;
        new_tail->next = NULL;
    }
    if (list->list_count > 0){
        list->list_count--;
    }
}

void print_list(const LinkedList* list, void (*func_print)(const void*)){
    if(list == NULL){return;}
    for(const Node* temp = list->head; temp; temp = temp->next){
        func_print(temp->data);
        if(temp->next){
            putchar(' ');
        }
    }
    putchar('\n');
}

void destroy_list(LinkedList* list, void (*free_data)(void*)) {
    if(list == NULL){return;}
    Node* cur = list->head;
    while (cur) {
        Node* next = cur->next;
        if (cur->data && free_data)
            free_data(cur->data);
        free(cur);
        cur = next;
    }
    free(list);
}

void free_data_node(void* n) {
    free(n);
}



