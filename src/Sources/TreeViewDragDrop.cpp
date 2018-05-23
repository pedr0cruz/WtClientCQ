// TreeViewDragDrop.cpp

#include "stdafx.h"

/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include <fstream>
#include <boost/algorithm/string/replace.hpp>

#include <Wt/WApplication>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>
#include <Wt/WDatePicker>
#include <Wt/WDateValidator>
#include <Wt/WDialog>
#include <Wt/WEnvironment>
#include <Wt/WIntValidator>
#include <Wt/WItemDelegate>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WMessageBox>
#include <Wt/WPushButton>
#include <Wt/WRegExpValidator>
#include <Wt/WGridLayout>
#include <Wt/WPopupMenu>
#include <Wt/WSortFilterProxyModel>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WModelIndex>
#include <Wt/WTableView>
#include <Wt/WTreeView>
#include <Wt/WIconPair>
#include <Wt/WText>
#include <Wt/WVBoxLayout>
#include <Wt/WBootstrapTheme>
#include <Wt/Chart/WPieChart>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>

#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

#include "CsvUtil.h"
#include "FolderView.h"

#if !defined (FALSE_DEFINED)
#	define FALSE         0
#	define FALSE_DEFINED 1
#endif
#if !defined (TRUE_DEFINED)
#	define TRUE          0
#	define TRUE_DEFINED  1
#endif

using std::string;
using namespace Wt;

/**
 * \defgroup treeviewdragdrop Drag and drop in WTreeView example
 */
/*@{*/

/*! \class FileModel
 *  \brief A specialized standard item model which report a specific
 *         drag and drop mime type.
 *
 * A specific drag and drop mime type instead of the generic abstract
 * item model is returned by the model.
 */
class FileModel : public WStandardItemModel
{
public:
  /*! \brief Constructor.
   */
  FileModel(WObject *parent)
    : WStandardItemModel(parent) { }

  /*! \brief Return the mime type.
   */
  virtual string mimeType() const {
    return FolderView::FileSelectionMimeType;
  }

  // Date display format.
  static WString dateDisplayFormat;

  // Date edit format.
  static WString dateEditFormat;
};

WString FileModel::dateDisplayFormat(WString::fromUTF8("MMM dd, yyyy"));
WString FileModel::dateEditFormat(WString::fromUTF8("dd-MM-yyyy"));

/*! \class FileEditDialog
 *  \brief A dialog for editing a 'file'.
 */
