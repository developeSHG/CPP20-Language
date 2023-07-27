#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <coroutine>

// 오늘의 주제 : Conditionally Explicit Constructor (조건부 Explicit 생성자)

struct A
{
	A() = default;
	A(int n)
	{
		cout << n << endl;
	}
};

void TestA(A a)
{

}

struct B
{
	template<typename T>
	B(T t)
	{

	}
};

void TestB(B b)
{

}

struct C
{
	// 조건부 Explicit
	// - bool에 의한 간접 변환(implicit Conversion)은 허용
	// - 그 외에는 Explicit 
	template<typename T>
	explicit(!std::is_same<T, bool>::value) C(T t)
	{
		cout << typeid(t).name() << endl;
	}
};

void TestC(C c)
{

}

int main()
{
	{
		A a;
		TestA(a);
		TestA(10); // 컴파일 에러없이 통과된다. 이상하다
		// 왜그렇냐면 C++ 특성상 함수에서 A를 받아주고 있지만,
		// 생성자들 중에서 정수를 받아주는 생성자가 있기 때문에,
		// 간접적으로 임시 객체를 만들어 그 생성자를 호출한 다음에,
		// 넘겨주고 있는 것이다.

		// 사실상 이런 코드를 넘겨주고 있는 셈
		{
			A a2(10);
			TestA(a2);
		}

		// 하지만 내가 의도한 것이 아니기 때문에, 마음대로 허용해주고 싶지 않게 하면
		// 이때 붙일 수 있는 키워드가 explicit(명시적) 이다.
		// 간접적으로 호출되고 변환해주는 것을 막는 기능이다.

		// explicit : 원하지 않은 형변환이 일어나지 않도록 제한!
		// explicit A(int n)
	}


	{
		// 위에 까진 C++20 이전에도 있었던 기능이였다.
		// 새로 추가된 기능으로 예제를 살펴보면
		// B의 경우는 템플릿으로 모든 타입에 대해 허용하고 있다.
		B b1 = 2002;
		TestB(b1);
		TestB(2002);
		TestB("Hello World");

		// 간접적으로 임시 객체를 만들어 변환해주고 있다.
		// 그럼 A와 동일하게 explicit로 선언해주게 되면??
		B b1 = 2002;
		TestB(b1);
		TestB(2002); // 컴파일 에러
		TestB("Hello World"); // 컴파일 에러


		// 의도한 대로 당연히 b객체만 허용할 수 있게 된다.
		// 근데 만약 거꾸로 모든 애들을 막아주고 싶었던 것은 아니고,
		// bool 형태는 허용하게 해주고 싶다거나, 조건부적으로 explicit 키워드를 붙이고 싶다하면
		// 추가된 문법인 Conditionally Explicit Constructor 개념을 사용하면 된다.
		C c1 = true;
		TestC(c1);
		TestC(true);
	}

}