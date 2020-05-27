# Conda 常用命令

Windows 系统的 powershell 下无法激活 conda 环境，需要切换到 cmd 下使用。

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
