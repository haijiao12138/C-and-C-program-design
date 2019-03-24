#define false 0
#define true 1
#include "stdio.h"
typedef struct
{ char name[3];							/*�ļ���Ŀ¼��*/
 char type[2];								/*�ļ�������*/
 char attribute;							/*����*/
 char address;							/*�ļ���Ŀ¼����ʼ�̿��*/
 char length;							/*�ļ����ȣ����̿�Ϊ��λ*/
}content;								/*Ŀ¼�ṹ*/
#define n 5 							/*ģ��ʵ����ϵͳ������ļ����������*/
typedef struct
{ int  dnum;							/*�����̿��*/
  int  bnum;							/*�����̿��ڵڼ����ֽ�*/
}pointer;								/*�Ѵ��ļ����ж�дָ��Ľṹ*/
typedef  struct
{char  name[20];						/*�ļ�����·����*/
 char  attribute;						/*�ļ������ԣ���1���ֽڱ�ʾ��char����*/
 int  number;							/*�ļ���ʼ�̿��*/
 int  length;							/*�ļ����ȣ��ļ�ռ�õ��ֽ���*/int  flag; 							/*�������ͣ��á�0����ʾ�Զ�������ʽ���ļ��ģ�
�á�1����ʾд������ʽ���ļ���*/
pointer  read;
pointer  write;								/*���ļ���λ�ã��ļ��մ�ʱdnumΪ�ļ���ʼ��
pointer  write;

					/*д�ļ���λ�ã��ļ��ս���ʱdnumΪ�ļ���ʼ��
���,bnumΪ��0�����ļ���ʱΪ�ļ���ĩβ*/
}OFILE;   							/*�Ѵ��ļ��������Ͷ���*/
struct
{OFILE  file[n];  						/*�Ѵ��ļ���*/
 int  length;							/*�Ѵ��ļ����еǼǵ��ļ�����*/
}openfile;								/*�Ѵ��ļ�����*/
char buffer1[64];						/*ģ�⻺��1*/
content buffer2[8];						/*ģ�⻺��2*/
FILE *fc;								/*ģ����̵��ļ���ָ��*/

int copen(x1,x2)
  OFILE *x1,*x2;
 {
   strcpy(x1->name,x2->name);
   x1->attribute=x2->attribute;
   x1->number=x2->number;
   x1->length=x2->length;
   x1->flag=x2->flag;
   x1->read.dnum=x2->read.dnum;
   x1->read.bnum=x2->read.bnum;
   x1->write.dnum=x2->write.dnum;
   x1->write.bnum=x2->write.bnum;
   return 1;
 }

  int sopen(name)
  /*���Ѵ��ļ����в����ļ�name*/
  char *name;
  {int i;
   i=0;
   /*���β����Ѵ��ļ���*/
   while(i<openfile.length&&strcmp(openfile.file[i].name,name)!=0)i++;
   if(i>=openfile.length)
    return(-1);
   return(i);
   }/*���Һ���sopen����*/

  dopen(name)
  /*���Ѵ��ļ�����ɾ���ļ�name*/
  char *name;
  {int i;
   i=sopen(name);
   if(i==-1)
     printf("�ļ�δ��\n");
   else
    {copen(&openfile.file[i],&openfile.file[openfile.length-1]);
     openfile.length--;
     }
   }/*ɾ������dopen����*/

  iopen(x)
  /*���Ѵ��ļ����в���n�ļ�x->ame*/
  content  *x;
  {int i;
   i=sopen(x->name);
   if(i!=-1)
    {printf("�ļ��Ѿ���\n");
     return(false);
    }
   else if(openfile.length==n)
    { printf("�Ѵ��ļ�������\n");
      return(false);
     }
   else
    {copen(&openfile.file[openfile.length],x);
     openfile.length++;
     return(true);
     }
  }/*��д�Ѵ��ļ���������*/

