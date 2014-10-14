// -*- C++ -*-
//
// Package:    TauTest
// Class:      TauTest
// 
/**\class TauTest TauTest.cc MyCode/TauTest/src/TauTest.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Monica Vazquez Acosta,40 1-B16,+41227671546,
//         Created:  Fri Oct 10 12:14:17 CEST 2014
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TFile.h"
#include "TH1F.h"


#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TauReco/interface/BaseTau.h"
#include "DataFormats/TauReco/interface/PFTauFwd.h"
#include "DataFormats/TauReco/interface/PFTauTagInfo.h"
#include "DataFormats/TauReco/interface/PFTauDiscriminator.h"
#include "RecoTauTag/TauTagTools/interface/PFTauElementsOperators.h"
#include "RecoTauTag/RecoTau/interface/TauDiscriminationProducerBase.h"



//
// class declaration
//

class TauTest : public edm::EDAnalyzer {
   public:
      explicit TauTest(const edm::ParameterSet&);
      ~TauTest();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
  TFile* rootFile_;
  std::string fileName_;

  edm::InputTag tauLabel_;

  edm::InputTag tauDecayModeLabel_;

  edm::InputTag tauLooseIsolationLabel_;
  edm::InputTag tauMediumIsolationLabel_;
  edm::InputTag tauTightIsolationLabel_;

  edm::InputTag tauLooseMuonRejectionLabel_;
  edm::InputTag tauMediumMuonRejectionLabel_;
  edm::InputTag tauTightMuonRejectionLabel_;

  edm::InputTag tauLooseElectronRejectionLabel_;
  edm::InputTag tauMediumElectronRejectionLabel_;
  edm::InputTag tauTightElectronRejectionLabel_;

  int event_count;

  TH1F *h_Tau_pt;  
  TH1F *h_Tau_eta;

  TH1F *h_Tau_decaymode;

  TH1F *h_Tau_isolation;
  TH1F *h_Tau_muonrejection;
  TH1F *h_Tau_electronrejection;


};



//
// constructors and destructor
//
TauTest::TauTest(const edm::ParameterSet& iConfig)

{
  fileName_ = iConfig.getUntrackedParameter<std::string>("fileName");
  tauLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauTag");

  tauDecayModeLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauDecayModeTag");

  tauLooseIsolationLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauLooseIsolationTag");
  tauMediumIsolationLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauMediumIsolationTag");
  tauTightIsolationLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauTightIsolationTag");

  tauLooseMuonRejectionLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauLooseMuonRejectionTag");
  tauMediumMuonRejectionLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauMediumMuonRejectionTag");
  tauTightMuonRejectionLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauTightMuonRejectionTag");

  tauLooseElectronRejectionLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauLooseElectronRejectionTag");
  tauMediumElectronRejectionLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauMediumElectronRejectionTag");
  tauTightElectronRejectionLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauTightElectronRejectionTag");


}


TauTest::~TauTest()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TauTest::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   event_count++;

   //std::cout << "EVENT IN ANALYZER = " << event_count << std::endl;
   //std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

   edm::Handle<reco::PFTauCollection> tauHandle;
   iEvent.getByLabel(tauLabel_,tauHandle);

   //reco::PFTauCollection thetaus = *tauHandle;

   //DECAY MODE
   edm::Handle<reco::PFTauDiscriminator> tauDecayModeHandle;
   iEvent.getByLabel(tauDecayModeLabel_,tauDecayModeHandle);
   reco::PFTauDiscriminator thetauDecayModes = *tauDecayModeHandle;

   //ISOLATION
   edm::Handle<reco::PFTauDiscriminator> tauLooseIsolationHandle;
   iEvent.getByLabel(tauLooseIsolationLabel_,tauLooseIsolationHandle);
   reco::PFTauDiscriminator theLooseIsolations = *tauLooseIsolationHandle;

   edm::Handle<reco::PFTauDiscriminator> tauMediumIsolationHandle;
   iEvent.getByLabel(tauMediumIsolationLabel_,tauMediumIsolationHandle);
   reco::PFTauDiscriminator theMediumIsolations = *tauMediumIsolationHandle;

   edm::Handle<reco::PFTauDiscriminator> tauTightIsolationHandle;
   iEvent.getByLabel(tauTightIsolationLabel_,tauTightIsolationHandle);
   reco::PFTauDiscriminator theTightIsolations = *tauTightIsolationHandle;

   //ELECTRON REJECTION
   edm::Handle<reco::PFTauDiscriminator> tauLooseElectronRejectionHandle;
   iEvent.getByLabel(tauLooseElectronRejectionLabel_,tauLooseElectronRejectionHandle);
   reco::PFTauDiscriminator theLooseElectronRejections = *tauLooseElectronRejectionHandle;

   edm::Handle<reco::PFTauDiscriminator> tauMediumElectronRejectionHandle;
   iEvent.getByLabel(tauMediumElectronRejectionLabel_,tauMediumElectronRejectionHandle);
   reco::PFTauDiscriminator theMediumElectronRejections = *tauMediumElectronRejectionHandle;

   edm::Handle<reco::PFTauDiscriminator> tauTightElectronRejectionHandle;
   iEvent.getByLabel(tauTightElectronRejectionLabel_,tauTightElectronRejectionHandle);
   reco::PFTauDiscriminator theTightElectronRejections = *tauTightElectronRejectionHandle;

   //MUON REJECTION
   edm::Handle<reco::PFTauDiscriminator> tauLooseMuonRejectionHandle;
   iEvent.getByLabel(tauLooseMuonRejectionLabel_,tauLooseMuonRejectionHandle);
   reco::PFTauDiscriminator theLooseMuonRejections = *tauLooseMuonRejectionHandle;

   edm::Handle<reco::PFTauDiscriminator> tauMediumMuonRejectionHandle;
   iEvent.getByLabel(tauMediumMuonRejectionLabel_,tauMediumMuonRejectionHandle);
   reco::PFTauDiscriminator theMediumMuonRejections = *tauMediumMuonRejectionHandle;

   edm::Handle<reco::PFTauDiscriminator> tauTightMuonRejectionHandle;
   iEvent.getByLabel(tauTightMuonRejectionLabel_,tauTightMuonRejectionHandle);
   reco::PFTauDiscriminator theTightMuonRejections = *tauTightMuonRejectionHandle;


   for(reco::PFTauCollection::const_iterator iTau = tauHandle->begin(); iTau!=tauHandle->end(); ++iTau){
     reco::PFTauRef thetauRef(reco::PFTauRef(tauHandle,iTau - tauHandle->begin()));
     //std::cout << "HELLO TAU decay mode finding " << iTau->tauID("decayModeFindingOldDMs") << std::endl;
     
     //Recommendation
     //Taus that pass decay mode finding and have pt > 20 GeV
     bool resultDecayMode = ((*tauDecayModeHandle)[thetauRef] > 0.5 );

     //isolation
     bool resultLooseIsolation = ((*tauLooseIsolationHandle)[thetauRef] > 0.5 );
     bool resultMediumIsolation = ((*tauMediumIsolationHandle)[thetauRef] > 0.5 );
     bool resultTightIsolation = ((*tauTightIsolationHandle)[thetauRef] > 0.5 );

     //electron rejection
     bool resultLooseElectronRejection = ((*tauLooseElectronRejectionHandle)[thetauRef] > 0.5 );
     bool resultMediumElectronRejection = ((*tauMediumElectronRejectionHandle)[thetauRef] > 0.5 );
     bool resultTightElectronRejection = ((*tauTightElectronRejectionHandle)[thetauRef] > 0.5 );

     //muon rejection
     bool resultLooseMuonRejection = ((*tauLooseMuonRejectionHandle)[thetauRef] > 0.5 );
     bool resultMediumMuonRejection = ((*tauMediumMuonRejectionHandle)[thetauRef] > 0.5 );
     bool resultTightMuonRejection = ((*tauTightMuonRejectionHandle)[thetauRef] > 0.5 );
     
     if( resultDecayMode && iTau->pt() > 20) {
       //FILL THE HISTROGRAMS
       h_Tau_pt->Fill(iTau->pt());
       h_Tau_eta->Fill(iTau->eta());
       
       //ISOLATION
       if(resultLooseIsolation) h_Tau_isolation->Fill(1);
       if(resultMediumIsolation) h_Tau_isolation->Fill(2);
       if(resultTightIsolation) h_Tau_isolation->Fill(3);

       //ELECTRON REJECTION
       if(resultLooseElectronRejection) h_Tau_electronrejection->Fill(1);
       if(resultMediumElectronRejection) h_Tau_electronrejection->Fill(2);
       if(resultTightElectronRejection) h_Tau_electronrejection->Fill(3);

       //MUON REJECTION
       if(resultLooseMuonRejection) h_Tau_muonrejection->Fill(1);
       if(resultMediumMuonRejection) h_Tau_muonrejection->Fill(2);
       if(resultTightMuonRejection) h_Tau_muonrejection->Fill(3);

       //DECAY MODE
       h_Tau_decaymode->Fill(iTau->decayMode());
       
       //std::cout << "HELLO TAU:pt,eta " << iTau->pt() << " " << iTau->eta() << std::endl;
       //if( iTau->decayMode() == 0 ) std::cout << "HELLO TAU: kOneProng0PiZero"  << std::endl;
       //if( iTau->decayMode() == 1 ) std::cout << "HELLO TAU: kOneProng1PiZero"  << std::endl;
       //if( iTau->decayMode() == 2 ) std::cout << "HELLO TAU: kOneProng2PiZero"  << std::endl;
       //if( iTau->decayMode() == 5 ) std::cout << "HELLO TAU: kTwoProng0PiZero"  << std::endl;
       //if( iTau->decayMode() == 6 ) std::cout << "HELLO TAU: kTwoProng1PiZero"  << std::endl;
       //if( iTau->decayMode() == 10) std::cout << "HELLO TAU: kThreeProng0PiZero"  << std::endl;
       
       /*
	enum hadronicDecayMode {
	 kNull = -1,
	 kOneProng0PiZero, // 0
	 kOneProng1PiZero, // 1
	 kOneProng2PiZero, // 2
	 kOneProng3PiZero, // 3
	 kOneProngNPiZero, // 4
	 kTwoProng0PiZero, // 5
	 kTwoProng1PiZero, // 6
	 kTwoProng2PiZero, // 7
	 kTwoProng3PiZero, // 8
	 kTwoProngNPiZero, // 9
	 kThreeProng0PiZero, // 10
	 kThreeProng1PiZero, // 11
	 kThreeProng2PiZero, // 12
	 kThreeProng3PiZero, // 13
	 kThreeProngNPiZero, // 14
	 kRareDecayMode      // 15
       };
       */
     }
     
   }


   
}


