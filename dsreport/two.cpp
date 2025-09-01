#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
using namespace std;

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct LNode { //单链表（链式结构）结点的定义
  ElemType data;
  struct LNode *next;
} LNode, *LinkList;

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L != NULL)
    return INFEASIBLE;
  L = (LinkList)malloc(sizeof(LNode));
  L->data = 0;
  L->next = NULL;
  return OK;

  /********** End **********/
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else {
    LinkList p = L, q = L->next;
    while (p != NULL) {
      q = p->next;
      free(p);
      p = q;
    }
    L = NULL;
    return OK;
  }

  /********** End **********/
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else {
    LinkList p = L->next;
    LinkList pp = NULL;
    while (p != NULL) {
      pp = p->next;
      free(p);
      p = pp;
    }
    L->next = NULL; //不要忘了
    return OK;
  }
  /********** End **********/
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else {
    if (L->next == NULL)
      return TRUE;
    else
      return FALSE;
  }

  /********** End **********/
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else {
    int length = 0;
    LinkList p = L->next;

    while (p != NULL) {
      p = p->next;
      length++;
    }
    return length;
  }

  /********** End **********/
}

status GetElem(LinkList L, int i, ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /** ******** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else {
    if (i < 1)
      return ERROR;
    else {
      int a = 0;
      LinkList p = L;
      while (a != i) {
        p = p->next;
        if (p == NULL)
          return ERROR;
        ++a;
      }
      e = p->data;
      return OK;
    }
  }

  /********** End **********/
}
status LocateElem(LinkList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else {
    LinkList p = L;
    int locate = 0;
    while (p != NULL) {
      if (p->data == e)
        return locate;
      else {
        p = p->next;
        locate++;
      }
    }
    return ERROR;
  }
  /********** End **********/
}
status PriorElem(LinkList L, ElemType e, ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else {
    LinkList p = L;
    LinkList q = NULL;
    while (p != NULL) {
      if (p->data == e) {
        if (L->next == p)
          return ERROR;
        else {
          pre = q->data;
          return OK;
        }
      } else {
        q = p;
        p = p->next;
      }
    }
    return ERROR;
  }

  /********** End **********/
}
status NextElem(LinkList L, ElemType e, ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{

  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else {
    LinkList p = L->next, q;
    while (p != NULL) {

      q = p->next;
      if (p->data == e) {
        if (q == NULL)
          return ERROR;
        else {
          next = q->data;
          return OK;
        }
      } else {
        p = q;
      }
    }
    return ERROR;
  }

  /********** End **********/
}
status ListInsert(LinkList &L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else if (i < 1)
    return ERROR;
  else {
    //定位
    LinkList p = L;
    //int locate = 1;
    for (int t = 1; t <= i - 1; t++) {
      p = p->next;
      if (p == NULL)
        return ERROR;
    }
    LinkList f = (LinkList)malloc(sizeof(LNode));
    f->data = e;
    f->next = p->next;
    p->next = f;

    return OK;
  }

  /********** End **********/
}
status ListDelete(LinkList &L, int i, ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  if (i < 1)
    return ERROR;
  LinkList p = L, q = NULL;
  for (int t = 1; t <= i; t++) {
    q = p;
    p = p->next;
    if (p == NULL)
      return ERROR;
  }
  q->next = p->next;
  e = p->data;
  free(p);
  return OK;

  /********** End **********/
}
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  LinkList p = L->next;
  while (p) {
    if (p->next == NULL)
      printf("%d", p->data);
    else
      printf("%d ", p->data);
    p = p->next;
  }
  return OK;
  /********** End **********/
}
status SaveList(LinkList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin 1 *********/
  if (L == NULL)
    return INFEASIBLE;
  FILE *fp;
  fp = fopen(FileName, "w");
  LinkList p = L->next;
  while (p) {
    fprintf(fp, "%d", p->data);
    if (p->next != NULL) {
      fprintf(fp, " ");
    }
    p = p->next;
  }
  fclose(fp);
  return OK;

  /********** End 1 **********/
}

status LoadList(LinkList &L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
  // 请在这里补充代码，完成本关任务
  /********** Begin 2 *********/
  if (L)
    return INFEASIBLE;
  L = (LinkList)malloc(sizeof(LNode));
  L->data = 0;
  L->next = NULL;
  LinkList tail = L;
  FILE *fp;
  fp = fopen(FileName, "r");
  ElemType data;
  while (fscanf(fp, "%d", &data) != EOF) {
    LinkList f = (LinkList)malloc(sizeof(LNode));
    f->data = data;
    f->next = NULL;
    tail->next = f;
    tail = f;
  }
  fclose(fp);
  return OK;

  /********** End 2 **********/
}
status reverseList(LinkList &L) {
  if (!L)
    return INFEASIBLE;
  else {
    LinkList p, q;
    p = L->next;
    L->next = NULL;
    while (p) {
      q = p->next;
      p->next = L->next;
      L->next = p;
      p = q;
    }
    return OK;
  }
}