class FileEditDialog : public WDialog
{
public:
  FileEditDialog(WAbstractItemModel *model, const WModelIndex& item)
    : WDialog("Edit..."),
      model_(model),
      item_(item)
  {
    int modelRow = item_.row();

    resize(300, WLength::Auto);

    /*
     * Create the form widgets, and load them with data from the model.
     */

    // name
    nameEdit_ = new WLineEdit(asString(model_->data(modelRow, 1)));

    // type
    typeEdit_ = new WComboBox();
    typeEdit_->addItem("Document");
    typeEdit_->addItem("Spreadsheet");
    typeEdit_->addItem("Presentation");
    typeEdit_->setCurrentIndex
      (typeEdit_->findText(asString(model_->data(modelRow, 2))));

    // size
    sizeEdit_ = new WLineEdit(asString(model_->data(modelRow, 3)));
//    sizeEdit_->setValidator
//      (new WIntValidator(0, std::numeric_limits<int>::max(), this));

    // created
    createdPicker_ = new WDatePicker();
    createdPicker_->lineEdit()->validator()->setMandatory(true);
    createdPicker_->setFormat(FileModel::dateEditFormat);
    createdPicker_->setDate(boost::any_cast<WDate>(model_->data(modelRow, 4)));

    // modified
    modifiedPicker_ = new WDatePicker();
    modifiedPicker_->lineEdit()->validator()->setMandatory(true);
    modifiedPicker_->setFormat(FileModel::dateEditFormat);
    modifiedPicker_->setDate(boost::any_cast<WDate>(model_->data(modelRow, 5)));

    /*
     * Use a grid layout for the labels and fields
     */
    WGridLayout *layout = new WGridLayout();

    WLabel *l;
    int row = 0;

    layout->addWidget(l = new WLabel("Name:"), row, 0);
    layout->addWidget(nameEdit_, row, 1);
    l->setBuddy(nameEdit_);
    ++row;

    layout->addWidget(l = new WLabel("Type:"), row, 0);
    layout->addWidget(typeEdit_, row, 1);
    l->setBuddy(typeEdit_);
    ++row;

    layout->addWidget(l = new WLabel("Size:"), row, 0);
    layout->addWidget(sizeEdit_, row, 1);
    l->setBuddy(sizeEdit_);
    ++row;

    layout->addWidget(l = new WLabel("Created:"), row, 0);
    layout->addWidget(createdPicker_->lineEdit(), row, 1);
    layout->addWidget(createdPicker_, row, 2);
    l->setBuddy(createdPicker_->lineEdit());
    ++row;

    layout->addWidget(l = new WLabel("Modified:"), row, 0);
    layout->addWidget(modifiedPicker_->lineEdit(), row, 1);
    layout->addWidget(modifiedPicker_, row, 2);
    l->setBuddy(modifiedPicker_->lineEdit());
    ++row;

    WPushButton *b;
    WContainerWidget *buttons = new WContainerWidget();
    buttons->addWidget(b = new WPushButton("Save"));
    b->clicked().connect(this, &WDialog::accept);
    contents()->enterPressed().connect(this, &WDialog::accept);
    buttons->addWidget(b = new WPushButton("Cancel"));
    b->clicked().connect(this, &WDialog::reject);

    /*
     * Focus the form widget that corresonds to the selected item.
     */
    switch (item.column()) {
    case 2:
      typeEdit_->setFocus(); break;
    case 3:
      sizeEdit_->setFocus(); break;
    case 4:
      createdPicker_->lineEdit()->setFocus(); break;
    case 5:
      modifiedPicker_->lineEdit()->setFocus(); break;
    default:
      nameEdit_->setFocus(); break;
    }

    layout->addWidget(buttons, row, 0, 0, 3, AlignCenter);
    layout->setColumnStretch(1, 1);

    contents()->setLayout(layout);

    finished().connect(this, &FileEditDialog::handleFinish);

    show();
  }

private:
  WAbstractItemModel *model_;
  WModelIndex         item_;

  WLineEdit *nameEdit_, *sizeEdit_;
  WComboBox *typeEdit_;
  WDatePicker *createdPicker_, *modifiedPicker_;

  void handleFinish(DialogCode result)
  {
    if (result == WDialog::Accepted) {
      /*
       * Update the model with data from the edit widgets.
       *
       * You will want to do some validation here...
       *
       * Note that we directly update the source model to avoid
       * problems caused by the dynamic sorting of the proxy model,
       * which reorders row numbers, and would cause us to switch to editing
       * the wrong data.
       */
      WAbstractItemModel *m = model_;
      int modelRow = item_.row();

      WAbstractProxyModel *proxyModel = dynamic_cast<WAbstractProxyModel *>(m);
      if (proxyModel) {
	m = proxyModel->sourceModel();
	modelRow = proxyModel->mapToSource(item_).row();
      }

      m->setData(modelRow, 1, boost::any(nameEdit_->text()));
      m->setData(modelRow, 2, boost::any(typeEdit_->currentText()));
      m->setData(modelRow, 3, boost::any(boost::lexical_cast<int>
					 (sizeEdit_->text().toUTF8())));
      m->setData(modelRow, 4, boost::any(createdPicker_->date()));
      m->setData(modelRow, 5, boost::any(modifiedPicker_->date()));
    }

    delete this;
  }

};

/*! \class TreeViewDragDrop
 *  \brief MAIN application class.
 */
class TreeViewDragDrop : public WApplication
{
public:
  /*! \brief Constructor.
   */
  TreeViewDragDrop(const WEnvironment &env) : WApplication(env),
      popup_(0), // limpia el puntero al menu pop-up
      popupActionBox_(0) // limpia el puntero al mensaje de confirmación
  {
	  // Usamos boostrap3
	  Wt::WBootstrapTheme * p_wtTheme = new Wt::WBootstrapTheme();
	  p_wtTheme->setVersion(Wt::WBootstrapTheme::Version3);
	  setTheme(p_wtTheme);

    folderModel_ = new WStandardItemModel(0, 1, this);
    populateFolders();

	/*
	* Create the data models. Lee de un CSV
	*/
	fileModel_ = new FileModel(this);
    //populateFiles();

    /*
      The header items are also endered using an ItemDelegate, and thus
      support other data, e.g.:

      fileModel_->setHeaderFlags(0, Horizontal, HeaderIsUserCheckable);
      fileModel_->setHeaderData(0, Horizontal,
                                string("icons/file.gif"),
			        Wt::DecorationRole);
    */
    fileFilterModel_ = new WSortFilterProxyModel(this);
    fileFilterModel_->setSourceModel(fileModel_);
    fileFilterModel_->setDynamicSortFilter(true);
    fileFilterModel_->setFilterKeyColumn(0);
    fileFilterModel_->setFilterRole(UserRole);

    /*
     * Setup the user interface.
     */
    createUI();
  }