allocate( )
/*����һ�����̿飬���ؿ��*/
{int i;
 fseek(fc,0,SEEK_SET);					/*��ģ����̵��ļ�ָ������ģ�����FAT��*/
 fread(buffer1,64L,1,fc);					/*��FAT���е�һ���̿����ģ�⻺��buffer1��*/
 for(i=3;i<63;i++)
   if(buffer1[i]==0)						/*FAT�еĵ�i��Ϊ0,�����i����̿�,�޸�FAT��
,����д�ش���*/
    { buffer1[i]=255;
      fseek(fc,0,SEEK_SET);
      fwrite (buffer1,64L,1,fc);
      return(i);						/*���ش��̺�*/
    }
 fread(buffer1,64L,1,fc);					/*��FAT���еڶ����̿����ģ�⻺��buffer1��*/
 for(i=0;i<63;i++)
   if(buffer1[i]==0)						/*FAT�еĵ�i��Ϊ0,�����i��64����̿�,�޸�FAT
��,����д�ش���*/
   { buffer1[i]=255;
    fseek(fc,-64L,SEEK_CUR);
    fwrite(buffer1,64L,1,fc);
    return(i+64);						/*���ش��̺�*/
   }
 printf("�Ѿ�û�д��̿ռ�\n");
 return(false);
 }/*������̿麯������*/

read_file(name,length)
/*���ļ��������ļ�·����name����ȡ����length*/
 char *name;
 int length;
{int i,t;
 char ch;
  if((i=sopen(name))==-1)
  {printf("�ļ�û�д򿪻򲻴���\n");
   return(false);
   }
 if(openfile.file[i].flag==1)
  {printf("�ļ���д��ʽ�򿪣����ܶ�\n");
   return(false);
  }
  t=0;
  fseek(fc,openfile.file[i].read.dnum*64L,SEEK_SET);
  fread(buffer1,64,1,fc);
  while(t<length&&buffer1[openfile.file[i].read.bnum]!='#')
  {putchar(buffer1[openfile.file[i].read.bnum]);	/*����һ���ַ�������������Ļ����ʾ��*/
   if((t+1)%64==0)putchar('\n');
   /*�޸Ķ�ָ��*/
   openfile.file[i].read.bnum++;
   if(openfile.file[i].read.bnum>=64)		/*һ����꣬��ȡ��һ���̿�*/
    {fseek(fc,openfile.file[i].read.dnum/64*64, SEEK_SET);
     fread(buffer1,64,1,fc);
     openfile.file[i].read.dnum=buffer1[openfile.file[i].read.dnum%64];	/*�޸Ķ�ָ��*/
     openfile.file[i].read.bnum=0;
     fseek(fc,openfile.file[i].read.dnum*64L,SEEK_SET);
     fread(buffer1,64,1,fc);				/*��ȡ��һ��*/
    }
   t++;
  }
 }/*����������*/

write_file(name,buff,length)
/*д�ļ�����*/
 char *name;							/*�ļ�·����*/
 char *buff;							/*���׼��д����̵�����*/
 int length;							/*д�����ݵĳ���*/
{int i,t,dd;
  if((i=sopen(name))==-1)				/*�ļ������ڣ��޷�д*/
  {printf("�ļ�û�д򿪻򲻴���\n");
   return(false);
   }
  if(openfile.file[i].flag==0)
  {printf("�ļ��Զ���ʽ�򿪣�����д\n");
   return(false);
  }
  t=0;
  fseek(fc,openfile.file[i].write.dnum*64L, SEEK_SET);
  fread(buffer1,64,1,fc);
  while(t<length)
  {buffer1[openfile.file[i].write.bnum]=buff[t];
   openfile.file[i].write.bnum++;
   openfile.file[i].length++;
   if(openfile.file[i].write.bnum>=64)
    {fseek(fc, openfile.file[i].write.dnum*64L, SEEK_SET);
     fwrite(buffer1,64,1,fc);				/*һ��д�꣬д�ش���*/
     if((dd=allocate())==false)
      { openfile.file[i].write.bnum--;
        printf("�޴��̿ռ�,������Ϣ��ʧ��дʧ��\n");
        return(false);
       }/*if*/
     fseek(fc,openfile.file[i].write.dnum/64*64L, SEEK_SET);
     fread(buffer1,64,1,fc);
     buffer1[openfile.file[i].write.dnum%64]=dd;
     fseek(fc,openfile.file[i].write.dnum/64*64L, SEEK_SET);
     fwrite(buffer1,64,1,fc);
     openfile.file[i].write.dnum=dd;
     openfile.file[i].write.bnum=0;
    }/*if*/
   t++;
  }/*while*/
  fseek(fc, openfile.file[i].write.dnum*64L, SEEK_SET);
  fwrite(buffer1,64,1,fc);					/*һ��д�꣬д�ش���*/
}/*д��������*/

