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
#include "DistributionGaussian.pypp.h"

namespace bp = boost::python;

struct DistributionGaussian_wrapper : DistributionGaussian, bp::wrapper< DistributionGaussian > {

    DistributionGaussian_wrapper(DistributionGaussian const & arg )
    : DistributionGaussian( arg )
      , bp::wrapper< DistributionGaussian >(){
        // copy constructor
        
    }

    DistributionGaussian_wrapper(double mean, double std_dev )
    : DistributionGaussian( mean, std_dev )
      , bp::wrapper< DistributionGaussian >(){
        // constructor
    
    }

    virtual double getMean(  ) const  {
        if( bp::override func_getMean = this->get_override( "getMean" ) )
            return func_getMean(  );
        else
            return this->DistributionGaussian::getMean(  );
    }
    
    
    double default_getMean(  ) const  {
        return DistributionGaussian::getMean( );
    }

    virtual double probabilityDensity( double x ) const  {
        if( bp::override func_probabilityDensity = this->get_override( "probabilityDensity" ) )
            return func_probabilityDensity( x );
        else
            return this->DistributionGaussian::probabilityDensity( x );
    }
    
    
    double default_probabilityDensity( double x ) const  {
        return DistributionGaussian::probabilityDensity( x );
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
        if( dynamic_cast< DistributionGaussian_wrapper * >( boost::addressof( inst ) ) ){
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

void register_DistributionGaussian_class(){

    { //::DistributionGaussian
        typedef bp::class_< DistributionGaussian_wrapper, bp::bases< IDistribution1D > > DistributionGaussian_exposer_t;
        DistributionGaussian_exposer_t DistributionGaussian_exposer = DistributionGaussian_exposer_t( "DistributionGaussian", bp::init< double, double >(( bp::arg("mean"), bp::arg("std_dev") )) );
        bp::scope DistributionGaussian_scope( DistributionGaussian_exposer );
        { //::DistributionGaussian::clone
        
            typedef ::DistributionGaussian * ( ::DistributionGaussian::*clone_function_type )(  ) const;
            
            DistributionGaussian_exposer.def( 
                "clone"
                , clone_function_type( &::DistributionGaussian::clone )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::DistributionGaussian::getMean
        
            typedef double ( ::DistributionGaussian::*getMean_function_type )(  ) const;
            typedef double ( DistributionGaussian_wrapper::*default_getMean_function_type )(  ) const;
            
            DistributionGaussian_exposer.def( 
                "getMean"
                , getMean_function_type(&::DistributionGaussian::getMean)
                , default_getMean_function_type(&DistributionGaussian_wrapper::default_getMean) );
        
        }
        { //::DistributionGaussian::probabilityDensity
        
            typedef double ( ::DistributionGaussian::*probabilityDensity_function_type )( double ) const;
            typedef double ( DistributionGaussian_wrapper::*default_probabilityDensity_function_type )( double ) const;
            
            DistributionGaussian_exposer.def( 
                "probabilityDensity"
                , probabilityDensity_function_type(&::DistributionGaussian::probabilityDensity)
                , default_probabilityDensity_function_type(&DistributionGaussian_wrapper::default_probabilityDensity)
                , ( bp::arg("x") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( DistributionGaussian_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            DistributionGaussian_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&DistributionGaussian_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( DistributionGaussian_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            DistributionGaussian_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&DistributionGaussian_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( DistributionGaussian_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            DistributionGaussian_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&DistributionGaussian_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( DistributionGaussian_wrapper::*default_printParameters_function_type )(  ) const;
            
            DistributionGaussian_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&DistributionGaussian_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            DistributionGaussian_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &DistributionGaussian_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( DistributionGaussian_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            DistributionGaussian_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&DistributionGaussian_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( DistributionGaussian_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            DistributionGaussian_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&DistributionGaussian_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
