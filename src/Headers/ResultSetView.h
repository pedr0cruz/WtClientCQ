// ResultSetView

#ifndef RESULTSET_VIEW_H
#define RESULTSET_VIEW_H

#pragma once

#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WTemplate>
#include <Wt/WCssDecorationStyle>
#include <Wt/WAnimation>
#include <Wt/WDialog>
#include <Wt/WLabel>
#include <Wt/WSignal>
#include <Wt/WTableView>

#include <vector>
#include <string>

#include "ResultSetModel.h"

#if 1
///	TableView: Shows the data from a model.
/// This class inherits from WTable to implement a custom table view.
class TableView : public Wt::WTableView
{
private:
    /// Indice de la fila seleccionada
	int selectedRow;
    /// Indice del encabezamiento seleccionado
    int selectedHeader;
    
    /// Señal de selección de fila
	Wt::Signal<int> rowSelect;
    /// Señal de búsqueda por columna
    Wt::Signal<int> findByColumn;
    /// Señal de ordenamiento por columnas
    Wt::Signal<int, bool> sortByColumn;

    /// Indica orden ascendente o descendente por cada columna
	std::vector<bool> sortOrder;

    /// FIX ME HACK PENDIENTE TODO
	void s_selectRow(int);

public:
    /// Constructor
	TableView(Wt::WContainerWidget *parent = 0);
    /// Establece los encabezamientos
    void setHeader(std::vector <std::string>);
    /// Agrega una fila recibida en un argumento como vector de cadenas
    void addRow(std::vector <std::string>);
    /// Oculta/muestra la vista (argumento en true/false) y establece qué animación utilizar.
    void setHidden(bool, const Wt::WAnimation & animation = Wt::WAnimation());
    /// Establece la cantidad de filas/columnas que se usarán como encabezamientos (según header_orientation).
	void setHeaderCount(int headers_count, Wt::Orientation header_orientation);

/*
	Signal< int, int > &  cellClicked()
		Signal emitted when a cell is clicked.More...

		Signal< int, int, int, int > &  currentCellChanged()
		Signal emitted when a new cell received focus.More...

		Signal &  itemSelectionChanged()
		Signal emitted when the selection changes.More...
*/

    Wt::Signal<int>& rowSelected(){ return rowSelect; }
    Wt::Signal<int>& onFindByColumn(){ return findByColumn; }
    Wt::Signal<int, bool>& onSortByColumn(){ return sortByColumn; }

    /// Destructor
	virtual ~TableView();
};
#endif

////////////////////////// ResultSetView /////////////////////////////////////////

///	ResultSetView: Shows the data from a result set.
/// This class inherits from WContainerWidget to implement a container which holds
/// a set of results.
class ResultSetView : public Wt::WContainerWidget
{
private:
    ///  DATOS ESPECÍFICOS de cada vista

    static const char* ItemSelectionMimeType;

    ResultSetModel* model_;
	bool usePager;
	int maxRows;
	int totalRows;
	int maxPages;
	int actualPage;

    std::vector < std::string> header;
    std::vector < std::vector <std::string> > data;
    std::vector < std::vector <std::string> > filterData;

	TableView* table;
	Wt::WContainerWidget *divPager;
	Wt::WContainerWidget *divTotalPages;
	Wt::WText *totalPages;
	Wt::WContainerWidget *divTablesPager;
	Wt::WMenu *pagerTable;
	Wt::WContainerWidget * firstItem;
	Wt::WMenuItem * firstItem_mi;
	Wt::WContainerWidget * previousItem;
	Wt::WMenuItem * previousItem_mi;
	Wt::WContainerWidget * nextItem;
	Wt::WMenuItem * nextItem_mi;
	Wt::WContainerWidget * lastItem;
	Wt::WMenuItem * lastItem_mi;

    //	Wt::Signal<string> rowSelect;

    /// FIN de DATOS ESPECÍFICOS de cada vista

	void s_nextTablaCliente();
	void s_lastTablaCliente();
	void s_prevTablaCliente();
	void s_firstTablaCliente();
	void s_findByColumn(int);
	void s_rowSelected(int);


//	Wt::EventSignal<WScrollEvent>& Wt::WContainerWidget::scrolled();

	void filterBy(int, Wt::WString);
	void sortByColumn(int, bool);

	void updatePagination();
	void showRows();

public:
	ResultSetView(Wt::WContainerWidget *parent = 0);
    ResultSetView(std::vector <std::string>, Wt::WContainerWidget *parent = 0);

    void setHeader(std::vector <std::string>);
    void setData(std::vector < std::vector <std::string> >);
    /// Toma el modelo y lo guarda de la matriz <vector <vector>>
	void createData();
	void fillTable();
	void clearTable();

	TableView* getTable(){ return table; };

	void setMaxRows(int t){ maxRows = t; }
	void setPager(bool pager){ usePager = pager; }
	void setModel(ResultSetModel* model){ model_ = model; }

//	Wt::Signal<string>& onSelectedRow(){ return rowSelect; }
	
	/*
	Wt::Signal& Wt::WAbstractItemView::selectionChanged()
	{
	}
	*/

	~ResultSetView();
};
#endif /// RESULTSET_VIEW_H
