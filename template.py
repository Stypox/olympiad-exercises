import os, sys, subprocess, shutil

def checkExistsConfirmOverwrite(destination):
	if os.path.exists(destination):
		x = input("The file/directory of this problem already exists, overwrite it? [y/n] ")
		if x not in ["y", "Y"]:
			return False
	return True

def copyTreeCheck(source, destination):
	if checkExistsConfirmOverwrite(destination):
		shutil.copytree(source, destination, dirs_exist_ok=True)
		return True
	return False

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
	elif source in ["k", "kattis"]:
		destinationDir = "./kattis/"
		destinationFile = f"{destinationDir}{problem}.cpp"
		if checkExistsConfirmOverwrite(destinationFile):
			shutil.copy2("./src/template-kattis/template.cpp", destinationFile)
	else:
		print(f"Invalid source: {source}")
		return

	programs = ["codium", "code", "vscodium", "atom"]
	for program in programs:
		try:
			subprocess.check_output(["which", program], stderr=subprocess.STDOUT)
			os.system(f"{program} {destinationDir}")
			break
		except: pass

def main(argv):
	if len(argv) != 3:
		print("Usage: template.py [o|olinfo|og|olinfo-grader|u|uva|k|kattis] PROBLEM")
	else:
		create(argv[1], argv[2])

if __name__ == "__main__":
	main(sys.argv)
