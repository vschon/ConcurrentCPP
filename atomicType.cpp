#include <memory>
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

using namespace std;

class spinlock_mutex {
private:
    atomic_flag flag;
public:
    spinlock_mutex():
        flag(ATOMIC_FLAG_INIT)
    {}
    void lock() {
        while(flag.test_and_set(memory_order_acquire));
    }

    void unlock() {
        flag.clear(memory_order_release);
    }

};

spinlock_mutex m;

void f(int n) {
    for(int count = 0; count < 5; count++) {
    m.lock();
    cout << "Out put from thread " << n << " : " << count << "\n";
    m.unlock();
    }
}
    

int main() {
    vector<thread> v;
    for(int n = 0; n < 10; ++n) {
        v.emplace_back(f, n);
    }
    
    for(auto& t: v) {
        t.join();
    }
    
    return 0;
}
