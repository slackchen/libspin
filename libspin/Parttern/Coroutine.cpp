//
// Created by Adrian on 2017/8/11.
//

#include "Coroutine.h"

#define DEFAULT_STACK_SZIE (1024*128)
#define MAX_ROUTINUE_SIZE   1024

struct CoroutineContext::CoroutineInfo
{
    ucontext_t ctx;
    Fun func;
    void *arg;
    CoroutinueState state;
    char stack[DEFAULT_STACK_SZIE];
};

CoroutineContext::CoroutineContext()
    :runningCoroutinue(-1), coroutineCount(0)
    ,coroutines(MAX_ROUTINUE_SIZE)
{
    for (auto& c : coroutines)
        c.state = CoroutinueState::Free;
}

CoroutineContext::~CoroutineContext()
{
}

void CoroutineContext::Resume(int id)
{
    if(id < 0 || id >= coroutineCount){
        return;
    }

    CoroutineInfo& ci = coroutines[id];

    if (ci.state == CoroutinueState::Suspend) {
        swapcontext(&(main),&(ci.ctx));
    }
}

void CoroutineContext::YieldReturn()
{
    if(runningCoroutinue != -1 )
    {
        CoroutineInfo& ci = coroutines[runningCoroutinue];
        ci.state = CoroutinueState::Suspend;
        runningCoroutinue = -1;

        swapcontext(&(ci.ctx),&(main));
    }
}

void CoroutineContext::CoroutineCallback(CoroutineContext *cc)
{
    int id = cc->runningCoroutinue;

    if(id != -1){
        CoroutineInfo& ci = cc->coroutines[id];

        ci.func(ci.arg);

        ci.state = CoroutinueState::Free;

        cc->runningCoroutinue = -1;

		swapcontext(&(ci.ctx), &(cc->main));
    }
}

int CoroutineContext::Create(Fun func, void *arg)
{
    int id = 0;

    for(id = 0; id < coroutineCount; ++id )
    {
        if(coroutines[id].state == CoroutinueState::Free)
        {
            break;
        }
    }

    if (id == coroutineCount)
    {
        coroutineCount++;
    }

    CoroutineInfo& ci = coroutines[id];

    ci.state = CoroutinueState::Runnable;
    ci.func = func;
    ci.arg = arg;

    getcontext(&(ci.ctx));

    ci.ctx.uc_stack.ss_sp = ci.stack;
    ci.ctx.uc_stack.ss_size = DEFAULT_STACK_SZIE;
    ci.ctx.uc_stack.ss_flags = 0;
    ci.ctx.uc_link = &(main);
    runningCoroutinue = id;

    makecontext(&(ci.ctx), (void (*)(void)) (CoroutineCallback), 1, this);
    swapcontext(&(main), &(ci.ctx));

    return id;
}

int CoroutineContext::Finished()
{
    if (runningCoroutinue != -1)
    {
        return 0;
    }
    else
    {
        for(int i = 0; i < coroutineCount; ++i){
            if(coroutines[i].state != CoroutinueState::Free){
                return 0;
            }
        }
    }

    return 1;
}