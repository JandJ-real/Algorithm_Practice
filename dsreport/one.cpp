#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;
#define TRUE 1 //�йس�������
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct { //˳���˳��ṹ���Ķ���
  ElemType *elem;
  int length;
  int listsize;
} SqList;
typedef struct { //���Ա�ļ������Ͷ���
  struct {
    char name[30];
    SqList L;
  } elem[10];
  int length;
} LISTS;
LISTS Lists; //���Ա��ϵĶ���Lists

status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType &e);
int LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType e, ElemType &pre);
status NextElem(SqList L, ElemType e, ElemType &next);
status ListInsert(SqList &L, int i, ElemType e);
status ListTraverse(SqList L);
status ListDelete(SqList &L, int i, ElemType &e);
status SaveList(SqList L, char FileName[]);
status LoadList(SqList &L, char FileName[]);
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
ElemType MaxSubArray(SqList L);
int SubArrayNum(SqList L, int k);
status SortList(SqList);

ElemType max(ElemType a, ElemType b) { return a > b ? a : b; }

/***************************************************************
 *�������ƣ�InitList
 *�������ܣ��������Ա�
 *ע�ͣ� ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBL
 *����ֵ���ͣ�status����
 ****************************************************************/

status InitList(SqList &L) {
  if (!L.elem) //������Ա�Ϊ��
  {
    L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE); //�ڴ����
    L.length = 0;                //���ȳ�ʼ��Ϊ0
    L.listsize = LIST_INIT_SIZE; //��ʼ���ռ��С
    return OK;
  } else {
    return INFEASIBLE;
  }
}

/***************************************************************
 *�������ƣ�DestroyList
 *�������ܣ��������Ա�
 *ע�ͣ�������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
 *����ֵ���ͣ�status����
 ****************************************************************/

status DestroyList(SqList &L) {
  if (L.elem) //������Ա����
  {
    free(L.elem); //�ͷſռ�
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
  } else
    return INFEASIBLE;
}

/***************************************************************
 *�������ƣ�ClearList
 *�������ܣ�������Ա�
 *ע�ͣ�������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
 *����ֵ���ͣ�status����
 ****************************************************************/

status ClearList(SqList &L) {
  if (L.elem) //������Ա����
  {
    L.length = 0; //������Ϊ0���ȼ���ɾ������Ԫ��
    return OK;
  } else
    return INFEASIBLE;
}

/***************************************************************
 *�������ƣ�ListEmpty
 *�������ܣ�������Ա�
 *ע�ͣ�������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE
 *����ֵ���ͣ�status����
 ****************************************************************/

status ListEmpty(SqList L) {
  if (!L.elem) //������Ա�����
  {
    return INFEASIBLE;
  } else {
    if (L.length == 0)
      return TRUE;
    else
      return FALSE;
  }
}

/***************************************************************
 *�������ƣ�ListLength
 *�������ܣ����Ա���
 *ע�ͣ�������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE
 *����ֵ���ͣ�status����
 ****************************************************************/

status ListLength(SqList L) {
  /********** Begin *********/
  if (!L.elem)
    return INFEASIBLE;
  else
    return L.length;

  /********** End **********/
}

/***************************************************************
*�������ƣ�GetElem
*�������ܣ���ȡԪ��
*ע�ͣ�������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK��
���i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
*����ֵ���ͣ�status����
****************************************************************/

status GetElem(SqList L, int i, ElemType &e) {
  if (!L.elem)
    return INFEASIBLE;
  else {
    if (i < 1 || i > L.length)
      return ERROR;
    else {
      e = L.elem[i - 1];
      return OK;
    }
  }
}

/***************************************************************
*�������ƣ�LocateElem
*�������ܣ�����Ԫ��
*ע�ͣ� ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ�
���e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
*����ֵ���ͣ�int����
****************************************************************/

