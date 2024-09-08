xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)). See also https://pdos.csail.mit.edu/6.828/, which
provides pointers to on-line resources for v6.

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by
Takahiro Aoyagi, Silas Boyd-Wickizer, Anton Burtsev, Ian Chen, Dan
Cross, Cody Cutler, Mike CAT, Tej Chajed, Asami Doi, eyalz800, Nelson
Elhage, Saar Ettinger, Alice Ferrazzi, Nathaniel Filardo, flespark,
Peter Froehlich, Yakir Goaron,Shivam Handa, Matt Harvey, Bryan Henry,
jaichenhengjie, Jim Huang, Matúš Jókay, Alexander Kapshuk, Anders
Kaseorg, kehao95, Wolfgang Keller, Jungwoo Kim, Jonathan Kimmitt,
Eddie Kohler, Vadim Kolontsov , Austin Liew, l0stman, Pavan
Maddamsetti, Imbar Marinescu, Yandong Mao, , Matan Shabtay, Hitoshi
Mitake, Carmi Merimovich, Mark Morrissey, mtasm, Joel Nider,
OptimisticSide, Greg Price, Jude Rich, Ayan Shafqat, Eldar Sehayek,
Yongming Shen, Fumiya Shigemitsu, Cam Tenny, tyfkda, Warren Toomey,
Stephen Tu, Rafael Ubal, Amane Uehara, Pablo Ventura, Xi Wang, Keiichi
Watanabe, Nicolas Wolovick, wxdao, Grant Wu, Jindong Zhang, Icenowy
Zheng, ZhUyU1997, and Zou Chang Wei.

The code in the files that constitute xv6 is
Copyright 2006-2020 Frans Kaashoek, Robert Morris, and Russ Cox.

ERROR REPORTS

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu). The main purpose of xv6 is as a teaching
operating system for MIT's 6.S081, so we are more interested in
simplifications and clarifications than new features.

BUILDING AND RUNNING XV6

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu. Once they are installed, and in your shell
search path, you can run "make qemu".

# ����д��¼

---

#### 8.29

������������Ǹ�ʵ�ʿα�ͬ����....

�ع�һ��д���ܱʼǣ���page table��ʼ��

page: ����洢�豸�ĵ�Ԫ��xv6��Ϊ4KB��С

page table: �洢�����ڴ�ӳ�䵽�����ڴ�ı�

xv6ΪSv39����ʹ����39λ�������ڴ棬����27λ����Ѱ��page table entries (PTEs)��12λΪOffset

PTE: page table entry�����а�����44λ��physical page
number (PPN),������λ�����ڴ�ҳ������10λ��flag��Ϊ������Ϣ

![alt text](images/image2.png)

xv6��Ѱַ����������Ѱַ��ʽ������ҳ���Ϊ������ÿһ���洢512��PTE��satp��λ����һ��ҳ��9λ��L2��Ϊƫ��Ѱ�ҵ�һ��PTE�����е�PPNѰ�ҵ��ڶ���ҳ��ѭ��Ѱ�ң�������ҳ���PPN��λ������Ҫ������ҳ���ٽ��12λoffset��Ϊ�����ַ

![alt text](images/image.png)

��Ϊxv6���ں��ڴ�ṹ���ں��в��ֵ�ַΪֱ��ӳ�䣬�ӿ��ں��ٶ�

![alt text](images/image3.png)


![alt text](images/image4.png)

- RISC-V��trap����

����trap�ļĴ�����

stvec:��trap handler�ĵ�ַ

sepc: system exception process counter ������trapǰ��pc

scause: ʶ��trap��ԭ��

sscratch: �����ݴ��ļĴ�����Ϊ�ں��ṩ���õļĴ���

sstatus: ��һЩ������Ϣ������SIEλ���Ƿ���device interrupt

trap���̣�

����������豸�жϣ����� sstatus �Ĵ����е� SIE λ���������ִ�����²�����
ͨ����� sstatus �е� SIE λ�������жϡ�
�������������pc����ֵ���Ƶ� sepc��
����ǰģʽ��user or supervisor�������� sstatus �Ĵ����е� SPP λ�С�
���� scause �Է�ӳ�����ԭ��
��ģʽ����Ϊsupervisor��
�� stvec ��ֵ���Ƶ������������pc����
���µĳ��������λ�ÿ�ʼִ�С�

user space��trap:

����ת��trampoline page�е�uservec,���������û��Ĵ������ٽ���usertrap�У����ݲ�ͬtrap����ִ�в�ͬ����������ʱ�ȵ���usertrapret������ĳЩ��Ϣ���罫stvec����Ϊuservec���Ա���֮ǰ����Ϊ��kernelvec������sepc����userret���ݲ����ȣ�������userret����λ�û��Ĵ��������ء�

����trampoline page��ÿһ�������ж�ӳ��������ͬ�������ַ�����Ե���trampoline page���л�page tableʱ�ܲ�Ӱ��trap handler������

kernel space��trap:

��usertrap�д�user space����kernel spaceʱ��stvec�ᱻ����Ϊkernelvec�ĵ�ַ��

kernel trap���̸�user trap��࣬����kernel trapҪô��kernel�������ˣ��ǾͱȽ����أ�ֱ�Ӱݰݣ�Ҫô���Ǽ�ʱ�����ˣ���Ҫ�л��̡߳�

- Page Fault

���û������˷Ƿ����ڴ��ַʱ�����ᷢ��page fault������ʲ����ڵĵ�ַ��flag�Ŀ��Ʒ��������Ӧ�Ĳ������м�������page fault�����������ԣ�������ϵͳ�ٶȡ�

1. Copy On Write(COW)
    �ȶ�ָ��ͬһ�飬Ҫд���ٷֿ�

2. lazy allocation
    �Ȳ����䣬Ҫ�����ٷ���

3. demand paging
    �Ȳ����أ�Ҫ�����ټ���

4. paging to disk
    �Ѵ��̵��ڴ�


#### 8.16

���쿴�Σ�д��ʼ�

kernal = trusted computing base (TCB)



#### 8.15

�����ǰ�lab1д����

��ô��ûѧ��Ĺ����Σ�����Ӣ�����е�С�����ˣ��ĵ���ʱ��ⲻȫ��˼������lab����̫˳

lab1����һЩ�Ƚϻ�����ʵ�飬��Ҫ����Ϥ�õ�

����bug:

- file descriptorͬʱ���������������ޣ�ʹ����ǵù�

- find��make grade���������Ƿ�д�˲�ѯ�����ļ��Ĵ��룬���Ǻ����xargsҪ�ã�ûд�Ļ�����bug

- �󲿷�ʵ�鶼����͵���������о����ǲ�̫�ã��Ҿ;���������˵����
