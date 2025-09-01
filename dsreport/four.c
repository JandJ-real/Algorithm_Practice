#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//常量 宏定义
#define TRUE 1
#define FALSE -1
#define OK 1
#define ERROR -1
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAXLEN 20
#define INFINE 9999


typedef int status;
typedef int KeyType;

//定义图的类型 例如：无向图
typedef enum {DG,DN,UDG,UDN} GraphKind;

typedef struct {
    KeyType  key;
    char others[20];
}VertexType; //顶点类型定义


typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号
    struct ArcNode  *nextarc;	   //下一个表结点指针
}ArcNode;

typedef struct VNode{				//头结点及其数组类型定义
    VertexType data;       	//顶点信息
    ArcNode *firstarc;      	 //指向第一条弧
}VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
}ALGraph;

typedef struct{
    struct{
        char name[20];
        ALGraph G;
    }elem[10];
    int length;
}BTG;

//函数原型
status CreateGraph(ALGraph *G,VertexType V[],KeyType VR[][2]);
int LocateVex(ALGraph G,KeyType u);
status DestroyGraph(ALGraph *G);
status PutVex(ALGraph *G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph *G,VertexType v);
status DeleteVex(ALGraph *G,KeyType v);
status InsertArc(ALGraph *G,KeyType v,KeyType w);
status DeleteArc(ALGraph *G,KeyType v,KeyType w);
status DFSTraverse(ALGraph G);
status BFSTraverse(ALGraph G);
int VerticesSetLessThanK(ALGraph G, KeyType v, int k);
int ConnectedComponentsNums(ALGraph G);
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph *G1, char FileName[]);
int ShortestPathLength(ALGraph G,int v,int w);

