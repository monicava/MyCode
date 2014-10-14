import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")

process.GlobalTag.globaltag = cms.string('START53_V10::All')

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'root://eoscms//eos/cms/store/user/agilbert/samples/DYJetsToLL-Summer12-53X-Sample.root'
    )
)

# print event content 
process.printEventContent = cms.EDAnalyzer("EventContentAnalyzer")



## Example classic sequence
process.demo = cms.EDAnalyzer('TauTest',
    tauTag                   = cms.untracked.InputTag("hpsPFTauProducer"),

    # DECAY MODE
    #################################################                        
    # DECAY MODE:OLD (default)
    #tauDecayModeTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByDecayModeFinding"),
    tauDecayModeTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByDecayModeFindingOldDMs"),
    ## DECAY MODE:NEW (2 prongs included)
    #tauDecayModeTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByDecayModeFindingNewDMs"),

    #ISOLATION
    #################################################                        
    # Run 1: 3 Hit
    #tauLooseIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits"),
    #tauMediumIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByMediumCombinedIsolationDBSumPtCorr3Hits"),
    #tauTightIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByTightCombinedIsolationDBSumPtCorr3Hits"),

    #OLD DM: MVA without LT
    tauLooseIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByLooseIsolationMVA3oldDMwoLT"),
    tauMediumIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByMediumIsolationMVA3oldDMwoLT"),
    tauTightIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByTightIsolationMVA3oldDMwoLT"),

    #OLD DM: MVA without LT                              
    #tauLooseIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByLooseIsolationMVA3oldDMwLT"),
    #tauMediumIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByMediumIsolationMVA3oldDMwLT"),
    #tauTightIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByTightIsolationMVA3oldDMwLT"),

    #NEW DM: MVA without LT
    #tauLooseIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByLooseIsolationMVA3newDMwoLT"),
    #tauMediumIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByMediumIsolationMVA3newDMwoLT"),
    #tauTightIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByTightIsolationMVA3newDMwoLT"),

    #NEW DM: MVA without LT                              
    #tauLooseIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByLooseIsolationMVA3newDMwLT"),
    #tauMediumIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByMediumIsolationMVA3newDMwLT"),
    #tauTightIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByTightIsolationMVA3newDMwLT"),

    ##MUON REJECTION:  recommended Rejection2
    #################################################
    tauLooseMuonRejectionTag      = cms.untracked.InputTag("hpsPFTauDiscriminationByLooseMuonRejection2"),
    tauMediumMuonRejectionTag      = cms.untracked.InputTag("hpsPFTauDiscriminationByMediumMuonRejection2"),
    tauTightMuonRejectionTag      = cms.untracked.InputTag("hpsPFTauDiscriminationByTightMuonRejection2"),

    ##ELECTRON REJECTION: recommended MV5
    #################################################                          
    tauLooseElectronRejectionTag  = cms.untracked.InputTag("hpsPFTauDiscriminationByMVA5LooseElectronRejection"),
    tauMediumElectronRejectionTag  = cms.untracked.InputTag("hpsPFTauDiscriminationByMVA5MediumElectronRejection"),
    tauTightElectronRejectionTag  = cms.untracked.InputTag("hpsPFTauDiscriminationByMVA5TightElectronRejection"),

    #OUTPUT ROOT FILE
    #################################################                               
    fileName           = cms.untracked.string("Histos.root")
                              
)

## Example new sequence


process.p = cms.Path(#process.printEventContent+
                      #old tauID
                      #process.recoTauClassicHPSSequence
                      #new tauID
                      process.PFTau
                     # process.recoTauClassicHPSSequence
                     #+process.printEventContent
                     +process.demo
                    )
