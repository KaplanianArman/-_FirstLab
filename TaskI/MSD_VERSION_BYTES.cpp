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

const int MAXN = 50'000;
const int ALPH_SIZE = 256;
uint32_t arr[MAXN], cur_arr[MAXN];

uint64_t ans = 0;

void MSD(int l, int r, int d) {
    int sz = r - l;
    if (sz <= 32 || d == 0) {
        for (int i = l + 1; i < r; ++i) {
            uint32_t cur = arr[i];
            int j = i - 1;
            while (j >= l && arr[j] > cur) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = cur;
        }

        for (int i = l; i < r; ++i) {
            ans += 1LL * (i + 1) * arr[i];
        }
        return;
    }

    int CNT[ALPH_SIZE]{}, TMP[ALPH_SIZE]{};
    for (int i = l; i < r; ++i) {
        int cur_byte = (arr[i] >> ((d - 1) * 8));
        cur_byte &= 255;
        TMP[cur_byte]++;
    }

    CNT[0] = TMP[0];
    for (int i = 1; i < ALPH_SIZE; ++i) {
        TMP[i] += TMP[i - 1];
        CNT[i] = TMP[i];
    }

    for (int i = sz - 1; i >= 0; --i) {
        int pos_in_arr = i + l;

        int cur_byte = (arr[pos_in_arr] >> ((d - 1) * 8));
        cur_byte &= 255;

        int pos_in_cur_arr = CNT[cur_byte] - 1;

        cur_arr[pos_in_cur_arr] = arr[pos_in_arr];

        CNT[cur_byte]--;
    }

    for (int i = 0; i < sz; ++i) arr[l + i] = cur_arr[i];

    for (int i = 0; i < ALPH_SIZE; ++i) {
        int left = (i ? TMP[i - 1] : 0);
        int cur_cnt = TMP[i] - left;
        if (cur_cnt > 0) MSD(left + l, TMP[i] + l, d - 1);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

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
        while (d < 4 && (mx >> ((d - 1) * 8)) != 0) d++;

        ans = 0;
        MSD(0, n, d);
        std::cout << ans << '\n';
    }
    return 0;
}