/**

La arquitectura MVC consta de:

1 - Modelo: contiene los datos y la estructura de los mismos.
2 - Vista: contiene codigo que muestra la IU.
3 - Controlador: conecta el modelo con la vista y reacciona a las acciones del usuario.

1 - El panel de la izquierda contiene la vista WorkspaceView conectada al modelo WorkspaceModel mediante el controlador WorkspaceController.

2 - El panel superior contiene un WTabWidget que contiene en cada pestaña su propia vista Resultset2View y cada una va conectada a su modelo correspondiente Resultset2Model. Todos los modelos controlados mediante el ResultSetsController.

3 - El panel inferior contiene un WTabWidget que contiene en cada pestaña su propia vista RecordsetView y cada una va conectada a su modelo correspondiente Recordset2Model. Todos los modelos controlados mediante el RecordSetsController.

*** OJO ***
4 - En el panel inferior en cada una de las pestañas lo que van son FORMULARIOS. 
    Estos se pueden implementar con UNA entre las siguientes alternativas:
    4.1 - WContainerWidget
    4.2 - WTemplateFormView
    4.3 - WViewWidget

5 - Las diferentes pestañas se recorren iterando. Incorporamos el patrón de iterador polimórfico (polymorphic iterator). Aunque pueda parecer innecesario en este momento, cuando se incorporen las vistas de gráficos o reportes de diferente tipo, un iterador polimórfico será necesario. En todos los casos dicho iterador devolverá un WContainerWidget* lo que permite acceder a la clase derivada correspondiente.

*/

class WApplication;
class ObserverGoF;

class CQWtAppView
{
	///	...	
};

class CQWtApplication : public WApplication
                      , public ObserverGoF
{
	std::shared_ptr <CQWtAppView> mainView;
	std::shared_ptr <WorkspaceController>  wsController;
	std::shared_ptr <ResultSetsController> rssController;
	std::shared_ptr <RecordsetController>  recController;
}

class WorkspaceController;
class WorkspaceModel;
class WorkspaceView;

class WorkspaceModel : public WStandardItemModel
{
	std::shared_ptr<CQJSON> cqSession;
}

class WorkspaceView : public WTreeView
{
	std::shared_ptr <WorkspaceModel> wsModel;
}

class WorkspaceController : public SubjectGoF
{
	std::shared_ptr <WorkspaceModel> wsModel;
	std::shared_ptr <WorkspaceView>  wsView;
}

class ResultSet2Controller;
class ResultSet2Model;
class ResultSet2View;

class ResultSet2Model : public WStandardItemModel
{
	std::shared_ptr<CQJSON> cqSession;
}

class ResultSet2View : public WTableView
{
	std::shared_ptr<ResultSet2Model> rsModel;
}

class ResultSetsController : public SubjectGoF
{
	std::shared_ptr <WTabWidget> rssTabWidget;
	vector < std::shared_ptr <ResultSet2Model> >  rsModels;
	vector < std::shared_ptr <ResultSet2View> >   rsViews;
}

class RecordsetController;
class RecordsetModel;
class RecordsetView;

class RecordsetModel : public WStandardItemModel
{
	std::shared_ptr <CQJSON> cqSession;
}

class RecordsetView : public WTableView
                    , public CoRHandlerGoF
{
	std::shared_ptr <RecordsetModel> rsModel;
}

class RecordsetsController : public SubjectGoF
{
	std::shared_ptr <WTabWidget> recTabWidget;
	vector <std::shared_ptr <RecordsetModel> >  recModels;
	vector <std::shared_ptr <RecordsetView> >   recViews;
}


