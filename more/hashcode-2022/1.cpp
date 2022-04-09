#include <bits/stdc++.h>
using namespace std;

vector<string> files{"./input/a_an_example.in.txt", "./input/b_better_start_small.in.txt", "./input/c_collaboration.in.txt",
	"./input/d_dense_schedule.in.txt", "./input/e_exceptional_skills.in.txt", "./input/f_find_great_mentors.in.txt"};

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
	vector<int> levels;
};

struct Project {
	string name;
	int days, score, bestBefore;
	vector<Skill> roles;
};

struct Comp {
	int skill;
	Comp() {}
	Comp(int skill) : skill{skill} {}

	bool operator() (Contributor* c1, Contributor* c2) const {
		return c1->levels[skill] < c2->levels[skill];
	}
};

struct Output {
	string progetto;
	vector<string> nomi;
};

ifstream in;
ofstream out;

int numContrib, numProj;
vector<Contributor> contribs;
vector<Project> projects;
DoppiaMappa<string, int> skillNames;
vector<set<Contributor*, Comp>> devsPerSkill;
vector<Output> soluzione;

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
		contribs[c].levels.resize(skillNames.uno.size());
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


void setupDevsPerSkill() {
	devsPerSkill.resize(0);
	for (int i = 0; i < skillNames.uno.size(); ++i) {
		devsPerSkill.push_back(set<Contributor*, Comp>{Comp{i}});
	}

	for (int c = 0; c < numContrib; ++c) {
		for (auto&& skill : contribs[c].skills) {
			devsPerSkill[skill.name].insert(&contribs[c]);
		}
	}
}

void gridone() {
	struct ProgInCod {
		int tempofine;
		set<Contributor*> persone;

		bool operator<(const ProgInCod& o) const {
			return tempofine > o.tempofine;
		}
	};

	soluzione.resize(0);
	vector<int> indiciProjects(numProj);
	iota(indiciProjects.begin(), indiciProjects.end(), 0);
	int progettiFatti = 0;
	int tempo = 0;
	priority_queue<ProgInCod> finiProgetti;

	auto rimuoviProgetto = [&](int& p) {
		swap(indiciProjects[p], indiciProjects.back()); // rimuoviamo il progetto
		indiciProjects.pop_back();
		--p;
	};

	bool celafacciamo = true;
	while (celafacciamo || finiProgetti.size() > 0) {
		while (!finiProgetti.empty() && finiProgetti.top().tempofine <= tempo) {
			set<Contributor*> persone = finiProgetti.top().persone;
			for (auto scelto:persone){
				for (int i = 0; i < devsPerSkill.size(); ++i) {
					if (scelto->levels[i] > 0) {
						devsPerSkill[i].insert(scelto);
					}
				}
			}
			finiProgetti.pop();
		}

		celafacciamo = false; // TODO
		for (int p = 0; p < indiciProjects.size(); ++p) {
			Project& proj = projects[indiciProjects[p]];
			if (proj.score + min(-tempo + proj.bestBefore, 0) <= 0) {
				rimuoviProgetto(p);
				continue;
			}

			set<Contributor*> scelti;
			vector<Contributor*> sceltiOrd;
			for (int r = 0; r < proj.roles.size(); ++r) {
				Contributor cmp;
				cmp.levels.resize(proj.roles[r].name + 1);
				cmp.levels[proj.roles[r].name] = proj.roles[r].level;
				auto it = devsPerSkill[proj.roles[r].name].lower_bound(&cmp);

				// TODO -1

				while (it != devsPerSkill[proj.roles[r].name].end()) {
					if (scelti.count(*it)) {
						++it;
					} else {
						break;
					}
				}

				if (it == devsPerSkill[proj.roles[r].name].end()) {
					// impossibile al momento
					break;
				}

				scelti.insert(*it);
				sceltiOrd.push_back(*it);
			}

			if (scelti.size() < proj.roles.size()) {
				continue; // infattibile
			}

			vector<string> contributorNames;
			for (auto scelto:sceltiOrd){
				contributorNames.push_back(scelto->name);
				for (auto&& dpc : devsPerSkill) {
					dpc.erase(scelto);
				}
			}
			celafacciamo=true;
			soluzione.push_back(Output{proj.name, contributorNames});
			finiProgetti.push(ProgInCod{tempo + proj.days, std::move(scelti)});
			rimuoviProgetto(p);
		}
		++tempo;
	}
}

void scriviOutput() {
	out << soluzione.size() << endl;
	for(int i = 0; i < soluzione.size(); i++) {
		out << soluzione[i].progetto << endl;
		for(int j = 0; j < soluzione[i].nomi.size(); j++) {
			out << soluzione[i].nomi[j] << " ";
		}
		out << endl;
	}
}


int main(int argc, char const* argv[]) {
	in = ifstream{files[argv[1][0] - 'a']};
	out = ofstream{argv[1] + string(".txt")};
	leggiInput();
	setupDevsPerSkill();
	gridone();
	scriviOutput();
}
