#include<stdio.h> 

struct MyStack
{
   int index;
   int data[100];
};

void push(struct MyStack *stack,int num){ //Ԫ����ջ 
	stack->data[stack->index] = num;
	stack->index++;
	int i;
	printf("ջ��Ԫ��Ϊ��");
	for(i=0;i<stack->index;i++){
		printf("%d ",stack->data[i]); 
	}
	printf("\n");
}

int pop(struct MyStack *stack){ //ɾ��ջ��Ԫ�ز����� 
	stack->index--;
	return stack->data[stack->index];
}

int peek(struct MyStack *stack){ //����ջ��Ԫ�� 
	int i =stack->index-1;
	return stack->data[i];
}

void print(struct MyStack *stack){//��ӡջ��Ԫ�� 
	int i;
	printf("ջ��Ԫ��Ϊ��");
	for(i=0;i<stack->index;i++){
		printf("%d ",stack->data[i]);
	}
	printf("\n");
}
int main(){
  struct MyStack stack;
  stack.index=0;
  stack.data; 
  push(&stack,1);
  push(&stack,9);
  push(&stack,3);
  push(&stack,8);
  push(&stack,4);
  push(&stack,2);
  printf("ջ��Ԫ��Ϊ��%d\n",peek(&stack));
  print(&stack);
  printf("ջ��Ԫ���ѳ�ջ��ջ��Ԫ��Ϊ��%d\n",pop(&stack));
  print(&stack);
  return 0;
}
