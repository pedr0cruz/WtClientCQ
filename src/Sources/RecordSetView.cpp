//	RecordSetView.cpp

#include "stdafx.h"

#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <Wt/WMenu>
#include <Wt/WSignal>
#include <Wt/WLineEdit>
#include <Wt/WBreak>

#include "RecordSetView.h"

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
/// Constructor de la clase RecordSetView
/// @param[in] parent Puntero a clase padre que debe ser de tipo Wt::WContainerWidget o derivada
RecordSetView::RecordSetView(Wt::WContainerWidget* parent) : Wt::WTemplateFormView(parent)
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
/// Establece la fila de encabezamiento
/// @param[in] headers Vector con cadenas de texto de encabezamiento de columnas
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

/// Establece la cantidad de filas o columnas de encabezamiento
/// @param[in] headers_count Entero con cantidad de filas (o columnas) de encabezamiento
/// @param[in] headers_orientation Enumeración de tipo Wt::Orientation que establece si los encabezados son verticales u horizontales
void TableView2::setHeaderCount(int headers_count, Wt::Orientation headers_orientation)
{
}

/// Destructor 
RecordSetView::~RecordSetView()
{
}

#endif



////////////////////////// RecordSetView /////////////////////////////////////////

/// Constructor de la clase RecordSetView
/// @param[in] parent Puntero a clase padre que debe ser de tipo Wt::WContainerWidget o derivada
RecordSetView::RecordSetView(WContainerWidget *parent) : WTemplateFormView(parent)
{
	// Limpia el estilo	
	this->setStyleClass(Wt::WString::fromUTF8(""));
	// Ocupa todo el ancho
	this->setInline(0);
/*
	this->setHtmlTagName("div");
	{
		//inicializacion de las tablas dentro del stack y los signals
		table = new TableView2(this);
		table->rowSelected().connect(SLOT(this, RecordSetView::s_rowSelected));
		table->onFindByColumn().connect(SLOT(this, RecordSetView::s_findByColumn));
		table->onSortByColumn().connect(SLOT(this, RecordSetView::sortByColumn));
		actualPage = 1;

		divPager = new Wt::WContainerWidget(this);
		divPager->setStyleClass(Wt::WString::fromUTF8("row"));
		divPager->setInline(0);
		divPager->setHtmlTagName("div");
		{//texto de total de paginas
			divTotalPages = new Wt::WContainerWidget(divPager);

			divTotalPages->setStyleClass(Wt::WString::fromUTF8("col-md-4"));
			divTotalPages->setInline(0);
			divTotalPages->setHtmlTagName("div");
			{
				totalPages = new Wt::WText(divTotalPages);

				totalPages->setStyleClass(Wt::WString::fromUTF8("totalPages"));
				totalPages->setInline(0);
				totalPages->setTextFormat((Wt::TextFormat)0);
				totalPages->setText(Wt::WString::fromUTF8("<b>Página 0 de 0 </b>"));
			}
			divTablesPager = new Wt::WContainerWidget(divPager);

			divTablesPager->setStyleClass(Wt::WString::fromUTF8("col-md-8"));
			divTablesPager->setInline(0);
			divTablesPager->setHtmlTagName("div");
			{
				pagerTable = new Wt::WMenu(new Wt::WStackedWidget(), divTablesPager);
				divTablesPager->addWidget(pagerTable->contentsStack());

				pagerTable->setStyleClass(Wt::WString::fromUTF8("pager nav pull-right nav pagerTable"));
				pagerTable->setInline(1);
				{//botones de paginacion
					firstItem = new Wt::WContainerWidget(divTablesPager);
					firstItem_mi = pagerTable->addItem(Wt::WString("<<"), firstItem);
					firstItem->setStyleClass(Wt::WString::fromUTF8(""));
					firstItem->setInline(0);
					firstItem_mi->decorationStyle().setCursor(Wt::PointingHandCursor);

					pagerTable->setItemDisabled(0, 1);
					pagerTable->setItemHidden(0, 0);
					previousItem = new Wt::WContainerWidget(divTablesPager);
					previousItem_mi = pagerTable->addItem(Wt::WString("<"), previousItem);
					previousItem->setStyleClass(Wt::WString::fromUTF8(""));
					previousItem->setInline(0);
					previousItem_mi->decorationStyle().setCursor(Wt::PointingHandCursor);

					pagerTable->setItemDisabled(1, 1);
					pagerTable->setItemHidden(1, 0);
					nextItem = new Wt::WContainerWidget(divTablesPager);
					nextItem_mi = pagerTable->addItem(Wt::WString(">"), nextItem);
					nextItem->setStyleClass(Wt::WString::fromUTF8(""));
					nextItem->setInline(0);
					nextItem_mi->decorationStyle().setCursor(Wt::PointingHandCursor);

					pagerTable->setItemDisabled(2, 1);
					pagerTable->setItemHidden(2, 0);
					lastItem = new Wt::WContainerWidget(divTablesPager);
					lastItem_mi = pagerTable->addItem(Wt::WString(">>"), lastItem);
					lastItem->setStyleClass(Wt::WString::fromUTF8(""));
					lastItem->setInline(0);
					lastItem_mi->decorationStyle().setCursor(Wt::PointingHandCursor);

					pagerTable->setItemDisabled(3, 1);
					pagerTable->setItemHidden(3, 0);
				}
			}
		}
	}
	maxRows = 10;
	totalRows = 1;
	maxPages = 1;
	//connections
	firstItem_mi->clicked().connect(SLOT(this, RecordSetView::s_firstTablaCliente));
	lastItem_mi->clicked().connect(SLOT(this, RecordSetView::s_lastTablaCliente));
	previousItem_mi->clicked().connect(SLOT(this, RecordSetView::s_prevTablaCliente));
	nextItem_mi->clicked().connect(SLOT(this, RecordSetView::s_nextTablaCliente));
*/
}

