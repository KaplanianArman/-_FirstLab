#include <iostream>

uint32_t cur = 0;  // беззнаковое 32-битное число

// Генератор 24-битного числа
uint32_t nextRand24(uint32_t a, uint32_t b) {
    cur = cur * a + b;      // вычисляется с переполнениями по модулю 2^32
    return cur >> 8;         // число от 0 до 2^24 - 1
}

// Генератор 32-битного числа на основе двух 24-битных
uint32_t nextRand32(uint32_t a, uint32_t b) {
    uint32_t x = nextRand24(a, b);
    uint32_t y = nextRand24(a, b);
    return (x << 8) ^ y;     // число от 0 до 2^32 - 1
}

uint32_t* GetMedian(uint32_t* a, uint32_t* b, uint32_t* c) {
    uint32_t a_val = *a;
    uint32_t b_val = *b;
    uint32_t c_val = *c;
    if (a_val > b_val) {
        if (b_val > c_val) {//a > b > c
            return b;
        }
        if (a_val > c_val) {//a > c >= b
            return c;
        }
        else {//c >= a > b;
            return a;
        }
    }
    else {
        if (a_val > c_val) {//b >= a > c
            return a;
        }
        else if (b_val > c_val) {//b > c >= a
            return c;
        }
        else {//c >= b >= a
            return b;
        }
    }
}

uint32_t* LomutoPartition(uint32_t* beg, uint32_t* end) {
    uint32_t sz = end - beg;
    uint32_t mid = sz / 2;
    uint32_t* mid_ptr = beg + mid;
    uint32_t* pivot_ptr = GetMedian(beg, mid_ptr, end - 1);
    uint32_t pivot = *pivot_ptr;
    std::swap(*pivot_ptr, *(end - 1));

    uint32_t* i = beg - 1;
    while (beg + 1 < end) {
        if (*beg < pivot) {
            ++i;
            std::swap(*i, *beg);
        }
        ++beg;
    }
    std::swap(*i, *(end - 1));
    return i;
}

int FindIndexK(uint32_t* beg, uint32_t* end, uint32_t k) {
    uint32_t* q = LomutoPartition(beg, end);
    uint32_t cnt_left = q - beg - 1;
    if (cnt_left + 1 == k) {
        return *q;
    }
    if (cnt_left > k) {
        return FindIndexK(beg, q, k);
    }
    return FindIndexK(q + 1, end, k);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, k, a, b;
    std::cin >> n >> k >> a >> b;

    uint32_t arr[n];

    for (uint32_t i = 0; i < n; i++) {
        arr[i] = nextRand32(a, b);  // генерируем i-й элемент
    }

    uint32_t *beg = arr;
    uint32_t *end = beg + n;
    for (int i = 0; i < n; ++i) std::cout << arr[i] << ' ';
    std::cout << '\n';
    std::cout << FindIndexK(beg, end, k) << '\n';
    /*
    12 130926 3941054950 2013898548 197852696 2753287507 2013898548
    12 130926 197852696 2013898548 2013898548 2753287507 3941054950
    */
    return 0;
}