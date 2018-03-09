// CQWtClient: Cliente de ClearQuest en Wt C++

#include "CQWtApp.h"

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
	return new CQWtApplication(env);
}

int main(int argc, char *argv[])
{
	auto ret_val = Wt::WRun(argc, argv, &createApplication);
	return ret_val;
}