#if 0
/// Constructor de la clase RecordSetView
/// @param[in] parent Puntero a clase padre que debe ser de tipo Wt::WContainerWidget o derivada
/// @param[in] parent Puntero a clase padre que debe ser de tipo Wt::WContainerWidget o derivada
RecordSetView::RecordSetView(vector<string>, Wt::WContainerWidget *parent)
{
}

void RecordSetView::setHeader(vector<string> m_header)
{
	header = m_header;
	table->setHeader(header);
	fillTable();
}

void RecordSetView::setData(vector < vector<string> > m_data)
{
	data = m_data;
	filterData = data;
	fillTable();
}

void RecordSetView::fillTable()
{
	totalRows = static_cast<int> (filterData.size());
	maxPages = (totalRows - 1) / maxRows + 1;
	clearTable();

	for (int i = 0; i < filterData.size(); i++){
		table->addRow(filterData[i]);
	}
	s_firstTablaCliente();
}

void RecordSetView::clearTable()
{
#if 0
	int total = table->rowCount();
	for (int i = total - 1; i > 0; i--)
		table->deleteRow(i);
#endif
}

void RecordSetView::createData()
{
	vector<string> m_header;
	vector < vector<string> > m_data;

	int numColumns = Model_->columnCount();

	for (int col = 0; col < numColumns; col++){
//		m_header.push_back( Model_->data(0, col));
//		WString colname = JsonColumn.get("name");
//		setHeaderData(col, colname.toUTF8());
	}


	data = m_data;
	filterData = data;
	fillTable();
}

void RecordSetView::s_rowSelected(int row)
{
	//TODO / HACK / FIXME
	//rowSelect.emit(filterData[row - 1][0]);
}

