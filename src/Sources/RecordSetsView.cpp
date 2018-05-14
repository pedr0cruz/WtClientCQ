//	RecordSetsView.cpp

#include "stdafx.h"

#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WTabWidget>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <Wt/WMenu>
#include <Wt/WSignal>
#include <Wt/WLineEdit>
#include <Wt/WBreak>

#include <string>
#include <vector>

#include "RecordSetsView.h"

using std::string;
using std::vector;
using namespace Wt;

// ejemplo tomado de stack overflow
#if 0

Wt::Dbo::QueryModel< Wt::Dbo::ptr<TableTag> > * qmTags1 = new Wt::Dbo::QueryModel< Wt::Dbo::ptr<TableTag> >();
qmTags1->setQuery(ddbbSession_.find<TableTag>());
qmTags1->addAllFieldsAsColumns();

WTableView * wtv1 = new WTableView();
wtv1->setModel(qmTags1);
this->root()->addWidget(wtv1);

#endif

#if 0

#include <Wt/WApplication.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WTableView.h>
#include "../treeview-dragdrop/CsvUtil.h"

/*
* Configure column widths and matching table width
*/
const int WIDTH = 120;
for (int i = 0; i < tableView->model()->columnCount(); ++i)
	tableView->setColumnWidth(i, 120);

/*
* 7 pixels are padding/border per column
* 2 pixels are border of the entire table
*/
tableView->setWidth((WIDTH + 7) * tableView->model()->columnCount() + 2);

#endif

#if 0
// Constructor de la clase RecordSetsView
// @param[in] parent Puntero a clase padre que debe ser de tipo Wt::WContainerWidget o derivada
RecordSetsView::RecordSetsView(Wt::WContainerWidget* parent) : Wt::WTemplateFormView(parent)
{
	setStyleClass(Wt::WString::fromUTF8("table-striped table table-hover table-bordered tableCQ"));
	setInline(0);
	//setHeaderCount(1, Wt::Orientation::Horizontal);
	//setHeaderCount(1, Wt::Orientation::Vertical);
	//selectedRow = 0;
	//selectedHeader = 1;
}
#endif

#if 0
// Establece la fila de encabezamiento
// @param[in] headers Vector con cadenas de texto de encabezamiento de columnas
void TableView2::setHeader(vector<string> headers)
{
#if 0
	sortOrder.resize(headers.size());

	elementAt(0, 0)->addWidget(new Wt::WText("<b>#</b>"));

	for (int i = 1; i < headers.size(); i++){
		elementAt(0, i)->addWidget(new Wt::WText("<button class = \"btn btn-default btn-xs\""
			"><span class = \"glyphicon glyphicon-search\">"
			"</span></button>", Wt::XHTMLUnsafeText));
		elementAt(0, i)->addWidget(new Wt::WText("&nbsp;&nbsp;&nbsp;<b>" + headers[i] + "</b>"));
		elementAt(0, i)->addWidget(new Wt::WText("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b></b>"));
		elementAt(0, i)->widget(2)->setStyleClass("pull-right");
		elementAt(0, i)->widget(2)->decorationStyle().setBackgroundImage(Wt::WLink("resources/sort-arrow-none.gif"),
			Wt::WCssDecorationStyle::NoRepeat, Wt::CenterY | Wt::Right);
		elementAt(0, i)->widget(2)->decorationStyle().setCursor(Wt::PointingHandCursor);


		//funcion para el ordenamiento de la columna y el intercambio del background
		((Wt::WText*)elementAt(0, i)->widget(2))->clicked().connect(std::bind([=](){
			elementAt(0, selectedHeader)->widget(2)->decorationStyle().setBackgroundImage(Wt::WLink("resources/sort-arrow-none.gif"),
				Wt::WCssDecorationStyle::NoRepeat, Wt::CenterY | Wt::Right);

			if (sortOrder[i]){
				elementAt(0, i)->widget(2)->decorationStyle().setBackgroundImage(Wt::WLink("resources/sort-arrow-up.gif"),
					Wt::WCssDecorationStyle::NoRepeat, Wt::CenterY | Wt::Right);
			}
			else elementAt(0, i)->widget(2)->decorationStyle().setBackgroundImage(Wt::WLink("resources/sort-arrow-down.gif"),
				Wt::WCssDecorationStyle::NoRepeat, Wt::CenterY | Wt::Right);

			if (selectedHeader != i) sortOrder[selectedHeader] = false;
			sortOrder[i] = !sortOrder[i];
			selectedHeader = i;

			sortByColumn.emit(i, sortOrder[i]);
		}));

		((Wt::WText*)elementAt(0, i)->widget(0))->clicked().connect(std::bind([=](){
			findByColumn.emit(i);
		}));

		sortOrder[i] = false;
	}
#endif
}

// Establece la cantidad de filas o columnas de encabezamiento
// @param[in] headers_count Entero con cantidad de filas (o columnas) de encabezamiento
// @param[in] headers_orientation Enumeración de tipo Wt::Orientation que establece si los encabezados son verticales u horizontales
void TableView2::setHeaderCount(int headers_count, Wt::Orientation headers_orientation)
{
}

// Destructor 
RecordSetsView::~RecordSetsView()
{
}

#endif



//**************************** RecordSetsView ***********************************

#if 0
// Patrón Factory para crear esta vista
// @param[in] parent Puntero a clase padre que debe ser de tipo Wt::WContainerWidget o derivada
RecordSetsView* RecordSetsView::createView(Wt::WContainerWidget* parentContainer)
{
    return new RecordSetsView(parentContainer);
}
#endif

// Constructor de la clase RecordSetsView
// @param[in] parent Puntero a clase padre que debe ser de tipo Wt::WContainerWidget o derivada
//RecordSetsView::RecordSetsView(WContainerWidget *parent) : WContainerWidget(parent)
RecordSetsView::RecordSetsView(WContainerWidget *parent) : WTabWidget(parent)
{
    //tabWidgetContainer_ = parent;
    //tabWidget_ = new WTabWidget(tabWidgetContainer_);
}

// Destructor
RecordSetsView::~RecordSetsView()
{
    //delete tabWidget_;
    //delete tabWidgetContainer_;
}

#if 0

WTabWidget* RecordSetsView::getTabWidget()
{
    return tabWidget_;
}

WContainerWidget* RecordSetsView::getTabWidgetContainer()
{
    return tabWidgetContainer_;
}

#endif

// Establece el modelo usado para esta vista
// @param model Puntero al modelo que a utilizar
void RecordSetsView::setModel(RecordSetsModel* model)
{
    model_ = model;
}

