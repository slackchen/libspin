#include "Headers.h"

#if defined(__APPLE__)
#define _XOPEN_SOURCE
#endif

#include "Parttern/Coroutine.h"

using namespace std;

void test1(void* arg)
{
    CoroutinueContext& context = *(CoroutinueContext*)arg;

    cout << "Coroutine 1 before yield" << endl;

    context.Yield();

    cout << "Coroutine 1 after yield" << endl;

}

void test2(void* arg)
{
    CoroutinueContext& context = *(CoroutinueContext*)arg;

    cout << "Coroutine 2 before yield" << endl;

    context.Yield();

    cout << "Coroutine 2 after yield" << endl;

}

int main() {

    CoroutinueContext context;

    int c1 = context.Create(test1, &context);
    int c2 = context.Create(test2, &context);

    while (!context.Finished())
    {
        context.Resume(c1);
        context.Resume(c2);
    }


    cout << "Hello, World!" << endl;


    ostringstream str;
    str << "<li> </li>" << endl;
    cout << str.str();

    return 0;
}
