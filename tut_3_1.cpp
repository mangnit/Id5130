#include <iostream>
#include <vector>

using namespace std;

const size_t num = 1e7 + 8;
vector<bool> v(num, false);

void cross_multiples(size_t k) {
    // pragma omp parllel for
    for (size_t i = k * k; i < num; i += k) {
        v[i] = true;
    }
}

int main() {

    vector<size_t> sol;

    for (size_t i = 2; i < num; i++) {
        if (!v[i]) {
            sol.push_back(i);

            if (i * i < num)
                cross_multiples(i);
        }
    }

    for (auto p : sol) {
        cout << p << '\n';
    }
}
