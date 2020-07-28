# Python Pandas

``` python
import pandas as pd

s = pd.Series([1, 2, 3, 4])
print(s)
df = pd.DataFrame({
    'A': 1,
    'B': [1, 2, 3, 4],
    'C': 0,
    'D': [4, 3, 2, 1]
})
print(df)

print(df.head(2))
print(df.tail(2))
print(df.T)

arr = s.array
mat = df.to_numpy()
print(arr, mat, sep='\n')

print(df.describe())
print(df.sort_index(axis=1, ascending=False))
print(df.sort_values(by='D'))

# df = pd.read_csv('filename')
# df.to_csv('filename')
# df = pd.read_excel('filename')
# df.to_excel('filename')

# big csv file
# chunks = pd.read_csv('filename', chunksize=30)
# for chunk in chunks:
#     pass
# or
# reader = pd.read_table('filename', iterator='True')
# status = True
# while status:
#     try:
#         chunk = reader.get_chunk()
#     except StopIteration:
#         status = False

# df.loc(tags)
# df.iloc(indexes)
# df.concat, df.append
# df.apply(f)

# df.dropna()
# df.fillna()

````