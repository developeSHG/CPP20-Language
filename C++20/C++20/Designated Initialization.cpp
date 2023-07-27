#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <coroutine>

// 오늘의 주제 : Designated Initialization (지정 초기화)

struct Pos2D
{
	int x;
	int y;
};

class Pos3D
{
public:
	// Pos3D() {}
	// Pos3D(int x, int y, int z) : x(x), y(y), z(z) { }
	int x;
	int y;
	int z;
};

int main()
{
	// 지정초기화를 알기 전에, 미리 알아야할 것
	// Aggregate Initialization 문법이 있다. (진작에 추가된 것임)
	// 구조체나 클래스를 사용할 때, 일반적으로 아래처럼 초기화한다.
	Pos3D pos;
	pos.x = 0;
	pos.y = 1;
	pos.y = 2;

	// 하지만, 멤버를 매번 할당하는 게 지저분하다. 
	// 그래서 생성자를 만들어서 대입할 수 있지만, 생성자를 만드는 순간, 기본 생성자가 막히기 때문에 기본 생성자도 정의해야한다.
	
	// Aggregate Initialization 문법은 아래처럼 맡바로 초기화를 할 수 있다. (순서대로)
	// 하지만 조건이 있다
	// - 직접 만든 생성자가 없어야 한다.
	// - 가상 함수가 없어야 한다.
	// - private / protected / static인 데이터 변수 X
	Pos3D pos{ 1, 2, 3 };

	// 그럼에도 위 방법이 마음에 안드는 경우는 변수가 세 가지 밖에 없지만,
	// 인자가 많아진다고 가정하면, 일일이 초기화하는 경우도 매우 피곤하다.
	// 또 y, z만 초기값을 정해주고 싶다고 하면 {0, 3, 5} 식으로 x도 임의로 초기값을 정해줄 수 밖에 없다.

	// 근데 새롭게 추가된 문법에는 이렇게 사용할 수 있다.
	// 모든 멤버 변수를 다 채울 필요없이 원하는 변수만 초기화가 가능하다는 장점이 있다.
	Pos3D pos{ .y = 3, .z = 5 };

	// 정리하면, 지정해서 초기화할 수 있는 문법이 C++20에 추가된 것.
	// 하지만 주의할 것은 지정해서 초기화할 수 있다곤 했지만,
	// 순서를 마음대로 뒤집어서 초기화는 불가능하다. (클래스 멤버 선언 순서대로)
	Pos3D pos{ .z = 3, .y = 5 }; // 컴파일 에러


	// Tip
	// Aggregate Initialization 문법은 변수 타입과 다른 값을 넣을 경우, 축소 변환이 일어나서 에러없이 사용 가능하다.
	Pos3D pos{ 1, 2, 3.f }; // 축소 변환 (narrowing conversion)
	// 하지만 지정초기화 경우는 다른 타입에 대해 축소 변환이 일어나지 않아 컴파일 에러가 발생한다.
	Pos3D pos{ .x = 1, .y = 2, .z = 3.f }; // 컴파일 에러
}