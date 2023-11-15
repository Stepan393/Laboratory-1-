/*
Домнин Степан, 105 группа, Лабораторная работа №1.
Задание:
    Данные (элементы массива) - 64-разрядные целые числа (long long int).
    Вид сортировки - числа упорядочиваются по невозрастанию.
    Методы сортировки:
        1. Метод простого выбора.
        2. Пирамидальная сортировка.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

long long *createArray(int, char);                                    // Функция генерации массива
void reversed(long long *, int);                                // Функция изменения порядка элементов в массиве на обратный
void selectionSort(long long *, int);       // Функция сортировки массива методом простого выбора
void maxHeapify(long long*, int, int, long long*, long long*);  // Процедура преобразования в двоичную кучу поддерева с корневым узлом i, что является
                                                                // индексом в arr[]. n - размер кучи
void buildMaxHeap(long long*, int, long long*, long long*);
void heapSort(long long *, int);            // Функция пирамидальной сортировки массива
void printArray(long long *, int);                              // Функция вывода массива
void swap(long long *, long long *);                            
int comp(const void *, const void *);                           // Функция-компаратор для qsort

int main(int argc, char const *argv[])
{
    SetConsoleOutputCP(CP_UTF8); // Для корректного отображения кириллицы

   int N, fl_len = 0;
    char fl_arrayType = 'u'; // флаги задания параметров
    int fl_sortType = 2;

    if (argc <= 1)
    {
        printf("Справочная информация: \n\t%s --help", argv[0], argv[0]);
        return 0;
    }

    if (!strcmp(argv[1], "--help"))
    {
        printf("\nИспользование: main.exe --len [N] [--arrayType [atype]] [--sortType [stype]]\n\n\
Описание\n\
    Программа вычисляет число перемещений и число сравнений при генерации и сортировке массива целых чисел разными способами.\n\n\
Параметры:\n\
    --len [N]   Длина генерируемого массива (натуральное число, обязательный параметр)\n\
    --arrayType [atype] Тип генерации массива (по умолчанию: u):\n\
        s - отсортированы в порядке невозрастания\n\
        r - отсортированы в порядке возрастания\n\
        u - несортированный\n\
    --sortType [stype] Используемый алгоритм сортировки (по умолчанию: 2):\n\
        1 - сортировка методом простого выбора выбора\n\
        2 - пирамидальная сортировка\n\n\
Примеры:\n\
main.exe --len 100\n\
    Генерирует неотсортированный массив длиной 100 и сортирует его с помощью пирамидальной сортировки.\n\n\
main.exe --len 50 --arrayType r --sortType 1\n\
    Генерирует отсортированный массив длиной 50 в порядке убывания и сортирует его с помощью сортировки методом простого выбора.\n");
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {

        if (!strcmp(argv[i], "--len"))
        {
            fl_len = 1;
            if (i + 1 > argc - 1 || sscanf(argv[i + 1], "%d", &N) != 1 || (N <= 0))
            {
                printf("'--len' параметр требует целочисленного аргумента. Справочная информация: \n\t%s --help\n");
                return 0;
            }
            i++;
            continue;
        }

        if (!strcmp(argv[i], "--arrayType"))
        {
            if (i + 1 > argc - 1 || sscanf(argv[i + 1], "%c", &fl_arrayType) != 1 || (fl_arrayType != 's' && fl_arrayType != 'r' && fl_arrayType != 'u'))
            {
                printf("Неправильный аргумент для параметра '--arrayType'. Справочная информация: \n\t%s --help\n");
                return 0;
            }
            i++;
            continue;
        }

        if (!strcmp(argv[i], "--sortType"))
        {
            if (i + 1 > argc - 1 || sscanf(argv[i + 1], "%d", &fl_sortType) != 1 || (fl_sortType > 2 && fl_sortType < 1))
            {
                printf("Неправильный аргумент для параметра '--sortType'. Справочная информация: \n\t%s --help\n");
                return 0;
            }
            i++;
            continue;
        }
    }

    if (fl_len = 0)
    {
        printf("Отсутствует обязательный параметр '--len'. Справочная информация: \n\t%s --help\n");
        return 0;
    }

    long long *mas;

    if (fl_arrayType == 's' || fl_arrayType == 'r' || fl_arrayType == 'u')
    {
        mas = createArray(N, fl_arrayType);
    }

    long long *mas1 = (long long *)malloc(N * sizeof(long long));
    
    for (int i = 0; i < N; i++)
    {
        mas1[i] = mas[i];
    }

    
    selectionSort(mas, N);
    
    heapSort(mas1, N);

    free(mas);
    free(mas1);

    system("pause");
    return 0;
}

long long *createArray(int N, char type)
{
    long long *a = (long long *)malloc(N * sizeof(long long));

    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        // Генерация случайного 64-битного целого числа
        a[i] = (long long) rand() * rand() * rand() * rand() * rand();
    }
    
    if (type == 's')
    {
        qsort(a, N, sizeof(long long), comp);
        reversed(a, N);
    }
    else if (type == 'r')
    {
        qsort(a, N, sizeof(long long), comp);
    }

    return a;
}

void reversed(long long *arr, int N)
{
    for (int i = 0; i < N / 2; i++)
    {
        swap(&arr[i], &arr[N - i - 1]);
    }
}

void selectionSort(long long *mas, int N)
{
    long long cmp = 0, mov = 0;
    // Проходим по всем элементам массива
    for (int i = 0; i < N - 1; i++)
    {
        // Находим максимальный элемент в оставшейся части массива
        int min_idx = i;
        for (int j = i + 1; j < N; j++)
        {
            cmp += 1;
            if (mas[j] > mas[min_idx])
            {
                min_idx = j;
            }
        }

        // Меняем найденный максимальный элемент с текущим элементом
        swap(&mas[i], &mas[min_idx]);
        mov += 1;
    }
    printf("Selection sort − %lld − %lld \n" , cmp , mov);
}

void maxHeapify(long long* arr, int i, int n, long long* cmp, long long* moves) {
    int l = 2*i+1;
    int r = 2*i+2;
    int largest;
    if(l<n && arr[l]<arr[i]) {
        largest=l;
    } else {
        largest=i;
    }
    (*cmp)++;
    if(r<n && arr[r]<arr[largest]) {
        largest=r;
    }
    (*cmp)++;
    if(largest!=i) {
        swap(&arr[i], &arr[largest]);
        (*moves)++;
        maxHeapify(arr, largest, n, cmp, moves);
    }
}

void buildMaxHeap(long long* arr, int n, long long* cmp, long long* moves) {
    for(int i=n/2-1; i>=0; i--) {
        maxHeapify(arr, i, n, cmp, moves);
    }
}

void heapSort(long long* arr, int n) {
    long long cmp = 0, mov = 0;
    buildMaxHeap(arr, n, &cmp, &mov);
    for(int i=n-1; i>0; i--) {
        swap(&arr[0], &arr[i]);
        mov++;
        maxHeapify(arr, 0, i, &cmp, &mov);
    }
    printf("Heapsort − %lld − %lld \n" , cmp , mov);
}

void printArray(long long *mas, int N)
{
    for (int i = 0; i < N; i++)
        if (i < N - 1)
            printf("%lld ", mas[i]);
        else
            printf("%lld\n", mas[i]);
}

void swap(long long *a, long long *b)
{
    long long temp = *a;
    *a = *b;
    *b = temp;
}

int comp(const void * a, const void * b)
{
    const long long *x = (const long long *)a;
    const long long *y = (const long long *)b;
    return (*x > *y) - (*x < *y);
}