import random

f = open("input.txt").read()
lines = f.split("\n")

groups = [name for name in lines[0].split(" ")]

ppl = []
for line in lines[1:]:
   if line == "": continue
   data = line.split(" ")
   name = data[0]
   prefs = data[1:] + [None for i in range(len(groups) - len(data[1:]))]
   ppl.append((name, prefs))

sizes = [0 for i in range(len(groups))]
for i in range(len(ppl)):
   sizes[i % len(sizes)] += 1
print(sizes)

bestscore = 468732587642
bestgroup = []
for i in range(1000):
   random.shuffle(ppl)
   currg = 0
   lastp = 0

   score = 0
   for p in range(len(ppl)):
      if p-lastp >= sizes[currg]:
         lastp=p
         currg+=1
      groupname = groups[currg]

      for pref in ppl[p][1]:
         if pref == groupname:
            break
         score+=1

   if score < bestscore:
      bestscore = score
      bestgroup = ppl.copy()

currg = 0
lastp = 0
for p in range(len(ppl)):
   if p-lastp >= sizes[currg]:
      lastp=p
      currg+=1
   groupname = groups[currg]
   print(bestgroup[p][0] + ": " + groupname)
