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

// 오늘의 주제 : Range-Based For Loop With Initializer
// 범위 기반 루프문에 대해서도 이니셜라이저를 사용하게 될 수 있다.

struct User
{
	int id;
};

User* GetUser()
{
	// TODO...
	return nullptr;
}

int main()
{
	// C++17
	// if w/ Initialzer 
	// 선언을 범위 영역안에 정의할 수 있다.
	if (int a = 10; a == 10) // for문처럼 초기화하는 부분이 들어감.
	{
		cout << a << endl;
	}

	// 은근히 유용하게 활용될 수 있는 ex
	{
		User* user = GetUser();
		if (user == nullptr || user->id == 0)
			return;

		User* user2 = nullptr;
		// (or) user =  GetUser();
		// 이런식으로 user2라고 이름을 새로 파서 사용을 해야한 경우가 되게 빈번할 것이다. (깔끔하지 않다)
		// 아니면 user에 다시 유저를 받아왔는데, 이러면 warning 생길 뿐더러, 버그를 유발시킬 수도 있다.

		// 하지만 C++17에 추가된 기능을 사용하면
		// 이름도 범위를 벗어나면 더이상 사용할 수 없기 때문에 이름이 곁치는 문제를 우아하게 해결할 수 있다.
		if (User* user = GetUser();  user == nullptr || user->id == 0)
			return;


		// Switch w/ Initializer
		{
			switch (int b = 3; b)
			{
			case 2:
				break;
			case 3:
				cout << "df" << endl;
				break;
			}
		}
	}

	// C++20에서 추가된 기능
	// Range-Based for + Initializer
	for (vector<int> vec{ 1,2,3 }; auto v : vec)
	{
		cout << v << endl;
	}
}