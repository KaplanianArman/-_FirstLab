#include <iostream>

int POW10[10];//массив степеней десятки для вычисления текущего разряда

const int MAXN = 50'000;
uint32_t arr[MAXN];

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

void MSD(int l, int r, int d) {
    if (d == 0) {
        for (int i = l; i < r; ++i) {
            ans += 1LL * (i + 1) * arr[i];
        }
        return;
    }

    int CNT[10] = {0};

    int n = r - l;//количество элементов arr[l;r)
    int cur_mas[n], cur_mas_digit[n];//вспомогательные массивы

    for (int i = l; i < r; ++i) {//подсчет цифр
        int cur_digit = (arr[i] / POW10[d - 1]) % 10;
        cur_mas_digit[i - l] = cur_digit;
        CNT[cur_digit]++;
    }

    for (int i = 1; i <= 9; ++i) CNT[i] += CNT[i - 1];//считаем префиксные суммы

    for (int i = n - 1; i >= 0; --i) {
        int cur_digit = cur_mas_digit[i];

        int pos_in_cur_mas = CNT[cur_digit] - 1;//индекс куда нужно поставить элемент при сортировке по d
        int pos_in_arr = i + l;//индекс, на котором находится ИСХОДНОЕ число в arr

        cur_mas[pos_in_cur_mas] = arr[pos_in_arr];

        CNT[cur_digit]--;
    }

    //переносим данные в исходный массив
    for (int i = l; i < r; ++i) arr[i] = cur_mas[i - l];

    //заново считаем префиксные суммы
    for (int i = 0; i <= 9; ++i) CNT[i] = 0;
    for (int i = 0; i < n; ++i) CNT[cur_mas_digit[i]]++;
    for (int i = 1; i <= 9; ++i) CNT[i] += CNT[i - 1];

    for (int i = 0; i <= 9; ++i) {
        int left = (i ? CNT[i - 1] : 0);
        int cnt = CNT[i] - left;//колличество элементов, у которых разряд d равен i
        
        if (cnt == 1) {//элемент уже стоит на своем месте в отсортированном массиве
            int pos_in_arr = CNT[i] + l - 1;
            ans += 1LL * arr[pos_in_arr] * (pos_in_arr + 1);
        }
        else if (cnt > 1) {//разряд совпадает, нужно отсортировать для них по разряду меньше на единицу
            MSD(left + l, CNT[i] + l, d - 1);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    POW10[0] = 1;
    for (int i = 1; i <= 9; ++i) {
        POW10[i] = POW10[i - 1] * 10;
    }
    
    int t; 
    uint32_t n, a, b;
    std::cin >> t >> n >> a >> b;
    while (t--) {
        uint32_t mx = 0;
        for (int i = 0; i < n; ++i) {
            arr[i] = nextRand32(a, b);
            mx = std::max(mx, arr[i]);
        }

        int d = 1;
        while (d < 10 && mx / POW10[d] != 0) d++;
        ans = 0;
        MSD(0, n, d);
        std::cout << ans << '\n';
    }
    return 0;
}