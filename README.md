# libspin
自旋库是基于现代c++设计模式而产生的，目的是为了帮助c++生产者在更高层次进行设计开发，从而提供更好的抽象服务，提高项目开发效率。

# 代码示例
- Promise

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

# 写在最后
如果喜欢请star，联系方式：
email:whitespace@163.com
