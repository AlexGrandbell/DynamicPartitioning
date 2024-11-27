//
// Created by AlexGrandbell on 24-11-26.
//

#include "CPU.h"


//初始化进程，并按照初始时间排序
//void CPU::AddProcess(vector<Process> allProcesses) {
//    for(auto &process: allProcesses) {
//        ram->processesMap[process.id] = process;
//        ram->allProcesses.push(process.id);
//    }
//    //ram中的进程按照时间排序
//    for(auto &process: ram->processesMap) {
//        ram->allProcesses.push(process.first);
//    }
//}

//运行一次。先增加当前时间并运行一次内存，回收结束的空间。然后将当前时间小于等于进程创建时间的进程加入内存排到后面，不断尝试将等待中的进程按序加入，直到没有空间为止。
void CPU::RunOnce() {
    currentTime++;
    cout<<"---------"<<endl;
    cout<<"当前时间："<<currentTime<<endl;
    cout<<"\n运行过程: "<<endl;
    ram->RunOnceAndRecycle();
    while(!ram->allProcesses.empty() && ram->processesMap[ram->allProcesses.top()].createTime <= currentTime) {
        ram->waitingProcesses.push(ram->allProcesses.top());
        ram->allProcesses.pop();
    }
    while(!ram->waitingProcesses.empty()) {
        if(ram->AllocateMemory(ram->waitingProcesses.top())) {
            ram->waitingProcesses.pop();
        } else {
            break;
        }
    }
    cout<<"\n此次运行完毕，当前内存分配状态为："<<endl;
    ram->ShowMemoryStatus();
    cout<<"---------"<<endl;
}

//运行到结束
void CPU::RunToEnd() {
    cout<<"开始运行"<<endl;
    while(ram->totalTime>currentTime || !ram->partitionSpacesMap.size() > 1) {
        RunOnce();
    }
    cout<<"结束运行"<<endl;
}
