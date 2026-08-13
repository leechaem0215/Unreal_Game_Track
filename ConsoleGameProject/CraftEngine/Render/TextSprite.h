#pragma once

#include <Core/Core.h>
#include <string>

namespace Craft
{
	class CRAFT_API TextSprite
	{
	public:
		TextSprite() = default;

		explicit TextSprite(const std::wstring& image);

		void SetImage(const std::wstring& newImage);

		inline const std::wstring& GetImage() const
		{
			return image;
		}

		inline int GetWidth() const
		{
			return width;
		}

		inline int GetHeight() const
		{
			return height;
		}

	private:
		void CalculateSize();

	private:
		std::wstring image;

		int width = 0;
		int height = 0;
	};
}