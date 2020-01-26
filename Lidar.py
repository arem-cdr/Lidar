"""

import serial
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import numpy as np
from math import *

ser = serial.Serial('/dev/ttyACM0', 115200)
L = []


# Always start by initializing Qt (only once per application)
app = QtGui.QApplication([])

# Define a top-level widget to hold everything
win = QtGui.QWidget()
win.setWindowTitle("IHM Asservissement")


plot = pg.PlotWidget()
listw = QtGui.QListWidget()
layout = QtGui.QGridLayout()
win.setLayout(layout)

layout.addWidget(plot)  # plot goes on right side, spanning 3 rows


s1 = pg.ScatterPlotItem(size=10, pen=pg.mkPen(
    None), brush=pg.mkBrush(255, 255, 255, 120))
spots = [{'pos': [0, 0], 'data': 1}]
s1.addPoints(spots)
plot.addItem(s1)
plot.setXRange(0, 2000)
plot.setYRange(0, 3000)


win.show()
while True:
    ser_bytes = ser.readline()
    decoded_byte = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
    L.append(decoded_byte)
    if (decoded_byte == 100.0):
        print(L)
        # print("Stop")
        L.pop(360)
        Lx = [1000+L[i]*cos(i*pi/180.0) for i in range(360)]
        Ly = [1500+L[i]*sin(i*pi/180.0) for i in range(360)]
        pos = np.ndarray(shape=(2, 360), dtype=float)
        for i in range(360):
            pos[0, i] = Lx[i]
            pos[1, i] = Ly[i]
        # print(pos)
        spots = [{'pos': pos[:, i], 'data': 1} for i in range(360)]
        s1.setData(spots)
        L.clear()
        QtGui.QApplication.processEvents()


app.exec_()


"""

import serial
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import numpy as np
from math import *

POS_ROBOT_X = 1000
POS_ROBOT_Y = 750
R = 100

# init serial
ser = serial.Serial('/dev/ttyACM0', 2000000)
L = []
# Always start by initializing Qt (only once per application)
app = QtGui.QApplication([])

# Define a top-level widget to hold everything
win = QtGui.QWidget()
win.setWindowTitle("Lidar")

plot = pg.PlotWidget()
layout = QtGui.QGridLayout()
win.setLayout(layout)
Data = pg.ScatterPlotItem(pen=None, symbol='o',
                          symbolPen=None, symbolBrush='r')
Curve = pg.PlotCurveItem()
plot.addItem(Data)
plot.setXRange(0, 2000)
plot.setYRange(0, 3000)

layout.addWidget(plot)  # plot goes on right side, spanning 3 rows
win.show()


while True:
    ser_bytes = ser.readline()
    decoded_byte = 0
    try:
        decoded_byte = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
    except ValueError:
        print("Failed to convert string to float")
    L.append(decoded_byte)
    if (decoded_byte == 100.0):
        # print(L)
        # print("Stop")
        spots = []
        robots = []
        if len(L) == 361:
            L.pop(360)

            Lx = [1000+L[i]*cos(i*pi/180.0) for i in range(360)]
            Ly = [750+L[i]*sin(i*pi/180.0) for i in range(360)]
            pos = np.ndarray(shape=(2, 360), dtype=float)
            for i in range(360):
                indice = [i-2, i-1, i, i+1, i+2]
                if (i == 0):
                    indice[0] = 358
                    indice[1] = 359
                if (i == 1):
                    indice[0] = 359
                if (i == 359):
                    indice[3] = 0
                    indice[4] = 1
                if (i == 358):
                    indice[4] = 0
                somme = [0, 0, 0, 0, 0]
                for j in range(5):
                    somme[j] = L[indice[2]] - L[indice[j]]
                if (abs(somme[1]) < 70 and abs(somme[3]) < 70):
                    spots.append(
                        {'pos': (Lx[i], Ly[i]), 'size': 5, 'pen': None, 'brush': 'g', 'symbol': 'o'})
                    if (len(robots) == 0):
                        if ((Lx[i]-POS_ROBOT_X != 0 or Ly[i]-POS_ROBOT_Y != 0) and (0 <= Lx[i] <= 2000 and 0 <= Ly[i] <= 3000)):
                            # print(Lx[i]-POS_ROBOT_X, Ly[i]-POS_ROBOT_Y)
                            robots.append([Lx[i], Ly[i]])
                    else:
                        check = 1
                        for k in range(len(robots)):
                            if (((robots[k][0]-Lx[i])**2 + (robots[k][1]-Ly[i])**2) < R**2) or not(0 <= Lx[i] <= 2000 and 0 <= Ly[i] <= 3000):
                                #print(robots[k][0], Lx[i], robots[k][1], Ly[i])
                                check = 0
                        if check:
                            if ((Lx[i]-POS_ROBOT_X != 0 or Ly[i]-POS_ROBOT_Y != 0)):
                                robots.append([Lx[i], Ly[i]])
                else:
                    spots.append(
                        {'pos': (Lx[i], Ly[i]), 'size': 5, 'pen': None, 'brush': 'r', 'symbol': 'o'})

            # print(pos)
            Data.setData(spots)
            L.clear()
            print(len(robots))
            robots.clear()
        else:
            L.clear()
        spots.clear()
        robots.clear()
        QtGui.QApplication.processEvents()


QtGui.QApplication.processEvents()
app.exec_()
