#include <iostream>
template <typename T>
struct Comparator
{
    virtual bool operator()(T const &, T const &) const = 0;
};

struct IntComparator final : Comparator<int>
{
    bool operator()(int const &lha, int const &rha) const override
    {
        return lha < rha;
    }
};
template <typename T>
void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename Element>
void qsort(Element *arr, int left, int right, Comparator<Element> &compare) // сортировка
{
    if (left < right)
    {
        int pos = (left + right) / 2;
        Element opor = arr[(left + right) / 2];
        int i = left, j = right;
        while (true)
        {
            while (compare(arr[i], opor))
            {
                i++;
            }
            while (compare(opor, arr[j]))
            {
                j--;
            }
            if (i >= j)
            {
                pos = j;
                break;
            }

            swap(arr[i], arr[j]);
            ++i;
            --j;
        }
        qsort(arr, left, pos, compare);
        qsort(arr, pos + 1, right, compare);
    }
}
int main()
{
    IntComparator compare;
    int mas[] = {1, 7, 5, 4, 3};
    qsort(mas, 0, 4, compare);
    for (int i = 0; i < 5; ++i)
    {
        std::cout << mas[i] << " ";
    }
    return 0;
}
