#define n 64            				/*模拟实验中假定的页表长度*/
#define length 10
struct
{int  lnumber;							/*页号*/
 int  flag;              				/*表示页是否在主存，“1”表示在，“0”表示不在*/
 int  pnumber;          				/*该页所在主存块的块号*/
 int  write;             				/*该页是否被修改过，“1”表示修改过，“0”表示没
有修改过*/
 int  dnumber;          				/*该页存放在磁盘上的位置，即磁盘块号*/
}page[n];                				/*页表定义*/
int m;                   				/*m为作业在主存中的主存块块数*/
int page_length;           				/*页表实际长度*/
int p[length];            				/*存放在主存中页的页号*/
int head;								/*主存中页号队列头指针*/

 page_interrupt(lnumber)
 int lnumber;
 {int j;
  printf("发生缺页中断* %d\n",lnumber);
  /*淘汰页*/
  j=p[head];
  p[head]=lnumber;
  head=(head+1)%m;
  if (page[j].write==1)
    printf("将页 %d写回磁盘第%d块\n",j,page[j].dnumber);
  page[j].flag=0;                 		/*第j页存在标志改为“0”*/
  page[lnumber].pnumber=page[j].pnumber;
  page[lnumber].flag=1;          		/*第lnumber页存在标志改为“0”*/
  page[lnumber].write=0;         		/*第lunmber页修改标志改为“1”*/
  printf("淘汰主存块%2d中的页%2d，从磁盘第%d块中调入页%2d\n",  page[j].pnumber,j,page[lnumber].dnumber,lnumber);
  }/*缺页中断处理函数结束*/

  command(laddress,write)
  unsigned  laddress;
  int write;
  {unsigned paddress,ad,pnumber,lnumber;
   kk:
   /*取出逻辑地址laddress的页号lnumber（高6位）和页内地址ad*/
   lnumber=laddress>>10;
   ad=laddress&0x3ff;
   if(lnumber>=page_length)
    { printf("不存在该页\n");
      return;
    }
   if(page[lnumber].flag==1)      			/*页在主存*/
   {pnumber=page[lnumber].pnumber;			/*从页表中取得块号*/
    paddress=pnumber<<10|ad;    			/*合并块号和块内地址形成物理地址paddress*/
    printf("逻辑地址是：%x   对应物理地址是:%x\n",laddress,paddress);
    if(write==1)                				/*如果需要写，修改页的修改标志位*/
    page[lnumber].write=1;
    }
   else
   {page_interrupt(lnumber);         			/*缺页中断*/
    goto kk;
   }
  }/*命令处理函数结束*/

 main( )
 {int lnumber,flag,pnumber,write,dnumber;
  unsigned laddress;
  int i;
  /*输入页表的信息，创建页表page*/
  printf("输入页表的信息，创建页表（若页号为－1，则结束输入）)\n");
  printf("输入页号和辅存地址:");
  scanf("%d%d",&lnumber,&dnumber);
  i=0;
  while(lnumber!=-1)
  {page[i].lnumber=lnumber;
   page[i].flag=0;
   page[i].write=0;
   page[i].dnumber=dnumber;
   i++;
   printf("输入页号和辅存地址:");
   scanf("%d%d",&lnumber,&dnumber);
  }
  page_length=i;
  printf("输入主存块号，主存块数要小于%d,(以－1结束）:",i);
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
  printf("输入指令性质(1-修改,0-不需要，其他—结束程序运行)和逻辑地址:");
  scanf("%d%x",&write,&laddress);
  while(write==0||write==1)
  {command(laddress,write);				/* 执行指令*/
   printf("输入指令性质(1-修改,0-不需要，其他—结束程序运行)和逻辑地址:");
   scanf("%d%x",&write,&laddress);
  }
 }/*main( )结束*/
