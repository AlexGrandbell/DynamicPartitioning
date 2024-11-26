#include <iostream>
#include "CPU.h"
#include "RAMwithOeder.h"

using namespace std;

int main() {
    //初始化内存
    Process processor1 =  Process(8,0,4);
    Process processor2 =  Process(16,0,2);
    Process processor3 =  Process(64,0,1);
    Process processor4 =  Process(124,0,2);
    Process processor5 =  Process(50,1,5);
    Process processor6 =  Process(16,1,5);

    vector<Process> processes = {processor1, processor2, processor3, processor4, processor5, processor6};
    RAMwithOeder ram = RAMwithOeder(256, processes);
    CPU cpu = CPU(&ram);
//    cpu.AddProcess(processes);
    cpu.RunToEnd();
    return 0;
}
