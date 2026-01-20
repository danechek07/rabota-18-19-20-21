#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "database.h"

// Статический массив с константными значениями (как "загрузка из файла")
Product products[SIZE];

// Заполнение массива начальными значениями
void fill_array() {
    strcpy(products[0].name, "Молоко 3.2%");
    products[0].day = 15; products[0].month = 1; products[0].year = 2026;
    products[0].shelf_life = 6; products[0].price = 89.90; strcpy(products[0].series, "MOL001");

    strcpy(products[1].name, "Хлеб нарезной");
    products[1].day = 18; products[1].month = 1; products[1].year = 2026;
    products[1].shelf_life = 3; products[1].price = 52.00; strcpy(products[1].series, "HLEB12");

    strcpy(products[2].name, "Колбаса Докторская");
    products[2].day = 16; products[2].month = 1; products[2].year = 2026;
    products[2].shelf_life = 14; products[2].price = 489.00; strcpy(products[2].series, "KOL889");

    strcpy(products[3].name, "Сыр Российский 50%");
    products[3].day = 17; products[3].month = 1; products[3].year = 2026;
    products[3].shelf_life = 45; products[3].price = 720.50; strcpy(products[3].series, "SYR404");

    strcpy(products[4].name, "Йогурт клубничный");
    products[4].day = 19; products[4].month = 1; products[4].year = 2026;
    products[4].shelf_life = 7; products[4].price = 48.90; strcpy(products[4].series, "YOG777");

    strcpy(products[5].name, "Творог 5%");
    products[5].day = 20; products[5].month = 1; products[5].year = 2026;
    products[5].shelf_life = 10; products[5].price = 135.00; strcpy(products[5].series, "TVO22");

    strcpy(products[6].name, "Масло сливочное 83%");
    products[6].day = 15; products[6].month = 1; products[6].year = 2026;
    products[6].shelf_life = 60; products[6].price = 389.00; strcpy(products[6].series, "MAS101");
}

// Печать одной записи
void print_product(Product p, int index) {
    printf("| %2d | %-20s |        %02d.%02d.%04d |      %3d дней |  %7.2f | %-10s |\n",
        index + 1, p.name, p.day, p.month, p.year, p.shelf_life, p.price, p.series);
}

// Печать всего массива
void print_array() {
    printf("=========================================================================================\n");
    printf("| №  | Наименование         | Дата производства | Срок годности |   Цена   |   Серия    |\n");
    printf("=========================================================================================\n");
    for (int i = 0; i < SIZE; i++) {
        print_product(products[i], i);
    }
    printf("=========================================================================================\n");
}

// Изменение записи
void edit_record() {
    int index;
    printf("Введите номер записи для изменения (1-%d): ", SIZE);
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= SIZE) {
        printf("Неверный номер записи\n");
        return;
    }

    printf("Текущие данные:\n");
    print_product(products[index], index);
    printf("Введите новые данные:\n");
    printf("Наименование: ");
    scanf(" %49[^\n]", products[index].name);
    printf("Дата производства (дд мм гггг): ");
    scanf("%d %d %d", &products[index].day, &products[index].month, &products[index].year);
    printf("Срок годности (дней): ");
    scanf("%d", &products[index].shelf_life);
    printf("Цена: ");
    scanf("%f", &products[index].price);
    printf("Серия: ");
    scanf("%19s", products[index].series);

    printf("Запись обновлена\n");
}
// Поиск по наименованию
void search_by_name() {
    char search[50];
    printf("Введите наименование для поиска: ");
    scanf(" %49[^\n]", search);

    int found = 0;
    for (int i = 0; i < SIZE; i++) {
        if (strstr(products[i].name, search) != NULL) {
            print_product(products[i], i);
            found = 1;
        }
    }

    if (!found) printf("Товар не найден\n");
}

// Сравнение по цене для qsort
int compare_by_price(const void* a, const void* b) {
    const Product* p1 = (const Product*)a;
    const Product* p2 = (const Product*)b;
    if (p1->price < p2->price) return -1;
    if (p1->price > p2->price) return 1;
    return 0;
}

// Сортировка по цене
void sort_array() {
    qsort(products, SIZE, sizeof(Product), compare_by_price);
    printf("Массив отсортирован по цене\n");
    print_array();
}

// Сохранение в новый файл
void save_to_file() {
    char new_filename[100] = "products_modified.txt";
    FILE* f = fopen(new_filename, "w");
    if (!f) {
        printf("Не удалось создать файл %s\n", new_filename);
        return;
    }

    for (int i = 0; i < SIZE; i++) {
        fprintf(f, "%s|%02d.%02d.%04d|%d|%.2f|%s\n",
            products[i].name,
            products[i].day, products[i].month, products[i].year,
            products[i].shelf_life,
            products[i].price,
            products[i].series);
    }

    fclose(f);
    printf("Данные сохранены в %s\n", new_filename);
}

// Загрузка из файла (самый простой вариант)
void load_from_file() {
    char filename[100];
    printf("Введите имя файла для загрузки: ");
    scanf(" %99[^\n]", filename);
    if (strlen(filename) == 0) strcpy(filename, "products_modified.txt");

    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Не удалось открыть файл %s\n", filename);
        return;
    }

    int i = 0;
    char name[50];
    int day, month, year, shelf_life;
    float price;
    char series[20];

    // Читаем данные в формате: Название|дд.мм.гггг|срок|цена|серия
    while (i < SIZE &&
        fscanf(f, "%49[^|]|%d.%d.%d|%d|%f|%19s\n",
            name, &day, &month, &year, &shelf_life, &price, series) == 7) {

        strcpy(products[i].name, name);
        products[i].day = day;
        products[i].month = month;
        products[i].year = year;
        products[i].shelf_life = shelf_life;
        products[i].price = price;
        strcpy(products[i].series, series);

        i++;
    }

    fclose(f);
    printf("Загружено %d записей из %s\n", i, filename);
}

// Вывод товаров с истекающим сроком (в течение 5 дней от текущей даты)
void print_expiring_products() {
    time_t now = time(NULL);
    struct tm* current = localtime(&now);
    int current_day = current->tm_mday;
    int current_month = current->tm_mon + 1;
    int current_year = current->tm_year + 1900;

    printf("Товары, срок годности которых заканчивается в течение 5 дней (от %02d.%02d.%04d):\n",
        current_day, current_month, current_year);

    int found = 0;
    printf("=========================================================================================\n");
    printf("| №  | Наименование         | Дата производства | Срок годности |   Цена   |   Серия    |\n");
    printf("=========================================================================================\n");

    for (int i = 0; i < SIZE; i++) {
        // Конвертируем дату производства в time_t
        struct tm prod_date = { 0 };
        prod_date.tm_year = products[i].year - 1900;
        prod_date.tm_mon = products[i].month - 1;
        prod_date.tm_mday = products[i].day;
        prod_date.tm_hour = 12;  // Чтобы избежать проблем с DST
        time_t prod_time = mktime(&prod_date);

        if (prod_time == -1) continue;  // Ошибка даты

        // Добавляем shelf_life дней (примерно: shelf_life * 86400 сек)
        time_t exp_time = prod_time + (products[i].shelf_life * 86400);

        // Разница в днях с текущим
        double diff_sec = difftime(now, exp_time);
        int days_left = (int)(-diff_sec / 86400);  // Отрицательная diff если истекает

        if (days_left <= 5 && days_left >= 0) {
            print_product(products[i], i);
            found = 1;
        }
    }

    if (!found) {
        printf("|                          Таких товаров нет                                     |\n");
    }
    printf("=========================================================================================\n");
}