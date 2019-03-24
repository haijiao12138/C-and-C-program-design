#include "string.h"
#define n 10							/*假定系统中可容纳的作业数量为n*/
 typedef  struct  jcb
 {char  name[4];						/*作业名*/
  int  length;							/*作业长度，所需主存大小*/
  int  printer;							/*作业执行所需打印机的数量*/
  int  tape;							/*作业执行所需磁带机的数量*/
  int  runtime;						/*作业估计执行时间*/
  int  waittime;						/*作业在系统中的等待时间*/
  int  next;							/*指向下一个作业控制块的指针*/
   }JCB;								/*作业控制块类型定义*/
  int head; 							/*作业队列头指针定义*/
  int tape,printer;
  long memory;
  JCB jobtable[n];						/*作业表*/
  int jobcount=0;						/*系统内现有作业数量*/
  shedule(  )
 /*作业调度函数*/
 {float xk,k;
  int p,q,s,t;
  do
   {p=head;
    q=s=-1;
    k=0;
    while(p!=-1)
     { if(jobtable[p].length<=memory&&jobtable[p].tape<=tape&&jobtable[p].printer<=printer)
      { /*系统可用资源是否满足作业需求*/
       xk=(float)(jobtable[p].waittime)/jobtable[p].runtime;
       if(q==0||xk>k)				/*满足条件的第一个作业或者作业q的响应比小于作业p的响应比*/
        {k=xk;					/*记录响应比*/
         q=p;
         t=s;
	     }/*if*/
        }/*if*/
      s=p;
      p=jobtable[p].next;				/*指针p后移*/
      }/*while*/
     if(q!=-1)
      { if(t==-1)					/*是作业队列的第一个*/
	      head=jobtable[head].next;
       else
	      jobtable[t].next=jobtable[q].next;
       /*为作业q分配资源：分配主存空间；分配磁带机;分配打印机*/
        memory=memory-jobtable[q].length;
        tape=tape-jobtable[q].tape;
        printer=printer-jobtable[q].printer;
        printf("选中作业的作业名：%s\n",jobtable[q].name);
       }
    }while(q!=-1);
   }/*作业调度函数结束*/

main(  )
 {char name[4];
  int size,tcount,pcount,wtime,rtime;
  int p;
  /*系统数据初始化*/
  memory=65536;
  tape=4;
  printer=2;
  head=-1;
  printf("输入作业相关数据(以作业大小为负数停止输入)：\n");
  /*输入数据，建立作业队列*/
  printf("输入作业名、作业大小、磁带机数、打印机数、等待时间、估计执行时间\n");
  scanf("%s%d%d %d %d %d",name,&size,&tcount,&pcount,&wtime,&rtime);
  while(size!=-1)
  {/*创建JCB*/
   if(jobcount<n)p=jobcount;
   else { printf("无法再创建作业\n");
          break;
         }
   jobcount++;
   /*填写该作业相关内容*/
   strcpy(jobtable[p].name,name);
   jobtable[p].length=size;
   jobtable[p].printer=pcount;
   jobtable[p].tape=tcount;
   jobtable[p].runtime=rtime;
   jobtable[p].waittime=wtime;
   /*挂入作业队列队首*/
   jobtable[p].next=head;
   head=p;
   /* 输入一个作业数据*/
   printf("输入作业名、作业大小、磁带机数、打印机数、等待时间、估计执行时间\n");
   scanf("%s%d%d%d%d%d",name,&size,&tcount,&pcount,&wtime,&rtime);
   }/*while*/
  shedule( );							/*进行作业调度*/
  }/*main( )函数结束*/
