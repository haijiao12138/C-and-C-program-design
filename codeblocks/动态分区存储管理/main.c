#define  n  10    						/*�ٶ�ϵͳ����������ҵ����Ϊn*/
#define  m  10    					/*�ٶ�ϵͳ����Ŀ����������Ϊm*/
#define minisize 100
struct
{ float address;  						/*�ѷַ�����ʼ��ַ*/
 float length;      						/*�ѷַ������ȣ���λΪ�ֽ�*/
 int flag;         						/*�ѷ�������Ǽ�����־���á�0����ʾ����Ŀ��ʵ����ֻ֧��һ���ַ�����ҵ��*/
}used_table[n];  	 					/*�ѷ�������*/
struct
{float address;   						/*��������ʼ��ַ*/
 float length;   	 					/*���������ȣ���λΪ�ֽ�*/
 int flag;       						/*��������Ǽ�����־���á�0����ʾ����Ŀ���á�1��
��ʾδ����*/
}free_table[m];   						/*��������*/

 allocate(J,xk)
/*�������ŷ����㷨����xk��С�Ŀռ�*/
 char J;
 float xk;
{int i,k;
  float ad;
  k=-1;
  for(i=0;i<m;i++)  					/*Ѱ�ҿռ����xk����С�������Ǽ���k*/
   if(free_table[i].length>=xk&&free_table[i].flag==1)
     if(k==-1||free_table[i].length<free_table[k].length)
       k=i;
  if(k==-1)        					/*δ�ҵ����ÿ�����������*/
  {printf("�޿��ÿ�����\n");
   return;
  }
 /*�ҵ����ÿ���������ʼ���䣺����������С��Ҫ�����Ŀռ��С��minisize��С���������ȫ�����䣻����������С��Ҫ�����Ŀռ�����minisize��С����ӿ���������һ���ַ���*/
  if(free_table[k].length-xk<=minisize)
   {free_table[k].flag=0;
    ad=free_table[k].address;
    xk=free_table[k].length;
   }
  else
   {free_table[k].length=free_table[k].length-xk;
    ad=free_table[k].address+free_table[k].length;
   }
   /*�޸��ѷ�������*/
  i=0;
  while(used_table[i].flag!=0&&i<n) 		/*Ѱ�ҿձ�Ŀ*/
    i++;
  if(i>=n)                				/*�ޱ�Ŀ��д�ѷַ���*/
  {printf("�ޱ�Ŀ��д�ѷַ���������\n");
   /*������������*/
   if(free_table[k].flag==0) 				/*ǰ���ҵ���������������*/
     free_table[k].flag=1;
   else                     			/*ǰ���ҵ�����ĳ����������һ����*/
    free_table[k].length=free_table[k].length+xk;
   return;
   }
  else                      			/*�޸��ѷ�������*/
  {used_table[i].address=ad;
   used_table[i].length=xk;
   used_table[i].flag=J;
   }
  return;
 }/*������亯������*/

 reclaim(J)
/*������ҵ��ΪJ����ҵ��ռ����ռ�*/
 char J;
{int i,k,j,s,t;
  float S,L;
  /*Ѱ���ѷ��������ж�Ӧ�Ǽ���*/
  s=0;
  while((used_table[s].flag!=J||used_table[s].flag==0)&&s<n)
    s++;
  if(s>=n)                  			/*���ѷ����������Ҳ�������ΪJ����ҵ*/
  {printf("�Ҳ�������ҵ\n");
   return;
   }
  /*�޸��ѷ�������*/
  used_table[s].flag=0;
  /*ȡ�ù黹��������ʼ��ַS�ͳ���L*/
  S=used_table[s].address;
  L=used_table[s].length;
  j=-1;k=-1;i=0;
 /*Ѱ�һ��շ����������ڿ����������ڱ�Ŀk�����ڱ�Ŀj*/
  while(i<m&&(j==-1||k==-1))
  {if(free_table[i].flag==0)
   {if(free_table[i].address+free_table[i].length==S)k=i; 	/*�ҵ�����*/
if(free_table[i].address==S+L)j=i;     	/*�ҵ�����*/
 }
    i++;
   }
  if(k!=-1)
    if(j!=-1)               				/* ���ڿ����������ڿ�����������ϲ�*/
    {free_table[k].length=free_table[j].length+free_table[k].length+L;
     free_table[j].flag=0;
     }
    else                    			/* ���ڿ����������ڷǿ������������ںϲ�*/
    free_table[k].length=free_table[k].length+L;
  else
    if(j!=-1)              				/*���ڷǿ�����������Ϊ�������������ںϲ�*/
     {free_table[j].address=S;
      free_table[j].length=free_table[j].length+L;
     }
    else                    			/*�����ھ�Ϊ�ǿ���������������ֱ������*/
     {								/*�ڿ���������Ѱ�ҿ���Ŀ*/
      t=0;
      while(free_table[t].flag==1&&t<m)
        t++;
      if(t>=m)             			/*����������,���տռ�ʧ��,���ѷ�������ԭ*/
      {printf("������б�û�пռ�,���տռ�ʧ��\n");
       used_table[s].flag=J;
       return;
       }
      free_table[t].address=S;
      free_table[t].length=L;
      free_table[t].flag=1;
     }
  return 1;//(true);
  }/*����黹��������*/

 main( )
 {int i,a;
  float xk;
  char J;
  /*���������ʼ��*/
  free_table[0].address=10240;
  free_table[0].length=102400;
  free_table[0].flag=1;
  for(i=1;i<m;i++)
    free_table[i].flag=0;
  /*�ѷ��������ʼ��*/
  for(i=0;i<n;i++)
    used_table[i].flag=0;
  while(1)
  {printf("ѡ�����0-�˳�,1-��������,2-��������,3-��ʾ���棩\n");
   printf("ѡ����(0~3) :");
   scanf("%d",&a);
   switch(a)
   {case 0: exit(0);          			/*a=0�������*/
    case 1: 							/*a=1��������ռ�*/
	    printf("������ҵ��J����ҵ���賤��xk: ");
	    scanf("%*c%c%f",&J,&xk);
	    allocate(J,xk)					;/*��������ռ�*/
	    break;
    case 2:                   			/*a=2��������ռ�*/
	    printf("����Ҫ���շ�������ҵ��");
	    scanf("%*c%c",&J);
	    reclaim(J);						/*��������ռ�*/
	    break;
    case 3:                    			/*a=3��ʾ����������������������ѷ�������*/
	    printf("�����������\n��ʼ��ַ  ��������  ��־\n");
        for(i=0;i<m;i++)
        printf("%5.0f%10.0f%6d\n",free_table[i].address,free_table[i].length, free_table[i].flag);
	    printf(" �������,����ѷ�������\n");
        getch();
	    printf(" ����ѷ�������\n��ʼ��ַ  ��������  ��־\n");
	    for(i=0;i<n;i++)
	     if(used_table[i].flag!=0)
           printf("%6.0f%9.0f%6c\n",used_table[i].address,used_table[i].length, used_table[i].flag);
	     else
           printf("%6.0f%9.0f%6d\n",used_table[i].address,used_table[i].length, used_table[i].flag);
	     break;
     default:printf("û�и�ѡ��\n");
     }/*case*/
   }/*while*/
 }/*main( )����*/
