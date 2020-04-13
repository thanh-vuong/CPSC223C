// Thanh Vuong
// CPSC 223C
// Linked Lists
// 4/12/2020

#include "slist.h"

snode* snode_create(int data, snode* next) {
    snode* p = (snode*)malloc(sizeof(snode));
    p->data = data;
    p->next = next;
    return p;
}

slist* slist_create() {
    slist* p = (slist*)malloc(sizeof(slist));
    p->head = NULL;
    p->tail = NULL;
    p->size = 0;
    return p;
}

bool slist_empty(slist* list) { return list->size == 0; }
size_t slist_size(slist* list) { return list->size; }

void slist_popfront(slist* list) {
    if (slist_empty(list)) { printf("List is empty\n"); return; }
    // p refers to head node
    snode* p = list->head;
    // move head ptr forward
    list->head = list->head->next;
    // remove head node
    free(p);
    --list->size;
}

void slist_popback(slist* list) {
    if (slist_empty(list)) { printf("List is empty\n"); return; }
    if (slist_size(list) == 1) { slist_popfront(list); return; }
    snode* p = list->head;
    // move p to node before tail
    while (p->next != list->tail) { p = p->next; }
    // remove old tail node
    free(list->tail);
    // move tail backward to p
    list->tail = p;
    p->next = NULL;
    --list->size;
}

void slist_pushfront(slist* list, int data) {
    // new node before head
    snode* p = snode_create(data, list->head);
    // move head backward to p
    list->head = p;
    if (list->size == 0) { list->tail = p; }
    ++list->size;
}

void slist_pushback(slist* list, int data) {
    if (list->size == 0) { slist_pushfront(list, data); return; }
    // new node after tail
    snode* p = snode_create(data, NULL);
    list->tail->next = p;
    // move tail forward
    list->tail = p;
    ++list->size;
}

void slist_clear(slist* list) {
    while (!slist_empty(list)) { slist_popfront(list); }
}

void slist_print(slist* list, const char* msg) {
    printf("%s\n", msg);
    if (slist_empty(list)) { printf("List is empty\n"); return; }

    snode* p = list->head;
    while (p != NULL) {
        printf("%d --> %p\n", p->data, p->next);
        p = p->next;
    }
}

int slist_front(slist* list) {
    if (slist_empty(list)) { fprintf(stderr, "List is empty\n"); exit(1); }
    return list->head->data;
}

int slist_back(slist* list) {
    if (slist_empty(list)) { fprintf(stderr, "List is empty\n"); exit(1); }
    return list->tail->data;
}