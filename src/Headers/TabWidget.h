#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <Wt/WTabWidget>
#include <Wt/WCssDecorationStyle>
#include <Wt/WAnimation>

#include <vector>
#include <string>

#include <Wt/WSignal>

//using namespace std;
using namespace Wt;

///	TabWidget: Contains common functionality for the Tabbed Widget Container used in this project
class TabWidget : public WTabWidget
{
private:

public:
	TabWidget (Wt::WContainerWidget *parent = 0);
	~TableView();
};

#endif /// TABWIDGET_H
