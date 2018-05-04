///  ObserverGoF.h
///  Patron de Diseño Observer

#ifndef OBSERVER_H
#define OBSERVER_H

#pragma once

#include <string>
#include <vector>

class SubjectGoF;

/// Clase Observador: recibe una llamada a "update" cuando un Sujeto cambia
class ObserverGoF
{
public:
    /// Recibe el objeto que cambio
    virtual void update(SubjectGoF* s) = 0;
    /// Destructor
	virtual ~ObserverGoF();
protected:
	ObserverGoF();
};

/// Clase Sujeto: cuando cambia, invoca a notify para que se enteren los Observadores
class SubjectGoF
{
public:
	/// Obtiene y almacena un objeto Observador
	virtual void attach(ObserverGoF* o);
	/// Notifica a todos los observadores, que ocurrio un cambio
	virtual void notify();
	/// Devuelve el nombre del sujeto
    std::string subjectName();
	/// Destructor
	virtual ~SubjectGoF();
protected:
    SubjectGoF(const std::string & name);
    /// Nombre del sujeto (para identificar cada uno de los sujetos)
    std::string name_;
    /// Lista de observadores
    std::vector<ObserverGoF*> vecObservers;
};

#endif
