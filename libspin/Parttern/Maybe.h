//
// Created by Adrian on 2017/8/10.
//

#ifndef UNTITLED_MAYBE_H
#define UNTITLED_MAYBE_H

template <typename T> struct Maybe;
template  <typename T> auto maybe(T* context)
{
    return Maybe<T>(context);
}

template  <typename T>
struct Maybe
{
    T* context;

    Maybe(T *context) : context(context) {}

    template <typename TFunc> auto With(TFunc evaluator)
    {
        return context != nullptr ? maybe(evaluator(context)) : nullptr;
    }

    template <typename Func> auto Do(Func action)
    {
        if (context != nullptr) action(context);
        return *this;
    }
};

#endif //UNTITLED_MAYBE_H
