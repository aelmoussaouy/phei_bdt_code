# phei_bdt_code

Higgs boson event classification with Boosted Decision Trees (BDTs) using [ROOT](https://root.cern) and TMVA.

The input data, `data/Higgs_data.root`, contains two trees: `sig_tree` (signal) and `bkg_tree` (background).

## Repository structure

```
phei_bdt_code/
├── courses/     # course material (coming soon)
├── exercices/   # exercises (coming soon)
├── scripts/     # Python notebooks and ROOT C++ macros
└── data/        # Higgs_data.root
```

There are **two ways** to run the code:

1. **Python (Jupyter notebooks on Google Colab).** No local installation needed.
2. **ROOT C++ macros.** Run locally with a ROOT installation.

---

## Option 1: Python notebooks on Google Colab

| Notebook | Description | Run |
|---|---|---|
| `scripts/ROOT.ipynb` | Installs ROOT on Colab and runs a quick check | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/aelmoussaouy/phei_bdt_code/blob/main/scripts/ROOT.ipynb) |
| `scripts/Classification_Higgs_with_BDT_.ipynb` | Signal/background classification with a single TMVA BDT | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/aelmoussaouy/phei_bdt_code/blob/main/scripts/Classification_Higgs_with_BDT_.ipynb) |
| `scripts/Comparing_BDTs_Higgs_classfication.ipynb` | Comparison of several BDT configurations with ROC curves | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/aelmoussaouy/phei_bdt_code/blob/main/scripts/Comparing_BDTs_Higgs_classfication.ipynb) |

**Steps**

1. Download `Higgs_data.root` from the `data/` folder of this repository and upload it to the top level of your Google Drive (My Drive):
   ```
   MyDrive/Higgs_data.root
   ```
   (or change `inputFileName` in the notebook to point to your copy).
2. Click an **Open in Colab** badge above.
3. Run the cells in order (`Runtime > Run all`). The first cells install ROOT, which takes a few minutes, and then ask you to authorise access to Google Drive.

---

## Option 2: ROOT C++ macros

| Macro | Description |
|---|---|
| `scripts/TMVA_training.C` | Trains a BDT on 7 mass variables and writes `TMVA_Output.root` and the weights to `dataset/weights/` |
| `scripts/TMVA_applying.C` | Loads the trained BDT, applies it to signal and background events, and saves `bdt_response.png` and `BDT_applied.root` |

**Requirements:** a working [ROOT installation](https://root.cern/install/) with TMVA enabled (included by default).

**Steps**

```bash
# 1. Get the code and data
git clone https://github.com/aelmoussaouy/phei_bdt_code.git
cd phei_bdt_code/scripts

# 2. Train the BDT
root -l -b -q TMVA_training.C

# 3. Apply the trained BDT (run after training)
root -l -b -q TMVA_applying.C

# 4. (Optional) Inspect the training results with the TMVA GUI
root -l -e 'TMVA::TMVAGui("TMVA_Output.root")'
```

Flags: `-l` skips the ROOT splash screen, `-b` runs in batch mode (no windows), and `-q` quits when the macro finishes.
Run the macros from the `scripts/` folder: they read the data from `../data/Higgs_data.root`, and the output files are written to `scripts/`.
