#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <coroutine>
#include <array>
// 오늘의 주제 : Non-Type Template Parameter

// 일방적으로 템플릿을 사용할 때,
// 어떤 타입에 대응해서 치환을 하게끔 설정했는데
// 경우에 따라서 지정된 타입(int 등)으로도 사용했었다.
// 그래서 Non-Type에 대해서만 들어갔었는데, C++20로 넘어오면서 추가된 것들이 생겼다.
// 보다보면 약간 흑마법같은 기능.

// Non-Type
// - int, enum
// - 포인터, 참조값
// - nullptr_t

// C++20 에서 추가된 것
// - 부동소수점 (floating-point)
// - Literal Type (types of constexpr variables)
// - String Literal

// int나 enum같은 정수만 지원됐었는데, 부동소수점까지 지원하게 됐다.
template<double d>
auto GetDouble()
{
	return d;
}

// 거의 리터럴 타입.
// constexpr을 이용해서 거의 상수처럼 고정을 해서 만든 것.
// 기존에 사용하던 클래스나 구조체 경우는 객체로 사용하기 위한 설계도였는데,
// 이것은 정수 하나를 일종의 타입으로 만들기위한 꼼수를 이용한 것.
struct ClassType
{
	// constexpr을 넣어줌으로써, 컴파일 타임에 생성자도 확정이 되어 만들어질 수 있다.
	// 그래서 밑에 메인함수에 2021 같은 상수도 들어간 것.
	constexpr ClassType(int) { }
};

// 이것도 정수를 타입처럼 만들기 위해 구조체를 만든 것.
template<int N>
struct IntToType
{
	enum { value = N };
};

template<ClassType c>
auto GetClassType()
{
	return c;
}

template<int N>
class StringLiteral
{
public:
	constexpr StringLiteral(char const (&str)[N])
	{
		std::copy(str, str + N, _data);
	}

	char _data[N];
};

template<StringLiteral str>
class ClassTemplate { };

template<StringLiteral str>
void FunctionTemplate()
{
	cout << str._data << endl;
}

int main()
{
	auto d1 = GetDouble<5.5>();
	auto c1 = GetClassType<ClassType(2021)>(); // 넣어주는 정수에 따라 타입 자체가 완전히 달라진다.

	// 두 개도 정수지만, 완전히 다른 타입인 셈. (마치 개와 고양이)
	IntToType<2>();
	IntToType<3>();

	// 템플릿 문법 안에서는 어떤 클래스 타입만 넣어줬지만, 정수뿐만 아니라 문자열도 넣어줄 수 있다.
	ClassTemplate<"Hello World"> cls1;
	FunctionTemplate<"Hello World">();

	// 근데 이런걸 왜 씀?
	// ex) Compile-Time Regular Expression (정규 표현식)
	// 정규 표현식이란 건 어떤 문자열(s*1^sdfsd)의 형태를 만든다면, 그 표현식에 부합하는지 안하는지 이용해서 패턴 매칭을 해주는 것.
	// 정규 표현식 계산을 하고 싶을때, 정규 표현식을 std::regex 란 걸 이용해서 만드는데, regex는 런타임에서만 동작한다.
	// 정규 표현식 패턴을 미리 컴파일 타임에 안다면, 굳이 런타임까지 갈 필요 없음.
	
	// 그래서 기존 방식을 이용할 수 없었지만, 
	// 위에 새로운 문법을 이용해서 클래스를 타입화 한 것처럼
	// 최대한 컴파일 타임에 해결할 수 있는 수단이 된다는 게 힌트.
	// 그럼에도 거의 잘 사용할 일이 없을듯. (그래서 흑마법이라 한 것)
}