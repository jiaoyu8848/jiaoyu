#include<stdio.h>
#include<stdlib.h> 
//����ڵ� 
typedef struct StackNode{
	int data;
	struct StackNode*next;
}StackNode;

//������ջ 
typedef struct LinkedStack{
	StackNode*top;
}LinkedStack;

//��ʼ�� 
LinkedStack*initStack()
{
	LinkedStack*stack=(LinkedStack*)malloc(sizeof(LinkedStack));
	if(stack!=NULL)
	{
		stack->top=NULL;
	}
	return stack;
}

//������ջ 
void freeStack(LinkedStack*stack)
{
	StackNode*current=stack->top;
	StackNode*next;
	while(current!=NULL)
	{
		next=current->next;
		free(current);
		current=next;
	}
}

//��ջ 
void push(LinkedStack*stack,int data)
{
	StackNode*newNode=(StackNode*)malloc(sizeof(StackNode));
	newNode->next=stack->top->next;
	newNode->data=data;
	stack->top=newNode;
}

//��ջ
void pop(LinkedStack*stack,int data)
{
	if(stack!=NULL)	
	{
		StackNode*temp=stack->top;
		data=temp->data;
		stack->top=temp->next;
		free(temp);
	}
} 

//��ջ��Ԫ�� 
int peek(LinkedStack*stack)
{
	if (stack!=NULL)
	{
		return stack->top->data;
	}
} 


int main(){
LinkedStack*stack=initStack();
	freeStack(stack);
	return 0;

}

