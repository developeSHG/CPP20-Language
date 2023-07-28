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

// 오늘의 주제 : Template Parameter for Lambda
// 템플릿을 람다와 혼합해서 사용할 수 있다.

// C++11 Typed Lambda
// 태초의 람다
auto sumTyped = [](int a, int b) { return a + b; }; 

// C++14 Generic Lambda
// 두 타입이 달라 됨
auto sumGeneric = [](auto a, auto b) { return a + b; };

// C++14 Generic Lambda
// 후자가 전자로 convertible (변환 가능)해야 함
// ex) a가 int라면, b도 int로 변환이 가능한 type 중 하나여야 한다.
auto sumDeclType = [](auto a, decltype(a) b) { return a + b; };

// C++20 Template Lambda
// 두 타입 같아야 함
auto sumTemplate = []<typename T>(T a, T b) { return a + b; };

// 갈수록 문법이 진화됨에 따라 점점 복잡해져서 사실상 직접 사용할일이 있겠다 싶긴 하다.
// 하지만 그럼에도 문법이 유용하게 사용할 수 있는 경우가 있다.
// ex) 벡터의 사이즈를 반환하는 람다함수를 만들어보자.
{
	// 예전 같으면 람다에 templte 활용을 못해서 지정된 타입으로 사용해야했지만,
	// auto getVectorSize = [](const vector<int>&v) { return v.size(); };
	
	// 이렇게 편리하게 활용할 수 있다.
	auto getVectorSize = []<typename T>(const vector<T>&v) { return v.size(); };
}

int main()
{
	// true로 테스트하는 이유는, 미묘한 차이가 있기때문에
	auto res1 = sumTyped(true, 100); // 101
	auto res2 = sumGeneric(true, 100); // 101
	auto res3 = sumDeclType(true, 100); // 2 (후자가 전자로 변환이 가능하다는 조건이 있기 때문에, bool에서는 0과 1만 존재해서 100이 1로 변환)
	auto res4 = sumTemplate(true, true); // 2

	cout << res1 << endl;
	cout << res2 << endl;
	cout << res3 << endl;
	cout << res4 << endl;

	vector<int> v1{ 1, 2 };
	vector<double> v2{ 1.0, 2.0, 3.0 };
	auto s1 = getVectorSize(v1);
	auto s2 = getVectorSize(v2);
	cout << s1 << endl;
	cout << s2 << endl;
}