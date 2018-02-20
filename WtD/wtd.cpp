#include "wtd.h"

WtD::WtD(const Wt::WEnvironment& env) : Wt::WApplication(env), ui(new Ui_WtD)
{
	ui->setupUi(root());

}

WtD::~WtD()
{
	delete ui;
}
