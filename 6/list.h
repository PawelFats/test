#include <stdio.h>

typedef struct Node{
    void* data;           
    struct Node* next;    
} Node;

typedef struct LinkedList{
    Node* head;           
    Node* tail;           
    size_t list_count;    
} LinkedList;

//Создать узел. Сохраняет указатель data, не делает копию
Node* create_node(const void* data);

//Создать пустой список
LinkedList* create_list(void);

//Добавить элемент в конец. Возвращает указатель на новый узел или NULL
Node* push_back(LinkedList* list, const void* data);

//Добавить элемент в начало. Возвращает новый узел или NULL
Node* push_front(LinkedList* list, const void* data);

//Найти предыдущий узел для заданного node. NULL если не найден/если node == head
Node* find_prev(LinkedList* list, Node* node);

//Вставить после node. Возвращает новый узел или NULL при ошибке. 
Node* insert_after(LinkedList* list, Node* node, const void* data);

//Вставить перед node (ищет предыдущий узел). Возвращает новый узел или NULL
Node* insert_before(LinkedList* list, Node* node, const void* data);

//Удалить первый узел
void pop_front(LinkedList *list);

//Удалить последний узел
void pop_back(LinkedList* list);

//Пройти список и распечатать каждый элемент через func_print
void print_list(const LinkedList* list, void (*func_print)(const void*));

//Полностью освободить список. free_data — для освобождения каждого node->data (может быть NULL)
void destroy_list(LinkedList* list, void (*free_data)(void*));

//free для передачи в destroy_list
void free_data_node(void* n);
