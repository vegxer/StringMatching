#include <iostream>
#include <string>

using namespace std;


const int ALPHABET_SIZE = 256;
const int SIZE = 100;

struct SuffixTreeNode
{
	SuffixTreeNode* children[ALPHABET_SIZE]; //дети вершины
	SuffixTreeNode* suffixLink; //суффиксная ссылка на вершину
	//start и end - индексы начала и конца строки на ребре в исходной строке
	int start;
	int* end;
	int suffixIndex; //индекс суффикса в исходной строке
};


char text[SIZE]; //входная строка
SuffixTreeNode* root; //корень дерева
//указатель на последнюю созданную внутреннюю вершину
SuffixTreeNode* lastNewNode;

SuffixTreeNode* activeNode; //активная вершина
int activeEdge = -1; //индекс символа входной строки
int activeLength = 0; //позиция на ребре

int remainingSuffixCount = 0; //осталось добавить суффиксов в дерево
//индексы последних символов на ребре в исходной строке
int leafEnd = -1;
int* rootEnd;
int* NewNodeEnd;
int Size = -1; //длина входной строки

SuffixTreeNode* newNode(int, int*);
int edgeLength(SuffixTreeNode*);
bool walkDown(SuffixTreeNode*);
void suffixTreeExtension(int);
void printSuffixTree(int, int);
void setAndPrintSuffixIndex(SuffixTreeNode*, int);
void deleteTree(SuffixTreeNode*);
bool traverseTree(SuffixTreeNode*, string, int);
bool traverseEdge(string, int, int, int);
void buildSuffixTree();

int main()
{
	setlocale(LC_CTYPE, "rus");
	string input;
	cout << "Введите строку: ";
	cin >> input;
	input += '$';
	for (int i = 0; i < input.length(); ++i)
		text[i] = input[i];
	buildSuffixTree();
	//вывод дерева
	cout << "Суффиксное дерево:\n";
	setAndPrintSuffixIndex(root, 0);
	string pattern;
	cout << "Введите паттерн: ";
	cin >> pattern;
	//поиск паттерна
	bool res = traverseTree(root, pattern + '$', 0);
	cout << "Вхождение подстроки в строку" << (res ? " найдено\n" : " не найдено\n");
	//удаление дерева
	deleteTree(root);
	system("pause");
	return 0;
}

bool traverseTree(SuffixTreeNode* currNode, string pattern, int index)
{
	if (traverseEdge(pattern, index, currNode->start, *(currNode->end)))
		return true;
	//индекс символа паттерна
	index += edgeLength(currNode);
	/*если есть потомок для данного символа строки,
	то идём дальше, иначе вхождения уже не будет*/
	if (index < pattern.length() && currNode->children[pattern[index]] != NULL)
		return traverseTree(currNode->children[pattern[index]], pattern, index);
	else
		return false;
}

bool traverseEdge(string pattern, int index, int start, int end)
{
	//идём по ребру
	for (int k = start; k <= end && pattern[index] != '$'; k++, index++)
	{
		if (text[k] != pattern[index])
			return false;
	}
	return pattern[index] == '$';
}

//создание новой вершины
SuffixTreeNode* newNode(int start, int* end)
{
	SuffixTreeNode* node = new SuffixTreeNode;
	int i;
	for (i = 0; i < ALPHABET_SIZE; i++)
		node->children[i] = NULL;
	node->suffixLink = root; //суффиксная ссылка для всех вершин изначально - на корень
	node->start = start;
	node->end = end;
	/*для листьев индекс суффикса потом
	установится, а для внутренний останется -1*/
	node->suffixIndex = -1;
	return node;
}

//длина строки на ребре
int edgeLength(SuffixTreeNode* path)
{
	return *(path->end) - (path->start) + 1;
}

//переход по вершинам вниз
bool walkDown(SuffixTreeNode* currentNode)
{
	/* Если длина строки на текущем ребре меньше
	вставляемой, то переходим на следующую вершину */
	if (activeLength >= edgeLength(currentNode))
	{
		activeEdge += edgeLength(currentNode);
		activeLength -= edgeLength(currentNode);
		activeNode = currentNode;
		return true;
	}
	return false;
}