int LocateElem(SqList L, ElemType e) {
  if (!L.elem)
    return INFEASIBLE;
  else {
    int flag = -1; //��ʾ��δ�ҵ�
    for (int i = 0; i < L.length; i++) {
      if (L.elem[i] == e) {
        flag = i;
        break;
      }
    }
    if (flag == -1)
      return ERROR;
    else
      return flag + 1;
  }
}

/***************************************************************
*�������ƣ�PriorElem
*�������ܣ����ǰ��
*ע�ͣ�������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK��
���û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
*����ֵ���ͣ�status����
****************************************************************/

status PriorElem(SqList L, ElemType e, ElemType &pre) {

  if (!L.elem)
    return INFEASIBLE;
  else {
    for (int i = 1; i < L.length; i++) {
      if (L.elem[i] == e) {
        pre = L.elem[i - 1];
        return OK;
      }
    }
    return ERROR;
  }
}

/***************************************************************
*�������ƣ�NextElem
*�������ܣ���ȡ���
*ע�ͣ�������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK��
���û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
*����ֵ���ͣ�status����
****************************************************************/

status NextElem(SqList L, ElemType e, ElemType &next)

{

  if (!L.elem)
    return INFEASIBLE;
  else {
    for (int i = 0; i < L.length - 1; i++) {
      if (L.elem[i] == e) {
        next = L.elem[i + 1];
        return OK;
      }
    }
    return ERROR;
  }
}

/***************************************************************
*�������ƣ�ListInsert
*�������ܣ�����Ԫ��
*ע�ͣ�������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��
������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
*����ֵ���ͣ�status����
****************************************************************/

status ListInsert(SqList &L, int i, ElemType e) {
  if (!L.elem)
    return INFEASIBLE;
  else {

    if (i < 1 || i > L.length + 1)
      return ERROR;

    else {

      L.length++;
      if (L.length >= L.listsize) //�ǵ����ݣ�
      {
        L.elem = (ElemType *)realloc(L.elem, sizeof(ElemType *) *
                                                 (L.listsize + LISTINCREMENT));
      }
      for (int j = L.length - 1; j >= i; j--) {
        L.elem[j] = L.elem[j - 1];
      }
      L.elem[i - 1] = e;
      return OK;
    }
  }
}

/***************************************************************
*�������ƣ�ListTraverse
*�������ܣ�������
*ע�ͣ� ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��
������Ա�L�����ڣ�����INFEASIBLE��
*����ֵ���ͣ�status����
****************************************************************/

status ListTraverse(SqList L) {

  if (!L.elem)
    return INFEASIBLE;
  else {

    for (int i = 0; i < L.length; i++) {
      printf("%d", L.elem[i]);
      if (i != L.length - 1)
        printf(" ");
    }
    return OK;
  }
}

/***************************************************************
*�������ƣ�ListDelete
*�������ܣ�ɾ��Ԫ��
*ע�ͣ�������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK��
��ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
*����ֵ���ͣ�status����
****************************************************************/

status ListDelete(SqList &L, int i, ElemType &e)

{

  if (!L.elem)
    return INFEASIBLE;
  else {
    if (i <= 0 || i >= L.length + 1)
      return ERROR; //�ж�i��λ���Ƿ�Ϸ�
    else {
      if (i == L.length) //��������һ��Ԫ�أ�ɾ������
      {
        e = L.elem[i - 1];
        L.length--;
        return OK;
      } else //������Ҫ������Ԫ����ǰ�ƶ�
      {
        e = L.elem[i - 1];
        for (int j = i - 1; j <= L.length - 2; j++) {
          L.elem[j] = L.elem[j + 1];
        }
        L.length--;
        return OK;
      }
    }
  }
}

/***************************************************************
 *�������ƣ�SaveList
 *�������ܣ��������Ա��ļ���
 *ע�ͣ�������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
 *����ֵ���ͣ�status����
 ****************************************************************/

