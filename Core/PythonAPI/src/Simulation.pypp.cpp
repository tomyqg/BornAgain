// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "Simulation.pypp.h"

namespace bp = boost::python;

struct Simulation_wrapper : Simulation, bp::wrapper< Simulation > {

    Simulation_wrapper( )
    : Simulation( )
      , bp::wrapper< Simulation >(){
        // null constructor
    
    }

    virtual ::Simulation * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else
            return this->Simulation::clone(  );
    }
    
    
    ::Simulation * default_clone(  ) const  {
        return Simulation::clone( );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else
            return this->IParameterized::areParametersChanged(  );
    }
    
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else
            this->IParameterized::clearParameterPool(  );
    }
    
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else
            return this->IParameterized::createParameterTree(  );
    }
    
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else
            this->IParameterized::printParameters(  );
    }
    
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void registerParameter( ::std::string const & name, double * parpointer ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer );
        }
        else{
            IParameterized::registerParameter( name, parpointer );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer ){
        if( dynamic_cast< Simulation_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else
            return this->IParameterized::setParameterValue( name, value );
    }
    
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else
            this->IParameterized::setParametersAreChanged(  );
    }
    
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

};

void register_Simulation_class(){

    { //::Simulation
        typedef bp::class_< Simulation_wrapper, bp::bases< ICloneable, IParameterized >, boost::noncopyable > Simulation_exposer_t;
        Simulation_exposer_t Simulation_exposer = Simulation_exposer_t( "Simulation", bp::init< >() );
        bp::scope Simulation_scope( Simulation_exposer );
        { //::Simulation::clone
        
            typedef ::Simulation * ( ::Simulation::*clone_function_type )(  ) const;
            typedef ::Simulation * ( Simulation_wrapper::*default_clone_function_type )(  ) const;
            
            Simulation_exposer.def( 
                "clone"
                , clone_function_type(&::Simulation::clone)
                , default_clone_function_type(&Simulation_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::Simulation::getInstrument
        
            typedef ::Instrument const & ( ::Simulation::*getInstrument_function_type )(  ) const;
            
            Simulation_exposer.def( 
                "getInstrument"
                , getInstrument_function_type( &::Simulation::getInstrument )
                , bp::return_value_policy< bp::copy_const_reference >() );
        
        }
        { //::Simulation::getIntensityData
        
            typedef ::OutputData< double > * ( ::Simulation::*getIntensityData_function_type )(  ) const;
            
            Simulation_exposer.def( 
                "getIntensityData"
                , getIntensityData_function_type( &::Simulation::getIntensityData )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::Simulation::getPolarizedIntensityData
        
            typedef ::OutputData< double > * ( ::Simulation::*getPolarizedIntensityData_function_type )( int,int ) const;
            
            Simulation_exposer.def( 
                "getPolarizedIntensityData"
                , getPolarizedIntensityData_function_type( &::Simulation::getPolarizedIntensityData )
                , ( bp::arg("row"), bp::arg("column") )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::Simulation::getSample
        
            typedef ::ISample * ( ::Simulation::*getSample_function_type )(  ) const;
            
            Simulation_exposer.def( 
                "getSample"
                , getSample_function_type( &::Simulation::getSample )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Simulation::getSampleBuilder
        
            typedef ::ISampleBuilder * ( ::Simulation::*getSampleBuilder_function_type )(  ) const;
            
            Simulation_exposer.def( 
                "getSampleBuilder"
                , getSampleBuilder_function_type( &::Simulation::getSampleBuilder )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Simulation::getSimulationParameters
        
            typedef ::SimulationParameters ( ::Simulation::*getSimulationParameters_function_type )(  ) const;
            
            Simulation_exposer.def( 
                "getSimulationParameters"
                , getSimulationParameters_function_type( &::Simulation::getSimulationParameters ) );
        
        }
        { //::Simulation::normalize
        
            typedef void ( ::Simulation::*normalize_function_type )(  ) ;
            
            Simulation_exposer.def( 
                "normalize"
                , normalize_function_type( &::Simulation::normalize ) );
        
        }
        { //::Simulation::prepareSimulation
        
            typedef void ( ::Simulation::*prepareSimulation_function_type )(  ) ;
            
            Simulation_exposer.def( 
                "prepareSimulation"
                , prepareSimulation_function_type( &::Simulation::prepareSimulation ) );
        
        }
        { //::Simulation::runSimulation
        
            typedef void ( ::Simulation::*runSimulation_function_type )(  ) ;
            
            Simulation_exposer.def( 
                "runSimulation"
                , runSimulation_function_type( &::Simulation::runSimulation ) );
        
        }
        { //::Simulation::runSimulationElement
        
            typedef void ( ::Simulation::*runSimulationElement_function_type )( ::std::size_t ) ;
            
            Simulation_exposer.def( 
                "runSimulationElement"
                , runSimulationElement_function_type( &::Simulation::runSimulationElement )
                , ( bp::arg("index") ) );
        
        }
        { //::Simulation::setBeamIntensity
        
            typedef void ( ::Simulation::*setBeamIntensity_function_type )( double ) ;
            
            Simulation_exposer.def( 
                "setBeamIntensity"
                , setBeamIntensity_function_type( &::Simulation::setBeamIntensity )
                , ( bp::arg("intensity") ) );
        
        }
        { //::Simulation::setBeamParameters
        
            typedef void ( ::Simulation::*setBeamParameters_function_type )( double,double,double ) ;
            
            Simulation_exposer.def( 
                "setBeamParameters"
                , setBeamParameters_function_type( &::Simulation::setBeamParameters )
                , ( bp::arg("lambda"), bp::arg("alpha_i"), bp::arg("phi_i") ) );
        
        }
        { //::Simulation::setDetectorParameters
        
            typedef void ( ::Simulation::*setDetectorParameters_function_type )( ::OutputData< double > const & ) ;
            
            Simulation_exposer.def( 
                "setDetectorParameters"
                , setDetectorParameters_function_type( &::Simulation::setDetectorParameters )
                , ( bp::arg("output_data") ) );
        
        }
        { //::Simulation::setDetectorParameters
        
            typedef void ( ::Simulation::*setDetectorParameters_function_type )( ::std::size_t,double,double,::std::size_t,double,double,bool ) ;
            
            Simulation_exposer.def( 
                "setDetectorParameters"
                , setDetectorParameters_function_type( &::Simulation::setDetectorParameters )
                , ( bp::arg("n_phi"), bp::arg("phi_f_min"), bp::arg("phi_f_max"), bp::arg("n_alpha"), bp::arg("alpha_f_min"), bp::arg("alpha_f_max"), bp::arg("isgisaxs_style")=(bool)(false) ) );
        
        }
        { //::Simulation::setDetectorParameters
        
            typedef void ( ::Simulation::*setDetectorParameters_function_type )( ::DetectorParameters const & ) ;
            
            Simulation_exposer.def( 
                "setDetectorParameters"
                , setDetectorParameters_function_type( &::Simulation::setDetectorParameters )
                , ( bp::arg("params") ) );
        
        }
        { //::Simulation::setDetectorResolutionFunction
        
            typedef void ( ::Simulation::*setDetectorResolutionFunction_function_type )( ::IResolutionFunction2D const & ) ;
            
            Simulation_exposer.def( 
                "setDetectorResolutionFunction"
                , setDetectorResolutionFunction_function_type( &::Simulation::setDetectorResolutionFunction )
                , ( bp::arg("p_resolution_function") ) );
        
        }
        { //::Simulation::setInstrument
        
            typedef void ( ::Simulation::*setInstrument_function_type )( ::Instrument const & ) ;
            
            Simulation_exposer.def( 
                "setInstrument"
                , setInstrument_function_type( &::Simulation::setInstrument )
                , ( bp::arg("instrument") ) );
        
        }
        { //::Simulation::setSample
        
            typedef void ( ::Simulation::*setSample_function_type )( ::ISample const & ) ;
            
            Simulation_exposer.def( 
                "setSample"
                , setSample_function_type( &::Simulation::setSample )
                , ( bp::arg("sample") ) );
        
        }
        { //::Simulation::setSampleBuilder
        
            typedef void ( ::Simulation::*setSampleBuilder_function_type )( ::ISampleBuilder * ) ;
            
            Simulation_exposer.def( 
                "setSampleBuilder"
                , setSampleBuilder_function_type( &::Simulation::setSampleBuilder )
                , ( bp::arg("p_sample_builder") ) );
        
        }
        { //::Simulation::setSimulationParameters
        
            typedef void ( ::Simulation::*setSimulationParameters_function_type )( ::SimulationParameters const & ) ;
            
            Simulation_exposer.def( 
                "setSimulationParameters"
                , setSimulationParameters_function_type( &::Simulation::setSimulationParameters )
                , ( bp::arg("sim_params") ) );
        
        }
        { //::Simulation::setThreadInfo
        
            typedef void ( ::Simulation::*setThreadInfo_function_type )( ::ThreadInfo const & ) ;
            
            Simulation_exposer.def( 
                "setThreadInfo"
                , setThreadInfo_function_type( &::Simulation::setThreadInfo )
                , ( bp::arg("thread_info") ) );
        
        }
        { //::Simulation::smearIntensityFromZAxisTilting
        
            typedef void ( ::Simulation::*smearIntensityFromZAxisTilting_function_type )(  ) ;
            
            Simulation_exposer.def( 
                "smearIntensityFromZAxisTilting"
                , smearIntensityFromZAxisTilting_function_type( &::Simulation::smearIntensityFromZAxisTilting ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( Simulation_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            Simulation_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&Simulation_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( Simulation_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            Simulation_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&Simulation_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( Simulation_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            Simulation_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&Simulation_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( Simulation_wrapper::*default_printParameters_function_type )(  ) const;
            
            Simulation_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&Simulation_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            Simulation_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &Simulation_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( Simulation_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            Simulation_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&Simulation_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( Simulation_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            Simulation_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&Simulation_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
