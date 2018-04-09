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


int get2(linklist *head ,char i)
{	
	int j,num=0;
	linklist *p;
	p=head;j=0;
	while((p->next!=NULL))
	{
		p=p->next;num++;}
	p=head;
	while((p->next!=NULL))
	{
		p=p->next;
		if (p->data==i) 
		{
			printf("已找到该字符, 位置为：");
			printf("%d\n",j+1);	
			return 0;
		}
		else j++;
	}
	if(num==j) printf("未找到 \n");  
}



/*int InsertSList(SeqList *r,int i,DataType x)// 插入操作
{
	int j;
	if(i<1||i>r->last+2)return(-1);
	if(r-last==MAXSIZE-1)return(-1);
	for(j=r->last;j>=i-1;j--)
		r->data[i+1]=r->data[j];
	r->data[i-1]=x;
	r->last++;
	return 1;
}*/
void insert(linklist *head ,char i,x)
{	
	int j,a,num=0;
	linklist *p;
	p=head;j=0;
	while((p->next!=NULL))
	{
		p=p->next;num++;}
	p=head;
	while((p->next!=NULL))
	{
		p=p->next;
		if (p->data==i) 
		{
			printf("已找到该字符, 位置为：");
			printf("%d\n",j+1);	
		}
		else j++;
	}
	if(num==j) printf("未找到 \n");  
	for(a=num;a>=j-1;a--)// 插入操作
		p->data[a+1]=p->data[a];
	L->data[j-1]=x;
	L->last++;
	return1;
}

/*int ListDelete(SeqList *r,int i)//删除操作
{
	int j;
	if(i<1||i>r->last+1)return(-1);
	if(r->last==-1)return(-1);
	for(j=i;j<=r->last;j++)
		r->data[j-1]=r->data[j];
	r->last--;
	return(1);
}*/

int main(void)
{
	linklist *head,*r;
	char zifu;
	head=createlist();
	printf("链表信息为:");
	r=head->next;
	while(r)
	{
		printf("%c",r->data);
		r=r->next;
	}

		printf("请输入要查询的字符：\n");
		getchar();
		scanf("%c",&zifu);
		int result;
		result= get2(head,zifu);
	return 0;
}

