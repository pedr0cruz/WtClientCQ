//  DecoratorGoF.h
//  Patron de Diseño Decorator

#ifndef DECORATOR_H
#define DECORATOR_H

#pragma once

/// Clase Componente: Define la funcionalidad mínima necesaria para usar la clase Decorador
///
class ComponentGoF
{
public:
    /// Función virtual que será llamada desde las instancias de la clase Decorator
    virtual void operation() = 0;
};

/// Clase Decorador: Permite agregar responsabilidades a instances de clases de forma dinámica
///
class DecoratorGoF : public ComponentGoF
{
public:
    /// Constructor que recibe puntero a componente al que se le aplica el patrón Decorator
    DecoratorGoF(ComponentGoF* component);

    /// Función virtual que será reemplazada en las clases concretas derivadas de ésta.
    virtual void operation();

private:
	ComponentGoF* component_;
};

#endif // #ifndef DECORATOR_H
