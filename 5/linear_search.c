//generic функцию линейного поиска в массиве
#include <stdio.h>
#include <string.h>

void* linear_search(
    const void* arr, 
    size_t len_ar, 
    size_t type_size, 
    const void* key, 
    int (*cmp)(const void*, const void*))
{
    const char* byte_step = (const char*)arr;
    for(size_t i = 0; i < len_ar; i++){
        const void* elem = byte_step + i * type_size;
        if(cmp(elem, key)){
            return (void*)elem;
        }
    }
    return NULL;
}

int cmp_int(const void* a, const void* b){
    const int* x = (const int*)a;
    const int* y = (const int*)b;
    return (*x == *y);
}

int cmp_double(const void* a, const void* b) {
    const double* x = (const double*)a;
    const double* y = (const double*)b;
    return (*x == *y);
}

int cmp_string(const void* a, const void* b){

    const char* x = *(const char* const*)a;
    const char* y = *(const char* const*)b;

    return strcmp(x, y) == 0 ? 1 : 0;
}

int cmp_char(const void* a, const void* b){

    const char* x = (const char*)a;
    const char* y = (const char*)b;

    return (*x == *y);
}

int main(void){

    //int
    int arr_int[] = {1, 3, 5, 7, 9};
    int key_int = 5;
    int* found_int = linear_search(arr_int, 5, sizeof(int), &key_int, cmp_int);
    if (found_int){
        printf("Found int: %d\n", *found_int);
    }

    //double
    double arr_double[] = {1.1, 2.2, 3.3};
    double key_double = 2.2;
    double* found_double = linear_search(arr_double, 3, sizeof(double), &key_double, cmp_double);
    if (found_double){
        printf("Found double: %.1f\n", *found_double);
    }

    //char
    const char* str = "Hello World!";
    const char key_char = 'W';
    char* found_char = linear_search(str, strlen(str), sizeof(char), &key_char, cmp_char);
    if(found_char){
        printf("Found char: %c\n", *found_char);
    }

    //strings
    const char* arr_str[] = {"apple", "banana", "cherry"};
    const char* key_str = "banana";
    char** found_str = linear_search(arr_str, 3, sizeof(char*), &key_str, cmp_string);
    if (found_str){
        printf("Found string: %s\n", *found_str);
    }

    return 0;
}