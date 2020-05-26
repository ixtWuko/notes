# Conda ????

Windows???powershell??????conda???????cmd??
```bash
# update
conda update conda
conda update anaconda

# environment
conda env list # show all environment
conda create --name machine_learning python=3.5 scipy scikit-learn
conda remove --name machine_learning --all

# activate
activate machine_learning

# install package
conda search matplotlib
conda install --name machine_learning matplotlib
conda install matplotlib # in current environment

conda remove --name machine_learning matplotlib
conda remove matplotlib # in current environment

# update package
conda update matplotlib
conda update --all
```
