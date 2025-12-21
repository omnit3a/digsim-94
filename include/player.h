#ifndef PLAYER_H_
#define PLAYER_H_

struct player_info_s {
  int x_pos;
  int y_pos;
  int health;
  int score;
  int lvl;
};

struct player_skills_s {
  int mining;
  int trading;
  int attack;
  int defense;
};

struct player_info_s player_get_info ();
struct player_skills_s player_get_skills ();

void player_set_info (struct player_info_s new_info);
void player_set_skills (struct player_skills_s new_skills);
void player_level_up (void);

#endif
