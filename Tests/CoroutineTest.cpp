//
// Created by Adrian on 2017/8/12.
//

#include "../Headers.h"
#include "Parttern/Coroutine.h"

using namespace std;

void test1(void* arg)
{
    CoroutineContext& context = *(CoroutineContext*)arg;

    cout << "Coroutine 1 before yield" << endl;

    context.YieldReturn();

    cout << "Coroutine 1 after yield" << endl;

}

void test2(void* arg)
{
    CoroutineContext& context = *(CoroutineContext*)arg;

    cout << "Coroutine 2 before yield" << endl;

    context.YieldReturn();

    cout << "Coroutine 2 after yield" << endl;

}

int main() {

    CoroutineContext context;

    int c1 = context.Create(test1, &context);
    int c2 = context.Create(test2, &context);

    while (!context.Finished())
    {
        context.Resume(c1);
        context.Resume(c2);
    }

    return 0;
}