status SaveList(SqList L, char FileName[]) {
  FILE *fp;
  fp = fopen(FileName, "w");
  if (!L.elem)
    return INFEASIBLE;
  else {
    for (int i = 0; i < L.length; i++) {
      fprintf(fp, "%d", L.elem[i]); //�����ݴ�ӡ���ļ���
      if (i != L.length - 1) {
        fprintf(fp, " "); //��ʽ����
      }
    }
    fclose(fp);
    return OK;
  }
}

/***************************************************************
 *�������ƣ�LoadList
 *�������ܣ����ļ��ж������ݵ����Ա�
 *ע�ͣ�
 *������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
 *����ֵ���ͣ�status����
 ****************************************************************/

status LoadList(SqList &L, char FileName[]) {
  FILE *fp;
  fp = fopen(FileName, "r");
  if (L.elem)
    return INFEASIBLE;
  else {
    L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE); //�����±�
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    ElemType data;
    while (fscanf(fp, "%d", &data) != EOF) //���ļ��ж�ȡ����
    {
      if (L.length >= L.listsize) //�����Ա���������������
      {
        L.elem = (ElemType *)realloc(L.elem, sizeof(ElemType) *
                                                 (L.listsize + LISTINCREMENT));
        L.listsize += LISTINCREMENT;
      }
      L.elem[L.length++] = data;
    }

    fclose(fp);
    return OK;
  }
}

/***************************************************************
 *�������ƣ�AddList
 *�������ܣ�����±�
 *ע�ͣ�������Ա�������������ERROR�����򴴽�һ�������Ա������ڴ棬����OK��
 *����ֵ���ͣ�status����
 ****************************************************************/

status AddList(LISTS &Lists, char ListName[])

{
  if (Lists.length > 9)
    return ERROR;
  else {
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
  }
  /********** End **********/
}

/***************************************************************
 *�������ƣ�RemoveList
 *�������ܣ�ɾ��ָ����
 *ע�ͣ�����ҵ������Ա�ɾ��������OK�����򷵻�ERROR
 *����ֵ���ͣ�status����
 ****************************************************************/

status RemoveList(LISTS &Lists, char ListName[]) {
  int flag = -1; //�ж��Ƿ��ҵ�Ŀ��
  for (int i = 0; i < Lists.length; i++) {
    if (strcmp(Lists.elem[i].name, ListName) == 0) //���αȽ�
    {
      flag = i;
      break; //�ҵ����˳�ѭ��
    }
  }
  if (flag != -1) {
    for (int i = flag; i < Lists.length - 1; i++) {
      Lists.elem[i] = Lists.elem[i + 1];
    }
    Lists.length--;
    return OK;
  } else
    return ERROR;
}

/***************************************************************
 *�������ƣ�LocateList
 *�������ܣ�����ָ����
 *ע�ͣ�����ҵ������Ա��������߼���ţ����򷵻�0.
 *����ֵ���ͣ�int����
 ****************************************************************/

int LocateList(LISTS Lists, char ListName[])
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{

  int flag = -1;
  for (int i = 0; i < Lists.length; i++) {
    if (strcmp(Lists.elem[i].name, ListName) == 0) {
      flag = i + 1;
      break;
    }
  }
  if (flag == -1)
    return 0;
  else
    return flag;
}

/***************************************************************
 *�������ƣ�MaxSubArray
 *�������ܣ�������������������
 *ע�ͣ�����̰��˼�뱣��������
 *����ֵ���ͣ�ElemType����
 ****************************************************************/

ElemType MaxSubArray(SqList L) {
  ElemType ans = L.elem[0];
  ElemType sum = 0;
  for (int i = 0; i < L.length; i++) {
    if (sum >= 0)
      sum += L.elem[i];
    else
      sum = L.elem[i];
    ans = max(ans, sum);
  }
  return ans;
}

/***************************************************************
 *�������ƣ�SubArrayNum
 *�������ܣ������ΪK�����������
 *ע�ͣ�����ǰ׺�ͺ�ö���㷨�Ƚ�ÿһ�����
 *����ֵ���ͣ�int����
 ****************************************************************/

