//
// Created by Adrian on 2017/8/10.
//

#include "../Headers.h"
#include "Parttern/Channel.h"

using namespace std;


struct Data
{
    char b[1024] = {0};
    int i;

    Data(int i) : i(i) {}

    friend ostream &operator<<(ostream &os, const Data &data) {
        for (auto& v : data.b)
            os << "b: " << v << "i: " << data.i;
        return os;
    }
};

Channel<int> channel;

int main() {

    cout << "begin to channel 1000000+ times..." << endl;

    for (int i = 0; i < 500000; ++i)
        channel << i;

    thread t1([](){

        using namespace chrono;

        system_clock::time_point start = system_clock::now();

        int i = 0;
        while (true)
        {
            //cout << channel << endl;
            int n = *channel;
            i++;
            if (i >= 1000100)
                break;
        }


        system_clock::time_point end = system_clock::now();
        milliseconds ms = duration_cast<milliseconds>(end - start);

        cout << "thread finished at: " << ms.count() << "ms" << endl;

    });

    for (int i = 0; i < 500000; ++i)
        channel << i;


    this_thread::sleep_for(chrono::seconds(2));
    for (int i = 100; i < 200; ++i)
        channel << i;

    t1.join();


}
