// Patron de Dise�o Mediator

#include "stdafx.h"

#include "MediatorGoF.h"

using namespace std;

/////// Clase Mediador: act�a como mediador entre varios clientes para minimizar
/////// la cantidad de interacciones entre objetos. Dichos clientes, en vez de
/////// comunicarse directamente entre s�, se comunican solamente con el mediador.

MediatorGoF::MediatorGoF()
{
}

MediatorGoF::~MediatorGoF()
{
}

/// Registra un objeto cliente. Devuelve false si el cliente ya habia sido registrado.
void MediatorGoF::registerClient(std::shared_ptr<ColleagueGoF> colleague_ptr)
{
    colleagues_vec_.push_back(colleague_ptr);
}
