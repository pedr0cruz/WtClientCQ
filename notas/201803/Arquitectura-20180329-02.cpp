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

5 - Implementaremos los formularios como derivados de WTemplateFormView y de MediatorGoF. Este último (MediatorGoF) es el que va a implementar el patrón de diseño Mediador (Mediator) para que las interacciones entre los controles del formulario se realicen todas a través del mediador y no de control a control. Esto es para minimizar la cantidad de interacciones diferentes.

6 - Las diferentes pestañas se recorren iterando. Incorporamos el patrón de iterador polimórfico (polymorphic iterator). Aunque pueda parecer innecesario en este momento, cuando se incorporen las vistas de gráficos o reportes de diferente tipo, un iterador polimórfico será necesario. En todos los casos dicho iterador devolverá un WContainerWidget* lo que permite acceder a la clase derivada correspondiente.

7 - Resumen del diagrama y explicación de los patrones aplicados

7.1 - Los controladores implementan SubjectGoF y la clase CQWtApplication implementa ObserverGoF. Este es el patrón Observer.

7.2 - ResultSet2View implementa la vista del patrón MVC y deriva de WTableView.

7.3 - ResultSet2View, TableCell, TableRow y TableColumn implementan el patrón Cadena de Responsabilidad.
      TableCell, TableRow y TableColumn no son las WTableCell, WTableRow ni WTableColumn de WT. Son 
	  clases hechas para implementar este patrón con nombres similares a las clases de WT.

7.4 - La biblioteca WT no tiene todavía la separación de la vista del controlador en los controles 
      derivados de WFormWidget.

7.5 - RecordsetView deriva de WTemplateFormView y también de MediatorGoF. Cada instancia de RecordsetView contiene un vector de punteros a los controles contenidos por dicho formulario. Estos controles derivan de WFormWidget. Según la documentación de WT, la vista dada por WTemplateFormView es estática, o sea, cada vez que se modifique el modelo es necesario generar la vista nuevamente. Eso son detalles de implementación, asi que no creo que deba reflejarse en el diagrama.

8 - WorkspaceController, WorkspaceModel y WorkspaceView pueden quedarse tal como están, dentro de lo que tengo entendido.

9 - IMPORTANTE: En el caso de los formularios, no vale la pena implementar una Cadena de Responsabilidad. Lo que sí vale la pena es implementar el patrón Mediador (Mediator) porque entre los controles PUEDE haber gran variedad de interacciones y es mejor centralizar toda la interacción entre dichos controles utilizando un mediador común a todas esas interacciones. Dicho mediador es una clase que implementa las funciones del formulario, y para que quede CLARO que es un patrón de diseño es mejor SEPARAR esa funcionalidad en una clase aparte, llamada, como es lógico, MediatorGoF.

10 - Otra nota: Tanto el panel superior como el inferior tienen un contenedor con pestañas (que se implementa con WTabWidget) dentro del cual van otros contenedores (uno en cada pestaña). En el caso del panel superior se van a insertar dentro de él contenedores derivados de WTableView, mientras que en el caso del panel inferior se insertarán contenedores que implementan la interfaz de WTemplateFormView, pues son, en esencia, formularios.

11 - El controlador conectado a la vista del panel superior (ResultSetsController) conecta con las vistas y con los modelos asociados mediante sus correspondientes vectores identificados con rsViews y rsModels, respectivamente. Por supuesto, el índice en cada vector de vistas es el mismo en el vector de modelos para el modelo asociado a dicha vista.

12 - En el caso de RecordsetController, éste también contiene dos vectores a modelos (formModels) y a vistas (formViews) que están asociados entre sí por el índice dentro del vector correspondiente. O sea, el primer elemento dentro del vector formModels es el modelo que corresponde a la primera vista del vector formViews, y así sucesivamente. 


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

class RecordsetView : public WTemplateFormView
                    , public MediatorGoF
{
	std::shared_ptr <WFormWidget> controls;
}

class RecordsetsController : public SubjectGoF
{
	std::shared_ptr <WTabWidget> recTabWidget;
	vector <std::shared_ptr <RecordsetModel> >  recModels;
	vector <std::shared_ptr <RecordsetView> >   recViews;
}

class FormControl : public WFormWidget
{
}

