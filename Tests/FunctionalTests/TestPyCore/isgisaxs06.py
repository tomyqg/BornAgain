# IsGISAXS06 example: 2D lattice with different disorder
import sys
import os
import numpy
import gzip

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *

M_PI = numpy.pi

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation_lattice():
# defining materials
    matMng = MaterialManager.instance()
    mAmbience = matMng.addHomogeneousMaterial("Air", 1.0, 0.0 )
    mSubstrate = matMng.addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8 )
    # collection of particles
    lattice_params = Lattice2DIFParameters()
    m_length_1 = 10.0*nanometer
    m_length_2 = 10.0*nanometer
    m_angle = 90.0*degree
    m_xi = 0.0*degree
    m_domain_size_1 = 20000.0*nanometer
    m_domain_size_2 = 20000.0*nanometer
    m_corr_length_1 = 300.0*nanometer/2.0/M_PI
    m_corr_length_2 = 100.0*nanometer/2.0/M_PI
   
    interference = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    interference.setProbabilityDistribution(pdf)
    
    n_particle = complex(1.0-6e-4, 2e-8)
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(n_particle, cylinder_ff.clone())
    position = kvector_t(0.0, 0.0, 0.0)
    particle_decoration = ParticleDecoration()
    particle_info =  PositionParticleInfo(cylinder, 0, position, 1.0)
    particle_decoration.addParticleInfo(particle_info)
    particle_decoration.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
    multi_layer.addLayer(substrate_layer)
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)
    
    sim_params= SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    sim_params.me_lattice_type = SimulationParameters.LATTICE
    simulation.setSimulationParameters(sim_params)
    
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return GetOutputData(simulation)


# ----------------------------------
# describe sample and run simulation - cylinders lattice centered
# ----------------------------------
def RunSimulation_centered():
# defining materials
    matMng = MaterialManager.instance()
    mAmbience = matMng.addHomogeneousMaterial("Air", 1.0, 0.0 )
    mSubstrate = matMng.addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8 )
    # collection of particles
    lattice_params = Lattice2DIFParameters()
    m_length_1 = 10.0*nanometer
    m_length_2 = 10.0*nanometer
    m_angle = 90.0*degree
    m_xi = 0.0*degree
    m_domain_size_1 = 20000.0*nanometer
    m_domain_size_2 = 20000.0*nanometer
    m_corr_length_1 = 300.0*nanometer/2.0/M_PI
    m_corr_length_2 = 100.0*nanometer/2.0/M_PI
    interference = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    interference.setProbabilityDistribution(pdf)
    
    n_particle = complex(1.0-6e-4, 2e-8)
    particle_decoration = ParticleDecoration()
    position = kvector_t(0.0, 0.0, 0.0)
    # particle 1
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(n_particle, cylinder_ff)
    position = kvector_t(0.0, 0.0, 0.0)
    particle_info = PositionParticleInfo(cylinder, 0, position, 1.0)
    particle_decoration.addParticleInfo(particle_info)
    # particle 2
    position_2 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    particle_info.setPosition(position_2)  
    particle_decoration.addParticleInfo(particle_info)
    particle_decoration.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
    multi_layer.addLayer(substrate_layer)
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)
    
    sim_params= SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    sim_params.me_lattice_type = SimulationParameters.LATTICE
    simulation.setSimulationParameters(sim_params)
    
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return GetOutputData(simulation)


# ----------------------------------
# describe sample and run simulation - cylinders lattice rotated
# ----------------------------------
def RunSimulation_rotated():
# defining materials
    matMng = MaterialManager.instance()
    mAmbience = matMng.addHomogeneousMaterial("Air", 1.0, 0.0 )
    mSubstrate = matMng.addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8 )
    # collection of particles
    lattice_params = Lattice2DIFParameters()
    m_length_1 = 10.0*nanometer
    m_length_2 = 10.0*nanometer
    m_angle = 90.0*degree
    m_xi = 30.0*degree
    m_domain_size_1 = 20000.0*nanometer
    m_domain_size_2 = 20000.0*nanometer
    m_corr_length_1 = 300.0*nanometer/2.0/M_PI
    m_corr_length_2 = 100.0*nanometer/2.0/M_PI
    interference = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    pdf.setGamma(30.0*degree)
    interference.setProbabilityDistribution(pdf)
    
    n_particle = complex(1.0-6e-4, 2e-8)
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(n_particle, cylinder_ff)
    position = kvector_t(0.0, 0.0, 0.0)
    particle_decoration = ParticleDecoration()
    particle_info =  PositionParticleInfo(cylinder, 0, position, 1.0)
    particle_decoration.addParticleInfo(particle_info)
    particle_decoration.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
    multi_layer.addLayer(substrate_layer)
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)
    
    sim_params = SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    sim_params.me_lattice_type = SimulationParameters.LATTICE
    simulation.setSimulationParameters(sim_params)
    
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return GetOutputData(simulation)


