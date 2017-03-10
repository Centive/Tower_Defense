#include "stdafx.h"
#include "CppUnitTest.h"

#include <Engine.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTest
{
	class Foo
	{
	public:
		Foo()
			: num(0xfeedf00d)
		{
			++counter;
		}

		~Foo()
		{
			--counter;
		}

		static s32 counter;
		u32 num;
	};

	s32 Foo::counter = 0;
	
	typedef BlockAllocator<Foo> Foolocator;
	typedef Handle<Foo> Foodle;

	TEST_CLASS(MemoryTest)
	{
	public:
		TEST_METHOD(AllocationTest)
		{
			Foolocator allocator(1);

			Foodle a = allocator.New();
			Assert::IsTrue(a.IsValid());
			Assert::IsTrue(a.GetIndex() == 0);
			Assert::IsTrue(a.GetGeneration() == 0);
			
			Foodle b = allocator.New();
			Assert::IsFalse(b.IsValid());
		}

		TEST_METHOD(DeallocationTest)
		{
			Foolocator allocator(1);

			Foodle a = allocator.New();
			Assert::IsTrue(a.IsValid());
			Assert::IsTrue(a.GetIndex() == 0);
			Assert::IsTrue(a.GetGeneration() == 0);
			
			Foodle b = allocator.New();
			Assert::IsFalse(b.IsValid());

			allocator.Delete(a);
			
			Foodle c = allocator.New();
			Assert::IsTrue(c.IsValid());
			Assert::IsTrue(c.GetIndex() == 0);
			Assert::IsTrue(c.GetGeneration() == 1);
		}

		TEST_METHOD(RecycleTest)
		{
			Foolocator allocator(5);

			Foodle f0 = allocator.New();
			Foodle f1 = allocator.New();
			Foodle f2 = allocator.New();
			Assert::IsTrue(
				f0.IsValid() &&
				f1.IsValid() &&
				f2.IsValid() &&
				f0.GetIndex() == 0 &&
				f1.GetIndex() == 1 &&
				f2.GetIndex() == 2 &&
				f0.GetGeneration() == 0 &&
				f1.GetGeneration() == 0 &&
				f2.GetGeneration() == 0);
			
			// freeslot = 3
			allocator.Delete(f0);
			// freeslot = 0
			allocator.Delete(f1);
			// freeslot = 1
			allocator.Delete(f2);
			// freeslot = 2

			Foodle f3 = allocator.New();
			Foodle f4 = allocator.New();
			Foodle f5 = allocator.New();
			Assert::IsTrue(
				f3.IsValid() &&
				f4.IsValid() &&
				f5.IsValid() &&
				f3.GetIndex() == 2 &&
				f4.GetIndex() == 1 &&
				f5.GetIndex() == 0 &&
				f3.GetGeneration() == 1 &&
				f4.GetGeneration() == 1 &&
				f5.GetGeneration() == 1);
			
			Foodle f6 = allocator.New();
			Assert::IsTrue(f6.IsValid());
			Assert::IsTrue(f6.GetIndex() == 3);
			Assert::IsTrue(f6.GetGeneration() == 0);
		}

		TEST_METHOD(ConstructionTest)
		{
			Foolocator allocator(5);

			Foodle a = allocator.New();
			Foo* foo = a.Get();
			Assert::IsTrue(foo != nullptr);
			Assert::IsTrue(foo->num == 0xfeedf00d);
		}

		TEST_METHOD(DestructionTest)
		{
			Foolocator allocator(5);

			Foo::counter = 0;
			
			Foodle a = allocator.New();
			Assert::IsTrue(Foo::counter == 1);
			
			Foodle b = allocator.New();
			Assert::IsTrue(Foo::counter == 2);

			Foodle c = allocator.New();
			Assert::IsTrue(Foo::counter == 3);

			allocator.Delete(a);
			Assert::IsTrue(Foo::counter == 2);

			allocator.Delete(b);
			Assert::IsTrue(Foo::counter == 1);

			allocator.Delete(c);
			Assert::IsTrue(Foo::counter == 0);
		}
	};
}