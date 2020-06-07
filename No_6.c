#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

typedef struct book{
    int bookNumber;     //库存 
    char bookName[20];  //书名
    char bookCode[10];  //编号
    struct book *next;	
} Book;

typedef struct user{
	char userCode[10];				//编号
	char userName[20];				//用户名 
	char userBorrow[10][20];		//所借书号
	struct user *next;	
}User;

typedef struct manager{
	char manName[15];				//管理员姓名
	struct manager *next;
}Manager;

Book *Book_head;
User *User_head;
Manager *Manager_head;

void umenu(char *a){
	printf("-----------------------------------------\n");
    printf("|\t\t图书馆用户系统\t\t|\n");
    printf("|\t\t欢迎您，%s\t\t|\n",a);
    printf("|\t\t0. 退出系统\t\t|\n");
    printf("|\t\t1. 借阅图书\t\t|\n");
    printf("|\t\t2. 归还图书\t\t|\n");
    printf("|\t\t3. 查询图书\t\t|\n");
    printf("-----------------------------------------\n");
}

void amenu(char *a){
	printf("-----------------------------------------\n");
    printf("|\t\t图书馆管理员系统\t\t|\n");
    printf("|\t\t欢迎您，%s\t\t|\n",a);
    printf("|\t\t0. 退出系统\t\t|\n");
    printf("|\t\t1. 录入图书信息\t\t|\n");
    printf("|\t\t2. 删除图书信息\t\t|\n");
    printf("|\t\t3. 录入读者信息\t\t|\n");
    printf("|\t\t4. 删除读者信息\t\t|\n");
    printf("-----------------------------------------\n");
}

Book *bookLoad(){
	FILE *fp;
	Book *h=NULL,*t=h,*p;
	if((fp=fopen("Book.txt","r"))==NULL){
		printf("\t\t文件打开失败\n");
		exit(1);
	}
	getc(fp);
	if(feof(fp)){
		fclose(fp);
		return NULL;
	}
	rewind(fp);
	while(!feof(fp)){
		p=(Book *)malloc(sizeof(Book));
		p->next=NULL;
		fscanf(fp,"%s",p->bookCode);
		fscanf(fp,"%s",p->bookName);
		fscanf(fp,"%d",&p->bookNumber);
		if(h==NULL)
			h=p;
		else
			t->next=p;
		t=p;
	}
	fclose(fp);
	return h;
}

User *userLoad(void){
	FILE *fp;
	User *h=NULL,*t=h,*p;
	if((fp=fopen("User.txt","r"))==NULL){
		printf("\t\t文件打开失败\n");
		exit(1);
	}
	getc(fp);
	if(feof(fp)){
		fclose(fp);
		return NULL;
	}
	rewind(fp);
	while(!feof(fp)){
		p=(User *)malloc(sizeof(User));
		p->next=NULL;
		fscanf(fp,"%s",p->userCode);
		fscanf(fp,"%s",p->userName);
		int i;
		for(i=0;i<10;i++){
			fscanf(fp,"%s",p->userBorrow[i]);
		}
		if(h==NULL)
			h=p;
		else
			t->next=p;
		t=p;
	}
	fclose(fp);
	return h;
}

Manager *managerLoad(void){
	FILE *fp;
	Manager *h=NULL,*t=h,*p;
	if((fp=fopen("Manager.txt","r"))==NULL){
		printf("\t\t文件打开失败\n");
		exit(1);
	}
	getc(fp);
	if(feof(fp)){
		fclose(fp);
		return NULL;
	}
	rewind(fp);
	while(!feof(fp)){
		p=(Manager *)malloc(sizeof(Manager));
		p->next=NULL;
		fscanf(fp,"%s",p->manName);
		if(h==NULL)
			h=p;
		else
			t->next=p;
		t=p;
	}
	fclose(fp);
	return h;
}

void saveBook(void){
	FILE *fp;
	Book *t=Book_head->next;
	if(!t)
		return;
	if((fp=fopen("Book.txt","w+"))==NULL){
		printf("\t\t文件打开失败\n");
		exit(1);
	}
	while(t->next){
		fprintf(fp,"%s ",t->bookCode);
		fprintf(fp,"%s ",t->bookName);
		fprintf(fp,"%d\n",t->bookNumber);
		t=t->next;
	}
	fprintf(fp,"%s ",t->bookCode);
	fprintf(fp,"%s ",t->bookName);
	fprintf(fp,"%d",t->bookNumber);
	fclose(fp);
}

