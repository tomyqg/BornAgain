"""

"""
import bornagain as ba
import ctypes


class MySampleBuilder(ba.ISampleBuilder):
    """

    """
    def __init__(self):
        ba.ISampleBuilder.__init__(self)
        self.sample = None
        # parameters describing the sample
        self.radius = ctypes.c_double(5.5*ba.nanometer)
        self.sigma = ctypes.c_double(0.15)
        self.distance = ctypes.c_double(63.1*ba.nanometer)
        self.disorder = ctypes.c_double(2.4*ba.nanometer)
        self.kappa = ctypes.c_double(8.5)
        self.tptfe = ctypes.c_double(29.0*ba.nanometer)
        self.thmdso = ctypes.c_double(23.9*ba.nanometer)
        # register parameters
        self.registerParameter("radius", ctypes.addressof(self.radius))
        self.registerParameter("sigma", ctypes.addressof(self.sigma))
        self.registerParameter("distance", ctypes.addressof(self.distance))
        self.registerParameter("disorder", ctypes.addressof(self.disorder))
        self.registerParameter("kappa", ctypes.addressof(self.kappa))
        self.registerParameter("tptfe", ctypes.addressof(self.tptfe))
        self.registerParameter("thmdso", ctypes.addressof(self.thmdso))

    # constructs the sample for current values of parameters
    def buildSample(self):
        # defining materials
        m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
        m_Si = ba.HomogeneousMaterial("Si", 5.78164736e-6, 1.02294578e-7)
        m_Ag = ba.HomogeneousMaterial("Ag", 2.24749529E-5, 1.61528396E-6)
        m_PTFE = ba.HomogeneousMaterial("PTFE", 5.20508729E-6, 1.96944292E-8)
        m_HMDSO = ba.HomogeneousMaterial("HMDSO", 2.0888308E-6, 1.32605651E-8)

        # collection of particles
        nparticles = 3
        nfwhm = 2.0
        sphere_ff = ba.FormFactorFullSphere(self.radius.value)
        sphere = ba.Particle(m_Ag, sphere_ff)
        position = ba.kvector_t(0*ba.nanometer, 0*ba.nanometer, -1.0*self.thmdso.value)
        sphere.setPosition(position)

        gauss_distr = ba.DistributionLogNormal(self.radius.value, self.sigma.value)
        par_distr = ba.ParameterDistribution("/Particle/FullSphere/Radius", gauss_distr, nparticles, nfwhm)

        part_coll = ba.ParticleDistribution(sphere, par_distr)

        # assembling the sample
        particle_layout = ba.ParticleLayout()
        particle_layout.addParticle(part_coll, 1.0)
        # particle_layout.addParticle(part_coll, 1.0, ba.kvector_t(0, 0, -1.0*self.thmdso.value))
        interference = ba.InterferenceFunctionRadialParaCrystal(self.distance.value, 1e6*ba.nanometer)
        interference.setKappa(self.kappa.value)
        interference.setDomainSize(20000.0)
        pdf = ba.FTDistribution1DGauss(self.disorder.value)
        interference.setProbabilityDistribution(pdf)

        particle_layout.addInterferenceFunction(interference)
        particle_layout.setApproximation(ba.ILayout.SSCA)
        particle_layout.setTotalParticleSurfaceDensity(1)

        # roughness
        r_ptfe = ba.LayerRoughness()
        r_ptfe.setSigma(2.3*ba.nanometer)
        r_ptfe.setHurstParameter(0.3)
        r_ptfe.setLatteralCorrLength(5.0*ba.nanometer)

        r_hmdso = ba.LayerRoughness()
        r_hmdso.setSigma(1.1*ba.nanometer)
        r_hmdso.setHurstParameter(0.3)
        r_hmdso.setLatteralCorrLength(5.0*ba.nanometer)

        # sample configuratuion
        # air layer with particles and substrate forms multilayer
        # Layer(material_name, thickness[nm])
        air_layer = ba.Layer(m_air)
        hmdso_layer = ba.Layer(m_HMDSO, self.thmdso.value)
        hmdso_layer.addLayout(particle_layout)
        ptfe_layer = ba.Layer(m_PTFE, self.tptfe.value)
        substrate_layer = ba.Layer(m_Si)

        # it is importamt to start from the top layer down to the bottom one
        multi_layer = ba.MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayerWithTopRoughness(hmdso_layer, r_hmdso)
        multi_layer.addLayerWithTopRoughness(ptfe_layer, r_ptfe)
        multi_layer.addLayer(substrate_layer)

        self.sample = multi_layer
        return self.sample
