#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#define Ready 0
#define Running 1
#define Block 3
#define Over 4

typedef struct PCBNode
{
    int ID;
    int Priority;
    int CPUtime;
    int Alltime;
    int Arrivetime;
    int state;
    int counter;
    struct PCBNode* next;
}PCB;

PCB* run;
PCB* ready;
PCB* over;
PCB* head;

int Min(PCB* head)//最小Alltime的PCB块
{
    PCB* p;
    int min=0, id=0;
    p = head->next;
    if (p)
    {
        min = p->Alltime;
        id = p->ID;
        while (p->next)
        {
            if (min > p->next->Alltime)
            {
                min = p->next->Alltime;
                id = p->next->ID;
                p = p->next;
            }
            else
            {
                p = p->next;
            }
        }
    }
    return id;
}

int Max(PCB* head)//最大优先级
{
    PCB *p;

    int max=0, id=0;
    p = head ->next;
    if (p)
    {
        max = p->Priority;
        id = p->ID;
        while (p->next)
        {
            if (max <= p->next->Priority)
            {
                max = p->next->Priority;
                id = p->next->ID;
                p = p->next;
            }
            else
            {
                p = p->next;
            }
        }
    }
    return id;
}

PCB* CreatPCB(int n)//创建PCB块
{
    int i;
    PCB* p, * q;
    head = (PCB*)malloc(sizeof(PCB));
    head->next = NULL;//取消尾指针1
    p = head;
    for (i = 1;i <= n;i++)
    {
        q = (PCB*)malloc(sizeof(PCB));
        q->ID = i;
        q->CPUtime = 0;
        q->Alltime = rand() % 200;
        q->Priority = rand() % 10;
        q->state = Ready;
        q->Arrivetime = 0;
        p->next = q;
        p = q;
        q->next = NULL;
    }
    head->next->Priority = 0;
    return head;
}

void Display(PCB* head)//显示PCB进程块
{
    PCB* p;
    p = head->next;
    printf("ID  Arrivetime CPUtime(已占用) Alltime Priority  state\n");
    while (p)
    {
        printf("%d        ", p->ID);
        printf("%d        ", p->Arrivetime);
        printf("%d              ", p->CPUtime);
        printf("%d        ", p->Alltime);
        printf("%d        ", p->Priority);
        printf("%d        \n", p->state);
        p = p->next;
    }
}

void FCFS(PCB* head, PCB* over)//FCFS跳读算法
{
    PCB* p, * q;
    int j = 0;
    int n = 0, s = 0;
    double m;
    ready = head;
    p = ready->next;
    q = over;
    while (p)
    {
        p->state = Running;
        ready->next = p->next;
        n = p->Alltime + n;
        p->CPUtime = p->Alltime;
        p->Alltime = 0;
        s = s + n;
        p->next = NULL;
        q->next = p;
        p->state = Over;
        q = q->next;
        q->next = NULL;
        p = head->next;
        j++;
        printf("第%d次执行算法后的就绪队列：\n", j);
        Display(head);
    }
    m = (double)s / j;
    printf("完成顺寻为:\n");
    Display(over);
    printf("\n");
    printf("每个进程的平均等待时间为：%1f\n", m);
    printf("所有进程的等待时间为：%d", s);
}

void SJF(PCB* head, PCB* over)//SJF算法
{
    PCB* p, * q, * b, * o;
    int s;
    int m, n, h = 0, d = 0, j = 0;
    double f;
    p = head->next;
    q = over;
    o = head;
    printf("完成顺寻为:");
    m = p->ID;
    n = p->Alltime;
    s = Min(head);
    b = p->next;
    printf("  %d\n", s);
    while (head->next)
    {
        while (s != p->ID)
        {
            o = p;
            p = p->next;
        }
        d = p->Alltime;
        p->CPUtime = p->Alltime;
        p->Alltime = 0;
        h = d + h;
        b = p;
        q->next = b;
        o->next = p->next;
        p = head->next;
        b->next = NULL;
        o = head;
        q = q->next;
        s = Min(head);
        j++;
        printf("第%d次执行算法后的就绪序列:\n", j);
        Display(head);
    }
    f = (double)h / j;
    printf("完成顺寻为：\n");
    Display(over);
    printf("每个进程等待的平均时间为:%1f\n", f);
    printf("所有进程的等待时间为：%d\n", h);
}