void saveUser(void){
	FILE *fp;
	User *t=User_head->next;
	if(!t)
		return;
	if((fp=fopen("User.txt","w+"))==NULL){
		printf("\t\t文件打开失败\n");
		exit(1);
	}
	int i=0;
	while(t->next){
		fprintf(fp,"%s ",t->userCode);
		fprintf(fp,"%s ",t->userName);
		for(i=0;i<9;i++){
			fprintf(fp,"%s ",t->userBorrow[i]);
		}
		fprintf(fp,"%s\n",t->userBorrow[9]);
		t=t->next;
	}
	fprintf(fp,"%s ",t->userCode);
	fprintf(fp,"%s ",t->userName);
	for(i=0;i<9;i++){
		fprintf(fp,"%s ",t->userBorrow[i]);
	}
	fprintf(fp,"%s",t->userBorrow[9]);
	fclose(fp);
}

void saveManger(void){
	FILE *fp;
	Manager *t=Manager_head->next;
	if(!t)
		return;
	if((fp=fopen("Manager.txt","w+"))==NULL){
		printf("\t\t文件打开失败\n");
		exit(1);
	}
	while(t->next){
		fprintf(fp,"%s ",t->manName);
		t=t->next;
	}
	fprintf(fp,"%s ",t->manName);
	fclose(fp);
}

void saveAll(void){
	saveBook();
	saveUser();
	saveManger();
}

User *findUser(char *UserName){
	User *t=User_head->next;
	while(t){
		if(strcmp(t->userName,UserName)==0)
			break;
		t=t->next;
	}
	return t;
}

Manager *findManager(char *ManagerName){
	Manager *t=Manager_head->next;
	while(t){
		if(strcmp(ManagerName,t->manName)==0)
			break;
		t=t->next;
	}
	return t;
}

