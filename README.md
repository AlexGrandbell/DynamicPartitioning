OS Experiment:

Experiment 1 Dynamic partition management

(1) The design of main memory allocation simulation system for dynamic partition management - the first adaptation method, the best adaptation method and the worst adaptation method to simulate the memory allocation and recovery;

(2) can input the given memory size, the number of processes, the size of the memory space required by each process, etc.;

(3) The ability to select distribution or recovery operations; It can also display the usage of memory space after memory allocation or recycling.

(4) Can display the storage address and size of the process in memory.

The project implements three algorithms

Project structure:
Process and PartitionSpace are the bottom layers
RAM references the above two files, and is the parent class, and has three subclasses, respectively RAMwithFirstFit, RAMwithBestFit, RAMwithWorstFit, by simply adjusting the comparison function of the free area priority queue to implement three algorithms
The CPU only refers to the RAM file, and the algorithm is differentiated by pointer polymorphism
Menu references the CPU and three RAM subclass files for user interaction
Main.cpp implements the main function by referencing the Menu file

操作系统实验：

实验一 动态分区管理

（1）动态分区管理的主存分配模拟系统的设计—最先适应法、最佳适应法、最坏适应法，模拟实现内存的分配回收；

（2）能够输入给定的内存大小，进程的个数，每个进程所需内存空间的大小等； 

（3）能够选择分配或回收操作；并能显示完成内存分配或回收后内存空间的使用情况；

（4）能够显示进程在内存的存储地址、大小等。

项目实现了三种算法

项目结构：
Process与PartitionSpace为底层
RAM引用以上两个文件，并为父类，有三个子类，分别为RAMwithFirstFit、RAMwithBestFit、RAMwithWorstFit通过简单调整空闲区优先队列的比较函数来实现三种算法
CPU仅引用RAM文件，以指针多态实现算法的区分
Menu引用CPU与三个RAM子类文件，实现用户交互
main.cpp引用Menu文件，实现主函数
