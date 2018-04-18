#ifndef MEDIATOR_H
#define MEDIATOR_H

// Patron de Diseño Mediator

#include <vector>
#include <memory>

using namespace std;

class ColleagueGoF;

/// Clase Mediador: Hace de intermedio entre múltiples clientes que necesitan comunicarse entre ellos.
class MediatorGoF
{
public:
    /// Registra un objeto cliente
    //void registerClient(std::shared_ptr<ColleagueGoF> colleague_ptr);
    void registerClient(ColleagueGoF* colleague_ptr);

    /// Virtual destructor
	virtual ~MediatorGoF();

protected:
	/// Protegido para obligar a utilizar el patrón Factory para su creación
    MediatorGoF();
protected:
    //std::vector <std::shared_ptr<ColleagueGoF> > colleagues_vec_;
    std::vector <ColleagueGoF*> colleagues_vec_;
};

class ColleagueGoF
{
public:
    /// Constructor que recibe puntero a mediador
    //ColleagueGoF(std::shared_ptr<MediatorGoF>);
    ColleagueGoF(MediatorGoF*);

    /// virtual Destructor
    virtual ~ColleagueGoF();
};

#endif
