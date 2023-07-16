#ifndef LIST_H
#define LIST_H

struct list {
    int data; // поле данных
    struct list *next; // указатель на следующий элемент
    struct list *prev; // указатель на предыдущий элемент
};

struct list_args {
    struct list *head; //указатель на начало списка
    struct list *tail; //указатель на конец списка
    int direction; //направление обхода
};

struct list_args *init();
void print_and_bin(struct list *head);

#endif /* LIST_H */