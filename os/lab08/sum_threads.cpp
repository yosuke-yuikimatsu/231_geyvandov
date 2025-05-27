#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <random>
#include <ctime>

static long long sum = 0;
static std::mutex mtx;

void worker(const std::vector<int>& a, int start, int len) {
    long long local = 0;
    for (int i = 0; i < len; ++i) local += a[start + i];
    std::lock_guard<std::mutex> lg(mtx);
    sum += local;
}

int main() {
    int N;
    if (!(std::cin >> N) || N < 16) return 1;

    std::vector<int> a(N);
    std::mt19937 rng((unsigned)std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 999);
    for (int& x : a) x = dist(rng);

    std::cout << "Array:";
    for (int x : a) std::cout << ' ' << x;
    std::cout << '\n';

    int base = N / 4;
    int rem = N % 4;
    int idx = 0;
    std::thread th[4];
    for (int i = 0; i < 4; ++i) {
        int len = base + (i < rem);
        th[i] = std::thread(worker, std::cref(a), idx, len);
        idx += len;
    }
    for (auto& t : th) t.join();

    std::cout << "Total sum: " << sum << '\n';
    return 0;
}
