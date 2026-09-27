#include <iostream>

int mas[100'000];

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

int HoarePartition(int l, int r) {
    int a = mas[l], b = mas[(l + r) / 2], c = mas[r];
    int pivot = GetMedian(a, b, c);
    int i = l - 1, j = r + 1;
    while (true) {
        ++i;
        while (mas[i] < pivot) {
            ++i;
        }

        --j;
        while (mas[j] > pivot) {
            --j;
        }
        if (i >= j) {
            return j;
        }
        std::swap(mas[i], mas[j]);
    }
}

void QuickSort(int l, int r) {
    if (l >= r) {
        return;
    }
    int q = HoarePartition(l, r);
    QuickSort(l, q);
    QuickSort(q + 1, r);
}

int main() {
    int n; std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> mas[i];
    }

    QuickSort(0, n - 1);
    for (int i = 0; i < n; ++i) {
        std::cout << mas[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}