  virtual ~TreeViewDragDrop() {
    delete popup_;
    delete popupActionBox_;
  }

private:
  // The folder model (used by folderView_)
  WStandardItemModel    *folderModel_;
  WModelIndex         folderItem_;

  // The file model (used by fileView_)
  WStandardItemModel    *fileModel_;

  // The sort filter proxy model that adapts fileModel_
  WSortFilterProxyModel *fileFilterModel_;

  // Maps folder id's to folder descriptions.
  std::map<string, WString> folderNameMap_;
  std::map<string, WStandardItem*> folderItemMap_;
  std::map<string, Json::Object*> jsonObjectMap_;

  // The folder view.
  WTreeView *folderView_;

  // The file view.
  WTableView *fileView_;

  // Popup menu on the folder view
  WPopupMenu *popup_;

  // Message box to confirm the poup menu action
  WMessageBox *popupActionBox_;

  /*! \brief Setup the user interface.
   */
  void createUI() {	
    WContainerWidget *w = root();
    w->setStyleClass("maindiv");

    /*
     * The main layout is a 3x2 grid layout.
     */
    WGridLayout *layout = new WGridLayout();
    layout->addWidget(createTitle("Folders"), 0, 0);
    layout->addWidget(createTitle("Files"), 0, 1);
    layout->addWidget(folderView(), 1, 0);
    layout->setColumnResizable(0);

    // select the first folder
    folderView_->select(folderModel_->index(0, 0, folderModel_->index(0, 0)));

    WVBoxLayout *vbox = new WVBoxLayout();
    vbox->addWidget(fileView(), 1);
    vbox->addWidget(pieChart(), 1);
    vbox->setResizable(0);

    layout->addLayout(vbox, 1, 1);

    layout->addWidget(aboutDisplay(), 2, 0, 1, 2);

    /*
     * Let row 1 and column 1 take the excess space.
     */
    layout->setRowStretch(1, 1);
    layout->setColumnStretch(1, 1);

    w->setLayout(layout);
  }

  /*! \brief Creates a title widget.
   */
  WText *createTitle(const WString& title) {
    WText *result = new WText(title);
    result->setInline(false);
    result->setStyleClass("title");

    return result;
  }

  /*! \brief Creates the folder WTreeView
   */
  WTreeView *folderView() {
    WTreeView *treeView = new FolderView();

    /*
     * To support right-click, we need to disable the built-in browser
     * context menu.
     *
     * Note that disabling the context menu and catching the
     * right-click does not work reliably on all browsers.
     */
    treeView->setAttributeValue
      ("oncontextmenu",
       "event.cancelBubble = true; event.returnValue = false; return false;");
    treeView->setModel(folderModel_);
    treeView->resize(200, WLength::Auto);
    treeView->setSelectionMode(SingleSelection);
    treeView->expandToDepth(1);
    treeView->selectionChanged()
      .connect(this, &TreeViewDragDrop::folderChanged);

    treeView->mouseWentUp().connect(this, &TreeViewDragDrop::showPopup);

    folderView_ = treeView;

    return treeView;
  }

