#include <iostream>

int main() {
    int n; std::cin >> n;
    int c[101] = {0};
    int used[101] = {0};

    for (int i = 0; i < n; ++i) {
        int cur; std::cin >> cur;
        for (int j = cur + 1; j <= 100; ++j) c[j]++;
        std::cout << c[cur] + used[cur] << ' ';
        used[cur]++;
    }
    std::cout << '\n';
    return 0;
}