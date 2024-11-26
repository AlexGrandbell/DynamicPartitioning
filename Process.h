//
// Created by AlexGrandbell on 24-11-26.
//

#ifndef DYNAMICPARTITIONING_PROCESS_H
#define DYNAMICPARTITIONING_PROCESS_H

//进程类
class Process {
public:
    int id; //进程id
    int needSize; //进程大小
    int createTime; //进程创建时间
    int needTime; //进程需要运行时间
    static int processId; //静态变量，用于生成进程id

    Process(int needSize, int createTime, int needTime): needSize(needSize), createTime(createTime), needTime(needTime){
        id = processId++;
    }
    Process(): needSize(0), createTime(0), needTime(0){
        id = 0;
    }
    //重载比较时间开始运算符，以便在优先队列中使用
    bool operator>(const Process &other) const {
        return createTime> other.createTime;
    }
    bool operator<(const Process &other) const {
        return createTime < other.createTime;
    }
};

#endif //DYNAMICPARTITIONING_PROCESS_H
