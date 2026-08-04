#pragma once

#pragma warning(disable: 4251)

// 빌드 모드에 따라서 변경될 값
#if _DEBUG
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)
#else
#define DLLEXPORT
#define DLLIMPORT
#endif

// 특정 값에 따라 분기하도록 처리
#if ENGINE_BUILD_DLL
#define CRAFT_API DLLEXPORT
#else
#define CRAFT_API DLLIMPORT
#endif