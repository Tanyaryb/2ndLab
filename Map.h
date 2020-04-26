#pragma once
#include <Windows.h>
#include <exception>
using namespace std;

#define MAP_FUNC_RETURNS_NODE_POINTER map<TKey, TValue>::Tree::Node* map<TKey, TValue>
#define TREE_FUNC_RETURNS_NODE_POINTER map<TKey, TValue>::Tree::Node* map<TKey, TValue>::Tree


typedef enum { BLACK, RED } nodeColor; // к-ч дерево, описание

#define NIL nil 

#pragma region LIST
template <typename T>
class List
{
public:
	class Node
	{
	public:
		Node* next = nullptr;
		T data;
		size_t CurrentElementsSumm;
	};
	Node* end = nullptr;
	Node* current = nullptr;
	Node* start = nullptr;
	void push_back(T element, size_t CurrentElementsSumm = 0)
	{
		if (!end)
		{
			end = start = current = new Node;
			end->data = element;
			end->CurrentElementsSumm = CurrentElementsSumm;
		}
		else
		{
			end->next = new Node;
			end = end->next;
			end->data = element;
			end->CurrentElementsSumm = CurrentElementsSumm;
		}
	}
	void pop_back()
	{
		if (start != end)
		{
			List<T>::Node* temp = start;
			while (temp->next != end)
			{
				temp = temp->next;
			}
			delete temp->next;
			end = temp;
			end->next = nullptr;
		}
		else if (get_size() == 1)
		{
			List<T>::Node* temp = end;
			end = start = NULL;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	List<T>::Node* get_pointer(size_t index)
	{
		if (get_size() == 0 || (index > get_size() - 1))
		{
			throw out_of_range("Invalid argument");
		}
		else if (index == get_size() - 1)
			return end;
		else if (index == 0)
			return start;
		else
		{
			List<T>::Node *temp = start;
			while ((temp) && (index--))
			{
				temp = temp->next;
			}
			return temp;
		}
	}
	void pop_front()
	{
		if (start != end)
		{
			Node* temp = start;
			start = start->next;
			delete temp;
		}
		else if (get_size() == 1)
		{
			Node* temp = start;
			start = end = nullptr;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	size_t get_size()
	{
		Node* temp = start;
		size_t length = 0;
		while (temp)
		{
			length++;
			temp = temp->next;
		}
		return length;
	}
	T next()
	{
		if (current)
		{
			T value = current->data;
			current = current->next;
			return value;
		}
	}
	bool isCurrent() {
		return current ? true : false;
	}
};
#pragma endregion

#pragma region MAP_CLASS
template <typename TKey, typename TValue>
class map {
public:
	class Tree;
	Tree* tree_of_elements;
	map()
	{
		tree_of_elements = new Tree;
	}
	typename Tree::Node* insert(TKey, TValue); // добавление элемента с ключом и значением
	void remove(TKey); // удаление элемента дерева по ключу
	typename Tree::Node* find(TKey);	// поиск элемента
	void clear(); // очищение ассоциативного массива
	List<TKey> get_keys(); // возвращает список ключей
	List<TValue> get_values(); // возвращает список значений
	void print(); // вывод дерева в консоль
};
#pragma endregion

#pragma region RED-BLACK_TREE_CLASS
template <typename TKey, typename TValue>
class map<TKey, TValue>::Tree {
public:
	class Node {
	public:
		Node* right;
		Node* left;
		Node* parent = nullptr;
		pair <TKey, TValue> data;	//pair - объект, который хранит два значения (ключ и значение)	| data.first() - первое значение (ключ), data.second() - второе значение (значение)
		nodeColor color = BLACK;
		size_t CurrentElementsSumm = 1;
	};
	void insertFixup(Node*);
	void deleteFixup(Node*);
	void rotateLeft(Node*);
	void rotateRight(Node*);
	void clear(Node *);
	void get_values(typename Node*, List<TValue>&);
	void get_keys(typename Node *, List<TKey> &);
	void print(Node*, string);
	Node* nil = new Node;
public:
	typename Node* insert(TKey, TValue);
	void deleteNode(Node *);
	Node* find(TKey);
	Node* root = NIL;
};
#pragma endregion

#pragma region FUNCTIONS_OF_MAP_REALIZATION

template <typename TKey, typename TValue>
void map<TKey, TValue>::remove(TKey key)
{
	auto node = find(key);
	if (node == nullptr) throw exception("There is no element in the tree");
	tree_of_elements->deleteNode(node);
}

template <typename TKey, typename TValue>
List<TValue> map<TKey, TValue>::get_values() {
	List<TValue> list;
	tree_of_elements->get_values(tree_of_elements->root, list);
	return list;
}

template <typename TKey, typename TValue>
List<TKey> map<TKey, TValue>::get_keys() {
	List<TKey> list;
	tree_of_elements->get_keys(tree_of_elements->root, list);
	return list;
}

template <typename TKey, typename TValue>
typename MAP_FUNC_RETURNS_NODE_POINTER::insert(TKey key, TValue value)
{
	return tree_of_elements->insert(key,value);
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::print()
{
	tree_of_elements->print(tree_of_elements->root, "");
}

template <typename TKey, typename TValue>
typename MAP_FUNC_RETURNS_NODE_POINTER::find(TKey key)
{
	return tree_of_elements->find(key);
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::clear()
{
	tree_of_elements->clear(tree_of_elements->root);
}

#pragma endregion

#pragma region FUNCTIONS_OF_TREE_REALIZATION

template <typename TKey, typename TValue>
void map<TKey, TValue>::Tree::deleteFixup(Node* node) 
{

	while (node != root && node->color == BLACK) {
		if (node == node->parent->left) 
		{
			Node* brother = node->parent->right;
			if (brother->color == RED) 
			{
				brother->color = BLACK;
				node->parent->color = RED;
				rotateLeft(node->parent);
				brother = node->parent->right;
			}
			if (brother->left->color == BLACK && brother->right->color == BLACK) 
			{
				brother->color = RED;
				node = node->parent;
			}
			else 
			{
				if (brother->right->color == BLACK) 
				{
					brother->left->color = BLACK;
					brother->color = RED;
					rotateRight(brother);
					brother = node->parent->right;
				}
				brother->color = node->parent->color;
				node->parent->color = BLACK;
				brother->right->color = BLACK;
				rotateLeft(node->parent);
				node = root;
			}
		}
		else 
		{
			Node* brother = node->parent->left;
			if (brother->color == RED) 
			{
				brother->color = BLACK;
				node->parent->color = RED;
				rotateRight(node->parent);
				brother = node->parent->left;
			}
			if (brother->right->color == BLACK && brother->left->color == BLACK) 
			{
				brother->color = RED;
				node = node->parent;
			}
			else 
			{
				if (brother->left->color == BLACK) 
				{
					brother->right->color = BLACK;
					brother->color = RED;
					rotateLeft(brother);
					brother = node->parent->left;
				}
				brother->color = node->parent->color;
				node->parent->color = BLACK;
				brother->left->color = BLACK;
				rotateRight(node->parent);
				node = root;
			}
		}
	}
	node->color = BLACK;
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::Tree::deleteNode(Node* node) {
	Node *childOfDeleteElement, *willDelete;

	if (!node || node == NIL) return;

	if (node->left == NIL || node->right == NIL) {
		willDelete = node;
	}
	else {
		willDelete = node->right;
		while (willDelete->left != NIL) willDelete = willDelete->left;
	}

	if (willDelete->left != NIL)
		childOfDeleteElement = willDelete->left;
	else
		childOfDeleteElement = willDelete->right;

	childOfDeleteElement->parent = willDelete->parent;
	if (willDelete->parent)
		if (willDelete == willDelete->parent->left)
			willDelete->parent->left = childOfDeleteElement;
		else
			willDelete->parent->right = childOfDeleteElement;
	else
		root = childOfDeleteElement;

	if (willDelete != node) node->data = willDelete->data;

	if (willDelete->color == BLACK)
		deleteFixup(childOfDeleteElement);

	delete willDelete;
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::Tree::get_keys(typename Tree::Node* node, List<TKey>& list)
{
	if (root == NIL || node == NIL) return;
	if (node->left) get_keys(node->left, list);
	if (node->right) get_keys(node->right, list);
	list.push_back(node->data.first, node->CurrentElementsSumm);
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::Tree::get_values(typename Tree::Node* node, List<TValue>& list)
{
	if (root == NIL) return;
	if (node->left) get_values(node->left, list);
	if (node->right) get_values(node->right, list);
	list.push_back(node->data.second, node->CurrentElementsSumm);
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::Tree::clear(typename Tree::Node* node)
{
	if (node->left != NIL) clear(node->left);
	if (node->right != NIL) clear(node->right);
	if (node == root) root = NIL;
	delete node;
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::Tree::print(typename Tree::Node* root, string str)
{
	if (root == NIL) return;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (root == this->root)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "> (" << root->data.first << " | " << root->data.second << ")" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		str += " ";
	}
	if (root->right != NIL) {
		string _str = str;
		cout << _str;
		if (root->right->color == BLACK)
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		else SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "R> (" << root->right->data.first << " | " << root->right->data.second << ")" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		_str += "| ";
		print(root->right, _str);
	}
	else if (root->left != NIL) {
		cout << str;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "R> (-)" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	}
	if (root->left != NIL) {
		string _str = str;
		cout << _str;
		if (root->left->color == BLACK)
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		else SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "L> (" << root->left->data.first << " | " << root->left->data.second << ")" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		_str += "  ";
		print(root->left, _str);
	}
	else if (root->right != NIL) {
		cout << str;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "L> (-)" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	}
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::Tree::rotateLeft(Node* node)
{

	// перемещение node right влево
	Node* rightSon = node->right;

	/* установление связи node right */
	node->right = rightSon->left;
	if (rightSon->left != NIL) rightSon->left->parent = node;

	/* установление связи rightSon parent */
	if (rightSon != NIL) rightSon->parent = node->parent;
	if (node->parent) {
		if (node == node->parent->left)
			node->parent->left = rightSon;
		else
			node->parent->right = rightSon;
	}
	else {
		root = rightSon;
	}

	/* связывание rightSon и node*/
	rightSon->left = node;
	if (node != NIL) node->parent = rightSon;
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::Tree::rotateRight(Node* node) {
	Node* leftSon = node->left;

	/* установление связи node left  */
	node->left = leftSon->right;
	if (leftSon->right != NIL) leftSon->right->parent = node;

	/* установление связи leftSon parent  */
	if (leftSon != NIL) leftSon->parent = node->parent;
	if (node->parent) {
		if (node == node->parent->right)
			node->parent->right = leftSon;
		else
			node->parent->left = leftSon;
	}
	else {
		root = leftSon;
	}

	/* связывание leftSon и node */
	leftSon->right = node;
	if (node != NIL) node->parent = leftSon;
}

template <typename TKey, typename TValue>
typename TREE_FUNC_RETURNS_NODE_POINTER::find(TKey key)
{
	Node* current = root;
	while (current != NIL)
		if (key == current->data.first)
			return current;
		else
		{
			current = key < current->data.first ? current->left : current->right;
		}
	return nullptr;
}

template <typename TKey, typename TValue>
void map<TKey, TValue>::
	Tree::insertFixup(Node* node)
{
	/* проверка к-ч свойств, если есть нарушение, то надо восстанавливать к-ч дерево */
	while (node != root && node->parent->color == RED) {
		/* нарушение */
		if (node->parent == node->parent->parent->left) {
			Node* uncle = node->parent->parent->right;
			if (uncle->color == RED) {

				/* uncle - красный */
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {

				/* uncle - черный */
				if (node == node->parent->right) {
					/* поворот узла влево*/
					node = node->parent;
					rotateLeft(node);
				}

				/* перекрашиваем и поворачиваем вправо */
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotateRight(node->parent->parent);
			}
		}
		else {

			/* тоже самое, что и выше */
			Node* uncle = node->parent->parent->left;
			if (uncle->color == RED) {

				/* uncle - красный */
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {

				/* uncle - черный */
				if (node == node->parent->left) {
					node = node->parent;
					rotateRight(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotateLeft(node->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

template <typename TKey, typename TValue>
typename TREE_FUNC_RETURNS_NODE_POINTER::insert(TKey key, TValue value)
{
	Node *current, *newNode, *parent;
	current = root;
	parent = 0;
	while (current != NIL) {
		if (key == current->data.first)
		{
			current->CurrentElementsSumm++;
			return current;
		}
		parent = current;
		current = key < current->data.first ? current->left : current->right;
	}

	/* создание нового узла */
	newNode = new Node;
	newNode->data = make_pair(key, value);
	newNode->parent = parent;
	newNode->left = NIL;
	newNode->right = NIL;
	newNode->color = RED;

	/* вставка узла в дерево */
	if (parent) {
		if (key < parent->data.first)
			parent->left = newNode;
		else
			parent->right = newNode;
	}
	else {
		root = newNode;
	}

	insertFixup(newNode);
	return newNode;
}
#pragma endregion
