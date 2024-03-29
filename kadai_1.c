//play_0 初手3回殴り,3回で許す逆しっぺ返し
//VS
//play_1 しっぺ返し

//n回0,その後all1はnがいくつでも逆しっぺ返しと戦うと「引き分け」
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
// #include <unistd.h> windowsだとコンパイルされない…?
#include <string.h>

#define N 50 /* 試行回数 */
#define OID (id^1) /* 相手のid */
#define CLIENT_0 "ID0" /* 名前 */
#define CLIENT_1 "ID1"

/*
int sct[2][2]:点数表
			自分		相手
    [0][0]：	協調		協調
    [0][1]：	協調		裏切り
    [1][0]：	裏切り		協調
    [1][1]：	裏切り		裏切り
int *h:過去の手
    *(h+2*i+ID):i回目のIDの手
int sc[2]:点数
    sc[ID]:IDの点
*/

/*この手を計算する関数のプロトタイプ宣言名前は何でもよい。引数も必要に応じて変えること
この例では自分のID、今何回目か、現在までの点数、過去の手の配列を渡している。*/

int play_0(int ID, int n,int SC[2] , int *H);/*ID0の関数*/
int play_1(int ID, int n,int SC[2] , int *H);/*ID1の関数*/
const int SCT[2][2]={{5,0},{10,2}}; /*点数表*/

int main(void){
    int i,j,k,t,n = N,rh[2] ;
    char c_name[2][255];

    int *h; //int h[2][N];
    int sc[2]={0,0};
    FILE *LOG;

    LOG=fopen("log_tai","w");

    setbuf(stderr,NULL);
    
    // 乱数を使いたい時に備えて初期化   
    //  srand((unsigned int)time(NULL));
    srand((unsigned int)19720117L);

    //calloc
    h=(int *)calloc(2*n,sizeof(int));

/////////////////////////////////////////
    for(j=0;j<n;j++){
		rh[0]=play_0(0, j, sc, h);
		rh[1]=play_1(1, j, sc, h);

		for(k=0;k<2;k++){
			*(h+(2*j)+k)=rh[k];
			sc[k] += SCT[rh[k]][rh[k^1]];
		}
		fprintf(LOG,"Turn %3d,h: %d %d, sc:%3d %3d,total: %3d %3d\n",j+1,
			*(h+(2*j)),*(h+(2*j)+1),
			SCT[*(h+(2*j))][*(h+(2*j)+1)],SCT[*(h+(2*j)+1)][*(h+(2*j))],sc[0],sc[1]);
    }  
    
    fprintf(LOG,"      %s : %s .\n",CLIENT_0,CLIENT_1);
    fprintf(LOG,"score  %d : %d . %d\n",sc[0],sc[1],sc[0]+sc[1]);
    printf("      %s : %s .\n",CLIENT_0,CLIENT_1);
    printf("score  %d : %d . %d\n",sc[0],sc[1],sc[0]+sc[1]);
    fprintf(stderr,"\n THE END\n");

    fclose(LOG);
    free(h);
    return 0;  
}
/////////////////////////////////////////
/////////////////////////////////////////

int play_0(int ID,int n,int SC[2] , int *H)/*ID0の関数*/{
    int  t,i,j;
    if(n<=3) return 1; //3回殴ってから逆しっぺ返し
    t = *(H+2*(n-1)+(ID^1));
    i = *(H+2*(n-2)+(ID^1));
    j = *(H+2*(n-3)+(ID^1));
    if(t==0 && i==0 && j==0) return 0;
    return 1;
}

int play_1(int ID,int n,int SC[2] , int *H)/*ID1の関数*/{
    int  t,i,j;
    if(n==0) return 0;
    t = *(H+2*(n-1)+(ID^1));
    i = *(H+2*(n-2)+(ID^1));
    j = *(H+2*(n-3)+(ID^1));
    if(n==1){
        if(t==0) return 0;
    }
    if(n==2){
        if(t==0 && i==0) return 0;
    }
    if(t==0 && i==0 && j==0) return 0;
    return 1;
}
