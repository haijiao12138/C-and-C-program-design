#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    int letters=0;//��ĸ
    int space=0,digit=0,other=0;//�ո����֣�����
    printf("������һ���ַ� ��\n");
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
    printf("��ĸ����%d\n �ո�����%d\n ���֣�%d\n ������%d\n",letters,space,digit,other);
    return 0;
}
