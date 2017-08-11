//
// Created by Adrian on 2017/8/7.
//

#ifndef UNTITLED_CHANNEL_H
#define UNTITLED_CHANNEL_H

#include <mutex>
#include <list>
#include <ostream>

template <typename T>
class Channel
{
    std::mutex mtx;
    std::mutex mtxCheck;
    std::queue<T> q;

public:
    Channel()
    {
        mtxCheck.lock();
    }

    virtual ~Channel()
    {
        Close();
    }

    void Close()
    {
        mtxCheck.unlock();
    }

    void Write(const T& elem)
    {
        mtxCheck.unlock();

        std::lock_guard<std::mutex> lck(mtx);
        q.push(elem);

        mtxCheck.lock();
    }

    T Read()
    {
        {
            std::lock_guard<std::mutex> lck(mtx);
            if (q.empty()) {

                std::lock_guard<std::mutex> lckCheck(mtxCheck);
            }

        }

        std::lock_guard<std::mutex> lck(mtx);
        T elem = q.front();
        q.pop();

        return elem;
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> lck(mtx);
        return q.empty();
    }

    T operator * ()
    {
        return Read();
    }

    friend Channel& operator >> (Channel& channel, T& elem)
    {
        elem = channel.Read();
        return channel;
    }

    friend void operator << (Channel& channel, const T& elem)
    {
        channel.Write(elem);
    }

    friend std::ostream &operator<<(std::ostream &os, Channel &channel) {
        os << channel.Read();
        return os;
    }

};


#endif //UNTITLED_CHANNEL_H