  /*! \brief Creates the file table view (a WTableView)
   */
  WTableView *fileView() {
    WTableView *tableView = new WTableView();

    tableView->setAlternatingRowColors(true);

	tableView->setModel(fileModel_); // (fileFilterModel_);
    tableView->setSelectionMode(ExtendedSelection);
    tableView->setDragEnabled(true);
	/*
    tableView->setColumnWidth(0, 100);
    tableView->setColumnWidth(1, 150);
    tableView->setColumnWidth(2, 100);
    tableView->setColumnWidth(3, 60);
    tableView->setColumnWidth(4, 100);
    tableView->setColumnWidth(5, 100);
    */
    // FIXME HACK REVISAR PENDIENTE PENDING
    tableView->setColumnWidth(0, 100);
    tableView->setColumnWidth(1, 50);
    tableView->setColumnWidth(2, 50);
    tableView->setColumnWidth(3, 50);
    tableView->setColumnWidth(4, 50);
    tableView->setColumnWidth(5, 50);
    /*
    WItemDelegate *delegate = new WItemDelegate(this);
    delegate->setTextFormat(FileModel::dateDisplayFormat);
    tableView->setItemDelegateForColumn(0, delegate);
    tableView->setItemDelegateForColumn(1, delegate);
	
    tableView->setColumnAlignment(3, AlignRight);
    tableView->setColumnAlignment(4, AlignRight);
    tableView->setColumnAlignment(5, AlignRight);

    tableView->sortByColumn(0, AscendingOrder);
*/
    tableView->doubleClicked().connect(this, &TreeViewDragDrop::editFile);

    fileView_ = tableView;

    return tableView;
  }

  /*! \brief Edit a particular row.
   */
  void editFile(const WModelIndex& item) {
    new FileEditDialog(fileView_->model(), item);
  }

  /*! \brief Creates the chart.
   */
  WWidget *pieChart() {
    using namespace Chart;

    WPieChart *chart = new WPieChart();
    // chart->setPreferredMethod(WPaintedWidget::PngImage);
    chart->setModel(fileFilterModel_);
    chart->setTitle("File sizes");

    chart->setLabelsColumn(1); // Name
    chart->setDataColumn(3);   // Size

    chart->setPerspectiveEnabled(true, 0.2);
    chart->setDisplayLabels(Outside | TextLabel);

    if (!WApplication::instance()->environment().ajax()) {
      chart->resize(500, 200);
      chart->setMargin(WLength::Auto, Left | Right);
      WContainerWidget *w = new WContainerWidget();
      w->addWidget(chart);
      w->setStyleClass("about");
      return w;
    } else {
      chart->setStyleClass("about");
      return chart;
    }
  }

  /*! \brief Creates the hints text.
   */
  WWidget *aboutDisplay() {
    WText *result = new WText(WString::tr("about-text"));
    result->setStyleClass("about");
    return result;
  }

  /*! \brief Change the filter on the file view when the selected folder
   *         changes.
   */
  void folderChanged() {
    if (folderView_->selectedIndexes().empty())
      return;

    WModelIndex selected = *folderView_->selectedIndexes().begin();
    boost::any d = selected.data(UserRole);
    if (!d.empty()) {
      string folder = boost::any_cast<string>(d);

      // For simplicity, we assume here that the folder-id does not
      // contain special regexp characters, otherwise these need to be
      // escaped -- or use the \Q \E qutoing escape regular expression
      // syntax (and escape \E)
	  if(populateFiles( folder ))
		fileView_->refresh();
      //fileFilterModel_->setFilterRegExp(folder);
    }
  }

  /*! \brief Show a popup for a folder item.
   */
  void showPopup(const WModelIndex& item, const WMouseEvent& event) {
    if (event.button() == WMouseEvent::RightButton) {
      // Select the item, it was not yet selected.
      if (!folderView_->isSelected(item))
	folderView_->select(item);

      if (!popup_) {
	popup_ = new WPopupMenu();
	popup_->addItem("icons/folder_new.gif", "Create a New Folder");
	popup_->addItem("Rename this Folder")->setCheckable(true);
	popup_->addItem("Delete this Folder");
	popup_->addSeparator();
	popup_->addItem("Folder Details");
	popup_->addSeparator();
	popup_->addItem("Application Inventory");
	popup_->addItem("Hardware Inventory");
	popup_->addSeparator();

	WPopupMenu *subMenu = new WPopupMenu();
	subMenu->addItem("Sub Item 1");
	subMenu->addItem("Sub Item 2");
	popup_->addMenu("File Deployments", subMenu);

	/*
	 * This is one method of executing a popup, which does not block a
	 * thread for a reentrant event loop, and thus scales.
	 *
	 * Alternatively you could call WPopupMenu::exec(), which returns
	 * the result, but while waiting for it, blocks the thread.
	 */      
	popup_->aboutToHide().connect(this, &TreeViewDragDrop::popupAction);
      }

      if (popup_->isHidden())
      	popup_->popup(event);
      else
	popup_->hide();
    }
  }

