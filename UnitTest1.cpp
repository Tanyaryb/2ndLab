#include "CppUnitTest.h"
#include "../ConsoleApplication9/map.h"
#include "../ConsoleApplication9/lab2.cpp"
#include <stdexcept>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab1Tests
{
	TEST_CLASS(Lab1Tests)
	{
	public:
		TEST_METHOD(find_test)
		{
			map<int, int> card;
			bool before = card.find(5);
			card.insert(5, 1);
			bool after = card.find(5);
			Assert::AreEqual(!before, after);
		}
		TEST_METHOD(insert_test)
		{
			map<int, int> card;
			bool before = card.find(5);
			card.insert(5, 1);
			bool after = card.find(5);
			Assert::AreEqual(!before, after);
		}
		TEST_METHOD(remove_test)
		{
			map<int, int> card;
			card.insert(5, 1);
			bool before = card.find(5);
			card.remove(5);
			bool after = card.find(5);
			Assert::AreEqual(before, !after);
		}
		TEST_METHOD(clear_test)
		{
			map<int, int> card;
			card.insert(5, 1);
			card.insert(6, 2);
			card.clear();
			bool findTwoElements;
			if (card.find(5) == nullptr && card.find(6) == nullptr) findTwoElements = false;
			Assert::IsFalse(findTwoElements);
		}
		TEST_METHOD(get_keys_test)
		{
			map<int, int> card;
			card.insert(12, 1);
			card.insert(2, 2);
			card.insert(7, 3);
			List<int> list = card.get_keys();
			int sum_of_keys = 0;
			while (list.isCurrent())
				sum_of_keys += list.next();
			Assert::IsTrue(sum_of_keys == 21);
		}
		TEST_METHOD(get_values_test)
		{
			map<int, int> card;
			card.insert(12, 1);
			card.insert(6, 2);
			card.insert(7, 3);
			List<int> list = card.get_values();
			int sum_of_values = 0;
			while (list.isCurrent())
				sum_of_values += list.next();
			Assert::IsTrue(sum_of_values == 6);
		}
		TEST_METHOD(sort_List_test)
		{
			List<HaffmansTree*> list;
			HaffmansTree* CurrentElementsSumm = new HaffmansTree;
			CurrentElementsSumm->symbol = 'a';
			CurrentElementsSumm->CurrentElementsSumm = 19;
			HaffmansTree* b = new HaffmansTree;
			b->symbol = 'b';
			b->CurrentElementsSumm = 7;
			HaffmansTree* symbol = new HaffmansTree;
			symbol->symbol = 'c';
			symbol->CurrentElementsSumm = 24;
			list.push_back(symbol);
			list.push_back(b);
			list.push_back(CurrentElementsSumm);
			sortList(list);
			Assert::AreEqual(list.get_pointer(0)->data->symbol, 'b');
			Assert::AreEqual(list.get_pointer(1)->data->symbol, 'a');
			Assert::AreEqual(list.get_pointer(2)->data->symbol, 'c');
		}
		TEST_METHOD(CreateTreeHaffman_test)
		{
			List<HaffmansTree*> list;
			HaffmansTree* CurrentElementsSumm = new HaffmansTree;
			CurrentElementsSumm->symbol = 'a';
			CurrentElementsSumm->CurrentElementsSumm = 19;
			HaffmansTree* b = new HaffmansTree;
			b->symbol = 'b';
			b->CurrentElementsSumm = 7;
			HaffmansTree* symbol = new HaffmansTree;
			symbol->symbol = 'c';
			symbol->CurrentElementsSumm = 24;
			list.push_back(symbol);
			list.push_back(b);
			list.push_back(CurrentElementsSumm);
			CreateTreeHaffman(list);
			Assert::AreEqual(list.start->data->left->symbol, 'c');
			Assert::AreEqual(list.start->data->right->left->symbol, 'b');
			Assert::AreEqual(list.start->data->right->right->symbol, 'a');

		}
		TEST_METHOD(CreateMapOfHaffmanCode_test)
		{
			List<HaffmansTree*> list;
			HaffmansTree* CurrentElementsSumm = new HaffmansTree;
			CurrentElementsSumm->symbol = 'a';
			CurrentElementsSumm->CurrentElementsSumm = 19;
			HaffmansTree* b = new HaffmansTree;
			b->symbol = 'b';
			b->CurrentElementsSumm = 7;
			HaffmansTree* symbol = new HaffmansTree;
			symbol->symbol = 'c';
			symbol->CurrentElementsSumm = 24;
			list.push_back(symbol);
			list.push_back(b);
			list.push_back(CurrentElementsSumm);
			CreateTreeHaffman(list);
			HaffmansTree* root = list.start->data;
			List<bool> listCode;
			map<char, bool*> table;
			table.insert('a', nullptr);
			table.insert('b', nullptr);
			table.insert('c', nullptr);
			CreateMapOfHaffmanCode(root, table, listCode);
			Assert::AreEqual(table.find('c')->data.second[0], false);
			Assert::AreEqual(table.find('b')->data.second[0], true);
			Assert::AreEqual(table.find('b')->data.second[1], false);
			Assert::AreEqual(table.find('a')->data.second[0], true);
			Assert::AreEqual(table.find('a')->data.second[1], true);


		}
	};
}
