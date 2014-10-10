import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")

process.GlobalTag.globaltag = cms.string('START53_V10::All')

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

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
    tauDecayModeTag          = cms.untracked.InputTag(""),               
    tauIsolationTag          = cms.untracked.InputTag("hpsPFTauDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits"),
    tauMuonRejectionTag      = cms.untracked.InputTag("hpsPFTauDiscriminationByLooseMuonRejection2"),
    tauElectronRejectionTag  = cms.untracked.InputTag("hpsPFTauDiscriminationByMVA3LooseElectronRejection"),
    fileName           = cms.untracked.string("Histos.root")
                              
)

## Example new sequence


process.p = cms.Path(#process.printEventContent+
                      process.recoTauClassicHPSSequence
                     # process.recoTauClassicHPSSequence
                     +process.printEventContent
                    )
                     #+process.demo)
