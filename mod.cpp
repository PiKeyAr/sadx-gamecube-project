#include "stdafx.h"
#include <SADXModLoader.h>
#include "IniFile.hpp"
#include "Trampoline.h"
#include "IniFile.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>

using std::unordered_map;
using std::vector;
using std::string;

float sphe_cursol_scale = 1.0f;
float menu_shadow_scale_x = 3.96900012f;
float menu_shadow_scale_y = 1.0f;
bool DLLLoaded_HDGUI = false;
static float Options_ArrowScale = 0.0f;
static float Options_ArrowScaleAmount = 0.1f;

void FileIcon_Hook(int that_cant_be_right, float Texture_X, float Texture_Y, float Texture_Z)
{
	float Arrow1_X;
	float Arrow1_Y;
	float Arrow2_X;
	float Arrow2_Y;
	float Arrow1Center_X = 251.0f;
	float Arrow1Center_Y = 268.0f;
	float Arrow2Center_X = 218.0f;
	float Arrow2Center_Y = 322.0f;
	float Arrow1Scale = 0.0f + Options_ArrowScale;
	float Arrow2Scale = 1.0f - Options_ArrowScale;
	Arrow1_X = (Arrow1Center_X - 32 * Arrow1Scale) - 320.0f + HorizontalStretch * 320.0f;
	Arrow1_Y = (Arrow1Center_Y - 32 * Arrow1Scale) - 240.0f + VerticalStretch * 240.0f;
	Arrow2_X = (Arrow2Center_X - 32 * Arrow2Scale) - 320.0f + HorizontalStretch * 320.0f;
	Arrow2_Y = (Arrow2Center_Y - 32 * Arrow2Scale) - 240.0f + VerticalStretch * 240.0f;
	njTextureShadingMode(1);
	DisplayScreenTexture(44, Texture_X, Texture_Y, Texture_Z);
	DrawBG(45, Arrow1_X, Arrow1_Y, Texture_Z, Arrow1Scale, Arrow1Scale);
	DrawBG(46, Arrow2_X, Arrow2_Y, Texture_Z, Arrow2Scale, Arrow2Scale);
	njTextureShadingMode(2);
}

void BrandingFixes()
{
	WriteCall((void*)0x005092A1, FileIcon_Hook); //Save icon
	WriteData((float**)0x50B524, &menu_shadow_scale_x);
	WriteData((float**)0x50B50D, &menu_shadow_scale_y);
	WriteData((float**)0x431B46, &sphe_cursol_scale); //AVA_CSR
	WriteData((float**)0x431B57, &sphe_cursol_scale); //AVA_CSR
	WriteData((float*)0x10D7E20, 3.25f); //Trial menu shadow X scale
	WriteData((float*)0x10D7E1C, 3.96900012f); //Trial menu shadow Y scale
	//AVA_NEW16NO fixes
	WriteData((float*)0x5079F7, 1.125f); //sub_5079E0
	WriteData((float*)0x5079FC, 1.125f); //sub_5079E0
	WriteData((float*)0x507A1F, 1.125f); //sub_5079E0
	WriteData((float*)0x507A24, 1.125f); //sub_5079E0
	WriteData((float*)0x507A4A, 1.125f); //sub_5079E0
	WriteData((float*)0x507A4F, 1.125f); //sub_5079E0
	WriteData((float*)0x507A82, 1.125f); //sub_5079E0
	WriteData((float*)0x507A87, 1.125f); //sub_5079E0
	WriteData((float*)0x507AE2, 1.125f); //sub_5079E0
	WriteData((float*)0x507AE7, 1.125f); //sub_5079E0
	WriteData((float*)0x507897, 1.125f); //sub_507880
	WriteData((float*)0x50789C, 1.125f); //sub_507880
	WriteData((float*)0x5078BF, 1.125f); //sub_507880
	WriteData((float*)0x5078C4, 1.125f); //sub_507880
	WriteData((float*)0x5078EA, 1.125f); //sub_507880
	WriteData((float*)0x5078EF, 1.125f); //sub_507880
	WriteData((float*)0x507935, 1.125f); //sub_507880
	WriteData((float*)0x50793A, 1.125f); //sub_507880
	WriteData((float*)0x507989, 1.125f); //sub_507880
	WriteData((float*)0x50798E, 1.125f); //sub_507880
	WriteData((float*)0x50AEA1, 1.125f); //sub_50AE30
	WriteData((float*)0x50AEA6, 1.125f); //sub_50AE30
	WriteData((float*)0x50AEE0, 1.125f); //sub_50AE30
	WriteData((float*)0x50AEE5, 1.125f); //sub_50AE30
	WriteData((float*)0x510DE9, 1.75f); //Sound test
	WriteData((float*)0x510DEE, 1.375f); //Sound test
	WriteData((float*)0x510E0B, 1.75f); //Sound test
	WriteData((float*)0x510E10, 1.375f); //Sound test
	WriteData((float*)0x510E32, 1.75f); //Sound test
	WriteData((float*)0x510E37, 1.375f); //Sound test
	WriteData((float*)0x510E5C, 1.75f); //Sound test
	WriteData((float*)0x510E61, 1.375f); //Sound test
	WriteData((float*)0x510E79, 1.75f); //Sound test
	WriteData((float*)0x510E7E, 1.375f); //Sound test
	WriteData((float*)0x50A058, 1.125f); //sub_50A010
	WriteData((float*)0x50A06A, 1.125f); //sub_50A010
	WriteData((float*)0x50AE0A, 1.125f); //sub_50ADE0
	WriteData((float*)0x50AE0F, 1.125f); //sub_50ADE0
	WriteData((float*)0x50AEA1, 1.125f); //sub_50AE30
	WriteData((float*)0x50AEA6, 1.125f); //sub_50AE30
	WriteData((float*)0x50AEE0, 1.125f); //sub_50AE30
	WriteData((float*)0x50AEE5, 1.125f); //sub_50AE30
	WriteData((float*)0x50AF5A, 1.125f); //sub_50AF30
	WriteData((float*)0x50AF5F, 1.125f); //sub_50AF30
}

