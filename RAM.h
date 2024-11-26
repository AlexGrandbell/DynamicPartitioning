//
// Created by AlexGrandbell on 24-11-26.
//

#ifndef DYNAMICPARTITIONING_RAM_H
#define DYNAMICPARTITIONING_RAM_H

#include "PartitionSpace.h"
#include "Process.h"
#include <list>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

//内存类，抽象类
class RAM {
public:
    int totalSize; //总大小

    //总进程列表，根据开始时间优先队列
    map<int, Process> processesNum;//所有进程对照表
    //自定义优先队列比较器
    struct ProcessComparator {
        const map<int, Process>* processesNum;
        ProcessComparator() : processesNum(nullptr) {}
        ProcessComparator(const std::map<int, Process>& processesNum):processesNum(&processesNum) {}
        bool operator()(int lhs, int rhs) const {
            if (!processesNum) {
                throw std::logic_error("未初始化比较器");
            }
            return processesNum->at(lhs).createTime > processesNum->at(rhs).createTime;
        }
    };
    priority_queue<int, vector<int>,ProcessComparator> processes;//所有进程ID优先队列
    priority_queue<int, vector<int>,ProcessComparator> waitingProcesses;//等待进程ID优先队列

    map<int, PartitionSpace> partitionSpacesNum;//分区空间对照表
    list<int> partitionSpaces;//总分区链表
//    list<PartitionSpace> freePartitionSpaces;//空闲分区链表
//    priority_queue<PartitionSpace, vector<PartitionSpace>, greater<PartitionSpace>> freePartitionSpacesBeatQueue;//空闲分最佳适应法区优先队列
//    priority_queue<PartitionSpace, vector<PartitionSpace>, less<PartitionSpace>> freePartitionSpacesWorstQueue;//空闲分区最坏适应法优先队列

    RAM(int totalSize, vector<Process> processes) : totalSize(totalSize) {
        // 添加初始化分区到 map
        partitionSpacesNum[0] = PartitionSpace(0, totalSize, true);
        partitionSpaces.push_back(0);

        // 将进程添加到 processesNum 中
        for (auto &process : processes) {
            processesNum[process.id] = process;
        }

        //初始化优先队列时传入ProcessComparator
        this->processes = priority_queue<int, vector<int>, ProcessComparator>(ProcessComparator(processesNum));
        waitingProcesses = priority_queue<int, vector<int>, ProcessComparator>(ProcessComparator(processesNum));

        //将进程ID推入优先队列
        for (auto &process : processesNum) {
            this->processes.push(process.first);
        }
    }

    //分配内存接口
    virtual bool AllocateMemory(int processID) = 0;
    //运行一次减少时间接口并回收结束的内存
    virtual void RunOnceAndRecycle() = 0;
    //显示内存分配状态
    void ShowMemoryStatus();

protected:
    //合并一次空闲分区
    virtual void mergeFreePartitionSpacesOnce() = 0;
};



#endif //DYNAMICPARTITIONING_RAM_H