void Prio(PCB* head, PCB* over)//优先调度算法
{
    PCB* p, * q, * b, * o;
    int s;
    int m, n, h = 0, d = 0, j = 0;
    double f;
    p = head->next;
    o = head;
    q = over;
    printf("当前拥有最大优先级的块号是：");
    m = p->ID;
    n = p->Alltime;
    s = Max(head);
    b = p->next;
    printf("%d\n", s);
    while (head->next)
    {
        while (s != p->ID)
        {
            o = p;
            p = p->next;
        }
        d = p->Alltime;
        p->CPUtime = p->Alltime;
        p->Alltime = 0;
        h = d + h;
        b = p;
        q->next = b;
        o->next = p->next;
        p = head->next;
        b->next = NULL;
        o = head;
        q = q->next;
        s = Max(head);
        j++;
        printf("第%d次执行算法后的就绪队列：\n", j);
        Display(head);
    }
    f = (double)h / j;
    printf("完成顺寻为：");
    Display(head);
    printf("每个进程等待的时间为：%1f\n", f);
    printf("所有进程等待的时间为：%d", h);
}

void RR(PCB* head, PCB* over, int t, int k)
{
    PCB* p, * q, * r, * o, * tail;
    int n = 0, s = 0, f;
    double h;
    f = k;
    p = head->next;
    while (p->next)
    {
        tail = p;
        p = p->next;
    }
    printf("执行顺序为：\n");
    tail = p;
    o = p;
    tail->next = head->next;
    p = head->next;
    q = over;
    while (k > 0)
    {
        r = head->next;
        if (p->Alltime > t)
        {
            p->Alltime = p->Alltime - t;
            n = n + t;
            s = s + n;
            o = p;
            printf("执行进程%d      ", p->ID);
            printf("该进程的Alltime变为%d\n", p->Alltime);
            p = p->next;
        }
        else
        {
            printf("         完成进程：%d       \n", p->ID);
            n = n + p->Alltime;
            s = s + n;
            p->Alltime = 0;
            o->next = p->next;
            q->next = p;
            q = q->next;
            q->next = NULL;
            p = o->next;
            k--;
        }
    }
    h = (double)s / f;
    printf("完成顺寻为：\n");
    Display(over);
    printf("每个进程等待的平均时间为：%lf\n", h);
    printf("所有进程等待的总时间为：%d", s);
}

int main(void)
{
    int n, m, t;
    printf("|------------------------------------------------------------------------------|\n");
    printf("|                       进 程 调 度 的 模 拟                                   |\n");
    printf("|------------------------------------------------------------------------------|\n");
    printf("\t\t\t|----选项--------------------|\n");
    printf("\t\t\t|         1. FCFS调度法      |\n");
    printf("\t\t\t|----------------------------|\n");
    printf("\t\t\t|         2. SJF调度算法     |\n");
    printf("\t\t\t|----------------------------|\n");
    printf("\t\t\t|         3. 优先调度算法    |\n");
    printf("\t\t\t|----------------------------|\n");
    printf("\t\t\t|         4. RR调度算法      |\n");
    printf("\t\t\t|----------------------------|\n");
    printf("\n");
    printf("请输入要创建的进程数目：");
    cin >> n;
    head = CreatPCB(n);
    printf("创建的就绪队列为：\n");
    Display(head);
    printf("请选择要调度的算法：");
    cin >> m;
    over = (PCB*)malloc(sizeof(PCB));
    over->next = NULL;
    switch (m)
    {
    case 1:
        system("CLS");
        FCFS(head, over);
        break;
    case 2:
        system("CLS");
        SJF(head, over);
        break;
    case 3:
        system("CLS");
        Prio(head, over);
        break;
    case 4:
        system("CLS");
        printf("请输入时间片的大小：");
        cin >> t;
        RR(head, over, t, n);
        break;
    }
    return 0;
}










