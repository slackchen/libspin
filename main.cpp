#include "Headers.h"

using namespace std;

int main() {

    cout << "Hello, World!" << endl;

    ostringstream str;
    str << "<li> </li>" << endl;
    cout << str.str();

    return 0;
}
