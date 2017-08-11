//
// Created by Adrian on 2017/8/11.
//

#ifndef UNTITLED_COROUTINE_H
#define UNTITLED_COROUTINE_H

#ifdef __APPLE__
#define _XOPEN_SOURCE
#endif

#include <ucontext.h>
#include <vector>

enum class CoroutinueState
{
    Free,
    Runnable,
    Running,
    Suspend
};


class  CoroutinueContext
{
public:
    typedef void (*Fun)(void *arg);

    struct CoroutinueInfo;

    CoroutinueContext();

    ~CoroutinueContext();

    static void CoroutinueThread(CoroutinueContext *cc);

    int  Create(Fun func, void *arg);

    void Yield();

    void Resume(int id);

    int  Finished();

protected:
    ucontext_t main;
    int runningCoroutinue;
    int coroutinueCount;
    std::vector<CoroutinueInfo> coroutinues;
};


#endif //UNTITLED_COROUTINE_H
