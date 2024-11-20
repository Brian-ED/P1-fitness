#include "src/frontend-brian/frontend.c"

int main() {
    start_app:

    if(has_logged_in()){
      goto welcome_back;
    } else {
      goto start_introduction;
    };

  welcome_back:
    if (Ask_do_you_want_to_change_weight()) {
      goto update_weight;
    } else {
      goto does_user_want_to_change_settings;
    }

  update_weight:
    // change weight here
    goto does_user_want_to_change_settings;

  does_user_want_to_change_settings:
    if (ask_does_user_want_to_change_days_or_exercises()) {
      goto change_days_or_exercises;
    } else {
      goto workout_program_is_constant;
    }
  workout_program_is_constant:

  change_days_or_exercises:

  rate_excersizes:

  start_introduction:

  introduction:

  return 0;
}