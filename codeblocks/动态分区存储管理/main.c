#define  n  10    						/*假定系统允许的最大作业数量为n*/
#define  m  10    					/*假定系统允许的空闲区表最大为m*/
#define minisize 100
struct
{ float address;  						/*已分分区起始地址*/
 float length;      						/*已分分区长度，单位为字节*/
 int flag;         						/*已分配区表登记栏标志，用“0”表示空栏目，实验中只支持一个字符的作业名*/
}used_table[n];  	 					/*已分配区表*/
struct
{float address;   						/*空闲区起始地址*/
 float length;   	 					/*空闲区长度，单位为字节*/
 int flag;       						/*空闲区表登记栏标志，用“0”表示空栏目，用“1”
表示未分配*/
}free_table[m];   						/*空闲区表*/

 allocate(J,xk)
/*采用最优分配算法分配xk大小的空间*/
 char J;
 float xk;
{int i,k;
  float ad;
  k=-1;
  for(i=0;i<m;i++)  					/*寻找空间大于xk的最小空闲区登记项k*/
   if(free_table[i].length>=xk&&free_table[i].flag==1)
     if(k==-1||free_table[i].length<free_table[k].length)
       k=i;
  if(k==-1)        					/*未找到可用空闲区，返回*/
  {printf("无可用空闲区\n");
   return;
  }
 /*找到可用空闲区，开始分配：若空闲区大小与要求分配的空间差小于minisize大小，则空闲区全部分配；若空闲区大小与要求分配的空间差大于minisize大小，则从空闲区划出一部分分配*/
  if(free_table[k].length-xk<=minisize)
   {free_table[k].flag=0;
    ad=free_table[k].address;
    xk=free_table[k].length;
   }
  else
   {free_table[k].length=free_table[k].length-xk;
    ad=free_table[k].address+free_table[k].length;
   }
   /*修改已分配区表*/
  i=0;
  while(used_table[i].flag!=0&&i<n) 		/*寻找空表目*/
    i++;
  if(i>=n)                				/*无表目填写已分分区*/
  {printf("无表目填写已分分区，错误\n");
   /*修正空闲区表*/
   if(free_table[k].flag==0) 				/*前面找到的是整个空闲区*/
     free_table[k].flag=1;
   else                     			/*前面找到的是某个空闲区的一部分*/
    free_table[k].length=free_table[k].length+xk;
   return;
   }
  else                      			/*修改已分配区表*/
  {used_table[i].address=ad;
   used_table[i].length=xk;
   used_table[i].flag=J;
   }
  return;
 }/*主存分配函数结束*/

 reclaim(J)
/*回收作业名为J的作业所占主存空间*/
 char J;
{int i,k,j,s,t;
  float S,L;
  /*寻找已分配区表中对应登记项*/
  s=0;
  while((used_table[s].flag!=J||used_table[s].flag==0)&&s<n)
    s++;
  if(s>=n)                  			/*在已分配区表中找不到名字为J的作业*/
  {printf("找不到该作业\n");
   return;
   }
  /*修改已分配区表*/
  used_table[s].flag=0;
  /*取得归还分区的起始地址S和长度L*/
  S=used_table[s].address;
  L=used_table[s].length;
  j=-1;k=-1;i=0;
 /*寻找回收分区的上下邻空闲区，上邻表目k，下邻表目j*/
  while(i<m&&(j==-1||k==-1))
  {if(free_table[i].flag==0)
   {if(free_table[i].address+free_table[i].length==S)k=i; 	/*找到上邻*/
if(free_table[i].address==S+L)j=i;     	/*找到下邻*/
 }
    i++;
   }
  if(k!=-1)
    if(j!=-1)               				/* 上邻空闲区，下邻空闲区，三项合并*/
    {free_table[k].length=free_table[j].length+free_table[k].length+L;
     free_table[j].flag=0;
     }
    else                    			/* 上邻空闲区，下邻非空闲区，与上邻合并*/
    free_table[k].length=free_table[k].length+L;
  else
    if(j!=-1)              				/*上邻非空闲区，下邻为空闲区，与下邻合并*/
     {free_table[j].address=S;
      free_table[j].length=free_table[j].length+L;
     }
    else                    			/*上下邻均为非空闲区，回收区域直接填入*/
     {								/*在空闲区表中寻找空栏目*/
      t=0;
      while(free_table[t].flag==1&&t<m)
        t++;
      if(t>=m)             			/*空闲区表满,回收空间失败,将已分配区表复原*/
      {printf("主存空闲表没有空间,回收空间失败\n");
       used_table[s].flag=J;
       return;
       }
      free_table[t].address=S;
      free_table[t].length=L;
      free_table[t].flag=1;
     }
  return 1;//(true);
  }/*主存归还函数结束*/

 main( )
 {int i,a;
  float xk;
  char J;
  /*空闲区表初始化*/
  free_table[0].address=10240;
  free_table[0].length=102400;
  free_table[0].flag=1;
  for(i=1;i<m;i++)
    free_table[i].flag=0;
  /*已分配区表初始化*/
  for(i=0;i<n;i++)
    used_table[i].flag=0;
  while(1)
  {printf("选择功能项（0-退出,1-分配主存,2-回收主存,3-显示主存）\n");
   printf("选择功项(0~3) :");
   scanf("%d",&a);
   switch(a)
   {case 0: exit(0);          			/*a=0程序结束*/
    case 1: 							/*a=1分配主存空间*/
	    printf("输入作业名J和作业所需长度xk: ");
	    scanf("%*c%c%f",&J,&xk);
	    allocate(J,xk)					;/*分配主存空间*/
	    break;
    case 2:                   			/*a=2回收主存空间*/
	    printf("输入要回收分区的作业名");
	    scanf("%*c%c",&J);
	    reclaim(J);						/*回收主存空间*/
	    break;
    case 3:                    			/*a=3显示主存情况，输出空闲区表和已分配区表*/
	    printf("输出空闲区表：\n起始地址  分区长度  标志\n");
        for(i=0;i<m;i++)
        printf("%5.0f%10.0f%6d\n",free_table[i].address,free_table[i].length, free_table[i].flag);
	    printf(" 按任意键,输出已分配区表\n");
        getch();
	    printf(" 输出已分配区表：\n起始地址  分区长度  标志\n");
	    for(i=0;i<n;i++)
	     if(used_table[i].flag!=0)
           printf("%6.0f%9.0f%6c\n",used_table[i].address,used_table[i].length, used_table[i].flag);
	     else
           printf("%6.0f%9.0f%6d\n",used_table[i].address,used_table[i].length, used_table[i].flag);
	     break;
     default:printf("没有该选项\n");
     }/*case*/
   }/*while*/
 }/*main( )结束*/
