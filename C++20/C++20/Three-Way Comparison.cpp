#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <coroutine>

// 오늘의 주제 : Three-Way Comparison 연산자 (Spaceship Operator <=> )

struct MyInt
{
	MyInt(int value) : _value(value) { }

	// < <= > >= == !=
	// 보통 < 로 연산자 오버로딩을 하면 위의 수식도 필요한게 일반적.
	// 저것을 다 정의하는 것보다, 알아서 자동으로 해줄 수 있게 지원하는 게 Spaceship Operator
	bool operator<(const MyInt& rhs) const { return _value < rhs._value; }

	auto operator<=>(const MyInt& rhs) const = default; // 리턴형 타입을 bool로 하면 에러가 난다. 자동추론하게끔
	// auto operator<=>(const MyInt& rhs) const { return _value <=> rhs._value; } // 어떤 식으로 이루어질지 정의해줄 수 있지만, 간단하게해서 컴파일이 알아서 만들어줄 수 있기에 default

	int _value;
};

struct Strong
{
	std::strong_ordering operator<=>(const Strong&) const = default;
};

struct Weak
{
	std::weak_ordering operator<=>(const Weak&) const = default;
};

struct Partial
{
	std::partial_ordering operator<=>(const Partial&) const = default;
};

struct Test
{
	auto operator<=>(const Test&) const = default;
	// 위의 타입은 자동추론에 의해 partial_ordering 으로 되어있다.
	// 왜그러냐면 밑의 변수들의 타입 strong, weak, partial의 ordering 조건을 모두 만족해야 하는데,
	// 밑에 설명한대로 partial의 비교 조건이 제일 느슨하기 때문에
	// strong은 weak, partial을 포함하고 있고, weak는 partial을 포함하고 있기에
	// strong과 weak를 할 수 없는 제약사항이 있어서 partial_ordering으로 되었다.

	Strong s;
	Weak w;
	Partial p;
};

int main()
{
	{
		MyInt a = 1;
		MyInt b = 2;

		bool test = a < b;
		bool test2 = a > b;
		bool test3 = a <= b;

		// [여기서 이상한 점]
		// <=> 연산자를 사용했지만
		// 만약 value가 한 개가 아닌 여러개가 있다고 가정하면, 
		// 오퍼레이터 연산자가 어떤 변수를 기준으로 했는지 만들어졌는지 모호하다. 
		// 또 bool 타입으로 리턴을 안하고, string_ordering 이라는 타입이 무엇을 하는지 알 수가 없다.

		// ordering 이라는 것이 크게 3가지로 구분할 수 있다.
		// 1. strong ordering
		// 2. weak ordering
		// 3. partial ordering

		// 위의 ordering들의 차이를 알기위해선 비교 특성에 대해 먼저 알고 있어야 한다.
		// 비교 (Relational, Equivalence, Comparable)
		// - 6종 비교 연산 지원 ==, !=, <, <=, >, >= (Relational 조건을 만족)
		// - 모든 Equivalent한 값들은 서로 구분되지 않고 완전 똑같다 (Equivalence 조건을 만족)
		// ex) 대소문자 구별 안하는 문자열 비교 abc Abc
		// - a < b, a == b, a > b 중 하나는 참이다 (Comparable 조건을 만족)
		// ex) float 비교할 때, b가 NaN(not a number)면 3연산이 다 true가 아님.

		// Strong Ordering : Relational(O), Equivalence(O), Comparable(O)
		// Weak Ordering : Relational(O), Comparable(O)
		// Partial Ordering : Relational(O)

		// weak ordering 같은 경우는 C++ 표준에서 사용하는 타입중에서 weak ordering으로 된 경우는 잘 없기 떄문에 직관적이지 않고,
		// 보통 string ordering과 partial ordering이 친숙하고 직관적이다.

		// 다시 위에서 이상한 점을 야기한대로
		// 변수가 여러개 있다고 가정하면, 선언된 순서대로 하나씩 테스트해보게 된다.
	}

	{
		int a1 = 100;
		int b1 = 200;

		auto ret = (a1 <=> b1); // Spaceship Operator 연산자를 사용해 타입이 strong_ordering인 ret 구조체를 할당. 

		// strong_ordering이라는 구조체를 내뱉어줬지만, 부호를 체크해서 추가적으로 어떤 결과물을 의미하는지 알 수가 있다.
		if (ret < 0)
			cout << "a < b" << endl;
		else if (ret == 0)
			cout << "a == b" << endl;
		else if (ret > 0)
			cout << "a > b" << endl;
	}
}