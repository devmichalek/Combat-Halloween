#pragma once

namespace cmm
{
	class State
	{
	protected:
		bool prev;
		bool next;
		bool exit;
		virtual bool isReady() const = 0;
	public:
		State();
		~State();

		bool isPrev() const;
		bool isNext() const;
		bool isExit() const;
		bool isState() const;
	};
}