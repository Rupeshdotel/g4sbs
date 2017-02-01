#include "G4SBSESEPP.hh"
#include <fstream>

G4SBSESEPP::G4SBSESEPP() {
  Clear();
  fRadFileName = "";
  fRosenFileName = "";
  fRad = true;
  fRosenbluth = false;
  fUserEvents = 0;
  fRadEvents = 0;
  fRosenEvents = 0;
}

void G4SBSESEPP::Clear(){
  fEp.clear();
  fPp.clear();
  fGp.clear();
  fEth.clear();
  fEphi.clear();
  fPth.clear();
  fPphi.clear();
  fGth.clear();
  fGphi.clear();
}
////////////////////////////////////////////////////////////////////////////////
// The all important global index - accesses all containers within this
// class and gets incremented once per event. Doesn't have to be static...
//
unsigned int G4SBSESEPP::fEvent = 0;

////////////////////////////////////////////////////////////////////////////////
// Allow G4SBSEventGen access
//
void G4SBSESEPP::LoadFiles(int n,TString name,bool rad,bool rose){
  fUserEvents = n;
  fRadFileName = "esepp/" + name;
  fRad = rad;
  fRosenbluth = rose;

  if( fRad && fRosenbluth ) {
    if( fUserEvents == 1 ) fUserEvents++;
    fUserEvents /= 2;
  }

  if( fRad )  LoadRadEvents();

  if( fRosenbluth ) {
    // <user-defined-name>_<particletype><particlecharge>.dat
    // This should be safe...assuming the ESEPP naming convention is used
    int pos = fRadFileName.Last('.');
    fRosenFileName = fRadFileName.Replace(pos-1,1,'0');
    LoadRosenbluthEvents();
  }
}

////////////////////////////////////////////////////////////////////////////////
// Open .dat files - handle containers - change N events to be generated
// if necessary
//
void  G4SBSESEPP::OpenFile(TString name){
  const char* filename = name;
  int temp = 0; // line #

  std::ifstream input(filename);
  if( input.is_open() ){ 
    double Eprime, Pprime, Gprime; 
    double Eth, Ephi, Pth, Pphi, Gth, Gphi;

    Eprime = Pprime = Gprime = 0.0;
    Eth = Pth = Gth = 0.0;
    Ephi = Pphi = Gphi = 0.0;
   
    while(input >> Eprime >> Eth >> Ephi 
	  >> Pprime >> Pth >> Pphi 
	  >> Gprime >> Gth >> Gphi ){
      
      // Only take # of requested events
      if( temp >= fUserEvents ) break;

      fEp.push_back( Eprime );
      fPp.push_back( Pprime );
      fGp.push_back( Gprime );
      fEth.push_back( Eth );
      fEphi.push_back( Ephi );
      fPth.push_back( Pth );
      fPphi.push_back( Pphi );
      fGth.push_back( Gth );
      fGphi.push_back( Gphi );
      
      temp++;
    }
  } else {
    std::cerr << "Error: " << name << " did not "
	      << "open properly. Check for typos in .mac file or " 
	      << "add the /g4sbs/ESEPPfile <filename> command. Put file "
	      << "in the esepp/ directory." << std::endl;
  }
  input.close();

  if( temp != fUserEvents ) {
    std::cout << "Notice: ESEPP file " << name << " does not have "
	      << fUserEvents << " events, and will only be generating " 
	      << temp << " events." << std::endl;
  }
  
  std::cout << "Loaded " << temp << " ESEPP events from " 
	    << name << "." << std::endl;

  // This will change # of events to be generated, if necessary.
  if(fRad) fRadEvents = temp;
  if(fRosenbluth) fRosenEvents = temp;
}

////////////////////////////////////////////////////////////////////////////////
// Load up standard ESEPP .dat file output.
//
void G4SBSESEPP::LoadRadEvents(){
  OpenFile(fRadFileName);
}

////////////////////////////////////////////////////////////////////////////////
// Load up optional ESEPP Rosenbluth .dat file output.
//
void G4SBSESEPP::LoadRosenbluthEvents(){
  OpenFile(fRosenFileName);
}

////////////////////////////////////////////////////////////////////////////////
// Some get-methods to access the containers
//
double G4SBSESEPP::GetEprime(unsigned int index){
  if( index >= fEp.size() ) {
    std::cerr << "Error accessing Eprime due to bad index!" << std::endl;
    return 0.0;
  } else {
    return fEp[index];
  }
}

double G4SBSESEPP::GetEtheta(unsigned int index){
  if( index >= fEth.size() ) {
    std::cerr << "Error accessing Etheta due to bad index!" << std::endl;
    return 0.0;
  } else {
    return fEth[index];
  }
}

double G4SBSESEPP::GetEphi(unsigned int index){
  if( index >= fEphi.size() ) {
    std::cerr << "Error accessing Ephi due to bad index!" << std::endl;
    return 0.0;
  } else {
    return fEphi[index];
  }
}

double G4SBSESEPP::GetPprime(unsigned int index){
  if( index >= fPp.size() ) {
    std::cerr << "Error accessing Pprime due to bad index!" << std::endl;
    return 0.0;
  } else {
    return fPp[index];
  }
}

double G4SBSESEPP::GetPtheta(unsigned int index){
  if( index >= fPth.size() ) {
    std::cerr << "Error accessing Ptheta due to bad index!" << std::endl;
    return 0.0;
  } else {
    return fPth[index];
  }
}

double G4SBSESEPP::GetPphi(unsigned int index){
  if( index >= fPphi.size() ) {
    std::cerr << "Error accessing Pphi due to bad index!" << std::endl;
    return 0.0;
  } else {
    return fPphi[index];
  }
}

double G4SBSESEPP::GetGprime(unsigned int index){
  if( index >= fGp.size() ) {
    std::cerr << "Error accessing Gprime due to bad index!" << std::endl;
    return 0.0;
  } else {
    return fGp[index];
  }
}

double G4SBSESEPP::GetGtheta(unsigned int index){
  if( index >= fGth.size() ) {
    std::cerr << "Error accessing Gtheta due to bad index!" << std::endl;
    return 0.0;
  } else {
    return fGth[index];
  }
}

double G4SBSESEPP::GetGphi(unsigned int index){
  if( index >= fGphi.size() ) {
    std::cerr << "Error accessing Gphi due to bad index!" << std::endl;
    return 0.0;
  } else {
    return fGphi[index];
  }
}
