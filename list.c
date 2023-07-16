#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "list.h"

//функция инициализации списка
struct list_args *init() {
    int n; //количество элементов списка
    struct list *new_el; //указатель для создаваемого элемента
    struct list *cur; //указатель для текущего элемента
    struct list_args *result;
    result = (struct list_args*)malloc(sizeof(struct list_args));
    int stime; //5 строчeк нужны для получения случайных чисел
    long ltime;
    ltime = time (NULL);
    stime = (unsigned int) ltime/2;
    srand(stime);
    printf("Введите размер двусвязного списка\n");
    scanf("%d", &n);
    printf("\n");
    if (n < 1) {
        printf("Невозможно создать список такого размера\n");
        printf("\n");
        result->head = NULL;
        result->tail = NULL;
        result->direction = -1;
        return result;
    }
    // выделение памяти под корень списка
    new_el = (struct list*)malloc(sizeof(struct list));
    if (new_el == NULL) { //если память не выделилась, то возвращаем NULL
        printf("Ошибка выделения памяти!\n");
        result->head = NULL;
        result->tail = NULL;
        result->direction = -1;
        return result;
    }
    new_el->data = rand()%1000; //добавляем данные
    new_el->next = NULL; // указатель на следующий узел
    new_el->prev = NULL; // указатель на предыдущий узел
    cur = new_el;
    result->head = new_el; //начало списка теперь записано в result->head
    for (int i = 1; i < n; i++) {
        new_el = (struct list*)malloc(sizeof(struct list)); //выделение памяти
        if (new_el == NULL) { //если во время цикла память не выделилась, то очищаем всю занятую ранее память и возращаем NULL
            printf("Ошибка выделения памяти!\n");
	        cur = result->head;
	        struct list *del;
            while (cur != NULL) {
		        del = cur;
		        cur = cur->next;
		        free (del);
	        }
            result->head = NULL;
            result->tail = NULL;
            result->direction = -1;
            return result;
        }
        cur->next = new_el; // предыдущий узел указывает на создаваемый
        new_el->data = rand()%1000; // добавляем данные в узел
        new_el->next = NULL; // теперь этот узел является последним
        new_el->prev = cur; // созданный узел указывает на предыдущий узел
        cur = new_el; // переходим на созданный узел
    }
    result->tail = cur; //в cur хранится указатель на конец списка, поэтому записываем его в result->tail
    result->direction = -1;
    return result; //возвращаем указатели на начало и конец списка
}

//функция для вывода элементов списка, а также перевода их в двоичную систему
void print_and_bin(struct list *head) {
    printf("Чтобы вывести элементы двузвязного списка, введите '1', иначе любой другой символ\n");
    int ans;
    struct list *cur; //указатель на текущий элемент
    cur = head;
    scanf("%d",&ans);
    //вывод элементов
    if (ans == 1) {
        printf("\n");
        printf("Элементы двусвязного списка:\n");
        do {
            printf("%d\t", cur->data); // вывод значения элемента cur
            cur = cur->next; // переход к следующему узлу
        } while (cur != NULL); // условие окончания обхода
        printf("\n");
    }
    printf("\n");
    cur = head;
    //переводим в двоичную систему
    int bin, k;
    do {
        bin = 0;
        k = 1;
        while (cur->data) {
            bin += (cur->data % 2) * k;
            k *= 10;
            cur->data /= 2;
        }
        cur->data = bin;
        cur = cur->next; // переход к следующему узлу
    } while (cur != NULL); // условие окончания обхода
    cur = head;
    //вывод элементов в двоичной форме
    if (ans == 1) {
        printf("Элементы двусвязного списка в двоичной системе:\n");
        do {
            printf("%010d\t", cur->data); // вывод значения элемента cur
            cur = cur->next; // переход к следующему узлу
        } while (cur != NULL); // условие окончания обхода
        printf("\n");
        printf("\n");
    }
}

