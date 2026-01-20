#ifndef DATABASE_H
#define DATABASE_H

#define SIZE 7

// Структура для продукта (Вариант 19 из лабы 18)
typedef struct {
    char name[50]; // Наименование
    int day, month, year; // Дата производства
    int shelf_life; // Срок годности в днях
    float price; // Цена
    char series[20]; // Номер серии
} Product;

extern Product products[SIZE];  // Глобальный массив

// Прототипы функций
void fill_array(void);
void print_array(void);
void edit_record(void);
void search_by_name(void);
void sort_array(void);
void save_to_file(void);
void load_from_file(void);
void print_expiring_products(void);

#endif