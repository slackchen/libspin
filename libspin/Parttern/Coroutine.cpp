//
// Created by Adrian on 2017/8/11.
//

#include "Coroutine.h"

#define DEFAULT_STACK_SZIE (1024*128)
#define MAX_ROUTINUE_SIZE   1024

struct CoroutinueContext::CoroutinueInfo
{
    ucontext_t ctx;
    Fun func;
    void *arg;
    CoroutinueState state;
    char stack[DEFAULT_STACK_SZIE];
};

CoroutinueContext::CoroutinueContext()
    :runningCoroutinue(-1), coroutinueCount(0)
    ,coroutinues(MAX_ROUTINUE_SIZE)
{
    for (auto& c : coroutinues)
        c.state = CoroutinueState::Free;
}

CoroutinueContext::~CoroutinueContext()
{
}

void CoroutinueContext::Resume(int id)
{
    if(id < 0 || id >= coroutinueCount){
        return;
    }

    CoroutinueInfo& ci = coroutinues[id];

    if (ci.state == CoroutinueState::Suspend) {
        swapcontext(&(main),&(ci.ctx));
    }
}

void CoroutinueContext::YieldReturn()
{
    if(runningCoroutinue != -1 )
    {
        CoroutinueInfo& ci = coroutinues[runningCoroutinue];
        ci.state = CoroutinueState::Suspend;
        runningCoroutinue = -1;

        swapcontext(&(ci.ctx),&(main));
    }
}

void CoroutinueContext::CoroutinueThread(CoroutinueContext *cc)
{
    int id = cc->runningCoroutinue;

    if(id != -1){
        CoroutinueInfo& ci = cc->coroutinues[id];

        ci.func(ci.arg);

        ci.state = CoroutinueState::Free;

        cc->runningCoroutinue = -1;

		swapcontext(&(ci.ctx), &(cc->main));
    }
}

int CoroutinueContext::Create(Fun func, void *arg)
{
    int id = 0;

    for(id = 0; id < coroutinueCount; ++id )
    {
        if(coroutinues[id].state == CoroutinueState::Free)
        {
            break;
        }
    }

    if (id == coroutinueCount)
    {
        coroutinueCount++;
    }

    CoroutinueInfo& ci = coroutinues[id];

    ci.state = CoroutinueState::Runnable;
    ci.func = func;
    ci.arg = arg;

    getcontext(&(ci.ctx));

    ci.ctx.uc_stack.ss_sp = ci.stack;
    ci.ctx.uc_stack.ss_size = DEFAULT_STACK_SZIE;
    ci.ctx.uc_stack.ss_flags = 0;
    ci.ctx.uc_link = &(main);
    runningCoroutinue = id;

    makecontext(&(ci.ctx), (void (*)(void)) (CoroutinueThread), 1, this);
    swapcontext(&(main), &(ci.ctx));

    return id;
}

int CoroutinueContext::Finished()
{
    if (runningCoroutinue != -1)
    {
        return 0;
    }
    else
    {
        for(int i = 0; i < coroutinueCount; ++i){
            if(coroutinues[i].state != CoroutinueState::Free){
                return 0;
            }
        }
    }

    return 1;
}