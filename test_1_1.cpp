#include<stdio.h>
#include<stdlib.h>
typedef char datatype;
typedef struct node
{
	datatype data;
	struct node *next;
}linklist;
linklist *createlist()
{
	char ch;
	linklist *head,*s,*r;
	head=(linklist*)malloc(sizeof(linklist));
	r=head;
	printf("请输入字符产生链表，以#结束\n");
	ch=getchar();
	while(ch!='#')
	{
		s=(linklist*)malloc(sizeof(linklist));
		s->data=ch;
		r->next=s;
		r=s;
		ch=getchar();
	}
   r->next=NULL;
   return head;
}
linklist *get(linklist *head ,int i)
{	
	int j;
	linklist *p;
	p=head;j=0;
	while((p->next!=NULL)&&(j<i))
	{
		p=p->next;
		j++;
	}
	if (i==j)return p;
	else return NULL;
}
void main()
{
	linklist *head,*r;
	int num;
	head=createlist();
	printf("链表信息为:");
	r=head->next;
	while(r)
	{
		printf("%c",r->data);
		r=r->next;
	}
	printf("\n");
		printf("请输入要查询的序号：\n");
		scanf("%d",&num);
		r=get(head,num);
		if(r==NULL)printf("            \n");
		printf("查找的结果为 :%c\n",r->data);
	}