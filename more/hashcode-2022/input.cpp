#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B>
struct DoppiaMappa{
	map<A, B> uno;
	map<B, A> due;

	B atPrimo(const A& a) {
		return uno[a];
	}

	A atSecon(const B& b) {
		return due[b];
	}

	void add(const A& a, const B& b) {
		uno[a] = b;
		due[b] = a;
	}

	void removePrimo(const A& a) {
		const B& b = uno[a];
		uno.erase(a);
		due.erase(b);
	}

	void removeSecon(const B& b) {
		const A& a = due[b];
		uno.erase(a);
		due.erase(b);
	}
};

struct Skill {
	int name;
	int level;
};

struct Contributor {
	string name;
	vector<Skill> skills;
	vector<int> levels(1000, 0);
};

struct Project {
	string name;
	int days, score, bestBefore;
	vector<Skill> roles;
};

ifstream in;
ofstream out{"output.txt"};

int numContrib, numProj;
vector<Contributor> contribs;
vector<Project> projects;
DoppiaMappa<string, int> skillNames;

vector<Skill> leggiSkills() {
	int N;
	in >> N;
	vector<Skill> res(N);
	for (int n = 0; n < N; ++n) {
		string name;
		in >> name >> res[n].level;

		if (!skillNames.uno.count(name)) {
			skillNames.add(name, skillNames.uno.size());
		}
		res[n].name = skillNames.atPrimo(name);
	}
	return res;
}

void leggiInput() {
	in >> numContrib >> numProj;

	contribs.resize(numContrib);
	for (int c = 0; c < numContrib; ++c) {
		in >> contribs[c].name;
		contribs[c].skills = leggiSkills();
	}

    for(int c = 0; c < numContrib; c++)
    {
        for(Skill skill : contribs[c].skills)
        {
            contribs[c].levels[skill.name] = skill.level;
        }
    }

	projects.resize(numProj);
	for(int p = 0; p < numProj; ++p) {
		in >> projects[p].name >> projects[p].days >> projects[p].score
			>> projects[p].bestBefore;
		projects[p].roles = leggiSkills();
	}
}

int main(int argc, char const* argv[]) {
	in = ifstream{argv[1]};
	leggiInput();
	cout<<skillNames.uno.size()<<endl;
}