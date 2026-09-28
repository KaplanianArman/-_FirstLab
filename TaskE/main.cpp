#include <iostream>

const int MAXN = 10'000'000;
uint32_t arr[MAXN];

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

struct partition {
    int ind_left;
    int ind_right;
};

int GetMedianInd(int l, int mid, int r) {
    uint32_t a = arr[l], b = arr[mid], c = arr[r];
    if (a > b) {
        if (b > c) {//a > b > c
            return mid;
        }
        if (a > c) {//a > c >= b
            return r;
        }
        else {//c >= a > b
            return l;
        }
    }
    else {
        if (a > c) {//b >= a > c 
            return l;
        }
        if (b > c) {//b > c >= a
            return r;
        }
        else {//c >= b >= a
            return mid;
        }
    }
}

partition LomutoPartition(int l, int r) {
    int mid = (l + r) / 2;
    int pivot_ind = GetMedianInd(l, mid, r - 1);
    uint32_t pivot = arr[pivot_ind];
    std::swap(arr[pivot_ind], arr[r - 1]);
    int i = l;
    for (int j = l; j < r - 1; ++j) {
        if (arr[j] < pivot) {
            std::swap(arr[j], arr[i]);
            ++i;
        }
    }
    std::swap(arr[i], arr[r - 1]);
    int j = i + 1;
    for (int k = j; k < r; ++k) {
        if (arr[k] == pivot) {
            std::swap(arr[j], arr[k]);
            ++j;
        }
    }
    return {i, j - 1};
}

uint32_t GetFirstK(int l, int r, uint32_t k) {
    partition q = LomutoPartition(l, r);
    int ind_left = q.ind_left, ind_right = q.ind_right;

    int cnt_left = ind_left - l;
    int cnt_left_and_mid = ind_right + 1 - l;

    if (cnt_left >= k) return GetFirstK(l, ind_left, k);
    else if (cnt_left_and_mid >= k) return arr[ind_left];
    return GetFirstK(ind_right + 1, r, k - cnt_left_and_mid);
}



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, k, a, b;
    std::cin >> n >> k >> a >> b;

    for (uint32_t i = 0; i < n; i++) {
        arr[i] = nextRand32(a, b);  // генерируем i-й элемент
    }
    
    std::cout << GetFirstK(0, n, k) << '\n';
    return 0;
}