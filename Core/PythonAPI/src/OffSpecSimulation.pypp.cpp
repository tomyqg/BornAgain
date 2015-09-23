// This file has been generated by Py++.

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Automatically generated boost::python code for BornAgain Python bindings
//! @brief     Automatically generated boost::python code for BornAgain Python bindings
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Juelich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "OffSpecSimulation.pypp.h"

namespace bp = boost::python;

struct OffSpecSimulation_wrapper : OffSpecSimulation, bp::wrapper< OffSpecSimulation > {

    OffSpecSimulation_wrapper( )
    : OffSpecSimulation( )
      , bp::wrapper< OffSpecSimulation >(){
        // null constructor
    m_pyobj = 0;
    }

    virtual ::OffSpecSimulation * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->OffSpecSimulation::clone(  );
        }
    }
    
    ::OffSpecSimulation * default_clone(  ) const  {
        return OffSpecSimulation::clone( );
    }

    virtual ::OutputData< double > * getIntensityData(  ) const  {
        if( bp::override func_getIntensityData = this->get_override( "getIntensityData" ) )
            return func_getIntensityData(  );
        else{
            return this->OffSpecSimulation::getIntensityData(  );
        }
    }
    
    ::OutputData< double > * default_getIntensityData(  ) const  {
        return OffSpecSimulation::getIntensityData( );
    }

    virtual int getNumberOfSimulationElements(  ) const  {
        if( bp::override func_getNumberOfSimulationElements = this->get_override( "getNumberOfSimulationElements" ) )
            return func_getNumberOfSimulationElements(  );
        else{
            return this->OffSpecSimulation::getNumberOfSimulationElements(  );
        }
    }
    
    int default_getNumberOfSimulationElements(  ) const  {
        return OffSpecSimulation::getNumberOfSimulationElements( );
    }

    virtual double getWavelength(  ) const  {
        if( bp::override func_getWavelength = this->get_override( "getWavelength" ) )
            return func_getWavelength(  );
        else{
            return this->OffSpecSimulation::getWavelength(  );
        }
    }
    
    double default_getWavelength(  ) const  {
        return OffSpecSimulation::getWavelength( );
    }

    virtual void prepareSimulation(  ) {
        if( bp::override func_prepareSimulation = this->get_override( "prepareSimulation" ) )
            func_prepareSimulation(  );
        else{
            this->OffSpecSimulation::prepareSimulation(  );
        }
    }
    
    void default_prepareSimulation(  ) {
        OffSpecSimulation::prepareSimulation( );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else{
            this->IParameterized::clearParameterPool(  );
        }
    }
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void registerParameter( ::std::string const & name, double * parpointer, ::AttLimits const & limits=AttLimits::limitless( ) ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer, limits );
        }
        else{
            IParameterized::registerParameter( name, parpointer, boost::ref(limits) );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer, ::AttLimits const & limits=AttLimits::limitless( ) ){
        if( dynamic_cast< OffSpecSimulation_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ), limits);
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ), limits);
        }
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else{
            return this->IParameterized::setParameterValue( name, value );
        }
    }
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

    virtual void transferToCPP(  ) {
        
        if( !this->m_pyobj) {
            this->m_pyobj = boost::python::detail::wrapper_base_::get_owner(*this);
            Py_INCREF(this->m_pyobj);
        }
        
        if( bp::override func_transferToCPP = this->get_override( "transferToCPP" ) )
            func_transferToCPP(  );
        else{
            this->ICloneable::transferToCPP(  );
        }
    }
    
    void default_transferToCPP(  ) {
        
        if( !this->m_pyobj) {
            this->m_pyobj = boost::python::detail::wrapper_base_::get_owner(*this);
            Py_INCREF(this->m_pyobj);
        }
        
        ICloneable::transferToCPP( );
    }

    PyObject* m_pyobj;

};