void RecordSetView::s_findByColumn(int column)
{
	Wt::WDialog *dialog = new Wt::WDialog(Wt::WString("Buscar por " + header[column] + ":"));

	Wt::WLabel *label = new Wt::WLabel("Inserte valor de búsqueda: ",
		dialog->contents());
	Wt::WLineEdit *edit = new Wt::WLineEdit(dialog->contents());
	label->setBuddy(edit);
	//edit->validator()->setMandatory(true);

	Wt::WPushButton *ok = new Wt::WPushButton("Buscar...", dialog->footer());
	ok->setDefault(true);

	dialog->footer()->setPadding("2px", Wt::Verticals);
	dialog->titleBar()->setPadding("2px", Wt::Verticals);
	dialog->contents()->setPadding("4px", Wt::Verticals);

	dialog->footer()->setPadding("40px", Wt::Horizontals);
	dialog->titleBar()->setPadding("40px", Wt::Horizontals);
	dialog->contents()->setPadding("40px", Wt::Horizontals);
	Wt::WPushButton *cancel = new Wt::WPushButton("Cancelar", dialog->footer());
	dialog->rejectWhenEscapePressed();
	//dialog->setClosable(true);
	//dialog->setTitleBarEnabled(false);

	Wt::WValidator *validator = new Wt::WValidator;
	validator->setMandatory(true);
	edit->setValidator(validator);
	dialog->contents()->setInline(1);

	Wt::WBreak *br = new Wt::WBreak(dialog->contents());
	br->hide();
	Wt::WText *out = new Wt::WText("Debe insertar algún valor", dialog->contents());
	out->setStyleClass("alert alert-danger");
	out->setInline(false);
	out->hide();
	out->setPadding("4px", Wt::Verticals);
	
	ok->clicked().connect(std::bind([=]() {
		if (edit->validate() == Wt::WValidator::InvalidEmpty){
			out->show();
			br->show();
		}
		else dialog->accept();
	}));

	cancel->clicked().connect(dialog, &Wt::WDialog::reject);

	dialog->finished().connect(std::bind([=]() {
		if (dialog->result() == Wt::WDialog::Accepted)
			filterBy(column, edit->text());
		delete dialog;
	}));

	dialog->show();
}

void RecordSetView::filterBy(int column, Wt::WString value)
{
	filterData.clear();
	for (int i = 0; i < data.size(); i++)
		if (data[i][column] == value)
			filterData.push_back(data[i]);
	fillTable();
}

void RecordSetView::sortByColumn(int column, bool order)
{
	//filterData = data;

	for (int i = 0; i < filterData.size(); i++){
		for (int j = i + 1; j < filterData.size(); j++)
			if ((filterData[i][column] < filterData[j][column]) == order){
				vector<string> temp = filterData[j];
				filterData[j] = filterData[i];
				filterData[i] = temp;
			}
	}
	fillTable();
}

void RecordSetView::s_firstTablaCliente()
{
	actualPage = 1;
	updatePagination();
	showRows();
}

void RecordSetView::s_prevTablaCliente()
{
	actualPage--;
	updatePagination();
	showRows();
}

void RecordSetView::s_lastTablaCliente()
{
	actualPage = maxPages;
	updatePagination();
	showRows();
}

void RecordSetView::s_nextTablaCliente()
{
	actualPage++;
	updatePagination();
	showRows();
}

void RecordSetView::updatePagination()
{
	if (actualPage == 1){
		firstItem_mi->setDisabled(true);
		previousItem_mi->setDisabled(true);
	}
	else firstItem_mi->setDisabled(false);

	if (actualPage == maxPages){
		lastItem_mi->setDisabled(true);
		nextItem_mi->setDisabled(true);
	}
	else
		lastItem_mi->setDisabled(false);

	if (actualPage != 1 && actualPage != maxPages){
		previousItem_mi->setDisabled(false);
		nextItem_mi->setDisabled(false);
	}
	if (actualPage == 1 && actualPage != maxPages)
		nextItem_mi->setDisabled(false);
	if (actualPage == maxPages && actualPage != 1)
		previousItem_mi->setDisabled(false);

	totalPages->setText(Wt::WString("Página {1} de {2}").arg(actualPage).arg(maxPages));
}

void RecordSetView::showRows()
{
#if 0
	int ini = (actualPage - 1)*maxRows + 1;
	int fin = (actualPage)*maxRows;
	for (int i = 1; i <= totalRows; i++){
		if (i >= ini && i <= fin)
			table->rowAt(i)->show();
		else table->rowAt(i)->hide();
	}
#endif
}
#endif

/// Establece el modelo usado para esta vista
/// @param model Puntero al modelo que a utilizar
void RecordSetView::setModel(RecordSetModel* model)
{
    model_ = model;
}

/// Oculta (hidden: true) o muestra (hiddeN : false) la vista 
/// @param hidden Si es true, oculta la vista, la hace visible en caso contrario
/// @param animation Establece el tipo de animación a usar para ocultar o mostrar la vista
void RecordSetView::setHidden(bool hidden, const Wt::WAnimation &animation)
{
    WTemplateFormView::setHidden(hidden, animation);
}

/// Destructor
RecordSetView::~RecordSetView()
{
}
