#include "TextSprite.h"

#include <algorithm>

namespace Craft
{
	TextSprite::TextSprite(const std::wstring& image)
		: image(image)
	{
		CalculateSize();
	}

	void TextSprite::SetImage(const std::wstring& newImage)
	{
		image = newImage;
		CalculateSize();
	}

	void TextSprite::CalculateSize()
	{
		width = 0;
		height = 0;

		if (image.empty())
		{
			return;
		}

		int currentLineWidth = 0;

		for (const wchar_t character : image)
		{
			// Windows 줄바꿈의 \r은 무시
			if (character == L'\r')
			{
				continue;
			}

			if (character == L'\n')
			{
				width = (std::max)(width, currentLineWidth);
				currentLineWidth = 0;
				++height;

				continue;
			}

			++currentLineWidth;
		}

		// 마지막 줄의 너비 계산
		width = (std::max)(width, currentLineWidth);

		// 이미지가 줄바꿈으로 끝나지 않았다면 마지막 줄 추가
		if (image.back() != L'\n')
		{
			++height;
		}
	}
}