int main()
{
    ALGraph G;
    ALGraph *p;
    p=&G;
    BTG GS;
    GS.length=0;
    G.vexnum=0;
    G.arcnum=0;
    VertexType V[30];
    KeyType VR[100][2];
    int i=0,j;
    printf("\n请输入顶点序列：\n");
    do {
        scanf("%d%s",&V[i].key,V[i].others);
    } while(V[i++].key!=-1);
    i=0;
    printf("\n请输入关系对序列\n");
    do {
        scanf("%d%d",&VR[i][0],&VR[i][1]);
    } while(VR[i++][0]!=-1);
    int op=1,state=0,key=0,pos=0,result,key2=0,distance=0,num=0,count=0;
    char filename[20],graphname[20];
    VertexType value;
    while(op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Singly-Linked List Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1.CreateGraph    2.DestroyGraph\n");
        printf("    	  3.LocateVex      4.PutVex\n");
        printf("    	  5.FirstAdjVex    6.NextAdjVex\n");
        printf("    	  7.InsertVex      8.DeleteVex\n");
        printf("    	  9.InsertArc      10.DeleteArc\n");
        printf("    	  11.DFSTraverse   12.BFSTraverse\n");
        printf("    	  13.VerticesSetLessThanK   14.ShortestPathLength\n");
        printf("    	  15.ConnectedComponentsNums      16.SaveGraph\n");
        printf("    	  17.LoadGraph     18.AddGraph\n");
        printf("    	  19.LocateGraph   20.RemoveGraph\n");
        printf("    	  21.SelectGraph\n");
        printf("          0.exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~22]:");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                state=CreateGraph(&G,V,VR);
                if(state==ERROR) printf("\n邻接表创建失败！\n");
                else printf("\n邻接表创建成功！\n");
                getchar();
                getchar();
                break;
            case 2:
                state=DestroyGraph(&G);
                if(state==ERROR) printf("\n图不存在！\n");
                else printf("\n图已销毁！\n");
                getchar();
                getchar();
                break;
            case 3:
                printf("\n请输入需要查找顶点的关键字：\n");
                scanf("%d",&key);
                pos=LocateVex(G,key);
                if(pos==-1) printf("\n该结点不存在!\n");
                else if(pos==-2) printf("\n图不存在！\n");
                else printf("\n该结点是:%d,%s\n",G.vertices[pos].data.key,G.vertices[pos].data.others);
                getchar();
                getchar();
                break;
            case 4:
                printf("\n请输入需要更改顶点的关键字：\n");
                scanf("%d",&key);
                printf("\n请输入更改后的顶点的关键字和值：\n");
                scanf("%d%s",&value.key,value.others);
                state=PutVex(&G,key,value);
                if(state==ERROR) printf("\n赋值失败！\n");
                else printf("\n赋值成功！\n");
                getchar();
                getchar();
                break;
            case 5:
                printf("\n请输入需要查找顶点的关键字：\n");
                scanf("%d",&key);
                pos=FirstAdjVex(G,key);
                if(pos<0) printf("\n该顶点不存在或者不存在邻接点！\n");
                else printf("\n该顶点第一个邻接点是：%d,%s\n",G.vertices[pos].data.key,G.vertices[pos].data.others);
                getchar();
                getchar();
                break;
            case 6:
                printf("\n请输入查找的顶点：\n");
                scanf("%d",&key);
                printf("\n请输入相应邻接点：\n");
                scanf("%d",&key2);
                pos=NextAdjVex(G,key,key2);
                if(pos<0) printf("\n查找失败！\n");
                else printf("\n下一个邻接点是：%d%,%s\n",G.vertices[pos].data.key,G.vertices[pos].data.others);
                getchar();
                getchar();
                break;
            case 7:
                printf("\n请输入新顶点的关键字和值：\n");
                scanf("%d%s",&value.key,value.others);
                state=InsertVex(&G,value);
                if(state==ERROR) printf("\n插入失败！\n");
                else printf("\n插入成功！\n");
                getchar();
                getchar();
                break;
            case 8:
                printf("\n请输入删除顶点的关键字：\n");
                scanf("%d",&key);
                state=DeleteVex(&G,key);
                if(state==ERROR) printf("\n删除失败！\n");
                else printf("\n删除成功！\n");
                getchar();
                getchar();
                break;
            case 9:
                printf("\n请输入插入弧的弧尾弧头关键字：\n");
                scanf("%d%d",&key,&key2);
                state=InsertArc(&G,key,key2);
                if(state==ERROR) printf("\n插入失败！\n");
                else printf("\n插入成功！\n");
                getchar();
                getchar();
                break;
            case 10:
                printf("\n请输入删除弧的弧尾弧头关键字：\n");
                scanf("%d%d",&key,&key2);
                state=DeleteArc(&G,key,key2);
                if(state==ERROR) printf("\n删除失败！\n");
                else printf("\n删除成功！\n");
                getchar();
                getchar();
                break;
            case 11:
                DFSTraverse(G);
                getchar();
                getchar();
                break;
            case 12:
                BFSTraverse(G);
                getchar();
                getchar();
                break;
            case 13:
                printf("\n请输入中心顶点的关键字：\n");
                scanf("%d",&key);
                printf("\n请输入距离k：\n");
                scanf("%d",&distance);
                printf("\n与顶点距离小于k的顶点有：\n");
                VerticesSetLessThanK(G,key,distance);
                getchar();
                getchar();
                break;
            case 14:
                printf("\n请输入两个顶点的关键字：\n");
                scanf("%d%d",&key,&key2);
                result=ShortestPathLength(G,key,key2);
                printf("\n最短路径长为:%d\n",result);
                getchar();
                getchar();
                break;
            case 15:
                printf("\n该图的连通分量有%d个\n",ConnectedComponentsNums(G));
                getchar();
                getchar();
                break;
            case 16:
                printf("\n请输入需要保存的文件名称：\n");
                scanf("%s",filename);
                SaveGraph(G,filename);
                printf("\n已成功保存！\n");
                getchar();
                getchar();
                break;
            case 17:
                printf("\n请输入需要导入的文件名称：\n");
                scanf("%s",filename);
                LoadGraph(&G,filename);
                printf("\n已成功导入！\n");
                printf("%d",G.vexnum);
                getchar();
                getchar();
                break;
            case 18:
                printf("\n请输入添加邻接表的数量：\n");
                scanf("%d",&num);
                while(count<num)
                {
                    printf("\n请输入邻接表的名称：\n");
                    scanf("%s",GS.elem[GS.length+count].name);
                    printf("\n请输入顶点序列：\n");
                    i=0;
                    do {
                         scanf("%d%s",&V[i].key,V[i].others);
                    } while(V[i++].key!=-1);
                    i=0;
                    printf("\n请输入关系对序列\n");
                    do {
                        scanf("%d%d",&VR[i][0],&VR[i][1]);
                    } while(VR[i++][0]!=-1);

                    GS.elem[GS.length].G.vexnum=0;
                    CreateGraph(&(GS.elem[GS.length].G),V,VR);
                    GS.length++;
                    count++;
                }
                printf("\n创建成功！\n");
                count=0;
                getchar();
                getchar();
                break;
            case 19:
                printf("\n请输入需要查找的邻接表的名称：\n");
                scanf("%s",graphname);
                for(i=0;i<GS.length;i++)
                    if(!strcmp(graphname,GS.elem[i].name)) break;
                if(i>=GS.length) printf("\n邻接表不存在！\n");
                else printf("\n所查找的邻接表是第%d个！\n",i+1);
                getchar();
                getchar();
                break;
            case 20:
                printf("\n请输入需要删除的邻接表的名称：\n");
                scanf("%s",graphname);
                for(i=0;i<GS.length;i++)
                    if(!strcmp(graphname,GS.elem[i].name)) break;
                if(i>=GS.length) printf("\n邻接表不存在！\n");
                else
                {
                    for(j=i;j<GS.length-1;j++)
                        GS.elem[j]=GS.elem[j+1];
                    GS.length--;
                    printf("\n删除成功！\n");
                }
                getchar();
                getchar();
                break;
            case 21:
                printf("\n请输入选定的邻接表名称：\n");
                scanf("%s",graphname);
                for(i=0;i<GS.length;i++)
                    if(!strcmp(graphname,GS.elem[i].name)) break;
                if(i>=GS.length) printf("\n邻接表不存在！\n");
                else
                {
                     G=GS.elem[i].G;
                     printf("\n选定成功！\n");
                }
                getchar();
                getchar();
                break;
            case 0:
                break;
        }
    }
}



