
#include <stdio.h>

int main() {
	int outPutBuf[82][82];
	char a,b;
	int n;
	bool firstCase=true;
	while(scanf("%d %c %c",&n,&a,&b)!=EOF){
		
		if(firstCase==true){//�жϽ�����һ����������ʱ�Ƿ��� 
			firstCase=false;
		}
		else {
			printf("\n");
		} 
		
		for(int i=1,j=1;i<=n;i+=2,j++){
			int x=n/2+1,y=x;
			x-=j-1;y-=j-1;//����ÿ��Ȧ���Ͻǵ����� 
			char c=j%2==1?a:b;
			for(int k=1;k<=i;k++){
				outPutBuf[x+k-1][y]=c;//��߸�ֵ 
				outPutBuf[x][y+k-1]=c;//�ϱ߸�ֵ 
				outPutBuf[x+i-1][y+k-1]=c;//�ұ߸�ֵ 
				outPutBuf[x+k-1][y+i-1]=c;//�±߸�ֵ 
			}
		}
		
		if(n!=1){
			outPutBuf[1][1]=' ';
			outPutBuf[n][1]=' ';
			outPutBuf[1][n]=' ';
			outPutBuf[n][n]=' ';
			
		}
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				printf("%c",outPutBuf[i][j]);
			}
			printf("\n");
		}
		   
	}
	return 0;
}
/*
#include <stdio.h>

int main(){
    int outPutBuf[82][82];//����Ԥ�Ű���������
    char a, b;
    int n;
    bool firstCase = true; //����Ƿ�Ϊ��һ������
    while(scanf("%d %c %c", &n, &a, &b) == 3){
        if(firstCase == true){
            firstCase = false;
        }
        else{
            printf("\n");//�����ʽ�����˵�һ���⣬�������֮ǰ���ӻ���
        }
        for(int i=1, j=1; i <= n; i+=2, j++){//���ﵽ���������Ȧ
            int x = n/2+1, y = x;
            x -= j-1;
            y -= j-1;//����ÿ��Ȧ���Ͻǵ������
            char c = j%2 == 1 ? a : b; //���㵱ǰȦ��Ҫʹ���ĸ��ַ�
            //printf("%d %d\n", x, y);
            for(int k=1; k <= i; k++){
                outPutBuf[x+k-1][y] = c; //��߸�ֵ
                outPutBuf[x][y+k-1] = c; //�ϱ߸�ֵ
                outPutBuf[x+i-1][y+k-1] = c; //�ұ߸�ֵ
                outPutBuf[x+k-1][y+i-1] = c; //�±߸�ֵ
            }
        }

        if(n != 1){
            outPutBuf[1][1] = ' ';
            outPutBuf[1][n] = ' ';
            outPutBuf[n][1] = ' ';
            outPutBuf[n][n] = ' ';
        }

        for(int i=1; i <= n; i++){
            for(int j=1; j <= n; j++){
                printf("%c", outPutBuf[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}*/
