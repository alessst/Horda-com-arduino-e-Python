import pandas as pd
from pandas.io import excel

ex = pd.read_excel("Cenoura.xlsx")
di = dict(ex)

print(di["Luz"])

