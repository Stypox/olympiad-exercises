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
    vector<int> levels;
    int libero = 0;

    Contributor(){
        levels.resize(1000, 0);
    }
};

struct Project {
	string name;
	int days, score, bestBefore;
	vector<Skill> roles;
};

struct Output {
    string progetto;
    vector<string> nomi;
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

void scriviOutput(vector<Output> soluzione) {
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
	in = ifstream{argv[1]};
    //out = ofstream{argv[2]};
	leggiInput();

    vector<Output> soluzione;
	//cout<<skillNames.uno.size()<<endl;

    for(int i=0; i<numProj; i++)
    {
        bool preso = 1;
        Output tentativo;
        tentativo.progetto = projects[i].name;

        int tempo = 0;
        vector<bool> personaPresa(1501, 0);
        vector<int> candidati(100, 1500);

        for(int j=0; j<projects[i].roles.size(); j++)
        {
            int tempo2 = 20000*100000;

            for(int k=0; k<numContrib; k++)
            {
                if(contribs[k].levels[projects[i].roles[j].name] >= projects[i].roles[j].level && !personaPresa[k])
                {
                    //proviamo a prenderla
                    if(contribs[k].libero < tempo2)
                    {
                        tempo2 = contribs[k].libero;
                        personaPresa[candidati[j]] = false;
                        candidati[j] = k;
                        personaPresa[k] = true;
                    }
                }
            }

            if(candidati[j] == 1500)
            {
                preso = false;
                break;
            }

            tempo = max(tempo, tempo2);
        }

        //cout<<"here\n";

        if(!preso) continue;

        tempo += projects[i].days;

        for(int j=0; j<projects[i].roles.size(); j++)
        {
            int persona = candidati[j];
            contribs[persona].libero = tempo;
            if(contribs[persona].levels[projects[i].roles[j].name] = projects[i].roles[j].level)
            {
                contribs[persona].levels[projects[i].roles[j].name]++;
                //gestire skills
            }

            tentativo.nomi.push_back(contribs[persona].name);
        }



        soluzione.push_back(tentativo);

    }

    scriviOutput(soluzione);
}