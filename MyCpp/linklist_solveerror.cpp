#include<stdio.h>
#include<stdlib.h>
typedef char datatype;
typedef struct node
{	datatype data;
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

int get2(linklist *head ,char i)
{	
	int j;
	linklist *p;
	p=head->next;
	j=0;	
	while (p!=NULL && p->data!=i)
	{ p=p->next;
	  j++;
	}
	if(p!=NULL)  
	{
		printf("find! \n");
		return j;
	}
	else 
	{
		printf("not find! \n");   
		return -1;
	}
}

int main(void)
{
	linklist *head,*r;
	int result;
	char f = 'b';
	head=createlist();
	scanf("%c",&f);
	printf("链表信息为:");
	r=head->next;
	while(r)
	{
		printf("%c",r->data);
		r=r->next;
	}
    printf("请输入要查询的字符:\n");
	scanf("%c",&f);
	result= get2(head,f);
	printf("%d\n",result);
	return 0;
}
