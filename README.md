# phei_bdt_code

Higgs boson event classification with Boosted Decision Trees (BDTs) using [ROOT](https://root.cern) and TMVA.

## Notebooks

| Notebook | Description | Run |
|---|---|---|
| `ROOT.ipynb` | Installs ROOT on Colab and runs a quick check | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/aelmoussaouy/phei_bdt_code/blob/main/ROOT.ipynb) |
| `Classification_Higgs_with_BDT_.ipynb` | Signal/background classification with a single TMVA BDT | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/aelmoussaouy/phei_bdt_code/blob/main/Classification_Higgs_with_BDT_.ipynb) |
| `Comparing_BDTs_Higgs_classfication.ipynb` | Comparison of several BDT configurations with ROC curves | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/aelmoussaouy/phei_bdt_code/blob/main/Comparing_BDTs_Higgs_classfication.ipynb) |

## Data

The notebooks read `Higgs_data.root` from Google Drive. Before running, upload it to:

```
MyDrive/Colab_Notebooks/Higgs_data.root
```

or change `inputFileName` in the notebook to point to your copy.
