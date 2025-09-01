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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct LNode { //��������ʽ�ṹ�����Ķ���
  ElemType data;
  struct LNode *next;
} LNode, *LinkList;

status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
    L->next = NULL; //��Ҫ����
    return OK;
  }
  /********** End **********/
}

status ListEmpty(LinkList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{

  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
  /********** Begin *********/
  if (L == NULL)
    return INFEASIBLE;
  else if (i < 1)
    return ERROR;
  else {
    //��λ
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
  // �������ﲹ����룬��ɱ�������
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
    int swap = 1;        // ���ڼ���Ƿ�������
    ElemType t;          // ���ڽ����ڵ�
    LinkList end = NULL; // ָ�������򲿷ֵ�ĩβ

    while (swap) { //��û�з�����������swapΪ0�����˳�ѭ��
      swap = 0;    // ��ÿ���ⲿѭ����ʼʱ���ý�����־
      LinkList current = L->next; // ������ͷ��ʼ����

      while (current->next != end) {
        LinkList next = current->next;

        if (current->data > next->data) {
          t = current->data;
          current->data = next->data;
          next->data = t;
          swap = 1; // ��Ƿ����˽���
        } else {
          current = current->next;
        }
      }
      end = current; // ÿ�ִ�ѭ������ʱ�������򲿷ֵ�ĩβΪ��ǰ�ڵ�
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
  char filename[80]; //���ж�д�������ļ���
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
    printf("    ��ѡ����Ĳ���[0~21]:");
    scanf("%d", &op);

    switch (op) {
    case 1:
      if (InitList(L[k]) == OK)
        printf("���Ա����ɹ���\n");
      else
        printf("���Ա���ʧ�ܣ�\n");
      getchar();
      getchar();
      break;
    case 2:
      if (DestroyList(L[k]) == OK)
        printf("���Ա����ٳɹ�!\n");
      else
        printf("���Ա�����ʧ��!\n");
      getchar();
      getchar();
      break;
    case 3:
      if (ClearList(L[k]) == OK)
        printf("���Ա�����ɹ�!\n");
      else
        printf("���Ա����ʧ��!\n");
      getchar();
      getchar();
      break;
    case 4:
      j = ListEmpty(L[k]);
      if (j == TRUE)
        printf("���Ա�Ϊ��!\n");
      else if (j == FALSE)
        printf("���Ա�Ϊ��!\n");
      else
        printf("���Ա�����!\n");
      getchar();
      getchar();
      break;
    case 5:
      j = ListLength(L[k]);
      if (j == INFEASIBLE)
        printf("���Ա�����!\n");
      else
        printf("���Ա�ĳ���Ϊ%d\n", j);
      getchar();
      getchar();
      break;
    case 6:
      printf("������Ҫ��ȡԪ�ص�λ��:\n");
      scanf("%d", &i);
      j = GetElem(L[k], i, e);
      if (j == OK)
        printf("��Ԫ��Ϊ%d,�����ѱ�����e��\n", e);
      else if (j == ERROR)
        printf("λ�ò��Ϸ�!\n");
      else
        printf("���Ա�����!\n");
      getchar();
      getchar();
      break;
    case 7:
      printf("������Ҫ���ҵ�Ԫ��ֵ:\n");
      scanf("%d", &e);
      j = LocateElem(L[k], e);
      printf("Ŀǰ����Ϊ:\n");
      ListTraverse(L[k]);
      printf("\n");
      if (j == ERROR)
        printf("�����ڸ�Ԫ��!\n");
      else if (j == INFEASIBLE)
        printf("���Ա�����!\n");
      else
        printf("��Ԫ�ص�λ�����Ϊ%d", j);
      getchar();
      getchar();
      break;
    case 8:
      printf("������Ҫ����ǰ����Ԫ��:\n");
      scanf("%d", &e);
      j = PriorElem(L[k], e, pre);
      printf("Ŀǰ����Ϊ:\n");
      if (ListTraverse(L[k]) == INFEASIBLE)
        printf("���Ա����ڣ�\n");
      printf("\n");
      if (j == OK)
        printf("��Ԫ�ص�ǰ��Ϊ%d,�����ѱ�����pre��\n", pre);
      else if (j == ERROR)
        printf("Ԫ�ز��������л򲻴���ǰ��!\n");
      else
        printf("���Ա�����!\n");
      getchar();
      getchar();
      break;
    case 9:
      printf("������Ҫ���Һ�̵�Ԫ��:\n");
      scanf("%d", &e);
      j = NextElem(L[k], e, next);
      printf("Ŀǰ����Ϊ:\n");
      if (ListTraverse(L[k]) == INFEASIBLE)
        printf("���Ա����ڣ�\n");
      printf("\n");

      if (j == OK)
        printf("��Ԫ�صĺ��Ϊ%d,�����ѱ�����next��\n", next);
      else if (j == ERROR)
        printf("Ԫ�ز��������л򲻴��ں��!\n");
      else
        printf("���Ա�����!\n");
      getchar();
      getchar();
      break;
    case 10:
      printf("��L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e,������i��e:\n");
      scanf("%d%d", &i, &e);
      j = ListInsert(L[k], i, e);
      if (j == OK)
        printf("����ɹ�!\n");
      else if (j == ERROR)
        printf("����λ�ò���ȷ!\n");
      else
        printf("���Ա�����!\n");
      getchar();
      getchar();
      break;
    case 11:
      printf("������Ҫɾ����Ԫ��λ��(�ڼ���Ԫ��):\n");
      scanf("%d", &i);
      j = ListDelete(L[k], i, e);
      if (j == OK)
        printf("ɾ���ɹ�������%d�ѱ�����e��\n", e);
      else if (j == ERROR)
        printf("ɾ��λ�ò���ȷ!\n");
      else
        printf("���Ա�����!\n");
      getchar();
      getchar();
      break;
    case 12:
      if (ListTraverse(L[k]) == INFEASIBLE)
        printf("���Ա����ڣ�\n");
      getchar();
      getchar();
      break;
    case 13:
      if (L[k] == NULL)
        printf("���Ա�����!\n");
      else if (L[k]->next != NULL)
        printf("ֻ����Կ����Ա���в���!\n");
      else {
        j = 1;
        printf("����������Ԫ�أ�0�����������:\n");
        scanf("%d", &e);
        while (e != 0) {
          ListInsert(L[k], j++, e);
          scanf("%d", &e);
        }
        printf("����ɹ�!");
      }
      getchar();
      getchar();
      break;
    case 14:
      if (reverseList(L[k]) == OK) {
        printf("����ת�ɹ�!\n");
        printf("Ŀǰ����˳��Ϊ:\n");
        ListTraverse(L[k]);
      } else
        printf("���Ա�����!\n");
      getchar();
      getchar();
      break;
    case 15:
      printf("Ҫɾ�������ڼ�����㣺\n");
      scanf("%d", &i);
      j = RemoveNthFromEnd(L[k], i, e);
      if (j == INFEASIBLE)
        printf("���Ա�����!\n");
      else if (j == ERROR)
        printf("���Ա�Ϊ��!\n");
      else if (i <= 0 || i > ListLength(L[k]))
        printf("����λ�ò���ȷ!\n");
      else
        printf("Ԫ��%dɾ���ɹ�", e);
      getchar();
      getchar();
      break;
    case 16:
      j = sortList(L[k]);
      if (j == INFEASIBLE)
        printf("���Ա�����!\n");
      else if (j == ERROR)
        printf("���Ա�Ϊ��!\n");
      else
        printf("���Ա�����ɹ�!\n");
      getchar();
      getchar();
      break;
    case 17:
      printf("�������ļ�·��:\n");
      scanf("%s", filename);
      if (SaveList(L[k], filename) == OK)
        printf("д��ɹ�!\n");
      else
        printf("д��ʧ�ܣ����Ա�����!\n");
      getchar();
      getchar();
      break;
    case 18:
      printf("�������ļ�·��:\n");
      scanf("%s", filename);
      if (LoadList(L[k], filename) == OK)
        printf("����ɹ�!\n");
      else
        printf("����ʧ�ܣ����Ա��Ѵ���!\n");
      getchar();
      getchar();
      break;
    case 19:
      printf("������Ҫ�л������Ա����:\n");
      x = k;
      scanf("%d", &k);
      if (k < 1 || k > 10) {
        printf("������1-10������!\n");
        k = x;
      } else {
        k--;
        printf("�л��ɹ�!\n");
      }
      getchar();
      getchar();
      break;
    case 20:
      printf("������Ҫɾ�������Ա����:\n");
      scanf("%d", &x);
      if (x < 1 || x > 10)
        printf("������1-10������!\n");
      else {
        if (L[x - 1] == NULL)
          printf("�����Ա�δ��ʼ��,����ɾ��!\n");
        else {
          L[x - 1] = NULL;
          printf("ɾ���ɹ�!\n");
        }
      }
      getchar();
      getchar();
      break;
    case 21:
      for (int i = 0; i < 10; i++) {
        if (L[i]) {
          printf("��%d������: ", i + 1);
          cout << name[i] << " ";
          ListTraverse(L[i]); //��ӡ����
          printf("\n");
        }
      }
      getchar();
      getchar();
      break;
    case 22:
      cout << "�����ǰ��������" << endl;
      cin >> name[k];
      cout << "�����ɹ�!" << endl;
      getchar();
      getchar();
      break;
    case 23:
      printf("������Ҫ���ҵ����Ա���:\n");
      std::string s;
      cin >> s;
      int tag = 0, num = 0;
      for (int i = 0; i < 10; ++i) {

        if (L[i])
          num++;

        if (s == name[i]) {
          cout << "�ñ���ڣ�Ϊ��" << num << "����" << endl;
          tag = 1;
          break;
        }
      }
if(!tag){
    cout << "�ñ�����" << endl;
}
      getchar();
      getchar();
      break;
    }
  }
}
