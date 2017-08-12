//
// Created by Adrian on 2017/8/11.
//

#ifndef UNTITLED_COROUTINE_H
#define UNTITLED_COROUTINE_H

#ifdef __APPLE__
#define _XOPEN_SOURCE
#endif

#ifdef WIN32
	#include "ucontext.h"
#else
	#include <ucontext.h>
#endif

#include <vector>

enum class CoroutinueState
{
    Free,
    Runnable,
    Running,
    Suspend
};


class  CoroutineContext
{
public:
    typedef void (*Fun)(void *arg);

    struct CoroutineInfo;

    CoroutineContext();

    ~CoroutineContext();

    static void CoroutineCallback(CoroutineContext *cc);

    int  Create(Fun func, void *arg);

    void YieldReturn();

    void Resume(int id);

    int  Finished();

protected:
    ucontext_t main;
    int runningCoroutinue;
    int coroutineCount;
    std::vector<CoroutineInfo> coroutines;
};


#endif //UNTITLED_COROUTINE_H
