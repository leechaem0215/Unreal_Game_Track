#include "ScreenBuffer.h"
#include <cassert>
#include <iostream>

namespace Craft 
{
	ScreenBuffer::ScreenBuffer(const Vector2& screenSize)
		: size(screenSize)
	{
		// 콘솔 버퍼 생성
		buffer = CreateConsoleScreenBuffer
		(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			nullptr, // null 넣어주면 상속안함
			CONSOLE_TEXTMODE_BUFFER,
			nullptr
		);

		// 값 확인 (어서트)
		assert(buffer != INVALID_HANDLE_VALUE);

		// 화면 창 크기 설정
		SMALL_RECT rect = {};
		rect.Top = 0;
		rect.Left = 0;
		rect.Right = static_cast<short>(size.x - 1);
		rect.Bottom = static_cast<short>(size.y - 1);
		BOOL result = SetConsoleWindowInfo(buffer, TRUE, &rect);

		// 결과 확인
		assert(result == TRUE);
		
		// 화면 버퍼 크기 설정
		result = SetConsoleScreenBufferSize(buffer, size);
		assert(result == TRUE);

		// 직접 만든 콘솔의 커서 끄기
		CONSOLE_CURSOR_INFO info;
		result = GetConsoleCursorInfo(buffer, &info);
		assert(result == TRUE);

		// 커서 안보이게 설정
		info.bVisible = FALSE;
		result = SetConsoleCursorInfo(buffer, &info);
		assert(result == TRUE);
	}
	ScreenBuffer::~ScreenBuffer()
	{
		// 콘솔 닫기
		if (buffer)
		{
			CloseHandle(buffer);
		}
	}
	void ScreenBuffer::Clear() const
	{
		// 콘솔 전체를 지우는 함수
		// 공백 문자를 화면 전체에 한 번에 설정
		
		// 화면에 설정된 글자 수
		DWORD writtenCount = 0;

		BOOL result = FillConsoleOutputCharacterA(
			buffer,
			' ',
			size.x * size.y,
			Vector2::Zero,
			&writtenCount
		);
		// 어서트
		assert(result == TRUE);
	}
	void ScreenBuffer::Draw(const CHAR_INFO* const charInfo) const // CHAR_INFO* 2차원으로 다룰것임
	{
		// charInfo 는 2차원 배열 (1차원 배열에 2차원 배열 정보를 기록)

		// 설정할 글자 영역
		SMALL_RECT rect = { 0, 0, static_cast<short>(size.x - 1), static_cast<short>(size.y - 1) }; // left, top, right, bottom

		// 콘솔에  CHAR_INFO 타입으로 글자 쓰는 함수
		BOOL result = WriteConsoleOutputW(
			buffer,
			charInfo, // charInfo = size
			size,
			Vector2::Zero, // 기록된 영역을 넘겨주면 그걸 입력으로도 쓰고 출력으로도 쓴다. 어디부터 어디까지 기록할거라는..
			&rect // 참조로 넘김
		);
		assert(result == TRUE);
	}
}