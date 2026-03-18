#include <string>
#include <iostream>
#include <algorithm>

class Item
{
public:
	Item() : name_(""), price_(0) {};
	Item(const std::string& name, int price)
	{
		name_ = name;
		price_ = price;
	}
	const std::string& GetName() const { return name_; }
	int GetPrice() const { return price_; }
	void Clear()
	{
		name_ = "";
		price_ = 0;
	}

private:
	std::string name_;
	int price_;
};

bool CompareItemsByPrice(const Item& a, const Item& b)
{
	return a.GetPrice() < b.GetPrice();
}

template<typename T>
class Inventory
{
public:
	Inventory(int capacity = 10)
	{
		capacity_ = capacity;
		size_ = 0;
		pItems_ = new T[capacity];
	}
	Inventory(const Inventory<T>& item) {
		capacity_ = item.capacity_;
		size_ = item.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = item.pItems_[i];
		}
		std::cout << "인벤토리 복사 완료" << std::endl;
	}
	~Inventory() { delete[] pItems_; }

	void AddItem(const T& item)
	{
		if (size_ >= capacity_)
		{
			//std::cout << "인벤토리가 꽉 찼습니다!" << std::endl;
			//return;
			Resize(capacity_ * 2);
			std::cout << "인벤토리 용량이 " << capacity_ << "으로 증가했습니다." << std::endl;
		}
		pItems_[size_++] = item;
	}
	void RemoveLastItem()
	{
		if (size_ <= 0)
		{
			std::cout << "인벤토리가 비어있습니다." << std::endl;
			return;
		}
		--size_;
		std::cout << "아이템이 삭제되었습니다. [이름 : " << pItems_[size_].GetName() << ", 가격: " << pItems_[size_].GetPrice() << "G]" << std::endl;
	}
	int GetSize() const { return size_; }
	int GetCapacity() const { return capacity_; }
	void PrintAllItems() const
	{
		for (int i = 0; i < size_; i++)
		{
			std::cout << "[이름: " << pItems_[i].GetName() << ", 가격: " << pItems_[i].GetPrice() << "G]" << std::endl;
		}
	}

	// Challenge
	void Assign(const Inventory<T>& other)
	{
		delete[] pItems_;

		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];

		for (int i = 0; i < size_; i++)
		{
			pItems_[i] = other.pItems_[i];
		}
	}
	void Resize(int newCapacity)
	{
		T* pNewItems = new T[newCapacity];

		for (int i = 0; i < size_; ++i)
		{
			pNewItems[i] = pItems_[i];
		}

		delete[] pItems_;
		pItems_ = pNewItems;
		capacity_ = newCapacity;
	}
	void SortItems() { std::sort(pItems_, pItems_ + size_, CompareItemsByPrice); }

private:
	T* pItems_;
	int capacity_;
	int size_;
};

void PrintMenu()
{
	std::cout << "" << std::endl;
	std::cout << "원하시는 작업을 선택해주세요." << std::endl;
	std::cout << " ------------------" << std::endl;
	std::cout << "| 0. 프로그램 종료 |" << std::endl;
	std::cout << "| 1. 인벤토리 추가 |" << std::endl;
	std::cout << "| 2. 인벤토리 삭제 |" << std::endl;
	std::cout << "| 3. 인벤토리 출력 |" << std::endl;
	std::cout << "| 4. 인벤토리 정렬 |" << std::endl;
	std::cout << " ------------------" << std::endl;
}

int InputInt(const std::string& message)
{
	int value = 0;
	std::cout << message;
	while (true)
	{
		std::cin >> value;
		if (!std::cin.fail()) break;
		std::cout << "숫자만 입력해주세요: ";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	return value;
}

void main()
{
	int capacity = 0;
	capacity = InputInt("컨테이너의 크기를 입력해주세요: ");

	if (capacity <= 0)
	{
		capacity = 1;
		std::cout << "최소 용량이 0이 될 수 없습니다. 1이 되도록 자동으로 보정합니다." << std::endl;
	}

	Inventory<Item>* itemInventory = new Inventory<Item>(capacity);

	PrintMenu();

	int keyinput = 0;
	std::string name = "";
	int price = 0;
	while (true)
	{
		std::cin >> keyinput;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}

		if (keyinput == 0) {
			std::cout << "프로그램을 종료합니다." << std::endl;
			break;
		}

		switch (keyinput) {
		case 1:
			std::cout << "아이템 이름을 입력해주세요: ";
			std::cin >> name;
			price = InputInt("가격을 입력해주세요: ");
			itemInventory->AddItem(Item(name, price));
			std::cout << "아이템이 추가되었습니다. [이름 : " << name << ", 가격: " << price << "G]" << std::endl;
			break;
		case 2:
			itemInventory->RemoveLastItem();
			break;
		case 3:
			itemInventory->PrintAllItems();
			break;
		case 4:
			itemInventory->SortItems();
			itemInventory->PrintAllItems();
			std::cout << "아이템이 정렬이 완료되었습니다." << std::endl;
			break;
		default:
			std::cout << "잘못된 입력입니다. 다시 입력해주세요" << std::endl;
			break;
		}
		PrintMenu();
	}

	//Inventory<Item> copiedInventory = *itemInventory;

	delete itemInventory;
	itemInventory = nullptr;
}

//void main()
//{
//	Inventory<Item>* itemInventory = new Inventory<Item>();
//	for (int i = 0; i < 11; ++i)
//	{
//		itemInventory->AddItem(Item("Item" + std::to_string(i), i * 100));
//	}
//
//	itemInventory->PrintAllItems();
//	std::cout << "ItemCapacity : " << itemInventory->GetCapacity() << std::endl;
//
//	itemInventory->Resize(25);
//	for (int i = 0; i < 14; ++i)
//	{
//		itemInventory->AddItem(Item("Item" + std::to_string(i), i * 100));
//	}
//
//	itemInventory->PrintAllItems();
//	std::cout << "ItemCapacity : " << itemInventory->GetCapacity() << std::endl;
//
//	itemInventory->SortItems();
//	itemInventory->PrintAllItems();
//
//	Inventory<Item>* itemInventory2 = new Inventory<Item>(*itemInventory);
//	itemInventory2->PrintAllItems();
//
//	delete itemInventory;
//	delete itemInventory2;
//}