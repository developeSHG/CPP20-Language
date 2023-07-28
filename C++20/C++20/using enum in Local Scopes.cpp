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

// 오늘의 주제 : using enum in Local Scopes
// 지역 범위에서도 using enum을 사용할 수 있다.

enum class Color
{
	Red,
	Green,
	Blue,
};

using enum Color;
// 이걸 main 코드에 Color::Red가 아닌 Red만 정의 가능.
// 하지만, 이렇게 외부에 Color를 using 해버리게 되면,
// 혹시라도 나중에 사용하지 않을 때도 불구하고, 인식해버리게 되는 경우가 생길 수 있다.

// 그래서 전역으로 하는 게 아닌, 부분적으로 열어줄 수 있는 방법이 추가되었다.

int main()
{
	Color color = Color::Blue;

	switch (color)
	{
		case Red :
			break;
		case Green:
			break;
		case Blue:
			break;
	}
	
	// C++20 추가된 기능
	// 전역에 선언된 using enum은 없다고 가정하고 테스트
	switch (color)
	{
		using enum Color; 

	case Red:
		break;
	case Green:
		break;
	case Blue:
		break;
	}
}