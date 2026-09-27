#include <iostream>

struct track {
    int p;
    int s;
    int ind;
};

bool IsLess(track* a, track* b) {
    if (a->p != b->p) {
        return a->p < b->p;
    }
    return a->s <= b->s;
}

void Merge(track* beg1, track* end1, track* beg2, track* end2, int sz) {
    track cur_mas[sz];

    track* ptr1 = beg1;
    track* ptr2 = beg2;
    int pos = 0;

    while (ptr1 < end1 && ptr2 < end2) {
        if (IsLess(ptr1, ptr2)) {
            cur_mas[pos] = *ptr1;
            ++ptr1;
        }
        else {
            cur_mas[pos] = *ptr2;
            ++ptr2;
        }
        ++pos;
    }

    while (ptr1 < end1) {
        cur_mas[pos] = *ptr1;
        ++ptr1;
        ++pos;
    }

    while (ptr2 < end2) {
        cur_mas[pos] = *ptr2;
        ++ptr2;
        ++pos;
    }

    for (int i = 0; i < sz; ++i) {
        *(beg1++) = cur_mas[i];
    }
}

void MergeSort(track* beg, track* end) {
    if (beg + 1 >= end) {//пустой массив или массив из одного элемента всегда отсортирован
        return;
    }
    int sz = end - beg;
    int mid = sz / 2;
    track* mid_ptr = beg + mid;
    MergeSort(beg, mid_ptr);
    MergeSort(mid_ptr, end);
    Merge(beg, mid_ptr, mid_ptr, end, sz);
}


int main() {
    int n; std::cin >> n;
    track mas[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> mas[i].p >> mas[i].s;
        mas[i].ind = i + 1;
    }

    track* beg = mas;
    track* end = beg + n;
    MergeSort(beg, end);

    for (int i = 0; i < n; ++i) {
        std::cout << mas[i].ind << ' ';
    }
    std::cout << '\n';
    return 0;
}