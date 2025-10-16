// Knapecz, Adam - 1DAE11
#include "Time.h"
#include "Square.h"
#include "Container.h"

#include <string>
#include <iostream>

class Container;
void TestSquares();
void CompareTimes(const Time* t1, const Time* t2);
void PrintInstancesCntr(const std::string& message);
void TestContainer();
void PrintContainer(const Container* c);

int main()
{
	// TestSquares();

	/*
	const Time* t1{ new Time{1, 2, 3} };
	const Time* t2{ new Time{1, 1, 1} };
	CompareTimes(t1, t1);
	CompareTimes(t1, t2);
	delete t1;
	delete t2;
	*/

	/*
	PrintInstancesCntr("Before creating the Time objects");
	Time* t3{ new Time{1} };
	Time* t4{ new Time{1} };
	PrintInstancesCntr("After creating 2 objects");
	Time* t5{ new Time{3} };
	PrintInstancesCntr("After creating 3 objects");
	delete t3;
	PrintInstancesCntr("After deleting 1 instance");
	delete t4;
	delete t5;
	PrintInstancesCntr("After deleting all instances");
	*/
	TestContainer();
}

void TestSquares()
{
	std::cout << "--> Squares with constructor delegation" << std::endl;
	Square s1{10.0f};
	s1.Print();
	std::cout << std::endl;
	Square s2{20.0f, 30.0f};
	s2.Print();
	std::cout << std::endl;
}

void CompareTimes(const Time* t1, const Time* t2)
{
	const bool a = t1->GetSeconds() == t2->GetSeconds();
	const bool b = t1->GetMinutes() == t2->GetMinutes();
	const bool c = t1->GetHours() == t2->GetHours();

	std::cout << "--> Comparing 2 time objects" << std::endl;
	t1->Print();
	t2->Print();
	std::cout << "They are ";
	if (!(a && b && c))
	{
		std::cout << "not";
	}
	std::cout << " equal" << std::endl;
}

void PrintInstancesCntr(const std::string& message)
{
	std::cout << message << " -> Nr of Time objects: " << Time::GetNrInstances() << std::endl;
}

void TestContainer()
{
	std::cout << "\n-- Container tests --\n";
	// Define a Container object
	const int cap{5};
	std::cout << "Create container with capacity of " << cap << " elements\n";
	Container* pContainer{new Container{cap}};
	PrintContainer(pContainer);

	// Add some values to the container
	int actNr{0};
	std::cout << "\nPush back of " << (cap - 1) << " elements\n";
	for (int idx{1}; idx < cap; ++idx)
	{
		pContainer->PushBack(rand() % 21);
		++actNr;
	}
	PrintContainer(pContainer);

	std::cout << "\nChange the value of the elements (using Set)\n";
	for (int idx{0}; idx < actNr; ++idx)
	{
		pContainer->Set(idx, rand() % 21);
	}
	PrintContainer(pContainer);

	std::cout << "\nPush back another " << (cap - 1) << " elements\n";
	for (int i{1}; i < cap; ++i)
	{
		pContainer->PushBack(rand() % 21);
		++actNr;
	}
	PrintContainer(pContainer);
	delete pContainer;
}

void PrintContainer(const Container* pContainer)
{
	std::cout << "-- Print container --\n";
	std::cout << "   Capacity: " << pContainer->Capacity() << std::endl;
	std::cout << "   Size: " << pContainer->Size() << std::endl;
	std::cout << "   Get the elements (using Get and Size)\n   ";
	for (int idx{0}; idx < pContainer->Size(); ++idx)
	{
		std::cout << pContainer->Get(idx) << " ";
	}
	std::cout << std::endl;
}