search(name,flag,dnum,bnum)
/*����·����Ϊname���ļ���Ŀ¼,���ظ�Ŀ¼����ʼ�̿��*/
  char *name;
  int  flag;							/*flag=8��ʾ����Ŀ¼,����Ϊ�ļ�*/
  int *dnum,*bnum;						/*�����ļ���Ŀ¼��Ŀ¼��Ǽ�λ�ã��̿�dnum��
��bnum��*/
 {int k,i,s,t,j,last=0;
  char pna[3],type[2];
  if((strcmp(name,"")==0)||(strcmp(name,"/")==0))/*��Ŀ¼*/
    return(2);
  k=0;
  if(name[0]=='/')k=1;
  i=2;								/* i=��Ŀ¼����ʼ�̿��*/
  while(last!=1)
  {/* pna=��name�з����"/"��һ��Ŀ¼�������ļ�����*/
   for(s=0;name[k]!='.'&&name[k]!='/'&&s<3&&name[k]!='\0';s++,k++)
     pna[s]=name[k];
   for(;s<3;s++)						/*�ÿո�ȫ���ֳ���*/
     pna[s]=' ';
   while(name[k]!='.'&&name[k]!='\0'&&name[k]!='/')/*��ȥ�����ַ�*/
     k++;
   type[0]=type[1]=' ';
   if(name[k]=='.')						/*ȡ�ļ�������type*/
     if(flag==8)
      {printf("Ŀ¼��Ӧ������������,����ʧ��\n");
       return(false);
      }
     else
     {/*�ļ�������������Ϊ����,������ַ�����*/
      k++;
      if(name[k]!='\0')type[0]=name[k];
      k++;
      if(name[k]!='\0')type[1]=name[k];
      if(name[k]!='\0'&&name[k+1]!='\0')
       {	printf("�ļ�������\n");
	    return(false);
       }
      last=1;
     }
   else
     if(name[k]!='\0')k++;
   if(name[k]=='\0')
     last=1;
   /*�������ֵ���pna��Ŀ¼��*/
   fseek(fc,i*64L,SEEK_SET);
   fread(buffer2,64L,1,fc);
   j=0;
   if(last==1&&flag!=8)						/*��������pna��������type���ļ�Ŀ¼��*/
    while(j<8&&!(buffer2[j].attribute!=8&&buffer2[j].name[0]==pna[0]&&
        buffer2[j].name[1]==pna[1]&&buffer2[j].name[2]==pna[2]&&
        buffer2[j].type[0]==type[0]&&buffer2[j].type[1]==type[1]))
         j++;
   else								   /*�������ֵ���pna��Ŀ¼��*/
    while(j<8&&!(buffer2[j].attribute==8&&buffer2[j].name[0]==pna[0]&&buffer2[j].name[1]==pna[1]&&buffer2[j].name[2]==pna[2]))
         j++;
   if(j<8)								/*�ҵ���Ŀ¼���ļ�*/
     if(last==1)						/*���ҽ���*/
      {*dnum=i;
       *bnum=j;
       return(buffer2[j].address);
      }
      else							/*���һ�δ����*/
       i=buffer2[j].address; 				/*��ȡ��һ���̿�*/
   else
    { printf("·������\n");
      return(false);
    }
  }/*while ���ҽ���*/
  }/*search()����*/