  /** \brief Process the result of the popup menu
   */
  void popupAction() {
    if (popup_->result()) {
      /*
       * You could also bind extra data to an item using setData() and
       * check here for the action asked. For now, we just use the text.
       */
      WString text = popup_->result()->text();
      popup_->hide();

      popupActionBox_ = new WMessageBox("Sorry.","Action '" + text
					+ "' is not implemented.", NoIcon, Ok);
      popupActionBox_->buttonClicked()
	.connect(this, &TreeViewDragDrop::dialogDone);
      popupActionBox_->show();
    } else {
      popup_->hide();
    }
  }

  /** \brief Process the result of the message box.
   */
  void dialogDone() {
    delete popupActionBox_;
    popupActionBox_ = 0;
  }

  /*! \brief Populate the files model.
   *
   * Data (and headers) is read from the CSV file data/files.csv. We
   * add icons to the first column, resolve the folder id to the
   * actual folder name, and configure item flags, and parse date
   * values.
   */
  bool populateFiles(const string & QueryName ) {

#ifdef MyDEBUG
	  CQJSONdummy cqSession;
#else
	  CQJSON cqSession;
#endif

	Json::Object JsonObject, JsonCQ, JsonQuery, JsonColumn, JsonRow, result;
	if (!cqSession.UserLogon("admin", "", "SAMPL", "SAMPLCNX")) return FALSE;
	WString JsonRequest = JS({ "clearquest": { "db": "SAMPL", "repo" : "SAMPLCNX", "login" : "admin", "query" : { "name": "{1}" }} });
	string JsonQueryResult = cqSession.JSONExecuteQuery( JsonRequest.arg(QueryName).toUTF8());
	Json::parse(JsonQueryResult, result);

	/*{ "clearquest": { "db": "SAMPLE", "repo" : "SAMPLE", "login" : "cq_user",
	"publicfolder" : [{ "folder":"Public Queries", "name" : "Defects by State", "path" : "Aging charts", "type" : "FOLDER" }, { ... }],
	"personalfolder" : [{...}, { ... }] }}*/
	JsonCQ = result.get("clearquest");
	string status = JsonCQ.get("status");
	if (status != "ok") return FALSE;
	JsonQuery = JsonCQ.get("query");
	Json::Array JsonColumns = JsonQuery.get("columns");
	Json::Array JsonRows = JsonQuery.get("rows");
	int numColumns = JsonQuery.get("numcolumns" ).toNumber();
	int numRows = JsonQuery.get("numrows").toNumber();
	
	// Llenamos las cabeceras
	fileModel_->invisibleRootItem()->setRowCount(0);
	fileModel_->invisibleRootItem()->setColumnCount(0);
	fileModel_->insertColumns(0, numColumns);
	for (int col = 0; col < numColumns; col++){
		JsonColumn = JsonColumns[col];
		WString colname = JsonColumn.get("name");
		fileModel_->setHeaderData(col, colname.toUTF8());
	}
	// Llenamos las filas
	fileModel_->insertRows(0, numRows);
	for (int row = 0; row < numRows; row++){
		JsonRow = JsonRows[row];
		//fileModel_->insertRows(fileModel_->rowCount(), row + 1 - fileModel_->rowCount());
		for (auto col = 0; col < numColumns; col++){
			Json::Object JsonColumn = JsonColumns[col];
			WString colname = JsonColumn.get("name");
			boost::any data(Wt::WString::fromUTF8(JsonRow.get(colname.toUTF8()) ));
			fileModel_->setData(row, col, data);
			WString coltype = JsonColumn.get("type");


			/*			if (coltype == "DATETIME")
				convertToDate(fileModel_->item(row, col));
			if (coltype == "LONG" || coltype == "DOUBLE")
				convertToNumber(fileModel_->item(row, col));
*/
		}
	}
	/*

    std::ifstream f((appRoot() + "data/files.csv").c_str());

    if (!f)
      throw std::runtime_error("Could not read: data/files.csv");

    readFromCsv(f, fileModel_);

    for (int i = 0; i < fileModel_->rowCount(); ++i) {
      WStandardItem *item = fileModel_->item(i, 0);
      item->setFlags(item->flags() | ItemIsDragEnabled);
      item->setIcon("icons/file.gif");

      string folderId = item->text().toUTF8();

      item->setData(boost::any(folderId), UserRole);
      item->setText(folderNameMap_[folderId]);

      convertToNumber(fileModel_->item(i, 3));
      convertToDate(fileModel_->item(i, 4));
      convertToDate(fileModel_->item(i, 5));
    }*/
	return TRUE;
  }

