#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//常量和宏的定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX(x,y) ((x)>(y)?(x):(y))

typedef int status;
typedef int KeyType;

//结点结构定义
typedef struct{
    KeyType key;
    char others[20];
}TElemType;

//二叉树结构定义
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//多个二叉树的管理
typedef struct{
    struct{
        char name[20];
        BiTree T;
    }elem[10];
    int length;
}BTA;

//访问函数
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

//定义队列
typedef struct{
    BiTree data[50];
    int front;
    int rear;
}Queue;

//初始化队列
status InitQueue(Queue *Q)
{
    Q->front=Q->rear=0;
    return OK;
}

//入列
status EnQueue(Queue *Q,BiTree p)
{
    if((Q->rear+1)%50==Q->front) return ERROR;
    else
    {
        Q->data[Q->rear]=p;
        Q->rear=(Q->rear+1)%50;
        return OK;
    }
}

//出列
status DeQueue(Queue *Q,BiTree *q)
{
    if(Q->rear==Q->front) return ERROR;
    else
    {
        *q=Q->data[Q->front];
        Q->front=(Q->front+1)%50;
        return OK;
    }
}

//函数原型
status CreateBiTree(BiTree *T,TElemType definition[]);
status Judgedata(TElemType definition[]);
status PreOrderTraverse(BiTree T);
status InOrderTraverse(BiTree T);
status PostOrderTraverse(BiTree T);
status LevelOrderTraverse(BiTree T);
status DestroyBiTree(BiTree *T);
status ClearBiTree(BiTree *T);
status EmptyBiTree(BiTree T);
int BiTreeDepth(BiTree T);
BiTree LocateNode(BiTree T,KeyType e);
status Assign(BiTree T, KeyType e, TElemType value);
BiTree GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree *T,KeyType e,int LR,TElemType c);
status DeleteNode(BiTree *T,KeyType e);
BiTree ParentTree(BiTree T,BiTree p);
int MaxSumPath(BiTree T);
BiTree LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2);
status InvertTree(BiTree *T,BiTree *NEWT);
status SaveBiTree(BiTree T,char FileName[]);
status LoadBiTree(BiTree *T,char FileName[]);
int NodeNumber(BiTree T);
int leafnum(BiTree T);


