#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 1024
typedef char datatype;


typedef struct node
{ datatype data;
	struct node *lchild,*rchild;
}  bitree;

bitree *CREATREE()
{	char ch;int i=0;
	bitree *Q[maxsize];
	int front,rear;
	bitree *root,*s;
	root=NULL;
	front=1;rear=0;
	printf("请输入二叉树的各结点，@表示虚结点，以‘#’结束：\n");
	scanf("%c",&ch);
	while(ch!='#')
	{	putchar(ch);
		s=NULL;
		if(ch!='@')
		{
			s=(bitree *)malloc(sizeof(bitree));
			s->data=ch;
			s->lchild=NULL;
			s->rchild=NULL;
			i++;
		}
		rear++;
		Q[rear]=s;
		if(rear==1)
			root=s;
		else
		{
			if(s&&Q[front])
				if(rear%2==0)
					Q[front]->lchild=s;
				else
					Q[front]->rchild=s;
			if(rear%2==1)
				front++;
		}
		scanf("%c",&ch);
	}
	return root;
}


void preorder(bitree *p)/*  xian */
{	
	if(p!=NULL)
	{	
		printf("%c",p->data);
		preorder(p->lchild);
		preorder(p->rchild);
	}
	return;
}


void inorder(bitree *p)/*  zhong */
{	
	if(p!=NULL)
	{	
		inorder(p->lchild);
		printf("%c",p->data);
		inorder(p->rchild);
	}
	return;
}

void postorder(bitree *p)/*  hou */
{	
	if(p!=NULL)
	{	
		postorder(p->lchild);
		postorder(p->rchild);
		printf("%c",p->data);
	}
	return;
}

/*void chaxunorder(bitree *p,char g)   // chaxun 
{	
	
	//bitree *p;p=root;
	
	int flag=0;
	  if(p!=NULL)
	{	
		inorder(p->lchild);
		if(p->data==g)
			{
				printf("\n已找到该字符%c",p->data);
				flag=1;
			}
		inorder(p->rchild);
		
	}
	if(flag==0)
		printf("\n未找到该字符");
	return;
}*/

bitree *chaxunorder(bitree *p,char g)  //chaxun
{	
	if(p->data==g)
		return p;
	if(p->lchild!=NULL)
		return(chaxunorder(p->lchild,g));
	if(p->rchild!=NULL)
		return(chaxunorder(p->rchild,g));
	return NULL;
}


int main(void)
{	
	char g;
	bitree *root,*r;
	root=CREATREE();
	printf("\n先序遍历如果如下：\n");
	preorder(root);
	printf("\n中序遍历如果如下：\n");
	inorder(root);
	printf("\n后序遍历如果如下：\n");
	postorder(root);
	printf("\n请入要查询的字符：\n");
	getchar();
	scanf("%c",&g);
	r=chaxunorder(root,g);
	printf("%c\n",r->data);
	return 0;
}