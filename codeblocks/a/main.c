#define false 0
#define true 1
#include "stdio.h"
typedef struct
{ char name[3];							/*文件或目录名*/
 char type[2];								/*文件类型名*/
 char attribute;							/*属性*/
 char address;							/*文件或目录的起始盘块号*/
 char length;							/*文件长度，以盘块为单位*/
}content;								/*目录结构*/
#define n 5 							/*模拟实验中系统允许打开文件的最大数量*/
typedef struct
{ int  dnum;							/*磁盘盘块号*/
  int  bnum;							/*磁盘盘块内第几个字节*/
}pointer;								/*已打开文件表中读写指针的结构*/
typedef  struct
{char  name[20];						/*文件绝对路径名*/
 char  attribute;						/*文件的属性，用1个字节表示，char类型*/
 int  number;							/*文件起始盘块号*/
 int  length;							/*文件长度，文件占用的字节数*/int  flag; 							/*操作类型，用“0”表示以读操作方式开文件的，
用“1”表示写操作方式打开文件的*/
pointer  read;
pointer  write;								/*读文件的位置，文件刚打开时dnum为文件起始盘
pointer  write;

					/*写文件的位置，文件刚建立时dnum为文件起始盘
块号,bnum为“0”，文件打开时为文件的末尾*/
}OFILE;   							/*已打开文件表项类型定义*/
struct
{OFILE  file[n];  						/*已打开文件表*/
 int  length;							/*已打开文件表中登记的文件数量*/
}openfile;								/*已打开文件表定义*/
char buffer1[64];						/*模拟缓冲1*/
content buffer2[8];						/*模拟缓冲2*/
FILE *fc;								/*模拟磁盘的文件的指针*/

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
  /*在已打开文件表中查找文件name*/
  char *name;
  {int i;
   i=0;
   /*依次查找已打开文件表*/
   while(i<openfile.length&&strcmp(openfile.file[i].name,name)!=0)i++;
   if(i>=openfile.length)
    return(-1);
   return(i);
   }/*查找函数sopen结束*/

  dopen(name)
  /*在已打开文件表中删除文件name*/
  char *name;
  {int i;
   i=sopen(name);
   if(i==-1)
     printf("文件未打开\n");
   else
    {copen(&openfile.file[i],&openfile.file[openfile.length-1]);
     openfile.length--;
     }
   }/*删除函数dopen结束*/

  iopen(x)
  /*在已打开文件表中插入n文件x->ame*/
  content  *x;
  {int i;
   i=sopen(x->name);
   if(i!=-1)
    {printf("文件已经打开\n");
     return(false);
    }
   else if(openfile.length==n)
    { printf("已打开文件表已满\n");
      return(false);
     }
   else
    {copen(&openfile.file[openfile.length],x);
     openfile.length++;
     return(true);
     }
  }/*填写已打开文件表函数结束*/

allocate( )
/*分配一个磁盘块，返回块号*/
{int i;
 fseek(fc,0,SEEK_SET);					/*将模拟磁盘的文件指针移至模拟磁盘FAT表*/
 fread(buffer1,64L,1,fc);					/*将FAT表中第一个盘块读入模拟缓冲buffer1中*/
 for(i=3;i<63;i++)
   if(buffer1[i]==0)						/*FAT中的第i项为0,分配第i块磁盘块,修改FAT表
,并且写回磁盘*/
    { buffer1[i]=255;
      fseek(fc,0,SEEK_SET);
      fwrite (buffer1,64L,1,fc);
      return(i);						/*返回磁盘号*/
    }
 fread(buffer1,64L,1,fc);					/*将FAT表中第二个盘块读入模拟缓冲buffer1中*/
 for(i=0;i<63;i++)
   if(buffer1[i]==0)						/*FAT中的第i项为0,分配第i＋64块磁盘块,修改FAT
表,并且写回磁盘*/
   { buffer1[i]=255;
    fseek(fc,-64L,SEEK_CUR);
    fwrite(buffer1,64L,1,fc);
    return(i+64);						/*返回磁盘号*/
   }
 printf("已经没有磁盘空间\n");
 return(false);
 }/*分配磁盘块函数结束*/

