#include <stdexcept>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

mutex m;

void printEven(int x) {
    if (x%2==0) cout << x << " is even \n";
    else throw (logic_error("not even"));
}

void printThreadID(int id) {
    try {
        m.lock();
        printEven(id);
    }
    catch (logic_error&) {
        cout << "[exception caught]\n";
    }
    m.lock();//or use a lock_guard
}

int main() {
    vector<thread> S;
    for (int i = 0; i < 10; i++) {
        S.push_back(thread(printThreadID, i + 1));
    }

    for (auto& th: S) th.join();
    return 0;
}
