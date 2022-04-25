import matplotlib.pyplot as plt
import csv
data = []
with open('output.csv',newline='') as csvfile:
	spamreader = csv.reader(csvfile,delimiter=',')
	for row in spamreader:
		data.append(row)
def getcolumn(data,col,start = 0):
	column = []
	for i in range(start,len(data)):
		column.append(float(data[i][col]))
	return column

X,S,I,E,N,R,D = getcolumn(data,0,1),getcolumn(data,1,1),getcolumn(data,2,1),getcolumn(data,3,1),getcolumn(data,4,1),getcolumn(data,5,1),getcolumn(data,6,1)
plt.plot(X,S,label="Sains")
plt.plot(X,I,label="Infectés")
plt.plot(X,E,label="Incubation")
plt.plot(X,R,label="Réémis")
plt.plot(X,D,label="Morts")
plt.plot(X,N,label="Population")
plt.legend(loc="upper right")
plt.xlabel("Jours")
plt.ylabel("Part de la population")
plt.show()

