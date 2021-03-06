import os, sys, subprocess
from distutils.dir_util import copy_tree

def copyTreeCheck(source, destination):
	if os.path.exists(destination):
		x = input("The directory of this problem already exists, overwrite it? [y/n] ")
		if x not in ["y", "Y"]:
			return False

	copy_tree(source, destination)
	return True

def create(source, problem):
	destinationDir = None
	if source in ["o", "olinfo", "og", "olinfo-grader"]:
		sourceDir = "./src/template-olinfo" + ("/" if source in ["o", "olinfo"] else "-grader/")
		destinationDir = f"./olinfo/{problem}/"
		written = copyTreeCheck(sourceDir, destinationDir)

		if written:
			readme = f"{destinationDir}README.md"
			with open(readme, "r") as f: readmeCont = f.read()
			readmeCont = "".join(readmeCont.split("<!--")[1:])
			readmeCont = readmeCont.replace("$PROBLEM", f"{problem}")
			with open(readme, "w") as f: f.write(readmeCont)
	elif source in ["u", "uva"]:
		destinationDir = f"./uva/{problem}/"
		written = copyTreeCheck("./src/template-uva/", destinationDir)

		if written:
			tasks = f"{destinationDir}.vscode/tasks.json"
			with open(tasks, "r") as f: tasksCont = f.read()
			tasksCont = tasksCont.replace("$PROBLEM", problem)
			with open(tasks, "w") as f: f.write(tasksCont)
	else:
		print(f"Invalid source: {source}")
		return

	programs = ["code", "codium", "vscodium", "atom"]
	for program in programs:
		try:
			subprocess.check_output(["which", program])
			os.system(f"{program} {destinationDir}")
			break
		except: pass

def main(argv):
	if len(argv) != 3:
		print("Usage: template.py [o|olinfo|og|olinfo-grader|u|uva] PROBLEM")
	else:
		create(argv[1], argv[2])

if __name__ == "__main__":
	main(sys.argv)
