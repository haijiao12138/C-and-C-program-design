#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    int letters=0;//字母
    int space=0,digit=0,other=0;//空格，数字，其他
    printf("请输入一行字符 ：\n");
    while((c=getchar())!='\n')
    {
        if(c>='a'&&c<='z'||c>='A'&&c<='Z')
            letters++;
        else if(c==' ')
            space++;
        else if(c>='0'&&c<='9')
            digit++;
        else
            other++;
    }
    printf("字母数：%d\n 空格数：%d\n 数字：%d\n 其他：%d\n",letters,space,digit,other);
    return 0;
}
