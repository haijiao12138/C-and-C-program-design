
#include <stdio.h>

int main() {
	int outPutBuf[82][82];
	char a,b;
	int n;
	bool firstCase=true;
	while(scanf("%d %c %c",&n,&a,&b)!=EOF){
		
		if(firstCase==true){//判断进行下一组数据输入时是否换行 
			firstCase=false;
		}
		else {
			printf("\n");
		} 
		
		for(int i=1,j=1;i<=n;i+=2,j++){
			int x=n/2+1,y=x;
			x-=j-1;y-=j-1;//计算每个圈左上角的坐标 
			char c=j%2==1?a:b;
			for(int k=1;k<=i;k++){
				outPutBuf[x+k-1][y]=c;//左边赋值 
				outPutBuf[x][y+k-1]=c;//上边赋值 
				outPutBuf[x+i-1][y+k-1]=c;//右边赋值 
				outPutBuf[x+k-1][y+i-1]=c;//下边赋值 
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
    int outPutBuf[82][82];//用于预排版的输出缓存
    char a, b;
    int n;
    bool firstCase = true; //标记是否为第一组数据
    while(scanf("%d %c %c", &n, &a, &b) == 3){
        if(firstCase == true){
            firstCase = false;
        }
        else{
            printf("\n");//输出格式，除了第一行外，其余各行之前都加换行
        }
        for(int i=1, j=1; i <= n; i+=2, j++){//从里到外输出各个圈
            int x = n/2+1, y = x;
            x -= j-1;
            y -= j-1;//计算每个圈左上角点的坐标
            char c = j%2 == 1 ? a : b; //计算当前圈需要使用哪个字符
            //printf("%d %d\n", x, y);
            for(int k=1; k <= i; k++){
                outPutBuf[x+k-1][y] = c; //左边赋值
                outPutBuf[x][y+k-1] = c; //上边赋值
                outPutBuf[x+i-1][y+k-1] = c; //右边赋值
                outPutBuf[x+k-1][y+i-1] = c; //下边赋值
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
