Sampling Calorimetry with Resistive Anode Micromegas (SCREAM)

Before running the code the environment must be set. So, 

source setupGeant410p03.sh

Then compile: 

gmake

To run without visualization open and change according to your needs run.mac. Do, 

Scream run.mac

For more statistics change and run the scripts in Parallel directory. 

After running the code a number of histograms are produced for electrons, muon and pions:  

1. Histo 1-5: Energy deposited to detector chamber1 pads (1,5), (2,5), (3,5), (4,5), (5,5). 

2. Histo 6-11: The total energy deposited in chambers 1 to 6. 

3. Histo 12: Energy deposited in all chambers. 

4. Histo 13-17: Smeared energy deposited to detector chamber1 pads (1,5), (2,5), (3,5), (4,5), (5,5). 

5. Histo 18-23: Smeared total energy deposited in chambers 1 to 6. 

6. Histo 24: Smeared energy deposited in all chambers. 

7. Histo 25: The smear factor used only for chamber 1. Maybe we could add other also. 

