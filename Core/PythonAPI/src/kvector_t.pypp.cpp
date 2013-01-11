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
#include "kvector_t.pypp.h"

namespace bp = boost::python;

void register_kvector_t_class(){

    { //::Geometry::BasicVector3D< double >
        typedef bp::class_< Geometry::BasicVector3D< double > > kvector_t_exposer_t;
        kvector_t_exposer_t kvector_t_exposer = kvector_t_exposer_t( "kvector_t", bp::init< >() );
        bp::scope kvector_t_scope( kvector_t_exposer );
        bp::scope().attr("X") = (int)Geometry::BasicVector3D<double>::X;
        bp::scope().attr("Y") = (int)Geometry::BasicVector3D<double>::Y;
        bp::scope().attr("Z") = (int)Geometry::BasicVector3D<double>::Z;
        bp::scope().attr("NUM_COORDINATES") = (int)Geometry::BasicVector3D<double>::NUM_COORDINATES;
        bp::scope().attr("SIZE") = (int)Geometry::BasicVector3D<double>::SIZE;
        kvector_t_exposer.def( bp::init< double const &, double const &, double const & >(( bp::arg("x1"), bp::arg("y1"), bp::arg("z1") )) );
        { //::Geometry::BasicVector3D< double >::angle
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*angle_function_type )( ::Geometry::BasicVector3D< double > const & ) const;
            
            kvector_t_exposer.def( 
                "angle"
                , angle_function_type( &::Geometry::BasicVector3D< double >::angle )
                , ( bp::arg("v") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::cosTheta
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*cosTheta_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "cosTheta"
                , cosTheta_function_type( &::Geometry::BasicVector3D< double >::cosTheta ) );
        
        }
        { //::Geometry::BasicVector3D< double >::cross
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > ( exported_class_t::*cross_function_type )( ::Geometry::BasicVector3D< double > const & ) const;
            
            kvector_t_exposer.def( 
                "cross"
                , cross_function_type( &::Geometry::BasicVector3D< double >::cross )
                , ( bp::arg("v") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::dot
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*dot_function_type )( ::Geometry::BasicVector3D< double > const & ) const;
            
            kvector_t_exposer.def( 
                "dot"
                , dot_function_type( &::Geometry::BasicVector3D< double >::dot )
                , ( bp::arg("v") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::getPhi
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*getPhi_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "getPhi"
                , getPhi_function_type( &::Geometry::BasicVector3D< double >::getPhi ) );
        
        }
        { //::Geometry::BasicVector3D< double >::getR
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*getR_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "getR"
                , getR_function_type( &::Geometry::BasicVector3D< double >::getR ) );
        
        }
        { //::Geometry::BasicVector3D< double >::getTheta
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*getTheta_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "getTheta"
                , getTheta_function_type( &::Geometry::BasicVector3D< double >::getTheta ) );
        
        }
        { //::Geometry::BasicVector3D< double >::mag
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*mag_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "mag"
                , mag_function_type( &::Geometry::BasicVector3D< double >::mag ) );
        
        }
        { //::Geometry::BasicVector3D< double >::mag2
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*mag2_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "mag2"
                , mag2_function_type( &::Geometry::BasicVector3D< double >::mag2 ) );
        
        }
        { //::Geometry::BasicVector3D< double >::magxy
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*magxy_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "magxy"
                , magxy_function_type( &::Geometry::BasicVector3D< double >::magxy ) );
        
        }
        kvector_t_exposer.def( bp::self *= bp::other< double >() );
        kvector_t_exposer.def( bp::self += bp::self );
        kvector_t_exposer.def( bp::self -= bp::self );
        kvector_t_exposer.def( bp::self /= bp::other< double >() );
        { //::Geometry::BasicVector3D< double >::operator=
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > & ( exported_class_t::*assign_function_type )( ::Geometry::BasicVector3D< double > const & ) ;
            
            kvector_t_exposer.def( 
                "assign"
                , assign_function_type( &::Geometry::BasicVector3D< double >::operator= )
                , ( bp::arg("v") )
                , bp::return_self< >() );
        
        }
        { //::Geometry::BasicVector3D< double >::operator[]
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*__getitem___function_type )( int ) const;
            
            kvector_t_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::Geometry::BasicVector3D< double >::operator[] )
                , ( bp::arg("i") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::operator[]
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double & ( exported_class_t::*__getitem___function_type )( int ) ;
            
            kvector_t_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::Geometry::BasicVector3D< double >::operator[] )
                , ( bp::arg("i") )
                , bp::return_value_policy< bp::copy_non_const_reference >() );
        
        }
        { //::Geometry::BasicVector3D< double >::orthogonal
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > ( exported_class_t::*orthogonal_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "orthogonal"
                , orthogonal_function_type( &::Geometry::BasicVector3D< double >::orthogonal ) );
        
        }
        { //::Geometry::BasicVector3D< double >::perp
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*perp_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "perp"
                , perp_function_type( &::Geometry::BasicVector3D< double >::perp ) );
        
        }
        { //::Geometry::BasicVector3D< double >::perp
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*perp_function_type )( ::Geometry::BasicVector3D< double > const & ) const;
            
            kvector_t_exposer.def( 
                "perp"
                , perp_function_type( &::Geometry::BasicVector3D< double >::perp )
                , ( bp::arg("v") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::perp2
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*perp2_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "perp2"
                , perp2_function_type( &::Geometry::BasicVector3D< double >::perp2 ) );
        
        }
        { //::Geometry::BasicVector3D< double >::perp2
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*perp2_function_type )( ::Geometry::BasicVector3D< double > const & ) const;
            
            kvector_t_exposer.def( 
                "perp2"
                , perp2_function_type( &::Geometry::BasicVector3D< double >::perp2 )
                , ( bp::arg("v") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::phi
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*phi_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "phi"
                , phi_function_type( &::Geometry::BasicVector3D< double >::phi ) );
        
        }
        { //::Geometry::BasicVector3D< double >::r
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*r_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "r"
                , r_function_type( &::Geometry::BasicVector3D< double >::r ) );
        
        }
        { //::Geometry::BasicVector3D< double >::rho
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*rho_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "rho"
                , rho_function_type( &::Geometry::BasicVector3D< double >::rho ) );
        
        }
        { //::Geometry::BasicVector3D< double >::rotate
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > & ( exported_class_t::*rotate_function_type )( double,::Geometry::BasicVector3D< double > const & ) ;
            
            kvector_t_exposer.def( 
                "rotate"
                , rotate_function_type( &::Geometry::BasicVector3D< double >::rotate )
                , ( bp::arg("a"), bp::arg("v") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Geometry::BasicVector3D< double >::rotateX
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > & ( exported_class_t::*rotateX_function_type )( double ) ;
            
            kvector_t_exposer.def( 
                "rotateX"
                , rotateX_function_type( &::Geometry::BasicVector3D< double >::rotateX )
                , ( bp::arg("a") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Geometry::BasicVector3D< double >::rotateY
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > & ( exported_class_t::*rotateY_function_type )( double ) ;
            
            kvector_t_exposer.def( 
                "rotateY"
                , rotateY_function_type( &::Geometry::BasicVector3D< double >::rotateY )
                , ( bp::arg("a") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Geometry::BasicVector3D< double >::rotateZ
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > & ( exported_class_t::*rotateZ_function_type )( double ) ;
            
            kvector_t_exposer.def( 
                "rotateZ"
                , rotateZ_function_type( &::Geometry::BasicVector3D< double >::rotateZ )
                , ( bp::arg("a") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Geometry::BasicVector3D< double >::set
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*set_function_type )( double const &,double const &,double const & ) ;
            
            kvector_t_exposer.def( 
                "set"
                , set_function_type( &::Geometry::BasicVector3D< double >::set )
                , ( bp::arg("x1"), bp::arg("y1"), bp::arg("z1") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setLambdaAlphaPhi
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setLambdaAlphaPhi_function_type )( double const &,double const &,double const & ) ;
            
            kvector_t_exposer.def( 
                "setLambdaAlphaPhi"
                , setLambdaAlphaPhi_function_type( &::Geometry::BasicVector3D< double >::setLambdaAlphaPhi )
                , ( bp::arg("_lambda"), bp::arg("_alpha"), bp::arg("_phi") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setMag
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setMag_function_type )( double ) ;
            
            kvector_t_exposer.def( 
                "setMag"
                , setMag_function_type( &::Geometry::BasicVector3D< double >::setMag )
                , ( bp::arg("ma") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setPerp
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setPerp_function_type )( double ) ;
            
            kvector_t_exposer.def( 
                "setPerp"
                , setPerp_function_type( &::Geometry::BasicVector3D< double >::setPerp )
                , ( bp::arg("rh") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setPhi
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setPhi_function_type )( double ) ;
            
            kvector_t_exposer.def( 
                "setPhi"
                , setPhi_function_type( &::Geometry::BasicVector3D< double >::setPhi )
                , ( bp::arg("ph") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setR
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setR_function_type )( double ) ;
            
            kvector_t_exposer.def( 
                "setR"
                , setR_function_type( &::Geometry::BasicVector3D< double >::setR )
                , ( bp::arg("ma") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setTheta
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setTheta_function_type )( double ) ;
            
            kvector_t_exposer.def( 
                "setTheta"
                , setTheta_function_type( &::Geometry::BasicVector3D< double >::setTheta )
                , ( bp::arg("th") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setX
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setX_function_type )( double const & ) ;
            
            kvector_t_exposer.def( 
                "setX"
                , setX_function_type( &::Geometry::BasicVector3D< double >::setX )
                , ( bp::arg("a") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setXYZ
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setXYZ_function_type )( double const &,double const &,double const & ) ;
            
            kvector_t_exposer.def( 
                "setXYZ"
                , setXYZ_function_type( &::Geometry::BasicVector3D< double >::setXYZ )
                , ( bp::arg("x1"), bp::arg("y1"), bp::arg("z1") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setY
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setY_function_type )( double const & ) ;
            
            kvector_t_exposer.def( 
                "setY"
                , setY_function_type( &::Geometry::BasicVector3D< double >::setY )
                , ( bp::arg("a") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setZ
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setZ_function_type )( double const & ) ;
            
            kvector_t_exposer.def( 
                "setZ"
                , setZ_function_type( &::Geometry::BasicVector3D< double >::setZ )
                , ( bp::arg("a") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::theta
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*theta_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "theta"
                , theta_function_type( &::Geometry::BasicVector3D< double >::theta ) );
        
        }
        { //::Geometry::BasicVector3D< double >::transform
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > & ( exported_class_t::*transform_function_type )( ::Geometry::Transform3D const & ) ;
            
            kvector_t_exposer.def( 
                "transform"
                , transform_function_type( &::Geometry::BasicVector3D< double >::transform )
                , ( bp::arg("m") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Geometry::BasicVector3D< double >::unit
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > ( exported_class_t::*unit_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "unit"
                , unit_function_type( &::Geometry::BasicVector3D< double >::unit ) );
        
        }
        { //::Geometry::BasicVector3D< double >::x
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*x_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "x"
                , x_function_type( &::Geometry::BasicVector3D< double >::x ) );
        
        }
        { //::Geometry::BasicVector3D< double >::y
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*y_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "y"
                , y_function_type( &::Geometry::BasicVector3D< double >::y ) );
        
        }
        { //::Geometry::BasicVector3D< double >::z
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*z_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "z"
                , z_function_type( &::Geometry::BasicVector3D< double >::z ) );
        
        }
        kvector_t_exposer.def( bp::self != bp::self );
        kvector_t_exposer.def( bp::other< double >() * bp::self );
        kvector_t_exposer.def( bp::self * bp::self );
        kvector_t_exposer.def( bp::self * bp::other< double >() );
        kvector_t_exposer.def( bp::self + bp::self );
        kvector_t_exposer.def( +bp::self );
        kvector_t_exposer.def( bp::self - bp::self );
        kvector_t_exposer.def( -bp::self );
        kvector_t_exposer.def( bp::self / bp::other< double >() );
        kvector_t_exposer.def( bp::self_ns::str( bp::self ) );
        kvector_t_exposer.def( bp::self == bp::self );
    }

}