void findBook(void){
	Book *t=Book_head->next;
	char book_n[20];
	if(t==NULL){
		printf("\t\t抱歉，暂无书籍\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	printf("\t\t请输入你需要查找的书名：");
	gets(book_n);
	while(t){
		if(strcmp(book_n,t->bookName)==0)
			break;
		t=t->next;
	}
	if(t==NULL){
		printf("\t\t抱歉，无此书籍\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	t=Book_head->next;
	printf("\n\n\t**********************************");
	printf("********************************\n\n");
    printf("\t %-8s%-10s%-10s%\n\n","编号","书名","数量");
	while(t){
		if(strcmp(book_n,t->bookName)==0)
			printf("\t %-8s%-10s%-10d%\n",t->bookCode,t->bookName,t->bookNumber);
		t=t->next;
	}
	printf("\n\t**************************************");
	printf("****************************\n\n\n");
	printf("\n\t\t按任意键退出");
	getch();
}

Book *findBookCode(char *BookCode)
{
	Book *t=Book_head->next;
	while(t){
		if(strcmp(BookCode,t->bookCode)==0)
			return t;
		t=t->next;
	}
}

/*打印书单*/
void printBook(void){
	Book *t=Book_head->next;
	if(t==NULL){
		printf("\t\t抱歉，暂无上架书籍\n");
		return;
	}
	printf("\n\n\t**********************************");
	printf("********************************\n\n");
	printf("\t %-8s%-10s%-10s%\n\n","编号","书名","数量");
	while(t){
		printf("\t %-8s%-10s%-10d%\n",t->bookCode,t->bookName,t->bookNumber);
		t=t->next;
	}
	printf("\n\t**************************************");
	printf("****************************\n\n\n");
}
/*寻找该书是否存在*/
Book *Ifexist(char *BookCode){
	Book *t=Book_head->next;
	while(t){
		if(strcmp(t->bookCode,BookCode)==0)
			break;
		t=t->next;
	}
	return t;
}
/*查询学生是否借过此书*/
int Ifborrow(User *userCode,char *bookCode){
	
	int temp=0,i;
	for(i=0;i<10;i++){
		if(strcmp(userCode->userBorrow[i],bookCode)==0){
			temp=1;
			break;
		}
	}
	return temp;
}

void printBorbook(User *userCode){
	int temp=0,i;
	Book *t;
	printf("\n\n\t*************************");
	printf("********************************\n\n");
	printf("\t %-8s%-10s%-10s%\n\n","编号","书名","数量");
	for(i=0;i<10;i++){
		if(strcmp(userCode->userBorrow[i],"0")!=0){
			t=findBookCode(userCode->userBorrow[i]);
			printf("\t %-8s%-10s%-10d%\n",t->bookCode,t->bookName,t->bookNumber);
		}
	}
	printf("\n\t*****************************");
	printf("****************************\n\n\n");
}
/*还书具体操作*/
void backBook(User *userCode,char *BookCode){
	int i=0;
	Book *t;
	for(i=0;i<10;i++){
		if(strcmp(userCode->userBorrow[i],BookCode)==0){
			userCode->userBorrow[i][0]='0';
			userCode->userBorrow[i][1]='\0';
			break;
		}
	}
	t=findBookCode(BookCode);
	t->bookNumber++;
}

void uBorrow(User *userCode){
	Book *t;
	char numb[10];
	printf("\n\t\t欢迎进入借书系统\n");
	printf("\t\t书单如下\n");
	printBook();
	printf("\n\t\t请选择你想借书的编号：");
	gets(numb);
	t=Ifexist(numb);
	printf("\t\t正在办理···\n");
	Sleep(500);
	if(!t){
		printf("\t\t该书不存在，请重试\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	if(t->bookNumber==0){
		printf("\t\t抱歉，库存不足，借书失败\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	if(Ifborrow(userCode,numb)){
		printf("\t\t抱歉，您已借过此书，请勿重复借书\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	int i=0;
	for(i=0;i<10;i++){
		if(strcmp(userCode->userBorrow[i],"0")==0){
			userCode->userBorrow[i][0]='\0';
			strcat(userCode->userBorrow[i],numb);
			t->bookNumber--;
			break;
		}
	}
	printf("\t\t恭喜您办理成功！\n");
	printf("\t\t按任意键退出");
	getch();
	return;
}

/*学生还书*/
void uBack(User *userCode){
	char Book_num[15];
	int temp=0,i;
	printf("\n\t\t欢迎进入还书系统\n");
	printf("\n\t\t正在查找已借书籍···\n");
	Sleep(500);
	for(i=0;i<10;i++){
		if(strcmp(userCode->userBorrow[i],"0")!=0){
			temp=1;
			break;
		}
	}
	if(temp==0){
		printf("\n\t\t暂无借书记录\n");
		printf("\n\t\t按任意键退出");
		getch();
		return;
	}
	printBorbook(userCode);
	printf("\n\t\t请输入书的编号进行归还：");
	gets(Book_num);
	temp=0;
	for(i=0;i<10;i++){
		if(strcmp(userCode->userBorrow[i],Book_num)==0){
			temp=1;
			break;
		}
	}
	if(!temp){
		printf("\t\t输入错误，您未借过此书\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}	
	backBook(userCode,Book_num);	
	printf("\t\t归还成功！\n");
	printf("\t\t按任意键退出");
	getch();
}

//编号升序查看书架
void searchCode(void){
	if(Book_head->next==NULL)
	{
		printf("\t\t暂无书籍\n");
		return;
	}
	if(Book_head->next->next==NULL)
	{
		return;
	}
	Book *p1,*p2,*p3,*end,*temp;
	Book *head=Book_head;
	end=NULL;
	while(head->next!=end){
		for(p1=head,p2=p1->next,p3=p2->next;p3!=end;p1=p1->next,p2=p2->next,p3=p3->next){
			if((strcmp(p2->bookCode,p3->bookCode))>0){
				p1->next=p2->next;
				p2->next=p3->next;
				p3->next=p2;
				temp=p2;
				p2=p3;
				p3=temp;
			}
			
		}
		end=p2;
	}
	printBook();
}

void addBook(void){	
	printf("\t\t请输入以下信息：\n");
	Book *new=(Book *)malloc(sizeof(Book));
	new->next=NULL;
	Book *t=Book_head;
	printf("\t\t书籍编号：");
	gets(new->bookCode);
	if(findBookCode(new->bookCode)){
		free(new);
		printf("\t\t该书已上架过\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	printf("\t\t书名：");
	gets(new->bookName);
	printf("\t\t数量：");
	scanf("%d",&new->bookNumber);
	getchar();
	printf("\t\t上架成功！\n");
	while(t->next){
		t=t->next;
	}
	t->next=new;
	printf("\t\t按任意键退出");
	getch();
}
/*管理员下架书籍*/
void deleteBook(void){
	char BookCode[20];
	Book *t=Book_head->next;
	searchCode();
	if(!t){
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	printf("\t\t请输入需下架的书籍编号：");
	gets(BookCode);
	t=findBookCode(BookCode);
	if(!t){
		printf("\t\t抱歉，无此书籍\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	t->bookNumber=0;
	printf("\t\t下架成功！\n");
	printf("\t\t按任意键退出");
	getch();
}

User *findUserCode(char *UserCode){
	User *t=User_head->next;
	while(t){
		if(strcmp(t->userCode,UserCode)==0)
			break;
		t=t->next;
	}
	return t;
}

void addUser(void){	
	printf("\t\t请输入以下信息：\n");
	User *new=(User *)malloc(sizeof(User));
	new->next=NULL;
	User *t=User_head;
	printf("\t\t用户编号：");
	gets(new->userCode);
	if(findUserCode(new->userCode)){
		free(new);
		printf("\t\t该用户已存在\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	printf("\t\t用户名：");
	gets(new->userName);
	getchar();
	printf("\t\t成功！\n");
	while(t->next){
		t=t->next;
	}
	t->next=new;
	printf("\t\t按任意键退出");
	getch();
}

void deleteUser(void){
	char code[20];
	Book *a;
	User *head=User_head;
	User *t=User_head->next;
	printf("\t\t用户名单如下···\n");
	if(!t){
		printf("\n\t\t抱歉，找不到该用户\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	printf("\n\n     *************************************");
	printf("********************************\n\n");
	printf("      %-10s%-8s%-10s\n\n","编号","用户名","借书数量");
	while(t)
	{
		int n=0,i;
		for(i=0;i<10;i++){
			if(strcmp(t->userBorrow[i],"0")!=0)
				n++;
		}
		printf("      %-10s%-8s%-10d\n",t->userCode,t->userName,n);		
		t=t->next;
	}
	printf("\n     *****************************************");
	printf("****************************\n\n\n");

	printf("\t\t请输入你想删除用户的账号："); 
	gets(code);
	t=findUserCode(code);
	if(!t){
		printf("\t\t抱歉，找不到该用户\n");
		printf("\t\t按任意键退出");
		getch();
		return;
	}
	printf("\t\t删除成功！\n");
	int i;
	for(i=0;i<10;i++){
		if(strcmp(t->userBorrow[i],"0")!=0){
			a=findBookCode(t->userBorrow[i]);
			a->bookNumber+=1;
		}
	}
	t=User_head->next;
	while(t){
		if(strcmp(code,t->userCode)==0){
			head->next=t->next;
			free(t);
			break;
		}
		head=t;
		t=t->next;
	}
	printf("\t\t按任意键退出\n");
	getch();
	return;
}

 
int main(int argc, char* argv[]){
	Book_head=(Book *)malloc(sizeof(Book));
	User_head=(User *)malloc(sizeof(User));
	Manager_head=(Manager *)malloc(sizeof(Manager));

	Book_head->next=bookLoad();
	User_head->next=userLoad();
	Manager_head->next=managerLoad();
	
	if(strcmp(argv[1],"-u")==0){
		umenu(argv[2]);
		User *user;
		user=findUser(argv[2]);
		char c = '1';
		while(c!='0'){			
		    printf("\t\t：");
		    scanf("%c",&c);
		    while(getchar()!='\n');
		    switch(c){
			   case '1':uBorrow(user);break;
			   case '2':uBack(user);break;
			   case '3':findBook();break;
			   case '0':saveAll();break;
			   default:printf("\t\t输入错误，请重新输入\n");Sleep(500);break;	    
		    }
	    }
    } 
	
        else if(strcmp(argv[1],"-a")==0){ 
        amenu(argv[2]);
        char c = '1';
		while(c!='0'){
		    printf("\t\t：");
		    scanf("%c",&c);
		    while(getchar()!='\n');
		    switch(c){
			    case '1':addBook();break;
			    case '2':deleteBook();break;
			    case '3':addUser();break;
			    case '4':deleteUser();break;
			    case '0':saveAll();break;		
				default:printf("\t\t输入错误，请重新输入\n");Sleep(500);break;		    
		    }
	    }
    }

    system("PAUSE");
    return 0;
} 

