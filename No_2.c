#include<stdio.h>
#include<string.h>
int a[105]={0},b[105]={0};

void getValue(int a[]) { 
  int i;
  char s[105]; 
  gets(s);
  a[0]=strlen(s);  
  for(i=1;i<=a[0];i++)
    a[i]=s[a[0]-i]-'0'; 
}

void printValue(int a[]){
  int i;
  if (a[0]==0){printf("0\n");return;}
  for(i=a[0];i>0;i--) printf("%d",a[i]);
  printf("\n");
  return ;
}

int compare (int a[],int b[]){ 
  int i; 
  if (a[0]>b[0]) return 1;
  if (a[0]<b[0]) return -1;
  for(i=a[0];i>0;i--){ 
	 if (a[i]>b[i]) return 1; 
     if (a[i]<b[i]) return -1;
    } 
  return 0;
} 

void add(int a[],int b[]){ 
  int i,k; 
  if(a[0]<b[0]) a[0]=b[0];    
  for(i=1;i<=a[0];i++) a[i]+=b[i];   
  for(i=1;i<=a[0];i++){ 
	 a[i+1]+=a[i]/10;
     a[i]%=10;
    } 
  if(a[a[0]+1]>0) a[0]++;
}

void subtract(int a[],int b[]){ 
  int flag,i; 
  flag=compare(a,b); 
  if (flag==0) {a[0]=0;return;} 
  if(flag==1){
  for(i=1;i<=a[0];i++) {
       if(a[i]<b[i]) {a[i+1]--;a[i]+=10;} 
       a[i]=a[i]-b[i];
      } 
     while(a[a[0]]==0) a[0]--; 
     return;
    } 
  if (flag==-1){ 
     printf("-"); 
     for(i=1;i<=b[0];i++){
	   if(b[i]<a[i]){b[i+1]--;b[i]+=10;}
       a[i]=b[i]-a[i];
      } 
     a[0]=b[0]; 
     while(a[a[0]]==0) a[0]--;
     return;
   } 
}

int main(){
  printf("请输入两个大数：\n");
  getValue(a);getValue(b);
  printf("请输入 +或- 进行加法或减法运算：\n");
  char chose;
  scanf("%c",&chose);
  if(chose=='+')
  add(a,b);
  else if(chose=='-')
  subtract(a,b); 
  printValue(a);
  return 0;
}

