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
  Trainer main_player;
  vector<Trainer> gym_leaders;
  
public:


  // TODO: Add constructor here to initialize members
  League(std::ifstream &fin0, std::ifstream &fin1){    
    main_player = Trainer(fin0);

    int num_gyms;
    fin1 >> num_gyms;

    string ignore;
    fin1 >> ignore;
    
    for(int i = 0; i < num_gyms; i++){
      Trainer gym_leader = Trainer(fin1);
      gym_leaders.push_back(gym_leader);
    }
  }

  // TODO: Add member functions here

  simulate_league_battle(){
    for(const auto& gym_leader : gym_leaders){
      simulate_team_battle();
    }
  }

  simulate_team_battle(const Trainer * main_player, const Trainer * gym_leader){  
    Pokemon gym_leader_pokemon = gym_leader->choose_Pokemon();
    Pokemon main_player_pokemon = main_player->choose_Pokemon(gym_leader_pokemon.type());

    int gym_leader_active_roster_count = 5, main_player_active_roster_count = 5;
  
    while(gym_leader_active_roster_count && main_player_active_roster_count){
      
      bool battle_result = Pokemon_battle(main_player_pokemon, gym_leader_pokemon);
      if(battle_result){
        gym_leader_active_roster_count--;
      }
      else{
        main_player_active_roster_count--;
      }
    }
      
    rest_pokemon(&main_player);
    
  }

  rest_pokemon(const Trainer){
    main_player->reset();
  }

  print_battle_results(){
    
  }



  

  ~League() {
    // TODO: put code here to clean up by deleting all Trainer objects
    
  }
  
};

int main(int argc, char *argv[]) {

  if (argc != 3) {

    std::cout << "INVALID COMMAND" << endl;
    return 1;
  }

  string ashFile = argv[1];
  string leagueFile = argv[2];
  
  ifstream inf1;
  ifstream inf2;
  
  League(inf1, inf2);
  
  Simulate_league_battle();
  Simulate_team_battle();
  Print_battle_results();
  ~League();

  // TODO: Add code to read command line args and open file streams here
  


  // TODO: Create a League object, call function to run the simulation
  
  
  
}