#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//�����ͺ�Ķ���
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX(x,y) ((x)>(y)?(x):(y))

typedef int status;
typedef int KeyType;

//���ṹ����
typedef struct{
    KeyType key;
    char others[20];
}TElemType;

//�������ṹ����
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//����������Ĺ���
typedef struct{
    struct{
        char name[20];
        BiTree T;
    }elem[10];
    int length;
}BTA;

//���ʺ���
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

//�������
typedef struct{
    BiTree data[50];
    int front;
    int rear;
}Queue;

//��ʼ������
status InitQueue(Queue *Q)
{
    Q->front=Q->rear=0;
    return OK;
}

//����
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

//����
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

//����ԭ��
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
    //��������������������н�������
    printf("���������н�����������������������Ķ���\n��1a,2b,�ս���ʾΪ0null,��-1null��ʾ����:\n");
    do {
        scanf("%d%s",&definition[i].key,definition[i].others);
    } while (definition[i++].key!=-1);
    i=0;
    //��ʼ�˵�ѡ��
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
        printf("    ��ѡ����Ĳ���[0~26]:");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                state=Judgedata(definition);
                if(state==ERROR)
                {
                    printf("\n�ؼ��ֲ�Ψһ��\n");
                    getchar();
                    getchar();
                    break;
                }
                if(T)
                {
                    printf("\n�������Ѵ��ڣ������ٴδ�����\n");
                    getchar();
                    getchar();
                    break;
                }
                state=CreateBiTree(&T,definition);
                printf("\n�������Ѵ����ɹ���\n");
                getchar();
                getchar();
                break;
            case 2:
                if(!T)
                {
                    printf("\n�����������ڣ��޷�ǰ�������\n");
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
                    printf("\n�����������ڣ��޷����������\n");
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
                    printf("\n�����������ڣ��޷����������\n");
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
                    printf("\n�����������ڣ��޷����������\n");
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
                    printf("\n�����������ڣ��޷����٣�\n");
                    getchar();
                    getchar();
                    break;
                }
                DestroyBiTree(&T);
                printf("\n�������ѳɹ����٣�\n");
