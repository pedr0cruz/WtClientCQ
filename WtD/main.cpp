#include "wtd.h"

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
	return new WtD(env);
}

int __main(int argc, char *argv[])
{
	return Wt::WRun(argc, argv, &createApplication);
}
