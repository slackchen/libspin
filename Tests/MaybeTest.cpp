//
// Created by Adrian on 2017/8/10.
//

#include "../Headers.h"
#include "Parttern/Maybe.h"

using namespace std;


struct Person
{
    string* name;
};

int main() {

    Person* p = new Person;
    p->name = new string("good boy");

    auto z = maybe(p)
            .With([](auto x) { return x->name; })
            .Do([](auto x) { cout << *x << endl; })
    ;

    return 0;
}
