import matplotlib.pyplot as plt
import numpy as np
import csv


# dt = 1.0/10000.0 # 10kHz
# t = np.arange(0.0, 1.0, dt) # 10s
# # a constant plus 100Hz and 1000Hz
# s = 4.0 * np.sin(2 * np.pi * 100 * t) + 0.25 * np.sin(2 * np.pi * 1000 * t) + 25
def plotfft(filename: str):
    t = [] # column 0
    data1 = [] # column 1
    # data2 = [] # column 2

    with open(filename) as f:
        # open the csv file
        reader = csv.reader(f)
        for row in reader:
            # read the rows 1 one by one
            t.append(float(row[0])) # leftmost column
            data1.append(float(row[1])) # second column
            # data2.append(float(row[2])) # third column

    # for i in range(len(t)):
    #     # print the data to verify it was read
    #     print(str(t[i]) + ", " + str(data1[i]))

    #######################################################

    Fs = len(t)/t[-1]


    Ts = 1.0/Fs; # sampling interval
    ts = np.arange(0,t[-1],Ts) # time vector
    y = data1 # the data to make the fft from
    n = len(y) # length of the signal
    k = np.arange(n)
    T = n/Fs
    frq = k/T # two sides frequency range
    frq = frq[range(int(n/2))] # one side frequency range
    Y = np.fft.fft(y)/n # fft computing and normalization
    Y = Y[range(int(n/2))]

    fig, (ax1, ax2) = plt.subplots(2, 1)
    ax1.plot(t,y,'b')
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,abs(Y),'b') # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')
    plt.show()
    # plt.savefig(filename[:-4] + "_plot")

plotfft("sigA.csv")
input()
plotfft("sigB.csv")
input()
plotfft("sigC.csv")
input()
plotfft("sigD.csv")