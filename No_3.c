#include<stdio.h> 

struct MyStack
{
   int index;
   int data[100];
};

void push(struct MyStack *stack,int num){ //元素入栈 
	stack->data[stack->index] = num;
	stack->index++;
	int i;
	printf("栈中元素为：");
	for(i=0;i<stack->index;i++){
		printf("%d ",stack->data[i]); 
	}
	printf("\n");
}

int pop(struct MyStack *stack){ //删除栈顶元素并返回 
	stack->index--;
	return stack->data[stack->index];
}

int peek(struct MyStack *stack){ //返回栈顶元素 
	int i =stack->index-1;
	return stack->data[i];
}

void print(struct MyStack *stack){//打印栈中元素 
	int i;
	printf("栈中元素为：");
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
  printf("栈顶元素为：%d\n",peek(&stack));
  print(&stack);
  printf("栈顶元素已出栈且栈顶元素为：%d\n",pop(&stack));
  print(&stack);
  return 0;
}
