#include "TFile.h"
#include "TTree.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Types.h"

void TMVA_training() {
    TFile *inputFile = TFile::Open("Higgs_data.root");
    TTree *signalTree = (TTree *)inputFile->Get("sig_tree");
    TTree *backgroundTree = (TTree *)inputFile->Get("bkg_tree");

    TFile *outputFile = TFile::Open("TMVA_Output.root", "RECREATE");

    TMVA::Factory factory("TMVAClassification", outputFile,
                          "!V:ROC:!Silent:Color:AnalysisType=Classification");

    TMVA::DataLoader *loader = new TMVA::DataLoader("dataset");

    for (auto v : {"m_jj", "m_jjj", "m_lv", "m_jlv", "m_bb", "m_wbb", "m_wwbb"})
        loader->AddVariable(v, 'F');

    loader->AddSignalTree(signalTree, 1.0);
    loader->AddBackgroundTree(backgroundTree, 1.0);

    loader->PrepareTrainingAndTestTree("", "",
                                       "nTrain_Signal=5000:nTrain_Background=5000:"
                                       "SplitMode=Random:NormMode=NumEvents:!V");

    factory.BookMethod(loader, TMVA::Types::kBDT, "BDT",
                       "!V:NTrees=400:MinNodeSize=2.5%:MaxDepth=3:"
                       "BoostType=AdaBoost:AdaBoostBeta=0.5:"
                       "SeparationType=GiniIndex:nCuts=20");

    factory.TrainAllMethods();
    factory.TestAllMethods();
    factory.EvaluateAllMethods();
}

// root -l -e 'TMVA::TMVAGui("TMVA_Output.root")'