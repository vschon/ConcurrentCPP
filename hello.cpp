#include <thread>
#include <iostream>

using namespace std;

void sayHello() {
    cout << "Hello!" << endl;
}


int main() {
    thread t(sayHello);
    t.join();
    return 0;

}
    
