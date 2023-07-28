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

// 오늘의 주제 : Attribute

// 힌트를 줘서 추가적으로 컴파일러가 warning을 잡아주는 기능.
// 컴파일러한테 걸어주는 주석같은 느낌.

// Attribute를 추가로, return이 없다는 시그니쳐를 정의해줄 수 있다.
[[noreturn]]
int Func()
{
	return 10; // warning
}

[[nodiscard]]
int Func2()
{
	return 10; // warning
}

class Knight
{
public:
	// 생성자에서는 nodiscard를 붙일 수 없었는데, C++20에서 추가.
	[[nodiscard("생성자 버리지 마")]]
	Knight(int hp) : _hp(hp)
	{

	}

	int _hp = 100;
};

// enum class에도 nodiscard를 붙일 수 있도록 C++20에서 추가
enum class [[nodiscard("에러코드 사용하세요")]] ErrorCode
{
	None,
	Waring
};

ErrorCode GetError()
{
	return ErrorCode::Waring;
}

int main()
{
	// [[noreturn]] C++11 - return이 없다.
	// [[deprecated]] C++14 - 어떤 함수를 더이상 사용하면 안돼.
	// [[nodiscard]] C++17 - 버리지 않는 카드. 
	
	Func2(); // 버리지 않아야 하는데, 함수 호출만 하니 warning
	auto a = Func2(); // 이런식 받아주는 형태로 사용.

	// nodiscard를 여러 곳에서 사용하면 어디서 warning이 일어나는지 알기가 힘들다.
	// 그래서 C++20엔 사유가 추가되었다.
	// [[nodiscard("사유")]]

	Knight(10); // 사실상 객체는 저장해서 사용해야하는데 임시 객체를 만들었다가 버리는 셈.
	auto a = Knight(10);
}