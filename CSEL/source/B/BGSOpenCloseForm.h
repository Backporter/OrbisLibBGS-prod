#pragma once

namespace ConsoleRE
{
	class TESObjectREFR;

	class BGSOpenCloseForm
	{
	public:
		virtual ~BGSOpenCloseForm();
		
		// add
		virtual void HandleOpen(TESObjectREFR* a_target, TESObjectREFR* a_activator);
		virtual void HandleClose(TESObjectREFR* a_target, TESObjectREFR* a_activator);
		virtual void Unk_04();
	};
}