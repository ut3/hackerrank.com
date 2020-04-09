/*
 * Copyright 2020 J. Rick Ramstetter
 * rick.ramstetter@gmail.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *

 * https://www.hackerrank.com/challenges/magic-spells/problem
 * You are battling a powerful dark wizard. He casts his spells from a distance, giving you only a few seconds to react and conjure your counterspells. For a counterspell to be effective, you must first identify what kind of spell you are dealing with.
 * 
 * The wizard uses scrolls to conjure his spells, and sometimes he uses some of his generic spells that restore his stamina. In that case, you will be able to extract the name of the scroll from the spell. Then you need to find out how similar this new spell is to the spell formulas written in your spell journal.
 * 
 * Spend some time reviewing the locked code in your editor, and complete the body of the counterspell function.
 * 
 * Check Dynamic cast to get an idea of how to solve this challenge.
 * 
 * 
 * rick comment:
 * dynamic cast is trivial compared to longest common substring
 * this problem is nonsense, why is LCS here?!
*/

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};


void counterspell(Spell *spell) {

    #define RevealIfType(T, R) \
        do { if (dynamic_cast<T*>(spell)) {\
            dynamic_cast<T*>(spell)->R();\
            return; } } while(0)
    RevealIfType(Fireball, revealFirepower);
    RevealIfType(Frostbite, revealFrostpower);
    RevealIfType(Thunderstorm, revealThunderpower);
    RevealIfType(Waterbolt, revealWaterpower);

    string one = spell->revealScrollName();
    string two = SpellJournal::journal;

    auto lcs = [](string& s1, string& s2, int e1, int e2) -> int
    {
        vector<vector<int> > seen;
        {
            vector<int> s2v;
            s2v.resize(s2.length() + 1, -1);
            seen.resize(s1.length() + 1, s2v);
        }
        
        auto lcsimpl = [&seen](auto& lcsref, string& s1, string &s2, int e1, int e2) -> int
        {
            if (seen[e1][e2] < 0)
            {
                if (e1 >= s1.length() || e2 >= s2.length())
                    seen[e1][e2] = 0;

                else if (s1.at(e1) == s2.at(e2))
                    seen[e1][e2] = 1 + lcsref(lcsref, s1, s2, e1 + 1, e2 + 1);

                else
                {
                    int a = lcsref(lcsref, s1, s2, e1 + 1, e2);
                    int b = lcsref(lcsref, s1, s2, e1, e2 + 1);
                    seen[e1][e2] = a > b ? a : b;                     
                }
            }
            return seen[e1][e2];
        };
        int val = lcsimpl(lcsimpl, s1 , s2, e1, e2);
        return val;
    };

    cout << lcs(one, two, 0, 0) << endl;

}


class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
              else if(s == "water") {
             spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
