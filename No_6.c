#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

typedef struct book{
    int bookNumber;     //��� 
    char bookName[20];  //����
    char bookCode[10];  //���
    struct book *next;	
} Book;

typedef struct user{
	char userCode[10];				//���
	char userName[20];				//�û��� 
	char userBorrow[10][20];		//�������
	struct user *next;	
}User;

typedef struct manager{
	char manName[15];				//����Ա����
	struct manager *next;
}Manager;

Book *Book_head;
User *User_head;
Manager *Manager_head;

void umenu(char *a){
	printf("-----------------------------------------\n");
    printf("|\t\tͼ����û�ϵͳ\t\t|\n");
    printf("|\t\t��ӭ����%s\t\t|\n",a);
    printf("|\t\t0. �˳�ϵͳ\t\t|\n");
    printf("|\t\t1. ����ͼ��\t\t|\n");
    printf("|\t\t2. �黹ͼ��\t\t|\n");
    printf("|\t\t3. ��ѯͼ��\t\t|\n");
    printf("-----------------------------------------\n");
}

void amenu(char *a){
	printf("-----------------------------------------\n");
    printf("|\t\tͼ��ݹ���Աϵͳ\t\t|\n");
    printf("|\t\t��ӭ����%s\t\t|\n",a);
    printf("|\t\t0. �˳�ϵͳ\t\t|\n");
    printf("|\t\t1. ¼��ͼ����Ϣ\t\t|\n");
    printf("|\t\t2. ɾ��ͼ����Ϣ\t\t|\n");
    printf("|\t\t3. ¼�������Ϣ\t\t|\n");
    printf("|\t\t4. ɾ��������Ϣ\t\t|\n");
    printf("-----------------------------------------\n");
}

