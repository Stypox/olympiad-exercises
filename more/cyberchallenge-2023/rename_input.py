import os
for txt in os.listdir():
    if txt.endswith(".txt") and "output" not in txt and txt != "input.txt":
        os.rename(txt, "input.txt")
        break
