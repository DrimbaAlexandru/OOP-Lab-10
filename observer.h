#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


class observer
{
public:
    virtual void update()=0;
};

class observable
{
    vector<observer*> subscribers;

public:
    void subscribe(observer* el)
    {
        subscribers.push_back(el);
    }
    void unsubscribe(observer* el)
    {
        auto it=subscribers.begin();
        while(it!=subscribers.end())
        {
            if((*it)==el)
                subscribers.erase(it);
            it++;
        }
    }
    void notify()
    {
        auto it=subscribers.begin();
        while(it!=subscribers.end())
        {
            (*it)->update();
            it++;
        }
    }
};
#endif // OBSERVER_H