create_file(name,attribute)
 /*�����ļ�������·����name,�ļ�����attribute*/
  char *name;
  int attribute;
 {int dnum,bnum,i,j,last,k,s,d,t,tt,b,dd,flag,dn,bn;
  char dname[3],tname[2],pathname[20];
  OFILE x;
  if(attribute%2==1)
   {printf("ֻ���ļ�,�޷�д,���ܽ���\n");
    return(false);
   }
  if(openfile.length==n)
   {printf("�Ѵ򿪱�����,���ܽ���\n");
    return(false);
   }
  /*��name�ֳ������֣�Ŀ¼·��pathname��Ŀ¼��dname*/
  for(j=0;name[j]!='\0';j++)				/*�������һ����/��*/
    if(name[j]=='/')s=j;
  /*����Ŀ¼·��*/
  for(j=0;j<s;j++)
    pathname[j]=name[j];
  pathname[j]='\0';
  /*�����ļ���*/
  for(k=0,j=s+1;name[j]!='\0'&&k<3&&name[j]!='.';j++,k++)
    dname[k]=name[j];
  if(k==0)
  {printf("�����ļ�����Ŀ¼��\n");
   return(false);
  }
  for(;k<3;k++)
    dname[k]=' ';
  k=0;
  if(name[j++]=='.')						/*����������*/
  { for(;name[j]!='\0'&&k<2&&name[j]!='.';j++,k++)
     tname[k]=name[j];
  }
  for(;k<2;k++)
    tname[k]=' ';
  if((d=search(pathname,8,&dn,&bn))==false)	/*�ҵ�Ŀ¼·��*/
  {printf("Ŀ¼�����ڣ����ܽ���");
   return(false);
  }
  /*ȷ�ϸ�Ŀ¼�����ڵ�ͬʱ���ҿ�Ŀ¼��*/
   b=-1;
   fseek(fc,d*64L,SEEK_SET);
   fread(buffer2,64L,1,fc); 				/*����d�̿������*/
   for(t=0;t<8;t++)
    {if(buffer2[t].name[0]==dname[0]&&buffer2[t].name[1]==dname[1]&&buffer2[t].name[2]==dname[2]&&buffer2[t].type[0]==tname[0]&&buffer2[t].type[1]==tname[1])
     {/*�ҵ�����dname���ļ�������ʧ��*/
      printf("�ļ��Ѿ����ڣ����ܽ���\n");
      return(false);
     }
    if(buffer2[t].name[0]=='$'&&b==-1)
      b=t;
   }/*for*/
   if(b==-1)							/*û�п�Ŀ¼�����ʧ��*/
    { printf("Ŀ¼�޿ռ�\n");
      return(false);
      }
   if((dd=allocate( ))==false)				/*���������Ŀ¼�Ĵ����̿�dd*/
     { printf("�����ļ�ʧ��\n");
       return(false);
      }
   /*��дĿ¼��*/
   for(i=0;i<3;i++)
     buffer2[b].name[i]=dname[i];
   for(i=0;i<2;i++)
     buffer2[b].type[i]=tname[i];
   buffer2[b].attribute=attribute;
   buffer2[b].address=dd;
   buffer2[b].length=0;
   fseek(fc,d*64L,SEEK_SET);
   fwrite(buffer2,64L,1,fc);
   /*��д�Ѵ��ļ���*/
   strcpy(x.name,name);
   x.attribute=attribute;
   x.number=dd;
   x.length=0;
   x.flag=1;
   x.read.dnum=x.write.dnum=dd;
   x.read.bnum=x.write.bnum=0;
   iopen(&x);
 }/*�����ļ�����*/

 open_file(name,attribute)
 /*���ļ�����*/
  char *name;
  int  attribute;
 {OFILE x;
  int dnum,bnum,last,i,d;
  if((d=search(name,4,&dnum,&bnum))==false)
  {printf("�ļ������ڣ��򿪲���ʧ��\n");
   return(false);
  }
  fseek(fc,dnum*64L,SEEK_SET);			/*������ӦĿ¼��*/
  fread(buffer2,64,1,fc);
  if((buffer2[bnum].attribute%2==1)&& attribute==1)/*��ֻ���ļ�Ҫ��д*/
   { printf("�ļ�����д����ʧ��");
     return(false);
     }
   strcpy(x.name,name);
   x.attribute=buffer2[bnum].attribute;
   x.number=buffer2[bnum].address;
   x.read.dnum=x.write.dnum=buffer2[bnum].address;
   x.read.bnum=x.write.bnum=0;
   x.flag=attribute;
   if(attribute==1)
    {while(d!='\xff')						/*Ѱ���ļ�ĩβ*/
     {fseek(fc, d/64*64L, SEEK_SET);
      fread(buffer1,64L,1,fc);				/*����dnum������FAT*/
      last=d;
      d=buffer1[d%64];					/*����dnum����һ�����ݸ���dnum*/
     }/*while*/
     x.write.dnum=last;					/*��ддָ��*/
     fseek(fc, last*64L, SEEK_SET);
     fread(buffer1,64L,1,fc);
     for(i=0;i<64&&buffer1[i]!='#';i++);
     x.write.bnum=i;
     x.length=(buffer2[bnum].length-1)*64+i;
   }
   iopen(&x);							/*��д�Ѵ��ļ���*/
  }

 close_file(name)
 /*�ر��ļ�����*/
 char *name;
 {int i,dnum,bnum;
  if((i=sopen(name))==-1)
  {printf("�򿪵��ļ���û�и��ļ�,�ر�ʧ��\n");
   return(false);
   }
  if(openfile.file[i].flag==1)				/*д�ļ���׷���ļ�������*/
   {fseek(fc,openfile.file[i].write.dnum*64L, SEEK_SET);
    fread(buffer1,64,1,fc);
    buffer1[openfile.file[i].write.bnum]='#';
    fseek(fc,openfile.file[i].write.dnum*64L, SEEK_SET);
    fwrite(buffer1,64,1,fc);
    fputc('#',fc);
   search(name,4,&dnum,&bnum);			/*���Ҹ��ļ�Ŀ¼λ��*/
   /*�޸�Ŀ¼�е��ļ�����*/
   fseek(fc,dnum*64L, SEEK_SET);
   fread(buffer2,64,1,fc);
   buffer2[bnum].length=openfile.file[i].length/64+1;
   fseek(fc, dnum*64L, SEEK_SET);
   fwrite(buffer2,64,1,fc);
   }
  /*���Ѵ��ļ�����ɾ�����ļ��ĵǼ���*/
   if(openfile.length>1)
     copen(&openfile.file[i],&openfile.file[openfile.length-1]);
  openfile.length--;
  }

