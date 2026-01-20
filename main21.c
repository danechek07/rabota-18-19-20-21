#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include "database.h"

int main(void) {
    system("chcp 1251");
    int choice;
    do {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Инициализация массива\n");
        printf("2. Вывести массив продуктов\n");
        printf("3. Изменить запись\n");
        printf("4. Поиск по наименованию\n");
        printf("5. Сортировка по цене\n");
        printf("6. Сохранить в новый файл\n");
        printf("7. Загрузка из файла\n");
        printf("8. Вывести товары с истекающим сроком годности\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            fill_array();
            printf("Массив инициализирован (%d записей)\n", SIZE);
            break;
        case 2:
            print_array();
            break;
        case 3:
            edit_record();
            break;
        case 4:
            search_by_name();
            break;
        case 5:
            sort_array();
            break;
        case 6:
            save_to_file();
            break;
        case 7:
            load_from_file();
            break;
        case 8:
            print_expiring_products();
            break;
        case 0:
            printf("Выход из программы\n");
            break;
        default:
            printf("Неверный выбор\n");
        }
    } while (choice != 0);
    return 0;
}