int SubArrayNum(SqList L, int k) {
  int count = 0;

  // ����ǰ׺������
  int *prefixSum = (int *)malloc(sizeof(int) * (L.length + 1));
  prefixSum[0] = 0;
  for (int i = 0; i < L.length; i++) {
    prefixSum[i + 1] = prefixSum[i] + L.elem[i];
  }

  // �������������鲢�ȽϺ��Ƿ�Ϊk
  for (int i = 0; i < L.length; i++) {
    for (int j = i + 1; j <= L.length; j++) {
      if (prefixSum[j] - prefixSum[i] == k) {
        count++;
      }
    }
  }
  return count;
}

/***************************************************************
 *�������ƣ�SortList
 *�������ܣ����Ա�����
 *ע�ͣ�������Ա����ڣ�����INFEASIBLE��������Ա�Ϊ�գ�����ERROR��
 *����ֵ���ͣ�status����
 ****************************************************************/

status SortList(SqList L) {
  if (!L.elem)
    return INFEASIBLE;
  else if (L.length == 0)
    return ERROR;
  else {
    sort(L.elem, L.elem + L.length); //���ÿ⺯����С��������
    return OK;
  }
}




int main(void) {
  Lists.elem[0].L.elem = NULL;
  Lists.length = 1;
  int op = 1;
  int n = 0;
  int u = 0; //Ĭ�϶Ե�һ�����Ա����
  ElemType e1, e2, e3, e5, e6, e7;
  int f, i, m, j, k; //������ʱ�������ݻ����״̬�ж�
  char filename[80]; //���ж�д�������ļ���
  char listname[20]; //���ڶ����Ա���������λ�Ȳ���
  while (op) {
    system("cls");
    printf("\n\n"); //����������һ������Ĳ˵�
    printf("                           Menu \n");
    printf("---------------------------------------------------------\n");
    printf("    	  1. InitList          11. ListDelete\n");
    printf("    	  2. DestroyList       12. ListTrabverse\n");
    printf("    	  3. ClearList         13. MaxSubArray\n");
    printf("    	  4. ListEmpty         14. SubArrayNum\n");
    printf("    	  5. ListLength        15. SortList\n");
    printf("    	  6. GetElem           16. SaveList\n");
    printf("          7. LocateElem        17. LoadList\n");
    printf("          8. PriorElem         18. InitValue\n");
    printf("    	  9. NextElem          19. "
           "ChooseList\n");
    printf("          10. ListInsert       20. NameList\n");
    printf("          21.AddList           22. RemoveList\n");
    printf("          23.LocateList        24. AllListTrabverse\n");
    printf("          0.Exit\n");
    printf("---------------------------------------------------------\n");
    printf("    ��ѡ����Ĳ���[0~24]:");
    scanf("%d", &op);
    switch (op) {
    case 1:
      if (InitList(Lists.elem[n].L) == OK)
        printf("���Ա����ɹ���\n");
      else
        printf("���Ա���ʧ�ܣ�\n");
      getchar();
      getchar();
      break;
    case 2:
      if (DestroyList(Lists.elem[n].L) == OK)
        printf("���Ա����ٳɹ���\n");
      else
        printf("���Ա�����ʧ�ܣ�\n");
      getchar();
      getchar();
      break;
    case 3:
      if (ClearList(Lists.elem[n].L) == OK)
        printf("���Ա��������\n");
      else
        printf("���Ա����ʧ�ܣ�\n");
      getchar();
      getchar();
      break;
    case 4:
      if (ListEmpty(Lists.elem[n].L) == TRUE)
        printf("���Ա�Ϊ�գ�\n");
      else if (ListEmpty(Lists.elem[n].L) == FALSE)
        printf("���Ա�Ϊ��!\n");
      else
        printf("���Ա�����!\n");
      getchar();
      getchar();
      break;
    case 5:
      if (ListLength(Lists.elem[n].L) == INFEASIBLE)
        printf("���Ա�����!\n");
      else
        printf("���Ա�ĳ���Ϊ%d\n", ListLength(Lists.elem[n].L));
      getchar();
      getchar();
      break;
    case 6:
      printf("��������Ҫ��ȡ��Ԫ��λ��:\n");
      scanf("%d", &i);
      if (GetElem(Lists.elem[n].L, i, e1) == INFEASIBLE)
        printf("���Ա�����!\n");
      else if (GetElem(Lists.elem[n].L, i, e1) == ERROR)
        printf("�����λ�ò������Ա���Ч��Χ��!\n");
      else
        printf("��λ�õ�Ԫ��ֵΪ%d���ѱ�����e1��\n", e1);
      getchar();
      getchar();
      break;
    case 7:
      printf("������Ҫ���ҵ�Ԫ��e:\n");
      scanf("%d", &e2);
      if (LocateElem(Lists.elem[n].L, e2) == INFEASIBLE)
        printf("���Ա�����!\n");
      else if (LocateElem(Lists.elem[n].L, e2) == ERROR)
        printf("�����ݲ�����!\n");
      else
        printf("��Ԫ�������Ա��е�һ�γ��ֵ�λ�����Ϊ%d\n",
               LocateElem(Lists.elem[n].L, e2));
      getchar();
      getchar();
      break;
    case 8:
      ElemType e4;
      ElemType pre;
      printf("��������Ҫ����ǰ����Ԫ��:\n");
      scanf("%d", &e4);
      if (PriorElem(Lists.elem[n].L, e4, pre) == INFEASIBLE)
        printf("���Ա�����!\n");
      else if (PriorElem(Lists.elem[n].L, e4, pre) == ERROR)
        printf("ǰ��������!\n");
      else
        printf("%d��ǰ��ֵΪ%d,�ѱ�����pre��\n", e4, pre);
      getchar();
      getchar();
      break;
    case 9:
      ElemType next;
      printf("��������Ҫ���Һ�̵�Ԫ��e:\n");
      scanf("%d", &e5);
      if (NextElem(Lists.elem[n].L, e5, next) == INFEASIBLE)
        printf("���Ա�����!\n");
      else if (NextElem(Lists.elem[n].L, e5, next) == ERROR)
        printf("��̲�����!\n");
      else
        printf("%d�ĺ��ֵΪ%d,�ѱ�����next��\n", e5, next);
      getchar();
      getchar();
      break;
    case 10:
      printf("������Ҫ�����λ�ã����Ա�ڼ���Ԫ��֮ǰ����Ԫ��ֵ\n");
      scanf("%d%d", &i, &e6);
      f = ListInsert(Lists.elem[n].L, i, e6);
      if (f == INFEASIBLE)
        printf("���Ա�����!\n");
      else if (f == ERROR)
        printf("����λ�ò���ȷ!\n");
      else
        printf("����ɹ�!\n");

      getchar();
      getchar();
      break;
    case 11:
      printf("������Ҫɾ����Ԫ��λ��(�ڼ���Ԫ��)\n");
      scanf("%d", &i);
      m = ListDelete(Lists.elem[n].L, i, e7);
      if (m == INFEASIBLE)
        printf("���Ա�����!\n");
      else if (m == ERROR)
        printf("ɾ��λ�ò���ȷ!\n");
      else
        printf("ɾ���ɹ�!ɾ��������%d�ѱ�����e7��\n", e7);
      getchar();
      getchar();
      break;
    case 12:
      j = ListTraverse(Lists.elem[n].L);
      if (j == INFEASIBLE)
        printf("���Ա����ڣ�\n");
      if (j == OK && !Lists.elem[n].L.length)
        printf("�����Ա�\n");
      getchar();
      getchar();
      break;
    case 13:
      if (!Lists.elem[n].L.elem)
        printf("���Ա�����!\n");
      else if (Lists.elem[n].L.length == 0)
        printf("���Ա�Ϊ��!\n");
      else
        printf("��������������Ϊ%d\n", MaxSubArray(Lists.elem[n].L));
      getchar();
      getchar();
      break;
    case 14:
      if (!Lists.elem[n].L.elem)
        printf("���Ա�����!\n");
      else if (Lists.elem[n].L.length == 0)
        printf("���Ա�Ϊ��!\n");
      else {
        printf("������Ŀ���K��ֵ:\n");
        scanf("%d", &k);
        printf("��Ϊ%d��������������ĿΪ%d\n", k,
               SubArrayNum(Lists.elem[n].L, k));
      }
      getchar();
      getchar();
      break;
    case 15:
      j = SortList(Lists.elem[n].L);
      if (j == INFEASIBLE)
        printf("���Ա�����!\n");
      else if (j == ERROR)
        printf("���Ա�Ϊ��!\n");
      else
        printf("���������!\n");
      getchar();
      getchar();
      break;
    case 16:
      printf("�������ļ�·��:\n");
      scanf("%s", filename);
      if (SaveList(Lists.elem[n].L, filename) == OK)
        printf("����д�����!\n");
      else
        printf("д��ʧ��!\n");
      getchar();
      getchar();
      break;
    case 17:
      printf("�������ļ�·��:\n");
      scanf("%s", filename);
      if (LoadList(Lists.elem[n].L, filename) == OK)
        printf("���ݶ������!\n");
      else
        printf("����ʧ��!\n");
      getchar();
      getchar();
      break;
    case 18:
      if (!Lists.elem[n].L.elem)
        printf("���Ա�����!\n");
      else {
        printf("����������Ҫ�������Ա��ֵ(��0��������):\n");
        scanf("%d", &e3);
        while (e3 != 0) {
          ListInsert(Lists.elem[n].L, Lists.elem[n].L.length + 1, e3);
          scanf("%d", &e3);
        }
        printf("�����Ѵ������Ա�!\n");
      }
      getchar();
      getchar();
      break;
    case 19:
      printf("��ѡ����Ҫ���������Ա���(1-10):\n");
      u = n;
      scanf("%d", &n);
      n--;
      if (n + 1 > Lists.length) {
        printf("�л�ʧ��!\n");
        n = u;
      } else
        printf("�л��ɹ�!\n");
      getchar();
      getchar();
      break;
    case 20:
      printf("��Ե�ǰ���Ա��������:\n");
      scanf("%s", Lists.elem[n].name);
      printf("�����ɹ�!\n");
      getchar();
      getchar();
      break;
    case 21:
      if (Lists.length > 9)
        printf("���Ա��Ѵ�10�����޷����!\n");
      else {
        printf("������Ҫ��ӵ����Ա���:\n");
        scanf("%s", listname);
        AddList(Lists, listname);
        printf("��ӳɹ�!\n");
      }
      getchar();
      getchar();
      break;
    case 22:
      printf("������Ҫɾ�������Ա���:\n");
      scanf("%s", listname);
      if (RemoveList(Lists, listname) == OK)
        printf("ɾ���ɹ�!\n");
      else
        printf("ɾ��ʧ��!\n");
      getchar();
      getchar();
      break;
    case 23:
      printf("������Ҫ���ҵ����Ա���:\n");
      scanf("%s", listname);
      f = LocateList(Lists, listname);
      if (f != 0)
        printf("�����Ա���߼����Ϊ%d\n", f);
      else
        printf("û���ҵ������Ա�\n");
      getchar();
      getchar();
      break;
    case 24:

      for (int i = 0; i < 10; i++) {
        if (Lists.elem[i].L.elem && Lists.elem[i].L.length) {
          printf("%s ", Lists.elem[i].name); //��ӡ���Ա���
          ListTraverse(Lists.elem[i].L);     //��ӡ����
          printf("\n");
        }
      }
      getchar();
      getchar();
      break;
    case 0:
      break;
    } // end of switch
  }   // end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0;
}