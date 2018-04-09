#include<stdio.h>
#include<stdlib.h>
typedef int datatype;
typedef struct node
{	datatype data;
	struct node *next;
}linklist;
linklist *createlist()
{
	int num;
	linklist *head,*s,*r;
	head = NULL;
	printf("请输入数字，构成一个链表，以-1结束\n");
	scanf("%d",&num);
	while(num!=-1)
	{
		s=(linklist*)malloc(sizeof(linklist));
		s->data=num;
		if(head==NULL)
			head = s;
		else
			r->next=s;
		r=s;
		scanf("%d",&num);
	}
	r->next=NULL;
	return head;
}

linklist *insertnum(linklist *head ,int i,int x)
{	
	int j=1,temp=0;
	linklist *p,*s,*r;
	p=head;
	s = (linklist *) malloc(sizeof(linklist));
	s->data = x;
	while (p!=NULL && j<i)
	{ 
		r = p;  //保存前一个结点的地址
		p=p->next;
		j++;
	}
	//分三种情况考虑
	if(j==1)  
	{		
		s->next = head;
		head = s;			
	}
	else if (p!=NULL)
	{
		s->next = p->next;
		p->next = s;
		temp = p->data;
		p->data = s->data;
		s->data = temp;
	}
	else
	{   
		r->next = s;
		s->next = NULL;
	}
	return head;
}
void Print(linklist *head)
{
	linklist *r;
	r = head;
	while(r)
	{
		printf("%d",r->data);
		r=r->next;
	}
}
int main(void)
{
	linklist *head,*r;
	int result,f,x;
	head=createlist();
	printf("链表信息为:");
	r=head;
	Print(r);
    printf("请输入要插入的位置和值:\n");
	scanf("%d",&f);
	scanf("%d",&x);
	r = insertnum(head,f,x);
	Print(r);
	return 0;
}