BiTree T=NULL,NEWT=NULL;
TElemType definition[100]={0};
int main(void)
{
    BTA bta;
    bta.length=0;
    int op=1,state=0,ans,i=0,depth=0,key,key2,pos,num=0,count=0,j=0;
    char filename[20],treename[20];
    TElemType value;
    BiTree p,q;
    printf("\n\n");
    //定义二叉树，按先序序列接受数据
    printf("按先序序列建立二叉树，请输入二叉树的定义\n如1a,2b,空结点表示为0null,以-1null表示结束:\n");
    do {
        scanf("%d%s",&definition[i].key,definition[i].others);
    } while (definition[i++].key!=-1);
    i=0;
    //开始菜单选择
    while(op)
    {
        system("cls");
        printf("      Menu for Binary Tree \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. CreateBiTree        2. PreOrderTraverse\n");
        printf("    	  3. InOderTraverse      4. PostOrderTraverse\n");
        printf("    	  5. LevelOderTraverse   6. DestroyBiTree\n");
        printf("    	  7. ClearBiTree         8. EmptyBiTree\n");
        printf("    	  9. BiTreeDepth         10.LocateNode\n");
        printf("    	  11.Assign              12.GetSibling\n");
        printf("    	  13.InsertNode          14.DeleteNode\n");
        printf("    	  15.ParentTree          16.MaxPathSum\n");
        printf("    	  17.SaveBiTree          18.LoadBiTree\n");
        printf("    	  19.LowestCommonAncestor 20.InvertTree\n");
        printf("    	  21.AddBiTree           22.LocateBiTree\n");
        printf("    	  23.DeleteBiTree        24.SelectBiTree\n");
        printf("    	  25.NodeNumber          26.leafnum\n");
        printf("          0.exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~26]:");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                state=Judgedata(definition);
                if(state==ERROR)
                {
                    printf("\n关键字不唯一！\n");
                    getchar();
                    getchar();
                    break;
                }
                if(T)
                {
                    printf("\n二叉树已存在，不能再次创建！\n");
                    getchar();
                    getchar();
                    break;
                }
                state=CreateBiTree(&T,definition);
                printf("\n二叉树已创建成功！\n");
                getchar();
                getchar();
                break;
            case 2:
                if(!T)
                {
                    printf("\n二叉树不存在，无法前序遍历！\n");
                    getchar();
                    getchar();
                    break;
                }
                PreOrderTraverse(T);
                getchar();
                getchar();
                break;
            case 3:
                if(!T)
                {
                    printf("\n二叉树不存在，无法中序遍历！\n");
                    getchar();
                    getchar();
                    break;
                }
                InOrderTraverse(T);
                getchar();
                getchar();
                break;
            case 4:
                if(!T)
                {
                    printf("\n二叉树不存在，无法后序遍历！\n");
                    getchar();
                    getchar();
                    break;
                }
                PostOrderTraverse(T);
                getchar();
                getchar();
                break;
            case 5:
                if(!T)
                {
                    printf("\n二叉树不存在，无法层序遍历！\n");
                    getchar();
                    getchar();
                    break;
                }
                LevelOrderTraverse(T);
                getchar();
                getchar();
                break;
            case 6:
                if(!T)
                {
                    printf("\n二叉树不存在，无法销毁！\n");
                    getchar();
                    getchar();
                    break;
                }
                DestroyBiTree(&T);
                printf("\n二叉树已成功销毁！\n");
//                for(i=0;i<10;i++) printf("%d ",definition[i].key);
                getchar();
                getchar();
                break;
            case 7:
                if(!T)
                {
                    printf("\n二叉树不存在，无法清空！\n");
                    getchar();
                    getchar();
                    break;
                }
                ClearBiTree(&T);
                printf("\n二叉树已清空！\n");
                getchar();
                getchar();
                break;
            case 8:
                state=EmptyBiTree(T);
                if(state==INFEASIBLE) printf("\n二叉树不存在！\n");
                else if(state==TRUE) printf("\n二叉树为空！\n");
                else printf("\n二叉树不为空！\n");
                getchar();
                getchar();
                break;
            case 9:
                if(!T)
                {
                    printf("\n二叉树不存在!\n");
                    getchar();
                    getchar();
                    break;
                }
                depth=BiTreeDepth(T);
                printf("二叉树的深度为：%d",depth);
                getchar();
                getchar();
                break;
            case 10:
                if(!T)
                {
                    printf("\n二叉树不存在!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n请输入需要查找的结点的关键字：\n");
                scanf("%d",&key);
                p=LocateNode(T,key);
                if(!p) printf("\n所查找的结点不存在！\n");
                else
                    printf("\n查找的节点是：%d,%s\n",p->data.key,p->data.others);
                getchar();
                getchar();
                break;
            case 11:
                if(!T)
                {
                    printf("\n二叉树不存在!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n请输出需要改变结点的关键字：\n");
                scanf("%d",&key);
                printf("\n请输入新结点的关键字和值：\n");
                scanf("%d%s",&value.key,value.others);
                state=Assign(T,key,value);
                if(state==ERROR) printf("\n赋值失败！\n");
                else printf("\n赋值成功！\n");
                getchar();
                getchar();
                break;
            case 12:
                if(!T)
                {
                    printf("\n二叉树不存在!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n请输入需要查找兄弟的结点的关键字：\n");
                scanf("%d",&key);
                p=GetSibling(T,key);
                if(!p) printf("\n该结点没有兄弟！\n");
                else printf("\n该结点的兄弟结点是：%d,%s\n",p->data.key,p->data.others);
                getchar();
                getchar();
                break;
            case 13:
                printf("\n请输入插入结点的位置，0表示左孩子，1表示右孩子，-1表示作为根节点插入：\n");
                scanf("%d",&pos);
                if(pos!=-1)
                {
                    printf("\n请输入插入结点双亲的关键字：\n");
                    scanf("%d",&key);
                }
                printf("\n请输入插入结点的关键字和值：\n");
                scanf("%d%s",&value.key,value.others);
                if(LocateNode(T,value.key))
                {
                    printf("\n插入结点的关键字重复！\n");
                    getchar();
                    getchar();
                    break;
                }
                state=InsertNode(&T,key,pos,value);
                if(state==ERROR)
                    printf("\n插入失败！\n");
                else
                    printf("\n插入成功！\n");
                getchar();
                getchar();
                break;
            case 14:
                printf("\n请输入需要删除的结点的关键字:\n");
                scanf("%d",&key);
                state=DeleteNode(&T,key);
                if(state==ERROR)
                    printf("\n删除失败！\n");
                else
                    printf("\n删除成功！\n");
                getchar();
                getchar();
                break;
            case 15:
                printf("\n请输入需要查找双亲的结点的关键字：\n");
                scanf("%d",&key);
                q=LocateNode(T,key);
                p=ParentTree(T,q);
                if(!p) printf("\n该结点为根节点或者该结点不存在！\n");
                else printf("\n该结点的双亲是：%d,%s\n",p->data.key,p->data.others);
                getchar();
                getchar();
                break;
            case 16:
                if(!T)
                {
                    printf("\n二叉树不存在!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n和最大的路径是：\n");
                MaxSumPath(T);
                printf("\n二叉树的最大路径和为：%d\n",maxroute(T));
                getchar();
                getchar();
                break;
            case 17:
                if(!T)
                {
                    printf("\n二叉树不存在！\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n请输入需要保存的文件名称：\n");
                scanf("%s",filename);
                SaveBiTree(T,filename);
                printf("\n已成功保存！\n");
                getchar();
                getchar();
                break;
            case 18:
                printf("\n请输入需要读取的文件名称：\n");
                scanf("%s",filename);
                LoadBiTree(&T,filename);
                printf("\n已成功读取！\n");
                getchar();
                getchar();
                break;
            case 19:
               if(!T)
                {
                    printf("\n二叉树不存在!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n请输入需要查找最小公共祖先的两个结点的关键字：\n");
                scanf("%d %d",&key,&key2);
                BiTree p=LowestCommonAncestor(T,key,key2);
                printf("\n最小公共祖先是：%d,%s\n",p->data.key,p->data.others);
                getchar();
                getchar();
                break;
            case 20:
                if(!T)
                {
                    printf("\n二叉树不存在!\n");
                    getchar();
                    getchar();
                    break;
                }
                InvertTree(&T,&NEWT);
                T=NEWT;
                printf("\n已成功交换左右子树！\n");
                getchar();
                getchar();
                break;
            case 21:
                printf("\n请输入添加二叉树的数量：\n");
                scanf("%d",&num);
                while(count<num)
                {
                    printf("\n请输入二叉树的名称：\n");
                    scanf("%s",bta.elem[count].name);
                    printf("\n请输入二叉树的定义：\n");
                    do {
                        scanf("%d%s",&definition[i].key,definition[i].others);
                    } while (definition[i++].key!=-1);
                    i=0;
                    CreateBiTree(&bta.elem[bta.length++].T,definition);
                    count++;
                }
                printf("\n创建成功！\n");
                count=0;
                getchar();
                getchar();
                break;
            case 22:
                printf("\n请输入需要查找的二叉树的名称：\n");
                scanf("%s",treename);
                for(i=0;i<bta.length;i++)
                    if(!strcmp(treename,bta.elem[i].name)) break;
                if(i>=bta.length) printf("\n二叉树不存在！\n");
                else printf("\n所查找的二叉树是第%d个！\n",i+1);
                getchar();
                getchar();
                break;
            case 23:
                printf("\n请输入需要删除的二叉树的名称：\n");
                scanf("%s",treename);
                for(i=0;i<bta.length;i++)
                    if(!strcmp(treename,bta.elem[i].name)) break;
                if(i>=bta.length) printf("\n二叉树不存在！\n");
                else
                {
                    for(j=i;j<bta.length-1;j++)
                        bta.elem[j]=bta.elem[j+1];
                    bta.length--;
                    printf("\n删除成功！\n");
                }
                getchar();
                getchar();
                break;
            case 24:
                printf("\n请输入选定的二叉树名称：\n");
                scanf("%s",treename);
                for(i=0;i<bta.length;i++)
                    if(!strcmp(treename,bta.elem[i].name)) break;
                if(i>=bta.length) printf("\n二叉树不存在！\n");
                else
                {
                     T=bta.elem[i].T;
                     printf("\n选定成功！\n");
                }
                getchar();
                getchar();
                break;
            case 25:
                if(!T)
                {
                    printf("\n二叉树不存在!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n二叉树有%d个结点！\n",NodeNumber(T));
                getchar();
                getchar();
                break;
            case 26:
                if(!T)
                {
                    printf("\n二叉树不存在!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n二叉树有%d个叶子！\n",leafnum(T));
                getchar();
                getchar();
                break;
            case 0:
                break;
        }
    }
}



//判断二叉树的结点中关键字是否重复
status Judgedata(TElemType definition[])
{
    int num[200]={0},flag=0,j=0;  //建立标记数组 空间换时间
    while(definition[j].key!=-1)
    {
        num[definition[j].key]++;
        if(num[definition[j].key]>1&&definition[j].key!=0)
            return ERROR;
        j++;
    }
    return OK;
}



//创建二叉树
int i=0; //定义一个全局变量
status CreateBiTree(BiTree *T,TElemType definition[])
{
    //空结点赋值为null
    if(definition[i].key==0)
    {
        *T=NULL;
        i++;
        return OK;
    }
    else
    {
        *T=(BiTree)malloc(sizeof(BiTNode));
        (*T)->data=definition[i];
        i++;
        CreateBiTree(&((*T)->lchild),definition);  //递归创建
        CreateBiTree(&((*T)->rchild),definition);
    }
    //创建完成一个二叉树后，将i重置为0
    if((*T)->data.key==definition[0].key) i=0;
    return OK;
}

//前序遍历的递归实现
status PreOrderTraverse(BiTree T)
{
    if(!T) return OK;
    else
    {
        printf("%d,%s ",T->data.key,T->data.others);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
        return OK;
    }
}

//中序遍历的递归实现
//status InOrderTraverse(BiTree T)
//{
//    if(!T) return OK;
//    else
//    {
//        InOrderTraverse(T->lchild);
//        printf("%d,%s ",T->data.key,T->data.others);
//        InOrderTraverse(T->rchild);
//        return OK;
//    }
//}

//中序遍历使用栈实现
status InOrderTraverse(BiTree T)
{
    BiTree st[20];
    int top=0;
    do{
        while(T)
        {
            if(top==20) exit(OVERFLOW);
            st[++top]=T;
            T=T->lchild;
        }
        if(top)
        {
            T=st[top--];
            printf("%d,%s ",T->data.key,T->data.others);
            T=T->rchild;
        }
    }while(top||T);
}

//后序遍历
status PostOrderTraverse(BiTree T)
{
    if(!T) return OK;
    else
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%d,%s ",T->data.key,T->data.others);
        return OK;
    }
}

//层序遍历 使用队列
status LevelOrderTraverse(BiTree T)
{
    Queue Q;
    InitQueue(&Q);
    BiTree p;
    EnQueue(&Q,T);
    while(Q.front!=Q.rear)
    {
        DeQueue(&Q,&p);
        printf("%d,%s ",p->data.key,p->data.others);
        if(p->lchild) EnQueue(&Q,p->lchild);
        if(p->rchild) EnQueue(&Q,p->rchild);
    }
    return OK;
}

//销毁二叉树，并释放所有结点的空间
status DestroyBiTree(BiTree *T)
{
    if(!*T) return ERROR;
    DestroyBiTree(&(*T)->lchild);
    DestroyBiTree(&(*T)->rchild);
    free(*T);
    *T=NULL;
    return OK;
}

//、、、、置空二叉树 结点空间未释放
status ClearBiTree(BiTree *T)
{
    if(!(*T)) return OK;
    (*T)->data.key=0;
    strcpy((*T)->data.others,"null");
    ClearBiTree(&(*T)->lchild);
    ClearBiTree(&(*T)->rchild);
    return OK;
}

//判断二叉树是否为空
status EmptyBiTree(BiTree T)
{
    if(!T) return INFEASIBLE;
    if(!T->data.key) return TRUE;
    else return ERROR;
}

//递归求树的深度
int BiTreeDepth(BiTree T)
{
    if(!T) return 0;
    int depth1=1,depth2=1;
    depth1+=BiTreeDepth(T->lchild);
    depth2+=BiTreeDepth(T->rchild);
    return MAX(depth1,depth2);  //比较两次递归结果并取最大值返回
}

//查找结点位置
BiTree LocateNode(BiTree T,KeyType e)
{

    if(!T) return NULL;
    if(T->data.key==e) return T;

    BiTree p=LocateNode(T->lchild,e);
    if(p) return p;  //若在左子树找到则返回p，否则在右子树中找
    p=LocateNode(T->rchild,e);
    if(p) return p;   //若在右子树找到则返回，否则返回NULL
    else return NULL;
}

//给节点赋值
status Assign(BiTree T, KeyType e, TElemType value)
{
    BiTree p;
    p=LocateNode(T,e);   //判断关键字是否重复
    if(!p) return ERROR;
    else
    {
        if(value.key!=e&&LocateNode(T,value.key)) return ERROR;
        p->data=value;
        return OK;
    }
}

//获得兄弟结点
BiTree GetSibling(BiTree T,KeyType e)
{
    if(T->lchild==NULL&&T->rchild==NULL) return NULL;
    if(T->lchild!=NULL&&T->lchild->data.key==e) return T->rchild;  //注意先要判空
    if(T->rchild!=NULL&&T->rchild->data.key==e) return T->lchild;

    if(T->lchild)
    {
        BiTree p=GetSibling(T->lchild,e);
        if(p) return p;
    }

    if(T->rchild)
    {
        BiTree p=GetSibling(T->rchild,e);
        if(p) return p;
    }

    return NULL;
}

//插入结点
status InsertNode(BiTree *T,KeyType e,int LR,TElemType c)
{
    if(LR==-1) //作为根节点插入
    {
        BiTree p=(BiTree)malloc(sizeof(BiTNode));
        p->data=c;
        p->lchild=NULL;
        p->rchild=*T;
        *T=p;
        return OK;
    }

    BiTree p;
    p=LocateNode(*T,e);
    if(!p) return ERROR;
    else
    {
        if(LR==0) //左孩子插入
        {
            BiTree q=(BiTree)malloc(sizeof(BiTNode));
            q->data=c;
            if(!p->lchild)
            {
                q->lchild=NULL;
                q->rchild=NULL;
                p->lchild=q;
            }
            else
            {
                q->rchild=p->lchild;
                q->lchild=NULL;
                p->lchild=q;
            }
            return OK;
        }

        if(LR==1)  //右孩子插入
        {
            BiTree q=(BiTree)malloc(sizeof(BiTNode));
            q->data=c;
            if(!p->rchild)
            {
                q->lchild=NULL;
                q->rchild=NULL;
                p->rchild=q;
            }
            else
            {
                q->rchild=p->rchild;
                q->lchild=NULL;
                p->rchild=q;
            }
            return OK;
        }
    }
}

//求结点双亲
BiTree ParentTree(BiTree T,BiTree p)
{
    BiTree q=NULL;
    if(T==NULL||p==T) return NULL;
    else
    {
        if(T->lchild==p||T->rchild==p) return T;
        q=ParentTree(T->lchild,p);
        if(!q)
        {
            q=ParentTree(T->rchild,p);
            return q;
        }
        return q;
    }
}

//删除结点
status DeleteNode(BiTree *T, KeyType e)
{
    BiTree p,q,k,m;
    p=LocateNode(*T,e);
    if(!p) return ERROR;
    if(!p->lchild&&!p->rchild)
    {
        if(p==(*T))
        {
            free(p);
            return OK;
        }
        else
        {
            q=ParentTree(*T,p);
            if(q->lchild==p)
            {
                free(p);
                q->lchild=NULL;
            }
            else
            {
                free(p);
                q->lchild=NULL;
            }
        }
        return OK;
    }
    else if(p->lchild&&p->rchild)
    {
        if(p==*T)
        {
            q=*T;
            m=(*T)->lchild;
            while(m->rchild) m=m->rchild;
            m->rchild=(*T)->rchild;
            (*T)=(*T)->lchild;
            free(q);
            return OK;
        }
        q=ParentTree(*T,p);
        m=p->lchild;
        k=m;
        while(k->rchild) k=k->rchild;
        k->rchild=p->rchild;
        if(q->lchild==p)
        {
            free(p);
            q->lchild=m;
        }
        else
        {
            free(p);
            q->rchild=m;
        }
        return OK;
    }
    else
    {
        if((*T)==p)
        {
            q=(*T);
            if((*T)->lchild)
            {
                (*T)=(*T)->lchild;
                free(q);
            }
            else
            {
                (*T)=(*T)->rchild;
                free(q);
            }
            return OK;
        }
        q=ParentTree((*T),p);
        if(p->lchild) k=p->lchild;
        else k=p->rchild;
        if(q->lchild==p)
        {
            free(p);
            q->lchild=k;
        }
        else
        {
            free(p);
            q->rchild=k;
        }
        return OK;
    }
}

//辅助函数
int maxroute(BiTree T)
{
    if(!T) return 0;
    else
        return MAX(T->data.key+maxroute(T->lchild),T->data.key+maxroute(T->rchild));
}

//求最大路径和
int MaxSumPath(BiTree T)
{
    if(T)
    {
        printf("%d ",T->data.key);
        if(maxroute(T->lchild)>=maxroute(T->rchild))
            MaxSumPath(T->lchild);
        else
            MaxSumPath(T->rchild);
    }
}

//最小公共祖先
BiTree LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2)
{
    if(T==NULL||T->data.key==e1||T->data.key==e2) return T;
    BiTree left=LowestCommonAncestor(T->lchild,e1,e2); //左子树里找
    BiTree right=LowestCommonAncestor(T->rchild,e1,e2); //右子树里找
    if(left&&right) return T;
    else if(!left) return right;
    else return left;
}

//翻转二叉树
status InvertTree(BiTree *T,BiTree *NEWT)
{
    if(!*T)
    {
        *NEWT=NULL;
        return OK;
    }
    else
    {
        *NEWT=(BiTree)malloc(sizeof(BiTNode));
        (*NEWT)->data=(*T)->data;
        InvertTree(&(*T)->lchild,&(*NEWT)->rchild); //不同方向递归进行翻转
        InvertTree(&(*T)->rchild,&(*NEWT)->lchild);
        return OK;
    }
}

//用save来存储二叉树的信息 按照先序遍历顺序
int POT(BiTree T,TElemType *save)
{
    int i=0;
    if(!T)
    {
        save->key=0;
        strcpy(save->others,"null");
        i++;
    }
    if(T)
    {
        save->key=T->data.key;
        strcpy(save->others,T->data.others);
        i++;
        i+=POT(T->lchild,save+i);
        i+=POT(T->rchild,save+i);
    }
    return i;
}
//保存到二叉树
status SaveBiTree(BiTree T,char FileName[])
{
    FILE *fp;
    fp=fopen(FileName,"w");
    TElemType save[100];
    int i=0,j;
    i=POT(T,save);
    for(j=0;j<i;j++)
    {
        fprintf(fp,"%d %s ",(save+j)->key,(save+j)->others);
    }
    fclose(fp);
    return OK;
}


int create(BiTree *T,TElemType definition[])
{
    int i=0;
    if(definition->key==0)
    {
        *T=NULL;
        i++;
    }
    else
    {
        *T=(BiTree)malloc(sizeof(BiTNode));
        (*T)->data.key=(definition+i)->key;
        strcpy((*T)->data.others,(definition+i)->others);
        i++;
        i+=create(&(*T)->lchild,definition+i);
        i+=create(&(*T)->rchild,definition+i);
    }
    return i;
}
//导出二叉树
status LoadBiTree(BiTree *T,char FileName[])
{
    FILE *fp;
    fp=fopen(FileName,"r");
    TElemType load[100];
    int j=0;
    while(fscanf(fp,"%d %s ",&(load+j)->key,(load+j)->others)!=EOF)
        j++;
    fclose(fp);
    create(&(*T),load);
    return OK;
}
//递归求节点数
int NodeNumber(BiTree T)
{
    if(!T) return 0;
    else return NodeNumber(T->lchild)+NodeNumber(T->rchild)+1;
}
//求叶子树
int leafnum(BiTree T)
{
    if(!T) return 0;
    int cnt=0;
    if(!T->lchild&&!T->rchild) cnt++;
    int left=leafnum(T->lchild);
    int right=leafnum(T->rchild);
    cnt+=left+right;
    return cnt;
}
