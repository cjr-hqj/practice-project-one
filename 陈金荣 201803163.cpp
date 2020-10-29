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

int Min(PCB* head)//��СAlltime��PCB��
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

int Max(PCB* head)//������ȼ�
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

PCB* CreatPCB(int n)//����PCB��
{
    int i;
    PCB* p, * q;
    head = (PCB*)malloc(sizeof(PCB));
    head->next = NULL;//ȡ��βָ��1
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

void Display(PCB* head)//��ʾPCB���̿�
{
    PCB* p;
    p = head->next;
    printf("ID  Arrivetime CPUtime(��ռ��) Alltime Priority  state\n");
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

void FCFS(PCB* head, PCB* over)//FCFS�����㷨
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
        printf("��%d��ִ���㷨��ľ������У�\n", j);
        Display(head);
    }
    m = (double)s / j;
    printf("���˳ѰΪ:\n");
    Display(over);
    printf("\n");
    printf("ÿ�����̵�ƽ���ȴ�ʱ��Ϊ��%1f\n", m);
    printf("���н��̵ĵȴ�ʱ��Ϊ��%d", s);
}

void SJF(PCB* head, PCB* over)//SJF�㷨
{
    PCB* p, * q, * b, * o;
    int s;
    int m, n, h = 0, d = 0, j = 0;
    double f;
    p = head->next;
    q = over;
    o = head;
    printf("���˳ѰΪ:");
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
        printf("��%d��ִ���㷨��ľ�������:\n", j);
        Display(head);
    }
    f = (double)h / j;
    printf("���˳ѰΪ��\n");
    Display(over);
    printf("ÿ�����̵ȴ���ƽ��ʱ��Ϊ:%1f\n", f);
    printf("���н��̵ĵȴ�ʱ��Ϊ��%d\n", h);
}

void Prio(PCB* head, PCB* over)//���ȵ����㷨
{
    PCB* p, * q, * b, * o;
    int s;
    int m, n, h = 0, d = 0, j = 0;
    double f;
    p = head->next;
    o = head;
    q = over;
    printf("��ǰӵ��������ȼ��Ŀ���ǣ�");
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
        printf("��%d��ִ���㷨��ľ������У�\n", j);
        Display(head);
    }
    f = (double)h / j;
    printf("���˳ѰΪ��");
    Display(head);
    printf("ÿ�����̵ȴ���ʱ��Ϊ��%1f\n", f);
    printf("���н��̵ȴ���ʱ��Ϊ��%d", h);
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
    printf("ִ��˳��Ϊ��\n");
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
            printf("ִ�н���%d      ", p->ID);
            printf("�ý��̵�Alltime��Ϊ%d\n", p->Alltime);
            p = p->next;
        }
        else
        {
            printf("         ��ɽ��̣�%d       \n", p->ID);
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
    printf("���˳ѰΪ��\n");
    Display(over);
    printf("ÿ�����̵ȴ���ƽ��ʱ��Ϊ��%lf\n", h);
    printf("���н��̵ȴ�����ʱ��Ϊ��%d", s);
}

int main(void)
{
    int n, m, t;
    printf("|------------------------------------------------------------------------------|\n");
    printf("|                       �� �� �� �� �� ģ ��                                   |\n");
    printf("|------------------------------------------------------------------------------|\n");
    printf("\t\t\t|----ѡ��--------------------|\n");
    printf("\t\t\t|         1. FCFS���ȷ�      |\n");
    printf("\t\t\t|----------------------------|\n");
    printf("\t\t\t|         2. SJF�����㷨     |\n");
    printf("\t\t\t|----------------------------|\n");
    printf("\t\t\t|         3. ���ȵ����㷨    |\n");
    printf("\t\t\t|----------------------------|\n");
    printf("\t\t\t|         4. RR�����㷨      |\n");
    printf("\t\t\t|----------------------------|\n");
    printf("\n");
    printf("������Ҫ�����Ľ�����Ŀ��");
    cin >> n;
    head = CreatPCB(n);
    printf("�����ľ�������Ϊ��\n");
    Display(head);
    printf("��ѡ��Ҫ���ȵ��㷨��");
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
        printf("������ʱ��Ƭ�Ĵ�С��");
        cin >> t;
        RR(head, over, t, n);
        break;
    }
    return 0;
}










