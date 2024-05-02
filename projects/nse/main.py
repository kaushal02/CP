import pandas as pd
import numpy as np

def MA(df, nDays, key = "Close"):
    MAKey = "MA" + str(nDays)
    tempKey = key + ".cumsum"
    df[tempKey] = np.cumsum(df[key])
    df[MAKey] = 0.0
    df[MAKey][nDays:] = ((df[tempKey][nDays:].to_numpy() - df[tempKey][:-nDays].to_numpy()) / nDays).round(2)
    df.drop(tempKey, axis=1, inplace=True)
    return df

df = pd.read_csv('nifty50/2023.csv')
df = MA(df, 3)
df = MA(df, 10)
df = MA(df, 20)
print(df)