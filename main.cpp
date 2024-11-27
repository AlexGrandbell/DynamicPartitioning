#include <iostream>
#include "CPU.h"
#include "RAMwithOeder.h"

using namespace std;

int main() {
    //初始化内存
    Process processor1 =  Process(8,0,5);
    Process processor2 =  Process(16,0,3);
    Process processor3 =  Process(64,0,1);
    Process processor4 =  Process(124,0,3);
    Process processor5 =  Process(50,1,5);
    Process processor6 =  Process(16,2,5);
    Process processor7 =  Process(16,10,5);

    vector<Process> processes = {processor1, processor2, processor3, processor4, processor5, processor6, processor7};
    RAMwithOeder ram = RAMwithOeder(236, processes);
    CPU cpu = CPU(&ram);
//    cpu.AddProcess(allProcesses);
    cpu.RunToEnd();
    return 0;
}
