#include <iostream>

const int MAXN = 500'001;
const int INF = 1'000'000'001;

int X[MAXN], Y[MAXN], INDS[MAXN];
int InS[MAXN] = {0};

bool IsLessOrEquil(int a, int b) {
    if (X[a] != X[b]) return X[a] <= X[b];
    return Y[a] <= Y[b];
}

void Merge(int l, int r) {
    int sz = r - l;
    int mid = (l + r) / 2;

    int cur_mas_x[sz];
    int cur_mas_y[sz];
    int cur_mas_inds[sz];

    int ptr1 = l, ptr2 = mid;
    int pos = 0;

    while (ptr1 < mid && ptr2 < r) {
        if (IsLessOrEquil(ptr1, ptr2)) {
            cur_mas_x[pos] = X[ptr1];
            cur_mas_y[pos] = Y[ptr1];
            cur_mas_inds[pos] = INDS[ptr1];
            ++ptr1;
        }
        else {
            cur_mas_x[pos] = X[ptr2];
            cur_mas_y[pos] = Y[ptr2];
            cur_mas_inds[pos] = INDS[ptr2];
            ++ptr2;
        }
        ++pos;
    }

    while (ptr1 < mid) {
        cur_mas_x[pos] = X[ptr1];
        cur_mas_y[pos] = Y[ptr1];
        cur_mas_inds[pos] = INDS[ptr1];
        ++ptr1;
        ++pos;
    }

    while (ptr2 < r) {
        cur_mas_x[pos] = X[ptr2];
        cur_mas_y[pos] = Y[ptr2];
        cur_mas_inds[pos] = INDS[ptr2];
        ++ptr2;
        ++pos;
    }

    for (int i = 0; i < sz; ++i) {
        X[l + i] = cur_mas_x[i];
        Y[l + i] = cur_mas_y[i];
        INDS[l + i] = cur_mas_inds[i];
    }
}

void MergeSort(int l, int r) {
    if (l + 1 >= r) return;
    int mid = (l + r) / 2;
    MergeSort(l, mid);
    MergeSort(mid, r);
    Merge(l, r);
}

int main() {
    int n; std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> X[i] >> Y[i];
        INDS[i] = i + 1;
    }
    MergeSort(0, n);
    int k = 0;
    int mx_x = -INF, mx_y = -INF;
    for (int i = n - 1; i >= 0; --i) {
        if (X[i] > mx_x || Y[i] > mx_y) {
            ++k; InS[INDS[i]] = 1;
            mx_x = std::max(mx_x, X[i]);
            mx_y = std::max(mx_y, Y[i]);
        }
    }

    std::cout << k << '\n';
    for (int i = 0; i <= n; ++i) {
        if (InS[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}