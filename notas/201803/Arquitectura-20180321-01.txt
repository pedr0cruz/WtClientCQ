/**

La arquitectura MVC consta de:

1 - Modelo
	El modelo contiene los datos y la estructura de los mismos.
2 - Vista
	La vista contiene codigo que muestra la IU.
3 - Controlador
	El controlador conecta el modelo con la vista y reacciona a las acciones del usuario.

Nota 1: El objeto WObject desciende de Wt::Core::Observable que implementa el patrón Observer.
		Todo objeto que necesite ser Observado debe, por lo tanto, descender de WObject.
		Son innecesarias las clases ObserverGoF y SubjectGoF.

Nota 2: Para cada consulta se tiene un RecordSet (clase RecordSet2Model) junto con su 
		correspondiente RecordSet2View.

Nota 3: La vista de todos los RecordSet es un contenedor con pestañas (tabs) y para cada pestaña
		hay un WTableView asociada a su propio RecordSet.

Nota 4: Las múltiples vistas que pueden mostrarse en el panel inferior derecho se encapsulan
		con el patrón Composite. Al usar el WTabWidget, ya se está usando ese patrón de forma
		implícita.

Nota 5: Las diferentes pestañas se recorren iterando. Incorporamos el patrón de iterador polimórfico
		(polymorphic iterator). Aunque pueda parecer innecesario en este momento, cuando se
		incorporen las vistas de gráficos o reportes de diferente tipo, un iterador polimórfico será
		necesario. En todos los casos dicho iterador devolverá un WContainerWidget* lo que permite
		acceder a la clase derivada correspondiente.
*/

class ResultSet2Controller;
class ResultSet2Model;
class ResultSet2View;
class ResultSetsView;

class ResultSet2Model : public WObject
{
	std::shared_ptr<CQJSON> cqSession;
}

class ResultSet2View : public WObject
{
	std::shared_ptr<CQJSON> cqSession;
}

class ResultSetsView : public WObject
{
	std::shared_ptr <WTabWidget> table;
}

class ResultSetsController : public WObject
{
	vector < ResultSet2Model >  rsModels;
	vector < ResultSet2View >   rsViews;
}

class ResultSet2View {
	ResultSet2Model* Model_;
	// ... ui data ...
	long cacheStartRow;
	bool usePager, maxRows, totalRows, maxPages, actualPage;

	vector < string > header;
	
	// Duda: porque esto esta en ResultSetView si en 
	//	ResultSetModel tambien hay un wTableData ???
	vector < vector <string> > data;
	
	vector < vector <string> > filterData;

	WTableView *table;
	// WT view widgets
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

	Wt::Signal<string> rowSelect;
}
class ResultSet2Controller {
	WContainerWidget* rsViewContainer_;
	ResultSet2View*  rsView_;
	ResultSet2Model* rsModel_;
	//string selectedItem_;
	vector < string > selectedItems_;
}

Notas: 

1 - Poner una cadena de responsabilidad para que los eventos de la interfaz de usuario
puedan ser manejados por el controlador correspondiente. Puede que algunos eventos
sean controlados por un controlador para las filas o segun la celda segun el rol
de cada columna (se supone que todas las celdas de cada columna tienen el mismo
rol, o sea, todas las celdas de una columna son texto, o son un combobox, o son
una imagen).

2 - Hay varias alternativas para manejar la tabla con las filas. Puede hacerse un
patrón Composite y recorrerlo usando Iterator, o puede hacerse un patrón Visitor 
para visitar las filas. Para mi la mejor opción es un patrón Iterator, y obtener
el iterador desde cada fila, y cuando se llegue a la última se devuelve un 
NullIterator, el cual siempre va a dar que no hay más registros, o sea, que 
está en el último registro. En ese caso se implementaría un iterador virtual del
cual se derivan todos: el normal y el nulo. También puede implementarse la opción
de crear el iterador directo (o sea del inicio al final) o inverso.

3 - Valorar de que manera se haria el filtrado. Lo que es más intuitivo es con
un iterador filtrado que bien puede llamarse FilteredIterator.

4 - Valorar si es necesario implementar el cache. Supongo que eso depende del caso 
en particular. Posiblemente pudiera implementarse con el patrón decorator, de forma
que sea opcional ???

5 - Es posible que valga la pena implementar el patrón bridge entre WTableView
y las clases para la implementación del rendering, de modo que sea más fácil
de cambiar en el futuro lo que se haga. La pregunta es si vale la pena el
incremento en la complejidad del sistema ?



