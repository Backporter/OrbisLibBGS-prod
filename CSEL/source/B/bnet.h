#pragma once

namespace ConsoleRE
{
	// bnet::OrbisExternalAuthInfo is unkown, its never directly used
	class bnet
	{
	public:
		bnet();
		virtual ~bnet();

	private:
	};
	static_assert(sizeof(bnet) != 0, "class size mismatch");

	class OrbisExternalAuthInfo
	{
	public:
		OrbisExternalAuthInfo();
		virtual ~OrbisExternalAuthInfo();

	private:
	};
	static_assert(sizeof(OrbisExternalAuthInfo) != 0, "class size mismatch");
}