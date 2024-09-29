#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>

#include "Pokemon.hpp"
#include "Trainer.hpp"

using namespace std;
class League {
private:
  // TODO: Add member variables here
  Trainer * player;
  vector<Trainer *> gym_leaders;
  int num_gym_leaders;
  vector<Trainer*> defeated;
  
public:
  // TODO: Add constructor here to initialize members
  League(std::ifstream &player_input, std::ifstream &gym_input) {
    player = Trainer_factory(player_input);

    string ignore;
    gym_input >> num_gym_leaders;
    gym_input >> ignore; // read in the word "leaders"

    for(int i = 0; i < num_gym_leaders; ++i) {
      gym_leaders.push_back(Trainer_factory(gym_input));
    }
  }

  // TODO: Add member functions here
  void simulate_league_battle(){
    // Face up against each gym leader
    for(int i = 0; i < gym_leaders.size(); ++i) {
      player->reset();
      Trainer *current_gym_leader = gym_leaders[i];

      cout << "-----" << *player << " vs. " << *current_gym_leader << "-----" << endl;

      // Team battle against that gym leader
      int num_wins = simulate_team_battle(current_gym_leader);

      cout << "Result: " << *player << "=" << num_wins << ", "
          << *current_gym_leader << "=" << 5 - num_wins << endl;

      if (num_wins >= 3) {
        defeated.push_back(current_gym_leader);
      }

      if (num_wins == 0 || num_wins == 5) {
        cout << "It's a clean sweep!" << endl;
      }

      cout << endl;
    }

    print_league_battle_results();
  }

  int simulate_team_battle(Trainer * current_gym_leader){  
    int num_wins = 0;
    for(int i = 0; i < 5; ++i) {
      // Each individual pokemon battle
      Pokemon enemy = current_gym_leader->choose_pokemon();
      cout << *current_gym_leader << " chooses " << enemy << endl;
      Pokemon p = player->choose_pokemon(enemy.get_type());
      cout << *player << " chooses " << p << endl;
      if (Pokemon_battle(p, enemy)) {
        cout << p << " defeats " << enemy << endl << endl;
        ++num_wins;
      }
      else {
        cout << enemy << " defeats " << p << endl << endl;
      }
    }

    return num_wins;
  }

  void print_league_battle_results(){
    cout << *player << " won " << defeated.size() << " matches by defeating:" << endl;
    for(int i = 0; i < defeated.size(); ++i) {
      cout << *defeated[i] << endl;
    }
  }

  ~League() {
    // TODO: put code here to clean up by deleting all Trainer objects
    delete player;
    for(size_t i = 0; i < gym_leaders.size(); ++i) {
      delete gym_leaders[i];
    }
  }
  
};

int main(int argc, char *argv[]) {
  // TODO: Add code to read command line args and open file streams here
  if (argc != 3) {
    cout << "Usage: battle.exe PLAYER_FILE GYM_LEADERS_FILE" << endl;
    return 1;
  }

  std::string player_in_name = argv[1];
  std::string gym_leaders_in_name = argv[2];

  std::ifstream player_in(player_in_name);
  if ( !player_in.is_open() ) {
    cout << "Unable to open " << player_in_name << endl;
    return 1;
  }
  std::ifstream gym_in(gym_leaders_in_name);
  if ( !gym_in.is_open() ) {
    cout << "Unable to open " << gym_leaders_in_name << endl;
    return 1;
  }

  // TODO: Create a League object, call function to run the simulation
  League my_league = League(player_in, gym_in);

  my_league.simulate_league_battle();
}