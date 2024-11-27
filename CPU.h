//
// Created by AlexGrandbell on 24-11-26.
//

#ifndef DYNAMICPARTITIONING_CPU_H
#define DYNAMICPARTITIONING_CPU_H

#include "RAM.h"

using namespace std;

//CPU类，模拟调度
class CPU {
public:
    RAM *ram; //内存
    int currentTime; //当前时间

    CPU(RAM *ram): ram(ram), currentTime(-1) {}

    //运行一次
    void RunOnce();
    //运行到结束
    void RunToEnd();
};

#endif //DYNAMICPARTITIONING_CPU_H
