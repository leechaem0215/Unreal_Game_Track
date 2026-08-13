#pragma once

#include <Core/Core.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <initializer_list>

namespace Craft
{
	struct CRAFT_API TextAssetInfo
	{
		std::wstring key;
		std::wstring filePath;
	};

	class CRAFT_API ResourceManager
	{
	public:
		// 리소스 목록을 불러오고, 불러온 키 목록 반환
		static std::vector<std::wstring> LoadAll(
			std::initializer_list<TextAssetInfo> assetList
		);

		static void LoadText(
			const std::wstring& key,
			const std::wstring& filePath
		);

		static const std::wstring& GetText(
			const std::wstring& key
		);

	private:
		static std::unordered_map<
			std::wstring,
			std::wstring
		> textAssets;
	};
}