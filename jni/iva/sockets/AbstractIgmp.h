#ifndef _ABSTRACT_IGMP_H_
#define _ABSTRACT_IGMP_H_

class AbstractIgmp
{
public:
    virtual int send() = 0;
};

#endif