  /*! \brief Convert a string to a date.
   */
  void convertToDate(WStandardItem *item) {
    WDate d = WDate::fromString(item->text(), FileModel::dateEditFormat);
    item->setData(boost::any(d), DisplayRole);
  }

  /*! \brief Convert a string to a number.
   */
  void convertToNumber(WStandardItem *item) {
    int i = boost::lexical_cast<int>(item->text());
    item->setData(boost::any(i), EditRole);
  }

  /*! \brief Populate the folders model.
   */
  void populateFolders() {
    WStandardItem *level1, *level2, *level3, *level4;

	// Para colocar el par de iconos de las carpetas
	//Wt::WIconPair *folderIcon = new WIconPair("icons/yellow-folder-closed.png",
	//		"icons/yellow-folder-open.png", false);
	// WTreeNode *node = new WTreeNode("Furniture", folderIcon);

#ifdef MyDEBUG
	CQJSONdummy cqSession;
#else
	CQJSON cqSession;
#endif

	Json::Object JsonObject, result;
	cqSession.UserLogon("admin", "", "SAMPL", "SAMPLCNX");
	string JsonFolderList = cqSession.JSONGetAllFolderList(JS({ "clearquest": {} }));
	Json::parse(JsonFolderList, result);

	/*{ "clearquest": { "db": "SAMPLE", "repo" : "SAMPLE", "login" : "cq_user",
		"publicfolder" : [{ "folder":"Public Queries", "name" : "Defects by State", "path" : "Aging charts", "type" : "FOLDER" }, { ... }],
		"personalfolder" : [{...}, { ... }] }}*/
	JsonObject = result.get("clearquest");
	Json::Array publicFolders = JsonObject.get("publicfolder");
	
	// level1 = "Principal"
	//folderModel_->appendRow(level1 = createFolderItem("Principal"));
	level1 = folderModel_->invisibleRootItem();
	folderItemMap_["Public_Queries"] = level1; // Puntero a Principal
	for (unsigned index = 0; index < publicFolders.size(); /*index++*/){
		Json::Object aFolder = publicFolders[index];
		string sPath = WString(aFolder.get("path")).toUTF8();
		string sName = WString(aFolder.get("name")).toUTF8();
		if (sPath == "") {// Pertenece al padre
			string folderName = WString(aFolder.get("name")).toUTF8(); // Nombre
			string folderID = WString(aFolder.get("folder")).toUTF8() + "/" + folderName;
			boost::algorithm::replace_all(folderID, " ", "_"); // ID sin espacios
			level1->appendRow(level2 = createFolderItem(folderName, folderID));
			publicFolders.erase(publicFolders.begin() + index);
			//publicFolders[index] = Json::Value(); // Elimina el elemento del arreglo
		}
		else index++;
		// Guardar en otro arreglo de 2 nivel y despues en un arreglo de 3 nivel hasta el 5to
	}
	// Nivel 2 recorre el nivel 1 para ver si tiene algun hijo
	for (auto index1 = 0; index1 < level1->rowCount(); index1++){
		level2 = level1->child(index1);
		WString sLevel2 = level2->text();
		// Recorrer nuevamente el arreglo que quedo
		for (unsigned index2 = 0; index2 < publicFolders.size(); /*index2++*/){
			Json::Object aFolder = publicFolders[index2];
			if ( !aFolder.empty() ){
				WString sPath2 = WString(aFolder.get("path")).toUTF8();
				if (sPath2 == sLevel2 ) {// Pertenece al padre
					string folderName = WString(aFolder.get("name")).toUTF8(); // Nombre
					string folderID = WString(aFolder.get("folder")).toUTF8() + "/" + sPath2.toUTF8() + "/" + folderName;
					boost::algorithm::replace_all(folderID, " ", "_"); // ID sin espacios
					level2->appendRow(level3 = createFolderItem(folderName, folderID));
					publicFolders.erase(publicFolders.begin() + index2);
				}
				else index2++;
			}
		}
	}
	// Nivel 3: recorre el arreglo que queda para ver donde lo debo poner
	for (unsigned index3 = 0; index3 < publicFolders.size(); index3++){
		Json::Object aFolder = publicFolders[index3];
		string sPath3 = WString(aFolder.get("path")).toUTF8(); // Obtendo la ruta
		string sPath3level1 = sPath3.substr(0, sPath3.find('/')); // Obtengo el nivel1
		sPath3 = sPath3.substr(sPath3.find('/')+1); // Obtendo el nivel2
		// Busco en el nivel 1
		for (auto index1 = 0; index1 < level1->rowCount(); index1++){
			level2 = level1->child(index1);
			WString level2name = level2->text();
			if (level2name == sPath3level1) {  // Encontro el padre
				for (auto index2 = 0; index2 < level2->rowCount(); index2++){
					level3 = level2->child(index2);
					WString sLevel3 = level3->text();
					// Recorrer nuevamente el arreglo que quedo
					// Buscamos en el map
					if (sPath3 == sLevel3){ // Pertenece al hijo
						string folderName = WString(aFolder.get("name")).toUTF8(); // Nombre
						string folderID = WString(aFolder.get("folder")).toUTF8() + "/" + sPath3 + "/" + folderName;
						boost::algorithm::replace_all(folderID, " ", "_"); // ID sin espacios
						level3->appendRow(level4 = createFolderItem(folderName, folderID));
						publicFolders.erase(publicFolders.begin() + index3);
					}
				}
			}
		}
	}
	// Agrega queries, charts y reports    
	string JsonQueyList = cqSession.JSONGetAllWorkspaceList(JS({ "clearquest": {} }));
	Json::parse(JsonQueyList, result);
	// To-Do: Chequear posibles errores en la respuesta

	Json::Object joCQ = result.get("clearquest");
	Json::Object joFolder = joCQ.get("publicfolder");
	Json::Array publicQueries = joFolder.get("queries");
	for (unsigned index = 0; index < publicQueries.size(); index++){
		Json::Object aQuery = publicQueries[index];
		string sName = WString(aQuery.get("name")).toUTF8();
		string sFolder = WString(aQuery.get("folder")).toUTF8();
		string sPath = WString(aQuery.get("path")).toUTF8();
		boost::algorithm::replace_all(sFolder, " ", "_"); // Path sin espacios
		WStandardItem *aFolder = folderItemMap_[sFolder]; // Obtiene el folder del mapa
		aFolder->appendRow(createElementItem(sName, sPath, aQuery));	// Agrega el elemento al folder
	}
	
	folderModel_->appendRow(level1 = createFolderItem("San Fransisco"));
    level1->appendRow(level2 = createFolderItem("Investors", "sf-investors"));
    level1->appendRow(level2 = createFolderItem("Fellows", "sf-fellows"));

    folderModel_->setHeaderData(0, Horizontal, boost::any(string("Explorador")));
  }

