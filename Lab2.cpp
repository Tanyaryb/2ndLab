#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "map.h"
using namespace std;

class HaffmansTree
{
public:
	int CurrentElementsSumm;
	char symbol;
	HaffmansTree* left, * right;

	HaffmansTree() { left = right = nullptr; }

	HaffmansTree(HaffmansTree* L, HaffmansTree* R)
	{
		left = L;
		right = R;
		CurrentElementsSumm = L->CurrentElementsSumm + R->CurrentElementsSumm;
	}
};

void sortList(List<HaffmansTree*> &list)
{
	List<HaffmansTree*>::Node *left = list.start;
	List<HaffmansTree*>::Node *right = list.start->next;          //Второй элемент — это пусть будет следующий за головой элемент

	List<HaffmansTree*>::Node *temp = new List<HaffmansTree*>::Node;              //Временное звено для хранения переставляемого всех значений переставляемого звена

	while (left->next) {                 //Обходим по всем звеньям, за исключением крайнего правого
		while (right) {              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
			if ((left->data->CurrentElementsSumm) >= (right->data->CurrentElementsSumm)) {        //Проверяем необходимость перестановки
				swap(left->data, right->data);
			}
			right = right->next;                    //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
		}
		left = left->next;                              //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
		right = left->next;                             //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад, это следующий элемент относительно текущего первого
	}
}

void CreateTreeHaffman(List<HaffmansTree*>& tree)
{
	while (tree.get_size() != 1)
	{
		sortList(tree);

		HaffmansTree* SonLeft = tree.start->data;
		tree.pop_front();
		HaffmansTree* SonRight = tree.start->data;
		tree.pop_front();
		HaffmansTree* parent = new HaffmansTree(SonLeft, SonRight);
		tree.push_back(parent);
	}
}

void CreateMapOfHaffmanCode(HaffmansTree* root, map<char, bool*>& table, List<bool>& listCode)
{

	if (root->left != nullptr)
	{
		listCode.push_back(false);
		CreateMapOfHaffmanCode(root->left, table, listCode);
	}

	if (root->right != nullptr)
	{
		listCode.push_back(true);
		CreateMapOfHaffmanCode(root->right, table, listCode);
	}

	if (root->left == nullptr && root->right == nullptr)
	{

		table.find(root->symbol)->data.second = new bool[listCode.get_size()];
		for (int i = 0; i < listCode.get_size(); i++)
		{
			table.find(root->symbol)->data.second[i] = listCode.get_pointer(i)->data;
		}

	}

	if (listCode.get_size() == 0)
		return;
	listCode.pop_back();
}

void PrintTable(map<char, bool*>::Tree::Node *root)
{
	int arrSize;
	if (root->data.first != 0)
	{

		PrintTable(root->right);

		cout << root->data.first << " - symbol | code: ";
		arrSize = _msize(root->data.second) / sizeof(root->data.second[0]);
		for (int i = 0; i < arrSize; i++)
		{
			cout << root->data.second[i];
		}
		cout << endl;

		PrintTable(root->left);
	}
}

void Haffman(string str)
{
	map<char, size_t> card;
	map<char, bool*> table;
	int MemoryCounter = 0;
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] != 0)
		{
			card.insert(str[i], i/*не важно*/);
			table.insert(str[i], nullptr);
			++MemoryCounter;
		}
	}
	List<char> list = card.get_keys();
	List<HaffmansTree*> tree;
	while (list.get_size() != 0)
	{
		HaffmansTree* element = new HaffmansTree();
		element->CurrentElementsSumm = list.start->CurrentElementsSumm;
		element->symbol = list.start->data;
		tree.push_back(element);
		list.pop_front();
	}
	cout << "It takes memory:" << MemoryCounter * 8 << " bit." << endl;
	float AspectRatio = (float)1 / MemoryCounter;
	MemoryCounter = 0;
	CreateTreeHaffman(tree);
	HaffmansTree* root = tree.start->data;
	List<bool> listCode;
	int arrSize;
	CreateMapOfHaffmanCode(root,table, listCode);
	cout << "Coded string: " << endl;
	char ch = 'a';
	int i = 0;
	ch = str[i];
	while (ch != 0)
	{
		i++;
		arrSize = _msize(table.find(ch)->data.second) / sizeof(table.find(ch)->data.second[0]);
		MemoryCounter = MemoryCounter + arrSize;
		for (int i = 0; i < arrSize; i++)
			cout << table.find(ch)->data.second[i];
		cout << " ";
		ch = str[i];
	}
	cout << endl;
	cout << "The encoded string takes up memory: " << MemoryCounter << " bit." << endl;
	AspectRatio = AspectRatio * MemoryCounter * 100;
	cout << "AspectRatio = " << (int)AspectRatio << "%" << endl << endl;

	PrintTable(table.tree_of_elements->root);
}

int main()
{
	cout << "Write the line: ";
	string str;
	getline(cin, str);
	Haffman(str);
}
