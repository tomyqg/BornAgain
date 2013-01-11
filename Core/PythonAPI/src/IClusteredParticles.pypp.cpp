// This file has been generated by Py++.

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "BasicVector3D.h"
#include "Experiment.h"
#include "FormFactorCrystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorFullSphere.h"
#include "FormFactorGauss.h"
#include "FormFactorLorentz.h"
#include "FormFactorPrism3.h"
#include "FormFactorPyramid.h"
#include "FormFactorSphereGaussianRadius.h"
#include "GISASExperiment.h"
#include "HomogeneousMaterial.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IDecoration.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "IMaterial.h"
#include "IParameterized.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISelectionRule.h"
#include "ISingleton.h"
#include "Lattice.h"
#include "LatticeBasis.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "LayerRoughness.h"
#include "MaterialManager.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "Crystal.h"
#include "ParticleDecoration.h"
#include "OpticalFresnel.h"
#include "ParameterPool.h"
#include "ParticleInfo.h"
#include "DiffuseParticleInfo.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "RealParameterWrapper.h"
#include "Transform3D.h"
#include "Units.h"
#include "Types.h"
#include "IClusteredParticles.pypp.h"

namespace bp = boost::python;

struct IClusteredParticles_wrapper : IClusteredParticles, bp::wrapper< IClusteredParticles > {

    IClusteredParticles_wrapper( )
    : IClusteredParticles( )
      , bp::wrapper< IClusteredParticles >(){
        // null constructor
    
    }

