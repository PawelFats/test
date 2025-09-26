#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

typedef struct {
    char name[32];
    int age;
} Person;

typedef struct {
    double x, y;
} Point;

void print_int(const void* data){
    printf("%d", *(const int*)data);
}

void print_person(const void* data) {
    const Person* p = (const Person*)data;
    printf("{%s, %d}", p->name, p->age);
}

void print_point(const void* data) {
    const Point* pt = (const Point*)data;
    printf("(%.1f,%.1f)", pt->x, pt->y);
}

void test_int(void) {
    puts("=== test: int ===");
    LinkedList* list = create_list();

    for (int i = 1; i <= 5; ++i) {
        int* v = malloc(sizeof *v);
        *v = i * 10;
        push_back(list, v);
    }

    printf("push_back: ");
    print_list(list, print_int);      //10 20 30 40 50

    pop_front(list);
    printf("pop_front: ");
    print_list(list, print_int);      //20 30 40 50

    pop_back(list);
    printf("pop_back: ");
    print_list(list, print_int);      //20 30 40

    destroy_list(list, free_data_node);
}

void test_person(void) {
    puts("\n=== test: person ===");
    LinkedList* people = create_list();

    Person* a = malloc(sizeof *a); 
    strcpy(a->name, "Pasha"); 
    a->age = 23;
    Person* b = malloc(sizeof *b); 
    strcpy(b->name, "Ivan");   
    b->age = 99;
    Person* c = malloc(sizeof *c); 
    strcpy(c->name, "Petr"); 
    c->age = 28;

    push_back(people, a);
    push_back(people, b);
    push_front(people, c); //Petr, Pasha, Ivan

    printf("person: ");
    print_list(people, print_person);  //{Petr,28} {Pasha,23} {Ivan,99} 

    Node* first = people->head;
    Person* d = malloc(sizeof *d); 
    strcpy(d->name, "Danil"); 
    d->age = 22;
    insert_after(people, first, d);   //Petr, Danil, Pasha, Ivan, 

    printf("insert_after(head): ");
    print_list(people, print_person);

    destroy_list(people, free_data_node);
}

void test_point(void) {
    puts("\n=== test: points ===");
    LinkedList* pts = create_list();

    Point* p1 = malloc(sizeof *p1); 
    p1->x = 1.0; 
    p1->y = 1.0;
    Point* p2 = malloc(sizeof *p2); 
    p2->x = 2.0; 
    p2->y = 2.0;
    Point* p3 = malloc(sizeof *p3); 
    p3->x = 4.0; 
    p3->y = 4.0;

    push_back(pts, p1);
    push_back(pts, p3); //p1, p3

    insert_before(pts, pts->tail, p2); //p1, p2, p3

    printf("points: ");
    print_list(pts, print_point); //(1.0,1.0) (2.0,2.0) (4.0,4.0)

    pop_back(pts);
    printf("after pop_back: ");
    print_list(pts, print_point); //(1.0,1.0) (2.0,2.0)

    destroy_list(pts, free_data_node);
}

int main(void) {
    test_int();
    test_person();
    test_point();
    return 0;
}