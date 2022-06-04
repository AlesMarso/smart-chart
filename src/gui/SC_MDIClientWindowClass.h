#include "SC_CommonWindowClass.h"

namespace gui
{
	class SC_MDIClientWindowClass : public SC_CommonWindowClass
	{
	public:
		SC_MDIClientWindowClass();
		~SC_MDIClientWindowClass();

	public:


	protected:
		LRESULT MessageHandle(HWND, UINT, WPARAM, LPARAM) override;

	private:

	};
}
