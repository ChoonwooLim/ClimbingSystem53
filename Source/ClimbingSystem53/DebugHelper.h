#pragma once

namespace Debug
{
	static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 Inkey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(Inkey, 6.f, Color, Msg);
		}

		UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
	}
}

/* 📌 코드 분석
1. namespace Debug
namespace Debug
Debug라는 네임스페이스(namespace) 를 정의하여, 같은 이름의 함수나 변수가 다른 곳과 충돌하지 않도록 함.

2. static void Print(...)
static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 Inkey = -1)
Print 함수는 디버깅 메시지를 화면과 로그 창에 출력하는 역할.
매개변수 설명
const FString& Msg: 출력할 메시지 (문자열)
const FColor& Color = FColor::MakeRandomColor(): 메시지 색상 (기본값은 랜덤 색)
int32 Inkey = -1: 고유 메시지 키 (같은 키를 사용하면 기존 메시지가 갱신됨)

3. if (GEngine) { GEngine->AddOnScreenDebugMessage(...) }
if (GEngine)
{
    GEngine->AddOnScreenDebugMessage(Inkey, 6.f, Color, Msg);
}
GEngine이 존재하면 게임 화면에 디버그 메시지를 출력.
AddOnScreenDebugMessage의 매개변수:
Inkey: 고유 메시지 키
6.f: 화면에 표시되는 지속 시간 (6초)
Color: 메시지 색상
Msg: 출력할 메시지


📌 최종 정리
namespace Debug
{
    static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 Inkey = -1)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(Inkey, 6.f, Color, Msg);
        }
        
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
    }
}

게임 화면과 로그 창에 메시지를 동시에 출력하는 유틸리티 함수.
GEngine->AddOnScreenDebugMessage(...) → 게임 화면에 표시.
UE_LOG(...) → 로그 창에 출력.
FColor::MakeRandomColor()를 기본값으로 설정하여, 색상이 자동으로 랜덤 지정됨.

✅ 한 줄 요약
📌 이 코드는 게임 화면과 로그 창에 동시에 디버깅 메시지를 출력하는 유틸리티 함수이다! 🎯
*/