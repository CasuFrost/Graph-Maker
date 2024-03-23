import os
path = 'PngLetters'
directory = os.fsencode(path)
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    print(filename)
    old_file = os.path.join(path, filename)
    new_file = os.path.join(path, '8'+filename)
    os.rename(old_file, new_file)