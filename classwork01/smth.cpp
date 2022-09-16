#include <assert.h>
#include <stdio.h>
#include <cstring>
#include <float.h>
#include <iostream>

void* min(void* arr, int arr_size, int type_size, int (*compare)(const void *, const void *)) {
    if (arr_size == 0) return arr;

    void* cur_min = arr;
    arr_size--;

    for (; arr_size > 0; --arr_size) {
        if (compare(cur_min, (char*)arr + type_size * arr_size) < 0) {
            cur_min = (char*)arr + type_size * arr_size;
        }
    }
    return cur_min;
}

void my_swap(void* lft, void* rht, int type_size) {
    if (lft == NULL || rht == NULL) return;

    void* tmp_mem = malloc(type_size);

    memcpy(tmp_mem, lft    , type_size);
    memcpy(lft    , rht    , type_size);
    memcpy(rht    , tmp_mem, type_size);
    free(tmp_mem);

    return;
}


void myQsort (void* _Base, 
              size_t _NumOfElements, 
              size_t _SizeOfElements, 
              int _CompareFunction(void const*, void const*))
{
    if (_NumOfElements <= 1)
        return;
    
    char *l   = (char *)_Base;
    char *r   = (char *)_Base + (_NumOfElements - 1) * _SizeOfElements;
    char *piv = (char *)_Base + (_NumOfElements / 2) * _SizeOfElements;

    while (l <= r)
    {
        while (_CompareFunction(l, piv) < 0)
            l += _SizeOfElements;
        while (_CompareFunction(r, piv) > 0)
            r -= _SizeOfElements;
        
        if (l <= r)
        {
            if (piv == l)
                piv = r;
            else if (piv == r)
                piv = l;
            
            my_swap(l, r, _SizeOfElements);

            l += _SizeOfElements;
            r -= _SizeOfElements;
        }
    }

    int left_length  = (r - (char*)_Base)/_SizeOfElements + 1;
    int right_length = ((char*)_Base + _SizeOfElements*_NumOfElements - l)/_SizeOfElements; 
    
    myQsort(_Base, left_length,  _SizeOfElements, _CompareFunction);
    myQsort(l,     right_length, _SizeOfElements, _CompareFunction);
}


int min_cmp(const void* lft, const void* rht) {
    return *(int*)lft - *(int*)rht; 
}

int max_cmp(const void* lft, const void* rht) {
    return *(int*)rht - *(int*)lft; 
}

int min_odd_even_cmp(const void* lft, const void* rht) {
    const int* lft_ = (const int*) lft;
    const int* rht_ = (const int*) rht;

    if ((*lft_ & 1) == (*rht_ & 1)) {
        return *lft_ - *rht_; 
    }

    return -1 * (*lft_ & 1) + 1 * (*rht_ & 1);
}


void print_base_type_size() {
    std::cout << 8 * sizeof(char)      << "sizeof(char),     \t max val:\t" <<  CHAR_MAX   << "\t\t\t\t, min val: " << CHAR_MIN  <<  "\n";
    std::cout << 8 * sizeof(short int) << "sizeof(short int),\t max val:\t" <<  INT16_MAX  << "\t\t\t\t, min val: " << INT16_MIN <<  "\n";
    std::cout << 8 * sizeof(int)       << "sizeof(int),      \t max val:\t" <<  INTMAX_MAX << "\t\t\t\t, min val: " << INT_MIN   <<  "\n";
    std::cout << 8 * sizeof(long int)  << "sizeof(long int), \t max val:\t" <<  INT32_MAX  << "\t\t\t\t, min val: " << INT32_MIN <<  "\n";
    std::cout << 8 * sizeof(float)     << "sizeof(float),    \t max val:\t" <<  FLT_MAX    << "\t\t\t\t, min val: " << FLT_MIN   <<  "\n";
    std::cout << 8 * sizeof(double)    << "sizeof(double),   \t max val:\t" <<  DBL_MAX    << "\t\t\t\t, min val: " << DBL_MIN   <<  "\n";
    return;
}


int main() {
    
    int (*cmp_func_arr[])(void const*, void const*) = {
        min_cmp,
        max_cmp,
        min_odd_even_cmp
    };

    //test qsort functions
    int abc[10] = {10, 9, 8, 7, 9, 5, 15, 3, 2, 1};

    for (int it = 0; it < 10; ++it) {
        std::cout << abc[it];
    }
    std::cout << "not sorted\n";

    for (size_t func_num = 0; func_num < sizeof(cmp_func_arr) / sizeof(cmp_func_arr[0]); ++func_num) {
        myQsort(abc, 10, sizeof(int), cmp_func_arr[func_num]);
        for (int it = 0; it < 10; ++it) {
            std::cout << abc[it];
        }
        std::cout << '\n';
    }

    //print size of base types
    print_base_type_size();

    return 0;
}