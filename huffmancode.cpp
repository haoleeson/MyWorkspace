#include<stdio.h>	
#include<stdlib.h>
#include<string.h>
#define n   6          	/* 叶子数目 */
#define m 	2*n-1   	/* 结点总数 */  
#define Maxval 	1   	/* 最大权值 */   
typedef 	char 	datatype;	
typedef 	struct //定义为结构类型
{
	float weight;				 //权值
 	datatype data;				
 	int lchild, rchild, parent;	
} hufmtree;	
hufmtree  tree[m];				
typedef 	struct	
{	char 	bits[n];			/* 编码数组位串，其中n为叶子结点数目*/
	int 	start;         		/* 编码在位串的起始位置 */
	datatype data;       			
} codetype;		
codetype code[n];	

void HUFFMAN(hufmtree tree[ ])	
{	int 	i, j, p1,p2;	
 	char 	ch;		
	float small1,small2,f;	 
 	for( i=0; i<m; i++)          		/* 初始化 */
 	{	tree[i].parent=0;		
  		tree[i].lchild=0;	
		tree[i].rchild=0;	
		tree[i].weight=0.0;		
		tree[i].data= '0';		
 	}
	for( i=0;i<n;i++)				/* 输入n个结点的权值 */
	{	scanf("%f ", &f);	
		tree[i].weight=f;	
		scanf("%c", &ch);			//* 输入n个结点的值 */
		tree[i].data=ch; 
	}
    for(i=n;i<m;i++)	
	{	p1=p2=0;	
		small1=small2=Maxval;
		for ( j=0; j<=i-1; j++ )
			if ( tree[j].parent==0)
				if ( tree[j].weight<small1 )
				{	
					small2=small1;
					small1=tree[j].weight;
					p2=p1;
					p1=j;
				}
				else  if( tree[j].weight<small2 )
				{ 	
					small2=tree[j].weight;	
					p2=j;
				}
				tree[p1].parent=i;
				tree[p2].parent=i;
				tree[i].lchild=p1;
				tree[i].rchild=p2;
				tree[i].weight = tree[p1].weight+tree[p2].weight;
	}
}     
void HUFFMANCODE(codetype code[ ],hufmtree tree[ ] )	
/* code 存放求出的哈夫曼编码的数组	 */
{ 
	int i, c, p;	
 	codetype cd;						
 	for ( i=0; i<n; i++ )				
 	{	cd. start=n;	
  		c=i;								
   		p=tree[c].parent;	
  		cd.data=tree[c].data;
		while( p!=0 )
		{
			cd.start-- ;
			if( tree[p]. lchild == c)
				cd.bits[cd.start]= '0';
			else 
				cd.bits [cd.start]='1';
			c=p;
			p=tree[c].parent;
		}
		code[i]=cd;   	 /* 一个字符的编码存入code[i] */
		printf("%c:",cd.data );//输出cd的数据语句
		for(int k=cd.start;k<n;k++)
			printf("%c",cd.bits[k]);
		printf("\n");
	}
}
void HUFFMANDECODE(codetype code[ ],hufmtree tree[ ])	
{	int 	i, c, p, b;		
	int endflag=2;						
	i=m-1;								
	scanf ( "%1d", &b);  				
	while ( b != endflag)	
	{	if( b==0) 	i=tree[i].lchild;			
  		else i=tree[i].rchild;           		
		if ( tree[i].lchild==0 )
		{
			putchar( code[i].data);
			i=m-1;	
		}
		scanf("%1d", &b);
	}
	if ((tree[i].lchild!=0)&&(i!=m-1) )
		printf("\nERROR\n");
} 
 				
void main()	
{
	printf("输入结点的权值和结点字母，用空格隔开:(如：0.4 a)\n");	
	HUFFMAN( tree);	
	printf("\n编码结果\n");	
	HUFFMANCODE(code, tree );		
	printf("\n开始译码，请输入密码：\n");	
	HUFFMANDECODE(code, tree);	
	printf("\n");	

}