status RemoveNthFromEnd(LinkList &L, int n, ElemType &e) {
  if (L == NULL)
    return INFEASIBLE;
  else if (L->next == NULL)
    return ERROR;

  else {
    int x = ListLength(L) - n + 1;
    ListDelete(L, x, e);
    return OK;
  }
}
status sortList(LinkList L) {

  if (L == NULL)
    return INFEASIBLE;
  else if (L->next == NULL)
    return ERROR;
  else {
    int swap = 1;        // 用于检测是否发生交换
    ElemType t;          // 用于交换节点
    LinkList end = NULL; // 指向已排序部分的末尾

    while (swap) { //若没有发生交换，即swap为0，则退出循环
      swap = 0;    // 在每次外部循环开始时重置交换标志
      LinkList current = L->next; // 从链表头开始遍历

      while (current->next != end) {
        LinkList next = current->next;

        if (current->data > next->data) {
          t = current->data;
          current->data = next->data;
          next->data = t;
          swap = 1; // 标记发生了交换
        } else {
          current = current->next;
        }
      }
      end = current; // 每轮大循环结束时，已排序部分的末尾为当前节点
    }
    return OK;
  }
}

int main() {
  LinkList L[10];
  string name[10];
  int op = 1;
  int k = 0, x = 0;
  ElemType e = 0, pre = 0, next = 0;
  int i = 0, j = 0;
  char filename[80]; //进行读写操作的文件名
  for (int i = 0; i < 10; ++i) {
    L[i] = NULL;
  }

  while (op) {
    system("cls");
    printf("\n\n");
    printf("      Menu for Linear Table On Linked List Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. InitList         12. ListTraverse\n");
    printf("    	  2. DestroyList      13.InitValue\n");
    printf("    	  3. ClearList        14. ReverseList \n");
    printf("    	  4. ListEmpty        15.RemoveNthFromEnd\n");
    printf("    	  5. ListLength       16. SortList\n");
    printf("    	  6. GetElem          17.SaveList\n");
    printf("          7. LocateElem       18. LoadList\n");
    printf("          8. PriorElem        19.ChangeList\n");
    printf("          9. NextElem         20. RemoveList\n");
    printf("          10. ListInsert      21.AllListTraverse\n");
    printf("          11. ListDelete      22.NameList\n");
    printf("          23.LocateList\n");
    printf("    	  0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~21]:");
    scanf("%d", &op);

    switch (op) {
    case 1:
      if (InitList(L[k]) == OK)
        printf("线性表创建成功！\n");
      else
        printf("线性表创建失败！\n");
      getchar();
      getchar();
      break;
    case 2:
      if (DestroyList(L[k]) == OK)
        printf("线性表销毁成功!\n");
      else
        printf("线性表销毁失败!\n");
      getchar();
      getchar();
      break;
    case 3:
      if (ClearList(L[k]) == OK)
        printf("线性表清除成功!\n");
      else
        printf("线性表清除失败!\n");
      getchar();
      getchar();
      break;
    case 4:
      j = ListEmpty(L[k]);
      if (j == TRUE)
        printf("线性表为空!\n");
      else if (j == FALSE)
        printf("线性表不为空!\n");
      else
        printf("线性表不存在!\n");
      getchar();
      getchar();
      break;
    case 5:
      j = ListLength(L[k]);
      if (j == INFEASIBLE)
        printf("线性表不存在!\n");
      else
        printf("线性表的长度为%d\n", j);
      getchar();
      getchar();
      break;
    case 6:
      printf("请输入要获取元素的位置:\n");
      scanf("%d", &i);
      j = GetElem(L[k], i, e);
      if (j == OK)
        printf("该元素为%d,数据已保存在e中\n", e);
      else if (j == ERROR)
        printf("位置不合法!\n");
      else
        printf("线性表不存在!\n");
      getchar();
      getchar();
      break;
    case 7:
      printf("请输入要查找的元素值:\n");
      scanf("%d", &e);
      j = LocateElem(L[k], e);
      printf("目前链表为:\n");
      ListTraverse(L[k]);
      printf("\n");
      if (j == ERROR)
        printf("不存在该元素!\n");
      else if (j == INFEASIBLE)
        printf("线性表不存在!\n");
      else
        printf("该元素的位置序号为%d", j);
      getchar();
      getchar();
      break;
    case 8:
      printf("请输入要查找前驱的元素:\n");
      scanf("%d", &e);
      j = PriorElem(L[k], e, pre);
      printf("目前链表为:\n");
      if (ListTraverse(L[k]) == INFEASIBLE)
        printf("线性表不存在！\n");
      printf("\n");
      if (j == OK)
        printf("该元素的前驱为%d,数据已保存在pre中\n", pre);
      else if (j == ERROR)
        printf("元素不在链表中或不存在前驱!\n");
      else
        printf("线性表不存在!\n");
      getchar();
      getchar();
      break;
    case 9:
      printf("请输入要查找后继的元素:\n");
      scanf("%d", &e);
      j = NextElem(L[k], e, next);
      printf("目前链表为:\n");
      if (ListTraverse(L[k]) == INFEASIBLE)
        printf("线性表不存在！\n");
      printf("\n");

      if (j == OK)
        printf("该元素的后继为%d,数据已保存在next中\n", next);
      else if (j == ERROR)
        printf("元素不在链表中或不存在后继!\n");
      else
        printf("线性表不存在!\n");
      getchar();
      getchar();
      break;
    case 10:
      printf("在L的第i个位置之前插入新的数据元素e,请输入i和e:\n");
      scanf("%d%d", &i, &e);
      j = ListInsert(L[k], i, e);
      if (j == OK)
        printf("插入成功!\n");
      else if (j == ERROR)
        printf("插入位置不正确!\n");
      else
        printf("线性表不存在!\n");
      getchar();
      getchar();
      break;
    case 11:
      printf("请输入要删除的元素位置(第几个元素):\n");
      scanf("%d", &i);
      j = ListDelete(L[k], i, e);
      if (j == OK)
        printf("删除成功，数据%d已保存在e中\n", e);
      else if (j == ERROR)
        printf("删除位置不正确!\n");
      else
        printf("线性表不存在!\n");
      getchar();
      getchar();
      break;
    case 12:
      if (ListTraverse(L[k]) == INFEASIBLE)
        printf("线性表不存在！\n");
      getchar();
      getchar();
      break;
    case 13:
      if (L[k] == NULL)
        printf("线性表不存在!\n");
      else if (L[k]->next != NULL)
        printf("只允许对空线性表进行操作!\n");
      else {
        j = 1;
        printf("请连续输入元素，0代表结束输入:\n");
        scanf("%d", &e);
        while (e != 0) {
          ListInsert(L[k], j++, e);
          scanf("%d", &e);
        }
        printf("输入成功!");
      }
      getchar();
      getchar();
      break;
    case 14:
      if (reverseList(L[k]) == OK) {
        printf("链表翻转成功!\n");
        printf("目前链表顺序为:\n");
        ListTraverse(L[k]);
      } else
        printf("线性表不存在!\n");
      getchar();
      getchar();
      break;
    case 15:
      printf("要删除倒数第几个结点：\n");
      scanf("%d", &i);
      j = RemoveNthFromEnd(L[k], i, e);
      if (j == INFEASIBLE)
        printf("线性表不存在!\n");
      else if (j == ERROR)
        printf("线性表为空!\n");
      else if (i <= 0 || i > ListLength(L[k]))
        printf("输入位置不正确!\n");
      else
        printf("元素%d删除成功", e);
      getchar();
      getchar();
      break;
    case 16:
      j = sortList(L[k]);
      if (j == INFEASIBLE)
        printf("线性表不存在!\n");
      else if (j == ERROR)
        printf("线性表为空!\n");
      else
        printf("线性表排序成功!\n");
      getchar();
      getchar();
      break;
    case 17:
      printf("请输入文件路径:\n");
      scanf("%s", filename);
      if (SaveList(L[k], filename) == OK)
        printf("写入成功!\n");
      else
        printf("写入失败，线性表不存在!\n");
      getchar();
      getchar();
      break;
    case 18:
      printf("请输入文件路径:\n");
      scanf("%s", filename);
      if (LoadList(L[k], filename) == OK)
        printf("读入成功!\n");
      else
        printf("读入失败，线性表已存在!\n");
      getchar();
      getchar();
      break;
    case 19:
      printf("请输入要切换的线性表序号:\n");
      x = k;
      scanf("%d", &k);
      if (k < 1 || k > 10) {
        printf("请输入1-10的数字!\n");
        k = x;
      } else {
        k--;
        printf("切换成功!\n");
      }
      getchar();
      getchar();
      break;
    case 20:
      printf("请输入要删除的线性表序号:\n");
      scanf("%d", &x);
      if (x < 1 || x > 10)
        printf("请输入1-10的数字!\n");
      else {
        if (L[x - 1] == NULL)
          printf("该线性表未初始化,无需删除!\n");
        else {
          L[x - 1] = NULL;
          printf("删除成功!\n");
        }
      }
      getchar();
      getchar();
      break;
    case 21:
      for (int i = 0; i < 10; i++) {
        if (L[i]) {
          printf("第%d个链表: ", i + 1);
          cout << name[i] << " ";
          ListTraverse(L[i]); //打印数据
          printf("\n");
        }
      }
      getchar();
      getchar();
      break;
    case 22:
      cout << "请给当前链表命名" << endl;
      cin >> name[k];
      cout << "命名成功!" << endl;
      getchar();
      getchar();
      break;
    case 23:
      printf("请输入要查找的线性表名:\n");
      std::string s;
      cin >> s;
      int tag = 0, num = 0;
      for (int i = 0; i < 10; ++i) {

        if (L[i])
          num++;

        if (s == name[i]) {
          cout << "该表存在，为第" << num << "个表" << endl;
          tag = 1;
          break;
        }
      }
if(!tag){
    cout << "该表不存在" << endl;
}
      getchar();
      getchar();
      break;
    }
  }
}
