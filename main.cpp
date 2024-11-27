#include <iostream>
#include "CPU.h"
#include "RAMwithOeder.h"
#include "RAMwithBest.h"
#include "RAMwithWorst.h"

using namespace std;

int main() {
    //初始化内存
    Process processor1 =  Process(8,0,5);
    Process processor2 =  Process(16,0,4);
    Process processor3 =  Process(64,0,1);
    Process processor4 =  Process(124,0,4);
    Process processor5 =  Process(7,1,5);
    Process processor6 =  Process(16,2,5);
    Process processor7 =  Process(16,10,5);

    vector<Process> processes = {processor1, processor2, processor3, processor4, processor5, processor6, processor7};
    RAMwithOeder ram = RAMwithOeder(236, processes);
    RAMwithBest ram2 = RAMwithBest(236, processes);
    RAMwithWorst ram3 = RAMwithWorst(236, processes);
    CPU cpu = CPU(&ram);
    cout<<"最先适应法"<<endl;
    cpu.RunToEnd();

    cout<<"--------------------"<<endl;
    cout<<"最佳适应法"<<endl;
    cpu = CPU(&ram2);
    cpu.RunToEnd();

    cout<<"--------------------"<<endl;
    cout<<"最坏适应法"<<endl;
    cpu = CPU(&ram3);
    cpu.RunToEnd();

    return 0;
}
