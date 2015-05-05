//===============================================================================
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TF1.h"
#include "TH1.h"

//===============================================================================
void Calibration(){

  //===============================================================================
  gStyle->SetOptTitle(0);

  //The root files with the individual plots 
  const int numberoffiles = 4;
  const int numberofchambers = 6;

  TString filename[numberoffiles];
  //mu-
  filename[0]="testcalo_mu-_50.root";
  filename[1]="testcalo_mu-_100.root";
  filename[2]="testcalo_mu-_150.root";
  filename[3]="testcalo_mu-_200.root";

  //Energy distributions we want to fit 
  TString energy[numberofchambers];
  //nosmear
  // energy[0] = "histo/6";
  // energy[1] = "histo/7";
  // energy[2] = "histo/8";
  // energy[3] = "histo/9";
  // energy[4] = "histo/10";
  // energy[5] = "histo/11";

  //smeared
  energy[0] = "histo/18";
  energy[1] = "histo/19";
  energy[2] = "histo/20";
  energy[3] = "histo/21";
  energy[4] = "histo/22";
  energy[5] = "histo/23";

  double mpshift = 0;//-0.22278298;

  TGraphErrors *grMPV[numberoffiles];
  TGraphErrors *grSigma[numberoffiles];
  
  //For the mpv and sigma plot 
  std::vector<double> chamb;
  std::vector<double> mpv;
  std::vector<double> thesigma;
  std::vector<double> chamr;
  std::vector<double> mpvr;
  std::vector<double> thesigmaerr;
  chamb.push_back(1.);chamb.push_back(2.);chamb.push_back(3.);chamb.push_back(4.);chamb.push_back(5.);chamb.push_back(6.);
  
  //======================================================================================
  //Canvas
  TCanvas *can[numberoffiles][numberofchambers];
  TString canname;

  TCanvas *canmpv[numberoffiles];
  
  //======================================================================================
  //Read the files and histograms here
  TFile* files[numberoffiles];
  for (int k=0; k<numberoffiles; k++){
    files[k]= new TFile(filename[k]);
  }
  TH1F * histo[numberoffiles][numberofchambers];

  for (int i=0; i<numberoffiles; i++){
    gROOT->Reset();
    for (int k=0; k<numberofchambers; k++){
      histo[i][k]= (TH1F*) files[i]->Get(energy[k]);

      if (!histo[i][k]){std::cerr << "Could not get histogram " << energy[k] << "in file "
				    <<  files[i]->GetName() << std::endl;}
      std::cout << "=========================================================================" << std::endl;
      std::cout << files[i]->GetName() << std::endl;

      canname = filename[i] + histo[i][k]->GetName();
      can[i][k] = new TCanvas(canname, canname,800,600);
      can[i][k]->cd();

      histo[i][k]->Draw();

      TF1 *fit = 0;
      double mpc = 0;
      double minfit = 0.;
      double maxfit = 0.05;

      histo[i][k]->Fit("landau","R+","same",minfit,maxfit);
      fit = (TF1*) histo[i][k]->GetFunction("landau");

      mpc = fit->GetParameter(1) - mpshift * fit->GetParameter(2); 

      mpv.push_back(mpc * 1000.);
      mpvr.push_back(fit->GetParError(1) * 1000.);
      chamr.push_back(0.);

      thesigma.push_back(fit->GetParameter(2) * 1000.);
      thesigmaerr.push_back(fit->GetParError(2) * 1000.);
   
      // std::cout << "Chamber " << k << " MPV "<< mpc << std::endl;

      can[i][k]->Print(canname + ".root",".root");
      can[i][k]->Close();
  
      
    }// end of loop over histos   
    
    //For the multi plot
    grMPV[i] = new TGraphErrors(mpv.size(),&chamb[0],&mpv[0],&mpvr[0],&chamr[0]);
    grSigma[i] = new TGraphErrors(thesigma.size(),&chamb[0],&thesigma[0],&thesigmaerr[0],&chamr[0]);
    
    mpv.clear();
    mpvr.clear();
    thesigma.clear();
    thesigmaerr.clear();
    chamr.clear();
    
  }// end of loop over files
  
  const Int_t nch = 6;
  char *chamb_labels[nch] = {"Std1","Star","Mirror","Snake","Spider","Std2"};
  TFile f("mpvandsigma.root","recreate");

  //======================================================================================
  //For the multi mpv plot
  TCanvas *c1 = new TCanvas("c1","mpv",200,10,1200,968); 
  //Change the bin labels
  grMPV[0]->GetXaxis()->SetBinLabel( grMPV[0]->GetXaxis()->FindBin(1.0) , chamb_labels[0]); 
  grMPV[0]->GetXaxis()->SetBinLabel( grMPV[0]->GetXaxis()->FindBin(2.0) , chamb_labels[1]); 
  grMPV[0]->GetXaxis()->SetBinLabel( grMPV[0]->GetXaxis()->FindBin(3.0) , chamb_labels[2]); 
  grMPV[0]->GetXaxis()->SetBinLabel( grMPV[0]->GetXaxis()->FindBin(4.0) , chamb_labels[3]); 
  grMPV[0]->GetXaxis()->SetBinLabel( grMPV[0]->GetXaxis()->FindBin(5.0) , chamb_labels[4]); 
  grMPV[0]->GetXaxis()->SetBinLabel( grMPV[0]->GetXaxis()->FindBin(6.0) , chamb_labels[5]); 
  grMPV[0]->GetXaxis()->SetTitleOffset(2.0);
  grMPV[0]->GetYaxis()->SetTitleOffset(1.2);
  grMPV[0]->GetXaxis()->SetLabelSize(0.06);
  
  grMPV[0]->SetMarkerStyle(20); 
  grMPV[0]->SetMarkerSize(1.2); 
  grMPV[0]->SetMarkerColor(1);  
  grMPV[0]->SetLineColor(1);
  grMPV[0]->Draw("APL");
  c1->Update();
    
  grMPV[1]->SetMarkerStyle(21);
  grMPV[1]->SetMarkerSize(1.2); 
  grMPV[1]->SetMarkerColor(2);
  grMPV[1]->SetLineColor(2);
  grMPV[1]->Draw("PSL");
  c1->Update();

  grMPV[2]->SetMarkerStyle(22);
  grMPV[2]->SetMarkerSize(1.2); 
  grMPV[2]->SetMarkerColor(3);
  grMPV[2]->SetLineColor(3);
  grMPV[2]->Draw("PSL");
  c1->Update();

  grMPV[3]->SetMarkerStyle(23);
  grMPV[3]->SetMarkerSize(1.2); 
  grMPV[3]->SetMarkerColor(4);
  grMPV[3]->SetLineColor(4);
  grMPV[3]->Draw("PSL");
  c1->Update();
  
  TLegend *leg = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions of pad dimensions
  leg->AddEntry(grMPV[0],"50 GeV","LP");  
  leg->AddEntry(grMPV[1],"100 GeV","LP");  
  leg->AddEntry(grMPV[2],"150 GeV","LP");  
  leg->AddEntry(grMPV[3],"200 GeV","LP");  
  leg->SetFillColor(18);
  leg->SetHeader(" #mu^{-} energies ");
                                            
  leg->Draw("PS");
  c1->Update();
  
  grMPV[0]-> SetTitle( " Landau Most Probable Value for different #mu^{-} energies  " );
  grMPV[0]->GetHistogram()->SetXTitle(" Chamber ");
  grMPV[0]->GetHistogram()->SetYTitle(" Landau MPV (MIPs) (keV) ");
  grMPV[0]->GetYaxis()->SetRangeUser(0.7,1.1);
  //grMPV[0]->GetXaxis()->SetRangeUser(0.,5000.);
  c1->Update();

  //c1->Print("mpv.png",".png");

  c1->Write();
  c1->Close();

 
  //======================================================================================
  //For the multi sigma plot
  TCanvas *c2 = new TCanvas("c2","sigma",200,10,1200,968); 
  //Change the bin labels
  grSigma[0]->GetXaxis()->SetBinLabel( grSigma[0]->GetXaxis()->FindBin(1.0) , chamb_labels[0]); 
  grSigma[0]->GetXaxis()->SetBinLabel( grSigma[0]->GetXaxis()->FindBin(2.0) , chamb_labels[1]); 
  grSigma[0]->GetXaxis()->SetBinLabel( grSigma[0]->GetXaxis()->FindBin(3.0) , chamb_labels[2]); 
  grSigma[0]->GetXaxis()->SetBinLabel( grSigma[0]->GetXaxis()->FindBin(4.0) , chamb_labels[3]); 
  grSigma[0]->GetXaxis()->SetBinLabel( grSigma[0]->GetXaxis()->FindBin(5.0) , chamb_labels[4]); 
  grSigma[0]->GetXaxis()->SetBinLabel( grSigma[0]->GetXaxis()->FindBin(6.0) , chamb_labels[5]); 
  grSigma[0]->GetXaxis()->SetTitleOffset(2.0);
  grSigma[0]->GetYaxis()->SetTitleOffset(1.2);
  grSigma[0]->GetXaxis()->SetLabelSize(0.06);
  
  grSigma[0]->SetMarkerStyle(20); 
  grSigma[0]->SetMarkerSize(1.2); 
  grSigma[0]->SetMarkerColor(1);  
  grSigma[0]->SetLineColor(1);
  grSigma[0]->Draw("APL");
  c2->Update();
    
  grSigma[1]->SetMarkerStyle(21);
  grSigma[1]->SetMarkerSize(1.2); 
  grSigma[1]->SetMarkerColor(2);
  grSigma[1]->SetLineColor(2);
  grSigma[1]->Draw("PSL");
  c2->Update();

  grSigma[2]->SetMarkerStyle(22);
  grSigma[2]->SetMarkerSize(1.2); 
  grSigma[2]->SetMarkerColor(3);
  grSigma[2]->SetLineColor(3);
  grSigma[2]->Draw("PSL");
  c2->Update();

  grSigma[3]->SetMarkerStyle(23);
  grSigma[3]->SetMarkerSize(1.2); 
  grSigma[3]->SetMarkerColor(4);
  grSigma[3]->SetLineColor(4);
  grSigma[3]->Draw("PSL");
  c2->Update();
  
  TLegend *leg = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions of pad dimensions
  leg->AddEntry(grSigma[0],"50 GeV","LP");  
  leg->AddEntry(grSigma[1],"100 GeV","LP");  
  leg->AddEntry(grSigma[2],"150 GeV","LP");  
  leg->AddEntry(grSigma[3],"200 GeV","LP");  
  leg->SetFillColor(18);
  leg->SetHeader(" #mu^{-} energies ");
                                            
  leg->Draw("PS");
  c2->Update();
  
  grSigma[0]-> SetTitle( " Landau Sigma Value for different #mu^{-} energies  " );
  grSigma[0]->GetHistogram()->SetXTitle(" Chamber ");
  grSigma[0]->GetHistogram()->SetYTitle(" Landau Sigma (keV) ");
  grSigma[0]->GetYaxis()->SetRangeUser(0.15,0.32);
  //grSigma[0]->GetXaxis()->SetRangeUser(0.,5000.);
  c2->Update();

  //c2->Print("sigma.png",".png");

  c2->Write();
  f.Close();


  
  


}

