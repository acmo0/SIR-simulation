# Simulation of SIERD model
## Installation
Executables files are located in the bin folder, please download *generate.py* and *simulation_sir* from the [lastest release](https://github.com/acmo0/SIR-simulation/releases/tag/v1.0) or clone the github repo.
To plot calculated data, you need to install matplotlib using :
```
sudo apt install python3-matplotlib
```
or
```
pip install matplotlib
```
## Usage
The model can be schematized like this :
![fig1](https://github.com/acmo0/SIR-simulation/blob/main/img/diag2.png)
To start the simulation use :
```
./simulation_sir S0 E0 I0 alpha beta gamma delta epsilon mu nu duration points
```
Explanation of parameters (see figure too) :
```
S0 : initial percentage of healthy population
E0 : initial percentage of exposed pupulation
I0 initial percentage of infected population
alpha : incubation rate per time
beta : average number of contacts (per person per time)
gamma : cure rate (per time)
delta : death rate (per time)
epsilon : deimmunization rate (per time)
mu : natural death rate (per time)
nu : birth rate (per time)
duration of simulation (in day)
points : number of points for the simulation (at least 10000 is recommended)
```
## Install from sources
First, clone the github repo and go to source then compile program with :
```
gcc -o simulation_sir model.c
```
## Exemple
```
./simulation_sir 0.99 0 0.01 1.3 5.7 0.2 0.0125 0.01 0.0001 0.0008 40 300000
```
gives the following output :

![fig](https://github.com/acmo0/SIR-simulation/blob/main/img/fig_demo.png)