Book *bookLoad(){
	FILE *fp;
	Book *h=NULL,*t=h,*p;
	if((fp=fopen("Book.txt","r"))==NULL){
		printf("\t\t�ļ���ʧ��\n");
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
		printf("\t\t�ļ���ʧ��\n");
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
		printf("\t\t�ļ���ʧ��\n");
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
		printf("\t\t�ļ���ʧ��\n");
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
		printf("\t\t�ļ���ʧ��\n");
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
		printf("\t\t�ļ���ʧ��\n");
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
		printf("\t\t��Ǹ�������鼮\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}
	printf("\t\t����������Ҫ���ҵ�������");
	gets(book_n);
	while(t){
		if(strcmp(book_n,t->bookName)==0)
			break;
		t=t->next;
	}
	if(t==NULL){
		printf("\t\t��Ǹ���޴��鼮\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}
	t=Book_head->next;
	printf("\n\n\t**********************************");
	printf("********************************\n\n");
    printf("\t %-8s%-10s%-10s%\n\n","���","����","����");
	while(t){
		if(strcmp(book_n,t->bookName)==0)
			printf("\t %-8s%-10s%-10d%\n",t->bookCode,t->bookName,t->bookNumber);
		t=t->next;
	}
	printf("\n\t**************************************");
	printf("****************************\n\n\n");
	printf("\n\t\t��������˳�");
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

/*��ӡ�鵥*/
void printBook(void){
	Book *t=Book_head->next;
	if(t==NULL){
		printf("\t\t��Ǹ�������ϼ��鼮\n");
		return;
	}
	printf("\n\n\t**********************************");
	printf("********************************\n\n");
	printf("\t %-8s%-10s%-10s%\n\n","���","����","����");
	while(t){
		printf("\t %-8s%-10s%-10d%\n",t->bookCode,t->bookName,t->bookNumber);
		t=t->next;
	}
	printf("\n\t**************************************");
	printf("****************************\n\n\n");
}
/*Ѱ�Ҹ����Ƿ����*/
Book *Ifexist(char *BookCode){
	Book *t=Book_head->next;
	while(t){
		if(strcmp(t->bookCode,BookCode)==0)
			break;
		t=t->next;
	}
	return t;
}
/*��ѯѧ���Ƿ�������*/
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
	printf("\t %-8s%-10s%-10s%\n\n","���","����","����");
	for(i=0;i<10;i++){
		if(strcmp(userCode->userBorrow[i],"0")!=0){
			t=findBookCode(userCode->userBorrow[i]);
			printf("\t %-8s%-10s%-10d%\n",t->bookCode,t->bookName,t->bookNumber);
		}
	}
	printf("\n\t*****************************");
	printf("****************************\n\n\n");
}
/*����������*/
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
	printf("\n\t\t��ӭ�������ϵͳ\n");
	printf("\t\t�鵥����\n");
	printBook();
	printf("\n\t\t��ѡ���������ı�ţ�");
	gets(numb);
	t=Ifexist(numb);
	printf("\t\t���ڰ�������\n");
	Sleep(500);
	if(!t){
		printf("\t\t���鲻���ڣ�������\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}
	if(t->bookNumber==0){
		printf("\t\t��Ǹ����治�㣬����ʧ��\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}
	if(Ifborrow(userCode,numb)){
		printf("\t\t��Ǹ�����ѽ�����飬�����ظ�����\n");
		printf("\t\t��������˳�");
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
	printf("\t\t��ϲ������ɹ���\n");
	printf("\t\t��������˳�");
	getch();
	return;
}

/*ѧ������*/
void uBack(User *userCode){
	char Book_num[15];
	int temp=0,i;
	printf("\n\t\t��ӭ���뻹��ϵͳ\n");
	printf("\n\t\t���ڲ����ѽ��鼮������\n");
	Sleep(500);
	for(i=0;i<10;i++){
		if(strcmp(userCode->userBorrow[i],"0")!=0){
			temp=1;
			break;
		}
	}
	if(temp==0){
		printf("\n\t\t���޽����¼\n");
		printf("\n\t\t��������˳�");
		getch();
		return;
	}
	printBorbook(userCode);
	printf("\n\t\t��������ı�Ž��й黹��");
	gets(Book_num);
	temp=0;
	for(i=0;i<10;i++){
		if(strcmp(userCode->userBorrow[i],Book_num)==0){
			temp=1;
			break;
		}
	}
	if(!temp){
		printf("\t\t���������δ�������\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}	
	backBook(userCode,Book_num);	
	printf("\t\t�黹�ɹ���\n");
	printf("\t\t��������˳�");
	getch();
}

//�������鿴���
void searchCode(void){
	if(Book_head->next==NULL)
	{
		printf("\t\t�����鼮\n");
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
	printf("\t\t������������Ϣ��\n");
	Book *new=(Book *)malloc(sizeof(Book));
	new->next=NULL;
	Book *t=Book_head;
	printf("\t\t�鼮��ţ�");
	gets(new->bookCode);
	if(findBookCode(new->bookCode)){
		free(new);
		printf("\t\t�������ϼܹ�\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}
	printf("\t\t������");
	gets(new->bookName);
	printf("\t\t������");
	scanf("%d",&new->bookNumber);
	getchar();
	printf("\t\t�ϼܳɹ���\n");
	while(t->next){
		t=t->next;
	}
	t->next=new;
	printf("\t\t��������˳�");
	getch();
}
/*����Ա�¼��鼮*/
void deleteBook(void){
	char BookCode[20];
	Book *t=Book_head->next;
	searchCode();
	if(!t){
		printf("\t\t��������˳�");
		getch();
		return;
	}
	printf("\t\t���������¼ܵ��鼮��ţ�");
	gets(BookCode);
	t=findBookCode(BookCode);
	if(!t){
		printf("\t\t��Ǹ���޴��鼮\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}
	t->bookNumber=0;
	printf("\t\t�¼ܳɹ���\n");
	printf("\t\t��������˳�");
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
	printf("\t\t������������Ϣ��\n");
	User *new=(User *)malloc(sizeof(User));
	new->next=NULL;
	User *t=User_head;
	printf("\t\t�û���ţ�");
	gets(new->userCode);
	if(findUserCode(new->userCode)){
		free(new);
		printf("\t\t���û��Ѵ���\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}
	printf("\t\t�û�����");
	gets(new->userName);
	getchar();
	printf("\t\t�ɹ���\n");
	while(t->next){
		t=t->next;
	}
	t->next=new;
	printf("\t\t��������˳�");
	getch();
}

void deleteUser(void){
	char code[20];
	Book *a;
	User *head=User_head;
	User *t=User_head->next;
	printf("\t\t�û��������¡�����\n");
	if(!t){
		printf("\n\t\t��Ǹ���Ҳ������û�\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}
	printf("\n\n     *************************************");
	printf("********************************\n\n");
	printf("      %-10s%-8s%-10s\n\n","���","�û���","��������");
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

	printf("\t\t����������ɾ���û����˺ţ�"); 
	gets(code);
	t=findUserCode(code);
	if(!t){
		printf("\t\t��Ǹ���Ҳ������û�\n");
		printf("\t\t��������˳�");
		getch();
		return;
	}
	printf("\t\tɾ���ɹ���\n");
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
	printf("\t\t��������˳�\n");
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
		    printf("\t\t��");
		    scanf("%c",&c);
		    while(getchar()!='\n');
		    switch(c){
			   case '1':uBorrow(user);break;
			   case '2':uBack(user);break;
			   case '3':findBook();break;
			   case '0':saveAll();break;
			   default:printf("\t\t�����������������\n");Sleep(500);break;	    
		    }
	    }
    } 
	
        else if(strcmp(argv[1],"-a")==0){ 
        amenu(argv[2]);
        char c = '1';
		while(c!='0'){
		    printf("\t\t��");
		    scanf("%c",&c);
		    while(getchar()!='\n');
		    switch(c){
			    case '1':addBook();break;
			    case '2':deleteBook();break;
			    case '3':addUser();break;
			    case '4':deleteUser();break;
			    case '0':saveAll();break;		
				default:printf("\t\t�����������������\n");Sleep(500);break;		    
		    }
	    }
    }

    system("PAUSE");
    return 0;
} 

