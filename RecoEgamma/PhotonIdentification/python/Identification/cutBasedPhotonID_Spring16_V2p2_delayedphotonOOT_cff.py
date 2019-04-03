
from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry

import FWCore.ParameterSet.Config as cms

# Common functions and classes for ID definition are imported here:
from RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_tools \
    import ( WorkingPoint_V2,
	     WorkingPoint_OOT_V1, 
             IsolationCutInputs,
             IsolationCutInputsOOT,
             configureVIDCutBasedPhoID_V5,
	     configureVIDCutBasedPhoID_OOT_V1, )             

#
# This is the first version of Spring16 cuts for 80X samples
#
# The cut values are taken from the twiki:
#       https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2
#       (where they may not stay, if a newer version of cuts becomes available for these
#        conditions)
# See also the presentation explaining these working points (this will not change):
#     https://indico.cern.ch/event/491548/contributions/2384977/attachments/1377936/2102914/CutBasedPhotonID_25-11-2016.pdf

#
# First, define cut values
#

# Loose working point Barrel and Endcap
idName = "cutBasedPhotonID-Spring16-V2p2-delayedphotonOOT-loose"

WP_Loose_EB = WorkingPoint_OOT_V1(
    idName    ,  # idName
    1.7     ,    # SmajorCut
    0.022   ,    # full5x5_SigmaIEtaIEtaCut
# Isolation cuts are generally absIso < C1 + pt*C2, except for NeuHad is < C1 + pt*C2 + pt*pt*C3
    6.0     ,    # absTrackerIsoWithEACut_C1
    0.005996,    # absTrackerIsoWithEACut_C2
    9.00    ,    # absPFNeuHadIsoWithEACut_C1
    -0.0008001,  # absPFNeuHadIsoWithEACut_C2
    2.934e-05  , # absPFNeuHadIsoWithEACut_C3
    7.0     ,    # absEcalIsoWithEACut_C1
    0.007132     # absEcalIsoWithEACut_C2
    )
WP_Loose_EE = WorkingPoint_OOT_V1(
    idName    ,  # idName
    1.7     ,    # SmajorCut
    0.022   ,    # full5x5_SigmaIEtaIEtaCut
# Isolation cuts are generally absIso < C1 + pt*C2, except for NeuHad is < C1 + pt*C2 + pt*pt*C3
    6.0     ,    # absTrackerIsoWithEACut_C1
    0.005996,    # absTrackerIsoWithEACut_C2
    9.00    ,    # absPFNeuHadIsoWithEACut_C1
    -0.0008001,  # absPFNeuHadIsoWithEACut_C2
    2.934e-05  , # absPFNeuHadIsoWithEACut_C3
    7.0     ,    # absEcalIsoWithEACut_C1
    0.007132     # absEcalIsoWithEACut_C2
    )

# Medium working point Barrel and Endcap
idName = "cutBasedPhotonID-Spring16-V2p2-delayedphotonOOT-medium"

WP_Medium_EB = WorkingPoint_OOT_V1(
    idName    ,  # idName
    1.5     ,    # SmajorCut
    0.019   ,    # full5x5_SigmaIEtaIEtaCut
# Isolation cuts are generally absIso < C1 + pt*C2, except for NeuHad is < C1 + pt*C2 + pt*pt*C3
    4.0     ,    # absTrackerIsoWithEACut_C1
    0.005996,    # absTrackerIsoWithEACut_C2
    7.00    ,    # absPFNeuHadIsoWithEACut_C1
    -0.0008001,  # absPFNeuHadIsoWithEACut_C2
    2.934e-05  , # absPFNeuHadIsoWithEACut_C3
    5.0     ,    # absEcalIsoWithEACut_C1
    0.007132     # absEcalIsoWithEACut_C2
    )
WP_Medium_EE = WorkingPoint_OOT_V1(
    idName    ,  # idName
    1.5     ,    # SmajorCut
    0.019   ,    # full5x5_SigmaIEtaIEtaCut
# Isolation cuts are generally absIso < C1 + pt*C2, except for NeuHad is < C1 + pt*C2 + pt*pt*C3
    4.0     ,    # absTrackerIsoWithEACut_C1
    0.005996,    # absTrackerIsoWithEACut_C2
    7.00    ,    # absPFNeuHadIsoWithEACut_C1
    -0.0008001,  # absPFNeuHadIsoWithEACut_C2
    2.934e-05  , # absPFNeuHadIsoWithEACut_C3
    5.0     ,    # absEcalIsoWithEACut_C1
    0.007132     # absEcalIsoWithEACut_C2
    )

