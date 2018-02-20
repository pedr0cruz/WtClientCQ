#ifndef WTD_H
#define WTD_H

#include <Wt/WApplication>

#include "ui_wtd.h"

class WtD : public Wt::WApplication
{

public:
	WtD(const Wt::WEnvironment& env);
	~WtD();

	// declare slots here

private:
	Ui_WtD *ui;
	
};

#endif // WTD_H
