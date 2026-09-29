#include <iostream>

int POW10[10];//массив степеней десятки для вычисления текущего разряда

const int MAXN = 50'000;
uint32_t arr[MAXN], cur_mas[MAXN];

uint64_t ans = 0;//переменная для ответа на текущий запрос

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

uint32_t n;
int CNT[10] = {0};

void LSD(int D) {
    for (int d = 1; d <= D; ++d) {
        for (int i = 0; i < n; ++i) {
            int cur_digit = (arr[i] / POW10[d - 1]) % 10;
            CNT[cur_digit]++;
        }

        for (int i = 1; i <= 9; ++i) CNT[i] += CNT[i - 1];

        for (int i = n - 1; i >= 0; --i) {
            int cur_digit = (arr[i] / POW10[d - 1]) % 10;
            int pos = CNT[cur_digit] - 1;
            cur_mas[pos] = arr[i];
            CNT[cur_digit]--;
        }

        for (int i = 0; i < n; ++i) {
            arr[i] = cur_mas[i];
        }

        for (int i = 0; i <= 9; ++i) CNT[i] = 0;
    }
    for (int i = 0; i < n; ++i) ans += 1LL * (i + 1) * arr[i];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    POW10[0] = 1;
    for (int i = 1; i <= 9; ++i) {
        POW10[i] = POW10[i - 1] * 10;
    }
    
    int t; 
    uint32_t a, b;
    std::cin >> t >> n >> a >> b;
    while (t--) {
        uint32_t mx = 0;
        for (int i = 0; i < n; ++i) {
            arr[i] = nextRand32(a, b);
            mx = std::max(mx, arr[i]);
        }
        
        ans = 0;

        int D = 1;
        while (D < 10 && mx / POW10[D] != 0) D++;
        LSD(D);
        std::cout << ans << '\n';
    }
    return 0;
}