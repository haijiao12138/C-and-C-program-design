#include "string.h"
#define n 10							/*�ٶ�ϵͳ�п����ɵ���ҵ����Ϊn*/
 typedef  struct  jcb
 {char  name[4];						/*��ҵ��*/
  int  length;							/*��ҵ���ȣ����������С*/
  int  printer;							/*��ҵִ�������ӡ��������*/
  int  tape;							/*��ҵִ������Ŵ���������*/
  int  runtime;						/*��ҵ����ִ��ʱ��*/
  int  waittime;						/*��ҵ��ϵͳ�еĵȴ�ʱ��*/
  int  next;							/*ָ����һ����ҵ���ƿ��ָ��*/
   }JCB;								/*��ҵ���ƿ����Ͷ���*/
  int head; 							/*��ҵ����ͷָ�붨��*/
  int tape,printer;
  long memory;
  JCB jobtable[n];						/*��ҵ��*/
  int jobcount=0;						/*ϵͳ��������ҵ����*/
  shedule(  )
 /*��ҵ���Ⱥ���*/
 {float xk,k;
  int p,q,s,t;
  do
   {p=head;
    q=s=-1;
    k=0;
    while(p!=-1)
     { if(jobtable[p].length<=memory&&jobtable[p].tape<=tape&&jobtable[p].printer<=printer)
      { /*ϵͳ������Դ�Ƿ�������ҵ����*/
       xk=(float)(jobtable[p].waittime)/jobtable[p].runtime;
       if(q==0||xk>k)				/*���������ĵ�һ����ҵ������ҵq����Ӧ��С����ҵp����Ӧ��*/
        {k=xk;					/*��¼��Ӧ��*/
         q=p;
         t=s;
	     }/*if*/
        }/*if*/
      s=p;
      p=jobtable[p].next;				/*ָ��p����*/
      }/*while*/
     if(q!=-1)
      { if(t==-1)					/*����ҵ���еĵ�һ��*/
	      head=jobtable[head].next;
       else
	      jobtable[t].next=jobtable[q].next;
       /*Ϊ��ҵq������Դ����������ռ䣻����Ŵ���;�����ӡ��*/
        memory=memory-jobtable[q].length;
        tape=tape-jobtable[q].tape;
        printer=printer-jobtable[q].printer;
        printf("ѡ����ҵ����ҵ����%s\n",jobtable[q].name);
       }
    }while(q!=-1);
   }/*��ҵ���Ⱥ�������*/

main(  )
 {char name[4];
  int size,tcount,pcount,wtime,rtime;
  int p;
  /*ϵͳ���ݳ�ʼ��*/
  memory=65536;
  tape=4;
  printer=2;
  head=-1;
  printf("������ҵ�������(����ҵ��СΪ����ֹͣ����)��\n");
  /*�������ݣ�������ҵ����*/
  printf("������ҵ������ҵ��С���Ŵ���������ӡ�������ȴ�ʱ�䡢����ִ��ʱ��\n");
  scanf("%s%d%d %d %d %d",name,&size,&tcount,&pcount,&wtime,&rtime);
  while(size!=-1)
  {/*����JCB*/
   if(jobcount<n)p=jobcount;
   else { printf("�޷��ٴ�����ҵ\n");
          break;
         }
   jobcount++;
   /*��д����ҵ�������*/
   strcpy(jobtable[p].name,name);
   jobtable[p].length=size;
   jobtable[p].printer=pcount;
   jobtable[p].tape=tcount;
   jobtable[p].runtime=rtime;
   jobtable[p].waittime=wtime;
   /*������ҵ���ж���*/
   jobtable[p].next=head;
   head=p;
   /* ����һ����ҵ����*/
   printf("������ҵ������ҵ��С���Ŵ���������ӡ�������ȴ�ʱ�䡢����ִ��ʱ��\n");
   scanf("%s%d%d%d%d%d",name,&size,&tcount,&pcount,&wtime,&rtime);
   }/*while*/
  shedule( );							/*������ҵ����*/
  }/*main( )��������*/
