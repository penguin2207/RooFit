/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "../include/Poly2PLShape.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(Poly2PLShape) 

 Poly2PLShape::Poly2PLShape(const char *name, const char *title, 
                        RooAbsReal& _x,
                        RooAbsReal& _xbar,
                        RooAbsReal& _sigma,
                        RooAbsReal& _alpha,
                        RooAbsReal& _n) :
   RooAbsPdf(name,title), 
   x("x","x",this,_x),
   xbar("xbar","xbar",this,_xbar),
   sigma("sigma","sigma",this,_sigma),
   alpha("alpha","alpha",this,_alpha),
   n("n","n",this,_n)
 { 
 } 


 Poly2PLShape::Poly2PLShape(const Poly2PLShape& other, const char* name) :  
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   xbar("xbar",this,other.xbar),
   sigma("sigma",this,other.sigma),
   alpha("alpha",this,other.alpha),
   n("n",this,other.n)
 { 
 } 



 Double_t Poly2PLShape::evaluate() const 
 { 
   assert(alpha > 0. && alpha < TMath::Sqrt(2) && n > 1.);

   double y((x - xbar) / sigma);

   if(y < -TMath::Sqrt(2.)) return 0.;

   if(y < alpha) return -y * y / 2. + 1.;
   else{
     double f(alpha / n);
     double atAlpha(-alpha * alpha / 2. + 1.);
     return TMath::Power(f, n) * TMath::Power(atAlpha, n + 1.) * TMath::Power(y - alpha + atAlpha * f, -n);
   }
 } 



 Int_t Poly2PLShape::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
 { 
   if (matchArgs(allVars,analVars,x)) return 1 ; 
   return 0 ; 
 } 



 Double_t Poly2PLShape::analyticalIntegral(Int_t code, const char* rangeName) const  
 { 
   assert(code==1) ; 
   if(code == 1){
     double atAlpha(-alpha * alpha / 2. + 1.);
     return sigma * (-(alpha * alpha * alpha + 2. * TMath::Sqrt(2.)) / 6. + alpha + TMath::Sqrt(2.) + atAlpha * atAlpha * n / alpha / (n - 1.));
   }
   return 0 ; 
 } 