# ----------------------------------
# describe sample and run simulation - lattice variants
# ----------------------------------
def RunSimulation_variants():

    # building simulation
    simulation.runSimulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)
    
    sim_params = SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    sim_params.me_lattice_type = SimulationParameters.LATTICE
    simulation.setSimulationParameters(sim_params)

    # running simulation and copying data
    OutputDatap_total = simulation.getOutputDataClone()
    p_total.setAllTo(0.0)
    nbins = 3
    xi_min = 0.0*degree
    xi_max = 240.0*degree
    xi= StochasticSampledParameter(StochasticDoubleGate(xi_min, xi_max), nbins, xi_min, xi_max)
    #for size_t i in range(xi.getNbins()) :
    for i in range(xi.getNbins()) :
        xi_value = xi.getBinValue(i)
        probability = xi.getNormalizedProbability(i)
        m_builder.setXi(xi_value)
#             MultiLayer *p_sample = dynamic_cast<MultiLayer *>(m_builder.buildSample());
        p_sample =  buildSample()
        simulation.setSample(p_sample)
        simulation.runSimulation()
        delete p_sample
        p_single_output = simulation.getOutputDataClone()
        p_single_output.scaleAll(probability)
        p_total += p_single_output
        delete p_single_output
        
    return GetOutputData(simulation)
    delete p_total


# IsGISAXS6 functional test sample builder for varying xi angle
def buildSample():
#ISample* FunctionalTests::IsGISAXS06::LatticeVariantBuilder::buildSample() const

    n_particle = complex(1.0-6e-4, 2e-8)
    matMng = MaterialManager.instance()
    mAmbience = matMng.addHomogeneousMaterial("Air", 1.0, 0.0 )
    mSubstrate = matMng.addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8 )
    lattice_params = Lattice2DIFParameters()
    m_length_1 = 10.0*nanometer
    m_length_2 = 10.0*nanometer
    m_angle = 90.0*degree
    m_domain_size_1 = 20000.0*nanometer
    m_domain_size_2 = 20000.0*nanometer
    m_corr_length_1 = 300.0*nanometer/2.0/M_PI
    m_corr_length_2 = 100.0*nanometer/2.0/M_PI
    p_interference_function = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DCauchy (300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    p_interference_function.setProbabilityDistribution(pdf)

    particle_decoration = ParticleDecoration()
    # particle
    ff_cyl = FormFactorCylinder(5.0*nanometer, 5.0*nanometer)
    position = kvector_t(0.0, 0.0, 0.0)
    cylinder = Particle(n_particle, ff_cyl.clone())
    particle_info = PositionParticleInfo( cylinder , 0, position, 1.0)
    particle_decoration.addParticleInfo(particle_info)
    particle_decoration.addInterferenceFunction(p_interference_function)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
    multi_layer.addLayer(substrate_layer)
    return p_multi_layer

      
# ----------------------------------
# read reference data from file
# ----------------------------------
def GetReferenceData():
    path = os.path.split(__file__)[0]
    if path: path +="/"
    flattice = gzip.open(path+'../TestCore/IsGISAXS06/isgisaxs06_reference_lattice.ima.gz', 'rb')
    referencelattice=numpy.fromstring(flattice.read(),numpy.float64,sep=' ')
    flattice.close()
    fcentered = gzip.open(path+'../TestCore/IsGISAXS06/isgisaxs06_reference_centered.ima.gz', 'rb')
    referencecentered=numpy.fromstring(fBA_Size.read(),numpy.float64,sep=' ')
    frotated.close()
    frotated = gzip.open(path+'../TestCore/IsGISAXS06/isgisaxs06_reference_rotated.ima.gz', 'rb')
    referencerotated=numpy.fromstring(fDWBA.read(),numpy.float64,sep=' ')
    frotated.close()
    fvariants = gzip.open(path+'../TestCore/IsGISAXS06/isgisaxs06_reference_variants.ima.gz', 'rb')
    referencevariants=numpy.fromstring(fDWBA.read(),numpy.float64,sep=' ')
    fvariants.close()
    reference=numpy.concatenate((referencelattice,referencecentered,referencerotated,referencevariants),axis=0)  
    return reference


# --------------------------------------------------------------
# calculate numeric difference between result and reference data
# --------------------------------------------------------------
def GetDifference(data, reference):
    reference = reference.reshape(data.shape)
    # calculating relative average difference
    data -= reference
    diff=0.0
    epsilon = sys.float_info.epsilon
    for x, y in numpy.ndindex(data.shape):
        v1 = data[x][y]
        v2 = reference[x][y]
        if v1 <= epsilon and v2 <= epsilon:
            diff += 0.0
        elif(v2 <= epsilon):
            diff += abs(v1/epsilon)
        else:
            diff += abs(v1/v2)
    return diff/data.size


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def RunTest():
    result_lattice = RunSimulation_lattice()
    result_centered = RunSimulation_centered()
    result_rotated = RunSimulation_rotated()
    result_variants = RunSimulation_variants()
    
    result = numpy.concatenate((result_lattice,result_centered,result_rotated,result_variants),axis=0)
    #result = numpy.concatenate((result_lattice,result_centered,result_rotated),axis=0) 
    reference = GetReferenceData()

    diff = GetDifference(result, reference)
    status = "OK"
    if(diff > 1e-10): status = "FAILED"
    return "IsGISAXS06" + " 2D lattice with different disorder " + status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  print RunTest()




 
 