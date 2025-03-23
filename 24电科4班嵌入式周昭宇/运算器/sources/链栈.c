#include<stdio.h>
#include<stdlib.h> 
//定义节点 
typedef struct StackNode{
	int data;
	struct StackNode*next;
}StackNode;

//定义链栈 
typedef struct LinkedStack{
	StackNode*top;
}LinkedStack;

//初始化 
LinkedStack*initStack()
{
	LinkedStack*stack=(LinkedStack*)malloc(sizeof(LinkedStack));
	if(stack!=NULL)
	{
		stack->top=NULL;
	}
	return stack;
}

//销毁链栈 
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

//入栈 
void push(LinkedStack*stack,int data)
{
	StackNode*newNode=(StackNode*)malloc(sizeof(StackNode));
	newNode->next=stack->top->next;
	newNode->data=data;
	stack->top=newNode;
}

//出栈
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

//找栈顶元素 
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

