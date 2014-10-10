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

   std::cout << "EVENT IN ANALYZER = " << event_count << std::endl;
   std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

   edm::Handle<reco::PFTauCollection> tauHandle;
   iEvent.getByLabel(tauLabel_,tauHandle);

   reco::PFTauCollection thetaus = *tauHandle;

   edm::Handle<reco::PFTauDiscriminator> tauIDDiscr;


   for(reco::PFTauCollection::const_iterator tau_iter = thetaus.begin(); tau_iter!=thetaus.end(); ++tau_iter){

     //reco::PFTauRef thistau = *tau_iter;

     std::cout << "HELLO TAU:pt,eta " << tau_iter->pt() << " " << tau_iter->eta() << std::endl;
     //std::cout << "HELLO TAU decay mode finding " << tau_iter->tauID("decayModeFindingOldDMs") << std::endl;
     std::cout << "HELLO TAU:decay mode " << tau_iter->decayMode() << std::endl;

     //Recommendation
     //Taus that pass decay mode finding and have pt > 20 GeV
     if( tau_iter->decayMode() && tau_iter->pt() > 20) {
     std::cout << "HELLO TAU:pt,eta " << tau_iter->pt() << " " << tau_iter->eta() << std::endl;
     std::cout << "HELLO TAU:decay mode " << tau_iter->decayMode() << std::endl;

     }

     //FILL THE HISTROGRAMS
     h_Tau_pt->Fill(tau_iter->pt());
     h_Tau_eta->Fill(tau_iter->eta());


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

}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauTest::endJob() 
{
  rootFile_->cd();

  //WRITE-OUT THE HISTOGRAMS 
  h_Tau_pt->Write();
  h_Tau_eta->Write();


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
