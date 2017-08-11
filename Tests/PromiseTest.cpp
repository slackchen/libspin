//
// Created by Adrian on 2017/8/10.
//

#include "../Headers.h"
#include "Parttern/Promise.h"

using namespace std;

int main() {

    auto promise = make_promise([](auto promise, auto success, auto failure){
        if (promise.status == PromiseStatus::Resolved)
        {
            for (int i = 0; i < 1000; ++i)
            {
                cout << i << endl;
            }

            success(1);
        } else
        {
            failure(2);
        }
    });

    promise.Then([](int value){

        // success
        cout << "success: " << value << endl;

    }, [](int value){

        // failure
        cout << "failure: " << value << endl;
    });

    return 0;
}

