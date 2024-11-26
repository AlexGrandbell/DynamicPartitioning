//
// Created by AlexGrandbell on 24-11-26.
//

#include "CPU.h"


//初始化进程，并按照初始时间排序
//void CPU::AddProcess(vector<Process> processes) {
//    for(auto &process: processes) {
//        ram->processesNum[process.id] = process;
//        ram->processes.push(process.id);
//    }
//    //ram中的进程按照时间排序
//    for(auto &process: ram->processesNum) {
//        ram->processes.push(process.first);
//    }
//}

//运行一次。先增加当前时间并运行一次内存，回收结束的空间。然后将当前时间小于等于进程创建时间的进程加入内存排到后面，不断尝试将等待中的进程按序加入，直到没有空间为止。
void CPU::RunOnce() {
    currentTime++;
    cout<<"---------"<<endl;
    cout<<"当前时间："<<currentTime<<endl;
    ram->RunOnceAndRecycle();
    while(!ram->processes.empty() && ram->processesNum[ram->processes.top()].createTime <= currentTime) {
        ram->waitingProcesses.push(ram->processes.top());
        ram->processes.pop();
    }
    while(!ram->waitingProcesses.empty()) {
        if(ram->AllocateMemory(ram->waitingProcesses.top())) {
            ram->waitingProcesses.pop();
        } else {
            break;
        }
    }
    cout<<"此次运行完毕，当前内存分配状态为："<<endl;
    ram->ShowMemoryStatus();
    cout<<"---------"<<endl;
}

//运行到结束
void CPU::RunToEnd() {
    cout<<"开始运行"<<endl;
    while(!ram->processes.empty() || !ram->waitingProcesses.empty()) {
        RunOnce();
    }
    cout<<"结束运行"<<endl;
}
