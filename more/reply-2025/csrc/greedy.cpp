#include "template.cpp"

using namespace std;

// Compile without debug: g++ -O3 -Wall -Wpedantic -Wextra -DDEBUG solve.cpp -o solve.out
// Compile with debug: g++ -Wall -Wpedantic -Wextra -fsanitize=address -g -DDEBUG solve.cpp -o solve.out

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int randInt(int L, int R) {
  return std::uniform_int_distribution<int>(L, R)(rng);
}

int getIndex(const Resource &r) {
  if (r.T == ResourceType::A) {
    return 0;
  } else if (r.T == ResourceType::B) {
    return 1;
  } else if (r.T == ResourceType::C) {
    return 2;
  } else if (r.T == ResourceType::D) {
    return 3;
  } else if (r.T == ResourceType::E) {
    return 4;
  } else if (r.T == ResourceType::X) {
    return 5;
  }
  assert(false);
}

#define ll long long 
ll apply1(ll x, int percentage) {
  return x + (x * percentage) / 100;
}

struct Effect {
  int effectAdd = 0; // aggiungere case 
  int effectCutOff = 0; // cambia cutoff [T_min, T_max]
  int effectProfit = 0; // 
  int effectEnergy = 0; // energia cumulativa

  ll profit = 0; 
  int houseActive = 0;
  ll costMaintainance = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> activeProfitable; // tempo di quelli che producono profitto
  
  void removeActiveProfitable(int T) {
    while (activeProfitable.size()) {
      auto [time, cost]  = activeProfitable.top();
      if (time < T) {
        // remove it
        profit -= cost;
        activeProfitable.pop();
      } else {
        return;
      }
    }
  }

  ll getHouseActive() {
    return houseActive + apply1(houseActive, effectAdd);
  }

  void addResources(int time, const Resource &r) {
    if (r.T == ResourceType::A) {
      effectAdd += r.E;
    } else if (r.T == ResourceType::B) {
      effectCutOff += r.E;
    } else if (r.T == ResourceType::D) {
      effectProfit += r.E;
    } else if (r.T == ResourceType::E) {
      effectEnergy += r.E;
    }
    houseActive += r.U;
    activeProfitable.push({time + r.W, r.U});
    costMaintainance += r.M;
  }

  void removeResource(const Resource &r) {
    if (r.T == ResourceType::A) {
      effectAdd -= r.E;
    } else if (r.T == ResourceType::B) {
      effectCutOff -= r.E;
    } else if (r.T == ResourceType::D) {
      effectProfit -= r.E;
    } else if (r.T == ResourceType::E) {
      effectEnergy -= r.E;
    }
    houseActive -= r.U;
    costMaintainance -= r.M;
  }

  ll getCostMaintainance() {
    return costMaintainance + apply1(costMaintainance, effectEnergy);
  }
};

vector<vector<int>> solve(int D, vector<Resource>& resources, vector<Turn>& turns) {
  int SZ = 6;

  vector<vector<int>> ans;
  
  ll budget = D;

  // Create the resources
  vector<vector<Resource>> minCost(SZ);
  
  for (auto &x : resources) {
    minCost[getIndex(x)].push_back(x);
  }
  auto apply1SortCost = [&](int rimTurns) {
    // sort the minCost
    auto calcCost = [&](const Resource &r) {
      int cost = min(r.L, rimTurns) * r.M;
      return r.A + cost;
    };

    for (int i = 0; i < SZ; ++i) {
      auto &v = minCost[i];
      sort(v.begin(), v.end(), [&](const Resource &a, const Resource &b) {
        int x = calcCost(a);
        int y = calcCost(b);
      
        if (x != y) {
          return x < y;
        }
        
        // just sort by the percentage
        return a.E > b.E;
      });
    }
  };

  apply1SortCost(turns.size());
  
  vector<priority_queue<int>> times(SZ);

  Effect effect;
  
  int T = turns.size();
  for (int turn = 0; turn < T; ++turn) {
    vector<int> choice;
    auto [minCut, maxCut, reward] = turns[turn];
  
    // choice
    for (int i = 0; i < 50; ++i) { 
      int idx = randInt(0, SZ - 1);
      if (idx == 2 || idx == 4) { // don't choose C for now
        continue;
      }

      if (minCost[idx].empty()) {
        continue;
      }
      deb("Idx ", idx);
      deb(minCost[idx]);
      auto &v = minCost[idx];
      if (v[0].A > budget) {
        continue;
      }
      
      budget -= v[0].A; // per attivarlo
      effect.addResources(turn, v[0]);
      deb("DBG ", v[0]);
      deb("IdxPush ", v[0].I);
      times[idx].push(turn + v[0].L);   
      choice.push_back(v[0].I);  
    }

    minCut = apply1(minCut, effect.effectCutOff);
    maxCut = apply1(maxCut, effect.effectCutOff);

    // change the budget
    ll P = 1LL * reward * effect.getHouseActive();
    budget += apply1(P, effect.effectProfit);
    // remove the cost mantainance
    budget -= effect.getCostMaintainance();
    effect.removeActiveProfitable(turn);
    {
      // remove
      for (int i = 0; i < SZ; ++i) {
        while (times[i].size()) {
          int time = times[i].top();
          if (time <= turn) {
            times[i].pop();
            effect.removeResource(minCost[i][0]);
          } else {
            break;
          }
        }
      }
    }
    ans.push_back(choice);
  }

  int prova = eval(D, resources, turns, ans);
  deb(prova);
  return ans;
}