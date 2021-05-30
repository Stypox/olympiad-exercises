#include<bits/stdc++.h>

template<class Iter>
void heapsAlgorithm(Iter begin, Iter end, int size) {
    if (size == 1) {
        std::for_each(begin, end, [](auto a){ std::cout<<a<<" "; });
        std::cout<<"\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        heapsAlgorithm(begin, end, size - 1);
        std::swap(begin[size % 2 ? 0 : i], begin[size - 1]);
    }
}

template<class Iter>
void heapsAlgorithm(Iter begin, Iter end) {
    heapsAlgorithm<Iter>(begin, end, end-begin);
}

int main() {
    std::vector<int> arr{1,2,3,4,5};
    heapsAlgorithm(arr.begin(), arr.end());
}