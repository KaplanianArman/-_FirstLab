#include <iostream>

int POW10[10];
int CNT[10];

const int MAXN = 50'000;
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



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    POW10[0] = 1;
    for (int i = 1; i <= 9; ++i) {
        POW10[i] = POW10[i - 1] * 10;
    }

    int t; std::cin >> t;
    while (t--) {
        int n, a, b; std::cin >> n >> a >> b;
        for (int i = 0; i < n; ++i) {
            arr[i] = nextRand32(a, b);
        }
        
    }
    

    return 0;
}