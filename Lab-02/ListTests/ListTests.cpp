#include <list>
#include <vector>
#include "CppUnitTest.h"
#include "my_list.h"


namespace ListTests { class SimpleElem; }
namespace ListTests { class NoCopyElem; }

//  Для того, чтобы выполнить тестирование одного из указанных контейнеров (std::list или MyList),
//  должна быть раскомментирована одна из следующих строк:
//template<typename T> using ContainerTemplate = std::list<T>;
template<typename T> using ContainerTemplate = MyList<T>;

//; ____________________________ ТОЖЕ ВАЖНО!!! ____________________________;
// Для проверки бонусного задания необходимо заменить SimpleElem на NoCopyElem
using Elem = ListTests::SimpleElem;
//using Elem = ListTests::NoCopyElem;


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListTests
{
	class SimpleElem {
		uint32_t watch;
		int data;
		static size_t elem_counter;
		void check() const { Assert::IsTrue(watch == 0xDEADBEEF, L"Повреждение памяти!! (Обращение к неинициализированному экземпляру класса SimpleElem)"); }
	public:
		SimpleElem(const SimpleElem& e) : data(e.data), watch(e.watch) { e.check(); ++elem_counter; }
		SimpleElem& operator=(const SimpleElem& e) { e.check();  data = e.data; watch = e.watch; }
		explicit SimpleElem(int value) : data(value), watch(0xDEADBEEF) { ++elem_counter; }
		SimpleElem(SimpleElem&& e) noexcept { e.check(); data = e.data; watch = e.watch; ++elem_counter; }
		SimpleElem& operator=(SimpleElem&& e) noexcept { check(); e.check(); data = e.data; watch = e.watch; }
		bool operator==(const SimpleElem& e) const { check(); e.check(); return data == e.data; }
		~SimpleElem() { check(); watch = 0; --elem_counter; }
		static size_t count() { return elem_counter; }
	};
	size_t SimpleElem::elem_counter = 0;

	class NoCopyElem {
		uint32_t watch;
		int data;
		static size_t elem_counter;
		void check() const { Assert::IsTrue(watch == 0xDEADDEAD, L"Повреждение памяти!! (Обращение к неинициализированному экземпляру класса NoCopyElem)"); }
	public:
		NoCopyElem(const NoCopyElem& e) = delete;
		NoCopyElem& operator=(const NoCopyElem& e) = delete;
		explicit NoCopyElem(int value) : data(value), watch(0xDEADDEAD) { ++elem_counter; }
		NoCopyElem(NoCopyElem&& e) noexcept { e.check(); data = e.data; watch = e.watch; ++elem_counter; }
		NoCopyElem& operator=(NoCopyElem&& e) noexcept { check(); e.check(); data = e.data; watch = e.watch; }
		bool operator==(const NoCopyElem& e) const { check(); e.check(); return data == e.data; }
		~NoCopyElem() { check(); watch = 0; --elem_counter; }
		static size_t count() { return elem_counter; }
	};
	size_t NoCopyElem::elem_counter = 0;


	TEST_CLASS(ComplexTypeTests)
	{

	public:

		TEST_METHOD(IteratorTests)
		{
			ContainerTemplate<int> list{ 3, 4, 8, 5, 2, 13, 20 };
			list.push_back(10);
			Assert::IsTrue(list.end() == ++--list.end(), L"++--list.end() должен возвращать list.end()");
			Assert::AreEqual(10, *(--list.end()), L"--list.end() должен возвращать последний элемент");
		}

		TEST_METHOD(StringTests)
		{
			ContainerTemplate<std::string> list{ "123", "AAAAAAAA", "abc", "cde" };
			std::vector<std::string> expected1{ "123", "AAAAAAAA", "abc", "cde" };

			Assert::AreEqual(std::size_t(4), list.size(), L"Неправильно считается количество строковых элементов");
			Assert::IsTrue(std::equal(list.begin(), list.end(), expected1.begin(), expected1.end()), L"Неправильный порядок строковых элементов");
			Assert::IsTrue(std::equal(list.rbegin(), list.rend(), expected1.rbegin(), expected1.rend()), L"Неправильный порядок строковых элементов");

			for (const auto& str : expected1)
				list.erase(std::find(list.begin(), list.end(), str));

			Assert::AreEqual(std::size_t(0), list.size(), L"Список не пуст после удаления всех элементов");
			for (const auto& elem : list)
				Assert::Fail(L"Что-то лежит в списке после удаления всех элементов");

			list.push_back("test-1");
			list.push_back("test-2");
			list.push_back("test-4");
			std::vector<std::string> expected2{ "test-1", "test-2", "test-4" };
			Assert::IsTrue(std::equal(list.begin(), list.end(), expected2.begin(), expected2.end()), L"Неправильный порядок строковых элементов");
			Assert::IsTrue(std::equal(list.rbegin(), list.rend(), expected2.rbegin(), expected2.rend()), L"Неправильный порядок строковых элементов");
		}

		TEST_METHOD(ElemTests)
		{
			size_t init_count = Elem::count();
			{
				ContainerTemplate<Elem> list;
				Assert::AreEqual(std::size_t(0), Elem::count() - init_count, L"Создан лишний экземпляр класса Elem");

				for (const auto& elem : list)
					Assert::Fail(L"Что-то лежит в пустом списке");

				list.push_back(Elem(40));
				list.push_back(Elem(75));
				list.push_front(Elem(50));
				list.push_back(Elem(23));
				list.push_back(Elem(87));
				Assert::IsTrue(Elem::count() - init_count == 5, L"Создан лишний экземпляр класса Elem");

				auto find_result = std::find(list.begin(), list.end(), Elem(75));
				Assert::IsTrue(find_result != list.end(), L"Не найден элемент со значением 75");
				Assert::IsTrue(*find_result == Elem(75), L"Неправильно найден элемент со значением 75");

				list.erase(find_result);
				Assert::IsTrue(Elem::count() - init_count == 4, L"Неправильно работает удаление элементов списка");
			}
			Assert::IsTrue(Elem::count() - init_count == 0, L"Утечка памяти!!");
		}

		TEST_METHOD(CopyElemTests)
		{
			size_t init_count = Elem::count();
			{
				ContainerTemplate<Elem> list;
				{
					ContainerTemplate<Elem> list1;
					ContainerTemplate<Elem> list2(std::move(list1));
					for (const auto& elem : list2)
						Assert::Fail(L"Что-то лежит в пустом списке после копирования");

					list2.push_back(Elem(40));
					list2.push_front(Elem(50));
					list2.push_back(Elem(23));
					list2.push_back(Elem(87));
					Assert::IsTrue(Elem::count() - init_count == 4, L"Неправильно работает удаление элементов списка");
					list = std::move(list2);
				}
				Assert::IsTrue(list.back() == Elem(87), L"Неправильно работает копирование списка");
				Assert::IsTrue(Elem::count() - init_count == 4, L"Неправильно работает удаление элементов списка");
			}
			Assert::IsTrue(Elem::count() - init_count == 0, L"Утечка памяти!!");
		}

		TEST_METHOD(TestCountOfEvenElem) {
			//1
			ContainerTemplate<int> list1{ 1,1,1,1,1,12,2,3,4,3,5,4,5,6,6,7,8,6,5,4,3,2,42,4 };
			Assert::IsTrue(list1.countOfEvenElem() == 12, L"Неправильно посчитано кол-во четных элементов!");

			ContainerTemplate<int> list2{ 33,33,1,3,2,2,2,2,2,2,2,2,2,3,3,1,3,13,12,4123,4123 };
			Assert::IsTrue(list2.countOfEvenElem() == 10, L"Неправильно посчитано кол-во четных элементов!");

			ContainerTemplate<int> list3{ 2 };
			Assert::IsTrue(list3.countOfEvenElem() == 1, L"Неправильно посчитано кол-во четных элементов!");
		}

		TEST_METHOD(TestFindMaxElemAndCountItEntry){
			ContainerTemplate<int> list1{ 1,1,1,1,1,12,2,3,4,3,5,4,5,6,6,7,8,6,5,4,3,2,42,4 };
			Assert::IsTrue(list1.findMaxElemAndCountItEntry().first == 42 && list1.findMaxElemAndCountItEntry().second == 1,
				L"Не найден правильный максимум или кол-во его вхождений");

			ContainerTemplate<int> list2{ 33,33,1,3,2,2,2,2,2,2,2,2,2,3,3,1,3,13,12,4123,4123 };
			Assert::IsTrue(list2.findMaxElemAndCountItEntry().first == 4123 && list2.findMaxElemAndCountItEntry().second == 2,
				L"Не найден правильный максимум или кол-во его вхождений");

			ContainerTemplate<int> list3{ 2 };
			Assert::IsTrue(list3.findMaxElemAndCountItEntry().first == 2 && list3.findMaxElemAndCountItEntry().second == 1,
				L"Не найден правильный максимум или кол-во его вхождений");
		}
		
		TEST_METHOD(TestSplitList) {
			ContainerTemplate<int> list_4{ 1,2,3,-1,-2,-3 };
			std::pair<ContainerTemplate<int>, ContainerTemplate<int>> pair = list_4.splitList();
			Assert::IsTrue(*pair.first.begin() == -1 && *pair.first.rbegin() == -3, L"Неправильное разделение");
			Assert::IsTrue(*pair.second.begin() == 1 && *pair.second.rbegin() == 3, L"Неправильное разделение");

			ContainerTemplate<int> list_5{ 123,123,123,123,3,-1,123,0, 2,-5,-7 };
			std::pair<ContainerTemplate<int>, ContainerTemplate<int>> pair_1 = list_5.splitList();
			Assert::IsTrue(*pair_1.first.begin() == -1 && *pair_1.first.rbegin() == -7, L"Неправильное разделение");
			Assert::IsTrue(*pair_1.second.begin() == 123 && *pair_1.second.rbegin() == 2, L"Неправильное разделение");

			ContainerTemplate<int> list_6{ 1,1,1,1,-1234567,123,13,3,3,3,123123123 };
			std::pair<ContainerTemplate<int>, ContainerTemplate<int>> pair_2 = list_6.splitList();
			Assert::IsTrue(*pair_2.first.begin() == -1234567 && *pair_2.first.rbegin() == -1234567, L"Неправильное разделение");
			Assert::IsTrue(*pair_2.second.begin() == 1 && *pair_2.second.rbegin() == 123123123, L"Неправильное разделение");
		}

		TEST_METHOD(Test_reverse_custom) {
			ContainerTemplate<int> list_7{ 1,2,3,-1,-2,-3 };
			list_7.reverse_custom();
			std::pair<ContainerTemplate<int>, ContainerTemplate<int>> pair_4 = list_7.splitList();
			Assert::IsTrue(*pair_4.first.begin() == -3 && *pair_4.first.rbegin() == -1, L"Неправильное разделение");
			Assert::IsTrue(*pair_4.second.begin() == 3 && *pair_4.second.rbegin() == 1, L"Неправильное разделение");

			ContainerTemplate<int> list_8{ 123,123,123,123,3,-1,123,0, 2,-5,-7 };
			list_8.reverse_custom();
			std::pair<ContainerTemplate<int>, ContainerTemplate<int>> pair_5 = list_8.splitList();
			Assert::IsTrue(*pair_5.first.begin() == -7 && *pair_5.first.rbegin() == -1, L"Неправильное разделение");
			Assert::IsTrue(*pair_5.second.begin() == 2 && *pair_5.second.rbegin() == 123, L"Неправильное разделение");

			ContainerTemplate<int> list_9{ 1,1,1,1,-1234567,123,13,3,3,3,123123123 };
			list_9.reverse_custom();
			std::pair<ContainerTemplate<int>, ContainerTemplate<int>> pair_6 = list_9.splitList();
			Assert::IsTrue(*pair_6.first.begin() == -1234567 && *pair_6.first.rbegin() == -1234567, L"Неправильное разделение");
			Assert::IsTrue(*pair_6.second.begin() == 123123123 && *pair_6.second.rbegin() == 1, L"Неправильное разделение");
		}
	};
}
