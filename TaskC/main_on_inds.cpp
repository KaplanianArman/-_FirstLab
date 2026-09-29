#include <iostream>

const int MAXN = 100'000;

struct track {
    int p;
    int s;
    int ind;
};

track arr[MAXN];

bool IsLessOrEquil(int i, int j) {
    if (arr[i].p != arr[j].p) return arr[i].p < arr[j].p;
    return arr[i].s <= arr[j].s;
}

void Merge(int l, int r) {
    int sz = r - l;
    track cur_mas[sz];

    int mid = (l + r) / 2;
    int ptr1 = l, ptr2 = mid;
    int pos = 0;

    while (ptr1 < mid && ptr2 < r) {
        if (IsLessOrEquil(ptr1, ptr2)) {
            cur_mas[pos] = arr[ptr1];
            ++ptr1;
        }
        else {
            cur_mas[pos] = arr[ptr2];
            ++ptr2;
        }
        ++pos;
    }

    while (ptr1 < mid) {
        cur_mas[pos] = arr[ptr1];
        ++ptr1; ++pos;
    }

    while (ptr2 < r) {
        cur_mas[pos] = arr[ptr2];
        ++ptr2; ++pos;
    }

    for (int i = 0; i < sz; ++i) {
        arr[i + l] = cur_mas[i];
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
        std::cin >> arr[i].p >> arr[i].s;
        arr[i].ind = i + 1;
    }
    MergeSort(0, n);
    for (int i = 0; i < n; ++i) std::cout << arr[i].ind << ' ';
    std::cout << '\n';
    
    return 0;
}