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
	head=(linklist*)malloc(sizeof(linklist));
	r=head;
	printf("请输入数字，构成非递减有序表，以-1结束\n");
	scanf("%d",&num);
	while(num!=-1)
	{
		s=(linklist*)malloc(sizeof(linklist));
		s->data=num;
		r->next=s;
		r=s;
		scanf("%d",&num);
	}
	r->next=NULL;
	return head;
}

linklist *insert(linklist *head ,int i)
{	
	int j=0,temp=0;
	linklist *p,*s,*r;
	p=head->next;
	s = (linklist *) malloc(sizeof(linklist));
	s->data = i;
	while (p!=NULL && p->data<i)
	{ 
		r = p;  //保存前一个结点的地址
		p=p->next;
		j++;
	}
	//分三种情况考虑
	if(j==0)  
	{		
		s->next = head->next;
		head->next = s;			
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
	r = head->next;
	while(r)
	{
		printf("%d",r->data);
		r=r->next;
	}
}
int main(void)
{
	linklist *head,*r;
	int result,f;
	head=createlist();
	printf("链表信息为:");
	r=head;
	Print(r);
    printf("请输入要插入的数字:\n");
	scanf("%d",&f);
	r = insert(head,f);
	Print(r);
	return 0;
}
