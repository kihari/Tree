#include <iostream>
#include<Windows.h>
#include<random>
#include<ctime>
#include<string.h>
#include<cctype>

using namespace std;
int H = 0;
int barr[1000];
int x = 0;
int minimal = 0;
int maximum = 0;

struct Node
{
	int data;
	Node* left;
	Node* right;
};

struct random_n
{
	int data;
	int size;
	random_n* left;
	random_n* right;
	random_n(int key) { data = key; left = right = 0; size = 1; }
};
template <typename Type>
Type DeleteTree(Type tree)
{
	if (!tree)
		return tree;
	DeleteTree(tree->left);
	DeleteTree(tree->right);

	delete tree;
	tree = NULL;

	return tree;
}
template <typename Type>
void print(Type tree, int t)
{
	if (tree)
	{
		print(tree->right, t + 1);
		for (int i = 0; i < t; i++)
			cout << "    ";

		cout << tree->data << endl;
		print(tree->left, t + 1);
	}
}
template <typename Type>
int heigh(Type tree)
{
	int h = 0;
	int hl = 0;
	int hr = 0;
	if (tree)
	{
		hl = heigh(tree->left);
		hr = heigh(tree->right);
		if (hl > hr)
			h = hl + 1;
		else
			h = hr + 1;
	}
	return h;
}
template <typename Type>
void print1(Type tree, int t)
{
	if (tree)
	{
		print1(tree->right, t + 1);
		print1(tree->left, t + 1);
		if (tree->right == NULL && tree->left == NULL)
		{
			barr[x] = t;
			x++;
		}
	}
}

int* generation(int* arr, int size, int min, int max);
int* sort(int* arr, int size);
bool repeat(int key, int* arr, int size);
Node* addnode(Node* tree, int key);
random_n* Lrotate(random_n* tree);
random_n* Rrotate(random_n* tree);
random_n* insertroot(random_n* tree, int key);
random_n* insert(random_n* tree, int key);
void print_data(Node* tree, random_n* rand_t, int item);