void
TauTest::beginJob()
{

  event_count=0;

  rootFile_ = new TFile( fileName_.c_str(), "RECREATE" );
  rootFile_->cd();

  //BOOK THE HISTOGRAMS
  h_Tau_pt        =  new TH1F("h_Tau_pt","p_{t}^{#tau}",25,0,200);
  h_Tau_eta      =  new TH1F("h_Tau_eta","#eta^{#tau}",20,-5,5);

  h_Tau_decaymode      =  new TH1F("h_Tau_decaymode","#tau decay mode",16,-0.5,15.5);

  h_Tau_isolation =  new TH1F("h_Tau_isolation","#tau isolation: loose, medium, tight",3,0.5,3.5);
  h_Tau_electronrejection =  new TH1F("h_Tau_electronrejection","#tau electron rejection: loose, medium, tight",3,0.5,3.5);
  h_Tau_muonrejection =  new TH1F("h_Tau_muonrejection","#tau muon rejection: loose, medium, tight",3,0.5,3.5);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauTest::endJob() 
{
  rootFile_->cd();


  //WRITE-OUT THE HISTOGRAMS 
  h_Tau_pt->Write();
  h_Tau_eta->Write();
  h_Tau_decaymode->Write();
  h_Tau_isolation->Write();
  h_Tau_electronrejection->Write();
  h_Tau_muonrejection->Write();

  rootFile_->Write();
  rootFile_->Close();
}


// ------------ method called when starting to processes a run  ------------
void 
TauTest::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
TauTest::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TauTest::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TauTest::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TauTest::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}



//define this as a plug-in
DEFINE_FWK_MODULE(TauTest);