static vector<string> split(const string& s, char delim)
{
	vector<string> elems;
	std::stringstream ss(s);
	string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

void UVPatcher(const IniFile* uvlist, Uint32 baseaddr)
{
	for (int idx = 0; idx < 65535; idx++)
	{
		char key[8]{};
		snprintf(key, sizeof(key), "%u", idx);
		if (!uvlist->hasGroup(key))
			break;

		const IniGroup* group = uvlist->getGroup(key);
		auto data = group->data();
		Uint32 addr = uvlist->getIntRadix(key, "a", 16) + baseaddr;
		auto uvarray = (NJS_TEX*)addr;
		for (const auto& iter : *data)
		{
			vector<string> vals = split(uvlist->getString(key, iter.first.c_str()), ',');
			if (vals.size() < 2)
			{
				continue;
			}
			assert(vals.size() == 2);
			int idx_uv = std::stoi(iter.first);
			uvarray[idx_uv].u = static_cast<int>(strtod(vals[0].c_str(), nullptr));
			uvarray[idx_uv].v = static_cast<int>(strtod(vals[1].c_str(), nullptr));
			//PrintDebug("UV array: %s\n", iter.first.c_str());
		}

	}
}

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions &helperFunctions)
	{
		const std::string s_path(path);
		DLLLoaded_HDGUI = (GetModuleHandle(L"HD_GUI") != nullptr);
		if (!DLLLoaded_HDGUI) BrandingFixes();

		//UV patches
		const std::string s_uvpatch(s_path + "\\data\\uv_sonic.ini");
		const IniFile* const uvpatch_sonic = new IniFile(s_uvpatch);
		UVPatcher(uvpatch_sonic, 0x400000);
	}

	__declspec(dllexport) void __cdecl OnInput()
	{
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		//TODO: Make it accelerate like on GC
		if (GameMode == GameModes_Menu)
		{
			if (Options_ArrowScale > 1.0f) Options_ArrowScaleAmount = -0.02f;
			if (Options_ArrowScale < 0.0f) Options_ArrowScaleAmount = 0.02f;
			Options_ArrowScale = Options_ArrowScale + Options_ArrowScaleAmount;
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}