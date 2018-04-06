#ifndef OBSERVER_H
#define OBSERVER_H

// Patron de Diseño Observer

#include <vector>
#include <memory>

using namespace std;

class SubjectGoF;

// Clase Observador: recibe una llamada a "update" cuando un Sujeto cambia
class ObserverGoF
{
public:
	virtual void update(SubjectGoF* s) = 0; // Recibe el objeto que cambio
	virtual ~ObserverGoF();
protected:
	ObserverGoF();
};

// Clase Sujeto: cuando cambia, invoca a notify para que se enteren los Observadores
class SubjectGoF
{
public:
	// Obtiene y almacena un objeto Observador
	//virtual void attach(ObserverGoF *o);
	virtual void attach(std::shared_ptr <ObserverGoF> o);
	// Notifica a todos los observadores, que ocurrio un cambio
	virtual void notify();
	// Devuelve el nombre del sujeto
	string subjectName();
	// Destructor
	virtual ~SubjectGoF();
protected:
	SubjectGoF(string name);
	string name_;
	//vector<ObserverGoF *> vecObservers; // Lista de observadores
	vector <std::shared_ptr <ObserverGoF> > vecObservers; // Lista de observadores
};


#endif


