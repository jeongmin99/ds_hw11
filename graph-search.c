#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 10

typedef struct node//��� ����ü ����
{
	int vertex;
	struct node* link;

}Node;


Node* graph[MAX_VERTICES];//��������Ʈ ���·� ������ �� ������ ������ ������ �迭
short int isInserted[MAX_VERTICES];//������ ���ԵǾ��ִ��� �Ǵ��ϴ� �迭
short int visited[MAX_VERTICES];//������ �湮�ߴ��� �Ǵ��ϴ� �迭
int nodecount=0;//������ ����


/* ť ���� */
int queue[MAX_VERTICES];//ť���� �����͸� ������ �迭
int front=0;//ť�� front
int rear=0;//ť�� rear


/* �Լ� ������Ÿ�� ����*/
void initializeGraph();
void insertVertex(int);
void insertEdge(int,int);
void insertNode(int,int);
void dfs(int);
void bfs(int);
void printGraph();
void freeGraph();
void enqueue(int);
int dequeue();

int main()
{
	char command;
	int key1,key2;

	setvbuf(stdout, NULL, _IONBF, 0);
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                  		   Graph Searches                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeGraph();//�׷��� �ʱ�ȭ
			break;
		case 'q': case 'Q':
			freeGraph();//�׷��� �޸� ����
			break;
		case 'v': case 'V':
			printf("Your Key = ");//���� ���� �Է�
			scanf("%d", &key1);
			insertVertex(key1);//���� ����
			break;
		case 'e': case 'E':
			printf("Your Key = ");//������ ����� ���� 2���Է�
			scanf("%d %d", &key1,&key2);
			insertEdge(key1,key2);
			break;

		case 'd': case 'D':
			printf("Your Key = ");//dfs�� ������ ���� �Է�
			scanf("%d", &key1);
			for(int i=0;i<MAX_VERTICES;i++)//�湮�迭 �ʱ�ȭ
			{
				visited[i]=FALSE;
			}
			dfs(key1);
			break;
		case 'b': case 'B':
			printf("Your Key = ");//bfs�� ������ ���� �Է�
			scanf("%d", &key1);
			for(int i=0;i<MAX_VERTICES;i++)//�湮�迭 �ʱ�ȭ
			{
				visited[i]=FALSE;
			}
			bfs(key1);
			break;

		case 'p': case 'P':
			printGraph();//��������Ʈ�� ����� ���� ���
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void initializeGraph()//�׷��� �ʱ�ȭ
{


	nodecount=0;//���� ���� �ʱ�ȭ

	for(int i=0;i<MAX_VERTICES;i++)//���� ����Ʈ ���� �迭���� ������ �ε����� ����
	{
		if(graph[i]!=NULL)//��尡 �����ϸ�
		{
			Node* cur=graph[i];
			Node* prev=NULL;
			while(cur!=NULL)/*��� �޸� ����*/
			{
				prev=cur;
				cur=cur->link;
				free(prev);
			}
		}
		graph[i]=NULL;//���� ����Ʈ �迭 �ʱ�ȭ
		visited[i]=FALSE;//�湮 �迭 �ʱ�ȭ
		isInserted[i]=FALSE;//���Ե� �������� Ȯ���ϴ� �迭 �ʱ�ȭ
	}

}

void insertVertex(int v)//���� ����
{
	if(nodecount+1>MAX_VERTICES)//��� ������ �ִ� ������ �Ѿ���ϸ�
	{
		printf("������ ����á���ϴ�.\n");
		return;
	}

	if(isInserted[v]==TRUE)//v�� ������ �̹� ���ԵǾ��ٸ�
	{
		printf("�̹� ���Ե� �����Դϴ�.\n");
		return;
	}

	isInserted[v]=TRUE;//v�� ���� ������ �Ǿ��ٰ� üũ
	nodecount++;//��� ���� ����
}

void insertEdge(int v1,int v2)//���� ����
{

	if(isInserted[v1]==FALSE || isInserted[v2]==FALSE)//v1�� �����̳� v2�� ������ ���Ե��� �ʾҴٸ�
	{
		printf("�������� �ʴ� �����Դϴ�.\n");
		return;
	}
	else
	{
		Node* cur=graph[v2];//v2 ����(��������Ʈ �迭�� v2�ε���) ����
		while(cur!=NULL)/* v1 ������ v2�� ����Ǿ��ִ��� �Ǵ�*/
		{
			if(cur->vertex==v1)//����Ǿ��ִٸ�
			{
				printf("�̹� �����ϴ� �����Դϴ�.\n");
				return;
			}
			cur=cur->link;
		}

		insertNode(v1,v2);//v2���� �迭�� v1��� ����

		cur=graph[v1];//v1 ����(��������Ʈ �迭�� v1 �ε���) ����

		while(cur!=NULL)/* v2 ������ v1�� ����Ǿ��ִ��� �Ǵ�*/
		{
			if(cur->vertex==v2)//����Ǿ��ִٸ�
			{
				printf("�̹� �����ϴ� �����Դϴ�.\n");
				return;
			}
			cur=cur->link;
		}

		insertNode(v2,v1);//v1 ���� �迭�� v2��� ����
	}


}
void insertNode(int v1,int v2)//���Ḯ��Ʈ v2 �ε����� ��� ����
{

	/* v1 ���� ��� ����*/
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->vertex=v1;
	newNode->link=NULL;

	if(graph[v2]==NULL)//v2 �ε����� ���������
	{
		graph[v2]=newNode;//����Ҵ�
	}
	else
	{
		Node* cur=graph[v2];
		Node* prev=NULL;
		while(cur!=NULL)/* ���� ������ �����ϱ����� ����Ʈ�� ���� ��尡 �տ� ������ ����*/
	    {
		    if(cur->vertex>=v1)//v1���� ���� ��尡 ũ�ų� ������
		    {
				if(cur==graph[v2])//���� ��� ��ġ�� �Ǿ��̸�
				{
					newNode->link=cur;//���ο� ����� ������带 ������� ��ũ
					graph[v2]=newNode;//�� �� ���� ���ο� ���
				}
				else
				{
					newNode->link=cur;//���ο� ����� �������� ������
					prev->link=newNode;//���� ����� ���� ���� ���ο� ���
				}
			    return;
			}

			prev=cur;//���� ��� ����
			cur=cur->link;//������ �̵�

		}

	/* ����Ʈ�� ������ ���� ���*/
	prev->link=newNode;//��������� �������� ���ο���
	return ;

	}
}

void dfs(int v)//���� �켱 Ž��
{

	Node* cur=graph[v];//Ž�� ��带 ��������Ʈ �迭�� v�ε����� ����
	visited[v]=TRUE;//v ���� �湮
	printf("%d ",v);//���
	while(cur!=NULL)//Ž����尡 �����ϴ� ����
	{
		if(visited[cur->vertex]==FALSE)//Ž������� ������ �湮 ��������
		{
			dfs(cur->vertex);//Ž������� �������� ��������� dfsȣ��
		}
		cur=cur->link;//Ž����� �̵�
	}
}

void bfs(int v)//�ʺ� �켱 Ž��
{

	Node* cur;//Ž����� ����
	visited[v]=TRUE;//v ���� �湮
	printf("%d ",v);//���� ���
	enqueue(v);//v ���� ť�� ����

	while(TRUE)
	{
		v=dequeue();//ť���� ��� ����
		if(v==-1) return;//ť�� ����� �� �����ſ����� �Լ� ����
		for(cur=graph[v];cur!=NULL;cur=cur->link)//���� v ��������Ʈ�� Ž������� ��ġ�� ����, Ž����� �̵��ϸ鼭 Ž��
		{
			if(visited[cur->vertex]==FALSE)//Ž����� ������ �湮 ��������
			{
				printf("%d ",cur->vertex);//���� ���
				enqueue(cur->vertex);//ť�� ���� ����
				visited[cur->vertex]=TRUE;//���� �湮
			}

		}
	}

}

void enqueue(int v)//ť�� ��� ����
{
	if((rear+1)%MAX_VERTICES==front)//ť�� ������������
	{
		return;//�Լ�����
	}

	rear=(rear+1)%MAX_VERTICES;//rear�� ����
	queue[rear]=v;//rear�� ����Ű�� ���� ��� ����

}

int dequeue()//ť���� ��� ������
{
	if(front==rear)//ť�� ���������
	{
		return -1;//-1 ��ȯ
	}

	front=(front+1)%MAX_VERTICES;//front�� ����
	return queue[front];//front�� ����Ű�� ��ġ�� ��� ��ȯ
}

void printGraph()//��������Ʈ �迭�� ����� ���� ���
{
	for(int i=0;i<MAX_VERTICES;i++)//��� ��������Ʈ �迭 �ε����� ���鼭
	{
		printf("graph[%d]= ",i);
		Node* cur=graph[i];//Ž�� ��带 �ε����� �ش��ϴ� �迭��ҷ� ����
		while(cur!=NULL)
		{
			printf("[%d] ",cur->vertex);//Ž����� ������ ���
			cur=cur->link;//Ž�� ��� �̵�
		}

		printf("\n");
	}

}
void freeGraph()//�׷��� ����
{

	for(int i=0;i<MAX_VERTICES;i++)//��� ���� �ݺ�
	{
		if(graph[i]!=NULL)//��������Ʈ�迭�� ������� ������
		{
			Node* cur=graph[i];/* �� �迭�� �ִ� ���� Ž���Ͽ� �ϳ��� ����*/
			Node* prev=NULL;
			while(cur!=NULL)
			{
				prev=cur;
				cur=cur->link;
				free(prev);
			}

		}
	}
}