read_file(name,length)
/*读文件函数，文件路径名name，读取长度length*/
 char *name;
 int length;
{int i,t;
 char ch;
  if((i=sopen(name))==-1)
  {printf("文件没有打开或不存在\n");
   return(false);
   }
 if(openfile.file[i].flag==1)
  {printf("文件以写方式打开，不能读\n");
   return(false);
  }
  t=0;
  fseek(fc,openfile.file[i].read.dnum*64L,SEEK_SET);
  fread(buffer1,64,1,fc);
  while(t<length&&buffer1[openfile.file[i].read.bnum]!='#')
  {putchar(buffer1[openfile.file[i].read.bnum]);	/*读出一个字符（这里是在屏幕上显示）*/
   if((t+1)%64==0)putchar('\n');
   /*修改读指针*/
   openfile.file[i].read.bnum++;
   if(openfile.file[i].read.bnum>=64)		/*一块读完，读取下一个盘块*/
    {fseek(fc,openfile.file[i].read.dnum/64*64, SEEK_SET);
     fread(buffer1,64,1,fc);
     openfile.file[i].read.dnum=buffer1[openfile.file[i].read.dnum%64];	/*修改读指针*/
     openfile.file[i].read.bnum=0;
     fseek(fc,openfile.file[i].read.dnum*64L,SEEK_SET);
     fread(buffer1,64,1,fc);				/*读取下一个*/
    }
   t++;
  }
 }/*读函数结束*/

