from os import listdir

filename = [f for f in listdir('./') if '.h' in f or '.cpp' in f]

cnt = 0
for file in filename:
    cnt += len(open(file, 'rt').readlines())
print cnt