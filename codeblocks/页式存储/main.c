#define n 64            				/*ģ��ʵ���мٶ���ҳ����*/
#define length 10
struct
{int  lnumber;							/*ҳ��*/
 int  flag;              				/*��ʾҳ�Ƿ������棬��1����ʾ�ڣ���0����ʾ����*/
 int  pnumber;          				/*��ҳ���������Ŀ��*/
 int  write;             				/*��ҳ�Ƿ��޸Ĺ�����1����ʾ�޸Ĺ�����0����ʾû
���޸Ĺ�*/
 int  dnumber;          				/*��ҳ����ڴ����ϵ�λ�ã������̿��*/
}page[n];                				/*ҳ����*/
int m;                   				/*mΪ��ҵ�������е���������*/
int page_length;           				/*ҳ��ʵ�ʳ���*/
int p[length];            				/*�����������ҳ��ҳ��*/
int head;								/*������ҳ�Ŷ���ͷָ��*/

 page_interrupt(lnumber)
 int lnumber;
 {int j;
  printf("����ȱҳ�ж�* %d\n",lnumber);
  /*��̭ҳ*/
  j=p[head];
  p[head]=lnumber;
  head=(head+1)%m;
  if (page[j].write==1)
    printf("��ҳ %dд�ش��̵�%d��\n",j,page[j].dnumber);
  page[j].flag=0;                 		/*��jҳ���ڱ�־��Ϊ��0��*/
  page[lnumber].pnumber=page[j].pnumber;
  page[lnumber].flag=1;          		/*��lnumberҳ���ڱ�־��Ϊ��0��*/
  page[lnumber].write=0;         		/*��lunmberҳ�޸ı�־��Ϊ��1��*/
  printf("��̭�����%2d�е�ҳ%2d���Ӵ��̵�%d���е���ҳ%2d\n",  page[j].pnumber,j,page[lnumber].dnumber,lnumber);
  }/*ȱҳ�жϴ���������*/

  command(laddress,write)
  unsigned  laddress;
  int write;
  {unsigned paddress,ad,pnumber,lnumber;
   kk:
   /*ȡ���߼���ַladdress��ҳ��lnumber����6λ����ҳ�ڵ�ַad*/
   lnumber=laddress>>10;
   ad=laddress&0x3ff;
   if(lnumber>=page_length)
    { printf("�����ڸ�ҳ\n");
      return;
    }
   if(page[lnumber].flag==1)      			/*ҳ������*/
   {pnumber=page[lnumber].pnumber;			/*��ҳ����ȡ�ÿ��*/
    paddress=pnumber<<10|ad;    			/*�ϲ���źͿ��ڵ�ַ�γ������ַpaddress*/
    printf("�߼���ַ�ǣ�%x   ��Ӧ�����ַ��:%x\n",laddress,paddress);
    if(write==1)                				/*�����Ҫд���޸�ҳ���޸ı�־λ*/
    page[lnumber].write=1;
    }
   else
   {page_interrupt(lnumber);         			/*ȱҳ�ж�*/
    goto kk;
   }
  }/*�����������*/

 main( )
 {int lnumber,flag,pnumber,write,dnumber;
  unsigned laddress;
  int i;
  /*����ҳ�����Ϣ������ҳ��page*/
  printf("����ҳ�����Ϣ������ҳ����ҳ��Ϊ��1����������룩)\n");
  printf("����ҳ�ź͸����ַ:");
  scanf("%d%d",&lnumber,&dnumber);
  i=0;
  while(lnumber!=-1)
  {page[i].lnumber=lnumber;
   page[i].flag=0;
   page[i].write=0;
   page[i].dnumber=dnumber;
   i++;
   printf("����ҳ�ź͸����ַ:");
   scanf("%d%d",&lnumber,&dnumber);
  }
  page_length=i;
  printf("���������ţ��������ҪС��%d,(�ԣ�1������:",i);
  scanf("%d",&pnumber);
  m=0;
  head=0;
  while(pnumber!=-1)
  {if(m<=i)
   {page[m].pnumber=pnumber;
    page[m].flag=1;
    p[m]=m;
    m++;
    }
  scanf("%d",&pnumber);
  }
  printf("����ָ������(1-�޸�,0-����Ҫ��������������������)���߼���ַ:");
  scanf("%d%x",&write,&laddress);
  while(write==0||write==1)
  {command(laddress,write);				/* ִ��ָ��*/
   printf("����ָ������(1-�޸�,0-����Ҫ��������������������)���߼���ַ:");
   scanf("%d%x",&write,&laddress);
  }
 }/*main( )����*/