int Locate(VertexType V[],KeyType num)
{
    int i=0;
    while(num!=V[i].key&&V[i].key!=-1) i++;
    if(V[i].key==-1) return -1;
    else return i;
}

void initnum(int num[])
{
    int i;
    for(i=0;i<50;i++) num[i]=0;

}
int num[50]={0};
status CreateGraph(ALGraph *G,VertexType V[],KeyType VR[][2])
{
    if((*G).vexnum) return ERROR;
    //初始化标记数组
    initnum(num);
    int i=0,m,n,j;
    ArcNode *p,*q;
    (*G).kind=UDG;
    while(V[i].key!=-1)
    {
        num[V[i].key]++;  //判误
        if(num[V[i].key]>1) return ERROR;
        (*G).vertices[i].data=V[i];
        (*G).vertices[i].firstarc=NULL;
        i++;
    }
    (*G).vexnum=i;
    if(!(*G).vexnum||(*G).vexnum>MAX_VERTEX_NUM) return ERROR;

    i=0;
    while(VR[i][0]>0)
    {
        m=Locate(V,VR[i][0]);
        n=Locate(V,VR[i][1]);
        if(m<0||n<0) return ERROR;
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=n;
        p->nextarc=(*G).vertices[m].firstarc;
        (*G).vertices[m].firstarc=p;

        q=(ArcNode*)malloc(sizeof(ArcNode));
        q->adjvex=m;
        q->nextarc=(*G).vertices[n].firstarc;
        (*G).vertices[n].firstarc=q;

        i++;
    }
    (*G).arcnum=i;

    return OK;
}

int LocateVex(ALGraph G,KeyType u)
{
    int i;
    if(G.vexnum==0) return -2;
    for(i=0;i<G.vexnum;i++)
        if(G.vertices[i].data.key==u) break;

    if(i>=G.vexnum) return -1;
    else return i;
}

status DestroyGraph(ALGraph *G)
{
    if((*G).vexnum==0) return ERROR;
    int i;
    for(i=0;i<(*G).vexnum;i++)
    {
        ArcNode *p=(*G).vertices[i].firstarc;
        if(!p) continue;
        ArcNode *q=p->nextarc;
        while(q)
        {
            free(p);
            p=q;
            q=q->nextarc;
        }
        free(p);
        (*G).vertices[i].firstarc=NULL;
    }
    (*G).vexnum=0;
    (*G).arcnum=0;
    return OK;
}

