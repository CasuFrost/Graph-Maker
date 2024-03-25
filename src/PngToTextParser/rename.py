import os
path = 'PngText'
directory = os.fsencode(path)
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    if(filename[0]=='8' and len(filename)!=1):
        old_file = os.path.join(path, filename)
        a=filename.replace('8','')
        new_file = os.path.join(path, a)
        os.rename(old_file, new_file)
