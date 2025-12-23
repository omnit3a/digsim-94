// player.c
// handles the player and their stats and info and whatnot
// 
// 
// created: 21/12/2025

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// external libraries

// internal headers
#include <player.h>
#include <e_world.h>

struct player_info_s player_info = {
  MAP_WIDTH/2,    // x_pos
  MAP_LENGTH/2,    // y_pos
  0,    // x_facing
  0,    // y_facing
  20,   // health
  0,    // score
  1,    // lvl
  false // is_holding_torch
};

struct player_skills_s player_skills = {
  1, // mining
  1, // trading
  2, // attack
  2  // defense
};

struct player_info_s player_get_info () {
  return player_info;
}

struct player_skills_s player_get_skills () {
  return player_skills;
}

void player_set_info (struct player_info_s new_info) {
  player_info = new_info;
}

void player_set_skills (struct player_skills_s new_skills) {
  player_skills = new_skills;
}

void player_level_up () {
  player_skills.mining  = player_skills.mining  + player_info.lvl;
  player_skills.trading = player_skills.trading + player_info.lvl;
  player_skills.attack  = player_skills.attack  + player_info.lvl + 1;
  player_skills.defense = player_skills.defense + player_info.lvl + 1;
}
