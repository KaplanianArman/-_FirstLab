#include <iostream>

int GetMedian(int a, int b, int c) {
    if (a > b) {
        if (b > c) {//a > b > c
            return b;
        }
        if (a > c) {//a > c >= b
            return c;
        }
        else {//c >= a > b
            return a;
        }
    }
    else {
        if (a > c) {//b >= a > c 
            return a;
        }
        if (b > c) {//b > c >= a
            return c;
        }
        else {//c >= b >= a
            return b;
        }
    }
}

int* HoarePartition(int* beg, int* end) {
    int sz = end - beg;
    int mid = sz / 2;
    int* mid_ptr = beg + mid - 1;
    int pivot = GetMedian(*beg, *mid_ptr, *(end - 1));

    int* i = beg - 1;
    int* j = end;

    while (true) {
        i++;
        while (*i < pivot) {
            i++;
        }

        j--;
        while (*j > pivot) {
            j--;
        }

        if (i >= j) {
            return j;
        }
        
        std::swap(*i, *j);
    }
}

void QuickSort(int* beg, int* end) {
    if (beg + 1 >= end) {
        return;
    }

    int* q = HoarePartition(beg, end);
    QuickSort(beg, q + 1);
    QuickSort(q + 1, end);
}

int main() {
    int n; std::cin >> n;
    int mas[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> mas[i];
    }

    int* beg = mas;
    int* end = beg + n;
    QuickSort(beg, end);

    for (int i = 0; i < n; ++i) {
        std::cout << mas[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}