# Tight working point Barrel and Endcap
idName = "cutBasedPhotonID-Spring16-V2p2-delayedphotonOOT-tight"
WP_Tight_EB = WorkingPoint_OOT_V1(
    idName    ,  # idName
    1.3     ,    # SmajorCut
    0.017   ,    # full5x5_SigmaIEtaIEtaCut
# Isolation cuts are generally absIso < C1 + pt*C2, except for NeuHad is < C1 + pt*C2 + pt*pt*C3
    2.0     ,    # absTrackerIsoWithEACut_C1
    0.005996,    # absTrackerIsoWithEACut_C2
    5.00    ,    # absPFNeuHadIsoWithEACut_C1
    -0.0008001,  # absPFNeuHadIsoWithEACut_C2
    2.934e-05  , # absPFNeuHadIsoWithEACut_C3
    3.0     ,    # absEcalIsoWithEACut_C1
    0.007132     # absEcalIsoWithEACut_C2
    )
WP_Tight_EE = WorkingPoint_OOT_V1(
    idName    ,  # idName
    1.3     ,    # SmajorCut
    0.017   ,    # full5x5_SigmaIEtaIEtaCut
# Isolation cuts are generally absIso < C1 + pt*C2, except for NeuHad is < C1 + pt*C2 + pt*pt*C3
    2.0     ,    # absTrackerIsoWithEACut_C1
    0.005996,    # absTrackerIsoWithEACut_C2
    5.00    ,    # absPFNeuHadIsoWithEACut_C1
    -0.0008001,  # absPFNeuHadIsoWithEACut_C2
    2.934e-05  , # absPFNeuHadIsoWithEACut_C3
    3.0     ,    # absEcalIsoWithEACut_C1
    0.007132     # absEcalIsoWithEACut_C2
    )

# Second, define where to find the precomputed isolations and what effective
# areas to use for pile-up correction
isoInputs = IsolationCutInputsOOT(
    # chHadIsolationMapName  
    'photonIDValueMapProducer:phoTrkIsolation' ,
    # chHadIsolationEffAreas 
    "RecoEgamma/PhotonIdentification/data/Spring16/effAreaPhotons_cone03_TrkIsolation_90percentBased_OOT.txt",
    # neuHadIsolationMapName
    'photonIDValueMapProducer:phoNeutralHadronIsolation' ,
    # neuHadIsolationEffAreas
    "RecoEgamma/PhotonIdentification/data/Spring16/effAreaPhotons_cone03_pfNeutralHadrons_90percentBased_OOT.txt" ,
    # phoIsolationMapName  
    "photonIDValueMapProducer:phoEcalPFClIsolation" ,
    # phoIsolationEffAreas
    "RecoEgamma/PhotonIdentification/data/Spring16/effAreaPhotons_cone03_EcalPF_90percentBased_OOT.txt"
)

#
# Finally, set up VID configuration for all cuts
#
cutBasedPhotonID_Spring16_V2p2_delayedphotonOOT_loose  = configureVIDCutBasedPhoID_OOT_V1 ( WP_Loose_EB, WP_Loose_EE, isoInputs)
cutBasedPhotonID_Spring16_V2p2_delayedphotonOOT_medium = configureVIDCutBasedPhoID_OOT_V1 ( WP_Medium_EB, WP_Medium_EE, isoInputs)
cutBasedPhotonID_Spring16_V2p2_delayedphotonOOT_tight  = configureVIDCutBasedPhoID_OOT_V1 ( WP_Tight_EB, WP_Tight_EE, isoInputs)

## The MD5 sum numbers below reflect the exact set of cut variables
# and values above. If anything changes, one has to 
# 1) comment out the lines below about the registry, 
# 2) run "calculateMD5 <this file name> <one of the VID config names just above>
# 3) update the MD5 sum strings below and uncomment the lines again.
#

central_id_registry.register(cutBasedPhotonID_Spring16_V2p2_delayedphotonOOT_loose.idName,
                             'cd6b75595f1119b1a94dd3b0d4d57bb6')
central_id_registry.register(cutBasedPhotonID_Spring16_V2p2_delayedphotonOOT_medium.idName,
                             'b4e3706a61e6432a89b38c6cf13b55f3')
central_id_registry.register(cutBasedPhotonID_Spring16_V2p2_delayedphotonOOT_tight.idName,
                             '17cce290dfe1512fb31e118c66b596d8')

cutBasedPhotonID_Spring16_V2p2_delayedphotonOOT_loose.isPOGApproved = cms.untracked.bool(True)
cutBasedPhotonID_Spring16_V2p2_delayedphotonOOT_medium.isPOGApproved = cms.untracked.bool(True)
cutBasedPhotonID_Spring16_V2p2_delayedphotonOOT_tight.isPOGApproved = cms.untracked.bool(True)