//                for(i=0;i<10;i++) printf("%d ",definition[i].key);
                getchar();
                getchar();
                break;
            case 7:
                if(!T)
                {
                    printf("\n�����������ڣ��޷���գ�\n");
                    getchar();
                    getchar();
                    break;
                }
                ClearBiTree(&T);
                printf("\n����������գ�\n");
                getchar();
                getchar();
                break;
            case 8:
                state=EmptyBiTree(T);
                if(state==INFEASIBLE) printf("\n�����������ڣ�\n");
                else if(state==TRUE) printf("\n������Ϊ�գ�\n");
                else printf("\n��������Ϊ�գ�\n");
                getchar();
                getchar();
                break;
            case 9:
                if(!T)
                {
                    printf("\n������������!\n");
                    getchar();
                    getchar();
                    break;
                }
                depth=BiTreeDepth(T);
                printf("�����������Ϊ��%d",depth);
                getchar();
                getchar();
                break;
            case 10:
                if(!T)
                {
                    printf("\n������������!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n��������Ҫ���ҵĽ��Ĺؼ��֣�\n");
                scanf("%d",&key);
                p=LocateNode(T,key);
                if(!p) printf("\n�����ҵĽ�㲻���ڣ�\n");
                else
                    printf("\n���ҵĽڵ��ǣ�%d,%s\n",p->data.key,p->data.others);
                getchar();
                getchar();
                break;
            case 11:
                if(!T)
                {
                    printf("\n������������!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n�������Ҫ�ı���Ĺؼ��֣�\n");
                scanf("%d",&key);
                printf("\n�������½��Ĺؼ��ֺ�ֵ��\n");
                scanf("%d%s",&value.key,value.others);
                state=Assign(T,key,value);
                if(state==ERROR) printf("\n��ֵʧ�ܣ�\n");
                else printf("\n��ֵ�ɹ���\n");
                getchar();
                getchar();
                break;
            case 12:
                if(!T)
                {
                    printf("\n������������!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n��������Ҫ�����ֵܵĽ��Ĺؼ��֣�\n");
                scanf("%d",&key);
                p=GetSibling(T,key);
                if(!p) printf("\n�ý��û���ֵܣ�\n");
                else printf("\n�ý����ֵܽ���ǣ�%d,%s\n",p->data.key,p->data.others);
                getchar();
                getchar();
                break;
            case 13:
                printf("\n������������λ�ã�0��ʾ���ӣ�1��ʾ�Һ��ӣ�-1��ʾ��Ϊ���ڵ���룺\n");
                scanf("%d",&pos);
                if(pos!=-1)
                {
                    printf("\n�����������˫�׵Ĺؼ��֣�\n");
                    scanf("%d",&key);
                }
                printf("\n�����������Ĺؼ��ֺ�ֵ��\n");
                scanf("%d%s",&value.key,value.others);
                if(LocateNode(T,value.key))
                {
                    printf("\n������Ĺؼ����ظ���\n");
                    getchar();
                    getchar();
                    break;
                }
                state=InsertNode(&T,key,pos,value);
                if(state==ERROR)
                    printf("\n����ʧ�ܣ�\n");
                else
                    printf("\n����ɹ���\n");
                getchar();
                getchar();
                break;
            case 14:
                printf("\n��������Ҫɾ���Ľ��Ĺؼ���:\n");
                scanf("%d",&key);
                state=DeleteNode(&T,key);
                if(state==ERROR)
                    printf("\nɾ��ʧ�ܣ�\n");
                else
                    printf("\nɾ���ɹ���\n");
                getchar();
                getchar();
                break;
            case 15:
                printf("\n��������Ҫ����˫�׵Ľ��Ĺؼ��֣�\n");
                scanf("%d",&key);
                q=LocateNode(T,key);
                p=ParentTree(T,q);
                if(!p) printf("\n�ý��Ϊ���ڵ���߸ý�㲻���ڣ�\n");
                else printf("\n�ý���˫���ǣ�%d,%s\n",p->data.key,p->data.others);
                getchar();
                getchar();
                break;
            case 16:
                if(!T)
                {
                    printf("\n������������!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n������·���ǣ�\n");
                MaxSumPath(T);
                printf("\n�����������·����Ϊ��%d\n",maxroute(T));
                getchar();
                getchar();
                break;
            case 17:
                if(!T)
                {
                    printf("\n�����������ڣ�\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n��������Ҫ������ļ����ƣ�\n");
                scanf("%s",filename);
                SaveBiTree(T,filename);
                printf("\n�ѳɹ����棡\n");
                getchar();
                getchar();
                break;
            case 18:
                printf("\n��������Ҫ��ȡ���ļ����ƣ�\n");
                scanf("%s",filename);
                LoadBiTree(&T,filename);
                printf("\n�ѳɹ���ȡ��\n");
                getchar();
                getchar();
                break;
            case 19:
               if(!T)
                {
                    printf("\n������������!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n��������Ҫ������С�������ȵ��������Ĺؼ��֣�\n");
                scanf("%d %d",&key,&key2);
                BiTree p=LowestCommonAncestor(T,key,key2);
                printf("\n��С���������ǣ�%d,%s\n",p->data.key,p->data.others);
                getchar();
                getchar();
                break;
            case 20:
                if(!T)
                {
                    printf("\n������������!\n");
                    getchar();
                    getchar();
                    break;
                }
                InvertTree(&T,&NEWT);
                T=NEWT;
                printf("\n�ѳɹ���������������\n");
                getchar();
                getchar();
                break;
            case 21:
                printf("\n��������Ӷ�������������\n");
                scanf("%d",&num);
                while(count<num)
                {
                    printf("\n����������������ƣ�\n");
                    scanf("%s",bta.elem[count].name);
                    printf("\n������������Ķ��壺\n");
                    do {
                        scanf("%d%s",&definition[i].key,definition[i].others);
                    } while (definition[i++].key!=-1);
                    i=0;
                    CreateBiTree(&bta.elem[bta.length++].T,definition);
                    count++;
                }
                printf("\n�����ɹ���\n");
                count=0;
                getchar();
                getchar();
                break;
            case 22:
                printf("\n��������Ҫ���ҵĶ����������ƣ�\n");
                scanf("%s",treename);
                for(i=0;i<bta.length;i++)
                    if(!strcmp(treename,bta.elem[i].name)) break;
                if(i>=bta.length) printf("\n�����������ڣ�\n");
                else printf("\n�����ҵĶ������ǵ�%d����\n",i+1);
                getchar();
                getchar();
                break;
            case 23:
                printf("\n��������Ҫɾ���Ķ����������ƣ�\n");
                scanf("%s",treename);
                for(i=0;i<bta.length;i++)
                    if(!strcmp(treename,bta.elem[i].name)) break;
                if(i>=bta.length) printf("\n�����������ڣ�\n");
                else
                {
                    for(j=i;j<bta.length-1;j++)
                        bta.elem[j]=bta.elem[j+1];
                    bta.length--;
                    printf("\nɾ���ɹ���\n");
                }
                getchar();
                getchar();
                break;
            case 24:
                printf("\n������ѡ���Ķ��������ƣ�\n");
                scanf("%s",treename);
                for(i=0;i<bta.length;i++)
                    if(!strcmp(treename,bta.elem[i].name)) break;
                if(i>=bta.length) printf("\n�����������ڣ�\n");
                else
                {
                     T=bta.elem[i].T;
                     printf("\nѡ���ɹ���\n");
                }
                getchar();
                getchar();
                break;
            case 25:
                if(!T)
                {
                    printf("\n������������!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n��������%d����㣡\n",NodeNumber(T));
                getchar();
                getchar();
                break;
            case 26:
                if(!T)
                {
                    printf("\n������������!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("\n��������%d��Ҷ�ӣ�\n",leafnum(T));
                getchar();
                getchar();
                break;
            case 0:
                break;
        }
    }
}



//�ж϶������Ľ���йؼ����Ƿ��ظ�
status Judgedata(TElemType definition[])
{
    int num[200]={0},flag=0,j=0;  //����������� �ռ任ʱ��
    while(definition[j].key!=-1)
    {
        num[definition[j].key]++;
        if(num[definition[j].key]>1&&definition[j].key!=0)
            return ERROR;
        j++;
    }
    return OK;
}



//����������
int i=0; //����һ��ȫ�ֱ���
status CreateBiTree(BiTree *T,TElemType definition[])
{
    //�ս�㸳ֵΪnull
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
        CreateBiTree(&((*T)->lchild),definition);  //�ݹ鴴��
        CreateBiTree(&((*T)->rchild),definition);
    }
    //�������һ���������󣬽�i����Ϊ0
    if((*T)->data.key==definition[0].key) i=0;
    return OK;
}

//ǰ������ĵݹ�ʵ��
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

//��������ĵݹ�ʵ��
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

//�������ʹ��ջʵ��
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

//�������
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

//������� ʹ�ö���
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

//���ٶ����������ͷ����н��Ŀռ�
status DestroyBiTree(BiTree *T)
{
    if(!*T) return ERROR;
    DestroyBiTree(&(*T)->lchild);
    DestroyBiTree(&(*T)->rchild);
    free(*T);
    *T=NULL;
    return OK;
}

//���������ÿն����� ���ռ�δ�ͷ�
status ClearBiTree(BiTree *T)
{
    if(!(*T)) return OK;
    (*T)->data.key=0;
    strcpy((*T)->data.others,"null");
    ClearBiTree(&(*T)->lchild);
    ClearBiTree(&(*T)->rchild);
    return OK;
}

//�ж϶������Ƿ�Ϊ��
status EmptyBiTree(BiTree T)
{
    if(!T) return INFEASIBLE;
    if(!T->data.key) return TRUE;
    else return ERROR;
}

//�ݹ����������
int BiTreeDepth(BiTree T)
{
    if(!T) return 0;
    int depth1=1,depth2=1;
    depth1+=BiTreeDepth(T->lchild);
    depth2+=BiTreeDepth(T->rchild);
    return MAX(depth1,depth2);  //�Ƚ����εݹ�����ȡ���ֵ����
}

//���ҽ��λ��
BiTree LocateNode(BiTree T,KeyType e)
{

    if(!T) return NULL;
    if(T->data.key==e) return T;

    BiTree p=LocateNode(T->lchild,e);
    if(p) return p;  //�����������ҵ��򷵻�p������������������
    p=LocateNode(T->rchild,e);
    if(p) return p;   //�����������ҵ��򷵻أ����򷵻�NULL
    else return NULL;
}

//���ڵ㸳ֵ
status Assign(BiTree T, KeyType e, TElemType value)
{
    BiTree p;
    p=LocateNode(T,e);   //�жϹؼ����Ƿ��ظ�
    if(!p) return ERROR;
    else
    {
        if(value.key!=e&&LocateNode(T,value.key)) return ERROR;
        p->data=value;
        return OK;
    }
}

//����ֵܽ��
BiTree GetSibling(BiTree T,KeyType e)
{
    if(T->lchild==NULL&&T->rchild==NULL) return NULL;
    if(T->lchild!=NULL&&T->lchild->data.key==e) return T->rchild;  //ע����Ҫ�п�
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

//������
status InsertNode(BiTree *T,KeyType e,int LR,TElemType c)
{
    if(LR==-1) //��Ϊ���ڵ����
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
        if(LR==0) //���Ӳ���
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

        if(LR==1)  //�Һ��Ӳ���
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

//����˫��
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

//ɾ�����
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

//��������
int maxroute(BiTree T)
{
    if(!T) return 0;
    else
        return MAX(T->data.key+maxroute(T->lchild),T->data.key+maxroute(T->rchild));
}

//�����·����
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

//��С��������
BiTree LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2)
{
    if(T==NULL||T->data.key==e1||T->data.key==e2) return T;
    BiTree left=LowestCommonAncestor(T->lchild,e1,e2); //����������
    BiTree right=LowestCommonAncestor(T->rchild,e1,e2); //����������
    if(left&&right) return T;
    else if(!left) return right;
    else return left;
}

//��ת������
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
        InvertTree(&(*T)->lchild,&(*NEWT)->rchild); //��ͬ����ݹ���з�ת
        InvertTree(&(*T)->rchild,&(*NEWT)->lchild);
        return OK;
    }
}

//��save���洢����������Ϣ �����������˳��
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
//���浽������
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
//����������
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
//�ݹ���ڵ���
int NodeNumber(BiTree T)
{
    if(!T) return 0;
    else return NodeNumber(T->lchild)+NodeNumber(T->rchild)+1;
}
//��Ҷ����
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