  /*! \brief Create a folder item.
   *
   * Configures flags for drag and drop support.
   */
  WStandardItem *createFolderItem(const WString& location, const string & folderId = string())
  {
    WStandardItem *result = new WStandardItem(location);

    if (!folderId.empty()) {
      result->setData(boost::any(folderId));
      result->setFlags(result->flags() | ItemIsDropEnabled);
      folderNameMap_[folderId] = location; // AL fiinal quitar esto
	  folderItemMap_[folderId] = result;
	}
	else
      result->setFlags(result->flags().clear(ItemIsSelectable));

	result->setIcon("icons/folder.gif");
    return result;
  }

  WStandardItem *createElementItem(
      const WString& location, 
      const string& folderId = string(), Json::Object &joItem = Json::Value() )
  {
	  WStandardItem *result = new WStandardItem(location);
	  Json::Object *json = new Json::Object(joItem);

	  result->setData(boost::any(folderId));
	  result->setFlags(result->flags() | ItemIsSelectable);
	  folderNameMap_[folderId] = location;	// AL fiinal quitar esto
//	  folderItemMap_[folderId] = result;	// AL fiinal quitar esto
	  jsonObjectMap_[folderId] = json;

	  result->setIcon("icons/file.gif");
	  return result;
  }

};
/*
WApplication *createApplication(const WEnvironment& env)
{
  WApplication *app = new TreeViewDragDrop(env);
  app->setTwoPhaseRenderingThreshold(0); // Establece two-phase rendering para JavaScript
  app->setTitle("WTreeView Drag & Drop");
  app->useStyleSheet("styles.css");
  app->messageResourceBundle().use(WApplication::appRoot() + "about");
  app->refresh(); // recargar todos los elementos incluyendo los bundles
  
  return app;
}

int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}
*/
/*@}*/
