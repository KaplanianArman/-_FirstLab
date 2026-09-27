#include <iostream>

const int MAXN = 1'000'000;  // максимум n по условию
uint64_t ans = 0;
uint32_t arr[MAXN];

uint32_t cur = 0;              // текущее значение генератора

// Генератор 24-битных чисел по условию задачи
uint32_t nextRand24(uint32_t a, uint32_t b) {
    // 32-битные переполнения (uint32_t автоматически усекает до 2^32)
    cur = cur * a + b;
    return cur >> 8;  // берём старшие 24 бита (сдвиг вправо на 8)
}

void Merge(int l, int r, int mid, int sz) {
    int cur_mas[sz];
    int ptr1 = l, ptr2 = mid;
    int pos = 0;

    while (ptr1 < mid && ptr2 < r) {
        if (arr[ptr1] <= arr[ptr2]) {
            cur_mas[pos] = arr[ptr1];
            ++ptr1;
        }
        else {
            cur_mas[pos] = arr[ptr2];
            ans += mid - ptr1;
            ++ptr2;
        }
        ++pos;
    }

    while (ptr1 < mid) {
        cur_mas[pos] = arr[ptr1];
        ++ptr1;
        ++pos;
    }

    while (ptr2 < r) {
        cur_mas[pos] = arr[ptr2];
        ++ptr2;
        ++pos;
    }

    for (int i = 0; i < sz; ++i) {
        arr[l + i] = cur_mas[i];
    }
}

void MergeSort(int l, int r) {
    if (l + 1 >= r) {
        return;
    }
    int sz = r - l;
    int mid = (r + l) / 2;
    MergeSort(l, mid);
    MergeSort(mid, r);
    Merge(l, r, mid, sz);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, m, a, b;
    std::cin >> n >> m >> a >> b;

    // Генерируем n элементов
    for (uint32_t i = 0; i < n; i++) {
        uint32_t x = nextRand24(a, b) % m; // получаем 24-битное значение по модулю m
        arr[i] = x;                        // записываем в массив
    }
    MergeSort(0, n);
    std::cout << ans << '\n';
    return 0;
}