//  TabWidget.h

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <Wt/WTabWidget>
#include <Wt/WCssDecorationStyle>
#include <Wt/WAnimation>

#include <vector>
#include <string>

#include <Wt/WSignal>

///	TabWidget: Contains common functionality for the Tabbed Widget Container used in this project
class TabWidget : public Wt::WTabWidget
{
public:
	TabWidget (Wt::WContainerWidget *parent = 0);
    ~TabWidget();
protected:
private:
};

#endif /// TABWIDGET_H
