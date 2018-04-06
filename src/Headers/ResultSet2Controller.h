#ifndef RESULTSET2_CTRL_H
#define RESULTSET2_CTRL_H

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItemModel>
#include <Wt/WModelIndex>

#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>

#include "ResultSet2View.h"
#include "ResultSet2Model.h"

#include "ObserverGoF.h"

using namespace Wt;

///	Controller for ResultSet which includes the result obtained from a query.
///	Implements the Subject of the Observer Pattern and contains a selected item.
class ResultSet2Controller  : public Wt::WObject
                            , public SubjectGoF
{
public:
    /// Constructor
    ResultSet2Controller(const string & name);

    /// Crea una vista
    WWidget* createView(WContainerWidget* container);

    void recordChanged(const string & s);
    //EventSignal<WScrollEvent>& scrolled();

    void clicked();
    void doubleClicked();
    void focussed();
    void keyPressed();
    void mouseWheel();
    void scrolled(WScrollEvent e);

//	void rowChanged();

    /// Slot para seleccion de nuevo item
    string selectedItem() { return selectedItem_; }

    /// Destructor
    ~ResultSet2Controller();

protected:
    WContainerWidget* rsViewContainer_;

    ResultSet2View*  rsView_;
    ResultSet2Model* rsModel_;

    string selectedItem_;

    void fillModel();
};

#endif /// RESULTSET2_CTRL_H