void register_OffSpecSimulation_class(){

    { //::OffSpecSimulation
        typedef bp::class_< OffSpecSimulation_wrapper, bp::bases< Simulation >, std::auto_ptr< OffSpecSimulation_wrapper >, boost::noncopyable > OffSpecSimulation_exposer_t;
        OffSpecSimulation_exposer_t OffSpecSimulation_exposer = OffSpecSimulation_exposer_t( "OffSpecSimulation", "Main class to run an off-specular simulation.", bp::init< >() );
        bp::scope OffSpecSimulation_scope( OffSpecSimulation_exposer );
        { //::OffSpecSimulation::clone
        
            typedef ::OffSpecSimulation * ( ::OffSpecSimulation::*clone_function_type)(  ) const;
            typedef ::OffSpecSimulation * ( OffSpecSimulation_wrapper::*default_clone_function_type)(  ) const;
            
            OffSpecSimulation_exposer.def( 
                "clone"
                , clone_function_type(&::OffSpecSimulation::clone)
                , default_clone_function_type(&OffSpecSimulation_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::OffSpecSimulation::getInstrument
        
            typedef ::Instrument const & ( ::OffSpecSimulation::*getInstrument_function_type)(  ) const;
            
            OffSpecSimulation_exposer.def( 
                "getInstrument"
                , getInstrument_function_type( &::OffSpecSimulation::getInstrument )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "Returns the instrument containing beam and detector information." );
        
        }
        { //::OffSpecSimulation::getIntensityData
        
            typedef ::OutputData< double > * ( ::OffSpecSimulation::*getIntensityData_function_type)(  ) const;
            typedef ::OutputData< double > * ( OffSpecSimulation_wrapper::*default_getIntensityData_function_type)(  ) const;
            
            OffSpecSimulation_exposer.def( 
                "getIntensityData"
                , getIntensityData_function_type(&::OffSpecSimulation::getIntensityData)
                , default_getIntensityData_function_type(&OffSpecSimulation_wrapper::default_getIntensityData)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::OffSpecSimulation::getNumberOfSimulationElements
        
            typedef int ( ::OffSpecSimulation::*getNumberOfSimulationElements_function_type)(  ) const;
            typedef int ( OffSpecSimulation_wrapper::*default_getNumberOfSimulationElements_function_type)(  ) const;
            
            OffSpecSimulation_exposer.def( 
                "getNumberOfSimulationElements"
                , getNumberOfSimulationElements_function_type(&::OffSpecSimulation::getNumberOfSimulationElements)
                , default_getNumberOfSimulationElements_function_type(&OffSpecSimulation_wrapper::default_getNumberOfSimulationElements) );
        
        }
        { //::OffSpecSimulation::getWavelength
        
            typedef double ( ::OffSpecSimulation::*getWavelength_function_type)(  ) const;
            typedef double ( OffSpecSimulation_wrapper::*default_getWavelength_function_type)(  ) const;
            
            OffSpecSimulation_exposer.def( 
                "getWavelength"
                , getWavelength_function_type(&::OffSpecSimulation::getWavelength)
                , default_getWavelength_function_type(&OffSpecSimulation_wrapper::default_getWavelength) );
        
        }
        { //::OffSpecSimulation::prepareSimulation
        
            typedef void ( ::OffSpecSimulation::*prepareSimulation_function_type)(  ) ;
            typedef void ( OffSpecSimulation_wrapper::*default_prepareSimulation_function_type)(  ) ;
            
            OffSpecSimulation_exposer.def( 
                "prepareSimulation"
                , prepareSimulation_function_type(&::OffSpecSimulation::prepareSimulation)
                , default_prepareSimulation_function_type(&OffSpecSimulation_wrapper::default_prepareSimulation) );
        
        }
        { //::OffSpecSimulation::removeDetectorResolutionFunction
        
            typedef void ( ::OffSpecSimulation::*removeDetectorResolutionFunction_function_type)(  ) ;
            
            OffSpecSimulation_exposer.def( 
                "removeDetectorResolutionFunction"
                , removeDetectorResolutionFunction_function_type( &::OffSpecSimulation::removeDetectorResolutionFunction )
                , "Removes detector resolution function." );
        
        }
        { //::OffSpecSimulation::setAnalyzerProperties
        
            typedef void ( ::OffSpecSimulation::*setAnalyzerProperties_function_type)( ::kvector_t const &,double,double ) ;
            
            OffSpecSimulation_exposer.def( 
                "setAnalyzerProperties"
                , setAnalyzerProperties_function_type( &::OffSpecSimulation::setAnalyzerProperties )
                , ( bp::arg("direction"), bp::arg("efficiency"), bp::arg("total_transmission")=1.0e+0 )
                , "Sets the polarization analyzer characteristics of the detector." );
        
        }
        { //::OffSpecSimulation::setBeamIntensity
        
            typedef void ( ::OffSpecSimulation::*setBeamIntensity_function_type)( double ) ;
            
            OffSpecSimulation_exposer.def( 
                "setBeamIntensity"
                , setBeamIntensity_function_type( &::OffSpecSimulation::setBeamIntensity )
                , ( bp::arg("intensity") )
                , "Sets beam intensity from here (forwarded to Instrument)." );
        
        }
        { //::OffSpecSimulation::setBeamParameters
        
            typedef void ( ::OffSpecSimulation::*setBeamParameters_function_type)( double,::IAxis const &,double ) ;
            
            OffSpecSimulation_exposer.def( 
                "setBeamParameters"
                , setBeamParameters_function_type( &::OffSpecSimulation::setBeamParameters )
                , ( bp::arg("lambda"), bp::arg("alpha_axis"), bp::arg("phi_i") )
                , "Sets beam parameters from here (forwarded to Instrument)." );
        
        }
        { //::OffSpecSimulation::setBeamPolarization
        
            typedef void ( ::OffSpecSimulation::*setBeamPolarization_function_type)( ::kvector_t const & ) ;
            
            OffSpecSimulation_exposer.def( 
                "setBeamPolarization"
                , setBeamPolarization_function_type( &::OffSpecSimulation::setBeamPolarization )
                , ( bp::arg("bloch_vector") )
                , "Sets the beam polarization according to the given Bloch vector." );
        
        }
        { //::OffSpecSimulation::setDetectorParameters
        
            typedef void ( ::OffSpecSimulation::*setDetectorParameters_function_type)( ::OutputData< double > const & ) ;
            
            OffSpecSimulation_exposer.def( 
                "setDetectorParameters"
                , setDetectorParameters_function_type( &::OffSpecSimulation::setDetectorParameters )
                , ( bp::arg("output_data") )
                , "Sets detector parameters using axes of output data." );
        
        }
        { //::OffSpecSimulation::setDetectorParameters
        
            typedef void ( ::OffSpecSimulation::*setDetectorParameters_function_type)( ::std::size_t,double,double,::std::size_t,double,double,bool ) ;
            
            OffSpecSimulation_exposer.def( 
                "setDetectorParameters"
                , setDetectorParameters_function_type( &::OffSpecSimulation::setDetectorParameters )
                , ( bp::arg("n_phi"), bp::arg("phi_f_min"), bp::arg("phi_f_max"), bp::arg("n_alpha"), bp::arg("alpha_f_min"), bp::arg("alpha_f_max"), bp::arg("isgisaxs_style")=(bool)(false) )
                , "Sets detector parameters using angle ranges." );
        
        }
        { //::OffSpecSimulation::setDetectorResolutionFunction
        
            typedef void ( ::OffSpecSimulation::*setDetectorResolutionFunction_function_type)( ::IResolutionFunction2D const & ) ;
            
            OffSpecSimulation_exposer.def( 
                "setDetectorResolutionFunction"
                , setDetectorResolutionFunction_function_type( &::OffSpecSimulation::setDetectorResolutionFunction )
                , ( bp::arg("resolution_function") )
                , "Define resolution function for detector." );
        
        }
        { //::OffSpecSimulation::setInstrument
        
            typedef void ( ::OffSpecSimulation::*setInstrument_function_type)( ::Instrument const & ) ;
            
            OffSpecSimulation_exposer.def( 
                "setInstrument"
                , setInstrument_function_type( &::OffSpecSimulation::setInstrument )
                , ( bp::arg("instrument") )
                , "Sets the instrument containing beam and detector information." );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type)(  ) ;
            typedef bool ( OffSpecSimulation_wrapper::*default_areParametersChanged_function_type)(  ) ;
            
            OffSpecSimulation_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&OffSpecSimulation_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type)(  ) ;
            typedef void ( OffSpecSimulation_wrapper::*default_clearParameterPool_function_type)(  ) ;
            
            OffSpecSimulation_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&OffSpecSimulation_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type)(  ) const;
            typedef ::ParameterPool * ( OffSpecSimulation_wrapper::*default_createParameterTree_function_type)(  ) const;
            
            OffSpecSimulation_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&OffSpecSimulation_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type)(  ) const;
            typedef void ( OffSpecSimulation_wrapper::*default_printParameters_function_type)(  ) const;
            
            OffSpecSimulation_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&OffSpecSimulation_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int,::AttLimits const & );
            
            OffSpecSimulation_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &OffSpecSimulation_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer"), bp::arg("limits")=AttLimits::limitless( ) )
                , "main method to register data address in the pool." );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type)( ::std::string const &,double ) ;
            typedef bool ( OffSpecSimulation_wrapper::*default_setParameterValue_function_type)( ::std::string const &,double ) ;
            
            OffSpecSimulation_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&OffSpecSimulation_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type)(  ) ;
            typedef void ( OffSpecSimulation_wrapper::*default_setParametersAreChanged_function_type)(  ) ;
            
            OffSpecSimulation_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&OffSpecSimulation_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICloneable::transferToCPP
        
            typedef void ( ::ICloneable::*transferToCPP_function_type)(  ) ;
            typedef void ( OffSpecSimulation_wrapper::*default_transferToCPP_function_type)(  ) ;
            
            OffSpecSimulation_exposer.def( 
                "transferToCPP"
                , transferToCPP_function_type(&::ICloneable::transferToCPP)
                , default_transferToCPP_function_type(&OffSpecSimulation_wrapper::default_transferToCPP) );
        
        }
    }

}
