import os

User="user1"
OldPwd="!@#$%^&"
NewPwd="def"
FilePath="./change_text_in_file.txt"

str ="sed -i '' 's:" + User + "\\:" + OldPwd + ":" + User + "\\:" + NewPwd + ":g' " + FilePath
print(str)
os.system(str)