write_file(name,buff,length)
/*写文件函数*/
 char *name;							/*文件路径名*/
 char *buff;							/*存放准备写入磁盘的内容*/
 int length;							/*写入内容的长度*/
{int i,t,dd;
  if((i=sopen(name))==-1)				/*文件不存在，无法写*/
  {printf("文件没有打开或不存在\n");
   return(false);
   }
  if(openfile.file[i].flag==0)
  {printf("文件以读方式打开，不能写\n");
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
     fwrite(buffer1,64,1,fc);				/*一块写完，写回磁盘*/
     if((dd=allocate())==false)
      { openfile.file[i].write.bnum--;
        printf("无磁盘空间,部分信息丢失，写失败\n");
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
  fwrite(buffer1,64,1,fc);					/*一块写完，写回磁盘*/
}/*写函数结束*/

search(name,flag,dnum,bnum)
/*查找路径名为name的文件或目录,返回该目录的起始盘块号*/
  char *name;
  int  flag;							/*flag=8表示查找目录,否则为文件*/
  int *dnum,*bnum;						/*返回文件或目录的目录项登记位置，盘块dnum中
第bnum项*/
 {int k,i,s,t,j,last=0;
  char pna[3],type[2];
  if((strcmp(name,"")==0)||(strcmp(name,"/")==0))/*根目录*/
    return(2);
  k=0;
  if(name[0]=='/')k=1;
  i=2;								/* i=根目录的起始盘块号*/
  while(last!=1)
  {/* pna=从name中分离出"/"后一个目录名（或文件名）*/
   for(s=0;name[k]!='.'&&name[k]!='/'&&s<3&&name[k]!='\0';s++,k++)
     pna[s]=name[k];
   for(;s<3;s++)						/*用空格补全名字长度*/
     pna[s]=' ';
   while(name[k]!='.'&&name[k]!='\0'&&name[k]!='/')/*除去多余字符*/
     k++;
   type[0]=type[1]=' ';
   if(name[k]=='.')						/*取文件类型名type*/
     if(flag==8)
      {printf("目录不应该有有类型名,查找失败\n");
       return(false);
      }
     else
     {/*文件遇到类型名认为结束,后面的字符作废*/
      k++;
      if(name[k]!='\0')type[0]=name[k];
      k++;
      if(name[k]!='\0')type[1]=name[k];
      if(name[k]!='\0'&&name[k+1]!='\0')
       {	printf("文件名错误\n");
	    return(false);
       }
      last=1;
     }
   else
     if(name[k]!='\0')k++;
   if(name[k]=='\0')
     last=1;
   /*查找名字等于pna的目录项*/
   fseek(fc,i*64L,SEEK_SET);
   fread(buffer2,64L,1,fc);
   j=0;
   if(last==1&&flag!=8)						/*查找名字pna、类型名type的文件目录项*/
    while(j<8&&!(buffer2[j].attribute!=8&&buffer2[j].name[0]==pna[0]&&
        buffer2[j].name[1]==pna[1]&&buffer2[j].name[2]==pna[2]&&
        buffer2[j].type[0]==type[0]&&buffer2[j].type[1]==type[1]))
         j++;
   else								   /*查找名字等于pna的目录项*/
    while(j<8&&!(buffer2[j].attribute==8&&buffer2[j].name[0]==pna[0]&&buffer2[j].name[1]==pna[1]&&buffer2[j].name[2]==pna[2]))
         j++;
   if(j<8)								/*找到该目录或文件*/
     if(last==1)						/*查找结束*/
      {*dnum=i;
       *bnum=j;
       return(buffer2[j].address);
      }
      else							/*查找还未结束*/
       i=buffer2[j].address; 				/*读取下一个盘块*/
   else
    { printf("路径错误\n");
      return(false);
    }
  }/*while 查找结束*/
  }/*search()结束*/

create_file(name,attribute)
 /*建立文件函数，路径名name,文件属性attribute*/
  char *name;
  int attribute;
 {int dnum,bnum,i,j,last,k,s,d,t,tt,b,dd,flag,dn,bn;
  char dname[3],tname[2],pathname[20];
  OFILE x;
  if(attribute%2==1)
   {printf("只读文件,无法写,不能建立\n");
    return(false);
   }
  if(openfile.length==n)
   {printf("已打开表已满,不能建立\n");
    return(false);
   }
  /*将name分成两部分，目录路径pathname和目录名dname*/
  for(j=0;name[j]!='\0';j++)				/*查找最后一个“/”*/
    if(name[j]=='/')s=j;
  /*分离目录路径*/
  for(j=0;j<s;j++)
    pathname[j]=name[j];
  pathname[j]='\0';
  /*分离文件名*/
  for(k=0,j=s+1;name[j]!='\0'&&k<3&&name[j]!='.';j++,k++)
    dname[k]=name[j];
  if(k==0)
  {printf("错误文件名或目录名\n");
   return(false);
  }
  for(;k<3;k++)
    dname[k]=' ';
  k=0;
  if(name[j++]=='.')						/*分离类型名*/
  { for(;name[j]!='\0'&&k<2&&name[j]!='.';j++,k++)
     tname[k]=name[j];
  }
  for(;k<2;k++)
    tname[k]=' ';
  if((d=search(pathname,8,&dn,&bn))==false)	/*找到目录路径*/
  {printf("目录不存在，不能建立");
   return(false);
  }
  /*确认该目录不存在的同时查找空目录项*/
   b=-1;
   fseek(fc,d*64L,SEEK_SET);
   fread(buffer2,64L,1,fc); 				/*读出d盘块的内容*/
   for(t=0;t<8;t++)
    {if(buffer2[t].name[0]==dname[0]&&buffer2[t].name[1]==dname[1]&&buffer2[t].name[2]==dname[2]&&buffer2[t].type[0]==tname[0]&&buffer2[t].type[1]==tname[1])
     {/*找到名字dname的文件，建立失败*/
      printf("文件已经存在，不能建立\n");
      return(false);
     }
    if(buffer2[t].name[0]=='$'&&b==-1)
      b=t;
   }/*for*/
   if(b==-1)							/*没有空目录项，建立失败*/
    { printf("目录无空间\n");
      return(false);
      }
   if((dd=allocate( ))==false)				/*分配给建立目录的磁盘盘块dd*/
     { printf("建立文件失败\n");
       return(false);
      }
   /*填写目录项*/
   for(i=0;i<3;i++)
     buffer2[b].name[i]=dname[i];
   for(i=0;i<2;i++)
     buffer2[b].type[i]=tname[i];
   buffer2[b].attribute=attribute;
   buffer2[b].address=dd;
   buffer2[b].length=0;
   fseek(fc,d*64L,SEEK_SET);
   fwrite(buffer2,64L,1,fc);
   /*填写已打开文件表*/
   strcpy(x.name,name);
   x.attribute=attribute;
   x.number=dd;
   x.length=0;
   x.flag=1;
   x.read.dnum=x.write.dnum=dd;
   x.read.bnum=x.write.bnum=0;
   iopen(&x);
 }/*建立文件结束*/

 open_file(name,attribute)
 /*打开文件函数*/
  char *name;
  int  attribute;
 {OFILE x;
  int dnum,bnum,last,i,d;
  if((d=search(name,4,&dnum,&bnum))==false)
  {printf("文件不存在，打开操作失败\n");
   return(false);
  }
  fseek(fc,dnum*64L,SEEK_SET);			/*读出对应目录项*/
  fread(buffer2,64,1,fc);
  if((buffer2[bnum].attribute%2==1)&& attribute==1)/*对只读文件要求写*/
   { printf("文件不能写，打开失败");
     return(false);
     }
   strcpy(x.name,name);
   x.attribute=buffer2[bnum].attribute;
   x.number=buffer2[bnum].address;
   x.read.dnum=x.write.dnum=buffer2[bnum].address;
   x.read.bnum=x.write.bnum=0;
   x.flag=attribute;
   if(attribute==1)
    {while(d!='\xff')						/*寻找文件末尾*/
     {fseek(fc, d/64*64L, SEEK_SET);
      fread(buffer1,64L,1,fc);				/*读出dnum项所在FAT*/
      last=d;
      d=buffer1[d%64];					/*读出dnum块下一块内容赋给dnum*/
     }/*while*/
     x.write.dnum=last;					/*填写写指针*/
     fseek(fc, last*64L, SEEK_SET);
     fread(buffer1,64L,1,fc);
     for(i=0;i<64&&buffer1[i]!='#';i++);
     x.write.bnum=i;
     x.length=(buffer2[bnum].length-1)*64+i;
   }
   iopen(&x);							/*填写已打开文件表*/
  }

 close_file(name)
 /*关闭文件函数*/
 char *name;
 {int i,dnum,bnum;
  if((i=sopen(name))==-1)
  {printf("打开的文件中没有该文件,关闭失败\n");
   return(false);
   }
  if(openfile.file[i].flag==1)				/*写文件的追加文件结束符*/
   {fseek(fc,openfile.file[i].write.dnum*64L, SEEK_SET);
    fread(buffer1,64,1,fc);
    buffer1[openfile.file[i].write.bnum]='#';
    fseek(fc,openfile.file[i].write.dnum*64L, SEEK_SET);
    fwrite(buffer1,64,1,fc);
    fputc('#',fc);
   search(name,4,&dnum,&bnum);			/*查找该文件目录位置*/
   /*修改目录中的文件长度*/
   fseek(fc,dnum*64L, SEEK_SET);
   fread(buffer2,64,1,fc);
   buffer2[bnum].length=openfile.file[i].length/64+1;
   fseek(fc, dnum*64L, SEEK_SET);
   fwrite(buffer2,64,1,fc);
   }
  /*在已打开文件表中删除该文件的登记项*/
   if(openfile.length>1)
     copen(&openfile.file[i],&openfile.file[openfile.length-1]);
  openfile.length--;
  }

delete(name)
/*删除文件*/
 char *name;
{
 int dnum,bnum,t;
if((t=search(name,4,&dnum,&bnum))==false)	/*查找文件*/
  {printf("文件不存在\n");
   return(false);
  }
if(sopen(name)!=-1)						/*文件打开，不能删除*/
 { printf("该文件打开，不能删除\n");
   return(false);
  }
 fseek(fc,dnum*64L, SEEK_SET);
 fread(buffer2,64,1,fc);
 buffer2[bnum].name[0]='$';				/*将该文件的目录置成空目录*/
 fseek(fc,dnum*64L, SEEK_SET);
 fwrite(buffer2,64,1,fc);
 while(t!='\xff')							/*通过FAT查找每一个盘块号，并依次删除*/
  {dnum=t;
   fseek(fc, dnum/64*64, SEEK_SET);
   fread(buffer1,64,1,fc);
   t=buffer1[dnum%64];
   buffer1[dnum%64]=0;
   fseek(fc, dnum/64*64L, SEEK_SET);
   fwrite(buffer1,64,1,fc);
  }
 }/*文件删除结束*/

 md(name)
 /*建立目录函数，目录路径名name*/
  char *name;
 {int dnum,bnum,i,j,last,k,s,d,t,tt,b,dd,flag,dn,bn;
  char dname[3],pathname[20];
  i=2;								/* i=根目录的起始盘块号*/
  /*将name分成两部分，目录路径pathname和目录名dname*/
  for(j=0;name[j]!='\0';j++)				/*查找最后一个“/”*/
    if(name[j]=='/')s=j;
  /*分离目录路径*/
  for(j=0;j<s;j++)
    pathname[j]=name[j];
  pathname[j]='\0';
  /*分离目录名*/
  for(k=0,j=s+1;name[j]!='\0'&&k<3&&name[j]!='.';j++,k++)
    dname[k]=name[j];
  if(k==0)
  {printf("错误文件名或目录名\n");
   return(false);
  }
  for(;k<3;k++)
    dname[k]=' ';
  if((d=search(pathname,8,&dn,&bn))==false)	/*找到目录路径*/
  {printf("目录不存在，不能建立\n");
   return(false);
  }
  b=-1;
 /*确认该目录不存在的同时查找空目录项*/
   fseek(fc,d*64L,SEEK_SET);
   fread(buffer2,64L,1,fc);				/*读出d盘块的内容*/
   for(t=0;t<8;t++)
    { if(buffer2[t].name[0]==dname[0]&&buffer2[t].name[1]==dname[1]
      &&buffer2[t].name[2]==dname[2]&&buffer2[t].attribute==8)
     {/*找到名字dname的目录，建立失败*/
      printf("目录已经存在，不能建立\n");
      return(false);
     }
    if(buffer2[t].name[0]=='$'&&b==-1)
       b=t;
    }/*for*/
   if(b==-1)							/*没有空目录项，不能建立*/
    { printf("目录无空间\n");
      return(false);
    }
    if((dd=allocate( ))==false)				/*分配给建立目录的磁盘盘块dd*/
     { printf("没有磁盘空间\n");
       return(false);
      }
   /*填写目录项*/
   for(i=0;i<3;i++)
     buffer2[b].name[i]=dname[i];
   buffer2[b].type[0]=buffer2[b].type[1]=' ';
   buffer2[b].attribute=8;
   buffer2[b].address=dd;
   buffer2[b].length=0;
   fseek(fc,d*64L,SEEK_SET);
   fwrite(buffer2,64L,1,fc);
   /*分给新建目录的盘块初始化*/
   for(t=0;t<8;t++)
    buffer2[t].name[0]='$';
   fseek(fc, dd*64L, SEEK_SET);
   fwrite(buffer2,64L,1,fc);
 }/*建立目录结束*/

 dir(name)
/*显示目录内容*/
 char *name;
 {int i,bnum,t,tt,dnum,dn,bn;
  if((dnum=search(name,8,&dn,&bn))==false)	/*找到目录路径*/
  { printf("目录不存在\n");
    return(false);
   }
  printf("名称  扩展名  起始盘块  长度\n");
 /*显示目录内容*/
  fseek(fc,dnum*64L, SEEK_SET);
  fread(buffer2,64L,1,fc);
  for(t=0;t<8;t++)						/*显示该盘块中目录项的内容*/
  if(buffer2[t].name[0]!='$')
   printf(" %c%c%c    %c%c    %4d%7d\n", buffer2[t].name[0], buffer2[t].name[1],buffer2[t].name[2],buffer2[t].type[0],buffer2[t].type[1],buffer2[t].address,
buffer2[t].length);
 }/*显示目录函数结束*/

rd(name)
/*删除空目录*/
 char *name;
{
 int dnum,bnum,t,i;
if((t=search(name,8,&dnum,&bnum))==false)	/*查找文件*/
  {printf("目录不存在\n");
   return(false);
  }
if(strcmp(name,"/")==0)						/*根目录不能删除*/
 { printf("该目录为根目录，不能删除\n");
   return(false);
  }
fseek(fc,t*64L, SEEK_SET);			/*判断该子目录是否为空目录*/
fread(buffer2,64,1,fc);
int flag=1;
for(i=0;i<8;i++)
if(buffer2[bnum].name[0]!='$')flag=0;
if(flag==0)						/*非空目录不能删除*/
 { printf("该目录为非空目录，不能删除\n");
   return(false);
  }
 fseek(fc,dnum*64L, SEEK_SET);			/*删除空目录*/
 fread(buffer2,64,1,fc);
 buffer2[bnum].name[0]='$';				/*将该文件的目录置成空目录*/
 fseek(fc,dnum*64L, SEEK_SET);
 fwrite(buffer2,64,1,fc);
 fseek(fc,t/64*64, SEEK_SET); 		/*删除该子目录占用的盘块*/
 fread(buffer1,64,1,fc);
 t=buffer1[t%64];
 buffer1[t%64]=0;
 fseek(fc, t/64*64L, SEEK_SET);
 fwrite(buffer1,64,1,fc);
}


typefile(name)
/*显示文件内容*/
 char *name;
{int i,dnum,dn,bn,t;
 if((dnum=search(name,1,&dn,&bn))==false)
  {printf("文件不存在\n");
   return(false);
  }
  if(sopen(name)!=-1)
  {printf("该文件打开，不能显示\n");
   return(false);
  }
  while(dnum!='\xff')
  {fseek(fc,dnum*64L,SEEK_SET);
   fread(buffer1,64,1,fc);						/*读一个盘块到缓冲*/
   for(t=0;t<64&&buffer1[t]!='#';t++)			/*显示缓冲内容*/
    putchar(buffer1[t]);
   printf("\n");
    }
   /*获得下一个盘块*/
   fseek(fc, dnum/64*64L, SEEK_SET);
   fread(buffer1,64,1,fc);
   dnum=buffer1[dnum%64];
  }
 /*显示文件函数结束*/

 change(name,attribute)
 /*改变文件name的属性为attribute*/
  char *name;
  int attribute;
 {int dnum,bnum;
  if(search(name,1,&dnum,&bnum)==false)		/*查找文件目录*/
  { printf("文件不存在\n");
    return(false);
   }
 if(sopen(name)!=-1)
 { printf("该文件打开，不能改变文件属性\n");
   return(false);
  }
  fseek(fc,dnum*64L,SEEK_SET);
  fread(buffer2,64,1,fc);					/*读出该目录所在盘块*/
  buffer2[bnum].attribute=attribute;			/*修改属性*/
  fseek(fc,dnum*64L,SEEK_SET);
  fwrite(buffer2,64,1,fc);					/*写回磁盘*/
 }/*改变文件属性函数结束*/

 main( )
 {char name[20],buffer[64];
  int attribute,type,length,i,a,j;
  /*建立文件，模拟磁盘*/
  if((fc=fopen("c:\\c","w+"))==NULL)
  {printf("无法打开文件\n");
   exit(0);
  }
  /*初始化已打开文件表*/
  openfile.length=0;
  /*初始化磁盘*/
  /*初始化文件分配表*/
  buffer1[0]=buffer1[1]=buffer1[2]=255;		/*磁盘第0、1块存放FAT表，第2块存放根目录*/
  for(i=3;i<64;i++)
   buffer1[i]=0;
  buffer1[13]=buffer1[49]=254;			/*假定模拟磁盘中有两个坏盘块：第13块和49块*/
  fwrite(buffer1,64L,1,fc);
  for(i=0;i<64;i++)
   buffer1[i]=0;
  fwrite(buffer1,64L,1,fc);
  /*初始化根目录*/
  for(i=0;i<8;i++)
   buffer2[i].name[0]='$';					/*若目录项第一个字符为“$”表示该目录项为空*/
  fwrite(buffer2,64L,1,fc);
  /*初始化已打开文件表*/
  while(1)
   {printf("\n  0 - 结束\n");
    printf("  1 - 建立文件\n");
    printf("  2 - 打开文件\n");
    printf("  3 - 读文件\n");
    printf("  4 - 写文件\n");
    printf("  5 - 关闭文件\n");
    printf("  6 - 删除文件\n");
    printf("  7 - 建立目录\n");
    printf("  8 - 显示目录内容\n");
    printf("  9 – 删除目录\n");
    printf(" 10 - 显示文件内容\n");
    printf(" 11 - 改变文件属性\n");
    printf(" 选择功能项（0~9）:");
    scanf("%d",&a);
    switch(a)
    {
      case 0:							 /*a=0程序结束*/
              fclose(fc);
              exit(0);
      case 1: 							/*a=1建立文件*/
              printf("输入文件路径名和文件属性（1-只读文件，3-只读系统文件，4-普通文件）:");
              scanf("%s%d",name,&attribute);
              create_file(name,attribute); 	/*建立文件*/
              break;
      case 2: 							/*a=2打开文件*/
              printf("输入文件路径名和操作类型（0-读文件，1-写文件）:");
              scanf("%s%d",name,&type);
              open_file(name,type);   	/*打开文件*/
              break;
      case 3: 							/*a=3读文件*/
              printf("输入文件路径名和读长度");
              scanf("%s%d",name,&length);
              read_file(name,length);  	/*读文件*/
              break;
      case 4: 							/*a=4写文件*/
              printf("输入文件路径名:");
              scanf("%s",name);
              printf("输入写的内容和和写长度");
              scanf("%s%d",buffer,&length);
              write_file(name,buffer,length); /*写文件*/
              break;
      case 5: 							/*a=5关闭文件*/
              printf("输入文件路径名");
              scanf("%s",name);
              close_file(name);     		/*关闭文件*/
              break;
      case 6:  						/*a=6删除文件*/
              printf("输入文件路径名");
              scanf("%s",name);
              delete(name);    			/*删除文件*/
              break;
      case 7: 							/*a=7建立目录*/
              printf("输入目录路径名");
              scanf("%s",name);
              md(name);    			/*建立目录*/
              break;
      case 8: 							/*a=8显示目录*/
              printf("输入目录路径名");
              scanf("%s",name);
              dir(name);  				/*显示目录*/
              break;
      case 9: 							/*a=9删除目录*/
              printf("输入目录路径名");
              scanf("%s",name);
              rd(name);  				/*删除目录*/
              break;
      case 10: 							/*a=10显示文件*/
              printf("输入文件路径名");
              scanf("%s",name);
              typefile(name);  			/*显示文件*/
              break;
      case 11:							/* a=11改变文件属性 */
              printf("输入文件路径名和文件属性（1-只读文件，3-只读系统文件，4-普通文件）：");
              scanf("%s%d",name,&attribute);
              change(name,attribute);
      }/* switch */
    }/* while */
  }/*main( )结束*/
