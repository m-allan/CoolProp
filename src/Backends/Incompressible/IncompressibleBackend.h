
#ifndef INCOMPRESSIBLEBACKEND_H_
#define INCOMPRESSIBLEBACKEND_H_

#include "IncompressibleFluid.h"
#include "AbstractState.h"
#include "Exceptions.h"

#include <vector>

namespace CoolProp {

class IncompressibleBackend : public AbstractState  {
protected:
    int Ncomp;
    bool _mole_fractions_set;
    static bool _REFPROP_supported;
    std::vector<long double> mass_fractions;
    IncompressibleFluid *fluid;
public:
    IncompressibleBackend(){};
    virtual ~IncompressibleBackend(){};

    /// The instantiator
    /// @param fluid_name the string with the fluid name
    IncompressibleBackend(const std::string &fluid_name);
    /// The instantiator
	/// @param fluid_names The vector of strings of the fluid components, without file ending
	IncompressibleBackend(const std::vector<std::string> &component_names);

    // Incompressible backend uses mole fractions
    bool using_mole_fractions(){return false;};

    /// Updating function for incompressible fluid
    /**
    In this function we take a pair of thermodynamic states, those defined in the input_pairs
    enumeration and update all the internal variables that we can.

    @param input_pair Integer key from CoolProp::input_pairs to the two inputs that will be passed to the function
    @param value1 First input value
    @param value2 Second input value
    */
    void update(long input_pair, double value1, double value2);

    /// Set the mole fractions
    /**
    @param mole_fractions The vector of mole fractions of the components
    */
    void set_mole_fractions(const std::vector<long double> &mole_fractions);

    /// Set the mass fractions
    /**
    @param mass_fractions The vector of mass fractions of the components
    */
    void set_mass_fractions(const std::vector<long double> &mass_fractions);

    /// Check if the mole fractions have been set, etc.
    void check_status();
        
    /// Calculate T given pressure and density
    /**
    @param rhomass The mass density in kg/m^3
    @param p The pressure in Pa
    @returns T The temperature in K
    */
    long double DmassP_flash(long double rhomass, long double p);
    /// Calculate T given pressure and enthalpy
    /**
    @param hmass The mass enthalpy in J/kg
    @param p The pressure in Pa
    @returns T The temperature in K
    */
    long double HmassP_flash(long double hmass, long double p);
    /// Calculate T given pressure and entropy
    /**
    @param smass The mass entropy in J/kg/K
    @param p The pressure in Pa
    @returns T The temperature in K
    */
    long double PSmass_flash(long double p, long double smass);
    
    /// Calculate T given pressure and internal energy
    /**
    @param umass The mass internal energy in J/kg
    @param p The pressure in Pa
    @returns T The temperature in K
    */
    long double PUmass_flash(long double p, long double umass);

    /// Get the viscosity [Pa-s]
    long double calc_viscosity(void);
    /// Get the thermal conductivity [W/m/K] (based on the temperature and density in the state class)
    long double calc_conductivity(void);
};

} /* namespace CoolProp */
#endif /* INCOMPRESSIBLEBACKEND_H_ */
