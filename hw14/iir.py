import matplotlib.pyplot as plt
import numpy as np
import csv


# dt = 1.0/10000.0 # 10kHz
# t = np.arange(0.0, 1.0, dt) # 10s
# # a constant plus 100Hz and 1000Hz
# s = 4.0 * np.sin(2 * np.pi * 100 * t) + 0.25 * np.sin(2 * np.pi * 1000 * t) + 25
def plotfft(filename: str, a: float, b: float):
    t = [] # column 0
    data1 = [] # column 1
    t_avg = []
    data1_avg = []
    # data2 = [] # column 2
    
    

    with open(filename) as f:
        # open the csv file
        reader = csv.reader(f)
        for i, row in enumerate(reader):
            # read the rows 1 one by one
            t.append(float(row[0])) # leftmost column
            data1.append(float(row[1])) # second column

            t_avg.append(float(row[0]))
            if i > 0:
                data1_avg.append(float(data1_avg[-1]*a + b * float(row[1])))
            else:
                data1_avg.append(float(b * float(row[1])))

            # else:
            #     t_avg.append(0)
            #     data1_avg.append(0)
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

    fig, axs = plt.subplots(2, 2)
    fig.suptitle(filename[:-4] + " a: " + str(a) + " b: " + str(b))
    axs[0,0].plot(t,y,'b')
    axs[0,0].set_xlabel('Time')
    axs[0,0].set_ylabel('Amplitude') 
    axs[1,0].loglog(frq,abs(Y),'b') # plotting the fft
    axs[1,0].set_xlabel('Freq (Hz)')
    axs[1,0].set_ylabel('|Y(freq)|')
    
    
    
    # plt.show()
    # plt.savefig(filename[:-4] + "_plot")

    ################################ now plot avg data

    Fs_avg = len(t_avg)/t_avg[-1]


    Ts_avg = 1.0/Fs_avg; # sampling interval
    ts_avg = np.arange(0,t_avg[-1],Ts_avg) # time vector
    y_avg = data1_avg # the data to make the fft from
    n_avg = len(y_avg) # length of the signal
    k_avg = np.arange(n_avg)
    T_avg = n_avg/Fs_avg
    frq_avg = k_avg/T_avg # two sides frequency range
    frq_avg = frq_avg[range(int(n_avg/2))] # one side frequency range
    Y_avg = np.fft.fft(y_avg)/n_avg # fft computing and normalization
    Y_avg = Y_avg[range(int(n_avg/2))]

   
    axs[0,1].plot(t_avg,y_avg,'r')
    axs[0,1].set_xlabel('Time')
    axs[0,1].set_ylabel('Amplitude')
    axs[1,1].loglog(frq_avg,abs(Y_avg),'r') # plotting the fft
    axs[1,1].set_xlabel('Freq (Hz)')
    axs[1,1].set_ylabel('|Y(freq)|')
    # plt.show()
    plt.savefig(filename[:-4] + "_iir")


plotfft("sigA.csv", 0.999, 0.001)
# input()
plotfft("sigB.csv",0.999, 0.001)
# input()
plotfft("sigC.csv",0.995, 0.005)
# input()
plotfft("sigD.csv",0.999, 0.001)