status PutVex(ALGraph *G,KeyType u,VertexType value)
{
    int i,j;
    i=LocateVex(*G,u);
    if(i==-1) return ERROR;
    j=LocateVex(*G,value.key);
    if(j>0&&j!=i) return ERROR;
    G->vertices[i].data=value;
    return OK;
}

int FirstAdjVex(ALGraph G,KeyType u)
{
    int i=0;
    i=LocateVex(G,u);
    if(i<0) return ERROR;
    if(!G.vertices[i].firstarc) return ERROR;
    int j=G.vertices[i].firstarc->adjvex;
    return j;
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
{
    int i,j;
    i=LocateVex(G,v);
    j=LocateVex(G,w);
    if(i<0||j<0) return ERROR;
    ArcNode *p=G.vertices[i].firstarc;
    while (p->adjvex!=j&&p->nextarc)
    {
         p=p->nextarc;
    }
    if(p->nextarc==NULL) return ERROR;
    else return p->nextarc->adjvex;

    return ERROR;
}

status InsertVex(ALGraph *G,VertexType v)
{
    if((*G).vexnum==MAX_VERTEX_NUM) return ERROR;
    int i;
    i=LocateVex(*G,v.key);
    if(i>0) return ERROR;
    (*G).vertices[(*G).vexnum].data=v;
    (*G).vertices[(*G).vexnum].firstarc=NULL;
    (*G).vexnum++;
    return OK;
}

//删除结点
status DeleteVex(ALGraph *G, KeyType v)
{
    if(G->vexnum==1) return ERROR;

    int i,m;
    m=LocateVex(*G,v);
    if(m<0) return ERROR;

    ArcNode *p,*p0,*p1;
    p=G->vertices[m].firstarc;
    while(p)
    {
        p0=p->nextarc;
        free(p);
        G->arcnum--;
        p=p0;
    }
    G->vertices[m].firstarc=NULL;

    for(i=0;i<G->vexnum;i++)
    {
        p=G->vertices[i].firstarc;
        if(!p) continue;

        p0=p->nextarc;
        if(p->adjvex==m)
        {
            free(p);
            G->vertices[i].firstarc=p0;
            continue;
        }

        while(p0)
        {
            if(p0->adjvex==m)
            {
                p->nextarc=p0->nextarc;
                free(p0);
                break;
            }
            else
            {
                p=p->nextarc;
                p0=p0->nextarc;
            }
        }
    }
    G->vexnum--;
    for(i=0;i<G->vexnum;i++)
    {
        if(i>=m)
        {
            G->vertices[i]=G->vertices[i+1];
        }

        p=G->vertices[i].firstarc;
        while(p)
        {
            if(p->adjvex>m) p->adjvex--;
            p=p->nextarc;
        }
    }
    printf("%d",G->arcnum);
       return OK;
}

status InsertArc(ALGraph *G,KeyType v,KeyType w)
{
    int i,j;
    i=LocateVex(*G,v);
    j=LocateVex(*G,w);
    if(i<0||j<0) return ERROR;

    ArcNode *p,*q;
    p=G->vertices[i].firstarc;
    while(p)
    {
        if(p->adjvex==j) return ERROR;
        p=p->nextarc;
    }

    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=j;
    p->nextarc=G->vertices[i].firstarc;
    G->vertices[i].firstarc=p;

    q=(ArcNode*)malloc(sizeof(ArcNode));
    q->adjvex=i;
    q->nextarc=G->vertices[j].firstarc;
    G->vertices[j].firstarc=q;


    G->arcnum++;
    return OK;
}

status DeleteArc(ALGraph *G,KeyType v,KeyType w)
{
    int i,j;
    i=LocateVex(*G,v);
    j=LocateVex(*G,w);
    if(i==-1||j==-1) return ERROR;

    ArcNode *p,*q;
    p=G->vertices[i].firstarc;
    if(!p) return ERROR;

    q=p->nextarc;
    if(p->adjvex==j)
    {
        free(p);
        G->vertices[i].firstarc=q;
    }
    else
    {
        q=p->nextarc;
        while(q)
        {
            if(q->adjvex==j)
            {
                p->nextarc=q->nextarc;
                free(q);
                break;
            }
            p=p->nextarc;
            q=q->nextarc;
        }
        if(!q) return ERROR;
    }

    p=G->vertices[j].firstarc;
    if(!p) return ERROR;
    q=p->nextarc;
    if(p->adjvex==i)
    {
        free(p);
        G->vertices[j].firstarc=q;
    }
    else
    {
        q=p->nextarc;
        while(q)
        {
            if(q->adjvex==i)
            {
                p->nextarc=q->nextarc;
                free(q);
                break;
            }
            p=p->nextarc;
            q=q->nextarc;
        }
        if(!q) return ERROR;
    }
    return OK;
}

int visited[20]={0};
void initvisited(int visited[])
{
    int i;
    for(i=0;i<20;i++) visited[i]=0;
}
status DFS(ALGraph G,ArcNode*p)
{
    if(p==NULL) return ERROR;
    if(!visited[p->adjvex])
    {
        printf("%d,%s ",G.vertices[p->adjvex].data.key,G.vertices[p->adjvex].data.others);
        visited[p->adjvex]=1;
        DFS(G,G.vertices[p->adjvex].firstarc);
    }
    DFS(G,p->nextarc);
    return OK;
}

status DFSTraverse(ALGraph G)
{
    int i;
    initvisited(visited);
    for(i=0;i<G.vexnum;i++)
    {
        if(visited[i]==0)
        {
            printf("%d,%s ",G.vertices[i].data.key,G.vertices[i].data.others);
            visited[i]=1;
        }
        DFS(G,G.vertices[i].firstarc);
    }
    return OK;
}

//构造队列
typedef struct{
    int data[20];
    int front;
    int rear;
}Queue;

//队列初始化
status InitQueue(Queue *Q)
{
    Q->front=0;
    Q->rear=0;
    return OK;
}

//队列判空
status QueueEmpty(Queue Q)
{
    if(Q.front==Q.rear)
        return TRUE;
    else
    return FALSE;
}

//入队
status EnQueue(Queue *Q,int e)
{
    if((Q->rear+1)%20==Q->front)
    return ERROR;
    Q->data[Q->rear]=e;
    Q->rear=(Q->rear+1)%20;
    return OK;
}

//出队
status DeQueue(Queue *Q,int *e)
{
    if(Q->front==Q->rear)
        return ERROR;
    *e=Q->data[Q->front];
    Q->front=(Q->front+1)%20;
    return OK;
}

Queue Q;

status BFSTraverse(ALGraph G)
{
    initvisited(visited);
    InitQueue(&Q);
    int v,u;
    ArcNode *p;
    for(v=0;v<G.vexnum;v++)
    {
        if(!visited[v])
        {
            printf("%d,%s ",G.vertices[v].data.key,G.vertices[v].data.others);
            visited[v]=1;
            EnQueue(&Q,v);
            while(QueueEmpty(Q)<0)
            {
                DeQueue(&Q,&u);
                p=G.vertices[u].firstarc;
                while(p)
                {
                    if(!visited[p->adjvex])
                    {
                       visited[p->adjvex]=1;
                       printf("%d,%s ",G.vertices[p->adjvex].data.key,G.vertices[p->adjvex].data.others);
                       EnQueue(&Q,p->adjvex);
                    }
                    p=p->nextarc;
                }
            }
        }
    }
}

void find(ALGraph G, int q, int a[],int count,int k)
{
    if(count>=k) return;
    a[q]=1;
    count++;
    ArcNode *p=G.vertices[q].firstarc;
    int countnow;
    while(p)
    {
        if(count<k)
        {
            countnow=count;
            find(G,p->adjvex,a,countnow,k);
        }
        p=p->nextarc;
    }
}

int VerticesSetLessThanK(ALGraph G, KeyType v, int k)
{
    int q=LocateVex(G,v);
    if(q==-1) return ERROR;

    int sign[20]={0},i;
    for(i=0;i<20;i++) sign[i]=0;
    find(G,q,sign,0,k);
    for(i=0;i<G.vexnum;i++)
    {
        if(sign[i])
            printf("%d %s\n", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    return OK;
}


status DFS2(ALGraph G,ArcNode*p)
{
    if(p==NULL) return ERROR;
    if(!visited[p->adjvex])
    {
        visited[p->adjvex]=1;
        DFS2(G,G.vertices[p->adjvex].firstarc);
    }
    DFS2(G,p->nextarc);
    return OK;
}
int ConnectedComponentsNums(ALGraph G)
{
    int i,count=0;
    for(i=0;i<20;i++) visited[i]=0;
    for(i=0;i<G.vexnum;i++)
    {
        if(visited[i]==0)
        {
            visited[i]=1;
            count++;
        }
        DFS2(G,G.vertices[i].firstarc);
    }
    return count;
}

status SaveGraph(ALGraph G, char FileName[])
{
    FILE *fp;
    fp=fopen(FileName,"w");
    ArcNode *p;
    int i,count=0,arcnum[20]={0};
    fprintf(fp,"%d %d\n",G.vexnum,G.arcnum);
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertices[i].firstarc;
        if(p) fprintf(fp,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
        else
        {
            fprintf(fp,"%d %s\n",G.vertices[i].data.key,G.vertices[i].data.others);
            arcnum[i]=0;
            continue;
        }
        while(p&&p->nextarc)
        {
            count++;
            fprintf(fp,"%d ",p->adjvex);
            p=p->nextarc;
        }
        fprintf(fp,"%d\n",p->adjvex);
        count++;
        arcnum[i]=count;
        count=0;
    }
    fclose(fp);
    return OK;
}
status LoadGraph(ALGraph *G1, char FileName[])
{
    FILE* fp = fopen(FileName, "r");
    int count,count1,i,data,flag=1;
    char c;
    ArcNode *a,*p;
    fscanf(fp, "%d %d\n", &count, &count1);
    G1->vexnum=count;
    G1->arcnum = count1;
    for (i = 0; i < count; i++)
    {
        //printf("99");
        int flag = 1;
        fscanf(fp, "%d",&G1->vertices[i].data.key);
        fscanf(fp, "%s", G1->vertices[i].data.others);
        //printf("00");
        //printf("%d",G1->vertices[i].data.key);
        while(fscanf(fp,"%d",&data)>0)
        {
            a=(ArcNode*)malloc(sizeof(ArcNode));
            a->adjvex=data;
            a->nextarc=NULL;
            if(flag)
            {
                G1->vertices[i].firstarc=a;
                p=a;
                flag=0;
            }
            else
            {
                p->nextarc=a;
                p=a;
            }
            if(fgetc(fp)=='\n') break;
        }
    }
    fclose(fp);
    return OK;
}

int ShortestPathLength(ALGraph G,int v,int w)
{
    int dist[20]={0};
    int key1=LocateVex(G,v);
    int key2=LocateVex(G,w);
    Dijkstra(G,key1,dist);
    return dist[key2];
}

int get_weight(ALGraph G,int start,int end)
{
    ArcNode *p;
    if(start==end) return 0;
    p=G.vertices[start].firstarc;
    while(p)
    {
        if(end==p->adjvex) return 1;
        p=p->nextarc;
    }
    return INFINE;
}


void Dijkstra(ALGraph G, int vs, int dist[])
{
 	int i, j, k, t,m;
	int min;
	int tmp;
	int flag[20];      // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。


    for(i=1;i<=G.vexnum;i++)
    {
        flag[i]=0;
        dist[i]=get_weight(G,vs,i);
    }
    flag[vs]=1;
    dist[vs]=0;

    for(i=1;i<G.vexnum;i++)
    {
        min=INFINE;
        for(j=1;j<=G.vexnum;j++)
        {
            if(flag[j]==0&&dist[j]<min)
            {
                min=dist[j];
                k=j;
            }
        }
        flag[k]=1;
        for(j=1;j<=G.vexnum;j++)
        {
            tmp=get_weight(G,k,j);
            tmp=(tmp==INFINE?INFINE:(min+tmp));
            if(flag[j]==0&&(tmp<dist[j]))
            {
                dist[j]=tmp;
            }
        }
    }
}
