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
  edm::InputTag tauIsolationLabel_;
  edm::InputTag tauMuonRejectionLabel_;
  edm::InputTag tauElectronRejectionLabel_;

  int event_count;

  TH1F *h_Tau_pt;  
  TH1F *h_Tau_eta;

  TH1F *h_Tau_decaymode;

};



//
// constructors and destructor
//
TauTest::TauTest(const edm::ParameterSet& iConfig)

{
  fileName_ = iConfig.getUntrackedParameter<std::string>("fileName");
  tauLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauTag");

  tauDecayModeLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauDecayModeTag");
  tauIsolationLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauIsolationTag");
  tauMuonRejectionLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauMuonRejectionTag");
  tauElectronRejectionLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("tauElectronRejectionTag");


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

   std::cout << "EVENT IN ANALYZER = " << event_count << std::endl;
   std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

   edm::Handle<reco::PFTauCollection> tauHandle;
   iEvent.getByLabel(tauLabel_,tauHandle);

   //reco::PFTauCollection thetaus = *tauHandle;

   edm::Handle<reco::PFTauDiscriminator> tauDecayModeHandle;
   iEvent.getByLabel(tauDecayModeLabel_,tauDecayModeHandle);

   reco::PFTauDiscriminator thetauDecayModes = *tauDecayModeHandle;

   for(reco::PFTauCollection::const_iterator iTau = tauHandle->begin(); iTau!=tauHandle->end(); ++iTau){
     reco::PFTauRef thetauRef(reco::PFTauRef(tauHandle,iTau - tauHandle->begin()));
     //std::cout << "HELLO TAU decay mode finding " << iTau->tauID("decayModeFindingOldDMs") << std::endl;
     
     //Recommendation
     //Taus that pass decay mode finding and have pt > 20 GeV
     bool resultDecayMode = ((*tauDecayModeHandle)[thetauRef] > 0.5 );
     
     if( resultDecayMode && iTau->pt() > 20) {
       //FILL THE HISTROGRAMS
       h_Tau_pt->Fill(iTau->pt());
       h_Tau_eta->Fill(iTau->eta());
       
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