delete(name)
/*ɾ���ļ�*/
 char *name;
{
 int dnum,bnum,t;
if((t=search(name,4,&dnum,&bnum))==false)	/*�����ļ�*/
  {printf("�ļ�������\n");
   return(false);
  }
if(sopen(name)!=-1)						/*�ļ��򿪣�����ɾ��*/
 { printf("���ļ��򿪣�����ɾ��\n");
   return(false);
  }
 fseek(fc,dnum*64L, SEEK_SET);
 fread(buffer2,64,1,fc);
 buffer2[bnum].name[0]='$';				/*�����ļ���Ŀ¼�óɿ�Ŀ¼*/
 fseek(fc,dnum*64L, SEEK_SET);
 fwrite(buffer2,64,1,fc);
 while(t!='\xff')							/*ͨ��FAT����ÿһ���̿�ţ�������ɾ��*/
  {dnum=t;
   fseek(fc, dnum/64*64, SEEK_SET);
   fread(buffer1,64,1,fc);
   t=buffer1[dnum%64];
   buffer1[dnum%64]=0;
   fseek(fc, dnum/64*64L, SEEK_SET);
   fwrite(buffer1,64,1,fc);
  }
 }/*�ļ�ɾ������*/

 md(name)
 /*����Ŀ¼������Ŀ¼·����name*/
  char *name;
 {int dnum,bnum,i,j,last,k,s,d,t,tt,b,dd,flag,dn,bn;
  char dname[3],pathname[20];
  i=2;								/* i=��Ŀ¼����ʼ�̿��*/
  /*��name�ֳ������֣�Ŀ¼·��pathname��Ŀ¼��dname*/
  for(j=0;name[j]!='\0';j++)				/*�������һ����/��*/
    if(name[j]=='/')s=j;
  /*����Ŀ¼·��*/
  for(j=0;j<s;j++)
    pathname[j]=name[j];
  pathname[j]='\0';
  /*����Ŀ¼��*/
  for(k=0,j=s+1;name[j]!='\0'&&k<3&&name[j]!='.';j++,k++)
    dname[k]=name[j];
  if(k==0)
  {printf("�����ļ�����Ŀ¼��\n");
   return(false);
  }
  for(;k<3;k++)
    dname[k]=' ';
  if((d=search(pathname,8,&dn,&bn))==false)	/*�ҵ�Ŀ¼·��*/
  {printf("Ŀ¼�����ڣ����ܽ���\n");
   return(false);
  }
  b=-1;
 /*ȷ�ϸ�Ŀ¼�����ڵ�ͬʱ���ҿ�Ŀ¼��*/
   fseek(fc,d*64L,SEEK_SET);
   fread(buffer2,64L,1,fc);				/*����d�̿������*/
   for(t=0;t<8;t++)
    { if(buffer2[t].name[0]==dname[0]&&buffer2[t].name[1]==dname[1]
      &&buffer2[t].name[2]==dname[2]&&buffer2[t].attribute==8)
     {/*�ҵ�����dname��Ŀ¼������ʧ��*/
      printf("Ŀ¼�Ѿ����ڣ����ܽ���\n");
      return(false);
     }
    if(buffer2[t].name[0]=='$'&&b==-1)
       b=t;
    }/*for*/
   if(b==-1)							/*û�п�Ŀ¼����ܽ���*/
    { printf("Ŀ¼�޿ռ�\n");
      return(false);
    }
    if((dd=allocate( ))==false)				/*���������Ŀ¼�Ĵ����̿�dd*/
     { printf("û�д��̿ռ�\n");
       return(false);
      }
   /*��дĿ¼��*/
   for(i=0;i<3;i++)
     buffer2[b].name[i]=dname[i];
   buffer2[b].type[0]=buffer2[b].type[1]=' ';
   buffer2[b].attribute=8;
   buffer2[b].address=dd;
   buffer2[b].length=0;
   fseek(fc,d*64L,SEEK_SET);
   fwrite(buffer2,64L,1,fc);
   /*�ָ��½�Ŀ¼���̿��ʼ��*/
   for(t=0;t<8;t++)
    buffer2[t].name[0]='$';
   fseek(fc, dd*64L, SEEK_SET);
   fwrite(buffer2,64L,1,fc);
 }/*����Ŀ¼����*/

 dir(name)