void suffixTreeExtension(int pos)
{
	leafEnd = pos;
	++remainingSuffixCount; //осталось добавить суффиксов
	/*устанавливаем lastNewDone в NULL, показывая,
	что нет внутренних вершин, которые ожидают
	установки суффиксной ссылки*/
	lastNewNode = NULL;

	//Вставляем суффиксы в дерево
	while (remainingSuffixCount > 0)
	{
		if (activeLength == 0)
			activeEdge = pos;

		//Если нет вершины, из которой выходит ребро с нужной строкой,
		//то создаём его
		if (activeNode->children[text[activeEdge]] == NULL)
		{
			activeNode->children[text[activeEdge]] = newNode(activeEdge, &leafEnd);
			//установка суффиксной ссылки
			if (lastNewNode != NULL)
			{
				lastNewNode->suffixLink = activeNode;
				lastNewNode = NULL;
			}
		}
		//если есть ребро, выходящее из текущей вершины,
		//с нужной строкой, переходим по нему
		else
		{
			SuffixTreeNode* next = activeNode->children[text[activeEdge]];
			//спускаемся по вершинам
			if (walkDown(next))
				continue;

			if (text[next->start + activeLength] == text[pos])
			{
				/*Если lastNewNode в ожидании установки
				суффиксной ссылки, то устаналиваем её*/
				if (lastNewNode != NULL && activeNode != root)
				{
					lastNewNode->suffixLink = activeNode;
					lastNewNode = NULL;
				}
				activeLength++;
				break; //переходи к следующему шагу
			}
			/*Если мы остановились посреди ребра, то создаём новую
			внутренню вершину, из которой будет выходить ребро с
			оставшейся невставленной частью строки и частью дерева,
			которая была ниже*/
			NewNodeEnd = new int();
			*NewNodeEnd = next->start + activeLength - 1;
			//новая внутренняя вершина
			SuffixTreeNode* splitEdge = newNode(next->start, NewNodeEnd);
			activeNode->children[text[activeEdge]] = splitEdge;
			//новый листок, выходящий от внутренней вершины
			splitEdge->children[text[pos]] = newNode(pos, &leafEnd);
			next->start = next->start + activeLength;
			splitEdge->children[text[next->start]] = next;

			//установка суффиксной ссылки
			if (lastNewNode != NULL)
			{
				lastNewNode->suffixLink = splitEdge;
			}
			/*последняя созданная вершина - вершина,
			которая образовалась после разделения ребра*/
			lastNewNode = splitEdge;
		}

		//осталось добавить суффиксов
		--remainingSuffixCount;
		if (activeNode == root && activeLength > 0)
		{
			activeLength--;
			activeEdge = pos - remainingSuffixCount + 1;
		}
		else if (activeNode != root)
		{
			activeNode = activeNode->suffixLink;
		}
	}
}

//вывод строки с ребра
void printSuffixTree(int start, int end)
{
	for (int i = start; i <= end; i++)
		cout << text[i];
}

//установка индексов листьям и вывод дерева
void setAndPrintSuffixIndex(SuffixTreeNode* node, int edge_length)
{
	if (node == NULL)
		return;
	//если не корень
	if (node->start != -1)
		printSuffixTree(node->start, *(node->end));

	bool leaf = true;
	for (int i = 0; i < ALPHABET_SIZE; ++i)
	{
		if (node->children[i] != NULL)
		{
			if (leaf && node->start != -1)
				cout << " [" << node->suffixIndex << "]\n";
			leaf = false;
			setAndPrintSuffixIndex(node->children[i], edge_length + edgeLength(node->children[i]));
		}
	}
	if (leaf)
	{
		node->suffixIndex = Size - edge_length;
		cout << " [" << node->suffixIndex << "]\n";
	}
}

void deleteTree(SuffixTreeNode* tree)
{
	if (tree == NULL)
		return;
	for (int i = 0; i < ALPHABET_SIZE; ++i)
	{
		if (tree->children[i] != NULL)
			deleteTree(tree->children[i]);
	}
	if (tree->suffixIndex == -1)
		delete tree->end;
	delete tree;
}

//построение суффиксного дерева
void buildSuffixTree()
{
	Size = strlen(text); //длина строки
	rootEnd = new int();
	*rootEnd = -1;

	//корень с начальным и конечным индексом -1
	root = newNode(-1, rootEnd);
	activeNode = root; //первая акивная вершина - корень
	for (int i = 0; i < Size; ++i)
		suffixTreeExtension(i);
}