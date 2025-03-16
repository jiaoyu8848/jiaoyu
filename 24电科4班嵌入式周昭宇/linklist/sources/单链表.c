#include<stdio.h>
#include<stdlib.h> 
struct Node{
	int data;
	struct Node*next;
};

//创建头节点 
struct Node* creatlist()
{
	struct Node *head=(struct Node*)malloc(sizeof(struct Node));
	head->next=NULL;
	return head;
}

//创建新节点 
struct Node*creatNode(int data)
{
	struct Node*newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->data=data;
	newNode->next=NULL;
	return newNode; 
}

//销毁链表 
void destroyNode(struct Node*head)
{
	struct Node*current=head;
	struct Node*next;
	while(current!=NULL)
	{
		next=current->next;
		free(current);
		current=next;
	}
}

//插入节点 
void insertNode(struct Node*head,int data)
{
	struct Node*newNode=creatNode(data);
	newNode->next=head->next;
	head->next=newNode;
}

//删除节点 
void deleteNode(struct Node*head,int pos)
{
	 struct Node*posNode=head->next;
	 struct Node*posNodefront=head;  
	 if(posNode==NULL)
	 	printf("无法删除\n");
	else
		while(posNode->data!=pos)
	{
		posNodefront=posNode;
		posNode=posNodefront;
	}
	posNodefront->next=posNode->next;
	free(posNode);
}

//查找节点 
struct Node* seachNode(struct Node*head,int target)
{
	struct Node*current=head;
	while(current!=NULL)
	{
		if(current->data==target)
		{
			return current;
		}
		else current=current->next;
	}
	return NULL;
}

//打印链表 
void printlist(struct Node*head)
{
	struct Node*p=head->next;
	while(p)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
}


int main(){
struct Node*list=creatlist();
	insertNode(list,1);  
	insertNode(list,2); 
	insertNode(list,3); 
	printlist(list);
	return 0;

}