/*��ʾĿ¼����*/
 char *name;
 {int i,bnum,t,tt,dnum,dn,bn;
  if((dnum=search(name,8,&dn,&bn))==false)	/*�ҵ�Ŀ¼·��*/
  { printf("Ŀ¼������\n");
    return(false);
   }
  printf("����  ��չ��  ��ʼ�̿�  ����\n");
 /*��ʾĿ¼����*/
  fseek(fc,dnum*64L, SEEK_SET);
  fread(buffer2,64L,1,fc);
  for(t=0;t<8;t++)						/*��ʾ���̿���Ŀ¼�������*/
  if(buffer2[t].name[0]!='$')
   printf(" %c%c%c    %c%c    %4d%7d\n", buffer2[t].name[0], buffer2[t].name[1],buffer2[t].name[2],buffer2[t].type[0],buffer2[t].type[1],buffer2[t].address,
buffer2[t].length);
 }/*��ʾĿ¼��������*/

rd(name)
/*ɾ����Ŀ¼*/
 char *name;
{
 int dnum,bnum,t,i;
if((t=search(name,8,&dnum,&bnum))==false)	/*�����ļ�*/
  {printf("Ŀ¼������\n");
   return(false);
  }
if(strcmp(name,"/")==0)						/*��Ŀ¼����ɾ��*/
 { printf("��Ŀ¼Ϊ��Ŀ¼������ɾ��\n");
   return(false);
  }
fseek(fc,t*64L, SEEK_SET);			/*�жϸ���Ŀ¼�Ƿ�Ϊ��Ŀ¼*/
fread(buffer2,64,1,fc);
int flag=1;
for(i=0;i<8;i++)
if(buffer2[bnum].name[0]!='$')flag=0;
if(flag==0)						/*�ǿ�Ŀ¼����ɾ��*/
 { printf("��Ŀ¼Ϊ�ǿ�Ŀ¼������ɾ��\n");
   return(false);
  }
 fseek(fc,dnum*64L, SEEK_SET);			/*ɾ����Ŀ¼*/
 fread(buffer2,64,1,fc);
 buffer2[bnum].name[0]='$';				/*�����ļ���Ŀ¼�óɿ�Ŀ¼*/
 fseek(fc,dnum*64L, SEEK_SET);
 fwrite(buffer2,64,1,fc);
 fseek(fc,t/64*64, SEEK_SET); 		/*ɾ������Ŀ¼ռ�õ��̿�*/
 fread(buffer1,64,1,fc);
 t=buffer1[t%64];
 buffer1[t%64]=0;
 fseek(fc, t/64*64L, SEEK_SET);
 fwrite(buffer1,64,1,fc);
}


