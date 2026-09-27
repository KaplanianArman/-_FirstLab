#include <iostream>

int main() {
    int n; std::cin >> n;
    int mas[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> mas[i];
    }

    int ans = 0;
    for (int i = 1; i < n; ++i) {
        int cur = mas[i];
        int j = i - 1;
        while (j >= 0 && ++ans && mas[j] > cur) {
            mas[j + 1] = mas[j];
            j--;
        }
        ++j;
        mas[j] = cur;
    }
    std::cout << ans << '\n';
    return 0;
}