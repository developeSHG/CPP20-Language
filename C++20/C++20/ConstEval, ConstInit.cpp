#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <coroutine>

// 오늘의 주제 : consteval / constinit

int SqrRunTime(int n)
{
	return n * n;
}

// C++11
constexpr int SqrRunOrCompileTime(int n)
{
	return n * n;
}

// C++20
consteval int SqrCompileTime(int n)
{
	return n * n;
}

constinit int constInitVal2 = 100; // 나중에라도 원할 때 수정이 가능
constexpr int constInitVal3 = 100; // 수정이 안된다.

int main()
{
	// 함수 ( 일반 vs constexpr(C++11등장) vs consteval(C++20등장) )
	{
		// const 들을 비교해보기 전에 밑의 개념을 알고가자.
		
		// 컴파일 타임 vs 런타임
		// 컴파일 -> 실행파일(exe) -> 런타임
   
		// 정리하자면 C++ 코드를 컴파일러가 번역해서 바이너리 파일로 만들어 준 후,
		// 경과물들을 링크 단계를 거쳐서 최종적으로 실행파일을 만들게 된다.  
		// 그리고, 실행하게 된 프로그램을 런타임 단계라고 한다.
		// 실질적으로 컴파일은 프로램그램이 만들어지는 과정이고,
		// 프로그램이 실행되는 과정은 런타임 단계

		// 둘의 차이점은 컴파일은 컴파일 단계에서 숫자이건 함수건, 결과물이 결정되는 것이고,
		// 런타임은 컴파일 단계에서 결정되진 않았지만, 프로그램 실행중에 결정된다.
		// 사소한 것 같지만, 의외로 큰 차이가 보이게 된다.
		// 
		// 게임을 만들었을 때, 빠른 속도를 위해선 컴파일이 2시간 걸린다해도 런타임에선 문제없이 빠르게 동작한다하면 큰 문제는 없다.
		// 컴파일 단계는 말그대로 실행프로그램을 만드는 단계이기 때문에, 오래 걸리더라도 해당 값이 런타임에선 빠르게 동작한다면 그 자체로도 유용하다.

		int a = 10;

		enum
		{
			// enum은 어떤 정수에다 닉네임을 붙이는 문법이라
			// SqrRunTime은 컴파일 시점에 확정되지 않고, 런타임이 되서야 결과물이 나오는 것이기 때문에 
			// 문법은 유효하지 않다는 컴파일 에러가 발생한다.
			//VAL_1 = SqrRunTime(10), 
			VAL_2 = 100, //SqrRunOrCompileTime(10), 컴파일 시점으로 값 치환이 됌
			VAL_3 = 100, //SqrCompileTime(10), 컴파일 시점으로 값 치환이 됌
		};

		{
			// 이 함수가 만들어질 때는 어떤 값으로 들어올지 예측할 수 없기 때문에,
			// 10 * 10 = 100 이다 라고 바로 치환할 수가 없다. 
			// 실제로 실행될 때는 함수가 호출되면서 10이란 인자를 넘겨줬으니까,
			// 스택 프레임에 10이 들어가게 될것이고, 매게변수를 받아서 CPU가 수식을 계산한 다음,
			// 100이라는 결과를 스택에 넣어줘서 종료된 후, 저장된 위치로 돌아와 결과물을 도출해주는 동작이다.
			int val1 = SqrRunTime(10);

			// constexpr - 컴파일, 런타임 둘 다 가능하며, 최대한 컴파일 타임에 할 수 있으면 컴파일 타임에 만들어놓음.
			int val2 = SqrRunOrCompileTime(10);

			// consteval - 무조건 컴파일 타임.
			// 함수안에서 복잡한 연산을 하든 상관없이 조건만 맞아떨어진다면 모든 부담은 컴파일 단계에서 계산하고,
			// 실제 결과물 자체는 상수를 하드 코딩한 것처럼, 동작하기 때문에 빠르게 동작한다.
			int val3 = SqrCompileTime(10);
			// int val3 = 100; 치환되는 셈

			// 컴파일, 런타임 중에 언제 만들어졌는지 확실한 확인 방법은 디버그 디스어셈블리로 확인 가능


			// 그러면, 컴파일 타임에 만들어지는 게 좋은 거 같은데 왜 굳이 런타임에 만드느냐? 란 생각이 든다.
			// 하지만 어쩔 수 없이 런타임에 생성되는 경우가 생긴다.
			// 리터럴 상수가 아닌, 변수를 넣어줄 경우는 런타임중에 만들어진다.
			// 변수는 고정된 값이 아니라 어떤 값이 될지는 런타임 시점에서 알 수 있기 때문이다.
			int val1 = SqrRunTime(a);
			int val2 = SqrRunOrCompileTime(a);
			int val3 = SqrCompileTime(a); // 유효한 상수식이 아니라는 컴파일 에러
		}

		// consteval 특징
		// - 조건부 jump, loop 가능
		// - 다수의 명령어로 구성 가능
		// - constexpr 함수 호출 가능
		// - static, thread_local 안 됨
		// - try, goto 안 됨
		// - non-consteval 함수 호출 안 됨
		// - non-constexpr 데이터 사용 안 됨
	}

	// 변수 (const vs constexpr vs constinit)
	{
		// const (컴파일타임/런타임 중 둘 다 허용 + constness 있음. 즉 상수성을 보장)
		// const 변수의 초기화는 런타임까지 지연시킬 수 있다
		const int constIntVal = SqrRunTime(10);
		//constIntVal++;

		// constexpr (컴파일타임 허용 + constness 있음. 상수성을 보장)
		// constexpr 변수는 반드시 컴파일 타임에 초기화가 되어야 한다
		constexpr int constExprVal = SqrCompileTime(10);
		//constExprVal++;

		// constinit 특징 (컴파일타임 허용 + constness 없음 + static/thread_local)
		// - global 변수, static 변수, thread_local 변수를 대상으로 사용
		// -- 프로그램 시작 시 메모리 할당, 프로그램이 끝나면 메모리 해제
		// -- thread_local 변수는 thread에 종속적. 특정 thread가 해당 데이터를 사용할 때 생성됨.

		constinit thread_local int constInitVal = SqrCompileTime(10);
		constInitVal++;
	}
}