typefile(name)
/*��ʾ�ļ�����*/
 char *name;
{int i,dnum,dn,bn,t;
 if((dnum=search(name,1,&dn,&bn))==false)
  {printf("�ļ�������\n");
   return(false);
  }
  if(sopen(name)!=-1)
  {printf("���ļ��򿪣�������ʾ\n");
   return(false);
  }
  while(dnum!='\xff')
  {fseek(fc,dnum*64L,SEEK_SET);
   fread(buffer1,64,1,fc);						/*��һ���̿鵽����*/
   for(t=0;t<64&&buffer1[t]!='#';t++)			/*��ʾ��������*/
    putchar(buffer1[t]);
   printf("\n");
    }
   /*�����һ���̿�*/
   fseek(fc, dnum/64*64L, SEEK_SET);
   fread(buffer1,64,1,fc);
   dnum=buffer1[dnum%64];
  }
 /*��ʾ�ļ���������*/

 change(name,attribute)
 /*�ı��ļ�name������Ϊattribute*/
  char *name;
  int attribute;
 {int dnum,bnum;
  if(search(name,1,&dnum,&bnum)==false)		/*�����ļ�Ŀ¼*/
  { printf("�ļ�������\n");
    return(false);
   }
 if(sopen(name)!=-1)
 { printf("���ļ��򿪣����ܸı��ļ�����\n");
   return(false);
  }
  fseek(fc,dnum*64L,SEEK_SET);
  fread(buffer2,64,1,fc);					/*������Ŀ¼�����̿�*/
  buffer2[bnum].attribute=attribute;			/*�޸�����*/
  fseek(fc,dnum*64L,SEEK_SET);
  fwrite(buffer2,64,1,fc);					/*д�ش���*/
 }/*�ı��ļ����Ժ�������*/

 main( )
 {char name[20],buffer[64];
  int attribute,type,length,i,a,j;
  /*�����ļ���ģ�����*/
  if((fc=fopen("c:\\c","w+"))==NULL)
  {printf("�޷����ļ�\n");
   exit(0);
  }
  /*��ʼ���Ѵ��ļ���*/
  openfile.length=0;
  /*��ʼ������*/
  /*��ʼ���ļ������*/
  buffer1[0]=buffer1[1]=buffer1[2]=255;		/*���̵�0��1����FAT����2���Ÿ�Ŀ¼*/
  for(i=3;i<64;i++)
   buffer1[i]=0;
  buffer1[13]=buffer1[49]=254;			/*�ٶ�ģ����������������̿飺��13���49��*/
  fwrite(buffer1,64L,1,fc);
  for(i=0;i<64;i++)
   buffer1[i]=0;
  fwrite(buffer1,64L,1,fc);
  /*��ʼ����Ŀ¼*/
  for(i=0;i<8;i++)
   buffer2[i].name[0]='$';					/*��Ŀ¼���һ���ַ�Ϊ��$����ʾ��Ŀ¼��Ϊ��*/
  fwrite(buffer2,64L,1,fc);
  /*��ʼ���Ѵ��ļ���*/
  while(1)
   {printf("\n  0 - ����\n");
    printf("  1 - �����ļ�\n");
    printf("  2 - ���ļ�\n");
    printf("  3 - ���ļ�\n");
    printf("  4 - д�ļ�\n");
    printf("  5 - �ر��ļ�\n");
    printf("  6 - ɾ���ļ�\n");
    printf("  7 - ����Ŀ¼\n");
    printf("  8 - ��ʾĿ¼����\n");
    printf("  9 �C ɾ��Ŀ¼\n");
    printf(" 10 - ��ʾ�ļ�����\n");
    printf(" 11 - �ı��ļ�����\n");
    printf(" ѡ�����0~9��:");
    scanf("%d",&a);
    switch(a)
    {
      case 0:							 /*a=0�������*/
              fclose(fc);
              exit(0);
      case 1: 							/*a=1�����ļ�*/
              printf("�����ļ�·�������ļ����ԣ�1-ֻ���ļ���3-ֻ��ϵͳ�ļ���4-��ͨ�ļ���:");
              scanf("%s%d",name,&attribute);
              create_file(name,attribute); 	/*�����ļ�*/
              break;
      case 2: 							/*a=2���ļ�*/
              printf("�����ļ�·�����Ͳ������ͣ�0-���ļ���1-д�ļ���:");
              scanf("%s%d",name,&type);
              open_file(name,type);   	/*���ļ�*/
              break;
      case 3: 							/*a=3���ļ�*/
              printf("�����ļ�·�����Ͷ�����");
              scanf("%s%d",name,&length);
              read_file(name,length);  	/*���ļ�*/
              break;
      case 4: 							/*a=4д�ļ�*/
              printf("�����ļ�·����:");
              scanf("%s",name);
              printf("����д�����ݺͺ�д����");
              scanf("%s%d",buffer,&length);
              write_file(name,buffer,length); /*д�ļ�*/
              break;
      case 5: 							/*a=5�ر��ļ�*/
              printf("�����ļ�·����");
              scanf("%s",name);
              close_file(name);     		/*�ر��ļ�*/
              break;
      case 6:  						/*a=6ɾ���ļ�*/
              printf("�����ļ�·����");
              scanf("%s",name);
              delete(name);    			/*ɾ���ļ�*/
              break;
      case 7: 							/*a=7����Ŀ¼*/
              printf("����Ŀ¼·����");
              scanf("%s",name);
              md(name);    			/*����Ŀ¼*/
              break;
      case 8: 							/*a=8��ʾĿ¼*/
              printf("����Ŀ¼·����");
              scanf("%s",name);
              dir(name);  				/*��ʾĿ¼*/
              break;
      case 9: 							/*a=9ɾ��Ŀ¼*/
              printf("����Ŀ¼·����");
              scanf("%s",name);
              rd(name);  				/*ɾ��Ŀ¼*/
              break;
      case 10: 							/*a=10��ʾ�ļ�*/
              printf("�����ļ�·����");
              scanf("%s",name);
              typefile(name);  			/*��ʾ�ļ�*/
              break;
      case 11:							/* a=11�ı��ļ����� */
              printf("�����ļ�·�������ļ����ԣ�1-ֻ���ļ���3-ֻ��ϵͳ�ļ���4-��ͨ�ļ�����");
              scanf("%s%d",name,&attribute);
              change(name,attribute);
      }/* switch */
    }/* while */
  }/*main( )����*/
