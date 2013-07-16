/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Generic background shape with erf-like turn on and exponential decay

#include "Riostream.h" 

#include "../include/ErfcExpShape.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(ErfcExpShape) 

 ErfcExpShape::ErfcExpShape(const char *name, const char *title, 
                        RooAbsReal& _mass,
                        RooAbsReal& _alpha,
                        RooAbsReal& _beta,
                        RooAbsReal& _gamma) :
   RooAbsPdf(name,title), 
   mass("mass","mass",this,_mass),
   alpha("alphaBKG","alphaBKG",this,_alpha),
   beta("betaBKG","betaBKG",this,_beta),
   gamma("gammaBKG","gammaBKG",this,_gamma)
 { 
 } 


 ErfcExpShape::ErfcExpShape(const ErfcExpShape& other, const char* name) :  
   RooAbsPdf(other,name), 
   mass("mass",this,other.mass),
   alpha("alphaBKG",this,other.alpha),
   beta("betaBKG",this,other.beta),
   gamma("gammaBKG",this,other.gamma)
 { 
 } 



 Double_t ErfcExpShape::evaluate() const 
 { 
   return TMath::Erfc((beta * (alpha - mass))) / 2. * TMath::Exp(-gamma * mass) ; 
 } 



 Int_t ErfcExpShape::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
 { 
   if (matchArgs(allVars,analVars,mass)) return 1 ; 
   return 0 ; 
 } 



 Double_t ErfcExpShape::analyticalIntegral(Int_t code, const char* rangeName) const  
 { 
   if(code==1) return TMath::Exp(gamma * (-alpha + gamma / 4. / beta / beta)) / gamma;
   return 0 ; 
 } 


