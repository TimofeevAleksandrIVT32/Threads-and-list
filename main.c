#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include <locale.h>
#include <stdlib.h>
#include "list.h"
#include "threads.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //мьютекс
int flag = 0; //нужен для корректного очищения последнего элемента списка

int main() {
    setlocale(LC_ALL, "Rus");
    struct list_args *arg1; //аргументы для вызова функции в первом потоке
    struct list_args *arg2 = malloc(sizeof(struct list_args)); //аргументы для вызова функции во втором потоке
    arg1 = init(); //создаем двусвязный список (функция возвращает указатели на первый и последний элементы двусвязного списка)
    if (arg1->head == NULL) {//если элементов меньше 1 или произошли ошибки связанные с выделением динамической памяти, то будет возвращен NULL
        return 0; //завершаем работу программы
    }
    arg1->direction = 0; //при направлении 0 обход происходит с начала списка
    arg2->head = arg1->head; //заполняем аргументы для вызова функции во втором потоке
    arg2->tail = arg1->tail;
    arg2->direction = 1; //при направлении 1 обход происходит с конца списка
    print_and_bin (arg1->head); //вывод элементов и перевод их в двоичную систему
    pthread_t thread1; //создаем идентификатор потока 1
    pthread_t thread2; //создаем идентификатор потока 2
    pthread_create(&thread1,NULL,fun_for_threads,arg1); //создание 1 потока, который будет обрабатывать список с начала
    pthread_create(&thread2,NULL,fun_for_threads,arg2); //создание 2 потока, который будет обрабатывать список с конца
    pthread_join(thread1, NULL); //ожидаем завершения потока 1
    pthread_join(thread2, NULL); //ожидаем завершения потока 2
    free(arg1); //освобождаем память, выделенную для аргументов
    free(arg2);
    pthread_mutex_destroy(&mutex); //уничтожаем мьютекс
    return 0;
}