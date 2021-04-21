from html.parser import HTMLParser
import json, functools

class UltimaParser(HTMLParser):
	def __init__(self):
		HTMLParser.__init__(self)
		self.inside = {}
		self.squadre = []

	def ins(self, tag):
		if isinstance(tag, list):
			res = True
			for t in tag:
				res &= self.ins(t)
			return res
		else:
			if tag in self.inside:
				return self.inside[tag]
			return False

	def handle_starttag(self, tag, attrs):
		self.inside[tag] = True
		if self.ins(["html", "body", "table", "tbody"]) and tag == "tr":
			self.squadre.append([])

	def handle_endtag(self, tag):
		self.inside[tag] = False

	def handle_data(self, data):
		data = data.strip()
		if data != "" and self.ins(["html", "body", "table", "tbody", "tr", "td"]):
			self.squadre[-1].append(data)


squadre = {}

precedentiData = json.loads(open("precedenti_gare.json").read())
for squadra in precedentiData["rounds"]:
	name = squadra["team"]["name"].strip()

	if name not in squadre:
		squadre[name] = []
	for points in squadra["rounds"]:
		if points is not None:
			squadre[name].append(points)


ultimaParser = UltimaParser()
ultimaParser.feed(open("ultima_gara.html").read())
for squadra in ultimaParser.squadre:
	points = 0
	for score in squadra [5:]:
		points += int(float(score))

	if squadra[1] not in squadre:
		squadre[squadra[1]] = []
	squadre[squadra[1]].append(points)


out = open("output.txt", "w")

squadre = sorted(squadre.items(), key=lambda data: functools.reduce(lambda x, y: x+y, data[1]), reverse=True)
pos = 1
average = 0
for squadra in squadre:
	allPoints = functools.reduce(lambda x, y: x+y, squadra[1])
	print(f"{pos:>3} -> {squadra[0]:<35}  {allPoints}  {squadra[1]}", file=out)
	average += allPoints
	pos += 1

average /= pos
print("Average:", average)