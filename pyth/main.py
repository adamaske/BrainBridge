import matplotlib.pyplot as plt
import numpy as np
import openbci as ob
from openbci import cyton as bci

from brainflow.board_shim import BoardShim, BrainFlowInputParams, BoardIds, BrainFlowPresets
def plot():
    x = np.linspace(0, 20, 100)  # Create a list of evenly-spaced numbers over the range
    plt.plot(x, np.sin(x))       # Plot the sine of each x point
    plt.show()                   # Display the plot
    
def hello_world():
    print('Hello World!')

def main():
    BoardShim.enable_dev_board_logger()
    params = BrainFlowInputParams()

if __name__ == "__main__":
    hello_world()
    plot()