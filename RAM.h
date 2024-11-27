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

struct BaseComparator {
    virtual bool operator()(int lhs, int rhs) const = 0;
    virtual ~BaseComparator() = default;
};
struct CreateTimeComparator : public BaseComparator {
    const std::map<int, Process>* comProcessesNum;

    CreateTimeComparator(const std::map<int, Process>& processesMap): comProcessesNum(&processesMap) {}

    bool operator()(int lhs, int rhs) const override {
        return comProcessesNum->at(lhs).createTime > comProcessesNum->at(rhs).createTime;
    }
};


//内存类，抽象类
class RAM {
public:
    int totalSize; //总大小
    int totalTime;//最少时间

    //总进程列表，根据开始时间优先队列
    map<int, Process> processesMap;//所有进程对照表
    //自定义优先队列比较器
//    struct ProcessComparator {
//        const map<int, Process>* comProcessesMap;
//        ProcessComparator() : comProcessesMap(nullptr) {}
//        ProcessComparator(const std::map<int, Process>& processesNum): comProcessesMap(&processesNum) {}
//        bool operator()(int lhs, int rhs) const {
//            if (!comProcessesMap) {
//                throw std::logic_error("未初始化比较器");
//            }
//            return comProcessesMap->at(lhs).createTime > comProcessesMap->at(rhs).createTime;
//        }
//    };
    priority_queue<int, vector<int>,function<bool(int, int)>> allProcesses;//所有进程ID优先队列
    priority_queue<int, vector<int>,function<bool(int, int)>> waitingProcesses;//等待进程ID优先队列

    map<int, PartitionSpace> partitionSpacesMap;//分区空间对照表
    list<int> partitionAllSpaces;//总分区链表
//    priority_queue<int, vector<int>, function<bool(int, int)>> partitionFreeSpaces;//空闲分区列表优先队列

    RAM(int totalSize, vector<Process> processes) : totalSize(totalSize),totalTime(0) {
        //添加初始化分区到 map
        partitionSpacesMap[0] = PartitionSpace(0, totalSize, true);
        partitionAllSpaces.push_back(0);

        //将进程添加到processesNum中
        for (auto &process : processes) {
            processesMap[process.id] = process;
            if (process.createTime+process.needTime > totalTime) {
                totalTime = process.createTime+process.needTime;
            }
        }

        //初始化优先队列时传入ProcessComparator
        this->allProcesses = priority_queue<int, vector<int>, function<bool(int, int)>>(CreateTimeComparator(processesMap));
        waitingProcesses = priority_queue<int, vector<int>, function<bool(int, int)>>(CreateTimeComparator(processesMap));

        //将进程ID推入优先队列
        for (auto &process : processesMap) {
            this->allProcesses.push(process.first);
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
