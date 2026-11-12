#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TMVA/Reader.h"

void TMVA_applying() {
    TFile *inputFile = TFile::Open("../data/Higgs_data.root");
    TTree *trees[2] = {(TTree *)inputFile->Get("sig_tree"),
                       (TTree *)inputFile->Get("bkg_tree")};

    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");

    Float_t vars[7];
    const char *names[] =
        {"m_jj", "m_jjj", "m_lv", "m_jlv", "m_bb", "m_wbb", "m_wwbb"};

    for (int i = 0; i < 7; i++)
        reader->AddVariable(names[i], &vars[i]);

    reader->BookMVA("BDT method",
                    "dataset/weights/TMVAClassification_BDT.weights.xml");

    TH1F *hSig = new TH1F("hSig", "BDT response;BDT score;Normalised events", 50, -1, 1);
    TH1F *hBkg = new TH1F("hBkg", "BDT response;BDT score;Normalised events", 50, -1, 1);
    TH1F *hists[2] = {hSig, hBkg};

    for (int t = 0; t < 2; t++) {
        for (int i = 0; i < 7; i++)
            trees[t]->SetBranchAddress(names[i], &vars[i]);

        for (Long64_t ievt = 0; ievt < trees[t]->GetEntries(); ++ievt) {
            trees[t]->GetEntry(ievt);
            Double_t bdtScore = reader->EvaluateMVA("BDT method");
            // bdtScore near +1 -> signal-like, near -1 -> background-like
            hists[t]->Fill(bdtScore);
        }
    }

    gStyle->SetOptStat(0);
    TCanvas *c = new TCanvas("c", "BDT response", 800, 600);

    hSig->Scale(1.0 / hSig->Integral());
    hBkg->Scale(1.0 / hBkg->Integral());

    hSig->SetLineColor(kBlue);   hSig->SetFillColorAlpha(kBlue, 0.3);
    hBkg->SetLineColor(kRed);    hBkg->SetFillColorAlpha(kRed, 0.3);
    hSig->SetMaximum(1.2 * std::max(hSig->GetMaximum(), hBkg->GetMaximum()));

    hSig->Draw("HIST");
    hBkg->Draw("HIST SAME");

    TLegend *leg = new TLegend(0.65, 0.75, 0.88, 0.88);
    leg->AddEntry(hSig, "Signal", "f");
    leg->AddEntry(hBkg, "Background", "f");
    leg->Draw();

    c->SaveAs("bdt_response.png");

    TFile *out = TFile::Open("BDT_applied.root", "RECREATE");
    hSig->Write();
    hBkg->Write();
    out->Close();
}
