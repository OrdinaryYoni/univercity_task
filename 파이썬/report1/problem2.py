import csv

def meanIris(data):
    sums = [0,0,0,0]
    mean = []
    cnt = 0
    for line in data:
        if line == data[0]:
            continue
        for i in range(4):
            sums[i]+=float(line[i])
        cnt += 1
    for i in range(4):
        mean.append(f'{sums[i]/cnt:.2f}')

    return mean

def meanSetosa(data):
    sums = [0,0,0,0]
    mean = []
    cnt = 0
    for line in data:
        if line == data[0]:
            continue
        if line[4] != 'Setosa':
            continue
        for i in range(4):
            sums[i]+=float(line[i])
        cnt += 1
    for i in range(4):
        mean.append(f'{sums[i]/cnt:.2f}')

    return mean

def meanVersicolor(data):
    sums = [0,0,0,0]
    mean = []
    cnt = 0
    for line in data:
        if line == data[0]:
            continue
        if line[4] != 'Versicolor':
            continue
        for i in range(4):
            sums[i]+=float(line[i])
        cnt += 1
    for i in range(4):
        mean.append(f'{sums[i]/cnt:.2f}')

    return mean

def meanVirginica(data):
    sums = [0,0,0,0]
    mean = []
    cnt = 0
    for line in data:
        if line == data[0]:
            continue
        if line[4] != 'Virginica':
            continue
        for i in range(4):
            sums[i]+=float(line[i])
        cnt += 1
    for i in range(4):
        mean.append(f'{sums[i]/cnt:.2f}')

    return mean

def readFile(filename):
    data = []
    with open(filename,'r',newline='') as f:
        reader = csv.reader(f)
        print("iris.csv:")
        for row in reader:
            print([s.strip() for s in row])
            data.append([s.strip() for s in row])
    return data

def writeFile(filename, data, mean_data):
    with open(filename,'w',newline='') as f:
        writer = csv.writer(f)
        for row in data:
            writer.writerow(row)

        writer.writerow(['iris.mean','setosa.mean','versicolor.mean','virginica.mean'])
        for row in mean_data:
            writer.writerow(row)
    

def main():
    data = readFile('iris.csv')
    iris_mean, setosa_mean, versicolor_mean, virginica_mean = meanIris(data), meanSetosa(data),meanVersicolor(data), meanVirginica(data)
    print(f'iris_mean: {iris_mean}')
    print(f'setosa_mean: {setosa_mean}')
    print(f'versicolor_mean: {versicolor_mean}')
    print(f'virginica_mean: {virginica_mean}')
    mean = [iris_mean, setosa_mean, versicolor_mean, virginica_mean]
    writeFile('result.csv',data, mean)
    
if __name__ == '__main__':
    main()


