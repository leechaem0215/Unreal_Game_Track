#include "ResourceManager.h"

#include <fstream>
#include <stdexcept>

namespace Craft
{
	std::unordered_map<std::wstring,std::wstring> ResourceManager::textAssets;

	std::vector<std::wstring> ResourceManager::LoadAll(std::initializer_list<TextAssetInfo> assetList)
	{
		std::vector<std::wstring> loadedKeys;

		loadedKeys.reserve(assetList.size());

		for (const TextAssetInfo& asset : assetList)
		{
			LoadText(
				asset.key,
				asset.filePath
			);

			loadedKeys.emplace_back(asset.key);
		}

		return loadedKeys;
	}

	void ResourceManager::LoadText(
		const std::wstring& key,
		const std::wstring& filePath)
	{
		std::wifstream file(filePath);

		if (!file.is_open())
		{
			throw std::runtime_error(
				"텍스트 파일을 열 수 없습니다."
			);
		}

		std::wstring text;
		std::wstring line;

		bool isFirstLine = true;

		while (std::getline(file, line))
		{
			if (!isFirstLine)
			{
				text += L'\n';
			}

			text += line;
			isFirstLine = false;
		}

		textAssets[key] = std::move(text);
	}

	const std::wstring& ResourceManager::GetText(
		const std::wstring& key)
	{
		const auto iterator = textAssets.find(key);

		if (iterator == textAssets.end())
		{
			throw std::runtime_error(
				"등록되지 않은 텍스트 리소스입니다."
			);
		}

		return iterator->second;
	}
}