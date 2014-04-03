#include <thread>
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

void sayHello() {
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Hello!" << endl;
}
    


int main() {

    vector<int> S = {1, 2, 3};
    vector<int> S1 = move(S);
    cout << S.size() << endl;

    vector<int> S2 = static_cast<vector<int>&&>(S1);

    return 0;

}
    
