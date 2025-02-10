#pragma once
#ifndef COLLECTOR_HEADER
#define COLLECTOR_HEADER

// TODO: Hacer funciones isEmpty() o similares para mejor aprovechamiento

/// @brief Clase para la obtención de datos de un conjunto de pines
/// @tparam T Tipo de dato que devolverá al leer
template<class T>
class Collector {
public:
    Collector() = default;
    Collector(const Collector&) = default;
    Collector(Collector&&) noexcept = default;

    virtual ~Collector() noexcept = default;

    Collector& operator=(const Collector&) = default;
    Collector& operator=(Collector&&) noexcept = default;

    /// @brief Obtiene y devuelve los estados actuales
    /// @return El estado actual de los pines
    [[nodiscard]]
    virtual T getData() = 0;

    /// @brief Inicializa los pines a usar
    virtual void beginPins() = 0;
};

#endif // !COLLECTOR_HEADER