int main()
{
	Node* tree = NULL;
	random_n* rand_t = NULL;
	int size;
	int min = 1;
	int max = 100;
	int* arr;

	setlocale(LC_ALL, "rus");

	cout << "Введите кол-во ключей: ";
	cin >> size;
	cout << endl;

	//случайная последовательность ключей
	arr = new int[size];
	arr = generation(arr, size, min, max);

	cout << "Случайная последовательность ключей: ";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	for (int i = 0; i < size; i++)
	{
		tree = addnode(tree, arr[i]);
	}
	cout << "\nОбычное дерево:\n\n";
	print(tree, 0);
	cout << "\nВысота дерева = " << heigh(tree) << "\n";

	print1(tree, 0);

	minimal = barr[0];
	maximum = barr[0];
	for (int i = 0; i < x; i++)
	{
		if (minimal > barr[i])
			minimal = barr[i];
	}
	for (int i = 0; i < x; i++)
	{
		if (maximum < barr[i])
			maximum = barr[i];
	}
	cout << "Минимальная высота в обычном дереве: " << minimal + 1 << endl;
	cout << "Максимальная высота в обычном дереве: " << maximum + 1 << endl << endl;

	for (int i = 0; i < x; i++)
		barr[i] = 0;
	x = 0;

	for (int i = 0; i < size; i++)
		rand_t = insert(rand_t, arr[i]);
	cout << "Рандомизированное дерево:\n\n";
	print(rand_t, 0);
	cout << "\nВысота дерева = " << heigh(rand_t) << "\n";
	print1(rand_t, 0);

	minimal = barr[0];
	maximum = barr[0];
	for (int i = 0; i < x; i++)
	{
		if (minimal > barr[i])
			minimal = barr[i];
	}
	for (int i = 0; i < x; i++)
		if (maximum < barr[i])
			maximum = barr[i];

	cout << "Минимальная высота в рандомизированном дереве: " << minimal + 1 << endl;
	cout << "Максимальная высота в рандомизированном дереве: " << maximum + 1 << endl << endl;
	tree = DeleteTree(tree);
	rand_t = DeleteTree(rand_t);

	//деревья из упорядоченной последовательности ключей 
	for (int i = 0; i < x; i++)
		barr[i] = 0;
	x = 0;
	arr = sort(arr, size);
	cout << "\n\nУпорядоченная последовательность ключей:\n\n<";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";

	for (int i = 0; i < size; i++)
		tree = addnode(tree, arr[i]);

	cout << "\nОбычное дерево:\n\n";
	print(tree, 0);
	cout << "\nВысота дерева = " << heigh(tree) << "\n";

	print1(tree, 0);

	minimal = barr[0];
	maximum = barr[0];
	for (int i = 0; i < x; i++)
		if (minimal > barr[i])
			minimal = barr[i];

	for (int i = 0; i < x; i++)
		if (maximum < barr[i])
			maximum = barr[i];

	cout << "Минимальная высота в рандомизированном дереве: " << minimal + 1 << endl;
	cout << "Максимальная высота в рандомизированном дереве: " << maximum + 1 << endl << endl;

	for (int i = 0; i < x; i++)
		barr[i] = 0;
	x = 0;

	for (int i = 0; i < size; i++)
		rand_t = insert(rand_t, arr[i]);
	cout << "Рандомизированное дерево:\n\n";

	print(rand_t, 0);
	cout << "\nВысота дерева = " << heigh(rand_t) << "\n";

	print1(rand_t, 0);

	minimal = barr[0];
	maximum = barr[0];
	for (int i = 0; i < x; i++)
		if (minimal > barr[i])
			minimal = barr[i];

	for (int i = 0; i < x; i++)
		if (maximum < barr[i])
			maximum = barr[i];

	cout << "Минимальная высота в обычном дереве: " << minimal + 1 << endl;
	cout << "Максимальная высота в обычном дереве: " << maximum + 1 << endl << endl;

	for (int i = 0; i < x; i++)
		barr[i] = 0;
	x = 0;

	tree = DeleteTree(tree);
	rand_t = DeleteTree(rand_t);
	delete[] arr;

	//table

	cout << "\n\n\n\t\tЗависимость высоты от кол-ва ключей:\n\n";
	cout << "Случайная последовательность\n";
	cout << "кол-во ключей\tобычное дерево\tmin\tmax\tрандомизированное\tmin\tmax\n\n";
	print_data(tree, rand_t, 0);

	cout << "\n\nУпорядоченная последовательность\n";
	cout << "кол-во ключей\tобычное дерево\tmin\tmax\tрандомизированное\tmin\tmax\n\n";
	print_data(tree, rand_t, 1);

	return 0;
}
bool repeat(int key, int* arr, int size)
{
	bool flag = false;
	if (size == -1)
		return flag;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] == key)
		{
			flag = true;
			break;
		}
	}

	return flag;
}
int* generation(int* arr, int size, int min, int max)
{
	int i = 0;

	while (i < size)
	{
		arr[i] = min + rand() % (max - min);
		while (repeat(arr[i], arr, i))
		{
			arr[i] = min + rand() % (max - min);
		}
		i++;
	}
	return arr;
}
int* sort(int* arr, int size)
{
	int temp = 0;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return arr;
}
Node* addnode(Node* tree, int key)
{
	if (tree == NULL)
	{
		tree = new Node;
		tree->data = key;
		tree->left = NULL;
		tree->right = NULL;
	}
	else if (key == tree->data)
		cout << "Ключ " << key << " уже в дереве" << endl;
	else if (key < tree->data)
		tree->left = addnode(tree->left, key);
	else if (key > tree->data)
		tree->right = addnode(tree->right, key);
	return tree;
}
int getsize(random_n* tree)  //для поля size работает с пустыми деревьями
{
	if (!tree) return 0;
	return tree->size;
}
void fixsize(random_n* tree)  //установка корректного размера дерева
{
	tree->size = getsize(tree->left) + getsize(tree->right) + 1;
}
random_n* Rrotate(random_n* tree)
{
	random_n* q = tree->left;
	if (!q) return tree;
	tree->left = q->right;
	q->right = tree;
	q->size = tree->size;
	fixsize(tree);
	return q;
}
random_n* Lrotate(random_n* tree)
{
	random_n* q = tree->right;
	if (!tree) return q;
	tree->right = q->left;
	q->left = tree;
	q->size = tree->size;
	fixsize(tree);
	return q;
}
random_n* insertroot(random_n* tree, int key)
{
	if (!tree) return new random_n(key);
	if (key < tree->data)
	{
		tree->left = insertroot(tree->left, key);
		return Rrotate(tree);
	}
	else
	{
		tree->right = insertroot(tree->right, key);
		return Lrotate(tree);
	}
}
random_n* insert(random_n* tree, int key)
{
	if (!tree)
		return new random_n(key);
	if (rand() % (tree->size + 1) == 0)
	{
		return insertroot(tree, key);
	}
	if (key < tree->data)
		tree->left = insert(tree->left, key);
	else
		tree->right = insert(tree->right, key);

	fixsize(tree);
	return tree;
}
void print_data(Node* tree, random_n* rand_t, int mode)
{
	int size;
	int* arr;
	for (size = 25; size <= 300; size += 25)
	{
		arr = new int[size];

		arr = generation(arr, size, 0, 1000);
		if (mode == 1)
			arr = sort(arr, size);

		for (int i = 0; i < size; i++)
			tree = addnode(tree, arr[i]);
		for (int i = 0; i < size; i++)
			rand_t = insert(rand_t, arr[i]);

		print1(tree, 0);

		minimal = barr[0];
		maximum = barr[0];
		for (int i = 0; i < x; i++)
			if (minimal > barr[i])
				minimal = barr[i];

		for (int i = 0; i < x; i++)
			if (maximum < barr[i])
				maximum = barr[i];

		cout << size << "\t\t" << heigh(tree) << "\t\t" << minimal + 1 << "\t" << maximum + 1 << "\t\t" << heigh(rand_t);

		for (int i = 0; i < x; i++)
			barr[i] = 0;
		x = 0;

		print1(rand_t, 0);

		minimal = barr[0];
		maximum = barr[0];
		for (int i = 0; i < x; i++)
			if (minimal > barr[i])
				minimal = barr[i];

		for (int i = 0; i < x; i++)
			if (maximum < barr[i])
				maximum = barr[i];

		cout << "\t\t" << minimal + 1 << "\t" << maximum + 1 << endl;

		for (int i = 0; i < x; i++)
			barr[i] = 0;
		x = 0;

		tree = DeleteTree(tree);
		rand_t = DeleteTree(rand_t);
		delete[] arr;
	}
}