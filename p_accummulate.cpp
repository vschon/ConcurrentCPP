#include <iostream>
#include <thread>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

template<typename Iterator, typename T>
struct accumulate_block {
    void operator() (Iterator first, Iterator last, T& result) {
        result = accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T p_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = distance(first, last);
    if (length == 0)
        return init;

    unsigned long const minPerThread = 25;
    unsigned long const maxThread = (length + minPerThread - 1) / minPerThread;
    
    unsigned long const hardwareThread = thread::hardware_concurrency();
    unsigned long numThread;
    
    if (hardwareThread == 0)
        numThread = 2;
    else 
        numThread = (hardwareThread < maxThread? hardwareThread : maxThread);

    unsigned long const blockSize = length/numThread;

    vector<T> results(numThread);
    vector<thread> threads(numThread - 1);

    Iterator blockStart = first;

    for (unsigned long i = 0; i < (numThread - 1); i++) {
        Iterator blockEnd = blockStart;
        advance(blockEnd, blockSize);
        threads[i] = thread(accumulate_block<Iterator, T>(), 
                            blockStart, blockEnd, ref(results[i]));
        blockStart = blockEnd;
    }

    accumulate_block<Iterator, T>()(blockStart, last, results[numThread-1]);

    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
         
    return accumulate(results.begin(), results.end(), init);
    
}

int main() {


    vector<int> S;
    for(int i = 0; i < 1000; i++) {
        S.push_back(i);
    }

    int result = 0;

    result = p_accumulate<vector<int>::iterator, int>(S.begin(), S.end(), result);
    

    cout << result << endl;
    return 0;
}
