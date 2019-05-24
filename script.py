import subprocess, sys, os

def path():
    name = "lab_words"
    for user, dir, files in os.walk('.'):
        if name in files:
            name = user + '/' + name
            break
    return name

def run_prog(num):
    name = path()
    score = []
    for i in range(num):
        p = subprocess.Popen([name], stdin = subprocess.PIPE,stdout=subprocess.PIPE)
        for line in p.stdout:
            a = line
        a = a.decode('ascii')
        score.append(str(a).split()[1])

    return min(score)

def main(num):
    count = run_prog(num)
    print("min": count)

if __name__ == '__main__':
	if len(sys.argv)>0:
		main(int(sys.argv[1]))