    virtual ::IClusteredParticles * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->IClusteredParticles::clone(  );
        }
    }
    
    ::IClusteredParticles * default_clone(  ) const  {
        return IClusteredParticles::clone( );
    }

    virtual ::std::vector< DiffuseParticleInfo* > * createDiffuseParticleInfo( ::ParticleInfo const & parent_info ) const  {
        if( bp::override func_createDiffuseParticleInfo = this->get_override( "createDiffuseParticleInfo" ) )
            return func_createDiffuseParticleInfo( boost::ref(parent_info) );
        else{
            return this->IClusteredParticles::createDiffuseParticleInfo( boost::ref(parent_info) );
        }
    }
    
    ::std::vector< DiffuseParticleInfo* > * default_createDiffuseParticleInfo( ::ParticleInfo const & parent_info ) const  {
        return IClusteredParticles::createDiffuseParticleInfo( boost::ref(parent_info) );
    }

    virtual ::IFormFactor * createTotalFormFactor( ::IFormFactor const & meso_crystal_form_factor, ::complex_t ambient_refractive_index ) const  {
        if( bp::override func_createTotalFormFactor = this->get_override( "createTotalFormFactor" ) )
            return func_createTotalFormFactor( boost::ref(meso_crystal_form_factor), ambient_refractive_index );
        else{
            return this->IClusteredParticles::createTotalFormFactor( boost::ref(meso_crystal_form_factor), ambient_refractive_index );
        }
    }
    
    ::IFormFactor * default_createTotalFormFactor( ::IFormFactor const & meso_crystal_form_factor, ::complex_t ambient_refractive_index ) const  {
        return IClusteredParticles::createTotalFormFactor( boost::ref(meso_crystal_form_factor), ambient_refractive_index );
    }

    virtual void setAmbientRefractiveIndex( ::complex_t refractive_index ){
        bp::override func_setAmbientRefractiveIndex = this->get_override( "setAmbientRefractiveIndex" );
        func_setAmbientRefractiveIndex( refractive_index );
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

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ICompositeSample::getCompositeSample( );
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

    virtual void print_structure(  ) {
        if( bp::override func_print_structure = this->get_override( "print_structure" ) )
            func_print_structure(  );
        else{
            this->ISample::print_structure(  );
        }
    }
    
    void default_print_structure(  ) {
        ISample::print_structure( );
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

    virtual ::size_t size(  ) const  {
        if( bp::override func_size = this->get_override( "size" ) )
            return func_size(  );
        else{
            return this->ICompositeSample::size(  );
        }
    }
    
    ::size_t default_size(  ) const  {
        return ICompositeSample::size( );
    }

};

void register_IClusteredParticles_class(){

    bp::class_< IClusteredParticles_wrapper, bp::bases< ICompositeSample >, boost::noncopyable >( "IClusteredParticles", bp::init< >() )    
        .def( 
            "clone"
            , (::IClusteredParticles * ( ::IClusteredParticles::* )(  ) const)(&::IClusteredParticles::clone)
            , (::IClusteredParticles * ( IClusteredParticles_wrapper::* )(  ) const)(&IClusteredParticles_wrapper::default_clone)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "createDiffuseParticleInfo"
            , (::std::vector< DiffuseParticleInfo* > * ( ::IClusteredParticles::* )( ::ParticleInfo const & ) const)(&::IClusteredParticles::createDiffuseParticleInfo)
            , (::std::vector< DiffuseParticleInfo* > * ( IClusteredParticles_wrapper::* )( ::ParticleInfo const & ) const)(&IClusteredParticles_wrapper::default_createDiffuseParticleInfo)
            , ( bp::arg("parent_info") )
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "createTotalFormFactor"
            , (::IFormFactor * ( ::IClusteredParticles::* )( ::IFormFactor const &,::complex_t ) const)(&::IClusteredParticles::createTotalFormFactor)
            , (::IFormFactor * ( IClusteredParticles_wrapper::* )( ::IFormFactor const &,::complex_t ) const)(&IClusteredParticles_wrapper::default_createTotalFormFactor)
            , ( bp::arg("meso_crystal_form_factor"), bp::arg("ambient_refractive_index") )
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "setAmbientRefractiveIndex"
            , bp::pure_virtual( (void ( ::IClusteredParticles::* )( ::complex_t ) )(&::IClusteredParticles::setAmbientRefractiveIndex) )
            , ( bp::arg("refractive_index") ) )    
        .def( 
            "areParametersChanged"
            , (bool ( ::IParameterized::* )(  ) )(&::IParameterized::areParametersChanged)
            , (bool ( IClusteredParticles_wrapper::* )(  ) )(&IClusteredParticles_wrapper::default_areParametersChanged) )    
        .def( 
            "createParameterTree"
            , (::ParameterPool * ( ::IParameterized::* )(  ) const)(&::IParameterized::createParameterTree)
            , (::ParameterPool * ( IClusteredParticles_wrapper::* )(  ) const)(&IClusteredParticles_wrapper::default_createParameterTree)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "getCompositeSample"
            , (::ICompositeSample * ( ::ICompositeSample::* )(  ) )(&::ICompositeSample::getCompositeSample)
            , (::ICompositeSample * ( IClusteredParticles_wrapper::* )(  ) )(&IClusteredParticles_wrapper::default_getCompositeSample)
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "getCompositeSample"
            , (::ICompositeSample const * ( ::ICompositeSample::* )(  ) const)(&::ICompositeSample::getCompositeSample)
            , (::ICompositeSample const * ( IClusteredParticles_wrapper::* )(  ) const)(&IClusteredParticles_wrapper::default_getCompositeSample)
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "printParameters"
            , (void ( ::IParameterized::* )(  ) const)(&::IParameterized::printParameters)
            , (void ( IClusteredParticles_wrapper::* )(  ) const)(&IClusteredParticles_wrapper::default_printParameters) )    
        .def( 
            "print_structure"
            , (void ( ::ISample::* )(  ) )(&::ISample::print_structure)
            , (void ( IClusteredParticles_wrapper::* )(  ) )(&IClusteredParticles_wrapper::default_print_structure) )    
        .def( 
            "setParametersAreChanged"
            , (void ( ::IParameterized::* )(  ) )(&::IParameterized::setParametersAreChanged)
            , (void ( IClusteredParticles_wrapper::* )(  ) )(&IClusteredParticles_wrapper::default_setParametersAreChanged) )    
        .def( 
            "size"
            , (::size_t ( ::ICompositeSample::* )(  ) const)(&::ICompositeSample::size)
            , (::size_t ( IClusteredParticles_wrapper::* )(  ) const)(&IClusteredParticles_wrapper::default_size) );

}
