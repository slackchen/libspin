//
// Created by Adrian on 2017/8/10.
//

#ifndef UNTITLED_PROMISE_H
#define UNTITLED_PROMISE_H

enum class PromiseStatus
{
    Pending,
    Resolved,
    Rejected
};

template <typename TFunc>
class Promise
{
    TFunc func;

public:

    PromiseStatus status;

    Promise(TFunc func) : func(func), status(PromiseStatus::Pending) {}

    template <typename TSuccess, typename TFailure>
    Promise& Then(TSuccess success, TFailure failure)
    {
        std::thread thread1([=](){

            try
            {
                this->func(*this, success, failure);
                status = PromiseStatus::Resolved;
            }
            catch(...)
            {
                status = PromiseStatus::Rejected;
            }
        });

        thread1.join();

        this->func(*this, success, failure);

        return *this;
    }
};

template <typename TFunc>
auto make_promise(TFunc func)
{
    return Promise <TFunc>(func);
}

#endif //UNTITLED_PROMISE_H
