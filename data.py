import numpy as np
import pandas as pd

# load the data
url = 'https://archive.ics.uci.edu/ml/machine-learning-databases/00292/Wholesale%20customers%20data.csv'
data = pd.read_csv(url)

# convert the dataframe to a NumPy array
data_np = data.to_numpy()

# calculate the mean of each column
mean = np.mean(data_np, axis=0)
print("Mean of each column:", mean)

# calculate the standard deviation of each column
std = np.std(data_np, axis=0)
print("Standard deviation of each column:", std)

# calculate the correlation matrix
corr = np.corrcoef(data_np, rowvar=False)
print("Correlation matrix:", corr)
