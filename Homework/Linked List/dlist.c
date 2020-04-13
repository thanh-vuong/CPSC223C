// Thanh Vuong
// CPSC 223C
// Linked Lists
// 4/12/2020

#include "dlist.h"

dnode* dnode_create(int data, dnode* prev, dnode* next) {
    dnode* p = (dnode*)malloc(sizeof(dnode));
    p->data = data;
    p->next = next;
    p->prev = prev;
    return p;
}

dlist* dlist_create(void) {
    dlist* p = (dlist*)malloc(sizeof(dlist));
    p->head = NULL;
    p->tail = NULL;
    p->size = 0;
    return p;
}

bool dlist_empty(dlist* list) { return list->size == 0; }
size_t dlist_size(dlist* list) { return list->size; }

void dlist_popfront(dlist* list) {
    if (dlist_empty(list)) { printf("List is empty\n"); return; }
    // p refers to head node
    dnode* p = list->head;
    // move head ptr forward
    list->head = list->head->next;
    // remove head node
    free(p);
    --list->size;
}

void dlist_popback(dlist* list) {
    if (dlist_empty(list)) { printf("List is empty\n"); return; }
    if (dlist_size(list) == 1) { dlist_popfront(list); return; }
    // p refers to node before tail
    dnode* p = list->tail->prev;
    // remove old tail node
    free(list->tail);
    // p is new tail
    list->tail = p;
    p->next = NULL;
    --list->size;
}

void dlist_pushfront(dlist* list, int data) {
    // new node before head
    dnode* p = dnode_create(data, NULL, list->head);
    // move head backward to p
    list->head = p;
    if (list->size == 0) { list->tail = p; }
    ++list->size;
}

void dlist_pushback(dlist* list, int data) {
    if (list->size == 0) { dlist_pushfront(list, data); return; }
    // new node after tail
    dnode* p = dnode_create(data, list->tail, NULL);
    list->tail->next = p;
    // move tail forward
    list->tail = p;
    ++list->size;
}

void dlist_clear(dlist* list) {
    while (!dlist_empty(list)) { dlist_popfront(list); }
}

void dlist_print(dlist* list, const char* msg) {
    printf("%s\n", msg);
    if (dlist_empty(list)) { printf("List is empty\n"); return; }

    dnode* p = list->head;
    while (p != NULL) {
        printf("%p <-- %d --> %p\n", p->prev, p->data, p->next);
        p = p->next;
    }
}

int dlist_front(dlist* list) {
    if (dlist_empty(list)) { fprintf(stderr, "List is empty\n"); exit(1); }
    return list->head->data;
}

int dlist_back(dlist* list) {
    if (dlist_empty(list)) { fprintf(stderr, "List is empty\n"); exit(1); }
    return list->tail->data;
}