#include <stdio.h>

struct Node{
	int x;
	int y;
};

int main(){
	printf("请输入坐标点的个数：\n");
	int n,i;
	scanf("%d",&n);
	struct Node a[n];
	printf("请输入你的%d个坐标点：\n",n);
	for (i=0;i<n;i++)
	scanf("%d %d",&a[i].x,&a[i].y);
	
	printf("%d\n",deal(a, n));
	return 0;
}
int deal(struct Node *a, int n){//不能组成三角形的情况；1、斜率相等；2、斜率不存在 3、少于3个点 
	if (n <= 2)
		return 0;
	int sum = n*(n-1)*(n-2)/6; //Cn3种取法 
	int cnt = 0,i,j,k;
	for (i = 0; i < n;i++)
	for (j = i + 1; j < n;j++)
	for (k = j + 1; k < n; k++){
		if(a[k].x!=a[i].x&&a[j].x!=a[i].x&&a[k].x!=a[j].x) {
			if ((a[k].y-a[j].y)/(a[k].x-a[j].x)==(a[j].y-a[i].y)/(a[j].x-a[i].x))
			cnt++;
		}
		
		if(a[k].x==a[i].x&&a[j].x==a[i].x&&a[k].x==a[j].x) cnt++;
	}
	return sum - cnt;
 
}



