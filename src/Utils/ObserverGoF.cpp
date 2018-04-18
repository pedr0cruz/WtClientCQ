// Patron de Diseño Observer

#include "stdafx.h"

#include "ObserverGoF.h"

using namespace std;

/////// Clase Observador: recibe una llamada a "update" cuando un Sujeto cambia

ObserverGoF::~ObserverGoF()
{
}

ObserverGoF::ObserverGoF()
{
}

/////// Clase Sujeto: cuando cambia, invoca a notify para que se enteren los Observadores

// Obtiene y almacena un objeto Observador
//void SubjectGoF::attach(std::shared_ptr <ObserverGoF> o)
void SubjectGoF::attach(ObserverGoF *o)
{
	vecObservers.push_back (o); 
}

// Notifica a todos los observadores, que ocurrio un cambio
void SubjectGoF::notify()
{
	int size = static_cast <int> (vecObservers.size());
	for (int i = 0; i < size; i++) {
		vecObservers[i]->update(this);
	}
}

// Devuelve el nombre del sujeto
string SubjectGoF::subjectName()
{ 
	return name_; 
}

// Destructor
SubjectGoF::~SubjectGoF()
{
}

SubjectGoF::SubjectGoF(string name) : name_(name)
{
}

