#include "stdio.h"
#define  running  1  				/*��running ��ʾ���̴�������̬*/
#define  aready  2   				/*��aready��ʾ���̴��ھ���̬*/
#define  blocking  3  				/*��blocking��ʾ���̴��ڵȴ�̬*/
#define  sometime 5  				/*��sometime��ʾʱ��Ƭ��С*/
#define n 10          				/*�ٶ�ϵͳ������̸���Ϊn */
struct
{int  name;          				/*���̱�ʶ��*/
 int  status;          				/*����״̬*/
 int ax, bx, cx,dx;      				/*�����ֳ���Ϣ��ͨ�üĴ�������*/
 int pc;              				/*�����ֳ���Ϣ���������������*/
 int psw;             				/*�����ֳ���Ϣ������״̬�ּĴ�������*/
 int next;             				/*��һ�����̿��ƿ��λ��*/
}pcbarea[n];           				/*ģ����̿��ƿ����������*/
int PSW,AX,BX,CX,DX,PC,TIME; 		/*ģ��Ĵ���*/
int run;                    		/*����ָ���������н��̵Ľ��̿��ƿ��ָ��*/
struct
 {int  head;
  int  tail;
  }ready;                  		/*����������е�ͷָ��head��βָ��tail*/
int  pfree;                      	/*����ָ����н��̿��ƿ���е�ָ��*/

sheduling(  )                   	/*���̵��Ⱥ���*/
{int i;
 if (ready.head==-1)              	/*���н��̿��ƿ����Ϊ�գ��˳�*/
  {printf("�޾�������\n");
   return;
  }
 i=ready.head;                   	/*��������ͷָ�븳��i*/
 ready.head=pcbarea[ready.head].next;  	/*��������ͷָ�����*/
 if(ready.head==-1)ready.tail=-1;		/*��������Ϊ�գ�����βָ��ready.tail*/
 pcbarea[i].status=running;         	/*�޸Ľ��̿��ƿ�״̬*/
 TIME=sometime;               	/*�������ʱ�ӼĴ���*/
 /*�ָ��ý����ֳ���Ϣ��*/
 AX=pcbarea[run].ax;
 BX=pcbarea[run].bx;
 CX=pcbarea[run].cx;
 DX=pcbarea[run].dx;
 PC=pcbarea[run].pc;
 PSW=pcbarea[run].psw;
 run=i;                         	/*�޸�ָ�����н��̵�ָ��*/
 }/*���̵��Ⱥ�������*/

int create( int x)
/*��������*/
{int i;
 if(pfree==-1)                   	/*���н��̿��ƿ����Ϊ��*/
  {printf("�޿��н��̿��ƿ飬���̴���ʧ��\n");
   return;
  }
 i=pfree;                       	/*ȡ���н��̿��ƿ���еĵ�һ��*/
 pfree=pcbarea[pfree].next;        	/*pfree����*/
/*��д�ý��̿��ƿ����ݣ�*/
 pcbarea[i].name=x;
 pcbarea[i].status=aready;
 pcbarea[i].ax=x;
 pcbarea[i].bx=x;
 pcbarea[i].cx=x;
 pcbarea[i].dx=x;
 pcbarea[i].pc=x;
 pcbarea[i].psw=x;
 if(ready.head!=-1)               	/*�������в���ʱ������������з�ʽ*/
  {pcbarea[ready.tail].next=i;
   ready.tail=i;
   pcbarea[ready.tail].next=-1;
  }
 else                          	/*�������п�ʱ,����������з�ʽ*/
 {ready.head=i;
  ready.tail=i;
  pcbarea[ready.tail].next=-1;
 }
}/*���̴�����������*/

main()
{/*ϵͳ��ʼ��*/
 int num,i,j;
 run=ready.head=ready.tail=block=-1;
 pfree=0;
 for(j=0;j<n-1;j++)
   pcbarea[j].next=j+1;
 pcbarea[n-1].next=-1;
 printf("������̱��(�����ŵĳ�ͻ,�Ը����������,�����Դ���10������):\n");
 scanf("%d",&num);
 while(num>=0)
  {create(num);
   scanf("%d",&num);
  }
 sheduling( );       				/*���̵���*/
 if(run!=-1)
  {printf("���̱�ʶ��  ����״̬  �Ĵ�������:ax bx cx dx pc psw:\n");
   printf("%8d%10d%3d%3d%3d%3d%3d%3d\n",pcbarea[run].name,
   pcbarea[run].status,pcbarea[run].ax, pcbarea[run].bx, pcbarea[run].cx,
   pcbarea[run].dx, pcbarea[run].pc, pcbarea[run].psw);
}
  }/*main( )����*/
